
#include "irx_imports.h"
#include <stdbool.h>

IRX_ID("Sound_Data_HD", 2, 2);

#define _BYTE u8
#define _WORD u16
#define _DWORD u32
#define BOOL _DWORD

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

#define __fastcall
#define __cdecl

#define _break(...) __builtin_trap()

struct sceHardSynthVersionChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned __int16 reserved;
  unsigned __int8 versionMajor;
  unsigned __int8 versionMinor;
};

typedef struct sceHardSynthVersionChunk_ sceHardSynthVersionChunk;
typedef struct sceHardSynthVersionChunk_ sceSeqVersionChunk;

typedef struct sceHardSynthHeaderChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int headerSize;
  unsigned int bodySize;
  unsigned int programChunkAddr;
  unsigned int sampleSetChunkAddr;
  unsigned int sampleChunkAddr;
  unsigned int vagInfoChunkAddr;
  unsigned int seTimbreChunkAddr;
} sceHardSynthHeaderChunk;

typedef struct sceHardSynthProgramChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int maxProgramNumber;
  unsigned int programOffsetAddr[];
} sceHardSynthProgramChunk;

typedef struct sceHardSynthSampleSetChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int maxSampleSetNumber;
  unsigned int sampleSetOffsetAddr[];
} sceHardSynthSampleSetChunk;

typedef struct sceHardSynthSampleChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int maxSampleNumber;
  unsigned int sampleOffsetAddr[];
} sceHardSynthSampleChunk;

typedef struct sceHardSynthVagInfoChunk
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int maxVagInfoNumber;
  unsigned int vagInfoOffsetAddr[];
} sceHardSynthVagInfoChunk;

struct sdhd_info
{
  sceHardSynthVersionChunk *m_vers;
  sceHardSynthHeaderChunk *m_head;
  sceHardSynthProgramChunk *m_prog;
  sceHardSynthSampleSetChunk *m_sset;
  sceHardSynthSampleChunk *m_smpl;
  sceHardSynthVagInfoChunk *m_vagi;
};

struct SceSdHdProgramCommon_
{
  unsigned int volume;
  int panpot;
  int transpose;
  int detune;
};

typedef struct SceSdHdProgramCommon_ SceSdHdProgramCommon;
typedef struct SceSdHdProgramCommon_ SceSdHdSplitCommon;

typedef struct SceSdHdProgramKeyFollow_
{
  int pan;
  unsigned int panCenter;
} SceSdHdProgramKeyFollow;

typedef struct SceSdHdProgramLFO_
{
  unsigned int wavePitch;
  unsigned int waveAmp;
  unsigned int startPhasePitch;
  unsigned int startPhaseAmp;
  unsigned int phaseRandomPitch;
  unsigned int phaseRandomAmp;
  unsigned int cyclePitch;
  unsigned int cycleAmp;
  int pitchDepthUp;
  int pitchDepthDown;
  int midiPitchDepthUp;
  int midiPitchDepthDown;
  int ampDepthUp;
  int ampDepthDown;
  int midiAmpDepthUp;
  int midiAmpDepthDown;
} SceSdHdProgramLFO;

typedef struct SceSdHdProgramParam_
{
  unsigned int nSplit;
  unsigned int progAttr;
  SceSdHdProgramCommon common;
  SceSdHdProgramKeyFollow keyFollow;
  SceSdHdProgramLFO LFO;
} SceSdHdProgramParam;

typedef struct sceHardSynthSplitBlock_
{
  unsigned __int16 sampleSetIndex;
  unsigned __int8 splitRangeLow;
  unsigned __int8 splitCrossFade;
  unsigned __int8 splitRangeHigh;
  unsigned __int8 splitNumber;
  unsigned __int16 splitBendRangeLow;
  unsigned __int16 splitBendRangeHigh;
  char keyFollowPitch;
  unsigned __int8 keyFollowPitchCenter;
  char keyFollowAmp;
  unsigned __int8 keyFollowAmpCenter;
  char keyFollowPan;
  unsigned __int8 keyFollowPanCenter;
  unsigned __int8 splitVolume;
  char splitPanpot;
  char splitTranspose;
  char splitDetune;
} sceHardSynthSplitBlock;

typedef struct sceHardSynthProgramParam_
{
  unsigned int splitBlockAddr;
  unsigned __int8 nSplit;
  unsigned __int8 sizeSplitBlock;
  unsigned __int8 progVolume;
  char progPanpot;
  char progTranspose;
  char progDetune;
  char keyFollowPan;
  unsigned __int8 keyFollowPanCenter;
  unsigned __int8 progAttr;
  unsigned __int8 dmy;
  unsigned __int8 progLfoWave;
  unsigned __int8 progLfoWave2;
  unsigned __int8 progLfoStartPhase;
  unsigned __int8 progLfoStartPhase2;
  unsigned __int8 progLfoPhaseRandom;
  unsigned __int8 progLfoPhaseRandom2;
  unsigned __int16 progLfoFreq;
  unsigned __int16 progLfoFreq2;
  __int16 progLfoPitchDepth;
  __int16 progLfoPitchDepth2;
  __int16 progLfoMidiPitchDepth;
  __int16 progLfoMidiPitchDepth2;
  char progLfoAmpDepth;
  char progLfoAmpDepth2;
  char progLfoMidiAmpDepth;
  char progLfoMidiAmpDepth2;
  sceHardSynthSplitBlock splitBlock[];
} sceHardSynthProgramParam;

struct SceSdHdSplitRange_
{
  unsigned int low;
  unsigned int crossFade;
  unsigned int high;
};

typedef struct SceSdHdSplitRange_ SceSdHdSplitRange;
typedef struct SceSdHdSplitRange_ SceSdHdSampleVelRange;

typedef struct SceSdHdSplitBendRange_
{
  unsigned int low;
  unsigned int high;
} SceSdHdSplitBendRange;

typedef struct SceSdHdSplitKeyFollow_
{
  int pitch;
  unsigned int pitchCenter;
  int amp;
  unsigned int ampCenter;
  int pan;
  unsigned int panCenter;
} SceSdHdSplitKeyFollow;

typedef struct SceSdHdSplitBlock_
{
  unsigned int sampleSetIndex;
  unsigned int splitNumber;
  SceSdHdSplitRange range;
  SceSdHdSplitBendRange bendRange;
  SceSdHdSplitKeyFollow keyFollow;
  SceSdHdSplitCommon common;
} SceSdHdSplitBlock;

typedef struct SceSdHdSampleSetParam_
{
  unsigned int velCurve;
  unsigned int velLimitLow;
  unsigned int velLimitHigh;
  unsigned int nSample;
} SceSdHdSampleSetParam;

typedef struct sceHardSynthSampleSetParam_
{
  unsigned __int8 velCurve;
  unsigned __int8 velLimitLow;
  unsigned __int8 velLimitHigh;
  unsigned __int8 nSample;
  unsigned __int16 sampleIndex[];
} sceHardSynthSampleSetParam;

typedef struct SceSdHdSampleVelFollow_
{
  int pitch;
  unsigned int pitchCenter;
  unsigned int pitchVelCurve;
  int amp;
  unsigned int ampCenter;
  unsigned int ampVelCurve;
} SceSdHdSampleVelFollow;

typedef struct SceSdHdSampleCommon_
{
  unsigned int baseNote;
  int detune;
  int panpot;
  unsigned int group;
  unsigned int priority;
  unsigned int volume;
} SceSdHdSampleCommon;

typedef struct SceSdHdSampleADSR_
{
  unsigned int ADSR1;
  unsigned int ADSR2;
} SceSdHdSampleADSR;

typedef struct SceSdHdSampleKeyFollow_
{
  int ar;
  unsigned int arCenter;
  int dr;
  unsigned int drCenter;
  int sr;
  unsigned int srCenter;
  int rr;
  unsigned int rrCenter;
  int sl;
  unsigned int slCenter;
} SceSdHdSampleKeyFollow;

typedef struct SceSdHdSampleLFO_
{
  unsigned int pitchLFODelay;
  unsigned int pitchLFOFade;
  unsigned int ampLFODelay;
  unsigned int ampLFOFade;
} SceSdHdSampleLFO;

typedef struct SceSdHdSampleParam_
{
  int vagIndex;
  unsigned int spuAttr;
  unsigned int lfoAttr;
  SceSdHdSampleVelRange velRange;
  SceSdHdSampleVelFollow velFollow;
  SceSdHdSampleCommon common;
  SceSdHdSampleADSR ADSR;
  SceSdHdSampleKeyFollow keyFollow;
  SceSdHdSampleLFO LFO;
} SceSdHdSampleParam;

typedef struct sceHardSynthSampleParam_
{
  unsigned __int16 VagIndex;
  unsigned __int8 velRangeLow;
  unsigned __int8 velCrossFade;
  unsigned __int8 velRangeHigh;
  char velFollowPitch;
  unsigned __int8 velFollowPitchCenter;
  unsigned __int8 velFollowPitchVelCurve;
  char velFollowAmp;
  unsigned __int8 velFollowAmpCenter;
  unsigned __int8 velFollowAmpVelCurve;
  unsigned __int8 sampleBaseNote;
  char sampleDetune;
  char samplePanpot;
  unsigned __int8 sampleGroup;
  unsigned __int8 samplePriority;
  unsigned __int8 sampleVolume;
  unsigned __int8 dmy;
  unsigned __int16 sampleAdsr1;
  unsigned __int16 sampleAdsr2;
  char keyFollowAr;
  unsigned __int8 keyFollowArCenter;
  char keyFollowDr;
  unsigned __int8 keyFollowDrCenter;
  char keyFollowSr;
  unsigned __int8 keyFollowSrCenter;
  char keyFollowRr;
  unsigned __int8 keyFollowRrCenter;
  char keyFollowSl;
  unsigned __int8 keyFollowSlCenter;
  unsigned __int16 samplePitchLfoDelay;
  unsigned __int16 samplePitchLfoFade;
  unsigned __int16 sampleAmpLfoDelay;
  unsigned __int16 sampleAmpLfoFade;
  unsigned __int8 sampleLfoAttr;
  unsigned __int8 sampleSpuAttr;
} sceHardSynthSampleParam;

