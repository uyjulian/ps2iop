
#include "irx_imports.h"

IRX_ID("Sound_Data_SQ", 2, 1);

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

typedef struct sceSeqHeaderChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int fileSize;
  unsigned int songChunkAddr;
  unsigned int midiChunkAddr;
  unsigned int seSequenceChunkAddr;
  unsigned int seSongChunkAddr;
} sceSeqHeaderChunk;

typedef struct sceSeqMidiChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int maxMidiNumber;
  unsigned int midiOffsetAddr[];
} sceSeqMidiChunk;

typedef struct sceSeqSongChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int maxSongNumber;
  unsigned int songOffsetAddr[];
} sceSeqSongChunk;

typedef struct sceSeqMidiCompBlock_
{
  u16 compOption;
  u16 compTableSize;
  u8 compTable[];
} sceSeqMidiCompBlock;

typedef struct sceSeqMidiDataBlock_
{
  unsigned int sequenceDataOffset;
  u16 Division;
  sceSeqMidiCompBlock compBlock[];
} sceSeqMidiDataBlock;

typedef struct SceSdSqMidiData_
{
  u32 readStatus;
  u32 midiNumber;
  sceSeqMidiDataBlock *midiData;
  u32 offset;
  u32 nextOffset;
  u32 division;
  u32 compMode;
  u32 compTableSize;
  u32 deltaTime;
  u8 lastStatus;
  u8 reserve[3];
  u32 messageLength;
  u8 message[8];
  u32 originalMessageLength;
  u8 originalMessage[12];
} SceSdSqMidiData;

typedef struct SceSdSqSongData_
{
  u32 readStatus;
  u32 songNumber;
  void *topAddr;
  u32 offset;
  u32 nextOffset;
  u8 message[3];
  u8 reserve;
} SceSdSqSongData;

struct SceSdSqCompTableData_
{
  u8 status;
  u8 data;
};

typedef struct SceSdSqCompTableData_ SceSdSqCompTableData;
typedef struct SceSdSqCompTableData_ SceSdSqPolyKeyData;

typedef struct SceSdSqCompTableNoteOnEvent_
{
  u8 status;
  u8 note;
  u8 velocity;
  u8 reserve;
} SceSdSqCompTableNoteOnEvent;

typedef struct sceSeqSeSequenceChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int maxSeSequenceSetNumber;
  unsigned int tableOffset;
  u8 seSequenceMasterVolume;
  char seSequenceMasterPanpot;
  u16 seSequenceMasterTimeScale;
  unsigned int dmy0;
  unsigned int dmy1;
  unsigned int seSequenceSetOffsetAddr[];
} sceSeqSeSequenceChunk;

struct sdsq_info
{
  sceSeqVersionChunk *m_vers;
  sceSeqHeaderChunk *m_sequ;
  sceSeqMidiChunk *m_midi;
  sceSeqSongChunk *m_song;
};

//-------------------------------------------------------------------------
// Function declarations

int do_get_vers_sequ_chunk(sceSeqVersionChunk *indata, struct sdsq_info *dinfo);
int do_get_midi_chunk(void *indata, struct sdsq_info *dinfo);
int do_get_song_chunk(void *indata, struct sdsq_info *dinfo);
int do_get_midi_data_block(void *indata, unsigned int idx, sceSeqMidiDataBlock **datablk);
int sceSdSqGetMaxMidiNumber(void *addr);
int sceSdSqGetMaxSongNumber(void *addr);
int sceSdSqInitMidiData(void *addr, u32 midiNumber, SceSdSqMidiData *midiData);
int sceSdSqReadMidiData(SceSdSqMidiData *midiData);
int sceSdSqInitSongData(void *addr, u32 songNumber, SceSdSqSongData *songData);
int sceSdSqReadSongData(SceSdSqSongData *songData);
int sceSdSqGetMaxCompTableIndex(void *addr, u32 midiNumber);
int sceSdSqGetCompTableOffset(void *addr, u32 midiNumber, u32 *offset);
int sceSdSqGetCompTableDataByIndex(void *addr, u32 midiNumber, u32 compTableIndex, SceSdSqCompTableData *data);
int sceSdSqGetNoteOnEventByPolyKeyPress(void *addr, u32 midiNumber, SceSdSqPolyKeyData *pData, SceSdSqCompTableNoteOnEvent *kData);
int sceSdSqCopyMidiData(SceSdSqMidiData *to, const SceSdSqMidiData *from);
int sceSdSqCopySongData(SceSdSqSongData *to, const SceSdSqSongData *from);
int _start(int ac);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_sdsq;

