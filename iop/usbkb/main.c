
#include "irx_imports.h"

typedef struct _unit
{
	int dev_id;
	int number;
	int c_pipe;
	int d_pipe;
	int payload;
	int ifnum;
	int as;
	int count;
	u8 ledptn;
	u8 old_ledbtn;
	u8 old_ledbtn2;
	int rp;
	int wp;
	int rblen;
	u8 ringbuf[3][66];
	u8 data[];
} ps2kbd_unit;

//-------------------------------------------------------------------------
// Function declarations

int _start(int ac, char **av);
int usbkb_cleanup();
int usbkb_unload();
void usbkb_thread_proc();
void *usbkb_rpc_func(int fno, void *buffer, int length);
u8 *usbkb_rpc_fno_01_GetInfo(int fno, u8 *buffer);
u8 *usbkb_rpc_fno_02_Read(int fno, u8 *buffer);
u8 *usbkb_rpc_fno_03_GetLocation(int fno, u8 *buffer);
u8 *usbkb_rpc_fno_04_SetLEDStatus(int fno, u8 *buffer);
int usbkb_donecb_SetLEDStatus(int result, int count, ps2kbd_unit *arg);
u8 *usbkb_rpc_fno_05_SetLEDMode(int fno, u8 *buffer);
u8 *usbkb_rpc_fno_06_ClearRbuf(int fno, u8 *buffer);
int usbkb_drv_probe(int devID);
int usbkb_drv_connect(int devID);
ps2kbd_unit *usbkb_allocate_unit(int devID, int maxPacketSize, int interfaceNumber, int alternateSetting);
int usbkb_donecb_SetConfiguration(int result, int count, ps2kbd_unit *arg);
int usbkb_donecb_SetInterface(int result, int count, ps2kbd_unit *arg);
int usbkb_set_idle_request(ps2kbd_unit *cbArg);
int usbkb_donecb_set_idle_request(int result, int count, ps2kbd_unit *arg);
int usbkb_data_transfer(ps2kbd_unit *cbArg);
int usbkb_donecb_data_transfer(int result, int count, ps2kbd_unit *arg);
int usbkb_donecb_led_transfer(int result, int count, ps2kbd_unit *arg);
int usbkb_drv_disconnect(int devID);

//-------------------------------------------------------------------------
// Data declarations

int nullstr = 0; // weak
sceUsbdLddOps g_kbd_driver =
{
	NULL,
	NULL,
	"usbkeybd",
	&usbkb_drv_probe,
	&usbkb_drv_connect,
	&usbkb_drv_disconnect,
	0u,
	0u,
	0u,
	0u,
	0u,
	NULL
}; // idb
int g_usbkb_used_kb_count; // weak
int g_usbkb_cfg_keybd; // weak
ps2kbd_unit **g_usbkb_unit_buf;
u8 **g_usbkb_devloc_buf;
int g_usbkb_thread_id; // weak
SifRpcDataQueue_t g_usbkb_rpc_qd;
SifRpcServerData_t g_usbkb_rpc_sd;
int g_usbkb_cfg_debug; // weak
int g_usbkb_rpc_buf[36]; // weak
int g_usbkeybd_resident_flag; // weak
int g_usbkb_cfg_lmode; // weak


