
#include "irx_imports.h"
#include <usbd_macro.h>

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

#define VERBOSE_PRINTF(...) \
	{ \
		if ( g_verbose ) \
		{ \
			printf(__VA_ARGS__);\
		} \
	}

//-------------------------------------------------------------------------
// Function declarations

static void bulk_xfer(struct an986_priv *priv);
static int an986_ldd_connect(int devId);
static int an986_ldd_disconnect(int devId);
static int an986_ldd_probe(int devId);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_an986;
static struct an986_devinfo g_an986_devinfo[] =
{
	{ '-', 0x0000, "Unknown", 0x0000, "Unknown" },
	{ 'k', 0x03e8, "AOX", 0x0008, "101" },
	{ 'p', 0x0411, "Melco", 0x0001, "LUA-TX" },
	{ 'p', 0x0411, "Melco", 0x0005, "LUA-TX" },
	{ 'P', 0x0411, "Melco", 0x0009, "LUA2-TX" },
	{ '-', 0x0411, "Melco", 0x0012, "LUA-KTX" },
	{ '-', 0x0423, "CATC", 0x000a, "NetMate" },
	{ '-', 0x0423, "CATC", 0x000c, "NetMate2" },
	{ 'k', 0x04bb, "I-O Data", 0x0901, "ET/T" },
	{ 'p', 0x04bb, "I-O Data", 0x0904, "ET/TX" },
	{ 'k', 0x0506, "3Com", 0x03e8, "3C19250" },
	{ 'k', 0x0557, "ATEN", 0x2002, "UC-10T" },
	{ 'k', 0x0557, "ATEN", 0x4000, "DSB-650" },
	{ 'k', 0x0565, "Peracom", 0x0002, "Enet" },
	{ 'k', 0x0565, "Peracom", 0x0005, "Enet2" },
	{ 'k', 0x056e, "Elecom", 0x4000, "LD-USB/T" },
	{ 'p', 0x056e, "Elecom", 0x4002, "LD-USB/TX" },
	{ 'P', 0x056e, "Elecom", 0x4005, "LD-USBL/TX" },
	{ 'k', 0x05e9, "KLSI", 0x0008, "KL5KUSB101B" },
	{ 'p', 0x05e9, "KLSI", 0x0009, "Pegasus" },
	{ 'k', 0x066b, "Linksys", 0x2202, "USB10T" },
	{ 'p', 0x066b, "Linksys", 0x2203, "USB100TX" },
	{ 'p', 0x066b, "Linksys", 0x2204, "USB100TX" },
	{ 'p', 0x066b, "Linksys", 0x2206, "USB" },
	{ 'P', 0x066b, "Linksys", 0x400b, "USB100TX B" },
	{ 'k', 0x06e1, "ADS", 0x0008, "USBS-10B" },
	{ 'k', 0x0707, "SMC", 0x0100, "2202" },
	{ 'p', 0x0707, "SMC", 0x0200, "2202" },
	{ 'p', 0x07a6, "ADMtek", 0x0986, "Pegasus" },
	{ 'P', 0x07a6, "ADMtek", 0x8511, "PegasusII" },
	{ 'k', 0x07aa, "Corega", 0x0001, "USB-T" },
	{ 'p', 0x07aa, "Corega", 0x0004, "USB-TX" },
	{ 'P', 0x07aa, "Corega", 0x000d, "USB-TXS" },
	{ 'p', 0x07b8, "D-Link", 0xabc1, "DU-E10" },
	{ 'k', 0x07b8, "D-Link", 0x4000, "DU-E10" },
	{ 'p', 0x07b8, "D-Link", 0x4002, "DU-E100" },
	{ 'P', 0x07b8, "D-Link", 0x4102, "DU-E100 B1" },
	{ 'p', 0x083a, "Accton", 0x1046, "USB10/100" },
	{ 'k', 0x0846, "NetGear", 0x1001, "EA101" },
	{ 'p', 0x08dd, "Billionton", 0x0986, "USB100N" },
	{ 'p', 0x08dd, "Billionton", 0x0987, "USBLP-100" },
	{ 'p', 0x08dd, "Billionton", 0x0988, "USBEL-100" },
	{ 'P', 0x08dd, "Billionton", 0x8511, "USBE-100" },
	{ 'k', 0x13d2, "Shark", 0x0400, "Pocket" },
	{ '-', 0x1485, "PSION DACOM", 0x0002, "Gold Port" },
	{ 'p', 0x15e8, "SOHOware", 0x9100, "NUB100" },
	{ 'k', 0x1645, "Entrega", 0x0005, "E45" },
	{ 'k', 0x2001, "D-Link", 0x4000, "DSB-650C" },
	{ 'p', 0x2001, "D-Link", 0x4001, "DSB-650TX" },
	{ 'p', 0x2001, "D-Link", 0x4002, "DSB-650TX" },
	{ 'p', 0x2001, "D-Link", 0x4003, "DSB-650TX-PNA" },
	{ 'P', 0x2001, "D-Link", 0x400b, "DSB-650TX B1" },
	{ 'p', 0x2001, "D-Link", 0xabc1, "DSB-650" },
}; // weak
static sceUsbdLddOps g_an986_ldd =
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
static int g_thpri = 40; // weak
static int g_thstack = 16384; // weak
static int g_magic_count = 0; // weak
static int g_verbose = 0; // weak
static char *version_ptr = "Version 1.75.0"; // weak
static int g_resident_flag; // weak
static int g_load_mode; // weak


//----- (00400000) --------------------------------------------------------
static int ef_wait_wrap(struct an986_priv *priv, u32 efbits)
{
	int efret; // $s1
	u32 efres; // [sp+10h] [-8h] BYREF

	efret = WaitEventFlag(priv->m_efid, efbits, 17, &efres);
	if ( efret )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("WaitEventFlag (%d)", efret);
		VERBOSE_PRINTF("\n");
		return -1;
	}
	return priv->m_ef_wait_retval;
}
// 403504: using guessed type int g_verbose;

