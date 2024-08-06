
#include <acata.h>
#include <irx_imports.h>

#define MODNAME "ATA/ATAPI_driver"
IRX_ID(MODNAME, 1, 1);
// Text section hash:
// b4ae71c954a7435710d4be18af0c2ba0
// Known titles:
// NM00048
// NM00052
// Path strings:
// /home/kyota/psalm2hd/psalm-0.1.3/ata-iop-0.1.8/src/
// /home/kyota/psalm2hd/psalm-0.1.3/core-hdr-0.1.3/src/util/

extern struct irx_export_table _exp_acata;

struct ata_softc
{
  acQueueHeadData requestq;
  acUint32 active;
  acInt32 thid;
  struct ac_ata_h *atah;
  acUint16 cprio;
  acUint16 prio;
  acTimerData timer;
};

struct ata_dma
{
  acDmaData ad_dma;
  acAtaT ad_ata;
  acInt32 ad_thid;
  acInt32 ad_result;
  acUint32 ad_state;
};

struct atapi_dma
{
  acDmaData ad_dma;
  acAtapiT ad_atapi;
  acInt32 ad_thid;
  acInt32 ad_result;
  acUint32 ad_state;
};

struct atapi_sense
{
  // cppcheck-suppress unusedStructMember
  acUint8 s_valid;
  // cppcheck-suppress unusedStructMember
  acUint8 s_segnum;
  acUint8 s_key;
  // cppcheck-suppress unusedStructMember
  acUint8 s_info[4];
  // cppcheck-suppress unusedStructMember
  acUint8 s_aslen;
  // cppcheck-suppress unusedStructMember
  acUint8 s_csi[4];
  acUint8 s_asc;
  acUint8 s_ascq;
  // cppcheck-suppress unusedStructMember
  acUint8 s_fruc;
  // cppcheck-suppress unusedStructMember
  acUint8 s_sks[3];
};

#define acAtaEntry _start

static int ata_dma_xfer(acDmaT dma, int intr, acDmaOp op);
static void ata_dma_done(acDmaT dma);
static void ata_dma_error(acDmaT dma, int intr, acDmaState state, int result);
static int ata_ops_command(struct ac_ata_h *atah, int cmdpri, int pri);
static void ata_ops_done(struct ac_ata_h *atah, int result);
static int atapi_dma_xfer(acDmaT dma, int intr, acDmaOp op);
static void atapi_dma_done(acDmaT dma);
static void atapi_dma_error(acDmaT dma, int intr, acDmaState state, int result);
static int atapi_ops_command(struct ac_ata_h *atah, int cmdpri, int pri);
static void atapi_ops_done(struct ac_ata_h *atah, int result);
static int atapi_ops_error(struct ac_ata_h *atah, int ret);

static acDmaOpsData ops_8 = { &ata_dma_xfer, &ata_dma_done, &ata_dma_error };
static struct ac_ata_ops ops_37 = { &ata_ops_command, &ata_ops_done, NULL };
static acDmaOpsData ops_8_0 = { &atapi_dma_xfer, &atapi_dma_done, &atapi_dma_error };
static struct ac_ata_ops ops_48 = { &atapi_ops_command, &atapi_ops_done, &atapi_ops_error };
static struct ata_softc Atac;

// acata-entry.o

int acAtaEntry(int argc, char **argv)
{
  int ret;

  ret = acAtaModuleStart(argc, argv);
  if ( ret < 0 )
  {
    return ret;
  }
  if ( !RegisterLibraryEntries((struct irx_export_table *)&_exp_acata) == 0 )
    return -16;
  return 0;
}

// ata.o

static void ata_timer_done(acTimerT timer, struct ata_softc *arg)
{
  struct ac_ata_h *atah;
  int thid;

  (void)timer;
  atah = arg->atah;
  thid = arg->thid;
  Kprintf("acata:timer_done\n");
  atah->a_state = 511;
  if ( thid )
    iReleaseWaitThread(thid);
}

static void ata_thread(void *arg)
{
  int thid;
  acQueueT q_next;
  struct ac_ata_h *atah;
  struct ac_ata_h *_next_;
  acUint32 tmout;
  acAtaOpsT a_ops;
  int v10;
  acSpl state;
  struct ata_softc *argt;

  argt = (struct ata_softc *)arg;
  thid = GetThreadId();
  argt->thid = thid;
  while ( 1 )
  {
    CpuSuspendIntr(&state);
    q_next = argt->requestq.q_next;
    atah = 0;
    if ( q_next )
    {
      atah = (struct ac_ata_h *)argt->requestq.q_next;
      if ( argt == (struct ata_softc *)q_next )
      {
        atah = 0;
        argt->requestq.q_prev = 0;
        argt->requestq.q_next = 0;
      }
      else
      {
        _next_ = (struct ac_ata_h *)q_next->q_next;
        _next_->a_chain.q_prev = q_next->q_prev;
        argt->requestq.q_next = &_next_->a_chain;
      }
    }
    argt->atah = atah;
    CpuResumeIntr(state);
    if ( atah )
    {
      tmout = atah->a_tmout;
      a_ops = atah->a_ops;
      if ( !tmout )
        tmout = 5000000;
      atah->a_state = 3;
      acTimerAdd(&argt->timer, (acTimerDone)ata_timer_done, argt, tmout);
      v10 = a_ops->ao_command(atah, 32, 78);
      acTimerRemove(&argt->timer);
      if ( v10 < 0 && a_ops->ao_error )
      {
        acTimerAdd(&argt->timer, (acTimerDone)ata_timer_done, argt, 0xF4240u);
        v10 = a_ops->ao_error(atah, v10);
        acTimerRemove(&argt->timer);
      }
      argt->atah = 0;
      a_ops->ao_done(atah, v10);
      CancelWakeupThread(0);
    }
    else
    {
      SleepThread();
    }
    if ( thid != argt->thid )
      ExitThread();
  }
}