//----- (00400000) --------------------------------------------------------
int _start(int ac, char **av)
{
	int cur_ac; // $s2
	char **cur_av; // $s1
	int arg_rvalue; // $s0
	char *av_chrptr_1; // $a0
	char *av_chrptr_2; // $v1
	int devloc_i1; // $s2
	u8 *devloc_buf; // $v0
	int state_tmp; // $a0
	int devloc_i2; // $s0
	u8 *devloc_buf_tmp; // $a0
	int unit_index; // $s2
	int lddres; // $v0
	iop_thread_t thparam; // [sp+10h] [-20h] BYREF
	int state[2]; // [sp+28h] [-8h] BYREF

	if ( ac < 0 )
		return usbkb_unload();
	cur_ac = 0;
	printf("USB Keyboard Driver 1.03\n");
	g_usbkb_cfg_lmode = 0;
	g_usbkb_cfg_keybd = 2;
	g_usbkb_cfg_debug = 0;
	if ( ac <= 0 )
		goto LABEL_23;
	cur_av = av;
	while ( 1 )
	{
		arg_rvalue = 0;
		if ( **cur_av )
		{
			av_chrptr_1 = *cur_av;
			av_chrptr_2 = *cur_av;
			while ( *av_chrptr_2 != '=' )
			{
				av_chrptr_2 = &av_chrptr_1[++arg_rvalue];
				if ( !av_chrptr_1[arg_rvalue] )
					goto LABEL_10;
			}
			*av_chrptr_2 = 0;
			++arg_rvalue;
		}
LABEL_10:
		if ( strcmp(*cur_av, "lmode") )
			goto LABEL_15;
		if ( !strcmp(&(*cur_av)[arg_rvalue], "AUTOLOAD") )
			break;
		if ( !strcmp(&(*cur_av)[arg_rvalue], "TESTLOAD") )
		{
			g_usbkb_cfg_lmode = 2;
			goto LABEL_23;
		}
LABEL_15:
		if ( !strcmp(*cur_av, "keybd") )
		{
			g_usbkb_cfg_keybd = strtol(&(*cur_av)[arg_rvalue], 0, 10);
			if ( g_usbkb_cfg_keybd <= 0 )
				g_usbkb_cfg_keybd = 1;
			if ( g_usbkb_cfg_keybd >= 128 )
				g_usbkb_cfg_keybd = 127;
		}
		if ( !strcmp(*cur_av, "debug") )
			g_usbkb_cfg_debug = strtol(&(*cur_av)[arg_rvalue], 0, 10);
		++cur_ac;
		++cur_av;
		if ( cur_ac >= ac )
			goto LABEL_23;
	}
	g_usbkb_cfg_lmode = 1;
LABEL_23:
	printf("Max Keyboards : %d\n", g_usbkb_cfg_keybd);
	printf("Debug level : %d\n", g_usbkb_cfg_debug);
	CpuSuspendIntr(state);
	g_usbkb_unit_buf = AllocSysMemory(0, 4 * g_usbkb_cfg_keybd, 0);
	CpuResumeIntr(state[0]);
	if ( g_usbkb_unit_buf )
	{
		CpuSuspendIntr(state);
		g_usbkb_devloc_buf = AllocSysMemory(0, 4 * g_usbkb_cfg_keybd, 0);
		CpuResumeIntr(state[0]);
		if ( !g_usbkb_devloc_buf )
		{
			CpuSuspendIntr(state);
			FreeSysMemory(g_usbkb_unit_buf);
			CpuResumeIntr(state[0]);
			return 1;
		}
		devloc_i1 = 0;
		if ( g_usbkb_cfg_keybd > 0 )
		{
			while ( 1 )
			{
				CpuSuspendIntr(state);
				devloc_buf = AllocSysMemory(0, 7, 0);
				state_tmp = state[0];
				g_usbkb_devloc_buf[devloc_i1] = devloc_buf;
				CpuResumeIntr(state_tmp);
				if ( !g_usbkb_devloc_buf[devloc_i1] )
					break;
				if ( ++devloc_i1 >= g_usbkb_cfg_keybd )
					goto LABEL_32;
			}
			CpuSuspendIntr(state);
			devloc_i2 = 0;
			FreeSysMemory(g_usbkb_unit_buf);
			if ( devloc_i1 > 0 )
			{
				do
				{
					devloc_buf_tmp = g_usbkb_devloc_buf[devloc_i2++];
					FreeSysMemory(devloc_buf_tmp);
				}
				while ( devloc_i2 < devloc_i1 );
			}
			FreeSysMemory(g_usbkb_devloc_buf);
			CpuResumeIntr(state[0]);
			return 1;
		}
LABEL_32:
		unit_index = 0;
		for ( g_usbkb_used_kb_count = 0; unit_index < g_usbkb_cfg_keybd; ++unit_index )
		{
			g_usbkb_unit_buf[unit_index] = 0;
			*g_usbkb_devloc_buf[unit_index] = 0;
		}
		if ( g_usbkb_cfg_lmode == 1 )
		{
			printf("usbkeybd : AUTOLOAD MODE\n");
		}
		else
		{
			if ( g_usbkb_cfg_lmode < 2 )
			{
				if ( !g_usbkb_cfg_lmode )
					g_usbkeybd_resident_flag = 1;
				goto LABEL_44;
			}
			if ( g_usbkb_cfg_lmode != 2 )
			{
LABEL_44:
				lddres = sceUsbdRegisterLdd(&g_kbd_driver);
				if ( lddres )
					printf("usbkeybd: sceUsbdRegisterLdd -> 0x%x\n", lddres);
				if ( g_usbkb_cfg_lmode == 2 )
				{
					sceUsbdUnregisterLdd(&g_kbd_driver);
					usbkb_cleanup();
					if ( g_usbkeybd_resident_flag != 1 )
						return 1;
					return 5;
				}
				else if ( g_usbkeybd_resident_flag
							 && (thparam.attr = 0x2000000,
									 thparam.thread = usbkb_thread_proc,
									 thparam.priority = 50,
									 thparam.stacksize = 4096,
									 thparam.option = 0,
									 g_usbkb_thread_id = CreateThread(&thparam),
									 g_usbkb_thread_id > 0) )
				{
					StartThread(g_usbkb_thread_id, 0);
					return 2;
				}
				else
				{
					sceUsbdUnregisterLdd(&g_kbd_driver);
					usbkb_cleanup();
					return 1;
				}
			}
			printf("usbkeybd : TESTLOAD MODE\n");
		}
		g_usbkeybd_resident_flag = 0;
		goto LABEL_44;
	}
	return 1;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 402084: using guessed type int g_usbkb_cfg_keybd;
// 402090: using guessed type int g_usbkb_thread_id;
// 4020F0: using guessed type int g_usbkb_cfg_debug;
// 402188: using guessed type int g_usbkeybd_resident_flag;
// 40218C: using guessed type int g_usbkb_cfg_lmode;

//----- (00400554) --------------------------------------------------------
int usbkb_cleanup()
{
	int i; // $s1
	ps2kbd_unit *unit; // $v0
	int state[2]; // [sp+10h] [-8h] BYREF

	for ( i = 0; i < g_usbkb_cfg_keybd; ++i )
	{
		CpuSuspendIntr(state);
		FreeSysMemory(g_usbkb_devloc_buf[i]);
		CpuResumeIntr(state[0]);
		unit = g_usbkb_unit_buf[i];
		if ( unit )
		{
			sceUsbdClosePipe(unit->c_pipe);
			sceUsbdClosePipe(unit->d_pipe);
			CpuSuspendIntr(state);
			FreeSysMemory(unit);
			CpuResumeIntr(state[0]);
		}
	}
	CpuSuspendIntr(state);
	FreeSysMemory(g_usbkb_unit_buf);
	FreeSysMemory(g_usbkb_devloc_buf);
	return CpuResumeIntr(state[0]);
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400690) --------------------------------------------------------
int usbkb_unload()
{
	usbkb_cleanup();
	sceUsbdUnregisterLdd(&g_kbd_driver);
	TerminateThread(g_usbkb_thread_id);
	DeleteThread(g_usbkb_thread_id);
	sceSifRemoveRpc(&g_usbkb_rpc_sd, &g_usbkb_rpc_qd);
	sceSifRemoveRpcQueue(&g_usbkb_rpc_qd);
	return 1;
}
// 402090: using guessed type int g_usbkb_thread_id;

//----- (004006F8) --------------------------------------------------------
void usbkb_thread_proc()
{
	sceSifInitRpc(0);
	sceSifSetRpcQueue(&g_usbkb_rpc_qd, GetThreadId());
	sceSifRegisterRpc(&g_usbkb_rpc_sd, 0x80000211, usbkb_rpc_func, g_usbkb_rpc_buf, 0, 0, &g_usbkb_rpc_qd);
	sceSifRpcLoop(&g_usbkb_rpc_qd);
}
// 4020F8: using guessed type int g_usbkb_rpc_buf[36];

//----- (0040076C) --------------------------------------------------------
void *usbkb_rpc_func(int fno, void *buffer, int length)
{
	switch ( fno )
	{
		case 1:
			usbkb_rpc_fno_01_GetInfo(fno, buffer);
			break;
		case 2:
			usbkb_rpc_fno_02_Read(fno, buffer);
			break;
		case 3:
			usbkb_rpc_fno_03_GetLocation(fno, buffer);
			break;
		case 4:
			usbkb_rpc_fno_04_SetLEDStatus(fno, buffer);
			break;
		case 5:
			usbkb_rpc_fno_05_SetLEDMode(fno, buffer);
			break;
		case 6:
			usbkb_rpc_fno_06_ClearRbuf(fno, buffer);
			break;
		default:
			printf("usbkeybd.irx : Illegal function No.%d from EE\n", fno);
			break;
	}
	return buffer;
}

//----- (00400844) --------------------------------------------------------
u8 *usbkb_rpc_fno_01_GetInfo(int fno, u8 *buffer)
{
	u8 *infobuf; // $a0
	int i; // $a2

	*buffer = g_usbkb_cfg_keybd;
	infobuf = buffer + 2;
	buffer[1] = g_usbkb_used_kb_count;
	for ( i = 0; i < g_usbkb_cfg_keybd; ++infobuf )
	{
		if ( g_usbkb_unit_buf[i] )
			*infobuf = 1;
		else
			*infobuf = 0;
		++i;
	}
	return buffer;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (004008C4) --------------------------------------------------------
u8 *usbkb_rpc_fno_02_Read(int fno, u8 *buffer)
{
	int unit_index; // $a1
	ps2kbd_unit *unit; // $s0
	u8 *infobuf; // $a0
	u8 *ringbuf_tmp; // $a1
	int j; // $v1
	int i; // $v1
	int state; // [sp+10h] [-8h] BYREF

	unit_index = *buffer;
	if ( g_usbkb_cfg_keybd >= unit_index )
	{
		unit = g_usbkb_unit_buf[unit_index];
		if ( unit )
		{
			CpuSuspendIntr(&state);
			infobuf = buffer + 2;
			if ( unit->rblen <= 0 )
			{
				buffer[1] = 0;
				*buffer = unit->ledptn;
				for ( i = 0; i < unit->payload; ++infobuf )
				{
					*infobuf = 0;
					++i;
				}
			}
			else
			{
				ringbuf_tmp = unit->ringbuf[unit->rp];
				*buffer = *ringbuf_tmp;
				buffer[1] = ringbuf_tmp[1];
				for ( j = 0; j < unit->payload; ++infobuf )
				{
					*infobuf = ringbuf_tmp[j + 2];
					++j;
				}
				unit->rp += 1;
				if ( unit->rp >= 3 )
					unit->rp = 0;
				--unit->rblen;
			}
			CpuResumeIntr(state);
		}
		else
		{
			printf("USB keyboard %d is not connected!\n", unit_index);
			buffer[1] = -1;
		}
	}
	else
	{
		printf("Illegal index_no : %d\n", unit_index);
		buffer[1] = -1;
	}
	return buffer;
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400A50) --------------------------------------------------------
u8 *usbkb_rpc_fno_03_GetLocation(int fno, u8 *buffer)
{
	int unit_index; // $a1
	u8 *chrbuf; // $s0
	int k; // $v1
	ps2kbd_unit *unit; // $v0
	int j; // $v1
	int DeviceLocation; // $a3
	int tmpchr_i; // $v1
	int i; // $v1
	char tmpchr; // $v0
	u8 devloc_stk[8]; // [sp+10h] [-8h] BYREF

	unit_index = *buffer;
	chrbuf = buffer;
	if ( unit_index < g_usbkb_cfg_keybd )
	{
		unit = g_usbkb_unit_buf[unit_index];
		if ( unit )
		{
			DeviceLocation = sceUsbdGetDeviceLocation(unit->dev_id, devloc_stk);
			tmpchr_i = 0;
			if ( DeviceLocation )
			{
				printf(
					"usbkeybd%d: %s -> 0x%x\n",
					g_usbkb_unit_buf[*buffer]->number,
					"sceUsbdGetDeviceLocation",
					DeviceLocation);
				for ( i = 7; i >= 0; --i )
					*chrbuf++ = 0;
				return buffer;
			}
			else
			{
				do
				{
					tmpchr = devloc_stk[tmpchr_i++];
					*chrbuf++ = tmpchr;
				}
				while ( tmpchr_i < 7 );
				return buffer;
			}
		}
		else
		{
			printf("USB keyboard %d is not connected!\n", unit_index);
			for ( j = 7; j >= 0; --j )
				*chrbuf++ = 0;
			return buffer;
		}
	}
	else
	{
		printf("Illegal USB keyboard number! : %d\n", unit_index);
		for ( k = 7; k >= 0; --k )
			*chrbuf++ = 0;
		return buffer;
	}
}
// 402084: using guessed type int g_usbkb_cfg_keybd;
// 400A50: using guessed type u8 devloc_stk[8];

//----- (00400B8C) --------------------------------------------------------
u8 *usbkb_rpc_fno_04_SetLEDStatus(int fno, u8 *buffer)
{
	int unit_index; // $a1
	u8 ledptn; // $v1
	ps2kbd_unit *unit; // $s0
	int xferret; // $v0
	UsbDeviceRequest devreq; // [sp+18h] [-8h] BYREF

	unit_index = *buffer;
	if ( unit_index < g_usbkb_cfg_keybd )
	{
		unit = g_usbkb_unit_buf[unit_index];
		if ( unit )
		{
			unit->ledptn = buffer[1];
			devreq.requesttype = 33;
			devreq.request = 9;
			devreq.value = 512;
			devreq.length = 1;
			devreq.index = unit->ifnum;
			xferret = sceUsbdTransferPipe(unit->c_pipe, &unit->ledptn, 1u, &devreq, (sceUsbdDoneCallback)usbkb_donecb_SetLEDStatus, unit);
			if ( xferret )
			{
				printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "SET_REPORT", xferret);
				ledptn = ~buffer[1];
			}
			else
			{
				ledptn = unit->ledptn;
			}
		}
		else
		{
			printf("Keyboard %d is not connected.\n", unit_index);
			ledptn = ~buffer[1];
		}
	}
	else
	{
		printf("Illegal USB keyboard number! : %d\n", unit_index);
		ledptn = ~buffer[1];
	}
	buffer[1] = ledptn;
	return buffer;
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400CBC) --------------------------------------------------------
int usbkb_donecb_SetLEDStatus(int result, int count, ps2kbd_unit *arg)
{
	if ( result )
		printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "set_led_status", result);
	return 0;
}

