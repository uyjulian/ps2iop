
#include <irx_imports.h>

#include <stdarg.h>
#include <stdbool.h>
#include <libsd.h>
#include <iop_mmio_hwport.h>

IRX_ID("Sound_Device_Library", 3, 3);

#define __cdecl
#define __fastcall

#define SD_DMA_CS           (1 << 9) // Continuous stream
#define SD_DMA_START          (1 << 24)
#define SD_DMA_DIR_SPU2IOP        0
#define SD_DMA_DIR_IOP2SPU        1

extern struct irx_export_table _exp_libsd;

typedef struct spu2_u16pair_
{
  vu16 m_pair[2];
} spu2_u16pair_t;

typedef struct spu2_voice_params_
{
  vu16 m_voll;
  vu16 m_volr;
  vu16 m_pitch;
  vu16 m_adsr1;
  vu16 m_adsr2;
  vu16 m_envx;
  vu16 m_volxl;
  vu16 m_volxr;
} spu2_voice_params_t;

typedef struct spu2_voice_address_
{
  spu2_u16pair_t m_ssa;
  spu2_u16pair_t m_lsax;
  spu2_u16pair_t m_nax;
} spu2_voice_address_t;

typedef struct spu2_core_regs_
{
  spu2_voice_params_t m_voice_params[24]; /* 0x000 */
  spu2_u16pair_t m_pmon; /* 0x180 */
  spu2_u16pair_t m_non; /* 0x184 */
  spu2_u16pair_t m_vmixl; /* 0x188 */
  spu2_u16pair_t m_vmixel; /* 0x18c */
  spu2_u16pair_t m_vmixr; /* 0x190 */
  spu2_u16pair_t m_vmixer; /* 0x194 */
  vu16 m_mmix; /* 0x198 */
  vu16 m_attr; /* 0x19a */
  spu2_u16pair_t m_irqa; /* 0x19c */
  spu2_u16pair_t m_kon; /* 0x1a0 */
  spu2_u16pair_t m_koff; /* 0x1a4 */
  spu2_u16pair_t m_tsa; /* 0x1a8 */
  vu16 m_xferdata; /* 0x1ac */
  vu16 m_unk1ae; /* 0x1ae */
  vu16 m_admas; /* 0x1b0 */
  vu16 unk1b2[7]; /* 0x1b2 */
  spu2_voice_address_t m_voice_address[24]; /* 0x1c0 */
  spu2_u16pair_t m_esa; /* 0x2e0 */
  spu2_u16pair_t m_apf1_size; /* 0x2e4 */
  spu2_u16pair_t m_apf2_size; /* 0x2e8 */
  spu2_u16pair_t m_same_l_dst; /* 0x2EC */
  spu2_u16pair_t m_same_r_dst; /* 0x2F0 */
  spu2_u16pair_t m_comb1_l_src; /* 0x2F4 */
  spu2_u16pair_t m_comb1_r_src; /* 0x2F8 */
  spu2_u16pair_t m_comb2_l_src; /* 0x2FC */
  spu2_u16pair_t m_comb2_r_src; /* 0x300 */
  spu2_u16pair_t m_same_l_src; /* 0x304 */
  spu2_u16pair_t m_same_r_src; /* 0x308 */
  spu2_u16pair_t m_diff_l_dst; /* 0x30C */
  spu2_u16pair_t m_diff_r_dst; /* 0x310 */
  spu2_u16pair_t m_comb3_l_src; /* 0x314 */
  spu2_u16pair_t m_comb3_r_src; /* 0x318 */
  spu2_u16pair_t m_comb4_l_src; /* 0x31C */
  spu2_u16pair_t m_comb4_r_src; /* 0x320 */
  spu2_u16pair_t m_diff_l_src; /* 0x324 */
  spu2_u16pair_t m_diff_r_src; /* 0x328 */
  spu2_u16pair_t m_apf1_l_dst; /* 0x32C */
  spu2_u16pair_t m_apf1_r_dst; /* 0x330 */
  spu2_u16pair_t m_apf2_l_dst; /* 0x334 */
  spu2_u16pair_t m_apf2_r_dst; /* 0x338 */
  vu16 m_eea; /* 0x33C */
  vu16 unk33e; /* 0x33E */
  spu2_u16pair_t m_endx; /* 0x340 */
  vu16 m_statx; /* 0x344 */
  vu16 unk346[13]; /* 0x346 */
} spu2_core_regs_t;

typedef struct spu2_different_regs_
{
  vu16 m_mvoll; /* 0x760 */
  vu16 m_mvolr; /* 0x762 */
  vu16 m_evoll; /* 0x764 */
  vu16 m_evolr; /* 0x766 */
  vu16 m_avoll; /* 0x768 */
  vu16 m_avolr; /* 0x76A */
  vu16 m_bvoll; /* 0x76C */
  vu16 m_bvolr; /* 0x76E */
  vu16 m_mvolxl; /* 0x770 */
  vu16 m_mvolxr; /* 0x772 */
  vu16 m_iir_vol; /* 0x774 */
  vu16 m_comb1_vol; /* 0x776 */
  vu16 m_comb2_vol; /* 0x778 */
  vu16 m_comb3_vol; /* 0x77A */
  vu16 m_comb4_vol; /* 0x77C */
  vu16 m_wall_vol; /* 0x77E */
  vu16 m_apf1_vol; /* 0x780 */
  vu16 m_apf2_vol; /* 0x782 */
  vu16 m_in_coef_l; /* 0x784 */
  vu16 m_in_coef_r; /* 0x786 */
} spu2_different_regs_t;

typedef struct spu2_core_regs_padded_
{
  spu2_core_regs_t m_cregs;
  vu16 padding[80];
} spu2_core_regs_padded_t;

typedef struct spu2_regs_main_
{
  spu2_core_regs_padded_t m_core_regs[2];
} spu2_regs_main_t;

typedef struct spu2_regs_extra_
{
  spu2_core_regs_t core0_regs;
  vu16 padding346[80];
  spu2_core_regs_t core1_regs; /* 0x400 */
  spu2_different_regs_t m_different_regs[2];
  vu16 unk7b0[8];
  vu16 m_spdif_out; /* 0x7c0 */
  vu16 m_spdif_irqinfo; /* 0x7c2 */
  vu16 unk7c4; /* 0x7c4 */
  vu16 m_spdif_mode; /* 0x7c6 */
  vu16 m_spdif_media; /* 0x7c8 */
  vu16 m_unknown7ca; /* 0x7ca */
  vu16 m_spdif_protect; /* 0x7cc */
  vu16 unk7ce[25];
} spu2_regs_extra_t;

typedef struct spu2_regs_ /* base => 0xBF900000 */
{
  union spu2_regs_union_
  {
    spu2_regs_main_t m_m;
    spu2_regs_extra_t m_e;
  } m_u;
} spu2_regs_t;

struct mode_data_struct
{
  u32 m_mode_flags;
  u16 m_d_apf1_size;
  u16 m_d_apf2_size;
  u16 m_d_iir_vol;
  u16 m_d_comb1_vol;
  u16 m_d_comb2_vol;
  u16 m_d_comb3_vol;
  u16 m_d_comb4_vol;
  u16 m_d_wall_vol;
  u16 m_d_apf1_vol;
  u16 m_d_apf2_vol;
  u16 m_d_same_l_dst;
  u16 m_d_same_r_dst;
  u16 m_d_comb1_l_src;
  u16 m_d_comb1_r_src;
  u16 m_d_comb2_l_src;
  u16 m_d_comb2_r_src;
  u16 m_d_same_l_src;
  u16 m_d_same_r_src;
  u16 m_d_diff_l_dst;
  u16 m_d_diff_r_dst;
  u16 m_d_comb3_l_src;
  u16 m_d_comb3_r_src;
  u16 m_d_comb4_l_src;
  u16 m_d_comb4_r_src;
  u16 m_d_diff_l_src;
  u16 m_d_diff_r_src;
  u16 m_d_apf1_l_dst;
  u16 m_d_apf1_r_dst;
  u16 m_d_apf2_l_dst;
  u16 m_d_apf2_r_dst;
  u16 m_d_in_coef_l;
  u16 m_d_in_coef_r;
};

typedef struct
{
  u32 m_mode;
  void *m_data;
} IntrData;

typedef int (*sceSdBlockTransHandler)(int channel, void *userdata, void **addr, int *size);

typedef struct BlockHandlerIntrData_
{
  sceSdBlockTransHandler m_cb;
  void *m_userdata;
} BlockHandlerIntrData_t;

typedef struct CleanRegionBufferElement_
{
  u32 *m_spuaddr;
  u32 m_size;
} CleanRegionBufferElement_t;


typedef struct CleanRegionBuffer_
{
  CleanRegionBufferElement_t m_elements[97];
} CleanRegionBuffer_t;

typedef int (*SdCleanHandler)(int);


//-------------------------------------------------------------------------
// Function declarations

int __cdecl sceSdClearEffectWorkArea(int core, int channel, int effect_mode);
int __cdecl sceSdCleanEffectWorkArea(int core, int channel, int effect_mode);
void __cdecl sceSdGetEffectAttr(int core, sceSdEffectAttr *attr);
int __cdecl sceSdSetEffectAttr(int core, sceSdEffectAttr *attr);
static int __fastcall GetEEA(int core);
int __cdecl sceSdSetEffectMode(int core, sceSdEffectAttr *param);
int __cdecl sceSdSetEffectModeParams(int core, sceSdEffectAttr *attr);
static void InitSpu2_Inner();
int __cdecl sceSdVoiceTrans(s16 chan, u16 mode, u8 *iopaddr, u32 *spuaddr, u32 size);
u32 __cdecl sceSdVoiceTransStatus(s16 channel, s16 flag);
int __cdecl sceSdStopTrans(int channel);
int sceSdBlockTrans(s16 chan, u16 mode, u8 *iopaddr, u32 size, ...);
u32 __cdecl sceSdBlockTransStatus(s16 channel, s16 flag);
static void libsd_do_busyloop_1(int);
static u32 __fastcall DmaStartStop(int mainarg, void *vararg2, unsigned int vararg3);
static unsigned int __fastcall VoiceTrans_Write_IOMode(const u16 *iopaddr, unsigned int size, int chan);
static unsigned int __fastcall BlockTransWriteFrom(u8 *iopaddr, unsigned int size, char chan, char mode, u8 *startaddr);
static u32 __fastcall BlockTransRead(u8 *iopaddr, u32 size, char chan, u16 mode);
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
void __cdecl sceSdSetCoreAttr(u16 entry, u16 value);
u16 __cdecl sceSdGetCoreAttr(u16 entry);
SdIntrCallback __cdecl sceSdSetTransCallback(s32 core, SdIntrCallback cb);
sceSdTransIntrHandler __cdecl sceSdSetTransIntrHandler(int channel, sceSdTransIntrHandler func, void *arg);
void *__cdecl sceSdGetTransIntrHandlerArgument(int arg);
SdIntrCallback __cdecl sceSdSetIRQCallback(SdIntrCallback cb);
sceSdSpu2IntrHandler __cdecl sceSdSetSpu2IntrHandler(sceSdSpu2IntrHandler func, void *arg);
void *__cdecl sceSdGetSpu2IntrHandlerArgument();
static void reset_vars();
int __cdecl sceSdInit(int flag);
int __cdecl sceSdQuit();

