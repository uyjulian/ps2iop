
#include <irx_imports.h>

IRX_ID("USB_Modem_Driver/Conexant", 16, 22);

#define __fastcall
#define __cdecl
#define __noreturn
#define __int8 char
#define __int16 short
#define __int32 int
#define _BYTE u8
#define _WORD u16
#define _DWORD u32

/* 486 */
typedef int BOOL;

/* 487 */
typedef unsigned __int8 sf;

/* 488 */
typedef unsigned __int8 BOOLEAN;

/* 489 */
typedef unsigned int DWORD;

/* 490 */
typedef unsigned __int16 WORD;

/* 491 */
typedef unsigned __int8 UCHAR;

/* 492 */
typedef unsigned __int8 *PUCHAR;

/* 493 */
typedef int LONG;

/* 494 */
typedef unsigned int ULONG;

/* 495 */


/* 496 */
struct USBACF_Recv
{
  UCHAR Reg06;
  struct _USBACF_Recv_RxData
  {
    UCHAR Reg05;
    UCHAR Reg00;
  } RxData[15];
};

/* 497 */
struct USBACF_Txmit
{
  UCHAR addrH;
  UCHAR addrL;
  UCHAR data;
};

/* 498 */
struct PIPE_DATA
{
  int PipeHandle;
  LONG nActiveRequests;
  BOOLEAN NeedReset;
};

/* 501 */
typedef struct DEVICE_EXTENSION *PDEVICE_EXTENSION;

/* 502 */
struct DEVICE_EXTENSION
{
  int Handle;
  ULONG OpenCount;
  BOOLEAN Removed;
  BOOLEAN Started;
  BOOLEAN RegChangeFlag;
  BOOLEAN Configured;
  BOOLEAN NeedCleanup;
  int EP0Pipe;
  int RxEvent;
  struct PIPE_DATA PipeList[16];
  unsigned __int8 TxFIFO[1024];
  unsigned __int8 TxSendBuf[16];
  int TxFIFOIdx;
  unsigned __int8 RxFIFO[4096];
  unsigned __int8 RegShadow[8];
  unsigned __int8 RegChanged[8];
  union DEVICE_EXTENSION_u
  {
    UCHAR GpioBuf[4];
    struct _DEVICE_EXTENSION_u_s
    {
      UCHAR UsbGpout;
      UCHAR UsbGpoutEnable;
      UCHAR UsbModeByte;
      UCHAR UsbLedByte;
    } s;
  } u;
  BOOLEAN bGpioChanged;
  UCHAR bHighAddr;
  int RxFifoGetIdx;
  int RxFifoPutIdx;
  struct USBACF_Txmit TxRegs[16];
  struct USBACF_Txmit TmpTxRegs[16];
  int TmpTxRegIndex;
  int TxBufferToggle;
  struct USBACF_Recv RecvRegs;
  int bPowerState;
  ULONG dwFlags;
  int TxHandlerReentrancy;
  int MakeDataTransmitReentrancy;
  int RxHandlerReentrancy;
  ULONG RShellNtMCRshadow;
  UCHAR RShellNtMSRshadow;
  ULONG RShellNtOldMSRshadow;
  BOOLEAN DeviceIsOpened;
  UCHAR OldMSRShadow;
  int sm_xmit;
  int fpl;
  int mbxid;
  int buflen;
  iop_sys_clock_t sys_clock;
  BOOLEAN LedB1_Flag;
  BOOLEAN LedB2_Flag;
  sceModemOps_t modem_ops;
  int m_rx_count;
  int m_tx_count;
  int m_ef_bits;
  int m_evid_main;
  int m_thid1;
  int m_thid2;
  int m_thid_patchload;
  int m_recv_alarm_active;
  int m_modem_init_state;
  int f_patch;
  int m_status_80_flag;
  int m_status_40_flag;
  int f_started;
  UCHAR m_man[31];
  UCHAR m_pro[31];
  int m_recv_ev_count;
};

/* 505 */
typedef unsigned __int8 AT_UBYTE;

/* 506 */
typedef signed __int8 AT_SBYTE;

/* 507 */
typedef unsigned __int16 AT_UINT16;

/* 508 */
typedef signed __int16 AT_SINT16;

/* 509 */
typedef unsigned int AT_UINT32;

/* 510 */
typedef int AT_SINT32;

/* 511 */
typedef void AT_TASK;

/* 512 */
typedef AT_UINT32 AT_NINT32;

/* 513 */
typedef AT_UINT16 AT_NINT16;

/* 514 */
typedef AT_UINT32 AT_MTU;

/* 515 */
struct _AT_ETHER_HW_ADDR
{
  AT_UBYTE hw_addr[6];
};

/* 516 */
typedef struct _AT_ETHER_HW_ADDR AT_ETHER_HW_ADDR;

/* 517 */
typedef AT_UINT32 AT_datasize_t;

/* 518 */
struct _AT_Vptr
{
  AT_UINT32 buff;
  AT_UBYTE type;
};

/* 519 */
typedef struct _AT_Vptr AT_Vptr;

/* 520 */
struct _AT_VptrArray
{
  AT_SINT16 len;
  AT_Vptr vptr;
};

/* 521 */
typedef struct _AT_VptrArray AT_VptrArray;

/* 522 */
struct _AT_RevBuffs
{
  AT_datasize_t bufnum;
  AT_datasize_t total_len;
  AT_VptrArray buffers[1];
};

/* 523 */
typedef struct _AT_RevBuffs AT_RevBuffs;

/* 524 */
typedef AT_RevBuffs AT_Buffs;

/* 525 */
struct _AT_MaxBuffs
{
  AT_datasize_t bufnum;
  AT_datasize_t total_len;
  AT_VptrArray buffers[12];
};

/* 526 */
typedef struct _AT_MaxBuffs AT_MaxBuffs;

/* 527 */
typedef unsigned __int8 AT_CHAR;

/* 528 */
struct PP_modemProperty
{
  AT_SINT16 needToInit;
  AT_SINT16 needToDial;
  AT_SINT16 needToCd;
  AT_SINT16 needToDisc;
  AT_SINT16 connectHasSpeedReply;
  AT_CHAR *toneDialCommand;
  AT_CHAR *pulseDialCommand;
  AT_CHAR *answerCommand;
  AT_CHAR *okReply;
  AT_CHAR *connectReply;
  AT_CHAR *busyReply;
  AT_CHAR *errorReply;
  AT_CHAR *delayedReply;
  AT_CHAR *noCarrierReply;
  AT_CHAR *noDialToneReply;
  AT_CHAR *ringinMsg;
  AT_CHAR newLineChar;
  AT_CHAR *initScript;
  AT_CHAR *connScript;
  AT_CHAR *discScript;
};

/* 529 */
typedef struct PP_modemProperty PP_MODEM_PROPERTY;

/* 530 */
typedef AT_SBYTE PP_SBYTE;

/* 531 */
typedef AT_UBYTE PP_UBYTE;

/* 532 */
typedef AT_SINT16 PP_SWORD;

/* 533 */
typedef AT_UINT16 PP_UWORD;

/* 534 */
typedef AT_SINT32 PP_SLONG;

/* 535 */
typedef AT_UINT32 PP_ULONG;

/* 536 */
enum _PP_BOOL
{
  PP_FALSE = 0x0,
  PP_TRUE = 0x1,
};

/* 537 */
typedef enum _PP_BOOL PP_BOOL;

/* 538 */
enum _PP_YES_NO
{
  PP_YES = 0x0,
  PP_NO = 0x1,
};

/* 539 */
typedef enum _PP_YES_NO PP_YES_NO;

/* 540 */
enum _PP_OK_NG
{
  PP_OK = 0x0,
  PP_NG = 0x1,
};

/* 541 */
typedef enum _PP_OK_NG PP_OK_NG;

/* 542 */
enum _PP_ONOFF
{
  PP_OFF = 0x0,
  PP_ON = 0x1,
};

/* 543 */
typedef enum _PP_ONOFF PP_ONOFF;

/* 544 */
typedef void (__cdecl *PP_INTERRUPT)(int fxme1, int fxme2, int fxme3, int fxme4);

/* 545 */
enum _PP_COM_RESULT
{
  PP_COM_NOERR = 0x0,
  PP_COM_ERR_GENE = 0x1,
  PP_COM_ERR_OPEN = 0x2,
  PP_COM_ERR_UP = 0x3,
  PP_COM_ERR_DOWN = 0x4,
  PP_COM_ERR_WRITE = 0x5,
  PP_COM_ERR_READ = 0x6,
};

/* 546 */
typedef enum _PP_COM_RESULT PP_COM_RESULT;

/* 547 */
enum _PP_COM_PARITY
{
  PP_COM_PARITY_EVEN = 0x0,
  PP_COM_PARITY_ODD = 0x1,
  PP_COM_PARITY_NON = 0x2,
};

