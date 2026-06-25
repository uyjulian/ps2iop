
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
  int m_unkaa;
  int m_unkab;
  int m_ef_bits;
  int m_evid_main;
  int m_thid1;
  int m_thid2;
  int m_thid_patchload;
  int m_unkba;
  int m_unkbb;
  int f_patch;
  int m_unkbd;
  int m_unkbe;
  int f_started;
  UCHAR m_man[31];
  UCHAR m_pro[31];
  int m_unkca;
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

int __fastcall wrap_set_event_flag_modem(PDEVICE_EXTENSION dev_ext, u32 flagval);
int __fastcall wrap_set_event_flag_main(PDEVICE_EXTENSION dev_ext, u32 flagval);
int __fastcall ModemWrite(PDEVICE_EXTENSION dev_ext, char *data, int len);
int __fastcall PatchWrite(PDEVICE_EXTENSION dev_ext, char *data, int len);
size_t __fastcall ModemControl(PDEVICE_EXTENSION userdata, int cmd, void *buf, int bufsz);
int __fastcall ModemGetStatus(PDEVICE_EXTENSION dev_ext);
int __fastcall ModemStart(PDEVICE_EXTENSION dev_ext);
unsigned int __fastcall alarm_cb(PDEVICE_EXTENSION dev_ext);
int __fastcall get_ef_bits(PDEVICE_EXTENSION dev_ext);
u32 __fastcall wait_for_ef_bits(PDEVICE_EXTENSION dev_ext, u32 bits);
void __fastcall __noreturn th_2_proc_modem_status(PDEVICE_EXTENSION dev_ext);
int __fastcall th_1_proc_ef_bits(PDEVICE_EXTENSION dev_Ext);
int __fastcall cxtmdm_patchload_thread(PDEVICE_EXTENSION dev_ext);
PDEVICE_EXTENSION do_alloc_mem_for_dev_ext();
void __fastcall do_delete_threads(PDEVICE_EXTENSION edv_ext);
int __fastcall ModemStop(PDEVICE_EXTENSION dev_ext);
void __fastcall USBACF_RxFlowControl(PDEVICE_EXTENSION pUsb);
int __fastcall ModemRead(PDEVICE_EXTENSION dev_ext, char *buff, int size);
int __fastcall PatchRead(PDEVICE_EXTENSION dev_ext, char *buff, int size);
void __fastcall set_interface_done(int result, int count, PDEVICE_EXTENSION arg);
void __fastcall set_config_done(int result, int count, PDEVICE_EXTENSION arg);
int __fastcall UsbAcfModemProbe(int dev_id);
int __fastcall UsbAcfModemAttach(int dev_id);
int __fastcall UsbAcfModemDetach(int dev_id);
int __fastcall start(int argc, char **argv);
void __fastcall USBACF_Write16550Reg(PDEVICE_EXTENSION pUsb, int reg, char data);
void __fastcall MakeDataTransferRequest(PDEVICE_EXTENSION pUsb, BOOLEAN CallTxHandler);
int __fastcall USBACF_GetRxChar(PDEVICE_EXTENSION pUsb);
BOOLEAN __fastcall USBACF_TxBufferFull(PDEVICE_EXTENSION pUsb);
void __fastcall USBACF_PutTxChar(PDEVICE_EXTENSION pUsb, char data);
void __fastcall UsbTransmitRegisterCompletionRoutine(int result, int count, PDEVICE_EXTENSION context);
void __fastcall UsbTransmitDataCompletionRoutine(int result, int count, PDEVICE_EXTENSION context);
void __fastcall UsbReceiveRegisterCompletionRoutine(int result, int count, PDEVICE_EXTENSION context);
void __fastcall OnNewStatusReceived(PDEVICE_EXTENSION pUsb, struct USBACF_Recv *pUsbRecv, int nFifoCharsReceived);
BOOLEAN __fastcall USBACF_RxBufferNotEmpty(PDEVICE_EXTENSION pUsb);
int __fastcall CallUsbd(PDEVICE_EXTENSION pUsb, struct PIPE_DATA *Pipe, void *Buf, int Length, sceUsbdDoneCallback CompletionRoutine);
void __fastcall MakeReceiveRequest(PDEVICE_EXTENSION pUsb);
void __fastcall MakeRegisterTransmitRequest(PDEVICE_EXTENSION pUsb);
void __fastcall OnTransmitCompleted(PDEVICE_EXTENSION pUsb, int PacketLength);
void __fastcall UsbTransmitGpioCompletionRoutine(int result, int count, PDEVICE_EXTENSION context);
void __fastcall SendGpioLedRequest(PDEVICE_EXTENSION pUsb);
void __fastcall USBMODEM_ModifyMode(PDEVICE_EXTENSION pUsb, BYTE SetMode, BYTE ResetMode);
void __fastcall USBMODEM_ModifyLed(PDEVICE_EXTENSION pUsb, BYTE SetMode, BYTE ResetMode);
void __fastcall SetUsbModemPollState(PDEVICE_EXTENSION pUsb, int state);

//-------------------------------------------------------------------------
// Data declarations

char usbacf_patch[2275] = "S3100000A000B20269A9008DBC044C0EE101\r\nS31500009DA560606B606060606B6B6060606060606087\r\nS31500009DB56B60606B60606060606060606060606082\r\nS31500009DC56060606060606060606060606060606088\r\nS31500009DD5606060606060606B6B6060606060606062\r\nS31500009DE560606B606060606060606060606B606052\r\nS30700009DF5000066\r\nS31500009EB00000E500000000D02000000000000000C7\r\nS31500009EC0DD000003000000000000000000000000AC\r\nS31500009ED0000000000000000000000000000000007C\r\nS31500009EE00000000000000018DA000000000000007A\r\nS31500009EF00000E200000000000000000000A60000D4\r\nS30600009F00005A\r\nS31500009F010917FF4C11AD6487D00CA21820445A29B9\r\nS31500009F111F09804CF558604C83863D534C562BA93E\r\nS31500009F216B8DA79DA0FFA204C8B97B04C90DF03EA5\r\nS31500009F31DD1B9FD0F1CA10F0C8B97B04C934D00427\r\nS31500009F41A9388027C935D004A939801FC936D0D68A\r\nS31500009F51206A9FA200E8C8B97B04C90DD0F7B97B76\r\nS31500009F6104997C0488CAD0F6C8A931997B04A0FF5C\r\nS31500009F71A203C8B97B04C90DF026DDA29FD0F1CAA0\r\nS31500009F8110F0C8B97B04997704C90DD0F5ADCE049C\r\nS31500009F912901F009B28C40B200414CA3254CA02501\r\nS31500009FA1605652542DE25D0110244F6321AD3F8767\r\nS31500009FB1C9B1F015AD4D87C900F0132073E720D75D\r\nS31500009FC19FE2600110084CAE77A9008D4D8760A213\r\nS31500009FD103A9004C9BE44C019E4CF99DD20839061D\r\nS31500009FE1604C7886A900CDA102D00AA973CD0D01D6\r\nS31000009FF1B0038D0D01A9608DA79D60D7\r\nS31500009DF97F4C04D210600160AD43878540AD44872E\r\nS31500009E09854138A540E98C8540A541E9008541A5EC\r\nS31500009E1940ED52878540A541ED53878541A54148C7\r\nS31500009E29A5408542AD47878540AD48878541208B4A\r\nS31500009E3969B26444B20045B20043205022A5408D60\r\nS31500009E494D87A5418D4E87688542AD47878540ADCB\r\nS31500009E5948878541208B69B26444B20045B2004304\r\nS31500009E69205022A54148A54048B2FF42208B696887\r\nS31500009E798544688545A54065448540A54165458570\r\nS31500009E8941A54269008542A5406D4D878540A5419A\r\nS31400009E996D4E878541A54269008D4F874CA9867E\r\nS31500008678A950CD0286B0038D028660AD5702C93C6B\r\nS31500008688D01EB20747B25046B20A45B2B944209640\r\nS31500008698E3B20747B25046B20B45B2B9442096E357\r\nS315000086A860A5408D4D87A5418D4E87B2D040B20753\r\nS315000086B841B25A42208B69A542CD4F87F004B038A3\r\nS315000086C8800EA541CD4E87D005A540CD4D87B02853\r\nS315000086D8AD4B878540AD4C878541A541C900D0047F\r\nS315000086E8A540C996B012A9758D3F87A9778D408791\r\nS30E000086F8B200AEB248B1B75960F8\r\nS70500000000FA\r\n"; // weak
sceUsbdLddOps UsbAcfDriverDescriptor =
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
int thread_priority = 28; // weak
int stack_size = 4096; // weak
const char aX[] = "X";
int resident_flag; // weak
int load_mode; // weak
char g_dialconf; // idb


