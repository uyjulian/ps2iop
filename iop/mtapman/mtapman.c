
#include "irx_imports.h"

// Based on the module from SDK 3.1.0.
IRX_ID("multitap_manager", 3, 16);

#define __cdecl
#define __fastcall
#define __noreturn
#define __int32 int

//-------------------------------------------------------------------------
// Function declarations

s32 __cdecl read_stat6c_bit(u32 bit, sio2_transfer_data_t *tdata);
void __cdecl get_slot_number_setup_td(u32 port, u32 reg);
s32 __cdecl get_slot_number_check_td(u32 bit);
s32 __cdecl get_slot_number(u32 port, u32 retries);
s32 __cdecl change_slot_setup_td(unsigned int port, u8 slot);
int __cdecl change_slot(s32 *arg);
int __cdecl do_set_work_addr_ee(int addr);
int send_mtap_state_to_ee(void);
void __noreturn update_slot_numbers_thread(void);
int __cdecl get_slots1(int port);
int __cdecl get_slots2(int port);
void update_slot_numbers(void);
int __cdecl _start(int ac, char **av);
void _deinit(void);
s32 __cdecl mtapPortOpen(u32 port);
s32 __cdecl mtapPortClose(u32 port);
s32 __cdecl mtapGetConnection(u32 port);
s32 __fastcall mtapGetSlotNumber_unused(u32 port);
int __fastcall mtapChangeSlot_unused(u32 port, u32 slot);
int __cdecl do_set_main_priority_thread(int priority);
int do_get_version(void);
int __cdecl do_set_sif_priority_thread(int priority);
int __cdecl do_set_sif_priority_thread_sif(int priority);
u32 *__cdecl RpcServerHandlerInit(int fno, u32 *buffer);
u32 *__cdecl RpcServerHandlerOpen(int fno, u32 *buffer);
u32 *__cdecl RpcServerHandlerClose(int fno, u32 *buffer);
u32 *__cdecl RpcServerHandlerSetWorkAddr(int fno, u32 *buffer);
u32 *__cdecl RpcServerHandlerGetSlotNumber(int fno, u32 *buffer);
u32 *__cdecl RpcServerHandlerSetThreadPriority(int fno, u32 *buffer);
u32 *__cdecl RpcServerHandlerGetVersion(int fno, u32 *buffer);
void *__cdecl RpcServerHandler(int fno, void *buffer, int length);
void MtapServCommon(void);
int InitRpcServers(void);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_mtapman;
int g_ee_magic_value = 0; // weak
int g_MtapServPriority = 46; // weak
int g_event_flag; // idb
int g_threadid_main; // idb
int g_sema_ee_set_work_addr; // weak
int g_update_slot_numbers_thpriority; // weak
int g_state_open[4];
int g_state_getcon[4];
int g_state_slots[4];
sio2_transfer_data_t g_tdata; // idb
int g_in_buffer[64]; // weak
int g_out_buffer[64]; // weak
int g_ee_work_addr_value; // weak
int g_ee_work_addr_trid; // idb
int g_ee_data_contents[32];
SifRpcDataQueue_t g_RpcServerQd; // weak
SifRpcServerData_t g_RpcServerSd; // idb
int g_threadid_rpc; // idb
int g_RpcServerSb[32]; // weak

// Removed empty function with stack manipulation