typedef struct SceSdHdVAGInfoParam_
{
  unsigned int vagOffsetAddr;
  unsigned int vagSize;
  unsigned int vagSampleRate;
  unsigned int vagAttribute;
} SceSdHdVAGInfoParam;

typedef struct sceHardSynthVagParam_
{
  unsigned int vagOffsetAddr;
  unsigned __int16 vagSampleRate;
  unsigned __int8 vagAttribute;
  unsigned __int8 dmy;
} sceHardSynthVagParam;

//-------------------------------------------------------------------------
// Function declarations

void sdhd_1();
int __fastcall do_get_vers_head_chunk(sceHardSynthVersionChunk *indata, struct sdhd_info *dinfo);
int __fastcall do_get_prog_chunk(void *indata, struct sdhd_info *dinfo);
int __fastcall do_get_sset_chunk(void *indata, struct sdhd_info *dinfo);
int __fastcall do_get_smpl_chunk(void *indata, struct sdhd_info *dinfo);
int __fastcall do_get_vagi_chunk(void *indata, struct sdhd_info *dinfo);
int __fastcall do_copy_to_sdhd_program_param(SceSdHdProgramParam *dst, sceHardSynthProgramParam *src);
int __fastcall do_copy_to_sdhd_split_block(SceSdHdSplitBlock *dst, sceHardSynthSplitBlock *src);
unsigned int __fastcall do_copy_to_sdhd_set_param(SceSdHdSampleSetParam *dst, sceHardSynthSampleSetParam *src);
unsigned int __fastcall do_copy_to_sdhd_sample_param(SceSdHdSampleParam *dst, sceHardSynthSampleParam *src);
unsigned int __fastcall do_copy_to_sdhd_vag_info_param(SceSdHdVAGInfoParam *dst, int sz, sceHardSynthVagParam *src);
unsigned int __fastcall do_get_vag_size(sceHardSynthVersionChunk *indata, unsigned int *vagoffsaddr);
unsigned int __fastcall do_check_chunk_in_bounds(void *indata, struct sdhd_info *dinfo, unsigned int hdrmagic, unsigned int idx);
int __fastcall do_get_common_block_ptr_note(void *buffer, unsigned int programNumber, unsigned int swcase, unsigned int noteNumber, unsigned int velocity, int mode, void **ptr);
int __fastcall do_get_common_block_ptr(void *buffer, unsigned int sampleSetNumber, unsigned int swcase, unsigned int velocity, int mode, void **param);
int __cdecl sceSdHdGetMaxProgramNumber(void *buffer);
int __cdecl sceSdHdGetMaxSampleSetNumber(void *buffer);
int __cdecl sceSdHdGetMaxSampleNumber(void *buffer);
int __cdecl sceSdHdGetMaxVAGInfoNumber(void *buffer);
int __cdecl sceSdHdGetProgramParamAddr(void *buffer, unsigned int programNumber, sceHardSynthProgramParam **ptr);
int __cdecl sceSdHdGetProgramParam(void *buffer, unsigned int programNumber, SceSdHdProgramParam *param);
int __cdecl sceSdHdGetSplitBlockAddr(void *buffer, unsigned int programNumber, unsigned int splitBlockNumber, sceHardSynthSplitBlock **theParamPtr);
int __cdecl sceSdHdGetSplitBlock(void *buffer, unsigned int programNumber, unsigned int splitBlockNumber, SceSdHdSplitBlock *param);
int __cdecl sceSdHdGetSampleSetParamAddr(void *buffer, unsigned int sampleSetNumber, sceHardSynthSampleSetParam **ptr);
int __cdecl sceSdHdGetSampleSetParam(void *buffer, unsigned int sampleSetNumber, SceSdHdSampleSetParam *param);
int __cdecl sceSdHdGetSampleParamAddr(void *buffer, unsigned int sampleNumber, sceHardSynthSampleParam **ptr);
int __cdecl sceSdHdGetSampleParam(void *buffer, unsigned int sampleNumber, SceSdHdSampleParam *param);
int __cdecl sceSdHdGetVAGInfoParamAddr(void *buffer, unsigned int vagInfoNumber, sceHardSynthVagParam **ptr);
int __cdecl sceSdHdGetVAGInfoParam(void *buffer, unsigned int vagInfoNumber, SceSdHdVAGInfoParam *param);
int __cdecl sceSdHdCheckProgramNumber(void *buffer, unsigned int programNumber);
int __cdecl sceSdHdGetSplitBlockCountByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber);
int __cdecl sceSdHdGetSplitBlockAddrByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber, sceHardSynthSplitBlock **ptr);
int __cdecl sceSdHdGetSplitBlockByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber, SceSdHdSplitBlock *param);
int __cdecl sceSdHdGetSampleSetParamCountByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber);
int __cdecl sceSdHdGetSampleSetParamAddrByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber, sceHardSynthSampleSetParam **ptr);
int __cdecl sceSdHdGetSampleSetParamByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber, SceSdHdSampleSetParam *param);
int __cdecl sceSdHdGetSampleParamCountByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode);
int __cdecl sceSdHdGetSampleParamAddrByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode, sceHardSynthSampleParam **ptr);
int __cdecl sceSdHdGetSampleParamByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode, SceSdHdSampleParam *param);
int __cdecl sceSdHdGetVAGInfoParamCountByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode);
int __cdecl sceSdHdGetVAGInfoParamAddrByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode, sceHardSynthVagParam **ptr);
int __cdecl sceSdHdGetVAGInfoParamByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode, SceSdHdVAGInfoParam *param);
int __cdecl sceSdHdGetSampleParamCountByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode);
int __cdecl sceSdHdGetSampleParamAddrByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode, sceHardSynthSampleParam **ptr);
int __cdecl sceSdHdGetSampleParamByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode, SceSdHdSampleParam *param);
int __cdecl sceSdHdGetVAGInfoParamCountByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode);
int __cdecl sceSdHdGetVAGInfoParamAddrByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode, sceHardSynthVagParam **ptr);
int __cdecl sceSdHdGetVAGInfoParamByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode, SceSdHdVAGInfoParam *param);
int __cdecl sceSdHdGetVAGInfoParamAddrBySampleNumber(void *buffer, unsigned int sampleNumber, sceHardSynthVagParam **ptr);
int __cdecl sceSdHdGetVAGInfoParamBySampleNumber(void *buffer, unsigned int sampleNumber, SceSdHdVAGInfoParam *param);
int __cdecl sceSdHdGetSplitBlockNumberBySplitNumber(void *buffer, unsigned int programNumber, unsigned int splitNumber);
int __cdecl sceSdHdGetVAGSize(void *buffer, unsigned int vagInfoNumber);
int __cdecl sceSdHdGetSplitBlockCount(void *buffer, unsigned int programNumber);
int __cdecl sceSdHdGetMaxSplitBlockCount(void *buffer);
int __cdecl sceSdHdGetMaxSampleSetParamCount(void *buffer);
int __cdecl sceSdHdGetMaxSampleParamCount(void *buffer);
int __cdecl sceSdHdGetMaxVAGInfoParamCount(void *buffer);
int __cdecl sceSdHdModifyVelocity(unsigned int curveType, int velocity);
int __cdecl sceSdHdModifyVelocityLFO(unsigned int curveType, int velocity, int center);
int __cdecl sceSdHdGetValidProgramNumberCount(void *buffer);
int __cdecl sceSdHdGetValidProgramNumber(void *buffer, unsigned int *ptr);
int __cdecl sceSdHdGetSampleNumberBySampleIndex(void *buffer, unsigned int sampleSetNumber, unsigned int sampleIndexNumber);
int __fastcall _start(int ac);

//-------------------------------------------------------------------------
// Data declarations

const struct irx_export_table exports =
{
  1103101952u,
  NULL,
  258u,
  0u,
  { 115u, 100u, 104u, 100u, 0u, 0u, 0u, 0u },
  { &_start }
}; // idb


//----- (004000E4) --------------------------------------------------------
void sdhd_1()
{
  ;
}

//----- (004000F0) --------------------------------------------------------
int __fastcall do_get_vers_head_chunk(sceHardSynthVersionChunk *indata, struct sdhd_info *dinfo)
{
  int result; // $v0
  signed int chunkSize; // $v0
  sceHardSynthHeaderChunk *chk; // $a0

  dinfo->m_vers = 0;
  dinfo->m_head = 0;
  dinfo->m_prog = 0;
  dinfo->m_sset = 0;
  dinfo->m_smpl = 0;
  dinfo->m_vagi = 0;
  dinfo->m_vers = indata;
  if ( indata->Creator == 0x53434549 && indata->Type == 0x56657273 )
  {
    chunkSize = indata->chunkSize;
    chk = (sceHardSynthHeaderChunk *)((char *)indata + chunkSize);
    if ( chunkSize >= 0 )
    {
      dinfo->m_head = chk;
      if ( chk->Creator == 0x53434549 && chk->Type == 0x48656164 )
      {
        return 0;
      }
      else
      {
        result = 0x8103002F;
        dinfo->m_vers = 0;
        dinfo->m_head = 0;
      }
    }
    else
    {
      dinfo->m_vers = 0;
      return 0x8103002F;
    }
  }
  else
  {
    dinfo->m_vers = 0;
    return 0x8103000E;
  }
  return result;
}