//----- (00400060) --------------------------------------------------------
int do_get_vers_sequ_chunk(sceSeqVersionChunk *indata, struct sdsq_info *dinfo)
{
  dinfo->m_vers = 0;
  dinfo->m_sequ = 0;
  dinfo->m_midi = 0;
  dinfo->m_song = 0;
  dinfo->m_vers = indata;
  if ( indata->Creator != 0x53434549 || indata->Type != 0x56657273 )
  {
    dinfo->m_vers = 0;
    return 0x8104000E;
  }
  if ( (indata->chunkSize & 0x80000000) )
  {
    dinfo->m_vers = 0;
    return 0x8104002F;
  }
  dinfo->m_sequ = (sceSeqHeaderChunk *)((char *)indata + indata->chunkSize);
  if ( dinfo->m_sequ->Creator != 0x53434549 || dinfo->m_sequ->Type != 0x53657175 )
  {
    dinfo->m_vers = 0;
    dinfo->m_sequ = 0;
    return 0x8104002F;
  }
  return 0;
}

//----- (00400108) --------------------------------------------------------
int do_get_midi_chunk(void *indata, struct sdsq_info *dinfo)
{
  if ( dinfo->m_sequ->midiChunkAddr == 0xFFFFFFFF )
    return 0x81049024;
  if ( (dinfo->m_sequ->midiChunkAddr & 0x80000000) )
    return 0x8104002F;
  dinfo->m_midi = (sceSeqMidiChunk *)((char *)indata + dinfo->m_sequ->midiChunkAddr);
  if ( dinfo->m_midi->Creator != 0x53434549 || dinfo->m_midi->Type != 0x4D696469 )
  {
    dinfo->m_midi = 0;
    return 0x8104002F;
  }
  return 0;
}

//----- (00400174) --------------------------------------------------------
int do_get_song_chunk(void *indata, struct sdsq_info *dinfo)
{
  if ( dinfo->m_sequ->songChunkAddr == 0xFFFFFFFF )
    return 0x81049025;
  if ( (dinfo->m_sequ->songChunkAddr & 0x80000000) )
    return 0x8104002F;
  dinfo->m_song = (sceSeqSongChunk *)((char *)indata + dinfo->m_sequ->songChunkAddr);
  if ( dinfo->m_song->Creator != 0x53434549 || dinfo->m_song->Type != 0x536F6E67 )
  {
    dinfo->m_song = 0;
    return 0x8104002F;
  }
  return 0;
}

//----- (004001E0) --------------------------------------------------------
int do_get_midi_data_block(void *indata, unsigned int idx, sceSeqMidiDataBlock **datablk)
{
  int result; // $v0
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)indata, &dinfo);
  if ( result )
    return result;
  result = do_get_midi_chunk(indata, &dinfo);
  if ( result )
    return result;
  if ( dinfo.m_midi->maxMidiNumber < idx )
    return 0x81049026;
  if ( dinfo.m_midi->midiOffsetAddr[idx] == 0xFFFFFFFF )
    return 0x81049026;
  *datablk = (sceSeqMidiDataBlock *)((char *)dinfo.m_midi + dinfo.m_midi->midiOffsetAddr[idx]);
  return 0;
}

//----- (00400280) --------------------------------------------------------
int sceSdSqGetMaxMidiNumber(void *addr)
{
  int result; // $v0
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)addr, &dinfo);
  if ( result )
    return result;
  result = do_get_midi_chunk(addr, &dinfo);
  if ( result )
    return result;
  return dinfo.m_midi->maxMidiNumber;
}

//----- (004002CC) --------------------------------------------------------
int sceSdSqGetMaxSongNumber(void *addr)
{
  int result; // $v0
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)addr, &dinfo);
  if ( result )
    return result;
  result = do_get_song_chunk(addr, &dinfo);
  if ( result )
    return result;
  return dinfo.m_song->maxSongNumber;
}

