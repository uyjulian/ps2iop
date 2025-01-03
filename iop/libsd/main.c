
#include <irx_imports.h>

#include <stdarg.h>
#include <stdbool.h>
#include <libsd.h>
#include <iop_mmio_hwport.h>

IRX_ID("Sound_Device_Library", 3, 3);

#define __cdecl
#define __fastcall

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
#define BOOL int
#define _BYTE u8
#define _WORD u16
#define _DWORD u32
#define _QWORD u64
#define SD_DMA_CS           (1 << 9) // Continuous stream
#define SD_DMA_START          (1 << 24)
#define SD_DMA_DIR_SPU2IOP        0
#define SD_DMA_DIR_IOP2SPU        1

extern struct irx_export_table _exp_libsd;

typedef struct spu2_u16pair_
{
  vu16 pair[2];
} spu2_u16pair_t;

typedef struct spu2_voice_params_
{
  vu16 voll;
  vu16 volr;
  vu16 pitch;
  vu16 adsr1;
  vu16 adsr2;
  vu16 envx;
  vu16 volxl;
  vu16 volxr;
} spu2_voice_params_t;

typedef struct spu2_voice_address_
{
  spu2_u16pair_t ssa;
  spu2_u16pair_t lsax;
  spu2_u16pair_t nax;
} spu2_voice_address_t;

typedef struct spu2_core_regs_
{
  spu2_voice_params_t voice_params[24]; /* 0x000 */
  spu2_u16pair_t pmon; /* 0x180 */
  spu2_u16pair_t non; /* 0x184 */
  spu2_u16pair_t vmixl; /* 0x188 */
  spu2_u16pair_t vmixel; /* 0x18c */
  spu2_u16pair_t vmixr; /* 0x190 */
  spu2_u16pair_t vmixer; /* 0x194 */
  vu16 mmix; /* 0x198 */
  vu16 attr; /* 0x19a */
  spu2_u16pair_t irqa; /* 0x19c */
  spu2_u16pair_t kon; /* 0x1a0 */
  spu2_u16pair_t koff; /* 0x1a4 */
  spu2_u16pair_t tsa; /* 0x1a8 */
  vu16 xferdata_1ac; /* 0x1ac */
  vu16 unk1ae; /* 0x1ae */
  vu16 admas; /* 0x1b0 */
  vu8 unknown1b2[14]; /* 0x1b2 */
  spu2_voice_address_t voice_address[24]; /* 0x1c0 */
  spu2_u16pair_t esa; /* 0x2e0 */
  spu2_u16pair_t apf1_size; /* 0x2e4 */
  spu2_u16pair_t apf2_size; /* 0x2e8 */
  spu2_u16pair_t same_l_dst; /* 0x2EC */
  spu2_u16pair_t same_r_dst; /* 0x2F0 */
  spu2_u16pair_t comb1_l_src; /* 0x2F4 */
  spu2_u16pair_t comb1_r_src; /* 0x2F8 */
  spu2_u16pair_t comb2_l_src; /* 0x2FC */
  spu2_u16pair_t comb2_r_src; /* 0x300 */
  spu2_u16pair_t same_l_src; /* 0x304 */
  spu2_u16pair_t same_r_src; /* 0x308 */
  spu2_u16pair_t diff_l_dst; /* 0x30C */
  spu2_u16pair_t diff_r_dst; /* 0x310 */
  spu2_u16pair_t comb3_l_src; /* 0x314 */
  spu2_u16pair_t comb3_r_src; /* 0x318 */
  spu2_u16pair_t comb4_l_src; /* 0x31C */
  spu2_u16pair_t comb4_r_src; /* 0x320 */
  spu2_u16pair_t diff_l_src; /* 0x324 */
  spu2_u16pair_t diff_r_src; /* 0x328 */
  spu2_u16pair_t apf1_l_dst; /* 0x32C */
  spu2_u16pair_t apf1_r_dst; /* 0x330 */
  spu2_u16pair_t apf2_l_dst; /* 0x334 */
  spu2_u16pair_t apf2_r_dst; /* 0x338 */
  vu16 eea; /* 0x33C */
  vu16 unk33e; /* 0x33E */
  spu2_u16pair_t endx; /* 0x340 */
  vu16 statx; /* 0x344 */
  vu16 unk346; /* 0x346 */
  vu16 unk348; /* 0x348 */
  vu16 unk34A; /* 0x34A */
  vu16 unk34C; /* 0x34C */
  vu16 unk34E; /* 0x34E */
  vu16 unk350; /* 0x350 */
  vu16 unk352; /* 0x352 */
  vu16 unk354; /* 0x354 */
  vu16 unk356; /* 0x356 */
  vu16 unk358; /* 0x358 */
  vu16 unk35A; /* 0x35A */
  vu16 unk35C; /* 0x35C */
  vu16 unk35E; /* 0x35E */
} spu2_core_regs_t;

typedef struct spu2_different_regs_
{
  vu16 mvoll; /* 0x760 */
  vu16 mvolr; /* 0x762 */
  vu16 evoll; /* 0x764 */
  vu16 evolr; /* 0x766 */
  vu16 avoll; /* 0x768 */
  vu16 avolr; /* 0x76A */
  vu16 bvoll; /* 0x76C */
  vu16 bvolr; /* 0x76E */
  vu16 mvolxl; /* 0x770 */
  vu16 mvolxr; /* 0x772 */
  vu16 iir_vol; /* 0x774 */
  vu16 comb1_vol; /* 0x776 */
  vu16 comb2_vol; /* 0x778 */
  vu16 comb3_vol; /* 0x77A */
  vu16 comb4_vol; /* 0x77C */
  vu16 wall_vol; /* 0x77E */
  vu16 apf1_vol; /* 0x780 */
  vu16 apf2_vol; /* 0x782 */
  vu16 in_coef_l; /* 0x784 */
  vu16 in_coef_r; /* 0x786 */
} spu2_different_regs_t;

typedef struct spu2_core_regs_padded_
{
  spu2_core_regs_t cregs;
  vu8 padding[160];
} spu2_core_regs_padded_t;

typedef struct spu2_regs_main_
{
  spu2_core_regs_padded_t core_regs[2];
} spu2_regs_main_t;

typedef struct spu2_regs_extra_
{
  spu2_core_regs_t core0_regs;
  vu8 padding346[160];
  spu2_core_regs_t core1_regs; /* 0x400 */
  spu2_different_regs_t different_regs[2];
  vu8 unknown7b0[0x10];
  vu16 spdif_out; /* 0x7c0 */
  vu16 spdif_irqinfo; /* 0x7c2 */
  vu16 unknown7c4; /* 0x7c4 */
  vu16 spdif_mode; /* 0x7c6 */
  vu16 spdif_media; /* 0x7c8 */
  vu16 unknown7ca; /* 0x7ca */
  vu16 spdif_protect; /* 0x7cc */
  vu16 unknown7ce;
  vu16 unknown7d0;
  vu16 unknown7d2;
  vu16 unknown7d4;
  vu16 unknown7d6;
  vu16 unknown7d8;
  vu16 unknown7da;
  vu16 unknown7dc;
  vu16 unknown7de;
  vu16 unknown7e0;
  vu16 unknown7e2;
  vu16 unknown7e4;
  vu16 unknown7e6;
  vu16 unknown7e8;
  vu16 unknown7ea;
  vu16 unknown7ec;
  vu16 unknown7ee;
  vu16 unknown7f0;
  vu16 unknown7f2;
  vu16 unknown7f4;
  vu16 unknown7f6;
  vu16 unknown7f8;
  vu16 unknown7fa;
  vu16 unknown7fc;
  vu16 unknown7fe;
} spu2_regs_extra_t;

typedef struct spu2_regs_ /* base => 0xBF900000 */
{
  union spu2_regs_union_
  {
    spu2_regs_main_t main_regs;
    spu2_regs_extra_t extra_regs;
  } u;
} spu2_regs_t;

struct mode_data_struct
{
  int mode_flags;
  __int16 mode_data[32];
};

typedef struct
{
  u32 mode;
  void *data;
} IntrData;

typedef struct CleanEffectIntrData_
{
  void *cb;
  void *userdata;
} CleanEffectIntrData_t;

typedef struct CleanRegionBufferElement_
{
  u32 m_spuaddr;
  u32 m_size;
} CleanRegionBufferElement_t;


typedef struct CleanRegionBuffer_
{
  CleanRegionBufferElement_t m_elements[97];
} CleanRegionBuffer_t;


//-------------------------------------------------------------------------
// Function declarations

void libsd_1();
void SetEffectRegister(int core, int spu2_regs_offset, int val);
void __cdecl SetEffectData(int core, struct mode_data_struct *mode_data);
int __cdecl sceSdClearEffectWorkArea(int core, int channel, int effect_mode);
int __fastcall CleanHandler(int channel, int unusedarg, unsigned int notneededarg);
int __cdecl sceSdCleanEffectWorkArea(int core, int channel, int effect_mode);
void __cdecl sceSdGetEffectAttr(int core, sceSdEffectAttr *attr);
int __cdecl sceSdSetEffectAttr(int core, sceSdEffectAttr *attr);
int __fastcall GetEEA(int core);
int __cdecl sceSdSetEffectMode(int core, sceSdEffectAttr *param);
int __cdecl sceSdSetEffectModeParams(int core, sceSdEffectAttr *attr);
void InitSpu2_Inner();
void InitSpu2();
void InitCoreVolume(int flag);
int __cdecl sceSdVoiceTrans(s16 chan, u16 mode, u8 *iopaddr, u32 *spuaddr, u32 size);
u32 __cdecl sceSdVoiceTransStatus(s16 channel, s16 flag);
int __cdecl sceSdStopTrans(int channel);
int sceSdBlockTrans(s16 chan, u16 mode, u8 *iopaddr, u32 size, ...);
u32 __cdecl sceSdBlockTransStatus(s16 channel, s16 flag);
void some_stkclr();
int InitSpdif();
void SetDmaWrite(int chan);
void SetDmaRead(int chan);
void libsd_do_busyloop_2();
void libsd_do_busyloop_1(int);
u32 __fastcall DmaStartStop(int mainarg, unsigned int vararg2, unsigned int vararg3);
int __fastcall VoiceTrans_Write_IOMode(__int16 *iopaddr, unsigned int size, int chan);
int __fastcall do_finish_block_clean_xfer(int a1, int attr_offs_2);
int __fastcall TransInterrupt(IntrData *intr);
u32 __fastcall thunk_sceSdBlockTransStatus(int channel);
unsigned int __fastcall BlockTransWriteFrom(u32 iopaddr, unsigned int size, char chan, char mode, int startaddr);
u32 __fastcall BlockTransRead(u32 iopaddr, u32 size, char chan, __int16 mode);
int __fastcall SifDmaBatch(void *ee_addr, void *iop_addr, int size);
int __cdecl sceSdProcBatch(sceSdBatch *batch, u32 *rets, u32 num);
int __cdecl sceSdProcBatchEx(sceSdBatch *batch, u32 *rets, u32 num, u32 voice);
void __cdecl sceSdSetParam(u16 entry, u16 value);
u16 __cdecl sceSdGetParam(u16 entry);
void __cdecl sceSdSetSwitch(u16 entry, u32 value);
u32 __cdecl sceSdGetSwitch(u16 entry);
void __cdecl sceSdSetAddr(u16 entry, u32 value);
u32 __cdecl sceSdGetAddr(u16 entry);
u16 __cdecl sceSdNote2Pitch(u16 center_note, u16 center_fine, u16 note, s16 fine);
u16 __cdecl sceSdPitch2Note(u16 center_note, u16 center_fine, u16 pitch);
int __fastcall SetSpdifMode(int val);
void sceSdSetCoreAttr_default(char entry, char val);
void __cdecl sceSdSetCoreAttr(u16 entry, u16 value);
u16 __cdecl sceSdGetCoreAttr(u16 entry);
SdIntrCallback __cdecl sceSdSetTransCallback(s32 core, SdIntrCallback cb);
sceSdTransIntrHandler __cdecl sceSdSetTransIntrHandler(int channel, sceSdTransIntrHandler func, void *arg);
void *__cdecl sceSdGetTransIntrHandlerArgument(int arg);
SdIntrCallback __cdecl sceSdSetIRQCallback(SdIntrCallback cb);
sceSdSpu2IntrHandler __cdecl sceSdSetSpu2IntrHandler(sceSdSpu2IntrHandler func, void *arg);
void *__cdecl sceSdGetSpu2IntrHandlerArgument();
int __fastcall Spu2Interrupt(void *data);
int InitVoices();
int __fastcall Reset(char flag);
void reset_vars();
int __cdecl sceSdInit(int flag);
int __cdecl sceSdQuit();

//-------------------------------------------------------------------------
// Data declarations

