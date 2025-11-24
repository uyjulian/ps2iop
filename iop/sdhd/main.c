
#include "irx_imports.h"

IRX_ID("Sound_Data_HD", 2, 2);

struct sceHardSynthVersionChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  u16 reserved;
  u8 versionMajor;
  u8 versionMinor;
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
  u16 sampleSetIndex;
  u8 splitRangeLow;
  u8 splitCrossFade;
  u8 splitRangeHigh;
  u8 splitNumber;
  u16 splitBendRangeLow;
  u16 splitBendRangeHigh;
  char keyFollowPitch;
  u8 keyFollowPitchCenter;
  char keyFollowAmp;
  u8 keyFollowAmpCenter;
  char keyFollowPan;
  u8 keyFollowPanCenter;
  u8 splitVolume;
  char splitPanpot;
  char splitTranspose;
  char splitDetune;
} sceHardSynthSplitBlock;

typedef struct sceHardSynthProgramParam_
{
  unsigned int splitBlockAddr;
  u8 nSplit;
  u8 sizeSplitBlock;
  u8 progVolume;
  char progPanpot;
  char progTranspose;
  char progDetune;
  char keyFollowPan;
  u8 keyFollowPanCenter;
  u8 progAttr;
  u8 dmy;
  u8 progLfoWave;
  u8 progLfoWave2;
  u8 progLfoStartPhase;
  u8 progLfoStartPhase2;
  u8 progLfoPhaseRandom;
  u8 progLfoPhaseRandom2;
  u16 progLfoFreq;
  u16 progLfoFreq2;
  s16 progLfoPitchDepth;
  s16 progLfoPitchDepth2;
  s16 progLfoMidiPitchDepth;
  s16 progLfoMidiPitchDepth2;
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
  u8 velCurve;
  u8 velLimitLow;
  u8 velLimitHigh;
  u8 nSample;
  u16 sampleIndex[];
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
  u16 VagIndex;
  u8 velRangeLow;
  u8 velCrossFade;
  u8 velRangeHigh;
  char velFollowPitch;
  u8 velFollowPitchCenter;
  u8 velFollowPitchVelCurve;
  char velFollowAmp;
  u8 velFollowAmpCenter;
  u8 velFollowAmpVelCurve;
  u8 sampleBaseNote;
  char sampleDetune;
  char samplePanpot;
  u8 sampleGroup;
  u8 samplePriority;
  u8 sampleVolume;
  u8 dmy;
  u16 sampleAdsr1;
  u16 sampleAdsr2;
  char keyFollowAr;
  u8 keyFollowArCenter;
  char keyFollowDr;
  u8 keyFollowDrCenter;
  char keyFollowSr;
  u8 keyFollowSrCenter;
  char keyFollowRr;
  u8 keyFollowRrCenter;
  char keyFollowSl;
  u8 keyFollowSlCenter;
  u16 samplePitchLfoDelay;
  u16 samplePitchLfoFade;
  u16 sampleAmpLfoDelay;
  u16 sampleAmpLfoFade;
  u8 sampleLfoAttr;
  u8 sampleSpuAttr;
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
  u16 vagSampleRate;
  u8 vagAttribute;
  u8 dmy;
} sceHardSynthVagParam;

//-------------------------------------------------------------------------
// Function declarations

int do_get_vers_head_chunk(sceHardSynthVersionChunk *indata, struct sdhd_info *dinfo);
int do_get_prog_chunk(void *indata, struct sdhd_info *dinfo);
int do_get_sset_chunk(void *indata, struct sdhd_info *dinfo);
int do_get_smpl_chunk(void *indata, struct sdhd_info *dinfo);
int do_get_vagi_chunk(void *indata, struct sdhd_info *dinfo);
void do_copy_to_sdhd_program_param(SceSdHdProgramParam *dst, const sceHardSynthProgramParam *src);
void do_copy_to_sdhd_split_block(SceSdHdSplitBlock *dst, const sceHardSynthSplitBlock *src);
void do_copy_to_sdhd_set_param(SceSdHdSampleSetParam *dst, const sceHardSynthSampleSetParam *src);
void do_copy_to_sdhd_sample_param(SceSdHdSampleParam *dst, const sceHardSynthSampleParam *src);
void do_copy_to_sdhd_vag_info_param(SceSdHdVAGInfoParam *dst, int sz, const sceHardSynthVagParam *src);
unsigned int do_get_vag_size(sceHardSynthVersionChunk *indata, const unsigned int *vagoffsaddr);
unsigned int do_check_chunk_in_bounds(void *indata, const struct sdhd_info *dinfo, unsigned int hdrmagic, unsigned int idx);
int do_get_common_block_ptr_note(void *buffer, unsigned int programNumber, unsigned int swcase, unsigned int noteNumber, unsigned int velocity, int mode, void **ptr);
int do_get_common_block_ptr(void *buffer, unsigned int sampleSetNumber, unsigned int swcase, unsigned int velocity, int mode, void **param);
int sceSdHdGetMaxProgramNumber(void *buffer);
int sceSdHdGetMaxSampleSetNumber(void *buffer);
int sceSdHdGetMaxSampleNumber(void *buffer);
int sceSdHdGetMaxVAGInfoNumber(void *buffer);
int sceSdHdGetProgramParamAddr(void *buffer, unsigned int programNumber, sceHardSynthProgramParam **ptr);
int sceSdHdGetProgramParam(void *buffer, unsigned int programNumber, SceSdHdProgramParam *param);
int sceSdHdGetSplitBlockAddr(void *buffer, unsigned int programNumber, unsigned int splitBlockNumber, sceHardSynthSplitBlock **theParamPtr);
int sceSdHdGetSplitBlock(void *buffer, unsigned int programNumber, unsigned int splitBlockNumber, SceSdHdSplitBlock *param);
int sceSdHdGetSampleSetParamAddr(void *buffer, unsigned int sampleSetNumber, sceHardSynthSampleSetParam **ptr);
int sceSdHdGetSampleSetParam(void *buffer, unsigned int sampleSetNumber, SceSdHdSampleSetParam *param);
int sceSdHdGetSampleParamAddr(void *buffer, unsigned int sampleNumber, sceHardSynthSampleParam **ptr);
int sceSdHdGetSampleParam(void *buffer, unsigned int sampleNumber, SceSdHdSampleParam *param);
int sceSdHdGetVAGInfoParamAddr(void *buffer, unsigned int vagInfoNumber, sceHardSynthVagParam **ptr);
int sceSdHdGetVAGInfoParam(void *buffer, unsigned int vagInfoNumber, SceSdHdVAGInfoParam *param);
int sceSdHdCheckProgramNumber(void *buffer, unsigned int programNumber);
int sceSdHdGetSplitBlockCountByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber);
int sceSdHdGetSplitBlockAddrByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber, sceHardSynthSplitBlock **ptr);
int sceSdHdGetSplitBlockByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber, SceSdHdSplitBlock *param);
int sceSdHdGetSampleSetParamCountByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber);
int sceSdHdGetSampleSetParamAddrByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber, sceHardSynthSampleSetParam **ptr);
int sceSdHdGetSampleSetParamByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber, SceSdHdSampleSetParam *param);
int sceSdHdGetSampleParamCountByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode);
int sceSdHdGetSampleParamAddrByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode, sceHardSynthSampleParam **ptr);
int sceSdHdGetSampleParamByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode, SceSdHdSampleParam *param);
int sceSdHdGetVAGInfoParamCountByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode);
int sceSdHdGetVAGInfoParamAddrByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode, sceHardSynthVagParam **ptr);
int sceSdHdGetVAGInfoParamByNoteVelocity(void *buffer, unsigned int programNumber, unsigned int noteNumber, unsigned int velocity, unsigned int mode, SceSdHdVAGInfoParam *param);
int sceSdHdGetSampleParamCountByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode);
int sceSdHdGetSampleParamAddrByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode, sceHardSynthSampleParam **ptr);
int sceSdHdGetSampleParamByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode, SceSdHdSampleParam *param);
int sceSdHdGetVAGInfoParamCountByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode);
int sceSdHdGetVAGInfoParamAddrByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode, sceHardSynthVagParam **ptr);
int sceSdHdGetVAGInfoParamByVelocity(void *buffer, unsigned int sampleSetNumber, unsigned int velocity, unsigned int mode, SceSdHdVAGInfoParam *param);
int sceSdHdGetVAGInfoParamAddrBySampleNumber(void *buffer, unsigned int sampleNumber, sceHardSynthVagParam **ptr);
int sceSdHdGetVAGInfoParamBySampleNumber(void *buffer, unsigned int sampleNumber, SceSdHdVAGInfoParam *param);
int sceSdHdGetSplitBlockNumberBySplitNumber(void *buffer, unsigned int programNumber, unsigned int splitNumber);
int sceSdHdGetVAGSize(void *buffer, unsigned int vagInfoNumber);
int sceSdHdGetSplitBlockCount(void *buffer, unsigned int programNumber);
int sceSdHdGetMaxSplitBlockCount(void *buffer);
int sceSdHdGetMaxSampleSetParamCount(void *buffer);
int sceSdHdGetMaxSampleParamCount(void *buffer);
int sceSdHdGetMaxVAGInfoParamCount(void *buffer);
int sceSdHdModifyVelocity(unsigned int curveType, int velocity);
int sceSdHdModifyVelocityLFO(unsigned int curveType, int velocity, int center);
int sceSdHdGetValidProgramNumberCount(void *buffer);
int sceSdHdGetValidProgramNumber(void *buffer, unsigned int *ptr);
int sceSdHdGetSampleNumberBySampleIndex(void *buffer, unsigned int sampleSetNumber, unsigned int sampleIndexNumber);
int _start(int ac);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_sdhd;