//----- (00400318) --------------------------------------------------------
int sceSdSqInitMidiData(void *addr, u32 midiNumber, SceSdSqMidiData *midiData)
{
  int result; // $v0
  sceSeqMidiDataBlock *dblk; // $a1
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)addr, &dinfo);
  if ( result )
    return result;
  result = do_get_midi_chunk(addr, &dinfo);
  if ( result )
    return result;
  if ( dinfo.m_midi->maxMidiNumber < midiNumber )
    return 0x81049026;
  if ( dinfo.m_midi->midiOffsetAddr[midiNumber] == 0xFFFFFFFF )
    return 0x81049026;
  dblk = (sceSeqMidiDataBlock *)((char *)dinfo.m_midi + dinfo.m_midi->midiOffsetAddr[midiNumber]);
  // Unofficial: the following call was inlined
  memset(midiData, 0, sizeof(SceSdSqMidiData));
  midiData->midiData = dblk;
  midiData->midiNumber = midiNumber;
  midiData->nextOffset = dblk->sequenceDataOffset;
  midiData->messageLength = 1;
  midiData->originalMessageLength = 1;
  midiData->division = dblk->Division;
  midiData->compMode = ( midiData->nextOffset == 6 ) ? 0 : 1;
  midiData->compTableSize = ( midiData->nextOffset == 6 ) ? 0 : dblk->compBlock[0].compTableSize;
  midiData->readStatus = 0;
  return 0;
}

//----- (00400424) --------------------------------------------------------
int sceSdSqReadMidiData(SceSdSqMidiData *midiData)
{
  char niceflag; // $t1
  u8 cur_message; // $a0
  sceSeqMidiDataBlock *midiData_1; // $a1
  u32 nextOffset; // $v0
  u8 lastStatus; // $t0
  u8 *midiData_offs; // $a1
  u8 midiData_curval1; // $v1
  int midiData_curval1_1; // $a0
  u8 midiData_curval2; // $a0
  u8 *midiData_offs_plusone; // $a1
  u32 nextMessageLength; // $v1
  u8 midiData_curval4; // $v1
  u8 *currofssplusone; // $a1
  int someoffsx; // $v1
  u8 *someaddoffsone; // $a1
  int i; // $a3
  u8 midiData_curval7; // $a0
  int msg2ew; // $v1
  int endflg;

  endflg = 3;
  niceflag = 0;
  if ( midiData->readStatus )
    return 0x81048001;
  if ( !midiData->originalMessageLength )
  {
    midiData->readStatus = 2;
    return 0x8104002F;
  }
  cur_message = midiData->message[midiData->originalMessageLength + 11];
  midiData_1 = midiData->midiData;
  nextOffset = midiData->nextOffset;
  lastStatus = midiData->lastStatus;
  midiData->originalMessageLength = 0;
  midiData->messageLength = 0;
  midiData_offs = (u8 *)midiData_1 + nextOffset;
  midiData->offset = nextOffset;
  midiData_curval1_1 = 0;
  if ( !(cur_message & 0x80) || lastStatus == 255 )
  {
    midiData_curval1 = *midiData_offs;
    midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
    ++midiData->originalMessageLength;
    ++midiData_offs;
    midiData_curval1_1 = midiData_curval1 & 0x7F;
    while ( midiData_curval1 & 0x80 )
    {
      midiData_curval1 = *midiData_offs++;
      midiData->originalMessage[midiData->originalMessageLength++] = midiData_curval1;
      midiData_curval1_1 = (midiData_curval1_1 << 7) + (midiData_curval1 & 0x7F);
    }
  }
  midiData->deltaTime = midiData_curval1_1;
  midiData_curval2 = *midiData_offs;
  midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
  if ( (midiData_curval2 & 0x80) )
  {
    ++midiData_offs;
    ++midiData->originalMessageLength;
  }
  else
  {
    midiData_curval2 = lastStatus;
  }
  midiData->message[0] = midiData_curval2;
  midiData->lastStatus = midiData_curval2;
  switch ( midiData_curval2 & 0xF0 )
  {
    case 0x90:
    case 0xB0:
    case 0xE0:
    {
      endflg = 4;
      break;
    }
    case 0x80:
    case 0xC0:
    case 0xD0:
    {
      break;
    }
    case 0xA0:
    {
      if ( !midiData->compMode )
      {
        endflg = 4;
      }
      else
      {
        midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
        midiData->message[1] = midiData->originalMessage[midiData->originalMessageLength];
        midiData->message[2] = 8 * (midiData->originalMessage[midiData->originalMessageLength] & 0xF);
        midiData->originalMessageLength = midiData->originalMessageLength + 1;
        someoffsx = 2 * ((midiData->message[0] & 0xF) | (midiData->message[1] & 0x70));
        midiData->message[1] = midiData->message[1] & 0x7F;
        midiData_offs_plusone = midiData_offs + 1;
        midiData->message[0] = *((u8 *)&midiData->midiData->compBlock[1].compOption + someoffsx);
        midiData->message[1] = *((u8 *)&midiData->midiData->compBlock[1].compOption + someoffsx + 1);
        midiData->messageLength = 3;
        endflg = 1;
      }
      break;
    }
    case 0xF0:
    {
      if ( midiData_curval2 != 255 )
      {
        midiData->readStatus = 2;
        return 0x8104002F;
      }
      midiData->messageLength = 1;
      midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
      midiData->message[1] = midiData->originalMessage[midiData->originalMessageLength];
      midiData->messageLength = midiData->messageLength + 1;
      midiData->originalMessageLength = midiData->originalMessageLength + 1;
      someaddoffsone = midiData_offs + 1;
      midiData_curval7 = *someaddoffsone;
      midiData->originalMessage[midiData->originalMessageLength] = *someaddoffsone;
      midiData->message[2] = midiData->originalMessage[midiData->originalMessageLength];
      midiData->messageLength = midiData->messageLength + 1;
      midiData_offs_plusone = someaddoffsone + 1;
      ++midiData->originalMessageLength;
      msg2ew = midiData_curval7;
      for ( i = 1; msg2ew >= i; i += 1 )
      {
        midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs_plusone++;
        *(((char *)midiData + i) + 46) = midiData->originalMessage[midiData->originalMessageLength];
        msg2ew = midiData->message[2];
        ++midiData->messageLength;
        ++midiData->originalMessageLength;
      }
      niceflag = 1;
      if ( (*(u32 *)midiData->message & 0xFFFFFF) == 0x2FFF )
        midiData->readStatus = 1;
      endflg = 1;
      break;
    }
    default:
    {
      midiData->readStatus = 2;
      return 0x8104002F;
    }
  }
  if ( endflg >= 4 )
  {
    midiData_curval4 = *midiData_offs;
    midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
    midiData->message[1] = midiData_curval4;
    midiData->originalMessageLength = midiData->originalMessageLength + 1;
    currofssplusone = midiData_offs + 1;
    midiData->originalMessage[midiData->originalMessageLength] = *currofssplusone;
    midiData_offs_plusone = currofssplusone + 1;
    midiData->message[2] = midiData->originalMessage[midiData->originalMessageLength];
    nextMessageLength = 3;
    endflg = 2;
  }
  if ( endflg >= 3 )
  {
    midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
    midiData_offs_plusone = midiData_offs + 1;
    midiData->message[1] = midiData->originalMessage[midiData->originalMessageLength];
    nextMessageLength = 2;
  }
  if ( endflg >= 2 )
  {
    midiData->messageLength = nextMessageLength;
    midiData->originalMessageLength = midiData->originalMessageLength + 1;
  }
  if ( !niceflag )
    midiData->reserve[midiData->messageLength + 6] &= ~0x80u;
  midiData->nextOffset = midiData_offs_plusone - (u8 *)midiData->midiData;
  return 0;
}