//----- (00400088) --------------------------------------------------------
static void ef_set_wrap(struct an986_priv *priv, int wait_retval, u32 efbits)
{
	int efret; // $s1

	priv->m_ef_wait_retval = wait_retval;
	efret = SetEventFlag(priv->m_efid, efbits);
	if ( efret )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("SetEventFlag (%d)", efret);
		VERBOSE_PRINTF("\n");
	}
}
// 403504: using guessed type int g_verbose;

//----- (00400104) --------------------------------------------------------
static void an986_done(int efbits, int doneval, void *userdata)
{
	struct an986_priv *priv; // $a0

	priv = (struct an986_priv *)userdata;
	if ( efbits )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("%s: -> 0x%x\n", "an986_done", efbits);
		VERBOSE_PRINTF("\n");
	}
	priv->m_done_related = doneval;
	ef_set_wrap(priv, efbits, 4u);
}
// 403504: using guessed type int g_verbose;

//----- (00400194) --------------------------------------------------------
static int control_negative_xfer(struct an986_priv *priv, int xferoffs, int xferlen)
{
	int xferret; // $s0

	xferret = sceUsbdControlTransfer(priv->m_ctrl_pipe, 0xC0, 0xF0, 0, xferoffs, ( xferlen < 2 ) ? 2 : xferlen, &priv->m_usb_xfer_buf[xferoffs], an986_done, priv);
	if ( xferret )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("sceUsbdControlTransfer -> 0x%x", xferret);
		VERBOSE_PRINTF("\n");
		return -1;
	}
	return ef_wait_wrap(priv, 4u);
}
// 403504: using guessed type int g_verbose;

//----- (00400264) --------------------------------------------------------
static int control_positive_xfer(struct an986_priv *priv, int xferoffs, int xferlen)
{
	int xferret; // $s0

	xferret = sceUsbdControlTransfer(priv->m_ctrl_pipe, 0x40, 0xF1, 0, xferoffs, ( xferlen < 2 ) ? 2 : xferlen, &priv->m_usb_xfer_buf[xferoffs], an986_done, priv);
	if ( xferret )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("sceUsbdControlTransfer -> 0x%x", xferret);
		VERBOSE_PRINTF("\n");
		return -1;
	}
	return ef_wait_wrap(priv, 4u);
}
// 403504: using guessed type int g_verbose;

//----- (00400334) --------------------------------------------------------
static int control_inout_xfer(struct an986_priv *priv, char linkval, char xval, u16 *outptr)
{
	int result; // $v0

	priv->m_usb_xfer_buf[37] = linkval & 0x1F;
	priv->m_usb_xfer_buf[38] = 0;
	priv->m_usb_xfer_buf[39] = 0;
	priv->m_usb_xfer_buf[40] = (xval & 0x1F) | 0x40;
	result = control_positive_xfer(priv, 37, 4);
	if ( result )
		return result;
	while ( 1 )
	{
		result = control_negative_xfer(priv, 40, 1);
		if ( result )
			return result;
		if ( !!(priv->m_usb_xfer_buf[40] & 0x80) )
			break;
		DelayThread(10000);
	}
	result = control_negative_xfer(priv, 37, 4);
	if ( result )
		return result;
	*outptr = priv->m_usb_xfer_buf[38] | (priv->m_usb_xfer_buf[39] << 8);
	return 0;
}

//----- (004003F4) --------------------------------------------------------
static void an986_rx_done(int aresult, int acount, void *userdata)
{
	struct an986_priv *priv; // $s0
	sceInetPkt_t *pkt;

	pkt = (sceInetPkt_t *)userdata;
	priv = (struct an986_priv *)pkt->m_reserved1;
	if ( aresult )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("%s: -> 0x%x\n", "an986_rx_done", aresult);
		VERBOSE_PRINTF("\n");
	}
	priv->m_rx_packets += 1;
	pkt->m_reserved1 = NULL;
	if ( priv->m_start_stop_flag || priv->m_val_for_inet_stop )
	{
		sceInetFreePkt(&priv->m_devops, pkt);
	}
	else if ( acount < 68 )
	{
		priv->m_rx_errors += 1;
		sceInetFreePkt(&priv->m_devops, pkt);
	}
	else
	{
		if ( !!(pkt->rp[acount - 2] & 1) )
		{
			priv->m_multicast += 1;
		}
		if ( !!(pkt->rp[acount - 2] & 2) )
		{
			priv->m_err_rx_length += 1;
		}
		if ( !!(pkt->rp[acount - 2] & 4) )
		{
			priv->m_err_rx_length += 1;
		}
		if ( !!(pkt->rp[acount - 2] & 8) )
		{
			priv->m_err_rx_crc += 1;
		}
		if ( !!(pkt->rp[acount - 2] & 0x10) )
		{
			priv->m_err_rx_frame += 1;
		}
		if ( (pkt->rp[acount - 2] & 0x1E) )
		{
			priv->m_rx_errors += 1;
			sceInetFreePkt(&priv->m_devops, pkt);
		}
		else
		{
			priv->m_rx_bytes = priv->m_rx_bytes - 8 + acount;
			pkt->wp += acount - 8;
			sceInetPktEnQ(&priv->m_devops.rcvq, pkt);
			SetEventFlag(priv->m_devops.evfid, 4u);
		}
	}
	bulk_xfer(priv);
	priv->m_val_for_alarm_cb = 10;
}
// 403504: using guessed type int g_verbose;

//----- (004005E0) --------------------------------------------------------
static void bulk_xfer(struct an986_priv *priv)
{
	sceInetPkt_t *pkt; // $v0
	int xferret; // $s1
	int state; // [sp+18h] [-8h] BYREF

	pkt = sceInetAllocPkt(&priv->m_devops, 1524);
	if ( !pkt )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("sceInetAllocPkt(%d) - no space", 1524);
		VERBOSE_PRINTF("\n");
		CpuSuspendIntr(&state);
		priv->m_cnt_for_bulk_xfer += 1;
		CpuResumeIntr(state);
		return;
	}
	pkt->m_reserved1 = (void *)priv;
	pkt->rp += 2;
	pkt->wp += 2;
	xferret = sceUsbdTransferPipe(priv->m_bulk_in_pipe, pkt->wp, 0x5F2u, NULL, an986_rx_done, pkt);
	if ( xferret )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("sceUsbdBulkTransfer -> 0x%x\n", xferret);
		VERBOSE_PRINTF("\n");
		sceInetFreePkt(&priv->m_devops, pkt);
	}
}
// 403504: using guessed type int g_verbose;