/* 548 */
typedef enum _PP_COM_PARITY PP_COM_PARITY;

/* 549 */
enum _PP_COM_STOP
{
  PP_COM_STOP1 = 0x0,
  PP_COM_STOP15 = 0x1,
  PP_COM_STOP2 = 0x2,
};

/* 550 */
typedef enum _PP_COM_STOP PP_COM_STOP;

/* 551 */
enum _PP_COM_FLOW
{
  PP_COM_FLOW_XONOFF = 0x0,
  PP_COM_FLOW_RTSCTS = 0x1,
};

/* 552 */
typedef enum _PP_COM_FLOW PP_COM_FLOW;

/* 553 */
enum _PP_COM_SPEED
{
  PP_COM_SPEED_2400 = 0x0,
  PP_COM_SPEED_4800 = 0x1,
  PP_COM_SPEED_9600 = 0x2,
  PP_COM_SPEED_19200 = 0x3,
  PP_COM_SPEED_38400 = 0x4,
  PP_COM_SPEED_57600 = 0x5,
  PP_COM_SPEED_115200 = 0x6,
};

/* 554 */
typedef enum _PP_COM_SPEED PP_COM_SPEED;

/* 555 */
enum _PP_COM_WORD
{
  PP_COM_WORD7 = 0x0,
  PP_COM_WORD8 = 0x1,
};

/* 556 */
typedef enum _PP_COM_WORD PP_COM_WORD;

/* 557 */
enum _PP_COM_NUM
{
  PP_COM1 = 0x0,
  PP_COM2 = 0x1,
};

/* 558 */
typedef enum _PP_COM_NUM PP_COM_NUM;

/* 559 */
struct _PP_COM_PARA
{
  PP_COM_NUM devNum;
  PP_COM_PARITY parity;
  PP_COM_STOP stop;
  PP_COM_FLOW flow;
  PP_COM_SPEED speed;
  PP_COM_WORD wordlength;
  PP_UWORD vector;
};

/* 560 */
typedef struct _PP_COM_PARA PP_COM_PARA;

/* 561 */
typedef unsigned __int8 BYTE;


//-------------------------------------------------------------------------
// Function declarations

static void __fastcall wrap_set_event_flag_modem(PDEVICE_EXTENSION pUsb, u32 flagval);
static void __fastcall wrap_set_event_flag_main(PDEVICE_EXTENSION pUsb, u32 flagval);
static int __fastcall ModemWrite(void *userdata, void *data, int len);
static int __fastcall PatchWrite(PDEVICE_EXTENSION pUsb, const char *data, int len);
static int __fastcall ModemControl(void *userdata, int cmd, void *buf, int bufsz);
static int __fastcall ModemGetStatus(PDEVICE_EXTENSION pUsb);
static int __fastcall ModemStart(void *userdata, int unused);
static unsigned int __fastcall recv_alarm_callback(void *userdata);
static int __fastcall get_ef_bits(PDEVICE_EXTENSION pUsb);
static u32 __fastcall wait_for_ef_bits(PDEVICE_EXTENSION pUsb, u32 bits);
static void __fastcall __noreturn th_2_proc_modem_status(void *userdata);
static void __fastcall th_1_proc_ef_bits(void *userdata);
static void __fastcall cxtmdm_patchload_thread(void *userdata);
static PDEVICE_EXTENSION do_alloc_mem_for_dev_ext();
static void __fastcall do_delete_threads(PDEVICE_EXTENSION pUsb);
static int __fastcall ModemStop(void *userdata, int unused);
static void __fastcall USBACF_RxFlowControl(PDEVICE_EXTENSION pUsb);
static int __fastcall ModemRead(void *userdata, void *buff, int size);
static int __fastcall PatchRead(PDEVICE_EXTENSION pUsb, char *buff, int size);
static void __fastcall set_interface_done(int result, int count, void *arg);
static void __fastcall set_config_done(int result, int count, void *arg);
static int __fastcall UsbAcfModemProbe(int dev_id);
static int __fastcall UsbAcfModemAttach(int dev_id);
static int __fastcall UsbAcfModemDetach(int dev_id);
int __fastcall _start(int argc, char **argv);
static void __fastcall USBACF_Write16550Reg(PDEVICE_EXTENSION pUsb, int reg, char data);
static void __fastcall MakeDataTransferRequest(PDEVICE_EXTENSION pUsb, BOOLEAN CallTxHandler);
static int __fastcall USBACF_GetRxChar(PDEVICE_EXTENSION pUsb);
static BOOLEAN __fastcall USBACF_TxBufferFull(PDEVICE_EXTENSION pUsb);
static void __fastcall USBACF_PutTxChar(PDEVICE_EXTENSION pUsb, char data);
static void __fastcall UsbTransmitRegisterCompletionRoutine(int result, int count, void *context);
static void __fastcall UsbTransmitDataCompletionRoutine(int result, int count, void *context);
static void __fastcall UsbReceiveRegisterCompletionRoutine(int result, int count, void *context);
static void __fastcall OnNewStatusReceived(PDEVICE_EXTENSION pUsb, struct USBACF_Recv *pUsbRecv, int nFifoCharsReceived);
static BOOLEAN __fastcall USBACF_RxBufferNotEmpty(PDEVICE_EXTENSION pUsb);
static int __fastcall CallUsbd(PDEVICE_EXTENSION pUsb, struct PIPE_DATA *Pipe, void *Buf, int Length, sceUsbdDoneCallback CompletionRoutine);
static void __fastcall MakeReceiveRequest(PDEVICE_EXTENSION pUsb);
static void __fastcall MakeRegisterTransmitRequest(PDEVICE_EXTENSION pUsb);
static void __fastcall OnTransmitCompleted(PDEVICE_EXTENSION pUsb, int PacketLength);
static void __fastcall UsbTransmitGpioCompletionRoutine(int result, int count, void *context);
static void __fastcall SendGpioLedRequest(PDEVICE_EXTENSION pUsb);
static void __fastcall USBMODEM_ModifyMode(PDEVICE_EXTENSION pUsb, BYTE SetMode, BYTE ResetMode);
static void __fastcall USBMODEM_ModifyLed(PDEVICE_EXTENSION pUsb, BYTE SetMode, BYTE ResetMode);
static void __fastcall SetUsbModemPollState(PDEVICE_EXTENSION pUsb, int state);

//-------------------------------------------------------------------------
// Data declarations

static char usbacf_patch[2275] = "S3100000A000B20269A9008DBC044C0EE101\r\nS31500009DA560606B606060606B6B6060606060606087\r\nS31500009DB56B60606B60606060606060606060606082\r\nS31500009DC56060606060606060606060606060606088\r\nS31500009DD5606060606060606B6B6060606060606062\r\nS31500009DE560606B606060606060606060606B606052\r\nS30700009DF5000066\r\nS31500009EB00000E500000000D02000000000000000C7\r\nS31500009EC0DD000003000000000000000000000000AC\r\nS31500009ED0000000000000000000000000000000007C\r\nS31500009EE00000000000000018DA000000000000007A\r\nS31500009EF00000E200000000000000000000A60000D4\r\nS30600009F00005A\r\nS31500009F010917FF4C11AD6487D00CA21820445A29B9\r\nS31500009F111F09804CF558604C83863D534C562BA93E\r\nS31500009F216B8DA79DA0FFA204C8B97B04C90DF03EA5\r\nS31500009F31DD1B9FD0F1CA10F0C8B97B04C934D00427\r\nS31500009F41A9388027C935D004A939801FC936D0D68A\r\nS31500009F51206A9FA200E8C8B97B04C90DD0F7B97B76\r\nS31500009F6104997C0488CAD0F6C8A931997B04A0FF5C\r\nS31500009F71A203C8B97B04C90DF026DDA29FD0F1CAA0\r\nS31500009F8110F0C8B97B04997704C90DD0F5ADCE049C\r\nS31500009F912901F009B28C40B200414CA3254CA02501\r\nS31500009FA1605652542DE25D0110244F6321AD3F8767\r\nS31500009FB1C9B1F015AD4D87C900F0132073E720D75D\r\nS31500009FC19FE2600110084CAE77A9008D4D8760A213\r\nS31500009FD103A9004C9BE44C019E4CF99DD20839061D\r\nS31500009FE1604C7886A900CDA102D00AA973CD0D01D6\r\nS31000009FF1B0038D0D01A9608DA79D60D7\r\nS31500009DF97F4C04D210600160AD43878540AD44872E\r\nS31500009E09854138A540E98C8540A541E9008541A5EC\r\nS31500009E1940ED52878540A541ED53878541A54148C7\r\nS31500009E29A5408542AD47878540AD48878541208B4A\r\nS31500009E3969B26444B20045B20043205022A5408D60\r\nS31500009E494D87A5418D4E87688542AD47878540ADCB\r\nS31500009E5948878541208B69B26444B20045B2004304\r\nS31500009E69205022A54148A54048B2FF42208B696887\r\nS31500009E798544688545A54065448540A54165458570\r\nS31500009E8941A54269008542A5406D4D878540A5419A\r\nS31400009E996D4E878541A54269008D4F874CA9867E\r\nS31500008678A950CD0286B0038D028660AD5702C93C6B\r\nS31500008688D01EB20747B25046B20A45B2B944209640\r\nS31500008698E3B20747B25046B20B45B2B9442096E357\r\nS315000086A860A5408D4D87A5418D4E87B2D040B20753\r\nS315000086B841B25A42208B69A542CD4F87F004B038A3\r\nS315000086C8800EA541CD4E87D005A540CD4D87B02853\r\nS315000086D8AD4B878540AD4C878541A541C900D0047F\r\nS315000086E8A540C996B012A9758D3F87A9778D408791\r\nS30E000086F8B200AEB248B1B75960F8\r\nS70500000000FA\r\n"; // weak
static sceUsbdLddOps UsbAcfDriverDescriptor =
{
  NULL,
  NULL,
  "Conexant USB Modem Driver",
  &UsbAcfModemProbe,
  &UsbAcfModemAttach,
  &UsbAcfModemDetach,
  0u,
  0u,
  0u,
  0u,
  0u,
  NULL
}; // weak
static int thread_priority = 28; // weak
static int stack_size = 4096; // weak
static int resident_flag; // weak
static int load_mode; // weak
static char g_dialconf[400]; // idb


