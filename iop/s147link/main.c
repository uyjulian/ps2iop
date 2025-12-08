
#include "irx_imports.h"

IRX_ID("S147LINK", 2, 7);

#define __fastcall
#define __cdecl
#define _BYTE u8
#define _WORD u16
#define _DWORD u32
#define __int8 char
#define __int32 int

typedef unsigned int u_int;

struct s147link_dev9_mem_mmio_
{
  vu8 m_pad00;
  vu8 m_unk01;
  vu8 m_pad02;
  vu8 m_unk03;
  vu8 m_pad04;
  vu8 m_node_unk05;
  vu8 m_pad06;
  vu8 m_unk07;
  vu8 m_pad08;
  vu8 m_unk09;
  vu8 m_pad0A;
  vu8 m_pad0B;
  vu8 m_pad0C;
  vu8 m_unk0D;
  vu8 m_pad0E;
  vu8 m_pad0F;
  vu8 m_pad10;
  vu8 m_pad11;
  vu8 m_stsH_unk12;
  vu8 m_stsL_unk13;
  vu8 m_unk14;
  vu8 m_unk15;
  vu8 m_pad16;
  vu8 m_unk17;
  vu8 m_pad18;
  vu8 m_pad19;
  vu8 m_pad1A;
  vu8 m_pad1B;
  vu8 m_unk1C;
  vu8 m_unk1D;
  vu8 m_rxfc_hi_unk1E;
  vu8 m_rxfc_lo_unk1F;
  vu8 m_pad20;
  vu8 m_unk21;
  vu8 m_unk22;
  vu8 m_unk23;
  vu8 m_unk24;
  vu8 m_unk25;
  vu8 m_pad26;
  vu8 m_pad27;
  vu8 m_unk28;
  vu8 m_unk29;
  vu8 m_pad2A;
  vu8 m_maxnode_unk2B;
  vu8 m_pad2C;
  vu8 m_mynode_unk2D;
  vu8 m_pad2E;
  vu8 m_unk2F;
  vu8 m_pad30;
  vu8 m_unk31;
  vu8 m_pad32;
  vu8 m_pad33;
  vu8 m_watchdog_flag_unk34;
};

typedef struct __anon_struct_35
{
  unsigned int mynode;
  unsigned int maxnode;
  unsigned int nodemask;
  unsigned __int8 *R_top;
  unsigned int R_in;
  unsigned int R_out;
  unsigned int R_remain;
  unsigned __int8 R_number[16];
  unsigned int R_lost[16];
  unsigned int R_pd[16];
  unsigned int R_count;
  unsigned __int8 *T_top;
  unsigned int T_in;
  unsigned int T_out;
  unsigned int T_remain;
  unsigned int T_node;
  int T_error[16];
  unsigned int T_pd[16];
  unsigned int T_time[16];
  unsigned __int8 T_number;
  unsigned int timeout;
  unsigned int online;
  unsigned int ontimer;
  unsigned int offtimer;
  unsigned int rbfix;
  iop_sys_clock_t sys_clock;
} CL_COM;


//-------------------------------------------------------------------------
// Function declarations

int __fastcall _start(int argc, char **argv);
void __fastcall T_fix(CL_COM *io_pCommon);
int __fastcall clink_InterruptHandler(CL_COM *io_pCommon);
int __fastcall cl_mread(void *dstptr, int count);
int __fastcall cl_write(int node, unsigned __int8 *srcptr, int size);
int __fastcall cl_write_custom(int node, unsigned __int8 *srcptr, int cpVal);
int __fastcall cl_mwrite(unsigned __int8 *srcptr, int count);
int __fastcall InitS147link(int maxnode, int mynode, int priority);
void __fastcall reset_circlink();
u_int __fastcall alarm_handler(CL_COM *io_pCommon);
int __fastcall s147link_loop();
void *__fastcall dispatch(unsigned int fno, void *buf, int size);

//-------------------------------------------------------------------------
// Data declarations

int gbBRE;
unsigned __int8 rpc_buf[32784];
unsigned __int8 rx_buff[512][64];
unsigned __int8 tx_buff[256][64];
CL_COM cl_info;
struct s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio; // weak


//----- (00400000) --------------------------------------------------------
int __fastcall _start(int argc, char **argv)
{
  int maxnode; // [sp+10h] [+10h]
  int mynode; // [sp+14h] [+14h]
  int priority; // [sp+18h] [+18h]

  if ( argc >= 2 )
    maxnode = strtol(argv[1], 0, 10);
  if ( maxnode < 2 || maxnode >= 16 )
    maxnode = 2;
  if ( argc >= 3 )
    mynode = strtol(argv[2], 0, 10);
  if ( mynode <= 0 || maxnode < mynode )
    mynode = 1;
  if ( argc >= 4 )
    priority = strtol(argv[3], 0, 10);
  if ( priority < 9 || priority >= 124 )
    priority = 28;
  gbBRE = 1;
  if ( argc >= 5 && toupper(*argv[4]) == 'N' && toupper(argv[4][1]) == 'B' && toupper(argv[4][2]) == 'R' )
    gbBRE = 0;
  printf("== S147LINK (%d/%d)@%d ", mynode, maxnode, priority);
  if ( !gbBRE )
    printf("NBR ");
  printf("v2.07 ==\n");
  if ( !InitS147link(maxnode, mynode, priority) )
    return 0;
  printf("S147LINK: Can't Initialize driver thread.\n");
  return 1;
}
// 40005C: variable 'maxnode' is possibly undefined
// 4000C8: variable 'mynode' is possibly undefined
// 40013C: variable 'priority' is possibly undefined

