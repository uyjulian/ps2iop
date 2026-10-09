
#include "irx_imports.h"

// Based on the module from SDK 3.1.0.
IRX_ID("multitap_manager", 3, 16);

static s32 read_stat6c_bit(u32 bit, const sio2_transfer_data_t *tdata);
static void get_slot_number_setup_td(u32 port, u32 reg);
static s32 get_slot_number_check_td(u32 bit);
static s32 get_slot_number(u32 port, u32 retries);
static s32 change_slot_setup_td(unsigned int port, u8 slot);
static int change_slot(s32 *arg);
static int do_set_work_addr_ee(int addr);
static int send_mtap_state_to_ee(void);
static void update_slot_numbers_thread(void);
static int get_slots(int port);
static void update_slot_numbers(void);
int _start(int ac, char **av);
void _deinit(void);
s32 mtapPortOpen(u32 port);
s32 mtapPortClose(u32 port);
s32 mtapGetConnection(u32 port);
s32 mtapGetSlotNumber_unused(u32 port);
int mtapChangeSlot_unused(u32 port, u32 slot);
static int do_set_main_priority_thread(int priority);
static int do_get_version(void);
static int do_set_sif_priority_thread(int priority);
static int do_set_sif_priority_thread_sif(int priority);
static void RpcServerHandlerOpen(u32 *buffer);
static void RpcServerHandlerClose(u32 *buffer);
static void RpcServerHandlerSetWorkAddr(u32 *buffer);
static void RpcServerHandlerGetSlotNumber(u32 *buffer);
static void RpcServerHandlerSetThreadPriority(u32 *buffer);
static void RpcServerHandlerGetVersion(u32 *buffer);
static void *RpcServerHandler(int fno, void *buffer, int length);
static void MtapServCommon(void);
static int InitRpcServers(void);

extern struct irx_export_table _exp_mtapman;
static int g_ee_magic_value = 0;
static int g_MtapServPriority = 46;
static int g_event_flag;
static int g_threadid_main;
static int g_sema_ee_set_work_addr;
static int g_update_slot_numbers_thpriority;
static int g_state_open[4];
static int g_state_getcon[4];
static int g_state_slots[4];
static sio2_transfer_data_t g_tdata;
static int g_in_buffer[64];
static int g_out_buffer[64];
static int g_ee_work_addr_value;
static int g_ee_work_addr_trid;
static int g_ee_data_contents[32];
static SifRpcDataQueue_t g_RpcServerQd;
static SifRpcServerData_t g_RpcServerSd;
static int g_threadid_rpc;
static int g_RpcServerSb[32];

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
	g_tdata.port_ctrl1[port | 2] = 5 | (5 << 8) | (2 << 16) | (0xFF << 24);
	g_tdata.port_ctrl2[port | 2] = 0x64 | (3 << 16);
	g_tdata.regdata[reg] = ((port | 2) & 3) | 0x180640;
	for ( i = 0; i < 6; i += 1 )
		g_tdata.in[i + g_tdata.in_size] = 0;
	g_tdata.in[g_tdata.in_size] = 0x21;
	g_tdata.in[g_tdata.in_size + 1] = 0x12 | (!!( port >= 2 ));
	g_tdata.in_dma.addr = NULL;
	g_tdata.out_dma.addr = NULL;
	g_tdata.in_size += 6;
	g_tdata.out_size += 6;
}

static s32 get_slot_number_check_td(u32 bit)
{
	s32 retval;
	int i;

	retval = ( read_stat6c_bit(bit, &g_tdata) == 1 ) ? -1 : (( g_tdata.out[5] != 0x66 && !g_tdata.out[4] ) ? g_tdata.out[3] : -2);
	for ( i = 0; i < 0xFA; i += 1 )
		g_tdata.out[i] = g_tdata.out[i + 6];
	g_tdata.out_size -= 6;
	return retval;
}