//----- (0040071C) --------------------------------------------------------
static void an986_tx_done(int aresult, int acount, void *userdata)
{
	struct an986_priv *priv; // $s1
	sceInetPkt_t *pkt;

	(void)acount;
	pkt = (sceInetPkt_t *)userdata;
	priv = (struct an986_priv *)pkt->m_reserved1;
	if ( aresult )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("%s: -> 0x%x\n", "an986_tx_done", aresult);
		VERBOSE_PRINTF("\n");
	}
	pkt->m_reserved1 = NULL;
	sceInetFreePkt(&priv->m_devops, pkt);
}
// 403504: using guessed type int g_verbose;

//----- (004007AC) --------------------------------------------------------
static unsigned int alarm_cb(void *userdata)
{
	struct an986_priv *priv;

	priv = (struct an986_priv *)userdata;
	if ( (int)(priv->m_val_for_alarm_cb) > 0 )
		priv->m_val_for_alarm_cb -= 1;
	return priv->m_sysclk.lo;
}

//----- (004007DC) --------------------------------------------------------
static int an986_inet_start(void *userdata, int unused)
{
	struct an986_priv *priv;

	(void)unused;
	priv = (struct an986_priv *)userdata;
	priv->m_start_stop_flag = 0;
	if ( priv->m_val_for_inet_start )
		SetEventFlag(priv->m_devops.evfid, 1u);
	else
		ef_set_wrap(priv, 0, 2u);
	return 0;
}

//----- (00400840) --------------------------------------------------------
static int an986_inet_stop(void *userdata, int unused)
{
	struct an986_priv *priv;

	(void)unused;
	priv = (struct an986_priv *)userdata;
	priv->m_start_stop_flag = 1;
	if ( !priv->m_val_for_inet_stop )
		return 0;
	TerminateThread(priv->m_thid);
	DeleteThread(priv->m_thid);
	DeleteEventFlag(priv->m_efid);
	if ( priv->m_timer_active )
		CancelAlarm(alarm_cb, priv);
	sceInetUnregisterNetDevice(&priv->m_devops);
	sceInetFreeMem(&priv->m_devops, priv);
	return 0;
}

//----- (004008F4) --------------------------------------------------------
static int an986_inet_xmit(void *userdata, int unused)
{
  int xferres; // $s3
  sceInetPkt_t *pkt; // $s2
  u32 xrp2;
  struct an986_priv *priv;
  int dropped;

	(void)unused;
	priv = (struct an986_priv *)userdata;
	dropped = 0;
  xferres = -1;
  pkt = sceInetPktDeQ(&priv->m_devops.sndq);
  if ( !pkt )
  {
  	dropped = 1;
  }
  if ( !dropped && (priv->m_start_stop_flag || priv->m_val_for_inet_stop || !priv->m_link_status) )
  {
		dropped = 1;
  }
  if ( !dropped )
  {
  	xrp2 = pkt->wp - pkt->rp;
  	if ( xrp2 - 60 >= 0x5AF )
  		dropped = 1;
  }
  if ( !dropped )
  {
  	pkt->rp -= 2;
  	if ( !!((uiptr)(pkt->rp) & 3) )
  		dropped = 1;
  }
  if ( !dropped )
  {
    *((u16 *)(pkt->rp)) = xrp2;
    priv->m_tx_packets += 1;
    priv->m_tx_bytes += xrp2;
    xrp2 += 2;
    if ( !(((u8)xrp2) & 0x3F) )
      xrp2 += 1;
    pkt->m_reserved1 = (void *)priv;
    while ( 1 )
    {
      xferres = sceUsbdTransferPipe(
                  priv->m_bulk_out_pipe,
                  pkt->rp + 2,
                  xrp2,
                  NULL,
                  an986_tx_done,
                  pkt);
      if ( !xferres )
        break;
      if ( xferres != 274 )
      {
        VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
        VERBOSE_PRINTF("sceUsbdBulkTransfer -> 0x%x", xferres);
        VERBOSE_PRINTF("\n");
      	dropped = 1;
      	break;
      }
      DelayThread(10000);
    }
  }
  if ( dropped )
  {
    VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
    VERBOSE_PRINTF("dropped");
    VERBOSE_PRINTF("\n");
    priv->m_tx_dropped += 1;
    sceInetFreePkt(&priv->m_devops, pkt);
  }
  priv->m_val_for_alarm_cb = 10;
  return xferres;
}
// 403504: using guessed type int g_verbose;

//----- (00400AC4) --------------------------------------------------------
static int inet_81040000_multicast_list_handler(struct an986_priv *priv, u8 *ptr, int len)
{
	int k; // $t0

	bzero(&priv->m_usb_xfer_buf[8], 8);
	if ( len >= 0 )
	{
		if ( len != 6 * (len / 6) )
			return -512;
		if ( ptr )
		{
			for ( k = 0; k < (len / 6); k += 1 )
			{
				if ( !!(*ptr & 1) )
				{
					unsigned int valcr2;
					int i;
					unsigned int xcurval;

					valcr2 = 0xFFFFFFFF;
					for ( i = 0; i < 6; i += 1 )
					{
						int j;

						for ( j = 0; j < 8; j += 1 )
						{
							xcurval = valcr2 >> 1;
							if ( !!(((u8)valcr2 ^ (u8)(*ptr >> j)) & 1) )
								xcurval ^= 0xEDB88320;
							valcr2 = xcurval;
						}
						ptr += 1;
					}
					priv->m_usb_xfer_buf[((u8)(xcurval & 0x3F) >> 3) + 8] |= 1 << (xcurval & 7);
				}
			}
		}
	}
	else
	{
		if ( ptr )
			return -512;
		for ( k = 0; k < 8; k += 1 )
			priv->m_usb_xfer_buf[k + 8] = 0xFF;
	}
	return control_positive_xfer(priv, 8, 8);
}