//----- (004000F0) --------------------------------------------------------
int do_get_vers_head_chunk(sceHardSynthVersionChunk *indata, struct sdhd_info *dinfo)
{
  dinfo->m_vers = 0;
  dinfo->m_head = 0;
  dinfo->m_prog = 0;
  dinfo->m_sset = 0;
  dinfo->m_smpl = 0;
  dinfo->m_vagi = 0;
  dinfo->m_vers = indata;
  if ( indata->Creator != 0x53434549 || indata->Type != 0x56657273 )
  {
    dinfo->m_vers = 0;
    return 0x8103000E;
  }
  if ( (indata->chunkSize & 0x80000000) )
  {
    dinfo->m_vers = 0;
    return 0x8103002F;
  }
  dinfo->m_head = (sceHardSynthHeaderChunk *)((char *)indata + indata->chunkSize);
  if ( dinfo->m_head->Creator != 0x53434549 || dinfo->m_head->Type != 0x48656164 )
  {
    dinfo->m_vers = 0;
    dinfo->m_head = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (004001A0) --------------------------------------------------------
int do_get_prog_chunk(void *indata, struct sdhd_info *dinfo)
{
  if ( dinfo->m_head->programChunkAddr == 0xFFFFFFFF )
    return 0x81039005;
  if ( (dinfo->m_head->programChunkAddr & 0x80000000) )
    return 0x8103002F;
  dinfo->m_prog = (sceHardSynthProgramChunk *)((char *)indata + dinfo->m_head->programChunkAddr);
  if ( dinfo->m_prog->Creator != 0x53434549 || dinfo->m_prog->Type != 0x50726F67 )
  {
    dinfo->m_prog = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (0040020C) --------------------------------------------------------
int do_get_sset_chunk(void *indata, struct sdhd_info *dinfo)
{
  if ( dinfo->m_head->sampleSetChunkAddr == 0xFFFFFFFF )
    return 0x81039006;
  if ( (dinfo->m_head->sampleSetChunkAddr & 0x80000000) )
    return 0x8103002F;
  dinfo->m_sset = (sceHardSynthSampleSetChunk *)((char *)indata + dinfo->m_head->sampleSetChunkAddr);
  if ( dinfo->m_sset->Creator != 0x53434549 || dinfo->m_sset->Type != 0x53736574 )
  {
    dinfo->m_sset = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (00400278) --------------------------------------------------------
int do_get_smpl_chunk(void *indata, struct sdhd_info *dinfo)
{
  if ( dinfo->m_head->sampleChunkAddr == 0xFFFFFFFF )
    return 0x81039007;
  if ( (dinfo->m_head->sampleChunkAddr & 0x80000000) )
    return 0x8103002F;
  dinfo->m_smpl = (sceHardSynthSampleChunk *)((char *)indata + dinfo->m_head->sampleChunkAddr);
  if ( dinfo->m_smpl->Creator != 0x53434549 || dinfo->m_smpl->Type != 0x536D706C )
  {
    dinfo->m_smpl = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (004002E4) --------------------------------------------------------
int do_get_vagi_chunk(void *indata, struct sdhd_info *dinfo)
{
  if ( dinfo->m_head->vagInfoChunkAddr == 0xFFFFFFFF )
    return 0x81039008;
  if ( (dinfo->m_head->vagInfoChunkAddr & 0x80000000) )
    return 0x8103002F;
  dinfo->m_vagi = (sceHardSynthVagInfoChunk *)((char *)indata + dinfo->m_head->vagInfoChunkAddr);
  if ( dinfo->m_vagi->Creator != 0x53434549 || dinfo->m_vagi->Type != 0x56616769 )
  {
    dinfo->m_vagi = 0;
    return 0x8103002F;
  }
  return 0;
}

//----- (00400350) --------------------------------------------------------
void do_copy_to_sdhd_program_param(SceSdHdProgramParam *dst, const sceHardSynthProgramParam *src)
{
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
  dst->LFO.midiAmpDepthDown = src->progLfoMidiAmpDepth2;
}

//----- (00400470) --------------------------------------------------------
void do_copy_to_sdhd_split_block(SceSdHdSplitBlock *dst, const sceHardSynthSplitBlock *src)
{
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
  dst->common.detune = src->splitDetune;
}

//----- (0040053C) --------------------------------------------------------
void do_copy_to_sdhd_set_param(SceSdHdSampleSetParam *dst, const sceHardSynthSampleSetParam *src)
{
  dst->velCurve = src->velCurve;
  dst->velLimitLow = src->velLimitLow;
  dst->velLimitHigh = src->velLimitHigh;
  dst->nSample = src->nSample;
}

//----- (0040056C) --------------------------------------------------------
void do_copy_to_sdhd_sample_param(SceSdHdSampleParam *dst, const sceHardSynthSampleParam *src)
{
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
  dst->LFO.ampLFOFade = src->sampleAmpLfoFade;
}

//----- (00400704) --------------------------------------------------------
void do_copy_to_sdhd_vag_info_param(SceSdHdVAGInfoParam *dst, int sz, const sceHardSynthVagParam *src)
{
  dst->vagOffsetAddr = src->vagOffsetAddr;
  dst->vagSampleRate = src->vagSampleRate;
  dst->vagSize = sz;
  dst->vagAttribute = src->vagAttribute;
}

//----- (0040072C) --------------------------------------------------------
unsigned int do_get_vag_size(sceHardSynthVersionChunk *indata, const unsigned int *vagoffsaddr)
{
  unsigned int i; // $a0
  unsigned int bodySize; // $a1
  const sceHardSynthVagParam *vagparam; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  if ( do_get_vers_head_chunk(indata, &dinfo) || do_get_vagi_chunk(indata, &dinfo) )
    return 0;
  bodySize = dinfo.m_head->bodySize;
  for ( i = 0; dinfo.m_vagi->maxVagInfoNumber >= i; i += 1 )
  {
    if ( dinfo.m_vagi->vagInfoOffsetAddr[i] != 0xFFFFFFFF )
    {
      vagparam = (sceHardSynthVagParam *)((char *)(dinfo.m_vagi) + dinfo.m_vagi->vagInfoOffsetAddr[i]);
      if ( *vagoffsaddr < vagparam->vagOffsetAddr && vagparam->vagOffsetAddr < bodySize )
        bodySize = vagparam->vagOffsetAddr;
    }
  }
  return bodySize - *vagoffsaddr;
}

//----- (004007F4) --------------------------------------------------------
unsigned int do_check_chunk_in_bounds(
        void *indata,
        const struct sdhd_info *dinfo,
        unsigned int hdrmagic,
        unsigned int idx)
{
  (void)indata;

  switch ( hdrmagic )
  {
    case 0x536D706C:
    {
      if ( !dinfo->m_smpl )
        return 0x8103002F;
      if ( dinfo->m_smpl->maxSampleNumber < idx )
        return 0x81039014;
      if ( dinfo->m_smpl->sampleOffsetAddr[idx] == 0xFFFFFFFF )
        return 0x81039015;
      break;
    }
    case 0x53736574:
    {
      if ( !dinfo->m_sset )
        return 0x8103002F;
      if ( dinfo->m_sset->maxSampleSetNumber < idx )
        return 0x81039012;
      if ( dinfo->m_sset->sampleSetOffsetAddr[idx] == 0xFFFFFFFF )
        return 0x81039012;
      break;
    }
    case 0x56616769:
    {
      if ( !dinfo->m_vagi )
        return 0x8103002F;
      if ( dinfo->m_vagi->maxVagInfoNumber < idx )
        return 0x81039016;
      if ( dinfo->m_vagi->vagInfoOffsetAddr[idx] == 0xFFFFFFFF )
        return 0x81039017;
      break;
    }
    case 0x50726F67:
    {
      if ( !dinfo->m_prog )
        return 0x8103002F;
      if ( dinfo->m_prog->maxProgramNumber < idx )
        return 0x81039010;
      if ( dinfo->m_prog->programOffsetAddr[idx] == 0xFFFFFFFF )
        return 0x81039011;
      break;
    }
    default:
      break;
  }
  return 0;
}

//----- (004009A0) --------------------------------------------------------
int do_get_common_block_ptr_note(
        void *buffer,
        unsigned int programNumber,
        unsigned int swcase,
        unsigned int noteNumber,
        unsigned int velocity,
        int mode,
        void **ptr)
{
  int idx1; // $s1
  int i; // $s6
  sceHardSynthSplitBlock *p_splitblock; // $a1
  int j; // $s2
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-10h] BYREF
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+14h] [-Ch] BYREF
  sceHardSynthSampleParam *p_sampleparam; // [sp+18h] [-8h] BYREF
  sceHardSynthVagParam *p_vagparam; // [sp+1Ch] [-4h] BYREF

  idx1 = 0;
  if ( sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam) || p_programparam->splitBlockAddr == 0xFFFFFFFF )
  {
    return 0;
  }
  for ( i = 0; i < p_programparam->nSplit; i += 1 )
  {
    p_splitblock = (sceHardSynthSplitBlock *)((char *)p_programparam
                                            + p_programparam->splitBlockAddr
                                            + p_programparam->sizeSplitBlock * i);
    if ( noteNumber < (p_splitblock->splitRangeLow & 0x7Fu) || noteNumber > (p_splitblock->splitRangeHigh & 0x7Fu) )
    {
      continue;
    }
    switch ( swcase )
    {
      case 0:
        ++idx1;
        break;
      case 1:
        ++idx1;
        *ptr = p_splitblock;
        ptr = (void **)(((char *)ptr) + sizeof(void *));
        break;
      case 2:
        ++idx1;
        do_copy_to_sdhd_split_block((SceSdHdSplitBlock *)ptr, p_splitblock);
        ptr = (void **)(((char *)ptr) + sizeof(SceSdHdSplitBlock));
        break;
      default:
        if ( p_splitblock->sampleSetIndex == 0xFFFF
          || sceSdHdGetSampleSetParamAddr(buffer, p_splitblock->sampleSetIndex, &p_samplesetparam) )
        {
          break;
        }
        switch ( swcase )
        {
          case 3:
            ++idx1;
            break;
          case 4:
            ++idx1;
            *ptr = p_samplesetparam;
            ptr = (void **)(((char *)ptr) + sizeof(void *));
            break;
          case 5:
            ++idx1;
            do_copy_to_sdhd_set_param((SceSdHdSampleSetParam *)ptr, p_samplesetparam);
            ptr = (void **)(((char *)ptr) + sizeof(SceSdHdSampleSetParam));
            break;
          default:
            switch ( mode )
            {
              case 0:
                if ( velocity < p_samplesetparam->velLimitLow || velocity > p_samplesetparam->velLimitHigh )
                {
                  break;
                }
                for ( j = 0; j < p_samplesetparam->nSample; j += 1 )
                {
                  if ( p_samplesetparam->sampleIndex[j] != 0xFFFF
                    && !sceSdHdGetSampleParamAddr(buffer, p_samplesetparam->sampleIndex[j], &p_sampleparam)
                    && velocity >= (p_sampleparam->velRangeLow & 0x7Fu)
                    && (p_sampleparam->velRangeHigh & 0x7Fu) >= velocity )
                  {
                      switch ( swcase )
                      {
                        case 6:
                          ++idx1;
                          break;
                        case 7:
                          ++idx1;
                          *ptr = p_sampleparam;
                          ptr = (void **)(((char *)ptr) + sizeof(void *));
                          break;
                        case 8:
                          ++idx1;
                          do_copy_to_sdhd_sample_param((SceSdHdSampleParam *)ptr, p_sampleparam);
                          ptr = (void **)(((char *)ptr) + sizeof(SceSdHdSampleParam));
                          break;
                        default:
                          if ( p_sampleparam->VagIndex == 0xFFFF
                            || sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, &p_vagparam) )
                          {
                            break;
                          }
                          switch ( swcase )
                          {
                            case 9:
                              ++idx1;
                              break;
                            case 10:
                              ++idx1;
                              *ptr = p_vagparam;
                              ptr = (void **)(((char *)ptr) + sizeof(void *));
                              break;
                            case 11:
                              ++idx1;
                              do_copy_to_sdhd_vag_info_param((SceSdHdVAGInfoParam *)ptr, do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr), p_vagparam);
                              ptr = (void **)(((char *)ptr) + sizeof(SceSdHdVAGInfoParam));
                              break;
                            default:
                              break;
                          }
                          break;
                      }
                  }
                }
                break;
              case 1:
                for ( j = 0; j < p_samplesetparam->nSample; j += 1 )
                {
                  if ( p_samplesetparam->sampleIndex[j] != 0xFFFF
                    && !sceSdHdGetSampleParamAddr(buffer, p_samplesetparam->sampleIndex[j], &p_sampleparam)
                    && velocity >= (p_sampleparam->velRangeLow & 0x7Fu)
                    && (p_sampleparam->velRangeHigh & 0x7Fu) >= velocity )
                  {
                    switch ( swcase )
                    {
                      case 6:
                        ++idx1;
                        break;
                      case 7:
                        ++idx1;
                        *ptr = p_sampleparam;
                        ptr = (void **)(((char *)ptr) + sizeof(void *));
                        break;
                      case 8:
                        ++idx1;
                        do_copy_to_sdhd_sample_param((SceSdHdSampleParam *)ptr, p_sampleparam);
                        ptr = (void **)(((char *)ptr) + sizeof(SceSdHdSampleParam));
                        break;
                      default:
                        if ( p_sampleparam->VagIndex == 0xFFFF
                          || sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, &p_vagparam) )
                        {
                          break;
                        }
                        switch ( swcase )
                        {
                          case 9:
                            ++idx1;
                            break;
                          case 10:
                            ++idx1;
                            *ptr = p_vagparam;
                            ptr = (void **)(((char *)ptr) + sizeof(void *));
                            break;
                          case 11:
                            ++idx1;
                            do_copy_to_sdhd_vag_info_param((SceSdHdVAGInfoParam *)ptr, do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr), p_vagparam);
                            ptr = (void **)(((char *)ptr) + sizeof(SceSdHdVAGInfoParam));
                            break;
                        }
                        break;
                    }
                  }
                }
                break;
              default:
                break;
            }
            break;
        }
        break;
    }
  }
  return idx1;
}
// 400A9C: conditional instruction was optimized away because $s3.4==2
// 400B10: conditional instruction was optimized away because $s3.4==3

//----- (00400F08) --------------------------------------------------------
int do_get_common_block_ptr(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int swcase,
        unsigned int velocity,
        int mode,
        void **param)
{
  int idx1; // $s0
  int i; // $s3
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+10h] [-10h] BYREF
  sceHardSynthSampleParam *p_sampleparam; // [sp+14h] [-Ch] BYREF
  sceHardSynthVagParam *p_vagparam; // [sp+18h] [-8h] BYREF

  idx1 = 0;
  if ( sceSdHdGetSampleSetParamAddr(buffer, sampleSetNumber, &p_samplesetparam) )
    return 0;
  switch ( mode )
  {
    case 0:
      if ( velocity < p_samplesetparam->velLimitLow || velocity > p_samplesetparam->velLimitHigh )
        return 0;
      for ( i = 0; i < p_samplesetparam->nSample; i += 1 )
      {
        if ( p_samplesetparam->sampleIndex[i] != 0xFFFF
          && !sceSdHdGetSampleParamAddr(buffer, p_samplesetparam->sampleIndex[i], &p_sampleparam)
          && velocity >= (p_sampleparam->velRangeLow & 0x7Fu)
          && (p_sampleparam->velRangeHigh & 0x7Fu) >= velocity )
        {
          switch ( swcase )
          {
            case 6:
              ++idx1;
              break;
            case 7:
              ++idx1;
              *param = p_sampleparam;
              param = (void **)(((char *)param) + sizeof(void *));
              break;
            case 8:
              ++idx1;
              do_copy_to_sdhd_sample_param((SceSdHdSampleParam *)param, p_sampleparam);
              param = (void **)(((char *)param) + sizeof(SceSdHdSampleParam));
              break;
            default:
              if ( p_sampleparam->VagIndex == 0xFFFF
                || sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, &p_vagparam) )
              {
                break;
              }
              switch ( swcase )
              {
                case 9:
                  ++idx1;
                  break;
                case 10:
                  ++idx1;
                  *param = p_vagparam;
                  param = (void **)(((char *)param) + sizeof(void *));
                  break;
                case 11:
                  ++idx1;
                  do_copy_to_sdhd_vag_info_param((SceSdHdVAGInfoParam *)param, do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr), p_vagparam);
                  param = (void **)(((char *)param) + sizeof(SceSdHdVAGInfoParam));
                  break;
              }
          }
        }
      }
      return idx1;
    case 1:
      for ( i = 0; i < p_samplesetparam->nSample; i += 1 )
      {
        if ( p_samplesetparam->sampleIndex[i] != 0xFFFF
          && !sceSdHdGetSampleParamAddr(buffer, p_samplesetparam->sampleIndex[i], &p_sampleparam)
          && velocity >= (p_sampleparam->velRangeLow & 0x7Fu)
          && (p_sampleparam->velRangeHigh & 0x7Fu) >= velocity )
        {
          switch ( swcase )
          {
            case 6:
              ++idx1;
              break;
            case 7:
              ++idx1;
              *param = p_sampleparam;
              param = (void **)(((char *)param) + sizeof(void *));
              break;
            case 8:
              ++idx1;
              do_copy_to_sdhd_sample_param((SceSdHdSampleParam *)param, p_sampleparam);
              param = (void **)(((char *)param) + sizeof(SceSdHdSampleParam));
              break;
            default:
              if ( p_sampleparam->VagIndex == 0xFFFF || sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, &p_vagparam) )
                break;
              switch ( swcase )
              {
                case 9:
                  ++idx1;
                  break;
                case 10:
                  ++idx1;
                  *param = p_vagparam;
                  param = (void **)(((char *)param) + sizeof(void *));
                  break;
                case 11:
                  ++idx1;
                  do_copy_to_sdhd_vag_info_param((SceSdHdVAGInfoParam *)param, do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr), p_vagparam);
                  param = (void **)(((char *)param) + sizeof(SceSdHdVAGInfoParam));
                  break;
                default:
                  break;
              }
              break;
          }
        }
      }
      return idx1;
    default:
      return 0;
  }
}