//----- (00400CF4) --------------------------------------------------------
u8 *usbkb_rpc_fno_05_SetLEDMode(int fno, u8 *buffer)
{
	int unit_index; // $a1
	ps2kbd_unit *unit; // $a0
	u8 old_ledbtn_tmp; // $v1

	unit_index = *buffer;
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("Illegal USB keyboard number! : %d\n");
LABEL_6:
		old_ledbtn_tmp = ~buffer[1];
		goto LABEL_7;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("Keyboard %d is not connected.\n");
		goto LABEL_6;
	}
	old_ledbtn_tmp = buffer[1];
	unit->old_ledbtn2 = old_ledbtn_tmp;
LABEL_7:
	buffer[1] = old_ledbtn_tmp;
	return buffer;
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400D88) --------------------------------------------------------
u8 *usbkb_rpc_fno_06_ClearRbuf(int fno, u8 *buffer)
{
	int unit_index; // $a1
	ps2kbd_unit *unit; // $s0
	int state; // [sp+10h] [-8h] BYREF

	unit_index = *buffer;
	if ( unit_index < g_usbkb_cfg_keybd )
	{
		unit = g_usbkb_unit_buf[unit_index];
		if ( unit )
		{
			CpuSuspendIntr(&state);
			unit->wp = 0;
			unit->rp = 0;
			unit->rblen = 0;
			CpuResumeIntr(state);
			return buffer;
		}
		printf("clear_rbuf() : Keyboard %d is not connected.\n");
	}
	else
	{
		printf("clear_rbuf() : Illegal USB keyboard number! : %d\n");
	}
	return buffer;
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400E30) --------------------------------------------------------
int usbkb_drv_probe(int devID)
{
	UsbDeviceDescriptor *dev; // $a1
	UsbInterfaceDescriptor *intf; // $a0

	if ( g_usbkb_used_kb_count >= g_usbkb_cfg_keybd )
		return 0;
	dev = sceUsbdScanStaticDescriptor(devID, 0, 1u);
	if ( dev )
	{
		if ( !dev->bDeviceClass )
		{
			if ( dev->bNumConfigurations == 1 )
			{
				intf = sceUsbdScanStaticDescriptor(devID, dev, 4u);
				if ( !intf )
					return 0;
				if ( intf->bInterfaceClass != 3 )
					return 0;
				if ( intf->bInterfaceSubClass != 1 )
					return 0;
				if ( intf->bInterfaceProtocol != 1 )
					return 0;
				if ( g_usbkb_cfg_debug > 0 )
					printf("usbkeybd : resident_flag is ON\n");
				g_usbkeybd_resident_flag = intf->bInterfaceProtocol;
				return g_usbkb_cfg_lmode != 2;
			}
		}
	}
	return 0;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 402084: using guessed type int g_usbkb_cfg_keybd;
// 4020F0: using guessed type int g_usbkb_cfg_debug;
// 402188: using guessed type int g_usbkeybd_resident_flag;
// 40218C: using guessed type int g_usbkb_cfg_lmode;

//----- (00400F3C) --------------------------------------------------------
int usbkb_drv_connect(int devID)
{
	UsbConfigDescriptor *conf; // $v0
	UsbInterfaceDescriptor *intf; // $s0
	UsbEndpointDescriptor *endp; // $s2
	int maxPacketSize; // $a1
	ps2kbd_unit *unit; // $s1
	int xferret; // $s0
	int DeviceLocation; // $s0
	UsbDeviceRequest devreq; // [sp+18h] [-8h] BYREF

	conf = sceUsbdScanStaticDescriptor(devID, 0, 2u);
	if ( !conf )
		return -1;
	intf = sceUsbdScanStaticDescriptor(devID, conf, 4u);
	if ( !intf )
		return 0;
	if ( intf->bInterfaceClass == 3 )
	{
		if ( intf->bInterfaceSubClass == 1 )
		{
			if ( intf->bInterfaceProtocol != 1 )
				return 0;
			if ( intf->bNumEndpoints == 1 )
			{
				endp = sceUsbdScanStaticDescriptor(devID, intf, 5u);
				if ( endp )
				{
					if ( (endp->bEndpointAddress & 0x80) != 0 )
					{
						if ( (endp->bmAttributes & 3) != 3 )
							return -1;
						maxPacketSize = endp->wMaxPacketSizeLB | (endp->wMaxPacketSizeHB << 8);
						if ( maxPacketSize < 65 )
						{
							unit = usbkb_allocate_unit(devID, maxPacketSize, intf->bInterfaceNumber, intf->bAlternateSetting);
							if ( !unit )
								return -1;
							unit->c_pipe = sceUsbdOpenPipe(devID, 0);
							if ( unit->c_pipe < 0 )
								return -1;
							unit->d_pipe = sceUsbdOpenPipe(devID, endp);
							if ( unit->d_pipe < 0 )
							{
								FreeSysMemory(unit);
								return -1;
							}
							sceUsbdSetPrivateData(devID, unit);
							devreq.requesttype = 0;
							devreq.request = 9;
							devreq.index = 0;
							devreq.length = 0;
							devreq.value = conf->bConfigurationValue;
							xferret = sceUsbdTransferPipe(unit->c_pipe, 0, 0, &devreq, (sceUsbdDoneCallback)usbkb_donecb_SetConfiguration, unit);
							if ( xferret )
							{
								printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "sceUsbdSetConfiguration", xferret);
								return -1;
							}
							DeviceLocation = sceUsbdGetDeviceLocation(devID, g_usbkb_devloc_buf[unit->number]);
							if ( DeviceLocation )
							{
								printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "sceUsbdGetDeviceLocation", DeviceLocation);
								return -1;
							}
							if ( g_usbkb_cfg_debug > 0 )
							{
								printf("dev_id:%d\n", devID);
								printf("usbkeybd%d: attached (port=", unit->number);
								do
								{
									if ( !g_usbkb_devloc_buf[unit->number][DeviceLocation] )
										break;
									++DeviceLocation;
									printf("%s%d", DeviceLocation ? "," : "", g_usbkb_devloc_buf[unit->number][DeviceLocation]);
								}
								while ( DeviceLocation < 7 );
								printf(")\n");
							}
							++g_usbkb_used_kb_count;
							g_usbkb_unit_buf[unit->number] = unit;
							return 0;
						}
					}
				}
			}
			return -1;
		}
	}
	return 0;
}
// 401F30: using guessed type int nullstr;
// 402080: using guessed type int g_usbkb_used_kb_count;
// 4020F0: using guessed type int g_usbkb_cfg_debug;

