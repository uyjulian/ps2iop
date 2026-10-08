
#include "irx_imports.h"
#include <usbd_macro.h>

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
	u8 m_padding[2];
	u8 data[];
} ps2kbd_unit;

//-------------------------------------------------------------------------
// Function declarations

int _start(int ac, char **av);
static void usbkb_cleanup(void);
static int usbkb_unload(void);
static void usbkb_thread_proc(void *userdata);
static void *usbkb_rpc_func(int fno, void *buffer, int length);
static void usbkb_rpc_fno_01_GetInfo(int fno, u8 *buffer);
static void usbkb_rpc_fno_02_Read(int fno, u8 *buffer);
static void usbkb_rpc_fno_03_GetLocation(int fno, u8 *buffer);
static void usbkb_rpc_fno_04_SetLEDStatus(int fno, u8 *buffer);
static void usbkb_donecb_SetLEDStatus(int retres, int count, void *arg);
static void usbkb_rpc_fno_05_SetLEDMode(int fno, u8 *buffer);
static void usbkb_rpc_fno_06_ClearRbuf(int fno, const u8 *buffer);
static int usbkb_drv_probe(int devID);
static int usbkb_drv_connect(int devID);
static ps2kbd_unit *usbkb_allocate_unit(int devID, int maxPacketSize, int interfaceNumber, int alternateSetting);
static void usbkb_donecb_SetConfiguration(int retres, int count, void *arg);
static void usbkb_donecb_SetInterface(int retres, int count, void *arg);
static void usbkb_set_idle_request(ps2kbd_unit *unit);
static void usbkb_donecb_set_idle_request(int retres, int count, void *arg);
static void usbkb_data_transfer(ps2kbd_unit *unit);
static void usbkb_donecb_data_transfer(int retres, int count, void *arg);
static void usbkb_donecb_led_transfer(int retres, int count, void *arg);
static int usbkb_drv_disconnect(int devID);