//----- (00400300) --------------------------------------------------------
void __fastcall T_fix(CL_COM *io_pCommon)
{
  if ( io_pCommon->T_remain >= 0x101 )
  {
    io_pCommon->T_remain = 0x100;
    io_pCommon->T_out = 0;
    io_pCommon->T_in = io_pCommon->T_out;
    if ( !++io_pCommon->rbfix )
      --io_pCommon->rbfix;
  }
  if ( io_pCommon->T_remain == 0x100 && io_pCommon->T_in != io_pCommon->T_out )
  {
    io_pCommon->T_out = 0;
    io_pCommon->T_in = io_pCommon->T_out;
    if ( !++io_pCommon->rbfix )
      --io_pCommon->rbfix;
  }
}

//----- (00400458) --------------------------------------------------------
int __fastcall clink_InterruptHandler(CL_COM *io_pCommon)
{
  unsigned __int8 m_stsH_unk12; // $v0
  unsigned __int8 m_stsL_unk13; // $v0
  vu8 m_unk03; // $v0
  vu8 m_unk01; // $v0
  vu8 m_rxfc_hi_unk1E; // $v0
  vu8 m_rxfc_lo_unk1F; // $v1
  vu8 m_unk09; // $v0
  vu8 v8; // $v0
  unsigned __int8 v10; // $v0
  unsigned __int8 v11; // $v0
  unsigned __int8 *bufptr; // $s4
  unsigned __int8 *bufptr_v1; // $s4
  vu8 v14; // $v0
  vu8 v15; // $v0
  vu8 v16; // $v0
  unsigned __int8 *bufptr_v2; // $s4
  vu8 v18; // $v0
  vu8 v19; // $v0
  vu8 v20; // $v0
  vu8 v21; // $v0
  vu8 v22; // $v0
  unsigned __int8 v23; // $v0
  vu8 v24; // $v0
  unsigned __int8 *bufptr_v3; // $s4
  unsigned int i_v4; // [sp+10h] [+10h]
  unsigned int i_v5; // [sp+10h] [+10h]
  unsigned int j_v6; // [sp+14h] [+14h]
  unsigned int k_v7; // [sp+18h] [+18h]
  unsigned __int8 stsH; // [sp+1Ch] [+1Ch]
  unsigned __int8 stsL; // [sp+1Dh] [+1Dh]
  unsigned __int8 rnum; // [sp+1Eh] [+1Eh]
  unsigned int rxfs; // [sp+20h] [+20h]
  unsigned int rxfc; // [sp+24h] [+24h]
  unsigned int tflag; // [sp+28h] [+28h]
  int state; // [sp+2Ch] [+2Ch] BYREF

  m_stsH_unk12 = s147link_dev9_mem_mmio.m_stsH_unk12;
  stsH = m_stsH_unk12;
  m_stsL_unk13 = s147link_dev9_mem_mmio.m_stsL_unk13;
  stsL = m_stsL_unk13;
  if ( (m_stsL_unk13 & 8) != 0 )
  {
    m_unk03 = s147link_dev9_mem_mmio.m_unk03;
    if ( (m_unk03 & 8) != 0 )
    {
      s147link_dev9_mem_mmio.m_unk17 = 1;
      s147link_dev9_mem_mmio.m_unk17 = 0xE;
    }
    m_unk01 = s147link_dev9_mem_mmio.m_unk01;
    if ( (m_unk01 & 4) != 0 )
    {
      s147link_dev9_mem_mmio.m_unk17 = 0x16;
      if ( !io_pCommon->ontimer )
        io_pCommon->offtimer = 1;
      io_pCommon->ontimer = 1;
    }
  }
  rxfc = 0;
  m_rxfc_hi_unk1E = s147link_dev9_mem_mmio.m_rxfc_hi_unk1E;
  m_rxfc_lo_unk1F = s147link_dev9_mem_mmio.m_rxfc_lo_unk1F;
  rxfs = ((m_rxfc_hi_unk1E << 8) | m_rxfc_lo_unk1F) & io_pCommon->nodemask;
  if ( rxfs )
  {
    i_v4 = 2;
    for ( j_v6 = 1; io_pCommon->maxnode >= j_v6; ++j_v6 )
    {
      if ( j_v6 == io_pCommon->mynode )
      {
        rxfc |= i_v4;
      }
      else if ( (rxfs & i_v4) != 0 )
      {
        s147link_dev9_mem_mmio.m_node_unk05 = j_v6 | 0xC0;
        s147link_dev9_mem_mmio.m_unk07 = 0;
        m_unk09 = s147link_dev9_mem_mmio.m_unk09;
        if ( m_unk09 == io_pCommon->mynode )
        {
          v8 = s147link_dev9_mem_mmio.m_unk09;
          if ( v8 == 4 )
          {
            if ( s147link_dev9_mem_mmio.m_unk09 )
            {
              rxfc |= i_v4;
            }
            else
            {
              v10 = s147link_dev9_mem_mmio.m_unk09;
              rnum = v10;
              if ( io_pCommon->R_number[j_v6] == v10 )
              {
                rxfc |= i_v4;
              }
              else
              {
                v11 = s147link_dev9_mem_mmio.m_unk09;
                if ( io_pCommon->R_remain )
                {
                  bufptr = &io_pCommon->R_top[0x40 * io_pCommon->R_in];
                  *bufptr++ = j_v6;
                  *bufptr++ = io_pCommon->mynode;
                  *bufptr++ = 4;
                  *bufptr++ = 0;
                  *bufptr++ = rnum;
                  *bufptr = v11;
                  bufptr_v1 = bufptr + 1;
                  for ( k_v7 = 0; k_v7 < 0x3A; ++k_v7 )
                  {
                    v14 = s147link_dev9_mem_mmio.m_unk09;
                    *bufptr_v1++ = v14;
                  }
                  --io_pCommon->R_remain;
                  ++io_pCommon->R_in;
                  io_pCommon->R_in &= 0x1FFu;
                  io_pCommon->R_number[j_v6] = rnum;
                  rxfc |= i_v4;
                }
                else if ( io_pCommon->R_pd[j_v6] )
                {
                  rxfc |= i_v4;
                  if ( !++io_pCommon->R_lost[j_v6] )
                    ++io_pCommon->R_lost[j_v6];
                }
              }
            }
          }
          else
          {
            rxfc |= i_v4;
          }
        }
        else if ( m_unk09 )
        {
          rxfc |= i_v4;
        }
        else
        {
          v15 = s147link_dev9_mem_mmio.m_unk09;
          if ( v15 == 0x38 )
          {
            s147link_dev9_mem_mmio.m_node_unk05 = j_v6 | 0xC0;
            s147link_dev9_mem_mmio.m_unk07 = 0x38;
            v16 = s147link_dev9_mem_mmio.m_unk09;
            if ( (v16 & 0xE0) == 0x20 || (v16 & 0xE0) == 0x60 )
            {
              if ( io_pCommon->R_remain )
              {
                bufptr_v2 = &io_pCommon->R_top[0x40 * io_pCommon->R_in];
                *bufptr_v2++ = j_v6;
                *bufptr_v2++ = 0;
                *bufptr_v2 = 56;
                bufptr_v2 += 54;
                *bufptr_v2++ = v16;
                v18 = s147link_dev9_mem_mmio.m_unk09;
                *bufptr_v2++ = v18;
                v19 = s147link_dev9_mem_mmio.m_unk09;
                *bufptr_v2++ = v19;
                v20 = s147link_dev9_mem_mmio.m_unk09;
                *bufptr_v2++ = v20;
                v21 = s147link_dev9_mem_mmio.m_unk09;
                *bufptr_v2++ = v21;
                v22 = s147link_dev9_mem_mmio.m_unk09;
                *bufptr_v2++ = v22;
                v23 = s147link_dev9_mem_mmio.m_unk09;
                *bufptr_v2 = v23;
                v24 = s147link_dev9_mem_mmio.m_unk09;
                bufptr_v2[1] = v24;
                --io_pCommon->R_remain;
                ++io_pCommon->R_in;
                io_pCommon->R_in &= 0x1FFu;
                rxfc |= i_v4;
              }
              else if ( io_pCommon->R_pd[j_v6] )
              {
                rxfc |= i_v4;
                if ( !++io_pCommon->R_lost[j_v6] )
                  ++io_pCommon->R_lost[j_v6];
              }
            }
            else
            {
              rxfc |= i_v4;
            }
          }
          else
          {
            rxfc |= i_v4;
          }
        }
      }
      i_v4 *= 2;
    }
  }
  tflag = 0;
  if ( (stsL & 0x10) != 0 )
  {
    s147link_dev9_mem_mmio.m_unk17 = 1;
    s147link_dev9_mem_mmio.m_unk17 = 0xE;
  }
  if ( (stsL & 2) != 0 && (stsL & 4) == 0 && io_pCommon->timeout )
  {
    tflag = 1;
  }
  else if ( (stsL & 1) != 0 )
  {
    io_pCommon->timeout = 0;
    while ( 1 )
    {
      if ( io_pCommon->T_remain == 0x100 )
      {
        s147link_dev9_mem_mmio.m_unk15 = 0x1A;
        goto LABEL_62;
      }
      bufptr_v3 = &io_pCommon->T_top[0x40 * io_pCommon->T_out];
      if ( *bufptr_v3 == io_pCommon->mynode )
      {
        io_pCommon->T_node = bufptr_v3[1];
        if ( !io_pCommon->T_error[io_pCommon->T_node] || !io_pCommon->T_pd[io_pCommon->T_node] )
          break;
      }
      ++io_pCommon->T_remain;
      ++io_pCommon->T_out;
      io_pCommon->T_out = (unsigned __int8)io_pCommon->T_out;
      T_fix(io_pCommon);
    }
    s147link_dev9_mem_mmio.m_node_unk05 = (io_pCommon->mynode & 0xFF) | 0x40;
    s147link_dev9_mem_mmio.m_unk07 = 0;
    for ( i_v5 = 0; i_v5 < 0x40; ++i_v5 )
      s147link_dev9_mem_mmio.m_unk09 = *bufptr_v3++;
    ++io_pCommon->T_remain;
    ++io_pCommon->T_out;
    io_pCommon->T_out = (unsigned __int8)io_pCommon->T_out;
    T_fix(io_pCommon);
    s147link_dev9_mem_mmio.m_unk15 = 0x1B;
    tflag = 1;
    io_pCommon->timeout = 1;
  }
LABEL_62:
  CpuSuspendIntr(&state);
  if ( tflag )
    s147link_dev9_mem_mmio.m_unk17 = 3;
  if ( rxfc )
  {
    s147link_dev9_mem_mmio.m_rxfc_hi_unk1E = (rxfc >> 8) & 0xFF;
    s147link_dev9_mem_mmio.m_rxfc_lo_unk1F = rxfc;
  }
  s147link_dev9_mem_mmio.m_stsH_unk12 = stsH;
  s147link_dev9_mem_mmio.m_stsL_unk13 = stsL;
  CpuResumeIntr(state);
  return 1;
}
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (00401520) --------------------------------------------------------
int __fastcall cl_mread(void *dstptr, int count)
{
  int state; // [sp+10h] [+10h] BYREF
  size_t size; // [sp+14h] [+14h]
  int packs1; // [sp+18h] [+18h]

  CpuSuspendIntr(&state);
  size = 0x200 - cl_info.R_remain;
  if ( cl_info.R_remain == 0x200 )
  {
    CpuResumeIntr(state);
    return 0;
  }
  else
  {
    if ( count >= (int)size )
      count = size;
    else
      size = count;
    packs1 = cl_info.R_out + size - 0x200;
    if ( packs1 > 0 )
    {
      size -= packs1;
      size <<= 6;
      memcpy(dstptr, rx_buff[cl_info.R_out], size);
      memcpy((char *)dstptr + size, rx_buff, packs1 << 6);
    }
    else
    {
      memcpy(dstptr, rx_buff[cl_info.R_out], size << 6);
    }
    cl_info.R_remain += count;
    cl_info.R_out += count;
    cl_info.R_out = cl_info.R_out & 0x1FF;
    if ( cl_info.R_remain >= 0x201 )
    {
      cl_info.R_remain = 0x200;
      cl_info.R_out = 0;
      cl_info.R_in = 0;
      if ( !++cl_info.rbfix )
        --cl_info.rbfix;
      count = 0;
    }
    if ( cl_info.R_remain == 512 && cl_info.R_in != cl_info.R_out )
    {
      cl_info.R_out = 0;
      cl_info.R_in = 0;
      if ( !++cl_info.rbfix )
        --cl_info.rbfix;
      count = 0;
    }
    CpuResumeIntr(state);
    return count;
  }
}