//----- (00401244) --------------------------------------------------------
ps2kbd_unit *usbkb_allocate_unit(int devID, int maxPacketSize, int interfaceNumber, int alternateSetting)
{
	ps2kbd_unit *unit_tmp1; // $v0
	int DeviceLocation; // $v0
	int unit_index1; // $a2
	u8 **devloc_buf_tmp; // $t0
	int devloc_index; // $a1
	u8 *devloc_tmp; // $v0
	int unit_index2; // $a2
	ps2kbd_unit **unit_buf_cur; // $v1
	u8 devloc_stk[8]; // [sp+10h] [-8h] BYREF

	if ( g_usbkb_used_kb_count >= g_usbkb_cfg_keybd )
		return 0;
	unit_tmp1 = AllocSysMemory(0, maxPacketSize + 0xF8, 0);
	if ( unit_tmp1 )
	{
		unit_tmp1->dev_id = devID;
		DeviceLocation = sceUsbdGetDeviceLocation(devID, devloc_stk);
		if ( DeviceLocation )
		{
			printf("usbkeybd%d: %s -> 0x%x\n", unit_tmp1->number, "sceUsbdGetDeviceLocation", DeviceLocation);
			return 0;
		}
		unit_index1 = 0;
		if ( g_usbkb_cfg_keybd > 0 )
		{
			devloc_buf_tmp = g_usbkb_devloc_buf;
			while ( 1 )
			{
				devloc_index = 0;
				devloc_tmp = *devloc_buf_tmp;
				do
				{
					if ( *devloc_tmp != devloc_stk[devloc_index] )
						break;
					devloc_tmp = &(*devloc_buf_tmp)[++devloc_index];
				}
				while ( devloc_index < 7 );
				if ( devloc_index == 7 )
					break;
				++unit_index1;
				++devloc_buf_tmp;
				if ( unit_index1 >= g_usbkb_cfg_keybd )
					goto LABEL_14;
			}
			unit_tmp1->number = unit_index1;
		}
LABEL_14:
		if ( unit_index1 == g_usbkb_cfg_keybd )
		{
			unit_index2 = 0;
			if ( g_usbkb_cfg_keybd <= 0 )
				goto LABEL_20;
			unit_buf_cur = g_usbkb_unit_buf;
			do
			{
				if ( !*unit_buf_cur )
					break;
				++unit_index2;
				++unit_buf_cur;
			}
			while ( unit_index2 < g_usbkb_cfg_keybd );
			if ( unit_index2 >= g_usbkb_cfg_keybd )
			{
LABEL_20:
				printf("logical error\n");
				return 0;
			}
			unit_tmp1->number = unit_index2;
		}
		unit_tmp1->payload = maxPacketSize;
		unit_tmp1->ifnum = interfaceNumber;
		unit_tmp1->as = alternateSetting;
		unit_tmp1->count = 0;
		unit_tmp1->ledptn = 0;
		unit_tmp1->old_ledbtn = 0;
		unit_tmp1->old_ledbtn2 = 1;
		unit_tmp1->rp = 0;
		unit_tmp1->wp = 0;
		unit_tmp1->rblen = 0;
	}
	return unit_tmp1;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 402084: using guessed type int g_usbkb_cfg_keybd;
// 401244: using guessed type u8 devloc_stk[8];

//----- (00401458) --------------------------------------------------------
int usbkb_donecb_SetConfiguration(int result, int count, ps2kbd_unit *arg)
{
	int xferret; // $v0
	UsbDeviceRequest devreq; // [sp+18h] [-8h] BYREF

	if ( result )
		printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "sceUsbdSetConfiguration", result);
	if ( arg->as <= 0 )
		return usbkb_set_idle_request(arg);
	devreq.requesttype = 1;
	devreq.request = 11;
	devreq.value = arg->as;
	devreq.length = 0;
	devreq.index = arg->ifnum;
	xferret = sceUsbdTransferPipe(arg->c_pipe, 0, 0, &devreq, (sceUsbdDoneCallback)usbkb_donecb_SetInterface, arg);
	if ( xferret )
		return printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "sceUsbdSetInterface", xferret);
	return xferret;
}

