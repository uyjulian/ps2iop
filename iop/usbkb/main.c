
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
	int arg_rvalue; // $s0
	int devloc_i1; // $s2
	u8 *devloc_buf; // $v0
	int devloc_i2; // $s0
	int unit_index; // $s2
	int lddres; // $v0
	iop_thread_t thparam; // [sp+10h] [-20h] BYREF
	int state; // [sp+28h] [-8h] BYREF

	if ( ac < 0 )
		return usbkb_unload();
	printf("USB Keyboard Driver 1.03\n");
	g_usbkb_cfg_lmode = 0;
	g_usbkb_cfg_keybd = 2;
	g_usbkb_cfg_debug = 0;
	for ( cur_ac = 0; cur_ac < ac; cur_ac += 1 )
	{
		for ( arg_rvalue = 0; av[cur_ac][arg_rvalue] && av[cur_ac][arg_rvalue] != '='; arg_rvalue += 1 )
		{
		}
		if ( av[cur_ac][arg_rvalue] )
		{
			av[cur_ac][arg_rvalue] = 0;
			arg_rvalue += 1;
		}
		if ( !strcmp(av[cur_ac], "lmode") )
		{
			if ( !strcmp(&av[cur_ac][arg_rvalue], "AUTOLOAD") )
			{
				g_usbkb_cfg_lmode = 1;
				break;
			}
			if ( !strcmp(&av[cur_ac][arg_rvalue], "TESTLOAD") )
			{
				g_usbkb_cfg_lmode = 2;
				break;
			}
		}
		if ( !strcmp(av[cur_ac], "keybd") )
		{
			g_usbkb_cfg_keybd = strtol(&av[cur_ac][arg_rvalue], 0, 10);
			if ( g_usbkb_cfg_keybd <= 0 )
				g_usbkb_cfg_keybd = 1;
			if ( g_usbkb_cfg_keybd >= 128 )
				g_usbkb_cfg_keybd = 127;
		}
		if ( !strcmp(av[cur_ac], "debug") )
			g_usbkb_cfg_debug = strtol(&av[cur_ac][arg_rvalue], 0, 10);
	}
	printf("Max Keyboards : %d\n", g_usbkb_cfg_keybd);
	printf("Debug level : %d\n", g_usbkb_cfg_debug);
	CpuSuspendIntr(&state);
	g_usbkb_unit_buf = AllocSysMemory(0, 4 * g_usbkb_cfg_keybd, 0);
	CpuResumeIntr(state);
	if ( !g_usbkb_unit_buf )
	{
		return 1;
	}
	CpuSuspendIntr(&state);
	g_usbkb_devloc_buf = AllocSysMemory(0, 4 * g_usbkb_cfg_keybd, 0);
	CpuResumeIntr(state);
	if ( !g_usbkb_devloc_buf )
	{
		CpuSuspendIntr(&state);
		FreeSysMemory(g_usbkb_unit_buf);
		CpuResumeIntr(state);
		return 1;
	}
	for ( devloc_i1 = 0; devloc_i1 < g_usbkb_cfg_keybd; devloc_i1 += 1 )
	{
		CpuSuspendIntr(&state);
		devloc_buf = AllocSysMemory(0, 7, 0);
		g_usbkb_devloc_buf[devloc_i1] = devloc_buf;
		CpuResumeIntr(state);
		if ( !g_usbkb_devloc_buf[devloc_i1] )
		{
			CpuSuspendIntr(&state);
			FreeSysMemory(g_usbkb_unit_buf);
			for ( devloc_i2 = 0; devloc_i2 < devloc_i1; devloc_i2 += 1 )
			{
				FreeSysMemory(g_usbkb_devloc_buf[devloc_i2]);
			}
			FreeSysMemory(g_usbkb_devloc_buf);
			CpuResumeIntr(state);
			return 1;
		}
	}
	g_usbkb_used_kb_count = 0;
	for ( unit_index = 0; unit_index < g_usbkb_cfg_keybd; unit_index += 1 )
	{
		g_usbkb_unit_buf[unit_index] = 0;
		*g_usbkb_devloc_buf[unit_index] = 0;
	}
	switch ( g_usbkb_cfg_lmode )
	{
		default:
		case 0:
			g_usbkeybd_resident_flag = 1;
			break;
		case 1:
			printf("usbkeybd : AUTOLOAD MODE\n");
			g_usbkeybd_resident_flag = 0;
			break;
		case 2:
			printf("usbkeybd : TESTLOAD MODE\n");
			g_usbkeybd_resident_flag = 0;
			break;
	}
	lddres = sceUsbdRegisterLdd(&g_kbd_driver);
	if ( lddres )
		printf("usbkeybd: sceUsbdRegisterLdd -> 0x%x\n", lddres);
	if ( g_usbkb_cfg_lmode == 2 )
	{
		sceUsbdUnregisterLdd(&g_kbd_driver);
		usbkb_cleanup();
		return (g_usbkeybd_resident_flag != 1) ? 1 : 5;
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
	int state; // [sp+10h] [-8h] BYREF

	for ( i = 0; i < g_usbkb_cfg_keybd; i += 1 )
	{
		CpuSuspendIntr(&state);
		FreeSysMemory(g_usbkb_devloc_buf[i]);
		CpuResumeIntr(state);
		unit = g_usbkb_unit_buf[i];
		if ( unit )
		{
			sceUsbdClosePipe(unit->c_pipe);
			sceUsbdClosePipe(unit->d_pipe);
			CpuSuspendIntr(&state);
			FreeSysMemory(unit);
			CpuResumeIntr(state);
		}
	}
	CpuSuspendIntr(&state);
	FreeSysMemory(g_usbkb_unit_buf);
	FreeSysMemory(g_usbkb_devloc_buf);
	return CpuResumeIntr(state);
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

	buffer[0] = g_usbkb_cfg_keybd;
	buffer[1] = g_usbkb_used_kb_count;
	infobuf = buffer + 2;
	for ( i = 0; i < g_usbkb_cfg_keybd; i += 1 )
	{
		infobuf[i] = g_usbkb_unit_buf[i] ? 1 : 0;
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
	int j; // $v1
	int i; // $v1
	int state; // [sp+10h] [-8h] BYREF

	unit_index = *buffer;
	buffer[1] = -1;
	if ( g_usbkb_cfg_keybd < unit_index )
	{
		printf("Illegal index_no : %d\n", unit_index);
		return buffer;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("USB keyboard %d is not connected!\n", unit_index);
		return buffer;
	}
	CpuSuspendIntr(&state);
	infobuf = buffer + 2;
	if ( unit->rblen <= 0 )
	{
		buffer[0] = unit->ledptn;
		buffer[1] = 0;
		for ( i = 0; i < unit->payload; i += 1 )
		{
			infobuf[i] = 0;
		}
	}
	else
	{
		buffer[0] = unit->ringbuf[unit->rp][0];
		buffer[1] = unit->ringbuf[unit->rp][1];
		for ( j = 0; j < unit->payload; j += 1 )
		{
			infobuf[j] = unit->ringbuf[unit->rp][j + 2];
		}
		unit->rp += 1;
		if ( unit->rp >= 3 )
			unit->rp = 0;
		unit->rblen -= 1;
	}
	CpuResumeIntr(state);
	return buffer;
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400A50) --------------------------------------------------------
u8 *usbkb_rpc_fno_03_GetLocation(int fno, u8 *buffer)
{
	int unit_index; // $a1
	u8 *chrbuf; // $s0
	ps2kbd_unit *unit; // $v0
	int DeviceLocation; // $a3
	int tmpchr_i; // $v1
	int i; // $v1
	u8 devloc_stk[8]; // [sp+10h] [-8h] BYREF

	unit_index = *buffer;
	chrbuf = buffer;
	for ( i = 7; i >= 0; --i )
		chrbuf[i] = 0;
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("Illegal USB keyboard number! : %d\n", unit_index);
		return buffer;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("USB keyboard %d is not connected!\n", unit_index);
		return buffer;
	}
	DeviceLocation = sceUsbdGetDeviceLocation(unit->dev_id, devloc_stk);
	if ( DeviceLocation )
	{
		printf(
			"usbkeybd%d: %s -> 0x%x\n",
			g_usbkb_unit_buf[*buffer]->number,
			"sceUsbdGetDeviceLocation",
			DeviceLocation);
		return buffer;
	}
	for ( tmpchr_i = 0; tmpchr_i < 7; tmpchr_i += 1 )
	{
		chrbuf[i] = devloc_stk[tmpchr_i];
	}
	return buffer;
}
// 402084: using guessed type int g_usbkb_cfg_keybd;
// 400A50: using guessed type u8 devloc_stk[8];