//----- (00401864) --------------------------------------------------------
int __fastcall cl_write(int node, unsigned __int8 *srcptr, int size)
{
  int state; // [sp+10h] [+10h] BYREF
  unsigned __int8 node_tmp; // [sp+20h] [+20h]

  node_tmp = node;
  CpuSuspendIntr(&state);
  if ( cl_info.T_remain && size < 0x41 )
  {
    memcpy(tx_buff[cl_info.T_in], srcptr, size);
    tx_buff[cl_info.T_in][0] = cl_info.mynode;
    tx_buff[cl_info.T_in][1] = node_tmp;
    tx_buff[cl_info.T_in][2] = 4;
    tx_buff[cl_info.T_in][3] = 0;
    tx_buff[cl_info.T_in][4] = ++cl_info.T_number;
    --cl_info.T_remain;
    ++cl_info.T_in;
    cl_info.T_in = (cl_info.T_in & 0xFF);
    s147link_dev9_mem_mmio.m_unk15 = 0x1B;
    clink_InterruptHandler(&cl_info);
    CpuResumeIntr(state);
    return size;
  }
  else
  {
    CpuResumeIntr(state);
    return 0;
  }
}
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (00401A84) --------------------------------------------------------
int __fastcall cl_write_custom(int node, unsigned __int8 *srcptr, int cpVal)
{
  int state; // [sp+10h] [+10h] BYREF
  unsigned __int8 node_tmp; // [sp+20h] [+20h]
  unsigned __int8 cpVal_tmp; // [sp+28h] [+28h]

  node_tmp = node;
  cpVal_tmp = cpVal;
  CpuSuspendIntr(&state);
  if ( cl_info.T_remain )
  {
    memcpy(tx_buff[cl_info.T_in], srcptr, sizeof(unsigned __int8[64]));
    tx_buff[cl_info.T_in][0] = cl_info.mynode;
    tx_buff[cl_info.T_in][1] = node_tmp;
    tx_buff[cl_info.T_in][2] = cpVal_tmp;
    --cl_info.T_remain;
    ++cl_info.T_in;
    cl_info.T_in = (cl_info.T_in & 0xFF);
    s147link_dev9_mem_mmio.m_unk15 = 0x1B;
    clink_InterruptHandler(&cl_info);
    CpuResumeIntr(state);
    return 64;
  }
  else
  {
    CpuResumeIntr(state);
    return 0;
  }
}
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (00401C10) --------------------------------------------------------
int __fastcall cl_mwrite(unsigned __int8 *srcptr, int count)
{
  int state; // [sp+10h] [+10h] BYREF
  int i; // [sp+14h] [+14h]
  int j; // [sp+18h] [+18h]
  int packs0; // [sp+1Ch] [+1Ch]
  int packs1; // [sp+20h] [+20h]

  if ( cl_info.T_remain < count )
    return 0;
  if ( count >= 0x101 )
    return 0;
  j = 0;
  i = 0;
  while ( i < count )
  {
    srcptr[j] = cl_info.mynode;
    srcptr[j + 2] = 4;
    srcptr[j + 3] = 0;
    srcptr[j + 4] = ++cl_info.T_number;
    ++i;
    j += 0x40;
  }
  CpuSuspendIntr(&state);
  if ( cl_info.T_remain >= count )
  {
    packs1 = cl_info.T_in + count - 0x100;
    if ( packs1 > 0 )
    {
      packs0 = count - packs1;
      memcpy(tx_buff[cl_info.T_in], srcptr, (count - packs1) << 6);
      memcpy(tx_buff, &srcptr[0x40 * packs0], packs1 << 6);
    }
    else
    {
      memcpy(tx_buff[cl_info.T_in], srcptr, count << 6);
    }
    cl_info.T_remain -= count;
    cl_info.T_in += count;
    cl_info.T_in = (cl_info.T_in & 0xFF);
    s147link_dev9_mem_mmio.m_unk15 = 0x1B;
    clink_InterruptHandler(&cl_info);
    CpuResumeIntr(state);
    return count;
  }
  else
  {
    CpuResumeIntr(state);
    return 0;
  }
}
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (00401F3C) --------------------------------------------------------
int __fastcall InitS147link(int maxnode, int mynode, int priority)
{
  vu8 m_unk0D; // $v0
  vu8 v4; // $v0
  vu8 m_unk22; // $v0
  int i_tmp1; // $v0
  int i_tmp2; // $v0
  unsigned int *cl_info_tmp; // $v1
  unsigned __int8 m_stsH_unk12; // $v0
  unsigned __int8 m_stsL_unk13; // $v0
  iop_thread_t param; // [sp+10h] [+10h] BYREF
  int thid; // [sp+28h] [+28h]
  int i; // [sp+2Ch] [+2Ch]
  int j; // [sp+30h] [+30h]
  int state; // [sp+34h] [+34h] BYREF
  unsigned __int8 stsH; // [sp+38h] [+38h]
  unsigned __int8 stsL; // [sp+39h] [+39h]
  unsigned __int8 cTmp; // [sp+3Ah] [+3Ah]

  m_unk0D = s147link_dev9_mem_mmio.m_unk0D;
  cTmp = m_unk0D | 0x80;
  s147link_dev9_mem_mmio.m_unk0D = m_unk0D | 0x80;
  s147link_dev9_mem_mmio.m_unk22 = 2;
  if ( gbBRE )
    s147link_dev9_mem_mmio.m_unk23 = 0x51;
  else
    s147link_dev9_mem_mmio.m_unk23 = 0x11;
  s147link_dev9_mem_mmio.m_maxnode_unk2B = maxnode;
  s147link_dev9_mem_mmio.m_mynode_unk2D = mynode;
  s147link_dev9_mem_mmio.m_unk31 = 0;
  s147link_dev9_mem_mmio.m_unk2F = 2;
  for ( i = 0; i < 4; ++i )
  {
    s147link_dev9_mem_mmio.m_node_unk05 = i | 0x40;
    s147link_dev9_mem_mmio.m_unk07 = 0;
    for ( j = 0; j < 256; ++j )
      s147link_dev9_mem_mmio.m_unk09 = 0;
  }
  s147link_dev9_mem_mmio.m_unk28 = 0;
  s147link_dev9_mem_mmio.m_unk29 = 0;
  s147link_dev9_mem_mmio.m_unk21 = 0;
  s147link_dev9_mem_mmio.m_unk24 = 0;
  s147link_dev9_mem_mmio.m_unk25 = 0xFF;
  v4 = s147link_dev9_mem_mmio.m_unk0D;
  s147link_dev9_mem_mmio.m_unk0D = v4 & 0x7F;
  m_unk22 = s147link_dev9_mem_mmio.m_unk22;
  cTmp = m_unk22 | 1;
  s147link_dev9_mem_mmio.m_unk22 = m_unk22 | 1;
  s147link_dev9_mem_mmio.m_node_unk05 = mynode | 0x40;
  s147link_dev9_mem_mmio.m_unk07 = 0;
  s147link_dev9_mem_mmio.m_unk09 = mynode;
  s147link_dev9_mem_mmio.m_unk09 = 2;
  s147link_dev9_mem_mmio.m_unk09 = 4;
  cl_info.mynode = mynode;
  cl_info.maxnode = maxnode;
  i = 0;
  j = 1;
  while ( i < maxnode )
  {
    j = (2 * j) | 1;
    ++i;
  }
  cl_info.nodemask = j;
  cl_info.R_top = rx_buff[0];
  cl_info.R_remain = 0x200;
  cl_info.R_out = 0;
  cl_info.R_in = 0;
  for ( i = 0; i < 16; ++i )
  {
    cl_info.R_number[i] = 0;
    i_tmp1 = i;
    cl_info.T_error[i] = 0;
    cl_info.R_lost[i_tmp1] = 0;
    i_tmp2 = i;
    cl_info_tmp = &cl_info.mynode + i;
    cl_info_tmp[65] = 1;
    cl_info.R_pd[i_tmp2] = cl_info_tmp[65];
    cl_info.T_time[i] = 2;
  }
  cl_info.T_top = tx_buff[0];
  cl_info.T_remain = 0x100;
  cl_info.offtimer = 0;
  cl_info.ontimer = 0;
  cl_info.online = 0;
  cl_info.timeout = 0;
  cl_info.T_out = 0;
  cl_info.T_in = 0;
  cl_info.T_number = 0;
  cl_info.T_node = 2;
  cl_info.rbfix = 0;
  CpuSuspendIntr(&state);
  ReleaseIntrHandler(13);
  RegisterIntrHandler(13, 1, (int (__fastcall *)(void *))clink_InterruptHandler, &cl_info);
  s147link_dev9_mem_mmio.m_unk01 = 0xC;
  s147link_dev9_mem_mmio.m_unk14 = 0x8E;
  s147link_dev9_mem_mmio.m_unk15 = 0x1A;
  s147link_dev9_mem_mmio.m_unk1C = 0xFF;
  s147link_dev9_mem_mmio.m_unk1D = 0xFF;
  s147link_dev9_mem_mmio.m_rxfc_hi_unk1E = 0xFF;
  s147link_dev9_mem_mmio.m_rxfc_lo_unk1F = 0xFF;
  m_stsH_unk12 = s147link_dev9_mem_mmio.m_stsH_unk12;
  stsH = m_stsH_unk12;
  m_stsL_unk13 = s147link_dev9_mem_mmio.m_stsL_unk13;
  stsL = m_stsL_unk13;
  s147link_dev9_mem_mmio.m_stsH_unk12 = stsH;
  s147link_dev9_mem_mmio.m_stsL_unk13 = m_stsL_unk13;
  CpuResumeIntr(state);
  EnableIntr(13);
  sceSifInitRpc(0);
  param.attr = 0x2000000;
  param.thread = (void (__fastcall *)(void *))s147link_loop;
  param.priority = priority;
  param.stacksize = 0x800;
  param.option = 0;
  thid = CreateThread(&param);
  if ( thid > 0 )
  {
    if ( StartThread(thid, 0) )
    {
      printf("S147LINK: Cannot start RPC server thread ...\n");
      DeleteThread(thid);
      return -2;
    }
    else
    {
      USec2SysClock(0x7D0u, &cl_info.sys_clock);
      if ( SetAlarm(&cl_info.sys_clock, (unsigned int (__fastcall *)(void *))alarm_handler, &cl_info) )
      {
        printf("S147LINK: Cannot set alarm handler ...\n");
        DeleteThread(thid);
        return -3;
      }
      else
      {
        return 0;
      }
    }
  }
  else
  {
    printf("S147LINK: Cannot create RPC server thread ...\n");
    return -1;
  }
}
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (0040281C) --------------------------------------------------------
void __fastcall reset_circlink()
{
  vu8 m_unk0D; // $v0
  vu8 v1; // $v0
  vu8 m_unk22; // $v0
  vu8 m_stsH_unk12; // $v0
  vu8 m_stsL_unk13; // $v0
  int i; // [sp+0h] [+0h]
  int j; // [sp+4h] [+4h]
  vu8 v7; // [sp+8h] [+8h]

  m_unk0D = s147link_dev9_mem_mmio.m_unk0D;
  s147link_dev9_mem_mmio.m_unk0D = m_unk0D | 0x80;
  s147link_dev9_mem_mmio.m_unk22 = 2;
  if ( gbBRE )
    s147link_dev9_mem_mmio.m_unk23 = 0x51;
  else
    s147link_dev9_mem_mmio.m_unk23 = 0x11;
  s147link_dev9_mem_mmio.m_maxnode_unk2B = cl_info.maxnode;
  s147link_dev9_mem_mmio.m_mynode_unk2D = cl_info.mynode;
  s147link_dev9_mem_mmio.m_unk31 = 0;
  s147link_dev9_mem_mmio.m_unk2F = 2;
  for ( i = 0; i < 4; ++i )
  {
    s147link_dev9_mem_mmio.m_node_unk05 = i | 0x40;
    s147link_dev9_mem_mmio.m_unk07 = 0;
    for ( j = 0; j < 256; ++j )
      s147link_dev9_mem_mmio.m_unk09 = 0;
  }
  s147link_dev9_mem_mmio.m_unk28 = 0;
  s147link_dev9_mem_mmio.m_unk29 = 0;
  s147link_dev9_mem_mmio.m_unk21 = 0;
  s147link_dev9_mem_mmio.m_unk24 = 0;
  s147link_dev9_mem_mmio.m_unk25 = 0xFF;
  v1 = s147link_dev9_mem_mmio.m_unk0D;
  s147link_dev9_mem_mmio.m_unk0D = v1 & 0x7F;
  m_unk22 = s147link_dev9_mem_mmio.m_unk22;
  s147link_dev9_mem_mmio.m_unk22 = m_unk22 | 1;
  s147link_dev9_mem_mmio.m_node_unk05 = (cl_info.mynode & 0xFF) | 0x40;
  s147link_dev9_mem_mmio.m_unk07 = 0;
  s147link_dev9_mem_mmio.m_unk09 = cl_info.mynode;
  s147link_dev9_mem_mmio.m_unk09 = 2;
  s147link_dev9_mem_mmio.m_unk09 = 4;
  s147link_dev9_mem_mmio.m_unk01 = 0xC;
  s147link_dev9_mem_mmio.m_unk14 = 0x8E;
  s147link_dev9_mem_mmio.m_unk15 = 0x1A;
  s147link_dev9_mem_mmio.m_unk1C = 0xFF;
  s147link_dev9_mem_mmio.m_unk1D = 0xFF;
  s147link_dev9_mem_mmio.m_rxfc_hi_unk1E = 0xFF;
  s147link_dev9_mem_mmio.m_rxfc_lo_unk1F = 0xFF;
  m_stsH_unk12 = s147link_dev9_mem_mmio.m_stsH_unk12;
  v7 = m_stsH_unk12;
  m_stsL_unk13 = s147link_dev9_mem_mmio.m_stsL_unk13;
  s147link_dev9_mem_mmio.m_stsH_unk12 = v7;
  s147link_dev9_mem_mmio.m_stsL_unk13 = m_stsL_unk13;
}
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (00402D58) --------------------------------------------------------
u_int __fastcall alarm_handler(CL_COM *io_pCommon)
{
  unsigned __int8 m_stsL_unk13; // $v0
  int state; // [sp+10h] [+10h] BYREF
  unsigned __int8 stsL; // [sp+14h] [+14h]

  if ( io_pCommon->timeout )
  {
    if ( io_pCommon->T_time[io_pCommon->T_node] )
    {
      if ( io_pCommon->T_time[io_pCommon->T_node] >= io_pCommon->timeout )
      {
        ++io_pCommon->timeout;
      }
      else
      {
        CpuSuspendIntr(&state);
        m_stsL_unk13 = s147link_dev9_mem_mmio.m_stsL_unk13;
        stsL = m_stsL_unk13;
        io_pCommon->timeout = 0;
        s147link_dev9_mem_mmio.m_unk17 = 1;
        s147link_dev9_mem_mmio.m_unk17 = 0xE;
        cl_info.T_error[cl_info.T_node] = 0xFFFFFFFE;
        s147link_dev9_mem_mmio.m_unk15 = 0x1B;
        clink_InterruptHandler(&cl_info);
        CpuResumeIntr(state);
      }
    }
    else
    {
      io_pCommon->timeout = 0;
    }
  }
  if ( io_pCommon->ontimer )
  {
    if ( io_pCommon->ontimer < 0xFA )
    {
      ++io_pCommon->ontimer;
    }
    else
    {
      io_pCommon->online = 1;
      io_pCommon->offtimer = 0;
      io_pCommon->ontimer = io_pCommon->offtimer;
    }
  }
  if ( io_pCommon->offtimer )
  {
    if ( io_pCommon->offtimer < 0xFA )
      ++io_pCommon->offtimer;
    else
      io_pCommon->online = 0;
  }
  return io_pCommon->sys_clock.lo;
}
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;

