
#include "irx_imports.h"
#include "usbdpriv.h"

IRX_ID(MODNAME, 2, 4);

UsbdUsbHub_t *allocHubBuffer(void);
void freeHubBuffer(UsbdUsbHub_t *hub);
UsbdDevice_t *fetchPortElemByNumber(UsbdDevice_t *hub, int port);
void getHubStatusChange(UsbdUsbHub_t *dev);
void hubControlTransfer(
	UsbdUsbHub_t *hubDev,
	u8 requestType,
	u8 request,
	u16 value,
	u16 index,
	u16 length,
	void *destData,
	void *callback,
	const char *fromfunc);
void hubGetPortStatusCallback(UsbdIoRequest_t *req);
void hubDeviceResetCallback(UsbdIoRequest_t *arg);
void hubResetDevicePort(UsbdDevice_t *dev);
void hubCalculateMagicPowerValue(UsbdUsbHub_t *hubDevice);
void hubGetHubStatusCallback(UsbdIoRequest_t *req);
void hubStatusChangeCallback(UsbdIoRequest_t *req);
void hubSetPortPower(UsbdIoRequest_t *req);
void hubSetupPorts(UsbdIoRequest_t *req);
void hubCheckPorts(UsbdIoRequest_t *req);
void hubCheckPortsCB(UsbdIoRequest_t *req);
void hubCheckDeviceDesc(UsbdIoRequest_t *req);
int hubDrvConnect(int devId);
int hubDrvDisconnect(int devId);
int hubDrvProbe(int devId);
int initHubDriver(void);
void deinitHubDriver(void);
UsbdDevice_t *fetchDeviceById(int devId);
UsbdEndpoint_t *fetchEndpointById(int id);
UsbdDevice_t *getDeviceTreeRoot(void);
UsbdDevice_t *attachChildDevice(UsbdDevice_t *parent, u32 portNum);
void freeDevice(UsbdDevice_t *dev);
UsbdIoRequest_t *allocIoRequest(void);
void freeIoRequest(UsbdIoRequest_t *req);
UsbdEndpoint_t *allocEndpointForDevice(UsbdDevice_t *dev, u32 align);
int cleanUpFunc(UsbdDevice_t *dev, UsbdEndpoint_t *ep);
UsbdHcTD_t *allocTd(void);
void freeTd(UsbdHcTD_t *argTd);
UsbdHcIsoTD_t *allocIsoTd(void);
void freeIsoTd(UsbdHcIsoTD_t *argTd);
int addTimerCallback(UsbdTimerCbStruct_t *arg, TimerCallback func, void *cbArg, int delay);
int cancelTimerCallback(UsbdTimerCbStruct_t *arg);
void handleTimerList(void);
void addToHcEndpointList(u8 type, UsbdHcED_t *ed);
void removeHcEdFromList(int type, const UsbdHcED_t *hcEd);
int setupBandwidthInterruptScheduling(UsbdEndpoint_t *ep, const UsbEndpointDescriptor *endpDesc, int isLowSpeedDevice);
void removeEndpointFromQueue(const UsbdEndpoint_t *ep, int isLowSpeedDevice);
UsbdEndpoint_t *openDeviceEndpoint(UsbdDevice_t *dev, const UsbEndpointDescriptor *endpDesc, u32 alignFlag);
void killEndpoint(UsbdEndpoint_t *ep);
int removeEndpointFromDevice(UsbdDevice_t *dev, UsbdEndpoint_t *ep);
int setupControlTransfer(UsbdEndpoint_t *ep);
int setupIsocronTransfer(UsbdEndpoint_t *ep);
int setupBulkTransfer(UsbdEndpoint_t *ep);
void handleIoReqList(UsbdEndpoint_t *ep);
void usbdRebootInner(void);
void hubResetDevice(UsbdDevice_t *dev);
int checkDelayedResetsTree(UsbdDevice_t *tree);
int checkDelayedResets(UsbdDevice_t *dev);
void handleRhsc(void);
void checkGenTdQueue(void);
void processDoneQueue_GenTd(UsbdHcTD_t *arg);
void checkIsoTdQueue(void);
void processDoneQueue_IsoTd(UsbdHcIsoTD_t *arg);
void hcdProcessIntr(void);
static void PostIntrEnableFunction(void);
int initHardware(volatile OhciRegs *ohciRegs);
int initHcdStructs(void);
void deinitHcd(void);
void *AllocSysMemoryWrap(int size);
int FreeSysMemoryWrap(void *ptr);
int usbdLock(void);
int usbdUnlock(void);
void signalCallbackThreadFunc(UsbdIoRequest_t *req);
int usbdTransferPipeImpl(
	void *gp_val,
	int id,
	void *data,
	u32 length,
	UsbDeviceRequest *option,
	void *callback,
	void *cbArg,
	sceUsbdMultiIsochronousRequest *request);
int usbdIntrHandler(void *arg);
void hcdIrqThread(void *arg);
void callbackThreadFunc(void *arg);
void usbdReboot(int ac);
static void ParseOptionInput(const UsbdArgOption_t *option, const char *arguments);
int usbdModuleUnload(void);
int handleStaticDeviceDescriptor(UsbdDevice_t *dev, UsbDeviceDescriptor *devDescStart, UsbDeviceDescriptor *devDescEnd);
int callUsbDriverFunc(int (*func)(int devId), int devId, void *gpSeg);
void probeDeviceTree(UsbdDevice_t *tree, sceUsbdLddOps *drv);
int doRegisterDriver(sceUsbdLddOps *drv, void *drvGpSeg);
int doRegisterAutoLoader(sceUsbdLddOps *drv, void *drvGpSeg);
void disconnectDriver(UsbdDevice_t *tree, sceUsbdLddOps *drv);
int doUnregisterDriver(sceUsbdLddOps *drv);
int doUnregisterAutoLoader(void);
void *doGetDeviceStaticDescriptor(int devId, void *data, u8 type);
int doGetDeviceLocation(UsbdDevice_t *dev, u8 *path);
UsbdEndpoint_t *doOpenEndpoint(UsbdDevice_t *dev, const UsbEndpointDescriptor *endpDesc, u32 alignFlag);
int doCloseEndpoint(UsbdEndpoint_t *ep);
int attachIoReqToEndpoint(UsbdEndpoint_t *ep, UsbdIoRequest_t *req, void *destdata, u16 length, void *callback);
int doControlTransfer(
	UsbdEndpoint_t *ep,
	UsbdIoRequest_t *req,
	u8 requestType,
	u8 request,
	u16 value,
	u16 index,
	u16 length,
	void *destdata,
	void *callback);
void connectNewDevice(UsbdDevice_t *dev);
void fetchNextReportDescriptorCB(UsbdIoRequest_t *req);
void fetchNextReportDescriptor(UsbdIoRequest_t *req);
void killDevice(UsbdDevice_t *dev, UsbdEndpoint_t *ep);
void fetchConfigDescriptors(UsbdIoRequest_t *req);
void requestDeviceDescrptorCB(UsbdIoRequest_t *req);
void requestDeviceDescriptor(UsbdIoRequest_t *req);
void hubPeekDeviceDescriptor(UsbdIoRequest_t *req);
void hubSetFuncAddressCB(UsbdIoRequest_t *req);
void hubSetFuncAddress(UsbdEndpoint_t *ep);
int hubTimedSetFuncAddress(UsbdDevice_t *dev);
void flushPort(UsbdDevice_t *dev);
int usbdInitInner(void);

extern struct irx_export_table _exp_usbd;
static UsbdUsbHub_t *hubBufferList = NULL;
static void *hubBufferListMemoryBuffer = NULL;
static int hubAllocatedCount = 0;
sceUsbdLddOps usbHubDriver = {
	NULL,
	NULL,
	"hub",
	&hubDrvProbe,
	&hubDrvConnect,
	&hubDrvDisconnect,
	0u,
	0u,
	0u,
	0u,
	0u,
	NULL,
};
UsbdMemoryPool_t *memPool = NULL;
UsbdKernelResources_t usbKernelResources = {-1, -1, -1, -1, -1};
UsbdIoRequest_t *cbListStart = NULL;
UsbdIoRequest_t *cbListEnd = NULL;
#ifndef MINI_DRIVER
UsbdConfig_t usbConfig = {
	0x20,
	0x40,
	0x80,
	0x80,
	0x100,
	0x200,
	0x8,
	0x8,
	0x0,
	0x1E,
	0x24,
	0x0,
};
#else
UsbdConfig_t usbConfig = {
	0x10,
	0x20,
	0x40,
	0x40,
	0x100,
	0x200,
	0x4,
	0x4,
	0x0,
	0x1E,
	0x24,
	0x0,
};
#endif
static UsbdArgOption_t SupportedArgs[] = {
	{"dev=", &usbConfig.m_maxDevices, NULL},
	{"ed=", &usbConfig.m_maxEndpoints, NULL},
	{"gtd=", &usbConfig.m_maxTransfDesc, NULL},
	{"itd=", &usbConfig.m_maxIsoTransfDesc, NULL},
	{"ioreq=", &usbConfig.m_maxIoReqs, NULL},
	{"conf=", &usbConfig.m_maxStaticDescSize, NULL},
	{"hub=", &usbConfig.m_maxHubDevices, NULL},
	{"port=", &usbConfig.m_maxPortsPerHub, NULL},
	{"thpri=", &usbConfig.m_hcdThreadPrio, &usbConfig.m_cbThreadPrio},
	{"reportd=", &usbConfig.m_curDescNum, NULL},
	{NULL, NULL, NULL}};
UsbdMemoryPool_t *memPool_unused = NULL;
sceUsbdLddOps *drvListStart = NULL;
sceUsbdLddOps *drvListEnd = NULL;
sceUsbdLddOps *drvAutoLoader = NULL;
static const char *usbdVersionString = "Version 1.6.0";
void *hcdMemoryBuffer;

// hub.c

UsbdUsbHub_t *allocHubBuffer(void)
{
	UsbdUsbHub_t *res;

	if ( !hubBufferList )
	{
		return NULL;
	}
	res = hubBufferList;
	hubBufferList = hubBufferList->m_next;
	res->m_desc.bDescriptorType = 0;
	res->m_statusIoReq.m_busyFlag = 0;
	res->m_controlIoReq.m_busyFlag = 0;
	res->m_curAllocatedCount = hubAllocatedCount;
	hubAllocatedCount += 1;
	return res;
}

void freeHubBuffer(UsbdUsbHub_t *hub)
{
	hub->m_next = hubBufferList;
	hubBufferList = hub;
}

UsbdDevice_t *fetchPortElemByNumber(UsbdDevice_t *hub, int port)
{
	UsbdDevice_t *res;

	for ( res = hub->m_childListStart; res && port > 0; port -= 1, res = res->m_next )
	{
	}
	return res;
}

void getHubStatusChange(UsbdUsbHub_t *dev)
{
	if ( dev->m_statusIoReq.m_busyFlag )
	{
		dbg_printf("getHubStatusChange: StatusChangeEP IoReq is busy!\n");
		return;
	}
	attachIoReqToEndpoint(
		dev->m_statusChangeEp,
		&dev->m_statusIoReq,
		dev->m_statusChangeInfo,
		(int)(dev->m_numChildDevices + 7) >> 3,
		hubStatusChangeCallback);
}

void hubControlTransfer(
	UsbdUsbHub_t *hubDev,
	u8 requestType,
	u8 request,
	u16 value,
	u16 index,
	u16 length,
	void *destData,
	void *callback,
	const char *fromfunc)
{
	if ( hubDev->m_controlIoReq.m_busyFlag )
	{
		dbg_printf("ERROR: hubControlTransfer %p: ioReq busy\n", hubDev);
		printf("hub_control_transfer: busy - %s\n", fromfunc);
	}
	else
		doControlTransfer(
			hubDev->m_controlEp, &hubDev->m_controlIoReq, requestType, request, value, index, length, destData, callback);
}

void hubGetPortStatusCallback(UsbdIoRequest_t *req)
{
	UsbdUsbHub_t *dev;
	int feature;
	UsbdDevice_t *port;

	dev = (UsbdUsbHub_t *)req->m_userCallbackArg;
	feature = -1;
	if ( req->m_resultCode != USB_RC_OK )
	{
		dbg_printf("HubGetPortStatusCallback res %d\n", req->m_resultCode);
		return;
	}
	dbg_printf("port status change: %d: %08X\n", dev->m_portCounter, dev->m_portStatusChange);
	if ( (dev->m_portStatusChange & BIT(C_PORT_CONNECTION)) != 0 )
	{
		port = fetchPortElemByNumber(dev->m_controlEp->m_correspDevice, dev->m_portCounter);
		if ( !port )
		{
			hubStatusChangeCallback(&dev->m_statusIoReq);
			return;
		}
		if ( port->m_deviceStatus >= (unsigned int)DEVICE_CONNECTED )
		{
			flushPort(port);
		}
		feature = C_PORT_CONNECTION;
	}
	else if ( (dev->m_portStatusChange & BIT(C_PORT_ENABLE)) != 0 )
	{
		feature = C_PORT_ENABLE;
	}
	else if ( (dev->m_portStatusChange & BIT(C_PORT_SUSPEND)) != 0 )
	{
		feature = C_PORT_SUSPEND;
	}
	else if ( (dev->m_portStatusChange & BIT(C_PORT_OVER_CURRENT)) != 0 )
	{
		feature = C_PORT_OVER_CURRENT;
	}
	else if ( (dev->m_portStatusChange & BIT(C_PORT_RESET)) != 0 )
	{
		feature = C_PORT_RESET;
	}
	if ( feature >= 0 )
	{
		dev->m_portStatusChange &= ~BIT(feature);
		hubControlTransfer(
			dev,
			USB_DIR_OUT | USB_RT_PORT,
			USB_REQ_CLEAR_FEATURE,
			feature & 0xFFFF,
			dev->m_portCounter & 0xFFFF,
			0,
			NULL,
			hubGetPortStatusCallback,
			"clear_port_feature");
		return;
	}
	port = fetchPortElemByNumber(dev->m_controlEp->m_correspDevice, dev->m_portCounter);
	if ( !port )
	{
		hubStatusChangeCallback(&dev->m_statusIoReq);
		return;
	}
	if ( (dev->m_portStatusChange & BIT(PORT_CONNECTION)) != 0 )
	{
		dbg_printf("Hub Port CCS\n");
		if ( port->m_deviceStatus == DEVICE_NOTCONNECTED )
		{
			dbg_printf("resetting dev\n");
			port->m_deviceStatus = DEVICE_CONNECTED;
			addTimerCallback(&port->m_timer, (TimerCallback)hubResetDevice, port, 501);
			return;
		}
		if ( port->m_deviceStatus == DEVICE_RESETPENDING && (dev->m_portStatusChange & BIT(PORT_ENABLE)) != 0 )
		{
			dbg_printf("hub port reset done, opening control EP\n");
			port->m_deviceStatus = DEVICE_RESETCOMPLETE;
			port->m_isLowSpeedDevice = (dev->m_portStatusChange & BIT(PORT_LOW_SPEED)) != 0;
			if ( openDeviceEndpoint(port, NULL, 0) )
				hubTimedSetFuncAddress(port);
			else
				dbg_printf("Can't open default control ep.\n");
			dev->m_hubStatusCounter = 0;
		}
	}
	else
	{
		dbg_printf("disconnected; flushing port\n");
		flushPort(port);
	}
}

void hubDeviceResetCallback(UsbdIoRequest_t *arg)
{
	if ( arg->m_resultCode != USB_RC_OK )
	{
		dbg_printf("port reset err: %d\n", arg->m_resultCode);
		return;
	}
	getHubStatusChange((UsbdUsbHub_t *)arg->m_userCallbackArg);
}

void hubResetDevicePort(UsbdDevice_t *dev)
{
	UsbdUsbHub_t *privDataField;

	privDataField = (UsbdUsbHub_t *)dev->m_parent->m_privDataField;
	privDataField->m_hubStatusCounter = dev->m_attachedToPortNo;
	hubControlTransfer(
		privDataField,
		USB_DIR_OUT | USB_RT_PORT,
		USB_REQ_SET_FEATURE,
		PORT_RESET,
		dev->m_attachedToPortNo,
		0,
		NULL,
		hubDeviceResetCallback,
		"hub_port_reset");
}

void hubCalculateMagicPowerValue(UsbdUsbHub_t *hubDevice)
{
	UsbdDevice_t *dev;

	dev = hubDevice->m_dev;
	if ( (int)dev->m_magicPowerValue )
	{
		if ( (int)dev->m_magicPowerValue >= 0 && (int)dev->m_magicPowerValue < 6 && (int)dev->m_magicPowerValue >= 3 )
		{
			if ( (hubDevice->m_hubStatus & 1) != 0 )
				dev->m_magicPowerValue = 4;
			else
				dev->m_magicPowerValue = 5;
		}
	}
	else if ( hubDevice->m_isSelfPowered )
	{
		if ( (int)hubDevice->m_maxPower <= 0 )
			dev->m_magicPowerValue = 2;
		else
			dev->m_magicPowerValue = 3;
	}
	else
	{
		dev->m_magicPowerValue = (int)hubDevice->m_maxPower > 0;
	}
}