//-------------------------------------------------------------------------
// Data declarations

static vu16 *const g_ParamRegList[] =
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
static const int g_EffectSizes[] = { 2, 1240, 1000, 2312, 3580, 5564, 7896, 12296, 12296, 1920 };
static const struct mode_data_struct g_EffectParams[] =
{
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
    1u,
    1u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    1u,
    1u,
    0u,
    0u,
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
  },
  {
    0u,
    125u,
    91u,
    28032u,
    21688u,
    48848u,
    0u,
    0u,
    47744u,
    22528u,
    21248u,
    1238u,
    819u,
    1008u,
    551u,
    884u,
    495u,
    822u,
    439u,
    821u,
    438u,
    820u,
    437u,
    820u,
    437u,
    820u,
    437u,
    436u,
    310u,
    184u,
    92u,
    32768u,
    32768u
  },
  {
    0u,
    51u,
    37u,
    28912u,
    20392u,
    48352u,
    17424u,
    49392u,
    39936u,
    21120u,
    20160u,
    996u,
    795u,
    932u,
    687u,
    882u,
    614u,
    796u,
    605u,
    604u,
    398u,
    559u,
    309u,
    466u,
    183u,
    399u,
    181u,
    180u,
    128u,
    76u,
    38u,
    32768u,
    32768u
  },
  {
    0u,
    177u,
    127u,
    28912u,
    20392u,
    48352u,
    17680u,
    48880u,
    46272u,
    21120u,
    20160u,
    2308u,
    1899u,
    2084u,
    1631u,
    1954u,
    1558u,
    1900u,
    1517u,
    1516u,
    1070u,
    1295u,
    773u,
    1122u,
    695u,
    1071u,
    613u,
    612u,
    434u,
    256u,
    128u,
    32768u,
    32768u
  },
  {
    0u,
    227u,
    169u,
    28512u,
    20392u,
    48352u,
    17680u,
    48880u,
    42624u,
    22144u,
    21184u,
    3579u,
    2904u,
    3337u,
    2620u,
    3033u,
    2419u,
    2905u,
    2266u,
    2265u,
    1513u,
    2028u,
    1200u,
    1775u,
    978u,
    1514u,
    797u,
    796u,
    568u,
    340u,
    170u,
    32768u,
    32768u
  },
  {
    0u,
    421u,
    313u,
    24576u,
    20480u,
    19456u,
    47104u,
    48128u,
    49152u,
    24576u,
    23552u,
    5562u,
    4539u,
    5314u,
    4285u,
    4540u,
    3521u,
    4544u,
    3523u,
    3520u,
    2497u,
    3012u,
    1985u,
    2560u,
    1741u,
    2498u,
    1473u,
    1472u,
    1050u,
    628u,
    314u,
    32768u,
    32768u
  },
  {
    0u,
    829u,
    561u,
    32256u,
    20480u,
    46080u,
    45056u,
    19456u,
    45056u,
    24576u,
    21504u,
    7894u,
    6705u,
    7444u,
    6203u,
    7106u,
    5810u,
    6706u,
    5615u,
    5614u,
    4181u,
    4916u,
    3885u,
    4598u,
    3165u,
    4182u,
    2785u,
    2784u,
    1954u,
    1124u,
    562u,
    32768u,
    32768u
  },
  {
    0u,
    3u,
    3u,
    32767u,
    32767u,
    0u,
    0u,
    0u,
    33024u,
    0u,
    0u,
    8189u,
    4093u,
    4105u,
    9u,
    0u,
    0u,
    4105u,
    9u,
    8191u,
    8191u,
    8190u,
    8190u,
    8190u,
    8190u,
    8190u,
    8190u,
    4104u,
    4100u,
    8u,
    4u,
    32768u,
    32768u
  },
  {
    0u,
    3u,
    3u,
    32767u,
    32767u,
    0u,
    0u,
    0u,
    0u,
    0u,
    0u,
    8189u,
    4093u,
    4105u,
    9u,
    0u,
    0u,
    4105u,
    9u,
    8191u,
    8191u,
    8190u,
    8190u,
    8190u,
    8190u,
    8190u,
    8190u,
    4104u,
    4100u,
    8u,
    4u,
    32768u,
    32768u
  },
  {
    0u,
    23u,
    19u,
    28912u,
    20392u,
    48352u,
    17680u,
    48880u,
    34048u,
    24448u,
    21696u,
    881u,
    687u,
    741u,
    479u,
    688u,
    471u,
    856u,
    618u,
    470u,
    286u,
    301u,
    177u,
    287u,
    89u,
    416u,
    227u,
    88u,
    64u,
    40u,
    20u,
    32768u,
    32768u
  }
};
// Unofficial: move to bss
static const u32 g_ClearEffectData[256];
static spu2_regs_t *const g_ptr_to_bf900000 = (spu2_regs_t *)0xBF900000;
// Unofficial: move to bss
static int g_VoiceTransStatus[2];
// Unofficial: move to bss
static int g_VoiceTransIoMode[2];
static const u16 g_NotePitchTable[] =
{
  32768,
  34716,
  36780,
  38967,
  41285,
  43740,
  46340,
  49096,
  52015,
  55108,
  58385,
  61857,
  32768,
  32782,
  32797,
  32812,
  32827,
  32842,
  32856,
  32871,
  32886,
  32901,
  32916,
  32931,
  32945,
  32960,
  32975,
  32990,
  33005,
  33020,
  33035,
  33050,
  33065,
  33080,
  33094,
  33109,
  33124,
  33139,
  33154,
  33169,
  33184,
  33199,
  33214,
  33229,
  33244,
  33259,
  33274,
  33289,
  33304,
  33319,
  33334,
  33349,
  33364,
  33379,
  33394,
  33410,
  33425,
  33440,
  33455,
  33470,
  33485,
  33500,
  33515,
  33530,
  33546,
  33561,
  33576,
  33591,
  33606,
  33621,
  33636,
  33652,
  33667,
  33682,
  33697,
  33712,
  33728,
  33743,
  33758,
  33773,
  33789,
  33804,
  33819,
  33834,
  33850,
  33865,
  33880,
  33896,
  33911,
  33926,
  33941,
  33957,
  33972,
  33987,
  34003,
  34018,
  34033,
  34049,
  34064,
  34080,
  34095,
  34110,
  34126,
  34141,
  34157,
  34172,
  34187,
  34203,
  34218,
  34234,
  34249,
  34265,
  34280,
  34296,
  34311,
  34327,
  34342,
  34358,
  34373,
  34389,
  34404,
  34420,
  34435,
  34451,
  34466,
  34482,
  34497,
  34513,
  34528,
  34544,
  34560,
  34575,
  34591,
  34606,
  34622,
  34638,
  34653,
  34669,
  34685,
  34700,
};
// Unofficial: move to bss
static int g_SpdifSettings;
static const u16 g_CoreAttrShifts[] = { 7, 6, 14, 8 };
// Unofficial: move to bss
static sceSdEffectAttr g_EffectAttr[2];
// Unofficial: move to bss
static int g_VoiceTransCompleteBool[2];
// Unofficial: move to bss
static int g_VoiceTransCompleteEf[2];
// Unofficial: move to bss
static int g_vars_inited;
// Unofficial: move to bss
static SdIntrCallback g_Spu2IrqCallback;
// Unofficial: move to bss
static sceSdSpu2IntrHandler g_Spu2IntrHandler;
// Unofficial: move to bss
static void *g_Spu2IntrHandlerData;
// Unofficial: move to bss
static sceSdTransIntrHandler g_TransIntrHandlers[2];
// Unofficial: move to bss
static BlockHandlerIntrData_t g_BlockHandlerIntrData[2];
// Unofficial: move to bss
static SdCleanHandler g_CleanHandlers[2];
// Unofficial: move to bss
static IntrData g_TransIntrData[2];
static const u16 g_VoiceDataInit[] = { 1792, 0, 0, 0, 0, 0, 0, 0 };
static u32 g_CleanRegionMax[2];
static u32 g_CleanRegionCur[2];
static CleanRegionBuffer_t g_CleanRegionBuffer[2];
static u32 g_BlockTransBuff[2];
static u8 *g_BlockTransAddr[2];
static u32 g_BlockTransSize[2];
static u32 g_BatchData;
static SdIntrCallback g_TransIntrCallbacks[2];
static u32 g_EffectAddr[2];
spu2_regs_t spu2_regs; // weak

//----- (004000B0) --------------------------------------------------------
int _start()
{
  int regres; // $s0
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  regres = RegisterLibraryEntries(&_exp_libsd);
  CpuResumeIntr(state);
  if ( regres )
    return 1;
  InitSpu2_Inner();
  reset_vars();
  return 0;
}

//----- (00400110) --------------------------------------------------------
static void SetEffectRegisterPair(spu2_u16pair_t *pair, int val)
{
  unsigned int rval; // $a2

  rval = val << 2;
  // Unofficial: receive register pair instead of base+offset
  pair->m_pair[0] = (rval >> 16) & 0xFFFF;
  pair->m_pair[1] = rval;
}