//----- (00400000) --------------------------------------------------------
static void __fastcall wrap_set_event_flag_modem(PDEVICE_EXTENSION pUsb, u32 flagval)
{
  char outbuf[104]; // [sp+10h] [-68h] BYREF

  if ( (flagval & 0x200) == 0 )
    sprintf(outbuf, "%s%s%s%s%s%s", ( (flagval & 1) != 0 ) ? " StartDone" : "", ( (flagval & 2) != 0 ) ? " PlugOut" : "", ( (flagval & 0x10) != 0 ) ? " Connect" : "", ( (flagval & 0x20) != 0 ) ? " Disconnect" : "", ( (flagval & 0x40) != 0 ) ? " Ring" : "", ( (flagval & 0x100) != 0 ) ? " Recv" : "");
  SetEventFlag(pUsb->modem_ops.evfid, flagval);
}
// 400000: using guessed type char outbuf[104];

//----- (00400138) --------------------------------------------------------
static void __fastcall wrap_set_event_flag_main(PDEVICE_EXTENSION pUsb, u32 flagval)
{
  char curbuf[104]; // [sp+10h] [-68h] BYREF

  sprintf(curbuf, "%s%s%s%s", ( (flagval & 1) != 0 ) ? " START" : "", ( (flagval & 2) != 0 ) ? " STOP" : "", ( (flagval & 8) != 0 ) ? " STATE" : "", ( (flagval & 0x400) != 0 ) ? " BREAK" : "");
  SetEventFlag(pUsb->m_evid_main, flagval);
}
// 400138: using guessed type char curbuf[104];

//----- (00400208) --------------------------------------------------------
static int __fastcall ModemWrite(void *userdata, void *data, int len)
{
  int cnt; // $s3
  int xsend_len; // $v0
  int state; // [sp+10h] [-8h] BYREF
  PDEVICE_EXTENSION pUsb;

  pUsb = userdata;
  if ( !pUsb->f_started || !pUsb->f_patch )
    return 0;
  CpuSuspendIntr(&state);
  xsend_len = pUsb->modem_ops.snd_len - len;
  if ( xsend_len < 0 )
    xsend_len = sizeof(pUsb->TxFIFO);
  pUsb->modem_ops.snd_len = xsend_len;
  CpuResumeIntr(state);
  for ( cnt = 0; cnt < len; cnt += 1 )
  {
    if ( USBACF_TxBufferFull(pUsb) )
    {
      MakeDataTransferRequest(pUsb, 0);
      DelayThread(10000);
    }
    if ( USBACF_TxBufferFull(pUsb) )
      break;
    USBACF_PutTxChar(pUsb, ((char *)data)[cnt]);
  }
  MakeDataTransferRequest(pUsb, 0);
  return cnt;
}

//----- (00400338) --------------------------------------------------------
static int __fastcall PatchWrite(PDEVICE_EXTENSION pUsb, const char *data, int len)
{
  int cnt; // $s3
  int xsend_len; // $v0
  int state; // [sp+10h] [-8h] BYREF

  
  CpuSuspendIntr(&state);
  xsend_len = pUsb->modem_ops.snd_len - len;
  if ( xsend_len < 0 )
    xsend_len = sizeof(pUsb->TxFIFO);
  pUsb->modem_ops.snd_len = xsend_len;
  CpuResumeIntr(state);
  for ( cnt = 0; cnt < len; cnt += 1 )
  {
    while ( USBACF_TxBufferFull(pUsb) )
    {
      MakeDataTransferRequest(pUsb, 0);
      WaitSema(pUsb->sm_xmit);
    }
    USBACF_PutTxChar(pUsb, data[cnt]);
  }
  MakeDataTransferRequest(pUsb, 0);
  return cnt;
}

//----- (00400444) --------------------------------------------------------
static int __fastcall ModemControl(void *userdata, int cmd, void *buf, int bufsz)
{
  size_t retres; // $s1
  PDEVICE_EXTENSION pUsb;
  int if_type; // [sp+10h] [-10h] BYREF
  int state; // [sp+14h] [-Ch] BYREF
  int priority; // [sp+18h] [-8h] BYREF

  pUsb = userdata;
  switch ( cmd )
  {
  case sceModemCC_FLUSH_TXBUF:
    {
      CpuSuspendIntr(&state);
      pUsb->TxFIFOIdx = 0;
      pUsb->modem_ops.snd_len = sizeof(pUsb->TxFIFO);
      CpuResumeIntr(state);
      return 0;
    }
  case sceModemCC_GET_RX_COUNT:
    {
      if ( bufsz != 4 )
        return -512;
      bcopy(&pUsb->m_rx_count, buf, 4);
      return 0;
    }
  case sceModemCC_GET_TX_COUNT:
    {
      if ( bufsz != 4 )
        return -512;
      bcopy(&pUsb->m_tx_count, buf, 4);
      return 0;
    }
  case sceModemCC_SET_THPRI:
    {
      if ( bufsz != 4 )
        return -512;
      bcopy(buf, &priority, 4);
      retres = 0;
      if ( pUsb->m_thid1 > 0 )
      {
        retres = ChangeThreadPriority(pUsb->m_thid1, priority);
        if ( !retres )
          thread_priority = priority;
      }
      if ( pUsb->m_thid2 > 0 )
      {
        retres = ChangeThreadPriority(pUsb->m_thid2, priority);
        if ( !retres )
          thread_priority = priority;
      }
      if ( (pUsb->m_thid1 <= 0 || (int)retres == -413) && (unsigned int)(priority - 9) < 0x73 )
        thread_priority = priority;
      return retres;
    }
  case sceModemCC_GET_DIALCONF:
    {
      retres = strlen(g_dialconf) + 1;
      if ( bufsz < (int)retres )
        return -512;
      bcopy(g_dialconf, buf, retres);
      return retres;
    }
  case sceModemCC_GET_IF_TYPE:
    {
      if ( bufsz != 4 )
        return -512;
      if_type = sceModemIFT_GENERIC;
      bcopy(&if_type, buf, 4);
      return 0;
    }
  case sceModemCC_GET_THPRI:
    {
      if ( bufsz != 4 )
        return -512;
      bcopy(&thread_priority, buf, 4);
      return 0;
    }
  case sceModemCC_FLUSH_RXBUF:
    {
      CpuSuspendIntr(&state);
      pUsb->modem_ops.rcv_len = 0;
      pUsb->RxFifoGetIdx = 0;
      pUsb->RxFifoPutIdx = 0;
      CpuResumeIntr(state);
      return 0;
    }
  default:
    return -513;
  }
}
// 4034E8: using guessed type int thread_priority;

//----- (004006C8) --------------------------------------------------------
static int __fastcall ModemGetStatus(PDEVICE_EXTENSION pUsb)
{
  return pUsb->RShellNtMSRshadow;
}