//----- (00400000) --------------------------------------------------------
int __fastcall wrap_set_event_flag_modem(PDEVICE_EXTENSION dev_ext, u32 flagval)
{
  const char *curstr1; // $a2
  char *curres1; // $s0
  const char *curstr2; // $a2
  char *curres2; // $s0
  const char *curstr3; // $a2
  char *curres3; // $s0
  const char *curstr4; // $a2
  char *curres4; // $s0
  const char *curstr5; // $a2
  char *curres5; // $s0
  const char *curstr6; // $a2
  int curres6; // $v0
  char outbuf[104]; // [sp+10h] [-68h] BYREF

  if ( (flagval & 0x200) == 0 )
  {
    curstr1 = "";
    outbuf[0] = 0;
    if ( (flagval & 1) != 0 )
      curstr1 = " StartDone";
    curres1 = &outbuf[sprintf(outbuf, "%s", curstr1)];
    curstr2 = "";
    if ( (flagval & 2) != 0 )
      curstr2 = " PlugOut";
    curres2 = &curres1[sprintf(curres1, "%s", curstr2)];
    curstr3 = "";
    if ( (flagval & 0x10) != 0 )
      curstr3 = " Connect";
    curres3 = &curres2[sprintf(curres2, "%s", curstr3)];
    curstr4 = "";
    if ( (flagval & 0x20) != 0 )
      curstr4 = " Disconnect";
    curres4 = &curres3[sprintf(curres3, "%s", curstr4)];
    curstr5 = "";
    if ( (flagval & 0x40) != 0 )
      curstr5 = " Ring";
    curres5 = &curres4[sprintf(curres4, "%s", curstr5)];
    curstr6 = "";
    if ( (flagval & 0x100) != 0 )
      curstr6 = " Recv";
    curres6 = sprintf(curres5, "%s", curstr6);
    sprintf(&curres5[curres6], "%s", "");
  }
  return SetEventFlag(dev_ext->modem_ops.evfid, flagval);
}
// 400000: using guessed type char outbuf[104];

//----- (00400138) --------------------------------------------------------
int __fastcall wrap_set_event_flag_main(PDEVICE_EXTENSION dev_ext, u32 flagval)
{
  const char *curstr1; // $a2
  char *curres1; // $s0
  const char *curstr2; // $a2
  char *curres2; // $s0
  const char *curstr3; // $a2
  int curres3; // $v0
  const char *curstr4; // $a2
  char curbuf[104]; // [sp+10h] [-68h] BYREF

  curstr1 = "";
  curbuf[0] = 0;
  if ( (flagval & 1) != 0 )
    curstr1 = " START";
  curres1 = &curbuf[sprintf(curbuf, "%s", curstr1)];
  curstr2 = "";
  if ( (flagval & 2) != 0 )
    curstr2 = " STOP";
  curres2 = &curres1[sprintf(curres1, "%s", curstr2)];
  curstr3 = "";
  if ( (flagval & 8) != 0 )
    curstr3 = " STATE";
  curres3 = sprintf(curres2, "%s", curstr3);
  curstr4 = "";
  if ( (flagval & 0x400) != 0 )
    curstr4 = " BREAK";
  sprintf(&curres2[curres3], "%s", curstr4);
  return SetEventFlag(dev_ext->m_evid_main, flagval);
}
// 400138: using guessed type char curbuf[104];

//----- (00400208) --------------------------------------------------------
int __fastcall ModemWrite(PDEVICE_EXTENSION dev_ext, char *data, int len)
{
  int cnt; // $s3
  int xsend_len; // $v0
  PDEVICE_EXTENSION dev_ext_1; // $a0
  int state; // [sp+10h] [-8h] BYREF

  cnt = 0;
  if ( !dev_ext->f_started || !dev_ext->f_patch )
    return 0;
  CpuSuspendIntr(&state);
  xsend_len = dev_ext->modem_ops.snd_len - len;
  if ( xsend_len < 0 )
    xsend_len = 1024;
  dev_ext->modem_ops.snd_len = xsend_len;
  CpuResumeIntr(state);
  dev_ext_1 = dev_ext;
  if ( len > 0 )
  {
    do
    {
      if ( USBACF_TxBufferFull(dev_ext) )
      {
        MakeDataTransferRequest(dev_ext, 0);
        DelayThread(10000);
      }
      if ( USBACF_TxBufferFull(dev_ext) )
        break;
      bcopy(data, (void *)"X", 1);
      ++cnt;
      USBACF_PutTxChar(dev_ext, aX[0]);
      --len;
      ++data;
    }
    while ( len > 0 );
    dev_ext_1 = dev_ext;
  }
  MakeDataTransferRequest(dev_ext_1, 0);
  return cnt;
}

//----- (00400338) --------------------------------------------------------
int __fastcall PatchWrite(PDEVICE_EXTENSION dev_ext, char *data, int len)
{
  int cnt; // $s3
  int xsend_len; // $v0
  PDEVICE_EXTENSION dev_ext_1; // $a0
  int state; // [sp+10h] [-8h] BYREF

  cnt = 0;
  CpuSuspendIntr(&state);
  xsend_len = dev_ext->modem_ops.snd_len - len;
  if ( xsend_len < 0 )
    xsend_len = 1024;
  dev_ext->modem_ops.snd_len = xsend_len;
  CpuResumeIntr(state);
  dev_ext_1 = dev_ext;
  if ( len > 0 )
  {
    do
    {
      while ( USBACF_TxBufferFull(dev_ext) )
      {
        MakeDataTransferRequest(dev_ext, 0);
        WaitSema(dev_ext->sm_xmit);
      }
      bcopy(data, (void *)"X", 1);
      ++cnt;
      USBACF_PutTxChar(dev_ext, aX[0]);
      --len;
      ++data;
    }
    while ( len > 0 );
    dev_ext_1 = dev_ext;
  }
  MakeDataTransferRequest(dev_ext_1, 0);
  return cnt;
}

//----- (00400444) --------------------------------------------------------
size_t __fastcall ModemControl(PDEVICE_EXTENSION userdata, int cmd, void *buf, int bufsz)
{
  size_t retres; // $s1
  int *p_m_unkaa; // $a0
  int state_1; // $a0
  int state_2; // $a0
  int m_thid1; // $a0
  int m_thid2; // $a0
  int zerotmp; // [sp+10h] [-10h] BYREF
  int state; // [sp+14h] [-Ch] BYREF
  int priority; // [sp+18h] [-8h] BYREF

  retres = 0;
  if ( (unsigned int)(cmd + 0x3FFFFEF0) >= 2 && cmd != 0xC0000200 && bufsz != 4 )
    return -512;
  if ( cmd == 0xC0000111 )
  {
    CpuSuspendIntr(&state);
    state_2 = state;
    userdata->TxFIFOIdx = 0;
    userdata->modem_ops.snd_len = 1024;
    CpuResumeIntr(state_2);
    return retres;
  }
  if ( cmd > (int)0xC0000111 )
  {
    if ( cmd == 0xC0010000 )
    {
      p_m_unkaa = &userdata->m_unkaa;
      goto LABEL_28;
    }
    if ( cmd > (int)0xC0010000 )
    {
      if ( cmd == 0xC0010001 )
      {
        p_m_unkaa = &userdata->m_unkab;
        goto LABEL_28;
      }
      if ( cmd != 0xC1000000 )
        return -513;
      bcopy(buf, &priority, 4);
      m_thid1 = userdata->m_thid1;
      if ( m_thid1 > 0 )
      {
        retres = ChangeThreadPriority(m_thid1, priority);
        if ( !retres )
          thread_priority = priority;
      }
      m_thid2 = userdata->m_thid2;
      if ( m_thid2 > 0 )
      {
        retres = ChangeThreadPriority(m_thid2, priority);
        if ( !retres )
          thread_priority = priority;
      }
      if ( (userdata->m_thid1 <= 0 || retres == -413) && (unsigned int)(priority - 9) < 0x73 )
        thread_priority = priority;
      return retres;
    }
    retres = -513;
    if ( cmd != 0xC0000200 )
      return retres;
    retres = strlen(&g_dialconf) + 1;
    if ( bufsz >= retres )
    {
      bcopy(&g_dialconf, buf, retres);
      return retres;
    }
    return -512;
  }
  if ( cmd == 0xC0000100 )
  {
    zerotmp = 0;
    p_m_unkaa = &zerotmp;
    goto LABEL_28;
  }
  if ( cmd <= (int)0xC0000100 )
  {
    if ( cmd != 0xC0000000 )
      return -513;
    p_m_unkaa = &thread_priority;
LABEL_28:
    bcopy(p_m_unkaa, buf, 4);
    return retres;
  }
  if ( cmd != 0xC0000110 )
    return -513;
  CpuSuspendIntr(&state);
  state_1 = state;
  userdata->modem_ops.rcv_len = 0;
  userdata->RxFifoGetIdx = 0;
  userdata->RxFifoPutIdx = 0;
  CpuResumeIntr(state_1);
  return retres;
}
// 4034E8: using guessed type int thread_priority;