//----- (004001A0) --------------------------------------------------------
int __fastcall do_get_prog_chunk(void *indata, struct sdhd_info *dinfo)
{
  signed int programChunkAddr; // $a0
  sceHardSynthProgramChunk *chk; // $a0

  programChunkAddr = dinfo->m_head->programChunkAddr;
  if ( programChunkAddr == -1 )
    return 0x81039005;
  if ( programChunkAddr < 0 )
    return 0x8103002F;
  chk = (sceHardSynthProgramChunk *)((char *)indata + programChunkAddr);
  dinfo->m_prog = chk;
  if ( chk->Creator != 0x53434549 || chk->Type != 0x50726F67 )
  {
    dinfo->m_prog = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (0040020C) --------------------------------------------------------
int __fastcall do_get_sset_chunk(void *indata, struct sdhd_info *dinfo)
{
  signed int sampleSetChunkAddr; // $a0
  sceHardSynthSampleSetChunk *chk; // $a0

  sampleSetChunkAddr = dinfo->m_head->sampleSetChunkAddr;
  if ( sampleSetChunkAddr == -1 )
    return 0x81039006;
  if ( sampleSetChunkAddr < 0 )
    return 0x8103002F;
  chk = (sceHardSynthSampleSetChunk *)((char *)indata + sampleSetChunkAddr);
  dinfo->m_sset = chk;
  if ( chk->Creator != 0x53434549 || chk->Type != 0x53736574 )
  {
    dinfo->m_sset = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (00400278) --------------------------------------------------------
int __fastcall do_get_smpl_chunk(void *indata, struct sdhd_info *dinfo)
{
  signed int sampleChunkAddr; // $a0
  sceHardSynthSampleChunk *chk; // $a0

  sampleChunkAddr = dinfo->m_head->sampleChunkAddr;
  if ( sampleChunkAddr == -1 )
    return 0x81039007;
  if ( sampleChunkAddr < 0 )
    return 0x8103002F;
  chk = (sceHardSynthSampleChunk *)((char *)indata + sampleChunkAddr);
  dinfo->m_smpl = chk;
  if ( chk->Creator != 0x53434549 || chk->Type != 0x536D706C )
  {
    dinfo->m_smpl = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (004002E4) --------------------------------------------------------
int __fastcall do_get_vagi_chunk(void *indata, struct sdhd_info *dinfo)
{
  signed int vagInfoChunkAddr; // $a0
  sceHardSynthVagInfoChunk *chk; // $a0

  vagInfoChunkAddr = dinfo->m_head->vagInfoChunkAddr;
  if ( vagInfoChunkAddr == -1 )
    return 0x81039008;
  if ( vagInfoChunkAddr < 0 )
    return 0x8103002F;
  chk = (sceHardSynthVagInfoChunk *)((char *)indata + vagInfoChunkAddr);
  dinfo->m_vagi = chk;
  if ( chk->Creator != 0x53434549 || chk->Type != 0x56616769 )
  {
    dinfo->m_vagi = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (00400350) --------------------------------------------------------
int __fastcall do_copy_to_sdhd_program_param(SceSdHdProgramParam *dst, sceHardSynthProgramParam *src)
{
  int result; // $v0

  dst->nSplit = src->nSplit;
  dst->progAttr = src->progAttr;
  dst->common.volume = src->progVolume;
  dst->common.panpot = src->progPanpot;
  dst->common.transpose = src->progTranspose;
  dst->common.detune = src->progDetune;
  dst->keyFollow.pan = src->keyFollowPan;
  dst->keyFollow.panCenter = src->keyFollowPanCenter;
  dst->LFO.wavePitch = src->progLfoWave;
  dst->LFO.waveAmp = src->progLfoWave2;
  dst->LFO.startPhasePitch = src->progLfoStartPhase;
  dst->LFO.startPhaseAmp = src->progLfoStartPhase2;
  dst->LFO.phaseRandomPitch = src->progLfoPhaseRandom;
  dst->LFO.phaseRandomAmp = src->progLfoPhaseRandom2;
  dst->LFO.cyclePitch = src->progLfoFreq;
  dst->LFO.cycleAmp = src->progLfoFreq2;
  dst->LFO.pitchDepthUp = src->progLfoPitchDepth;
  dst->LFO.pitchDepthDown = src->progLfoPitchDepth2;
  dst->LFO.midiPitchDepthUp = src->progLfoMidiPitchDepth;
  dst->LFO.midiPitchDepthDown = src->progLfoMidiPitchDepth2;
  dst->LFO.ampDepthUp = src->progLfoAmpDepth;
  dst->LFO.ampDepthDown = src->progLfoAmpDepth2;
  dst->LFO.midiAmpDepthUp = src->progLfoMidiAmpDepth;
  result = src->progLfoMidiAmpDepth2;
  dst->LFO.midiAmpDepthDown = result;
  return result;
}

//----- (00400470) --------------------------------------------------------
int __fastcall do_copy_to_sdhd_split_block(SceSdHdSplitBlock *dst, sceHardSynthSplitBlock *src)
{
  int result; // $v0

  dst->sampleSetIndex = src->sampleSetIndex;
  dst->splitNumber = src->splitNumber;
  dst->range.low = src->splitRangeLow;
  dst->range.crossFade = src->splitCrossFade;
  dst->range.high = src->splitRangeHigh;
  dst->bendRange.low = src->splitBendRangeLow;
  dst->bendRange.high = src->splitBendRangeHigh;
  dst->keyFollow.pitch = src->keyFollowPitch;
  dst->keyFollow.pitchCenter = src->keyFollowPitchCenter;
  dst->keyFollow.amp = src->keyFollowAmp;
  dst->keyFollow.ampCenter = src->keyFollowAmpCenter;
  dst->keyFollow.pan = src->keyFollowPan;
  dst->keyFollow.panCenter = src->keyFollowPanCenter;
  dst->common.volume = src->splitVolume;
  dst->common.panpot = src->splitPanpot;
  dst->common.transpose = src->splitTranspose;
  result = src->splitDetune;
  dst->common.detune = result;
  return result;
}

//----- (0040053C) --------------------------------------------------------
unsigned int __fastcall do_copy_to_sdhd_set_param(SceSdHdSampleSetParam *dst, sceHardSynthSampleSetParam *src)
{
  unsigned int result; // $v0

  dst->velCurve = src->velCurve;
  dst->velLimitLow = src->velLimitLow;
  dst->velLimitHigh = src->velLimitHigh;
  result = src->nSample;
  dst->nSample = result;
  return result;
}

//----- (0040056C) --------------------------------------------------------
unsigned int __fastcall do_copy_to_sdhd_sample_param(SceSdHdSampleParam *dst, sceHardSynthSampleParam *src)
{
  unsigned int result; // $v0

  dst->vagIndex = src->VagIndex;
  dst->spuAttr = src->sampleSpuAttr;
  dst->lfoAttr = src->sampleLfoAttr;
  dst->velRange.low = src->velRangeLow;
  dst->velRange.crossFade = src->velCrossFade;
  dst->velRange.high = src->velRangeHigh;
  dst->velFollow.pitch = src->velFollowPitch;
  dst->velFollow.pitchCenter = src->velFollowPitchCenter;
  dst->velFollow.pitchVelCurve = src->velFollowPitchVelCurve;
  dst->velFollow.amp = src->velFollowAmp;
  dst->velFollow.ampCenter = src->velFollowAmpCenter;
  dst->velFollow.ampVelCurve = src->velFollowAmpVelCurve;
  dst->common.baseNote = src->sampleBaseNote;
  dst->common.detune = src->sampleDetune;
  dst->common.panpot = src->samplePanpot;
  dst->common.group = src->sampleGroup;
  dst->common.priority = src->samplePriority;
  dst->common.volume = src->sampleVolume;
  dst->ADSR.ADSR1 = src->sampleAdsr1;
  dst->ADSR.ADSR2 = src->sampleAdsr2;
  dst->keyFollow.ar = src->keyFollowAr;
  dst->keyFollow.arCenter = src->keyFollowArCenter;
  dst->keyFollow.dr = src->keyFollowDr;
  dst->keyFollow.drCenter = src->keyFollowDrCenter;
  dst->keyFollow.sr = src->keyFollowSr;
  dst->keyFollow.srCenter = src->keyFollowSrCenter;
  dst->keyFollow.rr = src->keyFollowRr;
  dst->keyFollow.rrCenter = src->keyFollowRrCenter;
  dst->keyFollow.sl = src->keyFollowSl;
  dst->keyFollow.slCenter = src->keyFollowSlCenter;
  dst->LFO.pitchLFODelay = src->samplePitchLfoDelay;
  dst->LFO.pitchLFOFade = src->samplePitchLfoFade;
  dst->LFO.ampLFODelay = src->sampleAmpLfoDelay;
  result = src->sampleAmpLfoFade;
  dst->LFO.ampLFOFade = result;
  return result;
}

//----- (00400704) --------------------------------------------------------
unsigned int __fastcall do_copy_to_sdhd_vag_info_param(SceSdHdVAGInfoParam *dst, int sz, sceHardSynthVagParam *src)
{
  unsigned int result; // $v0

  dst->vagOffsetAddr = src->vagOffsetAddr;
  dst->vagSampleRate = src->vagSampleRate;
  result = src->vagAttribute;
  dst->vagSize = sz;
  dst->vagAttribute = result;
  return result;
}

//----- (0040072C) --------------------------------------------------------
unsigned int __fastcall do_get_vag_size(sceHardSynthVersionChunk *indata, unsigned int *vagoffsaddr)
{
  bool condtmp1; // dc
  unsigned int result; // $v0
  unsigned int indx1; // $a0
  sceHardSynthVagInfoChunk *m_vagi; // $v1
  unsigned int bodySize; // $a1
  int indx2; // $v0
  unsigned int offsdata; // $v0
  sceHardSynthVagParam *vagparam; // $v0
  unsigned int curaddr; // $v1
  BOOL condtmp2; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  condtmp1 = do_get_vers_head_chunk(indata, &dinfo) != 0;
  result = 0;
  if ( !condtmp1 )
  {
    condtmp1 = do_get_vagi_chunk(indata, &dinfo) != 0;
    result = 0;
    if ( !condtmp1 )
    {
      indx1 = 0;
      m_vagi = dinfo.m_vagi;
      bodySize = dinfo.m_head->bodySize;
      indx2 = 0;
      do
      {
        offsdata = m_vagi->vagInfoOffsetAddr[indx2];
        condtmp1 = offsdata == -1;
        vagparam = (sceHardSynthVagParam *)((char *)m_vagi + offsdata);
        if ( !condtmp1 )
        {
          curaddr = vagparam->vagOffsetAddr;
          condtmp1 = *vagoffsaddr >= vagparam->vagOffsetAddr;
          condtmp2 = vagparam->vagOffsetAddr < bodySize;
          if ( !condtmp1 )
          {
            if ( condtmp2 )
              bodySize = curaddr;
          }
        }
        m_vagi = dinfo.m_vagi;
        indx2 = ++indx1;
      }
      while ( dinfo.m_vagi->maxVagInfoNumber >= indx1 );
      return bodySize - *vagoffsaddr;
    }
  }
  return result;
}

//----- (004007F4) --------------------------------------------------------
unsigned int __fastcall do_check_chunk_in_bounds(
        void *indata,
        struct sdhd_info *dinfo,
        unsigned int hdrmagic,
        unsigned int idx)
{
  unsigned int retres; // $a0
  unsigned int result; // $v0
  sceHardSynthProgramChunk *m_prog; // $a1
  sceHardSynthSampleSetChunk *m_sset; // $a1
  sceHardSynthSampleChunk *m_smpl; // $a1
  sceHardSynthVagInfoChunk *m_vagi; // $a1

  retres = 0;
  if ( hdrmagic == 0x536D706C )
  {
    m_smpl = dinfo->m_smpl;
    if ( !m_smpl )
      retres = 0x8103002F;
    if ( m_smpl->maxSampleNumber < idx )
      retres = 0x81039014;
    result = retres;
    if ( m_smpl->sampleOffsetAddr[idx] == -1 )
      return 0x81039015;
  }
  else if ( hdrmagic > 0x536D706C )
  {
    if ( hdrmagic == 0x53736574 )
    {
      m_sset = dinfo->m_sset;
      if ( !m_sset )
        retres = 0x8103002F;
      if ( m_sset->maxSampleSetNumber < idx )
        retres = 0x81039012;
      result = retres;
      if ( m_sset->sampleSetOffsetAddr[idx] == -1 )
        return 0x81039012;
    }
    else
    {
      result = 0;
      if ( hdrmagic == 0x56616769 )
      {
        m_vagi = dinfo->m_vagi;
        if ( !m_vagi )
          retres = 0x8103002F;
        if ( m_vagi->maxVagInfoNumber < idx )
          retres = 0x81039016;
        result = retres;
        if ( m_vagi->vagInfoOffsetAddr[idx] == -1 )
          return 0x81039017;
      }
    }
  }
  else
  {
    result = 0;
    if ( hdrmagic == 0x50726F67 )
    {
      m_prog = dinfo->m_prog;
      if ( !m_prog )
        retres = 0x8103002F;
      if ( m_prog->maxProgramNumber < idx )
        retres = 0x81039010;
      result = retres;
      if ( m_prog->programOffsetAddr[idx] == -1 )
        return 0x81039011;
    }
  }
  return result;
}

//----- (004009A0) --------------------------------------------------------
int __fastcall do_get_common_block_ptr_note(
        void *buffer,
        unsigned int programNumber,
        unsigned int swcase,
        unsigned int noteNumber,
        unsigned int velocity,
        int mode,
        void **ptr)
{
  int idx1; // $s1
  bool condtmp1; // dc
  int result; // $v0
  int idx2; // $s6
  sceHardSynthSplitBlock *p_splitblock; // $a1
  void **ptr_1; // $a0
  void **ptr_6; // $a0
  sceHardSynthSampleSetParam *samplesetparam_1; // $v1
  int idxnsample; // $s2
  int cursampleindexoffs1; // $v0
  char *cursampleindex1; // $v1
  void **ptr_3; // $a0
  int vag_size; // $v0
  void **ptr_2; // $a0
  sceHardSynthSampleSetParam *p_samplesetparam_1; // $v1
  int nsamplecur; // $s2
  int cursampleindexoffs2; // $v0
  char *cursampleindex2; // $v1
  void **ptr_5; // $a0
  int vagsz_tmp; // $v0
  void **ptr_4; // $a0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-10h] BYREF
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+14h] [-Ch] BYREF
  sceHardSynthSampleParam *p_sampleparam; // [sp+18h] [-8h] BYREF
  sceHardSynthVagParam *p_vagparam; // [sp+1Ch] [-4h] BYREF

  idx1 = 0;
  condtmp1 = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam) != 0;
  result = 0;
  if ( !condtmp1 )
  {
    result = 0;
    if ( p_programparam->splitBlockAddr != -1 )
    {
      idx2 = 0;
      if ( p_programparam->nSplit )
      {
        while ( 1 )
        {
          p_splitblock = (sceHardSynthSplitBlock *)((char *)p_programparam
                                                  + p_programparam->splitBlockAddr
                                                  + p_programparam->sizeSplitBlock * idx2);
          if ( noteNumber < (p_splitblock->splitRangeLow & 0x7Fu) || (p_splitblock->splitRangeHigh & 0x7Fu) < noteNumber )
            goto LABEL_78;
          if ( swcase >= 3 )
            break;
          if ( swcase == 1 )
          {
            ++idx1;
            *ptr++ = p_splitblock;
          }
          else
          {
            if ( !swcase )
              goto LABEL_18;
            ptr_1 = ptr;
            ++idx1;
            ptr += 17;
            do_copy_to_sdhd_split_block((SceSdHdSplitBlock *)ptr_1, p_splitblock);
          }
LABEL_78:
          if ( ++idx2 >= p_programparam->nSplit )
            return idx1;
        }
        if ( p_splitblock->sampleSetIndex == 0xFFFF
          || sceSdHdGetSampleSetParamAddr(buffer, p_splitblock->sampleSetIndex, &p_samplesetparam) )
        {
          goto LABEL_78;
        }
        if ( swcase - 3 >= 3 )
        {
          if ( !mode )
          {
            samplesetparam_1 = p_samplesetparam;
            if ( velocity < p_samplesetparam->velLimitLow )
              goto LABEL_78;
            if ( p_samplesetparam->velLimitHigh < velocity )
              goto LABEL_78;
            idxnsample = 0;
            if ( !p_samplesetparam->nSample )
              goto LABEL_78;
            cursampleindexoffs1 = 0;
            while ( 2 )
            {
              cursampleindex1 = (char *)samplesetparam_1 + cursampleindexoffs1;
              if ( *((unsigned __int16 *)cursampleindex1 + 2) != 0xFFFF
                && !sceSdHdGetSampleParamAddr(buffer, *((unsigned __int16 *)cursampleindex1 + 2), &p_sampleparam)
                && velocity >= (p_sampleparam->velRangeLow & 0x7Fu)
                && (p_sampleparam->velRangeHigh & 0x7Fu) >= velocity )
              {
                if ( swcase - 6 >= 3 )
                {
                  if ( p_sampleparam->VagIndex != 0xFFFF
                    && !sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, &p_vagparam) )
                  {
                    if ( swcase == 9 )
                      goto LABEL_46;
                    if ( swcase >= 9 )
                    {
                      if ( swcase == 10 )
                      {
                        ++idx1;
                        *ptr++ = p_vagparam;
                      }
                      else if ( swcase == 11 )
                      {
                        ++idx1;
                        vag_size = do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr);
                        ptr_2 = ptr;
                        ptr += 4;
                        do_copy_to_sdhd_vag_info_param((SceSdHdVAGInfoParam *)ptr_2, vag_size, p_vagparam);
                      }
                    }
                  }
                }
                else
                {
                  if ( swcase == 7 )
                  {
                    ++idx1;
                    *ptr++ = p_sampleparam;
                    goto LABEL_49;
                  }
                  if ( swcase < 8 )
                  {
                    if ( swcase != 6 )
                      goto LABEL_49;
LABEL_46:
                    ++idx1;
                    goto LABEL_49;
                  }
                  ptr_3 = ptr;
                  if ( swcase == 8 )
                  {
                    ++idx1;
                    ptr += 34;
                    do_copy_to_sdhd_sample_param((SceSdHdSampleParam *)ptr_3, p_sampleparam);
                  }
                }
              }
LABEL_49:
              samplesetparam_1 = p_samplesetparam;
              ++idxnsample;
              cursampleindexoffs1 = 2 * idxnsample;
              if ( idxnsample >= p_samplesetparam->nSample )
                goto LABEL_78;
              continue;
            }
          }
          if ( mode != 1 )
            goto LABEL_78;
          p_samplesetparam_1 = p_samplesetparam;
          nsamplecur = 0;
          if ( !p_samplesetparam->nSample )
            goto LABEL_78;
          cursampleindexoffs2 = 0;
          while ( 2 )
          {
            cursampleindex2 = (char *)p_samplesetparam_1 + cursampleindexoffs2;
            if ( *((unsigned __int16 *)cursampleindex2 + 2) != 0xFFFF
              && !sceSdHdGetSampleParamAddr(buffer, *((unsigned __int16 *)cursampleindex2 + 2), &p_sampleparam)
              && velocity >= (p_sampleparam->velRangeLow & 0x7Fu)
              && (p_sampleparam->velRangeHigh & 0x7Fu) >= velocity )
            {
              if ( swcase - 6 >= 3 )
              {
                if ( p_sampleparam->VagIndex != 0xFFFF
                  && !sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, &p_vagparam) )
                {
                  if ( swcase == 9 )
                    goto LABEL_74;
                  if ( swcase >= 9 )
                  {
                    if ( swcase == 10 )
                    {
                      ++idx1;
                      *ptr++ = p_vagparam;
                    }
                    else if ( swcase == 11 )
                    {
                      ++idx1;
                      vagsz_tmp = do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr);
                      ptr_4 = ptr;
                      ptr += 4;
                      do_copy_to_sdhd_vag_info_param((SceSdHdVAGInfoParam *)ptr_4, vagsz_tmp, p_vagparam);
                    }
                  }
                }
              }
              else
              {
                if ( swcase == 7 )
                {
                  ++idx1;
                  *ptr++ = p_sampleparam;
                  goto LABEL_77;
                }
                if ( swcase < 8 )
                {
                  if ( swcase != 6 )
                    goto LABEL_77;
LABEL_74:
                  ++idx1;
                  goto LABEL_77;
                }
                ptr_5 = ptr;
                if ( swcase == 8 )
                {
                  ++idx1;
                  ptr += 34;
                  do_copy_to_sdhd_sample_param((SceSdHdSampleParam *)ptr_5, p_sampleparam);
                }
              }
            }
LABEL_77:
            p_samplesetparam_1 = p_samplesetparam;
            ++nsamplecur;
            cursampleindexoffs2 = 2 * nsamplecur;
            if ( nsamplecur >= p_samplesetparam->nSample )
              goto LABEL_78;
            continue;
          }
        }
        if ( swcase == 4 )
        {
          ++idx1;
          *ptr++ = p_samplesetparam;
          goto LABEL_78;
        }
        if ( swcase >= 5 )
        {
          ptr_6 = ptr;
          if ( swcase == 5 )
          {
            ++idx1;
            ptr += 4;
            do_copy_to_sdhd_set_param((SceSdHdSampleSetParam *)ptr_6, p_samplesetparam);
          }
          goto LABEL_78;
        }
LABEL_18:
        ++idx1;
        goto LABEL_78;
      }
      return idx1;
    }
  }
  return result;
}
// 400A9C: conditional instruction was optimized away because $s3.4==2
// 400B10: conditional instruction was optimized away because $s3.4==3

//----- (00400F08) --------------------------------------------------------
int __fastcall do_get_common_block_ptr(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int swcase,
        unsigned int velocity,
        int mode,
        void **param)
{
  int idx1; // $s0
  bool condtmp; // dc
  int result; // $v0
  sceHardSynthSampleSetParam *p_samplesetparam_2; // $v1
  int nsampletmp2; // $s3
  int cursampleindexoffs2; // $v0
  char *cursampleindex2; // $v1
  void **param_3; // $a0
  int vagsz_tmp; // $v0
  void **param_4; // $a0
  sceHardSynthSampleSetParam *p_samplesetparam_1; // $v1
  int nsampletmp1; // $s3
  int cursampleindexoffs1; // $v0
  char *cursampleindex1; // $v1
  void **param_1; // $a0
  int vag_size; // $v0
  void **param_2; // $a0
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+10h] [-10h] BYREF
  sceHardSynthSampleParam *p_sampleparam; // [sp+14h] [-Ch] BYREF
  sceHardSynthVagParam *p_vagparam[2]; // [sp+18h] [-8h] BYREF

  idx1 = 0;
  condtmp = sceSdHdGetSampleSetParamAddr(buffer, sampleSetNumber, &p_samplesetparam) != 0;
  result = 0;
  if ( condtmp )
    return result;
  if ( mode )
  {
    result = 0;
    if ( mode != 1 )
      return result;
    p_samplesetparam_1 = p_samplesetparam;
    nsampletmp1 = 0;
    if ( !p_samplesetparam->nSample )
      return idx1;
    cursampleindexoffs1 = 0;
    while ( 1 )
    {
      cursampleindex1 = (char *)p_samplesetparam_1 + cursampleindexoffs1;
      if ( *((unsigned __int16 *)cursampleindex1 + 2) == 0xFFFF
        || sceSdHdGetSampleParamAddr(buffer, *((unsigned __int16 *)cursampleindex1 + 2), &p_sampleparam)
        || velocity < (p_sampleparam->velRangeLow & 0x7Fu)
        || (p_sampleparam->velRangeHigh & 0x7Fu) < velocity )
      {
        goto LABEL_58;
      }
      if ( swcase - 6 >= 3 )
        break;
      if ( swcase == 7 )
      {
        ++idx1;
        *param++ = p_sampleparam;
      }
      else
      {
        if ( swcase >= 8 )
        {
          param_1 = param;
          if ( swcase == 8 )
          {
            ++idx1;
            param += 34;
            do_copy_to_sdhd_sample_param((SceSdHdSampleParam *)param_1, p_sampleparam);
          }
          goto LABEL_58;
        }
        if ( swcase == 6 )
          goto LABEL_55;
      }
LABEL_58:
      p_samplesetparam_1 = p_samplesetparam;
      ++nsampletmp1;
      cursampleindexoffs1 = 2 * nsampletmp1;
      if ( nsampletmp1 >= p_samplesetparam->nSample )
        return idx1;
    }
    if ( p_sampleparam->VagIndex == 0xFFFF || sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, p_vagparam) )
      goto LABEL_58;
    if ( swcase != 9 )
    {
      if ( swcase >= 9 )
      {
        if ( swcase == 10 )
        {
          ++idx1;
          *param++ = p_vagparam[0];
        }
        else if ( swcase == 11 )
        {
          ++idx1;
          vag_size = do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam[0]->vagOffsetAddr);
          param_2 = param;
          param += 4;
          do_copy_to_sdhd_vag_info_param((SceSdHdVAGInfoParam *)param_2, vag_size, p_vagparam[0]);
        }
      }
      goto LABEL_58;
    }
LABEL_55:
    ++idx1;
    goto LABEL_58;
  }
  p_samplesetparam_2 = p_samplesetparam;
  result = 0;
  if ( velocity >= p_samplesetparam->velLimitLow )
  {
    result = 0;
    if ( p_samplesetparam->velLimitHigh >= velocity )
    {
      nsampletmp2 = 0;
      if ( p_samplesetparam->nSample )
      {
        cursampleindexoffs2 = 0;
        while ( 1 )
        {
          cursampleindex2 = (char *)p_samplesetparam_2 + cursampleindexoffs2;
          if ( *((unsigned __int16 *)cursampleindex2 + 2) == 0xFFFF
            || sceSdHdGetSampleParamAddr(buffer, *((unsigned __int16 *)cursampleindex2 + 2), &p_sampleparam)
            || velocity < (p_sampleparam->velRangeLow & 0x7Fu)
            || (p_sampleparam->velRangeHigh & 0x7Fu) < velocity )
          {
            goto LABEL_30;
          }
          if ( swcase - 6 >= 3 )
            break;
          if ( swcase == 7 )
          {
            ++idx1;
            *param++ = p_sampleparam;
          }
          else
          {
            if ( swcase >= 8 )
            {
              param_3 = param;
              if ( swcase == 8 )
              {
                ++idx1;
                param += 34;
                do_copy_to_sdhd_sample_param((SceSdHdSampleParam *)param_3, p_sampleparam);
              }
              goto LABEL_30;
            }
            if ( swcase == 6 )
              goto LABEL_27;
          }
LABEL_30:
          p_samplesetparam_2 = p_samplesetparam;
          ++nsampletmp2;
          cursampleindexoffs2 = 2 * nsampletmp2;
          if ( nsampletmp2 >= p_samplesetparam->nSample )
            return idx1;
        }
        if ( p_sampleparam->VagIndex == 0xFFFF
          || sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, p_vagparam) )
        {
          goto LABEL_30;
        }
        if ( swcase != 9 )
        {
          if ( swcase >= 9 )
          {
            if ( swcase == 10 )
            {
              ++idx1;
              *param++ = p_vagparam[0];
            }
            else if ( swcase == 11 )
            {
              ++idx1;
              vagsz_tmp = do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam[0]->vagOffsetAddr);
              param_4 = param;
              param += 4;
              do_copy_to_sdhd_vag_info_param((SceSdHdVAGInfoParam *)param_4, vagsz_tmp, p_vagparam[0]);
            }
          }
          goto LABEL_30;
        }
LABEL_27:
        ++idx1;
        goto LABEL_30;
      }
      return idx1;
    }
  }
  return result;
}

