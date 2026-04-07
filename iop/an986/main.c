
#include "irx_imports.h"

IRX_ID("INET_AN986_driver", 1, 75);

struct an986_priv
{
	int m_magic_cur;
	int m_is_pegasus2;
	int m_thid;
	int m_efid;
	int m_subclass;
	int m_ef_wait_retval;
	int m_done_related;
	int m_ctrl_pipe;
	int m_bulk_in_pipe;
	int m_bulk_out_pipe;
	int m_int_in_pipe;
	u8 m_usb_xfer_buf[268];
	sceInetDevOps_t m_devops;
	u8 m_hwaddr_tmp[8];
	int m_val_for_inet_stop;
	int m_start_stop_flag;
	int m_val_for_inet_start;
	int m_timer_active;
	iop_sys_clock_t m_sysclk;
	int m_link_status;
	int m_nego_status;
	int m_val_for_alarm_cb;
	u16 m_usb_ctrl_buf[2];
	int m_cnt_for_bulk_xfer;
	int m_rx_packets;
	int m_tx_packets;
	int m_rx_bytes;
	int m_tx_bytes;
	int m_rx_errors;
	int m_tx_errors;
	int m_rx_dropped;
	int m_tx_dropped;
	int m_multicast;
	int m_collisions;
	int m_err_rx_length;
	int m_err_rx_over;
	int m_err_rx_crc;
	int m_err_rx_frame;
	int m_err_rx_fifo;
	int m_err_rx_missed;
	int m_err_tx_aborted;
	int m_err_tx_carrier;
	int m_err_tx_fifo;
	int m_err_tx_heartbeat;
	int m_err_tx_window;
};

struct an986_devinfo
{
	int m_chip;
	int m_vendor_id;
	const char *m_vendor_name;
	int m_product_id;
	const char *m_device_name;
};

#define __fastcall
#define __cdecl
#define _BYTE u8
#define _WORD u16
#define __int8 char
#define __int16 short
#define u_char unsigned char

//-------------------------------------------------------------------------
// Function declarations

int __fastcall ef_wait_wrap(struct an986_priv *priv, u32 efbits);
int __fastcall ef_set_wrap(struct an986_priv *priv, int wait_retval, u32 efbits);
int __fastcall an986_done(int efbits, int doneval, struct an986_priv *priv);
int __fastcall control_negative_xfer(struct an986_priv *priv, int xferoffs, int xferlen);
int __fastcall control_positive_xfer(struct an986_priv *priv, int xferoffs, int xferlen);
int __fastcall control_inout_xfer(struct an986_priv *priv, char linkval, char xval, _WORD *outptr);
int __fastcall an986_rx_done(int aresult, int acount, sceInetPkt_t *pkt);
void __fastcall bulk_xfer(struct an986_priv *priv);
void __fastcall an986_tx_done(int aresult, int acount, sceInetPkt_t *pkt);
u32 __fastcall alarm_cb(struct an986_priv *priv);
int __fastcall an986_inet_start(struct an986_priv *priv);
int __fastcall an986_inet_stop(struct an986_priv *priv);
int __fastcall an986_inet_xmit(struct an986_priv *priv);
int __fastcall inet_81040000_multicast_list_handler(struct an986_priv *priv, _BYTE *ptr, int len);
int __fastcall an986_inet_control(struct an986_priv *priv, int code, _BYTE *ptr, int len);
int __fastcall inet_thread_proc(struct an986_priv *priv);
struct an986_priv *__fastcall do_allocate_mem_for_inet(char *vendor_name, char *device_name, int is_pegasus2);
struct an986_devinfo *__fastcall do_check_static_descriptor(int is_probe, unsigned __int16 id_vendor, unsigned __int16 id_product);
int __fastcall an986_ldd_connect(int devId);
int __fastcall an986_ldd_disconnect(int devId);
int __fastcall an986_ldd_probe(int devId);
int do_print_version();
int do_print_help();
int __fastcall scan_number(char *inchr, int *outptr);
int do_print_list();
int __fastcall an986_init(int ac, char **av);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_an986;
struct an986_devinfo g_an986_devinfo[53] =
{
	{ 45, 0, "Unknown", 0, "Unknown" },
	{ 107, 1000, "AOX", 8, "101" },
	{ 112, 1041, "Melco", 1, "LUA-TX" },
	{ 112, 1041, "Melco", 5, "LUA-TX" },
	{ 80, 1041, "Melco", 9, "LUA2-TX" },
	{ 45, 1041, "Melco", 18, "LUA-KTX" },
	{ 45, 1059, "CATC", 10, "NetMate" },
	{ 45, 1059, "CATC", 12, "NetMate2" },
	{ 107, 1211, "I-O Data", 2305, "ET/T" },
	{ 112, 1211, "I-O Data", 2308, "ET/TX" },
	{ 107, 1286, "3Com", 1000, "3C19250" },
	{ 107, 1367, "ATEN", 8194, "UC-10T" },
	{ 107, 1367, "ATEN", 16384, "DSB-650" },
	{ 107, 1381, "Peracom", 2, "Enet" },
	{ 107, 1381, "Peracom", 5, "Enet2" },
	{ 107, 1390, "Elecom", 16384, "LD-USB/T" },
	{ 112, 1390, "Elecom", 16386, "LD-USB/TX" },
	{ 80, 1390, "Elecom", 16389, "LD-USBL/TX" },
	{ 107, 1513, "KLSI", 8, "KL5KUSB101B" },
	{ 112, 1513, "KLSI", 9, "Pegasus" },
	{ 107, 1643, "Linksys", 8706, "USB10T" },
	{ 112, 1643, "Linksys", 8707, "USB100TX" },
	{ 112, 1643, "Linksys", 8708, "USB100TX" },
	{ 112, 1643, "Linksys", 8710, "USB" },
	{ 80, 1643, "Linksys", 16395, "USB100TX B" },
	{ 107, 1761, "ADS", 8, "USBS-10B" },
	{ 107, 1799, "SMC", 256, "2202" },
	{ 112, 1799, "SMC", 512, "2202" },
	{ 112, 1958, "ADMtek", 2438, "Pegasus" },
	{ 80, 1958, "ADMtek", 34065, "PegasusII" },
	{ 107, 1962, "Corega", 1, "USB-T" },
	{ 112, 1962, "Corega", 4, "USB-TX" },
	{ 80, 1962, "Corega", 13, "USB-TXS" },
	{ 112, 1976, "D-Link", 43969, "DU-E10" },
	{ 107, 1976, "D-Link", 16384, "DU-E10" },
	{ 112, 1976, "D-Link", 16386, "DU-E100" },
	{ 80, 1976, "D-Link", 16642, "DU-E100 B1" },
	{ 112, 2106, "Accton", 4166, "USB10/100" },
	{ 107, 2118, "NetGear", 4097, "EA101" },
	{ 112, 2269, "Billionton", 2438, "USB100N" },
	{ 112, 2269, "Billionton", 2439, "USBLP-100" },
	{ 112, 2269, "Billionton", 2440, "USBEL-100" },
	{ 80, 2269, "Billionton", 34065, "USBE-100" },
	{ 107, 5074, "Shark", 1024, "Pocket" },
	{ 45, 5253, "PSION DACOM", 2, "Gold Port" },
	{ 112, 5608, "SOHOware", 37120, "NUB100" },
	{ 107, 5701, "Entrega", 5, "E45" },
	{ 107, 8193, "D-Link", 16384, "DSB-650C" },
	{ 112, 8193, "D-Link", 16385, "DSB-650TX" },
	{ 112, 8193, "D-Link", 16386, "DSB-650TX" },
	{ 112, 8193, "D-Link", 16387, "DSB-650TX-PNA" },
	{ 80, 8193, "D-Link", 16395, "DSB-650TX B1" },
	{ 112, 8193, "D-Link", 43969, "DSB-650" }
}; // weak
sceUsbdLddOps g_an986_ldd =
{
	NULL,
	NULL,
	"an986",
	&an986_ldd_probe,
	&an986_ldd_connect,
	&an986_ldd_disconnect,
	0u,
	0u,
	0u,
	0u,
	0u,
	NULL
}; // weak
int g_thpri = 40; // weak
int g_thstack = 16384; // weak
int g_magic_count = 0; // weak
int g_verbose = 0; // weak
int dword_4036A8 = 0; // weak
char *version_ptr = "Version 1.75.0"; // weak
int g_resident_flag; // weak
int g_load_mode; // weak