//----- (004006D4) --------------------------------------------------------
static int __fastcall ModemStart(void *userdata, int unused)
{
  int i; // $s1
  UsbDeviceDescriptor *data; // $a1
  PDEVICE_EXTENSION pUsb;

  (void)unused;
  pUsb = userdata;
  data = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(pUsb->Handle, 0, 1u);
  if ( !data )
    return 0;
  if ( data->idVendor != 1394 )
    return 0;
  if ( data->idProduct != 4658 && data->idProduct != 4722 )
    return 0;
  if ( !sceUsbdScanStaticDescriptor(pUsb->Handle, data, 4u) )
    return 0;
  if ( pUsb->m_modem_init_state == 5 )
    return 0;
  for ( i = 0; i < 20; i += 1 )
  {
    if ( pUsb->f_patch )
      break;
    DelayThread(500000);
  }
  if ( pUsb->f_started != 1 )
  {
    USBACF_Write16550Reg(pUsb, 3, -128);
    USBACF_Write16550Reg(pUsb, 0, 1);
    USBACF_Write16550Reg(pUsb, 1, 0);
    DelayThread(100000);
    USBACF_Write16550Reg(pUsb, 3, 3);
    USBACF_Write16550Reg(pUsb, 2, -31);
    USBACF_Write16550Reg(pUsb, 4, 3);
  }
  USBMODEM_ModifyLed(pUsb, 1u, 0);
  wrap_set_event_flag_main(pUsb, 1u);
  pUsb->f_started = 1;
  return 0;
}

//----- (00400854) --------------------------------------------------------
static unsigned int __fastcall recv_alarm_callback(void *userdata)
{
  PDEVICE_EXTENSION pUsb;

  pUsb = userdata;
  pUsb->m_recv_alarm_active = 0;
  pUsb->modem_ops.rcv_len = pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx;
  iSetEventFlag(pUsb->modem_ops.evfid, sceModemEFP_Recv);
  pUsb->m_recv_ev_count += 1;
  return 0;
}

//----- (004008A8) --------------------------------------------------------
static int __fastcall get_ef_bits(PDEVICE_EXTENSION pUsb)
{
  return pUsb->m_ef_bits;
}

//----- (004008B4) --------------------------------------------------------
static u32 __fastcall wait_for_ef_bits(PDEVICE_EXTENSION pUsb, u32 bits)
{
  int m_ef_bits; // $v1
  u32 efbits; // [sp+10h] [-8h] BYREF

  efbits = 0;
  if ( (pUsb->m_ef_bits & bits) == 0 && WaitEventFlag(pUsb->m_evid_main, bits, 17, &efbits) != 0 )
    return -1;
  pUsb->m_ef_bits |= efbits;
  m_ef_bits = pUsb->m_ef_bits;
  pUsb->m_ef_bits = m_ef_bits & ~bits;
  return m_ef_bits & bits;
}

//----- (0040092C) --------------------------------------------------------
static void __fastcall __noreturn th_2_proc_modem_status(void *userdata)
{
  char Status; // $s1
  PDEVICE_EXTENSION pUsb;

  pUsb = userdata;
  while ( 1 )
  {
    Status = ModemGetStatus(pUsb);
    if ( (unsigned int)(pUsb->m_modem_init_state - 2) < 2 )
    {
      if ( pUsb->m_status_80_flag )
      {
        if ( (Status & 0x80) == 0 )
        {
          pUsb->m_status_80_flag = 0;
          wrap_set_event_flag_main(pUsb, 8u);
          USBMODEM_ModifyLed(pUsb, 0, 2);
        }
      }
      else
      {
        if ( (Status & 0x80) != 0 )
        {
          pUsb->m_status_80_flag = 1;
          wrap_set_event_flag_main(pUsb, 8u);
          USBMODEM_ModifyLed(pUsb, 2, 0);
        }
      }
    }
    if ( pUsb->m_status_40_flag )
    {
      if ( (Status & 0x40) == 0 )
      {
        pUsb->m_status_40_flag = 0;
        wrap_set_event_flag_main(pUsb, 8u);
      }
    }
    else
    {
      if ( (Status & 0x40) != 0 )
      {
        pUsb->m_status_40_flag = 1;
        wrap_set_event_flag_main(pUsb, 8u);
      }
    }
    MakeDataTransferRequest(pUsb, 0);
    DelayThread(1000000);
  }
}

//----- (00400A2C) --------------------------------------------------------
static void __fastcall th_1_proc_ef_bits(void *userdata)
{
  signed __int32 efbits_ret; // $v0
  PDEVICE_EXTENSION pUsb;

  pUsb = (PDEVICE_EXTENSION)userdata;
  pUsb->modem_ops.snd_len = sizeof(pUsb->TxFIFO);
  pUsb->m_modem_init_state = 0;
  while ( 1 )
  {
    efbits_ret = wait_for_ef_bits(pUsb, 0x7FFu);
    if ( efbits_ret < 0 )
      return;
    switch ( pUsb->m_modem_init_state )
    {
      case 0u:
        if ( (efbits_ret & 1) != 0 && pUsb->f_patch == 1 )
        {
          pUsb->m_modem_init_state = 2;
          wrap_set_event_flag_modem(pUsb, sceModemEFP_StartDone);
        }
        else if ( (efbits_ret & 1) != 0 )
        {
          pUsb->m_modem_init_state = 1;
        }
        break;
      case 1u:
        if ( (efbits_ret & 8) != 0 && pUsb->f_patch == 1 )
        {
          pUsb->m_modem_init_state = 2;
          wrap_set_event_flag_modem(pUsb, sceModemEFP_StartDone);
        }
        break;
      case 2u:
        if ( (efbits_ret & 8) != 0 && pUsb->m_status_80_flag )
        {
          pUsb->m_modem_init_state = 3;
          wrap_set_event_flag_modem(pUsb, sceModemEFP_Connect);
          USBMODEM_ModifyLed(pUsb, 2, 0);
        }
        break;
      case 3u:
        if ( (efbits_ret & 8) != 0 && !pUsb->m_status_80_flag )
        {
          pUsb->m_modem_init_state = 2;
          wrap_set_event_flag_modem(pUsb, sceModemEFP_Disconnect);
          USBMODEM_ModifyLed(pUsb, 0, 2);
        }
        break;
      case 4u:
        pUsb->m_modem_init_state = 0;
        wrap_set_event_flag_modem(pUsb, sceModemEFP_Disconnect);
        USBMODEM_ModifyLed(pUsb, 0, 2);
        break;
      case 5u:
      default:
        continue;
    }
    if ( (unsigned int)(pUsb->m_modem_init_state - 2) >= 2 )
      continue;
    if ( (efbits_ret & 2) != 0 )
    {
      pUsb->m_modem_init_state = 0;
      USBMODEM_ModifyLed(pUsb, 0, 1u);
    }
    else
    {
      if ( (efbits_ret & 0x400) != 0 )
        get_ef_bits(pUsb);
      if ( !pUsb->m_status_80_flag && pUsb->m_status_40_flag == 1 )
        wrap_set_event_flag_modem(pUsb, sceModemEFP_Ring);
    }
  }
}

//----- (00400C00) --------------------------------------------------------
static void __fastcall cxtmdm_patchload_thread(void *userdata)
{
  int readcmp1; // $s6
  int tempbuf_read1; // $s1
  int trycnt2; // $s3
  int patchread_bytes1; // $v0
  int tempbuf_ind1; // $s0
  int tempbuf_read2; // $s1
  int trycnt1; // $s3
  int patchread_bytes2; // $v0
  int tempbuf_ind2; // $s0
  char ati3[8]; // [sp+10h] [-B8h] BYREF
  char atload[8]; // [sp+18h] [-B0h] BYREF
  char tempbuf[152]; // [sp+20h] [-A8h] BYREF
  char tempstr[16]; // [sp+B8h] [-10h] BYREF
  PDEVICE_EXTENSION pUsb;

  pUsb = (PDEVICE_EXTENSION)userdata;
  readcmp1 = 0;
  strcpy(ati3, "ati3\r");
  strcpy(atload, "at**\r");
  strcpy(tempstr, "P2109-V90");
  USBACF_Write16550Reg(pUsb, 3, -128);
  USBACF_Write16550Reg(pUsb, 0, 1);
  USBACF_Write16550Reg(pUsb, 1, 0);
  DelayThread(100000);
  USBACF_Write16550Reg(pUsb, 3, 3);
  USBACF_Write16550Reg(pUsb, 2, -31);
  USBACF_Write16550Reg(pUsb, 4, 3);
  USBMODEM_ModifyLed(pUsb, 1u, 0);
  DelayThread(2000000);
  PatchWrite(pUsb, ati3, 6);
  DelayThread(1000000);
  tempbuf_read1 = 0;
  for ( trycnt2 = 0; trycnt2 <= 99999; trycnt2 += 1 )
  {
    patchread_bytes1 = PatchRead(pUsb, &tempbuf[tempbuf_read1], 50 - tempbuf_read1);
    if ( patchread_bytes1 )
    {
      tempbuf_read1 += patchread_bytes1;
      for ( tempbuf_ind1 = 0; tempbuf_ind1 < tempbuf_read1 - 1; tempbuf_ind1 += 1 )
      {
        if ( !memcmp(&tempbuf[tempbuf_ind1], tempstr, 9) )
        {
          readcmp1 = 1;
          break;
        }
      }
      if ( readcmp1 == 1 )
      {
        PatchWrite(pUsb, atload, 6);
        DelayThread(1000000);
        tempbuf_read2 = 0;
        for ( trycnt1 = 0; trycnt1 < 100; trycnt1 += 1 )
        {
          patchread_bytes2 = PatchRead(pUsb, &tempbuf[tempbuf_read2], 50 - tempbuf_read2);
          if ( patchread_bytes2 )
          {
            tempbuf_read2 += patchread_bytes2;
            for ( tempbuf_ind2 = 0; tempbuf_ind2 < tempbuf_read2 - 1; tempbuf_ind2 += 1 )
            {
              if ( !memcmp(&tempbuf[tempbuf_ind2], "..", 2) )
              {
                readcmp1 = 2;
                break;
              }
            }
            if ( readcmp1 == 2 )
              break;
            DelayThread(5000000);
          }
        }
        PatchWrite(pUsb, usbacf_patch, 2274);
        break;
      }
    }
  }
  USBACF_Write16550Reg(pUsb, 2, 3);
  if ( !pUsb->m_modem_init_state )
  {
    USBACF_Write16550Reg(pUsb, 4, 0);
    USBACF_Write16550Reg(pUsb, 2, 3);
  }
  if ( pUsb->m_modem_init_state == 1 )
    wrap_set_event_flag_main(pUsb, 8u);
  pUsb->f_patch = 1;
}
// 400DEC: conditional instruction was optimized away because $s6.4==0
// 400C00: using guessed type char tempbuf[152];

