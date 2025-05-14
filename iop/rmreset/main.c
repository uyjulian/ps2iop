
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
  int idx1_2; // $s0
  int idx1_1; // $a0
  int iobind1; // $s0
  char *p_inbuf_1; // $v0
  int indobuf_1; // $s0
  char *p_outbuf_1; // $v0
  int i; // $s0
  int idx2_2; // $s0
  int idx2_1; // $a0
  int iobind2; // $s0
  char *p_inbuf_2; // $v0
  int indobuf_2; // $s0
  char *p_outbuf_2; // $v0
  int j; // $s0
  char inoutbuf[32]; // [sp+10h] [-20h] BYREF

  (void)ac;
  (void)av;

  printf("rmreset start\n");
  ctrl_save = sio2_ctrl_get();
  sio2_ctrl_set(0xCu);
  idx1_2 = 0;
  idx1_1 = 0;
  do
  {
    sio2_portN_ctrl1_set(idx1_1, 0xC0C0050F);
    sio2_portN_ctrl2_set(idx1_2++, 0x1060014u);
    idx1_1 = idx1_2;
  }
  while ( idx1_2 < 4 );
  sio2_regN_set(0, 0x1C0740u);
  sio2_regN_set(1, 0);
  iobind1 = 3;
  inoutbuf[0] = 0x61;
  inoutbuf[1] = 6;
  inoutbuf[2] = 3;
  p_inbuf_1 = &inoutbuf[3];
  do
  {
    *p_inbuf_1 = 0;
    p_inbuf_1 = &inoutbuf[++iobind1];
  }
  while ( iobind1 < 12 );
  indobuf_1 = 0;
  p_outbuf_1 = inoutbuf;
  do
  {
    ++indobuf_1;
    sio2_data_out(*p_outbuf_1);
    p_outbuf_1 = &inoutbuf[indobuf_1];
  }
  while ( indobuf_1 < 7 );
  sio2_ctrl_set(0xB1u);
  while ( ((sio2_stat6c_get() >> 12) & 1) == 0 )
    ;
  for ( i = 0; i < 7; ++i )
    inoutbuf[i + 16] = sio2_data_in();
  sio2_ctrl_set(0xCu);
  idx2_2 = 0;
  idx2_1 = 0;
  do
  {
    sio2_portN_ctrl1_set(idx2_1, 0xC0C0050F);
    sio2_portN_ctrl2_set(idx2_2++, 0x1060014u);
    idx2_1 = idx2_2;
  }
  while ( idx2_2 < 4 );
  sio2_regN_set(0, 0x1C0741u);
  sio2_regN_set(1, 0);
  iobind2 = 3;
  inoutbuf[0] = 0x61;
  inoutbuf[1] = 6;
  inoutbuf[2] = 3;
  p_inbuf_2 = &inoutbuf[3];
  do
  {
    *p_inbuf_2 = 0;
    p_inbuf_2 = &inoutbuf[++iobind2];
  }
  while ( iobind2 < 12 );
  indobuf_2 = 0;
  p_outbuf_2 = inoutbuf;
  do
  {
    ++indobuf_2;
    sio2_data_out(*p_outbuf_2);
    p_outbuf_2 = &inoutbuf[indobuf_2];
  }
  while ( indobuf_2 < 7 );
  sio2_ctrl_set(0xB1u);
  while ( ((sio2_stat6c_get() >> 12) & 1) == 0 )
    ;
  for ( j = 0; j < 7; ++j )
    inoutbuf[j + 16] = sio2_data_in();
  sio2_ctrl_set(0xCu);
  sio2_ctrl_set(ctrl_save & 0xFFFFFFFE);
  printf("rmreset end\n");
  return 1;
}