//----- (00403018) --------------------------------------------------------
int __fastcall s147link_loop()
{
  int ThreadId; // $v0
  SifRpcDataQueue_t qd; // [sp+20h] [+20h] BYREF
  SifRpcServerData_t sd; // [sp+38h] [+38h] BYREF

  ThreadId = GetThreadId();
  sceSifSetRpcQueue(&qd, ThreadId);
  sceSifRegisterRpc(&sd, 0x14799, (SifRpcFunc_t)dispatch, rpc_buf, 0, 0, &qd);
  sceSifRpcLoop(&qd);
  return 0;
}

//----- (004030A8) --------------------------------------------------------
void *__fastcall dispatch(unsigned int fno, void *buf, int size)
{
  unsigned int fno_masked; // $v0
  int tmp_online; // $v1
  int state; // [sp+14h] [+14h] BYREF
  int node; // [sp+18h] [+18h]
  int sizea; // [sp+1Ch] [+1Ch]
  int i; // [sp+20h] [+20h]
  int j; // [sp+24h] [+24h]

  FlushDcache();
  fno_masked = fno & 0xFF000000;
  if ( (fno & 0xFF000000) == 0x8000000 )
  {
    *(_DWORD *)buf = cl_info.online;
  }
  else if ( fno_masked > 0x8000000 )
  {
    if ( fno_masked == 0xC000000 )
    {
      node = (unsigned __int8)fno;
      *(_DWORD *)buf = cl_info.R_lost[(unsigned __int8)fno];
      cl_info.R_lost[node] = 0;
    }
    else if ( fno_masked > 0xC000000 )
    {
      if ( fno_masked == 0xF000000 )
      {
        CpuSuspendIntr(&state);
        clink_InterruptHandler(&cl_info);
        CpuResumeIntr(state);
      }
      else if ( fno_masked > 0xF000000 )
      {
        if ( fno_masked == 0x10000000 )
        {
          CpuSuspendIntr(&state);
          cl_info.T_out = 0;
          cl_info.T_in = 0;
          cl_info.T_remain = 0x100;
          s147link_dev9_mem_mmio.m_unk17 = 1;
          s147link_dev9_mem_mmio.m_unk17 = 0xE;
          cl_info.T_error[cl_info.T_node] = 0xFFFFFFFD;
          *(_DWORD *)buf = cl_info.T_node;
          CpuResumeIntr(state);
        }
        else
        {
          if ( fno_masked != 0x11000000 )
            goto LABEL_50;
          *(_DWORD *)buf = cl_info.rbfix;
        }
      }
      else
      {
        if ( fno_masked != 0xD000000 )
          goto LABEL_50;
        node = (unsigned __int8)fno;
        sizea = (fno & 0xFFFF00) >> 8;
        *(_DWORD *)buf = cl_write_custom((unsigned __int8)fno, (unsigned __int8 *)buf, sizea);
      }
    }
    else if ( fno_masked == 0xA000000 )
    {
      node = (unsigned __int8)fno;
      CpuSuspendIntr(&state);
      cl_info.T_error[node] = 0;
      s147link_dev9_mem_mmio.m_unk15 = 0x1B;
      clink_InterruptHandler(&cl_info);
      CpuResumeIntr(state);
    }
    else if ( fno_masked > 0xA000000 )
    {
      if ( fno_masked != 0xB000000 )
        goto LABEL_50;
      CpuSuspendIntr(&state);
      s147link_dev9_mem_mmio.m_unk17 = 1;
      s147link_dev9_mem_mmio.m_unk17 = 0xE;
      cl_info.T_error[cl_info.T_node] = 0xFFFFFFFD;
      *(_DWORD *)buf = cl_info.T_node;
      s147link_dev9_mem_mmio.m_unk15 = 0x1B;
      clink_InterruptHandler(&cl_info);
      CpuResumeIntr(state);
    }
    else
    {
      if ( fno_masked != 0x9000000 )
        goto LABEL_50;
      node = (unsigned __int8)fno;
      *(_DWORD *)buf = cl_info.T_error[(unsigned __int8)fno];
    }
  }
  else if ( fno_masked == 0x3000000 )
  {
    node = (unsigned __int8)fno;
    sizea = (fno & 0xFFFF00) >> 8;
    *(_DWORD *)buf = cl_write((unsigned __int8)fno, (unsigned __int8 *)buf, sizea);
  }
  else if ( fno_masked > 0x3000000 )
  {
    if ( fno_masked == 0x5000000 )
    {
      CpuSuspendIntr(&state);
      cl_info.R_out = 0;
      cl_info.R_in = 0;
      cl_info.R_remain = 0x200;
      CpuResumeIntr(state);
    }
    else if ( fno_masked > 0x5000000 )
    {
      if ( fno_masked == 0x6000000 )
      {
        *(_DWORD *)buf = cl_info.R_remain;
      }
      else
      {
        if ( fno_masked != 0x7000000 )
          goto LABEL_50;
        *(_DWORD *)buf = cl_info.T_remain;
      }
    }
    else
    {
      if ( fno_masked != 0x4000000 )
        goto LABEL_50;
      sizea = (fno & 0xFFFF00) >> 8;
      *(_DWORD *)buf = cl_mwrite((unsigned __int8 *)buf, sizea);
    }
  }
  else if ( fno_masked == 0x1000000 )
  {
    node = (unsigned __int8)fno;
    cl_info.R_pd[(unsigned __int8)fno] = *(_DWORD *)buf;
    cl_info.T_pd[node] = *((_DWORD *)buf + 1);
    cl_info.T_time[node] = *((_DWORD *)buf + 2);
  }
  else if ( fno_masked > 0x1000000 )
  {
    if ( fno_masked != 0x2000000 )
      goto LABEL_50;
    *(_DWORD *)buf = cl_mread((char *)buf + 4, *(_DWORD *)buf);
    CpuSuspendIntr(&state);
    clink_InterruptHandler(&cl_info);
    CpuResumeIntr(state);
  }
  else
  {
    if ( fno_masked )
    {
LABEL_50:
      printf("S147LINK: Unknown RPC command (%X)\n", fno);
      goto LABEL_51;
    }
    *(_DWORD *)buf = 1;
  }
LABEL_51:
  if ( cl_info.online )
    tmp_online = *(_DWORD *)buf | 0x10000;
  else
    tmp_online = *(_DWORD *)buf;
  *(_DWORD *)buf = tmp_online;
  i = 1;
  j = 0x20000;
  while ( i < cl_info.maxnode )
  {
    if ( cl_info.T_error[i] )
      *(_DWORD *)buf |= j;
    if ( cl_info.R_lost[i] )
      *(_DWORD *)buf |= j;
    ++i;
    j *= 2;
  }
  FlushDcache();
  return buf;
}
// B0800000: using guessed type s147link_dev9_mem_mmio_ s147link_dev9_mem_mmio;