//----- (00400000) --------------------------------------------------------
int __fastcall ef_wait_wrap(struct an986_priv *priv, u32 efbits)
{
	int efret; // $s1
	int result; // $v0
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	efret = WaitEventFlag(priv->m_efid, efbits, 17, efres);
	if ( !efret )
		return priv->m_ef_wait_retval;
	result = -1;
	if ( g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("WaitEventFlag (%d)", efret);
		printf("\n");
		return -1;
	}
	return result;
}
// 403504: using guessed type int g_verbose;

//----- (00400088) --------------------------------------------------------
int __fastcall ef_set_wrap(struct an986_priv *priv, int wait_retval, u32 efbits)
{
	int m_efid; // $a0
	int retval; // $v0
	int efret; // $s1

	m_efid = priv->m_efid;
	priv->m_ef_wait_retval = wait_retval;
	retval = SetEventFlag(m_efid, efbits);
	efret = retval;
	if ( retval )
	{
		retval = g_verbose;
		if ( g_verbose )
		{
			printf("%s: ", priv->m_devops.interface);
			printf("SetEventFlag (%d)", efret);
			return printf("\n");
		}
	}
	return retval;
}
// 403504: using guessed type int g_verbose;

//----- (00400104) --------------------------------------------------------
int __fastcall an986_done(int efbits, int doneval, struct an986_priv *priv)
{
	struct an986_priv *priv_tmp; // $a0

	if ( !efbits )
		goto LABEL_4;
	priv_tmp = priv;
	if ( g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("%s: -> 0x%x\n", "an986_done", efbits);
		printf("\n");
LABEL_4:
		priv_tmp = priv;
	}
	priv->m_done_related = doneval;
	return ef_set_wrap(priv_tmp, efbits, 4u);
}
// 403504: using guessed type int g_verbose;

//----- (00400194) --------------------------------------------------------
int __fastcall control_negative_xfer(struct an986_priv *priv, int xferoffs, int xferlen)
{
	int xferret; // $s0
	int result; // $v0
	UsbDeviceRequest devreq; // [sp+18h] [-8h] BYREF

	if ( xferlen < 2 )
		xferlen = 2;
	devreq.requesttype = 0xC0;
	devreq.length = xferlen;
	devreq.request = 0xF0;
	devreq.value = 0;
	devreq.index = xferoffs;
	xferret = sceUsbdTransferPipe(
							priv->m_ctrl_pipe,
							&priv->m_usb_xfer_buf[xferoffs],
							(unsigned __int16)xferlen,
							&devreq,
							(sceUsbdDoneCallback)an986_done,
							priv);
	if ( !xferret )
		return ef_wait_wrap(priv, 4u);
	result = -1;
	if ( g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("sceUsbdControlTransfer -> 0x%x", xferret);
		printf("\n");
		return -1;
	}
	return result;
}
// 403504: using guessed type int g_verbose;

//----- (00400264) --------------------------------------------------------
int __fastcall control_positive_xfer(struct an986_priv *priv, int xferoffs, int xferlen)
{
	int xferret; // $s0
	int result; // $v0
	UsbDeviceRequest devreq; // [sp+18h] [-8h] BYREF

	if ( xferlen < 2 )
		xferlen = 2;
	devreq.requesttype = 0x40;
	devreq.length = xferlen;
	devreq.request = 0xF1;
	devreq.value = 0;
	devreq.index = xferoffs;
	xferret = sceUsbdTransferPipe(
							priv->m_ctrl_pipe,
							&priv->m_usb_xfer_buf[xferoffs],
							(unsigned __int16)xferlen,
							&devreq,
							(sceUsbdDoneCallback)an986_done,
							priv);
	if ( !xferret )
		return ef_wait_wrap(priv, 4u);
	result = -1;
	if ( g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("sceUsbdControlTransfer -> 0x%x", xferret);
		printf("\n");
		return -1;
	}
	return result;
}
// 403504: using guessed type int g_verbose;

//----- (00400334) --------------------------------------------------------
int __fastcall control_inout_xfer(struct an986_priv *priv, char linkval, char xval, _WORD *outptr)
{
	int result; // $v0
	struct an986_priv *priv_tmp; // $a0

	priv->m_usb_xfer_buf[37] = linkval & 0x1F;
	priv->m_usb_xfer_buf[38] = 0;
	priv->m_usb_xfer_buf[39] = 0;
	priv->m_usb_xfer_buf[40] = xval & 0x1F | 0x40;
	result = control_positive_xfer(priv, 37, 4);
	priv_tmp = priv;
	if ( !result )
	{
		while ( 1 )
		{
			result = control_negative_xfer(priv_tmp, 40, 1);
			if ( result )
				break;
			if ( (priv->m_usb_xfer_buf[40] & 0x80) != 0 )
			{
				result = control_negative_xfer(priv, 37, 4);
				if ( !result )
				{
					result = 0;
					*outptr = priv->m_usb_xfer_buf[38] | (priv->m_usb_xfer_buf[39] << 8);
				}
				return result;
			}
			DelayThread(10000);
			priv_tmp = priv;
		}
	}
	return result;
}

//----- (004003F4) --------------------------------------------------------
int __fastcall an986_rx_done(int aresult, int acount, sceInetPkt_t *pkt)
{
	struct an986_priv *priv; // $s0
	sceInetDevOps_t *p_m_devops; // $a0
	u_char rp_cur; // $v1
	int rp_mask; // $v0
	bool condtmp; // dc
	int rpcur_4; // $v0
	int rpcur_8; // $v0
	int rpcur_10; // $v0
	int rpcur_1e; // $v0
	struct sceInetPktQ *p_rcvq; // $a0
	int result; // $v0

	priv = (struct an986_priv *)pkt->m_reserved1;
	if ( aresult && g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("%s: -> 0x%x\n", "an986_rx_done", aresult);
		printf("\n");
	}
	++priv->m_rx_packets;
	pkt->m_reserved1 = 0;
	p_m_devops = &priv->m_devops;
	if ( priv->m_start_stop_flag || priv->m_val_for_inet_stop )
		goto LABEL_23;
	if ( acount < 68 )
	{
LABEL_19:
		++priv->m_rx_errors;
		p_m_devops = &priv->m_devops;
LABEL_23:
		sceInetFreePkt(p_m_devops, pkt);
		goto LABEL_22;
	}
	rp_cur = pkt->rp[acount - 2];
	if ( (rp_cur & 0x1F) != 0 )
	{
		rp_mask = rp_cur & 2;
		if ( (pkt->rp[acount - 2] & 1) != 0 )
		{
			++priv->m_multicast;
			rp_mask = rp_cur & 2;
		}
		condtmp = rp_mask == 0;
		rpcur_4 = rp_cur & 4;
		if ( !condtmp )
		{
			++priv->m_err_rx_length;
			rpcur_4 = rp_cur & 4;
		}
		condtmp = rpcur_4 == 0;
		rpcur_8 = rp_cur & 8;
		if ( !condtmp )
		{
			++priv->m_err_rx_length;
			rpcur_8 = rp_cur & 8;
		}
		condtmp = rpcur_8 == 0;
		rpcur_10 = rp_cur & 0x10;
		if ( !condtmp )
		{
			++priv->m_err_rx_crc;
			rpcur_10 = rp_cur & 0x10;
		}
		condtmp = rpcur_10 == 0;
		rpcur_1e = rp_cur & 0x1E;
		if ( !condtmp )
		{
			++priv->m_err_rx_frame;
			rpcur_1e = rp_cur & 0x1E;
		}
		p_rcvq = &priv->m_devops.rcvq;
		if ( rpcur_1e )
			goto LABEL_19;
	}
	else
	{
		p_rcvq = &priv->m_devops.rcvq;
	}
	priv->m_rx_bytes = priv->m_rx_bytes - 8 + acount;
	pkt->wp += acount - 8;
	sceInetPktEnQ(p_rcvq, pkt);
	SetEventFlag(priv->m_devops.evfid, 4u);
LABEL_22:
	bulk_xfer(priv);
	result = 10;
	priv->m_val_for_alarm_cb = 10;
	return result;
}
// 403504: using guessed type int g_verbose;