//----- (004012F0) --------------------------------------------------------
int sceSdHdGetMaxProgramNumber(void *buffer)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_prog_chunk(buffer, &dinfo);
  if ( result )
    return result;
  return dinfo.m_prog->maxProgramNumber;
}

//----- (0040133C) --------------------------------------------------------
int sceSdHdGetMaxSampleSetNumber(void *buffer)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_sset_chunk(buffer, &dinfo);
  if ( result )
    return result;
  return dinfo.m_sset->maxSampleSetNumber;
}

//----- (00401388) --------------------------------------------------------
int sceSdHdGetMaxSampleNumber(void *buffer)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_smpl_chunk(buffer, &dinfo);
  if ( result )
    return result;
  return dinfo.m_smpl->maxSampleNumber;
}

//----- (004013D4) --------------------------------------------------------
int sceSdHdGetMaxVAGInfoNumber(void *buffer)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_vagi_chunk(buffer, &dinfo);
  if ( result )
    return result;
  return dinfo.m_vagi->maxVagInfoNumber;
}

//----- (00401420) --------------------------------------------------------
int sceSdHdGetProgramParamAddr(void *buffer, unsigned int programNumber, sceHardSynthProgramParam **ptr)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_prog_chunk(buffer, &dinfo);
  if ( result )
    return result;
  result = do_check_chunk_in_bounds(buffer, &dinfo, 0x50726F67u, programNumber);
  if ( result )
    return result;
  *ptr = (sceHardSynthProgramParam *)((char *)dinfo.m_prog + dinfo.m_prog->programOffsetAddr[programNumber]);
  return 0;
}