//-------------------------------------------------------------------------
// Data declarations

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
	NULL,
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
	int i; // $s2
	int j; // $s0
	int lddres; // $v0
	iop_thread_t thparam; // [sp+10h] [-20h] BYREF
	int state; // [sp+28h] [-8h] BYREF

	if ( ac < 0 )
		return usbkb_unload();
	printf("USB Keyboard Driver 1.03\n");
	g_usbkb_cfg_lmode = 0;
	g_usbkb_cfg_keybd = 2;
	g_usbkb_cfg_debug = 0;
	for ( i = 0; i < ac; i += 1 )
	{
		for ( j = 0; av[i][j] && av[i][j] != '='; j += 1 );
		if ( av[i][j] )
		{
			av[i][j] = 0;
			j += 1;
		}
		if ( !strcmp(av[i], "lmode") )
		{
			if ( !strcmp(&av[i][j], "AUTOLOAD") )
			{
				g_usbkb_cfg_lmode = 1;
				break;
			}
			if ( !strcmp(&av[i][j], "TESTLOAD") )
			{
				g_usbkb_cfg_lmode = 2;
				break;
			}
		}
		if ( !strcmp(av[i], "keybd") )
		{
			g_usbkb_cfg_keybd = strtol(&av[i][j], NULL, 10);
			if ( g_usbkb_cfg_keybd <= 0 )
				g_usbkb_cfg_keybd = 1;
			if ( g_usbkb_cfg_keybd >= 128 )
				g_usbkb_cfg_keybd = 127;
		}
		if ( !strcmp(av[i], "debug") )
			g_usbkb_cfg_debug = strtol(&av[i][j], NULL, 10);
	}
	printf("Max Keyboards : %d\n", g_usbkb_cfg_keybd);
	printf("Debug level : %d\n", g_usbkb_cfg_debug);
	CpuSuspendIntr(&state);
	g_usbkb_unit_buf = AllocSysMemory(0, sizeof(*g_usbkb_unit_buf) * g_usbkb_cfg_keybd, NULL);
	CpuResumeIntr(state);
	if ( !g_usbkb_unit_buf )
		return 1;
	CpuSuspendIntr(&state);
	g_usbkb_devloc_buf = AllocSysMemory(0, sizeof(*g_usbkb_devloc_buf) * g_usbkb_cfg_keybd, NULL);
	CpuResumeIntr(state);
	if ( !g_usbkb_devloc_buf )
	{
		CpuSuspendIntr(&state);
		FreeSysMemory(g_usbkb_unit_buf);
		CpuResumeIntr(state);
		return 1;
	}
	for ( i = 0; i < g_usbkb_cfg_keybd; i += 1 )
	{
		CpuSuspendIntr(&state);
		g_usbkb_devloc_buf[i] = AllocSysMemory(0, 7, NULL);
		CpuResumeIntr(state);
		if ( !g_usbkb_devloc_buf[i] )
		{
			CpuSuspendIntr(&state);
			FreeSysMemory(g_usbkb_unit_buf);
			for ( j = 0; j < i; j += 1 )
				FreeSysMemory(g_usbkb_devloc_buf[j]);
			FreeSysMemory(g_usbkb_devloc_buf);
			CpuResumeIntr(state);
			return 1;
		}
	}
	g_usbkb_used_kb_count = 0;
	for ( i = 0; i < g_usbkb_cfg_keybd; i += 1 )
	{
		g_usbkb_unit_buf[i] = NULL;
		*g_usbkb_devloc_buf[i] = 0;
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
	thparam.attr = 0x2000000;
	thparam.thread = &usbkb_thread_proc;
	thparam.priority = 50;
	thparam.stacksize = 4096;
	thparam.option = 0;
	if ( !g_usbkeybd_resident_flag || ((g_usbkb_thread_id = CreateThread(&thparam)) <= 0) )
	{
		sceUsbdUnregisterLdd(&g_kbd_driver);
		usbkb_cleanup();
		return 1;
	}
	StartThread(g_usbkb_thread_id, NULL);
	return 2;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 402084: using guessed type int g_usbkb_cfg_keybd;
// 402090: using guessed type int g_usbkb_thread_id;
// 4020F0: using guessed type int g_usbkb_cfg_debug;
// 402188: using guessed type int g_usbkeybd_resident_flag;
// 40218C: using guessed type int g_usbkb_cfg_lmode;

//----- (00400554) --------------------------------------------------------
static void usbkb_cleanup(void)
{
	int i; // $s1
	int state; // [sp+10h] [-8h] BYREF

	for ( i = 0; i < g_usbkb_cfg_keybd; i += 1 )
	{
		CpuSuspendIntr(&state);
		FreeSysMemory(g_usbkb_devloc_buf[i]);
		CpuResumeIntr(state);
		if ( g_usbkb_unit_buf[i] )
		{
			sceUsbdClosePipe(g_usbkb_unit_buf[i]->c_pipe);
			sceUsbdClosePipe(g_usbkb_unit_buf[i]->d_pipe);
			CpuSuspendIntr(&state);
			FreeSysMemory(g_usbkb_unit_buf[i]);
			CpuResumeIntr(state);
		}
	}
	CpuSuspendIntr(&state);
	FreeSysMemory(g_usbkb_unit_buf);
	FreeSysMemory(g_usbkb_devloc_buf);
	CpuResumeIntr(state);
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400690) --------------------------------------------------------
static int usbkb_unload(void)
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
static void usbkb_thread_proc(void *userdata)
{
	(void)userdata;

	sceSifInitRpc(0);
	sceSifSetRpcQueue(&g_usbkb_rpc_qd, GetThreadId());
	sceSifRegisterRpc(&g_usbkb_rpc_sd, 0x80000211, usbkb_rpc_func, g_usbkb_rpc_buf, NULL, NULL, &g_usbkb_rpc_qd);
	sceSifRpcLoop(&g_usbkb_rpc_qd);
}
// 4020F8: using guessed type int g_usbkb_rpc_buf[36];

//----- (0040076C) --------------------------------------------------------
static void *usbkb_rpc_func(int fno, void *buffer, int length)
{
	(void)length;

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
static void usbkb_rpc_fno_01_GetInfo(int fno, u8 *buffer)
{
	u8 *infobuf; // $a0
	int i; // $a2

	(void)fno;

	buffer[0] = g_usbkb_cfg_keybd;
	buffer[1] = g_usbkb_used_kb_count;
	infobuf = buffer + 2;
	for ( i = 0; i < g_usbkb_cfg_keybd; i += 1 )
		infobuf[i] = g_usbkb_unit_buf[i] ? 1 : 0;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (004008C4) --------------------------------------------------------
static void usbkb_rpc_fno_02_Read(int fno, u8 *buffer)
{
	int unit_index; // $a1
	ps2kbd_unit *unit; // $s0
	u8 *infobuf; // $a0
	int i; // $v1
	int state; // [sp+10h] [-8h] BYREF

	(void)fno;

	unit_index = *buffer;
	buffer[1] = -1;
	if ( g_usbkb_cfg_keybd < unit_index )
	{
		printf("Illegal index_no : %d\n", unit_index);
		return;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("USB keyboard %d is not connected!\n", unit_index);
		return;
	}
	CpuSuspendIntr(&state);
	infobuf = buffer + 2;
	if ( unit->rblen <= 0 )
	{
		buffer[0] = unit->ledptn;
		buffer[1] = 0;
		for ( i = 0; i < unit->payload; i += 1 )
			infobuf[i] = 0;
	}
	else
	{
		buffer[0] = unit->ringbuf[unit->rp][0];
		buffer[1] = unit->ringbuf[unit->rp][1];
		for ( i = 0; i < unit->payload; i += 1 )
			infobuf[i] = unit->ringbuf[unit->rp][i + 2];
		unit->rp += 1;
		if ( unit->rp >= 3 )
			unit->rp = 0;
		unit->rblen -= 1;
	}
	CpuResumeIntr(state);
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400A50) --------------------------------------------------------
static void usbkb_rpc_fno_03_GetLocation(int fno, u8 *buffer)
{
	int unit_index; // $a1
	u8 *chrbuf; // $s0
	ps2kbd_unit *unit; // $v0
	int DeviceLocation; // $a3
	int i; // $v1
	u8 devloc_stk[7]; // [sp+10h] [-8h] BYREF

	(void)fno;

	unit_index = *buffer;
	chrbuf = buffer;
	for ( i = 0; i < (int)sizeof(devloc_stk); i += 1 )
		chrbuf[i] = 0;
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("Illegal USB keyboard number! : %d\n", unit_index);
		return;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("USB keyboard %d is not connected!\n", unit_index);
		return;
	}
	DeviceLocation = sceUsbdGetDeviceLocation(unit->dev_id, devloc_stk);
	if ( DeviceLocation )
	{
		printf(
			"usbkeybd%d: %s -> 0x%x\n",
			unit->number,
			"sceUsbdGetDeviceLocation",
			DeviceLocation);
		return;
	}
	for ( i = 0; i < (int)sizeof(devloc_stk); i += 1 )
		chrbuf[i] = devloc_stk[i];
}
// 402084: using guessed type int g_usbkb_cfg_keybd;
// 400A50: using guessed type u8 devloc_stk[8];

//----- (00400B8C) --------------------------------------------------------
static void usbkb_rpc_fno_04_SetLEDStatus(int fno, u8 *buffer)
{
	int unit_index; // $a1
	ps2kbd_unit *unit; // $s0
	int xferret; // $v0

	(void)fno;

	unit_index = *buffer;
	buffer[1] = ~buffer[1];
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("Illegal USB keyboard number! : %d\n", unit_index);
		return;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("Keyboard %d is not connected.\n", unit_index);
		return;
	}
	unit->ledptn = ~buffer[1];
	xferret = sceUsbdControlTransfer(unit->c_pipe, 0x21, USB_REQ_SET_REPORT, 512, unit->ifnum, sizeof(unit->ledptn), &unit->ledptn, &usbkb_donecb_SetLEDStatus, unit);
	if ( !xferret )
	{
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "SET_REPORT", xferret);
		return;
	}
	buffer[1] = unit->ledptn;
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400CBC) --------------------------------------------------------
static void usbkb_donecb_SetLEDStatus(int retres, int count, void *arg)
{
	ps2kbd_unit *unit;
	(void)count;

	unit = (ps2kbd_unit *)arg;
	if ( retres )
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "set_led_status", retres);
}