void hubGetHubStatusCallback(UsbdIoRequest_t *req)
{
	UsbdUsbHub_t *dev;

	dev = (UsbdUsbHub_t *)req->m_userCallbackArg;
	if ( req->m_resultCode != USB_RC_OK )
	{
		return;
	}
	if ( (dev->m_hubStatusChange & BIT(C_HUB_LOCAL_POWER)) != 0 )
	{
		dev->m_hubStatusChange &= ~BIT(C_HUB_LOCAL_POWER);
		hubControlTransfer(
			dev,
			USB_DIR_OUT | USB_RT_HUB,
			USB_REQ_CLEAR_FEATURE,
			C_HUB_LOCAL_POWER,
			0,
			0,
			NULL,
			hubGetHubStatusCallback,
			"clear_hub_feature");
		hubCalculateMagicPowerValue(dev);
	}
	else if ( (dev->m_hubStatusChange & BIT(C_HUB_OVER_CURRENT)) != 0 )
	{
		dev->m_hubStatusChange &= ~BIT(C_HUB_OVER_CURRENT);
		hubControlTransfer(
			dev,
			USB_DIR_OUT | USB_RT_HUB,
			USB_REQ_CLEAR_FEATURE,
			C_HUB_OVER_CURRENT,
			0,
			0,
			NULL,
			hubGetHubStatusCallback,
			"clear_hub_feature");
	}
	else
	{
		hubStatusChangeCallback(&dev->m_statusIoReq);
	}
}

void hubStatusChangeCallback(UsbdIoRequest_t *req)
{
	UsbdUsbHub_t *dev;
	int port;

	dev = (UsbdUsbHub_t *)req->m_userCallbackArg;
	if ( req->m_resultCode != USB_RC_OK )
	{
		dbg_printf("hubStatusChangeCallback, iores %d\n", req->m_resultCode);
		return;
	}
	if ( (dev->m_statusChangeInfo[0] & 1) != 0 )
	{
		dev->m_statusChangeInfo[0] &= ~1;
		hubControlTransfer(
			dev,
			USB_DIR_IN | USB_RT_HUB,
			USB_REQ_GET_STATUS,
			0,
			0,
			4u,
			&dev->m_hubStatus,
			hubGetHubStatusCallback,
			"scan_change_bitmap");
		return;
	}
	port = dev->m_hubStatusCounter;
	if ( port <= 0 )
	{
		port = 1;
		if ( (int)dev->m_numChildDevices <= 0 )
		{
			getHubStatusChange(dev);
			return;
		}
		while ( (((int)dev->m_statusChangeInfo[port >> 3] >> (port & 7)) & 1) == 0 )
		{
			port += 1;
			if ( (int)dev->m_numChildDevices < port )
			{
				getHubStatusChange(dev);
				return;
			}
		}
	}
	else if ( (((int)dev->m_statusChangeInfo[port >> 3] >> (port & 7)) & 1) == 0 )
	{
		getHubStatusChange(dev);
		return;
	}
	dev->m_statusChangeInfo[port >> 3] &= ~BIT(port & 7);
	dev->m_portCounter = port;
	hubControlTransfer(
		dev,
		USB_DIR_IN | USB_RT_PORT,
		USB_REQ_GET_STATUS,
		0,
		dev->m_portCounter,
		4u,
		&dev->m_portStatusChange,
		hubGetPortStatusCallback,
		"scan_change_bitmap");
}

void hubSetPortPower(UsbdIoRequest_t *req)
{
	UsbdUsbHub_t *dev;

	dev = (UsbdUsbHub_t *)req->m_userCallbackArg;
	// there is no result to check if this is the first call for this hub
	if ( (int)dev->m_portCounter > 0 && req->m_resultCode != USB_RC_OK )
	{
		return;
	}
	dev->m_portCounter += 1;
	if ( ((int)dev->m_numChildDevices < (int)dev->m_portCounter) || usbConfig.m_maxPortsPerHub < (int)dev->m_portCounter )
		getHubStatusChange(dev);
	else
		hubControlTransfer(
			dev,
			USB_DIR_OUT | USB_RT_PORT,
			USB_REQ_SET_FEATURE,
			PORT_POWER,
			dev->m_portCounter,
			0,
			NULL,
			hubSetPortPower,
			"set_port_power");
}

void hubSetupPorts(UsbdIoRequest_t *req)
{
	UsbdUsbHub_t *dev;
	u32 i;

	dev = (UsbdUsbHub_t *)req->m_userCallbackArg;
	if ( req->m_resultCode != USB_RC_OK )
	{
		return;
	}
	hubCalculateMagicPowerValue(dev);

	dev->m_hubStatusCounter = 0;
	dev->m_portCounter = 0;
	dev->m_numChildDevices = dev->m_desc.bNbrPorts;
	for ( i = 0; (int)i < (int)dev->m_numChildDevices && (int)i < usbConfig.m_maxPortsPerHub; i += 1 )
	{
		if ( !attachChildDevice(dev->m_controlEp->m_correspDevice, i + 1) )
		{
			dev->m_numChildDevices = i;
			break;
		}
	}
	if ( (int)dev->m_numChildDevices > 0 )
		hubSetPortPower(req);
}

void hubCheckPorts(UsbdIoRequest_t *req)
{
	UsbdUsbHub_t *dev;

	dev = (UsbdUsbHub_t *)req->m_userCallbackArg;
	hubControlTransfer(
		dev, USB_DIR_IN | USB_RT_HUB, USB_REQ_GET_STATUS, 0, 0, 4u, &dev->m_hubStatus, hubSetupPorts, "get_hub_status");
}

void hubCheckPortsCB(UsbdIoRequest_t *req)
{
	if ( req->m_resultCode != USB_RC_OK )
		return;
	hubCheckPorts(req);
}

void hubCheckDeviceDesc(UsbdIoRequest_t *req)
{
	UsbdUsbHub_t *dev;

	dev = (UsbdUsbHub_t *)req->m_userCallbackArg;
	if ( req->m_resultCode != USB_RC_OK )
	{
		return;
	}
	if ( dev->m_desc.bDescriptorType == USB_DT_HUB )
		hubCheckPorts(req);  // we've got the descriptor already
	else
		hubControlTransfer(
			dev,
			USB_DIR_IN | USB_RT_HUB,
			USB_REQ_GET_DESCRIPTOR,
			USB_DT_HUB << 8,
			0,
			sizeof(UsbHubDescriptor),
			&dev->m_desc,
			hubCheckPortsCB,
			"set_configuration_done");
}

// TODO: sizeof UsbHubDescriptor.deviceRemovable length set 32

int hubDrvConnect(int devId)
{
	UsbdDevice_t *dev;
	UsbConfigDescriptor *confDesc;
	UsbInterfaceDescriptor *intfDesc;
	UsbEndpointDescriptor *endpDesc;
	UsbdUsbHub_t *hubDevice;
	const UsbHubDescriptor *hubDesc;

	dev = fetchDeviceById(devId);
	if ( !dev )
		return -1;
	confDesc = (UsbConfigDescriptor *)doGetDeviceStaticDescriptor(devId, NULL, USB_DT_CONFIG);
	if ( !confDesc || confDesc->bNumInterfaces != 1 )
		return -1;
	intfDesc = (UsbInterfaceDescriptor *)doGetDeviceStaticDescriptor(devId, confDesc, USB_DT_INTERFACE);
	if ( !intfDesc )
	{
		return -1;
	}
	if ( intfDesc->bNumEndpoints != 1 )
	{
		return -1;
	}
	endpDesc = (UsbEndpointDescriptor *)doGetDeviceStaticDescriptor(devId, intfDesc, USB_DT_ENDPOINT);
	if ( !endpDesc )
	{
		return -1;
	}
	if ( (endpDesc->bEndpointAddress & USB_ENDPOINT_DIR_MASK) != USB_DIR_IN )
		return -1;
	if ( (endpDesc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) != USB_ENDPOINT_XFER_INT )
		return -1;
	hubDesc = (UsbHubDescriptor *)doGetDeviceStaticDescriptor(devId, endpDesc, USB_DT_HUB);
	hubDevice = allocHubBuffer();
	if ( !hubDevice )
		return -1;
	dev->m_privDataField = hubDevice;
	hubDevice->m_dev = dev;
	hubDevice->m_controlEp = dev->m_endpointListStart;
	hubDevice->m_statusChangeEp = doOpenEndpoint(dev, endpDesc, 0);
	if ( !hubDevice->m_statusChangeEp )
	{
		freeHubBuffer(hubDevice);
		return -1;
	}
	hubDevice->m_statusIoReq.m_userCallbackArg = hubDevice;
	hubDevice->m_controlIoReq.m_userCallbackArg = hubDevice;
	hubDevice->m_maxPower = confDesc->maxPower;
	hubDevice->m_isSelfPowered = (confDesc->bmAttributes >> 6) & 1;
	hubCalculateMagicPowerValue(hubDevice);
	if ( hubDesc )
	{
		bcopy(
			hubDesc,
			&hubDevice->m_desc,
			(hubDesc->bLength < sizeof(UsbHubDescriptor)) ? hubDesc->bLength : sizeof(UsbHubDescriptor));
	}
	hubControlTransfer(
		hubDevice,
		USB_DIR_OUT | USB_RECIP_DEVICE,
		USB_REQ_SET_CONFIGURATION,
		confDesc->bConfigurationValue,
		0,
		0,
		NULL,
		hubCheckDeviceDesc,
		"hub_attach");
	return 0;
}

int hubDrvDisconnect(int devId)
{
	UsbdDevice_t *dev;

	dev = fetchDeviceById(devId);
	if ( !dev )
		return -1;
	freeHubBuffer((UsbdUsbHub_t *)dev->m_privDataField);
	return 0;
}

int hubDrvProbe(int devId)
{
	const UsbDeviceDescriptor *devDesc;

	devDesc = (const UsbDeviceDescriptor *)doGetDeviceStaticDescriptor(devId, NULL, USB_DT_DEVICE);
	return devDesc && devDesc->bDeviceClass == USB_CLASS_HUB && devDesc->bNumConfigurations == 1;
}

int initHubDriver(void)
{
	int needMem;
	UsbdUsbHub_t *hub;
	int i;

	needMem = usbConfig.m_maxHubDevices * sizeof(UsbdUsbHub_t);
	hubBufferList = (UsbdUsbHub_t *)AllocSysMemoryWrap(needMem);
	if ( !hubBufferList )
	{
		dbg_printf("ERROR: unable to alloc hub buffer\n");
		return -1;
	}
	hub = hubBufferList;
	hubBufferListMemoryBuffer = hub;
	bzero(hubBufferList, needMem);
	usbConfig.m_allocatedSize_unused += needMem;
	for ( i = 0; i < usbConfig.m_maxHubDevices; i += 1 )
	{
		hub[i].m_next = (i < usbConfig.m_maxHubDevices - 1) ? &hub[i + 1] : NULL;
	}
	doRegisterDriver(&usbHubDriver, GetGP());
	return 0;
}

void deinitHubDriver(void)
{
	doUnregisterDriver(&usbHubDriver);
	FreeSysMemoryWrap(hubBufferListMemoryBuffer);
}

// mem.c

UsbdDevice_t *fetchDeviceById(int devId)
{
	UsbdDevice_t *dev;

	if ( devId <= 0 )
	{
		return NULL;
	}
	if ( devId >= usbConfig.m_maxDevices )
	{
		return NULL;
	}
	dev = &memPool->m_deviceTreeBuf[devId];
	if ( !dev->m_parent )
		return NULL;
	return dev;
}

UsbdEndpoint_t *fetchEndpointById(int id)
{
	UsbdEndpoint_t *ep;

	if ( id < 0 )
	{
		return NULL;
	}
	if ( id >= usbConfig.m_maxEndpoints )
	{
		return NULL;
	}
	ep = &memPool->m_endpointBuf[id];
	if ( !ep->m_correspDevice )
		return NULL;
	return ep;
}

UsbdDevice_t *getDeviceTreeRoot(void)
{
	return memPool->m_deviceTreeRoot;
}

UsbdDevice_t *attachChildDevice(UsbdDevice_t *parent, u32 portNum)
{
	UsbdDevice_t *newDev;

	newDev = memPool->m_freeDeviceListStart;
	if ( !newDev )
	{
		dbg_printf("Ran out of device handles\n");
		return NULL;
	}
	if ( newDev->m_next )
		newDev->m_next->m_prev = newDev->m_prev;
	else
		memPool->m_freeDeviceListEnd = newDev->m_prev;
	if ( newDev->m_prev )
		newDev->m_prev->m_next = newDev->m_next;
	else
		memPool->m_freeDeviceListStart = newDev->m_next;
	newDev->m_endpointListEnd = NULL;
	newDev->m_endpointListStart = NULL;
	newDev->m_devDriver = NULL;
	newDev->m_deviceStatus = DEVICE_NOTCONNECTED;
	newDev->m_resetFlag = 0;
	newDev->m_magicPowerValue = 0;
	newDev->m_childListEnd = NULL;
	newDev->m_childListStart = NULL;
	newDev->m_parent = parent;
	newDev->m_attachedToPortNo = portNum;
	newDev->m_privDataField = NULL;
	if ( parent )
	{
		newDev->m_prev = parent->m_childListEnd;
		if ( parent->m_childListEnd )
			parent->m_childListEnd->m_next = newDev;
		else
			parent->m_childListStart = newDev;
		newDev->m_next = NULL;
		parent->m_childListEnd = newDev;
	}
	return newDev;
}

void freeDevice(UsbdDevice_t *dev)
{
	if ( !dev || dev < memPool->m_deviceTreeBuf || dev >= memPool->m_deviceTreeBuf + usbConfig.m_maxDevices )
	{
		dbg_printf("freeDevice %p: Arg is not part of dev buffer\n", dev);
		return;
	}
	dev->m_prev = memPool->m_freeDeviceListEnd;
	if ( memPool->m_freeDeviceListEnd )
		memPool->m_freeDeviceListEnd->m_next = dev;
	else
		memPool->m_freeDeviceListStart = dev;
	dev->m_next = NULL;
	memPool->m_freeDeviceListEnd = dev;
	dev->m_parent = NULL;
}

UsbdIoRequest_t *allocIoRequest(void)
{
	UsbdIoRequest_t *res;

	res = memPool->m_freeIoReqList;
	if ( !res )
	{
		dbg_printf("ran out of IoReqs\n");
		return NULL;
	}
	if ( res->m_next )
		res->m_next->m_prev = res->m_prev;
	else
		memPool->m_freeIoReqListEnd = res->m_prev;
	if ( res->m_prev )
		res->m_prev->m_next = res->m_next;
	else
		memPool->m_freeIoReqList = res->m_next;
	return res;
}

void freeIoRequest(UsbdIoRequest_t *req)
{
	UsbdIoRequest_t *pos;

	if ( !req )
	{
		return;
	}
	if ( req < memPool->m_ioReqBufPtr || req >= memPool->m_ioReqBufPtr + usbConfig.m_maxIoReqs )
	{
		req->m_busyFlag = 0;
		return;
	}
	for ( pos = memPool->m_freeIoReqList; pos && pos != req; pos = pos->m_next )
	{
	}
	if ( pos )
	{
		dbg_printf("freeIoRequest %p: already free.\n", req);
		return;
	}
	req->m_busyFlag = 0;
	req->m_prev = memPool->m_freeIoReqListEnd;
	if ( memPool->m_freeIoReqListEnd )
		memPool->m_freeIoReqListEnd->m_next = req;
	else
		memPool->m_freeIoReqList = req;
	req->m_next = NULL;
	memPool->m_freeIoReqListEnd = req;
}

UsbdEndpoint_t *allocEndpointForDevice(UsbdDevice_t *dev, u32 align)
{
	UsbdEndpoint_t *newEp;

	newEp = memPool->m_freeEpListStart;
	if ( !newEp )
	{
		return NULL;
	}
	if ( newEp->m_next )
		newEp->m_next->m_prev = newEp->m_prev;
	else
		memPool->m_freeEpListEnd = newEp->m_prev;
	if ( newEp->m_prev )
		newEp->m_prev->m_next = newEp->m_next;
	else
		memPool->m_freeEpListStart = newEp->m_next;
	newEp->m_correspDevice = dev;
	newEp->m_ioReqListEnd = NULL;
	newEp->m_ioReqListStart = NULL;
	newEp->m_busyPrev = NULL;
	newEp->m_busyNext = NULL;
	newEp->m_inTdQueue = 0;
	newEp->m_alignFlag = align;
	newEp->m_prev = dev->m_endpointListEnd;
	if ( dev->m_endpointListEnd )
		dev->m_endpointListEnd->m_next = newEp;
	else
		dev->m_endpointListStart = newEp;
	newEp->m_next = NULL;
	dev->m_endpointListEnd = newEp;
	return newEp;
}