//----- (00400F40) --------------------------------------------------------
static PDEVICE_EXTENSION do_alloc_mem_for_dev_ext()
{
  PDEVICE_EXTENSION pUsb; // $s0
  iop_event_t evparam; // [sp+10h] [-50h] BYREF
  iop_thread_t thparam1; // [sp+20h] [-40h] BYREF
  iop_thread_t thparam2; // [sp+38h] [-28h] BYREF
  iop_sema_t semaparam; // [sp+50h] [-10h] BYREF

  pUsb = (PDEVICE_EXTENSION)sceInetAllocMem(0, sizeof(*pUsb));
  if ( !pUsb )
    return 0;
  bzero(pUsb, sizeof(*pUsb));
  pUsb->MakeDataTransmitReentrancy = -1;
  pUsb->PipeList[4].nActiveRequests = 0;
  semaparam.attr = 0;
  semaparam.initial = 1;
  semaparam.max = 1;
  semaparam.option = 0;
  pUsb->sm_xmit = CreateSema(&semaparam);
  pUsb->bHighAddr = 64;
  memset(&evparam, 0, sizeof(evparam));
  pUsb->m_evid_main = CreateEventFlag(&evparam);
  if ( pUsb->m_evid_main > 0 )
  {
    thparam1.attr = 0x2000000;
    thparam1.thread = th_1_proc_ef_bits;
    thparam1.option = 0;
    thparam1.priority = thread_priority;
    thparam1.stacksize = stack_size;
    pUsb->m_thid1 = CreateThread(&thparam1);
    if ( pUsb->m_thid1 > 0 && !StartThread(pUsb->m_thid1, pUsb) )
    {
      pUsb->m_status_80_flag = 0;
      pUsb->m_status_40_flag = 0;
      thparam2.attr = 0x2000000;
      thparam2.thread = th_2_proc_modem_status;
      thparam2.option = 0;
      thparam2.priority = thread_priority;
      thparam2.stacksize = stack_size;
      pUsb->m_thid2 = CreateThread(&thparam2);
      if ( pUsb->m_thid2 > 0 && !StartThread(pUsb->m_thid2, pUsb) )
      {
        USec2SysClock(0x2710u, &pUsb->sys_clock);
        return pUsb;
      }
      DeleteThread(pUsb->m_thid2);
    }
    DeleteEventFlag(pUsb->m_evid_main);
  }
  sceInetFreeMem(0, pUsb);
  return 0;
}
// 4034E8: using guessed type int thread_priority;
// 4034EC: using guessed type int stack_size;

//----- (004010A4) --------------------------------------------------------
static void __fastcall do_delete_threads(PDEVICE_EXTENSION pUsb)
{
  TerminateThread(pUsb->m_thid1);
  TerminateThread(pUsb->m_thid2);
  TerminateThread(pUsb->m_thid_patchload);
  DeleteThread(pUsb->m_thid1);
  DeleteThread(pUsb->m_thid2);
  DeleteThread(pUsb->m_thid_patchload);
  DeleteSema(pUsb->sm_xmit);
  DeleteEventFlag(pUsb->m_evid_main);
  sceInetFreeMem(0, pUsb);
}

//----- (00401130) --------------------------------------------------------
static int __fastcall ModemStop(void *userdata, int unused)
{
  int state; // [sp+10h] [-8h] BYREF
  PDEVICE_EXTENSION pUsb;

  (void)unused;
  pUsb = userdata;
  USBACF_Write16550Reg(pUsb, 4, 0);
  USBACF_Write16550Reg(pUsb, 2, 3);
  USBMODEM_ModifyLed(pUsb, 0, 2u);
  if ( pUsb->m_recv_alarm_active )
  {
    CancelAlarm(recv_alarm_callback, pUsb);
    pUsb->m_recv_alarm_active = 0;
    wrap_set_event_flag_main(pUsb, 2u);
  }
  if ( pUsb->m_modem_init_state == 5 )
  {
    sceModemUnregisterDevice(&pUsb->modem_ops);
    do_delete_threads(pUsb);
  }
  else
    wrap_set_event_flag_main(pUsb, 2u);
  CpuSuspendIntr(&state);
  pUsb->modem_ops.rcv_len = 0;
  pUsb->RxFifoGetIdx = 0;
  pUsb->RxFifoPutIdx = 0;
  pUsb->TxFIFOIdx = 0;
  pUsb->modem_ops.snd_len = sizeof(pUsb->TxFIFO);
  CpuResumeIntr(state);
  pUsb->f_started = 0;
  return 0;
}

//----- (00401224) --------------------------------------------------------
static void __fastcall USBACF_RxFlowControl(PDEVICE_EXTENSION pUsb)
{
  if ( pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx < 1024 && (pUsb->RegShadow[4] & 2) == 0 )
    USBACF_Write16550Reg(pUsb, 4, pUsb->RegShadow[4] | 2);
  else if ( pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx >= 3073 && (pUsb->RegShadow[4] & 2) != 0 )
    USBACF_Write16550Reg(pUsb, 4, pUsb->RegShadow[4] & 0xFD);
}

//----- (004012B4) --------------------------------------------------------
static int __fastcall ModemRead(void *userdata, void *buff, int size)
{
  int len; // $s3
  int state; // [sp+10h] [-8h] BYREF
  PDEVICE_EXTENSION pUsb;

  pUsb = userdata;
  if ( !pUsb->f_patch )
    return 0;
  CpuSuspendIntr(&state);
  for ( len = 0; len < size; len += 1 )
  {
    if ( !USBACF_RxBufferNotEmpty(pUsb) )
      break;
    ((char *)buff)[len] = USBACF_GetRxChar(pUsb);
  }
  pUsb->modem_ops.rcv_len = pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx;
  CpuResumeIntr(state);
  USBACF_RxFlowControl(pUsb);
  return len;
}

//----- (0040139C) --------------------------------------------------------
static int __fastcall PatchRead(PDEVICE_EXTENSION pUsb, char *buff, int size)
{
  int len; // $s3
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  for ( len = 0; len < size; len += 1 )
  {
    if ( !USBACF_RxBufferNotEmpty(pUsb) )
      break;
    buff[len] = USBACF_GetRxChar(pUsb);
  }
  pUsb->modem_ops.rcv_len = pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx;
  CpuResumeIntr(state);
  USBACF_RxFlowControl(pUsb);
  return len;
}

//----- (0040147C) --------------------------------------------------------
static void __fastcall set_interface_done(int result, int count, void *arg)
{
  PDEVICE_EXTENSION pUsb;

  (void)count;
  pUsb = arg;
  if ( result )
    printf("cxtmodem: %s -> 0x%x\n", "sceUsbdSetInterface", result);
  pUsb->Configured = 1;
  pUsb->Started = 1;
  SetUsbModemPollState(pUsb, 2);
}