vu16 *ParamRegList[44] =
{
  (vu16 *)0xBF900000,
  (vu16 *)0xBF900002,
  (vu16 *)0xBF900004,
  (vu16 *)0xBF900006,
  (vu16 *)0xBF900008,
  (vu16 *)0xBF90000A,
  (vu16 *)0xBF90000C,
  (vu16 *)0xBF90000E,
  (vu16 *)0xBF900198,
  (vu16 *)0xBF900760,
  (vu16 *)0xBF900762,
  (vu16 *)0xBF900764,
  (vu16 *)0xBF900766,
  (vu16 *)0xBF900768,
  (vu16 *)0xBF90076A,
  (vu16 *)0xBF90076C,
  (vu16 *)0xBF90076E,
  (vu16 *)0xBF900770,
  (vu16 *)0xBF900772,
  (vu16 *)0xBF900180,
  (vu16 *)0xBF900184,
  (vu16 *)0xBF9001A0,
  (vu16 *)0xBF9001A4,
  (vu16 *)0xBF900340,
  (vu16 *)0xBF900188,
  (vu16 *)0xBF90018C,
  (vu16 *)0xBF900190,
  (vu16 *)0xBF900194,
  (vu16 *)0xBF9002E0,
  (vu16 *)0xBF90033C,
  (vu16 *)0xBF9001A8,
  (vu16 *)0xBF90019C,
  (vu16 *)0xBF9001C0,
  (vu16 *)0xBF9001C4,
  (vu16 *)0xBF9001C8,
  (vu16 *)0xBF90019A,
  (vu16 *)0xBF9001A8,
  (vu16 *)0xBF9001AC,
  (vu16 *)0xBF9001AE,
  (vu16 *)0xBF9001B0,
  (vu16 *)0xBF900344,
  NULL,
  NULL,
  NULL
};
int EffectSizes[10] = { 2, 1240, 1000, 2312, 3580, 5564, 7896, 12296, 12296, 1920 };
struct mode_data_struct EffectParams[10] =
{
  {
    0,
    {
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      1,
      1,
      0,
      0,
      0,
      0,
      0,
      0,
      1,
      1,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0
    }
  },
  {
    0,
    {
      125,
      91,
      28032,
      21688,
      -16688,
      0,
      0,
      -17792,
      22528,
      21248,
      1238,
      819,
      1008,
      551,
      884,
      495,
      822,
      439,
      821,
      438,
      820,
      437,
      820,
      437,
      820,
      437,
      436,
      310,
      184,
      92,
      32768,
      32768
    }
  },
  {
    0,
    {
      51,
      37,
      28912,
      20392,
      -17184,
      17424,
      -16144,
      -25600,
      21120,
      20160,
      996,
      795,
      932,
      687,
      882,
      614,
      796,
      605,
      604,
      398,
      559,
      309,
      466,
      183,
      399,
      181,
      180,
      128,
      76,
      38,
      32768,
      32768
    }
  },
  {
    0,
    {
      177,
      127,
      28912,
      20392,
      -17184,
      17680,
      -16656,
      -19264,
      21120,
      20160,
      2308,
      1899,
      2084,
      1631,
      1954,
      1558,
      1900,
      1517,
      1516,
      1070,
      1295,
      773,
      1122,
      695,
      1071,
      613,
      612,
      434,
      256,
      128,
      32768,
      32768
    }
  },
  {
    0,
    {
      227,
      169,
      28512,
      20392,
      -17184,
      17680,
      -16656,
      -22912,
      22144,
      21184,
      3579,
      2904,
      3337,
      2620,
      3033,
      2419,
      2905,
      2266,
      2265,
      1513,
      2028,
      1200,
      1775,
      978,
      1514,
      797,
      796,
      568,
      340,
      170,
      32768,
      32768
    }
  },
  {
    0,
    {
      421,
      313,
      24576,
      20480,
      19456,
      -18432,
      -17408,
      -16384,
      24576,
      23552,
      5562,
      4539,
      5314,
      4285,
      4540,
      3521,
      4544,
      3523,
      3520,
      2497,
      3012,
      1985,
      2560,
      1741,
      2498,
      1473,
      1472,
      1050,
      628,
      314,
      32768,
      32768
    }
  },
  {
    0,
    {
      829,
      561,
      32256,
      20480,
      -19456,
      -20480,
      19456,
      -20480,
      24576,
      21504,
      7894,
      6705,
      7444,
      6203,
      7106,
      5810,
      6706,
      5615,
      5614,
      4181,
      4916,
      3885,
      4598,
      3165,
      4182,
      2785,
      2784,
      1954,
      1124,
      562,
      32768,
      32768
    }
  },
  {
    0,
    {
      3,
      3,
      32767,
      32767,
      0,
      0,
      0,
      -32512,
      0,
      0,
      8189,
      4093,
      4105,
      9,
      0,
      0,
      4105,
      9,
      8191,
      8191,
      8190,
      8190,
      8190,
      8190,
      8190,
      8190,
      4104,
      4100,
      8,
      4,
      32768,
      32768
    }
  },
  {
    0,
    {
      3,
      3,
      32767,
      32767,
      0,
      0,
      0,
      0,
      0,
      0,
      8189,
      4093,
      4105,
      9,
      0,
      0,
      4105,
      9,
      8191,
      8191,
      8190,
      8190,
      8190,
      8190,
      8190,
      8190,
      4104,
      4100,
      8,
      4,
      32768,
      32768
    }
  },
  {
    0,
    {
      23,
      19,
      28912,
      20392,
      -17184,
      17680,
      -16656,
      -31488,
      24448,
      21696,
      881,
      687,
      741,
      479,
      688,
      471,
      856,
      618,
      470,
      286,
      301,
      177,
      287,
      89,
      416,
      227,
      88,
      64,
      40,
      20,
      32768,
      32768
    }
  }
};
u32 ClearEffectData[256] =
{
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u,
  0u
};
spu2_regs_t *ptr_to_bf900000 = (spu2_regs_t *)0xBF900000;
int VoiceTransStatus[2] = { 0, 0 };
int VoiceTransIoMode[2] = { 1, 1 };
__int16 NotePitchTable[140] =
{
  32768,
  -30820,
  -28756,
  -26569,
  -24251,
  -21796,
  -19196,
  -16440,
  -13521,
  -10428,
  -7151,
  -3679,
  32768,
  -32754,
  -32739,
  -32724,
  -32709,
  -32694,
  -32680,
  -32665,
  -32650,
  -32635,
  -32620,
  -32605,
  -32591,
  -32576,
  -32561,
  -32546,
  -32531,
  -32516,
  -32501,
  -32486,
  -32471,
  -32456,
  -32442,
  -32427,
  -32412,
  -32397,
  -32382,
  -32367,
  -32352,
  -32337,
  -32322,
  -32307,
  -32292,
  -32277,
  -32262,
  -32247,
  -32232,
  -32217,
  -32202,
  -32187,
  -32172,
  -32157,
  -32142,
  -32126,
  -32111,
  -32096,
  -32081,
  -32066,
  -32051,
  -32036,
  -32021,
  -32006,
  -31990,
  -31975,
  -31960,
  -31945,
  -31930,
  -31915,
  -31900,
  -31884,
  -31869,
  -31854,
  -31839,
  -31824,
  -31808,
  -31793,
  -31778,
  -31763,
  -31747,
  -31732,
  -31717,
  -31702,
  -31686,
  -31671,
  -31656,
  -31640,
  -31625,
  -31610,
  -31595,
  -31579,
  -31564,
  -31549,
  -31533,
  -31518,
  -31503,
  -31487,
  -31472,
  -31456,
  -31441,
  -31426,
  -31410,
  -31395,
  -31379,
  -31364,
  -31349,
  -31333,
  -31318,
  -31302,
  -31287,
  -31271,
  -31256,
  -31240,
  -31225,
  -31209,
  -31194,
  -31178,
  -31163,
  -31147,
  -31132,
  -31116,
  -31101,
  -31085,
  -31070,
  -31054,
  -31039,
  -31023,
  -31008,
  -30992,
  -30976,
  -30961,
  -30945,
  -30930,
  -30914,
  -30898,
  -30883,
  -30867,
  -30851,
  -30836
};
int SpdifSettings = 0; // weak
sceSdEffectAttr EffectAttr[2] = { { 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } };
int VoiceTransCompleteBool[2] = { 0, 0 };
int VoiceTransCompleteEf[2] = { 0, 0 };
int vars_inited = 0; // weak
SdIntrCallback Spu2IrqCallback = NULL;
sceSdSpu2IntrHandler Spu2IntrHandler = NULL;
void *Spu2IntrHandlerData = NULL; // idb
sceSdTransIntrHandler TransIntrHandlers[2] = { NULL, NULL };
CleanEffectIntrData_t BlockHandlerIntrData[2] = { { NULL, NULL }, { NULL, NULL } };
int CleanHandlers[2] = { 0, 0 };
IntrData TransIntrData[2] = { { 0u, NULL }, { 1u, NULL } };
__int16 VoiceDataInit[8] = { 1792, 0, 0, 0, 0, 0, 0, 0 };
u32 CleanRegionMax[2];
u32 CleanRegionCur[2];
CleanRegionBuffer_t CleanRegionBuffer[2];
u32 BlockTransBuff[2];
u32 BlockTransAddr[2];
u32 BlockTransSize[2];
u32 BatchData;
SdIntrCallback TransIntrCallbacks[2];
u32 EffectAddr[2];
iop_mmio_hwport_t iop_mmio_hwport; // weak
spu2_regs_t spu2_regs; // weak
char byte_BF900800[63488]; // weak


//----- (004000A0) --------------------------------------------------------
void libsd_1()
{
  ;
}

//----- (004000B0) --------------------------------------------------------
int _start()
{
  int condtmp; // $s0
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  condtmp = RegisterLibraryEntries(&_exp_libsd);
  CpuResumeIntr(state);
  if ( condtmp )
  {
    return 1;
  }
  InitSpu2_Inner();
  reset_vars();
  return 0;
}

//----- (00400110) --------------------------------------------------------
void SetEffectRegister(int core, int spu2_regs_offset, int val)
{
  unsigned int rval; // $a2
  _WORD *regptr; // $a0

  rval = 4 * val;
  regptr = (_WORD *)&ptr_to_bf900000->u.main_regs.core_regs[core] + spu2_regs_offset;
  *regptr = (rval >> 16) & 0xFFFF;
  regptr[1] = rval;
}

//----- (0040013C) --------------------------------------------------------
void __cdecl SetEffectData(int core, struct mode_data_struct *mode_data)
{
  int deref_mode_data; // $s0
  BOOL condtmp; // $s1
  int regoffs1; // $v0
  int regoffs2; // $v0
  int regoffs3; // $v0
  int regoffs4; // $v0
  int regoffs5; // $v0
  int regoffs6; // $v0
  int regoffs7; // $v0
  int regoffs8; // $v0
  int regoffs9; // $v0

  deref_mode_data = mode_data->mode_flags;
  condtmp = mode_data->mode_flags == 0;
  if ( !mode_data->mode_flags || (deref_mode_data & 1) != 0 )
    SetEffectRegister(core, 370, (unsigned __int16)mode_data->mode_data[0]);
  if ( condtmp || (deref_mode_data & 2) != 0 )
    SetEffectRegister(core, 372, (unsigned __int16)mode_data->mode_data[1]);
  regoffs1 = 4 * core;
  if ( condtmp || (regoffs1 = 4 * core, (deref_mode_data & 4) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].iir_vol + 4 * regoffs1 + 4 * core) = mode_data->mode_data[2];
  regoffs2 = 4 * core;
  if ( condtmp || (regoffs2 = 4 * core, (deref_mode_data & 8) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].comb1_vol + 4 * regoffs2 + 4 * core) = mode_data->mode_data[3];
  regoffs3 = 4 * core;
  if ( condtmp || (regoffs3 = 4 * core, (deref_mode_data & 0x10) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].comb2_vol + 4 * regoffs3 + 4 * core) = mode_data->mode_data[4];
  regoffs4 = 4 * core;
  if ( condtmp || (regoffs4 = 4 * core, (deref_mode_data & 0x20) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].comb3_vol + 4 * regoffs4 + 4 * core) = mode_data->mode_data[5];
  regoffs5 = 4 * core;
  if ( condtmp || (regoffs5 = 4 * core, (deref_mode_data & 0x40) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].comb4_vol + 4 * regoffs5 + 4 * core) = mode_data->mode_data[6];
  regoffs6 = 4 * core;
  if ( condtmp || (regoffs6 = 4 * core, (deref_mode_data & 0x80) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].wall_vol + 4 * regoffs6 + 4 * core) = mode_data->mode_data[7];
  regoffs7 = 4 * core;
  if ( condtmp || (regoffs7 = 4 * core, (deref_mode_data & 0x100) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].apf1_vol + 4 * regoffs7 + 4 * core) = mode_data->mode_data[8];
  regoffs8 = 4 * core;
  if ( condtmp || (regoffs8 = 4 * core, (deref_mode_data & 0x200) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].apf2_vol + 4 * regoffs8 + 4 * core) = mode_data->mode_data[9];
  if ( condtmp || (deref_mode_data & 0x400) != 0 )
    SetEffectRegister(core, 374, (unsigned __int16)mode_data->mode_data[10]);
  if ( condtmp || (deref_mode_data & 0x800) != 0 )
    SetEffectRegister(core, 376, (unsigned __int16)mode_data->mode_data[11]);
  if ( condtmp || (deref_mode_data & 0x1000) != 0 )
    SetEffectRegister(core, 378, (unsigned __int16)mode_data->mode_data[12]);
  if ( condtmp || (deref_mode_data & 0x2000) != 0 )
    SetEffectRegister(core, 380, (unsigned __int16)mode_data->mode_data[13]);
  if ( condtmp || (deref_mode_data & 0x4000) != 0 )
    SetEffectRegister(core, 382, (unsigned __int16)mode_data->mode_data[14]);
  if ( condtmp || (deref_mode_data & 0x8000) != 0 )
    SetEffectRegister(core, 384, (unsigned __int16)mode_data->mode_data[15]);
  if ( condtmp || (deref_mode_data & 0x10000) != 0 )
    SetEffectRegister(core, 386, (unsigned __int16)mode_data->mode_data[16]);
  if ( condtmp || (deref_mode_data & 0x20000) != 0 )
    SetEffectRegister(core, 388, (unsigned __int16)mode_data->mode_data[17]);
  if ( condtmp || (deref_mode_data & 0x40000) != 0 )
    SetEffectRegister(core, 390, (unsigned __int16)mode_data->mode_data[18]);
  if ( condtmp || (deref_mode_data & 0x80000) != 0 )
    SetEffectRegister(core, 392, (unsigned __int16)mode_data->mode_data[19]);
  if ( condtmp || (deref_mode_data & 0x100000) != 0 )
    SetEffectRegister(core, 394, (unsigned __int16)mode_data->mode_data[20]);
  if ( condtmp || (deref_mode_data & 0x200000) != 0 )
    SetEffectRegister(core, 396, (unsigned __int16)mode_data->mode_data[21]);
  if ( condtmp || (deref_mode_data & 0x400000) != 0 )
    SetEffectRegister(core, 398, (unsigned __int16)mode_data->mode_data[22]);
  if ( condtmp || (deref_mode_data & 0x800000) != 0 )
    SetEffectRegister(core, 400, (unsigned __int16)mode_data->mode_data[23]);
  if ( condtmp || (deref_mode_data & 0x1000000) != 0 )
    SetEffectRegister(core, 402, (unsigned __int16)mode_data->mode_data[24]);
  if ( condtmp || (deref_mode_data & 0x2000000) != 0 )
    SetEffectRegister(core, 404, (unsigned __int16)mode_data->mode_data[25]);
  if ( condtmp || (deref_mode_data & 0x4000000) != 0 )
    SetEffectRegister(core, 406, (unsigned __int16)mode_data->mode_data[26]);
  if ( condtmp || (deref_mode_data & 0x8000000) != 0 )
    SetEffectRegister(core, 408, (unsigned __int16)mode_data->mode_data[27]);
  if ( condtmp || (deref_mode_data & 0x10000000) != 0 )
    SetEffectRegister(core, 410, (unsigned __int16)mode_data->mode_data[28]);
  if ( condtmp || (deref_mode_data & 0x20000000) != 0 )
    SetEffectRegister(core, 412, (unsigned __int16)mode_data->mode_data[29]);
  regoffs9 = 4 * core;
  if ( condtmp || (regoffs9 = 4 * core, (deref_mode_data & 0x40000000) != 0) )
    *(&ptr_to_bf900000->u.extra_regs.different_regs[0].in_coef_l + 4 * regoffs9 + 4 * core) = mode_data->mode_data[30];
  if ( condtmp || deref_mode_data < 0 )
    ptr_to_bf900000->u.extra_regs.different_regs[core].in_coef_r = mode_data->mode_data[31];
}