int cleanUpFunc(UsbdDevice_t *dev, UsbdEndpoint_t *ep)
{
	if ( !ep || ep < memPool->m_endpointBuf || ep >= memPool->m_endpointBuf + usbConfig.m_maxEndpoints )
	{
		return 0;
	}
	if ( ep->m_inTdQueue != NOTIN_QUEUE )
	{
		if ( ep->m_busyNext )
			ep->m_busyNext->m_busyPrev = ep->m_busyPrev;
		else
			memPool->m_tdQueueEnd = ep->m_busyPrev;
		if ( ep->m_busyPrev )
			ep->m_busyPrev->m_busyNext = ep->m_busyNext;
		else
			memPool->m_tdQueueStart = ep->m_busyNext;
		ep->m_inTdQueue = NOTIN_QUEUE;
	}
	if ( ep->m_next )
		ep->m_next->m_prev = ep->m_prev;
	else
		dev->m_endpointListEnd = ep->m_prev;
	if ( ep->m_prev )
		ep->m_prev->m_next = ep->m_next;
	else
		dev->m_endpointListStart = ep->m_next;
	ep->m_prev = memPool->m_freeEpListEnd;
	if ( memPool->m_freeEpListEnd )
		memPool->m_freeEpListEnd->m_next = ep;
	else
		memPool->m_freeEpListStart = ep;
	ep->m_next = NULL;
	memPool->m_freeEpListEnd = ep;
	ep->m_correspDevice = NULL;
	return 0;
}

UsbdHcTD_t *allocTd(void)
{
	UsbdHcTD_t *res;

	res = memPool->m_freeHcTdList;
	if ( !res )
	{
		return NULL;
	}
	memPool->m_freeHcTdList = res->m_next;
	res->m_next = NULL;
	return res;
}

void freeTd(UsbdHcTD_t *argTd)
{
	UsbdHcTD_t *pos;

	if ( !argTd )
	{
		return;
	}
	for ( pos = memPool->m_freeHcTdList; pos && argTd != pos; pos = pos->m_next )
	{
	}
	if ( pos )
	{
		dbg_printf("FreeTD %p: already free\n", argTd);
		return;
	}
	argTd->m_next = memPool->m_freeHcTdList;
	memPool->m_freeHcTdList = argTd;
}

UsbdHcIsoTD_t *allocIsoTd(void)
{
	UsbdHcIsoTD_t *newTd;

	newTd = memPool->m_freeHcIsoTdList;
	if ( !newTd )
	{
		return NULL;
	}
	memPool->m_freeHcIsoTdList = newTd->m_next;
	newTd->m_next = NULL;
	return newTd;
}

void freeIsoTd(UsbdHcIsoTD_t *argTd)
{
	UsbdHcIsoTD_t *pos;

	if ( !argTd )
	{
		return;
	}
	for ( pos = memPool->m_freeHcIsoTdList; pos && argTd != pos; pos = pos->m_next )
	{
	}
	if ( pos )
	{
		dbg_printf("freeIsoTd %p: already free\n", argTd);
		return;
	}
	argTd->m_next = memPool->m_freeHcIsoTdList;
	memPool->m_freeHcIsoTdList = argTd;
}

// timer.c

int addTimerCallback(UsbdTimerCbStruct_t *arg, TimerCallback func, void *cbArg, int delay)
{
	UsbdTimerCbStruct_t *pos;

	if ( arg->m_isActive )
		return -1;
	arg->m_isActive = 1;
	if ( delay > 0 )
		delay -= 1;
	arg->m_callbackProc = func;
	arg->m_callbackArg = cbArg;
	for ( pos = memPool->m_timerListStart; pos && delay >= (int)pos->m_delayCount;
				pos = pos->m_prev, delay -= pos->m_delayCount )
	{
	}
	if ( pos )
	{
		arg->m_next = pos->m_next;
		if ( pos->m_next )
			pos->m_next->m_prev = arg;
		else
			memPool->m_timerListStart = arg;
		arg->m_prev = pos;
		pos->m_next = arg;
		pos->m_delayCount -= delay;
	}
	else
	{
		arg->m_next = memPool->m_timerListEnd;
		if ( memPool->m_timerListEnd )
			memPool->m_timerListEnd->m_prev = arg;
		else
			memPool->m_timerListStart = arg;
		memPool->m_timerListEnd = arg;
		arg->m_prev = NULL;
	}
	arg->m_delayCount = delay;
	memPool->m_ohciRegs->HcInterruptEnable = OHCI_INT_SF;
	return 0;
}

int cancelTimerCallback(UsbdTimerCbStruct_t *arg)
{
	if ( !arg->m_isActive )
	{
		return -1;
	}
	if ( arg->m_prev )
		arg->m_prev->m_next = arg->m_next;
	else
		memPool->m_timerListEnd = arg->m_next;
	if ( arg->m_next )
		arg->m_next->m_prev = arg->m_prev;
	else
		memPool->m_timerListStart = arg->m_prev;
	arg->m_isActive = 0;
	arg->m_next = NULL;
	arg->m_prev = NULL;
	return 0;
}

void handleTimerList(void)
{
	UsbdTimerCbStruct_t *timer;

	timer = memPool->m_timerListStart;
	if ( timer )
	{
		if ( timer->m_delayCount > 0 )
			timer->m_delayCount = timer->m_delayCount - 1;
		while ( 1 )
		{
			timer = memPool->m_timerListStart;
			if ( !timer || (int)timer->m_delayCount > 0 )
				break;
			dbg_printf("timer expired\n");
			memPool->m_timerListStart = timer->m_prev;
			if ( timer->m_prev )
				timer->m_prev->m_next = NULL;
			else
				memPool->m_timerListEnd = NULL;
			timer->m_next = NULL;
			timer->m_prev = NULL;
			timer->m_isActive = 0;
			timer->m_callbackProc(timer->m_callbackArg);
		}
	}
	// disable SOF interrupts if there are no timers left
	if ( !memPool->m_timerListStart )
		memPool->m_ohciRegs->HcInterruptDisable = OHCI_INT_SF;
}

// endpoint.c

void addToHcEndpointList(u8 type, UsbdHcED_t *ed)
{
	ed->m_next = memPool->m_hcEdBuf[type].m_next;
	memPool->m_hcEdBuf[type].m_next = ed;
}

void removeHcEdFromList(int type, const UsbdHcED_t *hcEd)
{
	UsbdHcED_t *prev;
	UsbdHcED_t *pos;

	prev = &memPool->m_hcEdBuf[type];
	for ( pos = prev->m_next; pos && pos != hcEd; prev = pos, pos = pos->m_next )
	{
	}
	if ( pos )
	{
		prev->m_next = pos->m_next;
	}
}

int setupBandwidthInterruptScheduling(UsbdEndpoint_t *ep, const UsbEndpointDescriptor *endpDesc, int isLowSpeedDevice)
{
	int maxPacketSize;
	u32 *interruptBandwidthSchedulingValues;
	int endpType;
	int waitHigh;
	int waitLow;
	int schedulingIndex;
	int i;
	int packetSizeForScheduling;
	u32 *value_ptr2;

	maxPacketSize = endpDesc->wMaxPacketSizeLB + (endpDesc->wMaxPacketSizeHB << 8);
	interruptBandwidthSchedulingValues = memPool->m_interruptBandwidthSchedulingValues;
	if ( endpDesc->bInterval >= 0x20u )
	{
		endpType = 31;
		waitHigh = 1;
		waitLow = 32;
	}
	else if ( endpDesc->bInterval >= 0x10u )
	{
		endpType = 15;
		waitHigh = 2;
		waitLow = 16;
	}
	else if ( endpDesc->bInterval >= 8u )
	{
		endpType = 7;
		waitHigh = 4;
		waitLow = 8;
	}
	else if ( endpDesc->bInterval >= 4u )
	{
		endpType = 3;
		waitHigh = 8;
		waitLow = 4;
	}
	else if ( endpDesc->bInterval >= 2u )
	{
		endpType = 1;
		waitHigh = 16;
		waitLow = 2;
	}
	else
	{
		endpType = 0;
		waitHigh = 32;
		waitLow = 1;
	}
	schedulingIndex = 0;
	if ( waitLow >= 2 )
	{
		int maxValueSum;

		schedulingIndex = -1;
		maxValueSum = 0;
		for ( i = 0; i < waitLow; i += 1 )
		{
			int valueSum;
			u32 *value_ptr1;
			int j;

			valueSum = 0;
			value_ptr1 = &interruptBandwidthSchedulingValues[i];
			for ( j = 0; j < waitHigh; j += 1 )
			{
				valueSum += *value_ptr1;
				value_ptr1 += waitLow;
			}
			if ( schedulingIndex < 0 || valueSum < maxValueSum )
			{
				schedulingIndex = i;
				maxValueSum = valueSum;
			}
		}
		endpType += schedulingIndex;
	}
	packetSizeForScheduling = maxPacketSize + 13;
	if ( maxPacketSize >= 65 )
		packetSizeForScheduling = 77;
	ep->m_schedulingIndex = schedulingIndex;
	ep->m_waitHigh = waitHigh;
	ep->m_waitLow = waitLow;
	ep->m_packetSizeForScheduling = packetSizeForScheduling;
	if ( isLowSpeedDevice )
		packetSizeForScheduling *= 8;
	value_ptr2 = &interruptBandwidthSchedulingValues[schedulingIndex];
	for ( i = 0; i < waitHigh; i += 1 )
	{
		*value_ptr2 += packetSizeForScheduling;
		value_ptr2 += waitLow;
	}
	return endpType;
}

void removeEndpointFromQueue(const UsbdEndpoint_t *ep, int isLowSpeedDevice)
{
	int i;
	u32 *value_ptr;

	value_ptr = &memPool->m_interruptBandwidthSchedulingValues[ep->m_schedulingIndex];
	for ( i = 0; i < ep->m_waitHigh; i += 1 )
	{
		*value_ptr -= (ep->m_packetSizeForScheduling * (isLowSpeedDevice ? 8 : 1));
		if ( (int)*value_ptr < 0 )
			*value_ptr = 0;
		value_ptr += ep->m_waitLow;
	}
}

