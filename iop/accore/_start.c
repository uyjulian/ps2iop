
#include <accore.h>
#include <irx_imports.h>

#define MODNAME "Arcade_Core"
IRX_ID(MODNAME, 1, 1);
// Text section hash:
// cf99d72936452b3070371cc2c3cbe883
// Known titles:
// NM00004
// NM00005
// NM00006
// NM00008
// Path strings:
// /home/ueda/tmp/psalm-0.1.3/core-iop-0.1.6/src/
// /home/ueda/tmp/psalm-0.1.3/core-hdr-0.1.3/src/util/
// TODO: diff with module text hash 10cd5c69591445ffdde8468d75dd031b

extern struct irx_export_table _exp_accore;

typedef int (*acCoreInit)(int argc, char **argv);

struct dma_softc
{
  acQueueHeadData requestq;
  acInt32 status;
  acUint32 padding;
};

struct intr_handler
{
  acIntrHandler func;
  void *arg;
};

struct intr_softc
{
  acUint32 active;
  acUint32 enable;
  struct intr_handler handlers[3];
};

#define acCoreEntry _start

int acDev9ModuleStart(int argc, char **argv);

static acUint8 masks_8[3] = { 128u, 2u, 64u };
static struct dma_softc Dmac;
static struct intr_softc Intrc;

// accore-entry.o

int acCoreEntry(int argc, char **argv)
{
  unsigned int v4;
  acCoreInit *v5;
  int ret_v4;
  acCoreInit inits[3];

  v4 = 0;
  v5 = inits;
  inits[0] = acDev9ModuleStart;
  inits[1] = acIntrModuleStart;
  inits[2] = acDmaModuleStart;
  while ( 1 )
  {
    int ret;
    int v7;

    ret = (*v5)(argc, argv);
    v7 = ret;
    if ( ret < 0 )
    {
      printf("accore:init_start:%d: error %d\n", (int)v4, ret);
      ret_v4 = v7;
      break;
    }
    ++v4;
    ++v5;
    if ( v4 >= 3 )
    {
      ret_v4 = 0;
      break;
    }
  }
  if ( ret_v4 < 0 )
  {
    return ret_v4;
  }
  if ( RegisterLibraryEntries(&_exp_accore) != 0 )
    return -16;
  return 0;
}

// dev9.o

int acDev9ModuleStart(int argc, char **argv)
{
  int AcMemDelayReg;
  int AcIoDelayReg;

  (void)argc;
  (void)argv;
  AcMemDelayReg = GetAcMemDelayReg();
  SetAcMemDelayReg((AcMemDelayReg & 0xFFFFFF00) | 0x66);
  AcIoDelayReg = GetAcIoDelayReg();
  SetAcIoDelayReg((AcIoDelayReg & 0x80FFD700) | 0x6F000855);
  *((volatile acUint16 *)0xB241510C) = 0;
  *((volatile acUint16 *)0xB241511C) = 0;
  *((volatile acUint16 *)0xB2416000) = 0;
  *((volatile acUint16 *)0xB2416032) = 0;
  *((volatile acUint16 *)0xB2416036) = 0;
  *((volatile acUint16 *)0xB241603A) = 0;
  *((volatile acUint16 *)0xB2417000) = 6;
  *((volatile acUint16 *)0xB241601E) = 0;
  return 0;
}

// dma.o

static int dma_cancel(struct dma_softc *dmac, acDmaT dma, int intr, int result)
{
  int d_state;
  acQueueT q_next;
  acQueueT q_prev;
  acSpl state;

  (void)dmac;
  CpuSuspendIntr(&state);
  d_state = dma->d_state;
  if ( d_state )
  {
    if ( (unsigned int)d_state <= 3u )
    {
      if ( d_state == 3 )
      {
        dmac_disable(8u);
      }
      q_next = dma->d_chain.q_next;
      q_prev = dma->d_chain.q_prev;
      q_prev->q_next = q_next;
      q_next->q_prev = q_prev;
    }
    else
    {
      d_state = -13;
    }
  }
  else
  {
    d_state = -13;
  }
  CpuResumeIntr(state);
  if ( d_state >= 0 )
  {
    acDmaOpsT ops;

    ops = dma->d_ops;
    dma->d_state = 0;
    ops->do_error(dma, intr, (acDmaState)d_state, result);
  }
  return d_state;
}