//----- (00400C28) --------------------------------------------------------
static int an986_inet_control(void *userdata, int code, void *ptr, int len)
{
	int m_nego_status; // $v1
	const int *p_m_err_rx_over; // $s0
	int priority; // [sp+10h] [-8h] BYREF
	struct an986_priv *priv;

	priv = (struct an986_priv *)userdata;
	m_nego_status = -512;
	p_m_err_rx_over = NULL;
	switch ( code )
	{
		case 0x80000000:
			m_nego_status = g_thpri;
			break;
		case 0x80000100:
			m_nego_status = 1;
			break;
		case 0x80010000:
			p_m_err_rx_over = &priv->m_rx_packets;
			break;
		case 0x80010001:
			p_m_err_rx_over = &priv->m_tx_packets;
			break;
		case 0x80010002:
			p_m_err_rx_over = &priv->m_rx_bytes;
			break;
		case 0x80010003:
			p_m_err_rx_over = &priv->m_tx_bytes;
			break;
		case 0x80010004:
			p_m_err_rx_over = &priv->m_rx_errors;
			break;
		case 0x80010005:
			p_m_err_rx_over = &priv->m_tx_errors;
			break;
		case 0x80010006:
			p_m_err_rx_over = &priv->m_rx_dropped;
			break;
		case 0x80010007:
			p_m_err_rx_over = &priv->m_tx_dropped;
			break;
		case 0x80011000:
			p_m_err_rx_over = &priv->m_multicast;
			break;
		case 0x80011001:
			p_m_err_rx_over = &priv->m_collisions;
			break;
		case 0x80011002:
			p_m_err_rx_over = &priv->m_err_rx_length;
			break;
		case 0x80011003:
			p_m_err_rx_over = &priv->m_err_rx_over;
			break;
		case 0x80011004:
			p_m_err_rx_over = &priv->m_err_rx_crc;
			break;
		case 0x80011005:
			p_m_err_rx_over = &priv->m_err_rx_frame;
			break;
		case 0x80011006:
			p_m_err_rx_over = &priv->m_err_rx_fifo;
			break;
		case 0x80011007:
			p_m_err_rx_over = &priv->m_err_rx_missed;
			break;
		case 0x80011008:
			p_m_err_rx_over = &priv->m_err_tx_aborted;
			break;
		case 0x80011009:
			p_m_err_rx_over = &priv->m_err_tx_carrier;
			break;
		case 0x8001100A:
			p_m_err_rx_over = &priv->m_err_tx_fifo;
			break;
		case 0x8001100B:
			p_m_err_rx_over = &priv->m_err_tx_heartbeat;
			break;
		case 0x8001100C:
			p_m_err_rx_over = &priv->m_err_tx_window;
			break;
		case 0x80020001:
			m_nego_status = ( priv->m_link_status > 0 ) ? priv->m_nego_status : 0;
			break;
		case 0x80030000:
			m_nego_status = priv->m_link_status;
			break;
		case 0x81000000:
			if ( !ptr )
				break;
			if ( len != sizeof(priority) )
				break;
			bcopy(ptr, &priority, sizeof(priority));
			m_nego_status = -403;
			if ( (unsigned int)(priority - 9) >= 0x73 )
				break;
			g_thpri = priority;
			m_nego_status = ChangeThreadPriority(priv->m_thid, priority);
			break;
		case 0x81040000:
			m_nego_status = inet_81040000_multicast_list_handler(priv, ptr, len);
			break;
	}
	if ( p_m_err_rx_over && ptr && len == sizeof(*p_m_err_rx_over) )
	{
		bcopy(p_m_err_rx_over, ptr, sizeof(*p_m_err_rx_over));
		m_nego_status = 0;
	}
	return m_nego_status;
}
// 400CFC: conditional instruction was optimized away because $a1.4==80010006
// 400D70: conditional instruction was optimized away because $a1.4==80011005
// 4034F8: using guessed type int g_thpri;