//----- (00400CF4) --------------------------------------------------------
static void usbkb_rpc_fno_05_SetLEDMode(int fno, u8 *buffer)
{
	int unit_index; // $a1
	ps2kbd_unit *unit; // $a0

	(void)fno;

	unit_index = *buffer;
	buffer[1] = ~buffer[1];
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("Illegal USB keyboard number! : %d\n", unit_index);
		return;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("Keyboard %d is not connected.\n", unit_index);
		return;
	}
	unit->old_ledbtn2 = ~buffer[1];
	buffer[1] = ~buffer[1];
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400D88) --------------------------------------------------------
static void usbkb_rpc_fno_06_ClearRbuf(int fno, const u8 *buffer)
{
	int unit_index; // $a1
	ps2kbd_unit *unit; // $s0
	int state; // [sp+10h] [-8h] BYREF

	(void)fno;

	unit_index = *buffer;
	if ( unit_index >= g_usbkb_cfg_keybd )
	{
		printf("clear_rbuf() : Illegal USB keyboard number! : %d\n", unit_index);
		return;
	}
	unit = g_usbkb_unit_buf[unit_index];
	if ( !unit )
	{
		printf("clear_rbuf() : Keyboard %d is not connected.\n", unit_index);
		return;
	}
	CpuSuspendIntr(&state);
	unit->wp = 0;
	unit->rp = 0;
	unit->rblen = 0;
	CpuResumeIntr(state);
}
// 402084: using guessed type int g_usbkb_cfg_keybd;