static int ata_intr(const struct ata_softc *arg)
{
  if ( arg )
  {
    int thid;

    thid = arg->thid;
    *((volatile acUint16 *)0xB3000000) = 0;
    if ( thid )
      iWakeupThread(thid);
  }
  return 1;
}

int ata_request(struct ac_ata_h *atah, int (*wakeup)(int thid))
{
  int unit;
  int thid;
  acQueueT q_prev;
  acSpl state;

  CpuSuspendIntr(&state);
  unit = 1;
  if ( (atah->a_flag & 0x10) != 0 )
    unit = 2;
  thid = Atac.thid;
  if ( (Atac.active & unit) == 0 )
  {
    thid = 0;
  }
  else
  {
    if ( Atac.thid == 0 )
    {
      wakeup = 0;
    }
    else
    {
      if ( Atac.requestq.q_next )
      {
        wakeup = 0;
      }
      else
      {
        Atac.requestq.q_prev = (acQueueT)&Atac;
        Atac.requestq.q_next = (acQueueT)&Atac;
      }
      q_prev = Atac.requestq.q_prev;
      atah->a_chain.q_next = (acQueueT)&Atac;
      atah->a_chain.q_prev = q_prev;
      q_prev->q_next = &atah->a_chain;
      Atac.requestq.q_prev = &atah->a_chain;
      if ( wakeup )
        atah->a_state = 3;
      else
        atah->a_state = 1;
    }
  }
  CpuResumeIntr(state);
  if ( thid == 0 )
  {
    return -6;
  }
  if ( wakeup == 0 )
  {
    return 0;
  }
  wakeup(thid);
  return 1;
}

static int ata_thread_init(struct ata_softc *atac, int priority)
{
  int th;
  iop_thread_t param;

  param.attr = 0x2000000;
  param.thread = ata_thread;
  param.priority = priority;
  param.stacksize = 0x800;
  param.option = 0;
  th = CreateThread(&param);
  if ( th > 0 )
    StartThread(th, atac);
  return th;
}

int ata_probe(acAtaReg atareg)
{
  int active;
  int unit;
  int count;

  (void)atareg;
  while ( (*((volatile acUint16 *)0xB6070000) & 0x80) != 0 )
    ;
  *((volatile acUint16 *)0xB6020000) = 4660;
  *((volatile acUint16 *)0xB6030000) = 18;
  active = 0;
  unit = 0;
  *((volatile acUint16 *)0xB6160000) = 2;
  *((volatile acUint16 *)0xB6010000) = 0;
  count = 0;
  while ( unit < 2 )
  {
    *((volatile acUint16 *)0xB6060000) = 16 * (unit != 0);
    *((volatile acUint16 *)0xB6070000) = 0;
    while ( count <= 1999999 )
    {
      // cppcheck-suppress knownConditionTrueFalse
      if ( (*((volatile acUint16 *)0xB6070000) & 0x80) == 0 )
        break;
      ++count;
    }
    if ( count )
      active |= 1 << unit;
    ++unit;
    count = 0;
  }
  return active;
}

static int ata_module_optarg(const char *str, int default_value)
{
  int result;
  char *next;

  result = strtol(str, &next, 0);
  if ( next == str )
    return default_value;
  return result;
}

int acAtaModuleStart(int argc, char **argv)
{
  int cmdprio;
  int prio;
  int delay;
  int index;
  char **v11;
  char *opt;
  int v13;
  const char *opt_v10;
  const char *opt_v11;
  int index_v12;
  char *msg;

  if ( acAtaModuleStatus() != 0 )
  {
    return -16;
  }
  cmdprio = Atac.cprio;
  prio = Atac.prio;
  delay = 2000000;
  if ( !Atac.cprio )
    cmdprio = 32;
  index = 1;
  if ( !Atac.prio )
  {
    delay = 1000000;
    prio = 78;
  }
  v11 = argv + 1;
  while ( index < argc )
  {
    opt = *v11;
    if ( **v11 == 45 )
    {
      v13 = opt[1];
      if ( v13 == 100 )
      {
        delay = ata_module_optarg(opt + 2, delay);
      }
      else if ( v13 >= 101 )
      {
        opt_v11 = opt + 2;
        if ( v13 == 112 )
        {
          prio = ata_module_optarg(opt_v11, prio);
        }
      }
      else
      {
        opt_v10 = opt + 2;
        if ( v13 == 99 )
        {
          cmdprio = ata_module_optarg(opt_v10, cmdprio);
        }
      }
    }
    ++v11;
    ++index;
  }
  if ( prio < cmdprio )
    cmdprio = prio;
  Atac.thid = 0;
  Atac.active = 0;
  Atac.cprio = cmdprio;
  Atac.prio = prio;
  Atac.requestq.q_prev = 0;
  Atac.requestq.q_next = 0;
  DelayThread(delay);
  ChangeThreadPriority(0, 123);
  index_v12 = ata_probe((acAtaReg)0xB6000000);
  Atac.active = index_v12;
  if ( index_v12 == 0 )
  {
    msg = "probe device";
    Atac.active = 0;
  }
  else
  {
    index_v12 = acIntrRegister(AC_INTR_NUM_ATA, (acIntrHandler)ata_intr, &Atac);
    if ( index_v12 < 0 && index_v12 != -11 )
    {
      msg = "register intr";
      Atac.active = 0;
    }
    else
    {
      int v18;

      v18 = ata_thread_init(&Atac, prio);
      index_v12 = v18;
      if ( v18 <= 0 )
      {
        acIntrRelease(AC_INTR_NUM_ATA);
        msg = "init thread";
        Atac.active = 0;
      }
      else
      {
        Atac.thid = v18;
        if ( acIntrEnable(AC_INTR_NUM_ATA) < 0 )
        {
          int thid;

          thid = Atac.thid;
          if ( thid > 0 )
          {
            int i;

            Atac.thid = 0;
            WakeupThread(thid);
            for ( i = 1000; ; i = 1000000 )
            {
              int ret;

              DelayThread(i);
              ret = DeleteThread(thid);
              if ( !ret )
                break;
              printf("acata:term_thread: DELETE ret=%d\n", ret);
            }
          }
          acIntrRelease(AC_INTR_NUM_ATA);
          msg = "enable intr";
          Atac.active = 0;
        }
        else
        {
          return 0;
        }
      }
    }
  }
  printf("acata: %s: error %d\n", msg, index_v12);
  return -6;
}