//----- (0040152C) --------------------------------------------------------
int usbkb_donecb_SetInterface(int result, int count, ps2kbd_unit *arg)
{
	if ( result )
		printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "sceUsbdSetInterface", result);
	return usbkb_set_idle_request(arg);
}

//----- (00401574) --------------------------------------------------------
int usbkb_set_idle_request(ps2kbd_unit *cbArg)
{
	int xferret; // $v0
	UsbDeviceRequest devreq; // [sp+18h] [-8h] BYREF

	devreq.requesttype = 33;
	devreq.request = 10;
	devreq.value = 0;
	devreq.length = 0;
	devreq.index = cbArg->ifnum;
	xferret = sceUsbdTransferPipe(cbArg->c_pipe, 0, 0, &devreq, (sceUsbdDoneCallback)usbkb_donecb_set_idle_request, cbArg);
	if ( xferret )
		return printf("usbkeybd%d: %s -> 0x%x\n", cbArg->number, "set_idle_request", xferret);
	return xferret;
}

//----- (004015FC) --------------------------------------------------------
int usbkb_donecb_set_idle_request(int result, int count, ps2kbd_unit *arg)
{
	if ( result )
		printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "set_idle_request_done", result);
	return usbkb_data_transfer(arg);
}

//----- (00401644) --------------------------------------------------------
int usbkb_data_transfer(ps2kbd_unit *cbArg)
{
	int xferret; // $v0

	xferret = sceUsbdTransferPipe(cbArg->d_pipe, cbArg->data, cbArg->payload, 0, (sceUsbdDoneCallback)usbkb_donecb_data_transfer, cbArg);
	if ( xferret )
		return printf("usbkeybd%d: %s -> 0x%x\n", cbArg->number, "sceUsbdInterruptTransfer", xferret);
	return xferret;
}