//----- (004014B0) --------------------------------------------------------
int sceSdHdGetProgramParam(void *buffer, unsigned int programNumber, SceSdHdProgramParam *param)
{
  int result; // $v0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam);
  if ( result )
    return result;
  do_copy_to_sdhd_program_param(param, p_programparam);
  return 0;
}

//----- (004014F0) --------------------------------------------------------
int sceSdHdGetSplitBlockAddr(
        void *buffer,
        unsigned int programNumber,
        unsigned int splitBlockNumber,
        sceHardSynthSplitBlock **theParamPtr)
{
  int result; // $v0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam);
  if ( result )
    return result;
  if ( p_programparam->splitBlockAddr == 0xFFFFFFFF )
    return 0x81039009;
  if ( (unsigned int)p_programparam->nSplit - 1 < splitBlockNumber )
    return 0x81039018;
  *theParamPtr = (sceHardSynthSplitBlock *)((char *)p_programparam
                                          + p_programparam->splitBlockAddr
                                          + p_programparam->sizeSplitBlock * splitBlockNumber);
  return 0;
}

//----- (0040158C) --------------------------------------------------------
int sceSdHdGetSplitBlock(
        void *buffer,
        unsigned int programNumber,
        unsigned int splitBlockNumber,
        SceSdHdSplitBlock *param)
{
  int result; // $v0
  sceHardSynthSplitBlock *p_splitblock; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSplitBlockAddr(buffer, programNumber, splitBlockNumber, &p_splitblock);
  if ( result )
    return result;
  do_copy_to_sdhd_split_block(param, p_splitblock);
  return 0;
}