int acAtaModuleStop()
{
  int thid;

  if ( acAtaModuleStatus() == 0 )
  {
    return 0;
  }
  thid = Atac.thid;
  if ( Atac.thid > 0 )
  {
    int i;

    Atac.thid = 0;
    WakeupThread(thid);
    for ( i = 1000; ; i = 1000000 )
    {
      int ret;

      DelayThread(i);
      ret = DeleteThread(thid);
      if ( !ret )
        break;
      printf("acata:term_thread: DELETE ret=%d\n", ret);
    }
  }
  acIntrDisable(AC_INTR_NUM_ATA);
  acIntrRelease(AC_INTR_NUM_ATA);
  Atac.active = 0;
  return 0;
}

int acAtaModuleRestart(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  return -88;
}

int acAtaModuleStatus()
{
  int ret;
  int state;

  CpuSuspendIntr(&state);
  ret = 0;
  if ( Atac.thid )
  {
    ret = 2;
    if ( !Atac.requestq.q_next )
      ret = 1;
  }
  CpuResumeIntr(state);
  return ret;
}

// atacmd.o

static int ata_dma_xfer(acDmaT dma, int intr, acDmaOp op)
{
  struct ata_dma *dmatmp;
  int thid;

  dmatmp = (struct ata_dma *)dma;
  if ( dmatmp->ad_state == 31 )
  {
    dmatmp->ad_result = dmatmp->ad_ata->ac_h.a_size;
    return op(dma, (void *)0xB6000000, dmatmp->ad_ata->ac_h.a_buf, dmatmp->ad_ata->ac_h.a_size);
  }
  thid = dmatmp->ad_thid;
  dmatmp->ad_state = 3;
  if (intr)
    iWakeupThread(thid);
  else
    WakeupThread(thid);
  return 0;
}

static void ata_dma_done(acDmaT dma)
{
  struct ata_dma *dmatmp;
  int thid;

  dmatmp = (struct ata_dma *)dma;

  thid = dmatmp->ad_thid;
  dmatmp->ad_state = 127;
  if ( thid )
    iWakeupThread(thid);
}

static void ata_dma_error(acDmaT dma, int intr, acDmaState state, int result)
{
  struct ata_dma *dmatmp;
  int thid;

  dmatmp = (struct ata_dma *)dma;
  thid = dmatmp->ad_thid;
  dmatmp->ad_state = 1023;
  dmatmp->ad_result = result;
  if ( thid )
  {
    if ( intr )
      iWakeupThread(thid);
    else
      WakeupThread(thid);
  }
  Kprintf("acata:A:dma_error: state=%d ret=%d\n", state, result);
}