//----- (00400660) --------------------------------------------------------
int __cdecl sceSdClearEffectWorkArea(int core, int channel, int effect_mode)
{
  int effect_mode_tmp; // $s0
  int channel_tmp1; // $s3
  unsigned int aligned_addr; // $s4
  unsigned int effect_size; // $s1
  unsigned int effect_addr; // $s2
  int xferres; // $s0
  int flag_tmp; // $s4
  u32 size; // $v1
  int channel_tmp2; // $v1
  int (__cdecl *callback_tmp)(void *); // [sp+18h] [-8h]
  int (__cdecl *handler_tmp)(int, void *); // [sp+1Ch] [-4h]

  effect_mode_tmp = (unsigned __int8)effect_mode;
  if ( (unsigned __int8)effect_mode >= 0xAu )
    return -100;
  if ( !(_BYTE)effect_mode )
    return 0;
  if ( DmaStartStop((16 * channel) | 4, channel, (unsigned __int8)effect_mode) != 0 )
  {
    return -210;
  }
  channel_tmp1 = channel;
  if ( VoiceTransIoMode[channel] != 1 )
  {
    return -201;
  }
  if ( QueryIntrContext() != 0 )
  {
    return -202;
  }
  aligned_addr = 0;
  effect_size = 8 * EffectSizes[effect_mode_tmp];
  effect_addr = (GetEEA(core) - (effect_size - 1)) >> 1;
  if ( (effect_size & 0x3F) != 0 )
  {
    effect_size = effect_size >> 6 << 6;
    aligned_addr = (GetEEA(core) - (effect_size - 1)) >> 1;
  }
  handler_tmp = TransIntrHandlers[channel_tmp1];
  callback_tmp = TransIntrCallbacks[channel_tmp1];
  TransIntrHandlers[channel_tmp1] = 0;
  TransIntrCallbacks[channel_tmp1] = 0;
  if ( !aligned_addr
    || ((xferres = sceSdVoiceTrans(channel, 0, (u8 *)ClearEffectData, (u32 *)(2 * effect_addr), 0x40u), xferres >= 0)
    && (xferres = sceSdVoiceTransStatus(channel, 1), effect_addr = aligned_addr, xferres >= 0)) )
  {
    flag_tmp = 1;
    while ( 1 )
    {
      size = 0x400;
      if ( effect_size < 0x401 )
      {
        size = effect_size;
        flag_tmp = 0;
      }
      xferres = sceSdVoiceTrans(channel, 0, (u8 *)ClearEffectData, (u32 *)(2 * effect_addr), size);
      if ( xferres < 0 )
        break;
      xferres = sceSdVoiceTransStatus(channel, 1);
      effect_size -= 1024;
      if ( xferres < 0 )
        break;
      effect_addr += 512;
      if ( !flag_tmp )
      {
        xferres = 0;
        break;
      }
    }
  }
  channel_tmp2 = channel;
  TransIntrHandlers[channel_tmp2] = handler_tmp;
  TransIntrCallbacks[channel_tmp2] = callback_tmp;
  some_stkclr();
  return xferres;
}

//----- (00400888) --------------------------------------------------------
int __fastcall CleanHandler(int channel, int unusedarg, unsigned int notneededarg)
{
  int channel_tmp; // $s2
  int channel_hi; // $s1
  int channel_offs; // $s0

  channel_tmp = channel;
  ++CleanRegionCur[channel];
  channel_hi = 16 * channel;
  if ( (int)CleanRegionCur[channel] >= (int)(CleanRegionMax[channel] - 1) )
  {
    CleanHandlers[channel_tmp] = 0;
    channel_hi = 16 * channel;
  }
  channel_offs = 97 * channel;
  DmaStartStop(
    channel_hi | 2,
    CleanRegionBuffer[channel].m_elements[CleanRegionCur[channel_tmp]].m_spuaddr,
    notneededarg);
  DmaStartStop(
    channel_hi | 6,
    (unsigned int)ClearEffectData,
    CleanRegionBuffer[0].m_elements[CleanRegionCur[channel_tmp] + channel_offs].m_size);
  return 0;
}

//----- (0040097C) --------------------------------------------------------
int __cdecl sceSdCleanEffectWorkArea(int core, int channel, int effect_mode)
{
  int v5; // $s0
  int v8; // $s3
  unsigned int v9; // $s1
  u32 *v10; // $a3
  int v11; // $s0
  CleanRegionBuffer_t *v12; // $t0
  u32 *v13; // $t1
  int v14; // $v1
  int v16; // $t0

  v5 = (unsigned __int8)effect_mode;
  if ( (unsigned __int8)effect_mode >= 0xAu )
    return -100;
  if ( !(_BYTE)effect_mode )
    return 0;
  if ( DmaStartStop((16 * channel) | 4, channel, (unsigned __int8)effect_mode) != 0 )
  {
    return -210;
  }
  v8 = channel;
  if ( VoiceTransIoMode[channel] != 1 )
  {
    return -201;
  }
  v9 = 8 * EffectSizes[v5];
  v10 = (u32 *)(GetEEA(core) - (v9 - 1));
  if ( (v9 & 0x3F) != 0 )
  {
    v9 = v9 >> 6 << 6;
    v11 = sceSdVoiceTrans(channel, 8u, (u8 *)ClearEffectData, v10, 0x40u);
    if ( v11 < 0 )
    {
LABEL_15:
      some_stkclr();
      return v11;
    }
    v10 = (u32 *)(GetEEA(core) - (v9 - 1));
  }
  v12 = &CleanRegionBuffer[channel];
  v13 = v10 + 256;
  v14 = v9 - 1024;
  CleanRegionMax[v8] = 0;
  if ( (int)(v9 - 1024) >= 1025 )
  {
    do
    {
      v12->m_elements[0].m_spuaddr = (u32)v13;
      v12->m_elements[0].m_size = 1024;
      v12 = (CleanRegionBuffer_t *)((char *)v12 + 8);
      v13 += 256;
      v14 -= 1024;
      ++CleanRegionMax[v8];
    }
    while ( v14 >= 1025 );
  }
  v12->m_elements[0].m_spuaddr = (u32)v13;
  v12->m_elements[0].m_size = v14;
  v16 = channel;
  CleanRegionMax[v16] = CleanRegionMax[channel] + 1;
  CleanHandlers[v16] = (int)CleanHandler;
  CleanRegionCur[v16] = 0;
  v11 = sceSdVoiceTrans(channel & 0xFFFF, 0, (u8 *)ClearEffectData, v10, 0x400u);
  if ( v11 >= 0 )
    v11 = 0;
  goto LABEL_15;
}

//----- (00400BBC) --------------------------------------------------------
void __cdecl sceSdGetEffectAttr(int core, sceSdEffectAttr *attr)
{
  attr->core = core;
  attr->mode = EffectAttr[core].mode;
  attr->delay = EffectAttr[core].delay;
  attr->feedback = EffectAttr[core].feedback;
  attr->depth_L = spu2_regs.u.extra_regs.different_regs[core].evoll;
  attr->depth_R = spu2_regs.u.extra_regs.different_regs[core].evolr;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00400C2C) --------------------------------------------------------
int __cdecl sceSdSetEffectAttr(int core, sceSdEffectAttr *attr)
{
  int clearram; // $s7
  int condtmp; // $s6
  int mode; // $s2
  vu16 *p_attr; // $s4
  int core_tmp; // $s1
  int core_tmp2; // $v0
  BOOL modecondtmp1; // $v0
  BOOL modecndtmp2; // $v0
  __int16 mode_data_0; // $v1
  int delay; // $a0
  __int16 feedback_tmp; // $v0
  int feedback; // $v1
  int condtmpeff; // $s5
  int retval; // $s0
  int core_offs; // $v1
  _WORD *effectptr; // $v1
  struct mode_data_struct mode_data; // [sp+10h] [-60h] BYREF
  int state; // [sp+5Ch] [-14h] BYREF
  int effect_mode; // [sp+60h] [-10h]
  int core_hi; // [sp+64h] [-Ch]

  clearram = 0;
  condtmp = 0;
  effect_mode = 0;
  mode_data.mode_flags = 0;
  mode = attr->mode;
  p_attr = &spu2_regs.u.main_regs.core_regs[core].cregs.attr;
  if ( (mode & SD_EFFECT_MODE_CLEAR) != 0 )
  {
    clearram = 1;
    effect_mode = EffectAttr[core].mode;
    condtmp = (mode & 0x200) != 0;
  }
  mode = (unsigned __int8)mode;
  if ( (unsigned __int8)mode >= (unsigned int)(SD_EFFECT_MODE_DELAY|SD_EFFECT_MODE_STUDIO_1) )
    return -100;
  core_tmp = core;
  EffectAttr[core].mode = mode;
  core_hi = core << 9;
  EffectAddr[core] = GetEEA(core) - (8 * EffectSizes[mode] - 1);
  // Unoffical: use memcpy from sysclib
  memcpy(&mode_data, &EffectParams[EffectAttr[core].mode], sizeof(mode_data));
  if ( mode == SD_EFFECT_MODE_ECHO )
  {
    EffectAttr[core_tmp].feedback = 128;
    EffectAttr[core_tmp].delay = 128;
    modecondtmp1 = 1;
  }
  else if ( mode == SD_EFFECT_MODE_DELAY )
  {
    EffectAttr[core_tmp].feedback = 0;
    EffectAttr[core_tmp].delay = 128;
    modecondtmp1 = 1;
  }
  else
  {
    core_tmp2 = core;
    EffectAttr[core_tmp2].feedback = 0;
    EffectAttr[core_tmp2].delay = 0;
    modecondtmp1 = mode < SD_EFFECT_MODE_PIPE;
  }
  if ( modecondtmp1 )
  {
    modecndtmp2 = mode < SD_EFFECT_MODE_PIPE;
    if ( mode >= SD_EFFECT_MODE_ECHO )
    {
      mode_data_0 = mode_data.mode_data[0];
      delay = attr->delay;
      EffectAttr[core].delay = delay;
      delay += 1;
      delay &= 0xFFFF;
      feedback_tmp = ((_WORD)delay << 6) - mode_data_0;
      delay <<= 5;
      delay &= 0xFFFF;
      mode_data.mode_data[10] = feedback_tmp;
      mode_data.mode_data[11] = delay - mode_data.mode_data[1];
      mode_data.mode_data[16] = mode_data.mode_data[17] + delay;
      mode_data.mode_data[12] = mode_data.mode_data[13] + delay;
      mode_data.mode_data[27] = mode_data.mode_data[29] + delay;
      mode_data.mode_data[26] = mode_data.mode_data[28] + delay;
      modecndtmp2 = mode < SD_EFFECT_MODE_PIPE;
    }
    if ( modecndtmp2 && mode >= SD_EFFECT_MODE_ECHO )
    {
      feedback = attr->feedback;
      EffectAttr[core].feedback = feedback;
      mode_data.mode_data[7] = 258 * feedback;
    }
  }
  condtmpeff = (*p_attr >> 7) & 1;
  if ( !condtmpeff
    || (CpuSuspendIntr(&state),
        *p_attr &= 0xFF7F,
        CpuResumeIntr(state),
        !clearram || (retval = sceSdClearEffectWorkArea(core, condtmp, effect_mode), retval >= 0)) )
  {
    spu2_regs.u.extra_regs.different_regs[core].evoll = attr->depth_L;
    spu2_regs.u.extra_regs.different_regs[core].evolr = attr->depth_R;
    SetEffectData(core, &mode_data);
    core_offs = 2 * core_hi;
    spu2_regs.u.main_regs.core_regs[0].cregs.esa.pair[core_hi] = EffectAddr[core] >> 17;
    effectptr = (_WORD *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.esa + core_offs + 2);
    *effectptr = EffectAddr[core] >> 1;
    (void)(unsigned __int16)*effectptr;
    retval = 0;
    if ( clearram )
      retval = sceSdClearEffectWorkArea(core, condtmp, mode);
  }
  if ( condtmpeff )
  {
    CpuSuspendIntr(&state);
    *p_attr |= SD_ENABLE_EFFECTS;
    (void)*p_attr;
    CpuResumeIntr(state);
  }
  some_stkclr();
  return retval;
}
// 400FA4: conditional instruction was optimized away because $s5.4==1
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401100) --------------------------------------------------------
int __fastcall GetEEA(int core)
{
  return (spu2_regs.u.main_regs.core_regs[core].cregs.eea << 17) | 0x1FFFF;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401128) --------------------------------------------------------