//----- (004006C8) --------------------------------------------------------
int __fastcall ModemGetStatus(PDEVICE_EXTENSION dev_ext)
{
  return dev_ext->RShellNtMSRshadow;
}

//----- (004006D4) --------------------------------------------------------
int __fastcall ModemStart(PDEVICE_EXTENSION dev_ext)
{
  int i; // $s1
  UsbDeviceDescriptor *data; // $a1
  int result; // $v0
  int idProduct; // $v1

  i = 0;
  data = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(dev_ext->Handle, 0, 1u);
  if ( !data )
    return 0;
  result = 0;
  if ( data->idVendor == 1394 )
  {
    idProduct = data->idProduct;
    if ( idProduct == 4658 || (result = 0, idProduct == 4722) )
    {
      if ( sceUsbdScanStaticDescriptor(dev_ext->Handle, data, 4u) )
      {
        result = 0;
        if ( dev_ext->m_unkbb == 5 )
          return result;
        for ( ; !dev_ext->f_patch; ++i )
        {
          DelayThread(500000);
          if ( i >= 20 )
            break;
        }
        if ( dev_ext->f_started != 1 )
        {
          USBACF_Write16550Reg(dev_ext, 3, -128);
          USBACF_Write16550Reg(dev_ext, 0, 1);
          USBACF_Write16550Reg(dev_ext, 1, 0);
          DelayThread(100000);
          USBACF_Write16550Reg(dev_ext, 3, 3);
          USBACF_Write16550Reg(dev_ext, 2, -31);
          USBACF_Write16550Reg(dev_ext, 4, 3);
        }
        USBMODEM_ModifyLed(dev_ext, 1u, 0);
        wrap_set_event_flag_main(dev_ext, 1u);
        dev_ext->f_started = 1;
      }
      return 0;
    }
  }
  return result;
}

//----- (00400854) --------------------------------------------------------
unsigned int __fastcall alarm_cb(PDEVICE_EXTENSION dev_ext)
{
  int RxFifoPutIdx; // $v0
  int RxFifoGetIdx; // $v1
  int evfid; // $a0

  RxFifoPutIdx = dev_ext->RxFifoPutIdx;
  RxFifoGetIdx = dev_ext->RxFifoGetIdx;
  evfid = dev_ext->modem_ops.evfid;
  dev_ext->m_unkba = 0;
  dev_ext->modem_ops.rcv_len = RxFifoPutIdx - RxFifoGetIdx;
  iSetEventFlag(evfid, 0x100u);
  ++dev_ext->m_unkca;
  return 0;
}

//----- (004008A8) --------------------------------------------------------
int __fastcall get_ef_bits(PDEVICE_EXTENSION dev_ext)
{
  return dev_ext->m_ef_bits;
}

//----- (004008B4) --------------------------------------------------------
u32 __fastcall wait_for_ef_bits(PDEVICE_EXTENSION dev_ext, u32 bits)
{
  bool condtmp; // dc
  u32 result; // $v0
  int m_ef_bits; // $v1
  int efbits[2]; // [sp+10h] [-8h] BYREF

  if ( (dev_ext->m_ef_bits & bits) == 0 )
  {
    condtmp = WaitEventFlag(dev_ext->m_evid_main, bits, 17, (u32 *)efbits) != 0;
    result = -1;
    if ( condtmp )
      return result;
    dev_ext->m_ef_bits |= efbits[0];
  }
  m_ef_bits = dev_ext->m_ef_bits;
  result = m_ef_bits & bits;
  dev_ext->m_ef_bits = m_ef_bits & ~bits;
  return result;
}
// 4008B4: using guessed type u32 efbits[2];

//----- (0040092C) --------------------------------------------------------
void __fastcall __noreturn th_2_proc_modem_status(PDEVICE_EXTENSION dev_ext)
{
  char Status; // $s1
  int masktmp; // $v0
  PDEVICE_EXTENSION dev_ext_tmp1; // $a0
  BYTE arg1tmp; // $a1
  BYTE arg2tmp; // $a2
  PDEVICE_EXTENSION dev_ext_tmp2; // $a0

  while ( 1 )
  {
    Status = ModemGetStatus(dev_ext);
    if ( (unsigned int)(dev_ext->m_unkbb - 2) < 2 )
    {
      if ( dev_ext->m_unkbd )
      {
        masktmp = Status & 0x40;
        if ( (Status & 0x80) != 0 )
          goto LABEL_9;
        dev_ext->m_unkbd = 0;
        wrap_set_event_flag_main(dev_ext, 8u);
        dev_ext_tmp1 = dev_ext;
        arg1tmp = 0;
        arg2tmp = 2;
      }
      else
      {
        masktmp = Status & 0x40;
        if ( (Status & 0x80) == 0 )
          goto LABEL_9;
        dev_ext->m_unkbd = 1;
        wrap_set_event_flag_main(dev_ext, 8u);
        dev_ext_tmp1 = dev_ext;
        arg1tmp = 2;
        arg2tmp = 0;
      }
      USBMODEM_ModifyLed(dev_ext_tmp1, arg1tmp, arg2tmp);
    }
    masktmp = Status & 0x40;
LABEL_9:
    if ( dev_ext->m_unkbe )
    {
      dev_ext_tmp2 = dev_ext;
      if ( masktmp )
        goto LABEL_16;
      dev_ext->m_unkbe = 0;
      goto LABEL_14;
    }
    if ( masktmp != 0 )
    {
      dev_ext->m_unkbe = 1;
LABEL_14:
      wrap_set_event_flag_main(dev_ext, 8u);
    }
    dev_ext_tmp2 = dev_ext;
LABEL_16:
    MakeDataTransferRequest(dev_ext_tmp2, 0);
    DelayThread(1000000);
  }
}

//----- (00400A2C) --------------------------------------------------------
int __fastcall th_1_proc_ef_bits(PDEVICE_EXTENSION dev_Ext)
{
  PDEVICE_EXTENSION tmp_dev_ext; // $a0
  signed __int32 efbits_ret; // $v0
  __int16 efbits_trimmed; // $s1
  bool condtmp; // dc
  int result; // $v0
  unsigned int m_unkbb; // $v1

  dev_Ext->modem_ops.snd_len = 1024;
  dev_Ext->m_unkbb = 0;
LABEL_2:
  tmp_dev_ext = dev_Ext;
  while ( 1 )
  {
    efbits_ret = wait_for_ef_bits(tmp_dev_ext, 0x7FFu);
    efbits_trimmed = efbits_ret;
    condtmp = efbits_ret < 0;
    result = 5;
    if ( condtmp )
      return result;
    m_unkbb = dev_Ext->m_unkbb;
    if ( m_unkbb == 5 )
      goto LABEL_2;
    if ( m_unkbb < 5 )
      return result; // FIXME: originally jr $v0
    if ( (unsigned int)(dev_Ext->m_unkbb - 2) >= 2 )
      goto LABEL_2;
    if ( (efbits_trimmed & 2) != 0 )
    {
      dev_Ext->m_unkbb = 0;
      USBMODEM_ModifyLed(dev_Ext, 0, 1u);
      tmp_dev_ext = dev_Ext;
    }
    else
    {
      if ( (efbits_trimmed & 0x400) != 0 )
        get_ef_bits(dev_Ext);
      tmp_dev_ext = dev_Ext;
      if ( !dev_Ext->m_unkbd && dev_Ext->m_unkbe == 1 )
      {
        wrap_set_event_flag_modem(dev_Ext, 0x40u);
        tmp_dev_ext = dev_Ext;
      }
    }
  }
}