//----- (00400018) --------------------------------------------------------
s32 __cdecl read_stat6c_bit(u32 bit, sio2_transfer_data_t *tdata)
{
	s32 retval; // $v1

	retval = 0;
	switch ( bit )
	{
		case 0u:
			retval = (tdata->stat6c >> 16) & 1;
			break;
		case 1u:
			retval = (tdata->stat6c >> 17) & 1;
			break;
		case 2u:
			retval = (tdata->stat6c >> 18) & 1;
			break;
		case 3u:
			retval = (tdata->stat6c >> 19) & 1;
			break;
		case 4u:
			retval = (tdata->stat6c >> 20) & 1;
			break;
		case 5u:
			retval = (tdata->stat6c >> 21) & 1;
			break;
		case 6u:
			retval = (tdata->stat6c >> 22) & 1;
			break;
		case 7u:
			retval = (tdata->stat6c >> 23) & 1;
			break;
		case 8u:
			retval = (tdata->stat6c >> 24) & 1;
			break;
		case 9u:
			retval = (tdata->stat6c >> 25) & 1;
			break;
		case 0xAu:
			retval = (tdata->stat6c >> 26) & 1;
			break;
		case 0xBu:
			retval = (tdata->stat6c >> 27) & 1;
			break;
		case 0xCu:
			retval = (tdata->stat6c >> 28) & 1;
			break;
		case 0xDu:
			retval = (tdata->stat6c >> 29) & 1;
			break;
		case 0xEu:
			retval = (tdata->stat6c >> 30) & 1;
			break;
		case 0xFu:
			retval = tdata->stat6c >> 31;
			break;
		default:
			return retval;
	}
	return retval;
}

//----- (00400170) --------------------------------------------------------
void __cdecl get_slot_number_setup_td(u32 port, u32 reg)
{
	int i; // $a3
	u32 p; // $a0
	u32 p_tmp; // $v0
	u32 in_size; // $a0
	u32 tmpval; // $v0
	u8 in_val_tmp; // $v1

	i = 0;
	p = port | 2;
	p_tmp = p;
	// Unofficial: combine writes
	g_tdata.port_ctrl1[p_tmp] = 5 | (5 << 8) | (2 << 16) | (0xFF << 24);
	g_tdata.port_ctrl2[p_tmp] = 0x64 | (3 << 16);
	g_tdata.regdata[reg] = (p & 3) | 0x180640;
	in_size = g_tdata.in_size;
	do
	{
		tmpval = in_size + i++;
		g_tdata.in[tmpval] = 0;
	}
	while ( i < 6 );
	g_tdata.in[in_size] = 0x21;
	in_val_tmp = 0x12;
	if ( port >= 2 )
		in_val_tmp = 0x13;
	g_tdata.in[in_size + 1] = in_val_tmp;
	g_tdata.in_dma.addr = 0;
	g_tdata.out_dma.addr = 0;
	g_tdata.in_size += 6;
	g_tdata.out_size += 6;
}

//----- (004002B0) --------------------------------------------------------
s32 __cdecl get_slot_number_check_td(u32 bit)
{
	s32 retval_tmp1; // $a1
	int i; // $a0
	u8 *tdata_ptr; // $v0
	u8 tdata_val; // $v1
	s32 retval_tmp2; // $v0

	if ( read_stat6c_bit(bit, &g_tdata) == 1 )
	{
		retval_tmp1 = -1;
	}
	else
	{
		retval_tmp1 = -2;
		if ( g_tdata.out[5] != 0x66 && !g_tdata.out[4] )
			retval_tmp1 = g_tdata.out[3];
	}
	for ( i = 0; i < 0xFA; ++i )
	{
		tdata_ptr = &g_tdata.out[i];
		tdata_val = g_tdata.out[i + 6];
		*tdata_ptr = tdata_val;
		retval_tmp2 = retval_tmp1;
	}
	g_tdata.out_size -= 6;
	return retval_tmp2;
}

//----- (00400360) --------------------------------------------------------
s32 __cdecl get_slot_number(u32 port, u32 retries)
{
	signed __int32 i; // $s0
	s32 slots_tmp; // $s1
	int j; // $v1
	int j2; // $v0
	s32 slots; // $v0

	if ( port >= 4 )
		return -3;
	i = 0;
	if ( !g_state_open[port] )
		return -4;
	do
	{
		sio2_mtap_transfer_init();
		j = 0xF;
		j2 = 0xF;
		g_tdata.in_size = 0;
		g_tdata.out_size = 0;
		do
		{
			g_tdata.regdata[j2] = 0;
			--j;
			--j2;
		}
		while ( j >= 0 );
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
			slots_tmp = slots;
			sio2_transfer_reset2();
			return slots_tmp;
		}
		++i;
		sio2_transfer_reset2();
	}
	while ( (int)retries >= i );
	return -4;
}