static s32 get_slot_number(u32 port, u32 retries)
{
	int i;
	int j;

	if ( port >= 4 )
		return -3;
	if ( !g_state_open[port] )
		return -4;
	for ( i = 0; i <= (int)retries; i += 1 )
	{
		s32 slots;

		sio2_mtap_transfer_init();
		g_tdata.in_size = 0;
		g_tdata.out_size = 0;
		for ( j = 0xF; j >= 0; j -= 1 )
			g_tdata.regdata[j] = 0;
		get_slot_number_setup_td(port, 0);
		sio2_transfer2(&g_tdata);
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
		g_tdata.port_ctrl1[port | 2] = 5 | (5 << 8) | (2 << 16) | (0xFF << 24);
		g_tdata.port_ctrl2[port | 2] = 0x64 | (3 << 16);
		g_tdata.regdata[0] = (port & 1) | 0x742 | 0x1C0000;
		g_tdata.regdata[1] = 0;
		for ( i = 0; i < 7; i += 1 )
			g_tdata.in[i] = 0;
		g_tdata.in[0] = 0x21;
		g_tdata.in[1] = 0x21 + !!( port >= 2 );
		g_tdata.in[2] = slot;
		g_tdata.in_size = 7;
		g_tdata.out_size = 7;
		g_tdata.in_dma.addr = NULL;
		g_tdata.out_dma.addr = NULL;
		sio2_transfer2(&g_tdata);
		if ( read_stat6c_bit(0, &g_tdata) != 1 && g_tdata.out[5] != 0x66 )
			return 1;
	}
	return 0;
}

static int change_slot(s32 *arg)
{
	int i;

	for ( i = 0; i < 4; i += 1 )
	{
		if ( arg[i] == -1 )
			arg[i + 4] = 0;
		else if ( arg[i] < 0 )
			arg[i + 4] = -1;
		else if ( !g_state_open[i] )
			arg[i + 4] = arg[i] ? -1 : 1;
		else if ( !mtapGetConnection(i) )
			arg[i + 4] = arg[i] ? -1 : 1;
		else if ( arg[i] >= g_state_slots[i] )
			arg[i + 4] = -1;
		else
		{
			arg[i + 4] = ( change_slot_setup_td(i, arg[i]) == 1 ) ? 1 : -1;
			if ( arg[i + 4] == -1 )
				g_state_getcon[i] = 0;
		}
	}
	for ( i = 0; i < 4; i += 1 )
		if ( arg[i + 4] < 0 )
			return 0;
	return 1;
}

static int do_set_work_addr_ee(int addr)
{
	WaitSema(g_sema_ee_set_work_addr);
	if ( !addr )
	{
		if ( g_ee_work_addr_value && g_ee_work_addr_trid )
			while ( sceSifDmaStat(g_ee_work_addr_trid) >= 0 )
				DelayThread(100);
		g_ee_work_addr_trid = 0;
	}
	g_ee_work_addr_value = addr;
	SignalSema(g_sema_ee_set_work_addr);
	return 1;
}

static int send_mtap_state_to_ee(void)
{
	int i;
	int trid;
	SifDmaTransfer_t dmat;
	int state;

	// Unofficial: remove unneeded zeroing of state
	WaitSema(g_sema_ee_set_work_addr);
	if ( !g_ee_work_addr_value || (g_ee_work_addr_trid && (sceSifDmaStat(g_ee_work_addr_trid) >= 0)) )
	{
		SignalSema(g_sema_ee_set_work_addr);
		return 0;
	}
	g_ee_magic_value += 1;
	g_ee_data_contents[0] = g_ee_magic_value;
	for ( i = 0; i < 4; i += 1 )
	{
		g_ee_data_contents[i + 2] = g_state_open[i];
		g_ee_data_contents[i + 6] = mtapGetConnection(i);
		g_ee_data_contents[i + 10] = get_slots(i);
	}
	g_ee_data_contents[1] = 1;
	dmat.dest = (void *)g_ee_work_addr_value;
	dmat.src = g_ee_data_contents;
	dmat.size = 128;
	dmat.attr = 0;
	CpuSuspendIntr(&state);
	trid = sceSifSetDma(&dmat, 1);
	CpuResumeIntr(state);
	g_ee_work_addr_trid = trid;
	SignalSema(g_sema_ee_set_work_addr);
	return 1;
}