//----- (00400F78) --------------------------------------------------------
static void inet_thread_proc(void *userdata)
{
	int xferret; // $s0
	int regres; // $s0
	int idxcnt; // $s2
	int indindx2; // $s0
	int i; // $s0
	int indindx; // $s0
	u16 outval_1; // [sp+28h] [-10h] BYREF
	u16 outval_2; // [sp+2Ah] [-Eh] BYREF
	u16 outval_3; // [sp+2Ch] [-Ch] BYREF
	int state; // [sp+30h] [-8h] BYREF
	struct an986_priv *priv;

	priv = (struct an986_priv *)userdata;
	if ( ef_wait_wrap(priv, 1u) )
		return;
	xferret = sceUsbdControlTransfer(priv->m_ctrl_pipe, 0, 9, priv->m_subclass, 0, 0, NULL, an986_done, priv);
	if ( xferret )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("sceUsbdSetConfiguration -> 0x%x", xferret);
		VERBOSE_PRINTF("\n");
		return;
	}
	if ( ef_wait_wrap(priv, 4u) )
		return;
	if ( control_negative_xfer(priv, 16, 6) )
		return;
	for ( i = 0; i < 3; i += 1 )
	{
		priv->m_usb_xfer_buf[32] = i;
		priv->m_usb_xfer_buf[33] = 0;
		priv->m_usb_xfer_buf[34] = 0;
		priv->m_usb_xfer_buf[35] = 2;
		if ( control_positive_xfer(priv, 32, 4) )
			return;
		while ( !control_negative_xfer(priv, 35, 1) )
		{
			if ( !!(priv->m_usb_xfer_buf[35] & 4) )
			{
				if ( control_negative_xfer(priv, 33, 3) )
					return;
				priv->m_hwaddr_tmp[(i * 2) + 0] = priv->m_usb_xfer_buf[33];
				priv->m_hwaddr_tmp[(i * 2) + 1] = priv->m_usb_xfer_buf[34];
				break;
			}
			DelayThread(10000);
		}
	}
	bcopy(priv->m_hwaddr_tmp, &priv->m_usb_xfer_buf[16], 6);
	if ( control_positive_xfer(priv, 16, 6) )
		return;
	bcopy(priv->m_hwaddr_tmp, priv->m_devops.hw_addr, 6);
	priv->m_link_status = -1;
	regres = sceInetRegisterNetDevice(&priv->m_devops);
	if ( regres < 0 )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("sceInetRegisterNetDevice -> %d", regres);
		VERBOSE_PRINTF("\n");
		return;
	}
	if ( ef_wait_wrap(priv, 2u) )
		return;
	priv->m_usb_xfer_buf[126] = 36;
	priv->m_usb_xfer_buf[127] = 6;
	if ( control_positive_xfer(priv, 126, 2) )
		return;
	priv->m_usb_xfer_buf[126] = 38;
	priv->m_usb_xfer_buf[127] = 4;
	if ( control_positive_xfer(priv, 126, 2) )
		return;
	if ( priv->m_is_pegasus2 )
	{
		priv->m_usb_xfer_buf[123] = 3;
		if ( control_positive_xfer(priv, 123, 1) )
			return;
		priv->m_usb_xfer_buf[123] = 2;
		if ( control_positive_xfer(priv, 123, 1) )
			return;
	}
	priv->m_usb_xfer_buf[1] = 8;
	if ( control_positive_xfer(priv, 1, 1) )
		return;
	while ( !control_negative_xfer(priv, 1, 1) && !!(priv->m_usb_xfer_buf[1] & 8) )
	{
		DelayThread(10000);
	}
	idxcnt = 0;
	indindx2 = 0;
	outval_1 = 0;
	while ( (outval_1 & 0x24) != 0x24 )
	{
		if ( control_inout_xfer(priv, idxcnt, 1, &outval_1) )
			return;
		if ( outval_1 == 0xFFFF )
		{
			idxcnt += 1;
			if ( idxcnt >= 32 )
			{
				VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
				VERBOSE_PRINTF("Valid PHY chip not found");
				VERBOSE_PRINTF("\n");
				return;
			}
		}
		else
		{
			if ( (outval_1 & 0x24) == 0x24 )
				break;
			DelayThread(100000);
			indindx2 += 1;
			if ( indindx2 >= 30 )
				priv->m_link_status = 0;
		}
	}
	priv->m_link_status = 1;
	printf(
		"%s: Auto-Nego complete and valid link detected (%d,BMSR=%04x)\n",
		priv->m_devops.interface,
		idxcnt,
		outval_1);
	if ( control_inout_xfer(priv, idxcnt, 4, priv->m_usb_ctrl_buf) || control_inout_xfer(priv, idxcnt, 5, &priv->m_usb_ctrl_buf[1]) )
		return;
	priv->m_usb_xfer_buf[1] = 0;
	outval_1 = priv->m_usb_ctrl_buf[0] & priv->m_usb_ctrl_buf[1];
	if ( !!(outval_1 & 0x140) )
		priv->m_usb_xfer_buf[1] |= 0x20u;
	if ( !!(outval_1 & 0x180) )
		priv->m_usb_xfer_buf[1] |= 0x10u;
	if ( control_positive_xfer(priv, 1, 1) )
		return;
	priv->m_nego_status = (( !!(outval_1 & 0x140) ) ? 2 : 1) << (( !!(outval_1 & 0x180) ) ? 2 : 0);
	printf(
		"%s: %s %s Duplex Mode (ANAR=0x%04x ANLPAR=0x%04x)\n",
		priv->m_devops.interface,
		( !!(outval_1 & 0x180) ) ? "100BaseTX" : "10BaseT",
		( !!(outval_1 & 0x140) ) ? "Full" : "Half",
		priv->m_usb_ctrl_buf[0],
		priv->m_usb_ctrl_buf[1]);
	if ( control_inout_xfer(priv, idxcnt, 2, &outval_2) || control_inout_xfer(priv, idxcnt, 3, &outval_3) )
		return;
	printf(
		"%s: PHY OUI=0x%06x MODEL=0x%02x REV=0x%x (0x%04x,0x%04x)\n",
		priv->m_devops.interface,
		(outval_2 << 6) | (outval_3 >> 10),
		(outval_3 >> 4) & 0x1F,
		outval_3 & 0xF,
		outval_2,
		outval_3);
	priv->m_usb_xfer_buf[0] = 0xC9;
	if ( control_positive_xfer(priv, 0, 1) )
		return;
	if ( priv->m_is_pegasus2 )
	{
		priv->m_usb_xfer_buf[124] = 0x34;
		priv->m_usb_xfer_buf[126] = 0x26;
		priv->m_usb_xfer_buf[127] = 0x30;
		if ( control_positive_xfer(priv, 124, 4) )
			return;
	}
	for ( i = 0; i < 8; i += 1 )
		bulk_xfer(priv);
	priv->m_val_for_inet_start = 1;
	if ( !priv->m_start_stop_flag )
		SetEventFlag(priv->m_devops.evfid, 1u);
	priv->m_val_for_alarm_cb = 10;
	USec2SysClock(0xF4240u, &priv->m_sysclk);
	SetAlarm(
		&priv->m_sysclk,
		alarm_cb,
		priv);
	indindx = 0;
	priv->m_timer_active = 1;
	while ( 1 )
	{
		while ( priv->m_val_for_alarm_cb > 0 )
		{
			control_negative_xfer(priv, 43, 5);
			if ( !!(priv->m_usb_xfer_buf[43] & 0x6C) )
			{
				if ( !!(priv->m_usb_xfer_buf[43] & 0x60) )
					priv->m_collisions += 1;
				if ( !!(priv->m_usb_xfer_buf[43] & 0xC) )
					priv->m_err_tx_carrier += 1;
				priv->m_tx_errors += 1;
			}
			if ( !!(priv->m_usb_xfer_buf[45] & 1) )
			{
				priv->m_err_rx_over += 1;
				priv->m_rx_errors += 1;
			}
			priv->m_err_rx_missed += priv->m_usb_xfer_buf[47];
			priv->m_rx_errors += priv->m_usb_xfer_buf[47];
			DelayThread(100000);
			indindx += 1;
			if ( indindx >= 11 )
			{
				indindx = 0;
				if ( priv->m_cnt_for_bulk_xfer > 0 )
				{
					CpuSuspendIntr(&state);
					priv->m_cnt_for_bulk_xfer -= 1;
					CpuResumeIntr(state);
					bulk_xfer(priv);
				}
			}
		}
		if ( control_inout_xfer(priv, idxcnt, 1, &outval_1) )
			return;
		if ( !(outval_1 & 4) )
		{
			priv->m_link_status = 0;
			while ( (outval_1 & 0x24) != 0x24 )
			{
				if ( control_inout_xfer(priv, idxcnt, 1, &outval_1) )
					return;
				if ( (outval_1 & 0x24) == 0x24 )
					break;
				DelayThread(100000);
			}
			priv->m_link_status = 1;
		}
		priv->m_val_for_alarm_cb = 10;
	}
}
// 403504: using guessed type int g_verbose;