//----- (004016AC) --------------------------------------------------------
int usbkb_donecb_data_transfer(int result, int count, ps2kbd_unit *arg)
{
	int ledmask; // $s1
	int data_index1; // $s0
	int data_index2; // $s0
	unsigned int data_tmp3; // $v1
	int xferret; // $v0
	int ringbuf_i; // $s0
	u8 *ringbuf_tmp; // $a0
	u8 *ringbuf_cur_tmp; // $v1
	UsbDeviceRequest devreq; // [sp+18h] [-10h] BYREF
	int state; // [sp+20h] [-8h] BYREF

	ledmask = 0;
	if ( result )
	{
		printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "data_transfer_done:sceUsbdInterruptTransfer", result);
		return usbkb_data_transfer(arg);
	}
	data_index1 = 0;
	if ( g_usbkb_cfg_debug > 0 )
	{
		arg->count += 1;
		printf("usbkeybd%d: count=%d led=%02X data=(", arg->number, arg->count, arg->ledptn);
		if ( count > 0 )
		{
			do
			{
				printf(" %02x", arg->data[data_index1++]);
			}
			while ( data_index1 < count );
		}
		printf(" )\n");
	}
	data_index2 = 2;
	if ( count > 2 )
	{
		while ( 1 )
		{
			data_tmp3 = arg->data[data_index2];
			if ( data_tmp3 == 0x53 )
				break;
			if ( data_tmp3 >= 0x54 )
			{
				if ( data_tmp3 == 0x90 )
				{
					ledmask |= 0x10u;
					goto LABEL_25;
				}
				if ( data_tmp3 == 0xE3 )
				{
					ledmask |= 8u;
					goto LABEL_25;
				}
				++data_index2;
			}
			else
			{
				if ( data_tmp3 == 0x39 )
				{
					if ( arg->old_ledbtn2 == 1 || (arg->old_ledbtn2 == 2 && (arg->data[0] & 0x22) != 0))
						ledmask |= 2u;
					goto LABEL_25;
				}
				if ( data_tmp3 == 0x47 )
				{
					ledmask |= 4u;
					goto LABEL_25;
				}
				++data_index2;
			}
LABEL_26:
			if ( data_index2 >= count )
				goto LABEL_27;
		}
		ledmask |= 1u;
LABEL_25:
		++data_index2;
		goto LABEL_26;
	}