static int ata_ops_command(struct ac_ata_h *atah, int cmdpri, int pri)
{
  int flag;
  int ret;
  const acAtaCommandData *cmd;
  int count;
  int flag_v8;
  int v16;
  int ret_v22;
  int sr_v34;
  int ret_v35;
  acAtaCommandData *cmd_v36;
  int rest_v37;
  struct ata_dma dma_data;
  acAtaT ata;

  ata = (acAtaT)atah;
  flag = atah->a_flag;
  ret = 0;
  if ( atah->a_state >= 0x1FFu )
  {
    return -116;
  }
  atah->a_state = 7;
  if ( (flag & 1) != 0 )
  {
    acDmaT dma;
    int ret_v3;

    dma = acDmaSetup(&dma_data.ad_dma, &ops_8, 4, 8, flag & 4);
    dma_data.ad_result = 0;
    // cppcheck-suppress unreadVariable
    dma_data.ad_thid = GetThreadId();
    // cppcheck-suppress unreadVariable
    dma_data.ad_ata = ata;
    dma_data.ad_state = 0;
    ret_v3 = acDmaRequest(dma);
    if ( ret_v3 < 0 )
    {
      printf("acata:A:dma_wait: error %d\n", ret_v3);
      return ret_v3;
    }
    while ( 1 )
    {
      int ret_v5;

      ret_v5 = dma_data.ad_state;
      if ( ret_v5 )
      {
        if ( (int)ret_v5 <= 0 )
        {
          printf("acata:A:dma_wait: TIMEDOUT %d\n", ret_v5);
          acDmaCancel(&dma_data.ad_dma, -116);
          ret = ret_v5;
          if ( ret_v5 >= 0 )
            ret = -116;
          if ( ret < 0 )
          {
            return ret;
          }
        }
        break;
      }
      if ( SleepThread() )
        break;
    }
  }
  ChangeThreadPriority(0, cmdpri);
  cmd = ata->ac_command;
  count = 5;
  flag_v8 = atah->a_flag;
  *((volatile acUint16 *)0xB6060000) = flag_v8 & 0x10;
  *((volatile acUint16 *)0xB6160000) = (flag_v8 & 2) ^ 2;
  *((volatile acUint16 *)0xB6010000) = 0;
  while ( count >= 0 )
  {
    int data;

    data = *cmd++;
    *(acUint16 *)(((2 * ((data >> 8) & 8) + ((data >> 8) & 7)) << 16) + 0xB6000000) = data & 0xFF;
    --count;
    if ( ((data >> 8) & 0xF) == 7 )
    {
      break;
    }
  }
  ChangeThreadPriority(0, pri);
  // cppcheck-suppress knownConditionTrueFalse
  if ( atah->a_state >= 0x1FFu )
  {
    return -116;
  }
  atah->a_state = 31;
  if ( atah->a_buf )
  {
    if ( (flag_v8 & 1) != 0 )
    {
      dma_data.ad_state = 31;
      acDmaRequest(&dma_data.ad_dma);
      printf("acata:dma start\n");
    }
    else
    {
      acUint16 *a_buf;

      a_buf = (acUint16 *)atah->a_buf;
      if ( (flag_v8 & 4) != 0 )
      {
        int a_size;

        a_size = atah->a_size;
        while ( (*((volatile acUint16 *)0xB6070000) & 0x80) != 0 )
          ;
        while ( a_size > 0 )
        {
          int xlen;
          int xlen_v15;
          int xlen_v16;
          int sr;
          int ret_v20;

          xlen = 512;
          if ( a_size < 513 )
            xlen = a_size;
          a_size -= xlen;
          xlen_v15 = (unsigned int)xlen >> 1;
          xlen_v16 = xlen_v15 - 1;
          while ( (*((volatile acUint16 *)0xB6070000) & 8) != 0 )
          {
            int ret_v17;

            ret_v17 = 0;
            if ( xlen_v16 >= 0 )
            {
              ret_v17 = *a_buf;
              a_buf++;
            }
            *((volatile acUint16 *)0xB6000000) = ret_v17;
            --xlen_v16;
          }
          if ( (flag_v8 & 2) != 0 )
          {
            sr = *((volatile acUint16 *)0xB6160000);
            ret_v20 = sr & 0xFF;
            while ( (*((volatile acUint16 *)0xB6160000) & 0x80) != 0 )
            {
              ret_v20 = -116;
              if ( SleepThread() != 0 )
                break;
              ret_v20 = *((volatile acUint16 *)0xB6160000);
            }
          }
          else
          {
            ret_v20 = *((volatile acUint16 *)0xB6070000);
            while ( (*((volatile acUint16 *)0xB6070000) & 0x80) != 0 )
            {
              sr = *((volatile acUint16 *)0xB6070000);
              ret_v20 = sr & 0xFF;
            }
          }
          if ( ret_v20 < 0 )
            break;
          if ( (ret_v20 & 8) == 0 )
            break;
        }
      }
      else
      {
        acUint16 *buf_v23;
        int rest;

        buf_v23 = (acUint16 *)atah->a_buf;
        rest = atah->a_size;
        while ( rest > 0 )
        {
          int sr_v25;
          int xlen_v27;
          int xlen_v28;
          int ret_v29;
          int xlen_v30;

          if ( (flag_v8 & 2) != 0 )
          {
            sr_v25 = *((volatile acUint16 *)0xB6160000);
            sr_v25 = sr_v25 & 0xFF;
            while ( (*((volatile acUint16 *)0xB6160000) & 0x80) != 0 )
            {
              sr_v25 = -116;
              if ( SleepThread() )
                break;
              sr_v25 = *((volatile acUint16 *)0xB6160000);
            }
          }
          else
          {
            sr_v25 = *((volatile acUint16 *)0xB6070000);
            while ( (*((volatile acUint16 *)0xB6070000) & 0x80) != 0 )
            {
              sr_v25 = *((volatile acUint16 *)0xB6070000);
              sr_v25 = sr_v25 & 0xFF;
            }
          }
          if ( sr_v25 < 0 )
            break;
          xlen_v27 = 512;
          if ( rest < 513 )
            xlen_v27 = rest;
          rest -= xlen_v27;
          xlen_v28 = (unsigned int)xlen_v27 >> 1;
          if ( (sr_v25 & 1) != 0 )
            xlen_v28 = 0;
          (void)(*((volatile acUint16 *)0xB6070000) & 0x80);
          xlen_v30 = xlen_v28 - 1;
          while ( (*((volatile acUint16 *)0xB6070000) & 8) != 0 )
          {
            if ( xlen_v30 >= 0 )
            {
              *buf_v23 = *((volatile acUint16 *)0xB6000000);
              buf_v23++;
            }
            --xlen_v30;
          }
          ret_v29 = *((volatile acUint16 *)0xB6070000) & 0x80;
          if ( !ret_v29 )
            break;
        }
      }
    }
  }
  v16 = flag_v8 & 2;
  ret_v22 = flag_v8 & 1;
  if ( ret_v22 )
  {
    signed int state;

    state = 63;
    while ( 1 )
    {
      int v38;

      v38 = *((volatile acUint16 *)0xB6160000) & 1;
      if ( v38 || state >= 511 )
      {
        printf("acata:A:dma_iowait: TIMEDOUT %04x:%02x:%02x\n", state, *((volatile acUint16 *)0xB6160000), *((volatile acUint16 *)0xB6010000));
        if ( state < 1023 )
          acDmaCancel(&dma_data.ad_dma, -116);
        ret = 0;
        if ( !v38 )
          ret = -116;
        break;
      }
      state = dma_data.ad_state;
      if ( (*((volatile acUint16 *)0xB6160000) & 0x80) == 0 && (int)dma_data.ad_state >= 64 )
      {
        ret = dma_data.ad_result;
        break;
      }
      if ( SleepThread() )
      {
        state = 511;
        if ( dma_data.ad_state == 31 )
          state = 1023;
      }
    }
  }
  else
  {
    ret = 0;
    if ( v16 )
    {
      while ( (*((volatile acUint16 *)0xB6160000) & 0x81) == 128 )
      {
        if ( SleepThread() )
        {
          ret = -116;
          break;
        }          
      }
    }
    else
    {
      int tmout;

      tmout = 99999;
      while ( (*((volatile acUint16 *)0xB6070000) & 0x81) == 128 )
      {
        if ( tmout < 0 )
        {
          ret = -116;
          break;
        }
        --tmout;
      }
    }
    if ( ret < 0 )
    {
      printf("acata:C:io_done: TIMEDOUT\n");
    }
  }
  if ( ret < 0 )
  {
    return ret;
  }
  sr_v34 = *((volatile acUint16 *)0xB6070000);
  if ( (*((volatile acUint16 *)0xB6070000) & 1) != 0 )
    return -((sr_v34 << 8) + *((volatile acUint16 *)0xB6010000));
  if ( atah->a_state < 0x1FFu )
  {
    atah->a_state = 127;
    ret_v35 = 0;
  }
  else
  {
    ret_v35 = -116;
  }
  cmd_v36 = ata->ac_command;
  if ( ret_v35 < 0 )
  {
    return -((sr_v34 << 8) + *((volatile acUint16 *)0xB6010000));
  }
  for ( rest_v37 = 6; rest_v37 > 0; --rest_v37 )
  {
    if ( (((int)*cmd_v36 >> 12) & 0xF) == 0 )
      break;
    *cmd_v36 = ((((int)*cmd_v36 >> 12) & 0xF) << 12) | ((*(acUint16 *)(((2 * (((int)*cmd_v36 >> 12) & 8) + (((int)*cmd_v36 >> 12) & 7)) << 16) + 0xB6000000)) & 0xFF);
    ++cmd_v36;
  }
  return 6 - rest_v37;
}