//----- (0040081C) --------------------------------------------------------
int sceSdSqInitSongData(void *addr, u32 songNumber, SceSdSqSongData *songData)
{
  int result; // $v0
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)addr, &dinfo);
  if ( result )
    return result;
  result = do_get_song_chunk(addr, &dinfo);
  if ( result )
    return result;
  if ( dinfo.m_song->maxSongNumber < songNumber )
    return 0x81049027;
  if ( dinfo.m_song->songOffsetAddr[songNumber] == 0xFFFFFFFF )
    return 0x81049027;
  // Unofficial: the following call was inlined
  memset(songData, 0, sizeof(SceSdSqSongData));
  songData->songNumber = songNumber;
  songData->readStatus = 0;
  songData->topAddr = (char *)(dinfo.m_song) + dinfo.m_song->songOffsetAddr[songNumber];
  return 0;
}

//----- (004008F0) --------------------------------------------------------
int sceSdSqReadSongData(SceSdSqSongData *songData)
{
  u8 *curOffset; // $a1

  if ( songData->readStatus )
    return 0x81048001;
  curOffset = (u8 *)songData->topAddr + songData->nextOffset;
  if ( (*curOffset & 0xF0) != 160 || (curOffset[1] & 0x80u) )
  {
    songData->readStatus = 2;
    return 0x8104002F;
  }
  songData->offset = songData->nextOffset;
  songData->message[0] = *curOffset;
  songData->message[1] = curOffset[1];
  songData->message[2] = curOffset[2];
  if ( (*(u32 *)songData->message & 0xFFFFFF) == 0x7F7FA0 )
    songData->readStatus = 1;
  else
    songData->nextOffset += 3;
  return 0;
}