//----- (004005E0) --------------------------------------------------------
void __fastcall bulk_xfer(struct an986_priv *priv)
{
	sceInetDevOps_t *devops_1; // $s3
	sceInetPkt_t *pkt_1; // $v0
	sceInetPkt_t *pkt_2; // $s0
	int state_1; // $a0
	u_char *rp; // $v0
	u_char *wp; // $v1
	int xferret; // $s1
	sceInetDevOps_t *devops_2; // $a0
	int state; // [sp+18h] [-8h] BYREF

	devops_1 = &priv->m_devops;
	pkt_1 = sceInetAllocPkt(&priv->m_devops, 1524);
	pkt_2 = pkt_1;
	if ( pkt_1 )
	{
		rp = pkt_1->rp;
		wp = pkt_2->wp;
		pkt_2->m_reserved1 = (void *)priv;
		pkt_2->rp = rp + 2;
		pkt_2->wp = wp + 2;
		xferret = sceUsbdTransferPipe(priv->m_bulk_in_pipe, pkt_2->wp, 0x5F2u, 0, (sceUsbdDoneCallback)an986_rx_done, pkt_2);
		if ( xferret )
		{
			devops_2 = devops_1;
			if ( g_verbose )
			{
				printf("%s: ", priv->m_devops.interface);
				printf("sceUsbdBulkTransfer -> 0x%x\n", xferret);
				printf("\n");
				devops_2 = devops_1;
			}
			sceInetFreePkt(devops_2, pkt_2);
		}
	}
	else
	{
		if ( g_verbose )
		{
			printf("%s: ", priv->m_devops.interface);
			printf("sceInetAllocPkt(%d) - no space", 1524);
			printf("\n");
		}
		CpuSuspendIntr(&state);
		state_1 = state;
		++priv->m_cnt_for_bulk_xfer;
		CpuResumeIntr(state_1);
	}
}
// 403504: using guessed type int g_verbose;

//----- (0040071C) --------------------------------------------------------
void __fastcall an986_tx_done(int aresult, int acount, sceInetPkt_t *pkt)
{
	struct an986_priv *priv; // $s1
	bool condtmp; // dc
	sceInetDevOps_t *p_m_devops; // $a0
	sceInetPkt_t *pkt_1; // $a1

	priv = (struct an986_priv *)pkt->m_reserved1;
	condtmp = aresult == 0;
	p_m_devops = &priv->m_devops;
	if ( condtmp )
		goto LABEL_4;
	pkt_1 = pkt;
	if ( g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("%s: -> 0x%x\n", "an986_tx_done", aresult);
		printf("\n");
		p_m_devops = &priv->m_devops;
LABEL_4:
		pkt_1 = pkt;
	}
	pkt->m_reserved1 = 0;
	sceInetFreePkt(p_m_devops, pkt_1);
}
// 403504: using guessed type int g_verbose;

//----- (004007AC) --------------------------------------------------------
u32 __fastcall alarm_cb(struct an986_priv *priv)
{
	int m_val_for_alarm_cb; // $v0
	bool tmpneg; // dc
	int tmpval; // $v0

	m_val_for_alarm_cb = priv->m_val_for_alarm_cb;
	tmpneg = m_val_for_alarm_cb <= 0;
	tmpval = m_val_for_alarm_cb - 1;
	if ( !tmpneg )
		priv->m_val_for_alarm_cb = tmpval;
	return priv->m_sysclk.lo;
}

//----- (004007DC) --------------------------------------------------------
int __fastcall an986_inet_start(struct an986_priv *priv)
{
	int m_val_for_inet_start; // $v0

	m_val_for_inet_start = priv->m_val_for_inet_start;
	priv->m_start_stop_flag = 0;
	if ( m_val_for_inet_start )
		SetEventFlag(priv->m_devops.evfid, 1u);
	else
		ef_set_wrap(priv, 0, 2u);
	return 0;
}

//----- (00400840) --------------------------------------------------------
int __fastcall an986_inet_stop(struct an986_priv *priv)
{
	int m_val_for_inet_stop; // $v1

	m_val_for_inet_stop = priv->m_val_for_inet_stop;
	priv->m_start_stop_flag = 1;
	if ( m_val_for_inet_stop )
	{
		TerminateThread(priv->m_thid);
		DeleteThread(priv->m_thid);
		DeleteEventFlag(priv->m_efid);
		if ( priv->m_timer_active )
			CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, priv);
		sceInetUnregisterNetDevice(&priv->m_devops);
		sceInetFreeMem(&priv->m_devops, priv);
	}
	return 0;
}

//----- (004008F4) --------------------------------------------------------
int __fastcall an986_inet_xmit(struct an986_priv *priv)
{
	int xferres; // $s3
	sceInetPkt_t *pkt; // $s2
	u_char *rp; // $v1
	u_char *xrp2; // $s1
	u_char *xrp3; // $v0
	int rpbytesp; // $v1
	sceInetDevOps_t *p_m_devops; // $a0

	xferres = -1;
	pkt = sceInetPktDeQ(&priv->m_devops.sndq);
	if ( pkt )
	{
		if ( priv->m_start_stop_flag
			|| priv->m_val_for_inet_stop
			|| !priv->m_link_status
			|| (rp = pkt->rp, xrp2 = (u_char *)(pkt->wp - rp), xrp3 = rp - 2, (unsigned int)(xrp2 - 60) >= 0x5AF)
			|| (pkt->rp = xrp3, ((unsigned __int8)xrp3 & 3) != 0) )
		{
LABEL_15:
			p_m_devops = &priv->m_devops;
			if ( g_verbose )
			{
				printf("%s: ", priv->m_devops.interface);
				printf("dropped");
				printf("\n");
				p_m_devops = &priv->m_devops;
			}
LABEL_17:
			++priv->m_tx_dropped;
			sceInetFreePkt(p_m_devops, pkt);
		}
		else
		{
			*((_WORD *)rp - 1) = (_WORD)xrp2;
			rpbytesp = (int)&xrp2[priv->m_tx_bytes];
			++priv->m_tx_packets;
			priv->m_tx_bytes = rpbytesp;
			if ( (((_BYTE)xrp2 + 2) & 0x3F) == 0 )
				++xrp2;
			pkt->m_reserved1 = (void *)priv;
			while ( 1 )
			{
				xferres = sceUsbdTransferPipe(
										priv->m_bulk_out_pipe,
										pkt->rp,
										(u32)(xrp2 + 2),
										0,
										(sceUsbdDoneCallback)an986_tx_done,
										pkt);
				if ( !xferres )
					break;
				if ( xferres != 274 )
				{
					p_m_devops = &priv->m_devops;
					if ( !g_verbose )
						goto LABEL_17;
					printf("%s: ", priv->m_devops.interface);
					printf("sceUsbdBulkTransfer -> 0x%x", xferres);
					printf("\n");
					goto LABEL_15;
				}
				DelayThread(10000);
			}
		}
	}
	priv->m_val_for_alarm_cb = 10;
	return xferres;
}
// 403504: using guessed type int g_verbose;

