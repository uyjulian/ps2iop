
#include "irx_imports.h"

// Based on the module from SDK 3.1.0.
IRX_ID("multitap_manager", 3, 16);

static int get_slots(int port);
int _start(int ac, char **av);
void _deinit(void);
s32 mtapPortOpen(u32 port);
s32 mtapPortClose(u32 port);
s32 mtapGetConnection(u32 port);
s32 mtapGetSlotNumber(u32 port);
int mtapChangeSlot(u32 port, u32 slot);
static int InitRpcServers(int thpri);

struct mtap_state
{
	int m_open;
	int m_connection;
	int m_slots;
};

extern struct irx_export_table _exp_mtapman;
static int g_ee_status_magic = 0;
static int g_event_flag;
static int g_main_thid;
static int g_ee_status_sema;
// Unofficial: move state into interleaved structure
static struct mtap_state g_mtap_state[4];
static sio2_transfer_data_t g_sio2_tdata;
static int g_sio2_inbuf[64];
static int g_sio2_outbuf[64];
static int g_ee_status_eeaddr;
static int g_ee_status_dma_trid;
static int g_ee_status_data[32];
static int g_sif_thid;

// Removed empty function with stack manipulation

static s32 read_stat6c_bit(u32 bit, const sio2_transfer_data_t *tdata)
{
	// Unofficial: calculate shift
	return ( bit < 16 ) ? ((tdata->stat6c >> (16 + bit)) & 1) : 0;
}

static void get_slot_number_setup_td(u32 port, u32 reg)
{
	int i;

	// Unofficial: combine writes
	g_sio2_tdata.port_ctrl1[port | 2] = 5 | (5 << 8) | (2 << 16) | (0xFF << 24);
	g_sio2_tdata.port_ctrl2[port | 2] = 0x64 | (3 << 16);
	g_sio2_tdata.regdata[reg] = ((port | 2) & 3) | 0x180640;
	for ( i = 0; i < 6; i += 1 )
		g_sio2_tdata.in[i + g_sio2_tdata.in_size] = 0;
	g_sio2_tdata.in[g_sio2_tdata.in_size] = 0x21;
	g_sio2_tdata.in[g_sio2_tdata.in_size + 1] = 0x12 | (!!( port >= 2 ));
	g_sio2_tdata.in_dma.addr = NULL;
	g_sio2_tdata.out_dma.addr = NULL;
	g_sio2_tdata.in_size += 6;
	g_sio2_tdata.out_size += 6;
}

static s32 get_slot_number_check_td(u32 bit)
{
	s32 retval;
	int i;

	retval = ( read_stat6c_bit(bit, &g_sio2_tdata) == 1 ) ? -1 : (( g_sio2_tdata.out[5] != 0x66 && !g_sio2_tdata.out[4] ) ? g_sio2_tdata.out[3] : -2);
	for ( i = 0; i < 0xFA; i += 1 )
		g_sio2_tdata.out[i] = g_sio2_tdata.out[i + 6];
	g_sio2_tdata.out_size -= 6;
	return retval;
}

static s32 get_slot_number(u32 port, u32 retries)
{
	int i;
	int j;

	if ( port >= (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])) )
		return -3;
	if ( !g_mtap_state[port].m_open )
		return -4;
	for ( i = 0; i <= (int)retries; i += 1 )
	{
		s32 slots;

		sio2_mtap_transfer_init();
		g_sio2_tdata.in_size = 0;
		g_sio2_tdata.out_size = 0;
		for ( j = 0; j < (int)(sizeof(g_sio2_tdata.regdata)/sizeof(g_sio2_tdata.regdata[0])); j += 1 )
			g_sio2_tdata.regdata[j] = 0;
		get_slot_number_setup_td(port, 0);
		sio2_transfer2(&g_sio2_tdata);
		slots = get_slot_number_check_td(0);
		if ( slots == -2 )
		{
			sio2_transfer_reset2();
			return -4;
		}
		if ( slots >= 0 )
		{
			sio2_transfer_reset2();
			return slots;
		}
		sio2_transfer_reset2();
	}
	return -4;
}