//----- (00400C00) --------------------------------------------------------
int __fastcall cxtmdm_patchload_thread(PDEVICE_EXTENSION dev_ext)
{
  int readcmp1; // $s6
  int tempbuf_read1; // $s1
  int trycnt2; // $s3
  PDEVICE_EXTENSION dev_ext_1; // $a0
  int patchread_bytes1; // $v0
  int tempbuf_ind1; // $s0
  char *tempbuf_cur1; // $a0
  int tempbuf_read2; // $s1
  int trycnt1; // $s3
  PDEVICE_EXTENSION dev_ext_2; // $a0
  int patchread_bytes2; // $v0
  int tempbuf_ind2; // $s0
  char *tempbuf_cur2; // $a0
  int result; // $v0
  char ati3[8]; // [sp+10h] [-B8h] BYREF
  char atload[8]; // [sp+18h] [-B0h] BYREF
  char tempbuf[152]; // [sp+20h] [-A8h] BYREF
  char tempstr[16]; // [sp+B8h] [-10h] BYREF

  readcmp1 = 0;
  strcpy(ati3, "ati3\r");
  strcpy(atload, "at**\r");
  strcpy(tempstr, "P2109-V90");
  USBACF_Write16550Reg(dev_ext, 3, -128);
  USBACF_Write16550Reg(dev_ext, 0, 1);
  USBACF_Write16550Reg(dev_ext, 1, 0);
  DelayThread(100000);
  USBACF_Write16550Reg(dev_ext, 3, 3);
  USBACF_Write16550Reg(dev_ext, 2, -31);
  USBACF_Write16550Reg(dev_ext, 4, 3);
  USBMODEM_ModifyLed(dev_ext, 1u, 0);
  DelayThread(2000000);
  PatchWrite(dev_ext, ati3, 6);
  DelayThread(1000000);
  tempbuf_read1 = 0;
  trycnt2 = 0;
  dev_ext_1 = dev_ext;
  do
  {
    patchread_bytes1 = PatchRead(dev_ext_1, &tempbuf[tempbuf_read1], 50 - tempbuf_read1);
    if ( patchread_bytes1 )
    {
      tempbuf_read1 += patchread_bytes1;
      tempbuf_ind1 = 0;
      if ( tempbuf_read1 - 1 > 0 )
      {
        tempbuf_cur1 = tempbuf;
        while ( memcmp(tempbuf_cur1, tempstr, 9) )
        {
          tempbuf_cur1 = &tempbuf[++tempbuf_ind1];
          if ( tempbuf_ind1 >= tempbuf_read1 - 1 )
            goto LABEL_8;
        }
        readcmp1 = 1;
      }
LABEL_8:
      if ( readcmp1 == 1 )
      {
        PatchWrite(dev_ext, atload, 6);
        DelayThread(1000000);
        tempbuf_read2 = 0;
        trycnt1 = 0;
        dev_ext_2 = dev_ext;
        while ( 1 )
        {
          patchread_bytes2 = PatchRead(dev_ext_2, &tempbuf[tempbuf_read2], 50 - tempbuf_read2);
          if ( patchread_bytes2 )
          {
            tempbuf_read2 += patchread_bytes2;
            tempbuf_ind2 = 0;
            if ( tempbuf_read2 - 1 > 0 )
            {
              tempbuf_cur2 = tempbuf;
              while ( memcmp(tempbuf_cur2, "..", 2) )
              {
                tempbuf_cur2 = &tempbuf[++tempbuf_ind2];
                if ( tempbuf_ind2 >= tempbuf_read2 - 1 )
                  goto LABEL_18;
              }
              readcmp1 = 2;
            }
LABEL_18:
            if ( readcmp1 == 2 )
            {
LABEL_21:
              PatchWrite(dev_ext, usbacf_patch, 2274);
              dev_ext_1 = dev_ext;
              goto LABEL_22;
            }
            DelayThread(5000000);
          }
          ++trycnt1;
          dev_ext_2 = dev_ext;
          if ( trycnt1 >= 100 )
            goto LABEL_21;
        }
      }
    }
    ++trycnt2;
    dev_ext_1 = dev_ext;
  }
  while ( trycnt2 <= 99999 );
LABEL_22:
  USBACF_Write16550Reg(dev_ext_1, 2, 3);
  result = dev_ext->m_unkbb;
  if ( !result )
  {
    USBACF_Write16550Reg(dev_ext, 4, 0);
    USBACF_Write16550Reg(dev_ext, 2, 3);
    result = dev_ext->m_unkbb;
  }
  if ( result == 1 )
    result = wrap_set_event_flag_main(dev_ext, 8u);
  dev_ext->f_patch = 1;
  return result;
}
// 400DEC: conditional instruction was optimized away because $s6.4==0
// 400C00: using guessed type char tempbuf[152];

//----- (00400F40) --------------------------------------------------------
PDEVICE_EXTENSION do_alloc_mem_for_dev_ext()
{
  PDEVICE_EXTENSION dev_ext; // $s0
  int evid_main; // $v0
  int thid1; // $v0
  u32 thprior_1; // $v0
  u32 stksz_1; // $a1
  int thid2; // $v0
  iop_event_t evparam; // [sp+10h] [-50h] BYREF
  iop_thread_t thparam1; // [sp+20h] [-40h] BYREF
  iop_thread_t thparam2; // [sp+38h] [-28h] BYREF
  iop_sema_t semaparam; // [sp+50h] [-10h] BYREF

  dev_ext = (PDEVICE_EXTENSION)sceInetAllocMem(0, 5816);
  if ( !dev_ext )
    return 0;
  bzero(dev_ext, 5816);
  dev_ext->MakeDataTransmitReentrancy = -1;
  dev_ext->PipeList[4].nActiveRequests = 0;
  semaparam.attr = 0;
  semaparam.initial = 1;
  semaparam.max = 1;
  semaparam.option = 0;
  dev_ext->sm_xmit = CreateSema(&semaparam);
  dev_ext->bHighAddr = 64;
  memset(&evparam, 0, sizeof(evparam));
  evid_main = CreateEventFlag(&evparam);
  dev_ext->m_evid_main = evid_main;
  if ( evid_main > 0 )
  {
    thparam1.attr = 0x2000000;
    thparam1.thread = (void (__cdecl *)(void *))th_1_proc_ef_bits;
    thparam1.option = 0;
    thparam1.priority = thread_priority;
    thparam1.stacksize = stack_size;
    thid1 = CreateThread(&thparam1);
    dev_ext->m_thid1 = thid1;
    if ( thid1 > 0 )
    {
      if ( StartThread(thid1, dev_ext) )
      {
LABEL_8:
        DeleteThread(dev_ext->m_thid2);
        goto LABEL_9;
      }
      thprior_1 = thread_priority;
      stksz_1 = stack_size;
      dev_ext->m_unkbd = 0;
      dev_ext->m_unkbe = 0;
      thparam2.attr = 0x2000000;
      thparam2.thread = (void (__cdecl *)(void *))th_2_proc_modem_status;
      thparam2.option = 0;
      thparam2.priority = thprior_1;
      thparam2.stacksize = stksz_1;
      thid2 = CreateThread(&thparam2);
      dev_ext->m_thid2 = thid2;
      if ( thid2 > 0 )
      {
        if ( !StartThread(thid2, dev_ext) )
        {
          USec2SysClock(0x2710u, &dev_ext->sys_clock);
          return dev_ext;
        }
        goto LABEL_8;
      }
    }
LABEL_9:
    DeleteEventFlag(dev_ext->m_evid_main);
  }
  sceInetFreeMem(0, dev_ext);
  return 0;
}
// 4034E8: using guessed type int thread_priority;
// 4034EC: using guessed type int stack_size;

//----- (004010A4) --------------------------------------------------------
void __fastcall do_delete_threads(PDEVICE_EXTENSION edv_ext)
{
  TerminateThread(edv_ext->m_thid1);
  TerminateThread(edv_ext->m_thid2);
  TerminateThread(edv_ext->m_thid_patchload);
  DeleteThread(edv_ext->m_thid1);
  DeleteThread(edv_ext->m_thid2);
  DeleteThread(edv_ext->m_thid_patchload);
  DeleteSema(edv_ext->sm_xmit);
  DeleteEventFlag(edv_ext->m_evid_main);
  sceInetFreeMem(0, edv_ext);
}