static int dma_xfer(acDmaT dma, void *ioptr, void *buf, int count)
{
  int slice;
  int ret;
  int slice_v2;
  int ret_v3;
  int state;

  slice = dma->d_slice;
  if ( count >= 4 << slice )
  {
    ret = count >> (slice + 2);
    slice_v2 = 1 << slice;
  }
  else
  {
    ret = count >> 2;
    slice_v2 = 1;
  }
  CpuSuspendIntr(&state);
  if ( dma == (acDmaT)Dmac.requestq.q_next && dma->d_state == 2 )
  {
    if ( ret > 0 )
    {
      int attr;
      unsigned int v12;
      int v13;
      int v14;

      attr = dma->d_attr;
      v12 = GetAcIoDelayReg() & 0x80FFDFFF;
      v13 = 0x62000000;
      if ( ioptr == (void *)0xB6000000 )
        v13 = 0x24000000;
      SetAcIoDelayReg(v12 | v13);
      dmac_ch_set_dpcr(8u, (unsigned int)attr >> 5);
      dmac_enable(8u);
      v14 = dmac_request(8u, buf, slice_v2, ret, attr & 1);
      if ( v14 == 1 )
      {
        *((volatile acUint32 *)0x1F801410) = ((unsigned int)ioptr & 0x3FFFFFF) | 0x14000000;
        Dmac.status = 2;
        dma->d_state = 3;
        dmac_transfer(8u);
        ret_v3 = 1;
      }
      else
      {
        Dmac.status = 1;
        ret_v3 = -5;
      }
    }
    else
    {
      ret_v3 = -22;
    }
  }
  else
  {
    ret_v3 = -13;
  }
  CpuResumeIntr(state);
  return ret_v3;
}

static int dma_request(struct dma_softc *dmac, acDmaT dma, int intr)
{
  acDmaState d_state;
  acDmaOpsT ops;
  int ret;
  acSpl state;

  CpuSuspendIntr(&state);
  if ( dma )
  {
    d_state = dma->d_state;
  }
  else
  {
    acDmaT q_next;

    q_next = (acDmaT)dmac->requestq.q_next;
    d_state = AC_DMA_STATE_READY;
    if ( dmac == (struct dma_softc *)q_next )
    {
      d_state = AC_DMA_STATE_FREE;
    }
    else
    {
      dma = (acDmaT)dmac->requestq.q_next;
      q_next->d_state = 2;
    }
  }
  ret = 0;
  if ( dma )
  {
    int flg;
    flg = 0;
    ops = dma->d_ops;
    if ( d_state == AC_DMA_STATE_QUEUE )
    {
      flg = 1;
    }
    else
    {
      if ( d_state )
      {
        if ( d_state != AC_DMA_STATE_READY )
        {
          ret = -13;
          if ( d_state == AC_DMA_STATE_XFER )
          {
            ret = 0;
            flg = 1;
          }
        }
      }
      else
      {
        acQueueT v10;
        acDmaT state_v5;
        unsigned int v12;

        v10 = dmac->requestq.q_next;
        state_v5 = (acDmaT)dmac->requestq.q_prev;
        dma->d_chain.q_next = &dmac->requestq;
        v12 = (unsigned int)dmac ^ (unsigned int)v10;
        ret = v12 == 0;
        flg = v12 != 0;
        dma->d_chain.q_prev = (acQueueT)state_v5;
        state_v5->d_chain.q_next = &dma->d_chain;
        dmac->requestq.q_prev = &dma->d_chain;
      }
      if ( ret < 0 )
      {
        flg = 0;
      }
    }
    if ( !flg )
    {
      ret = -13;
      if ( dma == (acDmaT)dmac->requestq.q_next )
      {
        if ( !ops->do_xfer )
        {
          ret = -14;
        }
        else
        {
          dma->d_state = 2;
          CpuResumeIntr(state);
          ret = ops->do_xfer(dma, intr, dma_xfer);
          CpuSuspendIntr(&state);
          if ( dma->d_state == 3 )
          {
            ret = 0;
          }
        }
      }
      flg = 1;
    }
    if ( ret < 0 )
    {
      flg = 0;
    }
    if ( flg )
    {
      acUint8 v13;

      v13 = dma->d_state + ret;
      ret = dma->d_state;
      dma->d_state = v13;
    }
  }
  CpuResumeIntr(state);
  if ( ret < 0 )
  {
    dma_cancel(dmac, dma, intr, ret);
  }
  return ret;
}

int acDmaRequest(acDmaT dma)
{
  int ret;

  ret = dma_request(&Dmac, dma, 0);
  if ( ret < 0 )
  {
    while ( dma_request(&Dmac, 0, 0) < 0 );
  }
  return ret;
}