static s32 change_slot_setup_td(unsigned int port, u8 slot)
{
	int j;
	int i;

	for ( j = 0; j < 10; j += 1 )
	{
		// Unofficial: combine writes
		g_sio2_tdata.port_ctrl1[port | 2] = 5 | (5 << 8) | (2 << 16) | (0xFF << 24);
		g_sio2_tdata.port_ctrl2[port | 2] = 0x64 | (3 << 16);
		g_sio2_tdata.regdata[0] = (port & 1) | 0x742 | 0x1C0000;
		g_sio2_tdata.regdata[1] = 0;
		for ( i = 0; i < 7; i += 1 )
			g_sio2_tdata.in[i] = 0;
		g_sio2_tdata.in[0] = 0x21;
		g_sio2_tdata.in[1] = 0x21 + !!( port >= 2 );
		g_sio2_tdata.in[2] = slot;
		g_sio2_tdata.in_size = 7;
		g_sio2_tdata.out_size = 7;
		g_sio2_tdata.in_dma.addr = NULL;
		g_sio2_tdata.out_dma.addr = NULL;
		sio2_transfer2(&g_sio2_tdata);
		if ( read_stat6c_bit(0, &g_sio2_tdata) != 1 && g_sio2_tdata.out[5] != 0x66 )
			return 1;
	}
	return 0;
}

static int change_slot(s32 *arg)
{
	int i;

	for ( i = 0; i < (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])); i += 1 )
	{
		if ( arg[i] == -1 )
			arg[i + 4] = 0;
		else if ( arg[i] < 0 )
			arg[i + 4] = -1;
		else if ( !g_mtap_state[i].m_open || !mtapGetConnection(i) )
			arg[i + 4] = arg[i] ? -1 : 1;
		else if ( arg[i] >= g_mtap_state[i].m_slots )
			arg[i + 4] = -1;
		else
		{
			arg[i + 4] = ( change_slot_setup_td(i, arg[i]) == 1 ) ? 1 : -1;
			if ( arg[i + 4] == -1 )
				g_mtap_state[i].m_connection = 0;
		}
	}
	for ( i = 0; i < (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])); i += 1 )
		if ( arg[i + 4] < 0 )
			return 0;
	return 1;
}

static int set_mtap_state_ee_addr(int addr)
{
	WaitSema(g_ee_status_sema);
	if ( !addr )
	{
		if ( g_ee_status_eeaddr && g_ee_status_dma_trid )
			while ( sceSifDmaStat(g_ee_status_dma_trid) >= 0 )
				DelayThread(100);
		g_ee_status_dma_trid = 0;
	}
	g_ee_status_eeaddr = addr;
	SignalSema(g_ee_status_sema);
	return 1;
}

static int send_mtap_state_to_ee(void)
{
	int i;
	int trid;
	SifDmaTransfer_t dmat;
	int state;

	// Unofficial: remove unneeded zeroing of state
	WaitSema(g_ee_status_sema);
	if ( !g_ee_status_eeaddr || (g_ee_status_dma_trid && (sceSifDmaStat(g_ee_status_dma_trid) >= 0)) )
	{
		SignalSema(g_ee_status_sema);
		return 0;
	}
	g_ee_status_magic += 1;
	g_ee_status_data[0] = g_ee_status_magic;
	for ( i = 0; i < (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])); i += 1 )
	{
		g_ee_status_data[i + 2] = g_mtap_state[i].m_open;
		g_ee_status_data[i + 6] = mtapGetConnection(i);
		g_ee_status_data[i + 10] = get_slots(i);
	}
	g_ee_status_data[1] = 1;
	dmat.dest = (void *)g_ee_status_eeaddr;
	dmat.src = g_ee_status_data;
	dmat.size = sizeof(g_ee_status_data);
	dmat.attr = 0;
	CpuSuspendIntr(&state);
	trid = sceSifSetDma(&dmat, 1);
	CpuResumeIntr(state);
	g_ee_status_dma_trid = trid;
	SignalSema(g_ee_status_sema);
	return 1;
}