//----- (00401760) --------------------------------------------------------
static struct an986_priv *do_allocate_mem_for_inet(const char *vendor_name, const char *device_name, int is_pegasus2)
{
	struct an986_priv *priv; // $s0
	int err; // $s1
	iop_event_t efparam; // [sp+10h] [-28h] BYREF
	iop_thread_t thparam; // [sp+20h] [-18h] BYREF

	err = 0;
	priv = (struct an986_priv *)sceInetAllocMem(NULL, sizeof(struct an986_priv));
	if ( !priv )
	{
		// Unofficial: don't reference null priv->m_devops.interface
		VERBOSE_PRINTF("%s: ", "an986");
		VERBOSE_PRINTF("sceInetAllocMem(%d) -> no space or not ready", (int)sizeof(struct an986_priv));
		VERBOSE_PRINTF("\n");
		return priv;
	}
	bzero(priv, sizeof(struct an986_priv));
	priv->m_is_pegasus2 = is_pegasus2;
	priv->m_magic_cur = g_magic_count;
	sprintf(priv->m_devops.interface, "an986,%d", priv->m_magic_cur);
	g_magic_count += 1;
	priv->m_devops.module_name = "an986";
	priv->m_devops.prot_ver = 2;
	priv->m_devops.flags = 1040;
	priv->m_devops.start = an986_inet_start;
	priv->m_devops.stop = an986_inet_stop;
	priv->m_devops.xmit = an986_inet_xmit;
	priv->m_devops.control = an986_inet_control;
	priv->m_devops.vendor_name = (char *)vendor_name;
	priv->m_devops.device_name = (char *)device_name;
	priv->m_devops.impl_ver = 0;
	priv->m_devops.priv = priv;
	priv->m_devops.mtu = 1500;
	memset(&efparam, 0, sizeof(efparam));
	priv->m_efid = CreateEventFlag(&efparam);
	if ( priv->m_efid <= 0 )
	{
		VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
		VERBOSE_PRINTF("CreateEventFlag -> %d", priv->m_efid);
		VERBOSE_PRINTF("\n");
		err = 1;
	}
	if ( !err )
	{
		thparam.attr = 0x2000000;
		thparam.thread = inet_thread_proc;
		thparam.option = 0;
		thparam.priority = g_thpri;
		thparam.stacksize = g_thstack;
		priv->m_thid = CreateThread(&thparam);
		if ( priv->m_thid <= 0 )
		{
			VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
			VERBOSE_PRINTF("CreateThread -> %d", priv->m_thid);
			VERBOSE_PRINTF("\n");
			err = 1;
		}
	}
	if ( !err )
	{
		err = StartThread(priv->m_thid, priv);
		if ( err )
		{
			VERBOSE_PRINTF("%s: ", priv->m_devops.interface);
			VERBOSE_PRINTF("StartThread -> %d", err);
			VERBOSE_PRINTF("\n");
			err = 1;
		}
	}
	if ( err )
	{
		if ( priv->m_thid > 0 )
			DeleteThread(priv->m_thid);
		if ( priv->m_efid > 0 )
			DeleteEventFlag(priv->m_efid);
		sceInetFreeMem(&priv->m_devops, priv);
		priv = NULL;
	}
	return priv;
}
// 4034F8: using guessed type int g_thpri;
// 4034FC: using guessed type int g_thstack;
// 403500: using guessed type int g_magic_count;
// 403504: using guessed type int g_verbose;

//----- (004019E4) --------------------------------------------------------
static struct an986_devinfo *do_check_static_descriptor(
				int is_probe,
				u16 id_vendor,
				u16 id_product)
{
	unsigned int i; // $s0

	if ( is_probe )
		VERBOSE_PRINTF("an986: idVendor=0x%04x idProduct=0x%04x\n", id_vendor, id_product);
	// Unofficial: avoid out of bounds read when device not found
	for ( i = 0; i < (sizeof(g_an986_devinfo)/sizeof(g_an986_devinfo[0])); i += 1 )
	{
		if ( id_vendor == g_an986_devinfo[i].m_vendor_id && id_product == g_an986_devinfo[i].m_product_id )
		{
			if ( is_probe )
				VERBOSE_PRINTF("an986: %s, %s", g_an986_devinfo[i].m_vendor_name, g_an986_devinfo[i].m_device_name);
			switch ( g_an986_devinfo[i].m_chip )
			{
			case 'p':
				if ( is_probe )
					VERBOSE_PRINTF(" [pegasus] -> supported\n");
				return &g_an986_devinfo[i];
			case 'P':
				if ( is_probe )
					VERBOSE_PRINTF(" [pegasusII] -> supported\n");
				return &g_an986_devinfo[i];
			case 'k':
				if ( is_probe )
					VERBOSE_PRINTF(" [klsi] -> unsupported\n");
				return NULL;
			default:
				break;
			}
		}
	}
	if ( is_probe )
		VERBOSE_PRINTF(" [unknown] -> unsupported\n");
	return NULL;
}
// 403090: using guessed type an986_devinfo g_an986_devinfo[53];
// 403504: using guessed type int g_verbose;