LABEL_27:
	if ( arg->old_ledbtn == ledmask || !arg->old_ledbtn2 )
	{
		usbkb_data_transfer(arg);
	}
	else
	{
		arg->old_ledbtn = ledmask;
		arg->ledptn ^= ledmask;
		devreq.requesttype = 33;
		devreq.request = 9;
		devreq.value = 512;
		devreq.length = 1;
		devreq.index = arg->ifnum;
		xferret = sceUsbdTransferPipe(arg->c_pipe, &arg->ledptn, 1u, &devreq, (sceUsbdDoneCallback)usbkb_donecb_led_transfer, arg);
		if ( xferret )
			printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "SET_REPORT", xferret);
	}
	CpuSuspendIntr(&state);
	ringbuf_i = 0;
	ringbuf_tmp = arg->ringbuf[arg->wp];
	ringbuf_tmp[1] = count;
	*ringbuf_tmp = arg->ledptn;
	if ( count > 0 )
	{
		ringbuf_cur_tmp = ringbuf_tmp;
		do
		{
			ringbuf_cur_tmp[2] = arg->data[ringbuf_i++];
			ringbuf_cur_tmp = &ringbuf_tmp[ringbuf_i];
		}
		while ( ringbuf_i < count );
	}
	arg->wp += 1;
	if ( arg->wp >= 3 )
		arg->wp = 0;
	if ( arg->rblen >= 3 )
	{
		arg->rp += 1;
		if ( arg->rp >= 3 )
			arg->rp = 0;
	}
	else
	{
		arg->rblen += 1;
	}
	return CpuResumeIntr(state);
}
// 4020F0: using guessed type int g_usbkb_cfg_debug;

//----- (004019D8) --------------------------------------------------------
int usbkb_donecb_led_transfer(int result, int count, ps2kbd_unit *arg)
{
	if ( result )
		printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "led_transfer_done", result);
	return usbkb_data_transfer(arg);
}

//----- (00401A20) --------------------------------------------------------
int usbkb_drv_disconnect(int devID)
{
	ps2kbd_unit *unit; // $s0

	unit = sceUsbdGetPrivateData(devID);
	if ( unit )
	{
		--g_usbkb_used_kb_count;
		g_usbkb_unit_buf[unit->number] = 0;
		if ( g_usbkb_cfg_debug > 0 )
			printf("usbkeybd%d: detached\n", unit->number);
		FreeSysMemory(unit);
		return 0;
	}
	return -1;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 4020F0: using guessed type int g_usbkb_cfg_debug;