UsbdEndpoint_t *openDeviceEndpoint(UsbdDevice_t *dev, const UsbEndpointDescriptor *endpDesc, u32 alignFlag)
{
	UsbdHcTD_t *td;
	int endpType;
	UsbdEndpoint_t *newEp;

	td = NULL;
	endpType = 0;
	newEp = allocEndpointForDevice(dev, alignFlag);
	if ( !newEp )
	{
		dbg_printf("ran out of endpoints\n");
		return NULL;
	}
	if ( endpDesc )
	{
		int hcMaxPktSize;
		int flags;

		hcMaxPktSize = endpDesc->wMaxPacketSizeLB + (endpDesc->wMaxPacketSizeHB << 8);
		switch ( endpDesc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK )
		{
			case USB_ENDPOINT_XFER_CONTROL:
			{
				endpType = TYPE_CONTROL;
				break;
			}
			case USB_ENDPOINT_XFER_ISOC:
			{
				endpType = TYPE_ISOCHRON;
				td = (UsbdHcTD_t *)allocIsoTd();
				if ( !td )
				{
					cleanUpFunc(dev, newEp);
					dbg_printf("Open ISOC EP: no TDs left\n");
					return NULL;
				}
				alignFlag = 1;
				break;
			}
			case USB_ENDPOINT_XFER_BULK:
			{
				endpType = TYPE_BULK;
				if ( (endpDesc->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN )
					alignFlag = 1;
				break;
			}
			case USB_ENDPOINT_XFER_INT:
			{
				endpType = setupBandwidthInterruptScheduling(newEp, endpDesc, dev->m_isLowSpeedDevice);
				dbg_printf(
					"opening INT endpoint (%d - %p), interval %d, list %d\n", newEp->m_id, newEp, endpDesc->bInterval, endpType);
				if ( (endpDesc->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN )
					alignFlag = 1;
				break;
			}
			default:
				break;
		}
		if ( !alignFlag && hcMaxPktSize > 62 )
		{
			hcMaxPktSize = 62;
		}
		flags = (hcMaxPktSize << 16) & 0x7FF0000;
		if ( endpType == TYPE_ISOCHRON )
			flags |= HCED_ISOC;
		if ( dev->m_isLowSpeedDevice )
			flags |= HCED_SPEED;
		flags |= ((endpDesc->bEndpointAddress & 0x1F) << 7)
					 | ((endpDesc->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN ? HCED_DIR_IN : HCED_DIR_OUT);
		newEp->m_hcEd->m_hcArea.asu32 = flags | (dev->m_functionAddress & 0x7F);
	}
	else
	{
		newEp->m_hcEd->m_hcArea.asu32 = 0x80000;
		newEp->m_hcEd->m_hcArea.asu32 |= dev->m_isLowSpeedDevice ? HCED_SPEED : 0;
		endpType = TYPE_CONTROL;
	}
	newEp->m_endpointType = endpType;
	if ( !td )
	{
		td = allocTd();
	}
	if ( !td )
	{
		dbg_printf("Ran out of TDs\n");
		cleanUpFunc(dev, newEp);
		return NULL;
	}
	newEp->m_hcEd->m_tdHead = td;
	newEp->m_hcEd->m_tdTail = td;
	addToHcEndpointList(endpType & 0xFF, newEp->m_hcEd);
	return newEp;
}

void killEndpoint(UsbdEndpoint_t *ep)
{
	UsbdHcED_t *hcEd;
	int i;
	UsbdIoRequest_t *req;

	hcEd = ep->m_hcEd;
	if ( ep->m_endpointType == TYPE_ISOCHRON )
	{
		for ( i = 0; i < usbConfig.m_maxIsoTransfDesc; i += 1 )
		{
			if ( memPool->m_hcIsoTdToIoReqLUT[i] && memPool->m_hcIsoTdToIoReqLUT[i]->m_correspEndpoint == ep )
			{
				freeIoRequest(memPool->m_hcIsoTdToIoReqLUT[i]);
				memPool->m_hcIsoTdToIoReqLUT[i] = NULL;
				freeIsoTd(&memPool->m_hcIsoTdBuf[i]);
			}
		}
		freeIsoTd((UsbdHcIsoTD_t *)hcEd->m_tdTail);
		hcEd->m_tdTail = NULL;
	}
	else
	{
		for ( i = 0; i < usbConfig.m_maxTransfDesc; i += 1 )
		{
			if ( memPool->m_hcTdToIoReqLUT[i] && memPool->m_hcTdToIoReqLUT[i]->m_correspEndpoint == ep )
			{
				freeIoRequest(memPool->m_hcTdToIoReqLUT[i]);
				memPool->m_hcTdToIoReqLUT[i] = NULL;
				freeTd(&memPool->m_hcTdBuf[i]);
			}
		}
		freeTd(hcEd->m_tdTail);
		hcEd->m_tdTail = NULL;
	}
	hcEd->m_tdHead = NULL;
	for ( req = ep->m_ioReqListStart; req; req = ep->m_ioReqListStart )
	{
		if ( req->m_next )
			req->m_next->m_prev = req->m_prev;
		else
			ep->m_ioReqListEnd = req->m_prev;
		if ( req->m_prev )
			req->m_prev->m_next = req->m_next;
		else
			ep->m_ioReqListStart = req->m_next;
		freeIoRequest(req);
	}
	removeEndpointFromQueue(ep, ep->m_correspDevice->m_isLowSpeedDevice);
	if ( ep->m_inTdQueue != NOTIN_QUEUE )
	{
		if ( ep->m_busyNext )
			ep->m_busyNext->m_busyPrev = ep->m_busyPrev;
		else
			memPool->m_tdQueueEnd = ep->m_busyPrev;
		if ( ep->m_busyPrev )
			ep->m_busyPrev->m_busyNext = ep->m_busyNext;
		else
			memPool->m_tdQueueStart = ep->m_busyNext;
		ep->m_inTdQueue = NOTIN_QUEUE;
	}
	ep->m_prev = memPool->m_freeEpListEnd;
	if ( memPool->m_freeEpListEnd )
		memPool->m_freeEpListEnd->m_next = ep;
	else
		memPool->m_freeEpListStart = ep;
	ep->m_next = NULL;
	memPool->m_freeEpListEnd = ep;
}

int removeEndpointFromDevice(UsbdDevice_t *dev, UsbdEndpoint_t *ep)
{
	ep->m_hcEd->m_hcArea.stru.m_hcArea |= HCED_SKIP;
	removeHcEdFromList(ep->m_endpointType, ep->m_hcEd);
	if ( ep->m_next )
		ep->m_next->m_prev = ep->m_prev;
	else
		dev->m_endpointListEnd = ep->m_prev;
	if ( ep->m_prev )
		ep->m_prev->m_next = ep->m_next;
	else
		dev->m_endpointListStart = ep->m_next;
	ep->m_correspDevice = NULL;
	addTimerCallback(&ep->m_timer, (TimerCallback)killEndpoint, ep, 200);
	return 0;
}

// io_request.c

int setupControlTransfer(UsbdEndpoint_t *ep)
{
	UsbdIoRequest_t *curIoReq;
	UsbdHcTD_t *dataTd;
	UsbdHcTD_t *tailTd;
	UsbdHcTD_t *statusTd;

	if ( !ep->m_hcEd->m_tdTail || ED_HALTED(*(ep->m_hcEd)) || ED_SKIPPED(*(ep->m_hcEd)) || !ep->m_ioReqListStart )
	{
		// endpoint error
		if ( ep->m_inTdQueue == NOTIN_QUEUE )
			return 0;
		if ( ep->m_busyNext )
			ep->m_busyNext->m_busyPrev = ep->m_busyPrev;
		else
			memPool->m_tdQueueEnd = ep->m_busyPrev;
		if ( ep->m_busyPrev )
		{
			ep->m_busyPrev->m_busyNext = ep->m_busyNext;
		}
		else
		{
			memPool->m_tdQueueStart = ep->m_busyNext;
		}
		ep->m_inTdQueue = NOTIN_QUEUE;
		return 0;
	}
	curIoReq = ep->m_ioReqListStart;
	dataTd = NULL;
	if ( curIoReq->m_destPtr && (int)curIoReq->m_length > 0 )
	{
		dataTd = allocTd();
		if ( !dataTd )
		{
			if ( ep->m_inTdQueue != NOTIN_QUEUE )
				return 0;
			ep->m_busyPrev = memPool->m_tdQueueEnd;
			if ( memPool->m_tdQueueEnd )
			{
				memPool->m_tdQueueEnd->m_busyNext = ep;
			}
			else
			{
				memPool->m_tdQueueStart = ep;
			}
			ep->m_busyNext = NULL;
			memPool->m_tdQueueEnd = ep;
			ep->m_inTdQueue = GENTD_QUEUE;
			return 0;
		}
	}
	statusTd = allocTd();
	tailTd = allocTd();
	if ( !statusTd || !tailTd )
	{
		freeTd(dataTd);
		freeTd(statusTd);
		freeTd(tailTd);
		if ( ep->m_inTdQueue != NOTIN_QUEUE )
			return 0;
		ep->m_busyPrev = memPool->m_tdQueueEnd;
		if ( memPool->m_tdQueueEnd )
		{
			memPool->m_tdQueueEnd->m_busyNext = ep;
		}
		else
		{
			memPool->m_tdQueueStart = ep;
		}
		ep->m_busyNext = NULL;
		memPool->m_tdQueueEnd = ep;
		ep->m_inTdQueue = GENTD_QUEUE;
		return 0;
	}
	if ( curIoReq->m_next )
		curIoReq->m_next->m_prev = curIoReq->m_prev;
	else
		ep->m_ioReqListEnd = curIoReq->m_prev;
	if ( curIoReq->m_prev )
		curIoReq->m_prev->m_next = curIoReq->m_next;
	else
		ep->m_ioReqListStart = curIoReq->m_next;
	// first stage: setup
	ep->m_hcEd->m_tdTail->m_hcArea = TD_HCAREA(USB_RC_NOTACCESSED, 2, 7, TD_SETUP, 0) << 16;
	ep->m_hcEd->m_tdTail->m_curBufPtr = &curIoReq->m_devReq;
	ep->m_hcEd->m_tdTail->m_next = dataTd ? dataTd : statusTd;
	ep->m_hcEd->m_tdTail->m_bufferEnd = ((char *)&curIoReq->m_devReq) + sizeof(UsbDeviceRequest) - 1;
	memPool->m_hcTdToIoReqLUT[ep->m_hcEd->m_tdTail - memPool->m_hcTdBuf] = curIoReq;
	// second stage: data
	if ( dataTd )
	{
		dataTd->m_hcArea = (curIoReq->m_devReq.requesttype & USB_ENDPOINT_DIR_MASK) != USB_DIR_IN ?
												 (TD_HCAREA(USB_RC_NOTACCESSED, 3, 7, TD_OUT, 1) << 16) :
												 (TD_HCAREA(USB_RC_NOTACCESSED, 3, 7, TD_IN, 1) << 16);
		dataTd->m_next = statusTd;
		dataTd->m_curBufPtr = curIoReq->m_destPtr;
		dataTd->m_bufferEnd = (char *)curIoReq->m_destPtr + curIoReq->m_length - 1;
		memPool->m_hcTdToIoReqLUT[dataTd - memPool->m_hcTdBuf] = curIoReq;
	}
	// third stage: status
	statusTd->m_hcArea = (curIoReq->m_devReq.requesttype & USB_ENDPOINT_DIR_MASK) != USB_DIR_IN ?
												 (TD_HCAREA(USB_RC_NOTACCESSED, 3, 0, TD_IN, 0) << 16) :
												 (TD_HCAREA(USB_RC_NOTACCESSED, 3, 0, TD_OUT, 0) << 16);
	statusTd->m_curBufPtr = NULL;
	statusTd->m_next = tailTd;
	statusTd->m_bufferEnd = NULL;
	memPool->m_hcTdToIoReqLUT[statusTd - memPool->m_hcTdBuf] = curIoReq;
	ep->m_hcEd->m_tdTail = tailTd;
	memPool->m_ohciRegs->HcCommandStatus |= OHCI_COM_CLF;  // control list filled
	if ( ep->m_ioReqListStart )
	{
		return 1;
	}
	if ( ep->m_inTdQueue == NOTIN_QUEUE )
	{
		return 1;
	}
	// remove endpoint from busy list if there are no IoRequests left
	if ( ep->m_busyNext )
		ep->m_busyNext->m_busyPrev = ep->m_busyPrev;
	else
		memPool->m_tdQueueEnd = ep->m_busyPrev;
	if ( ep->m_busyPrev )
		ep->m_busyPrev->m_busyNext = ep->m_busyNext;
	else
		memPool->m_tdQueueStart = ep->m_busyNext;
	ep->m_inTdQueue = NOTIN_QUEUE;
	return 1;
}

int setupIsocronTransfer(UsbdEndpoint_t *ep)
{
	UsbdHcED_t *ed;
	UsbdIoRequest_t *curIoReq;
	UsbdHcIsoTD_t *curTd;
	UsbdHcIsoTD_t *newTd;
	u16 frameNo;

	ed = ep->m_hcEd;
	if ( !ed->m_tdTail || ED_HALTED(*ed) || ED_SKIPPED(*ed) || !ep->m_ioReqListStart )
	{
		// endpoint error
		if ( ep->m_inTdQueue == NOTIN_QUEUE )
			return 0;
		if ( ep->m_busyNext )
			ep->m_busyNext->m_busyPrev = ep->m_busyPrev;
		else
			memPool->m_tdQueueEnd = ep->m_busyPrev;
		if ( ep->m_busyPrev )
		{
			ep->m_busyPrev->m_busyNext = ep->m_busyNext;
		}
		else
		{
			memPool->m_tdQueueStart = ep->m_busyNext;
		}
		ep->m_inTdQueue = NOTIN_QUEUE;
		return 0;
	}
	curIoReq = ep->m_ioReqListStart;
	curTd = (UsbdHcIsoTD_t *)ed->m_tdTail;
	newTd = allocIsoTd();
	if ( !newTd )
	{
		if ( ep->m_inTdQueue != NOTIN_QUEUE )
			return 0;
		ep->m_busyPrev = memPool->m_tdQueueEnd;
		if ( memPool->m_tdQueueEnd )
			memPool->m_tdQueueEnd->m_busyNext = ep;
		else
			memPool->m_tdQueueStart = ep;
		ep->m_busyNext = NULL;
		memPool->m_tdQueueEnd = ep;
		ep->m_inTdQueue = ISOTD_QUEUE;
		return 0;
	}
	if ( curIoReq->m_next )
		curIoReq->m_next->m_prev = curIoReq->m_prev;
	else
		ep->m_ioReqListEnd = curIoReq->m_prev;
	if ( curIoReq->m_prev )
		curIoReq->m_prev->m_next = curIoReq->m_next;
	else
		ep->m_ioReqListStart = curIoReq->m_next;
	if ( (UsbdHcTD_t *)((int)ed->m_tdHead & ~0xF) == ed->m_tdTail )
		frameNo = (memPool->m_hcHCCA->FrameNumber + 2) & 0xFFFF;
	else
		frameNo = (ep->m_isochronLastFrameNum) & 0xFFFF;
	frameNo = (u16)(frameNo + (curIoReq->m_waitFrames & 0xFFFF));
	ep->m_isochronLastFrameNum = (curIoReq->m_req.bNumPackets ? (curIoReq->m_req.bNumPackets & 0xFFFF) : 1) + frameNo;
	if ( curIoReq->m_req.bNumPackets )
	{
		int psw0_tmp;
		int i;

		curTd->m_hcArea = ((curIoReq->m_req.bNumPackets - 1) << 24) | frameNo | (USB_RC_NOTACCESSED << 28);
		curTd->m_next = newTd;
		curTd->m_bufferPage0 = (void *)((uiptr)curIoReq->m_destPtr & ~0xFFF);
		curTd->m_bufferEnd = NULL;
		if ( curIoReq->m_destPtr && (int)(curIoReq->m_length) > 0 )
		{
			curTd->m_bufferEnd = (char *)curIoReq->m_destPtr + ((int)curIoReq->m_length - 1);
		}
		psw0_tmp = ((uiptr)curIoReq->m_destPtr & 0xFFF) | (USB_RC_NOTACCESSED << 12);
		for ( i = 0; i < (int)curIoReq->m_req.bNumPackets; i += 1 )
		{
			curTd->m_psw[i] = psw0_tmp;
			psw0_tmp += curIoReq->m_req.Packets[i].bLength;
		}
	}
	else
	{
		curTd->m_hcArea = frameNo | (USB_RC_NOTACCESSED << 28);
		curTd->m_next = newTd;
		curTd->m_bufferPage0 = (void *)((uiptr)curIoReq->m_destPtr & ~0xFFF);
		curTd->m_bufferEnd = NULL;
		if ( curIoReq->m_destPtr && (int)(curIoReq->m_length) > 0 )
		{
			curTd->m_bufferEnd = (char *)curIoReq->m_destPtr + ((int)curIoReq->m_length - 1);
		}
		curTd->m_psw[0] = ((int)curIoReq->m_destPtr & 0xFFF) | (USB_RC_NOTACCESSED << 12);
	}
	memPool->m_hcIsoTdToIoReqLUT[curTd - memPool->m_hcIsoTdBuf] = curIoReq;
	ed->m_tdTail = (UsbdHcTD_t *)newTd;
	if ( ep->m_ioReqListStart )
	{
		return 1;
	}
	if ( ep->m_inTdQueue == NOTIN_QUEUE )
	{
		return 1;
	}
	// remove endpoint from busy list if there are no IoRequests left
	if ( ep->m_busyNext )
		ep->m_busyNext->m_busyPrev = ep->m_busyPrev;
	else
		memPool->m_tdQueueEnd = ep->m_busyPrev;
	if ( ep->m_busyPrev )
		ep->m_busyPrev->m_busyNext = ep->m_busyNext;
	else
		memPool->m_tdQueueStart = ep->m_busyNext;
	ep->m_inTdQueue = NOTIN_QUEUE;
	return 1;
}

int setupBulkTransfer(UsbdEndpoint_t *ep)
{
	UsbdHcED_t *ed;
	UsbdIoRequest_t *curIoReq;
	UsbdHcTD_t *curTd;
	UsbdHcTD_t *newTd;

	ed = ep->m_hcEd;
	if ( !ed->m_tdTail || ED_HALTED(*ed) || ED_SKIPPED(*ed) || !ep->m_ioReqListStart )
	{
		// endpoint error
		dbg_printf("ERROR UsbdEndpoint_t error\n");
		if ( ep->m_inTdQueue == NOTIN_QUEUE )
			return 0;
		if ( ep->m_busyNext )
			ep->m_busyNext->m_busyPrev = ep->m_busyPrev;
		else
			memPool->m_tdQueueEnd = ep->m_busyPrev;
		if ( ep->m_busyPrev )
		{
			ep->m_busyPrev->m_busyNext = ep->m_busyNext;
		}
		else
		{
			memPool->m_tdQueueStart = ep->m_busyNext;
		}
		ep->m_inTdQueue = NOTIN_QUEUE;
		return 0;
	}
	curIoReq = ep->m_ioReqListStart;
	curTd = ed->m_tdTail;
	newTd = allocTd();
	if ( !newTd )
	{
		if ( ep->m_inTdQueue != NOTIN_QUEUE )
			return 0;
		ep->m_busyPrev = memPool->m_tdQueueEnd;
		if ( memPool->m_tdQueueEnd )
			memPool->m_tdQueueEnd->m_busyNext = ep;
		else
			memPool->m_tdQueueStart = ep;
		ep->m_busyNext = NULL;
		memPool->m_tdQueueEnd = ep;
		ep->m_inTdQueue = GENTD_QUEUE;
		return 0;
	}
	if ( curIoReq->m_next )
		curIoReq->m_next->m_prev = curIoReq->m_prev;
	else
		ep->m_ioReqListEnd = curIoReq->m_prev;
	if ( curIoReq->m_prev )
		curIoReq->m_prev->m_next = curIoReq->m_next;
	else
		ep->m_ioReqListStart = curIoReq->m_next;
	curTd->m_hcArea = TD_HCAREA(USB_RC_NOTACCESSED, 0, 0, 3, 1) << 16;
	curTd->m_next = newTd;
	curTd->m_curBufPtr = curIoReq->m_destPtr;
	curTd->m_bufferEnd = NULL;
	if ( curIoReq->m_destPtr && (int)curIoReq->m_length > 0 )
	{
		curTd->m_bufferEnd = (char *)curIoReq->m_destPtr + ((int)curIoReq->m_length - 1);
	}
	memPool->m_hcTdToIoReqLUT[curTd - memPool->m_hcTdBuf] = curIoReq;
	ed->m_tdTail = newTd;
	if ( ep->m_endpointType == TYPE_BULK )
		memPool->m_ohciRegs->HcCommandStatus |= OHCI_COM_BLF;  // Bulk List Filled
	if ( ep->m_ioReqListStart )
	{
		return 1;
	}
	if ( ep->m_inTdQueue == NOTIN_QUEUE )
	{
		return 1;
	}
	// remove endpoint from busy list if there are no IoRequests left
	if ( ep->m_busyNext )
		ep->m_busyNext->m_busyPrev = ep->m_busyPrev;
	else
		memPool->m_tdQueueEnd = ep->m_busyPrev;
	if ( ep->m_busyPrev )
		ep->m_busyPrev->m_busyNext = ep->m_busyNext;
	else
		memPool->m_tdQueueStart = ep->m_busyNext;
	ep->m_inTdQueue = NOTIN_QUEUE;
	return 1;
}

void handleIoReqList(UsbdEndpoint_t *ep)
{
	switch ( ep->m_endpointType )
	{
		case TYPE_CONTROL:
		{
			setupControlTransfer(ep);
			break;
		}
		case TYPE_ISOCHRON:
		{
			setupIsocronTransfer(ep);
			break;
		}
		case TYPE_BULK:
		default:  // bulk or interrupt
		{
			setupBulkTransfer(ep);
			break;
		}
	}
}

// hub_resets.c

void usbdRebootInner(void)
{
	memPool->m_ohciRegs->HcRhPortStatus[0] = 16;
	memPool->m_ohciRegs->HcRhPortStatus[1] = 16;
}

void hubResetDevice(UsbdDevice_t *dev)
{
	if ( memPool->m_delayResets )
	{
		dev->m_deviceStatus = DEVICE_RESETDELAYED;
	}
	else
	{
		memPool->m_delayResets = 1;
		dev->m_deviceStatus = DEVICE_RESETPENDING;
		dev->m_resetFlag = 1;
		if ( dev->m_parent == memPool->m_deviceTreeRoot )  // root hub port
			memPool->m_ohciRegs->HcRhPortStatus[dev->m_attachedToPortNo - 1] = BIT(PORT_RESET);
		else  // normal hub port
			hubResetDevicePort(dev);
	}
}

int checkDelayedResetsTree(UsbdDevice_t *tree)
{
	UsbdDevice_t *dev;

	for ( dev = tree->m_childListStart; dev; dev = dev->m_next )
	{
		if ( dev->m_deviceStatus == DEVICE_RESETDELAYED )
		{
			hubResetDevice(dev);
			return 1;
		}
		if ( dev->m_childListStart )
		{
			if ( (u8)(dev->m_deviceStatus - 7) < 2u )
			{
				if ( checkDelayedResetsTree(dev) != 0 )
					return 1;
			}
		}
	}
	return 0;
}

int checkDelayedResets(UsbdDevice_t *dev)
{
	memPool->m_delayResets = 0;
	dev->m_resetFlag = 0;
	checkDelayedResetsTree(memPool->m_deviceTreeRoot);
	return 0;
}

void handleRhsc(void)
{
	UsbdDevice_t *port;
	volatile u32 *status_addr;
	UsbdDevice_t *next;

	port = memPool->m_deviceTreeRoot->m_childListStart;
	for ( status_addr = memPool->m_ohciRegs->HcRhPortStatus; port; status_addr += 1 )
	{
		u32 status;

		next = port->m_next;
		status = *status_addr;
		*status_addr = C_PORT_FLAGS;  // reset all flags
		if ( (status & BIT(PORT_CONNECTION)) != 0 )
		{
			if ( port->m_deviceStatus >= (unsigned int)DEVICE_CONNECTED && (status & BIT(C_PORT_CONNECTION)) != 0 )
				flushPort(port);
			if ( port->m_deviceStatus == DEVICE_NOTCONNECTED )
			{
				port->m_deviceStatus = DEVICE_CONNECTED;
				addTimerCallback(&port->m_timer, (TimerCallback)hubResetDevice, port, 501);
			}
			else if ( port->m_deviceStatus == DEVICE_RESETPENDING )
			{
				if ( (status & BIT(PORT_RESET)) == 0 )
				{
					port->m_deviceStatus = DEVICE_RESETCOMPLETE;
					port->m_isLowSpeedDevice = (status & BIT(PORT_LOW_SPEED)) != 0;
					if ( openDeviceEndpoint(port, NULL, 0) )
						hubTimedSetFuncAddress(port);
				}
			}
		}
		else
		{
			flushPort(port);
		}
		port = next;
	}
}

// td_queue.c

void checkGenTdQueue(void)
{
	UsbdEndpoint_t *queueStart_tmp1;

	if ( !memPool->m_freeHcTdList )
	{
		return;
	}
	for ( queueStart_tmp1 = memPool->m_tdQueueStart; queueStart_tmp1 && queueStart_tmp1->m_inTdQueue != GENTD_QUEUE;
				queueStart_tmp1 = queueStart_tmp1->m_busyNext )
	{
	}
	if ( queueStart_tmp1 )
		handleIoReqList(queueStart_tmp1);
}

void processDoneQueue_GenTd(UsbdHcTD_t *arg)
{
	u32 tdHcArea;
	const u8 *curBufPtr;
	const void *bufferEnd;
	UsbdIoRequest_t **lut_ptr1;
	u32 hcRes;
	UsbdIoRequest_t *req_1;
	UsbdHcED_t *ed;
	UsbdHcTD_t *tdListPos_2;
	UsbdHcTD_t *nextTd;
	UsbdIoRequest_t *req_2;
	UsbdIoRequest_t *listPos;
	UsbdIoRequest_t *pos;
	UsbdIoRequest_t *next_tmp1;
	UsbdIoRequest_t *firstElem;
	UsbdIoRequest_t *lastElem;

	lastElem = NULL;
	firstElem = NULL;
	tdHcArea = arg->m_hcArea;
	curBufPtr = (u8 *)arg->m_curBufPtr;
	bufferEnd = arg->m_bufferEnd;
	lut_ptr1 = &memPool->m_hcTdToIoReqLUT[arg - memPool->m_hcTdBuf];
	hcRes = arg->m_hcArea >> 28;
	req_1 = *lut_ptr1;
	*lut_ptr1 = NULL;
	if ( req_1 == 0 )
	{
		return;
	}
	freeTd(arg);
	if ( bufferEnd && (tdHcArea & 0x180000) != 0 )  // dir != SETUP
	{
		// transfer successful when !curBufPtr
		req_1->m_transferedBytes = curBufPtr ? (u32)(curBufPtr - (u8 *)req_1->m_destPtr) : req_1->m_length;
	}
	if ( req_1->m_resultCode == USB_RC_OK )
		req_1->m_resultCode = hcRes;
	if ( hcRes || (arg->m_hcArea & 0xE00000) != 0xE00000 )  // E00000: interrupts disabled
	{
		req_1->m_prev = NULL;
		firstElem = req_1;
		req_1->m_next = NULL;
		lastElem = req_1;
	}
	if ( hcRes )
	{
		UsbdHcTD_t *tdListPos_1;

		ed = req_1->m_correspEndpoint->m_hcEd;
		tdListPos_1 = ed->m_tdHead;
		if ( ED_HALTED(*ed) )
		{
			for ( tdListPos_2 = (UsbdHcTD_t *)((uiptr)tdListPos_1 & ~0xF); tdListPos_2 && tdListPos_2 != ed->m_tdTail;
						tdListPos_2 = nextTd )
			{
				UsbdIoRequest_t **lut_ptr2;

				nextTd = tdListPos_2->m_next;
				freeTd(tdListPos_2);
				lut_ptr2 = &memPool->m_hcTdToIoReqLUT[tdListPos_2 - memPool->m_hcTdBuf];
				req_2 = *lut_ptr2;
				*lut_ptr2 = NULL;
				if ( req_2 )
				{
					for ( listPos = firstElem; listPos && listPos != req_2; listPos = listPos->m_next )
					{
					}
					if ( listPos )
					{
						continue;
					}
					req_2->m_resultCode = USB_RC_ABORTED;
					req_2->m_prev = lastElem;
					if ( lastElem )
						lastElem->m_next = req_2;
					else
						firstElem = req_2;
					req_2->m_next = NULL;
					lastElem = req_2;
				}
			}
			ed->m_tdHead = ed->m_tdTail;
		}
	}
	for ( pos = firstElem; pos; pos = next_tmp1 )
	{
		pos->m_busyFlag = 0;
		next_tmp1 = pos->m_next;
		if ( pos->m_correspEndpoint->m_correspDevice )
		{
			if ( pos->m_callbackProc )
				pos->m_callbackProc(pos);
		}
		else
		{
			freeIoRequest(pos);
		}
	}
	checkGenTdQueue();
}

void checkIsoTdQueue(void)
{
	UsbdEndpoint_t *queueStart_tmp1;

	if ( !memPool->m_freeHcIsoTdList )
	{
		return;
	}
	for ( queueStart_tmp1 = memPool->m_tdQueueStart; queueStart_tmp1 && queueStart_tmp1->m_inTdQueue != ISOTD_QUEUE;
				queueStart_tmp1 = queueStart_tmp1->m_busyNext )
	{
	}
	if ( queueStart_tmp1 )
		handleIoReqList(queueStart_tmp1);
}

void processDoneQueue_IsoTd(UsbdHcIsoTD_t *arg)
{
	u32 hcArea;
	unsigned int psw_tmp;
	u32 tdHcRes;
	unsigned int pswRes;
	UsbdIoRequest_t **lut_ptr1;
	int pswOfs;
	UsbdIoRequest_t *req_1;
	UsbdHcED_t *ed;
	UsbdHcTD_t *tdHead;
	UsbdHcIsoTD_t *curTd;
	UsbdHcIsoTD_t *nextTd;
	UsbdIoRequest_t *req_2;
	UsbdIoRequest_t *listPos;
	UsbdIoRequest_t *pos;
	UsbdIoRequest_t *next_tmp1;
	UsbdIoRequest_t *listStart;
	UsbdIoRequest_t *listEnd;

	hcArea = arg->m_hcArea;
	psw_tmp = arg->m_psw[0];
	tdHcRes = hcArea >> 28;
	pswRes = psw_tmp >> 12;
	lut_ptr1 = &memPool->m_hcIsoTdToIoReqLUT[arg - memPool->m_hcIsoTdBuf];
	pswOfs = psw_tmp & 0x7FF;
	req_1 = *lut_ptr1;
	*lut_ptr1 = NULL;
	if ( !req_1 )
	{
		return;
	}
	if ( req_1->m_req.bNumPackets )
		bcopy(arg->m_psw, req_1->m_req.Packets, 16);
	freeIsoTd(arg);
	req_1->m_transferedBytes = 0;
	if ( req_1->m_req.bNumPackets )
	{
		req_1->m_resultCode = tdHcRes;
	}
	else
	{
		req_1->m_resultCode = tdHcRes | (pswRes << 4);
		if ( tdHcRes == USB_RC_OK && (pswRes == USB_RC_OK || pswRes == USB_RC_DATAUNDER) )
		{
			if ( (req_1->m_correspEndpoint->m_hcEd->m_hcArea.stru.m_hcArea & HCED_DIR_MASK) == HCED_DIR_IN )
				req_1->m_transferedBytes = pswOfs;
			else
				req_1->m_transferedBytes = req_1->m_length;
		}
	}
	req_1->m_prev = NULL;
	listStart = req_1;
	req_1->m_next = NULL;
	listEnd = req_1;
	ed = req_1->m_correspEndpoint->m_hcEd;
	tdHead = ed->m_tdHead;
	if ( ED_HALTED(*ed) )
	{
		for ( curTd = (UsbdHcIsoTD_t *)((uiptr)tdHead & ~0xF); curTd && curTd != (UsbdHcIsoTD_t *)(ed->m_tdTail);
					curTd = nextTd )
		{
			UsbdIoRequest_t **lut_ptr2;

			nextTd = curTd->m_next;
			freeIsoTd(curTd);
			lut_ptr2 = &memPool->m_hcIsoTdToIoReqLUT[curTd - memPool->m_hcIsoTdBuf];
			req_2 = *lut_ptr2;
			*lut_ptr2 = NULL;
			if ( req_2 )
			{
				for ( listPos = listStart; listPos && listPos != req_2; listPos = listPos->m_next )
				{
				}
				if ( listPos )
				{
					continue;
				}
				req_2->m_resultCode = USB_RC_ABORTED;
				req_2->m_prev = listEnd;
				if ( listEnd )
					listEnd->m_next = req_2;
				else
					listStart = req_2;
				req_2->m_next = NULL;
				listEnd = req_2;
			}
		}
		ed->m_tdHead = ed->m_tdTail;
	}
	for ( pos = listStart; pos; pos = next_tmp1 )
	{
		pos->m_busyFlag = 0;
		next_tmp1 = pos->m_next;
		if ( pos->m_correspEndpoint->m_correspDevice )
		{
			if ( pos->m_callbackProc )
				pos->m_callbackProc(pos);
		}
		else
		{
			freeIoRequest(pos);
		}
	}
	checkIsoTdQueue();
}

// hcd.c

void hcdProcessIntr(void)
{
	volatile OhciRegs *ohciRegs;
	volatile HcCA *hcHCCA;
	int intrFlags;
	UsbdHcTD_t *doneQueue;
	UsbdHcTD_t *prev;
	UsbdHcTD_t *next_tmp1;
	UsbdHcTD_t *next_tmp2;

	ohciRegs = memPool->m_ohciRegs;
	memPool->m_interruptCounters[0] += 1;
	hcHCCA = memPool->m_hcHCCA;
	intrFlags = ohciRegs->HcInterruptStatus & ohciRegs->HcInterruptEnable;
	if ( (intrFlags & OHCI_INT_SO) != 0 )
	{
		dbg_printf("HC: Scheduling overrun\n");
		ohciRegs->HcInterruptStatus = OHCI_INT_SO;
		intrFlags &= ~OHCI_INT_SO;
		memPool->m_interruptCounters[1] += 1;
	}
	doneQueue = (UsbdHcTD_t *)((uiptr)hcHCCA->DoneHead & ~0xF);
	prev = NULL;
	if ( doneQueue )
	{
		hcHCCA->DoneHead = NULL;
		ohciRegs->HcInterruptStatus = OHCI_INT_WDH;

		// reverse queue
		while ( doneQueue )
		{
			next_tmp1 = doneQueue;
			doneQueue = doneQueue->m_next;
			next_tmp1->m_next = prev;
			prev = next_tmp1;
		}
		for ( ; prev; prev = next_tmp2 )
		{
			next_tmp2 = prev->m_next;
			if ( prev < memPool->m_hcTdBuf || prev >= memPool->m_hcTdBufEnd )
			{
				if ( (UsbdHcIsoTD_t *)prev >= memPool->m_hcIsoTdBuf && (UsbdHcIsoTD_t *)prev < memPool->m_hcIsoTdBufEnd )
					processDoneQueue_IsoTd((UsbdHcIsoTD_t *)prev);
			}
			else
			{
				processDoneQueue_GenTd(prev);
			}
		}
		intrFlags &= ~OHCI_INT_WDH;
		memPool->m_interruptCounters[2] += 1;
	}
	if ( (intrFlags & OHCI_INT_SF) != 0 )
	{
		ohciRegs->HcInterruptStatus = OHCI_INT_SF;
		handleTimerList();
		intrFlags &= ~OHCI_INT_SF;
		memPool->m_interruptCounters[3] += 1;
	}
	if ( (intrFlags & OHCI_INT_RD) != 0 )
	{
		ohciRegs->HcInterruptStatus = OHCI_INT_RD;
		intrFlags &= ~OHCI_INT_RD;
		memPool->m_interruptCounters[4] += 1;
	}
	if ( (intrFlags & OHCI_INT_UE) != 0 )
	{
		dbg_printf("HC: Unrecoverable error\n");
		ohciRegs->HcInterruptStatus = OHCI_INT_UE;
		intrFlags &= ~OHCI_INT_UE;
		memPool->m_interruptCounters[5] += 1;
	}
	if ( (intrFlags & OHCI_INT_FNO) != 0 )
	{
		ohciRegs->HcInterruptStatus = OHCI_INT_FNO;
		intrFlags &= ~OHCI_INT_FNO;
		memPool->m_interruptCounters[6] += 1;
	}
	if ( (intrFlags & OHCI_INT_RHSC) != 0 )
	{
		dbg_printf("RHSC\n");
		ohciRegs->HcInterruptStatus = OHCI_INT_RHSC;
		handleRhsc();
		intrFlags &= ~OHCI_INT_RHSC;
		memPool->m_interruptCounters[7] += 1;
	}
	if ( (intrFlags & OHCI_INT_OC) != 0 )
	{
		ohciRegs->HcInterruptStatus = OHCI_INT_OC;
		intrFlags &= ~OHCI_INT_OC;
		memPool->m_interruptCounters[8] += 1;
	}

	if ( (intrFlags & ~OHCI_INT_MIE) != 0 )
	{
		dbg_printf("Disable intr: %d\n", intrFlags);
		ohciRegs->HcInterruptDisable = intrFlags;
	}
}

static void PostIntrEnableFunction(void)
{
	volatile int lw_busy;
	volatile OhciRegs *ohciRegs;

	lw_busy = 0;
	ohciRegs = memPool->m_ohciRegs;
	memPool->m_ohciRegs->HcInterruptDisable = OHCI_INT_MIE;
	do
	{
		(void)*((volatile u32 *)0xBFC00000);
		lw_busy -= 1;
	} while ( lw_busy > 0 );
	ohciRegs->HcInterruptEnable = OHCI_INT_MIE;
}

int initHardware(volatile OhciRegs *ohciRegs)
{
	int i;

	dbg_printf("Host Controller...\n");
	ohciRegs->HcInterruptDisable = ~0;
	ohciRegs->HcControl &= ~0x3Cu;
	DelayThread(2000);
	ohciRegs->HcCommandStatus = OHCI_COM_HCR;
	ohciRegs->HcControl = 0;
	for ( i = 1; i < 1000; i += 1 )
	{
		volatile int lw_busy;

		if ( (ohciRegs->HcCommandStatus & OHCI_COM_HCR) == 0 )
		{
			dbg_printf("HC reset done\n");
			return 0;
		}
		lw_busy = 0;
		do
		{
			(void)*((volatile u32 *)0xBFC00000);
			lw_busy -= 1;
		} while ( lw_busy > 0 );
	}
	return -1;
}

int initHcdStructs(void)
{
	int memSize;
	void *memBuf_1;
	HcCA *hcCommArea;
	UsbdHcIsoTD_t *hcIsoTdBuf;
	UsbdHcTD_t *hcTdBuf;
	int i;
	UsbdHcED_t *hcEdBuf;
	UsbdHcED_t *hcEdBuf2;
	UsbdEndpoint_t *endpointBuf;
	UsbdDevice_t *deviceTreeBuf;
	UsbdIoRequest_t *ioReqBuf;
	UsbdIoRequest_t **hcIsoTdToIoReqLUT;
	UsbdIoRequest_t **hcTdToIoReqLUT;
	UsbdIoRequest_t **devDescBuf;
	volatile OhciRegs *ohciRegs;

	ohciRegs = (volatile OhciRegs *)OHCI_REG_BASE;
	if ( initHardware(ohciRegs) < 0 )
		return -1;
	*(vu32 *)0xBF801570 |= 0x8000000u;
	*(vu32 *)0xBF801680 = 1;
	dbg_printf("Structs...\n");
	memSize = 0 + 28 + sizeof(HcCA) + sizeof(UsbdHcIsoTD_t) * usbConfig.m_maxIsoTransfDesc
					+ sizeof(UsbdHcTD_t) * usbConfig.m_maxTransfDesc + sizeof(UsbdHcED_t) * usbConfig.m_maxEndpoints
					+ sizeof(UsbdHcED_t) * 66 + sizeof(UsbdEndpoint_t) * usbConfig.m_maxEndpoints
					+ sizeof(UsbdDevice_t) * usbConfig.m_maxDevices + sizeof(UsbdIoRequest_t) * usbConfig.m_maxIoReqs
					+ sizeof(UsbdIoRequest_t *) * usbConfig.m_maxIsoTransfDesc
					+ sizeof(UsbdIoRequest_t *) * usbConfig.m_maxTransfDesc
					+ usbConfig.m_maxStaticDescSize * usbConfig.m_maxDevices;
	memBuf_1 = AllocSysMemoryWrap(memSize);
	if ( !memBuf_1 )
		return -1;
	if ( ((uiptr)memBuf_1) & 0xFF )
	{
		FreeSysMemoryWrap(memBuf_1);
		return -1;
	}
	hcdMemoryBuffer = memBuf_1;
	hcCommArea = (HcCA *)memBuf_1;
	bzero(memBuf_1, memSize);
	hcIsoTdBuf = (UsbdHcIsoTD_t *)(((unsigned int)memBuf_1 + (28 + sizeof(HcCA) - 1)) & 0xFFFFFFE0);
	*(UsbdConfig_t **)((u8 *)hcIsoTdBuf - 28) = &usbConfig;
	hcTdBuf = (UsbdHcTD_t *)&hcIsoTdBuf[usbConfig.m_maxIsoTransfDesc];
	hcEdBuf = (UsbdHcED_t *)&hcTdBuf[usbConfig.m_maxTransfDesc];
	hcEdBuf2 = (UsbdHcED_t *)&hcEdBuf[usbConfig.m_maxEndpoints];
	memPool = (UsbdMemoryPool_t *)&hcEdBuf2[66];
	memPool_unused = memPool;
	endpointBuf = (UsbdEndpoint_t *)&memPool[1];
	deviceTreeBuf = (UsbdDevice_t *)&endpointBuf[usbConfig.m_maxEndpoints];
	ioReqBuf = (UsbdIoRequest_t *)&deviceTreeBuf[usbConfig.m_maxDevices];
	hcIsoTdToIoReqLUT = (UsbdIoRequest_t **)&ioReqBuf[usbConfig.m_maxIoReqs];
	hcTdToIoReqLUT = &hcIsoTdToIoReqLUT[usbConfig.m_maxIsoTransfDesc];
	devDescBuf = &hcTdToIoReqLUT[usbConfig.m_maxTransfDesc];
	usbConfig.m_allocatedSize_unused += memSize;
	memPool->m_ohciRegs = ohciRegs;
	memPool->m_hcEdBuf = hcEdBuf;
	memPool->m_hcIsoTdToIoReqLUT = hcIsoTdToIoReqLUT;
	memPool->m_hcTdToIoReqLUT = hcTdToIoReqLUT;
	memPool->m_endpointBuf = endpointBuf;
	memPool->m_hcHCCA = (volatile HcCA *)(((unsigned int)memBuf_1 & 0x1FFFFFFF) | 0xA0000000);
	for ( i = 0; i < usbConfig.m_maxEndpoints; i += 1 )
	{
		endpointBuf[i].m_id = i;
		endpointBuf[i].m_hcEd = &hcEdBuf[i];
		endpointBuf[i].m_prev = memPool->m_freeEpListEnd;
		if ( memPool->m_freeEpListEnd )
			memPool->m_freeEpListEnd->m_next = &endpointBuf[i];
		else
			memPool->m_freeEpListStart = &endpointBuf[i];
		endpointBuf[i].m_next = NULL;
		memPool->m_freeEpListEnd = &endpointBuf[i];
	}
	memPool->m_tdQueueEnd = NULL;
	memPool->m_tdQueueStart = NULL;
	memPool->m_deviceTreeBuf = deviceTreeBuf;
	for ( i = 0; i < usbConfig.m_maxDevices; i += 1 )
	{
		deviceTreeBuf[i].m_functionAddress = i;
		deviceTreeBuf[i].m_id = (u8)i;
		deviceTreeBuf[i].m_staticDeviceDescPtr = (char *)devDescBuf + (usbConfig.m_maxStaticDescSize * i);
		deviceTreeBuf[i].m_prev = memPool->m_freeDeviceListEnd;
		if ( memPool->m_freeDeviceListEnd )
			memPool->m_freeDeviceListEnd->m_next = &deviceTreeBuf[i];
		else
			memPool->m_freeDeviceListStart = &deviceTreeBuf[i];
		deviceTreeBuf[i].m_next = NULL;
		memPool->m_freeDeviceListEnd = &deviceTreeBuf[i];
	}
	memPool->m_deviceTreeRoot = attachChildDevice(NULL, 0);  // virtual root
	memPool->m_deviceTreeRoot->m_magicPowerValue = 2;
	attachChildDevice(memPool->m_deviceTreeRoot, 1u);  // root hub port 0
	attachChildDevice(memPool->m_deviceTreeRoot, 2u);  // root hub port 1
	memPool->m_ioReqBufPtr = ioReqBuf;
	for ( i = 0; i < usbConfig.m_maxIoReqs; i += 1 )
	{
		ioReqBuf[i].m_id = i;
		ioReqBuf[i].m_prev = memPool->m_freeIoReqListEnd;
		if ( memPool->m_freeIoReqListEnd )
			memPool->m_freeIoReqListEnd->m_next = &ioReqBuf[i];
		else
			memPool->m_freeIoReqList = &ioReqBuf[i];
		ioReqBuf[i].m_next = NULL;
		memPool->m_freeIoReqListEnd = &ioReqBuf[i];
	}
	memPool->m_freeHcTdList = hcTdBuf;
	memPool->m_hcTdBuf = hcTdBuf;
	memPool->m_hcTdBufEnd = &hcTdBuf[usbConfig.m_maxTransfDesc];
	for ( i = 0; i < usbConfig.m_maxTransfDesc - 1; i += 1 )
	{
		hcTdBuf[i].m_next = &hcTdBuf[i + 1];
	}
	memPool->m_freeHcIsoTdList = hcIsoTdBuf;
	memPool->m_hcIsoTdBuf = hcIsoTdBuf;
	memPool->m_hcIsoTdBufEnd = &hcIsoTdBuf[usbConfig.m_maxIsoTransfDesc];
	for ( i = 0; i < usbConfig.m_maxIsoTransfDesc - 1; i += 1 )
	{
		hcIsoTdBuf[i].m_next = &hcIsoTdBuf[i + 1];
	}
	// build tree for interrupt table
	for ( i = 0; i < 63; i += 1 )
	{
		int intrId;
		hcEdBuf2[i].m_hcArea.asu32 = HCED_SKIP;
		if ( i <= 0 )
			hcEdBuf2[i].m_next = NULL;
		else
			hcEdBuf2[i].m_next = &hcEdBuf2[(i - 1) >> 1];
		intrId = i - 31;
		if ( intrId >= 0 )
		{
			intrId = ((intrId & 1) << 4) + ((intrId & 2) << 2) + (intrId & 4) + ((intrId & 8) >> 2) + ((intrId & 0x10) >> 4);
			hcCommArea->InterruptTable[intrId] = &hcEdBuf2[i];
		}
	}
	hcEdBuf2[TYPE_CONTROL].m_hcArea.asu32 = HCED_SKIP;
	ohciRegs->HcControlHeadEd = &hcEdBuf2[TYPE_CONTROL];
	hcEdBuf2[TYPE_BULK].m_hcArea.asu32 = HCED_SKIP;
	ohciRegs->HcBulkHeadEd = &hcEdBuf2[TYPE_BULK];
	hcEdBuf2[TYPE_ISOCHRON].m_hcArea.asu32 = HCED_SKIP;
	hcEdBuf2[0].m_next = &hcEdBuf2[TYPE_ISOCHRON];  // the isochronous endpoint
	ohciRegs->HcHCCA = hcCommArea;
	ohciRegs->HcFmInterval = 0x27782EDF;
	ohciRegs->HcPeriodicStart = 0x2A2F;
	ohciRegs->HcInterruptEnable = OHCI_INT_SO | OHCI_INT_WDH | OHCI_INT_UE | OHCI_INT_FNO | OHCI_INT_RHSC | OHCI_INT_MIE;
	ohciRegs->HcControl |=
		OHCI_CTR_CBSR | OHCI_CTR_PLE | OHCI_CTR_IE | OHCI_CTR_CLE | OHCI_CTR_BLE | OHCI_CTR_USB_OPERATIONAL;
	return 0;
}

void deinitHcd(void)
{
	UsbdDevice_t *i;
	UsbdReportDescriptor_t *hidDescriptorStart;
	UsbdReportDescriptor_t *next;

	initHardware((OhciRegs *)OHCI_REG_BASE);
	for ( i = memPool->m_freeDeviceListStart; i; i = i->m_next )
	{
		for ( hidDescriptorStart = i->m_reportDescriptorStart, next = hidDescriptorStart; next; hidDescriptorStart = next )
		{
			next = hidDescriptorStart->m_next;
			FreeSysMemoryWrap(hidDescriptorStart);
		}
	}
	FreeSysMemoryWrap(hcdMemoryBuffer);
}

// usbd_sys.c

void *AllocSysMemoryWrap(int size)
{
	void *ptr;
	int state;

	CpuSuspendIntr(&state);
	ptr = AllocSysMemory(ALLOC_FIRST, size, NULL);
	CpuResumeIntr(state);
	return ptr;
}

int FreeSysMemoryWrap(void *ptr)
{
	int res;
	int state;

	CpuSuspendIntr(&state);
	res = FreeSysMemory(ptr);
	CpuResumeIntr(state);
	return res;
}

int usbdLock(void)
{
	return WaitSema(usbKernelResources.m_usbdSema);
}

int usbdUnlock(void)
{
	return SignalSema(usbKernelResources.m_usbdSema);
}

// usbd_api.c

int sceUsbdRegisterLdd(sceUsbdLddOps *driver)
{
	void *old_gp;
	int res;

	old_gp = SetModuleGP();
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return USB_RC_BADCONTEXT;
	}
	res = doRegisterDriver(driver, old_gp);
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

int sceUsbdRegisterAutoloader(sceUsbdLddOps *drv)
{
	void *old_gp;
	int res;

	old_gp = SetModuleGP();
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return USB_RC_BADCONTEXT;
	}
	res = doRegisterAutoLoader(drv, old_gp);
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

int sceUsbdUnregisterLdd(sceUsbdLddOps *driver)
{
	void *old_gp;
	int res;

	old_gp = SetModuleGP();
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return USB_RC_BADCONTEXT;
	}
	res = doUnregisterDriver(driver);
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

int sceUsbdUnregisterAutoloader(void)
{
	void *old_gp;
	int res;

	old_gp = SetModuleGP();
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return USB_RC_BADCONTEXT;
	}
	res = doUnregisterAutoLoader();
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

void *sceUsbdScanStaticDescriptor(int devId, void *data, u8 type)
{
	void *old_gp;
	const UsbdDevice_t *dev;
	void *res;

	old_gp = SetModuleGP();
	res = NULL;
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return NULL;
	}
	dev = fetchDeviceById(devId);
	if ( dev && dev->m_deviceStatus == DEVICE_READY )
		res = doGetDeviceStaticDescriptor(devId, data, type);
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

int sceUsbdGetDeviceLocation(int devId, u8 *path)
{
	void *old_gp;
	int res;
	UsbdDevice_t *dev;

	old_gp = SetModuleGP();
	res = USB_RC_BADDEV;
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return USB_RC_BADCONTEXT;
	}
	dev = fetchDeviceById(devId);
	if ( dev && dev->m_deviceStatus == DEVICE_READY )
		res = doGetDeviceLocation(dev, path);
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

int sceUsbdSetPrivateData(int devId, void *data)
{
	void *old_gp;
	int res;
	UsbdDevice_t *dev;

	old_gp = SetModuleGP();
	res = USB_RC_BADDEV;
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return USB_RC_BADCONTEXT;
	}
	dev = fetchDeviceById(devId);
	if ( dev )
	{
		dev->m_privDataField = data;
		res = USB_RC_OK;
	}
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

void *sceUsbdGetPrivateData(int devId)
{
	void *old_gp;
	void *res;
	UsbdDevice_t *dev;

	old_gp = SetModuleGP();
	res = NULL;
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return NULL;
	}
	dev = fetchDeviceById(devId);
	if ( dev )
		res = dev->m_privDataField;
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

int sceUsbdOpenPipe(int devId, UsbEndpointDescriptor *desc)
{
	void *old_gp;
	UsbdDevice_t *dev;
	int res;
	const UsbdEndpoint_t *ep;

	old_gp = SetModuleGP();
	res = -1;
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return -1;
	}
	ep = NULL;
	dev = fetchDeviceById(devId);
	if ( dev )
		ep = doOpenEndpoint(dev, desc, 0);
	if ( ep )
		res = ep->m_id;
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

int sceUsbdOpenPipeAligned(int devId, UsbEndpointDescriptor *desc)
{
	void *old_gp;
	UsbdDevice_t *dev;
	int res;
	const UsbdEndpoint_t *ep;

	old_gp = SetModuleGP();
	res = -1;
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return -1;
	}
	ep = NULL;
	dev = fetchDeviceById(devId);
	if ( dev )
		ep = doOpenEndpoint(dev, desc, 1u);
	if ( ep )
		res = ep->m_id;
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

int sceUsbdClosePipe(int id)
{
	void *old_gp;
	UsbdEndpoint_t *ep;
	int res;

	old_gp = SetModuleGP();
	res = USB_RC_BADPIPE;
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return USB_RC_BADCONTEXT;
	}
	ep = fetchEndpointById(id);
	if ( ep )
		res = doCloseEndpoint(ep);
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

void signalCallbackThreadFunc(UsbdIoRequest_t *req)
{
	int state;

	CpuSuspendIntr(&state);
	req->m_prev = cbListEnd;
	if ( !cbListEnd )
		cbListStart = req;
	else
		cbListEnd->m_next = req;
	req->m_next = NULL;
	cbListEnd = req;
	CpuResumeIntr(state);
	SetEventFlag(usbKernelResources.m_callbackEvent, 1u);
}

int usbdTransferPipeImpl(
	void *gp_val,
	int id,
	void *data,
	u32 length,
	UsbDeviceRequest *option,
	void *callback,
	void *cbArg,
	sceUsbdMultiIsochronousRequest *request)
{
	int res;
	UsbdEndpoint_t *ep;
	int bNumPackets;
	UsbdIoRequest_t *req;

	if ( usbdLock() )
		return USB_RC_BADCONTEXT;
	res = USB_RC_OK;
	ep = fetchEndpointById(id);
	if ( !ep )
	{
		dbg_printf("sceUsbdTransferPipe: UsbdEndpoint_t %d not found\n", id);
		res = USB_RC_BADPIPE;
	}
	bNumPackets = 0;
	if ( request && res == USB_RC_OK )
	{
		bNumPackets = request->bNumPackets;
		data = request->bBufStart;
	}
	if ( request && res == USB_RC_OK )
	{
		if ( (unsigned int)(bNumPackets - 1) >= 8 || !data )
		{
			res = USB_RC_BADLENGTH;
		}
	}
	if ( (request || (data && (int)length > 0)) && res == USB_RC_OK )
	{
		if ( ep->m_alignFlag && ((uiptr)data & 3) != 0 )
		{
			res = USB_RC_BADALIGN;
		}
	}
	if ( request && res == USB_RC_OK )
	{
		if ( ep->m_endpointType != TYPE_ISOCHRON )
		{
			res = USB_RC_BADPIPE;
		}
	}
	if ( request && res == USB_RC_OK )
	{
		int i_pkt;

		length = 0;
		for ( i_pkt = 0; i_pkt < bNumPackets; i_pkt += 1 )
		{
			if ( (ep->m_hcEd->m_hcArea.stru.m_maxPacketSize & 0x7FFu) < request->Packets[i_pkt].bLength )
			{
				res = USB_RC_BADLENGTH;
				break;
			}
			length += request->Packets[i_pkt].bLength;
			if ( ep->m_alignFlag && (((((uiptr)data) & 0xFF) + (length & 0xFF)) & 3) != 0 )
			{
				res = USB_RC_BADALIGN;
				break;
			}
		}
	}
	if ( (request || (data && (int)length > 0)) && res == USB_RC_OK )
	{
		if ( (((unsigned int)data + length - 1) >> 12) - ((unsigned int)data >> 12) >= 2 )
		{
			res = USB_RC_BADLENGTH;
		}
	}
	if ( (!request && (data && (int)length > 0)) && res == USB_RC_OK )
	{
		switch ( ep->m_endpointType )
		{
			case TYPE_CONTROL:
			{
				if ( ((uiptr)data & 3) != 0 && (option->requesttype & 0x80) == 0 )
				{
					if ( (ep->m_hcEd->m_hcArea.stru.m_maxPacketSize & 0x7FF) == 64 && (int)length >= 63 )
					{
						res = USB_RC_BADALIGN;
					}
				}
				break;
			}
			case TYPE_ISOCHRON:
			{
				if ( (ep->m_hcEd->m_hcArea.stru.m_maxPacketSize & 0x7FFu) < length )
				{
					res = USB_RC_BADLENGTH;
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}
	if ( res == USB_RC_OK )
	{
		req = allocIoRequest();
		if ( !req )
		{
			dbg_printf("Ran out of IoReqs\n");
			res = USB_RC_IOREQ;
		}
	}
	if ( res == USB_RC_OK )
	{
		req->m_userCallbackArg = cbArg;
		req->m_gpSeg = gp_val;
		req->m_req.bNumPackets = 0;
		req->m_userCallbackProc = callback;
		switch ( ep->m_endpointType )
		{
			case TYPE_ISOCHRON:
			{
				if ( request )
				{
					req->m_waitFrames = request->bRelStartFrame;
					memcpy(&(req->m_req), request, sizeof(sceUsbdMultiIsochronousRequest));
				}
				else
				{
					req->m_waitFrames = (u32)option;
				}
				res = attachIoReqToEndpoint(ep, req, data, length, signalCallbackThreadFunc);
				break;
			}
			case TYPE_CONTROL:
			{
				if ( !option )
				{
					freeIoRequest(req);
					res = USB_RC_BADOPTION;
				}
				if ( res == USB_RC_OK )
				{
					if ( option->length != length )
					{
						freeIoRequest(req);
						res = USB_RC_BADLENGTH;
					}
				}
				if ( res == USB_RC_OK )
				{
					res = doControlTransfer(
						ep,
						req,
						option->requesttype,
						option->request,
						option->value,
						option->index,
						option->length,
						data,
						signalCallbackThreadFunc);
				}
				break;
			}
			default:
			{
				res = attachIoReqToEndpoint(ep, req, data, length, signalCallbackThreadFunc);
				break;
			}
		}
	}
	usbdUnlock();
	return res;
}

int sceUsbdTransferPipe(int id, void *data, u32 len, void *option, sceUsbdDoneCallback callback, void *cbArg)
{
	void *old_gp;
	int res;

	old_gp = SetModuleGP();
	res = usbdTransferPipeImpl(old_gp, id, data, len, (UsbDeviceRequest *)option, callback, cbArg, NULL);
	SetGP(old_gp);
	return res;
}

int sceUsbdMultiIsochronousTransfer(
	int pipeId, sceUsbdMultiIsochronousRequest *request, sceUsbdMultiIsochronousDoneCallback callback, void *cbArg)
{
	void *old_gp;
	int res;

	old_gp = SetModuleGP();
	res = usbdTransferPipeImpl(old_gp, pipeId, NULL, 0, NULL, callback, cbArg, request);
	SetGP(old_gp);
	return res;
}

int sceUsbdChangeThreadPriority(int prio1, int prio2)
{
	void *old_gp;
	int res;

	old_gp = SetModuleGP();
	res = 0;
	if ( usbConfig.m_hcdThreadPrio != prio1 )
	{
		usbConfig.m_hcdThreadPrio = prio1;
		res = ChangeThreadPriority(usbKernelResources.m_hcdTid, prio1);
	}
	if ( res == 0 && usbConfig.m_cbThreadPrio != prio2 )
	{
		usbConfig.m_cbThreadPrio = prio2;
		res = ChangeThreadPriority(usbKernelResources.m_callbackTid, prio2);
	}
	SetGP(old_gp);
	return res;
}

int sceUsbdGetReportDescriptor(int devId, int cfgNum, int ifNum, void **desc, u32 *len)
{
	void *old_gp;
	int res;
	UsbdDevice_t *dev;
	UsbdReportDescriptor_t *hidDescriptorStart;

	old_gp = SetModuleGP();
	res = USB_RC_BADDEV;
	if ( usbdLock() )
	{
		SetGP(old_gp);
		return USB_RC_BADCONTEXT;
	}
	hidDescriptorStart = NULL;
	dev = fetchDeviceById(devId);
	if ( dev )
	{
		res = USB_RC_UNKNOWN;
		for ( hidDescriptorStart = dev->m_reportDescriptorStart;
					hidDescriptorStart
					&& ((int)hidDescriptorStart->m_cfgNum != cfgNum || (int)hidDescriptorStart->m_ifNum != ifNum);
					hidDescriptorStart = hidDescriptorStart->m_next )
		{
		}
	}
	if ( hidDescriptorStart )
	{
		res = USB_RC_OK;
		if ( desc )
			*desc = hidDescriptorStart->m_data;
		if ( len )
			*len = hidDescriptorStart->m_length;
	}
	usbdUnlock();
	SetGP(old_gp);
	return res;
}

// usbd_main.c

int usbdIntrHandler(void *arg)
{
	const UsbdKernelResources_t *kernelResources;

	kernelResources = (UsbdKernelResources_t *)arg;
	iSetEventFlag(kernelResources->m_hcdIrqEvent, 1u);
	return 0;
}

void hcdIrqThread(void *arg)
{
	u32 efres;

	(void)arg;
	while ( 1 )
	{
		WaitEventFlag(usbKernelResources.m_hcdIrqEvent, 1u, WEF_OR | WEF_CLEAR, &efres);
		usbdLock();
		hcdProcessIntr();
		EnableIntr(IOP_IRQ_USB);
		PostIntrEnableFunction();
		usbdUnlock();
	}
}

void callbackThreadFunc(void *arg)
{
	UsbdIoRequest_t *req;
	UsbdIoRequest_t reqCopy;
	u32 efres;
	int state;

	(void)arg;
	while ( 1 )
	{
		WaitEventFlag(usbKernelResources.m_callbackEvent, 1u, WEF_OR | WEF_CLEAR, &efres);
		while ( 1 )
		{
			CpuSuspendIntr(&state);
			req = cbListStart;
			if ( req )
			{
				if ( req->m_next )
					req->m_next->m_prev = req->m_prev;
				else
					cbListEnd = req->m_prev;
				if ( req->m_prev )
					req->m_prev->m_next = req->m_next;
				else
					req = req->m_next;
			}
			CpuResumeIntr(state);
			if ( !req )
				break;
			bcopy(req, &reqCopy, sizeof(UsbdIoRequest_t));
			usbdLock();
			freeIoRequest(req);
			usbdUnlock();
			if ( reqCopy.m_userCallbackProc )
			{
				SetGP(reqCopy.m_gpSeg);
				if ( reqCopy.m_req.bNumPackets )
					reqCopy.m_userCallbackProcMultiIsochronous(reqCopy.m_resultCode, &reqCopy.m_req, reqCopy.m_userCallbackArg);
				else
					reqCopy.m_userCallbackProcRegular(reqCopy.m_resultCode, reqCopy.m_transferedBytes, reqCopy.m_userCallbackArg);
				SetGP(_gp);
			}
		}
	}
}

void usbdReboot(int ac)
{
	if ( (unsigned int)ac < 2 )
		usbdRebootInner();
}

static void ParseOptionInput(const UsbdArgOption_t *option, const char *arguments)
{
	int value_1;
	const char *p_1;
	int value_2;
	const char *p_2;

	value_1 = 0;
	for ( p_1 = arguments; *p_1 && *p_1 != ','; p_1 += 1 )
	{
		if ( (unsigned int)(*p_1 - '0') >= 9 )
			return;
		value_1 = 10 * value_1 + (*p_1 - '0');
	}
	if ( option->value2 ? (*p_1 != ',') : (*p_1 == ',') )
		return;
	if ( arguments < p_1 )
		*option->value = value_1;
	if ( !option->value2 )
	{
		return;
	}
	value_2 = 0;
	for ( p_2 = p_1 + 1; *p_2; p_2 += 1 )
	{
		if ( (unsigned int)(*p_2 - '0') >= 9 )
			return;
		value_2 = 10 * value_2 + (*p_2 - '0');
	}
	if ( p_1 + 1 < p_2 )
		*option->value2 = value_2;
}

int _start(int ac, char **av)
{
	int i;
	UsbdArgOption_t *args_ptr;
	const char *pParam;
	char *pArgs;
	iop_event_t ef;
	iop_thread_t thparam;
	iop_sema_t sema;
	int intrstate;

	if ( ac < 0 )
		return usbdModuleUnload();
	for ( i = 1; i < ac; i += 1 )
	{
		for ( args_ptr = SupportedArgs; args_ptr->param; args_ptr += 1 )
		{
			for ( pParam = args_ptr->param, pArgs = av[i]; *pParam && *pParam == *pArgs; pParam += 1, pArgs += 1 )
			{
			}
			if ( !*pParam )
			{
				ParseOptionInput(args_ptr, pArgs);
				break;
			}
		}
	}
	dbg_printf("Intr handler...\n");
	DisableIntr(IOP_IRQ_USB, &intrstate);
	if ( RegisterIntrHandler(IOP_IRQ_USB, 1, usbdIntrHandler, &usbKernelResources) )
	{
		if ( intrstate == IOP_IRQ_USB )
		{
			EnableIntr(IOP_IRQ_USB);
			return MODULE_NO_RESIDENT_END;
		}
	}
	else
	{
		dbg_printf("library entries...\n");
		if ( !RegisterLibraryEntries(&_exp_usbd) )
		{
			dbg_printf("Threads and events...\n");

			sema.attr = SA_THPRI;
			sema.initial = 1;
			sema.max = 1;
			sema.option = 0;
			usbKernelResources.m_usbdSema = CreateSema(&sema);
			if ( usbKernelResources.m_usbdSema >= 0 )
			{
				ef.attr = EA_SINGLE;
				ef.option = 0;
				ef.bits = 0;
				usbKernelResources.m_hcdIrqEvent = CreateEventFlag(&ef);
				if ( usbKernelResources.m_hcdIrqEvent >= 0 )
				{
					dbg_printf("HCD thread...\n");
					thparam.attr = TH_C;
					thparam.thread = hcdIrqThread;
#ifndef MINI_DRIVER
					thparam.stacksize = 0x4000;  // 16KiB
#else
					thparam.stacksize = 0x0800;  //  2KiB
#endif
					thparam.option = 0;
					thparam.priority = usbConfig.m_hcdThreadPrio;
					usbKernelResources.m_hcdTid = CreateThread(&thparam);
					if ( usbKernelResources.m_hcdTid >= 0 && !StartThread(usbKernelResources.m_hcdTid, NULL) )
					{
						ef.attr = EA_SINGLE;
						ef.option = 0;
						ef.bits = 0;
						usbKernelResources.m_callbackEvent = CreateEventFlag(&ef);
						if ( usbKernelResources.m_callbackEvent >= 0 )
						{
							dbg_printf("Callback thread...\n");
							thparam.attr = TH_C;
							thparam.thread = callbackThreadFunc;
#ifndef MINI_DRIVER
							thparam.stacksize = 0x4000;  // 16KiB
#else
							thparam.stacksize = 0x0800;  //  2KiB
#endif
							thparam.option = 0;
							thparam.priority = usbConfig.m_cbThreadPrio;
							usbKernelResources.m_callbackTid = CreateThread(&thparam);
							if (
								usbKernelResources.m_callbackTid >= 0 && !StartThread(usbKernelResources.m_callbackTid, NULL)
								&& usbdInitInner() >= 0 )
							{
								dbg_printf("Enabling interrupts...\n");
								EnableIntr(IOP_IRQ_USB);
								dbg_printf("Init done\n");
								return MODULE_REMOVABLE_END;
							}
						}
					}
				}
			}
		}
		else
		{
			dbg_printf("RegisterLibraryEntries failed\n");
		}
		if ( usbKernelResources.m_callbackTid > 0 )
			DeleteThread(usbKernelResources.m_callbackTid);
		if ( usbKernelResources.m_callbackEvent > 0 )
			DeleteEventFlag(usbKernelResources.m_callbackEvent);
		if ( usbKernelResources.m_hcdTid > 0 )
			DeleteThread(usbKernelResources.m_hcdTid);
		if ( usbKernelResources.m_hcdIrqEvent > 0 )
			DeleteEventFlag(usbKernelResources.m_hcdIrqEvent);
		if ( usbKernelResources.m_usbdSema > 0 )
			DeleteSema(usbKernelResources.m_usbdSema);
		ReleaseIntrHandler(IOP_IRQ_USB);
	}
	return MODULE_NO_RESIDENT_END;
}

int usbdModuleUnload(void)
{
	int intrstate;

	if ( ReleaseLibraryEntries(&_exp_usbd) == 0 )
	{
		return MODULE_REMOVABLE_END;
	}
	DisableIntr(IOP_IRQ_USB, &intrstate);
	ReleaseIntrHandler(IOP_IRQ_USB);
	TerminateThread(usbKernelResources.m_hcdTid);
	TerminateThread(usbKernelResources.m_callbackTid);
	DeleteThread(usbKernelResources.m_hcdTid);
	DeleteThread(usbKernelResources.m_callbackTid);
	DeleteEventFlag(usbKernelResources.m_hcdIrqEvent);
	DeleteEventFlag(usbKernelResources.m_callbackEvent);
	DeleteSema(usbKernelResources.m_usbdSema);
	deinitHcd();
	deinitHubDriver();
	return MODULE_NO_RESIDENT_END;
}

// report_descriptor_init.c

int handleStaticDeviceDescriptor(UsbdDevice_t *dev, UsbDeviceDescriptor *devDescStart, UsbDeviceDescriptor *devDescEnd)
{
	UsbDeviceDescriptor *devDescCur;
	u32 ifNum;
	unsigned int bLength;
	int i;
	u32 wItemLength;
	UsbdReportDescriptor_t *hidDescriptor;
	int state;
	u32 cfgNum;
	UsbHidDescriptor *usbHidDescriptor;
	const UsbConfigDescriptor *usbConfigDescriptor;
	const UsbInterfaceDescriptor *usbInterfaceDescriptor;

	dev->m_reportDescriptorStart = NULL;
	dev->m_reportDescriptorEnd = NULL;
	cfgNum = 0;
	ifNum = 0;
	for ( devDescCur = devDescStart; devDescCur < devDescEnd;
				devDescCur = (UsbDeviceDescriptor *)((char *)devDescCur + bLength) )
	{
		bLength = devDescCur->bLength;
		if ( bLength < 2 )
			break;
		if ( (char *)devDescEnd - (char *)devDescCur < (int)bLength )
			break;
		switch ( devDescCur->bDescriptorType )
		{
			case 1u:
			case 3u:
			case 5u:
			case 6u:
			case 7u:
			case 8u:
			case 9u:
			case 0xAu:
			case 0xBu:
			case 0xCu:
			case 0xDu:
			case 0xEu:
			case 0xFu:
			case 0x10u:
			case 0x11u:
			case 0x12u:
			case 0x13u:
			case 0x14u:
			case 0x15u:
			case 0x16u:
			case 0x17u:
			case 0x18u:
			case 0x19u:
			case 0x1Au:
			case 0x1Bu:
			case 0x1Cu:
			case 0x1Du:
			case 0x1Eu:
			case 0x1Fu:
			case 0x20u:
				break;
			case 2u:
				if ( (int)bLength >= 9 )
				{
					usbConfigDescriptor = (UsbConfigDescriptor *)devDescCur;
					cfgNum = usbConfigDescriptor->bConfigurationValue;
				}
				break;
			case 4u:
				if ( (int)bLength >= 9 )
				{
					usbInterfaceDescriptor = (UsbInterfaceDescriptor *)devDescCur;
					ifNum = usbInterfaceDescriptor->bInterfaceNumber;
				}
				break;
			case 0x21u:
				usbHidDescriptor = (UsbHidDescriptor *)devDescCur;
				for ( i = 0; i < usbHidDescriptor->bNumDescriptors; i += 1 )
				{
					if ( usbHidDescriptor->items[i].bDescriptorType == 0x22 )
					{
						wItemLength =
							usbHidDescriptor->items[i].wDescriptorLengthLb + (usbHidDescriptor->items[i].wDescriptorLengthHb << 8);
						CpuSuspendIntr(&state);
						hidDescriptor =
							(UsbdReportDescriptor_t *)AllocSysMemory(ALLOC_FIRST, wItemLength + sizeof(UsbdReportDescriptor_t), NULL);
						CpuResumeIntr(state);
						hidDescriptor->m_ifNum = ifNum;
						hidDescriptor->m_length = wItemLength;
						hidDescriptor->m_cfgNum = cfgNum;
						hidDescriptor->m_prev = dev->m_reportDescriptorEnd;
						if ( dev->m_reportDescriptorEnd )
							dev->m_reportDescriptorEnd->m_next = hidDescriptor;
						else
							dev->m_reportDescriptorStart = hidDescriptor;
						hidDescriptor->m_next = NULL;
						dev->m_reportDescriptorEnd = hidDescriptor;
					}
				}
				break;
			default:
				break;
		}
	}
	return 0;
}

// device_driver.c

int callUsbDriverFunc(int (*func)(int devId), int devId, void *gpSeg)
{
	int res;

	if ( !func )
		return 0;
	usbdUnlock();
	SetGP(gpSeg);
	res = func(devId);
	SetGP(_gp);
	usbdLock();
	return res;
}

void probeDeviceTree(UsbdDevice_t *tree, sceUsbdLddOps *drv)
{
	UsbdDevice_t *curDevice;

	for ( curDevice = tree->m_childListStart; curDevice; curDevice = curDevice->m_next )
	{
		if ( curDevice->m_deviceStatus == DEVICE_READY )
		{
			if ( curDevice->m_devDriver )
			{
				if ( curDevice->m_childListStart )
					probeDeviceTree(curDevice, drv);
			}
			else
			{
				curDevice->m_privDataField = NULL;
				if ( callUsbDriverFunc(drv->probe, curDevice->m_id, drv->gp) )
				{
					curDevice->m_devDriver = drv;
					callUsbDriverFunc(drv->connect, curDevice->m_id, drv->gp);
				}
			}
		}
	}
}

int doRegisterDriver(sceUsbdLddOps *drv, void *drvGpSeg)
{
	if ( drv->next || drv->prev || !drv->name || drv->reserved1 || drv->reserved2 )
	{
		return USB_RC_BADDRIVER;
	}
	if ( drvListStart == drv )
	{
		return USB_RC_BUSY;
	}
	drv->gp = drvGpSeg;
	drv->prev = drvListEnd;
	if ( drvListEnd )
		drvListEnd->next = drv;
	else
		drvListStart = drv;
	drv->next = NULL;
	drvListEnd = drv;
	if ( drv->probe )
	{
		probeDeviceTree(getDeviceTreeRoot(), drv);
	}
	return USB_RC_OK;
}

int doRegisterAutoLoader(sceUsbdLddOps *drv, void *drvGpSeg)
{
	if ( drv->next || drv->prev || !drv->name || drv->reserved1 || drv->reserved2 )
	{
		return USB_RC_BADDRIVER;
	}
	if ( drvAutoLoader )
	{
		return USB_RC_BUSY;
	}
	drv->gp = drvGpSeg;
	drvAutoLoader = drv;
	if ( drv->probe )
	{
		probeDeviceTree(getDeviceTreeRoot(), drv);
	}
	return USB_RC_OK;
}

void disconnectDriver(UsbdDevice_t *tree, sceUsbdLddOps *drv)
{
	UsbdEndpoint_t *ep;
	UsbdEndpoint_t *nextEp;
	UsbdDevice_t *tree_tmp1;

	if ( drv == tree->m_devDriver )
	{
		if ( tree->m_endpointListStart )
		{
			ep = tree->m_endpointListStart->m_next;
			for ( nextEp = ep; nextEp; ep = nextEp )
			{
				nextEp = ep->m_next;
				removeEndpointFromDevice(tree, ep);
			}
		}
		tree->m_devDriver = NULL;
		tree->m_privDataField = NULL;
	}
	for ( tree_tmp1 = tree->m_childListStart; tree_tmp1; tree_tmp1 = tree_tmp1->m_next )
	{
		disconnectDriver(tree_tmp1, drv);
	}
}

int doUnregisterDriver(sceUsbdLddOps *drv)
{
	sceUsbdLddOps *pos;

	for ( pos = drvListStart; pos && pos != drv; pos = pos->next )
	{
	}
	if ( !pos )
		return USB_RC_BADDRIVER;
	if ( drv->next )
		drv->next->prev = drv->prev;
	else
		drvListEnd = drv->prev;
	if ( drv->prev )
		drv->prev->next = drv->next;
	else
		drvListStart = drv->next;
	disconnectDriver(getDeviceTreeRoot(), drv);
	return USB_RC_OK;
}

int doUnregisterAutoLoader(void)
{
	drvAutoLoader = NULL;
	return USB_RC_OK;
}

// device.c

void *doGetDeviceStaticDescriptor(int devId, void *data, u8 type)
{
	UsbdDevice_t *dev;
	UsbDeviceDescriptor *descBuf;

	dev = fetchDeviceById(devId);
	if ( !dev )
	{
		return NULL;
	}
	descBuf =
		data ? (UsbDeviceDescriptor *)((char *)data + *(u8 *)data) : (UsbDeviceDescriptor *)dev->m_staticDeviceDescPtr;
	for ( ; descBuf->bLength >= 2u && (u8 *)descBuf < (u8 *)dev->m_staticDeviceDescEndPtr;
				descBuf = (UsbDeviceDescriptor *)((char *)descBuf + descBuf->bLength) )
	{
		if ( !type || descBuf->bDescriptorType == type )
			return descBuf;
	}
	return NULL;
}

int doGetDeviceLocation(UsbdDevice_t *dev, u8 *path)
{
	const UsbdDevice_t *deviceTreeRoot;
	int count;
	int cpCount;
	u8 tmpPath[16];

	deviceTreeRoot = getDeviceTreeRoot();
	for ( count = 0; dev != deviceTreeRoot && count < 6; dev = dev->m_parent, count += 1 )
	{
		tmpPath[count] = dev->m_attachedToPortNo;
	}
	if ( dev != deviceTreeRoot )
		return USB_RC_BADHUBDEPTH;
	if ( count >= 6 )
		return USB_RC_BADHUBDEPTH;
	for ( cpCount = 0; cpCount < 7; cpCount += 1 )
	{
		if ( cpCount < count )
			path[cpCount] = tmpPath[count - cpCount - 1];
		else
			path[cpCount] = 0;
	}
	return USB_RC_OK;
}

UsbdEndpoint_t *doOpenEndpoint(UsbdDevice_t *dev, const UsbEndpointDescriptor *endpDesc, u32 alignFlag)
{
	if ( !dev->m_parent )
	{
		return NULL;
	}
	if ( !endpDesc )
		return dev->m_endpointListStart;  // default control EP was already opened
	return openDeviceEndpoint(dev, endpDesc, alignFlag);
}

int doCloseEndpoint(UsbdEndpoint_t *ep)
{
	if ( ep->m_correspDevice->m_endpointListStart == ep )
		return 0;
	return removeEndpointFromDevice(ep->m_correspDevice, ep);
}

int attachIoReqToEndpoint(UsbdEndpoint_t *ep, UsbdIoRequest_t *req, void *destdata, u16 length, void *callback)
{
	if ( !ep->m_correspDevice )
	{
		return USB_RC_BUSY;
	}
	if ( req->m_busyFlag )
	{
		return USB_RC_BUSY;
	}
	req->m_busyFlag = 1;
	req->m_correspEndpoint = ep;
	req->m_destPtr = destdata;
	req->m_length = length;
	req->m_resultCode = USB_RC_OK;
	req->m_callbackProc = (InternCallback)callback;
	req->m_prev = ep->m_ioReqListEnd;
	if ( ep->m_ioReqListEnd )
		ep->m_ioReqListEnd->m_next = req;
	else
		ep->m_ioReqListStart = req;
	req->m_next = NULL;
	ep->m_ioReqListEnd = req;
	handleIoReqList(ep);
	return USB_RC_OK;
}

int doControlTransfer(
	UsbdEndpoint_t *ep,
	UsbdIoRequest_t *req,
	u8 requestType,
	u8 request,
	u16 value,
	u16 index,
	u16 length,
	void *destdata,
	void *callback)
{
	if ( req->m_busyFlag )
	{
		dbg_printf("ERROR: doControlTransfer: IoReq busy\n");
		return USB_RC_BUSY;
	}
	req->m_devReq.requesttype = requestType;
	req->m_devReq.request = request;
	req->m_devReq.value = value;
	req->m_devReq.index = index;
	req->m_devReq.length = length;
	return attachIoReqToEndpoint(ep, req, destdata, length, callback);
}

void connectNewDevice(UsbdDevice_t *dev)
{
	sceUsbdLddOps *drv;

	dbg_printf("searching driver for dev %d, FA %02X\n", dev->m_id, dev->m_functionAddress);
	dev->m_deviceStatus = DEVICE_READY;
	for ( drv = drvListStart; drv; drv = drv->next )
	{
		dev->m_privDataField = NULL;
		if ( callUsbDriverFunc(drv->probe, dev->m_id, drv->gp) )
		{
			dev->m_devDriver = drv;
			dbg_printf("Driver found (%s)\n", drv->name);
			callUsbDriverFunc(drv->connect, dev->m_id, drv->gp);
			return;
		}
	}
	// No driver found yet. Call autoloader.
	drv = drvAutoLoader;
	if ( drv )
	{
		dev->m_privDataField = NULL;
		if ( callUsbDriverFunc(drv->probe, dev->m_id, drv->gp) )
		{
			dev->m_devDriver = drv;
			dbg_printf("(autoloader) Driver found (%s)\n", drv->name);
			callUsbDriverFunc(drv->connect, dev->m_id, drv->gp);
			return;
		}
	}
	dbg_printf("no driver found\n");
}

void fetchNextReportDescriptorCB(UsbdIoRequest_t *req)
{
	req->m_correspEndpoint->m_correspDevice->m_reportDescriptorCurForFetch =
		req->m_correspEndpoint->m_correspDevice->m_reportDescriptorCurForFetch->m_next;
	if ( req->m_correspEndpoint->m_correspDevice->m_reportDescriptorCurForFetch )
		fetchNextReportDescriptor(req);
	else
		connectNewDevice(req->m_correspEndpoint->m_correspDevice);
}

void fetchNextReportDescriptor(UsbdIoRequest_t *req)
{
	doControlTransfer(
		req->m_correspEndpoint,
		&req->m_correspEndpoint->m_correspDevice->m_ioRequest,
		USB_DIR_IN | USB_RECIP_INTERFACE,
		6u,
		0x2200u,
		req->m_correspEndpoint->m_correspDevice->m_reportDescriptorCurForFetch->m_ifNum,
		req->m_correspEndpoint->m_correspDevice->m_reportDescriptorCurForFetch->m_length,
		req->m_correspEndpoint->m_correspDevice->m_reportDescriptorCurForFetch->m_data,
		fetchNextReportDescriptorCB);
}

void killDevice(UsbdDevice_t *dev, UsbdEndpoint_t *ep)
{
	removeEndpointFromDevice(dev, ep);
	checkDelayedResets(dev);
	hubResetDevice(dev);
}

void fetchConfigDescriptors(UsbdIoRequest_t *req)
{
	UsbdDevice_t *dev;
	const UsbDeviceDescriptor *staticDeviceDescPtr;
	int fetchDescriptorCounter;
	u32 fetchDesc_1;
	int fetchDesc_2;
	int curDescNum_1;
	UsbConfigDescriptor *destdata;
	int readLen;

	dev = req->m_correspEndpoint->m_correspDevice;
	staticDeviceDescPtr = (UsbDeviceDescriptor *)dev->m_staticDeviceDescPtr;
	if ( (int)dev->m_fetchDescriptorCounter > 0 && req->m_resultCode != USB_RC_OK )
	{
		killDevice(req->m_correspEndpoint->m_correspDevice, req->m_correspEndpoint);
		return;
	}
	fetchDescriptorCounter = dev->m_fetchDescriptorCounter;
	fetchDesc_1 = fetchDescriptorCounter + 1;
	dev->m_fetchDescriptorCounter = fetchDesc_1;
	fetchDesc_2 = fetchDescriptorCounter & 1;
	curDescNum_1 = fetchDescriptorCounter >> 1;
	destdata = (UsbConfigDescriptor *)dev->m_staticDeviceDescEndPtr;
	if ( curDescNum_1 > 0 && !fetchDesc_2 )
		dev->m_staticDeviceDescEndPtr = (char *)dev->m_staticDeviceDescEndPtr + READ_UINT16(&destdata->wTotalLength);
	readLen = fetchDesc_2 ? READ_UINT16(&destdata->wTotalLength) : 4;
	if ( (char *)dev->m_staticDeviceDescPtr + usbConfig.m_maxStaticDescSize < (char *)(&destdata->bLength + readLen) )
	{
		dbg_printf("USBD: UsbdDevice_t ignored, UsbdDevice_t descriptors too large\n");
		return;  // buffer is too small, silently ignore the device
	}
	if ( curDescNum_1 < staticDeviceDescPtr->bNumConfigurations )
	{
		doControlTransfer(
			req->m_correspEndpoint,
			&dev->m_ioRequest,
			USB_DIR_IN | USB_RECIP_DEVICE,
			USB_REQ_GET_DESCRIPTOR,
			curDescNum_1 | (USB_DT_CONFIG << 8),
			0,
			readLen,
			destdata,
			fetchConfigDescriptors);
		return;
	}
	dev->m_reportDescriptorStart = NULL;
	if ( usbConfig.m_curDescNum )
	{
		handleStaticDeviceDescriptor(
			dev, (UsbDeviceDescriptor *)dev->m_staticDeviceDescPtr, (UsbDeviceDescriptor *)dev->m_staticDeviceDescEndPtr);
		if ( dev->m_reportDescriptorStart )
		{
			dev->m_reportDescriptorCurForFetch = dev->m_reportDescriptorStart;
			fetchNextReportDescriptor(req);
			return;
		}
	}
	connectNewDevice(dev);
}

void requestDeviceDescrptorCB(UsbdIoRequest_t *req)
{
	UsbdDevice_t *dev;
	const UsbDeviceDescriptor *desc;

	dev = req->m_correspEndpoint->m_correspDevice;
	if ( req->m_resultCode != USB_RC_OK )
	{
		dbg_printf("unable to read device descriptor, err %d\n", req->m_resultCode);
		killDevice(req->m_correspEndpoint->m_correspDevice, req->m_correspEndpoint);
		return;
	}
	if ( req->m_transferedBytes >= sizeof(UsbDeviceDescriptor) )
	{
		dev->m_fetchDescriptorCounter = 0;
		dev->m_staticDeviceDescEndPtr = &((UsbDeviceDescriptor *)dev->m_staticDeviceDescEndPtr)[1];
		fetchConfigDescriptors(req);
		return;
	}
	desc = dev->m_staticDeviceDescPtr;
	req->m_correspEndpoint->m_hcEd->m_hcArea.stru.m_maxPacketSize =
		(req->m_correspEndpoint->m_hcEd->m_hcArea.stru.m_maxPacketSize & 0xF800) | desc->bMaxPacketSize0;
	req->m_length = sizeof(UsbDeviceDescriptor);
	requestDeviceDescriptor(req);
}

void requestDeviceDescriptor(UsbdIoRequest_t *req)
{
	UsbdDevice_t *dev;

	dev = req->m_correspEndpoint->m_correspDevice;
	dev->m_staticDeviceDescEndPtr = dev->m_staticDeviceDescPtr;
	doControlTransfer(
		req->m_correspEndpoint,
		&dev->m_ioRequest,
		USB_DIR_IN | USB_RECIP_DEVICE,
		USB_REQ_GET_DESCRIPTOR,
		USB_DT_DEVICE << 8,
		0,
		req->m_length,
		dev->m_staticDeviceDescPtr,
		requestDeviceDescrptorCB);
}

void hubPeekDeviceDescriptor(UsbdIoRequest_t *req)
{
	req->m_length = 8;
	requestDeviceDescriptor(req);

	// we've assigned a function address to the device and can reset the next device now, if there is one
	checkDelayedResets(req->m_correspEndpoint->m_correspDevice);
}

void hubSetFuncAddressCB(UsbdIoRequest_t *req)
{
	void *cb_arg;
	UsbdDevice_t *dev;
	void (*cb_func)(void *);
	int cb_delay;

	dev = req->m_correspEndpoint->m_correspDevice;
	if ( req->m_resultCode == USB_RC_NORESPONSE )
	{
		dbg_printf("device not responding\n");
		dev->m_functionDelay <<= 1;
		if ( dev->m_functionDelay > 0x500 )
		{
			killDevice(dev, req->m_correspEndpoint);
			return;
		}
		cb_func = (void (*)(void *))hubSetFuncAddress;
		cb_arg = req->m_correspEndpoint;
		cb_delay = dev->m_functionDelay | 1;
	}
	else
	{
		cb_func = (void (*)(void *))hubPeekDeviceDescriptor;
		cb_arg = req;
		cb_delay = 5;
		req->m_correspEndpoint->m_hcEd->m_hcArea.stru.m_hcArea |= dev->m_functionAddress & 0x7F;
		dev->m_deviceStatus = 7;
	}
	addTimerCallback(&dev->m_timer, cb_func, cb_arg, cb_delay);
}

void hubSetFuncAddress(UsbdEndpoint_t *ep)
{
	// dbg_printf("setting FA %02X\n", ep->m_correspDevice->m_functionAddress);
	doControlTransfer(
		ep,
		&ep->m_correspDevice->m_ioRequest,
		USB_DIR_OUT | USB_RECIP_DEVICE,
		USB_REQ_SET_ADDRESS,
		ep->m_correspDevice->m_functionAddress,
		0,
		0,
		NULL,
		hubSetFuncAddressCB);
}

int hubTimedSetFuncAddress(UsbdDevice_t *dev)
{
	dev->m_functionDelay = 20;
	addTimerCallback(&dev->m_timer, (TimerCallback)hubSetFuncAddress, dev->m_endpointListStart, 21);
	return 0;
}

void flushPort(UsbdDevice_t *dev)
{
	UsbdReportDescriptor_t *desc;
	UsbdDevice_t *child;
	int state;

	if ( dev->m_deviceStatus != DEVICE_NOTCONNECTED )
	{
		dev->m_deviceStatus = DEVICE_NOTCONNECTED;
		if ( dev->m_devDriver )
			callUsbDriverFunc(dev->m_devDriver->disconnect, dev->m_id, dev->m_devDriver->gp);
		dev->m_devDriver = NULL;
		if ( dev->m_timer.m_isActive )
			cancelTimerCallback(&dev->m_timer);
		while ( dev->m_endpointListStart )
		{
			removeEndpointFromDevice(dev, dev->m_endpointListStart);
		}
		for ( desc = dev->m_reportDescriptorStart; desc; desc = dev->m_reportDescriptorStart )
		{
			if ( desc->m_next )
				desc->m_next->m_prev = desc->m_prev;
			else
				dev->m_reportDescriptorEnd = desc->m_prev;
			if ( desc->m_prev )
				desc->m_prev->m_next = desc->m_next;
			else
				dev->m_reportDescriptorStart = desc->m_next;
			CpuSuspendIntr(&state);
			FreeSysMemory(desc);
			CpuResumeIntr(state);
		}
		while ( dev->m_childListStart )
		{
			child = dev->m_childListStart;
			if ( child->m_next )
				child->m_next->m_prev = child->m_prev;
			else
				dev->m_childListEnd = child->m_prev;
			if ( child->m_prev )
				child->m_prev->m_next = child->m_next;
			else
				dev->m_childListStart = child->m_next;
			flushPort(child);
			freeDevice(child);
		}
		dev->m_ioRequest.m_busyFlag = 0;
	}
	if ( dev->m_resetFlag )
		checkDelayedResets(dev);
}

int usbdInitInner(void)
{
	printf("USB Driver (%s)", usbdVersionString);
	printf("\n");
	dbg_printf("HCD init...\n");
	if ( initHcdStructs() < 0 )
		return -1;
	dbg_printf("Hub driver...\n");
	if ( initHubDriver() < 0 )
		return -1;
	return 0;
}