//----- (00401BA0) --------------------------------------------------------
static int an986_ldd_connect(int devId)
{
	UsbDeviceDescriptor *devdesc2; // $s0
	const struct an986_devinfo *cur_devinfo; // $s5
	UsbDeviceDescriptor *devdesc; // $s6
	UsbInterfaceDescriptor *intfdesc; // $a1
	UsbEndpointDescriptor *bulk_in_desc; // $s3
	UsbEndpointDescriptor *bulk_out_desc; // $s1
	UsbEndpointDescriptor *int_in_desc; // $s2
	struct an986_priv *mem_for_inet; // $s0

	VERBOSE_PRINTF("an986_attach,%d: called\n", devId);
	devdesc2 = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(devId, NULL, 1u);
	if ( !devdesc2 )
		return -1;
	cur_devinfo = do_check_static_descriptor(0, devdesc2->idVendor, devdesc2->idProduct);
	if ( !cur_devinfo )
		return -1;
	devdesc = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(devId, devdesc2, 2u);
	if ( !devdesc )
		return -1;
	if ( devdesc->bDeviceClass != 1 )
		return -1;
	intfdesc = (UsbInterfaceDescriptor *)sceUsbdScanStaticDescriptor(devId, devdesc, 4u);
	if ( !intfdesc )
		return -1;
	if ( intfdesc->bNumEndpoints != 3 )
		return -1;
	bulk_in_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, intfdesc, 5u);
	if ( !bulk_in_desc )
		return -1;
	if ( !(bulk_in_desc->bEndpointAddress & 0x80) )
		return -1;
	if ( (bulk_in_desc->bmAttributes & 3) != 2 )
		return -1;
	bulk_out_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, bulk_in_desc, 5u);
	if ( !bulk_out_desc )
		return -1;
	if ( !!(bulk_out_desc->bEndpointAddress & 0x80) )
		return -1;
	if ( (bulk_out_desc->bmAttributes & 3) != 2 )
		return -1;
	int_in_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, bulk_out_desc, 5u);
	if ( !int_in_desc )
		return -1;
	if ( !(int_in_desc->bEndpointAddress & 0x80) )
		return -1;
	if ( (int_in_desc->bmAttributes & 3) != 3 )
		return -1;
	mem_for_inet = do_allocate_mem_for_inet(cur_devinfo->m_vendor_name, cur_devinfo->m_device_name, cur_devinfo->m_chip == 'P');
	if ( !mem_for_inet )
		return -1;
	mem_for_inet->m_ctrl_pipe = sceUsbdOpenPipe(devId, NULL);
	if ( mem_for_inet->m_ctrl_pipe < 0 )
		return -1;
	mem_for_inet->m_bulk_in_pipe = sceUsbdOpenPipe(devId, bulk_in_desc);
	if ( mem_for_inet->m_bulk_in_pipe < 0 )
		return -1;
	mem_for_inet->m_bulk_out_pipe = sceUsbdOpenPipeAligned(devId, bulk_out_desc);
	if ( mem_for_inet->m_bulk_out_pipe < 0 )
		return -1;
	mem_for_inet->m_int_in_pipe = sceUsbdOpenPipe(devId, int_in_desc);
	if ( mem_for_inet->m_int_in_pipe < 0 )
		return -1;
	sceUsbdSetPrivateData(devId, mem_for_inet);
	mem_for_inet->m_devops.bus_type = 1;
	sceUsbdGetDeviceLocation(devId, mem_for_inet->m_devops.bus_loc);
	mem_for_inet->m_subclass = devdesc->bDeviceSubClass;
	ef_set_wrap(mem_for_inet, 0, 1u);
	VERBOSE_PRINTF("an986_attach,%d: -> attached\n", devId);
	return 0;
}
// 403504: using guessed type int g_verbose;

//----- (00401E3C) --------------------------------------------------------
static int an986_ldd_disconnect(int devId)
{
	struct an986_priv *priv; // $v0

	VERBOSE_PRINTF("an986_detach,%d: -> detached\n", devId);
	priv = (struct an986_priv *)sceUsbdGetPrivateData(devId);
	if ( !priv )
		return -1;
	priv->m_val_for_inet_stop = 1;
	SetEventFlag(priv->m_devops.evfid, 2u);
	return 0;
}
// 403504: using guessed type int g_verbose;

//----- (00401EA4) --------------------------------------------------------
static int an986_ldd_probe(int devId)
{
	UsbStringDescriptor *strdesc1; // $s2
	const UsbDeviceDescriptor *devdesc; // $v0

	if ( g_verbose )
	{
		int i;
		char strlocbuf[16];

		printf("an986_probe,%d: called", devId);
		if ( sceUsbdGetDeviceLocation(devId, (u8 *)strlocbuf) )
		{
			printf(" dev_id=%d\n", devId);
		}
		else
		{
			
			printf(" Loc:USB-");
			for ( i = 0; i < 7 && strlocbuf[i]; i += 1 )
			{
				printf("%s%d", i ? "," : "", strlocbuf[i]);
			}
		}
		strdesc1 = NULL;
		while ( 1 )
		{
			printf("\n");
			strdesc1 = (UsbStringDescriptor *)sceUsbdScanStaticDescriptor(devId, strdesc1, 0);
			if ( !strdesc1 )
				break;
			for ( i = 0; i < strdesc1->bLength; i += 1 )
			{
				printf(" %02x", ((u8 *)strdesc1)[i]);
			}
		}
	}
	devdesc = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(devId, NULL, 1u);
	if ( !devdesc )
		return 0;
	if ( !do_check_static_descriptor(1, devdesc->idVendor, devdesc->idProduct) )
		return 0;
	g_resident_flag = 1;
	if ( g_load_mode == 't' )
		return 0;
	VERBOSE_PRINTF("an986_probe,%d: -> accepted\n", devId);
	return 1;
}
// 403504: using guessed type int g_verbose;
// 403700: using guessed type int g_resident_flag;
// 403704: using guessed type int g_load_mode;
// 401EA4: using guessed type u8 strlocbuf[16];

//----- (00402050) --------------------------------------------------------
static int do_print_version(void)
{
	printf("AN986 (%s)\n", version_ptr);
	return 1;
}
// 4036F0: using guessed type char *version_ptr;

//----- (0040207C) --------------------------------------------------------
static int do_print_help(void)
{
	do_print_version();
	printf("Usage: an986 [-verbose] [-list] [thpri=<prio>] [thstack=<stack>] [-p <id>] [-P <id>]\n");
	return 2;
}