static void ata_ops_done(struct ac_ata_h *atah, int result)
{
  acAtaDone ac_done;
  acAtaT ata;

  ata = (acAtaT)atah;
  ac_done = ata->ac_done;
  if ( ac_done )
    ac_done(ata, atah->a_arg, result);
}

acAtaT acAtaSetup(acAtaData *ata, acAtaDone done, void *arg, unsigned int tmout)
{
  if ( ata )
  {
    ata->ac_h.a_ops = &ops_37;
    ata->ac_h.a_arg = arg;
    ata->ac_h.a_tmout = tmout;
    ata->ac_h.a_state = 0;
    ata->ac_h.a_flag = 0;
    ata->ac_done = done;
  }
  return ata;
}

acAtaCommandData *acAtaReply(acAtaT ata)
{
  if ( ata == 0 )
    return 0;
  return ata->ac_command;
}

int acAtaRequest(acAtaT ata, int flag, acAtaCommandData *cmd, int item, void *buf, int size)
{
  int v7;
  const acAtaCommandData *v8;
  char *v9;

  flag = (flag | 8) ^ 8;
  if ( !ata || !cmd )
  {
    return -22;
  }
  if ( (unsigned int)item >= 7 )
  {
    return -34;
  }
  v7 = item - 1;
  ata->ac_h.a_flag = flag;
  v8 = &cmd[v7];
  v9 = (char *)ata + 2 * v7;
  while ( v7 >= 0 )
  {
    --v7;
    *((acUint16 *)v9 + 18) = *v8--;
    v9 -= 2;
  }
  ata->ac_h.a_buf = buf;
  ata->ac_h.a_size = size;
  return ata_request(&ata->ac_h, WakeupThread);
}

int acAtaRequestI(acAtaT ata, int flag, acAtaCommandData *cmd, int item, void *buf, int size)
{
  int v7;
  const acAtaCommandData *v8;
  char *v9;

  flag = (flag | 8) ^ 8;
  if ( !ata || !cmd )
  {
    return -22;
  }
  if ( (unsigned int)item >= 7 )
  {
    return -34;
  }
  v7 = item - 1;
  ata->ac_h.a_flag = flag;
  v8 = &cmd[v7];
  v9 = (char *)ata + 2 * v7;
  while ( v7 >= 0 )
  {
    --v7;
    *((acUint16 *)v9 + 18) = *v8--;
    v9 -= 2;
  }
  ata->ac_h.a_buf = buf;
  ata->ac_h.a_size = size;
  return ata_request(&ata->ac_h, iWakeupThread);
}

int acAtaStatus(acAtaT ata)
{
  int state;

  if ( ata == 0 )
  {
    return -22;
  }
  state = ata->ac_h.a_state;
  if ( (unsigned int)(state - 1) >= 0x7E )
  {
    return 0;
  }
  if ( state != 1 )
    return 2;
  return 1;
}

// atapicmd.o

static int atapi_dma_xfer(acDmaT dma, int intr, acDmaOp op)
{
  struct atapi_dma *dmatmp;
  int thid;

  dmatmp = (struct atapi_dma *)dma;
  if ( dmatmp->ad_state == 31 )
  {
    dmatmp->ad_result = dmatmp->ad_atapi->ap_h.a_size;
    return op(dma, (void *)0xB6000000, dmatmp->ad_atapi->ap_h.a_buf, dmatmp->ad_atapi->ap_h.a_size);
  }
  thid = dmatmp->ad_thid;
  dmatmp->ad_state = 3;
  if (intr)
    iWakeupThread(thid);
  else
    WakeupThread(thid);
  return 0;
}