//----- (004012F0) --------------------------------------------------------
int __cdecl sceSdHdGetMaxProgramNumber(void *buffer)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_prog_chunk(buffer, &dinfo);
    if ( !result )
      return dinfo.m_prog->maxProgramNumber;
  }
  return result;
}

//----- (0040133C) --------------------------------------------------------
int __cdecl sceSdHdGetMaxSampleSetNumber(void *buffer)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_sset_chunk(buffer, &dinfo);
    if ( !result )
      return dinfo.m_sset->maxSampleSetNumber;
  }
  return result;
}

//----- (00401388) --------------------------------------------------------
int __cdecl sceSdHdGetMaxSampleNumber(void *buffer)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_smpl_chunk(buffer, &dinfo);
    if ( !result )
      return dinfo.m_smpl->maxSampleNumber;
  }
  return result;
}

//----- (004013D4) --------------------------------------------------------
int __cdecl sceSdHdGetMaxVAGInfoNumber(void *buffer)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_vagi_chunk(buffer, &dinfo);
    if ( !result )
      return dinfo.m_vagi->maxVagInfoNumber;
  }
  return result;
}

//----- (00401420) --------------------------------------------------------
int __cdecl sceSdHdGetProgramParamAddr(void *buffer, unsigned int programNumber, sceHardSynthProgramParam **ptr)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_prog_chunk(buffer, &dinfo);
    if ( !result )
    {
      result = do_check_chunk_in_bounds(buffer, &dinfo, 0x50726F67u, programNumber);
      if ( !result )
      {
        result = 0;
        *ptr = (sceHardSynthProgramParam *)((char *)dinfo.m_prog + dinfo.m_prog->programOffsetAddr[programNumber]);
      }
    }
  }
  return result;
}