//----- (00400B8C) --------------------------------------------------------
u8 *usbkb_rpc_fno_04_SetLEDStatus(int fno, u8 *buffer)
{
	int unit_index; // $a1
	ps2kbd_unit *unit; // $s0
	int xferret; // $v0
	UsbDeviceRequest devreq; // [sp+18h] [-8h] BYREF

	unit_index = *buffer;
	buffer[1] = ~buffer[1];
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("Illegal USB keyboard number! : %d\n", unit_index);
		return buffer;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("Keyboard %d is not connected.\n", unit_index);
		return buffer;
	}
	unit->ledptn = ~buffer[1];
	devreq.requesttype = 33;
	devreq.request = 9;
	devreq.value = 512;
	devreq.length = 1;
	devreq.index = unit->ifnum;
	xferret = sceUsbdTransferPipe(unit->c_pipe, &unit->ledptn, 1u, &devreq, (sceUsbdDoneCallback)usbkb_donecb_SetLEDStatus, unit);
	if ( !xferret )
	{
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "SET_REPORT", xferret);
		return buffer;
	}
	buffer[1] = unit->ledptn;
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

	unit_index = *buffer;
	buffer[1] = ~buffer[1];
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("Illegal USB keyboard number! : %d\n");
		return buffer;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("Keyboard %d is not connected.\n");
		return buffer;
	}
	unit->old_ledbtn2 = ~buffer[1];
	buffer[1] = ~buffer[1];
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
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("clear_rbuf() : Illegal USB keyboard number! : %d\n");
		return buffer;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("clear_rbuf() : Keyboard %d is not connected.\n");
		return buffer;
	}
	CpuSuspendIntr(&state);
	unit->wp = 0;
	unit->rp = 0;
	unit->rblen = 0;
	CpuResumeIntr(state);
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
	if ( !dev )
		return 0;
	if ( dev->bDeviceClass )
		return 0;
	if ( dev->bNumConfigurations != 1 )
		return 0;
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
	if ( intf->bInterfaceClass != 3 )
		return 0;
	if ( intf->bInterfaceSubClass != 1 )
		return 0;
	if ( intf->bInterfaceProtocol != 1 )
		return 0;
	if ( intf->bNumEndpoints != 1 )
		return -1;
	endp = sceUsbdScanStaticDescriptor(devID, intf, 5u);
	if ( !endp )
		return -1;
	if ( (endp->bEndpointAddress & 0x80) == 0 )
		return -1;
	if ( (endp->bmAttributes & 3) != 3 )
		return -1;
	maxPacketSize = endp->wMaxPacketSizeLB | (endp->wMaxPacketSizeHB << 8);
	if ( maxPacketSize >= 65 )
		return -1;
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
		int i;

		printf("dev_id:%d\n", devID);
		printf("usbkeybd%d: attached (port=", unit->number);
		for ( i = 0; i < 7 && g_usbkb_devloc_buf[unit->number][i]; i += 1 )
		{
			printf("%s%d", i ? "," : "", g_usbkb_devloc_buf[unit->number][i]);
		}
		printf(")\n");
	}
	g_usbkb_used_kb_count += 1;
	g_usbkb_unit_buf[unit->number] = unit;
	return 0;
}
// 401F30: using guessed type int nullstr;
// 402080: using guessed type int g_usbkb_used_kb_count;
// 4020F0: using guessed type int g_usbkb_cfg_debug;