int __cdecl sceSdSetEffectMode(int core, sceSdEffectAttr *param)
{
  int clearram; // $s6
  vu16 *p_attr; // $s2
  int condtmp; // $s5
  unsigned int mode; // $s1
  int core_tmp1; // $s0
  int core_tmp2; // $v0
  int EEA; // $v0
  int attr_effectsrel; // $s4
  struct mode_data_struct mode_data; // [sp+10h] [-50h] BYREF
  int state; // [sp+5Ch] [-4h] BYREF

  clearram = 0;
  mode_data.mode_flags = 0;
  p_attr = &spu2_regs.u.main_regs.core_regs[core].cregs.attr;
  condtmp = 0;
  if ( (param->mode & 0x100) != 0 )
  {
    clearram = 1;
    condtmp = (param->mode & 0x200) != 0;
  }
  mode = (unsigned __int8)param->mode;
  core_tmp1 = core;
  if ( mode >= 0xA )
    return -100;
  core_tmp2 = core;
  EffectAttr[core_tmp2].mode = mode;
  EffectAttr[core_tmp2].delay = 0;
  EffectAttr[core_tmp2].feedback = 0;
  EEA = GetEEA(core);
  EffectAddr[core_tmp1] = EEA - (8 * EffectSizes[mode] - 1);
  // Unoffical: don't use inlined memcpy
  memcpy(&mode_data, &EffectParams[mode], sizeof(mode_data));
  attr_effectsrel = (*p_attr >> 7) & 1;
  if ( attr_effectsrel )
  {
    CpuSuspendIntr(&state);
    *p_attr &= ~0x80u;
    CpuResumeIntr(state);
  }
  spu2_regs.u.extra_regs.different_regs[core].evoll = 0;
  spu2_regs.u.extra_regs.different_regs[core].evolr = 0;
  SetEffectData(core, &mode_data);
  spu2_regs.u.main_regs.core_regs[core].cregs.esa.pair[0] = EffectAddr[core] >> 17;
  spu2_regs.u.main_regs.core_regs[core].cregs.esa.pair[1] = EffectAddr[core] >> 1;
  if ( attr_effectsrel )
  {
    CpuSuspendIntr(&state);
    *p_attr |= 0x80u;
    CpuResumeIntr(state);
    (void)*p_attr;
  }
  if ( clearram )
    return sceSdCleanEffectWorkArea(core, condtmp, mode);
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;
// 401128: using guessed type struct mode_data_struct mode_data;

//----- (00401380) --------------------------------------------------------
int __cdecl sceSdSetEffectModeParams(int core, sceSdEffectAttr *attr)
{
  unsigned int mode_low; // $v1
  int mode; // $a0
  __int16 mode_data_0; // $v1
  int core_tmp1; // $a1
  int delay_plus_one; // $a0
  __int16 mode_data_10_set; // $v0
  int feedback; // $v1
  struct mode_data_struct mode_data; // [sp+10h] [-48h] BYREF

  mode_low = attr->mode & 0xFF;
  if ( mode_low >= 0xA )
    return -100;
  mode = EffectAttr[core].mode;
  if ( mode != mode_low )
    return -100;
  if ( mode < 9 )
  {
    if ( mode >= 7 )
    {
      // Unoffical: don't use inlined memcpy
      memcpy(&mode_data, &EffectParams[mode], sizeof(mode_data));
      mode_data.mode_flags = 0xC011C80;
      mode_data_0 = mode_data.mode_data[0];
      core_tmp1 = core;
      EffectAttr[core_tmp1].delay = attr->delay;
      delay_plus_one = EffectAttr[core].delay + 1;
      EffectAttr[core_tmp1].feedback = attr->feedback;
      mode_data_10_set = ((_WORD)delay_plus_one << 6) - mode_data_0;
      delay_plus_one <<= 5;
      delay_plus_one &= 0xFFFF;
      mode_data.mode_data[10] = mode_data_10_set;
      mode_data.mode_data[11] = delay_plus_one - mode_data.mode_data[1];
      mode_data.mode_data[12] = mode_data.mode_data[13] + delay_plus_one;
      mode_data.mode_data[16] = mode_data.mode_data[17] + delay_plus_one;
      mode_data.mode_data[26] = mode_data.mode_data[28] + delay_plus_one;
      feedback = EffectAttr[core].feedback;
      mode_data.mode_data[27] = mode_data.mode_data[29] + delay_plus_one;
      mode_data.mode_data[7] = 258 * feedback;
      SetEffectData(core, &mode_data);
    }
  }
  spu2_regs.u.extra_regs.different_regs[core].evoll = attr->depth_L;
  spu2_regs.u.extra_regs.different_regs[core].evolr = attr->depth_R;
  some_stkclr();
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401550) --------------------------------------------------------
void InitSpu2_Inner()
{
  vu32 dpcr1; // $v0
  vu32 dpcr2; // $v0
  int state; // [sp+10h] [-8h] BYREF

  iop_mmio_hwport.ssbus2.ind_4_address = 0xBF900000;
  iop_mmio_hwport.ssbus2.ind_9_address = (vu32)byte_BF900800;
  CpuSuspendIntr(&state);
  dpcr1 = iop_mmio_hwport.dmac1.dpcr1;
  iop_mmio_hwport.dmac1.dpcr1 = dpcr1 | 0x80000;
  dpcr2 = iop_mmio_hwport.dmac2.dpcr2;
  iop_mmio_hwport.dmac2.dpcr2 = dpcr2 | 8;
  CpuResumeIntr(state);
  iop_mmio_hwport.ssbus1.ind_4_delay = 0x200B31E1;
  iop_mmio_hwport.ssbus2.ind_9_delay = 0x200B31E1;
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;

//----- (004015E8) --------------------------------------------------------
void InitSpu2()
{
  InitSpu2_Inner();
  *(_DWORD *)&spu2_regs.u.extra_regs.spdif_mode = 0x2000900;
  spu2_regs.u.extra_regs.unknown7ca = 8;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401638) --------------------------------------------------------
void InitCoreVolume(int flag)
{
  vu16 attrsetflg; // $v0

  spu2_regs.u.extra_regs.spdif_out = 0xC032;
  if ( flag )
  {
    spu2_regs.u.main_regs.core_regs[0].cregs.attr = SD_ENABLE_EFFECTS|SD_MUTE|SD_SPU2_ON;
    attrsetflg = SD_ENABLE_EX_INPUT|SD_ENABLE_EFFECTS|SD_MUTE|SD_SPU2_ON;
  }
  else
  {
    spu2_regs.u.main_regs.core_regs[0].cregs.attr = SD_MUTE|SD_SPU2_ON;
    attrsetflg = SD_ENABLE_EX_INPUT|SD_MUTE|SD_SPU2_ON;
  }
  spu2_regs.u.main_regs.core_regs[1].cregs.attr = attrsetflg;
  spu2_regs.u.extra_regs.core0_regs.vmixl.pair[0] = 0xFFFF;
  spu2_regs.u.extra_regs.core0_regs.vmixl.pair[1] = 0xFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixel.pair[0] = -1;
  *(_QWORD *)&spu2_regs.u.extra_regs.core0_regs.vmixel.pair[1] = 0xFFFF00FFFFFF00FFLL;
  (*(spu2_u16pair_t *)((char *)&spu2_regs.u.extra_regs.core0_regs.vmixer + 2)).pair[0] = 0x00FF;
  (*(spu2_u16pair_t *)((char *)&spu2_regs.u.extra_regs.core0_regs.vmixer + 2)).pair[1] = 0xFF0;
  spu2_regs.u.extra_regs.core1_regs.vmixl.pair[0] = 0xFFFF;
  spu2_regs.u.extra_regs.core1_regs.vmixl.pair[1] = 0xFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixel.pair[0] = -1;
  *(_QWORD *)&spu2_regs.u.extra_regs.core1_regs.vmixel.pair[1] = 0xFFFF00FFFFFF00FFLL;
  (*(spu2_u16pair_t *)((char *)&spu2_regs.u.extra_regs.core1_regs.vmixer + 2)).pair[0] = 0x00FF;
  (*(spu2_u16pair_t *)((char *)&spu2_regs.u.extra_regs.core1_regs.vmixer + 2)).pair[1] = 0xFFC;
  if ( !flag )
  {
    *(_QWORD *)&spu2_regs.u.extra_regs.different_regs[0].mvoll = 0LL;
    *(_QWORD *)&spu2_regs.u.extra_regs.different_regs[1].mvoll = 0LL;
    spu2_regs.u.main_regs.core_regs[0].cregs.eea = 14;
    spu2_regs.u.main_regs.core_regs[1].cregs.eea = 15;
  }
  *(_QWORD *)&spu2_regs.u.extra_regs.different_regs[0].avoll = 0LL;
  *(_QWORD *)&spu2_regs.u.extra_regs.different_regs[1].avoll = 0x7FFF7FFFLL;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401890) --------------------------------------------------------
int __cdecl sceSdVoiceTrans(s16 chan, u16 mode, u8 *iopaddr, u32 *spuaddr, u32 size)
{
  char mode_tmp1; // $s4
  __int16 spuaddr_tmp; // $s5
  char mode_tmp2; // $s6
  int chan_tmp1; // $s2
  int chan_hi; // $s0
  unsigned int unused13; // $a2
  int chan_tmp2; // $s3
  int chan_tmp4; // $v0
  int chan_tmp5; // $v1
  unsigned int dmasize1; // $a2
  int dmaarg; // $a0
  u32 dmasize2; // $s1
  int chan_tmp3; // $v0

  mode_tmp1 = mode;
  spuaddr_tmp = (__int16)spuaddr;
  mode_tmp2 = mode;
  chan_tmp1 = chan & 1;
  if ( !size )
    return -100;
  chan_hi = 16 * chan_tmp1;
  chan_tmp2 = chan_tmp1;
  if ( DmaStartStop((16 * chan_tmp1) | 4, mode, (unsigned int)iopaddr) != 0 )
  {
    return -210;
  }
  if ( VoiceTransIoMode[chan_tmp1] != 1 )
  {
    return -201;
  }
  if ( (mode_tmp1 & 3) != SD_TRANS_WRITE )
  {
    if ( (mode_tmp1 & 3) != SD_TRANS_READ )
      return -100;
    chan_tmp3 = chan_tmp1;
    TransIntrData[chan_tmp3].mode = chan_tmp1 | 0x900;
    BlockHandlerIntrData[chan_tmp3].cb = 0;
    BlockHandlerIntrData[chan_tmp3].userdata = 0;
    VoiceTransStatus[chan_tmp2] = 0;
    DmaStartStop(chan_hi | 2, spuaddr_tmp, unused13);
    if ( QueryIntrContext() )
      iClearEventFlag(VoiceTransCompleteEf[chan_tmp2], 0xFFFFFFFE);
    else
      ClearEventFlag(VoiceTransCompleteEf[chan_tmp2], 0xFFFFFFFE);
    VoiceTransIoMode[chan_tmp1] = 0;
    dmasize1 = size >> 6 << 6;
    if ( (size & 0x3F) != 0 )
      dmasize1 += 64;
    dmaarg = (16 * chan_tmp1) | 5;
    return DmaStartStop(dmaarg, (unsigned __int16)iopaddr, dmasize1);
  }
  chan_tmp4 = chan_tmp1;
  TransIntrData[chan_tmp4].mode = chan_tmp1 | 0x500;
  BlockHandlerIntrData[chan_tmp4].cb = 0;
  BlockHandlerIntrData[chan_tmp4].userdata = 0;
  DmaStartStop(chan_hi | 2, spuaddr_tmp, unused13);
  if ( QueryIntrContext() )
    iClearEventFlag(VoiceTransCompleteEf[chan_tmp2], 0xFFFFFFFE);
  else
    ClearEventFlag(VoiceTransCompleteEf[chan_tmp2], 0xFFFFFFFE);
  chan_tmp5 = chan_tmp1;
  VoiceTransIoMode[chan_tmp1] = 0;
  if ( (mode_tmp2 & SD_TRANS_MODE_IO) == 0 )
  {
    VoiceTransStatus[chan_tmp5] = 0;
    dmasize1 = size >> 6 << 6;
    if ( (size & 0x3F) != 0 )
      dmasize1 += 64;
    dmaarg = (16 * chan_tmp1) | 6;
    return DmaStartStop(dmaarg, (unsigned __int16)iopaddr, dmasize1);
  }
  VoiceTransStatus[chan_tmp5] = 1;
  dmasize2 = size >> 6 << 6;
  if ( (size & 0x3F) != 0 )
    dmasize2 = (size >> 6 << 6) + 64;
  VoiceTrans_Write_IOMode((__int16 *)iopaddr, dmasize2, chan_tmp1);
  return dmasize2;
}
// 401958: variable 'unused13' is possibly undefined

//----- (00401B10) --------------------------------------------------------
u32 __cdecl sceSdVoiceTransStatus(s16 channel, s16 flag)
{
  int channel_tmp; // $s2
  int status_offset; // $s0
  int channel_hi; // $v0
  bool condtmp; // dc
  int efres[2]; // [sp+10h] [-8h] BYREF

  channel_tmp = channel;
  status_offset = channel << 16 >> 14;
  if ( *(int *)((char *)VoiceTransStatus + status_offset) == 1
    || *(int *)((char *)VoiceTransIoMode + status_offset) == 1 )
  {
    return 1;
  }
  if ( flag )
  {
    channel_hi = channel << 16;
    if ( flag == 1 )
    {
      condtmp = QueryIntrContext() != 0;
      if ( condtmp )
        return -202;
      WaitEventFlag(*(int *)((char *)VoiceTransCompleteEf + status_offset), 1u, 0, (u32 *)efres);
      goto LABEL_9;
    }
  }
  else
  {
    channel_hi = channel << 16;
    if ( *(int *)((char *)VoiceTransCompleteBool + status_offset) )
    {
LABEL_9:
      *(int *)((char *)VoiceTransCompleteBool + status_offset) = 0;
      *(int *)((char *)VoiceTransIoMode + status_offset) = 1;
      channel_hi = channel_tmp << 16;
    }
  }
  return *(int *)((char *)VoiceTransIoMode + (channel_hi >> 14));
}
// 401B10: using guessed type u32 efres[2];

//----- (00401C08) --------------------------------------------------------
int __cdecl sceSdStopTrans(int channel)
{
  unsigned int unused1; // $a1
  unsigned int unused2; // $a2
  int chan_tmp1; // $a0
  int chan_tmp2; // $v0

  chan_tmp1 = channel & 1;
  chan_tmp2 = chan_tmp1;
  TransIntrData[chan_tmp2].mode = chan_tmp1;
  BlockHandlerIntrData[chan_tmp2].cb = 0;
  BlockHandlerIntrData[chan_tmp2].userdata = 0;
  return DmaStartStop((16 * chan_tmp1) | 0xA, unused1, unused2);
}
// 401C54: variable 'unused1' is possibly undefined
// 401C54: variable 'unused2' is possibly undefined

//----- (00401C70) --------------------------------------------------------
int sceSdBlockTrans(s16 chan, u16 mode, u8 *iopaddr, u32 size, ...)
{
  int core; // $s0
  char chan_tmp2; // $s6
  u32 started; // $v1
  __int16 unused10; // $a1
  unsigned int unused11; // $a2
  int transfer_dir; // $a0
  int core_tmp3; // $a2
  int startaddr; // $a3
  va_list ramva; // $v0
  void **ramva_usrdat; // $v0
  void *blockhandlercb_1; // $a1
  void *blockhandleruserdata_1; // $v0
  unsigned int retres_2; // $v0
  int retres_1; // $s2
  int core_tmp1; // $a0
  void *cleanuserdata; // $v0
  u8 *iopaddr_tmp1; // $a0
  int core_tmp4; // $v0
  int core_tmp2; // $v0
  void *cleancb; // [sp+58h] [+38h] BYREF
  void *cleanuserdata_1; // [sp+5Ch] [+3Ch] BYREF
  va_list va2; // [sp+60h] [+40h] BYREF
  va_list cleancba; // [sp+58h] [+38h]
  va_list cleanuserdata_1a; // [sp+5Ch] [+3Ch]

  va_start(va2, size);
  va_start(cleanuserdata_1a, size);
  va_start(cleancba, size);
  cleancb = va_arg(cleanuserdata_1a, void *);
  va_copy(va2, cleanuserdata_1a);
  cleanuserdata_1 = va_arg(va2, void *);
  core = chan & 1;
  chan_tmp2 = chan;
  started = DmaStartStop((16 * core) | 4, mode, (unsigned int)iopaddr);
  transfer_dir = mode & 3;
  if ( transfer_dir == SD_TRANS_READ )
  {
    if ( !size )
    {
      return -100;
    }
    if ( started )
    {
      return -210;
    }
    core_tmp1 = core;
    TransIntrData[core_tmp1].mode = core | 0xA00;
    BlockHandlerIntrData[core_tmp1].cb = 0;
    BlockHandlerIntrData[core_tmp1].userdata = 0;
    if ( (mode & 0x80) != 0 )
    {
      cleanuserdata = cleanuserdata_1;
      if ( !cleancb )
      {
        TransIntrData[core_tmp1].mode = core;
        return -100;
      }
      BlockHandlerIntrData[core_tmp1].cb = cleancb;
      BlockHandlerIntrData[core_tmp1].userdata = cleanuserdata;
      TransIntrData[core_tmp1].mode |= 0x8000u;
      iopaddr_tmp1 = iopaddr;
    }
    else
    {
      if ( (mode & SD_TRANS_LOOP) != 0 )
      {
        size >>= 1;
        TransIntrData[core_tmp1].mode |= 0x1000u;
      }
      iopaddr_tmp1 = iopaddr;
    }
    retres_1 = BlockTransRead((u32)iopaddr_tmp1, size, core, mode);
    goto LABEL_31;
  }
  else
  {
    if ( (mode & 3u) >= SD_TRANS_STOP )
    {
      if ( transfer_dir == SD_TRANS_STOP )
      {
        core_tmp2 = core;
        BlockHandlerIntrData[core_tmp2].cb = 0;
        BlockHandlerIntrData[core_tmp2].userdata = 0;
        TransIntrData[core_tmp2].mode = core;
        return DmaStartStop((16 * core) | 0xA, unused10, unused11);
      }
      if ( transfer_dir != SD_TRANS_WRITE_FROM )
        return -100;
    }
    else
    {
      if ( (mode & 3) != SD_TRANS_WRITE )
        return -100;
    }
    if ( !size )
    {
      return -100;
    }
    if ( started )
    {
      return -210;
    }
    core_tmp3 = core;
    TransIntrData[core].mode = core | 0x600;
    startaddr = 0;
    if ( transfer_dir == SD_TRANS_WRITE_FROM )
      startaddr = (int)cleancb;
    BlockHandlerIntrData[core_tmp3].cb = 0;
    BlockHandlerIntrData[core_tmp3].userdata = 0;
    if ( (mode & 0x80) != 0 )
    {
      va_copy(ramva, cleancba);
      if ( transfer_dir == SD_TRANS_WRITE_FROM )
      {
        va_copy(ramva, cleanuserdata_1a);
        startaddr = (int)cleancb;
      }
      ramva_usrdat = (void **)(((unsigned int)ramva + 3) & ~3u);
      blockhandlercb_1 = *ramva_usrdat;
      blockhandleruserdata_1 = *(void **)(((unsigned int)ramva_usrdat + 7) & ~3u);
      if ( !blockhandlercb_1 )
      {
        TransIntrData[core_tmp3].mode = core;
        return -100;
      }
      BlockHandlerIntrData[core_tmp3].cb = blockhandlercb_1;
      BlockHandlerIntrData[core_tmp3].userdata = blockhandleruserdata_1;
      TransIntrData[core_tmp3].mode |= 0x8000u;
      retres_2 = BlockTransWriteFrom((u32)iopaddr, size, chan_tmp2, mode, startaddr);
    }
    else
    {
      if ( (mode & SD_TRANS_LOOP) != 0 )
      {
        size >>= 1;
        TransIntrData[core_tmp3].mode |= 0x1000u;
      }
      retres_2 = BlockTransWriteFrom((u32)iopaddr, size, chan_tmp2, mode, startaddr);
    }
    retres_1 = retres_2;
LABEL_31:
    if ( retres_1 < 0 )
    {
      core_tmp4 = core;
      BlockHandlerIntrData[core_tmp4].cb = 0;
      BlockHandlerIntrData[core_tmp4].userdata = 0;
      TransIntrData[core_tmp4].mode = core;
    }
    return retres_1;
  }
}
// 401FE8: variable 'unused10' is possibly undefined
// 401FE8: variable 'unused11' is possibly undefined

//----- (00402024) --------------------------------------------------------
u32 __cdecl sceSdBlockTransStatus(s16 channel, s16 flag)
{
  return thunk_sceSdBlockTransStatus(channel);
}

//----- (00402050) --------------------------------------------------------
void some_stkclr()
{
  ;
}

//----- (0040206C) --------------------------------------------------------
int InitSpdif()
{
  vu16 statx; // $v0
  unsigned int loopi; // $s0
  vu16 statxtmp; // $v0

  spu2_regs.u.extra_regs.spdif_out = 0;
  libsd_do_busyloop_1(2);
  spu2_regs.u.extra_regs.spdif_out = 0x8000;
  libsd_do_busyloop_1(1);
  *(_DWORD *)&spu2_regs.u.extra_regs.different_regs[0].mvoll = 0;
  *(_DWORD *)&spu2_regs.u.extra_regs.different_regs[1].mvoll = 0;
  spu2_regs.u.main_regs.core_regs[0].cregs.admas = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.admas = 0;
  spu2_regs.u.main_regs.core_regs[0].cregs.attr = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.attr = 0;
  libsd_do_busyloop_1(1);
  spu2_regs.u.main_regs.core_regs[0].cregs.attr = 0x8000;
  spu2_regs.u.main_regs.core_regs[1].cregs.attr = 0x8000;
  *(_DWORD *)&spu2_regs.u.extra_regs.different_regs[0].mvoll = 0;
  *(_DWORD *)&spu2_regs.u.extra_regs.different_regs[1].mvoll = 0;
  statx = spu2_regs.u.main_regs.core_regs[0].cregs.statx;
  loopi = 0;
  while ( 1 )
  {
    ++loopi;
    if ( (statx & 0x7FF) == 0 )
    {
      statxtmp = spu2_regs.u.main_regs.core_regs[1].cregs.statx;
      if ( (statxtmp & 0x7FF) == 0 )
        break;
    }
    if ( loopi >= 0xF01 )
      break;
    libsd_do_busyloop_1(1);
    statx = spu2_regs.u.main_regs.core_regs[0].cregs.statx;
  }
  spu2_regs.u.extra_regs.core0_regs.koff.pair[0] = 0xFFFF;
  spu2_regs.u.extra_regs.core0_regs.koff.pair[1] = 0xFF;
  spu2_regs.u.extra_regs.core1_regs.koff.pair[0] = 0xFFFF;
  spu2_regs.u.extra_regs.core1_regs.koff.pair[1] = 0xFF;
  *(_QWORD *)spu2_regs.u.extra_regs.core0_regs.pmon.pair = 0LL;
  *(_QWORD *)spu2_regs.u.extra_regs.core1_regs.pmon.pair = 0LL;
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (0040225C) --------------------------------------------------------
void SetDmaWrite(int chan)
{
  u8 *dmachanptr; // $a0

  dmachanptr = &iop_mmio_hwport.unv_1024[1024 * chan - 16];
  *(_DWORD *)dmachanptr = *(_DWORD *)dmachanptr & ~0xF000000u;
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;

//----- (00402284) --------------------------------------------------------
void SetDmaRead(int chan)
{
  u8 *dmachanptr; // $a0

  dmachanptr = &iop_mmio_hwport.unv_1024[1024 * chan - 16];
  *(_DWORD *)dmachanptr = (*(_DWORD *)dmachanptr & ~0xF000000u) | 0x2000000;
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;

//----- (004022B4) --------------------------------------------------------
void libsd_do_busyloop_2()
{
  int i; // [sp+0h] [-8h]
  int loopmul; // [sp+4h] [-4h]

  loopmul = 13;
  for ( i = 0; ; ++i )
  {
    if ( i >= 120 )
      break;
    loopmul *= 13;
  }
}

//----- (00402310) --------------------------------------------------------
void libsd_do_busyloop_1(int a1)
{
  int i; // $s0

  for ( i = 0; i < a1; i += 1 )
  {
    libsd_do_busyloop_2();
    ++i;
  }
}

//----- (00402358) --------------------------------------------------------
u32 __fastcall DmaStartStop(int mainarg, unsigned int vararg2, unsigned int vararg3)
{
  int core_tmp1; // $s1
  int attroffs; // $s2
  int dma_coreoffs1; // $s6
  int dma_coreoffs2; // $s5
  u8 *p_dmac_chcr; // $s3
  unsigned int tsa_tmp; // $t1
  int dmarw_rval; // $t0
  unsigned int vararg3_cal; // $a0
  u32 blocktransbufitem; // $s7
  int dmamagictmp; // $s5
  int statxoffs; // $a0
  _WORD *statxptr; // $v1
  unsigned int waittmp2; // $a0
  vu16 *attrptr; // $s0
  unsigned int waittmp1; // $a0
  vu16 *admasptr; // $v1
  int hichk; // $s0
  bool condtmp; // dc
  int core_tmp2; // $v0
  int core_tmp3; // $v0
  int state; // [sp+14h] [-4h] BYREF

  core_tmp1 = mainarg >> 4;
  attroffs = mainarg >> 4 << 9;
  dma_coreoffs1 = 272 * (mainarg >> 4);
  dma_coreoffs2 = 544 * (mainarg >> 4);
  p_dmac_chcr = &iop_mmio_hwport.unv_10f8[1088 * (mainarg >> 4) - 48];
  switch ( mainarg & 0xF )
  {
    case 2:
      tsa_tmp = (vararg2 >> 1) & ~7u;
      spu2_regs.u.main_regs.core_regs[mainarg >> 4].cregs.tsa.pair[1] = tsa_tmp;
      spu2_regs.u.main_regs.core_regs[mainarg >> 4].cregs.tsa.pair[0] = (tsa_tmp >> 16) & 0xFFFF;
      return 0;
    case 4:
      if ( (spu2_regs.u.main_regs.core_regs[mainarg >> 4].cregs.attr & SD_DMA_IN_PROCESS) != 0 )
        return -1;
      if ( (*(_DWORD *)p_dmac_chcr & SD_DMA_START) != 0 )
        return -1;
      if ( spu2_regs.u.main_regs.core_regs[mainarg >> 4].cregs.admas )
        return -1;
      return 0;
    case 5:
      CpuSuspendIntr(&state);
      *(&spu2_regs.u.main_regs.core_regs[0].cregs.attr + attroffs) |= SD_DMA_READ;
      CpuResumeIntr(state);
      SetDmaRead(core_tmp1);
      dmarw_rval = SD_DMA_START|SD_DMA_CS;
      goto LABEL_9;
    case 6:
      CpuSuspendIntr(&state);
      *(&spu2_regs.u.main_regs.core_regs[0].cregs.attr + attroffs) = (*(&spu2_regs.u.main_regs.core_regs[0].cregs.attr
                                                                     + attroffs) & ~SD_CORE_DMA) | SD_DMA_WRITE;
      CpuResumeIntr(state);
      SetDmaWrite(core_tmp1);
      dmarw_rval = SD_DMA_START|SD_DMA_CS|SD_DMA_DIR_IOP2SPU;
LABEL_9:
      vararg3_cal = (vararg3 >> 6) + ((vararg3 & 0x3F) != 0);
      *(_DWORD *)&iop_mmio_hwport.unv_10f8[4 * dma_coreoffs1 - 56] = vararg2;
      *(_WORD *)&iop_mmio_hwport.unv_10f8[2 * dma_coreoffs2 - 52] = 16;
      *(_WORD *)&iop_mmio_hwport.unv_10f8[2 * dma_coreoffs2 - 50] = vararg3_cal;
      *(_DWORD *)p_dmac_chcr = dmarw_rval;
      return vararg3_cal << 6;
    case 0xA:
      blocktransbufitem = 0;
      dmamagictmp = 0;
      if ( (*(_DWORD *)p_dmac_chcr & SD_DMA_START) != 0 )
      {
        blocktransbufitem = BlockTransBuff[core_tmp1];
        dmamagictmp = *(_DWORD *)&iop_mmio_hwport.unv_10f8[1088 * (mainarg >> 4) - 56];
        statxoffs = mainarg >> 4 << 10;
        *(_DWORD *)p_dmac_chcr &= ~SD_DMA_START;
        if ( (*(&spu2_regs.u.main_regs.core_regs[0].cregs.attr + attroffs) & 0x30) != 0 )
        {
          statxptr = (vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.statx + statxoffs);
          if ( (*(vu16 *)((_BYTE *)&spu2_regs.u.main_regs.core_regs[0].cregs.statx + statxoffs) & 0x80) == 0 )
          {
            waittmp2 = 1;
            do
            {
              if ( waittmp2 > 0x1000000 )
                break;
              ++waittmp2;
            }
            while ( (*statxptr & 0x80) == 0 );
          }
        }
      }
      attrptr = &spu2_regs.u.main_regs.core_regs[0].cregs.attr + attroffs;
      if ( (*attrptr & 0x30) != 0 )
      {
        CpuSuspendIntr(&state);
        *attrptr &= 0xFFCFu;
        CpuResumeIntr(state);
        if ( (*attrptr & 0x30) != 0 )
        {
          waittmp1 = 1;
          do
          {
            if ( waittmp1 >= 0xF01 )
              break;
            ++waittmp1;
          }
          while ( (*attrptr & 0x30) != 0 );
        }
      }
      admasptr = &spu2_regs.u.main_regs.core_regs[0].cregs.admas + attroffs;
      hichk = 0;
      if ( (*admasptr & 7) != 0 )
      {
        hichk = 1;
        *admasptr = 0;
      }
      condtmp = QueryIntrContext() == 0;
      core_tmp2 = core_tmp1;
      if ( condtmp )
        SetEventFlag(VoiceTransCompleteEf[core_tmp2], 1u);
      else
        iSetEventFlag(VoiceTransCompleteEf[core_tmp2], 1u);
      core_tmp3 = core_tmp1;
      VoiceTransCompleteBool[core_tmp3] = 0;
      VoiceTransIoMode[core_tmp3] = 1;
      CleanHandlers[core_tmp3] = 0;
      if ( dmamagictmp )
      {
        if ( hichk )
          return (dmamagictmp & ~0xFF000000) | (blocktransbufitem << 24);
      }
      return 0;
    default:
      return 0;
  }
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (0040280C) --------------------------------------------------------
int __fastcall VoiceTrans_Write_IOMode(__int16 *iopaddr, unsigned int size, int chan)
{
  unsigned int size_tmp; // $s3
  int chan_hi_9; // $fp
  int chan_hi_10; // $s6
  vu16 *p_xferdata_1ac; // $s7
  vu16 *p_attr; // $s5
  BOOL condtmp; // $v0
  int count; // $s2
  int i; // $v1
  vu16 iopaddr_tmp; // $v0
  unsigned int waittmp1; // $s0
  int state; // [sp+14h] [-4h] BYREF

  size_tmp = size;
  chan_hi_9 = chan << 9;
  if ( size )
  {
    chan_hi_10 = chan << 10;
    p_xferdata_1ac = &spu2_regs.u.main_regs.core_regs[chan].cregs.xferdata_1ac;
    p_attr = &spu2_regs.u.main_regs.core_regs[chan].cregs.attr;
    condtmp = size < 0x41;
    do
    {
      count = 64;
      if ( condtmp )
        count = size_tmp;
      for ( i = 0; i < count; *p_xferdata_1ac = iopaddr_tmp )
      {
        iopaddr_tmp = *iopaddr++;
        i += 2;
      }
      CpuSuspendIntr(&state);
      *p_attr = (*p_attr & ~SD_CORE_DMA) | SD_DMA_IO;
      CpuResumeIntr(state);
      if ( (*(vu16 *)((_BYTE *)&spu2_regs.u.main_regs.core_regs[0].cregs.statx + chan_hi_10) & SD_IO_IN_PROCESS) != 0 )
      {
        waittmp1 = 1;
        do
        {
          if ( waittmp1 >= 0xF01 )
            break;
          libsd_do_busyloop_1(1);
          ++waittmp1;
        }
        while ( (*(&spu2_regs.u.main_regs.core_regs[0].cregs.statx + chan_hi_9) & SD_IO_IN_PROCESS) != 0 );
      }
      size_tmp -= count;
      condtmp = size_tmp < 0x41;
    }
    while ( size_tmp );
  }
  CpuSuspendIntr(&state);
  *(&spu2_regs.u.main_regs.core_regs[0].cregs.attr + chan_hi_9) &= ~SD_CORE_DMA;
  CpuResumeIntr(state);
  VoiceTransIoMode[chan] = 1;
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (004029A8) --------------------------------------------------------
int __fastcall do_finish_block_clean_xfer(int a1, int attr_offs_2)
{
  int attr_offs; // $a1
  _WORD *attr_ptr; // $v1
  __int16 attr_ptr_deref; // $v0
  unsigned __int16 *admas_ptr; // $a1

  attr_offs = 2 * attr_offs_2;
  attr_ptr = (vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.attr + attr_offs);
  attr_ptr_deref = *(vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.attr + attr_offs);
  admas_ptr = (vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.admas + attr_offs);
  *attr_ptr = attr_ptr_deref & ~SD_CORE_DMA;
  *admas_ptr = 0;
  return *admas_ptr;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (004029EC) --------------------------------------------------------
int __fastcall TransInterrupt(IntrData *intr)
{
  u32 mode_c00; // $v1
  int no_flush_cache; // $s5
  u32 mode; // $v1
  int mode_1; // $s1
  u32 mode_300; // $a0
  vu16 *p_statx; // $a0
  int waittmp1; // $v1
  vu16 *p_attr; // $a0
  unsigned int waittmp2; // $v1
  int mode_1_tmp1; // $s0
  int unused13; // $a0
  int mode_1_tmp2; // $s0
  int mode_1_tmp3; // $a2
  u32 one_minus_buff; // $a3
  u32 addr_size_tmp; // $t1
  u8 *dmamagictmp3; // $a0
  int mode_1_tmp4; // $v1
  int dmamagictmp1; // [sp+14h] [-Ch] BYREF
  int dmamagictmp2; // [sp+18h] [-8h] BYREF

  mode_c00 = intr->mode & 0xC00;
  if ( mode_c00 == 0x400 )
  {
    no_flush_cache = 1;
  }
  else
  {
    if ( mode_c00 != 0x800 )
      return 1;
    no_flush_cache = 0;
  }
  mode = intr->mode;
  mode_1 = intr->mode & 1;
  mode_300 = intr->mode & 0x300;
  if ( mode_300 == 0x100 )
  {
    p_statx = &spu2_regs.u.main_regs.core_regs[mode_1].cregs.statx;
    if ( (*p_statx & 0x80) == 0 )
    {
      waittmp1 = 1;
      do
      {
        if ( waittmp1 > 0x1000000 )
          break;
        ++waittmp1;
      }
      while ( (*p_statx & 0x80) == 0 );
    }
    p_attr = &spu2_regs.u.main_regs.core_regs[mode_1].cregs.attr;
    *p_attr &= ~SD_CORE_DMA;
    if ( (*p_attr & SD_CORE_DMA) != 0 )
    {
      waittmp2 = 1;
      do
      {
        if ( waittmp2 >= 0xF01 )
          break;
        ++waittmp2;
      }
      while ( (*p_attr & SD_CORE_DMA) != 0 );
    }
    mode_1_tmp1 = mode_1;
    if ( !no_flush_cache )
      FlushDcache();
    if ( CleanHandlers[mode_1_tmp1] )
    {
      ((void (__fastcall *)(int, _DWORD))CleanHandlers[mode_1_tmp1])(mode_1, 0);
      return 1;
    }
    iSetEventFlag(VoiceTransCompleteEf[mode_1_tmp1], 1u);
    if ( TransIntrHandlers[mode_1_tmp1] )
    {
      VoiceTransIoMode[mode_1_tmp1] = 1;
      ((void (__fastcall *)(int, void *))TransIntrHandlers[mode_1_tmp1])(mode_1, intr->data);
      return 1;
    }
    if ( !TransIntrCallbacks[mode_1_tmp1] )
    {
      VoiceTransCompleteBool[mode_1_tmp1] = 1;
      return 1;
    }
    VoiceTransIoMode[mode_1_tmp1] = 1;
    ((void (__fastcall *)(int))TransIntrCallbacks[mode_1_tmp1])(unused13);
    return 1;
  }
  if ( mode_300 != 0x200 )
    return 1;
  mode_1_tmp2 = mode_1;
  if ( (mode & 0x8000) != 0 )
  {
    if ( BlockHandlerIntrData[mode_1_tmp2].cb )
    {
      ((void (__fastcall *)(int, void *, int *, int *))BlockHandlerIntrData[mode_1_tmp2].cb)(
        mode_1,
        BlockHandlerIntrData[mode_1_tmp2].userdata,
        &dmamagictmp1,
        &dmamagictmp2);
      if ( dmamagictmp2 > 0 )
      {
        *(_WORD *)&iop_mmio_hwport.unv_10f8[1088 * mode_1 - 50] = (dmamagictmp2 >> 6)
                                                                + (dmamagictmp2 - (dmamagictmp2 >> 6 << 6) > 0);
        *(_DWORD *)&iop_mmio_hwport.unv_10f8[1088 * mode_1 - 56] = dmamagictmp1;
        *(_DWORD *)&iop_mmio_hwport.unv_10f8[1088 * mode_1 - 48] = no_flush_cache | SD_DMA_START|SD_DMA_CS;
      }
      else
      {
        do_finish_block_clean_xfer(mode_1, mode_1 << 9);
        BlockHandlerIntrData[mode_1_tmp2].cb = 0;
        BlockHandlerIntrData[mode_1_tmp2].userdata = 0;
      }
    }
    else
    {
      do_finish_block_clean_xfer(mode_1, mode_1 << 9);
    }
    if ( !no_flush_cache )
    {
      FlushDcache();
      return 1;
    }
  }
  else
  {
    mode_1_tmp3 = mode_1;
    if ( (mode & 0x1000) != 0 )
    {
      one_minus_buff = 1 - BlockTransBuff[mode_1_tmp3];
      addr_size_tmp = BlockTransAddr[mode_1_tmp3] + one_minus_buff * BlockTransSize[mode_1_tmp3];
      *(_WORD *)&iop_mmio_hwport.unv_10f8[1088 * mode_1 - 50] = (int)BlockTransSize[mode_1_tmp3] / 64
                                                              + ((int)BlockTransSize[mode_1_tmp3] % 64 > 0);
      dmamagictmp3 = &iop_mmio_hwport.unv_10f8[1088 * mode_1 - 56];
      BlockTransBuff[mode_1_tmp3] = one_minus_buff;
      *(_DWORD *)dmamagictmp3 = addr_size_tmp;
      *(_DWORD *)&iop_mmio_hwport.unv_10f8[1088 * mode_1 - 48] = no_flush_cache | SD_DMA_START|SD_DMA_CS;
    }
    else
    {
      do_finish_block_clean_xfer(mode_1, mode_1 << 9);
    }
    mode_1_tmp4 = mode_1;
    if ( !no_flush_cache )
    {
      FlushDcache();
      mode_1_tmp4 = mode_1;
    }
    if ( TransIntrHandlers[mode_1_tmp4] )
    {
      ((void (__fastcall *)(int, void *))TransIntrHandlers[mode_1_tmp4])(mode_1, intr->data);
      return 1;
    }
    if ( TransIntrCallbacks[mode_1_tmp4] )
    {
      ((void (__fastcall *)(u8 *))TransIntrCallbacks[mode_1_tmp4])(dmamagictmp3);
      return 1;
    }
  }
  return 1;
}
// 402BE4: variable 'unused13' is possibly undefined
// 402E84: variable 'dmamagictmp3' is possibly undefined
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00402EB8) --------------------------------------------------------
u32 __fastcall thunk_sceSdBlockTransStatus(int channel)
{
  int dmamagictmp1; // $a2

  dmamagictmp1 = *(_DWORD *)&iop_mmio_hwport.unv_10f8[1088 * channel - 56];
  if ( (spu2_regs.u.main_regs.core_regs[channel].cregs.admas & 7) == 0 )
    dmamagictmp1 = 0;
  return (BlockTransBuff[channel] << 24) | (dmamagictmp1 & ~0xFF000000);
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00402F4C) --------------------------------------------------------
unsigned int __fastcall BlockTransWriteFrom(u32 iopaddr, unsigned int size, char chan, char mode, int startaddr)
{
  int chan_tmp0; // $s2
  int chan_tmp1; // $a1
  u32 startaddr_tmp; // $s3
  signed int size_align; // $s1
  unsigned int other_align; // $v1
  int chan_hi_offs; // $s0
  int size_align_r6; // $v1
  int state; // [sp+14h] [-4h] BYREF

  chan_tmp0 = chan & 1;
  chan_tmp1 = chan_tmp0;
  startaddr_tmp = startaddr;
  BlockTransAddr[chan_tmp1] = iopaddr;
  BlockTransBuff[chan_tmp1] = 0;
  BlockTransSize[chan_tmp1] = size;
  if ( startaddr )
  {
    size_align = size - (startaddr - iopaddr);
    if ( startaddr - iopaddr >= size )
    {
      other_align = startaddr - iopaddr - size;
      if ( (mode & SD_TRANS_LOOP) == 0 || other_align >= size )
        return -100;
      ++BlockTransBuff[chan_tmp1];
      size_align = size - other_align;
    }
    if ( size_align % 1024 > 0 )
    {
      size_align = (size_align / 1024 + 1) << 10;
      startaddr_tmp = iopaddr + BlockTransBuff[chan_tmp0] * size + size - size_align;
    }
  }
  else
  {
    startaddr_tmp = iopaddr;
    size_align = size;
  }
  CpuSuspendIntr(&state);
  chan_hi_offs = chan_tmp0 << 10;
  *(vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.attr + chan_hi_offs) &= ~SD_CORE_DMA;
  CpuResumeIntr(state);
  *(vu16 *)((char *)spu2_regs.u.main_regs.core_regs[0].cregs.tsa.pair + chan_hi_offs) = 0;
  *(vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.tsa.pair[1] + chan_hi_offs) = 0;
  *(vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.admas + chan_hi_offs) = 1 << chan_tmp0;
  SetDmaWrite(chan_tmp0);
  *(_DWORD *)&iop_mmio_hwport.unv_10f8[1088 * chan_tmp0 - 56] = startaddr_tmp;
  *(_WORD *)&iop_mmio_hwport.unv_10f8[1088 * chan_tmp0 - 52] = 16;
  size_align_r6 = size_align >> 6;
  if ( size_align < 0 )
    size_align_r6 = (size_align + 63) >> 6;
  *(_WORD *)&iop_mmio_hwport.unv_10f8[1088 * chan_tmp0 - 50] = size_align_r6 + (size_align - (size_align_r6 << 6) > 0);
  *(_DWORD *)&iop_mmio_hwport.unv_10f8[1088 * chan_tmp0 - 48] = SD_DMA_START|SD_DMA_CS|SD_DMA_DIR_IOP2SPU;
  return size;
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00403174) --------------------------------------------------------
u32 __fastcall BlockTransRead(u32 iopaddr, u32 size, char chan, __int16 mode)
{
  int chan_tmp1; // $s3
  int chan_tmp2; // $s5
  int chan_tmp_offs; // $s0
  int chan_dma_offs_tmp; // $a2
  int state; // [sp+14h] [-4h] BYREF

  chan_tmp1 = chan & 1;
  chan_tmp2 = chan_tmp1;
  BlockTransAddr[chan_tmp2] = iopaddr;
  BlockTransBuff[chan_tmp2] = 0;
  BlockTransSize[chan_tmp2] = size;
  CpuSuspendIntr(&state);
  chan_tmp_offs = chan_tmp1 << 10;
  spu2_regs.u.main_regs.core_regs[chan_tmp1].cregs.attr &= 0xFFCFu;
  CpuResumeIntr(state);
  *(vu16 *)((char *)spu2_regs.u.main_regs.core_regs[0].cregs.tsa.pair + chan_tmp_offs) = 0;
  *(vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.tsa.pair[1] + chan_tmp_offs) = 2 * (mode & ~0xF0FF) + 1024;
  *(vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.unk1ae + chan_tmp_offs) = (unsigned __int16)(mode & ~0xFFF) >> 11;
  libsd_do_busyloop_1(3);
  *(vu16 *)((char *)&spu2_regs.u.main_regs.core_regs[0].cregs.admas + chan_tmp_offs) = 4;
  SetDmaRead(chan_tmp1);
  chan_dma_offs_tmp = 1088 * chan_tmp1;
  *(_DWORD *)&iop_mmio_hwport.unv_10f8[chan_dma_offs_tmp - 56] = iopaddr;
  *(_WORD *)&iop_mmio_hwport.unv_10f8[chan_dma_offs_tmp - 52] = 16;
  *(_WORD *)&iop_mmio_hwport.unv_10f8[chan_dma_offs_tmp - 50] = (int)BlockTransSize[chan_tmp1] / 64
                                                              + ((int)BlockTransSize[chan_tmp1] % 64 > 0);
  *(_DWORD *)&iop_mmio_hwport.unv_10f8[chan_dma_offs_tmp - 48] = SD_DMA_START|SD_DMA_CS;
  return size;
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00403340) --------------------------------------------------------
int __fastcall SifDmaBatch(void *ee_addr, void *iop_addr, int size)
{
  int dmat; // $s2
  int waitcnt; // $s1
  int dma_status; // $s0
  SifDmaTransfer_t xferparam; // [sp+10h] [-18h] BYREF
  int state; // [sp+20h] [-8h] BYREF

  xferparam.dest = ee_addr;
  xferparam.src = iop_addr;
  xferparam.size = size;
  xferparam.attr = 0;
  CpuSuspendIntr(&state);
  dmat = sceSifSetDma(&xferparam, 1);
  CpuResumeIntr(state);
  waitcnt = 0;
  if ( !dmat )
    return -1;
  while ( 1 )
  {
    CpuSuspendIntr(&state);
    dma_status = sceSifDmaStat(dmat);
    CpuResumeIntr(state);
    ++waitcnt;
    if ( dma_status < 0 )
      break;
    if ( waitcnt < 0 )
      return -1;
  }
  return 0;
}

//----- (004033FC) --------------------------------------------------------
int __cdecl sceSdProcBatch(sceSdBatch *batch, u32 *rets, u32 num)
{
  unsigned int retres; // $s2
  u32 *rets_cr; // $s3
  int loop; // $s4
  u32 Param; // $s1
  u32 *batchdat_tmp; // $a1
  void *value; // $a0
  int entry; // $a2

  retres = 0;
  if ( num )
  {
    rets_cr = rets;
    loop = -1;
    while ( 2 )
    {
      Param = 0;
      switch ( batch->func )
      {
        case SD_BATCH_SETPARAM:
          sceSdSetParam(batch->entry, batch->value);
          goto LABEL_17;
        case SD_BATCH_SETSWITCH:
          sceSdSetSwitch(batch->entry, batch->value);
          goto LABEL_17;
        case SD_BATCH_SETADDR:
          sceSdSetAddr(batch->entry, batch->value);
          goto LABEL_17;
        case SD_BATCH_SETCORE:
          sceSdSetCoreAttr(batch->entry, batch->value);
          goto LABEL_17;
        case SD_BATCH_WRITEIOP:
          *(_DWORD *)batch->value = batch->entry;
          goto LABEL_17;
        case SD_BATCH_WRITEEE:
          batchdat_tmp = &BatchData;
          value = (void *)batch->value;
          BatchData = batch->entry;
          entry = 4;
          goto LABEL_15;
        case SD_BATCH_EERETURN:
          value = (void *)batch->value;
          entry = batch->entry;
          batchdat_tmp = rets;
LABEL_15:
          Param = SifDmaBatch(value, batchdat_tmp, entry);
          goto LABEL_17;
        case SD_BATCH_GETPARAM|SD_BATCH_SETPARAM:
          Param = sceSdGetParam(batch->entry);
          goto LABEL_17;
        case SD_BATCH_GETSWITCH:
          Param = sceSdGetSwitch(batch->entry);
          goto LABEL_17;
        case SD_BATCH_GETADDR:
          Param = sceSdGetAddr(batch->entry);
          goto LABEL_17;
        case SD_BATCH_GETCORE:
          Param = sceSdGetCoreAttr(batch->entry);
LABEL_17:
          if ( rets )
            *rets_cr = Param;
          ++rets_cr;
          --loop;
          ++retres;
          ++batch;
          if ( retres >= num )
            return retres;
          continue;
        default:
          return loop;
      }
    }
  }
  return retres;
}

//----- (004035E8) --------------------------------------------------------
int __cdecl sceSdProcBatchEx(sceSdBatch *batch, u32 *rets, u32 num, u32 voice)
{
  u32 retres_flip; // $s7
  int loop; // $s3
  u32 Param; // $s4
  int voicei1; // $s0
  int voicei3; // $s0
  u32 *retsptrtmp1; // $s1
  int voicei2; // $s0
  int voicei4; // $s0
  u32 *retsptrtmp2; // $s1
  u32 Addr; // $v0
  u32 *batchdat_tmp; // $a1
  void *value; // $a0
  int entry; // $a2

  retres_flip = 0;
  loop = 0;
  if ( num )
  {
    while ( 2 )
    {
      Param = 0;
      switch ( batch->func )
      {
        case SD_BATCH_SETPARAM:
          voicei1 = 0;
          if ( (batch->entry & 0x3E) == 0x3E )
          {
            do
            {
              if ( ((1 << voicei1) & voice) != 0 )
              {
                ++loop;
                sceSdSetParam((batch->entry & ~0x3E) | (2 * voicei1), batch->value);
              }
              ++voicei1;
            }
            while ( voicei1 < 24 );
            --loop;
          }
          else
          {
            sceSdSetParam(batch->entry, batch->value);
          }
          goto LABEL_42;
        case SD_BATCH_SETSWITCH:
          sceSdSetSwitch(batch->entry, batch->value);
          goto LABEL_42;
        case SD_BATCH_SETADDR:
          voicei2 = 0;
          if ( (*(_DWORD *)&batch->func & 0x7E0000) == 0x7E0000 )
          {
            do
            {
              if ( ((1 << voicei2) & voice) != 0 )
              {
                ++loop;
                sceSdSetAddr((batch->entry & ~0x3E | (2 * voicei2)), batch->value);
              }
              ++voicei2;
            }
            while ( voicei2 < 24 );
            --loop;
          }
          else
          {
            sceSdSetAddr(batch->entry, batch->value);
          }
          goto LABEL_42;
        case SD_BATCH_SETCORE:
          sceSdSetCoreAttr(batch->entry, batch->value);
          goto LABEL_42;
        case SD_BATCH_WRITEIOP:
          *(_DWORD *)batch->value = batch->entry;
          goto LABEL_42;
        case SD_BATCH_WRITEEE:
          batchdat_tmp = &BatchData;
          value = (void *)batch->value;
          BatchData = batch->entry;
          entry = 4;
          goto LABEL_40;
        case SD_BATCH_EERETURN:
          value = (void *)batch->value;
          entry = batch->entry;
          batchdat_tmp = rets;
LABEL_40:
          Param = SifDmaBatch(value, batchdat_tmp, entry);
          goto LABEL_42;
        case SD_BATCH_GETPARAM|SD_BATCH_SETPARAM:
          voicei3 = 0;
          if ( (batch->entry & 0x3E) == 0x3E )
          {
            retsptrtmp1 = &rets[loop];
            do
            {
              if ( ((1 << voicei3) & voice) != 0 )
                Param = sceSdGetParam((batch->entry & ~0x3E) | (2 * voicei3));
              if ( rets )
                *retsptrtmp1 = Param;
              ++retsptrtmp1;
              ++voicei3;
              ++loop;
            }
            while ( voicei3 < 24 );
            --loop;
          }
          else
          {
            Param = sceSdGetParam(batch->entry);
          }
          goto LABEL_42;
        case SD_BATCH_GETSWITCH:
          Param = sceSdGetSwitch(batch->entry);
          goto LABEL_42;
        case SD_BATCH_GETADDR:
          voicei4 = 0;
          if ( (*(_DWORD *)&batch->func & 0x7E0000) == 0x7E0000 )
          {
            retsptrtmp2 = &rets[loop];
            do
            {
              if ( ((1 << voicei4) & voice) != 0 )
              {
                Addr = sceSdGetAddr((batch->entry & ~0x3E) | (2 * voicei4));
                Param = Addr;
                if ( rets )
                  *retsptrtmp2 = Addr;
                ++retsptrtmp2;
                ++loop;
              }
              ++voicei4;
            }
            while ( voicei4 < 24 );
            --loop;
          }
          else
          {
            Param = sceSdGetAddr(batch->entry);
          }
          goto LABEL_42;
        case SD_BATCH_GETCORE:
          Param = sceSdGetCoreAttr(batch->entry);
LABEL_42:
          if ( rets )
            rets[loop] = Param;
          ++batch;
          ++retres_flip;
          ++loop;
          if ( retres_flip >= num )
            return loop;
          continue;
        default:
          return ~retres_flip;
      }
    }
  }
  return loop;
}

//----- (004039A0) --------------------------------------------------------
void __cdecl sceSdSetParam(u16 entry, u16 value)
{
  *(vu16 *)((char *)&(*(vu16 **)((char *)ParamRegList + ((entry >> 6) & 0x3FC)))[4 * (entry & 0x3E)]
          + (entry & 1) * (1024 - 984 * ((entry & 0x80) != 0))) = value;
}

//----- (004039FC) --------------------------------------------------------
u16 __cdecl sceSdGetParam(u16 entry)
{
  return *(vu16 *)((char *)&(*(vu16 **)((char *)ParamRegList + ((entry >> 6) & 0x3FC)))[4 * (entry & 0x3E)]
                 + (entry & 1) * (1024 - 984 * ((entry & 0x80) != 0)));
}

//----- (00403A5C) --------------------------------------------------------
void __cdecl sceSdSetSwitch(u16 entry, u32 value)
{
  vu16 *regptr; // $v0

  regptr = &(*(vu16 **)((char *)ParamRegList + ((entry >> 6) & 0x3FC)))[512 * (entry & 1)];
  *regptr = value;
  regptr[1] = (value >> 16) & 0xFF;
}

//----- (00403A94) --------------------------------------------------------
u32 __cdecl sceSdGetSwitch(u16 entry)
{
  vu16 *regptr; // $a0

  regptr = &(*(vu16 **)((char *)ParamRegList + ((entry >> 6) & 0x3FC)))[512 * (entry & 1)];
  return *regptr | (regptr[1] << 16);
}

//----- (00403ACC) --------------------------------------------------------
void __cdecl sceSdSetAddr(u16 entry, u32 value)
{
  vu16 *reg1; // $a1
  _WORD *reg1_hi; // $a1

  reg1 = &(*(vu16 **)((char *)ParamRegList + ((entry >> 6) & 0x3FC)))[512 * (entry & 1) + 3 * (entry & 0x3E)];
  *reg1 = value >> 17;
  reg1_hi = reg1 + 1;
  if ( (entry & 0xFF00) != 0x1D00 )
    *reg1_hi = (value >> 1) & ~7;
}

//----- (00403B30) --------------------------------------------------------
u32 __cdecl sceSdGetAddr(u16 entry)
{
  int retlo; // $a3
  vu16 *reg1; // $a1
  int regmask; // $a0
  int rethi; // $a2

  retlo = 0x1FFFF;
  reg1 = &(*(vu16 **)((char *)ParamRegList + ((entry >> 6) & 0x3FC)))[512 * (entry & 1) + 3 * (entry & 0x3E)];
  regmask = entry & 0xFF00;
  rethi = *reg1 << 17;
  if ( regmask != 0x1D00 )
  {
    retlo = 2 * reg1[1];
    if ( regmask == 0x2100 || regmask == 0x2200 )
    {
      rethi = *reg1 << 17;
      retlo = 2 * reg1[1];
    }
  }
  return rethi | retlo;
}

//----- (00403BD0) --------------------------------------------------------
u16 __cdecl sceSdNote2Pitch(u16 center_note, u16 center_fine, u16 note, s16 fine)
{
  int fine_x1; // $a3
  int fine_x2; // $v0
  int fine_x3; // $a1
  __int64 fine_x4; // kr00_8
  int fine_x5; // $a2
  int fine_x6; // $a3
  int fine_x7; // $v1
  __int16 offset2; // $t0
  int fine_x9; // $a1
  int offset1; // $a0
  int fine_x10_hi; // $v0
  int retval; // $a1

  fine_x1 = fine + center_fine;
  fine_x2 = (note + fine_x1 / 128 - center_note) << 16;
  fine_x3 = (__int16)(note + fine_x1 / 128 - center_note);
  fine_x4 = 0x2AAAAAABLL * (__int16)(note + fine_x1 / 128 - center_note);
  fine_x5 = fine_x1 / 128;
  fine_x6 = fine_x1 % 128;
  fine_x7 = ((fine_x4 >> 32) >> 1) - (fine_x2 >> 31);
  offset2 = fine_x7 - 2;
  fine_x9 = fine_x3 - 12 * fine_x7;
  offset1 = fine_x9;
  if ( (fine_x9 & 0x8000u) == 0 )
  {
    if ( (_WORD)fine_x9 )
      goto LABEL_5;
    fine_x10_hi = fine_x9 << 16;
    if ( fine_x6 >= 0 )
      goto LABEL_7;
  }
  offset1 = fine_x9 + 12;
  offset2 = fine_x7 - 3;
LABEL_5:
  fine_x10_hi = offset1 << 16;
  if ( fine_x6 < 0 )
  {
    fine_x6 += (fine_x5 + 1) << 7;
    fine_x10_hi = (offset1 - 1 + fine_x5) << 16;
  }
LABEL_7:
  retval = (*(unsigned __int16 *)((char *)NotePitchTable + (fine_x10_hi >> 15))
          * (unsigned __int16)NotePitchTable[fine_x6 + 12]) >> 16;
  if ( offset2 < 0 )
    return (unsigned int)(retval + (1 << (-offset2 - 1))) >> -offset2;
  return retval;
}

//----- (00403CE4) --------------------------------------------------------
u16 __cdecl sceSdPitch2Note(u16 center_note, u16 center_fine, u16 pitch)
{
  __int16 bit; // $t1
  unsigned __int16 i4; // $t2
  __int16 offset2; // $t0
  int i1; // $a3
  int pitch_tmp; // $v0
  int val; // $a2
  int i2; // $a3
  int i3; // $v0
  int i5; // $a3

  bit = 0;
  i4 = 0;
  offset2 = 0;
  if ( pitch >= 0x4000u )
    pitch = 0x3FFF;
  i1 = 0;
  pitch_tmp = pitch & 0xFF;
  do
  {
    if ( (pitch_tmp & 1) != 0 )
      bit = i1;
    pitch_tmp = (int)pitch >> ++i1;
  }
  while ( i1 < 14 );
  val = pitch << (15 - bit);
  i2 = 11;
  i3 = 11;
  while ( (unsigned __int16)val < (unsigned int)(unsigned __int16)NotePitchTable[i3] )
  {
    i3 = --i2;
    if ( i2 < 0 )
      goto LABEL_11;
  }
  i4 = i2;
LABEL_11:
  if ( !NotePitchTable[i4] )
    __builtin_trap();
  i5 = 127;
  while ( (unsigned __int16)(((unsigned __int16)val << 15) / (unsigned int)(unsigned __int16)NotePitchTable[i4]) < (unsigned int)(unsigned __int16)NotePitchTable[i5 + 12] )
  {
    if ( --i5 < 0 )
      return (((center_fine + offset2 + 1) & 0x7E)
            + ((i4 + center_note + 12 * (bit - 12) + ((unsigned __int16)(center_fine + offset2 + 1) >> 7)) << 8)) & ~1;
  }
  offset2 = i5;
  return (((center_fine + offset2 + 1) & 0x7E)
        + ((i4 + center_note + 12 * (bit - 12) + ((unsigned __int16)(center_fine + offset2 + 1) >> 7)) << 8)) & ~1;
}

//----- (00403E20) --------------------------------------------------------
int __fastcall SetSpdifMode(int val)
{
  vu16 spdif_out; // $t0
  int val_mask; // $v1
  vu16 spdif_mode; // $a1
  __int16 out_mask_fe57_1; // $a2
  vu16 out_mask_fe57_2; // $t0
  __int16 mode_mask_fff9_1; // $a3
  __int16 mode_mask_fff9_2; // $a1
  __int16 out_mask_apply_8000; // $a1
  vu16 out_mask_hoge_c0ff; // $a1

  spdif_out = spu2_regs.u.extra_regs.spdif_out;
  val_mask = val & 0xF;
  spdif_mode = spu2_regs.u.extra_regs.spdif_mode;
  out_mask_fe57_1 = spdif_out & ~0x1A8;
  out_mask_fe57_2 = spdif_out & ~0x1A8;
  mode_mask_fff9_1 = spdif_mode & ~6;
  mode_mask_fff9_2 = spdif_mode & ~6;
  if ( val_mask == 1 )
  {
    out_mask_fe57_2 = out_mask_fe57_1 | 0x100;
    mode_mask_fff9_2 = mode_mask_fff9_1 | 2;
  }
  else if ( (val & 0xFu) >= 2 )
  {
    if ( val_mask != 2 )
    {
      if ( val_mask != 3 )
        return -100;
      out_mask_fe57_2 = out_mask_fe57_1 | 0x100;
    }
  }
  else
  {
    if ( (val & 0xF) != 0 )
      return -100;
    out_mask_fe57_2 = out_mask_fe57_1 | 0x20;
  }
  if ( (val & 0x80) != 0 )
    out_mask_apply_8000 = mode_mask_fff9_2 | 0x8000;
  else
    out_mask_apply_8000 = mode_mask_fff9_2 & ~0x8000;
  if ( (val & 0xF00) == 2048 )
  {
    spu2_regs.u.extra_regs.spdif_media = 512;
    out_mask_hoge_c0ff = (out_mask_apply_8000 & ~0x3F00) | 0x1900;
  }
  else if ( (val & 0xF00) == 1024 )
  {
    spu2_regs.u.extra_regs.spdif_media = 0;
    out_mask_hoge_c0ff = (out_mask_apply_8000 & ~0x3F00) | 0x100;
  }
  else
  {
    spu2_regs.u.extra_regs.spdif_media = 512;
    out_mask_hoge_c0ff = (out_mask_apply_8000 & ~0x3F00) | 0x900;
  }
  spu2_regs.u.extra_regs.spdif_out = out_mask_fe57_2;
  spu2_regs.u.extra_regs.spdif_mode = out_mask_hoge_c0ff;
  SpdifSettings = val;
  return 0;
}
// 4055E0: using guessed type int SpdifSettings;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00403F50) --------------------------------------------------------
void sceSdSetCoreAttr_default(char entry, char val)
{
  __int16 setting_tmp; // $s1
  u16 param_tmp; // $s0
  u16 Param; // $v0
  int state; // [sp+10h] [-8h] BYREF

  setting_tmp = *(_WORD *)((char *)&SpdifSettings + (entry & 0xE) + 2);// should point to CoreAttrShifts
  CpuSuspendIntr(&state);
  param_tmp = (entry & 1) | 0x2300;
  Param = sceSdGetParam(param_tmp);
  sceSdSetParam(param_tmp, (Param & ~(1 << setting_tmp)) | ((val & 1) << setting_tmp));
  CpuResumeIntr(state);
}
// 4055E0: using guessed type int SpdifSettings;

//----- (00403FEC) --------------------------------------------------------
void __cdecl sceSdSetCoreAttr(u16 entry, u16 value)
{
  char entry_tmp; // $s0
  char value_tmp; // $s1
  u16 param_tmp; // $s0
  u16 Param; // $v0
  int state; // [sp+10h] [-8h] BYREF

  entry_tmp = entry;
  value_tmp = value;
  if ( (entry & ~0xFFFF0001) == SD_CORE_SPDIF_MODE )
  {
    SetSpdifMode(value);
  }
  else if ( (entry & ~0xFFFF0001) == SD_CORE_NOISE_CLK )
  {
    CpuSuspendIntr(&state);
    param_tmp = (entry_tmp & 1) | 0x2300;
    Param = sceSdGetParam(param_tmp);
    sceSdSetParam(param_tmp, (Param & ~0x3F00) | ((value_tmp & 0x3F) << 8));
    CpuResumeIntr(state);
  }
  else
  {
    sceSdSetCoreAttr_default(entry, value);
  }
}

//----- (004040A0) --------------------------------------------------------
u16 __cdecl sceSdGetCoreAttr(u16 entry)
{
  unsigned int attr; // $v1
  int retval_tmp; // $v0

  attr = spu2_regs.u.main_regs.core_regs[entry & 1].cregs.attr;
  switch ( entry & 0xE )
  {
    case SD_CORE_EFFECT_ENABLE:
      retval_tmp = (attr >> 7) & 1;
      break;
    case SD_CORE_IRQ_ENABLE:
      retval_tmp = (attr >> 6) & 1;
      break;
    case SD_CORE_MUTE_ENABLE:
      retval_tmp = (attr >> 14) & 1;
      break;
    case SD_CORE_NOISE_CLK:
      retval_tmp = (attr >> 8) & 0x3F;
      break;
    case SD_CORE_SPDIF_MODE:
      retval_tmp = SpdifSettings & 0xFFFF;
      break;
    default:
      retval_tmp = 0;
      break;
  }
  return retval_tmp;
}
// 4055E0: using guessed type int SpdifSettings;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404130) --------------------------------------------------------
SdIntrCallback __cdecl sceSdSetTransCallback(s32 core, SdIntrCallback cb)
{
  int core_tmp; // $a0
  SdIntrCallback oldtmp; // $v0

  core_tmp = (unsigned __int16)core;
  oldtmp = TransIntrCallbacks[core_tmp];
  TransIntrCallbacks[core_tmp] = cb;
  return oldtmp;
}

//----- (0040416C) --------------------------------------------------------
sceSdTransIntrHandler __cdecl sceSdSetTransIntrHandler(int channel, sceSdTransIntrHandler func, void *arg)
{
  sceSdTransIntrHandler oldtmp; // $v0

  oldtmp = TransIntrHandlers[channel];
  TransIntrHandlers[channel] = func;
  TransIntrData[channel].data = arg;
  return oldtmp;
}

//----- (004041A8) --------------------------------------------------------
void *__cdecl sceSdGetTransIntrHandlerArgument(int arg)
{
  return TransIntrData[arg].data;
}

//----- (004041C0) --------------------------------------------------------
SdIntrCallback __cdecl sceSdSetIRQCallback(SdIntrCallback cb)
{
  SdIntrCallback oldtmp; // $v0

  oldtmp = Spu2IrqCallback;
  Spu2IrqCallback = cb;
  return oldtmp;
}

//----- (004041E0) --------------------------------------------------------
sceSdSpu2IntrHandler __cdecl sceSdSetSpu2IntrHandler(sceSdSpu2IntrHandler func, void *arg)
{
  sceSdSpu2IntrHandler oldtmp; // $v0

  oldtmp = Spu2IntrHandler;
  Spu2IntrHandler = func;
  Spu2IntrHandlerData = arg;
  return oldtmp;
}

//----- (00404208) --------------------------------------------------------
void *__cdecl sceSdGetSpu2IntrHandlerArgument()
{
  return Spu2IntrHandlerData;
}

//----- (00404220) --------------------------------------------------------
int __fastcall Spu2Interrupt(void *data)
{
  vu8 irqinfo_val; // $v0
  int val; // $a0
  int condtmp2; // $v0
  bool condtmp1; // dc
  int condtmp3; // $v0

  if ( Spu2IntrHandler || Spu2IrqCallback )
  {
    irqinfo_val = spu2_regs.u.main_regs.core_regs[1].padding[98];
    val = (unsigned __int8)(irqinfo_val & 0xC) >> 2;
    if ( val )
    {
      condtmp2 = (irqinfo_val & 4) != 0;
      do
      {
        condtmp1 = condtmp2 == 0;
        condtmp3 = val & 2;
        if ( !condtmp1 )
        {
          spu2_regs.u.main_regs.core_regs[0].cregs.attr &= ~0x40u;
          condtmp3 = val & 2;
        }
        if ( condtmp3 )
          spu2_regs.u.main_regs.core_regs[1].cregs.attr &= ~0x40u;
        if ( Spu2IntrHandler )
        {
          Spu2IntrHandler(val, Spu2IntrHandlerData);
        }
        else if ( Spu2IrqCallback )
        {
          Spu2IrqCallback(0);
        }
        val = (unsigned __int8)(spu2_regs.u.main_regs.core_regs[1].padding[98] & 0xC) >> 2;
        condtmp2 = val & 1;
      }
      while ( val );
    }
  }
  return 1;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404344) --------------------------------------------------------
int InitVoices()
{
  __int16 *initdata_tmp; // $a2
  _WORD *regs_0; // $s1
  __int16 *regs_1024; // $s0
  _WORD *regs_448; // $s3
  vu16 attr; // $v0
  __int16 *regs_1472; // $s2
  vu16 attr_reg1; // $v0
  vu16 statx; // $v0
  vu16 attr_reg2; // $v0
  __int16 tmpreg1; // $v0
  __int16 *tmpreg2; // $s0
  _WORD *tmpreg3; // $s1
  __int16 tmpreg4; // $v0
  __int16 tmpreg5; // $v0
  __int16 tmpreg6; // $v0
  __int16 tempreg7; // $v0
  __int16 tmpreg8; // $v0
  _WORD *tmpreg9; // $s2
  _WORD *tmprega; // $s3
  vu16 kon_1; // $v0
  vu16 kon_2; // $v0
  vu16 koff_1; // $v0
  vu16 koff_2; // $v0
  vu16 endx_1; // $v0
  int i2; // [sp+10h] [-8h]
  int i1; // [sp+10h] [-8h]
  int i1a; // [sp+10h] [-8h]

  initdata_tmp = VoiceDataInit;
  regs_0 = (_WORD *)&spu2_regs;
  regs_1024 = (_WORD *)(&spu2_regs + 1024);
  regs_448 = (_WORD *)(&spu2_regs + 448);
  attr = spu2_regs.u.main_regs.core_regs[0].cregs.attr;
  spu2_regs.u.main_regs.core_regs[0].cregs.attr = attr & ~SD_CORE_DMA;
  spu2_regs.u.extra_regs.core0_regs.tsa.pair[0] = 0x0000;
  spu2_regs.u.extra_regs.core0_regs.tsa.pair[1] = 0x2800;
  i2 = 0;
  regs_1472 = (_WORD *)(&spu2_regs + 1472);
  do
  {
    spu2_regs.u.main_regs.core_regs[0].cregs.xferdata_1ac = *initdata_tmp;
    ++i2;
    ++initdata_tmp;
  }
  while ( i2 < 8 );
  attr_reg1 = spu2_regs.u.main_regs.core_regs[0].cregs.attr;
  spu2_regs.u.main_regs.core_regs[0].cregs.attr = (attr_reg1 & ~SD_CORE_DMA) | SD_DMA_IO;
  i1 = 0;
  statx = spu2_regs.u.main_regs.core_regs[0].cregs.statx;
  if ( (statx & SD_IO_IN_PROCESS) != 0 )
  {
    do
    {
      libsd_do_busyloop_1(1);
      ++i1;
    }
    while ( i1 <= 0x1000000 && (spu2_regs.u.main_regs.core_regs[0].cregs.statx & SD_IO_IN_PROCESS) != 0 );
  }
  attr_reg2 = spu2_regs.u.main_regs.core_regs[0].cregs.attr;
  spu2_regs.u.main_regs.core_regs[0].cregs.attr = attr_reg2 & ~SD_CORE_DMA;
  for ( i1a = 0; i1a < 24; ++i1a )
  {
    *regs_1024 = 0;
    tmpreg1 = *regs_1024;
    tmpreg2 = regs_1024 + 1;
    *regs_0 = tmpreg1;
    tmpreg3 = regs_0 + 1;
    *tmpreg2 = 0;
    tmpreg4 = *tmpreg2++;
    *tmpreg3++ = tmpreg4;
    *tmpreg2 = 0x3FFF;
    tmpreg5 = *tmpreg2++;
    *tmpreg3++ = tmpreg5;
    *tmpreg2 = 0;
    tmpreg6 = *tmpreg2++;
    *tmpreg3++ = tmpreg6;
    *tmpreg2 = 0;
    tempreg7 = *tmpreg2;
    regs_1024 = tmpreg2 + 4;
    *tmpreg3 = tempreg7;
    regs_0 = tmpreg3 + 4;
    *regs_1472 = 0;
    tmpreg8 = *regs_1472;
    tmpreg9 = regs_1472 + 1;
    *regs_448 = tmpreg8;
    *tmpreg9 = 10240;
    tmprega = regs_448 + 1;
    *tmprega = *tmpreg9;
    regs_1472 = tmpreg9 + 5;
    regs_448 = tmprega + 5;
  }
  spu2_regs.u.extra_regs.core1_regs.kon.pair[0] = 0xFFFF;
  spu2_regs.u.extra_regs.core1_regs.kon.pair[1] = 0xFF;
  kon_1 = spu2_regs.u.main_regs.core_regs[1].cregs.kon.pair[0];
  spu2_regs.u.main_regs.core_regs[0].cregs.kon.pair[0] = kon_1;
  kon_2 = spu2_regs.u.main_regs.core_regs[1].cregs.kon.pair[1];
  spu2_regs.u.main_regs.core_regs[0].cregs.kon.pair[1] = kon_2;
  libsd_do_busyloop_1(3);
  spu2_regs.u.extra_regs.core1_regs.koff.pair[0] = 0xFFFF;
  spu2_regs.u.extra_regs.core1_regs.koff.pair[1] = 0xFF;
  koff_1 = spu2_regs.u.main_regs.core_regs[1].cregs.koff.pair[0];
  spu2_regs.u.main_regs.core_regs[0].cregs.koff.pair[0] = koff_1;
  koff_2 = spu2_regs.u.main_regs.core_regs[1].cregs.koff.pair[1];
  spu2_regs.u.main_regs.core_regs[0].cregs.koff.pair[1] = koff_2;
  libsd_do_busyloop_1(3);
  spu2_regs.u.main_regs.core_regs[0].cregs.endx.pair[1] = 0;
  endx_1 = spu2_regs.u.main_regs.core_regs[0].cregs.endx.pair[1];
  spu2_regs.u.main_regs.core_regs[0].cregs.endx.pair[0] = endx_1;
  spu2_regs.u.main_regs.core_regs[1].cregs.endx.pair[1] = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.endx.pair[0] = spu2_regs.u.main_regs.core_regs[1].cregs.endx.pair[1];
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404644) --------------------------------------------------------
int __fastcall Reset(char flag)
{
  bool condtmp; // dc
  iop_event_t efparam; // [sp+10h] [-18h] BYREF
  int intrstate[2]; // [sp+20h] [-8h] BYREF

  DisableIntr(36, intrstate);
  DisableIntr(40, intrstate);
  DisableIntr(9, intrstate);
  ReleaseIntrHandler(36);
  ReleaseIntrHandler(40);
  ReleaseIntrHandler(9);
  VoiceTransStatus[0] = 0;
  VoiceTransStatus[1] = 0;
  VoiceTransIoMode[0] = 1;
  VoiceTransIoMode[1] = 1;
  VoiceTransCompleteBool[0] = 0;
  VoiceTransCompleteBool[1] = 0;
  Spu2IntrHandler = 0;
  TransIntrHandlers[0] = 0;
  TransIntrHandlers[1] = 0;
  CleanHandlers[0] = 0;
  CleanHandlers[1] = 0;
  TransIntrData[0].mode = 0;
  TransIntrData[1].mode = 1;
  TransIntrData[0].data = 0;
  TransIntrData[1].data = 0;
  BlockHandlerIntrData[0].cb = 0;
  BlockHandlerIntrData[1].cb = 0;
  BlockHandlerIntrData[0].userdata = 0;
  BlockHandlerIntrData[1].userdata = 0;
  Spu2IntrHandlerData = 0;
  Spu2IrqCallback = 0;
  TransIntrCallbacks[0] = 0;
  TransIntrCallbacks[1] = 0;
  condtmp = (flag & 0xF) != 0;
  if ( !condtmp )
  {
    bzero(EffectAttr, 40);
    EffectAddr[0] = 0x1DFFF0;
    EffectAddr[1] = 0x1FFFF0;
    spu2_regs.u.extra_regs.core0_regs.esa.pair[0] = 0x000E;
    spu2_regs.u.extra_regs.core0_regs.esa.pair[1] = 0xFFF8;
    spu2_regs.u.extra_regs.core1_regs.esa.pair[0] = 0x000F;
    spu2_regs.u.extra_regs.core1_regs.esa.pair[1] = 0xFFF8;
  }
  efparam.attr = 2;
  efparam.bits = 1;
  efparam.option = 0;
  if ( VoiceTransCompleteEf[0] <= 0 )
  {
    VoiceTransCompleteEf[0] = CreateEventFlag(&efparam);
  }
  else
  {
    if ( QueryIntrContext() )
      iSetEventFlag(VoiceTransCompleteEf[0], 1u);
    else
      SetEventFlag(VoiceTransCompleteEf[0], 1u);
  }
  if ( VoiceTransCompleteEf[1] <= 0 )
  {
    VoiceTransCompleteEf[1] = CreateEventFlag(&efparam);
  }
  else
  {
    if ( QueryIntrContext() )
      iSetEventFlag(VoiceTransCompleteEf[1], 1u);
    else
      SetEventFlag(VoiceTransCompleteEf[1], 1u);
  }
  if ( VoiceTransCompleteEf[0] <= 0 || VoiceTransCompleteEf[1] <= 0 )
    return -301;
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (004048C8) --------------------------------------------------------
void reset_vars()
{
  vars_inited = 0;
  VoiceTransCompleteEf[0] = 0;
  VoiceTransCompleteEf[1] = 0;
}
// 405628: using guessed type int vars_inited;

//----- (004048E4) --------------------------------------------------------
int __cdecl sceSdInit(int flag)
{
  char flag_tmp; // $s1
  int resetres; // $s2

  flag_tmp = flag;
  InitSpu2();
  if ( (flag_tmp & 0xF) == 0 )
    InitSpdif();
  resetres = Reset(flag_tmp);
  InitVoices();
  InitCoreVolume(flag_tmp & 0xF);
  EnableIntr(36);
  EnableIntr(40);
  EnableIntr(9);
  RegisterIntrHandler(36, 1, (int (__cdecl *)(void *))TransInterrupt, TransIntrData);
  RegisterIntrHandler(40, 1, (int (__cdecl *)(void *))TransInterrupt, &TransIntrData[1]);
  RegisterIntrHandler(9, 1, (int (__cdecl *)(void *))Spu2Interrupt, Spu2IntrHandlerData);
  vars_inited = 1;
  some_stkclr();
  return resetres;
}
// 405628: using guessed type int vars_inited;

//----- (004049C4) --------------------------------------------------------
int __cdecl sceSdQuit()
{
  unsigned int unused0; // $a1
  unsigned int unused1; // $a2
  unsigned int unused2; // $a1
  unsigned int unused3; // $a2
  int intrstate[2]; // [sp+10h] [-8h] BYREF

  DmaStartStop(10, unused0, unused1);
  DmaStartStop(26, unused2, unused3);
  if ( VoiceTransCompleteEf[0] > 0 )
    DeleteEventFlag(VoiceTransCompleteEf[0]);
  if ( VoiceTransCompleteEf[1] > 0 )
    DeleteEventFlag(VoiceTransCompleteEf[1]);
  DisableIntr(40, intrstate);
  DisableIntr(36, intrstate);
  DisableIntr(9, intrstate);
  ReleaseIntrHandler(40);
  ReleaseIntrHandler(36);
  ReleaseIntrHandler(9);
  some_stkclr();
  return 0;
}
// 4049D0: variable 'unused0' is possibly undefined
// 4049D0: variable 'unused1' is possibly undefined
// 4049D8: variable 'unused2' is possibly undefined
// 4049D8: variable 'unused3' is possibly undefined