//----- (004014B0) --------------------------------------------------------
int __cdecl sceSdHdGetProgramParam(void *buffer, unsigned int programNumber, SceSdHdProgramParam *param)
{
  int result; // $v0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam);
  if ( !result )
  {
    do_copy_to_sdhd_program_param(param, p_programparam);
    return 0;
  }
  return result;
}

//----- (004014F0) --------------------------------------------------------
int __cdecl sceSdHdGetSplitBlockAddr(
        void *buffer,
        unsigned int programNumber,
        unsigned int splitBlockNumber,
        sceHardSynthSplitBlock **theParamPtr)
{
  int result; // $v0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam);
  if ( !result )
  {
    if ( p_programparam->splitBlockAddr == -1 )
    {
      return 0x81039009;
    }
    else if ( (unsigned int)p_programparam->nSplit - 1 < splitBlockNumber )
    {
      return 0x81039018;
    }
    else
    {
      result = 0;
      *theParamPtr = (sceHardSynthSplitBlock *)((char *)p_programparam
                                              + p_programparam->splitBlockAddr
                                              + p_programparam->sizeSplitBlock * splitBlockNumber);
    }
  }
  return result;
}

//----- (0040158C) --------------------------------------------------------
int __cdecl sceSdHdGetSplitBlock(
        void *buffer,
        unsigned int programNumber,
        unsigned int splitBlockNumber,
        SceSdHdSplitBlock *param)
{
  int result; // $v0
  sceHardSynthSplitBlock *p_splitblock; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSplitBlockAddr(buffer, programNumber, splitBlockNumber, &p_splitblock);
  if ( !result )
  {
    do_copy_to_sdhd_split_block(param, p_splitblock);
    return 0;
  }
  return result;
}