//----- (004015CC) --------------------------------------------------------
int sceSdHdGetSampleSetParamAddr(void *buffer, unsigned int sampleSetNumber, sceHardSynthSampleSetParam **ptr)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_sset_chunk(buffer, &dinfo);
  if ( result )
    return result;
  result = do_check_chunk_in_bounds(buffer, &dinfo, 0x53736574u, sampleSetNumber);
  if ( result )
    return result;
  *ptr = (sceHardSynthSampleSetParam *)((char *)dinfo.m_sset + dinfo.m_sset->sampleSetOffsetAddr[sampleSetNumber]);
  return 0;
}

//----- (0040165C) --------------------------------------------------------
int sceSdHdGetSampleSetParam(void *buffer, unsigned int sampleSetNumber, SceSdHdSampleSetParam *param)
{
  int result; // $v0
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSampleSetParamAddr(buffer, sampleSetNumber, &p_samplesetparam);
  if ( result )
    return result;
  do_copy_to_sdhd_set_param(param, p_samplesetparam);
  return 0;
}

//----- (0040169C) --------------------------------------------------------
int sceSdHdGetSampleParamAddr(void *buffer, unsigned int sampleNumber, sceHardSynthSampleParam **ptr)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_smpl_chunk(buffer, &dinfo);
  if ( result )
    return result;
  result = do_check_chunk_in_bounds(buffer, &dinfo, 0x536D706Cu, sampleNumber);
  if ( result )
    return result;
  *ptr = (sceHardSynthSampleParam *)((char *)dinfo.m_smpl + dinfo.m_smpl->sampleOffsetAddr[sampleNumber]);
  return 0;
}

//----- (0040172C) --------------------------------------------------------
int sceSdHdGetSampleParam(void *buffer, unsigned int sampleNumber, SceSdHdSampleParam *param)
{
  int result; // $v0
  sceHardSynthSampleParam *p_sampleparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSampleParamAddr(buffer, sampleNumber, &p_sampleparam);
  if ( result )
    return result;
  do_copy_to_sdhd_sample_param(param, p_sampleparam);
  return 0;
}

//----- (0040176C) --------------------------------------------------------
int sceSdHdGetVAGInfoParamAddr(void *buffer, unsigned int vagInfoNumber, sceHardSynthVagParam **ptr)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_vagi_chunk(buffer, &dinfo);
  if ( result )
    return result;
  result = do_check_chunk_in_bounds(buffer, &dinfo, 0x56616769u, vagInfoNumber);
  if ( result )
    return result;
  *ptr = (sceHardSynthVagParam *)((char *)dinfo.m_vagi + dinfo.m_vagi->vagInfoOffsetAddr[vagInfoNumber]);
  return 0;
}

//----- (004017FC) --------------------------------------------------------
int sceSdHdGetVAGInfoParam(void *buffer, unsigned int vagInfoNumber, SceSdHdVAGInfoParam *param)
{
  int result; // $v0
  sceHardSynthVagParam *p_vagparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetVAGInfoParamAddr(buffer, vagInfoNumber, &p_vagparam);
  if ( result )
    return result;  
  do_copy_to_sdhd_vag_info_param(param, do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr), p_vagparam);
  return 0;
}

//----- (00401858) --------------------------------------------------------
int sceSdHdCheckProgramNumber(void *buffer, unsigned int programNumber)
{
  int result; // $v0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_prog_chunk(buffer, &dinfo);
  if ( result )
    return result;
  return do_check_chunk_in_bounds(buffer, &dinfo, 0x50726F67u, programNumber);
}

//----- (004018B8) --------------------------------------------------------
int sceSdHdGetSplitBlockCountByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 0, noteNumber, 0, 0, 0);
}

//----- (004018E8) --------------------------------------------------------
int sceSdHdGetSplitBlockAddrByNote(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        sceHardSynthSplitBlock **ptr)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 1u, noteNumber, 0, 0, (void **)ptr);
}

//----- (0040191C) --------------------------------------------------------
int sceSdHdGetSplitBlockByNote(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        SceSdHdSplitBlock *param)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 2u, noteNumber, 0, 0, (void **)param);
}

//----- (00401950) --------------------------------------------------------
int sceSdHdGetSampleSetParamCountByNote(void *buffer, unsigned int programNumber, unsigned int noteNumber)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 3u, noteNumber, 0, 0, 0);
}

//----- (00401980) --------------------------------------------------------
int sceSdHdGetSampleSetParamAddrByNote(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        sceHardSynthSampleSetParam **ptr)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 4u, noteNumber, 0, 0, (void **)ptr);
}