//----- (00400AC4) --------------------------------------------------------
int __fastcall inet_81040000_multicast_list_handler(struct an986_priv *priv, _BYTE *ptr, int len)
{
	int result; // $v0
	int curindx; // $a3
	struct an986_priv *priv_1; // $v0
	struct an986_priv *priv_2; // $a0
	int lendiv; // $v1
	int lendivm1; // $t0
	int lendivm1_1; // $v0
	unsigned int valcr2; // $v1
	int i; // $a3
	u8 rshavle; // $v0
	int j; // $a2
	unsigned int xcurval; // $a0

	bzero(&priv->m_usb_xfer_buf[8], 8);
	if ( len >= 0 )
	{
		lendiv = len / 6;
		result = -512;
		if ( len != 6 * (len / 6) )
			return result;
		priv_2 = priv;
		if ( ptr )
		{
			lendivm1 = lendiv - 1;
			if ( lendiv > 0 )
			{
				do
				{
					lendivm1_1 = lendivm1;
					if ( (*ptr & 1) != 0 )
					{
						valcr2 = -1;
						for ( i = 5; i >= 0; --i )
						{
							rshavle = *ptr++;
							for ( j = 7; j >= 0; --j )
							{
								xcurval = valcr2 >> 1;
								if ( (((unsigned __int8)valcr2 ^ rshavle) & 1) != 0 )
									xcurval ^= 0xEDB88320;
								valcr2 = xcurval;
								rshavle = rshavle >> 1;
							}
						}
						priv->m_usb_xfer_buf[((unsigned __int8)(xcurval & 0x3F) >> 3) + 8] |= 1 << (xcurval & 7);
						lendivm1_1 = lendivm1;
					}
					--lendivm1;
				}
				while ( lendivm1_1 > 0 );
				priv_2 = priv;
			}
		}
	}
	else
	{
		result = -512;
		if ( ptr )
			return result;
		curindx = 0;
		priv_1 = priv;
		do
		{
			priv_1->m_usb_xfer_buf[8] = -1;
			priv_1 = (struct an986_priv *)((char *)priv + ++curindx);
		}
		while ( curindx < 8 );
		priv_2 = priv;
	}
	return control_positive_xfer(priv_2, 8, 8);
}

//----- (00400C28) --------------------------------------------------------
int __fastcall an986_inet_control(struct an986_priv *priv, int code, _BYTE *ptr, int len)
{
	int m_nego_status; // $v1
	int *p_m_err_rx_over; // $s0
	int m_thid; // $a0
	int priority; // [sp+10h] [-8h] BYREF

	m_nego_status = -512;
	p_m_err_rx_over = 0;
	if ( code == 0x80011003 )
	{
		p_m_err_rx_over = &priv->m_err_rx_over;
	}
	else if ( code > (int)0x80011003 )
	{
		if ( code == 0x8001100A )
		{
			p_m_err_rx_over = &priv->m_err_tx_fifo;
		}
		else if ( code > (int)0x8001100A )
		{
			if ( code == 0x80020001 )
			{
				m_nego_status = 0;
				if ( priv->m_link_status > 0 )
					m_nego_status = priv->m_nego_status;
			}
			else if ( code > (int)0x80020001 )
			{
				if ( code == 0x81000000 )
				{
					if ( ptr )
					{
						if ( len == 4 )
						{
							bcopy(ptr, &priority, 4);
							m_nego_status = -403;
							if ( (unsigned int)(priority - 9) < 0x73 )
							{
								m_thid = priv->m_thid;
								g_thpri = priority;
								m_nego_status = ChangeThreadPriority(m_thid, priority);
							}
						}
					}
				}
				else if ( code > (int)0x81000000 )
				{
					if ( code == 0x81040000 )
						m_nego_status = inet_81040000_multicast_list_handler(priv, ptr, len);
				}
				else if ( code == 0x80030000 )
				{
					m_nego_status = priv->m_link_status;
				}
			}
			else if ( code == 0x8001100B )
			{
				p_m_err_rx_over = &priv->m_err_tx_heartbeat;
			}
			else if ( code == 0x8001100C )
			{
				p_m_err_rx_over = &priv->m_err_tx_window;
			}
		}
		else if ( code == 0x80011006 )
		{
			p_m_err_rx_over = &priv->m_err_rx_fifo;
		}
		else if ( code > (int)0x80011006 )
		{
			if ( code == 0x80011008 )
			{
				p_m_err_rx_over = &priv->m_err_tx_aborted;
			}
			else
			{
				p_m_err_rx_over = &priv->m_err_tx_carrier;
				if ( code <= (int)0x80011008 )
					p_m_err_rx_over = &priv->m_err_rx_missed;
			}
		}
		else if ( code == 0x80011004 )
		{
			p_m_err_rx_over = &priv->m_err_rx_crc;
		}
		else
		{
			p_m_err_rx_over = &priv->m_err_rx_frame;
		}
	}
	else if ( code == 0x80010004 )
	{
		p_m_err_rx_over = &priv->m_rx_errors;
	}
	else if ( code > (int)0x80010004 )
	{
		if ( code == 0x80010007 )
		{
			p_m_err_rx_over = &priv->m_tx_dropped;
		}
		else if ( code > (int)0x80010007 )
		{
			if ( code == 0x80011001 )
			{
				p_m_err_rx_over = &priv->m_collisions;
			}
			else if ( code > (int)0x80011001 )
			{
				p_m_err_rx_over = &priv->m_err_rx_length;
			}
			else if ( code == 0x80011000 )
			{
				p_m_err_rx_over = &priv->m_multicast;
			}
		}
		else if ( code == 0x80010005 )
		{
			p_m_err_rx_over = &priv->m_tx_errors;
		}
		else
		{
			p_m_err_rx_over = &priv->m_rx_dropped;
		}
	}
	else if ( code == 0x80010000 )
	{
		p_m_err_rx_over = &priv->m_rx_packets;
	}
	else if ( code > (int)0x80010000 )
	{
		if ( code == 0x80010002 )
		{
			p_m_err_rx_over = &priv->m_rx_bytes;
		}
		else
		{
			p_m_err_rx_over = &priv->m_tx_bytes;
			if ( code <= (int)0x80010002 )
				p_m_err_rx_over = &priv->m_tx_packets;
		}
	}
	else if ( code == 0x80000000 )
	{
		m_nego_status = g_thpri;
	}
	else if ( code == 0x80000100 )
	{
		m_nego_status = 1;
	}
	if ( p_m_err_rx_over && ptr && len == 4 )
	{
		bcopy(p_m_err_rx_over, ptr, 4);
		return 0;
	}
	return m_nego_status;
}
// 400CFC: conditional instruction was optimized away because $a1.4==80010006
// 400D70: conditional instruction was optimized away because $a1.4==80011005
// 4034F8: using guessed type int g_thpri;