//----- (004015CC) --------------------------------------------------------
int __cdecl sceSdHdGetSampleSetParamAddr(void *buffer, unsigned int sampleSetNumber, sceHardSynthSampleSetParam **ptr)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_sset_chunk(buffer, &dinfo);
    if ( !result )
    {
      result = do_check_chunk_in_bounds(buffer, &dinfo, 0x53736574u, sampleSetNumber);
      if ( !result )
      {
        result = 0;
        *ptr = (sceHardSynthSampleSetParam *)((char *)dinfo.m_sset + dinfo.m_sset->sampleSetOffsetAddr[sampleSetNumber]);
      }
    }
  }
  return result;
}
// 4015CC: using guessed type _DWORD dinfo[3];

//----- (0040165C) --------------------------------------------------------
int __cdecl sceSdHdGetSampleSetParam(void *buffer, unsigned int sampleSetNumber, SceSdHdSampleSetParam *param)
{
  int result; // $v0
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSampleSetParamAddr(buffer, sampleSetNumber, &p_samplesetparam);
  if ( !result )
  {
    do_copy_to_sdhd_set_param(param, p_samplesetparam);
    return 0;
  }
  return result;
}

//----- (0040169C) --------------------------------------------------------
int __cdecl sceSdHdGetSampleParamAddr(void *buffer, unsigned int sampleNumber, sceHardSynthSampleParam **ptr)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_smpl_chunk(buffer, &dinfo);
    if ( !result )
    {
      result = do_check_chunk_in_bounds(buffer, &dinfo, 0x536D706Cu, sampleNumber);
      if ( !result )
      {
        result = 0;
        *ptr = (sceHardSynthSampleParam *)((char *)dinfo.m_smpl + dinfo.m_smpl->sampleOffsetAddr[sampleNumber]);
      }
    }
  }
  return result;
}
// 40169C: using guessed type _DWORD dinfo[4];

//----- (0040172C) --------------------------------------------------------
int __cdecl sceSdHdGetSampleParam(void *buffer, unsigned int sampleNumber, SceSdHdSampleParam *param)
{
  int result; // $v0
  sceHardSynthSampleParam *p_sampleparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSampleParamAddr(buffer, sampleNumber, &p_sampleparam);
  if ( !result )
  {
    do_copy_to_sdhd_sample_param(param, p_sampleparam);
    return 0;
  }
  return result;
}

//----- (0040176C) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamAddr(void *buffer, unsigned int vagInfoNumber, sceHardSynthVagParam **ptr)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_vagi_chunk(buffer, &dinfo);
    if ( !result )
    {
      result = do_check_chunk_in_bounds(buffer, &dinfo, 0x56616769u, vagInfoNumber);
      if ( !result )
      {
        result = 0;
        *ptr = (sceHardSynthVagParam *)((char *)dinfo.m_vagi + dinfo.m_vagi->vagInfoOffsetAddr[vagInfoNumber]);
      }
    }
  }
  return result;
}
// 40176C: using guessed type _DWORD dinfo[5];

//----- (004017FC) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParam(void *buffer, unsigned int vagInfoNumber, SceSdHdVAGInfoParam *param)
{
  int result; // $v0
  int vag_size; // $v0
  sceHardSynthVagParam *p_vagparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetVAGInfoParamAddr(buffer, vagInfoNumber, &p_vagparam);
  if ( !result )
  {
    vag_size = do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr);
    do_copy_to_sdhd_vag_info_param(param, vag_size, p_vagparam);
    return 0;
  }
  return result;
}

//----- (00401858) --------------------------------------------------------
int __cdecl sceSdHdCheckProgramNumber(void *buffer, unsigned int programNumber)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_prog_chunk(buffer, &dinfo);
    if ( !result )
      return do_check_chunk_in_bounds(buffer, &dinfo, 0x50726F67u, programNumber);
  }
  return result;
}

//----- (004018B8) --------------------------------------------------------
int __cdecl sceSdHdGetSplitBlockCountByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 0, noteNumber, 0, 0, 0);
}

//----- (004018E8) --------------------------------------------------------
int __cdecl sceSdHdGetSplitBlockAddrByNote(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        sceHardSynthSplitBlock **ptr)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 1u, noteNumber, 0, 0, (void **)ptr);
}

//----- (0040191C) --------------------------------------------------------
int __cdecl sceSdHdGetSplitBlockByNote(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        SceSdHdSplitBlock *param)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 2u, noteNumber, 0, 0, (void **)param);
}

//----- (00401950) --------------------------------------------------------
int __cdecl sceSdHdGetSampleSetParamCountByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 3u, noteNumber, 0, 0, 0);
}

//----- (00401980) --------------------------------------------------------
int __cdecl sceSdHdGetSampleSetParamAddrByNote(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        sceHardSynthSampleSetParam **ptr)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 4u, noteNumber, 0, 0, (void **)ptr);
}

//----- (004019B4) --------------------------------------------------------
int __cdecl sceSdHdGetSampleSetParamByNote(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        SceSdHdSampleSetParam *param)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 5u, noteNumber, 0, 0, (void **)param);
}

//----- (004019E8) --------------------------------------------------------
int __cdecl sceSdHdGetSampleParamCountByNoteVelocity(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        unsigned int velocity,
        unsigned int mode)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 6u, noteNumber, velocity, mode, 0);
}

//----- (00401A20) --------------------------------------------------------
int __cdecl sceSdHdGetSampleParamAddrByNoteVelocity(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        unsigned int velocity,
        unsigned int mode,
        sceHardSynthSampleParam **ptr)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 7u, noteNumber, velocity, mode, (void **)ptr);
}

//----- (00401A5C) --------------------------------------------------------
int __cdecl sceSdHdGetSampleParamByNoteVelocity(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        unsigned int velocity,
        unsigned int mode,
        SceSdHdSampleParam *param)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 8u, noteNumber, velocity, mode, (void **)param);
}

//----- (00401A98) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamCountByNoteVelocity(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        unsigned int velocity,
        unsigned int mode)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 9u, noteNumber, velocity, mode, 0);
}

//----- (00401AD0) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamAddrByNoteVelocity(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        unsigned int velocity,
        unsigned int mode,
        sceHardSynthVagParam **ptr)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 0xAu, noteNumber, velocity, mode, (void **)ptr);
}

//----- (00401B0C) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamByNoteVelocity(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        unsigned int velocity,
        unsigned int mode,
        SceSdHdVAGInfoParam *param)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 0xBu, noteNumber, velocity, mode, (void **)param);
}

//----- (00401B48) --------------------------------------------------------
int __cdecl sceSdHdGetSampleParamCountByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 6u, velocity, mode, 0);
}

//----- (00401B78) --------------------------------------------------------
int __cdecl sceSdHdGetSampleParamAddrByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode,
        sceHardSynthSampleParam **ptr)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 7u, velocity, mode, (void **)ptr);
}

//----- (00401BAC) --------------------------------------------------------
int __cdecl sceSdHdGetSampleParamByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode,
        SceSdHdSampleParam *param)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 8u, velocity, mode, (void **)param);
}

//----- (00401BE0) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamCountByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 9u, velocity, mode, 0);
}

//----- (00401C10) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamAddrByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode,
        sceHardSynthVagParam **ptr)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 0xAu, velocity, mode, (void **)ptr);
}

//----- (00401C44) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode,
        SceSdHdVAGInfoParam *param)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 0xBu, velocity, mode, (void **)param);
}

//----- (00401C78) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamAddrBySampleNumber(
        void *buffer,
        unsigned int sampleNumber,
        sceHardSynthVagParam **ptr)
{
  int result; // $v0
  sceHardSynthSampleParam *p_sampleparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSampleParamAddr(buffer, sampleNumber, &p_sampleparam);
  if ( !result )
  {
    if ( p_sampleparam->VagIndex == 0xFFFF )
      return 0x81039019;
    else
      return sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, ptr);
  }
  return result;
}

//----- (00401CE8) --------------------------------------------------------
int __cdecl sceSdHdGetVAGInfoParamBySampleNumber(void *buffer, unsigned int sampleNumber, SceSdHdVAGInfoParam *param)
{
  int result; // $v0
  int vag_size; // $v0
  sceHardSynthVagParam *p_vagparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetVAGInfoParamAddrBySampleNumber(buffer, sampleNumber, &p_vagparam);
  if ( !result )
  {
    vag_size = do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr);
    do_copy_to_sdhd_vag_info_param(param, vag_size, p_vagparam);
    return 0;
  }
  return result;
}

//----- (00401D44) --------------------------------------------------------
int __cdecl sceSdHdGetSplitBlockNumberBySplitNumber(void *buffer, unsigned int programNumber, unsigned int splitNumber)
{
  int result; // $v0
  int idx1; // $v1
  sceHardSynthSplitBlock *splitblock; // $a0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam);
  if ( !result )
  {
    if ( p_programparam->splitBlockAddr == -1 )
    {
      return 0x81039009;
    }
    else
    {
      idx1 = 0;
      if ( p_programparam->nSplit )
      {
        splitblock = (sceHardSynthSplitBlock *)((char *)p_programparam + p_programparam->splitBlockAddr);
        while ( 1 )
        {
          result = idx1;
          if ( splitNumber == splitblock->splitNumber )
            break;
          ++idx1;
          splitblock = (sceHardSynthSplitBlock *)((char *)splitblock + p_programparam->sizeSplitBlock);
          if ( idx1 >= p_programparam->nSplit )
            return 0x81039020;
        }
      }
      else
      {
        return 0x81039020;
      }
    }
  }
  return result;
}

//----- (00401DD8) --------------------------------------------------------
int __cdecl sceSdHdGetVAGSize(void *buffer, unsigned int vagInfoNumber)
{
  int result; // $v0
  sceHardSynthVagParam *p_vagparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetVAGInfoParamAddr(buffer, vagInfoNumber, &p_vagparam);
  if ( !result )
    return do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr);
  return result;
}