//----- (004019B4) --------------------------------------------------------
int sceSdHdGetSampleSetParamByNote(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        SceSdHdSampleSetParam *param)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 5u, noteNumber, 0, 0, (void **)param);
}

//----- (004019E8) --------------------------------------------------------
int sceSdHdGetSampleParamCountByNoteVelocity(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        unsigned int velocity,
        unsigned int mode)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 6u, noteNumber, velocity, mode, 0);
}

//----- (00401A20) --------------------------------------------------------
int sceSdHdGetSampleParamAddrByNoteVelocity(
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
int sceSdHdGetSampleParamByNoteVelocity(
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
int sceSdHdGetVAGInfoParamCountByNoteVelocity(
        void *buffer,
        unsigned int programNumber,
        unsigned int noteNumber,
        unsigned int velocity,
        unsigned int mode)
{
  return do_get_common_block_ptr_note(buffer, programNumber, 9u, noteNumber, velocity, mode, 0);
}

//----- (00401AD0) --------------------------------------------------------
int sceSdHdGetVAGInfoParamAddrByNoteVelocity(
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
int sceSdHdGetVAGInfoParamByNoteVelocity(
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
int sceSdHdGetSampleParamCountByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 6u, velocity, mode, 0);
}

//----- (00401B78) --------------------------------------------------------
int sceSdHdGetSampleParamAddrByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode,
        sceHardSynthSampleParam **ptr)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 7u, velocity, mode, (void **)ptr);
}

//----- (00401BAC) --------------------------------------------------------
int sceSdHdGetSampleParamByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode,
        SceSdHdSampleParam *param)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 8u, velocity, mode, (void **)param);
}

//----- (00401BE0) --------------------------------------------------------
int sceSdHdGetVAGInfoParamCountByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 9u, velocity, mode, 0);
}

//----- (00401C10) --------------------------------------------------------
int sceSdHdGetVAGInfoParamAddrByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode,
        sceHardSynthVagParam **ptr)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 0xAu, velocity, mode, (void **)ptr);
}

//----- (00401C44) --------------------------------------------------------
int sceSdHdGetVAGInfoParamByVelocity(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int velocity,
        unsigned int mode,
        SceSdHdVAGInfoParam *param)
{
  return do_get_common_block_ptr(buffer, sampleSetNumber, 0xBu, velocity, mode, (void **)param);
}

//----- (00401C78) --------------------------------------------------------
int sceSdHdGetVAGInfoParamAddrBySampleNumber(
        void *buffer,
        unsigned int sampleNumber,
        sceHardSynthVagParam **ptr)
{
  int result; // $v0
  sceHardSynthSampleParam *p_sampleparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSampleParamAddr(buffer, sampleNumber, &p_sampleparam);
  if ( result )
    return result;
  if ( p_sampleparam->VagIndex == 0xFFFF )
    return 0x81039019;
  return sceSdHdGetVAGInfoParamAddr(buffer, p_sampleparam->VagIndex, ptr);
}

//----- (00401CE8) --------------------------------------------------------
int sceSdHdGetVAGInfoParamBySampleNumber(void *buffer, unsigned int sampleNumber, SceSdHdVAGInfoParam *param)
{
  int result; // $v0
  sceHardSynthVagParam *p_vagparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetVAGInfoParamAddrBySampleNumber(buffer, sampleNumber, &p_vagparam);
  if ( result )
    return result;
  do_copy_to_sdhd_vag_info_param(param, do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr), p_vagparam);
  return 0;
}

//----- (00401D44) --------------------------------------------------------
int sceSdHdGetSplitBlockNumberBySplitNumber(void *buffer, unsigned int programNumber, unsigned int splitNumber)
{
  int result; // $v0
  int i; // $v1
  sceHardSynthSplitBlock *splitblock; // $a0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam);
  if ( result )
    return result;
  if ( p_programparam->splitBlockAddr == 0xFFFFFFFF )
    return 0x81039009;
  splitblock = (sceHardSynthSplitBlock *)((char *)p_programparam + p_programparam->splitBlockAddr);
  for ( i = 0; i < p_programparam->nSplit; i += 1 )
  {
    if ( splitNumber == splitblock->splitNumber )
      return i;
    splitblock = (sceHardSynthSplitBlock *)((char *)splitblock + p_programparam->sizeSplitBlock);
  }
  return 0x81039020;
}

//----- (00401DD8) --------------------------------------------------------
int sceSdHdGetVAGSize(void *buffer, unsigned int vagInfoNumber)
{
  int result; // $v0
  sceHardSynthVagParam *p_vagparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetVAGInfoParamAddr(buffer, vagInfoNumber, &p_vagparam);
  if ( result )
    return result;
  return do_get_vag_size((sceHardSynthVersionChunk *)buffer, &p_vagparam->vagOffsetAddr);
}

//----- (00401E14) --------------------------------------------------------
int sceSdHdGetSplitBlockCount(void *buffer, unsigned int programNumber)
{
  int result; // $v0
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetProgramParamAddr(buffer, programNumber, &p_programparam);
  if ( result )
    return result;
  return p_programparam->nSplit;
}

//----- (00401E48) --------------------------------------------------------
int sceSdHdGetMaxSplitBlockCount(void *buffer)
{
  int curminval; // $s2
  int retres; // $v0
  signed int i; // $s1
  signed int j; // $s0
  int curval1; // $v1
  int curval2; // $v1
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF
  sceHardSynthSplitBlock *p_splitblock; // [sp+14h] [-4h] BYREF

  curminval = 0;
  retres = sceSdHdGetMaxProgramNumber(buffer);
  for ( i = 0; retres >= i; i += 1 )
  {
    if ( !sceSdHdGetProgramParamAddr(buffer, i, &p_programparam) )
    {
      for ( j = 0; j < p_programparam->nSplit; j += 1 )
      {
        if ( !sceSdHdGetSplitBlockAddr(buffer, i, j, &p_splitblock) )
        {
          curval1 = sceSdHdGetSplitBlockCountByNote(buffer, i, p_splitblock->splitRangeLow & 0x7F);
          curminval = ( curminval < curval1 ) ? curval1 : curminval;
          curval2 = sceSdHdGetSplitBlockCountByNote(buffer, i, p_splitblock->splitRangeHigh & 0x7F);
          curminval = ( curminval < curval2 ) ? curval2 : curminval;
        }
      }
    }
  }
  return curminval;
}

//----- (00401F70) --------------------------------------------------------
int sceSdHdGetMaxSampleSetParamCount(void *buffer)
{
  int curminval; // $s2
  int retres; // $s4
  signed int i; // $s1
  signed int j; // $s0
  int curval1; // $v1
  int curval2; // $v1
  sceHardSynthProgramParam *p_programparam; // [sp+10h] [-8h] BYREF
  sceHardSynthSplitBlock *p_splitblock; // [sp+14h] [-4h] BYREF

  curminval = 0;
  retres = sceSdHdGetMaxProgramNumber(buffer);
  for ( i = 0; retres >= i; i += 1 )
  {
    if ( !sceSdHdGetProgramParamAddr(buffer, i, &p_programparam) )
    {
      for ( j = 0; j < p_programparam->nSplit; j += 1 )
      {
        if ( !sceSdHdGetSplitBlockAddr(buffer, i, j, &p_splitblock) )
        {
          curval1 = sceSdHdGetSampleSetParamCountByNote(buffer, i, p_splitblock->splitRangeLow & 0x7F);
          curminval = ( curminval < curval1 ) ? curval1 : curminval;
          curval2 = sceSdHdGetSampleSetParamCountByNote(buffer, i, p_splitblock->splitRangeHigh & 0x7F);
          curminval = ( curminval < curval2 ) ? curval2 : curminval;
        }
      }
    }
  }
  return curminval;
}