static void update_slot_numbers_thread(void)
{
	int i;
	int resbits[2];

	while ( 1 )
	{
		WaitEventFlag(g_event_flag, 3u, 0x11, (u32 *)resbits);
		if ( (resbits[0] & 2) != 0 )
			break;
		for ( i = 0; i < 4; i += 1 )
		{
			if ( g_state_open[i] == 1 )
			{
				s32 slots;

				slots = get_slot_number(i, ( mtapGetConnection(i) == 1 ) ? 10 : 0);
				g_state_getcon[i] = ( slots >= 0 ) ? 1 : 0;
				g_state_slots[i] = ( slots >= 0 ) ? slots : 1;
			}
		}
		send_mtap_state_to_ee();
	}
	SetEventFlag(g_event_flag, 4u);
	ExitThread();
}

static int get_slots(int port)
{
	return g_state_slots[port];
}

// Unofficial: omit duplicate get_slots function

static void update_slot_numbers(void)
{
	SetEventFlag(g_event_flag, 1u);
}

int _start(int ac, char **av)
{
	int thid;
	int i;
	iop_event_t evparam;
	iop_thread_t thparam;
	iop_sema_t semaparam;

	if ( RegisterLibraryEntries(&_exp_mtapman) != 0 || SetRebootTimeLibraryHandlingMode(&_exp_mtapman, 2) != 0 )
		return 1;
	g_ee_work_addr_value = 0;
	g_ee_work_addr_trid = 0;
	g_update_slot_numbers_thpriority = 20;
	for ( i = 1; i < ac; i += 1 )
	{
		if ( !strncmp("thpri=", av[i], 6) )
		{
			int cursifpriority;
			int curmainpriority;
			int j;

			j = 6;
			curmainpriority = ( (look_ctype_table(av[i][j]) & 4) != 0 ) ? strtol(&av[i][j], NULL, 10) : -1;
			for ( ; (look_ctype_table(av[i][j]) & 4) != 0; j += 1 );
			cursifpriority = ( av[i][j] == ','  && (look_ctype_table(av[i][j + 1]) & 4) != 0 ) ? strtol(&av[i][j + 1], NULL, 10) : -1;
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
			g_update_slot_numbers_thpriority = curmainpriority;
			do_set_sif_priority_thread(cursifpriority);
		}
		else
		{
			// Unofficial: correct failure condition
			// Unofficial: removed call to empty function
			return 1;
		}
	}
	// Unofficial: correct success condition when argv parsing loop ends
	if ( !InitRpcServers() )
		// Unofficial: removed call to empty function
		return 1;
	evparam.attr = 2;
	evparam.bits = 0;
	g_event_flag = CreateEventFlag(&evparam);
	if ( g_event_flag <= 0 )
		// Unofficial: removed call to empty function
		return 1;
	thparam.attr = 0x2000000;
	thparam.thread = (void (*)(void *))update_slot_numbers_thread;
	thparam.stacksize = 2048;
	thparam.priority = g_update_slot_numbers_thpriority;
	thid = CreateThread(&thparam);
	g_threadid_main = thid;
	if ( thid <= 0 )
		// Unofficial: removed call to empty function
		return 1;
	StartThread(thid, NULL);
	semaparam.initial = 1;
	semaparam.attr = 0;
	semaparam.max = 16;
	g_sema_ee_set_work_addr = CreateSema(&semaparam);
	if ( g_sema_ee_set_work_addr < 0 )
		// Unofficial: removed call to empty function
		return 1;
	for ( i = 0; i < 4; i += 1 )
	{
		mtapPortClose(i);
		g_state_slots[i] = 1;
	}
	sio2_mtap_change_slot_set(change_slot);
	sio2_mtap_get_slot_max_set(get_slots);
	// Unofficial: use deduplicated get_slots function
	sio2_mtap_get_slot_max2_set(get_slots);
	sio2_mtap_update_slots_set(update_slot_numbers);
	g_tdata.in = (u8 *)g_in_buffer;
	g_tdata.out = (u8 *)g_out_buffer;
	return 0;
}

void _deinit(void)
{
	sio2_mtap_change_slot_set(NULL);
	sio2_mtap_get_slot_max_set(NULL);
	sio2_mtap_get_slot_max2_set(NULL);
	sio2_mtap_update_slots_set(NULL);
	do_set_work_addr_ee(0);
	WaitSema(g_sema_ee_set_work_addr);
	DeleteSema(g_sema_ee_set_work_addr);
}