//----- (00401E14) --------------------------------------------------------
int __cdecl sceSdHdGetSplitBlockCount(void *buffer, unsigned int programNumber)
{
  int result; // $v0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam);
  if ( !result )
    return p_programparam->nSplit;
  return result;
}

//----- (00401E48) --------------------------------------------------------
int __cdecl sceSdHdGetMaxSplitBlockCount(void *buffer)
{
  int curminval; // $s2
  int result; // $v0
  int retres; // $s4
  signed int programNr; // $s1
  void *buffer_1; // $a0
  signed int curidx2; // $s0
  void *buffer_2; // $a0
  int curval1; // $v1
  int curval2; // $v1
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF
  sceHardSynthSplitBlock *p_splitblock; // [sp+14h] [-4h] BYREF

  curminval = 0;
  result = sceSdHdGetMaxProgramNumber(buffer);
  retres = result;
  programNr = 0;
  if ( result >= 0 )
  {
    buffer_1 = buffer;
    do
    {
      if ( !sceSdHdGetProgramParamAddr(buffer_1, programNr, &p_programparam) )
      {
        curidx2 = 0;
        if ( p_programparam->nSplit )
        {
          buffer_2 = buffer;
          do
          {
            if ( !sceSdHdGetSplitBlockAddr(buffer_2, programNr, curidx2, &p_splitblock) )
            {
              curval1 = sceSdHdGetSplitBlockCountByNote(buffer, programNr, p_splitblock->splitRangeLow & 0x7F);
              if ( curminval < curval1 )
                curminval = curval1;
              curval2 = sceSdHdGetSplitBlockCountByNote(buffer, programNr, p_splitblock->splitRangeHigh & 0x7F);
              if ( curminval < curval2 )
                curminval = curval2;
            }
            ++curidx2;
            buffer_2 = buffer;
          }
          while ( curidx2 < p_programparam->nSplit );
        }
      }
      ++programNr;
      buffer_1 = buffer;
    }
    while ( retres >= programNr );
    return curminval;
  }
  return result;
}

//----- (00401F70) --------------------------------------------------------
int __cdecl sceSdHdGetMaxSampleSetParamCount(void *buffer)
{
  int curminval; // $s2
  int result; // $v0
  int retres; // $s4
  signed int programNr; // $s1
  void *buffer_1; // $a0
  signed int curidx2; // $s0
  void *buffer_2; // $a0
  int curval1; // $v1
  int curval2; // $v1
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF
  sceHardSynthSplitBlock *p_splitblock; // [sp+14h] [-4h] BYREF

  curminval = 0;
  result = sceSdHdGetMaxProgramNumber(buffer);
  retres = result;
  programNr = 0;
  if ( result >= 0 )
  {
    buffer_1 = buffer;
    do
    {
      if ( !sceSdHdGetProgramParamAddr(buffer_1, programNr, &p_programparam) )
      {
        curidx2 = 0;
        if ( p_programparam->nSplit )
        {
          buffer_2 = buffer;
          do
          {
            if ( !sceSdHdGetSplitBlockAddr(buffer_2, programNr, curidx2, &p_splitblock) )
            {
              curval1 = sceSdHdGetSampleSetParamCountByNote(buffer, programNr, p_splitblock->splitRangeLow & 0x7F);
              if ( curminval < curval1 )
                curminval = curval1;
              curval2 = sceSdHdGetSampleSetParamCountByNote(buffer, programNr, p_splitblock->splitRangeHigh & 0x7F);
              if ( curminval < curval2 )
                curminval = curval2;
            }
            ++curidx2;
            buffer_2 = buffer;
          }
          while ( curidx2 < p_programparam->nSplit );
        }
      }
      ++programNr;
      buffer_1 = buffer;
    }
    while ( retres >= programNr );
    return curminval;
  }
  return result;
}

//----- (00402098) --------------------------------------------------------
int __cdecl sceSdHdGetMaxSampleParamCount(void *buffer)
{
  int curminval; // $s0
  int result; // $v0
  int retres; // $s6
  signed int programNr; // $s2
  void *buffer_1; // $a0
  signed int curidx2; // $s4
  void *buffer_2; // $a0
  signed int sampleNr; // $s1
  int SampleNumberBySampleIndex; // $v0
  int curval1; // $v1
  int curval2; // $v1
  int curval3; // $v1
  int curval4; // $v1
  sceHardSynthProgramParam *p_programparam; // [sp+18h] [-10h] BYREF
  sceHardSynthSplitBlock *p_splitblock; // [sp+1Ch] [-Ch] BYREF
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+20h] [-8h] BYREF
  sceHardSynthSampleParam *p_sampleparam; // [sp+24h] [-4h] BYREF

  curminval = 0;
  result = sceSdHdGetMaxProgramNumber(buffer);
  retres = result;
  programNr = 0;
  if ( result >= 0 )
  {
    buffer_1 = buffer;
    do
    {
      if ( !sceSdHdGetProgramParamAddr(buffer_1, programNr, &p_programparam) )
      {
        curidx2 = 0;
        if ( p_programparam->nSplit )
        {
          buffer_2 = buffer;
          do
          {
            if ( !sceSdHdGetSplitBlockAddr(buffer_2, programNr, curidx2, &p_splitblock)
              && !sceSdHdGetSampleSetParamAddr(buffer, p_splitblock->sampleSetIndex, &p_samplesetparam) )
            {
              sampleNr = 0;
              if ( p_samplesetparam->nSample )
              {
                do
                {
                  SampleNumberBySampleIndex = sceSdHdGetSampleNumberBySampleIndex(
                                                buffer,
                                                p_splitblock->sampleSetIndex,
                                                sampleNr);
                  if ( !sceSdHdGetSampleParamAddr(buffer, SampleNumberBySampleIndex, &p_sampleparam) )
                  {
                    curval1 = sceSdHdGetSampleParamCountByNoteVelocity(
                                buffer,
                                programNr,
                                p_splitblock->splitRangeLow & 0x7F,
                                p_sampleparam->velRangeLow & 0x7F,
                                1u);
                    if ( curminval < curval1 )
                      curminval = curval1;
                    curval2 = sceSdHdGetSampleParamCountByNoteVelocity(
                                buffer,
                                programNr,
                                p_splitblock->splitRangeLow & 0x7F,
                                p_sampleparam->velRangeHigh & 0x7F,
                                1u);
                    if ( curminval < curval2 )
                      curminval = curval2;
                    curval3 = sceSdHdGetSampleParamCountByNoteVelocity(
                                buffer,
                                programNr,
                                p_splitblock->splitRangeHigh & 0x7F,
                                p_sampleparam->velRangeLow & 0x7F,
                                1u);
                    if ( curminval < curval3 )
                      curminval = curval3;
                    curval4 = sceSdHdGetSampleParamCountByNoteVelocity(
                                buffer,
                                programNr,
                                p_splitblock->splitRangeHigh & 0x7F,
                                p_sampleparam->velRangeHigh & 0x7F,
                                1u);
                    if ( curminval < curval4 )
                      curminval = curval4;
                  }
                  ++sampleNr;
                }
                while ( sampleNr < p_samplesetparam->nSample );
              }
            }
            ++curidx2;
            buffer_2 = buffer;
          }
          while ( curidx2 < p_programparam->nSplit );
        }
      }
      ++programNr;
      buffer_1 = buffer;
    }
    while ( retres >= programNr );
    return curminval;
  }
  return result;
}

//----- (004022D8) --------------------------------------------------------
int __cdecl sceSdHdGetMaxVAGInfoParamCount(void *buffer)
{
  int curminval; // $s0
  int result; // $v0
  int retres; // $s6
  signed int programNr; // $s2
  void *buffer_1; // $a0
  signed int curidx2; // $s4
  void *buffer_2; // $a0
  signed int sampleNr; // $s1
  int SampleNumberBySampleIndex; // $v0
  int curval1; // $v1
  int curval2; // $v1
  int curval3; // $v1
  int curval4; // $v1
  sceHardSynthProgramParam *p_programparam; // [sp+18h] [-10h] BYREF
  sceHardSynthSplitBlock *p_splitblock; // [sp+1Ch] [-Ch] BYREF
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+20h] [-8h] BYREF
  sceHardSynthSampleParam *p_sampleparam; // [sp+24h] [-4h] BYREF

  curminval = 0;
  result = sceSdHdGetMaxProgramNumber(buffer);
  retres = result;
  programNr = 0;
  if ( result >= 0 )
  {
    buffer_1 = buffer;
    do
    {
      if ( !sceSdHdGetProgramParamAddr(buffer_1, programNr, &p_programparam) )
      {
        curidx2 = 0;
        if ( p_programparam->nSplit )
        {
          buffer_2 = buffer;
          do
          {
            if ( !sceSdHdGetSplitBlockAddr(buffer_2, programNr, curidx2, &p_splitblock)
              && !sceSdHdGetSampleSetParamAddr(buffer, p_splitblock->sampleSetIndex, &p_samplesetparam) )
            {
              sampleNr = 0;
              if ( p_samplesetparam->nSample )
              {
                do
                {
                  SampleNumberBySampleIndex = sceSdHdGetSampleNumberBySampleIndex(
                                                buffer,
                                                p_splitblock->sampleSetIndex,
                                                sampleNr);
                  if ( !sceSdHdGetSampleParamAddr(buffer, SampleNumberBySampleIndex, &p_sampleparam) )
                  {
                    curval1 = sceSdHdGetVAGInfoParamCountByNoteVelocity(
                                buffer,
                                programNr,
                                p_splitblock->splitRangeLow & 0x7F,
                                p_sampleparam->velRangeLow & 0x7F,
                                1u);
                    if ( curminval < curval1 )
                      curminval = curval1;
                    curval2 = sceSdHdGetVAGInfoParamCountByNoteVelocity(
                                buffer,
                                programNr,
                                p_splitblock->splitRangeLow & 0x7F,
                                p_sampleparam->velRangeHigh & 0x7F,
                                1u);
                    if ( curminval < curval2 )
                      curminval = curval2;
                    curval3 = sceSdHdGetVAGInfoParamCountByNoteVelocity(
                                buffer,
                                programNr,
                                p_splitblock->splitRangeHigh & 0x7F,
                                p_sampleparam->velRangeLow & 0x7F,
                                1u);
                    if ( curminval < curval3 )
                      curminval = curval3;
                    curval4 = sceSdHdGetVAGInfoParamCountByNoteVelocity(
                                buffer,
                                programNr,
                                p_splitblock->splitRangeHigh & 0x7F,
                                p_sampleparam->velRangeHigh & 0x7F,
                                1u);
                    if ( curminval < curval4 )
                      curminval = curval4;
                  }
                  ++sampleNr;
                }
                while ( sampleNr < p_samplesetparam->nSample );
              }
            }
            ++curidx2;
            buffer_2 = buffer;
          }
          while ( curidx2 < p_programparam->nSplit );
        }
      }
      ++programNr;
      buffer_1 = buffer;
    }
    while ( retres >= programNr );
    return curminval;
  }
  return result;
}