//----- (00402098) --------------------------------------------------------
int sceSdHdGetMaxSampleParamCount(void *buffer)
{
  int curminval; // $s0
  int retres; // $s6
  signed int i; // $s2
  signed int j; // $s4
  signed int k; // $s1
  int curval1; // $v1
  int curval2; // $v1
  int curval3; // $v1
  int curval4; // $v1
  sceHardSynthProgramParam *p_programparam; // [sp+18h] [-10h] BYREF
  sceHardSynthSplitBlock *p_splitblock; // [sp+1Ch] [-Ch] BYREF
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+20h] [-8h] BYREF
  sceHardSynthSampleParam *p_sampleparam; // [sp+24h] [-4h] BYREF

  curminval = 0;
  retres = sceSdHdGetMaxProgramNumber(buffer);
  for ( i = 0; retres >= i; i += 1 )
  {
    if ( !sceSdHdGetProgramParamAddr(buffer, i, &p_programparam) )
    {
      for ( j = 0; j < p_programparam->nSplit; j += 1 )
      {
        if ( !sceSdHdGetSplitBlockAddr(buffer, i, j, &p_splitblock)
          && !sceSdHdGetSampleSetParamAddr(buffer, p_splitblock->sampleSetIndex, &p_samplesetparam) )
        {
          for ( k = 0; k < p_samplesetparam->nSample; k += 1 )
          {
            if ( !sceSdHdGetSampleParamAddr(buffer, sceSdHdGetSampleNumberBySampleIndex(buffer, p_splitblock->sampleSetIndex, k), &p_sampleparam) )
            {
              curval1 = sceSdHdGetSampleParamCountByNoteVelocity(
                          buffer,
                          i,
                          p_splitblock->splitRangeLow & 0x7F,
                          p_sampleparam->velRangeLow & 0x7F,
                          1u);
              curminval = ( curminval < curval1 ) ? curval1 : curminval;
              curval2 = sceSdHdGetSampleParamCountByNoteVelocity(
                          buffer,
                          i,
                          p_splitblock->splitRangeLow & 0x7F,
                          p_sampleparam->velRangeHigh & 0x7F,
                          1u);
              curminval = ( curminval < curval2 ) ? curval2 : curminval;
              curval3 = sceSdHdGetSampleParamCountByNoteVelocity(
                          buffer,
                          i,
                          p_splitblock->splitRangeHigh & 0x7F,
                          p_sampleparam->velRangeLow & 0x7F,
                          1u);
              curminval = ( curminval < curval3 ) ? curval3 : curminval;
              curval4 = sceSdHdGetSampleParamCountByNoteVelocity(
                          buffer,
                          i,
                          p_splitblock->splitRangeHigh & 0x7F,
                          p_sampleparam->velRangeHigh & 0x7F,
                          1u);
              curminval = ( curminval < curval4 ) ? curval4 : curminval;
            }
          }
        }
      }
    }
  }
  return curminval;
}

//----- (004022D8) --------------------------------------------------------
int sceSdHdGetMaxVAGInfoParamCount(void *buffer)
{
  int curminval; // $s0
  int retres; // $s6
  signed int i; // $s2
  signed int j; // $s4
  signed int k; // $s1
  int curval1; // $v1
  int curval2; // $v1
  int curval3; // $v1
  int curval4; // $v1
  sceHardSynthProgramParam *p_programparam; // [sp+18h] [-10h] BYREF
  sceHardSynthSplitBlock *p_splitblock; // [sp+1Ch] [-Ch] BYREF
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+20h] [-8h] BYREF
  sceHardSynthSampleParam *p_sampleparam; // [sp+24h] [-4h] BYREF

  curminval = 0;
  retres = sceSdHdGetMaxProgramNumber(buffer);
  for ( i = 0; retres >= i; i += 1 )
  {
    if ( !sceSdHdGetProgramParamAddr(buffer, i, &p_programparam) )
    {
      for ( j = 0; j < p_programparam->nSplit; j += 1 )
      {
        if ( !sceSdHdGetSplitBlockAddr(buffer, i, j, &p_splitblock)
          && !sceSdHdGetSampleSetParamAddr(buffer, p_splitblock->sampleSetIndex, &p_samplesetparam) )
        {
          for ( k = 0; k < p_samplesetparam->nSample; k += 1 )
          {
            if ( !sceSdHdGetSampleParamAddr(buffer, sceSdHdGetSampleNumberBySampleIndex(buffer, p_splitblock->sampleSetIndex, k), &p_sampleparam) )
            {
              curval1 = sceSdHdGetVAGInfoParamCountByNoteVelocity(
                          buffer,
                          i,
                          p_splitblock->splitRangeLow & 0x7F,
                          p_sampleparam->velRangeLow & 0x7F,
                          1u);
              curminval = ( curminval < curval1 ) ? curval1 : curminval;
              curval2 = sceSdHdGetVAGInfoParamCountByNoteVelocity(
                          buffer,
                          i,
                          p_splitblock->splitRangeLow & 0x7F,
                          p_sampleparam->velRangeHigh & 0x7F,
                          1u);
              curminval = ( curminval < curval2 ) ? curval2 : curminval;
              curval3 = sceSdHdGetVAGInfoParamCountByNoteVelocity(
                          buffer,
                          i,
                          p_splitblock->splitRangeHigh & 0x7F,
                          p_sampleparam->velRangeLow & 0x7F,
                          1u);
              curminval = ( curminval < curval3 ) ? curval3 : curminval;
              curval4 = sceSdHdGetVAGInfoParamCountByNoteVelocity(
                          buffer,
                          i,
                          p_splitblock->splitRangeHigh & 0x7F,
                          p_sampleparam->velRangeHigh & 0x7F,
                          1u);
              curminval = ( curminval < curval4 ) ? curval4 : curminval;
            }
          }
        }
      }
    }
  }
  return curminval;
}

//----- (00402518) --------------------------------------------------------
int sceSdHdModifyVelocity(unsigned int curveType, int velocity)
{
  switch ( curveType )
  {
    case 1u:
      return 128 - velocity;
    case 2u:
      velocity = velocity * velocity / 0x7Fu;
      return velocity ? velocity : 1;
    case 3u:
      velocity = velocity * velocity / 0x7Fu;
      velocity = velocity ? velocity : 1;
      return 128 - velocity;
    case 4u:
      velocity = (128 - velocity) * (128 - velocity);
      velocity = (velocity / 0x7F) & 0x3FFFFFF;
      velocity = velocity ? velocity : 1;
      return 128 - velocity;
    case 5u:
      velocity = 128 - velocity;
      velocity = velocity * velocity / 0x7Fu;
      return velocity ? velocity : 1;
    default:
      return velocity;
  }
}

