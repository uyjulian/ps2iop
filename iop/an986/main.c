
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

//-------------------------------------------------------------------------
// Function declarations

int ef_wait_wrap(struct an986_priv *priv, u32 efbits);
void ef_set_wrap(struct an986_priv *priv, int wait_retval, u32 efbits);
void an986_done(int efbits, int doneval, void *userdata);
int control_negative_xfer(struct an986_priv *priv, int xferoffs, int xferlen);
int control_positive_xfer(struct an986_priv *priv, int xferoffs, int xferlen);
int control_inout_xfer(struct an986_priv *priv, char linkval, char xval, u16 *outptr);
void an986_rx_done(int aresult, int acount, void *userdata);
void bulk_xfer(struct an986_priv *priv);
void an986_tx_done(int aresult, int acount, void *userdata);
unsigned int alarm_cb(void *userdata);
int an986_inet_start(void *userdata, int unused);
int an986_inet_stop(void *userdata, int unused);
int an986_inet_xmit(void *userdata, int unused);
int inet_81040000_multicast_list_handler(struct an986_priv *priv, u8 *ptr, int len);
int an986_inet_control(void *userdata, int code, void *ptr, int len);
void inet_thread_proc(void *userdata);
struct an986_priv *do_allocate_mem_for_inet(char *vendor_name, char *device_name, int is_pegasus2);
struct an986_devinfo *do_check_static_descriptor(int is_probe, u16 id_vendor, u16 id_product);
int an986_ldd_connect(int devId);
int an986_ldd_disconnect(int devId);
int an986_ldd_probe(int devId);
int do_print_version();
int do_print_help();
int scan_number(char *inchr, int *outptr);
int do_print_list();
int an986_init(int ac, char **av);

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
char *version_ptr = "Version 1.75.0"; // weak
int g_resident_flag; // weak
int g_load_mode; // weak


//----- (00400000) --------------------------------------------------------
int ef_wait_wrap(struct an986_priv *priv, u32 efbits)
{
	int efret; // $s1
	u32 efres[2]; // [sp+10h] [-8h] BYREF

	efret = WaitEventFlag(priv->m_efid, efbits, 17, efres);
	if ( !efret )
		return priv->m_ef_wait_retval;
	if ( g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("WaitEventFlag (%d)", efret);
		printf("\n");
	}
	return -1;
}
// 403504: using guessed type int g_verbose;

//----- (00400088) --------------------------------------------------------
void ef_set_wrap(struct an986_priv *priv, int wait_retval, u32 efbits)
{
	int efret; // $s1

	priv->m_ef_wait_retval = wait_retval;
	efret = SetEventFlag(priv->m_efid, efbits);
	if ( efret )
	{
		if ( g_verbose )
		{
			printf("%s: ", priv->m_devops.interface);
			printf("SetEventFlag (%d)", efret);
			printf("\n");
		}
	}
}
// 403504: using guessed type int g_verbose;

//----- (00400104) --------------------------------------------------------
void an986_done(int efbits, int doneval, void *userdata)
{
	struct an986_priv *priv_tmp; // $a0

	priv_tmp = (struct an986_priv *)userdata;
	if ( efbits )
	{
		if ( g_verbose )
		{
			printf("%s: ", priv_tmp->m_devops.interface);
			printf("%s: -> 0x%x\n", "an986_done", efbits);
			printf("\n");
		}
	}
	priv_tmp->m_done_related = doneval;
	ef_set_wrap(priv_tmp, efbits, 4u);
}
// 403504: using guessed type int g_verbose;

//----- (00400194) --------------------------------------------------------
int control_negative_xfer(struct an986_priv *priv, int xferoffs, int xferlen)
{
	int xferret; // $s0
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
							(u16)xferlen,
							&devreq,
							an986_done,
							priv);
	if ( !xferret )
		return ef_wait_wrap(priv, 4u);
	if ( g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("sceUsbdControlTransfer -> 0x%x", xferret);
		printf("\n");
	}
	return -1;
}
// 403504: using guessed type int g_verbose;

//----- (00400264) --------------------------------------------------------
int control_positive_xfer(struct an986_priv *priv, int xferoffs, int xferlen)
{
	int xferret; // $s0
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
							(u16)xferlen,
							&devreq,
							an986_done,
							priv);
	if ( !xferret )
		return ef_wait_wrap(priv, 4u);
	if ( g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("sceUsbdControlTransfer -> 0x%x", xferret);
		printf("\n");
	}
	return -1;
}
// 403504: using guessed type int g_verbose;