//----- (00400E30) --------------------------------------------------------
static int usbkb_drv_probe(int devID)
{
	UsbDeviceDescriptor *dev; // $a1
	const UsbInterfaceDescriptor *intf; // $a0

	if ( g_usbkb_used_kb_count >= g_usbkb_cfg_keybd )
		return 0;
	dev = sceUsbdScanStaticDescriptor(devID, NULL, 1u);
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
static int usbkb_drv_connect(int devID)
{
	UsbConfigDescriptor *conf; // $v0
	UsbInterfaceDescriptor *intf; // $s0
	UsbEndpointDescriptor *endp; // $s2
	int maxPacketSize; // $a1
	ps2kbd_unit *unit; // $s1
	int xferret; // $s0
	int DeviceLocation; // $s0

	conf = sceUsbdScanStaticDescriptor(devID, NULL, 2u);
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
	unit->c_pipe = sceUsbdOpenPipe(devID, NULL);
	if ( unit->c_pipe < 0 )
		return -1;
	unit->d_pipe = sceUsbdOpenPipe(devID, endp);
	if ( unit->d_pipe < 0 )
	{
		FreeSysMemory(unit);
		return -1;
	}
	sceUsbdSetPrivateData(devID, unit);
	xferret = sceUsbdSetConfiguration(unit->c_pipe, conf->bConfigurationValue, &usbkb_donecb_SetConfiguration, unit);
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
			printf("%s%d", i ? "," : "", g_usbkb_devloc_buf[unit->number][i]);
		printf(")\n");
	}
	g_usbkb_used_kb_count += 1;
	g_usbkb_unit_buf[unit->number] = unit;
	return 0;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 4020F0: using guessed type int g_usbkb_cfg_debug;

//----- (00401244) --------------------------------------------------------
static ps2kbd_unit *usbkb_allocate_unit(int devID, int maxPacketSize, int interfaceNumber, int alternateSetting)
{
	ps2kbd_unit *unit; // $v0
	int DeviceLocation; // $v0
	int i; // $a2
	int j; // $a1
	u8 devloc_stk[7]; // [sp+10h] [-8h] BYREF

	if ( g_usbkb_used_kb_count >= g_usbkb_cfg_keybd )
		return NULL;
	unit = AllocSysMemory(0, sizeof(*unit) + maxPacketSize, NULL);
	if ( !unit )
		return NULL;
	unit->dev_id = devID;
	DeviceLocation = sceUsbdGetDeviceLocation(devID, devloc_stk);
	if ( DeviceLocation )
	{
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "sceUsbdGetDeviceLocation", DeviceLocation);
		return NULL;
	}
	for ( i = 0; i < g_usbkb_cfg_keybd; i += 1 )
	{
		for ( j = 0; j < (int)sizeof(devloc_stk) && g_usbkb_devloc_buf[i][j] == devloc_stk[j]; j += 1 );
		if ( j == (int)sizeof(devloc_stk) )
			break;
	}
	if ( i == g_usbkb_cfg_keybd )
	{
		for ( i = 0; i < g_usbkb_cfg_keybd && g_usbkb_unit_buf[i]; i += 1 );
		if ( i >= g_usbkb_cfg_keybd )
		{
			printf("logical error\n");
			return NULL;
		}
	}
	unit->number = i;
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
static void usbkb_donecb_SetConfiguration(int retres, int count, void *arg)
{
	ps2kbd_unit *unit;
	int xferret; // $v0

	(void)count;

	unit = (ps2kbd_unit *)arg;
	if ( retres )
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "sceUsbdSetConfiguration", retres);
	if ( unit->as <= 0 )
	{
		usbkb_set_idle_request(unit);
		return;
	}
	xferret = sceUsbdSetInterface(unit->c_pipe, unit->ifnum, unit->as, &usbkb_donecb_SetInterface, unit);
	if ( xferret )
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "sceUsbdSetInterface", xferret);
}

//----- (0040152C) --------------------------------------------------------
static void usbkb_donecb_SetInterface(int retres, int count, void *arg)
{
	ps2kbd_unit *unit;

	(void)count;

	unit = (ps2kbd_unit *)arg;
	if ( retres )
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "sceUsbdSetInterface", retres);
	usbkb_set_idle_request(unit);
}