static void atapi_dma_done(acDmaT dma)
{
  struct atapi_dma *dmatmp;
  int thid;

  dmatmp = (struct atapi_dma *)dma;
  thid = dmatmp->ad_thid;
  dmatmp->ad_state = 127;
  if ( thid )
    iWakeupThread(thid);
}

static void atapi_dma_error(acDmaT dma, int intr, acDmaState state, int result)
{
  struct atapi_dma *dmatmp;
  int thid;

  dmatmp = (struct atapi_dma *)dma;
  thid = dmatmp->ad_thid;
  dmatmp->ad_state = 1023;
  dmatmp->ad_result = result;
  if ( thid )
  {
    if ( intr )
      iWakeupThread(thid);
    else
      WakeupThread(thid);
  }
  Kprintf("acata:P:dma_error: state=%d ret=%d\n", state, result);
}

static int atapi_packet_send(acAtaReg atareg, acAtapiPacketData *pkt, int flag)
{
  int count;
  int tmout;
  int v6;

  (void)atareg;
  count = 6;
  *((volatile acUint16 *)0xB6050000) = 0;
  *((volatile acUint16 *)0xB6040000) = 64;
  *((volatile acUint16 *)0xB6060000) = flag & 0x10;
  *((volatile acUint16 *)0xB6160000) = (flag & 2) ^ 2;
  *((volatile acUint16 *)0xB6010000) = flag & 1;
  *((volatile acUint16 *)0xB6070000) = 160;
  tmout = 999;
  // cppcheck-suppress knownConditionTrueFalse
  while ( (*((volatile acUint16 *)0xB6070000) & 0x80) != 0 )
  {
    if ( tmout < 0 )
    {
      printf("acata:P:wait: TIMEDOUT\n");
      v6 = -116;
      break;
    }
    --tmout;
    v6 = tmout + 1;
  }
  if ( v6 < 0 )
  {
    printf("acata:P:packet_send: TIMEDOUT\n");
    return -116;
  }
  // cppcheck-suppress knownConditionTrueFalse
  while ( (*((volatile acUint16 *)0xB6070000) & 8) != 0 )
  {
    --count;
    if ( count < 0 )
      break;
    *((volatile acUint16 *)0xB6000000) = pkt->u_h[0];
    pkt = (acAtapiPacketData *)((char *)pkt + 2);
  }
  return 0;
}

static int atapi_pio_read(acAtaReg atareg, acUint16 *buf, int count, int flag)
{
  char v6;
  int rest;
  int sr;
  int xlen;
  int sr_v5;
  int drop_v10;

  (void)atareg;
  v6 = flag;
  rest = count;
  sr = flag & 2;
  while ( 1 )
  {
    int xlen_v6;
    int drop;
    int xlen_v8;
    int sr_v9;

    if ( !sr )
    {
      sr_v5 = *((volatile acUint16 *)0xB6070000);
      while ( (*((volatile acUint16 *)0xB6070000) & 0x80) != 0 )
      {
        xlen = *((volatile acUint16 *)0xB6070000);
        sr_v5 = xlen & 0xFF;
      }
    }
    else
    {
      xlen = *((volatile acUint16 *)0xB6160000);
      sr_v5 = xlen & 0xFF;
      while ( (*((volatile acUint16 *)0xB6160000) & 0x80) != 0 )
      {
        sr_v5 = -116;
        if ( SleepThread() != 0 )
          break;
        sr_v5 = *((volatile acUint16 *)0xB6160000);
      }
    }
    if ( sr_v5 < 0 )
      return sr_v5;
    if ( (sr_v5 & 8) == 0 )
      break;
    xlen_v6 = (*((volatile acUint16 *)0xB6050000) << 8) + *((volatile acUint16 *)0xB6040000);
    drop = xlen_v6 - rest;
    if ( rest >= xlen_v6 )
      drop = 0;
    else
      xlen_v6 = rest;
    rest -= xlen_v6;
    xlen_v8 = (xlen_v6 + 1) / 2 - 1;
    while ( xlen_v8 >= 0 )
    {
      --xlen_v8;
      *buf++ = *((volatile acUint16 *)0xB6000000);
    }
    sr_v9 = drop + 1;
    for ( drop_v10 = sr_v9 / 2 - 1; drop_v10 >= 0; --drop_v10 )
      ;
    sr = v6 & 2;
    if ( (*((volatile acUint16 *)0xB6070000) & 0x80) == 0 )
    {
      break;
    }
  }
  return count - rest;
}