static void update_slot_numbers_thread(void *userdata)
{
	int i;
	u32 resbits;

	(void)userdata;
	while ( 1 )
	{
		WaitEventFlag(g_event_flag, 3, 0x11, &resbits);
		if ( (resbits & 2) )
			break;
		for ( i = 0; i < (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])); i += 1 )
		{
			if ( g_mtap_state[i].m_open == 1 )
			{
				s32 slots;

				slots = get_slot_number(i, ( mtapGetConnection(i) == 1 ) ? 10 : 0);
				g_mtap_state[i].m_connection = !!( slots >= 0 );
				g_mtap_state[i].m_slots = ( slots >= 0 ) ? slots : 1;
			}
		}
		send_mtap_state_to_ee();
	}
	SetEventFlag(g_event_flag, 4);
	ExitThread();
}

static int get_slots(int port)
{
	return g_mtap_state[port].m_slots;
}

// Unofficial: omit duplicate get_slots function

static void update_slot_numbers(void)
{
	SetEventFlag(g_event_flag, 1);
}

int _start(int ac, char **av)
{
	int cursifpriority;
	int curmainpriority;
	int i;
	iop_event_t evparam;
	iop_thread_t thparam;
	iop_sema_t semaparam;

	if ( RegisterLibraryEntries(&_exp_mtapman) || SetRebootTimeLibraryHandlingMode(&_exp_mtapman, 2) )
		return 1;
	// Unofficial: priority from local variable
	cursifpriority = 46;
	// Unofficial: priority from local variable
	curmainpriority = 20;
	g_ee_status_eeaddr = 0;
	g_ee_status_dma_trid = 0;
	for ( i = 1; i < ac; i += 1 )
	{
		if ( !strncmp("thpri=", av[i], 6) )
		{
			int j;

			j = 6;
			curmainpriority = ( isdigit(av[i][j]) ) ? strtol(&av[i][j], NULL, 10) : -1;
			for ( ; isdigit(av[i][j]); j += 1 );
			cursifpriority = ( av[i][j] == ','  && isdigit(av[i][j + 1]) ) ? strtol(&av[i][j + 1], NULL, 10) : -1;
			if ( (unsigned int)(curmainpriority - 9) >= 0x73 )
			{
				printf("MTAPMAN:invalid priority_main %d\n", curmainpriority);
				return 1;
			}
			if ( (unsigned int)(cursifpriority - 9) >= 0x73 )
			{
				printf("MTAPMAN:invalid priority_sif %d\n", cursifpriority);
				return 1;
			}
		}
		else
			// Unofficial: correct failure condition
			// Unofficial: removed call to empty function
			return 1;
	}
	// Unofficial: correct success condition when argv parsing loop ends
	if ( !InitRpcServers(cursifpriority) )
		// Unofficial: removed call to empty function
		return 1;
	evparam.attr = 2;
	evparam.bits = 0;
	g_event_flag = CreateEventFlag(&evparam);
	if ( g_event_flag <= 0 )
		// Unofficial: removed call to empty function
		return 1;
	thparam.attr = 0x2000000;
	thparam.thread = update_slot_numbers_thread;
	thparam.stacksize = 2048;
	// Unofficial: priority from local variable
	thparam.priority = curmainpriority;
	g_main_thid = CreateThread(&thparam);
	if ( g_main_thid <= 0 )
		// Unofficial: removed call to empty function
		return 1;
	StartThread(g_main_thid, NULL);
	semaparam.initial = 1;
	semaparam.attr = 0;
	semaparam.max = 16;
	g_ee_status_sema = CreateSema(&semaparam);
	if ( g_ee_status_sema < 0 )
		// Unofficial: removed call to empty function
		return 1;
	for ( i = 0; i < (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])); i += 1 )
	{
		mtapPortClose(i);
		g_mtap_state[i].m_slots = 1;
	}
	sio2_mtap_change_slot_set(change_slot);
	sio2_mtap_get_slot_max_set(get_slots);
	// Unofficial: use deduplicated get_slots function
	sio2_mtap_get_slot_max2_set(get_slots);
	sio2_mtap_update_slots_set(update_slot_numbers);
	g_sio2_tdata.in = (u8 *)g_sio2_inbuf;
	g_sio2_tdata.out = (u8 *)g_sio2_outbuf;
	return 0;
}