//----- (004009B8) --------------------------------------------------------
int sceSdSqGetMaxCompTableIndex(void *addr, u32 midiNumber)
{
  int result; // $v0
  sceSeqMidiDataBlock *dblk; // [sp+10h] [-8h] BYREF

  result = do_get_midi_data_block(addr, midiNumber, &dblk);
  if ( result )
    return result;
  if ( dblk->sequenceDataOffset == 6 )
    return 0x81049028;
  return dblk->compBlock[0].compTableSize >> 1;
}

//----- (00400A0C) --------------------------------------------------------
int sceSdSqGetCompTableOffset(void *addr, u32 midiNumber, u32 *offset)
{
  int result; // $v0
  sceSeqMidiDataBlock *dblk; // [sp+10h] [-8h] BYREF

  result = do_get_midi_data_block(addr, midiNumber, &dblk);
  if ( result )
    return result;
  if ( dblk->sequenceDataOffset == 6 )
    return 0x81049028;
  *offset = (char *)dblk - ((char *)addr - 10);
  return 0;
}

//----- (00400A78) --------------------------------------------------------
int sceSdSqGetCompTableDataByIndex(
        void *addr,
        u32 midiNumber,
        u32 compTableIndex,
        SceSdSqCompTableData *data)
{
  int result; // $v0
  sceSeqMidiDataBlock *dblk; // [sp+10h] [-8h] BYREF

  result = do_get_midi_data_block(addr, midiNumber, &dblk);
  if ( result )
    return result;
  if ( dblk->sequenceDataOffset == 6 )
    return 0x81049028;
  if ( dblk->compBlock[0].compTableSize >> 1 < compTableIndex )
    return 0x81049029;
  data->status = *((u8 *)&dblk->compBlock[1].compOption + (compTableIndex << 1));
  data->data = *((u8 *)&dblk->compBlock[1].compOption + (compTableIndex << 1) + 1);
  return 0;
}

//----- (00400B20) --------------------------------------------------------
int sceSdSqGetNoteOnEventByPolyKeyPress(
        void *addr,
        u32 midiNumber,
        SceSdSqPolyKeyData *pData,
        SceSdSqCompTableNoteOnEvent *kData)
{
  u32 compTableIndex; // $a2
  int result; // $v0
  SceSdSqCompTableData data; // [sp+10h] [-8h] BYREF

  if ( (pData->status & 0xF0) != 160 )
    return 0x8104902A;
  compTableIndex = (pData->status & 0xF) + (pData->data & 0xF0);
  if ( compTableIndex >= 0x80 )
    return 0x8104902A;
  result = sceSdSqGetCompTableDataByIndex(addr, midiNumber, compTableIndex, &data);
  if ( result )
    return result;
  kData->status = data.status;
  kData->note = data.data;
  kData->velocity = 8 * (pData->data & 0xF);
  return 0;
}

//----- (00400BC0) --------------------------------------------------------
int sceSdSqCopyMidiData(SceSdSqMidiData *to, const SceSdSqMidiData *from)
{
  // The following memcpy was inlined
  memcpy(to, from, sizeof(SceSdSqMidiData));
  return 0;
}

//----- (00400C04) --------------------------------------------------------
int sceSdSqCopySongData(SceSdSqSongData *to, const SceSdSqSongData *from)
{
  // The following memcpy was inlined
  memcpy(to, from, sizeof(SceSdSqSongData));
  return 0;
}

//----- (00400C40) --------------------------------------------------------
int _start(int ac)
{
  int regres; // $s0
  int state; // [sp+10h] [-8h] BYREF

  if ( ac < 0 )
  {
    CpuSuspendIntr(&state);
    regres = ReleaseLibraryEntries(&_exp_sdsq);
    CpuResumeIntr(state);
    return ( !regres ) ? 1 : 2;
  }
  CpuSuspendIntr(&state);
  regres = RegisterLibraryEntries(&_exp_sdsq);
  CpuResumeIntr(state);
  return ( !regres ) ? 2 : 1;
}