//----- (004014D4) --------------------------------------------------------
static void __fastcall set_config_done(int result, int count, void *arg)
{
  int r; // $v0
  UsbDeviceRequest _dr; // [sp+18h] [-8h] BYREF
  PDEVICE_EXTENSION pUsb;

  (void)count;
  pUsb = arg;
  if ( result )
    printf("cxtmodem: %s -> 0x%x\n", "sceUsbdSetConfiguration", result);
  _dr.requesttype = 1;
  _dr.request = 11;
  _dr.value = 0;
  _dr.index = 0;
  _dr.length = 0;
  r = sceUsbdTransferPipe(pUsb->EP0Pipe, 0, 0, &_dr, set_interface_done, pUsb);
  if ( r )
    printf("cxtmodem: %s -> 0x%x\n", "sceUsbdSetInterface", r);
}

//----- (00401574) --------------------------------------------------------
static int __fastcall UsbAcfModemProbe(int dev_id)
{
  UsbDeviceDescriptor *data; // $a1

  data = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(dev_id, 0, 1u);
  if ( !data )
    return 1;
  if ( data->idVendor != 1394 )
    return 0;
  if ( data->idProduct != 4658 && data->idProduct != 4722 )
    return 0;
  resident_flag = 1;
  return sceUsbdScanStaticDescriptor(dev_id, data, 4u) && load_mode != 2;
}
// 403560: using guessed type int resident_flag;
// 403564: using guessed type int load_mode;

//----- (00401610) --------------------------------------------------------
static int __fastcall UsbAcfModemAttach(int dev_id)
{
  UsbConfigDescriptor *data; // $s4
  UsbInterfaceDescriptor *idesc; // $s0
  PDEVICE_EXTENSION pUsb; // $v0
  int xind; // $s1
  int xferres; // $v0
  const UsbDeviceDescriptor *devdesc; // $a1
  int manufind; // $s2
  int manufflg1; // $s1
  int manufflg2; // $v0
  int manufx1; // $v1
  int prodind; // $s2
  int prodflg1; // $s1
  int prodflg2; // $v0
  int prodx1; // $v1
  UCHAR man[64]; // [sp+18h] [-A0h] BYREF
  UCHAR pro[64]; // [sp+58h] [-60h] BYREF
  iop_thread_t thparam; // [sp+98h] [-20h] BYREF
  char epocfg[9]; // [sp+B0h] [-8h] BYREF
  int xflg;

  memset(man, 0, sizeof(man));
  strcpy((char *)man, "Conexant");
  memset(pro, 0, sizeof(pro));
  strcpy((char *)pro, "SMARTSCM");
  data = (UsbConfigDescriptor *)sceUsbdScanStaticDescriptor(dev_id, 0, 2u);
  if ( !data )
    return -1;
  if ( data->bNumInterfaces != 1 )
    return -1;
  idesc = (UsbInterfaceDescriptor *)sceUsbdScanStaticDescriptor(dev_id, data, 4u);
  if ( !idesc )
    return -1;
  if ( idesc->bNumEndpoints != 8 )
    return -1;
  pUsb = do_alloc_mem_for_dev_ext();
  if ( !pUsb )
    return -1;
  pUsb->Handle = dev_id;
  pUsb->EP0Pipe = sceUsbdOpenPipe(dev_id, 0);
  if ( pUsb->EP0Pipe < 0 )
    return -1;
  for ( xind = 0; xind < 8; xind += 1 )
  {
    idesc = (UsbInterfaceDescriptor *)sceUsbdScanStaticDescriptor(dev_id, idesc, 5u);
    if ( !idesc )
      return -1;
    pUsb->PipeList[xind].PipeHandle = sceUsbdOpenPipe(dev_id, (UsbEndpointDescriptor *)idesc);
    if ( pUsb->PipeList[xind].PipeHandle < 0 )
      return -1;
  }
  sceUsbdSetPrivateData(dev_id, pUsb);
  epocfg[0] = 0;
  epocfg[1] = 9;
  *(_WORD *)&epocfg[4] = 0;
  *(_WORD *)&epocfg[6] = 0;
  *(_WORD *)&epocfg[2] = data->bConfigurationValue;
  xferres = sceUsbdTransferPipe(pUsb->EP0Pipe, 0, 0, epocfg, set_config_done, pUsb);
  if ( xferres )
  {
    printf("cxtmodem: %s -> 0x%x\n", "sceUsbdSetConfiguration", xferres);
    return -1;
  }
  devdesc = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(pUsb->Handle, 0, 1u);
  if ( !devdesc )
    return -1;
  if ( devdesc->idVendor != 1394 )
    return -1;
  if ( devdesc->idProduct != 4658 && devdesc->idProduct != 4722 )
    return -1;
  xflg = 1;
  DelayThread(100);
  bcopy(man, pUsb->m_man, 32);
  bcopy(pro, pUsb->m_pro, 32);
  manufind = 0;
  epocfg[0] = 0x80;
  epocfg[1] = 6;
  *(_WORD *)&epocfg[4] = 0;
  strcpy(&epocfg[6], "=");
  *(_WORD *)&epocfg[2] = devdesc->iManufacturer | 0x300;
  sceUsbdTransferPipe(pUsb->EP0Pipe, man, 0x3Du, epocfg, 0, pUsb);
  DelayThread(100);
  for ( manufflg1 = 1; manufflg1 < 32; manufflg1 += 1 )
  {
    manufflg2 = manufflg1 + manufind;
    if ( manufflg2 > 32 )
      break;
    manufx1 = *(const UCHAR *)&man[2 * manufflg2];
    if ( (unsigned int)(manufx1 - 32) >= 0x5F )
    {
      if ( manufflg1 != 1 )
      {
        pUsb->m_man[manufflg1 - 1] = 0;
        break;
      }
      xflg = 0;
      break;
    }
    if ( (char)manufx1 == ',' || (char)manufx1 == '=' )
    {
      manufind += 1;
      manufflg1 -= 1;
    }
    else
    {
      pUsb->m_man[manufflg1 - 1] = manufx1;
    }
  }
  if ( xflg )
  {
    prodind = 0;
    pUsb->m_pro[0] = 0;
    epocfg[0] = 0x80;
    epocfg[1] = 6;
    *(_WORD *)&epocfg[2] = devdesc->iProduct | 0x300;
    *(_WORD *)&epocfg[4] = 0;
    strcpy(&epocfg[6], "=");
    sceUsbdTransferPipe(pUsb->EP0Pipe, pro, 0x3Du, epocfg, 0, pUsb);
    DelayThread(100);
    for ( prodflg1 = 1; prodflg1 < 32; prodflg1 += 1 )
    {
      prodflg2 = prodflg1 + prodind;
      if ( prodflg2 > 32 )
        break;
      prodx1 = *(const UCHAR *)&pro[2 * prodflg2];
      if ( (unsigned int)(prodx1 - 32) >= 0x5F )
      {
        if ( prodflg1 != 1 )
          pUsb->m_pro[prodflg1 - 1] = 0;
        break;
      }
      if ( (char)prodx1 == 44 || (char)prodx1 == 61 )
      {
        prodind += 1;
        prodflg1 -= 1;
      }
      else
      {
        pUsb->m_pro[prodflg1 - 1] = prodx1;
      }
    }
  }
  pUsb->modem_ops.module_name = "cxtmdm";
  pUsb->modem_ops.vendor_name = (char *)pUsb->m_man;
  pUsb->modem_ops.device_name = (char *)pUsb->m_pro;
  pUsb->modem_ops.bus_type = sceModemBus_USB;
  if ( sceUsbdGetDeviceLocation(dev_id, pUsb->modem_ops.bus_loc) != 0 )
    return -1;
  pUsb->modem_ops.start = ModemStart;
  pUsb->modem_ops.stop = ModemStop;
  pUsb->modem_ops.recv = ModemRead;
  pUsb->modem_ops.send = ModemWrite;
  pUsb->modem_ops.prot_ver = sceModemProtVer;
  pUsb->modem_ops.impl_ver = 0;
  pUsb->modem_ops.priv = pUsb;
  pUsb->modem_ops.control = ModemControl;
  if ( sceModemRegisterDevice(&pUsb->modem_ops) < 0 )
    return -1;
  DelayThread(100);
  pUsb->f_patch = 0;
  pUsb->f_started = 0;
  thparam.attr = 0x2000000;
  thparam.thread = cxtmdm_patchload_thread;
  thparam.option = 0;
  thparam.priority = thread_priority;
  thparam.stacksize = stack_size;
  pUsb->m_thid_patchload = CreateThread(&thparam);
  if ( pUsb->m_thid_patchload <= 0 || StartThread(pUsb->m_thid_patchload, pUsb) )
    DeleteThread(pUsb->m_thid_patchload);
  return 0;
}
// 4034E8: using guessed type int thread_priority;
// 4034EC: using guessed type int stack_size;