int acDmaRequestI(acDmaT dma)
{
  int ret;

  ret = dma_request(&Dmac, dma, 1);
  if ( ret < 0 )
  {
    while ( dma_request(&Dmac, 0, 1) < 0 );
  }
  return ret;
}

int acDmaCancel(acDmaT dma, int result)
{
  int ret;

  ret = dma_cancel(&Dmac, dma, 0, result);
  if ( ret >= 0 )
  {
    while ( dma_request(&Dmac, 0, 0) < 0 );
  }
  return ret;
}

int acDmaCancelI(acDmaT dma, int result)
{
  int ret;

  ret = dma_cancel(&Dmac, dma, 1, result);
  if ( ret >= 0 )
  {
    while ( dma_request(&Dmac, 0, 1) < 0 );
  }
  return ret;
}

static int dma_intr(void *arg)
{
  acDmaData *q_next;
  acQueueData *v3;
  acQueueT q_prev;
  struct dma_softc *argt;

  argt = (struct dma_softc *)arg;
  if ( argt )
  {
    dmac_disable(8u);
    q_next = (acDmaData *)argt->requestq.q_next;
    if ( argt != (struct dma_softc *)q_next )
    {
      acDmaOpsT ops;
      acDmaState state;

      v3 = q_next->d_chain.q_next;
      q_prev = q_next->d_chain.q_prev;
      ops = q_next->d_ops;
      state = q_next->d_state;
      q_prev->q_next = v3;
      v3->q_prev = q_prev;
      q_next->d_state = 0;
      if ( state == AC_DMA_STATE_XFER )
        ops->do_done(q_next);
      else
        ops->do_error(q_next, 1, state, -13);
    }
    while ( dma_request(&Dmac, 0, 1) < 0 )
      ;
  }
  return 1;
}

acDmaT acDmaSetup(acDmaData *dma, acDmaOpsData *ops, int priority, int slice, int output)
{
  if ( dma )
  {
    acUint32 x;
    unsigned int v6;

    dma->d_ops = ops;
    dma->d_attr = (32 * priority) | (output != 0);
    x = slice / 4;
    v6 = 0;
    if ( x > 1 )
    {
      v6 = 1;
      while ( ((unsigned int)1 << v6) < x )
      {
        v6 = v6 + 1;
      }
      v6 = v6 - 1;
    }
    dma->d_slice = v6;
    dma->d_state = 0;
  }
  return dma;
}

int acDmaModuleStart(int argc, char **argv)
{
  int ret;
  char *msg;

  (void)argc;
  (void)argv;
  if ( Dmac.status )
  {
    return -16;
  }
  Dmac.requestq.q_prev = (acQueueT)&Dmac;
  Dmac.requestq.q_next = (acQueueT)&Dmac;
  ret = RegisterIntrHandler(41, 1, dma_intr, &Dmac);
  if ( !ret || ret == -104 )
  {
    ret = EnableIntr(41);
    if ( !ret )
    {
      dmac_disable(8u);
      Dmac.status = 1;
      return 0;
    }
    ReleaseIntrHandler(41);
    msg = "dma_intr_enable";
  }
  else
  {
    msg = "dma_intr_register";
  }
  printf("accore:dma_init:%s: error %d\n", msg, ret);
  return -6;
}

int acDmaModuleStop()
{
  int dummy;

  if ( Dmac.status )
  {
    DisableIntr(41, &dummy);
    ReleaseIntrHandler(41);
    Dmac.status = 0;
  }
  return 0;
}

int acDmaModuleRestart(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  return -88;
}

int acDmaModuleStatus()
{
  return Dmac.status;
}

// intr.o

static int intr_intr(void *arg)
{
  struct intr_softc *argt;

  argt = (struct intr_softc *)arg;
  if ( argt )
  {
    int index;
    struct intr_handler *v2;
    int sr;

    index = 2;
    v2 = &argt->handlers[1];
    sr = (*((volatile acUint16 *)0xB241C000) & 0xFF00) >> 8;
    while ( index >= 0 )
    {
      if ( masks_8[index] && masks_8[index] == ((sr & masks_8[index]) & 0xFF) && v2->func )
        v2->func(v2->arg);
      --index;
      --v2;
    }
  }
  return 1;
}

int acIntrClear(acIntrNum inum)
{
  acUint16 *v2;

  if ( inum == AC_INTR_NUM_ATA )
  {
    v2 = (acUint16 *)0xB3000000;
    *v2 = 0;
  }
  if ( inum == AC_INTR_NUM_UART )
  {
    v2 = (acUint16 *)0xB3100000;
    *v2 = 0;
  }
  return 0;
}