//----- (00401130) --------------------------------------------------------
int __fastcall ModemStop(PDEVICE_EXTENSION dev_ext)
{
  int state_1; // $a0
  int state; // [sp+10h] [-8h] BYREF

  USBACF_Write16550Reg(dev_ext, 4, 0);
  USBACF_Write16550Reg(dev_ext, 2, 3);
  USBMODEM_ModifyLed(dev_ext, 0, 2u);
  if ( dev_ext->m_unkba )
  {
    CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, dev_ext);
    dev_ext->m_unkba = 0;
    wrap_set_event_flag_main(dev_ext, 2u);
  }
  if ( dev_ext->m_unkbb == 5 )
  {
    sceModemUnregisterDevice(&dev_ext->modem_ops);
    do_delete_threads(dev_ext);
  }
  else
  {
    wrap_set_event_flag_main(dev_ext, 2u);
  }
  CpuSuspendIntr(&state);
  state_1 = state;
  dev_ext->modem_ops.rcv_len = 0;
  dev_ext->RxFifoGetIdx = 0;
  dev_ext->RxFifoPutIdx = 0;
  dev_ext->TxFIFOIdx = 0;
  dev_ext->modem_ops.snd_len = 1024;
  CpuResumeIntr(state_1);
  dev_ext->f_started = 0;
  return 0;
}

//----- (00401224) --------------------------------------------------------
void __fastcall USBACF_RxFlowControl(PDEVICE_EXTENSION pUsb)
{
  char valtmp; // $a2

  if ( pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx < 1024 && (pUsb->RegShadow[4] & 2) == 0 )
  {
    valtmp = pUsb->RegShadow[4] | 2;
LABEL_7:
    USBACF_Write16550Reg(pUsb, 4, valtmp);
    return;
  }
  if ( pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx >= 3073 && (pUsb->RegShadow[4] & 2) != 0 )
  {
    valtmp = pUsb->RegShadow[4] & 0xFD;
    goto LABEL_7;
  }
}

//----- (004012B4) --------------------------------------------------------
int __fastcall ModemRead(PDEVICE_EXTENSION dev_ext, char *buff, int size)
{
  int len; // $s3
  int state_1; // $a0
  int state; // [sp+10h] [-8h] BYREF

  len = 0;
  if ( dev_ext->f_patch )
  {
    CpuSuspendIntr(&state);
    for ( ; size > 0; ++buff )
    {
      if ( !USBACF_RxBufferNotEmpty(dev_ext) )
        break;
      *buff = USBACF_GetRxChar(dev_ext);
      --size;
      ++len;
    }
    state_1 = state;
    dev_ext->modem_ops.rcv_len = dev_ext->RxFifoPutIdx - dev_ext->RxFifoGetIdx;
    CpuResumeIntr(state_1);
    USBACF_RxFlowControl(dev_ext);
  }
  return len;
}

//----- (0040139C) --------------------------------------------------------
int __fastcall PatchRead(PDEVICE_EXTENSION dev_ext, char *buff, int size)
{
  int len; // $s3
  int state_1; // $a0
  int state; // [sp+10h] [-8h] BYREF

  len = 0;
  CpuSuspendIntr(&state);
  for ( ; size > 0; ++buff )
  {
    if ( !USBACF_RxBufferNotEmpty(dev_ext) )
      break;
    *buff = USBACF_GetRxChar(dev_ext);
    --size;
    ++len;
  }
  state_1 = state;
  dev_ext->modem_ops.rcv_len = dev_ext->RxFifoPutIdx - dev_ext->RxFifoGetIdx;
  CpuResumeIntr(state_1);
  USBACF_RxFlowControl(dev_ext);
  return len;
}

//----- (0040147C) --------------------------------------------------------
void __fastcall set_interface_done(int result, int count, PDEVICE_EXTENSION arg)
{
  if ( result )
    printf("cxtmodem: %s -> 0x%x\n", "sceUsbdSetInterface", result);
  arg->Configured = 1;
  arg->Started = 1;
  SetUsbModemPollState(arg, 2);
}

//----- (004014D4) --------------------------------------------------------
void __fastcall set_config_done(int result, int count, PDEVICE_EXTENSION arg)
{
  int r; // $v0
  UsbDeviceRequest _dr; // [sp+18h] [-8h] BYREF

  if ( result )
    printf("cxtmodem: %s -> 0x%x\n", "sceUsbdSetConfiguration", result);
  _dr.requesttype = 1;
  _dr.request = 11;
  _dr.value = 0;
  _dr.index = 0;
  _dr.length = 0;
  r = sceUsbdTransferPipe(arg->EP0Pipe, 0, 0, &_dr, (sceUsbdDoneCallback)set_interface_done, arg);
  if ( r )
    printf("cxtmodem: %s -> 0x%x\n", "sceUsbdSetInterface", r);
}

//----- (00401574) --------------------------------------------------------
int __fastcall UsbAcfModemProbe(int dev_id)
{
  UsbDeviceDescriptor *data; // $a1
  int result; // $v0
  int idProduct; // $v1

  data = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(dev_id, 0, 1u);
  if ( !data )
    return 1;
  result = 0;
  if ( data->idVendor == 1394 )
  {
    idProduct = data->idProduct;
    if ( idProduct == 4658 || (result = 0, idProduct == 4722) )
    {
      resident_flag = 1;
      return sceUsbdScanStaticDescriptor(dev_id, data, 4u) && load_mode != 2;
    }
  }
  return result;
}
// 403560: using guessed type int resident_flag;
// 403564: using guessed type int load_mode;