s32 mtapPortOpen(u32 port)
{
	s32 slot;

	if ( port >= 4 )
		return 0;
	g_state_open[port] = 1;
	slot = get_slot_number(port, 0xAu);
	g_state_getcon[port] = ( slot >= 0 ) ? 1 : 0;
	g_state_slots[port] = ( slot >= 0 ) ? slot : 1;
	return 1;
}

s32 mtapPortClose(u32 port)
{
	g_state_open[port] = 0;
	g_state_getcon[port] = 0;
	return 1;
}

s32 mtapGetConnection(u32 port)
{
	return g_state_getcon[port];
}

s32 mtapGetSlotNumber_unused(u32 port)
{
	s32 retres;

	if ( port >= 4 )
		return -1;
	if ( g_state_open[port] != 1 )
		return 1;
	retres = get_slot_number(port, 10u);
	return ( retres < 0 ) ? 1 : retres;
}

int mtapChangeSlot_unused(u32 port, u32 slot)
{
	int i;
	s32 data[8];

	if ( port >= 4 )
		return 0;
	if ( g_state_open[port] != 1 )
	{
		// Unofficial: removed call to empty function
		return 1;
	}
	for ( i = 3; i >= 0; i -= 1 )
		data[i] = -1;
	data[port] = slot;
	sio2_mtap_transfer_init();
	change_slot(data);
	sio2_transfer_reset2();
	// Unofficial: removed call to empty function
	return ( data[port + 4] < 0 ) ? 0 : 1;
}

static int do_set_main_priority_thread(int priority)
{
	int retres;

	retres = ChangeThreadPriority(g_threadid_main, priority);
	return ( retres >= 0 ) ? 0 : retres;
}

static int do_get_version(void)
{
	return _irx_id.v;
}

static int do_set_sif_priority_thread(int priority)
{
	g_MtapServPriority = priority;
	return 0;
}

static int do_set_sif_priority_thread_sif(int priority)
{
	int retres;

	retres = ChangeThreadPriority(g_threadid_rpc, priority);
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
	buffer[0] = do_set_work_addr_ee(buffer[1]);
}

static void RpcServerHandlerGetSlotNumber(u32 *buffer)
{
	buffer[1] = mtapGetConnection(buffer[0]);
}

static void RpcServerHandlerSetThreadPriority(u32 *buffer)
{
	u32 priority_main;
	u32 priority_sif;

	buffer[2] = 0;
	priority_main = buffer[0];
	if ( priority_main - 9 >= 0x73 )
	{
		printf("MTAPMAN:invalid priority_main %d\n", (int)priority_main);
		return;
	}
	priority_sif = buffer[1];
	if ( priority_sif - 9 >= 0x73 )
	{
		printf("MTAPMAN:invalid priority_sif %d\n", (int)priority_sif);
		return;
	}
	ChangeThreadPriority(0, 8);
	if ( do_set_main_priority_thread(priority_main) < 0 )
		printf("MTAPMAN:error to set priority_main\n");
	else if ( do_set_sif_priority_thread_sif(priority_sif) < 0 )
		printf("MTAPMAN:error to set priority_sif\n");
	else
		buffer[2] = 1;
}

static void RpcServerHandlerGetVersion(u32 *buffer)
{
	buffer[0] = do_get_version();
}

static void *RpcServerHandler(int fno, void *buffer, int length)
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

static void MtapServCommon(void)
{
	if ( !sceSifCheckInit() )
	{
		Kprintf("yet sif hasn't been init\n");
		sceSifInit();
	}
	sceSifInitRpc(0);
	sceSifSetRpcQueue(&g_RpcServerQd, GetThreadId());
	sceSifRegisterRpc(&g_RpcServerSd, 0x80000900, RpcServerHandler, g_RpcServerSb, NULL, NULL, &g_RpcServerQd);
	sceSifRpcLoop(&g_RpcServerQd);
}

static int InitRpcServers(void)
{
	iop_thread_t thparam;

	thparam.attr = 0x2000000;
	thparam.thread = (void (*)(void *))MtapServCommon;
	thparam.stacksize = 2048;
	thparam.priority = g_MtapServPriority;
	g_threadid_rpc = CreateThread(&thparam);
	if ( g_threadid_rpc )
		StartThread(g_threadid_rpc, NULL);
	else
		Kprintf("mtapman: CreateThread Error\n");
	return g_threadid_rpc ? 1 : 0;
}