int acIntrEnable(acIntrNum inum)
{
  acUint32 enable;

  if ( (unsigned int)inum >= (AC_INTR_NUM_LAST|AC_INTR_NUM_JV) )
    return -22;
  enable = Intrc.enable;
  Intrc.enable |= 1 << inum;
  if ( inum )
  {
    if ( inum == AC_INTR_NUM_UART )
      *((volatile acUint16 *)0xB241511E) = 0;
  }
  else
  {
    *((volatile acUint16 *)0xB241510C) = 0;
    *((volatile acUint16 *)0xB3000000) = 0;
  }
  if ( !enable )
  {
    switch (EnableIntr(13))
    {
      case 0:
        return 0;
      default:
        return -22;
    }
  }
  return 0;
}

int acIntrDisable(acIntrNum inum)
{
  int v1;
  acUint32 enable;
  int old_status;

  if ( (unsigned int)inum >= (AC_INTR_NUM_LAST|AC_INTR_NUM_JV) )
    return -22;
  if ( inum == AC_INTR_NUM_ATA )
  {
    *((volatile acUint16 *)0xB241510C) = 0;
  }
  if ( inum == AC_INTR_NUM_UART )
  {
    *((volatile acUint16 *)0xB241511C) = 0;
  }
  v1 = 1 << inum;
  Intrc.enable &= ~v1;
  if ( Intrc.enable )
    return 0;
  enable = DisableIntr(13, &old_status);
  if ( enable != (acUint32)-103 )
  {
    if ( !enable )
      return 0;
    return -22;
  }
  return 1;
}

int acIntrRegister(acIntrNum inum, acIntrHandler func, void *arg)
{
  char v3;
  struct intr_handler *handler;
  acUint32 active;
  acSpl state;

  v3 = inum;
  handler = &Intrc.handlers[inum];
  if ( (unsigned int)inum >= (AC_INTR_NUM_LAST|AC_INTR_NUM_JV) )
    return -22;
  if ( handler->func )
    return -11;
  CpuSuspendIntr(&state);
  active = Intrc.active;
  handler->func = func;
  handler->arg = arg;
  Intrc.active = active | (1 << v3);
  CpuResumeIntr(state);
  if ( !active )
  {
    switch (RegisterIntrHandler(13, 1, intr_intr, Intrc.handlers))
    {
      case -104:
        return -11;
      case -100:
        return -4;
      case 0:
        return 0;
      default:
        return -22;
    }
  }
  return 0;
}

int acIntrRelease(acIntrNum inum)
{
  char v1;
  struct intr_handler *handler;
  acUint32 active;
  acUint32 active_v5;
  acSpl state;

  v1 = inum;
  handler = &Intrc.handlers[inum];
  if ( (unsigned int)inum >= (AC_INTR_NUM_LAST|AC_INTR_NUM_JV) )
    return -22;
  if ( !handler->func )
  {
    return -2;
  }
  CpuSuspendIntr(&state);
  active = Intrc.active;
  handler->func = 0;
  handler->arg = 0;
  active_v5 = active & ~(1 << v1);
  Intrc.active = active_v5;
  CpuResumeIntr(state);
  if ( !active_v5 )
  {
    switch (ReleaseIntrHandler(13))
    {
      case -100:
        return -4;
      case -101:
        return -22;
      case 0:
        return 0;
      default:
        return -2;
    }
  }
  return 0;
}

int acIntrModuleStart(int argc, char **argv)
{
  int index;
  int v4;
  int state;

  (void)argc;
  (void)argv;
  if ( Intrc.active != 0 || !Intrc.enable )
  {
    return -16;
  }
  CpuSuspendIntr(&state);
  index = 2;
  v4 = 24;
  while ( index >= 0 )
  {
    acUint32 *v5;

    v5 = (acUint32 *)((char *)&Intrc.active + v4);
    v4 -= 8;
    --index;
    *v5 = 0;
    v5[1] = 0;
  }
  CpuResumeIntr(state);
  Intrc.enable = 0;
  Intrc.active = 0;
  return 0;
}

int acIntrModuleStop()
{
  int v1;

  DisableIntr(13, &v1);
  ReleaseIntrHandler(13);
  Intrc.enable = 0;
  Intrc.active = 0;
  return 0;
}

int acIntrModuleRestart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}

int acIntrModuleStatus()
{
  int ret;
  int state;

  CpuSuspendIntr(&state);
  if ( Intrc.enable )
    ret = 2;
  else
    ret = Intrc.active != 0;
  CpuResumeIntr(state);
  return ret;
}