//----- (00401610) --------------------------------------------------------
int __fastcall UsbAcfModemAttach(int dev_id)
{
  UsbConfigDescriptor *data; // $s4
  int result; // $v0
  UsbInterfaceDescriptor *idesc; // $s0
  PDEVICE_EXTENSION dev_ext; // $v0
  PDEVICE_EXTENSION cbArg; // $s3
  int epo_pipe_tmp; // $v0
  UsbInterfaceDescriptor *idesc_1; // $a1
  int xind; // $s1
  PDEVICE_EXTENSION dev_ext_tmp1; // $s2
  UsbEndpointDescriptor *desc0; // $v0
  UsbEndpointDescriptor *desc0_0; // $s0
  int pipe0_id; // $v0
  __int16 bConfigurationValue; // $v0
  int xferres; // $v0
  UsbDeviceDescriptor *devdesc; // $a1
  int pid_tmp; // $v1
  signed __int8 manuf; // $s0
  signed __int8 prod; // $s4
  int manufind; // $s2
  int manufflg1; // $s1
  int manufflg2; // $v0
  bool regres; // dc
  UCHAR *manufchk1; // $v0
  int manufx1; // $v1
  int prodind; // $s2
  int prodflg1; // $s1
  int prodflg2; // $v0
  UCHAR *prodchk1; // $v0
  int prodx1; // $v1
  u32 thprior_1; // $v1
  u32 stksz_1; // $a1
  int thid_patchload; // $v0
  UCHAR man[64]; // [sp+18h] [-A0h] BYREF
  UCHAR pro[64]; // [sp+58h] [-60h] BYREF
  iop_thread_t thparam; // [sp+98h] [-20h] BYREF
  char epocfg[9]; // [sp+B0h] [-8h] BYREF

  strcpy((char *)man, "Conexant");
  memset(&man[9], 0, 55);
  strcpy((char *)pro, "SMARTSCM");
  memset(&pro[9], 0, 55);
  data = (UsbConfigDescriptor *)sceUsbdScanStaticDescriptor(dev_id, 0, 2u);
  if ( data )
  {
    result = -1;
    if ( data->bNumInterfaces != 1 )
      return result;
    idesc = (UsbInterfaceDescriptor *)sceUsbdScanStaticDescriptor(dev_id, data, 4u);
    if ( idesc )
    {
      result = -1;
      if ( idesc->bNumEndpoints != 8 )
        return result;
      dev_ext = do_alloc_mem_for_dev_ext();
      cbArg = dev_ext;
      if ( dev_ext )
      {
        dev_ext->Handle = dev_id;
        epo_pipe_tmp = sceUsbdOpenPipe(dev_id, 0);
        cbArg->EP0Pipe = epo_pipe_tmp;
        if ( epo_pipe_tmp >= 0 )
        {
          idesc_1 = idesc;
          xind = 0;
          dev_ext_tmp1 = cbArg;
          while ( 1 )
          {
            desc0 = (UsbEndpointDescriptor *)sceUsbdScanStaticDescriptor(dev_id, idesc_1, 5u);
            desc0_0 = desc0;
            if ( !desc0 )
              break;
            pipe0_id = sceUsbdOpenPipe(dev_id, desc0);
            dev_ext_tmp1->PipeList[0].PipeHandle = pipe0_id;
            if ( pipe0_id < 0 )
              break;
            idesc_1 = (UsbInterfaceDescriptor *)desc0_0;
            ++xind;
            dev_ext_tmp1 = (PDEVICE_EXTENSION)((char *)dev_ext_tmp1 + 12);
            if ( xind >= 8 )
            {
              sceUsbdSetPrivateData(dev_id, cbArg);
              epocfg[0] = 0;
              epocfg[1] = 9;
              bConfigurationValue = data->bConfigurationValue;
              *(_WORD *)&epocfg[4] = 0;
              *(_WORD *)&epocfg[6] = 0;
              *(_WORD *)&epocfg[2] = bConfigurationValue;
              xferres = sceUsbdTransferPipe(cbArg->EP0Pipe, 0, 0, epocfg, (sceUsbdDoneCallback)set_config_done, cbArg);
              if ( xferres )
              {
                printf("cxtmodem: %s -> 0x%x\n", "sceUsbdSetConfiguration", xferres);
                return -1;
              }
              devdesc = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(cbArg->Handle, 0, 1u);
              if ( devdesc )
              {
                result = -1;
                if ( devdesc->idVendor == 1394 )
                {
                  pid_tmp = devdesc->idProduct;
                  if ( pid_tmp == 4658 || (result = -1, pid_tmp == 4722) )
                  {
                    manuf = devdesc->iManufacturer;
                    prod = devdesc->iProduct;
                    DelayThread(100);
                    bcopy(man, cbArg->m_man, 32);
                    bcopy(pro, cbArg->m_pro, 32);
                    manufind = 0;
                    epocfg[0] = 0x80;
                    epocfg[1] = 6;
                    *(_WORD *)&epocfg[4] = 0;
                    strcpy(&epocfg[6], "=");
                    *(_WORD *)&epocfg[2] = manuf | 0x300;
                    manufflg1 = 1;
                    sceUsbdTransferPipe(cbArg->EP0Pipe, man, 0x3Du, epocfg, 0, cbArg);
                    DelayThread(100);
                    manufflg2 = 1;
                    do
                    {
                      regres = 2 * manufflg2 >= 65;
                      manufchk1 = &man[2 * manufflg2];
                      if ( regres )
                        break;
                      manufx1 = *manufchk1;
                      if ( (unsigned int)(manufx1 - 32) >= 0x5F )
                      {
                        if ( manufflg1 == 1 )
                          goto LABEL_38;
                        *((_BYTE *)&cbArg->f_started + manufflg1 + 3) = 0;
                        break;
                      }
                      if ( (char)manufx1 == ',' || (char)manufx1 == '=' )
                      {
                        ++manufind;
                        --manufflg1;
                      }
                      else
                      {
                        *((_BYTE *)&cbArg->f_started + manufflg1 + 3) = manufx1;
                      }
                      manufflg2 = ++manufflg1 + manufind;
                    }
                    while ( manufflg1 < 32 );
                    prodind = 0;
                    cbArg->m_pro[0] = 0;
                    epocfg[0] = 0x80;
                    epocfg[1] = 6;
                    *(_WORD *)&epocfg[2] = prod | 0x300;
                    *(_WORD *)&epocfg[4] = 0;
                    strcpy(&epocfg[6], "=");
                    prodflg1 = 1;
                    sceUsbdTransferPipe(cbArg->EP0Pipe, pro, 0x3Du, epocfg, 0, cbArg);
                    DelayThread(100);
                    prodflg2 = 1;
                    do
                    {
                      regres = 2 * prodflg2 >= 65;
                      prodchk1 = &pro[2 * prodflg2];
                      if ( regres )
                        break;
                      prodx1 = *prodchk1;
                      if ( (unsigned int)(prodx1 - 32) >= 0x5F )
                      {
                        if ( prodflg1 != 1 )
                          cbArg->m_man[prodflg1 + 30] = 0;
                        break;
                      }
                      if ( (char)prodx1 == 44 || (char)prodx1 == 61 )
                      {
                        ++prodind;
                        --prodflg1;
                      }
                      else
                      {
                        cbArg->m_man[prodflg1 + 30] = prodx1;
                      }
                      prodflg2 = ++prodflg1 + prodind;
                    }
                    while ( prodflg1 < 32 );
LABEL_38:
                    cbArg->modem_ops.module_name = "cxtmdm";
                    cbArg->modem_ops.vendor_name = (char *)cbArg->m_man;
                    cbArg->modem_ops.device_name = (char *)cbArg->m_pro;
                    cbArg->modem_ops.bus_type = 1;
                    regres = sceUsbdGetDeviceLocation(dev_id, cbArg->modem_ops.bus_loc) != 0;
                    result = -1;
                    if ( !regres )
                    {
                      cbArg->modem_ops.start = (int (__cdecl *)(void *, int))ModemStart;
                      cbArg->modem_ops.stop = (int (__cdecl *)(void *, int))ModemStop;
                      cbArg->modem_ops.recv = (int (__cdecl *)(void *, void *, int))ModemRead;
                      cbArg->modem_ops.send = (int (__cdecl *)(void *, void *, int))ModemWrite;
                      cbArg->modem_ops.prot_ver = 0;
                      cbArg->modem_ops.impl_ver = 0;
                      cbArg->modem_ops.priv = cbArg;
                      cbArg->modem_ops.control = (int (__cdecl *)(void *, int, void *, int))ModemControl;
                      regres = sceModemRegisterDevice(&cbArg->modem_ops) < 0;
                      result = -1;
                      if ( !regres )
                      {
                        DelayThread(100);
                        thprior_1 = thread_priority;
                        stksz_1 = stack_size;
                        cbArg->f_patch = 0;
                        cbArg->f_started = 0;
                        thparam.attr = 0x2000000;
                        thparam.thread = (void (__cdecl *)(void *))cxtmdm_patchload_thread;
                        thparam.option = 0;
                        thparam.priority = thprior_1;
                        thparam.stacksize = stksz_1;
                        thid_patchload = CreateThread(&thparam);
                        cbArg->m_thid_patchload = thid_patchload;
                        if ( thid_patchload <= 0
                          || (regres = StartThread(thid_patchload, cbArg) == 0, result = 0, !regres) )
                        {
                          DeleteThread(cbArg->m_thid_patchload);
                          return 0;
                        }
                      }
                    }
                  }
                }
                return result;
              }
              return -1;
            }
          }
        }
      }
    }
  }
  return -1;
}
// 4034E8: using guessed type int thread_priority;
// 4034EC: using guessed type int stack_size;

//----- (00401B34) --------------------------------------------------------
int __fastcall UsbAcfModemDetach(int dev_id)
{
  PDEVICE_EXTENSION PrivateData; // $s0
  int result; // $v0
  int m_unkbb; // $v1
  PDEVICE_EXTENSION ptr; // $a0

  PrivateData = (PDEVICE_EXTENSION)sceUsbdGetPrivateData(dev_id);
  if ( !PrivateData )
    return -1;
  m_unkbb = PrivateData->m_unkbb;
  if ( m_unkbb != 2 )
  {
    if ( m_unkbb >= 3 )
    {
      if ( m_unkbb != 3 )
      {
        ptr = PrivateData;
        if ( m_unkbb != 4 )
          goto LABEL_10;
      }
    }
    else
    {
      ptr = PrivateData;
      if ( m_unkbb != 1 )
      {
LABEL_10:
        wrap_set_event_flag_modem(ptr, 2u);
        sceModemUnregisterDevice(&PrivateData->modem_ops);
        do_delete_threads(PrivateData);
        result = 0;
        goto LABEL_11;
      }
    }
  }
  PrivateData->m_unkbb = 5;
  wrap_set_event_flag_modem(PrivateData, 2u);
  result = 0;
LABEL_11:
  PrivateData->f_patch = 0;
  PrivateData->f_started = 0;
  return result;
}