//----- (00400F78) --------------------------------------------------------
int __fastcall inet_thread_proc(struct an986_priv *priv)
{
	int result; // $v0
	u16 m_subclass; // $v0
	int xferret; // $s0
	int xidx_1; // $s0
	struct an986_priv *priv_tmp4; // $s2
	struct an986_priv *priv_tmp5; // $a0
	int regres; // $s0
	bool resres; // dc
	struct an986_priv *priv_tmp6; // $a0
	int idxcnt; // $s2
	int indindx2; // $s0
	struct an986_priv *priv_tmp3; // $a0
	int outval_1_1; // $a3
	u16 cxtr1; // $v0
	u16 cxtr2; // $v1
	int negoval_tmp; // $a0
	const char *spdstr; // $a2
	const char *dupval; // $a3
	int i; // $s0
	int m_start_stop_flag; // $v0
	int indindx; // $s0
	struct an986_priv *priv_tmp7; // $a0
	u8 xfer43buftmp; // $v1
	int masktmp; // $v0
	int plusone_1; // $v1
	int valuse; // $a0
	int plusaddx; // $v1
	int state_1; // $a0
	struct an986_priv *priv_tmp2; // $a0
	UsbDeviceRequest devreq; // [sp+20h] [-18h] BYREF
	unsigned __int16 outval_1; // [sp+28h] [-10h] BYREF
	unsigned __int16 outval_2; // [sp+2Ah] [-Eh] BYREF
	unsigned __int16 outval_3; // [sp+2Ch] [-Ch] BYREF
	int state; // [sp+30h] [-8h] BYREF

	result = ef_wait_wrap(priv, 1u);
	if ( !result )
	{
		devreq.requesttype = 0;
		devreq.request = 9;
		m_subclass = priv->m_subclass;
		devreq.index = 0;
		devreq.length = 0;
		devreq.value = m_subclass;
		xferret = sceUsbdTransferPipe(priv->m_ctrl_pipe, 0, 0, &devreq, (sceUsbdDoneCallback)an986_done, priv);
		if ( xferret )
		{
			result = g_verbose;
			if ( g_verbose )
			{
				printf("%s: ", priv->m_devops.interface);
				printf("sceUsbdSetConfiguration -> 0x%x", xferret);
				return printf("\n");
			}
		}
		else
		{
			result = ef_wait_wrap(priv, 4u);
			if ( !result )
			{
				result = control_negative_xfer(priv, 16, 6);
				xidx_1 = 0;
				if ( !result )
				{
					priv_tmp4 = priv;
LABEL_8:
					priv->m_usb_xfer_buf[32] = xidx_1;
					priv->m_usb_xfer_buf[33] = 0;
					priv->m_usb_xfer_buf[34] = 0;
					priv->m_usb_xfer_buf[35] = 2;
					result = control_positive_xfer(priv, 32, 4);
					priv_tmp5 = priv;
					if ( !result )
					{
						while ( 1 )
						{
							result = control_negative_xfer(priv_tmp5, 35, 1);
							if ( result )
								break;
							if ( (priv->m_usb_xfer_buf[35] & 4) != 0 )
							{
								result = control_negative_xfer(priv, 33, 3);
								++xidx_1;
								if ( result )
									return result;
								priv_tmp4->m_hwaddr_tmp[0] = priv->m_usb_xfer_buf[33];
								priv_tmp4->m_hwaddr_tmp[1] = priv->m_usb_xfer_buf[34];
								priv_tmp4 = (struct an986_priv *)((char *)priv_tmp4 + 2);
								if ( xidx_1 < 3 )
									goto LABEL_8;
								bcopy(priv->m_hwaddr_tmp, &priv->m_usb_xfer_buf[16], 6);
								result = control_positive_xfer(priv, 16, 6);
								if ( result )
									return result;
								bcopy(priv->m_hwaddr_tmp, priv->m_devops.hw_addr, 6);
								priv->m_link_status = -1;
								regres = sceInetRegisterNetDevice(&priv->m_devops);
								if ( regres >= 0 )
								{
									result = ef_wait_wrap(priv, 2u);
									if ( !result )
									{
										priv->m_usb_xfer_buf[126] = 36;
										priv->m_usb_xfer_buf[127] = 6;
										result = control_positive_xfer(priv, 126, 2);
										if ( !result )
										{
											priv->m_usb_xfer_buf[126] = 38;
											priv->m_usb_xfer_buf[127] = 4;
											result = control_positive_xfer(priv, 126, 2);
											if ( !result )
											{
												if ( !priv->m_is_pegasus2
													|| (priv->m_usb_xfer_buf[123] = 3,
															resres = control_positive_xfer(priv, 123, 1) != 0,
															result = 2,
															!resres)
													&& (priv->m_usb_xfer_buf[123] = 2, (result = control_positive_xfer(priv, 123, 1)) == 0) )
												{
													priv->m_usb_xfer_buf[1] = 8;
													result = control_positive_xfer(priv, 1, 1);
													priv_tmp6 = priv;
													if ( !result )
													{
														while ( 1 )
														{
															result = control_negative_xfer(priv_tmp6, 1, 1);
															if ( result )
																break;
															idxcnt = 0;
															if ( (priv->m_usb_xfer_buf[1] & 8) == 0 )
															{
																indindx2 = 0;
																priv_tmp3 = priv;
																while ( 1 )
																{
																	result = control_inout_xfer(priv_tmp3, idxcnt, 1, &outval_1);
																	if ( result )
																		return result;
																	if ( outval_1 == 0xFFFF )
																	{
																		++idxcnt;
																		priv_tmp3 = priv;
																		if ( idxcnt >= 32 )
																		{
																			result = g_verbose;
																			if ( !g_verbose )
																				return result;
																			printf("%s: ", priv->m_devops.interface);
																			printf("Valid PHY chip not found");
																			return printf("\n");
																		}
																	}
																	else
																	{
																		if ( (outval_1 & 0x24) == 36 )
																		{
																			outval_1_1 = outval_1;
																			priv->m_link_status = 1;
																			printf(
																				"%s: Auto-Nego complete and valid link detected (%d,BMSR=%04x)\n",
																				priv->m_devops.interface,
																				idxcnt,
																				outval_1_1);
																			result = control_inout_xfer(priv, idxcnt, 4, priv->m_usb_ctrl_buf);
																			if ( !result )
																			{
																				result = control_inout_xfer(priv, idxcnt, 5, &priv->m_usb_ctrl_buf[1]);
																				if ( !result )
																				{
																					cxtr1 = priv->m_usb_ctrl_buf[0];
																					cxtr2 = priv->m_usb_ctrl_buf[1];
																					priv->m_usb_xfer_buf[1] = 0;
																					outval_1 = cxtr1 & cxtr2;
																					if ( (cxtr1 & cxtr2 & 0x140) != 0 )
																						priv->m_usb_xfer_buf[1] |= 0x20u;
																					if ( (outval_1 & 0x180) != 0 )
																						priv->m_usb_xfer_buf[1] |= 0x10u;
																					result = control_positive_xfer(priv, 1, 1);
																					if ( !result )
																					{
																						if ( (outval_1 & 0x180) != 0 )
																						{
																							negoval_tmp = 4;
																							if ( (outval_1 & 0x140) != 0 )
																								negoval_tmp = 8;
																						}
																						else
																						{
																							negoval_tmp = 1;
																							if ( (outval_1 & 0x140) != 0 )
																								negoval_tmp = 2;
																						}
																						priv->m_nego_status = negoval_tmp;
																						spdstr = "10BaseT";
																						if ( (outval_1 & 0x180) != 0 )
																							spdstr = "100BaseTX";
																						dupval = "Half";
																						if ( (outval_1 & 0x140) != 0 )
																							dupval = "Full";
																						printf(
																							"%s: %s %s Duplex Mode (ANAR=0x%04x ANLPAR=0x%04x)\n",
																							priv->m_devops.interface,
																							spdstr,
																							dupval,
																							priv->m_usb_ctrl_buf[0],
																							priv->m_usb_ctrl_buf[1]);
																						result = control_inout_xfer(priv, idxcnt, 2, &outval_2);
																						if ( !result )
																						{
																							result = control_inout_xfer(priv, idxcnt, 3, &outval_3);
																							if ( !result )
																							{
																								printf(
																									"%s: PHY OUI=0x%06x MODEL=0x%02x REV=0x%x (0x%04x,0x%04x)\n",
																									priv->m_devops.interface,
																									(outval_2 << 6) | (outval_3 >> 10),
																									(outval_3 >> 4) & 0x1F,
																									outval_3 & 0xF,
																									outval_2,
																									outval_3);
																								priv->m_usb_xfer_buf[0] = 0xC9;
																								result = control_positive_xfer(priv, 0, 1);
																								if ( !result )
																								{
																									if ( !priv->m_is_pegasus2
																										|| (priv->m_usb_xfer_buf[124] = 0x34,
																												priv->m_usb_xfer_buf[126] = 0x26,
																												priv->m_usb_xfer_buf[127] = 0x30,
																												(result = control_positive_xfer(priv, 124, 4)) == 0) )
																									{
																										for ( i = 0; i < 8; ++i )
																											bulk_xfer(priv);
																										m_start_stop_flag = priv->m_start_stop_flag;
																										priv->m_val_for_inet_start = 1;
																										if ( !m_start_stop_flag )
																											SetEventFlag(priv->m_devops.evfid, 1u);
																										priv->m_val_for_alarm_cb = 10;
																										USec2SysClock(0xF4240u, &priv->m_sysclk);
																										SetAlarm(
																											&priv->m_sysclk,
																											(unsigned int (__cdecl *)(void *))alarm_cb,
																											priv);
																										indindx = 0;
																										priv->m_timer_active = 1;
																										while ( 1 )
																										{
																											priv_tmp7 = priv;
																											do
																											{
																												control_negative_xfer(priv_tmp7, 43, 5);
																												xfer43buftmp = priv->m_usb_xfer_buf[43];
																												if ( (xfer43buftmp & 0x6C) != 0 )
																												{
																													masktmp = xfer43buftmp & 0xC;
																													if ( (priv->m_usb_xfer_buf[43] & 0x60) != 0 )
																													{
																														++priv->m_collisions;
																														masktmp = xfer43buftmp & 0xC;
																													}
																													if ( masktmp )
																														++priv->m_err_tx_carrier;
																													++priv->m_tx_errors;
																												}
																												if ( (priv->m_usb_xfer_buf[45] & 1) != 0 )
																												{
																													plusone_1 = priv->m_rx_errors + 1;
																													++priv->m_err_rx_over;
																													priv->m_rx_errors = plusone_1;
																												}
																												valuse = priv->m_usb_xfer_buf[47];
																												if ( priv->m_usb_xfer_buf[47] )
																												{
																													plusaddx = priv->m_rx_errors + valuse;
																													priv->m_err_rx_missed += valuse;
																													priv->m_rx_errors = plusaddx;
																												}
																												DelayThread(100000);
																												if ( ++indindx >= 11 )
																												{
																													indindx = 0;
																													if ( priv->m_cnt_for_bulk_xfer > 0 )
																													{
																														CpuSuspendIntr(&state);
																														state_1 = state;
																														--priv->m_cnt_for_bulk_xfer;
																														CpuResumeIntr(state_1);
																														bulk_xfer(priv);
																													}
																												}
																												priv_tmp7 = priv;
																											}
																											while ( priv->m_val_for_alarm_cb > 0 );
																											result = control_inout_xfer(priv, idxcnt, 1, &outval_1);
																											if ( result )
																												break;
																											if ( (outval_1 & 4) == 0 )
																											{
																												priv->m_link_status = 0;
																												for ( priv_tmp2 = priv; ; priv_tmp2 = priv )
																												{
																													result = control_inout_xfer(priv_tmp2, idxcnt, 1, &outval_1);
																													if ( result )
																														break;
																													if ( (outval_1 & 0x24) == 36 )
																													{
																														priv->m_link_status = 1;
																														goto LABEL_86;
																													}
																													DelayThread(100000);
																												}
																												return result;
																											}
LABEL_86:
																											priv->m_val_for_alarm_cb = 10;
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																			return result;
																		}
																		DelayThread(100000);
																		++indindx2;
																		priv_tmp3 = priv;
																		if ( indindx2 >= 30 )
																			priv->m_link_status = 0;
																	}
																}
															}
															DelayThread(10000);
															priv_tmp6 = priv;
														}
													}
												}
											}
										}
									}
									return result;
								}
								result = g_verbose;
								if ( !g_verbose )
									return result;
								printf("%s: ", priv->m_devops.interface);
								printf("sceInetRegisterNetDevice -> %d", regres);
								return printf("\n");
							}
							DelayThread(10000);
							priv_tmp5 = priv;
						}
					}
				}
			}
		}
	}
	return result;
}
// 403504: using guessed type int g_verbose;

//----- (00401760) --------------------------------------------------------
struct an986_priv *__fastcall do_allocate_mem_for_inet(char *vendor_name, char *device_name, int is_pegasus2)
{
	struct an986_priv *priv_1; // $s0
	struct an986_priv *priv_2; // $v0
	int magictmp1; // $v0
	int efid; // $v0
	sceInetDevOps_t *p_m_devops; // $a0
	int thid; // $v0
	int started; // $s1
	iop_event_t efparam; // [sp+10h] [-28h] BYREF
	iop_thread_t thparam; // [sp+20h] [-18h] BYREF

	priv_1 = (struct an986_priv *)sceInetAllocMem(0, 888);
	if ( priv_1 )
	{
		bzero(priv_1, 888);
		magictmp1 = g_magic_count;
		priv_1->m_is_pegasus2 = is_pegasus2;
		priv_1->m_magic_cur = magictmp1;
		g_magic_count = magictmp1 + 1;
		sprintf(priv_1->m_devops.interface, "an986,%d", magictmp1);
		priv_1->m_devops.module_name = "an986";
		priv_1->m_devops.prot_ver = 2;
		priv_1->m_devops.flags = 1040;
		priv_1->m_devops.start = (int (__cdecl *)(void *, int))an986_inet_start;
		priv_1->m_devops.stop = (int (__cdecl *)(void *, int))an986_inet_stop;
		priv_1->m_devops.xmit = (int (__cdecl *)(void *, int))an986_inet_xmit;
		priv_1->m_devops.control = (int (__cdecl *)(void *, int, void *, int))an986_inet_control;
		priv_1->m_devops.vendor_name = vendor_name;
		priv_1->m_devops.device_name = device_name;
		priv_1->m_devops.impl_ver = 0;
		priv_1->m_devops.priv = priv_1;
		priv_1->m_devops.mtu = 1500;
		memset(&efparam, 0, sizeof(efparam));
		efid = CreateEventFlag(&efparam);
		priv_1->m_efid = efid;
		if ( efid > 0 )
		{
			thparam.attr = 0x2000000;
			thparam.thread = (void (__cdecl *)(void *))inet_thread_proc;
			thparam.option = 0;
			thparam.priority = g_thpri;
			thparam.stacksize = g_thstack;
			thid = CreateThread(&thparam);
			priv_1->m_thid = thid;
			if ( thid > 0 )
			{
				started = StartThread(thid, priv_1);
				priv_2 = priv_1;
				if ( !started )
					return priv_2;
				if ( g_verbose )
				{
					printf("%s: ", priv_1->m_devops.interface);
					printf("StartThread -> %d", started);
					printf("\n");
				}
				DeleteThread(priv_1->m_thid);
			}
			else if ( g_verbose )
			{
				printf("%s: ", priv_1->m_devops.interface);
				printf("CreateThread -> %d", priv_1->m_thid);
				printf("\n");
			}
			DeleteEventFlag(priv_1->m_efid);
			p_m_devops = &priv_1->m_devops;
		}
		else
		{
			p_m_devops = &priv_1->m_devops;
			if ( g_verbose )
			{
				printf("%s: ", priv_1->m_devops.interface);
				printf("CreateEventFlag -> %d", priv_1->m_efid);
				printf("\n");
				p_m_devops = &priv_1->m_devops;
			}
		}
		sceInetFreeMem(p_m_devops, priv_1);
		return 0;
	}
	else
	{
		priv_2 = 0;
		if ( g_verbose )
		{
			printf("%s: ", (const char *)320);
			printf("sceInetAllocMem(%d) -> no space or not ready", 888);
			printf("\n");
			return 0;
		}
	}
	return priv_2;
}
// 4034F8: using guessed type int g_thpri;
// 4034FC: using guessed type int g_thstack;
// 403500: using guessed type int g_magic_count;
// 403504: using guessed type int g_verbose;

//----- (004019E4) --------------------------------------------------------
struct an986_devinfo *__fastcall do_check_static_descriptor(
				int is_probe,
				unsigned __int16 id_vendor,
				unsigned __int16 id_product)
{
	struct an986_devinfo *cur_devinfo; // $s1
	int cur_devinfo_count; // $s0
	const char **i; // $a2
	int m_chip; // $v1
	struct an986_devinfo *result; // $v0
	const char *cur_chipname; // $a1

	if ( is_probe && g_verbose )
		printf("an986: idVendor=0x%04x idProduct=0x%04x\n", id_vendor, id_product);
	cur_devinfo = g_an986_devinfo;
	cur_devinfo_count = 52;
	for ( i = &g_an986_devinfo[0].m_device_name;
				(const char *)id_vendor != *(i - 3) || (const char *)id_product != *(i - 1);
				i += 5 )
	{
		++cur_devinfo;
		if ( cur_devinfo_count-- <= 0 )
			return 0;
	}
	if ( is_probe && g_verbose )
		printf("an986: %s, %s", *(i - 2), *i);
	m_chip = cur_devinfo->m_chip;
	if ( cur_devinfo->m_chip == 'p' )
	{
		result = cur_devinfo;
		if ( is_probe )
		{
			result = cur_devinfo;
			if ( g_verbose )
			{
				printf(" [pegasus] -> supported\n");
				return cur_devinfo;
			}
		}
	}
	else if ( m_chip == 'P' )
	{
		result = cur_devinfo;
		if ( is_probe )
		{
			result = cur_devinfo;
			if ( g_verbose )
			{
				printf(" [pegasusII] -> supported\n");
				return cur_devinfo;
			}
		}
	}
	else
	{
		result = 0;
		if ( is_probe )
		{
			result = 0;
			if ( g_verbose )
			{
				cur_chipname = "unknown";
				if ( m_chip == 'k' )
					cur_chipname = "klsi";
				printf(" [%s] -> unsupported\n", cur_chipname);
				return 0;
			}
		}
	}
	return result;
}
// 403090: using guessed type an986_devinfo g_an986_devinfo[53];
// 403504: using guessed type int g_verbose;

//----- (00401BA0) --------------------------------------------------------
int __fastcall an986_ldd_connect(int devId)
{
	UsbDeviceDescriptor *devdesc2; // $s0
	int result; // $v0
	struct an986_devinfo *v4; // $s5
	UsbDeviceDescriptor *devdesc; // $s6
	UsbInterfaceDescriptor *intfdesc; // $a1
	UsbEndpointDescriptor *bulk_in_desc; // $s3
	UsbEndpointDescriptor *bulk_out_desc; // $s1
	UsbEndpointDescriptor *int_in_desc; // $s2
	struct an986_priv *mem_for_inet; // $s0
	int pipe1; // $v0
	int pipe2; // $v0
	int pipe3; // $v0
	int pipe4; // $v0

	if ( g_verbose )
		printf("an986_attach,%d: called\n", devId);
	devdesc2 = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(devId, 0, 1u);
	result = -1;
	if ( devdesc2 )
	{
		v4 = do_check_static_descriptor(0, devdesc2->idVendor, devdesc2->idProduct);
		if ( !v4 )
			return -1;
		devdesc = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(devId, devdesc2, 2u);
		if ( !devdesc )
			return -1;
		result = -1;
		if ( devdesc->bDeviceClass != 1 )
			return result;
		intfdesc = (UsbInterfaceDescriptor *)sceUsbdScanStaticDescriptor(devId, devdesc, 4u);
		if ( !intfdesc )
			return -1;
		result = -1;
		if ( intfdesc->bNumEndpoints == 3 )
		{
			bulk_in_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, intfdesc, 5u);
			result = -1;
			if ( bulk_in_desc )
			{
				result = -1;
				if ( (bulk_in_desc->bEndpointAddress & 0x80) != 0 )
				{
					result = -1;
					if ( (bulk_in_desc->bmAttributes & 3) == 2 )
					{
						bulk_out_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, bulk_in_desc, 5u);
						result = -1;
						if ( bulk_out_desc )
						{
							result = -1;
							if ( (bulk_out_desc->bEndpointAddress & 0x80) == 0 )
							{
								result = -1;
								if ( (bulk_out_desc->bmAttributes & 3) == 2 )
								{
									int_in_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, bulk_out_desc, 5u);
									result = -1;
									if ( int_in_desc )
									{
										result = -1;
										if ( (int_in_desc->bEndpointAddress & 0x80) != 0 )
										{
											result = -1;
											if ( (int_in_desc->bmAttributes & 3) == 3 )
											{
												mem_for_inet = do_allocate_mem_for_inet(
																				 (char *)v4->m_vendor_name,
																				 (char *)v4->m_device_name,
																				 v4->m_chip == 'P');
												if ( !mem_for_inet )
													return -1;
												pipe1 = sceUsbdOpenPipe(devId, 0);
												mem_for_inet->m_ctrl_pipe = pipe1;
												if ( pipe1 < 0 )
													return -1;
												pipe2 = sceUsbdOpenPipe(devId, bulk_in_desc);
												mem_for_inet->m_bulk_in_pipe = pipe2;
												if ( pipe2 < 0 )
													return -1;
												pipe3 = sceUsbdOpenPipeAligned(devId, bulk_out_desc);
												mem_for_inet->m_bulk_out_pipe = pipe3;
												if ( pipe3 < 0 )
													return -1;
												pipe4 = sceUsbdOpenPipe(devId, int_in_desc);
												mem_for_inet->m_int_in_pipe = pipe4;
												if ( pipe4 < 0 )
													return -1;
												sceUsbdSetPrivateData(devId, mem_for_inet);
												mem_for_inet->m_devops.bus_type = 1;
												sceUsbdGetDeviceLocation(devId, mem_for_inet->m_devops.bus_loc);
												mem_for_inet->m_subclass = devdesc->bDeviceSubClass;
												ef_set_wrap(mem_for_inet, 0, 1u);
												result = 0;
												if ( g_verbose )
												{
													printf("an986_attach,%d: -> attached\n", devId);
													return 0;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}
// 403504: using guessed type int g_verbose;

//----- (00401E3C) --------------------------------------------------------
int __fastcall an986_ldd_disconnect(int devId)
{
	struct an986_priv *priv; // $v0
	int evfid; // $a0

	if ( g_verbose )
		printf("an986_detach,%d: -> detached\n", devId);
	priv = (struct an986_priv *)sceUsbdGetPrivateData(devId);
	if ( !priv )
		return -1;
	evfid = priv->m_devops.evfid;
	priv->m_val_for_inet_stop = 1;
	SetEventFlag(evfid, 2u);
	return 0;
}
// 403504: using guessed type int g_verbose;

//----- (00401EA4) --------------------------------------------------------
int __fastcall an986_ldd_probe(int devId)
{
	int devid_tmp; // $s3
	UsbStringDescriptor *strdesc1; // $s2
	int idx7; // $s0
	char *curstre; // $v1
	const char *nul_or_com; // $a1
	UsbStringDescriptor *strdesc2; // $v0
	int bLength; // $s1
	int xlenx; // $s0
	int hxstr; // $a1
	UsbDeviceDescriptor *devdesc; // $v0
	int result; // $v0
	char strlocbuf[16]; // [sp+10h] [-10h] BYREF

	devid_tmp = devId;
	if ( g_verbose )
	{
		strdesc1 = 0;
		printf("an986_probe,%d: called", devId);
		if ( sceUsbdGetDeviceLocation(devid_tmp, (u8 *)strlocbuf) )
		{
			printf(" dev_id=%d\n", devid_tmp);
		}
		else
		{
			idx7 = 0;
			printf(" Loc:USB-");
			curstre = strlocbuf;
			do
			{
				if ( !*curstre )
					break;
				nul_or_com = (const char *)&dword_4036A8;
				if ( idx7 )
					nul_or_com = ",";
				++idx7;
				printf("%s%d", nul_or_com, (unsigned __int8)*curstre);
				curstre = &strlocbuf[idx7];
			}
			while ( idx7 < 7 );
		}
		while ( 1 )
		{
			printf("\n");
			strdesc2 = (UsbStringDescriptor *)sceUsbdScanStaticDescriptor(devid_tmp, strdesc1, 0);
			strdesc1 = strdesc2;
			devId = devid_tmp;
			if ( !strdesc2 )
				break;
			bLength = strdesc2->bLength;
			xlenx = 0;
			if ( strdesc2->bLength )
			{
				do
				{
					hxstr = *(&strdesc1->bLength + xlenx++);
					printf(" %02x", hxstr);
				}
				while ( xlenx < bLength );
			}
		}
	}
	devdesc = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(devId, 0, 1u);
	if ( !devdesc )
		return 0;
	if ( !do_check_static_descriptor(1, devdesc->idVendor, devdesc->idProduct) )
		return 0;
	g_resident_flag = 1;
	if ( g_load_mode == 't' )
		return 0;
	result = 1;
	if ( g_verbose )
	{
		printf("an986_probe,%d: -> accepted\n", devid_tmp);
		return 1;
	}
	return result;
}
// 403504: using guessed type int g_verbose;
// 4036A8: using guessed type int dword_4036A8;
// 403700: using guessed type int g_resident_flag;
// 403704: using guessed type int g_load_mode;
// 401EA4: using guessed type u8 strlocbuf[16];

//----- (00402050) --------------------------------------------------------
int do_print_version()
{
	printf("AN986 (%s)\n", version_ptr);
	return 1;
}
// 4036F0: using guessed type char *version_ptr;

//----- (0040207C) --------------------------------------------------------
int do_print_help()
{
	do_print_version();
	printf("Usage: an986 [-verbose] [-list] [thpri=<prio>] [thstack=<stack>] [-p <id>] [-P <id>]\n");
	return 2;
}

//----- (004020A8) --------------------------------------------------------
int __fastcall scan_number(char *inchr, int *outptr)
{
	char *curchrptr; // $a3
	int base; // $t1
	int curchrchr; // $v1
	int curval; // $t0
	int currel; // $a0

	curchrptr = inchr;
	base = 10;
	if ( *inchr == '0' && inchr[1] )
	{
		base = 8;
		curchrptr = inchr + 1;
		if ( inchr[1] == 'x' )
		{
			curchrptr = inchr + 2;
			base = 16;
		}
	}
	curchrchr = (unsigned __int8)*curchrptr;
	curval = 0;
	if ( *curchrptr )
	{
		while ( 1 )
		{
			if ( (unsigned int)(curchrchr - 48) >= 0xA )
			{
				if ( (unsigned int)(curchrchr - 97) >= 6 )
					break;
				currel = (char)curchrchr - 87;
			}
			else
			{
				currel = (char)curchrchr - 48;
			}
			if ( currel >= base )
				break;
			curchrchr = (unsigned __int8)*++curchrptr;
			curval = curval * base + currel;
			if ( !*curchrptr )
			{
				*outptr = curval;
				return 0;
			}
		}
	}
	printf("%s: %s - invalid digit\n", "scan_number", inchr);
	return -1;
}

//----- (00402188) --------------------------------------------------------
int do_print_list()
{
	int total_devinfo; // $s2
	struct an986_devinfo *cur_devinfo; // $s1
	const char **p_m_device_name; // $s0
	int m_chip; // $v1
	const char *cur_devname; // $a0

	do_print_version();
	total_devinfo = 52;
	printf("  VID   PID   Vendor          Device          Chip\n");
	printf("------------------------------------------------------\n");
	cur_devinfo = g_an986_devinfo;
	p_m_device_name = &g_an986_devinfo[0].m_device_name;
	do
	{
		printf("  %04x", *(p_m_device_name - 3));
		printf("  %04x", *(p_m_device_name - 1));
		printf("  %-14s", *(p_m_device_name - 2));
		printf("  %-14s", *p_m_device_name);
		m_chip = cur_devinfo->m_chip;
		if ( cur_devinfo->m_chip == 'k' )
		{
			cur_devname = "  KLSI";
		}
		else
		{
			if ( cur_devinfo->m_chip >= 0x6C )
			{
				if ( m_chip == 'p' )
				{
					cur_devname = "  Pegasus";
					goto LABEL_11;
				}
			}
			else if ( m_chip == 'P' )
			{
				cur_devname = "  PegasusII";
				goto LABEL_11;
			}
			cur_devname = "  Unknown";
		}
LABEL_11:
		p_m_device_name += 5;
		printf(cur_devname);
		++cur_devinfo;
		printf("\n");
	}
	while ( total_devinfo-- > 0 );
	return 3;
}
// 403090: using guessed type an986_devinfo g_an986_devinfo[53];

//----- (004022CC) --------------------------------------------------------
int __fastcall an986_init(int ac, char **av)
{
	int ac_min_one; // $s3
	const char **i; // $s2
	bool condtmp1; // dc
	int chipforce; // $v0
	const char *thpricur; // $s1
	char *thpricurx; // $s0
	int thirpcurxchr; // $v0
	const char *stkval; // $s1
	int result; // $v0
	int loadmode_tmp; // $v0
	unsigned int vidtmp; // [sp+10h] [-8h] BYREF

	ac_min_one = ac - 1;
	g_load_mode = 'n';
	g_resident_flag = 1;
	for ( i = (const char **)(av + 1); ac_min_one > 0; ++i )
	{
		if ( !strcmp("-help", *i) )
			return do_print_help();
		if ( !strcmp("-version", *i) )
			return do_print_version();
		if ( !strcmp("-verbose", *i) )
		{
			g_verbose = 1;
			--ac_min_one;
		}
		else
		{
			if ( !strcmp("-list", *i) )
				return do_print_list();
			condtmp1 = strcmp("-p", *i) != 0;
			chipforce = 'p';
			if ( !condtmp1 || (condtmp1 = strcmp("-P", *i) == 0, chipforce = 'P', condtmp1) )
			{
				g_an986_devinfo[0].m_chip = chipforce;
				--ac_min_one;
				++i;
				if ( ac_min_one <= 0 || scan_number((char *)*i, (int *)&vidtmp) )
					return do_print_help();
				g_an986_devinfo[0].m_vendor_id = (vidtmp >> 16) & 0xFFFF;
				g_an986_devinfo[0].m_product_id = vidtmp & 0xFFFF;
LABEL_34:
				--ac_min_one;
				continue;
			}
			if ( !strncmp("thpri=", *i, 6) )
			{
				thpricur = *i;
				thpricurx = (char *)(*i + 6);
				if ( (look_ctype_table(*thpricurx) & 4) == 0 )
					return do_print_help();
				g_thpri = strtol(thpricurx, 0, 10);
				if ( (unsigned int)(g_thpri - 9) >= 0x73 )
					return do_print_help();
				if ( !thpricur[6] )
					goto LABEL_34;
				while ( (look_ctype_table(*thpricurx) & 4) != 0 )
				{
					thirpcurxchr = *++thpricurx;
					if ( !*thpricurx )
						goto LABEL_27;
				}
			}
			else
			{
				if ( strncmp("thstack=", *i, 8) )
				{
					condtmp1 = strcmp("AUTOLOAD", *i) == 0;
					loadmode_tmp = 'a';
					if ( !condtmp1 )
					{
						condtmp1 = strcmp("lmode=AUTOLOAD", *i) == 0;
						loadmode_tmp = 'a';
						if ( !condtmp1 )
						{
							condtmp1 = strcmp("TESTLOAD", *i) == 0;
							loadmode_tmp = 't';
							if ( !condtmp1 )
							{
								condtmp1 = strcmp("lmode=TESTLOAD", *i) != 0;
								loadmode_tmp = 't';
								if ( condtmp1 )
									return do_print_help();
							}
						}
					}
					g_load_mode = loadmode_tmp;
					g_resident_flag = 0;
					goto LABEL_34;
				}
				stkval = *i;
				thpricurx = (char *)(*i + 8);
				if ( (look_ctype_table(*thpricurx) & 4) == 0 )
					return do_print_help();
				g_thstack = strtol(thpricurx, 0, 10);
				if ( stkval[8] )
				{
					do
					{
						if ( (look_ctype_table(*thpricurx) & 4) == 0 )
							break;
						++thpricurx;
					}
					while ( *thpricurx );
				}
				if ( !strcmp(thpricurx, "KB") )
				{
					g_thstack <<= 10;
					--ac_min_one;
					continue;
				}
			}
			thirpcurxchr = *thpricurx;
LABEL_27:
			--ac_min_one;
			if ( thirpcurxchr )
				return do_print_help();
		}
	}
	condtmp1 = sceUsbdRegisterLdd(&g_an986_ldd) != 0;
	result = 4;
	if ( !condtmp1 )
	{
		if ( g_verbose )
			printf("an986_start: load_mode='%c' resident_flag=%d\n", g_load_mode, g_resident_flag);
		if ( g_load_mode == 't' )
		{
			sceUsbdUnregisterLdd(&g_an986_ldd);
			return 5;
		}
		else if ( g_resident_flag )
		{
			do_print_version();
			return 0;
		}
		else
		{
			sceUsbdUnregisterLdd(&g_an986_ldd);
			return 6;
		}
	}
	return result;
}
// 403090: using guessed type an986_devinfo g_an986_devinfo[53];
// 4034B4: using guessed type sceUsbdLddOps g_an986_ldd;
// 4034F8: using guessed type int g_thpri;
// 4034FC: using guessed type int g_thstack;
// 403504: using guessed type int g_verbose;
// 403700: using guessed type int g_resident_flag;
// 403704: using guessed type int g_load_mode;

//----- (00402694) --------------------------------------------------------
int _start(int ac, char **av)
{
	int result; // $v0
	int initval; // $v0
	int initval_rshift; // $s0
	int initval_shifted; // $a1

	if ( RegisterLibraryEntries(&_exp_an986) )
	{
		printf("an986: module already loaded\n");
		return 1;
	}
	else
	{
		initval = an986_init(ac, av);
		initval_rshift = initval;
		if ( g_verbose )
			printf("an986: an986_init() -> 0x%x\n", initval);
		result = 0;
		if ( initval_rshift )
		{
			ReleaseLibraryEntries(&_exp_an986);
			initval_shifted = 16 * initval_rshift;
			if ( g_resident_flag )
				return initval_shifted | 5;
			else
				return initval_shifted | 1;
		}
	}
	return result;
}
// 402750: using guessed type int exports[2];
// 403504: using guessed type int g_verbose;
// 403700: using guessed type int g_resident_flag;