//----- (00401B34) --------------------------------------------------------
static int __fastcall UsbAcfModemDetach(int dev_id)
{
  PDEVICE_EXTENSION pUsb; // $s0

  pUsb = (PDEVICE_EXTENSION)sceUsbdGetPrivateData(dev_id);
  if ( !pUsb )
    return -1;
  switch ( pUsb->m_modem_init_state )
  {
  case 1:
  case 2:
  case 3:
  case 4:
    pUsb->m_modem_init_state = 5;
    wrap_set_event_flag_modem(pUsb, sceModemEFP_PlugOut);
    break;
  default:
  case 5:
    wrap_set_event_flag_modem(pUsb, sceModemEFP_PlugOut);
    sceModemUnregisterDevice(&pUsb->modem_ops);
    do_delete_threads(pUsb);
    break;
  }
  pUsb->f_patch = 0;
  pUsb->f_started = 0;
  return 0;
}

//----- (00401BE4) --------------------------------------------------------
int __fastcall _start(int argc, char **argv)
{
  int ac_cur; // $s2
  int eqcount; // $s0

  load_mode = 0;
  g_dialconf[0] = 0;
  for ( ac_cur = 0; ac_cur < argc; ac_cur += 1 )
  {
    if ( !strncmp("dial=", argv[ac_cur], 5) )
      strcpy(g_dialconf, argv[ac_cur] + 5);
    for ( eqcount = 0; argv[ac_cur][eqcount]; eqcount += 1 )
    {
      if ( argv[ac_cur][eqcount] == '=' )
      {
        argv[ac_cur][eqcount] = 0;
        eqcount += 1;
        break;
      }
    }
    if ( !strcmp(argv[ac_cur], "lmode") )
    {
      if ( !strcmp(&(argv[ac_cur])[eqcount], "AUTOLOAD") )
      {
        load_mode = 1;
        break;
      }
      if ( !strcmp(&(argv[ac_cur])[eqcount], "TESTLOAD") )
      {
        load_mode = 2;
        break;
      }
    }
  }
  switch ( load_mode )
  {
  case 0:
    resident_flag = 1;
    break;
  case 1:
  case 2:
    resident_flag = 0;
    break;
  default:
    break;
  }
  sceUsbdRegisterLdd(&UsbAcfDriverDescriptor);
  if ( load_mode == 2 )
  {
    sceUsbdUnregisterLdd(&UsbAcfDriverDescriptor);
    return ( resident_flag != 1 ) ? 1 : 5;
  }
  if ( !resident_flag )
  {
    sceUsbdUnregisterLdd(&UsbAcfDriverDescriptor);
    return 1;
  }
  return 0;
}
// 4034A4: using guessed type sceUsbdLddOps UsbAcfDriverDescriptor;
// 403560: using guessed type int resident_flag;
// 403564: using guessed type int load_mode;

//----- (00401DD8) --------------------------------------------------------
static void __fastcall USBACF_Write16550Reg(PDEVICE_EXTENSION pUsb, int reg, char data)
{
  if ( (unsigned int)reg < 8 )
  {
    pUsb->RegShadow[reg] = data;
    pUsb->RegChanged[reg] = -1;
    pUsb->RegChangeFlag = 1;
    MakeRegisterTransmitRequest(pUsb);
  }
}

//----- (00401E14) --------------------------------------------------------
static void __fastcall MakeDataTransferRequest(PDEVICE_EXTENSION pUsb, BOOLEAN CallTxHandler)
{
  int reent1; // $s3
  int NumOfBytes; // $a1
  int i; // $a0
  int j; // $a1
  int Length; // $s1

  (void)CallTxHandler;
  reent1 = 0;
  pUsb->MakeDataTransmitReentrancy += 1;
  if ( !pUsb->MakeDataTransmitReentrancy )
  {
    for ( ; pUsb->MakeDataTransmitReentrancy >= 0; pUsb->MakeDataTransmitReentrancy -= 1 )
    {
      if ( pUsb->PipeList[4].nActiveRequests > 0 )
        reent1 = 1;
      else if ( !pUsb->PipeList[4].NeedReset && pUsb->Started )
      {
        NumOfBytes = pUsb->TxFIFOIdx;
        if ( NumOfBytes >= 15 )
          NumOfBytes = 14;
        for ( i = 0; i < NumOfBytes; i += 1 )
          pUsb->TxSendBuf[i] = pUsb->TxFIFO[i];
        Length = i;
        for ( j = 0; (i + j) < pUsb->TxFIFOIdx; j += 1 )
          pUsb->TxFIFO[j] = pUsb->TxFIFO[i + j];
        pUsb->TxFIFOIdx = j;
        if ( !j )
          SignalSema(pUsb->sm_xmit);
        if ( Length > 0 || !pUsb->TxFIFOIdx )
        {
          if ( Length > 0 )
            CallUsbd(
              pUsb,
              &pUsb->PipeList[4],
              pUsb->TxSendBuf,
              Length,
              UsbTransmitDataCompletionRoutine);
        }
        else
        {
          continue;
        }
      }
      if ( reent1 == 1 )
        reent1 = 0;
    }
  }
}

//----- (00401F90) --------------------------------------------------------
static int __fastcall USBACF_GetRxChar(PDEVICE_EXTENSION pUsb)
{
  int nBytesAvail; // $a1

  nBytesAvail = pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx;
  if ( nBytesAvail > 0 )
  {
    signed __int8 c; // $a2
    c = pUsb->RxFIFO[pUsb->RxFifoGetIdx];
    pUsb->RxFifoGetIdx += 1;
    if ( nBytesAvail == 1 )
    {
      pUsb->RxFifoGetIdx = 0;
      pUsb->RxFifoPutIdx = 0;
    }
    return c;
  }
  else
  {
    pUsb->RxFifoGetIdx = 0;
    pUsb->RxFifoPutIdx = 0;
  }
  return 0;
}

//----- (00401FE8) --------------------------------------------------------
static BOOLEAN __fastcall USBACF_TxBufferFull(PDEVICE_EXTENSION pUsb)
{
  return (unsigned int)(pUsb->TxFIFOIdx) >= sizeof(pUsb->TxFIFO);
}

//----- (00401FFC) --------------------------------------------------------
static void __fastcall USBACF_PutTxChar(PDEVICE_EXTENSION pUsb, char data)
{
  if ( (unsigned int)(pUsb->TxFIFOIdx) < sizeof(pUsb->TxFIFO) )
  {
    pUsb->TxFIFO[pUsb->TxFIFOIdx] = data;
    pUsb->TxFIFOIdx += 1;
  }
}

//----- (00402038) --------------------------------------------------------
static void __fastcall UsbTransmitRegisterCompletionRoutine(int result, int count, void *context)
{
  PDEVICE_EXTENSION pUsb;

  pUsb = context;
  pUsb->PipeList[0].nActiveRequests -= 1;
  if ( pUsb->Started )
  {
    OnTransmitCompleted(pUsb, count);
    if ( !result )
      MakeRegisterTransmitRequest(pUsb);
  }
}

//----- (00402090) --------------------------------------------------------
static void __fastcall UsbTransmitDataCompletionRoutine(int result, int count, void *context)
{
  int state; // [sp+10h] [-8h] BYREF
  PDEVICE_EXTENSION pUsb;

  pUsb = context;
  pUsb->PipeList[4].nActiveRequests -= 1;
  if ( pUsb->Started && !result )
  {
    MakeDataTransferRequest(pUsb, 1u);
    CpuSuspendIntr(&state);
    pUsb->m_tx_count += count;
    CpuResumeIntr(state);
    if ( pUsb->TxFIFOIdx < 256 )
    {
      pUsb->modem_ops.snd_len = sizeof(pUsb->TxFIFO) - pUsb->TxFIFOIdx;
      wrap_set_event_flag_modem(pUsb, sceModemEFP_Send);
    }
  }
}

//----- (00402124) --------------------------------------------------------
static void __fastcall UsbReceiveRegisterCompletionRoutine(int result, int count, void *context)
{
  int count_1; // $s1
  int state; // [sp+10h] [-8h] BYREF
  PDEVICE_EXTENSION pUsb;

  pUsb = context;
  count_1 = count;
  pUsb->PipeList[5].nActiveRequests -= 1;
  if ( pUsb->Started && (pUsb->bPowerState & 2) != 0 )
  {
    if ( result )
      pUsb->bPowerState &= 0xFFFFFFFD;
    else
    {
      unsigned int count_rev; // $v0

      if ( (unsigned int)count_1 >= 0x20 )
        count_1 = 31;
      count_rev = count_1 - 1;
      if ( count_rev >> 1 < 0x11 )
        OnNewStatusReceived(pUsb, &pUsb->RecvRegs, count_rev >> 1);
      MakeReceiveRequest(pUsb);
      CpuSuspendIntr(&state);
      pUsb->m_rx_count += count_1;
      CpuResumeIntr(state);
    }
  }
}