//----- (00402518) --------------------------------------------------------
int __cdecl sceSdHdModifyVelocity(unsigned int curveType, int velocity)
{
  int retone; // $a0
  int retval1; // $a0
  unsigned int calc4; // $a1
  unsigned int calc5; // $v0
  unsigned int calc6; // $a0

  switch ( curveType )
  {
    case 1u:
      return 128 - velocity;
    case 2u:
      goto LABEL_10;
    case 3u:
      retval1 = 1;
      calc4 = velocity * velocity / 0x7Fu;
      if ( calc4 )
        retval1 = calc4;
      return 128 - retval1;
    case 4u:
      calc5 = (128 - velocity) * (128 - velocity);
      calc6 = 1;
      if ( ((calc5 / 0x7F) & 0x3FFFFFF) != 0 )
        calc6 = (calc5 / 0x7F) & 0x3FFFFFF;
      return 128 - calc6;
    case 5u:
      velocity = 128 - velocity;
LABEL_10:
      retone = 1;
      velocity = velocity * velocity / 0x7Fu;
      if ( velocity )
        return velocity;
      return retone;
    default:
      return velocity;
  }
}

//----- (0040261C) --------------------------------------------------------
int __cdecl sceSdHdModifyVelocityLFO(unsigned int curveType, int velocity, int center)
{
  int calc3; // $v1
  int calc4; // $v0
  int calc5; // $v1
  int calc6; // $v1
  int calc7; // $v0
  int calc8; // $v0
  int calc9; // $v1
  int calca; // $v0
  int calcb; // $v1
  int calcc; // $v0
  int calcd; // $lo
  int calce; // $v1
  int calcf; // $v0
  int calcg; // $v1

  if ( center >= 0 )
  {
    if ( center >= 128 )
      center = 127;
  }
  else
  {
    center = 0;
  }
  if ( velocity >= 0 )
  {
    if ( velocity >= 128 )
      velocity = 127;
  }
  else
  {
    velocity = 0;
  }
  switch ( curveType )
  {
    case 1u:
      calc3 = center - velocity;
      goto LABEL_65;
    case 2u:
      calc4 = ((velocity - 1) << 15) / 126 * (((velocity - 1) << 15) / 126)
            - ((center - 1) << 15) / 126 * (((center - 1) << 15) / 126);
      goto LABEL_39;
    case 3u:
      calc5 = ((velocity - 1) << 15) / 126 * (((velocity - 1) << 15) / 126) / -16384
            - ((center - 1) << 15) / 126 * (((center - 1) << 15) / 126) / -16384;
      goto LABEL_67;
    case 4u:
      calc5 = (0x10000 - ((center - 1) << 15) / 126) * (0x10000 - ((center - 1) << 15) / 126) / 0x4000
            - (0x10000 - ((velocity - 1) << 15) / 126) * (0x10000 - ((velocity - 1) << 15) / 126) / 0x4000;
      goto LABEL_67;
    case 5u:
      calc5 = (0x10000 - ((velocity - 1) << 15) / 126) * (0x10000 - ((velocity - 1) << 15) / 126) / 0x4000
            - (0x10000 - ((center - 1) << 15) / 126) * (0x10000 - ((center - 1) << 15) / 126) / 0x4000;
      goto LABEL_67;
    case 6u:
      if ( velocity == center )
        goto LABEL_48;
      if ( center >= velocity )
        calc6 = center - 1;
      else
        calc6 = 127 - center;
      calc7 = velocity - center;
      goto LABEL_25;
    case 7u:
      if ( velocity == center )
        goto LABEL_48;
      if ( center >= velocity )
        calc6 = center - 1;
      else
        calc6 = 127 - center;
      calc7 = center - velocity;
LABEL_25:
      calc8 = calc7 << 16;
      if ( !calc6 )
        _break(7u, 0);
      if ( calc6 == -1 && calc8 == 0x80000000 )
        _break(6u, 0);
      calc5 = calc8 / calc6;
      goto LABEL_67;
    case 8u:
      if ( velocity == center )
        goto LABEL_48;
      calc9 = (velocity - center) << 15;
      if ( center >= velocity )
      {
        if ( center == 1 )
          _break(7u, 0);
        if ( !center && calc9 == 0x80000000 )
          _break(6u, 0);
        calc5 = calc9 / (center - 1) * (calc9 / (center - 1)) / -16384;
      }
      else
      {
        calca = 127 - center;
        if ( 127 == center )
          _break(7u, 0);
        if ( calca == -1 && calc9 == 0x80000000 )
          _break(6u, 0);
        calc4 = calc9 / calca * (calc9 / calca);
LABEL_39:
        calc5 = calc4 >> 14;
        if ( calc4 < 0 )
          calc5 = (calc4 + 0x3FFF) >> 14;
      }
      goto LABEL_67;
    case 9u:
      if ( velocity == center )
      {
LABEL_48:
        calc5 = 0;
      }
      else
      {
        calcb = (velocity - center) << 15;
        if ( center >= velocity )
        {
          if ( center == 1 )
            _break(7u, 0);
          if ( !center && calcb == 0x80000000 )
            _break(6u, 0);
          calc5 = (calcb / (center - 1) + 0x8000) * (calcb / (center - 1) + 0x8000) / 0x4000 - 0x10000;
        }
        else
        {
          calcc = 127 - center;
          if ( 127 == center )
            _break(7u, 0);
          if ( calcc == -1 && calcb == 0x80000000 )
            _break(6u, 0);
          calcd = (0x8000 - calcb / calcc) * (0x8000 - calcb / calcc);
          calce = calcd >> 14;
          if ( calcd < 0 )
            calce = (calcd + 0x3FFF) >> 14;
          calcf = 0x10000;
LABEL_66:
          calc5 = calcf - calce;
        }
      }
LABEL_67:
      if ( calc5 < -65536 )
        return -65536;
      if ( calc5 > 0xFFFF )
        return 0xFFFF;
      return calc5;
    default:
      calc3 = velocity - center;
LABEL_65:
      calcg = calc3 << 16;
      calcf = (int)((unsigned __int64)(2181570691LL * calcg) >> 32) >> 6;
      calce = calcg >> 31;
      goto LABEL_66;
  }
}

//----- (00402AD0) --------------------------------------------------------
int __cdecl sceSdHdGetValidProgramNumberCount(void *buffer)
{
  int validcnt; // $s0
  int result; // $v0
  unsigned int allcnt; // $a0
  sceHardSynthProgramChunk *curoffsaddr; // $v1
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  validcnt = 0;
  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_prog_chunk(buffer, &dinfo);
    if ( !result )
    {
      allcnt = 0;
      curoffsaddr = dinfo.m_prog;
      do
      {
        if ( curoffsaddr->programOffsetAddr[0] != -1 )
          ++validcnt;
        ++allcnt;
        curoffsaddr = (sceHardSynthProgramChunk *)((char *)curoffsaddr + 4);
      }
      while ( dinfo.m_prog->maxProgramNumber >= allcnt );
      return validcnt;
    }
  }
  return result;
}
// 402AD0: using guessed type _DWORD dinfo[2];

//----- (00402B5C) --------------------------------------------------------
int __cdecl sceSdHdGetValidProgramNumber(void *buffer, unsigned int *ptr)
{
  int validcnt; // $s1
  int result; // $v0
  unsigned int allcnt; // $v1
  sceHardSynthProgramChunk *curprog; // $a0
  int xcurind; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  validcnt = 0;
  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( !result )
  {
    result = do_get_prog_chunk(buffer, &dinfo);
    if ( !result )
    {
      allcnt = 0;
      curprog = dinfo.m_prog;
      xcurind = 0;
      do
      {
        if ( curprog->programOffsetAddr[xcurind] != -1 )
        {
          ++validcnt;
          *ptr++ = allcnt;
        }
        curprog = dinfo.m_prog;
        xcurind = ++allcnt;
      }
      while ( dinfo.m_prog->maxProgramNumber >= allcnt );
      return validcnt;
    }
  }
  return result;
}
// 402B5C: using guessed type _DWORD dinfo[2];

//----- (00402C08) --------------------------------------------------------
int __cdecl sceSdHdGetSampleNumberBySampleIndex(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int sampleIndexNumber)
{
  int result; // $v0
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSampleSetParamAddr(buffer, sampleSetNumber, &p_samplesetparam);
  if ( !result )
  {
    result = 0x9006;
    if ( (unsigned int)p_samplesetparam->nSample - 1 >= sampleIndexNumber )
      return p_samplesetparam->sampleIndex[sampleIndexNumber];
  }
  return result;
}

//----- (00402C70) --------------------------------------------------------
int __fastcall _start(int ac)
{
  int unregres; // $s0
  int result; // $v0
  int regres; // $s0
  int state[2]; // [sp+10h] [-8h] BYREF

  if ( ac >= 0 )
  {
    CpuSuspendIntr(state);
    regres = RegisterLibraryEntries((struct irx_export_table *)&exports);
    CpuResumeIntr(state[0]);
    result = 1;
    if ( !regres )
      return 2;
  }
  else
  {
    CpuSuspendIntr(state);
    unregres = ReleaseLibraryEntries((struct irx_export_table *)&exports);
    CpuResumeIntr(state[0]);
    result = 2;
    if ( !unregres )
      return 1;
  }
  return result;
}