//----- (004020A8) --------------------------------------------------------
static int scan_number(const char *e_arg, unsigned int *n_result)
{
	const char *e_arg_1;
	unsigned int curbasex;
	unsigned int curnum;

	e_arg_1 = e_arg;
	curbasex = 10;
	if ( *e_arg == '0' && e_arg[1] )
	{
		e_arg_1 = e_arg + 1;
		curbasex = 8;
		if ( e_arg[1] == 'x' )
		{
			e_arg_1 = e_arg + 2;
			curbasex = 16;
		}
	}
	curnum = 0;
	if ( *e_arg_1 )
	{
		while ( 1 )
		{
			u32 e_arg_1_num;

			e_arg_1_num = (((u8)*e_arg_1)) - '0';
			if ( ((u8)*e_arg_1) - (unsigned int)'0' >= 0xA )
			{
				e_arg_1_num = (((u8)*e_arg_1)) - 'W';
				if ( ((u8)*e_arg_1) - (unsigned int)'a' >= 6 )
					break;
			}
			if ( e_arg_1_num >= curbasex )
				break;
			e_arg_1 += 1;
			curnum = curnum * curbasex + e_arg_1_num;
			if ( !*e_arg_1 )
			{
				*n_result = curnum;
				return 0;
			}
		}
	}
	printf("%s: %s - invalid digit\n", "scan_number", e_arg);
	return -1;
}

//----- (00402188) --------------------------------------------------------
static int do_print_list(void)
{
	unsigned int i; // $s2

	do_print_version();
	printf("  VID   PID   Vendor          Device          Chip\n");
	printf("------------------------------------------------------\n");
	for ( i = 0; i < (sizeof(g_an986_devinfo)/sizeof(g_an986_devinfo[0])); i += 1 )
	{
		printf("  %04x", g_an986_devinfo[i].m_vendor_id);
		printf("  %04x", g_an986_devinfo[i].m_product_id);
		printf("  %-14s", g_an986_devinfo[i].m_vendor_name);
		printf("  %-14s", g_an986_devinfo[i].m_device_name);
		switch ( g_an986_devinfo[i].m_chip )
		{
		case 'p':
			printf("  Pegasus");
			break;
		case 'P':
			printf("  PegasusII");
			break;
		case 'k':
			printf("  KLSI");
			break;
		default:
			printf("  Unknown");
			break;
		}
		printf("\n");
	}
	return 3;
}
// 403090: using guessed type an986_devinfo g_an986_devinfo[53];

//----- (004022CC) --------------------------------------------------------
static int an986_init(int ac, char **av)
{
	int i; // $s2
	char *thpricurx; // $s0
	unsigned int vidtmp; // [sp+10h] [-8h] BYREF

	g_load_mode = 'n';
	g_resident_flag = 1;
	for ( i = 1; i < ac; i += 1 )
	{
		if ( !strcmp("-help", av[i]) )
			return do_print_help();
		else if ( !strcmp("-version", av[i]) )
			return do_print_version();
		else if ( !strcmp("-verbose", av[i]) )
		{
			g_verbose = 1;
		}
		else if ( !strcmp("-list", av[i]) )
			return do_print_list();
		else if ( !strcmp("-p", av[i]) || !strcmp("-P", av[i]) )
		{
			g_an986_devinfo[0].m_chip = av[i][1];
			i += 1;
			if ( i >= ac || scan_number((char *)av[i], &vidtmp) )
				return do_print_help();
			g_an986_devinfo[0].m_vendor_id = (vidtmp >> 16) & 0xFFFF;
			g_an986_devinfo[0].m_product_id = vidtmp & 0xFFFF;
		}
		else if ( !strncmp("thpri=", av[i], 6) )
		{
			thpricurx = &av[i][6];
			if ( !(look_ctype_table(*thpricurx) & 4) )
				return do_print_help();
			g_thpri = strtol(thpricurx, NULL, 10);
			if ( (unsigned int)(g_thpri - 9) >= 0x73 )
				return do_print_help();
			while ( *thpricurx && !!(look_ctype_table(*thpricurx) & 4) )
			{
				thpricurx += 1;
			}
			if ( *thpricurx )
				return do_print_help();
		}
		else if ( !strncmp("thstack=", av[i], 8) )
		{
			thpricurx = &av[i][8];
			if ( !(look_ctype_table(*thpricurx) & 4) )
				return do_print_help();
			g_thstack = strtol(thpricurx, NULL, 10);
			while ( *thpricurx && !!(look_ctype_table(*thpricurx) & 4) )
			{
				thpricurx += 1;
			}
			if ( !strcmp(thpricurx, "KB") )
			{
				g_thstack <<= 10;
				thpricurx += 2;
			}
			if ( *thpricurx )
				return do_print_help();
		}
		else if ( !strcmp("AUTOLOAD", av[i]) || !strcmp("lmode=AUTOLOAD", av[i]) )
			g_load_mode = 'a';
		else if ( !strcmp("TESTLOAD", av[i]) || !strcmp("lmode=TESTLOAD", av[i]) )
			g_load_mode = 't';
		else
			return do_print_help();
	}
	if ( g_load_mode != 'n' )
		g_resident_flag = 0;
	if ( sceUsbdRegisterLdd(&g_an986_ldd) )
	{
		return 4;
	}
	VERBOSE_PRINTF("an986_start: load_mode='%c' resident_flag=%d\n", g_load_mode, g_resident_flag);
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
	sceUsbdUnregisterLdd(&g_an986_ldd);
	return 6;
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
	int initval; // $v0

	if ( RegisterLibraryEntries(&_exp_an986) )
	{
		printf("an986: module already loaded\n");
		return 1;
	}
	initval = an986_init(ac, av);
	VERBOSE_PRINTF("an986: an986_init() -> 0x%x\n", initval);
	if ( initval )
	{
		ReleaseLibraryEntries(&_exp_an986);
		return (initval << 4) | (g_resident_flag ? 4 : 0) | 1;
	}
	return 0;
}
// 402750: using guessed type int exports[2];
// 403504: using guessed type int g_verbose;
// 403700: using guessed type int g_resident_flag;