//----- (004021E8) --------------------------------------------------------
static void __fastcall OnNewStatusReceived(PDEVICE_EXTENSION pUsb, struct USBACF_Recv *pUsbRecv, int nFifoCharsReceived)
{
  UCHAR Reg06; // $s3
  int i; // $a3
  int RxFifoGetIdx; // $a0
  int j; // $a2
  int state; // [sp+10h] [-8h] BYREF

  Reg06 = pUsbRecv->Reg06;
  CpuSuspendIntr(&state);
  for ( i = 0; i < nFifoCharsReceived; i += 1 )
  {
    if ( (pUsbRecv->RxData[i].Reg05 & 1) == 0 )
      break;
    if ( (unsigned int)(pUsb->RxFifoPutIdx) < 0xFFFu )
    {
      pUsb->RxFIFO[pUsb->RxFifoPutIdx] = pUsbRecv->RxData[i].Reg00;
      pUsb->RxFifoPutIdx += 1;
    }
    else if ( pUsb->RxFifoGetIdx )
    {
      RxFifoGetIdx = pUsb->RxFifoGetIdx;
      for ( j = 0; (j + RxFifoGetIdx) < pUsb->RxFifoPutIdx; j += 1 )
        pUsb->RxFIFO[j] = pUsb->RxFIFO[j + RxFifoGetIdx];
      pUsb->RxFifoPutIdx = j;
      pUsb->RxFifoGetIdx = 0;
      pUsb->RxFIFO[pUsb->RxFifoPutIdx] = pUsbRecv->RxData[i].Reg00;
      pUsb->RxFifoPutIdx += 1;
    }
  }
  if ( i > 0 )
  {
    pUsb->m_rx_count += pUsb->RxFifoPutIdx;
    if ( pUsb->m_recv_alarm_active )
    {
      CancelAlarm(recv_alarm_callback, pUsb);
      pUsb->m_recv_alarm_active = 0;
    }
    if ( pUsb->RxFifoPutIdx < 1025 )
    {
      SetAlarm(&pUsb->sys_clock, recv_alarm_callback, pUsb);
      pUsb->m_recv_alarm_active = 1;
    }
    else
    {
      pUsb->modem_ops.rcv_len = pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx;
      wrap_set_event_flag_modem(pUsb, sceModemEFP_Recv);
      pUsb->m_recv_ev_count += 1;
    }
  }
  CpuResumeIntr(state);
  USBACF_RxFlowControl(pUsb);
  pUsb->RShellNtMSRshadow = Reg06;
}

//----- (0040239C) --------------------------------------------------------
static BOOLEAN __fastcall USBACF_RxBufferNotEmpty(PDEVICE_EXTENSION pUsb)
{
  return pUsb->RxFifoGetIdx != pUsb->RxFifoPutIdx;
}

//----- (004023B4) --------------------------------------------------------
static int __fastcall CallUsbd(
        PDEVICE_EXTENSION pUsb,
        struct PIPE_DATA *Pipe,
        void *Buf,
        int Length,
        sceUsbdDoneCallback CompletionRoutine)
{
  if ( !pUsb->Started )
    return 306;
  Pipe->nActiveRequests += 1;
  return sceUsbdTransferPipe(Pipe->PipeHandle, Buf, Length, 0, CompletionRoutine, pUsb);
}

//----- (0040241C) --------------------------------------------------------
static void __fastcall MakeReceiveRequest(PDEVICE_EXTENSION pUsb)
{
  if ( pUsb->PipeList[5].nActiveRequests <= 0 && !pUsb->PipeList[5].NeedReset && pUsb->Started )
    CallUsbd(pUsb, &pUsb->PipeList[5], &pUsb->RecvRegs, 31, UsbReceiveRegisterCompletionRoutine);
}

//----- (0040247C) --------------------------------------------------------
static void __fastcall MakeRegisterTransmitRequest(PDEVICE_EXTENSION pUsb)
{
  if ( pUsb->PipeList[0].nActiveRequests <= 0 )
  {
    while ( pUsb->RegChangeFlag || pUsb->TmpTxRegIndex )
    {
      unsigned int i; // $a0
      unsigned int TmpTxRegIndex; // $a2
      int size; // $s1

      if ( !pUsb->Started )
        break;
      if ( pUsb->PipeList[0].NeedReset )
        break;
      TmpTxRegIndex = pUsb->TmpTxRegIndex;
      for ( i = 0; i < 8; i += 1 )
      {
        if ( pUsb->RegChanged[i] )
        {
          if ( TmpTxRegIndex >= 0x10 )
            break;
          pUsb->TmpTxRegs[TmpTxRegIndex].addrH = pUsb->bHighAddr;
          pUsb->TmpTxRegs[TmpTxRegIndex].addrL = i;
          pUsb->TmpTxRegs[TmpTxRegIndex].data = pUsb->RegShadow[i];
          TmpTxRegIndex += 1;
          pUsb->RegChanged[i] = 0;
        }
      }
      if ( i == 8 )
        pUsb->RegChangeFlag = 0;
      size = 3 * TmpTxRegIndex;
      pUsb->TmpTxRegIndex = TmpTxRegIndex;
      if ( size )
      {
        memcpy(pUsb->TxRegs, pUsb->TmpTxRegs, size);
        pUsb->TmpTxRegIndex = 0;
        CallUsbd(pUsb, pUsb->PipeList, pUsb->TxRegs, size, UsbTransmitRegisterCompletionRoutine);
      }
    }
  }
}

//----- (004025B8) --------------------------------------------------------
static void __fastcall OnTransmitCompleted(PDEVICE_EXTENSION pUsb, int PacketLength)
{
  (void)pUsb;
  (void)PacketLength;
}

//----- (004025C0) --------------------------------------------------------
static void __fastcall UsbTransmitGpioCompletionRoutine(int result, int count, void *context)
{
  PDEVICE_EXTENSION pUsb;

  (void)count;
  pUsb = context;
  pUsb->PipeList[6].nActiveRequests -= 1;
  if ( pUsb->Started && !result )
    SendGpioLedRequest(pUsb);
}

//----- (00402604) --------------------------------------------------------
static void __fastcall SendGpioLedRequest(PDEVICE_EXTENSION pUsb)
{
  if ( !pUsb->PipeList[6].nActiveRequests && pUsb->bGpioChanged && pUsb->Started )
  {
    pUsb->bGpioChanged = 0;
    CallUsbd(pUsb, &pUsb->PipeList[6], &pUsb->u, 4, UsbTransmitGpioCompletionRoutine);
  }
}

//----- (00402668) --------------------------------------------------------
static void __fastcall USBMODEM_ModifyMode(PDEVICE_EXTENSION pUsb, BYTE SetMode, BYTE ResetMode)
{
  pUsb->bGpioChanged = 1;
  pUsb->u.GpioBuf[2] = (pUsb->u.GpioBuf[2] & ~ResetMode) | SetMode;
  SendGpioLedRequest(pUsb);
}

//----- (004026A0) --------------------------------------------------------
static void __fastcall USBMODEM_ModifyLed(PDEVICE_EXTENSION pUsb, BYTE SetMode, BYTE ResetMode)
{
  pUsb->bGpioChanged = 1;
  pUsb->u.GpioBuf[3] = (pUsb->u.GpioBuf[3] & ~ResetMode) | SetMode;
  SendGpioLedRequest(pUsb);
}

//----- (004026D8) --------------------------------------------------------
static void __fastcall SetUsbModemPollState(PDEVICE_EXTENSION pUsb, int state)
{
  switch ( state )
  {
  case 1:
    {
      pUsb->bPowerState &= ~2u;
      USBMODEM_ModifyLed(pUsb, 0, 1u);
      USBMODEM_ModifyLed(pUsb, 0, 2u);
      USBMODEM_ModifyLed(pUsb, 0, 4u);
      break;
    }
  case 2:
    {
      pUsb->bPowerState |= 2u;
      USBMODEM_ModifyMode(pUsb, 0xC9u, 0);
      USBMODEM_ModifyLed(pUsb, 1u, 0);
      DelayThread(10000);
      USBMODEM_ModifyMode(pUsb, 0, 8u);
      DelayThread(10000);
      pUsb->LedB1_Flag = 0;
      USBACF_Write16550Reg(pUsb, 3, -128);
      USBACF_Write16550Reg(pUsb, 0, 1);
      USBACF_Write16550Reg(pUsb, 1, 0);
      USBACF_Write16550Reg(pUsb, 3, 3);
      USBACF_Write16550Reg(pUsb, 2, -31);
      USBACF_Write16550Reg(pUsb, 4, 3);
      pUsb->PipeList[5].nActiveRequests = 0;
      MakeReceiveRequest(pUsb);
      break;
    }
  default:
    break;
  }
}
