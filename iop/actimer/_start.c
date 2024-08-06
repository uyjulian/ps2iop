
#include <actimer.h>
#include <irx_imports.h>

#define MODNAME "simple_timer"
IRX_ID(MODNAME, 1, 1);
// Text section hash:
// 6d5f9b91cc1ce01e895297ea9f8ae6b4
// Known titles:
// NM00005
// NM00006
// NM00008
// Path strings:
// /home/ueda/tmp/psalm-0.1.3/timer-iop-0.1.4/src/
// /home/ueda/tmp/psalm-0.1.3/core-hdr-0.1.3/src/util/
// TODO: diff with module text hash 0f77412b636a0393ccd6848c86ce5011

extern struct irx_export_table _exp_actimer;

struct timer_softc
{
  acQueueHeadData waitq;
  acTime tick;
};

#define acTimerEntry _start

static struct timer_softc Timerc;

// actimer-entry.o

int acTimerEntry(int argc, char **argv)
{
  int ret;

  ret = acTimerModuleStart(argc, argv);
  if ( ret < 0 )
  {
    return ret;
  }
  if ( RegisterLibraryEntries(&_exp_actimer) != 0 )
    return -16;
  return 0;
}

// timer.o

int acTimerAdd(acTimerT timer, acTimerDone done, void *arg, unsigned int us)
{
  acQueueT q_prev;
  iop_sys_clock_t t;
  acSpl state;

  if ( !Timerc.tick )
    return -6;
  if ( timer == 0 )
  {
    return -22;
  }
  if ( done == 0 )
  {
    return -22;
  }
  timer->t_done = done;
  timer->t_arg = arg;
  USec2SysClock(us, &t);
  timer->t_deadline = t.lo | ((acUint64)(t.hi) << 32);
  GetSystemTime(&t);
  timer->t_deadline += t.lo | ((acUint64)(t.hi) << 32);
  CpuSuspendIntr(&state);
  q_prev = Timerc.waitq.q_prev;
  timer->t_chain.q_next = (acQueueT)&Timerc;
  timer->t_chain.q_prev = q_prev;
  q_prev->q_next = &timer->t_chain;
  Timerc.waitq.q_prev = &timer->t_chain;
  CpuResumeIntr(state);
  return 0;
}

int acTimerRemove(acTimerT timer)
{
  acQueueT _next_;
  acQueueT _prev_;
  acSpl state;

  if ( !Timerc.tick )
    return -6;
  if ( timer == 0 )
  {
    return -22;
  }
  CpuSuspendIntr(&state);
  if ( timer->t_deadline )
  {
    _next_ = timer->t_chain.q_next;
    _prev_ = timer->t_chain.q_prev;
    _prev_->q_next = _next_;
    _next_->q_prev = _prev_;
  }
  CpuResumeIntr(state);
  return 0;
}

static unsigned int timer_handler(void *arg)
{
  acTime current;
  acTimerT timer;
  acTimerData *q_next;
  acQueueT q_prev;
  acTimerDone t_done;
  void *t_arg;
  iop_sys_clock_t v9;
  struct timer_softc *argt;

  argt = (struct timer_softc *)arg;
  GetSystemTime(&v9);
  memcpy(&current, &v9, sizeof(v9));
  if ( argt->tick == 0 )
  {
    return 0;
  }
  timer = (acTimerT)argt->waitq.q_next;
  while ( argt != (struct timer_softc *)timer )
  {
    q_next = (acTimerData *)timer->t_chain.q_next;
    if ( current >= timer->t_deadline )
    {
      q_prev = timer->t_chain.q_prev;
      q_prev->q_next = &q_next->t_chain;
      q_next->t_chain.q_prev = q_prev;
      t_done = timer->t_done;
      t_arg = timer->t_arg;
      timer->t_deadline = 0LL;
      t_done(timer, t_arg);
    }
    timer = q_next;
  }
  return argt->tick;
}

int acTimerModuleStart(int argc, char **argv)
{
  int tick;
  int v5;
  int v6;
  iop_sys_clock_t t;
  char *next;

  tick = 1000000;
  if ( Timerc.tick )
    return -16;
  if ( argc >= 2 )
  {
    tick = strtol(argv[1], &next, 10);
    if ( next == argv[1] )
    {
      tick = 1000000;
    }
    else if ( tick < 1000 )
    {
      tick = 1000;
    }
  }
  Timerc.tick = 0LL;
  Timerc.waitq.q_prev = (acQueueT)&Timerc;
  Timerc.waitq.q_next = (acQueueT)&Timerc;
  USec2SysClock(tick, &t);
  v5 = SetAlarm(&t, timer_handler, &Timerc);
  if ( v5 == -400 )
    return -12;
  v6 = 0;
  if ( v5 == -104 )
  {
    CancelAlarm(timer_handler, &Timerc);
    SetAlarm(&t, timer_handler, &Timerc);
    v6 = 0;
  }
  memcpy(&(Timerc.tick), &t, sizeof(t));
  return v6;
}

int acTimerModuleStop()
{
  if ( Timerc.tick )
  {
    CancelAlarm(timer_handler, &Timerc);
    Timerc.tick = 0LL;
  }
  return 0;
}

int acTimerModuleRestart(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  return -88;
}

int acTimerModuleStatus()
{
  return Timerc.tick != 0;
}