//----- (00401BE4) --------------------------------------------------------
int __fastcall start(int argc, char **argv)
{
  int ac_cur; // $s2
  int eqcount; // $s0
  char *eq_pos_tmp; // $a0
  char *eq_chkafter; // $v1
  int result; // $v0

  load_mode = 0;
  g_dialconf = 0;
  ac_cur = 0;
  if ( argc > 0 )
  {
    while ( 1 )
    {
      if ( !strncmp("dial=", *argv, 5) )
        strcpy(&g_dialconf, *argv + 5);
      eqcount = 0;
      if ( **argv )
      {
        eq_pos_tmp = *argv;
        while ( 1 )
        {
          eq_chkafter = eq_pos_tmp;
          if ( *eq_pos_tmp == '=' )
            break;
          ++eq_pos_tmp;
          ++eqcount;
          if ( !eq_chkafter[1] )
            goto LABEL_8;
        }
        *eq_pos_tmp = 0;
        ++eqcount;
      }
LABEL_8:
      if ( !strcmp(*argv, "lmode") )
      {
        if ( !strcmp(&(*argv)[eqcount], "AUTOLOAD") )
        {
          load_mode = 1;
          goto LABEL_14;
        }
        if ( !strcmp(&(*argv)[eqcount], "TESTLOAD") )
          break;
      }
      ++ac_cur;
      ++argv;
      if ( ac_cur >= argc )
        goto LABEL_14;
    }
    load_mode = 2;
  }
LABEL_14:
  if ( load_mode == 1 )
    goto LABEL_22;
  if ( load_mode >= 2 )
  {
    if ( load_mode != 2 )
      goto LABEL_23;
LABEL_22:
    resident_flag = 0;
    goto LABEL_23;
  }
  if ( !load_mode )
    resident_flag = 1;
LABEL_23:
  sceUsbdRegisterLdd(&UsbAcfDriverDescriptor);
  if ( load_mode == 2 )
  {
    sceUsbdUnregisterLdd(&UsbAcfDriverDescriptor);
    result = 5;
    if ( resident_flag != 1 )
      return 1;
  }
  else
  {
    result = 0;
    if ( !resident_flag )
    {
      sceUsbdUnregisterLdd(&UsbAcfDriverDescriptor);
      return 1;
    }
  }
  return result;
}
// 4034A4: using guessed type sceUsbdLddOps UsbAcfDriverDescriptor;
// 403560: using guessed type int resident_flag;
// 403564: using guessed type int load_mode;

//----- (00401DD8) --------------------------------------------------------
void __fastcall USBACF_Write16550Reg(PDEVICE_EXTENSION pUsb, int reg, char data)
{
  char *regtmp1; // $v0

  if ( (unsigned int)reg < 8 )
  {
    regtmp1 = (char *)pUsb + reg;
    regtmp1[5356] = data;
    regtmp1[5364] = -1;
    pUsb->RegChangeFlag = 1;
    MakeRegisterTransmitRequest(pUsb);
  }
}

//----- (00401E14) --------------------------------------------------------
void __fastcall MakeDataTransferRequest(PDEVICE_EXTENSION pUsb, BOOLEAN CallTxHandler)
{
  int reent1; // $s3
  int reent2; // $v0
  int NumOfBytes; // $a1
  int i; // $a0
  unsigned __int8 *Buf; // $v1
  unsigned __int8 txfifochr1; // $v0
  int j; // $a1
  int Length; // $s1
  char *txfifochr2; // $v0
  int xreentw; // $v0

  reent1 = 0;
  reent2 = pUsb->MakeDataTransmitReentrancy + 1;
  pUsb->MakeDataTransmitReentrancy = reent2;
  if ( !reent2 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        if ( pUsb->PipeList[4].nActiveRequests > 0 )
        {
          reent1 = 1;
          goto LABEL_19;
        }
        if ( !pUsb->PipeList[4].NeedReset && pUsb->Started )
          break;
LABEL_19:
        if ( reent1 == 1 )
          reent1 = 0;
        xreentw = pUsb->MakeDataTransmitReentrancy - 1;
        pUsb->MakeDataTransmitReentrancy = xreentw;
        if ( xreentw < 0 )
          return;
      }
      NumOfBytes = pUsb->TxFIFOIdx;
      i = 0;
      if ( NumOfBytes >= 15 )
        NumOfBytes = 14;
      if ( NumOfBytes > 0 )
      {
        Buf = pUsb->TxSendBuf;
        do
        {
          txfifochr1 = pUsb->TxFIFO[i++];
          *Buf = txfifochr1;
          Buf = &pUsb->TxSendBuf[i];
        }
        while ( i < NumOfBytes );
      }
      j = 0;
      for ( Length = i; i < pUsb->TxFIFOIdx; ++j )
      {
        txfifochr2 = (char *)pUsb + i++;
        pUsb->TxFIFO[j] = txfifochr2[216];
      }
      pUsb->TxFIFOIdx = j;
      if ( !j )
        SignalSema(pUsb->sm_xmit);
      if ( Length > 0 )
      {
        CallUsbd(
          pUsb,
          &pUsb->PipeList[4],
          pUsb->TxSendBuf,
          Length,
          (sceUsbdDoneCallback)UsbTransmitDataCompletionRoutine);
        goto LABEL_19;
      }
      if ( !pUsb->TxFIFOIdx )
        goto LABEL_19;
    }
  }
}