//----- (0040048C) --------------------------------------------------------
s32 __cdecl change_slot_setup_td(unsigned int port, u8 slot)
{
	int retcond; // $s1
	unsigned int p; // $s0
	unsigned int portor_tmp; // $s3
	int i; // $v1
	u8 *tmpptr; // $v0
	s32 result; // $v0

	retcond = 0;
	p = port | 2;
	portor_tmp = (port & 1) | 0x742;
	i = 0;
	do
	{
		// Unofficial: combine writes
		g_tdata.port_ctrl1[p] = 5 | (5 << 8) | (2 << 16) | (0xFF << 24);
		g_tdata.port_ctrl2[p] = 0x64 | (3 << 16);
		g_tdata.regdata[0] = portor_tmp | 0x1C0000;
		g_tdata.regdata[1] = 0;
		do
		{
			tmpptr = &g_tdata.in[i++];
			*tmpptr = 0;
		}
		while ( i < 7 );
		*g_tdata.in = 0x21;
		if ( port >= 2 )
			g_tdata.in[1] = 0x22;
		else
			g_tdata.in[1] = 0x21;
		g_tdata.in[2] = slot;
		g_tdata.in_size = 7;
		g_tdata.out_size = 7;
		g_tdata.in_dma.addr = 0;
		g_tdata.out_dma.addr = 0;
		sio2_transfer2(&g_tdata);
		if ( read_stat6c_bit(0, &g_tdata) == 1 )
		{
			++retcond;
		}
		else
		{
			result = retcond < 10;
			if ( g_tdata.out[5] != 0x66 )
				return result;
			++retcond;
		}
		i = 0;
	}
	while ( retcond < 10 );
	return retcond < 10;
}

//----- (00400680) --------------------------------------------------------
int __cdecl change_slot(s32 *arg)
{
	signed int port; // $s1
	int *p_state_getcon_cur; // $s2
	s32 *port_arg_tmp4_1; // $s0
	int arg_port; // $a1
	signed int port_tmp; // $v1
	int i2; // $s1
	s32 *port_arg_tmp4_2; // $a0

	port = 0;
	p_state_getcon_cur = g_state_getcon;
	port_arg_tmp4_1 = arg;
	do
	{
		arg_port = *port_arg_tmp4_1;
		port_tmp = port;
		if ( *port_arg_tmp4_1 == -1 )
			port_arg_tmp4_1[4] = 0;
		else if ( arg_port < 0 )
			port_arg_tmp4_1[4] = -1;
		else if ( !g_state_open[port_tmp] )
			port_arg_tmp4_1[4] = arg_port ? -1 : 1;
		else if ( !*p_state_getcon_cur )
			port_arg_tmp4_1[4] = arg_port ? -1 : 1;
		else if ( arg_port >= g_state_slots[port_tmp] )
			port_arg_tmp4_1[4] = -1;
		else
		{
			port_arg_tmp4_1[4] = ( change_slot_setup_td(port, arg_port) == 1 ) ? 1 : -1;
			if ( port_arg_tmp4_1[4] == -1 )
				*p_state_getcon_cur = 0;
		}
		++p_state_getcon_cur;
		++port;
		++port_arg_tmp4_1;
	}
	while ( port < 4 );
	i2 = 0;
	port_arg_tmp4_2 = arg;
	do
	{
		++i2;
		if ( port_arg_tmp4_2[4] < 0 )
			return 0;
		++port_arg_tmp4_2;
	}
	while ( i2 < 4 );
	return 1;
}

//----- (004007D0) --------------------------------------------------------
int __cdecl do_set_work_addr_ee(int addr)
{
	int sematmp; // $a0

	WaitSema(g_sema_ee_set_work_addr);
	if ( addr )
	{
		sematmp = g_sema_ee_set_work_addr;
		g_ee_work_addr_value = addr;
	}
	else
	{
		if ( g_ee_work_addr_value && g_ee_work_addr_trid )
		{
			while ( sceSifDmaStat(g_ee_work_addr_trid) >= 0 )
				DelayThread(100);
		}
		sematmp = g_sema_ee_set_work_addr;
		g_ee_work_addr_trid = 0;
		g_ee_work_addr_value = 0;
	}
	SignalSema(sematmp);
	return 1;
}
// 401AB8: using guessed type int g_sema_ee_set_work_addr;
// 401D84: using guessed type int g_ee_work_addr_value;