void _deinit(void)
{
	sio2_mtap_change_slot_set(NULL);
	sio2_mtap_get_slot_max_set(NULL);
	sio2_mtap_get_slot_max2_set(NULL);
	sio2_mtap_update_slots_set(NULL);
	set_mtap_state_ee_addr(0);
	WaitSema(g_ee_status_sema);
	DeleteSema(g_ee_status_sema);
}

s32 mtapPortOpen(u32 port)
{
	s32 slot;

	if ( port >= (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])) )
		return 0;
	g_mtap_state[port].m_open = 1;
	slot = get_slot_number(port, 10);
	g_mtap_state[port].m_connection = !!( slot >= 0 );
	g_mtap_state[port].m_slots = ( slot >= 0 ) ? slot : 1;
	return 1;
}

s32 mtapPortClose(u32 port)
{
	g_mtap_state[port].m_open = 0;
	g_mtap_state[port].m_connection = 0;
	return 1;
}

s32 mtapGetConnection(u32 port)
{
	return g_mtap_state[port].m_connection;
}

s32 mtapGetSlotNumber(u32 port)
{
	s32 retres;

	if ( port >= (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])) )
		return -1;
	if ( g_mtap_state[port].m_open != 1 )
		return 1;
	retres = get_slot_number(port, 10);
	return ( retres < 0 ) ? 1 : retres;
}

int mtapChangeSlot(u32 port, u32 slot)
{
	int i;
	s32 data[8];

	if ( port >= (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])) )
		return 0;
	if ( g_mtap_state[port].m_open != 1 )
		// Unofficial: removed call to empty function
		return 1;
	for ( i = 0; i < (int)(sizeof(g_mtap_state)/sizeof(g_mtap_state[0])); i += 1 )
		data[i] = -1;
	data[port] = slot;
	sio2_mtap_transfer_init();
	change_slot(data);
	sio2_transfer_reset2();
	// Unofficial: removed call to empty function
	return ( data[port + 4] < 0 ) ? 0 : 1;
}

static int set_main_thpriority(int priority)
{
	int retres;

	retres = ChangeThreadPriority(g_main_thid, priority);
	return ( retres >= 0 ) ? 0 : retres;
}

static int get_module_version(void)
{
	return _irx_id.v;
}

// Unofficial: remove thread priority related function

static int set_sif_thpriority(int priority)
{
	int retres;

	retres = ChangeThreadPriority(g_sif_thid, priority);
	return ( retres >= 0 ) ? 0 : retres;
}

// Unofficial: remove empty function

static void RpcServerHandlerOpen(u32 *buffer)
{
	buffer[1] = mtapPortOpen(buffer[0]);
}

static void RpcServerHandlerClose(u32 *buffer)
{
	buffer[1] = mtapPortClose(buffer[0]);
}

static void RpcServerHandlerSetWorkAddr(u32 *buffer)
{
	buffer[0] = set_mtap_state_ee_addr(buffer[1]);
}

static void RpcServerHandlerGetSlotNumber(u32 *buffer)
{
	buffer[1] = mtapGetConnection(buffer[0]);
}

static void RpcServerHandlerSetThreadPriority(u32 *buffer)
{
	buffer[2] = 0;
	if ( (u32)(buffer[0]) - 9 >= 0x73 )
	{
		printf("MTAPMAN:invalid priority_main %d\n", (int)buffer[0]);
		return;
	}
	if ( (u32)(buffer[1]) - 9 >= 0x73 )
	{
		printf("MTAPMAN:invalid priority_sif %d\n", (int)buffer[1]);
		return;
	}
	ChangeThreadPriority(0, 8);
	if ( set_main_thpriority(buffer[0]) < 0 )
		printf("MTAPMAN:error to set priority_main\n");
	else if ( set_sif_thpriority(buffer[1]) < 0 )
		printf("MTAPMAN:error to set priority_sif\n");
	else
		buffer[2] = 1;
}

static void RpcServerHandlerGetVersion(u32 *buffer)
{
	buffer[0] = get_module_version();
}