//----- (00401F90) --------------------------------------------------------
int __fastcall USBACF_GetRxChar(PDEVICE_EXTENSION pUsb)
{
  int nBytesAvail; // $a1
  int result; // $v0
  signed __int8 c; // $a2

  nBytesAvail = pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx;
  result = 0;
  if ( nBytesAvail > 0 )
  {
    c = pUsb->RxFIFO[pUsb->RxFifoGetIdx++];
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
  return result;
}

//----- (00401FE8) --------------------------------------------------------
BOOLEAN __fastcall USBACF_TxBufferFull(PDEVICE_EXTENSION pUsb)
{
  return pUsb->TxFIFOIdx >= 0x400u;
}

//----- (00401FFC) --------------------------------------------------------
void __fastcall USBACF_PutTxChar(PDEVICE_EXTENSION pUsb, char data)
{
  if ( pUsb->TxFIFOIdx < 0x400u )
    pUsb->TxFIFO[pUsb->TxFIFOIdx++] = data;
}

//----- (00402038) --------------------------------------------------------
void __fastcall UsbTransmitRegisterCompletionRoutine(int result, int count, PDEVICE_EXTENSION context)
{
  int Started; // $v1

  Started = context->Started;
  --context->PipeList[0].nActiveRequests;
  if ( Started )
  {
    OnTransmitCompleted(context, count);
    if ( !result )
      MakeRegisterTransmitRequest(context);
  }
}

//----- (00402090) --------------------------------------------------------
void __fastcall UsbTransmitDataCompletionRoutine(int result, int count, PDEVICE_EXTENSION context)
{
  int Started; // $v1
  int state_1; // $a0
  int TxFIFOIdx; // $v1
  int state; // [sp+10h] [-8h] BYREF

  Started = context->Started;
  --context->PipeList[4].nActiveRequests;
  if ( Started && !result )
  {
    MakeDataTransferRequest(context, 1u);
    CpuSuspendIntr(&state);
    state_1 = state;
    context->m_unkab += count;
    CpuResumeIntr(state_1);
    TxFIFOIdx = context->TxFIFOIdx;
    if ( TxFIFOIdx < 256 )
    {
      context->modem_ops.snd_len = 1024 - TxFIFOIdx;
      wrap_set_event_flag_modem(context, 0x200u);
    }
  }
}

//----- (00402124) --------------------------------------------------------
void __fastcall UsbReceiveRegisterCompletionRoutine(int result, int count, PDEVICE_EXTENSION context)
{
  int count_1; // $s1
  int bPowerState; // $v1
  unsigned int count_rev; // $v0
  int state_1; // $a0
  int state; // [sp+10h] [-8h] BYREF

  count_1 = count;
  --context->PipeList[5].nActiveRequests;
  if ( context->Started )
  {
    bPowerState = context->bPowerState;
    if ( (bPowerState & 2) != 0 )
    {
      if ( result )
      {
        context->bPowerState = bPowerState & 0xFFFFFFFD;
      }
      else
      {
        count_rev = count - 1;
        if ( (unsigned int)count >= 0x20 )
        {
          count_1 = 31;
          count_rev = 30;
        }
        if ( count_rev >> 1 < 0x11 )
          OnNewStatusReceived(context, &context->RecvRegs, count_rev >> 1);
        MakeReceiveRequest(context);
        CpuSuspendIntr(&state);
        state_1 = state;
        context->m_unkaa += count_1;
        CpuResumeIntr(state_1);
      }
    }
  }
}

//----- (004021E8) --------------------------------------------------------
void __fastcall OnNewStatusReceived(PDEVICE_EXTENSION pUsb, struct USBACF_Recv *pUsbRecv, int nFifoCharsReceived)
{
  UCHAR Reg06; // $s3
  int i; // $a3
  struct USBACF_Recv *curptr1; // $a1
  int RxFifoGetIdx; // $a0
  int j; // $a2
  PDEVICE_EXTENSION curptr2; // $v1
  int condval; // $a0
  int state; // [sp+10h] [-8h] BYREF

  Reg06 = pUsbRecv->Reg06;
  CpuSuspendIntr(&state);
  i = 0;
  if ( nFifoCharsReceived > 0 )
  {
    curptr1 = pUsbRecv;
    while ( 1 )
    {
      if ( (curptr1->RxData[0].Reg05 & 1) == 0 )
        goto LABEL_12;
      if ( pUsb->RxFifoPutIdx < 0xFFFu )
        goto LABEL_10;
      if ( pUsb->RxFifoGetIdx )
        break;
LABEL_11:
      ++i;
      curptr1 = (struct USBACF_Recv *)((char *)curptr1 + 2);
      if ( i >= nFifoCharsReceived )
        goto LABEL_12;
    }
    RxFifoGetIdx = pUsb->RxFifoGetIdx;
    j = 0;
    if ( RxFifoGetIdx < pUsb->RxFifoPutIdx )
    {
      curptr2 = pUsb;
      do
      {
        ++j;
        curptr2->RxFIFO[0] = pUsb->RxFIFO[RxFifoGetIdx++];
        curptr2 = (PDEVICE_EXTENSION)((char *)pUsb + j);
      }
      while ( RxFifoGetIdx < pUsb->RxFifoPutIdx );
    }
    pUsb->RxFifoPutIdx = j;
    pUsb->RxFifoGetIdx = 0;
LABEL_10:
    pUsb->RxFIFO[pUsb->RxFifoPutIdx++] = curptr1->RxData[0].Reg00;
    goto LABEL_11;
  }
LABEL_12:
  if ( i > 0 )
  {
    condval = pUsb->m_unkba;
    pUsb->m_unkaa += pUsb->RxFifoPutIdx;
    if ( condval )
    {
      CancelAlarm((unsigned int (__cdecl *)(void *))alarm_cb, pUsb);
      pUsb->m_unkba = 0;
    }
    if ( pUsb->RxFifoPutIdx < 1025 )
    {
      SetAlarm(&pUsb->sys_clock, (unsigned int (__cdecl *)(void *))alarm_cb, pUsb);
      pUsb->m_unkba = 1;
    }
    else
    {
      pUsb->modem_ops.rcv_len = pUsb->RxFifoPutIdx - pUsb->RxFifoGetIdx;
      wrap_set_event_flag_modem(pUsb, 0x100u);
      ++pUsb->m_unkca;
    }
  }
  CpuResumeIntr(state);
  USBACF_RxFlowControl(pUsb);
  pUsb->RShellNtMSRshadow = Reg06;
}

//----- (0040239C) --------------------------------------------------------
BOOLEAN __fastcall USBACF_RxBufferNotEmpty(PDEVICE_EXTENSION pUsb)
{
  return pUsb->RxFifoGetIdx != pUsb->RxFifoPutIdx;
}

//----- (004023B4) --------------------------------------------------------
int __fastcall CallUsbd(
        PDEVICE_EXTENSION pUsb,
        struct PIPE_DATA *Pipe,
        void *Buf,
        int Length,
        sceUsbdDoneCallback CompletionRoutine)
{
  if ( !pUsb->Started )
    return 306;
  ++Pipe->nActiveRequests;
  return sceUsbdTransferPipe(Pipe->PipeHandle, Buf, Length, 0, CompletionRoutine, pUsb);
}

//----- (0040241C) --------------------------------------------------------
void __fastcall MakeReceiveRequest(PDEVICE_EXTENSION pUsb)
{
  if ( pUsb->PipeList[5].nActiveRequests <= 0 && !pUsb->PipeList[5].NeedReset )
  {
    if ( pUsb->Started )
      CallUsbd(pUsb, &pUsb->PipeList[5], &pUsb->RecvRegs, 31, (sceUsbdDoneCallback)UsbReceiveRegisterCompletionRoutine);
  }
}

//----- (0040247C) --------------------------------------------------------
void __fastcall MakeRegisterTransmitRequest(PDEVICE_EXTENSION pUsb)
{
  unsigned int i; // $a0
  unsigned int TmpTxRegIndex; // $a2
  char *curptr1; // $v1
  PDEVICE_EXTENSION curptr2; // $a1
  unsigned __int8 curregval; // $v0
  int size; // $s1

  if ( pUsb->PipeList[0].nActiveRequests <= 0 )
  {
    while ( pUsb->RegChangeFlag || pUsb->TmpTxRegIndex )
    {
      if ( !pUsb->Started )
        break;
      i = 0;
      if ( pUsb->PipeList[0].NeedReset )
        break;
      TmpTxRegIndex = pUsb->TmpTxRegIndex;
      curptr1 = (char *)pUsb + 3 * TmpTxRegIndex;
      curptr2 = pUsb;
      do
      {
        if ( curptr2->RegChanged[0] )
        {
          if ( TmpTxRegIndex >= 0x10 )
            break;
          curregval = curptr2->RegShadow[0];
          curptr1[5437] = i;
          curptr1[5438] = curregval;
          ++TmpTxRegIndex;
          curptr1[5436] = pUsb->bHighAddr;
          curptr1 += 3;
          curptr2->RegChanged[0] = 0;
        }
        ++i;
        curptr2 = (PDEVICE_EXTENSION)((char *)pUsb + i);
      }
      while ( i < 8 );
      if ( i == 8 )
        pUsb->RegChangeFlag = 0;
      size = 3 * TmpTxRegIndex;
      pUsb->TmpTxRegIndex = TmpTxRegIndex;
      if ( size )
      {
        memcpy(pUsb->TxRegs, pUsb->TmpTxRegs, 3 * TmpTxRegIndex);
        pUsb->TmpTxRegIndex = 0;
        CallUsbd(pUsb, pUsb->PipeList, pUsb->TxRegs, size, (sceUsbdDoneCallback)UsbTransmitRegisterCompletionRoutine);
      }
    }
  }
}

//----- (004025B8) --------------------------------------------------------
void __fastcall OnTransmitCompleted(PDEVICE_EXTENSION pUsb, int PacketLength)
{
  ;
}

//----- (004025C0) --------------------------------------------------------
void __fastcall UsbTransmitGpioCompletionRoutine(int result, int count, PDEVICE_EXTENSION context)
{
  int Started; // $v1

  Started = context->Started;
  --context->PipeList[6].nActiveRequests;
  if ( Started )
  {
    if ( !result )
      SendGpioLedRequest(context);
  }
}

//----- (00402604) --------------------------------------------------------
void __fastcall SendGpioLedRequest(PDEVICE_EXTENSION pUsb)
{
  if ( !pUsb->PipeList[6].nActiveRequests && pUsb->bGpioChanged )
  {
    if ( pUsb->Started )
    {
      pUsb->bGpioChanged = 0;
      CallUsbd(pUsb, &pUsb->PipeList[6], &pUsb->u, 4, (sceUsbdDoneCallback)UsbTransmitGpioCompletionRoutine);
    }
  }
}

//----- (00402668) --------------------------------------------------------
void __fastcall USBMODEM_ModifyMode(PDEVICE_EXTENSION pUsb, BYTE SetMode, BYTE ResetMode)
{
  pUsb->bGpioChanged = 1;
  pUsb->u.GpioBuf[2] = (pUsb->u.GpioBuf[2] & ~ResetMode) | SetMode;
  SendGpioLedRequest(pUsb);
}

//----- (004026A0) --------------------------------------------------------
void __fastcall USBMODEM_ModifyLed(PDEVICE_EXTENSION pUsb, BYTE SetMode, BYTE ResetMode)
{
  pUsb->bGpioChanged = 1;
  pUsb->u.GpioBuf[3] = (pUsb->u.GpioBuf[3] & ~ResetMode) | SetMode;
  SendGpioLedRequest(pUsb);
}

//----- (004026D8) --------------------------------------------------------
void __fastcall SetUsbModemPollState(PDEVICE_EXTENSION pUsb, int state)
{
  if ( state == 1 )
  {
    pUsb->bPowerState &= ~2u;
    USBMODEM_ModifyLed(pUsb, 0, 1u);
    USBMODEM_ModifyLed(pUsb, 0, 2u);
    USBMODEM_ModifyLed(pUsb, 0, 4u);
  }
  else if ( state == 2 )
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
  }
}