//----- (0040261C) --------------------------------------------------------
int sceSdHdModifyVelocityLFO(unsigned int curveType, int velocity, int center)
{
  int calc5; // $v1
  int calcb; // $v1

  center = ( center >= 0 ) ? (( center >= 128 ) ? 127 : center) : 0;
  velocity = ( velocity >= 0 ) ? (( velocity >= 128 ) ? 127 : velocity) : 0;
  calc5 = 0;
  switch ( curveType )
  {
    case 0u:
    default:
      calc5 = (velocity - center) << 16;
      calc5 = (calc5 / 126) - (int)((unsigned int)calc5 >> 31);
      break;
    case 1u:
      calc5 = (center - velocity) << 16;
      calc5 = (calc5 / 126) - (int)((unsigned int)calc5 >> 31);
      break;
    case 2u:
      calc5 = ((velocity - 1) << 15) / 126 * (((velocity - 1) << 15) / 126)
            - ((center - 1) << 15) / 126 * (((center - 1) << 15) / 126);
      calc5 = ( calc5 < 0 ) ? ((calc5 + 0x3FFF) >> 14) : (calc5 >> 14);
      break;
    case 3u:
      calc5 = ((velocity - 1) << 15) / 126 * (((velocity - 1) << 15) / 126) / -16384
            - ((center - 1) << 15) / 126 * (((center - 1) << 15) / 126) / -16384;
      break;
    case 4u:
      calc5 = (0x10000 - ((center - 1) << 15) / 126) * (0x10000 - ((center - 1) << 15) / 126) / 0x4000
            - (0x10000 - ((velocity - 1) << 15) / 126) * (0x10000 - ((velocity - 1) << 15) / 126) / 0x4000;
      break;
    case 5u:
      calc5 = (0x10000 - ((velocity - 1) << 15) / 126) * (0x10000 - ((velocity - 1) << 15) / 126) / 0x4000
            - (0x10000 - ((center - 1) << 15) / 126) * (0x10000 - ((center - 1) << 15) / 126) / 0x4000;
      break;
    case 6u:
      if ( velocity == center )
        break;
      calc5 = ( center >= velocity ) ? (center - 1) : (127 - center);
      calcb = (velocity - center) << 16;
      if ( !calc5 )
        __builtin_trap();
      if ( calc5 == -1 && (unsigned int)calcb == 0x80000000 )
        __builtin_trap();
      calc5 = calcb / calc5;
      break;
    case 7u:
      if ( velocity == center )
        break;
      calc5 = ( center >= velocity ) ? (center - 1) : (127 - center);
      calcb = (center - velocity) << 16;
      if ( !calc5 )
        __builtin_trap();
      if ( calc5 == -1 && (unsigned int)calcb == 0x80000000 )
        __builtin_trap();
      calc5 = calcb / calc5;
      break;
    case 8u:
      if ( velocity == center )
        break;
      calcb = (velocity - center) << 15;
      if ( center >= velocity )
      {
        if ( center == 1 )
          __builtin_trap();
        if ( !center && (unsigned int)calcb == 0x80000000 )
          __builtin_trap();
        calc5 = calcb / (center - 1) * (calcb / (center - 1)) / -16384;
      }
      else
      {
        calc5 = 127 - center;
        if ( 127 == center )
          __builtin_trap();
        if ( calc5 == -1 && (unsigned int)calcb == 0x80000000 )
          __builtin_trap();
        calc5 = calcb / calc5 * (calcb / calc5);
        calc5 = ( calc5 < 0 ) ? ((calc5 + 0x3FFF) >> 14) : (calc5 >> 14);
      }
      break;
    case 9u:
      if ( velocity == center )
        break;
      calcb = (velocity - center) << 15;
      if ( center >= velocity )
      {
        if ( center == 1 )
          __builtin_trap();
        if ( !center && (unsigned int)calcb == 0x80000000 )
          __builtin_trap();
        calc5 = (calcb / (center - 1) + 0x8000) * (calcb / (center - 1) + 0x8000) / 0x4000 - 0x10000;
      }
      else
      {
        calc5 = 127 - center;
        if ( 127 == center )
          __builtin_trap();
        if ( calc5 == -1 && (unsigned int)calcb == 0x80000000 )
          __builtin_trap();
        calc5 = (0x8000 - calcb / calc5) * (0x8000 - calcb / calc5);
        calc5 = 0x10000 - (( calc5 < 0 ) ? ((calc5 + 0x3FFF) >> 14) : (calc5 >> 14));
      }
      break;
  }
  return ( calc5 < -65536 ) ? -65536 : (( calc5 > 0xFFFF ) ? 0xFFFF : calc5);
}

//----- (00402AD0) --------------------------------------------------------
int sceSdHdGetValidProgramNumberCount(void *buffer)
{
  int validcnt; // $s0
  int result; // $v0
  unsigned int i; // $a0
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  validcnt = 0;
  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_prog_chunk(buffer, &dinfo);
  if ( result )
    return result;
  for ( i = 0; dinfo.m_prog->maxProgramNumber >= i; i += 1 )
  {
    if ( dinfo.m_prog->programOffsetAddr[i] != 0xFFFFFFFF )
      ++validcnt;
  }
  return validcnt;
}

//----- (00402B5C) --------------------------------------------------------
int sceSdHdGetValidProgramNumber(void *buffer, unsigned int *ptr)
{
  int validcnt; // $s1
  int result; // $v0
  unsigned int i; // $v1
  struct sdhd_info dinfo; // [sp+10h] [-18h] BYREF

  validcnt = 0;
  result = do_get_vers_head_chunk((sceHardSynthVersionChunk *)buffer, &dinfo);
  if ( result )
    return result;
  result = do_get_prog_chunk(buffer, &dinfo);
  if ( result )
    return result;
  for ( i = 0; dinfo.m_prog->maxProgramNumber >= i; i += 1 )
  {
    if ( dinfo.m_prog->programOffsetAddr[i] != 0xFFFFFFFF )
    {
      ptr[validcnt] = i;
      validcnt += 1;
    }
  }
  return validcnt;
}

//----- (00402C08) --------------------------------------------------------
int sceSdHdGetSampleNumberBySampleIndex(
        void *buffer,
        unsigned int sampleSetNumber,
        unsigned int sampleIndexNumber)
{
  int result; // $v0
  sceHardSynthSampleSetParam *p_samplesetparam; // [sp+10h] [-8h] BYREF

  result = sceSdHdGetSampleSetParamAddr(buffer, sampleSetNumber, &p_samplesetparam);
  if ( result )
    return result;
  return ( (unsigned int)p_samplesetparam->nSample - 1 < sampleIndexNumber ) ? 0x9006 : p_samplesetparam->sampleIndex[sampleIndexNumber];
}

//----- (00402C70) --------------------------------------------------------
int _start(int ac)
{
  int regres; // $s0
  int state; // [sp+10h] [-8h] BYREF

  if ( ac < 0 )
  {
    CpuSuspendIntr(&state);
    regres = ReleaseLibraryEntries(&_exp_sdhd);
    CpuResumeIntr(state);
    return ( !regres ) ? 1 : 2;
  }
  CpuSuspendIntr(&state);
  regres = RegisterLibraryEntries(&_exp_sdhd);
  CpuResumeIntr(state);
  return ( !regres ) ? 2 : 1;
}