//----- (00400334) --------------------------------------------------------
int control_inout_xfer(struct an986_priv *priv, char linkval, char xval, u16 *outptr)
{
	int result; // $v0

	priv->m_usb_xfer_buf[37] = linkval & 0x1F;
	priv->m_usb_xfer_buf[38] = 0;
	priv->m_usb_xfer_buf[39] = 0;
	priv->m_usb_xfer_buf[40] = (xval & 0x1F) | 0x40;
	result = control_positive_xfer(priv, 37, 4);
	if ( result )
	{
		return result;
	}
	while ( 1 )
	{
		result = control_negative_xfer(priv, 40, 1);
		if ( result )
			return result;
		if ( (priv->m_usb_xfer_buf[40] & 0x80) != 0 )
		{
			result = control_negative_xfer(priv, 37, 4);
			if ( result )
			{
				return result;
			}
			*outptr = priv->m_usb_xfer_buf[38] | (priv->m_usb_xfer_buf[39] << 8);
			return 0;
		}
		DelayThread(10000);
	}
}

//----- (004003F4) --------------------------------------------------------
void an986_rx_done(int aresult, int acount, void *userdata)
{
	struct an986_priv *priv; // $s0
	sceInetPkt_t *pkt;

	pkt = (sceInetPkt_t *)userdata;
	priv = (struct an986_priv *)pkt->m_reserved1;
	if ( aresult && g_verbose )
	{
		printf("%s: ", priv->m_devops.interface);
		printf("%s: -> 0x%x\n", "an986_rx_done", aresult);
		printf("\n");
	}
	++priv->m_rx_packets;
	pkt->m_reserved1 = 0;
	if ( priv->m_start_stop_flag || priv->m_val_for_inet_stop )
	{
		sceInetFreePkt(&priv->m_devops, pkt);
	}
	else if ( acount < 68 )
	{
		++priv->m_rx_errors;
		sceInetFreePkt(&priv->m_devops, pkt);
	}
	else
	{
		if ( (pkt->rp[acount - 2] & 1) != 0 )
		{
			++priv->m_multicast;
		}
		if ( (pkt->rp[acount - 2] & 2) != 0 )
		{
			++priv->m_err_rx_length;
		}
		if ( (pkt->rp[acount - 2] & 4) != 0 )
		{
			++priv->m_err_rx_length;
		}
		if ( (pkt->rp[acount - 2] & 8) != 0 )
		{
			++priv->m_err_rx_crc;
		}
		if ( (pkt->rp[acount - 2] & 0x10) != 0 )
		{
			++priv->m_err_rx_frame;
		}
		if ( (pkt->rp[acount - 2] & 0x1E) )
		{
			++priv->m_rx_errors;
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
void bulk_xfer(struct an986_priv *priv)
{
	sceInetPkt_t *pkt; // $v0
	int xferret; // $s1
	int state; // [sp+18h] [-8h] BYREF

	pkt = sceInetAllocPkt(&priv->m_devops, 1524);
	if ( pkt )
	{
		pkt->m_reserved1 = (void *)priv;
		pkt->rp += 2;
		pkt->wp += 2;
		xferret = sceUsbdTransferPipe(priv->m_bulk_in_pipe, pkt->wp, 0x5F2u, 0, an986_rx_done, pkt);
		if ( xferret )
		{
			if ( g_verbose )
			{
				printf("%s: ", priv->m_devops.interface);
				printf("sceUsbdBulkTransfer -> 0x%x\n", xferret);
				printf("\n");
			}
			sceInetFreePkt(&priv->m_devops, pkt);
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
		++priv->m_cnt_for_bulk_xfer;
		CpuResumeIntr(state);
	}
}
// 403504: using guessed type int g_verbose;

//----- (0040071C) --------------------------------------------------------
void an986_tx_done(int aresult, int acount, void *userdata)
{
	struct an986_priv *priv; // $s1
	sceInetPkt_t *pkt;

	(void)acount;
	pkt = (sceInetPkt_t *)userdata;
	priv = (struct an986_priv *)pkt->m_reserved1;
	if ( aresult )
	{
		if ( g_verbose )
		{
			printf("%s: ", priv->m_devops.interface);
			printf("%s: -> 0x%x\n", "an986_tx_done", aresult);
			printf("\n");
		}
	}
	pkt->m_reserved1 = 0;
	sceInetFreePkt(&priv->m_devops, pkt);
}
// 403504: using guessed type int g_verbose;

//----- (004007AC) --------------------------------------------------------
unsigned int alarm_cb(void *userdata)
{
	struct an986_priv *priv;

	priv = (struct an986_priv *)userdata;
	if ( (int)(priv->m_val_for_alarm_cb) > 0 )
		priv->m_val_for_alarm_cb -= 1;
	return priv->m_sysclk.lo;
}

//----- (004007DC) --------------------------------------------------------
int an986_inet_start(void *userdata, int unused)
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
int an986_inet_stop(void *userdata, int unused)
{
	struct an986_priv *priv;

	(void)unused;
	priv = (struct an986_priv *)userdata;
	priv->m_start_stop_flag = 1;
	if ( priv->m_val_for_inet_stop )
	{
		TerminateThread(priv->m_thid);
		DeleteThread(priv->m_thid);
		DeleteEventFlag(priv->m_efid);
		if ( priv->m_timer_active )
			CancelAlarm(alarm_cb, priv);
		sceInetUnregisterNetDevice(&priv->m_devops);
		sceInetFreeMem(&priv->m_devops, priv);
	}
	return 0;
}

//----- (004008F4) --------------------------------------------------------
int an986_inet_xmit(void *userdata, int unused)
{
  int xferres; // $s3
  sceInetPkt_t *pkt; // $s2
  u8 *rp; // $v1
  u32 xrp2; // $s1
  struct an986_priv *priv;
  int dropped;

	(void)unused;
	priv = (struct an986_priv *)userdata;
	dropped = 0;
  xferres = -1;
  pkt = sceInetPktDeQ(&priv->m_devops.sndq);
  if ( pkt )
  {
    if ( priv->m_start_stop_flag
      || priv->m_val_for_inet_stop
      || !priv->m_link_status
      || (rp = pkt->rp, xrp2 = pkt->wp - rp, xrp2 - 60 >= 0x5AF)
      || (pkt->rp = rp - 2, ((uiptr)(pkt->rp) & 3) != 0) )
    {
			dropped = 1;
    }
    else
    {
      *((u16 *)rp - 1) = xrp2;
      ++priv->m_tx_packets;
      priv->m_tx_bytes += xrp2;
      if ( (((u8)xrp2 + 2) & 0x3F) == 0 )
        ++xrp2;
      pkt->m_reserved1 = (void *)priv;
      while ( 1 )
      {
        xferres = sceUsbdTransferPipe(
                    priv->m_bulk_out_pipe,
                    pkt->rp,
                    xrp2 + 2,
                    0,
                    an986_tx_done,
                    pkt);
        if ( !xferres )
          break;
        if ( xferres != 274 )
        {
          if ( g_verbose )
          {
	          printf("%s: ", priv->m_devops.interface);
	          printf("sceUsbdBulkTransfer -> 0x%x", xferres);
	          printf("\n");
          }
        	dropped = 1;
        	break;
        }
        DelayThread(10000);
      }
    }
  }
  if ( dropped )
  {
    if ( g_verbose )
    {
      printf("%s: ", priv->m_devops.interface);
      printf("dropped");
      printf("\n");
    }
    ++priv->m_tx_dropped;
    sceInetFreePkt(&priv->m_devops, pkt);
  }
  priv->m_val_for_alarm_cb = 10;
  return xferres;
}
// 403504: using guessed type int g_verbose;

//----- (00400AC4) --------------------------------------------------------
int inet_81040000_multicast_list_handler(struct an986_priv *priv, u8 *ptr, int len)
{
	int lendiv; // $v1
	int k; // $t0
	unsigned int valcr2; // $v1
	int i; // $a3
	u8 rshavle; // $v0
	int j; // $a2
	unsigned int xcurval; // $a0

	bzero(&priv->m_usb_xfer_buf[8], 8);
	if ( len >= 0 )
	{
		lendiv = len / 6;
		if ( len != 6 * (len / 6) )
			return -512;
		if ( ptr )
		{
			for ( k = lendiv - 1; lendiv > 0; k -= 1 )
			{
				if ( (*ptr & 1) != 0 )
				{
					valcr2 = -1;
					for ( i = 5; i >= 0; --i )
					{
						rshavle = *ptr++;
						for ( j = 7; j >= 0; --j )
						{
							xcurval = valcr2 >> 1;
							if ( (((u8)valcr2 ^ rshavle) & 1) != 0 )
								xcurval ^= 0xEDB88320;
							valcr2 = xcurval;
							rshavle >>= 1;
						}
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
		{
			priv->m_usb_xfer_buf[8 + k] = -1;
		}
	}
	return control_positive_xfer(priv, 8, 8);
}

//----- (00400C28) --------------------------------------------------------
int an986_inet_control(void *userdata, int code, void *ptr, int len)
{
	int m_nego_status; // $v1
	int *p_m_err_rx_over; // $s0
	int priority; // [sp+10h] [-8h] BYREF
	struct an986_priv *priv;

	priv = (struct an986_priv *)userdata;
	m_nego_status = -512;
	p_m_err_rx_over = 0;
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
			if ( ptr )
			{
				if ( len == 4 )
				{
					bcopy(ptr, &priority, 4);
					m_nego_status = -403;
					if ( (unsigned int)(priority - 9) < 0x73 )
					{
						g_thpri = priority;
						m_nego_status = ChangeThreadPriority(priv->m_thid, priority);
					}
				}
			}
			break;
		case 0x81040000:
			m_nego_status = inet_81040000_multicast_list_handler(priv, ptr, len);
			break;
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
void inet_thread_proc(void *userdata)
{
	int result; // $v0
	int xferret; // $s0
	int xidx_1; // $s0
	int regres; // $s0
	int idxcnt; // $s2
	int indindx2; // $s0
	int i; // $s0
	int indindx; // $s0
	UsbDeviceRequest devreq; // [sp+20h] [-18h] BYREF
	u16 outval_1; // [sp+28h] [-10h] BYREF
	u16 outval_2; // [sp+2Ah] [-Eh] BYREF
	u16 outval_3; // [sp+2Ch] [-Ch] BYREF
	int state; // [sp+30h] [-8h] BYREF
	struct an986_priv *priv;

	priv = (struct an986_priv *)userdata;
	result = ef_wait_wrap(priv, 1u);
	if ( !result )
	{
		devreq.requesttype = 0;
		devreq.request = 9;
		devreq.index = 0;
		devreq.length = 0;
		devreq.value = priv->m_subclass;
		xferret = sceUsbdTransferPipe(priv->m_ctrl_pipe, 0, 0, &devreq, an986_done, priv);
		if ( xferret )
		{
			result = g_verbose;
			if ( g_verbose )
			{
				printf("%s: ", priv->m_devops.interface);
				printf("sceUsbdSetConfiguration -> 0x%x", xferret);
				printf("\n");
				return;
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
LABEL_8:
					priv->m_usb_xfer_buf[32] = xidx_1;
					priv->m_usb_xfer_buf[33] = 0;
					priv->m_usb_xfer_buf[34] = 0;
					priv->m_usb_xfer_buf[35] = 2;
					result = control_positive_xfer(priv, 32, 4);
					if ( !result )
					{
						while ( 1 )
						{
							result = control_negative_xfer(priv, 35, 1);
							if ( result )
								break;
							if ( (priv->m_usb_xfer_buf[35] & 4) != 0 )
							{
								result = control_negative_xfer(priv, 33, 3);
								++xidx_1;
								if ( result )
									return;
								priv->m_hwaddr_tmp[(xidx_1 * 2) + 0] = priv->m_usb_xfer_buf[33];
								priv->m_hwaddr_tmp[(xidx_1 * 2) + 1] = priv->m_usb_xfer_buf[34];
								if ( xidx_1 < 3 )
									goto LABEL_8;
								bcopy(priv->m_hwaddr_tmp, &priv->m_usb_xfer_buf[16], 6);
								result = control_positive_xfer(priv, 16, 6);
								if ( result )
									return;
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
													|| ((priv->m_usb_xfer_buf[123] = 3,
															result = 2,
															control_positive_xfer(priv, 123, 1) == 0)
													&& (priv->m_usb_xfer_buf[123] = 2, (result = control_positive_xfer(priv, 123, 1)) == 0)) )
												{
													priv->m_usb_xfer_buf[1] = 8;
													result = control_positive_xfer(priv, 1, 1);
													if ( !result )
													{
														while ( 1 )
														{
															result = control_negative_xfer(priv, 1, 1);
															if ( result )
																break;
															idxcnt = 0;
															if ( (priv->m_usb_xfer_buf[1] & 8) == 0 )
															{
																indindx2 = 0;
																while ( 1 )
																{
																	result = control_inout_xfer(priv, idxcnt, 1, &outval_1);
																	if ( result )
																		return;
																	if ( outval_1 == 0xFFFF )
																	{
																		++idxcnt;
																		if ( idxcnt >= 32 )
																		{
																			result = g_verbose;
																			if ( !g_verbose )
																				return;
																			printf("%s: ", priv->m_devops.interface);
																			printf("Valid PHY chip not found");
																			printf("\n");
																			return;
																		}
																	}
																	else
																	{
																		if ( (outval_1 & 0x24) == 36 )
																		{
																			priv->m_link_status = 1;
																			printf(
																				"%s: Auto-Nego complete and valid link detected (%d,BMSR=%04x)\n",
																				priv->m_devops.interface,
																				idxcnt,
																				outval_1);
																			result = control_inout_xfer(priv, idxcnt, 4, priv->m_usb_ctrl_buf);
																			if ( !result )
																			{
																				result = control_inout_xfer(priv, idxcnt, 5, &priv->m_usb_ctrl_buf[1]);
																				if ( !result )
																				{
																					outval_1 = priv->m_usb_ctrl_buf[0] & priv->m_usb_ctrl_buf[1];
																					priv->m_usb_xfer_buf[1] = 0;
																					if ( (outval_1 & 0x140) != 0 )
																						priv->m_usb_xfer_buf[1] |= 0x20u;
																					if ( (outval_1 & 0x180) != 0 )
																						priv->m_usb_xfer_buf[1] |= 0x10u;
																					result = control_positive_xfer(priv, 1, 1);
																					if ( !result )
																					{
																						priv->m_nego_status = ( (outval_1 & 0x180) != 0 ) ? (( (outval_1 & 0x140) != 0 ) ? 8 : 4) : (( (outval_1 & 0x140) != 0 ) ? 2 : 1);
																						printf(
																							"%s: %s %s Duplex Mode (ANAR=0x%04x ANLPAR=0x%04x)\n",
																							priv->m_devops.interface,
																							( (outval_1 & 0x180) != 0 ) ? "100BaseTX" : "10BaseT",
																							( (outval_1 & 0x140) != 0 ) ? "Full" : "Half",
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
																											do
																											{
																												control_negative_xfer(priv, 43, 5);
																												if ( (priv->m_usb_xfer_buf[43] & 0x6C) != 0 )
																												{
																													if ( (priv->m_usb_xfer_buf[43] & 0x60) != 0 )
																													{
																														++priv->m_collisions;
																													}
																													if ( (priv->m_usb_xfer_buf[43] & 0xC) != 0 )
																														++priv->m_err_tx_carrier;
																													++priv->m_tx_errors;
																												}
																												if ( (priv->m_usb_xfer_buf[45] & 1) != 0 )
																												{
																													++priv->m_err_rx_over;
																													priv->m_rx_errors += 1;
																												}
																												if ( priv->m_usb_xfer_buf[47] )
																												{
																													priv->m_err_rx_missed += priv->m_usb_xfer_buf[47];
																													priv->m_rx_errors += priv->m_usb_xfer_buf[47];
																												}
																												DelayThread(100000);
																												if ( ++indindx >= 11 )
																												{
																													indindx = 0;
																													if ( priv->m_cnt_for_bulk_xfer > 0 )
																													{
																														CpuSuspendIntr(&state);
																														--priv->m_cnt_for_bulk_xfer;
																														CpuResumeIntr(state);
																														bulk_xfer(priv);
																													}
																												}
																											}
																											while ( priv->m_val_for_alarm_cb > 0 );
																											result = control_inout_xfer(priv, idxcnt, 1, &outval_1);
																											if ( result )
																												break;
																											if ( (outval_1 & 4) == 0 )
																											{
																												priv->m_link_status = 0;
																												while ( 1 )
																												{
																													result = control_inout_xfer(priv, idxcnt, 1, &outval_1);
																													if ( result )
																														break;
																													if ( (outval_1 & 0x24) == 36 )
																													{
																														priv->m_link_status = 1;
																														priv->m_val_for_alarm_cb = 10;
																														break;
																													}
																													DelayThread(100000);
																												}
																												return;
																											}
																											priv->m_val_for_alarm_cb = 10;
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																			return;
																		}
																		DelayThread(100000);
																		++indindx2;
																		if ( indindx2 >= 30 )
																			priv->m_link_status = 0;
																	}
																}
															}
															DelayThread(10000);
														}
													}
												}
											}
										}
									}
									return;
								}
								result = g_verbose;
								if ( !g_verbose )
									return;
								printf("%s: ", priv->m_devops.interface);
								printf("sceInetRegisterNetDevice -> %d", regres);
								printf("\n");
								return;
							}
							DelayThread(10000);
						}
					}
				}
			}
		}
	}
}
// 403504: using guessed type int g_verbose;

//----- (00401760) --------------------------------------------------------
struct an986_priv *do_allocate_mem_for_inet(char *vendor_name, char *device_name, int is_pegasus2)
{
	struct an986_priv *priv; // $s0
	int started; // $s1
	iop_event_t efparam; // [sp+10h] [-28h] BYREF
	iop_thread_t thparam; // [sp+20h] [-18h] BYREF

	priv = (struct an986_priv *)sceInetAllocMem(0, 888);
	if ( priv )
	{
		bzero(priv, 888);
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
		priv->m_devops.vendor_name = vendor_name;
		priv->m_devops.device_name = device_name;
		priv->m_devops.impl_ver = 0;
		priv->m_devops.priv = priv;
		priv->m_devops.mtu = 1500;
		memset(&efparam, 0, sizeof(efparam));
		priv->m_efid = CreateEventFlag(&efparam);
		if ( priv->m_efid > 0 )
		{
			thparam.attr = 0x2000000;
			thparam.thread = inet_thread_proc;
			thparam.option = 0;
			thparam.priority = g_thpri;
			thparam.stacksize = g_thstack;
			priv->m_thid = CreateThread(&thparam);
			if ( priv->m_thid > 0 )
			{
				started = StartThread(priv->m_thid, priv);
				if ( !started )
					return priv;
				if ( g_verbose )
				{
					printf("%s: ", priv->m_devops.interface);
					printf("StartThread -> %d", started);
					printf("\n");
				}
				DeleteThread(priv->m_thid);
			}
			else if ( g_verbose )
			{
				printf("%s: ", priv->m_devops.interface);
				printf("CreateThread -> %d", priv->m_thid);
				printf("\n");
			}
			DeleteEventFlag(priv->m_efid);
		}
		else
		{
			if ( g_verbose )
			{
				printf("%s: ", priv->m_devops.interface);
				printf("CreateEventFlag -> %d", priv->m_efid);
				printf("\n");
			}
		}
		sceInetFreeMem(&priv->m_devops, priv);
		return 0;
	}
	else
	{
		priv = 0;
		if ( g_verbose )
		{
			printf("%s: ", (const char *)320);
			printf("sceInetAllocMem(%d) -> no space or not ready", 888);
			printf("\n");
		}
	}
	return priv;
}
// 4034F8: using guessed type int g_thpri;
// 4034FC: using guessed type int g_thstack;
// 403500: using guessed type int g_magic_count;
// 403504: using guessed type int g_verbose;

//----- (004019E4) --------------------------------------------------------
struct an986_devinfo *do_check_static_descriptor(
				int is_probe,
				u16 id_vendor,
				u16 id_product)
{
	unsigned int i; // $s0

	if ( is_probe && g_verbose )
		printf("an986: idVendor=0x%04x idProduct=0x%04x\n", id_vendor, id_product);
	// Unofficial: avoid out of bounds read when device not found
	for ( i = 0; i < (sizeof(g_an986_devinfo)/sizeof(g_an986_devinfo[0])); i += 1 )
	{
		if ( id_vendor == g_an986_devinfo[i].m_vendor_id && id_product == g_an986_devinfo[i].m_product_id )
		{
			if ( is_probe && g_verbose )
				printf("an986: %s, %s", g_an986_devinfo[i].m_vendor_name, g_an986_devinfo[i].m_device_name);
			switch ( g_an986_devinfo[i].m_chip )
			{
			case 'p':
				if ( is_probe )
				{
					if ( g_verbose )
					{
						printf(" [pegasus] -> supported\n");
					}
				}
				return &g_an986_devinfo[i];
			case 'P':
				if ( is_probe )
				{
					if ( g_verbose )
					{
						printf(" [pegasusII] -> supported\n");
					}
				}
				return &g_an986_devinfo[i];
			case 'k':
				if ( is_probe )
				{
					if ( g_verbose )
					{
						printf(" [klsi] -> unsupported\n");
					}
				}
				return NULL;
			default:
				break;
			}
		}
	}
	if ( is_probe )
	{
		if ( g_verbose )
		{
			printf(" [unknown] -> unsupported\n");
		}
	}
	return NULL;
}
// 403090: using guessed type an986_devinfo g_an986_devinfo[53];
// 403504: using guessed type int g_verbose;

//----- (00401BA0) --------------------------------------------------------
int an986_ldd_connect(int devId)
{
	UsbDeviceDescriptor *devdesc2; // $s0
	struct an986_devinfo *cur_devinfo; // $s5
	UsbDeviceDescriptor *devdesc; // $s6
	UsbInterfaceDescriptor *intfdesc; // $a1
	UsbEndpointDescriptor *bulk_in_desc; // $s3
	UsbEndpointDescriptor *bulk_out_desc; // $s1
	UsbEndpointDescriptor *int_in_desc; // $s2
	struct an986_priv *mem_for_inet; // $s0

	if ( g_verbose )
		printf("an986_attach,%d: called\n", devId);
	devdesc2 = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(devId, 0, 1u);
	if ( devdesc2 )
	{
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
		if ( intfdesc->bNumEndpoints == 3 )
		{
			bulk_in_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, intfdesc, 5u);
			if ( bulk_in_desc )
			{
				if ( (bulk_in_desc->bEndpointAddress & 0x80) != 0 )
				{
					if ( (bulk_in_desc->bmAttributes & 3) == 2 )
					{
						bulk_out_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, bulk_in_desc, 5u);
						if ( bulk_out_desc )
						{
							if ( (bulk_out_desc->bEndpointAddress & 0x80) == 0 )
							{
								if ( (bulk_out_desc->bmAttributes & 3) == 2 )
								{
									int_in_desc = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(devId, bulk_out_desc, 5u);
									if ( int_in_desc )
									{
										if ( (int_in_desc->bEndpointAddress & 0x80) != 0 )
										{
											if ( (int_in_desc->bmAttributes & 3) == 3 )
											{
												mem_for_inet = do_allocate_mem_for_inet(
																				 (char *)cur_devinfo->m_vendor_name,
																				 (char *)cur_devinfo->m_device_name,
																				 cur_devinfo->m_chip == 'P');
												if ( !mem_for_inet )
													return -1;
												mem_for_inet->m_ctrl_pipe = sceUsbdOpenPipe(devId, 0);
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
												if ( g_verbose )
												{
													printf("an986_attach,%d: -> attached\n", devId);
												}
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
	return -1;
}
// 403504: using guessed type int g_verbose;

//----- (00401E3C) --------------------------------------------------------
int an986_ldd_disconnect(int devId)
{
	struct an986_priv *priv; // $v0

	if ( g_verbose )
		printf("an986_detach,%d: -> detached\n", devId);
	priv = (struct an986_priv *)sceUsbdGetPrivateData(devId);
	if ( !priv )
		return -1;
	priv->m_val_for_inet_stop = 1;
	SetEventFlag(priv->m_devops.evfid, 2u);
	return 0;
}
// 403504: using guessed type int g_verbose;

//----- (00401EA4) --------------------------------------------------------
int an986_ldd_probe(int devId)
{
	UsbStringDescriptor *strdesc1; // $s2
	int i; // $s0
	UsbDeviceDescriptor *devdesc; // $v0
	char strlocbuf[16]; // [sp+10h] [-10h] BYREF

	if ( g_verbose )
	{
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
	devdesc = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(devId, 0, 1u);
	if ( !devdesc )
		return 0;
	if ( !do_check_static_descriptor(1, devdesc->idVendor, devdesc->idProduct) )
		return 0;
	g_resident_flag = 1;
	if ( g_load_mode == 't' )
		return 0;
	if ( g_verbose )
	{
		printf("an986_probe,%d: -> accepted\n", devId);
	}
	return 1;
}
// 403504: using guessed type int g_verbose;
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
int scan_number(char *inchr, int *outptr)
{
	char *curchrptr; // $a3
	int base; // $t1
	int curval; // $t0
	int currel; // $a0

	curchrptr = inchr;
	base = 10;
	if ( *inchr == '0' && inchr[1] )
	{
		base = 8;
		curchrptr += 1;
		if ( inchr[1] == 'x' )
		{
			curchrptr += 1;
			base = 16;
		}
	}
	curval = 0;
	if ( *curchrptr )
	{
		while ( 1 )
		{
			if ( (unsigned int)((u8)*curchrptr - 48) >= 0xA )
			{
				if ( (unsigned int)((u8)*curchrptr - 97) >= 6 )
					break;
				currel = (char)(u8)*curchrptr - 87;
			}
			else
			{
				currel = (char)(u8)*curchrptr - 48;
			}
			if ( currel >= base )
				break;
			++curchrptr;
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
int an986_init(int ac, char **av)
{
	int i; // $s2
	char *thpricurx; // $s0
	int loadmode_tmp; // $v0
	unsigned int vidtmp; // [sp+10h] [-8h] BYREF

	g_load_mode = 'n';
	g_resident_flag = 1;
	for ( i = 1; i < ac; i += 1 )
	{
		if ( !strcmp("-help", av[i]) )
			return do_print_help();
		if ( !strcmp("-version", av[i]) )
			return do_print_version();
		if ( !strcmp("-verbose", av[i]) )
		{
			g_verbose = 1;
		}
		else
		{
			if ( !strcmp("-list", av[i]) )
				return do_print_list();
			if ( (strcmp("-p", av[i]) == 0) || (strcmp("-P", av[i]) == 0) )
			{
				g_an986_devinfo[0].m_chip = av[i][1];
				++i;
				if ( i >= ac || scan_number((char *)av[i], (int *)&vidtmp) )
					return do_print_help();
				g_an986_devinfo[0].m_vendor_id = (vidtmp >> 16) & 0xFFFF;
				g_an986_devinfo[0].m_product_id = vidtmp & 0xFFFF;
				continue;
			}
			if ( !strncmp("thpri=", av[i], 6) )
			{
				thpricurx = &av[i][6];
				if ( (look_ctype_table(*thpricurx) & 4) == 0 )
					return do_print_help();
				g_thpri = strtol(thpricurx, 0, 10);
				if ( (unsigned int)(g_thpri - 9) >= 0x73 )
					return do_print_help();
				if ( !*thpricurx )
				{
					continue;
				}
				while ( *thpricurx && (look_ctype_table(*thpricurx) & 4) != 0 )
				{
					++thpricurx;
				}
			}
			else
			{
				if ( strncmp("thstack=", av[i], 8) )
				{
					loadmode_tmp = 'a';
					if ( strcmp("AUTOLOAD", av[i]) != 0 )
					{
						loadmode_tmp = 'a';
						if ( strcmp("lmode=AUTOLOAD", av[i]) != 0 )
						{
							loadmode_tmp = 't';
							if ( strcmp("TESTLOAD", av[i]) != 0 )
							{
								loadmode_tmp = 't';
								if ( strcmp("lmode=TESTLOAD", av[i]) != 0 )
									return do_print_help();
							}
						}
					}
					g_load_mode = loadmode_tmp;
					g_resident_flag = 0;
					continue;
				}
				thpricurx = &av[i][8];
				if ( (look_ctype_table(*thpricurx) & 4) == 0 )
					return do_print_help();
				g_thstack = strtol(thpricurx, 0, 10);
				while ( *thpricurx && ((look_ctype_table(*thpricurx) & 4) != 0) )
				{
					++thpricurx;
				}
				if ( !strcmp(thpricurx, "KB") )
				{
					g_thstack <<= 10;
					continue;
				}
			}
			if ( *thpricurx )
				return do_print_help();
		}
	}
	if ( sceUsbdRegisterLdd(&g_an986_ldd) == 0 )
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
	return 4;
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
	else
	{
		initval = an986_init(ac, av);
		if ( g_verbose )
			printf("an986: an986_init() -> 0x%x\n", initval);
		if ( initval )
		{
			ReleaseLibraryEntries(&_exp_an986);
			return (initval << 4) | (g_resident_flag ? 4 : 0) | 1;
		}
	}
	return 0;
}
// 402750: using guessed type int exports[2];
// 403504: using guessed type int g_verbose;
// 403700: using guessed type int g_resident_flag;