//----- (00401574) --------------------------------------------------------
static void usbkb_set_idle_request(ps2kbd_unit *unit)
{
	int xferret; // $v0

	xferret = sceUsbdControlTransfer(unit->c_pipe, 0x21, USB_REQ_SET_IDLE, 0, unit->ifnum, 0, NULL, &usbkb_donecb_set_idle_request, unit);
	if ( xferret )
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "set_idle_request", xferret);
}

//----- (004015FC) --------------------------------------------------------
static void usbkb_donecb_set_idle_request(int retres, int count, void *arg)
{
	ps2kbd_unit *unit;

	(void)count;

	unit = (ps2kbd_unit *)arg;
	if ( retres )
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "set_idle_request_done", retres);
	usbkb_data_transfer(unit);
}

//----- (00401644) --------------------------------------------------------
static void usbkb_data_transfer(ps2kbd_unit *unit)
{
	int xferret; // $v0

	xferret = sceUsbdTransferPipe(unit->d_pipe, unit->data, unit->payload, NULL, &usbkb_donecb_data_transfer, unit);
	if ( xferret )
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "sceUsbdInterruptTransfer", xferret);
}

//----- (004016AC) --------------------------------------------------------
static void usbkb_donecb_data_transfer(int retres, int count, void *arg)
{
	ps2kbd_unit *unit;
	int ledmask; // $s1
	int i; // $s0
	int state; // [sp+20h] [-8h] BYREF

	unit = (ps2kbd_unit *)arg;
	ledmask = 0;
	if ( retres )
	{
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "data_transfer_done:sceUsbdInterruptTransfer", retres);
		usbkb_data_transfer(unit);
		return;
	}
	if ( g_usbkb_cfg_debug > 0 )
	{
		unit->count += 1;
		printf("usbkeybd%d: count=%d led=%02X data=(", unit->number, unit->count, unit->ledptn);
		for ( i = 0; i < count; i += 1 )
			printf(" %02x", unit->data[i]);
		printf(" )\n");
	}
	for ( i = 2; i < count; i += 1 )
	{
		switch ( unit->data[i] )
		{
			case 0x39:
				if ( unit->old_ledbtn2 == 1 || (unit->old_ledbtn2 == 2 && (unit->data[0] & 0x22) != 0))
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
	if ( unit->old_ledbtn == ledmask || !unit->old_ledbtn2 )
		usbkb_data_transfer(unit);
	else
	{
		int xferret; // $v0

		unit->old_ledbtn = ledmask;
		unit->ledptn ^= ledmask;
		xferret = sceUsbdControlTransfer(unit->c_pipe, 0x21, USB_REQ_SET_REPORT, 512, unit->ifnum, sizeof(unit->ledptn), &unit->ledptn, &usbkb_donecb_led_transfer, unit);
		if ( xferret )
			printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "SET_REPORT", xferret);
	}
	CpuSuspendIntr(&state);
	unit->ringbuf[unit->wp][0] = unit->ledptn;
	unit->ringbuf[unit->wp][1] = count;
	for ( i = 0; i < count; i += 1 )
		unit->ringbuf[i][2] = unit->data[i];
	unit->wp += 1;
	if ( unit->wp >= 3 )
		unit->wp = 0;
	if ( unit->rblen >= 3 )
	{
		unit->rp += 1;
		if ( unit->rp >= 3 )
			unit->rp = 0;
	}
	else
		unit->rblen += 1;
	CpuResumeIntr(state);
}
// 4020F0: using guessed type int g_usbkb_cfg_debug;

//----- (004019D8) --------------------------------------------------------
static void usbkb_donecb_led_transfer(int retres, int count, void *arg)
{
	ps2kbd_unit *unit;

	(void)count;

	unit = (ps2kbd_unit *)arg;
	if ( retres )
		printf("usbkeybd%d: %s -> 0x%x\n", unit->number, "led_transfer_done", retres);
	usbkb_data_transfer(unit);
}

//----- (00401A20) --------------------------------------------------------
static int usbkb_drv_disconnect(int devID)
{
	ps2kbd_unit *unit; // $s0

	unit = sceUsbdGetPrivateData(devID);
	if ( !unit )
		return -1;
	g_usbkb_used_kb_count -= 1;
	g_usbkb_unit_buf[unit->number] = NULL;
	if ( g_usbkb_cfg_debug > 0 )
		printf("usbkeybd%d: detached\n", unit->number);
	FreeSysMemory(unit);
	return 0;
}
// 402080: using guessed type int g_usbkb_used_kb_count;
// 4020F0: using guessed type int g_usbkb_cfg_debug;
