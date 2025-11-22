
#include "irx_imports.h"

IRX_ID("rmreset", 1, 1);

#include <iop_mmio_hwport.h>

void sio2_ctrl_set(u32 val)
{
  USE_IOP_MMIO_HWPORT();

  iop_mmio_hwport->sio2.ctrl = val;
}

u32 sio2_ctrl_get(void)
{
  USE_IOP_MMIO_HWPORT();

  return iop_mmio_hwport->sio2.ctrl;
}

u32 sio2_stat6c_get(void)
{
  USE_IOP_MMIO_HWPORT();

  return iop_mmio_hwport->sio2.recv1;
}

void sio2_portN_ctrl1_set(int N, u32 val)
{
  USE_IOP_MMIO_HWPORT();

  iop_mmio_hwport->sio2.send1_2_buf[N * 2] = val;
}

// Ununsed func removed

void sio2_portN_ctrl2_set(int N, u32 val)
{
  USE_IOP_MMIO_HWPORT();

  iop_mmio_hwport->sio2.send1_2_buf[(N * 2) + 1] = val;
}

// Ununsed func removed

// Ununsed func removed

void sio2_regN_set(int N, u32 val)
{
  USE_IOP_MMIO_HWPORT();

  iop_mmio_hwport->sio2.send3_buf[N] = val;
}

// Ununsed func removed

// Ununsed func removed

// Ununsed func removed

// Ununsed func removed

// Ununsed func removed

// Ununsed func removed

void sio2_data_out(u8 val)
{
  USE_IOP_MMIO_HWPORT();

  iop_mmio_hwport->sio2.out_fifo = val;
}

u8 sio2_data_in(void)
{
  USE_IOP_MMIO_HWPORT();

  return iop_mmio_hwport->sio2.in_fifo;
}

// Ununsed func removed

// Ununsed func removed

int _start(int ac, char **av)
{
  u32 ctrl_save; // $s3
  int i; // $s0
  char inoutbuf[32]; // [sp+10h] [-20h] BYREF

  (void)ac;
  (void)av;

  printf("rmreset start\n");
  ctrl_save = sio2_ctrl_get();
  sio2_ctrl_set(0xCu);
  for ( i = 0; i < 4; i += 1 )
  {
    sio2_portN_ctrl1_set(i, 0xC0C0050F);
    sio2_portN_ctrl2_set(i, 0x1060014u);
  }
  sio2_regN_set(0, 0x1C0740u);
  sio2_regN_set(1, 0);
  inoutbuf[0] = 0x61;
  inoutbuf[1] = 6;
  inoutbuf[2] = 3;
  for ( i = 3; i < 12; i += 1 )
    inoutbuf[i] = 0;
  for ( i = 0; i < 7; i += 1 )
    sio2_data_out(inoutbuf[i]);
  sio2_ctrl_set(0xB1u);
  while ( !((sio2_stat6c_get() >> 12) & 1) );
  for ( i = 0; i < 7; i += 1 )
    inoutbuf[i + 16] = sio2_data_in();
  sio2_ctrl_set(0xCu);
  for ( i = 0; i < 4; i += 1 )
  {
    sio2_portN_ctrl1_set(i, 0xC0C0050F);
    sio2_portN_ctrl2_set(i, 0x1060014u);
  }
  sio2_regN_set(0, 0x1C0741u);
  sio2_regN_set(1, 0);
  inoutbuf[0] = 0x61;
  inoutbuf[1] = 6;
  inoutbuf[2] = 3;
  for ( i = 3; i < 12; i += 1 )
    inoutbuf[i] = 0;
  for ( i = 0; i < 7; i += 1 )
    sio2_data_out(inoutbuf[i]);
  sio2_ctrl_set(0xB1u);
  while ( !((sio2_stat6c_get() >> 12) & 1) );
  for ( i = 0; i < 7; i += 1 )
    inoutbuf[i + 16] = sio2_data_in();
  sio2_ctrl_set(0xCu);
  sio2_ctrl_set(ctrl_save & 0xFFFFFFFE);
  printf("rmreset end\n");
  return 1;
}