static int atapi_ops_command(struct ac_ata_h *atah, int cmdpri, int pri)
{
  int flag;
  int ret_v5;
  int v28;
  struct atapi_dma dma_data;
  acAtapiT atapi;

  atapi = (acAtapiT)atah;
  flag = atah->a_flag;
  if ( (flag & 1) == 0 )
  {
    ret_v5 = 0;
  }
  else
  {
    acDmaT dma;
    int v8;
    int ret;

    dma = acDmaSetup(&dma_data.ad_dma, &ops_8_0, 4, 64, flag & 4);
    dma_data.ad_result = 0;
    // cppcheck-suppress unreadVariable
    dma_data.ad_thid = GetThreadId();
    // cppcheck-suppress unreadVariable
    dma_data.ad_atapi = atapi;
    dma_data.ad_state = 0;
    v8 = acDmaRequest(dma);
    ret = v8;
    if ( v8 < 0 )
    {
      printf("acata:P:dma_wait: error %d\n", v8);
      ret_v5 = ret;
    }
    else
    {
      while ( 1 )
      {
        int flg;

        flg = 0;
        ret_v5 = dma_data.ad_state;
        if ( ret_v5 )
        {
          if ( (int)ret_v5 > 0 )
          {
            ret_v5 = 0;
            break;
          }
          flg = 1;
        }
        if ( flg == 0 && SleepThread() )
          flg = 1;
        if ( flg != 0 )
        {
          printf("acata:P:dma_wait: TIMEDOUT %d\n", ret_v5);
          acDmaCancel(&dma_data.ad_dma, -116);
          if ( ret_v5 >= 0 )
          {
            ret_v5 = -116;
          }
          break;
        }
      }
    }
  }
  if ( ret_v5 < 0 )
    return ret_v5;
  ChangeThreadPriority(0, cmdpri);
  ret_v5 = atapi_packet_send((acAtaReg)0xB6000000, &atapi->ap_packet, flag);
  if ( ret_v5 >= 0 )
  {
    int v12;
    if ( atah->a_state < 0x1FFu )
    {
      atah->a_state = 31;
      v12 = 0;
    }
    else
    {
      v12 = -116;
    }
    ret_v5 = -116;
    if ( v12 >= 0 )
    {
      acUint16 *a_buf;

      a_buf = (acUint16 *)atah->a_buf;
      if ( !a_buf )
      {
        ret_v5 = 0;
      }
      else if ( (flag & 1) != 0 )
      {
        dma_data.ad_state = 31;
        ret_v5 = acDmaRequest(&dma_data.ad_dma);
      }
      else
      {
        int size;
        acUint16 *v15;

        size = atah->a_size;
        v15 = (acUint16 *)atah->a_buf;
        if ( (flag & 4) == 0 )
        {
          ret_v5 = atapi_pio_read((acAtaReg)0xB6000000, a_buf, atah->a_size, flag);
        }
        else
        {
          signed int a_size;
          int sr;

          a_size = atah->a_size;
          sr = flag & 2;
          while ( 1 )
          {
            int xlen;
            int sr_v14;
            int xlen_v15;
            int drop;
            int xlen_v17;
            int sr_v18;
            int drop_v20;

            if ( sr )
            {
              xlen = *((volatile acUint16 *)0xB6160000);
              sr_v14 = xlen & 0xFF;
              while ( (*((volatile acUint16 *)0xB6160000) & 0x80) != 0 )
              {
                sr_v14 = -116;
                if ( SleepThread() != 0 )
                  break;
                sr_v14 = *((volatile acUint16 *)0xB6160000);
              }
            }
            else
            {
              sr_v14 = *((volatile acUint16 *)0xB6070000);
              while ( (*((volatile acUint16 *)0xB6070000) & 0x80) != 0 )
              {
                xlen = *((volatile acUint16 *)0xB6070000);
                sr_v14 = xlen & 0xFF;
              }
            }
            ret_v5 = sr_v14;
            if ( sr_v14 < 0 )
              break;
            if ( (sr_v14 & 8) == 0 )
            {
              ret_v5 = size - a_size;
              break;
            }
            xlen_v15 = (*((volatile acUint16 *)0xB6050000) << 8) + *((volatile acUint16 *)0xB6040000);
            drop = xlen_v15 - a_size;
            if ( a_size >= xlen_v15 )
              drop = 0;
            else
              xlen_v15 = a_size;
            a_size -= xlen_v15;
            xlen_v17 = (xlen_v15 + 1) / 2 - 1;
            for ( sr_v18 = drop + 1; xlen_v17 >= 0; sr_v18 = drop + 1 )
            {
              *((volatile acUint16 *)0xB6000000) = *v15;
              v15++;
              --xlen_v17;
            }
            for ( drop_v20 = sr_v18 / 2 - 1; drop_v20 >= 0; --drop_v20 )
              *((volatile acUint16 *)0xB6000000) = 0;
            sr = flag & 2;
            if ( (*((volatile acUint16 *)0xB6070000) & 0x80) == 0 )
            {
              ret_v5 = size - a_size;
              break;
            }
          }
        }
      }
    }
  }
  ChangeThreadPriority(0, pri);
  if ( ret_v5 < 0 )
    return ret_v5;
  if ( atah->a_state < 0x1FFu )
  {
    atah->a_state = 63;
    v28 = 0;
  }
  else
  {
    v28 = -116;
  }
  if ( v28 < 0 )
    return -116;
  if ( (flag & 1) == 0 )
  {
    int v32;

    v32 = 0;
    if ( (flag & 2) != 0 )
    {
      while ( (*((volatile acUint16 *)0xB6160000) & 0x81) == 128 )
      {
        if ( SleepThread() )
        {
          v32 = -116;
          break;
        }
      }
    }
    else
    {
      int tmout;

      tmout = 99999;
      while ( (*((volatile acUint16 *)0xB6070000) & 0x81) == 128 )
      {
        if ( tmout < 0 )
        {
          v32 = -116;
          break;
        }
        --tmout;
      }
    }
    if ( v32 < 0 )
    {
      printf("acata:C:io_done: TIMEDOUT\n");
      ret_v5 = -116;
    }
  }
  else
  {
    signed int ret_v23;
    acInt32 ad_result;

    ret_v23 = 63;
    while ( 1 )
    {
      int v30;

      v30 = *((volatile acUint16 *)0xB6160000) & 1;
      if ( v30 || ret_v23 >= 511 )
      {
        printf("acata:P:dma_iowait: TIMEDOUT %04x:%02x:%02x\n", ret_v23, *((volatile acUint16 *)0xB6160000), *((volatile acUint16 *)0xB6010000));
        if ( ret_v23 < 1023 )
          acDmaCancel(&dma_data.ad_dma, -116);
        ad_result = 0;
        if ( !v30 )
          ad_result = -116;
        break;
      }
      ret_v23 = dma_data.ad_state;
      if ( (*((volatile acUint16 *)0xB6160000) & 0x80) == 0 && (int)dma_data.ad_state >= 64 )
      {
        ad_result = dma_data.ad_result;
        break;
      }
      if ( SleepThread() )
      {
        ret_v23 = 511;
        if ( dma_data.ad_state == 31 )
          ret_v23 = 1023;
      }
    }
    ret_v5 = ad_result;
  }
  if ( ret_v5 < 0 )
    return ret_v5;
  if ( (*((volatile acUint16 *)0xB6070000) & 1) != 0 )
    return -((*((volatile acUint16 *)0xB6070000) << 8) + *((volatile acUint16 *)0xB6010000));
  if ( atah->a_state >= 0x1FFu )
  {
    return -116;
  }
  atah->a_state = 127;
  return ret_v5;
}