static void *Rpc80000900ServerHandler(int fno, void *buffer, int length)
{
	(void)length;

	// Unofficial: clean up parameters and return value
	switch ( fno )
	{
		case 0:
			// Unofficial: omit call to empty function
			break;
		case 1:
			RpcServerHandlerOpen((u32 *)buffer);
			break;
		case 2:
			RpcServerHandlerClose((u32 *)buffer);
			break;
		case 3:
			RpcServerHandlerGetSlotNumber((u32 *)buffer);
			break;
		case 4:
			RpcServerHandlerSetThreadPriority((u32 *)buffer);
			break;
		case 5:
			RpcServerHandlerGetVersion((u32 *)buffer);
			break;
		case 6:
			RpcServerHandlerSetWorkAddr((u32 *)buffer);
			break;
		default:
			Kprintf("invalid function code (%03x)\n", fno);
			break;
	}
	return buffer;
}

static void *Rpc80000901ServerHandler(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	RpcServerHandlerOpen((u32 *)buffer);
	return buffer;
}

static void *Rpc80000902ServerHandler(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	RpcServerHandlerClose((u32 *)buffer);
	return buffer;
}

static void *Rpc80000903ServerHandler(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	RpcServerHandlerGetSlotNumber((u32 *)buffer);
	return buffer;
}

static void *Rpc80000904ServerHandler(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	RpcServerHandlerSetThreadPriority((u32 *)buffer);
	return buffer;
}

static void *Rpc80000905ServerHandler(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	RpcServerHandlerGetVersion((u32 *)buffer);
	return buffer;
}

static void *Rpc800009FEServerHandler(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	((u32 *)buffer)[1] = mtapGetSlotNumber(((u32 *)buffer)[0]);
	return buffer;
}

static void *Rpc800009FFServerHandler(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;

	((u32 *)buffer)[2] = mtapChangeSlot(((u32 *)buffer)[0], ((u32 *)buffer)[1]);
	return buffer;
}

static void MtapServCommon(void *userdata)
{
	SifRpcDataQueue_t qd;
	SifRpcServerData_t sd[8];
	int sifbuf[8][32];

	(void)userdata;

	if ( !sceSifCheckInit() )
	{
		Kprintf("yet sif hasn't been init\n");
		sceSifInit();
	}
	sceSifInitRpc(0);
	sceSifSetRpcQueue(&qd, GetThreadId());
	sceSifRegisterRpc(&sd[0], 0x80000900, Rpc80000900ServerHandler, &sifbuf[0], NULL, NULL, &qd);
	// Unofficial: the following RPC are for backwards compatibility
	sceSifRegisterRpc(&sd[1], 0x80000901, Rpc80000901ServerHandler, &sifbuf[1], NULL, NULL, &qd);
	sceSifRegisterRpc(&sd[2], 0x80000902, Rpc80000902ServerHandler, &sifbuf[2], NULL, NULL, &qd);
	sceSifRegisterRpc(&sd[3], 0x80000903, Rpc80000903ServerHandler, &sifbuf[3], NULL, NULL, &qd);
	sceSifRegisterRpc(&sd[4], 0x80000904, Rpc80000904ServerHandler, &sifbuf[4], NULL, NULL, &qd);
	sceSifRegisterRpc(&sd[5], 0x80000905, Rpc80000905ServerHandler, &sifbuf[5], NULL, NULL, &qd);
	sceSifRegisterRpc(&sd[6], 0x800009FE, Rpc800009FEServerHandler, &sifbuf[6], NULL, NULL, &qd);
	sceSifRegisterRpc(&sd[7], 0x800009FF, Rpc800009FFServerHandler, &sifbuf[7], NULL, NULL, &qd);
	sceSifRpcLoop(&qd);
}

static int InitRpcServers(int thpri)
{
	iop_thread_t thparam;

	thparam.attr = 0x2000000;
	thparam.thread = MtapServCommon;
	// Unofficial: bump stack size for RPC data
	thparam.stacksize = 4096;
	// Unofficial: thread priority from parameter
	thparam.priority = thpri;
	g_sif_thid = CreateThread(&thparam);
	if ( g_sif_thid )
		StartThread(g_sif_thid, NULL);
	else
		Kprintf("mtapman: CreateThread Error\n");
	return !!g_sif_thid;
}