//----- (0040013C) --------------------------------------------------------
static void __cdecl SetEffectData(int core, const struct mode_data_struct *mode_data)
{
  int mode_flags; // $s0

  mode_flags = mode_data->m_mode_flags;
  if ( !mode_flags )
    mode_flags = 0xFFFFFFFF;
  if ( (mode_flags & 1) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_apf1_size, mode_data->m_d_apf1_size);
  if ( (mode_flags & 2) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_apf2_size, mode_data->m_d_apf2_size);
  if ( ((mode_flags & 4)) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_iir_vol = mode_data->m_d_iir_vol;
  if ( (mode_flags & 8) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_comb1_vol = mode_data->m_d_comb1_vol;
  if ( (mode_flags & 0x10) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_comb2_vol = mode_data->m_d_comb2_vol;
  if ( (mode_flags & 0x20) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_comb3_vol = mode_data->m_d_comb3_vol;
  if ( (mode_flags & 0x40) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_comb4_vol = mode_data->m_d_comb4_vol;
  if ( (mode_flags & 0x80) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_wall_vol = mode_data->m_d_wall_vol;
  if ( (mode_flags & 0x100) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_apf1_vol = mode_data->m_d_apf1_vol;
  if ( (mode_flags & 0x200) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_apf2_vol = mode_data->m_d_apf2_vol;
  if ( (mode_flags & 0x400) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_same_l_dst, mode_data->m_d_same_l_dst);
  if ( (mode_flags & 0x800) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_same_r_dst, mode_data->m_d_same_r_dst);
  if ( (mode_flags & 0x1000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_comb1_l_src, mode_data->m_d_comb1_l_src);
  if ( (mode_flags & 0x2000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_comb1_r_src, mode_data->m_d_comb1_r_src);
  if ( (mode_flags & 0x4000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_comb2_l_src, mode_data->m_d_comb2_l_src);
  if ( (mode_flags & 0x8000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_comb2_r_src, mode_data->m_d_comb2_r_src);
  if ( (mode_flags & 0x10000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_same_l_src, mode_data->m_d_same_l_src);
  if ( (mode_flags & 0x20000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_same_r_src, mode_data->m_d_same_r_src);
  if ( (mode_flags & 0x40000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_diff_l_dst, mode_data->m_d_diff_l_dst);
  if ( (mode_flags & 0x80000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_diff_r_dst, mode_data->m_d_diff_r_dst);
  if ( (mode_flags & 0x100000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_comb3_l_src, mode_data->m_d_comb3_l_src);
  if ( (mode_flags & 0x200000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_comb3_r_src, mode_data->m_d_comb3_r_src);
  if ( (mode_flags & 0x400000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_comb4_l_src, mode_data->m_d_comb4_l_src);
  if ( (mode_flags & 0x800000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_comb4_r_src, mode_data->m_d_comb4_r_src);
  if ( (mode_flags & 0x1000000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_diff_l_src, mode_data->m_d_diff_l_src);
  if ( (mode_flags & 0x2000000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_diff_r_src, mode_data->m_d_diff_r_src);
  if ( (mode_flags & 0x4000000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_apf1_l_dst, mode_data->m_d_apf1_l_dst);
  if ( (mode_flags & 0x8000000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_apf1_r_dst, mode_data->m_d_apf1_r_dst);
  if ( (mode_flags & 0x10000000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_apf2_l_dst, mode_data->m_d_apf2_l_dst);
  if ( (mode_flags & 0x20000000) )
    SetEffectRegisterPair(&g_ptr_to_bf900000->m_u.m_m.m_core_regs[core].m_cregs.m_apf2_r_dst, mode_data->m_d_apf2_r_dst);
  if ( (mode_flags & 0x40000000) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_in_coef_l = mode_data->m_d_in_coef_l;
  if ( (mode_flags & 0x80000000) )
    g_ptr_to_bf900000->m_u.m_e.m_different_regs[core].m_in_coef_r = mode_data->m_d_in_coef_r;
}

//----- (00400660) --------------------------------------------------------
int __cdecl sceSdClearEffectWorkArea(int core, int channel, int effect_mode)
{
  unsigned int aligned_addr; // $s4
  unsigned int effect_size; // $s1
  unsigned int effect_addr; // $s2
  int xferres; // $s0
  int (__cdecl *callback_tmp)(void *); // [sp+18h] [-8h]
  int (__cdecl *handler_tmp)(int, void *); // [sp+1Ch] [-4h]

  effect_mode &= 0xFF;
  if ( effect_mode > SD_EFFECT_MODE_PIPE )
    return -100;
  if ( !effect_mode )
    return 0;
  // Unofficial: restrict channel
  channel &= 1;
  if ( DmaStartStop((channel << 4) | 4, 0, 0) )
    return -210;
  if ( g_VoiceTransIoMode[channel] != 1 )
    return -201;
  if ( QueryIntrContext() )
    return -202;
  aligned_addr = 0;
  effect_size = g_EffectSizes[effect_mode] << 3;
  effect_addr = (GetEEA(core) - (effect_size - 1)) >> 1;
  if ( (effect_size & 0x3F) )
  {
    effect_size = effect_size >> 6 << 6;
    aligned_addr = (GetEEA(core) - (effect_size - 1)) >> 1;
  }
  handler_tmp = g_TransIntrHandlers[channel];
  callback_tmp = g_TransIntrCallbacks[channel];
  g_TransIntrHandlers[channel] = 0;
  g_TransIntrCallbacks[channel] = 0;
  xferres = 0;
  if ( aligned_addr )
  {
    xferres = sceSdVoiceTrans(channel, 0, (u8 *)g_ClearEffectData, (u32 *)(effect_addr << 1), 0x40u);
    if ( xferres >= 0 )
      xferres = sceSdVoiceTransStatus(channel, 1);
    effect_addr = aligned_addr;
  }
  if ( xferres >= 0 )
  {
    int i;

    for ( i = 0; ; i += 1 )
    {
      u32 size; // $v1

      size = ( effect_size <= 0x400 ) ? effect_size : 0x400;
      xferres = sceSdVoiceTrans(channel, 0, (u8 *)g_ClearEffectData, (u32 *)((effect_addr + (i << 9)) << 1), size);
      if ( xferres < 0 )
        break;
      xferres = sceSdVoiceTransStatus(channel, 1);
      if ( xferres < 0 )
        break;
      if ( effect_size <= 0x400 )
      {
        xferres = 0;
        break;
      }
      effect_size -= 0x400;
    }
  }
  g_TransIntrHandlers[channel] = handler_tmp;
  g_TransIntrCallbacks[channel] = callback_tmp;
  return xferres;
}

//----- (00400888) --------------------------------------------------------
static int CleanHandler(int channel)
{
  int core;

  // Unofficial: restrict core
  core = channel & 1;
  g_CleanRegionCur[core] += 1;
  if ( (int)g_CleanRegionCur[core] >= (int)(g_CleanRegionMax[core] - 1) )
    g_CleanHandlers[core] = 0;
  DmaStartStop(
    (core << 4) | 2,
    g_CleanRegionBuffer[core].m_elements[g_CleanRegionCur[core]].m_spuaddr,
    0);
  DmaStartStop(
    (core << 4) | 6,
    (u8 *)g_ClearEffectData,
    g_CleanRegionBuffer[core].m_elements[g_CleanRegionCur[core]].m_size);
  return 0;
}

//----- (0040097C) --------------------------------------------------------
int __cdecl sceSdCleanEffectWorkArea(int core, int channel, int effect_mode)
{
  unsigned int effect_size; // $s1
  unsigned int effect_addr; // $a3
  int xferres; // $s0
  int i; // $t0

  effect_mode &= 0xFF;
  if ( effect_mode > SD_EFFECT_MODE_PIPE )
    return -100;
  if ( !effect_mode )
    return 0;
  // Unofficial: restrict channel
  channel &= 1;
  if ( DmaStartStop((channel << 4) | 4, 0, 0) )
    return -210;
  if ( g_VoiceTransIoMode[channel] != 1 )
    return -201;
  effect_size = g_EffectSizes[effect_mode] << 3;
  effect_addr = GetEEA(core) - (effect_size - 1);
  if ( (effect_size & 0x3F) )
  {
    effect_size = effect_size >> 6 << 6;
    xferres = sceSdVoiceTrans(channel, 8u, (u8 *)g_ClearEffectData, (u32 *)effect_addr, 0x40u);
    if ( xferres < 0 )
      return xferres;
    effect_addr = GetEEA(core) - (effect_size - 1);
  }
  effect_addr += 0x100;
  effect_size -= 0x400;
  for ( i = 0; ; i += 1 )
  {
    g_CleanRegionBuffer[channel].m_elements[i].m_spuaddr = (u32 *)effect_addr;
    g_CleanRegionBuffer[channel].m_elements[i].m_size = ( effect_size <= 0x400 ) ? effect_size : 0x400;
    if ( effect_size <= 0x400 )
      break;
    effect_addr += 0x100;
    effect_size -= 0x400;
  }
  g_CleanRegionMax[channel] = i + 1;
  g_CleanHandlers[channel] = CleanHandler;
  g_CleanRegionCur[channel] = 0;
  xferres = sceSdVoiceTrans(channel, 0, (u8 *)g_ClearEffectData, (u32 *)effect_addr, 0x400u);
  if ( xferres >= 0 )
    xferres = 0;
  return xferres;
}

//----- (00400BBC) --------------------------------------------------------
void __cdecl sceSdGetEffectAttr(int core, sceSdEffectAttr *attr)
{
  attr->core = core;
  attr->mode = g_EffectAttr[core].mode;
  attr->delay = g_EffectAttr[core].delay;
  attr->feedback = g_EffectAttr[core].feedback;
  attr->depth_L = spu2_regs.m_u.m_e.m_different_regs[core].m_evoll;
  attr->depth_R = spu2_regs.m_u.m_e.m_different_regs[core].m_evolr;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00400C2C) --------------------------------------------------------
int __cdecl sceSdSetEffectAttr(int core, sceSdEffectAttr *attr)
{
  int clearram; // $s7
  int channel; // $s6
  int mode; // $s2
  int effects_enabled; // $s5
  int retval; // $s0
  struct mode_data_struct mode_data; // [sp+10h] [-60h] BYREF
  int state; // [sp+5Ch] [-14h] BYREF
  int effect_mode; // [sp+60h] [-10h]

  mode_data.m_mode_flags = 0;
  mode = attr->mode;
  clearram = !!(mode & SD_EFFECT_MODE_CLEAR);
  effect_mode = clearram ? g_EffectAttr[core].mode : 0;
  channel = clearram && !!(mode & 0x200);
  mode &= 0xFF;
  if ( mode > SD_EFFECT_MODE_PIPE )
    return -100;
  g_EffectAttr[core].mode = mode;
  g_EffectAddr[core] = GetEEA(core) - ((g_EffectSizes[mode] << 3) - 1);
  // Unoffical: use memcpy from sysclib
  memcpy(&mode_data, &g_EffectParams[mode], sizeof(mode_data));
  switch ( mode )
  {
    case SD_EFFECT_MODE_ECHO:
      g_EffectAttr[core].feedback = 0x80;
      g_EffectAttr[core].delay = 0x80;
      break;
    case SD_EFFECT_MODE_DELAY:
      g_EffectAttr[core].feedback = 0;
      g_EffectAttr[core].delay = 0x80;
      break;
    default:
      g_EffectAttr[core].feedback = 0;
      g_EffectAttr[core].delay = 0;
      break;
  }
  if ( mode >= SD_EFFECT_MODE_ECHO && mode <= SD_EFFECT_MODE_DELAY )
  {
    int delay; // $a0

    delay = attr->delay;
    g_EffectAttr[core].delay = delay;
    g_EffectAttr[core].feedback = attr->feedback;
    delay += 1;
    delay &= 0xFFFF;
    mode_data.m_d_same_l_dst = (s16)((u16)delay << 6) - (s16)mode_data.m_d_apf1_size;
    delay <<= 5;
    delay &= 0xFFFF;
    mode_data.m_d_same_l_src = delay + mode_data.m_d_same_r_src;
    mode_data.m_d_same_r_dst = delay - mode_data.m_d_apf2_size;
    mode_data.m_d_comb1_l_src = delay + mode_data.m_d_comb1_r_src;
    mode_data.m_d_apf1_l_dst = delay + mode_data.m_d_apf2_l_dst;
    mode_data.m_d_apf1_r_dst = delay + mode_data.m_d_apf2_r_dst;
    mode_data.m_d_wall_vol = 0x102 * g_EffectAttr[core].feedback;
  }
  effects_enabled = (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr >> 7) & 1;
  if ( effects_enabled )
  {
    CpuSuspendIntr(&state);
    spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr &= ~SD_ENABLE_EFFECTS;
    CpuResumeIntr(state);
  }
  retval = ( effects_enabled && clearram ) ? sceSdClearEffectWorkArea(core, channel, effect_mode) : 0;
  if ( retval >= 0 )
  {
    spu2_regs.m_u.m_e.m_different_regs[core].m_evoll = attr->depth_L;
    spu2_regs.m_u.m_e.m_different_regs[core].m_evolr = attr->depth_R;
    SetEffectData(core, &mode_data);
    spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_esa.m_pair[0] = g_EffectAddr[core] >> 17;
    spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_esa.m_pair[1] = g_EffectAddr[core] >> 1;
    retval = clearram ? sceSdClearEffectWorkArea(core, channel, mode) : 0;
  }
  if ( effects_enabled )
  {
    CpuSuspendIntr(&state);
    spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr |= SD_ENABLE_EFFECTS;
    CpuResumeIntr(state);
  }
  return retval;
}
// 400FA4: conditional instruction was optimized away because $s5.4==1
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401100) --------------------------------------------------------
static int __fastcall GetEEA(int core)
{
  return (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_eea << 17) | 0x1FFFF;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401128) --------------------------------------------------------
int __cdecl sceSdSetEffectMode(int core, sceSdEffectAttr *param)
{
  int clearram; // $s6
  int channel; // $s5
  unsigned int mode; // $s1
  int effects_enabled; // $s4
  struct mode_data_struct mode_data; // [sp+10h] [-50h] BYREF
  int state; // [sp+5Ch] [-4h] BYREF

  mode_data.m_mode_flags = 0;
  mode = param->mode;
  clearram = !!(mode & 0x100);
  channel = clearram && !!(mode & 0x200);
  mode &= 0xFF;
  if ( mode > SD_EFFECT_MODE_PIPE )
    return -100;
  g_EffectAttr[core].mode = mode;
  g_EffectAttr[core].delay = 0;
  g_EffectAttr[core].feedback = 0;
  g_EffectAddr[core] = GetEEA(core) - ((g_EffectSizes[mode] << 3) - 1);
  // Unoffical: don't use inlined memcpy
  memcpy(&mode_data, &g_EffectParams[mode], sizeof(mode_data));
  effects_enabled = (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr >> 7) & 1;
  if ( effects_enabled )
  {
    CpuSuspendIntr(&state);
    spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr &= ~SD_ENABLE_EFFECTS;
    CpuResumeIntr(state);
  }
  spu2_regs.m_u.m_e.m_different_regs[core].m_evoll = 0;
  spu2_regs.m_u.m_e.m_different_regs[core].m_evolr = 0;
  SetEffectData(core, &mode_data);
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_esa.m_pair[0] = g_EffectAddr[core] >> 17;
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_esa.m_pair[1] = g_EffectAddr[core] >> 1;
  if ( effects_enabled )
  {
    CpuSuspendIntr(&state);
    spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr |= SD_ENABLE_EFFECTS;
    CpuResumeIntr(state);
  }
  return clearram ? sceSdCleanEffectWorkArea(core, channel, mode) : 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;
// 401128: using guessed type struct mode_data_struct mode_data;

//----- (00401380) --------------------------------------------------------
int __cdecl sceSdSetEffectModeParams(int core, sceSdEffectAttr *attr)
{
  int mode; // $a0
  struct mode_data_struct mode_data; // [sp+10h] [-48h] BYREF

  mode = attr->mode;
  mode &= 0xFF;
  if ( mode > SD_EFFECT_MODE_PIPE )
    return -100;
  if ( g_EffectAttr[core].mode != mode )
    return -100;
  if ( mode >= SD_EFFECT_MODE_ECHO && mode <= SD_EFFECT_MODE_DELAY )
  {
    int delay; // $a0

    // Unoffical: don't use inlined memcpy
    memcpy(&mode_data, &g_EffectParams[mode], sizeof(mode_data));
    mode_data.m_mode_flags = 0xC011C80;
    delay = attr->delay;
    g_EffectAttr[core].delay = delay;
    g_EffectAttr[core].feedback = attr->feedback;
    delay += 1;
    delay &= 0xFFFF;
    mode_data.m_d_same_l_dst = (s16)(((u16)delay << 6) - (s16)mode_data.m_d_apf1_size);
    delay <<= 5;
    delay &= 0xFFFF;
    mode_data.m_d_same_l_src = delay + mode_data.m_d_same_r_src;
    mode_data.m_d_same_r_dst = delay - mode_data.m_d_apf2_size;
    mode_data.m_d_comb1_l_src = delay + mode_data.m_d_comb1_r_src;
    mode_data.m_d_apf1_l_dst = delay + mode_data.m_d_apf2_l_dst;
    mode_data.m_d_apf1_r_dst = delay + mode_data.m_d_apf2_r_dst;
    mode_data.m_d_wall_vol = 0x102 * g_EffectAttr[core].feedback;
    SetEffectData(core, &mode_data);
  }
  spu2_regs.m_u.m_e.m_different_regs[core].m_evoll = attr->depth_L;
  spu2_regs.m_u.m_e.m_different_regs[core].m_evolr = attr->depth_R;
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401550) --------------------------------------------------------
static void InitSpu2_Inner()
{
  int state; // [sp+10h] [-8h] BYREF
  USE_IOP_MMIO_HWPORT();

  iop_mmio_hwport->ssbus2.ind_4_address = 0xBF900000;
  iop_mmio_hwport->ssbus2.ind_9_address = 0xBF900800;
  CpuSuspendIntr(&state);
  iop_mmio_hwport->dmac1.dpcr1 |= 0x80000;
  iop_mmio_hwport->dmac2.dpcr2 |= 8;
  CpuResumeIntr(state);
  iop_mmio_hwport->ssbus1.ind_4_delay = 0x200B31E1;
  iop_mmio_hwport->ssbus2.ind_9_delay = 0x200B31E1;
}

//----- (004015E8) --------------------------------------------------------
static void InitSpu2()
{
  InitSpu2_Inner();
  spu2_regs.m_u.m_e.m_spdif_mode = 0x0900;
  spu2_regs.m_u.m_e.m_spdif_media = 0x200;
  spu2_regs.m_u.m_e.m_unknown7ca = 8;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401638) --------------------------------------------------------
static void InitCoreVolume(int flag)
{
  int i;

  spu2_regs.m_u.m_e.m_spdif_out = 0xC032;
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
    spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_attr = (flag ? SD_ENABLE_EFFECTS : 0) | (i ? SD_ENABLE_EX_INPUT : 0) | SD_MUTE|SD_SPU2_ON;
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_vmixl.m_pair[0] = 0xFFFF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_vmixl.m_pair[1] = 0xFF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_vmixel.m_pair[0] = 0xFFFF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_vmixel.m_pair[1] = 0x00FF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_vmixr.m_pair[0] = 0xFFFF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_vmixr.m_pair[1] = 0x00FF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_vmixer.m_pair[0] = 0xFFFF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_vmixer.m_pair[1] = 0x00FF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_mmix = 0xFF0 + (i * 0xC);
  }
  if ( !flag )
  {
    // Unofficial: rerolled
    for ( i = 0; i < 2; i += 1 )
    {
      spu2_regs.m_u.m_e.m_different_regs[i].m_mvoll = 0;
      spu2_regs.m_u.m_e.m_different_regs[i].m_mvolr = 0;
      spu2_regs.m_u.m_e.m_different_regs[i].m_evoll = 0;
      spu2_regs.m_u.m_e.m_different_regs[i].m_evolr = 0;
    }
    // Unofficial: rerolled
    for ( i = 0; i < 2; i += 1 )
      spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_eea = 14 + i;
  }
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_e.m_different_regs[i].m_avoll = i ? 0x7FFF : 0;
    spu2_regs.m_u.m_e.m_different_regs[i].m_avolr = i ? 0x7FFF : 0;
    spu2_regs.m_u.m_e.m_different_regs[i].m_bvoll = 0;
    spu2_regs.m_u.m_e.m_different_regs[i].m_bvolr = 0;
  }
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00401890) --------------------------------------------------------
int __cdecl sceSdVoiceTrans(s16 chan, u16 mode, u8 *iopaddr, u32 *spuaddr, u32 size)
{
  int core; // $s2

  core = chan & 1;
  if ( !size )
    return -100;
  if ( DmaStartStop((core << 4) | 4, 0, 0) )
    return -210;
  if ( g_VoiceTransIoMode[core] != 1 )
    return -201;
  switch ( mode & 3 )
  {
    case SD_TRANS_READ:
      g_TransIntrData[core].m_mode = core | 0x900;
      g_BlockHandlerIntrData[core].m_cb = 0;
      g_BlockHandlerIntrData[core].m_userdata = 0;
      g_VoiceTransStatus[core] = 0;
      DmaStartStop((core << 4) | 2, spuaddr, 0);
      if ( QueryIntrContext() )
        iClearEventFlag(g_VoiceTransCompleteEf[core], ~1);
      else
        ClearEventFlag(g_VoiceTransCompleteEf[core], ~1);
      g_VoiceTransIoMode[core] = 0;
      return DmaStartStop((core << 4) | 5, iopaddr, (size >> 6 << 6) + ((size & 0x3F) ? 0x40 : 0));
    case SD_TRANS_WRITE:
      g_TransIntrData[core].m_mode = core | 0x500;
      g_BlockHandlerIntrData[core].m_cb = 0;
      g_BlockHandlerIntrData[core].m_userdata = 0;
      DmaStartStop((core << 4) | 2, spuaddr, 0);
      if ( QueryIntrContext() )
        iClearEventFlag(g_VoiceTransCompleteEf[core], ~1);
      else
        ClearEventFlag(g_VoiceTransCompleteEf[core], ~1);
      g_VoiceTransIoMode[core] = 0;
      if ( !(mode & SD_TRANS_MODE_IO) )
      {
        g_VoiceTransStatus[core] = 0;
        return DmaStartStop((core << 4) | 6, iopaddr, (size >> 6 << 6) + ((size & 0x3F) ? 0x40 : 0));
      }
      g_VoiceTransStatus[core] = 1;
      return VoiceTrans_Write_IOMode((u16 *)iopaddr, (size >> 6 << 6) + ((size & 0x3F) ? 0x40 : 0), core);
    default:
      return -100;
  }
}

//----- (00401B10) --------------------------------------------------------
u32 __cdecl sceSdVoiceTransStatus(s16 channel, s16 flag)
{
  u32 efres; // [sp+10h] [-8h] BYREF
  int core;

  core = channel & 1;
  if ( g_VoiceTransStatus[core] == 1 || g_VoiceTransIoMode[core] == 1 )
    return 1;
  switch ( flag )
  {
    case 0:
      if ( g_VoiceTransCompleteBool[core] )
      {
        g_VoiceTransCompleteBool[core] = 0;
        g_VoiceTransIoMode[core] = 1;
      }
      break;
    case 1:
      if ( QueryIntrContext() )
        return -202;
      WaitEventFlag(g_VoiceTransCompleteEf[core], 1, 0, &efres);
      g_VoiceTransCompleteBool[core] = 0;
      g_VoiceTransIoMode[core] = 1;
      break;
    default:
      break;
  }
  return g_VoiceTransIoMode[core];
}
// 401B10: using guessed type u32 efres[2];

//----- (00401C08) --------------------------------------------------------
int __cdecl sceSdStopTrans(int channel)
{
  int core; // $a0

  core = channel & 1;
  g_TransIntrData[core].m_mode = core;
  g_BlockHandlerIntrData[core].m_cb = 0;
  g_BlockHandlerIntrData[core].m_userdata = 0;
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
  switch (transfer_dir)
  {
    case SD_TRANS_READ:
      if ( !size )
        return -100;
      if ( started )
        return -210;
      g_TransIntrData[core].m_mode = core | 0xA00;
      g_BlockHandlerIntrData[core].m_cb = 0;
      g_BlockHandlerIntrData[core].m_userdata = 0;
      if ( (mode & 0x80) )
      {
        if ( !vararg_elm1 )
        {
          g_TransIntrData[core].m_mode = core;
          return -100;
        }
        g_BlockHandlerIntrData[core].m_cb = (void *)vararg_elm1;
        g_BlockHandlerIntrData[core].m_userdata = (void *)vararg_elm2;
        g_TransIntrData[core].m_mode |= 0x8000u;
      }
      else if ( (mode & SD_TRANS_LOOP) )
      {
        size >>= 1;
        g_TransIntrData[core].m_mode |= 0x1000u;
      }
      retres_1 = BlockTransRead(iopaddr, size, core, mode);
      break;
    case SD_TRANS_STOP:
      g_BlockHandlerIntrData[core].m_cb = 0;
      g_BlockHandlerIntrData[core].m_userdata = 0;
      g_TransIntrData[core].m_mode = core;
      return DmaStartStop((core << 4) | 0xA, 0, 0);
    case SD_TRANS_WRITE:
    case SD_TRANS_WRITE_FROM:
      if ( !size )
        return -100;
      if ( started )
        return -210;
      g_TransIntrData[core].m_mode = core | 0x600;
      g_BlockHandlerIntrData[core].m_cb = 0;
      g_BlockHandlerIntrData[core].m_userdata = 0;
      if ( (mode & 0x80) )
      {
        if ( !vararg_elm2 )
        {
          g_TransIntrData[core].m_mode = core;
          return -100;
        }
        g_BlockHandlerIntrData[core].m_cb = (void *)vararg_elm2;
        g_BlockHandlerIntrData[core].m_userdata = (void *)vararg_elm3;
        g_TransIntrData[core].m_mode |= 0x8000u;
      }
      else if ( (mode & SD_TRANS_LOOP) )
      {
        size >>= 1;
        g_TransIntrData[core].m_mode |= 0x1000u;
      }
      retres_1 = BlockTransWriteFrom(iopaddr, size, chan & 0xFF, mode, ( transfer_dir == SD_TRANS_WRITE_FROM ) ? (void *)vararg_elm1 : 0);
      break;
    default:
      return -100;
  }
  if ( retres_1 < 0 )
  {
    g_BlockHandlerIntrData[core].m_cb = 0;
    g_BlockHandlerIntrData[core].m_userdata = 0;
    g_TransIntrData[core].m_mode = core;
  }
  return retres_1;
}

//----- (00402024) --------------------------------------------------------
u32 __cdecl sceSdBlockTransStatus(s16 channel, s16 flag)
{
  int core;
  // Unofficial: inline thunk
  USE_IOP_MMIO_HWPORT();

  (void)flag;
  core = channel & 1;
  return (g_BlockTransBuff[core] << 24) | (((spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_admas & 7) ? (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->madr : 0) & ~0xFF000000);
}

//----- (0040206C) --------------------------------------------------------
static int InitSpdif()
{
  int i; // $s0

  spu2_regs.m_u.m_e.m_spdif_out = 0;
  libsd_do_busyloop_1(2);
  spu2_regs.m_u.m_e.m_spdif_out = 0x8000;
  libsd_do_busyloop_1(1);
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_e.m_different_regs[i].m_mvoll = 0;
    spu2_regs.m_u.m_e.m_different_regs[i].m_mvolr = 0;
  }
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_admas = 0;
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_attr = 0;
  libsd_do_busyloop_1(1);
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_attr = 0x8000;
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_e.m_different_regs[i].m_mvoll = 0;
    spu2_regs.m_u.m_e.m_different_regs[i].m_mvolr = 0;
  }
  for ( i = 0; (spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_statx & 0x7FF) && (spu2_regs.m_u.m_m.m_core_regs[1].m_cregs.m_statx & 0x7FF) && i < 0xF00; i += 1 )
    libsd_do_busyloop_1(1);
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_koff.m_pair[0] = 0xFFFF;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_koff.m_pair[1] = 0xFF;
  }
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_pmon.m_pair[0] = 0;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_pmon.m_pair[1] = 0;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_non.m_pair[0] = 0;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_non.m_pair[1] = 0;
  }
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (0040225C) --------------------------------------------------------
static void SetDmaWrite(int chan)
{
  vu32 *dmachanptr; // $a0
  USE_IOP_MMIO_HWPORT();

  dmachanptr = chan ? &iop_mmio_hwport->ssbus2.ind_9_delay : &iop_mmio_hwport->ssbus1.ind_4_delay;
  *dmachanptr &= ~0xF000000;
}

//----- (00402284) --------------------------------------------------------
static void SetDmaRead(int chan)
{
  vu32 *dmachanptr; // $a0
  USE_IOP_MMIO_HWPORT();

  dmachanptr = chan ? &iop_mmio_hwport->ssbus2.ind_9_delay : &iop_mmio_hwport->ssbus1.ind_4_delay;
  *dmachanptr = (*dmachanptr & ~0xF000000) | 0x2000000;
}

//----- (004022B4) --------------------------------------------------------
static void libsd_do_busyloop_2()
{
  int i; // [sp+0h] [-8h]
  int loopmul; // [sp+4h] [-4h]

  loopmul = 13;
  for ( i = 0; i < 120; i += 1 )
    loopmul *= 13;
}

//----- (00402310) --------------------------------------------------------
static void libsd_do_busyloop_1(int a1)
{
  int i; // $s0

  for ( i = 0; i < a1; i += 1 )
    libsd_do_busyloop_2();
}

//----- (00402358) --------------------------------------------------------
static u32 __fastcall DmaStartStop(int mainarg, void *vararg2, unsigned int vararg3)
{
  int core; // $s1
  unsigned int tsa_tmp; // $t1
  unsigned int vararg3_cal; // $a0
  u32 blocktransbufitem; // $s7
  int dma_addr; // $s5
  int i; // $a0
  int hichk; // $s0
  int state; // [sp+14h] [-4h] BYREF
  USE_IOP_MMIO_HWPORT();

  // Unofficial: restrict core
  core = (mainarg >> 4) & 1;
  switch ( mainarg & 0xF )
  {
    case 2:
      tsa_tmp = ((u16)(uiptr)vararg2 >> 1) & ~7u;
      spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_tsa.m_pair[1] = tsa_tmp;
      spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_tsa.m_pair[0] = (tsa_tmp >> 16) & 0xFFFF;
      return 0;
    case 4:
      if ( (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr & SD_DMA_IN_PROCESS) )
        return -1;
      if ( ((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr & SD_DMA_START) )
        return -1;
      if ( spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_admas )
        return -1;
      return 0;
    case 5:
      CpuSuspendIntr(&state);
      spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr |= SD_DMA_READ;
      CpuResumeIntr(state);
      SetDmaRead(core);
      vararg3_cal = (vararg3 >> 6) + (!!(vararg3 & 0x3F));
      (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->madr = (uiptr)vararg2;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
      ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[0] = 16;
#pragma GCC diagnostic pop
      ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[1] = vararg3_cal;
      (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr = SD_DMA_START|SD_DMA_CS;
      return vararg3_cal << 6;
    case 6:
      CpuSuspendIntr(&state);
      spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr = (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr & ~SD_CORE_DMA) | SD_DMA_WRITE;
      CpuResumeIntr(state);
      SetDmaWrite(core);
      vararg3_cal = (vararg3 >> 6) + (!!(vararg3 & 0x3F));
      (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->madr = (uiptr)vararg2;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
      ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[0] = 16;
#pragma GCC diagnostic pop
      ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[1] = vararg3_cal;
      (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr = SD_DMA_START|SD_DMA_CS|SD_DMA_DIR_IOP2SPU;
      return vararg3_cal << 6;
    case 0xA:
      blocktransbufitem = 0;
      dma_addr = 0;
      if ( ((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr & SD_DMA_START) )
      {
        blocktransbufitem = g_BlockTransBuff[core];
        dma_addr = (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->madr;
        (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr &= ~SD_DMA_START;
        if ( (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr & SD_CORE_DMA) )
        {
          for ( i = 0; !(spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_statx & 0x80) && i < 0x1000000; i += 1 )
          {
          }
        }
      }
      if ( (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr & SD_CORE_DMA) )
      {
        CpuSuspendIntr(&state);
        spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr &= ~SD_CORE_DMA;
        CpuResumeIntr(state);
        for ( i = 0; (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr & SD_CORE_DMA) && i < 0xF00; i += 1 )
        {
        }
      }
      hichk = 0;
      if ( (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_admas & 7) )
      {
        hichk = 1;
        spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_admas = 0;
      }
      if ( QueryIntrContext() )
        iSetEventFlag(g_VoiceTransCompleteEf[core], 1);
      else
        SetEventFlag(g_VoiceTransCompleteEf[core], 1);
      g_VoiceTransCompleteBool[core] = 0;
      g_VoiceTransIoMode[core] = 1;
      g_CleanHandlers[core] = 0;
      return ( dma_addr && hichk ) ? ((dma_addr & ~0xFF000000) | (blocktransbufitem << 24)) : 0;
    default:
      return 0;
  }
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (0040280C) --------------------------------------------------------
static unsigned int __fastcall VoiceTrans_Write_IOMode(const u16 *iopaddr, unsigned int size, int chan)
{
  unsigned int size_tmp; // $s3
  int count; // $s2
  int i; // $v1
  int state; // [sp+14h] [-4h] BYREF
  int core;

  // Unofficial: restrict core
  core = chan & 1;
  for ( size_tmp = size; size_tmp; size_tmp -= count )
  {
    count = ( size_tmp <= 0x40 ) ? size_tmp : 0x40;
    for ( i = 0; i < (count / 2); i += 1 )
      spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_xferdata = iopaddr[i];
    CpuSuspendIntr(&state);
    spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr = (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr & ~SD_CORE_DMA) | SD_DMA_IO;
    CpuResumeIntr(state);
    for ( i = 0; (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_statx & SD_IO_IN_PROCESS) && i < 0xF00; i += 1 )
      libsd_do_busyloop_1(1);
  }
  CpuSuspendIntr(&state);
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr &= ~SD_CORE_DMA;
  CpuResumeIntr(state);
  g_VoiceTransIoMode[core] = 1;
  // Unofficial: return size
  return size;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (004029A8) --------------------------------------------------------
static void do_finish_block_clean_xfer(int core)
{
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr &= ~SD_CORE_DMA;
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_admas = 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (004029EC) --------------------------------------------------------
static int __fastcall TransInterrupt(IntrData *intr)
{
  int no_flush_cache; // $s5
  u32 mode; // $v1
  int core; // $s1
  int i; // $v1
  void *dma_addr; // [sp+14h] [-Ch] BYREF
  int dma_size; // [sp+18h] [-8h] BYREF
  USE_IOP_MMIO_HWPORT();

  mode = intr->m_mode;
  switch ( mode & 0xC00 )
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
  core = mode & 1;
  switch ( mode & 0x300 )
  {
    case 0x100:
      for ( i = 0; !(spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_statx & 0x80) && i < 0x1000000; i += 1 )
      {
      }
      spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr &= ~SD_CORE_DMA;
      for ( i = 0; (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr & SD_CORE_DMA) && i < 0xF00; i += 1 )
      {
      }
      if ( !no_flush_cache )
        FlushDcache();
      if ( g_CleanHandlers[core] )
        g_CleanHandlers[core](core);
      else
      {
        iSetEventFlag(g_VoiceTransCompleteEf[core], 1);
        if ( g_TransIntrHandlers[core] )
        {
          g_VoiceTransIoMode[core] = 1;
          g_TransIntrHandlers[core](core, intr->m_data);
        }
        else if ( !g_TransIntrCallbacks[core] )
          g_VoiceTransCompleteBool[core] = 1;
        else
        {
          g_VoiceTransIoMode[core] = 1;
          g_TransIntrCallbacks[core](0);
        }
      }
      break;
    case 0x200:
      if ( (mode & 0x8000) )
      {
        if ( g_BlockHandlerIntrData[core].m_cb )
        {
          g_BlockHandlerIntrData[core].m_cb(
            core,
            g_BlockHandlerIntrData[core].m_userdata,
            &dma_addr,
            &dma_size);
          if ( dma_size > 0 )
          {
            ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[1] = (dma_size >> 6)
                                                                    + (dma_size - (dma_size >> 6 << 6) > 0);
            (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->madr = (uiptr)dma_addr;
            (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr = no_flush_cache | SD_DMA_START|SD_DMA_CS;
          }
          else
          {
            do_finish_block_clean_xfer(core);
            g_BlockHandlerIntrData[core].m_cb = 0;
            g_BlockHandlerIntrData[core].m_userdata = 0;
          }
        }
        else
          do_finish_block_clean_xfer(core);
        if ( !no_flush_cache )
          FlushDcache();
      }
      else
      {
        if ( (mode & 0x1000) )
        {
          g_BlockTransBuff[core] = 1 - g_BlockTransBuff[core];
          ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[1] = (int)g_BlockTransSize[core] / 0x40
                                                                  + ((int)g_BlockTransSize[core] % 0x40 > 0);
          (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->madr = (uiptr)(g_BlockTransAddr[core] + g_BlockTransBuff[core] * g_BlockTransSize[core]);
          (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr = no_flush_cache | SD_DMA_START|SD_DMA_CS;
        }
        else
          do_finish_block_clean_xfer(core);
        if ( !no_flush_cache )
          FlushDcache();
        if ( g_TransIntrHandlers[core] )
          g_TransIntrHandlers[core](core, intr->m_data);
        else if ( g_TransIntrCallbacks[core] )
          g_TransIntrCallbacks[core](0);
      }
      break;
    default:
      break;
  }
  return 1;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00402F4C) --------------------------------------------------------
static unsigned int __fastcall BlockTransWriteFrom(u8 *iopaddr, unsigned int size, char chan, char mode, u8 *startaddr)
{
  int core; // $s2
  u8 *startaddr_tmp; // $s3
  signed int size_align; // $s1
  int size_align_r6; // $v1
  int state; // [sp+14h] [-4h] BYREF
  USE_IOP_MMIO_HWPORT();

  core = chan & 1;
  startaddr_tmp = startaddr;
  g_BlockTransAddr[core] = iopaddr;
  g_BlockTransBuff[core] = 0;
  g_BlockTransSize[core] = size;
  if ( startaddr )
  {
    size_align = size - (startaddr - iopaddr);
    if ( (u32)(startaddr - iopaddr) >= size )
    {
      unsigned int other_align; // $v1

      other_align = startaddr - iopaddr - size;
      if ( !(mode & SD_TRANS_LOOP) || other_align >= size )
        return -100;
      g_BlockTransBuff[core] += 1;
      size_align = size - other_align;
    }
    if ( size_align % 0x400 > 0 )
    {
      size_align = (size_align / 0x400 + 1) << 10;
      startaddr_tmp = iopaddr + g_BlockTransBuff[core] * size + size - size_align;
    }
  }
  else
  {
    startaddr_tmp = iopaddr;
    size_align = size;
  }
  CpuSuspendIntr(&state);
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr &= ~SD_CORE_DMA;
  CpuResumeIntr(state);
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_tsa.m_pair[0] = 0;
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_tsa.m_pair[1] = 0;
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_admas = 1 << core;
  SetDmaWrite(core);
  (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->madr = (uiptr)startaddr_tmp;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
  ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[0] = 16;
#pragma GCC diagnostic pop
  size_align_r6 = (( size_align < 0 ) ? (size_align + 63) : size_align) >> 6;
  ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[1] = size_align_r6 + (size_align - (size_align_r6 << 6) > 0);
  (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr = SD_DMA_START|SD_DMA_CS|SD_DMA_DIR_IOP2SPU;
  return size;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00403174) --------------------------------------------------------
static u32 __fastcall BlockTransRead(u8 *iopaddr, u32 size, char chan, u16 mode)
{
  int core; // $s3
  int state; // [sp+14h] [-4h] BYREF
  USE_IOP_MMIO_HWPORT();

  core = chan & 1;
  g_BlockTransAddr[core] = iopaddr;
  g_BlockTransBuff[core] = 0;
  g_BlockTransSize[core] = size;
  CpuSuspendIntr(&state);
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr &= ~SD_CORE_DMA;
  CpuResumeIntr(state);
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_tsa.m_pair[0] = 0;
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_tsa.m_pair[1] = ((mode & ~0xF0FF) << 1) + 0x400;
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_unk1ae = (mode & ~0xFFF) >> 11;
  libsd_do_busyloop_1(3);
  spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_admas = 4;
  SetDmaRead(core);
  (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->madr = (uiptr)iopaddr;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
  ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[0] = 16;
#pragma GCC diagnostic pop
  ((vu16 *)&((core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->bcr))[1] = (int)g_BlockTransSize[core] / 0x40
                                                              + ((int)g_BlockTransSize[core] % 0x40 > 0);
  (core ? &iop_mmio_hwport->dmac2.newch[0] : &iop_mmio_hwport->dmac1.oldch[4])->chcr = SD_DMA_START|SD_DMA_CS;
  return size;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00403340) --------------------------------------------------------
static int __fastcall SifDmaBatch(void *ee_addr, void *iop_addr, int size)
{
  int dmat; // $s2
  int i; // $s1
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
  for ( i = 0, dma_status = 0; i >= 0 && dma_status >= 0; i += 1 )
  {
    CpuSuspendIntr(&state);
    dma_status = sceSifDmaStat(dmat);
    CpuResumeIntr(state);
  }
  return ( i < 0 ) ? -1 : 0;
}

//----- (004033FC) --------------------------------------------------------
int __cdecl sceSdProcBatch(sceSdBatch *batch, u32 *rets, u32 num)
{
  u32 cnt; // $s4

  for ( cnt = 0; cnt < num; cnt += 1 )
  {
    u32 Param; // $s1

    Param = 0;
    switch ( batch[cnt].func )
    {
      case SD_BATCH_SETPARAM:
        sceSdSetParam(batch[cnt].entry, batch[cnt].value);
        break;
      case SD_BATCH_SETSWITCH:
        sceSdSetSwitch(batch[cnt].entry, batch[cnt].value);
        break;
      case SD_BATCH_SETADDR:
        sceSdSetAddr(batch[cnt].entry, batch[cnt].value);
        break;
      case SD_BATCH_SETCORE:
        sceSdSetCoreAttr(batch[cnt].entry, batch[cnt].value);
        break;
      case SD_BATCH_WRITEIOP:
        *(u32 *)batch[cnt].value = batch[cnt].entry;
        break;
      case SD_BATCH_WRITEEE:
        g_BatchData = batch[cnt].entry;
        Param = SifDmaBatch((void *)batch[cnt].value, &g_BatchData, sizeof(g_BatchData));
        break;
      case SD_BATCH_EERETURN:
        Param = SifDmaBatch((void *)batch[cnt].value, rets, batch[cnt].entry);
        break;
      case SD_BATCH_GETPARAM|SD_BATCH_SETPARAM:
        Param = sceSdGetParam(batch[cnt].entry);
        break;
      case SD_BATCH_GETSWITCH:
        Param = sceSdGetSwitch(batch[cnt].entry);
        break;
      case SD_BATCH_GETADDR:
        Param = sceSdGetAddr(batch[cnt].entry);
        break;
      case SD_BATCH_GETCORE:
        Param = sceSdGetCoreAttr(batch[cnt].entry);
        break;
      default:
        return ~cnt;
    }
    if ( rets )
      rets[cnt] = Param;
  }
  return cnt;
}

//----- (004035E8) --------------------------------------------------------
int __cdecl sceSdProcBatchEx(sceSdBatch *batch, u32 *rets, u32 num, u32 voice)
{
  u32 cnt; // $s7
  int loop; // $s3
  int i; // $s0

  loop = 0;
  for ( cnt = 0; cnt < num; cnt += 1 )
  {
    u32 Param; // $s4

    Param = 0;
    switch ( batch[cnt].func )
    {
      case SD_BATCH_SETPARAM:
        if ( (batch[cnt].entry & 0x3E) == 0x3E )
        {
          for ( i = 0; i < 24; i += 1 )
          {
            if ( ((1 << i) & voice) )
            {
              loop += 1;
              sceSdSetParam((batch[cnt].entry & ~0x3E) | (i << 1), batch[cnt].value);
            }
          }
          --loop;
        }
        else
          sceSdSetParam(batch[cnt].entry, batch[cnt].value);
        break;
      case SD_BATCH_SETSWITCH:
        sceSdSetSwitch(batch[cnt].entry, batch[cnt].value);
        break;
      case SD_BATCH_SETADDR:
        if ( (batch[cnt].entry & 0x7E) == 0x7E )
        {
          for ( i = 0; i < 24; i += 1 )
          {
            if ( ((1 << i) & voice) )
            {
              loop += 1;
              sceSdSetAddr((batch[cnt].entry & ~0x3E) | (i << 1), batch[cnt].value);
            }
          }
          --loop;
        }
        else
          sceSdSetAddr(batch[cnt].entry, batch[cnt].value);
        break;
      case SD_BATCH_SETCORE:
        sceSdSetCoreAttr(batch[cnt].entry, batch[cnt].value);
        break;
      case SD_BATCH_WRITEIOP:
        *(u32 *)batch[cnt].value = batch[cnt].entry;
        break;
      case SD_BATCH_WRITEEE:
        g_BatchData = batch[cnt].entry;
        Param = SifDmaBatch((void *)batch[cnt].value, &g_BatchData, sizeof(g_BatchData));
        break;
      case SD_BATCH_EERETURN:
        Param = SifDmaBatch((void *)batch[cnt].value, rets, batch[cnt].entry);
        break;
      case SD_BATCH_GETPARAM|SD_BATCH_SETPARAM:
        if ( (batch[cnt].entry & 0x3E) == 0x3E )
        {
          for ( i = 0; i < 24; i += 1 )
          {
            if ( ((1 << i) & voice) )
              Param = sceSdGetParam((batch[cnt].entry & ~0x3E) | (i << 1));
            if ( rets )
              rets[loop] = Param;
            loop += 1;
          }
          --loop;
        }
        else
          Param = sceSdGetParam(batch[cnt].entry);
        break;
      case SD_BATCH_GETSWITCH:
        Param = sceSdGetSwitch(batch[cnt].entry);
        break;
      case SD_BATCH_GETADDR:
        if ( (batch[cnt].entry & 0x7E) == 0x7E )
        {
          for ( i = 0; i < 24; i += 1 )
          {
            if ( ((1 << i) & voice) )
            {
              Param = sceSdGetAddr((batch[cnt].entry & ~0x3E) | (i << 1));
              if ( rets )
                rets[loop] = Param;
              loop += 1;
            }
          }
          --loop;
        }
        else
          Param = sceSdGetAddr(batch[cnt].entry);
        break;
      case SD_BATCH_GETCORE:
        Param = sceSdGetCoreAttr(batch[cnt].entry);
        break;
      default:
        return ~cnt;
    }
    if ( rets )
      rets[loop] = Param;
    loop += 1;
  }
  return loop;
}

//----- (004039A0) --------------------------------------------------------
void __cdecl sceSdSetParam(u16 entry, u16 value)
{
  g_ParamRegList[((entry >> 8) & 0xFF)][((entry & 0x3E) << 2) + (((entry & 1) * (0x400 - 984 * (!!(entry & 0x80)))) >> 1)] = value;
}

//----- (004039FC) --------------------------------------------------------
u16 __cdecl sceSdGetParam(u16 entry)
{
  return g_ParamRegList[((entry >> 8) & 0xFF)][((entry & 0x3E) << 2) + (((entry & 1) * (0x400 - 984 * (!!(entry & 0x80)))) >> 1)];
}

//----- (00403A5C) --------------------------------------------------------
void __cdecl sceSdSetSwitch(u16 entry, u32 value)
{
  vu16 *regptr; // $v0

  regptr = &g_ParamRegList[((entry >> 8) & 0xFF)][(entry & 1) << 9];
  regptr[0] = value;
  regptr[1] = (value >> 16) & 0xFF;
}

//----- (00403A94) --------------------------------------------------------
u32 __cdecl sceSdGetSwitch(u16 entry)
{
  const vu16 *regptr; // $a0

  regptr = &g_ParamRegList[((entry >> 8) & 0xFF)][(entry & 1) << 9];
  return regptr[0] | (regptr[1] << 16);
}

//----- (00403ACC) --------------------------------------------------------
void __cdecl sceSdSetAddr(u16 entry, u32 value)
{
  vu16 *reg1; // $a1

  reg1 = &g_ParamRegList[((entry >> 8) & 0xFF)][((entry & 1) << 9) + 3 * (entry & 0x3E)];
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
  reg1 = &g_ParamRegList[((entry >> 8) & 0xFF)][((entry & 1) << 9) + 3 * (entry & 0x3E)];
  regmask = entry & 0xFF00;
  rethi = reg1[0] << 17;
  if ( regmask != 0x1D00 )
  {
    retlo = reg1[1] << 1;
    if ( regmask == 0x2100 || regmask == 0x2200 )
    {
      rethi = reg1[0] << 17;
      retlo = reg1[1] << 1;
    }
  }
  return rethi | retlo;
}

//----- (00403BD0) --------------------------------------------------------
u16 __cdecl sceSdNote2Pitch(u16 center_note, u16 center_fine, u16 note, s16 fine)
{
  int _fine; // $a3
  int val3; // $v0
  int _note; // $a1
  int _fine2; // $a2
  int offset2; // $a3
  int val2; // $v1
  s16 val; // $t0
  s16 offset1; // $a0
  int retval; // $a1

  _fine = fine + center_fine;
  _fine2 = _fine / 0x80;
  val3 = (note + _fine2 - center_note);
  _note = val3 & 0xFFFF;
  offset2 = _fine % 0x80;
  val2 = ((_note / 6) >> 1) - ((unsigned int)val3 << 16 >> 31);
  offset1 = _note - 12 * val2;
  val = val2 - 2;
  if ( (offset1 < 0) || (!offset1 && offset2 < 0) )
  {
    offset1 += 12;
    val -= 1;
  }
  if ( offset2 < 0 )
  {
    offset2 += (_fine2 + 1) << 7;
    offset1 -= 1;
    offset1 += _fine2;
  }
  retval = (g_NotePitchTable[offset1] * g_NotePitchTable[offset2 + 12]) >> 16;
  return ( val < 0 ) ? (unsigned int)(retval + (1 << (-val - 1))) >> -val : (unsigned int)retval;
}

//----- (00403CE4) --------------------------------------------------------
u16 __cdecl sceSdPitch2Note(u16 center_note, u16 center_fine, u16 pitch)
{
  int bit; // $t1
  int i1; // $a3
  int val; // $a2
  int i2; // $a3
  int i5; // $a3

  bit = 0;
  pitch = ( pitch > 0x3FFF ) ? 0x3FFF : pitch;
  for ( i1 = 0; i1 < 14; i1 += 1 )
  {
    if ( ((pitch >> i1) & 1) )
      bit = i1;
  }
  val = pitch << (15 - bit);
  val &= 0xFFFF;
  for ( i2 = 11; val < g_NotePitchTable[i2] && i2 > 0; i2 -= 1 )
  {
  }
  if ( !g_NotePitchTable[i2] )
    __builtin_trap();
  val <<= 15;
  val &= 0xFFFF;
  val /= g_NotePitchTable[i2];
  for ( i5 = 127; val < g_NotePitchTable[i5 + 12] && i5 > 0; i5 -= 1 )
  {
  }
  return (((center_fine + i5 + 1) & 0x7E)
        + ((i2 + center_note + 12 * (bit - 12) + ((u16)(center_fine + i5 + 1) >> 7)) << 8)) & ~1;
}

//----- (00403E20) --------------------------------------------------------
static int __fastcall SetSpdifMode(int val)
{
  u16 spdif_out_new; // $t0
  u16 spdif_mode_new; // $a1

  spdif_out_new = spu2_regs.m_u.m_e.m_spdif_out & ~0x1A8;
  spdif_mode_new = spu2_regs.m_u.m_e.m_spdif_mode & ~0xBF06;
  switch ( val & 0xF )
  {
    case 0:
      spdif_out_new |= 0x20;
      break;
    case 1:
      spdif_out_new |= 0x100;
      spdif_mode_new |= 2;
      break;
    case 2:
      break;
    case 3:
      spdif_out_new |= 0x100;
      break;
    default:
      return -100;
  }
  spdif_mode_new |= (val & 0x80) ? 0x8000 : 0;
  switch ( val & 0xF00 )
  {
    case 0x400:
      spu2_regs.m_u.m_e.m_spdif_media = 0;
      spdif_mode_new |= 0x100;
      break;
    case 0x800:
      spu2_regs.m_u.m_e.m_spdif_media = 0x200;
      spdif_mode_new |= 0x1900;
      break;
    default:
      spu2_regs.m_u.m_e.m_spdif_media = 0x200;
      spdif_mode_new |= 0x900;
      break;
  }
  spu2_regs.m_u.m_e.m_spdif_out = spdif_out_new;
  spu2_regs.m_u.m_e.m_spdif_mode = spdif_mode_new;
  g_SpdifSettings = val;
  return 0;
}
// 4055E0: using guessed type int g_SpdifSettings;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00403FEC) --------------------------------------------------------
void __cdecl sceSdSetCoreAttr(u16 entry, u16 value)
{
  u16 setting_tmp; // $s1
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
      // Unofficial: inline the following
      setting_tmp = g_CoreAttrShifts[((entry & 0xE) >> 1) - 1];
      CpuSuspendIntr(&state);
      param_tmp = (entry & 1) | 0x2300;
      sceSdSetParam(param_tmp, (sceSdGetParam(param_tmp) & ~(1 << setting_tmp)) | ((value & 1) << setting_tmp));
      CpuResumeIntr(state);
      break;
  }
}

//----- (004040A0) --------------------------------------------------------
u16 __cdecl sceSdGetCoreAttr(u16 entry)
{
  int core;

  core = entry & 1;
  switch ( entry & 0xE )
  {
    case SD_CORE_EFFECT_ENABLE:
      return (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr >> 7) & 1;
    case SD_CORE_IRQ_ENABLE:
      return (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr >> 6) & 1;
    case SD_CORE_MUTE_ENABLE:
      return (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr >> 14) & 1;
    case SD_CORE_NOISE_CLK:
      return (spu2_regs.m_u.m_m.m_core_regs[core].m_cregs.m_attr >> 8) & 0x3F;
    case SD_CORE_SPDIF_MODE:
      return g_SpdifSettings & 0xFFFF;
    default:
      return 0;
  }
}
// 4055E0: using guessed type int g_SpdifSettings;
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404130) --------------------------------------------------------
SdIntrCallback __cdecl sceSdSetTransCallback(s32 core, SdIntrCallback cb)
{
  SdIntrCallback oldtmp; // $v0

  // Unofficial: restrict core
  core &= 1;
  oldtmp = g_TransIntrCallbacks[core];
  g_TransIntrCallbacks[core] = cb;
  return oldtmp;
}

//----- (0040416C) --------------------------------------------------------
sceSdTransIntrHandler __cdecl sceSdSetTransIntrHandler(int channel, sceSdTransIntrHandler func, void *arg)
{
  sceSdTransIntrHandler oldtmp; // $v0
  int core;

  // Unofficial: restrict core
  core = channel & 1;
  oldtmp = g_TransIntrHandlers[core];
  g_TransIntrHandlers[core] = func;
  g_TransIntrData[core].m_data = arg;
  return oldtmp;
}

//----- (004041A8) --------------------------------------------------------
void *__cdecl sceSdGetTransIntrHandlerArgument(int arg)
{
  return g_TransIntrData[arg].m_data;
}

//----- (004041C0) --------------------------------------------------------
SdIntrCallback __cdecl sceSdSetIRQCallback(SdIntrCallback cb)
{
  SdIntrCallback oldtmp; // $v0

  oldtmp = g_Spu2IrqCallback;
  g_Spu2IrqCallback = cb;
  return oldtmp;
}

//----- (004041E0) --------------------------------------------------------
sceSdSpu2IntrHandler __cdecl sceSdSetSpu2IntrHandler(sceSdSpu2IntrHandler func, void *arg)
{
  sceSdSpu2IntrHandler oldtmp; // $v0

  oldtmp = g_Spu2IntrHandler;
  g_Spu2IntrHandler = func;
  g_Spu2IntrHandlerData = arg;
  return oldtmp;
}

//----- (00404208) --------------------------------------------------------
void *__cdecl sceSdGetSpu2IntrHandlerArgument()
{
  return g_Spu2IntrHandlerData;
}

//----- (00404220) --------------------------------------------------------
static int __fastcall Spu2Interrupt(void *data)
{
  int val; // $a0

  (void)data;
  if ( !g_Spu2IntrHandler && !g_Spu2IrqCallback )
    return 1;
  while ( ( val = (spu2_regs.m_u.m_e.m_spdif_irqinfo & 0xC) >> 2 ) )
  {
    int i;

    for ( i = 0; i < 2; i += 1 )
      if ( val & (1 << i) )
        spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_attr &= ~0x40u;
    if ( g_Spu2IntrHandler )
      g_Spu2IntrHandler(val, g_Spu2IntrHandlerData);
    else if ( g_Spu2IrqCallback )
      g_Spu2IrqCallback(0);
  }
  return 1;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404344) --------------------------------------------------------
static int InitVoices()
{
  int i;
  int j;

  spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_attr &= ~SD_CORE_DMA;
  spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_tsa.m_pair[0] = 0x0000;
  spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_tsa.m_pair[1] = 0x2800;
  for ( i = 0; i < (int)(sizeof(g_VoiceDataInit)/sizeof(g_VoiceDataInit[0])); i += 1 )
    spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_xferdata = g_VoiceDataInit[i];
  spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_attr = (spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_attr & ~SD_CORE_DMA) | SD_DMA_IO;
  for ( i = 0; (spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_statx & SD_IO_IN_PROCESS) && i <= 0x1000000; i += 1 )
    libsd_do_busyloop_1(1);
  spu2_regs.m_u.m_m.m_core_regs[0].m_cregs.m_attr &= ~SD_CORE_DMA;
  // Unofficial: rerolled
  for ( i = 0; i < 24; i += 1 )
  {
    for ( j = 0; j < 2; j += 1 )
      spu2_regs.m_u.m_m.m_core_regs[j ^ 1].m_cregs.m_voice_params[i].m_voll = 0;
    for ( j = 0; j < 2; j += 1 )
      spu2_regs.m_u.m_m.m_core_regs[j ^ 1].m_cregs.m_voice_params[i].m_volr = 0;
    for ( j = 0; j < 2; j += 1 )
      spu2_regs.m_u.m_m.m_core_regs[j ^ 1].m_cregs.m_voice_params[i].m_pitch = 0x3FFF;
    for ( j = 0; j < 2; j += 1 )
      spu2_regs.m_u.m_m.m_core_regs[j ^ 1].m_cregs.m_voice_params[i].m_adsr1 = 0;
    for ( j = 0; j < 2; j += 1 )
      spu2_regs.m_u.m_m.m_core_regs[j ^ 1].m_cregs.m_voice_params[i].m_adsr2 = 0;
    for ( j = 0; j < 2; j += 1 )
      spu2_regs.m_u.m_m.m_core_regs[j ^ 1].m_cregs.m_voice_address[i].m_ssa.m_pair[0] = 0;
    for ( j = 0; j < 2; j += 1 )
      spu2_regs.m_u.m_m.m_core_regs[j ^ 1].m_cregs.m_voice_address[i].m_ssa.m_pair[1] = 0x2800;
  }
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_m.m_core_regs[i ^ 1].m_cregs.m_kon.m_pair[0] = 0xFFFF;
    spu2_regs.m_u.m_m.m_core_regs[i ^ 1].m_cregs.m_kon.m_pair[1] = 0xFF;
  }
  libsd_do_busyloop_1(3);
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_m.m_core_regs[i ^ 1].m_cregs.m_koff.m_pair[0] = 0xFFFF;
    spu2_regs.m_u.m_m.m_core_regs[i ^ 1].m_cregs.m_koff.m_pair[1] = 0xFF;
  }
  libsd_do_busyloop_1(3);
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_endx.m_pair[1] = 0;
    spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_endx.m_pair[0] = 0;
  }
  return 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (00404644) --------------------------------------------------------
static int __fastcall Reset(char flag)
{
  iop_event_t efparam; // [sp+10h] [-18h] BYREF
  int intrstate; // [sp+20h] [-8h] BYREF
  int i;

  DisableIntr(36, &intrstate);
  DisableIntr(40, &intrstate);
  DisableIntr(9, &intrstate);
  ReleaseIntrHandler(36);
  ReleaseIntrHandler(40);
  ReleaseIntrHandler(9);
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    g_VoiceTransStatus[i] = 0;
    g_VoiceTransIoMode[i] = 1;
    g_VoiceTransCompleteBool[i] = 0;
    g_TransIntrHandlers[i] = 0;
    g_CleanHandlers[i] = 0;
    g_TransIntrData[i].m_mode = i;
    g_TransIntrData[i].m_data = 0;
    g_BlockHandlerIntrData[i].m_cb = 0;
    g_BlockHandlerIntrData[i].m_userdata = 0;
    g_TransIntrCallbacks[i] = 0;
  }
  g_Spu2IntrHandler = 0;
  g_Spu2IntrHandlerData = 0;
  g_Spu2IrqCallback = 0;
  if ( !(flag & 0xF) )
  {
    bzero(g_EffectAttr, sizeof(g_EffectAttr));
    // Unofficial: rerolled
    for ( i = 0; i < 2; i += 1 )
      g_EffectAddr[i] = 0x1DFFF0 + (0x20000 * i);    
    // Unofficial: rerolled
    for ( i = 0; i < 2; i += 1 )
    {
      spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_esa.m_pair[0] = 0x000E + i;
      spu2_regs.m_u.m_m.m_core_regs[i].m_cregs.m_esa.m_pair[1] = 0xFFF8;
    }
  }
  efparam.attr = 2;
  efparam.bits = 1;
  efparam.option = 0;
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
  {
    if ( g_VoiceTransCompleteEf[i] <= 0 )
      g_VoiceTransCompleteEf[i] = CreateEventFlag(&efparam);
    else
    {
      if ( QueryIntrContext() )
        iSetEventFlag(g_VoiceTransCompleteEf[i], 1);
      else
        SetEventFlag(g_VoiceTransCompleteEf[i], 1);
    }
  }
  return ( g_VoiceTransCompleteEf[0] <= 0 || g_VoiceTransCompleteEf[1] <= 0 ) ? -301 : 0;
}
// BF900000: using guessed type spu2_regs_t spu2_regs;

//----- (004048C8) --------------------------------------------------------
static void reset_vars()
{
  int i;

  g_vars_inited = 0;
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
    g_VoiceTransCompleteEf[i] = 0;
}
// 405628: using guessed type int g_vars_inited;

//----- (004048E4) --------------------------------------------------------
int __cdecl sceSdInit(int flag)
{
  int resetres; // $s2

  InitSpu2();
  if ( !(flag & 0xF) )
    InitSpdif();
  resetres = Reset(flag & 0xFF);
  InitVoices();
  InitCoreVolume(flag & 0xF);
  EnableIntr(36);
  EnableIntr(40);
  EnableIntr(9);
  RegisterIntrHandler(36, 1, (int (__cdecl *)(void *))TransInterrupt, &g_TransIntrData[0]);
  RegisterIntrHandler(40, 1, (int (__cdecl *)(void *))TransInterrupt, &g_TransIntrData[1]);
  RegisterIntrHandler(9, 1, (int (__cdecl *)(void *))Spu2Interrupt, g_Spu2IntrHandlerData);
  g_vars_inited = 1;
  return resetres;
}
// 405628: using guessed type int g_vars_inited;

//----- (004049C4) --------------------------------------------------------
int __cdecl sceSdQuit()
{
  int intrstate; // [sp+10h] [-8h] BYREF
  int i;

  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
    DmaStartStop((i << 4) | 0xA, 0, 0);
  // Unofficial: rerolled
  for ( i = 0; i < 2; i += 1 )
    if ( g_VoiceTransCompleteEf[i] > 0 )
      DeleteEventFlag(g_VoiceTransCompleteEf[i]);
  DisableIntr(40, &intrstate);
  DisableIntr(36, &intrstate);
  DisableIntr(9, &intrstate);
  ReleaseIntrHandler(40);
  ReleaseIntrHandler(36);
  ReleaseIntrHandler(9);
  return 0;
}