static void atapi_ops_done(struct ac_ata_h *atah, int result)
{
  acAtapiDone ap_done;
  acAtapiT atapi;

  atapi = (acAtapiT)atah;
  ap_done = atapi->ap_done;
  if ( ap_done )
    ap_done(atapi, atah->a_arg, result);
}

static int atapi_ops_error(struct ac_ata_h *atah, int ret)
{
  int flag;
  int v3;
  struct atapi_sense sense;
  union
  {
    struct
    {
      acUint8 opcode;
      acUint8 lun;
      // cppcheck-suppress unusedStructMember
      acUint8 padding[2];
      acUint8 len;
      // cppcheck-suppress unusedStructMember
      acUint8 padding2[7];
    };
    acAtapiPacketData pkt;
  } u;
  acAtapiT atapi;

  atapi = (acAtapiT)atah;
  if ( (*((volatile acUint16 *)0xB6070000) & 1) == 0 )
    return ret;
  memset(&sense, 0, sizeof(sense));
  memset(&u, 0, sizeof(u));
  flag = atah->a_flag;
  u.opcode = 0x03;
  u.len = 0x12;
  u.lun = atapi->ap_packet.u_b[1];
  *((volatile acUint16 *)0xB6160000) = (flag & 2) ^ 2;
  *((volatile acUint16 *)0xB6010000) = 0;
  v3 = atapi_packet_send((acAtaReg)0xB6000000, &u.pkt, flag);
  if ( v3 < 0 )
  {
    ret = v3;
  }
  else
  {
    int v4;
    int v5;

    v4 = atapi_pio_read((acAtaReg)0xB6000000, (acUint16 *)&sense, sizeof(sense), flag);
    v5 = v4;
    if ( v4 > 0 )
    {
      int v6;

      v6 = 0;
      if ( (flag & 2) != 0 )
      {
        while ( (*((volatile acUint16 *)0xB6160000) & 0x81) == 128 )
        {
          if ( SleepThread() )
          {
            v6 = -116;
            break;
          }
        }
      }
      else
      {
        int tmout;

        tmout = 99999;
        while ( (*((volatile acUint16 *)0xB6070000) & 0x81) == 128 )
        {
          if ( tmout < 0 )
          {
            v6 = -116;
            break;
          }
          --tmout;
        }
      }
      if ( v6 < 0 )
      {
        printf("acata:C:io_done: TIMEDOUT\n");
        v6 = -116;
      }
      v3 = v5;
      if ( v6 < 0 )
        v3 = -116;
      ret = v3;
    }
    else
    {
      ret = v4;
      if ( !v4 )
      {
        v3 = -5;
        ret = v3;
      }
    }
  }
  if ( ret > 0 )
    return -((sense.s_key << 16) | (sense.s_asc << 8) | sense.s_ascq);
  if ( !ret )
    return -5;
  return ret;
}

acAtapiT acAtapiSetup(acAtapiData *atapi, acAtapiDone done, void *arg, unsigned int tmout)
{
  if ( atapi )
  {
    atapi->ap_h.a_ops = &ops_48;
    atapi->ap_h.a_arg = arg;
    atapi->ap_h.a_tmout = tmout;
    atapi->ap_h.a_state = 0;
    atapi->ap_h.a_flag = 0;
    atapi->ap_done = done;
  }
  return atapi;
}

int acAtapiRequest(acAtapiT atapi, int flag, acAtapiPacketData *pkt, void *buf, int size)
{
  flag = flag | 8;
  if ( !atapi || !pkt )
  {
    return -22;
  }
  atapi->ap_h.a_flag = flag;
  atapi->ap_packet.u_w[0] = pkt->u_w[0];
  atapi->ap_packet.u_w[1] = pkt->u_w[1];
  atapi->ap_packet.u_w[2] = pkt->u_w[2];
  atapi->ap_h.a_buf = buf;
  atapi->ap_h.a_size = size;
  return ata_request(&atapi->ap_h, WakeupThread);
}

int acAtapiRequestI(acAtapiT atapi, int flag, acAtapiPacketData *pkt, void *buf, int size)
{
  flag = flag | 8;
  if ( !atapi || !pkt )
  {
    return -22;
  }
  atapi->ap_h.a_flag = flag;
  atapi->ap_packet.u_w[0] = pkt->u_w[0];
  atapi->ap_packet.u_w[1] = pkt->u_w[1];
  atapi->ap_packet.u_w[2] = pkt->u_w[2];
  atapi->ap_h.a_buf = buf;
  atapi->ap_h.a_size = size;
  return ata_request(&atapi->ap_h, iWakeupThread);
}

int acAtapiStatus(acAtapiT atapi)
{
  int state;

  if ( atapi == 0 )
  {
    return -22;
  }
  state = atapi->ap_h.a_state;
  if ( (unsigned int)(state - 1) >= 0x7E )
  {
    return 0;
  }
  if ( state != 1 )
    return 2;
  return 1;
}
