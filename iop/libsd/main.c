
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
  u32 *m_spuaddr;
  u32 m_size;
} CleanRegionBufferElement_t;


typedef struct CleanRegionBuffer_
{
  CleanRegionBufferElement_t m_elements[97];
} CleanRegionBuffer_t;


//-------------------------------------------------------------------------
// Function declarations

void SetEffectRegister(int core, int spu2_regs_offset, int val);
void __cdecl SetEffectData(int core, struct mode_data_struct *mode_data);
int __cdecl sceSdClearEffectWorkArea(int core, int channel, int effect_mode);
int CleanHandler(int channel);
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
int InitSpdif();
void SetDmaWrite(int chan);
void SetDmaRead(int chan);
void libsd_do_busyloop_2();
void libsd_do_busyloop_1(int);
u32 __fastcall DmaStartStop(int mainarg, void *vararg2, unsigned int vararg3);
int __fastcall VoiceTrans_Write_IOMode(const __int16 *iopaddr, unsigned int size, int chan);
void do_finish_block_clean_xfer(int core);
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
typedef int (*SdCleanHandler)(int);
SdCleanHandler CleanHandlers[2] = { 0, 0 };
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

//----- (004000B0) --------------------------------------------------------
int _start()
{
  int regres; // $s0
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  regres = RegisterLibraryEntries(&_exp_libsd);
  CpuResumeIntr(state);
  if ( regres )
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

  deref_mode_data = mode_data->mode_flags;
  if ( deref_mode_data == 0 )
    deref_mode_data = 0xFFFFFFFF;
  if ( (deref_mode_data & 1) != 0 )
    SetEffectRegister(core, 370, (unsigned __int16)mode_data->mode_data[0]);
  if ( (deref_mode_data & 2) != 0 )
    SetEffectRegister(core, 372, (unsigned __int16)mode_data->mode_data[1]);
  if ( ((deref_mode_data & 4) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].iir_vol = mode_data->mode_data[2];
  if ( ((deref_mode_data & 8) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].comb1_vol = mode_data->mode_data[3];
  if ( ((deref_mode_data & 0x10) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].comb2_vol = mode_data->mode_data[4];
  if ( ((deref_mode_data & 0x20) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].comb3_vol = mode_data->mode_data[5];
  if ( ((deref_mode_data & 0x40) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].comb4_vol = mode_data->mode_data[6];
  if ( ((deref_mode_data & 0x80) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].wall_vol = mode_data->mode_data[7];
  if ( ((deref_mode_data & 0x100) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].apf1_vol = mode_data->mode_data[8];
  if ( ((deref_mode_data & 0x200) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].apf2_vol = mode_data->mode_data[9];
  if ( (deref_mode_data & 0x400) != 0 )
    SetEffectRegister(core, 374, (unsigned __int16)mode_data->mode_data[10]);
  if ( (deref_mode_data & 0x800) != 0 )
    SetEffectRegister(core, 376, (unsigned __int16)mode_data->mode_data[11]);
  if ( (deref_mode_data & 0x1000) != 0 )
    SetEffectRegister(core, 378, (unsigned __int16)mode_data->mode_data[12]);
  if ( (deref_mode_data & 0x2000) != 0 )
    SetEffectRegister(core, 380, (unsigned __int16)mode_data->mode_data[13]);
  if ( (deref_mode_data & 0x4000) != 0 )
    SetEffectRegister(core, 382, (unsigned __int16)mode_data->mode_data[14]);
  if ( (deref_mode_data & 0x8000) != 0 )
    SetEffectRegister(core, 384, (unsigned __int16)mode_data->mode_data[15]);
  if ( (deref_mode_data & 0x10000) != 0 )
    SetEffectRegister(core, 386, (unsigned __int16)mode_data->mode_data[16]);
  if ( (deref_mode_data & 0x20000) != 0 )
    SetEffectRegister(core, 388, (unsigned __int16)mode_data->mode_data[17]);
  if ( (deref_mode_data & 0x40000) != 0 )
    SetEffectRegister(core, 390, (unsigned __int16)mode_data->mode_data[18]);
  if ( (deref_mode_data & 0x80000) != 0 )
    SetEffectRegister(core, 392, (unsigned __int16)mode_data->mode_data[19]);
  if ( (deref_mode_data & 0x100000) != 0 )
    SetEffectRegister(core, 394, (unsigned __int16)mode_data->mode_data[20]);
  if ( (deref_mode_data & 0x200000) != 0 )
    SetEffectRegister(core, 396, (unsigned __int16)mode_data->mode_data[21]);
  if ( (deref_mode_data & 0x400000) != 0 )
    SetEffectRegister(core, 398, (unsigned __int16)mode_data->mode_data[22]);
  if ( (deref_mode_data & 0x800000) != 0 )
    SetEffectRegister(core, 400, (unsigned __int16)mode_data->mode_data[23]);
  if ( (deref_mode_data & 0x1000000) != 0 )
    SetEffectRegister(core, 402, (unsigned __int16)mode_data->mode_data[24]);
  if ( (deref_mode_data & 0x2000000) != 0 )
    SetEffectRegister(core, 404, (unsigned __int16)mode_data->mode_data[25]);
  if ( (deref_mode_data & 0x4000000) != 0 )
    SetEffectRegister(core, 406, (unsigned __int16)mode_data->mode_data[26]);
  if ( (deref_mode_data & 0x8000000) != 0 )
    SetEffectRegister(core, 408, (unsigned __int16)mode_data->mode_data[27]);
  if ( (deref_mode_data & 0x10000000) != 0 )
    SetEffectRegister(core, 410, (unsigned __int16)mode_data->mode_data[28]);
  if ( (deref_mode_data & 0x20000000) != 0 )
    SetEffectRegister(core, 412, (unsigned __int16)mode_data->mode_data[29]);
  if ( ((deref_mode_data & 0x40000000) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].in_coef_l = mode_data->mode_data[30];
  if ( ((deref_mode_data & 0x80000000) != 0) )
    ptr_to_bf900000->u.extra_regs.different_regs[core].in_coef_r = mode_data->mode_data[31];
}

//----- (00400660) --------------------------------------------------------
int __cdecl sceSdClearEffectWorkArea(int core, int channel, int effect_mode)
{
  unsigned int aligned_addr; // $s4
  unsigned int effect_size; // $s1
  unsigned int effect_addr; // $s2
  int xferres; // $s0
  int flag_tmp; // $s4
  u32 size; // $v1
  int (__cdecl *callback_tmp)(void *); // [sp+18h] [-8h]
  int (__cdecl *handler_tmp)(int, void *); // [sp+1Ch] [-4h]

  if ( (unsigned __int8)effect_mode >= 0xAu )
    return -100;
  if ( !(_BYTE)effect_mode )
    return 0;
  if ( DmaStartStop((channel << 4) | 4, 0, 0) != 0 )
  {
    return -210;
  }
  if ( VoiceTransIoMode[channel] != 1 )
  {
    return -201;
  }
  if ( QueryIntrContext() != 0 )
  {
    return -202;
  }
  aligned_addr = 0;
  effect_size = 8 * EffectSizes[(unsigned __int8)effect_mode];
  effect_addr = (GetEEA(core) - (effect_size - 1)) >> 1;
  if ( (effect_size & 0x3F) != 0 )
  {
    effect_size = effect_size >> 6 << 6;
    aligned_addr = (GetEEA(core) - (effect_size - 1)) >> 1;
  }
  handler_tmp = TransIntrHandlers[channel];
  callback_tmp = TransIntrCallbacks[channel];
  TransIntrHandlers[channel] = 0;
  TransIntrCallbacks[channel] = 0;
  if ( !aligned_addr
    || ((xferres = sceSdVoiceTrans(channel, 0, (u8 *)ClearEffectData, (u32 *)(2 * effect_addr), 0x40u), xferres >= 0)
    && (xferres = sceSdVoiceTransStatus(channel, 1), effect_addr = aligned_addr, xferres >= 0)) )
  {
    flag_tmp = 1;
    while ( flag_tmp )
    {
      size = 0x400;
      if ( effect_size <= 0x400 )
      {
        size = effect_size;
        flag_tmp = 0;
      }
      xferres = sceSdVoiceTrans(channel, 0, (u8 *)ClearEffectData, (u32 *)(2 * effect_addr), size);
      if ( xferres < 0 )
        break;
      xferres = sceSdVoiceTransStatus(channel, 1);
      if ( xferres < 0 )
        break;
      effect_size -= 1024;
      effect_addr += 512;
    }
    if ( !flag_tmp )
    {
      xferres = 0;
    }
  }
  TransIntrHandlers[channel] = handler_tmp;
  TransIntrCallbacks[channel] = callback_tmp;
  return xferres;
}

//----- (00400888) --------------------------------------------------------
int CleanHandler(int channel)
{
  ++CleanRegionCur[channel];
  if ( (int)CleanRegionCur[channel] >= (int)(CleanRegionMax[channel] - 1) )
  {
    CleanHandlers[channel] = 0;
  }
  DmaStartStop(
    (channel << 4) | 2,
    CleanRegionBuffer[channel].m_elements[CleanRegionCur[channel]].m_spuaddr,
    0);
  DmaStartStop(
    (channel << 4) | 6,
    ClearEffectData,
    CleanRegionBuffer[channel].m_elements[CleanRegionCur[channel]].m_size);
  return 0;
}

//----- (0040097C) --------------------------------------------------------
int __cdecl sceSdCleanEffectWorkArea(int core, int channel, int effect_mode)
{
  unsigned int v9; // $s1
  u32 *v10; // $a3
  int v11; // $s0
  CleanRegionBufferElement_t *v12; // $t0
  u32 *v13; // $t1
  int v14; // $v1

  if ( (unsigned __int8)effect_mode >= 0xAu )
    return -100;
  if ( !(_BYTE)effect_mode )
    return 0;
  if ( DmaStartStop((channel << 4) | 4, 0, 0) != 0 )
  {
    return -210;
  }
  if ( VoiceTransIoMode[channel] != 1 )
  {
    return -201;
  }
  v9 = 8 * EffectSizes[(unsigned __int8)effect_mode];
  v10 = (u32 *)(GetEEA(core) - (v9 - 1));
  if ( (v9 & 0x3F) != 0 )
  {
    v9 = v9 >> 6 << 6;
    v11 = sceSdVoiceTrans(channel, 8u, (u8 *)ClearEffectData, v10, 0x40u);
    if ( v11 < 0 )
    {
      return v11;
    }
    v10 = (u32 *)(GetEEA(core) - (v9 - 1));
  }
  v12 = &CleanRegionBuffer[channel].m_elements[0];
  v13 = v10 + 256;
  CleanRegionMax[channel] = 0;
  for ( v14 = v9 - 1024; v14 >= 1025; v14 -= 1024 )
  {
    v12->m_spuaddr = v13;
    v12->m_size = 1024;
    v12 += 1;
    v13 += 256;
    ++CleanRegionMax[channel];
  }
  v12->m_spuaddr = v13;
  v12->m_size = v14;
  CleanRegionMax[channel] += 1;
  CleanHandlers[channel] = CleanHandler;
  CleanRegionCur[channel] = 0;
  v11 = sceSdVoiceTrans(channel & 0xFFFF, 0, (u8 *)ClearEffectData, v10, 0x400u);
  if ( v11 >= 0 )
    v11 = 0;
  return v11;
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
  int channel; // $s6
  int mode; // $s2
  __int16 mode_data_0; // $v1
  int delay; // $a0
  __int16 feedback_tmp; // $v0
  int feedback; // $v1
  int effects_enabled; // $s5
  int retval; // $s0
  struct mode_data_struct mode_data; // [sp+10h] [-60h] BYREF
  int state; // [sp+5Ch] [-14h] BYREF
  int effect_mode; // [sp+60h] [-10h]

  clearram = 0;
  channel = 0;
  effect_mode = 0;
  mode_data.mode_flags = 0;
  mode = attr->mode;
  if ( (mode & SD_EFFECT_MODE_CLEAR) != 0 )
  {
    clearram = 1;
    effect_mode = EffectAttr[core].mode;
    channel = (mode & 0x200) != 0;
  }
  if ( (unsigned __int8)mode >= (unsigned int)(SD_EFFECT_MODE_DELAY|SD_EFFECT_MODE_STUDIO_1) )
    return -100;
  EffectAttr[core].mode = (unsigned __int8)mode;
  EffectAddr[core] = GetEEA(core) - (8 * EffectSizes[(unsigned __int8)mode] - 1);
  // Unoffical: use memcpy from sysclib
  memcpy(&mode_data, &EffectParams[EffectAttr[core].mode], sizeof(mode_data));
  if ( (unsigned __int8)mode == SD_EFFECT_MODE_ECHO )
  {
    EffectAttr[core].feedback = 128;
    EffectAttr[core].delay = 128;
  }
  else if ( (unsigned __int8)mode == SD_EFFECT_MODE_DELAY )
  {
    EffectAttr[core].feedback = 0;
    EffectAttr[core].delay = 128;
  }
  else
  {
    EffectAttr[core].feedback = 0;
    EffectAttr[core].delay = 0;
  }
  if ( (unsigned __int8)mode < SD_EFFECT_MODE_PIPE )
  {
    if ( (unsigned __int8)mode >= SD_EFFECT_MODE_ECHO )
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
    }
    if ( (unsigned __int8)mode < SD_EFFECT_MODE_PIPE && (unsigned __int8)mode >= SD_EFFECT_MODE_ECHO )
    {
      feedback = attr->feedback;
      EffectAttr[core].feedback = feedback;
      mode_data.mode_data[7] = 258 * feedback;
    }
  }
  effects_enabled = (spu2_regs.u.main_regs.core_regs[core].cregs.attr >> 7) & 1;
  if ( effects_enabled )
  {
    CpuSuspendIntr(&state);
    spu2_regs.u.main_regs.core_regs[core].cregs.attr &= ~SD_ENABLE_EFFECTS;
    CpuResumeIntr(state);
  }
  if ( !effects_enabled
    || (!clearram || (retval = sceSdClearEffectWorkArea(core, channel, effect_mode), retval >= 0)) )
  {
    spu2_regs.u.extra_regs.different_regs[core].evoll = attr->depth_L;
    spu2_regs.u.extra_regs.different_regs[core].evolr = attr->depth_R;
    SetEffectData(core, &mode_data);
    spu2_regs.u.main_regs.core_regs[core].cregs.esa.pair[0] = EffectAddr[core] >> 17;
    spu2_regs.u.main_regs.core_regs[core].cregs.esa.pair[1] = EffectAddr[core] >> 1;
    retval = 0;
    if ( clearram )
      retval = sceSdClearEffectWorkArea(core, channel, (unsigned __int8)mode);
  }
  if ( effects_enabled )
  {
    CpuSuspendIntr(&state);
    spu2_regs.u.main_regs.core_regs[core].cregs.attr |= SD_ENABLE_EFFECTS;
    CpuResumeIntr(state);
  }
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
  int channel; // $s5
  unsigned int mode; // $s1
  int attr_effectsrel; // $s4
  struct mode_data_struct mode_data; // [sp+10h] [-50h] BYREF
  int state; // [sp+5Ch] [-4h] BYREF

  clearram = 0;
  mode_data.mode_flags = 0;
  channel = 0;
  if ( (param->mode & 0x100) != 0 )
  {
    clearram = 1;
    channel = (param->mode & 0x200) != 0;
  }
  mode = (unsigned __int8)param->mode;
  if ( mode >= 0xA )
    return -100;
  EffectAttr[core].mode = mode;
  EffectAttr[core].delay = 0;
  EffectAttr[core].feedback = 0;
  EffectAddr[core] = GetEEA(core) - (8 * EffectSizes[mode] - 1);
  // Unoffical: don't use inlined memcpy
  memcpy(&mode_data, &EffectParams[mode], sizeof(mode_data));
  attr_effectsrel = (spu2_regs.u.main_regs.core_regs[core].cregs.attr >> 7) & 1;
  if ( attr_effectsrel )
  {
    CpuSuspendIntr(&state);
    spu2_regs.u.main_regs.core_regs[core].cregs.attr &= ~0x80u;
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
    spu2_regs.u.main_regs.core_regs[core].cregs.attr |= 0x80u;
    CpuResumeIntr(state);
  }
  if ( clearram )
    return sceSdCleanEffectWorkArea(core, channel, mode);
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;
// 401128: using guessed type struct mode_data_struct mode_data;

//----- (00401380) --------------------------------------------------------
int __cdecl sceSdSetEffectModeParams(int core, sceSdEffectAttr *attr)
{
  int mode_low; // $v1
  int mode; // $a0
  int delay_plus_one; // $a0
  struct mode_data_struct mode_data; // [sp+10h] [-48h] BYREF

  mode_low = attr->mode & 0xFF;
  if ( (unsigned int)mode_low >= 0xA )
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
      EffectAttr[core].delay = attr->delay;
      EffectAttr[core].feedback = attr->feedback;
      delay_plus_one = EffectAttr[core].delay + 1;
      mode_data.mode_data[10] = (__int16)(((_WORD)delay_plus_one << 6) - (__int16)mode_data.mode_data[0]);
      delay_plus_one <<= 5;
      delay_plus_one &= 0xFFFF;
      mode_data.mode_data[11] = delay_plus_one - mode_data.mode_data[1];
      mode_data.mode_data[12] = mode_data.mode_data[13] + delay_plus_one;
      mode_data.mode_data[16] = mode_data.mode_data[17] + delay_plus_one;
      mode_data.mode_data[26] = mode_data.mode_data[28] + delay_plus_one;
      mode_data.mode_data[27] = mode_data.mode_data[29] + delay_plus_one;
      mode_data.mode_data[7] = 258 * EffectAttr[core].feedback;
      SetEffectData(core, &mode_data);
    }
  }
  spu2_regs.u.extra_regs.different_regs[core].evoll = attr->depth_L;
  spu2_regs.u.extra_regs.different_regs[core].evolr = attr->depth_R;
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401550) --------------------------------------------------------
void InitSpu2_Inner()
{
  int state; // [sp+10h] [-8h] BYREF

  iop_mmio_hwport.ssbus2.ind_4_address = 0xBF900000;
  iop_mmio_hwport.ssbus2.ind_9_address = 0xBF900800;
  CpuSuspendIntr(&state);
  iop_mmio_hwport.dmac1.dpcr1 |= 0x80000;
  iop_mmio_hwport.dmac2.dpcr2 |= 8;
  CpuResumeIntr(state);
  iop_mmio_hwport.ssbus1.ind_4_delay = 0x200B31E1;
  iop_mmio_hwport.ssbus2.ind_9_delay = 0x200B31E1;
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;

//----- (004015E8) --------------------------------------------------------
void InitSpu2()
{
  InitSpu2_Inner();
  spu2_regs.u.extra_regs.spdif_mode = 0x0900;
  spu2_regs.u.extra_regs.spdif_media = 0x200;
  spu2_regs.u.extra_regs.unknown7ca = 8;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401638) --------------------------------------------------------
void InitCoreVolume(int flag)
{
  spu2_regs.u.extra_regs.spdif_out = 0xC032;
  if ( flag )
  {
    spu2_regs.u.main_regs.core_regs[0].cregs.attr = SD_ENABLE_EFFECTS|SD_MUTE|SD_SPU2_ON;
    spu2_regs.u.main_regs.core_regs[1].cregs.attr = SD_ENABLE_EX_INPUT|SD_ENABLE_EFFECTS|SD_MUTE|SD_SPU2_ON;
  }
  else
  {
    spu2_regs.u.main_regs.core_regs[0].cregs.attr = SD_MUTE|SD_SPU2_ON;
    spu2_regs.u.main_regs.core_regs[1].cregs.attr = SD_ENABLE_EX_INPUT|SD_MUTE|SD_SPU2_ON;
  }
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixl.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixl.pair[1] = 0xFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixel.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixel.pair[1] = 0x00FF;
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixr.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixr.pair[1] = 0x00FF;
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixer.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.vmixer.pair[1] = 0x00FF;
  spu2_regs.u.main_regs.core_regs[0].cregs.mmix = 0xFF0;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixl.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixl.pair[1] = 0xFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixel.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixel.pair[1] = 0x00FF;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixr.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixr.pair[1] = 0x00FF;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixer.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.vmixer.pair[1] = 0x00FF;
  spu2_regs.u.main_regs.core_regs[1].cregs.mmix = 0xFFC;
  if ( !flag )
  {
    spu2_regs.u.extra_regs.different_regs[0].mvoll = 0;
    spu2_regs.u.extra_regs.different_regs[0].mvolr = 0;
    spu2_regs.u.extra_regs.different_regs[0].evoll = 0;
    spu2_regs.u.extra_regs.different_regs[0].evolr = 0;
    spu2_regs.u.extra_regs.different_regs[1].mvoll = 0;
    spu2_regs.u.extra_regs.different_regs[1].mvolr = 0;
    spu2_regs.u.extra_regs.different_regs[1].evoll = 0;
    spu2_regs.u.extra_regs.different_regs[1].evolr = 0;
    spu2_regs.u.main_regs.core_regs[0].cregs.eea = 14;
    spu2_regs.u.main_regs.core_regs[1].cregs.eea = 15;
  }
  spu2_regs.u.extra_regs.different_regs[0].avoll = 0;
  spu2_regs.u.extra_regs.different_regs[0].avolr = 0;
  spu2_regs.u.extra_regs.different_regs[0].bvoll = 0;
  spu2_regs.u.extra_regs.different_regs[0].bvolr = 0;
  spu2_regs.u.extra_regs.different_regs[1].avoll = 0x7FFF;
  spu2_regs.u.extra_regs.different_regs[1].avolr = 0x7FFF;
  spu2_regs.u.extra_regs.different_regs[1].bvoll = 0;
  spu2_regs.u.extra_regs.different_regs[1].bvolr = 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401890) --------------------------------------------------------
int __cdecl sceSdVoiceTrans(s16 chan, u16 mode, u8 *iopaddr, u32 *spuaddr, u32 size)
{
  int core; // $s2
  unsigned int dmasize1; // $a2
  u32 dmasize2; // $s1

  core = chan & 1;
  if ( !size )
    return -100;
  if ( DmaStartStop((core << 4) | 4, 0, 0) != 0 )
  {
    return -210;
  }
  if ( VoiceTransIoMode[core] != 1 )
  {
    return -201;
  }
  if ( (mode & 3) != SD_TRANS_WRITE )
  {
    if ( (mode & 3) != SD_TRANS_READ )
      return -100;
    TransIntrData[core].mode = core | 0x900;
    BlockHandlerIntrData[core].cb = 0;
    BlockHandlerIntrData[core].userdata = 0;
    VoiceTransStatus[core] = 0;
    DmaStartStop((core << 4) | 2, spuaddr, 0);
    if ( QueryIntrContext() )
      iClearEventFlag(VoiceTransCompleteEf[core], 0xFFFFFFFE);
    else
      ClearEventFlag(VoiceTransCompleteEf[core], 0xFFFFFFFE);
    VoiceTransIoMode[core] = 0;
    dmasize1 = size >> 6 << 6;
    if ( (size & 0x3F) != 0 )
      dmasize1 += 64;
    return DmaStartStop((core << 4) | 5, iopaddr, dmasize1);
  }
  TransIntrData[core].mode = core | 0x500;
  BlockHandlerIntrData[core].cb = 0;
  BlockHandlerIntrData[core].userdata = 0;
  DmaStartStop((core << 4) | 2, spuaddr, 0);
  if ( QueryIntrContext() )
    iClearEventFlag(VoiceTransCompleteEf[core], 0xFFFFFFFE);
  else
    ClearEventFlag(VoiceTransCompleteEf[core], 0xFFFFFFFE);
  VoiceTransIoMode[core] = 0;
  if ( (mode & SD_TRANS_MODE_IO) == 0 )
  {
    VoiceTransStatus[core] = 0;
    dmasize1 = size >> 6 << 6;
    if ( (size & 0x3F) != 0 )
      dmasize1 += 64;
    return DmaStartStop((core << 4) | 6, iopaddr, dmasize1);
  }
  VoiceTransStatus[core] = 1;
  dmasize2 = size >> 6 << 6;
  if ( (size & 0x3F) != 0 )
    dmasize2 = (size >> 6 << 6) + 64;
  VoiceTrans_Write_IOMode((__int16 *)iopaddr, dmasize2, core);
  return dmasize2;
}

//----- (00401B10) --------------------------------------------------------
u32 __cdecl sceSdVoiceTransStatus(s16 channel, s16 flag)
{
  int status_offset; // $s0
  u32 efres; // [sp+10h] [-8h] BYREF

  status_offset = channel << 16 >> 14;
  if ( *(int *)((char *)VoiceTransStatus + status_offset) == 1
    || *(int *)((char *)VoiceTransIoMode + status_offset) == 1 )
  {
    return 1;
  }
  switch ( flag )
  {
    case 0:
      if ( *(int *)((char *)VoiceTransCompleteBool + status_offset) )
      {
        *(int *)((char *)VoiceTransCompleteBool + status_offset) = 0;
        *(int *)((char *)VoiceTransIoMode + status_offset) = 1;
      }
      break;
    case 1:
      if ( QueryIntrContext() != 0 )
        return -202;
      WaitEventFlag(*(int *)((char *)VoiceTransCompleteEf + status_offset), 1u, 0, &efres);
      *(int *)((char *)VoiceTransCompleteBool + status_offset) = 0;
      *(int *)((char *)VoiceTransIoMode + status_offset) = 1;
      break;
    default:
      break;
  }
  return *(int *)((char *)VoiceTransIoMode + status_offset);
}
// 401B10: using guessed type u32 efres[2];

//----- (00401C08) --------------------------------------------------------
int __cdecl sceSdStopTrans(int channel)
{
  int core; // $a0

  core = channel & 1;
  TransIntrData[core].mode = core;
  BlockHandlerIntrData[core].cb = 0;
  BlockHandlerIntrData[core].userdata = 0;
  return DmaStartStop((core << 4) | 0xA, 0, 0);
}

//----- (00401C70) --------------------------------------------------------
int sceSdBlockTrans(s16 chan, u16 mode, u8 *iopaddr, u32 size, ...)
{
  int core; // $s0
  u32 started; // $v1
  int transfer_dir; // $a0
  int retres_1; // $s2
  uiptr vararg_elm1;
  uiptr vararg_elm2;
  uiptr vararg_elm3;
  va_list va2; // [sp+60h] [+40h] BYREF

  va_start(va2, size);
  vararg_elm1 = va_arg(va2, uiptr);
  vararg_elm2 = va_arg(va2, uiptr);
  vararg_elm3 = va_arg(va2, uiptr);
  va_end(va2);
  core = chan & 1;
  started = DmaStartStop((core << 4) | 4, 0, 0);
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
    TransIntrData[core].mode = core | 0xA00;
    BlockHandlerIntrData[core].cb = 0;
    BlockHandlerIntrData[core].userdata = 0;
    if ( (mode & 0x80) != 0 )
    {
      if ( !vararg_elm1 )
      {
        TransIntrData[core].mode = core;
        return -100;
      }
      BlockHandlerIntrData[core].cb = (void *)vararg_elm1;
      BlockHandlerIntrData[core].userdata = (void *)vararg_elm2;
      TransIntrData[core].mode |= 0x8000u;
    }
    else
    {
      if ( (mode & SD_TRANS_LOOP) != 0 )
      {
        size >>= 1;
        TransIntrData[core].mode |= 0x1000u;
      }
    }
    retres_1 = BlockTransRead((u32)iopaddr, size, core, mode);
  }
  else
  {
    if ( (mode & 3u) >= SD_TRANS_STOP )
    {
      if ( transfer_dir == SD_TRANS_STOP )
      {
        BlockHandlerIntrData[core].cb = 0;
        BlockHandlerIntrData[core].userdata = 0;
        TransIntrData[core].mode = core;
        return DmaStartStop((core << 4) | 0xA, 0, 0);
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
    TransIntrData[core].mode = core | 0x600;
    BlockHandlerIntrData[core].cb = 0;
    BlockHandlerIntrData[core].userdata = 0;
    if ( (mode & 0x80) != 0 )
    {
      if ( !vararg_elm2 )
      {
        TransIntrData[core].mode = core;
        return -100;
      }
      BlockHandlerIntrData[core].cb = (void *)vararg_elm2;
      BlockHandlerIntrData[core].userdata = (void *)vararg_elm3;
      TransIntrData[core].mode |= 0x8000u;
    }
    else
    {
      if ( (mode & SD_TRANS_LOOP) != 0 )
      {
        size >>= 1;
        TransIntrData[core].mode |= 0x1000u;
      }
    }
    retres_1 = BlockTransWriteFrom((u32)iopaddr, size, chan & 0xFF, mode, ( transfer_dir == SD_TRANS_WRITE_FROM ) ? (int)vararg_elm1 : 0);
  }
  if ( retres_1 < 0 )
  {
    BlockHandlerIntrData[core].cb = 0;
    BlockHandlerIntrData[core].userdata = 0;
    TransIntrData[core].mode = core;
  }
  return retres_1;
}

//----- (00402024) --------------------------------------------------------
u32 __cdecl sceSdBlockTransStatus(s16 channel, s16 flag)
{
  (void)flag;
  return thunk_sceSdBlockTransStatus(channel);
}

//----- (0040206C) --------------------------------------------------------
int InitSpdif()
{
  unsigned int loopi; // $s0

  spu2_regs.u.extra_regs.spdif_out = 0;
  libsd_do_busyloop_1(2);
  spu2_regs.u.extra_regs.spdif_out = 0x8000;
  libsd_do_busyloop_1(1);
  spu2_regs.u.extra_regs.different_regs[0].mvoll = 0;
  spu2_regs.u.extra_regs.different_regs[0].mvolr = 0;
  spu2_regs.u.extra_regs.different_regs[1].mvoll = 0;
  spu2_regs.u.extra_regs.different_regs[1].mvolr = 0;
  spu2_regs.u.main_regs.core_regs[0].cregs.admas = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.admas = 0;
  spu2_regs.u.main_regs.core_regs[0].cregs.attr = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.attr = 0;
  libsd_do_busyloop_1(1);
  spu2_regs.u.main_regs.core_regs[0].cregs.attr = 0x8000;
  spu2_regs.u.main_regs.core_regs[1].cregs.attr = 0x8000;
  spu2_regs.u.extra_regs.different_regs[0].mvoll = 0;
  spu2_regs.u.extra_regs.different_regs[0].mvolr = 0;
  spu2_regs.u.extra_regs.different_regs[1].mvoll = 0;
  spu2_regs.u.extra_regs.different_regs[1].mvolr = 0;
  for ( loopi = 0; (spu2_regs.u.main_regs.core_regs[0].cregs.statx & 0x7FF) && (spu2_regs.u.main_regs.core_regs[1].cregs.statx & 0x7FF) && loopi < 0xF00; ++loopi )
  {
    libsd_do_busyloop_1(1);
  }
  spu2_regs.u.main_regs.core_regs[0].cregs.koff.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.koff.pair[1] = 0xFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.koff.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.koff.pair[1] = 0xFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.pmon.pair[0] = 0;
  spu2_regs.u.main_regs.core_regs[0].cregs.pmon.pair[1] = 0;
  spu2_regs.u.main_regs.core_regs[0].cregs.non.pair[0] = 0;
  spu2_regs.u.main_regs.core_regs[0].cregs.non.pair[1] = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.pmon.pair[0] = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.pmon.pair[1] = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.non.pair[0] = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.non.pair[1] = 0;
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
  }
}

//----- (00402358) --------------------------------------------------------
u32 __fastcall DmaStartStop(int mainarg, void *vararg2, unsigned int vararg3)
{
  int core_tmp1; // $s1
  unsigned int tsa_tmp; // $t1
  unsigned int vararg3_cal; // $a0
  u32 blocktransbufitem; // $s7
  int dmamagictmp; // $s5
  unsigned int waittmp2; // $a0
  unsigned int waittmp1; // $a0
  int hichk; // $s0
  int state; // [sp+14h] [-4h] BYREF

  core_tmp1 = mainarg >> 4;
  switch ( mainarg & 0xF )
  {
    case 2:
      tsa_tmp = ((u16)(uiptr)vararg2 >> 1) & ~7u;
      spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.tsa.pair[1] = tsa_tmp;
      spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.tsa.pair[0] = (tsa_tmp >> 16) & 0xFFFF;
      return 0;
    case 4:
      if ( (spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.attr & SD_DMA_IN_PROCESS) != 0 )
        return -1;
      if ( (*(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) & SD_DMA_START) != 0 )
        return -1;
      if ( spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.admas )
        return -1;
      return 0;
    case 5:
      CpuSuspendIntr(&state);
      spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.attr |= SD_DMA_READ;
      CpuResumeIntr(state);
      SetDmaRead(core_tmp1);
      vararg3_cal = (vararg3 >> 6) + ((vararg3 & 0x3F) != 0);
      *(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].madr : &iop_mmio_hwport.dmac1.oldch[4].madr) = (u16)(uiptr)vararg2;
      *(vu16 *)(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr) = 16;
      *(((vu16 *)(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr)) + 1) = vararg3_cal;
      *(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) = SD_DMA_START|SD_DMA_CS;
      return vararg3_cal << 6;
    case 6:
      CpuSuspendIntr(&state);
      spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.attr = (spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.attr & ~SD_CORE_DMA) | SD_DMA_WRITE;
      CpuResumeIntr(state);
      SetDmaWrite(core_tmp1);
      vararg3_cal = (vararg3 >> 6) + ((vararg3 & 0x3F) != 0);
      *(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].madr : &iop_mmio_hwport.dmac1.oldch[4].madr) = (u16)(uiptr)vararg2;
      *(vu16 *)(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr) = 16;
      *(((vu16 *)(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr)) + 1) = vararg3_cal;
      *(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) = SD_DMA_START|SD_DMA_CS|SD_DMA_DIR_IOP2SPU;
      return vararg3_cal << 6;
    case 0xA:
      blocktransbufitem = 0;
      dmamagictmp = 0;
      if ( (*(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) & SD_DMA_START) != 0 )
      {
        blocktransbufitem = BlockTransBuff[core_tmp1];
        dmamagictmp = *(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].madr : &iop_mmio_hwport.dmac1.oldch[4].madr);
        *(core_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) &= ~SD_DMA_START;
        if ( (spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.attr & SD_CORE_DMA) != 0 )
        {
          for ( waittmp2 = 0; !(spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.statx & 0x80) && waittmp2 < 0x1000000; ++waittmp2 )
          {
          }
        }
      }
      if ( (spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.attr & SD_CORE_DMA) != 0 )
      {
        CpuSuspendIntr(&state);
        spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.attr &= ~SD_CORE_DMA;
        CpuResumeIntr(state);
        for ( waittmp1 = 0; (spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.attr & SD_CORE_DMA) != 0 && waittmp1 < 0xF00; ++waittmp1 )
        {
        }
      }
      hichk = 0;
      if ( (spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.admas & 7) != 0 )
      {
        hichk = 1;
        spu2_regs.u.main_regs.core_regs[core_tmp1].cregs.admas = 0;
      }
      if ( QueryIntrContext() == 0 )
        SetEventFlag(VoiceTransCompleteEf[core_tmp1], 1u);
      else
        iSetEventFlag(VoiceTransCompleteEf[core_tmp1], 1u);
      VoiceTransCompleteBool[core_tmp1] = 0;
      VoiceTransIoMode[core_tmp1] = 1;
      CleanHandlers[core_tmp1] = 0;
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
int __fastcall VoiceTrans_Write_IOMode(const __int16 *iopaddr, unsigned int size, int chan)
{
  unsigned int size_tmp; // $s3
  int count; // $s2
  int i; // $v1
  unsigned int waittmp1; // $s0
  int state; // [sp+14h] [-4h] BYREF

  for ( size_tmp = size; size_tmp; size_tmp -= count )
  {
    count = 64;
    if ( size_tmp < 0x41 )
      count = size_tmp;
    for ( i = 0; i < (count / 2); i += 1 )
    {
      spu2_regs.u.main_regs.core_regs[chan].cregs.xferdata_1ac = iopaddr[i];
    }
    CpuSuspendIntr(&state);
    spu2_regs.u.main_regs.core_regs[chan].cregs.attr = (spu2_regs.u.main_regs.core_regs[chan].cregs.attr & ~SD_CORE_DMA) | SD_DMA_IO;
    CpuResumeIntr(state);
    for ( waittmp1 = 0; (spu2_regs.u.main_regs.core_regs[chan].cregs.statx & SD_IO_IN_PROCESS) != 0 && waittmp1 < 0xF00; ++waittmp1 )
    {
      libsd_do_busyloop_1(1);
    }
  }
  CpuSuspendIntr(&state);
  spu2_regs.u.main_regs.core_regs[chan].cregs.attr &= ~SD_CORE_DMA;
  CpuResumeIntr(state);
  VoiceTransIoMode[chan] = 1;
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (004029A8) --------------------------------------------------------
void do_finish_block_clean_xfer(int core)
{
  spu2_regs.u.main_regs.core_regs[core].cregs.attr &= ~SD_CORE_DMA;
  spu2_regs.u.main_regs.core_regs[core].cregs.admas = 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (004029EC) --------------------------------------------------------
int __fastcall TransInterrupt(IntrData *intr)
{
  int no_flush_cache; // $s5
  u32 mode; // $v1
  int mode_1; // $s1
  int waittmp1; // $v1
  unsigned int waittmp2; // $v1
  int dmamagictmp1; // [sp+14h] [-Ch] BYREF
  int dmamagictmp2; // [sp+18h] [-8h] BYREF

  mode = intr->mode;
  switch ( intr->mode & 0xC00 )
  {
    case 0x400:
      no_flush_cache = 1;
      break;
    case 0x800:
      no_flush_cache = 0;
      break;
    default:
      return 1;
  }
  mode_1 = intr->mode & 1;
  switch ( intr->mode & 0x300 )
  {
    case 0x100:
      for ( waittmp1 = 0; (spu2_regs.u.main_regs.core_regs[mode_1].cregs.statx & 0x80) == 0 && waittmp1 < 0x1000000; ++waittmp1 )
      {
      }
      spu2_regs.u.main_regs.core_regs[mode_1].cregs.attr &= ~SD_CORE_DMA;
      for ( waittmp2 = 0; (spu2_regs.u.main_regs.core_regs[mode_1].cregs.attr & SD_CORE_DMA) != 0 && waittmp2 < 0xF00; ++waittmp2 )
      {
      }
      if ( !no_flush_cache )
        FlushDcache();
      if ( CleanHandlers[mode_1] )
      {
        CleanHandlers[mode_1](mode_1);
        return 1;
      }
      iSetEventFlag(VoiceTransCompleteEf[mode_1], 1u);
      if ( TransIntrHandlers[mode_1] )
      {
        VoiceTransIoMode[mode_1] = 1;
        TransIntrHandlers[mode_1](mode_1, intr->data);
        return 1;
      }
      if ( !TransIntrCallbacks[mode_1] )
      {
        VoiceTransCompleteBool[mode_1] = 1;
        return 1;
      }
      VoiceTransIoMode[mode_1] = 1;
      TransIntrCallbacks[mode_1](0);
      return 1;
    case 0x200:
      if ( (mode & 0x8000) != 0 )
      {
        if ( BlockHandlerIntrData[mode_1].cb )
        {
          ((void (__fastcall *)(int, void *, int *, int *))BlockHandlerIntrData[mode_1].cb)(
            mode_1,
            BlockHandlerIntrData[mode_1].userdata,
            &dmamagictmp1,
            &dmamagictmp2);
          if ( dmamagictmp2 > 0 )
          {
            *(((vu16 *)(mode_1 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr)) + 1) = (dmamagictmp2 >> 6)
                                                                    + (dmamagictmp2 - (dmamagictmp2 >> 6 << 6) > 0);
            *(mode_1 ? &iop_mmio_hwport.dmac2.newch[0].madr : &iop_mmio_hwport.dmac1.oldch[4].madr) = dmamagictmp1;
            *(mode_1 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) = no_flush_cache | SD_DMA_START|SD_DMA_CS;
          }
          else
          {
            do_finish_block_clean_xfer(mode_1);
            BlockHandlerIntrData[mode_1].cb = 0;
            BlockHandlerIntrData[mode_1].userdata = 0;
          }
        }
        else
        {
          do_finish_block_clean_xfer(mode_1);
        }
        if ( !no_flush_cache )
        {
          FlushDcache();
          return 1;
        }
      }
      else
      {
        if ( (mode & 0x1000) != 0 )
        {
          BlockTransBuff[mode_1] = 1 - BlockTransBuff[mode_1];
          *(((vu16 *)(mode_1 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr)) + 1) = (int)BlockTransSize[mode_1] / 64
                                                                  + ((int)BlockTransSize[mode_1] % 64 > 0);
          *(mode_1 ? &iop_mmio_hwport.dmac2.newch[0].madr : &iop_mmio_hwport.dmac1.oldch[4].madr) = BlockTransAddr[mode_1] + BlockTransBuff[mode_1] * BlockTransSize[mode_1];
          *(mode_1 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) = no_flush_cache | SD_DMA_START|SD_DMA_CS;
        }
        else
        {
          do_finish_block_clean_xfer(mode_1);
        }
        if ( !no_flush_cache )
        {
          FlushDcache();
        }
        if ( TransIntrHandlers[mode_1] )
        {
          TransIntrHandlers[mode_1](mode_1, intr->data);
          return 1;
        }
        if ( TransIntrCallbacks[mode_1] )
        {
          TransIntrCallbacks[mode_1](0);
          return 1;
        }
      }
      return 1;
    default:
      return 1;
  }
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00402EB8) --------------------------------------------------------
u32 __fastcall thunk_sceSdBlockTransStatus(int channel)
{
  int dmamagictmp1; // $a2

  dmamagictmp1 = *(channel ? &iop_mmio_hwport.dmac2.newch[0].madr : &iop_mmio_hwport.dmac1.oldch[4].madr);
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
  u32 startaddr_tmp; // $s3
  signed int size_align; // $s1
  unsigned int other_align; // $v1
  int size_align_r6; // $v1
  int state; // [sp+14h] [-4h] BYREF

  chan_tmp0 = chan & 1;
  startaddr_tmp = startaddr;
  BlockTransAddr[chan_tmp0] = iopaddr;
  BlockTransBuff[chan_tmp0] = 0;
  BlockTransSize[chan_tmp0] = size;
  if ( startaddr )
  {
    size_align = size - (startaddr - iopaddr);
    if ( startaddr - iopaddr >= size )
    {
      other_align = startaddr - iopaddr - size;
      if ( (mode & SD_TRANS_LOOP) == 0 || other_align >= size )
        return -100;
      ++BlockTransBuff[chan_tmp0];
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
  spu2_regs.u.main_regs.core_regs[chan_tmp0].cregs.attr &= ~SD_CORE_DMA;
  CpuResumeIntr(state);
  spu2_regs.u.main_regs.core_regs[chan_tmp0].cregs.tsa.pair[0] = 0;
  spu2_regs.u.main_regs.core_regs[chan_tmp0].cregs.tsa.pair[1] = 0;
  spu2_regs.u.main_regs.core_regs[chan_tmp0].cregs.admas = 1 << chan_tmp0;
  SetDmaWrite(chan_tmp0);
  *(chan_tmp0 ? &iop_mmio_hwport.dmac2.newch[0].madr : &iop_mmio_hwport.dmac1.oldch[4].madr) = startaddr_tmp;
  *(vu16 *)(chan_tmp0 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr) = 16;
  size_align_r6 = size_align >> 6;
  if ( size_align < 0 )
    size_align_r6 = (size_align + 63) >> 6;
  *(((vu16 *)(chan_tmp0 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr)) + 1) = size_align_r6 + (size_align - (size_align_r6 << 6) > 0);
  *(chan_tmp0 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) = SD_DMA_START|SD_DMA_CS|SD_DMA_DIR_IOP2SPU;
  return size;
}
// BF800000: using guessed type iop_mmio_hwport_t iop_mmio_hwport;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00403174) --------------------------------------------------------
u32 __fastcall BlockTransRead(u32 iopaddr, u32 size, char chan, __int16 mode)
{
  int chan_tmp1; // $s3
  int state; // [sp+14h] [-4h] BYREF

  chan_tmp1 = chan & 1;
  BlockTransAddr[chan_tmp1] = iopaddr;
  BlockTransBuff[chan_tmp1] = 0;
  BlockTransSize[chan_tmp1] = size;
  CpuSuspendIntr(&state);
  spu2_regs.u.main_regs.core_regs[chan_tmp1].cregs.attr &= ~SD_CORE_DMA;
  CpuResumeIntr(state);
  spu2_regs.u.main_regs.core_regs[chan_tmp1].cregs.tsa.pair[0] = 0;
  spu2_regs.u.main_regs.core_regs[chan_tmp1].cregs.tsa.pair[1] = 2 * (mode & ~0xF0FF) + 1024;
  spu2_regs.u.main_regs.core_regs[chan_tmp1].cregs.unk1ae = (unsigned __int16)(mode & ~0xFFF) >> 11;
  libsd_do_busyloop_1(3);
  spu2_regs.u.main_regs.core_regs[chan_tmp1].cregs.admas = 4;
  SetDmaRead(chan_tmp1);
  *(chan_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].madr : &iop_mmio_hwport.dmac1.oldch[4].madr) = iopaddr;
  *(vu16 *)(chan_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr) = 16;
  *(((vu16 *)(chan_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].bcr : &iop_mmio_hwport.dmac1.oldch[4].bcr)) + 1) = (int)BlockTransSize[chan_tmp1] / 64
                                                              + ((int)BlockTransSize[chan_tmp1] % 64 > 0);
  *(chan_tmp1 ? &iop_mmio_hwport.dmac2.newch[0].chcr : &iop_mmio_hwport.dmac1.oldch[4].chcr) = SD_DMA_START|SD_DMA_CS;
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
  if ( !dmat )
    return -1;
  for ( waitcnt = 0, dma_status = 0; waitcnt >= 0 && dma_status >= 0; ++waitcnt )
  {
    CpuSuspendIntr(&state);
    dma_status = sceSifDmaStat(dmat);
    CpuResumeIntr(state);
  }
  if ( waitcnt < 0 )
    return -1;
  return 0;
}

//----- (004033FC) --------------------------------------------------------
int __cdecl sceSdProcBatch(sceSdBatch *batch, u32 *rets, u32 num)
{
  unsigned int retres; // $s2
  u32 *rets_cr; // $s3
  int loop; // $s4
  u32 Param; // $s1

  rets_cr = rets;
  loop = -1;
  for ( retres = 0; retres < num; ++retres )
  {
    Param = 0;
    switch ( batch->func )
    {
      case SD_BATCH_SETPARAM:
        sceSdSetParam(batch->entry, batch->value);
        break;
      case SD_BATCH_SETSWITCH:
        sceSdSetSwitch(batch->entry, batch->value);
        break;
      case SD_BATCH_SETADDR:
        sceSdSetAddr(batch->entry, batch->value);
        break;
      case SD_BATCH_SETCORE:
        sceSdSetCoreAttr(batch->entry, batch->value);
        break;
      case SD_BATCH_WRITEIOP:
        *(_DWORD *)batch->value = batch->entry;
        break;
      case SD_BATCH_WRITEEE:
        BatchData = batch->entry;
        Param = SifDmaBatch((void *)batch->value, &BatchData, 4);
        break;
      case SD_BATCH_EERETURN:
        Param = SifDmaBatch((void *)batch->value, rets, batch->entry);
        break;
      case SD_BATCH_GETPARAM|SD_BATCH_SETPARAM:
        Param = sceSdGetParam(batch->entry);
        break;
      case SD_BATCH_GETSWITCH:
        Param = sceSdGetSwitch(batch->entry);
        break;
      case SD_BATCH_GETADDR:
        Param = sceSdGetAddr(batch->entry);
        break;
      case SD_BATCH_GETCORE:
        Param = sceSdGetCoreAttr(batch->entry);
        break;
      default:
        return loop;
    }
    if ( rets )
      *rets_cr = Param;
    ++rets_cr;
    --loop;
    ++batch;
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

  loop = 0;
  for ( retres_flip = 0; retres_flip < num; ++retres_flip )
  {
    Param = 0;
    switch ( batch->func )
    {
      case SD_BATCH_SETPARAM:
        if ( (batch->entry & 0x3E) == 0x3E )
        {
          for ( voicei1 = 0; voicei1 < 24; ++voicei1 )
          {
            if ( ((1 << voicei1) & voice) != 0 )
            {
              ++loop;
              sceSdSetParam((batch->entry & ~0x3E) | (2 * voicei1), batch->value);
            }
          }
          --loop;
        }
        else
        {
          sceSdSetParam(batch->entry, batch->value);
        }
        break;
      case SD_BATCH_SETSWITCH:
        sceSdSetSwitch(batch->entry, batch->value);
        break;
      case SD_BATCH_SETADDR:
        if ( (batch->entry & 0x7E) == 0x7E )
        {
          for ( voicei2 = 0; voicei2 < 24; ++voicei2 )
          {
            if ( ((1 << voicei2) & voice) != 0 )
            {
              ++loop;
              sceSdSetAddr((batch->entry & ~0x3E) | (2 * voicei2), batch->value);
            }
          }
          --loop;
        }
        else
        {
          sceSdSetAddr(batch->entry, batch->value);
        }
        break;
      case SD_BATCH_SETCORE:
        sceSdSetCoreAttr(batch->entry, batch->value);
        break;
      case SD_BATCH_WRITEIOP:
        *(_DWORD *)batch->value = batch->entry;
        break;
      case SD_BATCH_WRITEEE:
        BatchData = batch->entry;
        Param = SifDmaBatch((void *)batch->value, &BatchData, 4);
        break;
      case SD_BATCH_EERETURN:
        Param = SifDmaBatch((void *)batch->value, rets, batch->entry);
        break;
      case SD_BATCH_GETPARAM|SD_BATCH_SETPARAM:
        if ( (batch->entry & 0x3E) == 0x3E )
        {
          retsptrtmp1 = &rets[loop];
          for ( voicei3 = 0; voicei3 < 24; ++voicei3 )
          {
            if ( ((1 << voicei3) & voice) != 0 )
              Param = sceSdGetParam((batch->entry & ~0x3E) | (2 * voicei3));
            if ( rets )
              *retsptrtmp1 = Param;
            ++retsptrtmp1;
            ++loop;
          }
          --loop;
        }
        else
        {
          Param = sceSdGetParam(batch->entry);
        }
        break;
      case SD_BATCH_GETSWITCH:
        Param = sceSdGetSwitch(batch->entry);
        break;
      case SD_BATCH_GETADDR:
        if ( (batch->entry & 0x7E) == 0x7E )
        {
          retsptrtmp2 = &rets[loop];
          for ( voicei4 = 0; voicei4 < 24; ++voicei4 )
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
          }
          --loop;
        }
        else
        {
          Param = sceSdGetAddr(batch->entry);
        }
        break;
      case SD_BATCH_GETCORE:
        Param = sceSdGetCoreAttr(batch->entry);
        break;
      default:
        return ~retres_flip;
    }
    if ( rets )
      rets[loop] = Param;
    ++batch;
    ++loop;
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
  const vu16 *regptr; // $a0

  regptr = &(*(vu16 **)((char *)ParamRegList + ((entry >> 6) & 0x3FC)))[512 * (entry & 1)];
  return *regptr | (regptr[1] << 16);
}

//----- (00403ACC) --------------------------------------------------------
void __cdecl sceSdSetAddr(u16 entry, u32 value)
{
  vu16 *reg1; // $a1

  reg1 = &(*(vu16 **)((char *)ParamRegList + ((entry >> 6) & 0x3FC)))[512 * (entry & 1) + 3 * (entry & 0x3E)];
  reg1[0] = value >> 17;
  if ( (entry & 0xFF00) != 0x1D00 )
    reg1[1] = (value >> 1) & ~7;
}

//----- (00403B30) --------------------------------------------------------
u32 __cdecl sceSdGetAddr(u16 entry)
{
  int retlo; // $a3
  const vu16 *reg1; // $a1
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
  if ( (offset1 & 0x8000u) != 0 || (!(_WORD)offset1 && fine_x6 < 0) )
  {
    offset1 += 12;
    offset2 -= 1;
  }
  if ( fine_x6 < 0 )
  {
    fine_x6 += (fine_x5 + 1) << 7;
    offset1 -= 1;
    offset1 += fine_x5;
  }
  retval = (*(unsigned __int16 *)((char *)NotePitchTable + ((offset1 << 16) >> 15))
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
  int val; // $a2
  int i2; // $a3
  int i5; // $a3

  bit = 0;
  i4 = 0;
  offset2 = 0;
  if ( pitch >= 0x4000u )
    pitch = 0x3FFF;
  for ( i1 = 0; i1 < 14; i1 += 1 )
  {
    if ( (((int)pitch >> i1) & 1) != 0 )
      bit = i1;
  }
  val = pitch << (15 - bit);
  for ( i2 = 11; (unsigned __int16)val < (unsigned int)(unsigned __int16)NotePitchTable[i2]; i2 -= 1 )
  {
    if ( i2 <= 0 )
    {
      i2 = 0;
      break;
    }
  }
  i4 = i2;
  if ( !NotePitchTable[i4] )
    __builtin_trap();
  for ( i5 = 127; (unsigned __int16)(((unsigned __int16)val << 15) / (unsigned int)(unsigned __int16)NotePitchTable[i4]) < (unsigned int)(unsigned __int16)NotePitchTable[i5 + 12]; i5 -= 1 )
  {
    if ( i5 <= 0 )
    {
      i5 = offset2;
      break;
    }
  }
  offset2 = i5;
  return (((center_fine + offset2 + 1) & 0x7E)
        + ((i4 + center_note + 12 * (bit - 12) + ((unsigned __int16)(center_fine + offset2 + 1) >> 7)) << 8)) & ~1;
}

//----- (00403E20) --------------------------------------------------------
int __fastcall SetSpdifMode(int val)
{
  __int16 out_mask_fe57_2; // $t0
  __int16 out_mask_apply_8000; // $a1

  out_mask_fe57_2 = spu2_regs.u.extra_regs.spdif_out & ~0x1A8;
  out_mask_apply_8000 = spu2_regs.u.extra_regs.spdif_mode & ~6;
  switch ( val & 0xF )
  {
    case 0:
      out_mask_fe57_2 |= 0x20;
      break;
    case 1:
      out_mask_fe57_2 |= 0x100;
      out_mask_apply_8000 |= 2;
      break;
    case 2:
      break;
    case 3:
      out_mask_fe57_2 |= 0x100;
      break;
    default:
      return -100;
  }
  if ( (val & 0x80) != 0 )
    out_mask_apply_8000 |= 0x8000;
  else
    out_mask_apply_8000 &= ~0x8000;
  switch ( val & 0xF00 )
  {
    case 0x400:
      spu2_regs.u.extra_regs.spdif_media = 0;
      out_mask_apply_8000 &= ~0x3F00;
      out_mask_apply_8000 |= 0x100;
      break;
    case 0x800:
      spu2_regs.u.extra_regs.spdif_media = 512;
      out_mask_apply_8000 &= ~0x3F00;
      out_mask_apply_8000 |= 0x1900;
      break;
    default:
      spu2_regs.u.extra_regs.spdif_media = 512;
      out_mask_apply_8000 &= ~0x3F00;
      out_mask_apply_8000 |= 0x900;
      break;
  }
  spu2_regs.u.extra_regs.spdif_out = out_mask_fe57_2;
  spu2_regs.u.extra_regs.spdif_mode = out_mask_apply_8000;
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
  int state; // [sp+10h] [-8h] BYREF

  setting_tmp = *(_WORD *)((char *)&SpdifSettings + (entry & 0xE) + 2);// should point to CoreAttrShifts
  CpuSuspendIntr(&state);
  param_tmp = (entry & 1) | 0x2300;
  sceSdSetParam(param_tmp, (sceSdGetParam(param_tmp) & ~(1 << setting_tmp)) | ((val & 1) << setting_tmp));
  CpuResumeIntr(state);
}
// 4055E0: using guessed type int SpdifSettings;

//----- (00403FEC) --------------------------------------------------------
void __cdecl sceSdSetCoreAttr(u16 entry, u16 value)
{
  u16 param_tmp; // $s0
  int state; // [sp+10h] [-8h] BYREF

  switch ( entry & ~0xFFFF0001 )
  {
    case SD_CORE_SPDIF_MODE:
      SetSpdifMode(value);
      break;
    case SD_CORE_NOISE_CLK:
      CpuSuspendIntr(&state);
      param_tmp = (entry & 1) | 0x2300;
      sceSdSetParam(param_tmp, (sceSdGetParam(param_tmp) & ~0x3F00) | ((value & 0x3F) << 8));
      CpuResumeIntr(state);
      break;
    default:
      sceSdSetCoreAttr_default(entry, value);
      break;
  }
}

//----- (004040A0) --------------------------------------------------------
u16 __cdecl sceSdGetCoreAttr(u16 entry)
{
  switch ( entry & 0xE )
  {
    case SD_CORE_EFFECT_ENABLE:
      return (spu2_regs.u.main_regs.core_regs[entry & 1].cregs.attr >> 7) & 1;
    case SD_CORE_IRQ_ENABLE:
      return (spu2_regs.u.main_regs.core_regs[entry & 1].cregs.attr >> 6) & 1;
    case SD_CORE_MUTE_ENABLE:
      return (spu2_regs.u.main_regs.core_regs[entry & 1].cregs.attr >> 14) & 1;
    case SD_CORE_NOISE_CLK:
      return (spu2_regs.u.main_regs.core_regs[entry & 1].cregs.attr >> 8) & 0x3F;
    case SD_CORE_SPDIF_MODE:
      return SpdifSettings & 0xFFFF;
    default:
      return 0;
  }
}
// 4055E0: using guessed type int SpdifSettings;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404130) --------------------------------------------------------
SdIntrCallback __cdecl sceSdSetTransCallback(s32 core, SdIntrCallback cb)
{
  SdIntrCallback oldtmp; // $v0

  oldtmp = TransIntrCallbacks[(unsigned __int16)core];
  TransIntrCallbacks[(unsigned __int16)core] = cb;
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
  int val; // $a0

  (void)data;
  if ( !Spu2IntrHandler && !Spu2IrqCallback )
  {
    return 1;
  }
  while ( ( val = (unsigned __int8)(spu2_regs.u.extra_regs.spdif_irqinfo & 0xC) >> 2 ) )
  {
    if ( val & 1 )
      spu2_regs.u.main_regs.core_regs[0].cregs.attr &= ~0x40u;
    if ( val & 2 )
      spu2_regs.u.main_regs.core_regs[1].cregs.attr &= ~0x40u;
    if ( Spu2IntrHandler )
      Spu2IntrHandler(val, Spu2IntrHandlerData);
    else if ( Spu2IrqCallback )
      Spu2IrqCallback(0);
  }
  return 1;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404344) --------------------------------------------------------
int InitVoices()
{
  int i2; // [sp+10h] [-8h]
  int i1; // [sp+10h] [-8h]
  int i1a; // [sp+10h] [-8h]

  spu2_regs.u.main_regs.core_regs[0].cregs.attr &= ~SD_CORE_DMA;
  spu2_regs.u.main_regs.core_regs[0].cregs.tsa.pair[0] = 0x0000;
  spu2_regs.u.main_regs.core_regs[0].cregs.tsa.pair[1] = 0x2800;
  for ( i2 = 0; i2 < 8; ++i2 )
  {
    spu2_regs.u.main_regs.core_regs[0].cregs.xferdata_1ac = VoiceDataInit[i2];
  }
  spu2_regs.u.main_regs.core_regs[0].cregs.attr = (spu2_regs.u.main_regs.core_regs[0].cregs.attr & ~SD_CORE_DMA) | SD_DMA_IO;
  for ( i1 = 0; (spu2_regs.u.main_regs.core_regs[0].cregs.statx & SD_IO_IN_PROCESS) != 0 && i1 <= 0x1000000; ++i1 )
  {
    libsd_do_busyloop_1(1);
  }
  spu2_regs.u.main_regs.core_regs[0].cregs.attr &= ~SD_CORE_DMA;
  for ( i1a = 0; i1a < 24; ++i1a )
  {
    spu2_regs.u.main_regs.core_regs[1].cregs.voice_params[i1a].voll = 0;
    spu2_regs.u.main_regs.core_regs[0].cregs.voice_params[i1a].voll = 0;
    spu2_regs.u.main_regs.core_regs[1].cregs.voice_params[i1a].volr = 0;
    spu2_regs.u.main_regs.core_regs[0].cregs.voice_params[i1a].volr = 0;
    spu2_regs.u.main_regs.core_regs[1].cregs.voice_params[i1a].pitch = 0x3FFF;
    spu2_regs.u.main_regs.core_regs[0].cregs.voice_params[i1a].pitch = 0x3FFF;
    spu2_regs.u.main_regs.core_regs[1].cregs.voice_params[i1a].adsr1 = 0;
    spu2_regs.u.main_regs.core_regs[0].cregs.voice_params[i1a].adsr1 = 0;
    spu2_regs.u.main_regs.core_regs[1].cregs.voice_params[i1a].adsr2 = 0;
    spu2_regs.u.main_regs.core_regs[0].cregs.voice_params[i1a].adsr2 = 0;
    spu2_regs.u.main_regs.core_regs[1].cregs.voice_address[i1a].ssa.pair[0] = 0;
    spu2_regs.u.main_regs.core_regs[0].cregs.voice_address[i1a].ssa.pair[0] = 0;
    spu2_regs.u.main_regs.core_regs[1].cregs.voice_address[i1a].ssa.pair[1] = 0x2800;
    spu2_regs.u.main_regs.core_regs[0].cregs.voice_address[i1a].ssa.pair[1] = 0x2800;
  }
  spu2_regs.u.main_regs.core_regs[1].cregs.kon.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.kon.pair[1] = 0xFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.kon.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.kon.pair[1] = 0xFF;
  libsd_do_busyloop_1(3);
  spu2_regs.u.main_regs.core_regs[1].cregs.koff.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[1].cregs.koff.pair[1] = 0xFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.koff.pair[0] = 0xFFFF;
  spu2_regs.u.main_regs.core_regs[0].cregs.koff.pair[1] = 0xFF;
  libsd_do_busyloop_1(3);
  spu2_regs.u.main_regs.core_regs[0].cregs.endx.pair[1] = 0;
  spu2_regs.u.main_regs.core_regs[0].cregs.endx.pair[0] = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.endx.pair[1] = 0;
  spu2_regs.u.main_regs.core_regs[1].cregs.endx.pair[0] = 0;
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404644) --------------------------------------------------------
int __fastcall Reset(char flag)
{
  iop_event_t efparam; // [sp+10h] [-18h] BYREF
  int intrstate; // [sp+20h] [-8h] BYREF

  DisableIntr(36, &intrstate);
  DisableIntr(40, &intrstate);
  DisableIntr(9, &intrstate);
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
  if ( (flag & 0xF) == 0 )
  {
    bzero(EffectAttr, 40);
    EffectAddr[0] = 0x1DFFF0;
    EffectAddr[1] = 0x1FFFF0;
    spu2_regs.u.main_regs.core_regs[0].cregs.esa.pair[0] = 0x000E;
    spu2_regs.u.main_regs.core_regs[0].cregs.esa.pair[1] = 0xFFF8;
    spu2_regs.u.main_regs.core_regs[1].cregs.esa.pair[0] = 0x000F;
    spu2_regs.u.main_regs.core_regs[1].cregs.esa.pair[1] = 0xFFF8;
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
  int resetres; // $s2

  InitSpu2();
  if ( (flag & 0xF) == 0 )
    InitSpdif();
  resetres = Reset(flag & 0xFF);
  InitVoices();
  InitCoreVolume(flag & 0xF);
  EnableIntr(36);
  EnableIntr(40);
  EnableIntr(9);
  RegisterIntrHandler(36, 1, (int (__cdecl *)(void *))TransInterrupt, &TransIntrData[0]);
  RegisterIntrHandler(40, 1, (int (__cdecl *)(void *))TransInterrupt, &TransIntrData[1]);
  RegisterIntrHandler(9, 1, (int (__cdecl *)(void *))Spu2Interrupt, Spu2IntrHandlerData);
  vars_inited = 1;
  return resetres;
}
// 405628: using guessed type int vars_inited;

//----- (004049C4) --------------------------------------------------------
int __cdecl sceSdQuit()
{
  int intrstate; // [sp+10h] [-8h] BYREF

  DmaStartStop((0 << 4) | 0xA, 0, 0);
  DmaStartStop((1 << 4) | 0xA, 0, 0);
  if ( VoiceTransCompleteEf[0] > 0 )
    DeleteEventFlag(VoiceTransCompleteEf[0]);
  if ( VoiceTransCompleteEf[1] > 0 )
    DeleteEventFlag(VoiceTransCompleteEf[1]);
  DisableIntr(40, &intrstate);
  DisableIntr(36, &intrstate);
  DisableIntr(9, &intrstate);
  ReleaseIntrHandler(40);
  ReleaseIntrHandler(36);
  ReleaseIntrHandler(9);
  return 0;
}