//----- (00400888) --------------------------------------------------------
int send_mtap_state_to_ee(void)
{
	int i; // $a1
	int dmastat; // $v0
	int *p_ee_data_contents; // $a0
	int slot_value_tmp; // $v0
	int trid; // $s0
	SifDmaTransfer_t dmat; // [sp+10h] [-88h] BYREF
	int state; // [sp+90h] [-8h] BYREF

	state = 0;
	WaitSema(g_sema_ee_set_work_addr);
	if ( g_ee_work_addr_value
		&& ((i = 0, !g_ee_work_addr_trid) || (dmastat = sceSifDmaStat(g_ee_work_addr_trid), i = 0, dmastat < 0)) )
	{
		p_ee_data_contents = g_ee_data_contents;
		g_ee_data_contents[0] = ++g_ee_magic_value;
		do
		{
			p_ee_data_contents[2] = g_state_open[i];
			p_ee_data_contents[6] = g_state_getcon[i];
			slot_value_tmp = g_state_slots[i++];
			p_ee_data_contents[10] = slot_value_tmp;
			++p_ee_data_contents;
		}
		while ( i < 4 );
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
	else
	{
		SignalSema(g_sema_ee_set_work_addr);
		return 0;
	}
}
// 401A88: using guessed type int g_ee_magic_value;
// 401AB8: using guessed type int g_sema_ee_set_work_addr;
// 401D84: using guessed type int g_ee_work_addr_value;
// 400888: using guessed type SifDmaTransfer_t dmat;

//----- (004009D4) --------------------------------------------------------
void __noreturn update_slot_numbers_thread(void)
{
	signed __int32 port2; // $s1
	int *p_state_slots; // $s2
	int *p_state_getcon; // $s0
	int port1; // $s3
	u32 retrycnt; // $a1
	s32 slots; // $v0
	int resbits[2]; // [sp+10h] [-8h] BYREF

	while ( 1 )
	{
		WaitEventFlag(g_event_flag, 3u, 0x11, (u32 *)resbits);
		port2 = 0;
		if ( (resbits[0] & 2) != 0 )
			break;
		p_state_slots = g_state_slots;
		p_state_getcon = g_state_getcon;
		port1 = 0;
		do
		{
			if ( g_state_open[port1] == 1 )
			{
				if ( *p_state_getcon == 1 )
					retrycnt = 10;
				else
					retrycnt = 0;
				slots = get_slot_number(port2, retrycnt);
				if ( slots < 0 )
				{
					*p_state_getcon = 0;
					*p_state_slots = 1;
				}
				else
				{
					*p_state_getcon = 1;
					*p_state_slots = slots;
				}
			}
			++p_state_slots;
			++p_state_getcon;
			++port2;
			++port1;
		}
		while ( port2 < 4 );
		send_mtap_state_to_ee();
	}
	SetEventFlag(g_event_flag, 4u);
	ExitThread();
}
// 4009D4: using guessed type u32 resbits[2];

//----- (00400ACC) --------------------------------------------------------
int __cdecl get_slots1(int port)
{
	return g_state_slots[port];
}

//----- (00400AE4) --------------------------------------------------------
int __cdecl get_slots2(int port)
{
	return g_state_slots[port];
}

//----- (00400AFC) --------------------------------------------------------
void update_slot_numbers(void)
{
	SetEventFlag(g_event_flag, 1u);
}

//----- (00400B24) --------------------------------------------------------
int __cdecl _start(int ac, char **av)
{
	bool reglibres; // dc
	int result; // $v0
	int curac; // $s1
	const char **curav; // $s4
	int cursifpriority; // $s3
	int curmainpriority; // $s2
	const char *val_plus_six; // $s0
	unsigned int curmainprioity_minus_nine; // $v0
	int thid; // $v0
	int i; // $s1
	int i2; // $v0
	iop_event_t evparam; // [sp+10h] [-38h] BYREF
	iop_thread_t thparam; // [sp+20h] [-28h] BYREF
	iop_sema_t semaparam; // [sp+38h] [-10h] BYREF

	reglibres = RegisterLibraryEntries(&_exp_mtapman) != 0;
	result = 1;
	if ( reglibres )
		return result;
	reglibres = SetRebootTimeLibraryHandlingMode(&_exp_mtapman, 2) != 0;
	result = 1;
	if ( reglibres )
		return result;
	g_ee_work_addr_value = 0;
	g_ee_work_addr_trid = 0;
	g_update_slot_numbers_thpriority = 20;
	if ( ac <= 1 )
	{
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
		thparam.thread = (void (__cdecl *)(void *))update_slot_numbers_thread;
		thparam.stacksize = 2048;
		thparam.priority = g_update_slot_numbers_thpriority;
		thid = CreateThread(&thparam);
		g_threadid_main = thid;
		if ( thid <= 0 )
			// Unofficial: removed call to empty function
			return 1;
		StartThread(thid, 0);
		semaparam.initial = 1;
		semaparam.attr = 0;
		semaparam.max = 16;
		g_sema_ee_set_work_addr = CreateSema(&semaparam);
		if ( g_sema_ee_set_work_addr < 0 )
			// Unofficial: removed call to empty function
			return 1;
		i = 0;
		i2 = 0;
		do
		{
			++i;
			g_state_open[i2] = 0;
			g_state_getcon[i2] = 0;
			g_state_slots[i2] = 1;
			i2 = i;
		}
		while ( i < 4 );
		sio2_mtap_change_slot_set(change_slot);
		sio2_mtap_get_slot_max_set(get_slots1);
		sio2_mtap_get_slot_max2_set(get_slots2);
		sio2_mtap_update_slots_set(update_slot_numbers);
		result = 0;
		g_tdata.in = (u8 *)g_in_buffer;
		g_tdata.out = (u8 *)g_out_buffer;
		return result;
	}
	curac = 1;
	curav = (const char **)(av + 1);
	while ( curac < ac )
	{
		if ( !strncmp("thpri=", *curav, 6) )
		{
			cursifpriority = -1;
			curmainpriority = -1;
			val_plus_six = *curav + 6;
			if ( (look_ctype_table(*val_plus_six) & 4) != 0 )
				curmainpriority = strtol(val_plus_six, 0, 10);
			while ( (look_ctype_table(*val_plus_six) & 4) != 0 )
				++val_plus_six;
			curmainprioity_minus_nine = curmainpriority - 9;
			if ( *val_plus_six == ',' )
			{
				if ( (look_ctype_table(val_plus_six[1]) & 4) != 0 )
					cursifpriority = strtol(val_plus_six + 1, 0, 10);
				curmainprioity_minus_nine = curmainpriority - 9;
			}
			if ( curmainprioity_minus_nine >= 0x73 )
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
		++curac;
		++curav;
	}
	// Unofficial: correct failure condition
	// Unofficial: removed call to empty function
	return 1;
}
// 401AB8: using guessed type int g_sema_ee_set_work_addr;
// 401ABC: using guessed type int g_update_slot_numbers_thpriority;
// 401B84: using guessed type int g_in_buffer[64];
// 401C84: using guessed type int g_out_buffer[64];
// 401D84: using guessed type int g_ee_work_addr_value;

//----- (00400E44) --------------------------------------------------------
void _deinit(void)
{
	sio2_mtap_change_slot_set(0);
	sio2_mtap_get_slot_max_set(0);
	sio2_mtap_get_slot_max2_set(0);
	sio2_mtap_update_slots_set(0);
	do_set_work_addr_ee(0);
	WaitSema(g_sema_ee_set_work_addr);
	DeleteSema(g_sema_ee_set_work_addr);
}
// 401AB8: using guessed type int g_sema_ee_set_work_addr;

//----- (00400EA8) --------------------------------------------------------
s32 __cdecl mtapPortOpen(u32 port)
{
	u32 port_tmp; // $s0
	s32 slot_number; // $v0

	if ( port >= 4 )
		return 0;
	port_tmp = port;
	g_state_open[port] = 1;
	slot_number = get_slot_number(port, 0xAu);
	if ( slot_number < 0 )
	{
		g_state_getcon[port_tmp] = 0;
		g_state_slots[port_tmp] = 1;
	}
	else
	{
		g_state_getcon[port_tmp] = 1;
		g_state_slots[port_tmp] = slot_number;
	}
	return 1;
}

//----- (00400F3C) --------------------------------------------------------
s32 __cdecl mtapPortClose(u32 port)
{
	u32 port_tmp; // $a0

	port_tmp = port;
	g_state_open[port_tmp] = 0;
	g_state_getcon[port_tmp] = 0;
	return 1;
}

//----- (00400F60) --------------------------------------------------------
s32 __cdecl mtapGetConnection(u32 port)
{
	return g_state_getcon[port];
}

//----- (00400F78) --------------------------------------------------------
s32 __fastcall mtapGetSlotNumber_unused(u32 port)
{
	s32 retres; // $v0

	if ( port >= 4 )
		return -1;
	retres = 1;
	if ( g_state_open[port] == 1 )
	{
		retres = get_slot_number(port, 10u);
		if ( retres < 0 )
			return 1;
	}
	return retres;
}

//----- (00400FD4) --------------------------------------------------------
int __fastcall mtapChangeSlot_unused(u32 port, u32 slot)
{
	int idx; // $v1
	s32 *p_data_fill; // $v0
	s32 *p_data_slot; // $s0
	s32 data[8]; // [sp+10h] [-20h] BYREF

	if ( port >= 4 )
		return 0;
	if ( g_state_open[port] != 1 )
	{
		// Unofficial: removed call to empty function
		return 1;
	}
	idx = 3;
	p_data_fill = &data[3];
	do
	{
		*p_data_fill = -1;
		--idx;
		--p_data_fill;
	}
	while ( idx >= 0 );
	p_data_slot = &data[port];
	*p_data_slot = slot;
	sio2_mtap_transfer_init();
	change_slot(data);
	sio2_transfer_reset2();
	if ( p_data_slot[4] < 0 )
	{
		// Unofficial: removed call to empty function
		return 0;
	}
	else
	{
		// Unofficial: removed call to empty function
		return 1;
	}
}

//----- (004010AC) --------------------------------------------------------
int __cdecl do_set_main_priority_thread(int priority)
{
	int retres; // $v0

	retres = ChangeThreadPriority(g_threadid_main, priority);
	if ( retres >= 0 )
		return 0;
	return retres;
}

//----- (004010E8) --------------------------------------------------------
int do_get_version(void)
{
	return _irx_id.v;
}

//----- (00401100) --------------------------------------------------------
int __cdecl do_set_sif_priority_thread(int priority)
{
	g_MtapServPriority = priority;
	return 0;
}
// 401AA0: using guessed type int g_MtapServPriority;

//----- (00401110) --------------------------------------------------------
int __cdecl do_set_sif_priority_thread_sif(int priority)
{
	int retres; // $v0

	retres = ChangeThreadPriority(g_threadid_rpc, priority);
	if ( retres >= 0 )
		return 0;
	return retres;
}

//----- (0040114C) --------------------------------------------------------
u32 *__cdecl RpcServerHandlerInit(int fno, u32 *buffer)
{
	(void)fno;

	return buffer;
}

//----- (00401154) --------------------------------------------------------
u32 *__cdecl RpcServerHandlerOpen(int fno, u32 *buffer)
{
	(void)fno;

	buffer[1] = mtapPortOpen(*buffer);
	return buffer;
}

//----- (00401188) --------------------------------------------------------
u32 *__cdecl RpcServerHandlerClose(int fno, u32 *buffer)
{
	(void)fno;

	buffer[1] = mtapPortClose(*buffer);
	return buffer;
}

//----- (004011BC) --------------------------------------------------------
u32 *__cdecl RpcServerHandlerSetWorkAddr(int fno, u32 *buffer)
{
	(void)fno;

	*buffer = do_set_work_addr_ee(buffer[1]);
	return buffer;
}

//----- (004011F0) --------------------------------------------------------
u32 *__cdecl RpcServerHandlerGetSlotNumber(int fno, u32 *buffer)
{
	(void)fno;

	buffer[1] = mtapGetConnection(*buffer);
	return buffer;
}

//----- (00401224) --------------------------------------------------------
u32 *__cdecl RpcServerHandlerSetThreadPriority(int fno, u32 *buffer)
{
	u32 priority_main; // $a1
	u32 priority_sif; // $a1

	(void)fno;

	priority_main = *buffer;
	if ( priority_main - 9 >= 0x73 )
	{
		printf("MTAPMAN:invalid priority_main %d\n", priority_main);
		buffer[2] = 0;
		return buffer;
	}
	priority_sif = buffer[1];
	if ( priority_sif - 9 >= 0x73 )
	{
		printf("MTAPMAN:invalid priority_sif %d\n", priority_sif);
		buffer[2] = 0;
		return buffer;
	}
	ChangeThreadPriority(0, 8);
	if ( do_set_main_priority_thread(*buffer) < 0 )
	{
		printf("MTAPMAN:error to set priority_main\n");
		buffer[2] = 0;
		return buffer;
	}
	if ( do_set_sif_priority_thread_sif(buffer[1]) < 0 )
	{
		printf("MTAPMAN:error to set priority_sif\n");
		buffer[2] = 0;
	}
	else
	{
		buffer[2] = 1;
	}
	return buffer;
}

//----- (0040131C) --------------------------------------------------------
u32 *__cdecl RpcServerHandlerGetVersion(int fno, u32 *buffer)
{
	(void)fno;

	*buffer = do_get_version();
	return buffer;
}

//----- (00401348) --------------------------------------------------------
void *__cdecl RpcServerHandler(int fno, void *buffer, int length)
{
	void *SlotNumber; // $s0

	(void)length;

	SlotNumber = buffer;
	switch ( fno )
	{
		case 0:
			SlotNumber = RpcServerHandlerInit(fno, (u32 *)buffer);
			break;
		case 1:
			SlotNumber = RpcServerHandlerOpen(fno, (u32 *)buffer);
			break;
		case 2:
			SlotNumber = RpcServerHandlerClose(fno, (u32 *)buffer);
			break;
		case 3:
			SlotNumber = RpcServerHandlerGetSlotNumber(fno, (u32 *)buffer);
			break;
		case 4:
			SlotNumber = RpcServerHandlerSetThreadPriority(fno, (u32 *)buffer);
			break;
		case 5:
			SlotNumber = RpcServerHandlerGetVersion(fno, (u32 *)buffer);
			break;
		case 6:
			SlotNumber = RpcServerHandlerSetWorkAddr(fno, (u32 *)buffer);
			break;
		default:
			Kprintf("invalid function code (%03x)\n", fno);
			break;
	}
	return SlotNumber;
}

//----- (00401414) --------------------------------------------------------
void MtapServCommon(void)
{
	int ThreadId; // $v0

	if ( !sceSifCheckInit() )
	{
		Kprintf("yet sif hasn't been init\n");
		sceSifInit();
	}
	sceSifInitRpc(0);
	ThreadId = GetThreadId();
	sceSifSetRpcQueue(&g_RpcServerQd, ThreadId);
	sceSifRegisterRpc(&g_RpcServerSd, 0x80000900, RpcServerHandler, g_RpcServerSb, 0, 0, &g_RpcServerQd);
	sceSifRpcLoop(&g_RpcServerQd);
}
// 401E10: using guessed type SifRpcDataQueue_t g_RpcServerQd;
// 401E70: using guessed type int g_RpcServerSb[32];

//----- (004014B0) --------------------------------------------------------
int InitRpcServers(void)
{
	iop_thread_t thparam; // [sp+10h] [-18h] BYREF

	thparam.attr = 0x2000000;
	thparam.thread = (void (__cdecl *)(void *))MtapServCommon;
	thparam.stacksize = 2048;
	thparam.priority = g_MtapServPriority;
	g_threadid_rpc = CreateThread(&thparam);
	if ( g_threadid_rpc )
	{
		StartThread(g_threadid_rpc, 0);
		return 1;
	}
	else
	{
		Kprintf("mtapman: CreateThread Error\n");
		return 0;
	}
}
// 401AA0: using guessed type int g_MtapServPriority;