//----- (00401244) --------------------------------------------------------
ps2kbd_unit *usbkb_allocate_unit(int devID, int maxPacketSize, int interfaceNumber, int alternateSetting)
{
	ps2kbd_unit *unit; // $v0
	int DeviceLocation; // $v0
	int unit_index1; // $a2
	int devloc_index; // $a1
	int unit_index2; // $a2
	u8 devloc_stk[8]; // [sp+10h] [-8h] BYREF

	if ( g_usbkb_used_kb_count >= g_usbkb_cfg_keybd )
		return 0;
	unit = AllocSysMemory(0, maxPacketSize + 0xF8, 0);
	if ( !unit )
		return 0;
	unit->dev_id = devID;
	DeviceLocation = sceUsbdGetDeviceLocation(devID, devloc_stk);
	if ( DeviceLocation )
	{
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "sceUsbdGetDeviceLocation", DeviceLocation);
		return 0;
	}
	for ( unit_index1 = 0; unit_index1 < g_usbkb_cfg_keybd; unit_index1 += 1 )
	{
		for ( devloc_index = 0; devloc_index < 7; devloc_index += 1 )
		{
			if ( g_usbkb_devloc_buf[unit_index1][devloc_index] != devloc_stk[devloc_index] )
				break;
		}
		if ( devloc_index == 7 )
			break;
	}
	unit->number = unit_index1;
	if ( unit_index1 == g_usbkb_cfg_keybd )
	{
		for ( unit_index2 = 0; unit_index2 < g_usbkb_cfg_keybd; unit_index2 += 1 )
		{
			if ( !g_usbkb_unit_buf[unit_index2] )
				break;
		}
		if ( unit_index2 >= g_usbkb_cfg_keybd )
		{
			printf("logical error\n");
			return 0;
		}
		unit->number = unit_index2;
	}
	unit->payload = maxPacketSize;
	unit->ifnum = interfaceNumber;
	unit->as = alternateSetting;
	unit->count = 0;
	unit->ledptn = 0;
	unit->old_ledbtn = 0;
	unit->old_ledbtn2 = 1;
	unit->rp = 0;
	unit->wp = 0;
	unit->rblen = 0;
	return unit;
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
	int xferret; // $v0
	int ringbuf_i; // $s0
	UsbDeviceRequest devreq; // [sp+18h] [-10h] BYREF
	int state; // [sp+20h] [-8h] BYREF

	ledmask = 0;
	if ( result )
	{
		printf("usbkeybd%d: %s -> 0x%x\n", arg->number, "data_transfer_done:sceUsbdInterruptTransfer", result);
		return usbkb_data_transfer(arg);
	}
	if ( g_usbkb_cfg_debug > 0 )
	{
		arg->count += 1;
		printf("usbkeybd%d: count=%d led=%02X data=(", arg->number, arg->count, arg->ledptn);
		for ( data_index1 = 0; data_index1 < count; data_index1 += 1 )
		{
			printf(" %02x", arg->data[data_index1]);
		}
		printf(" )\n");
	}
	for ( data_index2 = 2; data_index2 < count; data_index2 += 1 )
	{
		switch ( arg->data[data_index2] )
		{
			case 0x39:
				if ( arg->old_ledbtn2 == 1 || (arg->old_ledbtn2 == 2 && (arg->data[0] & 0x22) != 0))
					ledmask |= 2u;
				break;
			case 0x47:
				ledmask |= 4u;
				break;
			case 0x53:
				ledmask |= 1u;
				break;
			case 0x90:
				ledmask |= 0x10u;
				break;
			case 0xE3:
				ledmask |= 8u;
				break;
		}
	}
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
	arg->ringbuf[arg->wp][0] = arg->ledptn;
	arg->ringbuf[arg->wp][1] = count;
	for ( ringbuf_i = 0; ringbuf_i < count; ringbuf_i += 1 )
	{
		arg->ringbuf[ringbuf_i][2] = arg->data[ringbuf_i];
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
		g_usbkb_used_kb_count -= 1;
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
