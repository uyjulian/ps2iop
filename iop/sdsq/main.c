
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
  signed int chunkSize; // $v0
  sceSeqSeSequenceChunk *chk; // $a0

  dinfo->m_vers = 0;
  dinfo->m_sequ = 0;
  dinfo->m_midi = 0;
  dinfo->m_song = 0;
  dinfo->m_vers = indata;
  if ( indata->Creator == 0x53434549 && indata->Type == 0x56657273 )
  {
    chunkSize = indata->chunkSize;
    chk = (sceSeqSeSequenceChunk *)((char *)indata + chunkSize);
    if ( chunkSize >= 0 )
    {
      dinfo->m_sequ = (sceSeqHeaderChunk *)chk;
      if ( chk->Creator == 0x53434549 && chk->Type == 0x53657175 )
      {
        return 0;
      }
      else
      {
        dinfo->m_vers = 0;
        dinfo->m_sequ = 0;
      }
    }
    else
    {
      dinfo->m_vers = 0;
      return 0x8104002F;
    }
  }
  else
  {
    dinfo->m_vers = 0;
    return 0x8104000E;
  }
  return 0x8104002F;
}

//----- (00400108) --------------------------------------------------------
int do_get_midi_chunk(void *indata, struct sdsq_info *dinfo)
{
  signed int midiChunkAddr; // $a0
  sceSeqMidiChunk *chk; // $a0

  midiChunkAddr = dinfo->m_sequ->midiChunkAddr;
  if ( midiChunkAddr == -1 )
    return 0x81049024;
  if ( midiChunkAddr < 0 )
    return 0x8104002F;
  chk = (sceSeqMidiChunk *)((char *)indata + midiChunkAddr);
  dinfo->m_midi = chk;
  if ( chk->Creator != 0x53434549 || chk->Type != 0x4D696469 )
  {
    dinfo->m_midi = 0;
    return 0x8104002F;
  }
  return 0;
}

//----- (00400174) --------------------------------------------------------
int do_get_song_chunk(void *indata, struct sdsq_info *dinfo)
{
  signed int songChunkAddr; // $a0
  sceSeqSongChunk *chk; // $a0

  songChunkAddr = dinfo->m_sequ->songChunkAddr;
  if ( songChunkAddr == -1 )
    return 0x81049025;
  if ( songChunkAddr < 0 )
    return 0x8104002F;
  chk = (sceSeqSongChunk *)((char *)indata + songChunkAddr);
  dinfo->m_song = chk;
  if ( chk->Creator != 0x53434549 || chk->Type != 0x536F6E67 )
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
  unsigned int offs; // $a0
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)indata, &dinfo);
  if ( !result )
  {
    result = do_get_midi_chunk(indata, &dinfo);
    if ( !result )
    {
      if ( dinfo.m_midi->maxMidiNumber < idx )
        return 0x81049026;
      offs = dinfo.m_midi->midiOffsetAddr[idx];
      if ( offs == -1 )
      {
        return 0x81049026;
      }
      else
      {
        *datablk = (sceSeqMidiDataBlock *)((char *)dinfo.m_midi + offs);
        return 0;
      }
    }
  }
  return result;
}

//----- (00400280) --------------------------------------------------------
int sceSdSqGetMaxMidiNumber(void *addr)
{
  int result; // $v0
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)addr, &dinfo);
  if ( !result )
  {
    result = do_get_midi_chunk(addr, &dinfo);
    if ( !result )
      return dinfo.m_midi->maxMidiNumber;
  }
  return result;
}

//----- (004002CC) --------------------------------------------------------
int sceSdSqGetMaxSongNumber(void *addr)
{
  int result; // $v0
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)addr, &dinfo);
  if ( !result )
  {
    result = do_get_song_chunk(addr, &dinfo);
    if ( !result )
      return dinfo.m_song->maxSongNumber;
  }
  return result;
}

//----- (00400318) --------------------------------------------------------
int sceSdSqInitMidiData(void *addr, u32 midiNumber, SceSdSqMidiData *midiData)
{
  int result; // $v0
  unsigned int offs; // $a0
  sceSeqMidiDataBlock *dblk; // $a1
  u32 Division; // $v0
  u32 nextOffset; // $v1
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)addr, &dinfo);
  if ( !result )
  {
    result = do_get_midi_chunk(addr, &dinfo);
    if ( !result )
    {
      if ( dinfo.m_midi->maxMidiNumber < midiNumber )
        return 0x81049026;
      offs = dinfo.m_midi->midiOffsetAddr[midiNumber];
      dblk = (sceSeqMidiDataBlock *)((char *)dinfo.m_midi + offs);
      if ( offs == -1 )
      {
        return 0x81049026;
      }
      else
      {
        // Unofficial: the following call was inlined
        memset(midiData, 0, sizeof(SceSdSqMidiData));
        midiData->midiData = dblk;
        midiData->midiNumber = midiNumber;
        midiData->nextOffset = dblk->sequenceDataOffset;
        Division = dblk->Division;
        nextOffset = midiData->nextOffset;
        midiData->messageLength = 1;
        midiData->originalMessageLength = 1;
        midiData->division = Division;
        if ( nextOffset == 6 )
        {
          midiData->compMode = 0;
        }
        else
        {
          midiData->compMode = 1;
          midiData->compTableSize = dblk->compBlock[0].compTableSize;
        }
        midiData->readStatus = 0;
        return 0;
      }
    }
  }
  return result;
}

//----- (00400424) --------------------------------------------------------
int sceSdSqReadMidiData(SceSdSqMidiData *midiData)
{
  char niceflag; // $t1
  u32 originalMessageLength; // $v0
  u8 cur_message; // $a0
  sceSeqMidiDataBlock *midiData_1; // $a1
  u32 nextOffset; // $v0
  u8 lastStatus; // $t0
  u8 *midiData_offs; // $a1
  u8 midiData_curval1; // $v1
  int midiData_curval1_1; // $a0
  u8 midiData_curval2; // $a0
  int midiData_curval2_msk; // $v1
  u8 midiData_curval9; // $v1
  u32 originalMessageLength_3; // $v0
  u8 *midiData_offs_plusone; // $a1
  u32 nextMessageLength; // $v1
  u8 midiData_curval4; // $v1
  u32 originalMessageLength_2; // $v0
  u8 *currofssplusone; // $a1
  u8 midiData_curval5; // $v1
  u8 midiData_curval3; // $v1
  u32 originalMessageLength_1; // $v0
  u8 msg1_tmp1; // $a0
  u8 msg0_tmp1; // $v1
  int someoffsx; // $v1
  u8 midiData_curval6; // $v1
  u8 *someaddoffsone; // $a1
  u32 messageLength; // $v0
  int somindx1; // $a3
  u32 addmsglen; // $v1
  u8 midiData_curval7; // $a0
  u32 somelsglenx; // $v0
  u8 midiData_curval8; // $v1
  char *ptroffscw; // $v0
  int msg2ew; // $v1
  int endflg;

  endflg = 3;
  niceflag = 0;
  if ( midiData->readStatus )
    return 0x81048001;
  originalMessageLength = midiData->originalMessageLength;
  if ( !originalMessageLength )
  {
    midiData->readStatus = 2;
    return 0x8104002F;
  }
  cur_message = midiData->message[originalMessageLength + 11];
  midiData_1 = midiData->midiData;
  nextOffset = midiData->nextOffset;
  lastStatus = midiData->lastStatus;
  midiData->originalMessageLength = 0;
  midiData->messageLength = 0;
  midiData_offs = (u8 *)midiData_1 + nextOffset;
  midiData->offset = nextOffset;
  if ( (cur_message & 0x80) == 0 || lastStatus == 255 )
  {
    midiData_curval1 = *midiData_offs;
    midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
    midiData_curval1_1 = midiData_curval1;
    ++midiData->originalMessageLength;
    ++midiData_offs;
    midiData_curval1_1 = midiData_curval1 & 0x7F;
    while ( midiData_curval1 & 0x80 )
    {
      midiData_curval1 = *midiData_offs++;
      midiData->originalMessage[midiData->originalMessageLength++] = midiData_curval1;
      midiData_curval1_1 = (midiData_curval1_1 << 7) + (midiData_curval1 & 0x7F);
    }
    midiData->deltaTime = midiData_curval1_1;
  }
  else
  {
    midiData->deltaTime = 0;
  }
  midiData_curval2 = *midiData_offs;
  midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
  if ( (midiData_curval2 & 0x80) != 0 )
  {
    ++midiData_offs;
    ++midiData->originalMessageLength;
  }
  else
  {
    midiData_curval2 = lastStatus;
  }
  midiData->message[0] = midiData_curval2;
  midiData_curval2_msk = midiData_curval2 & 0xF0;
  midiData->lastStatus = midiData_curval2;
  if ( midiData_curval2_msk == 0xB0 )
  {
    endflg = 4;
  }
  else
  {
    if ( (midiData_curval2 & 0xF0u) < 0xB1 )
    {
      if ( midiData_curval2_msk == 0x90 )
      {
        endflg = 4;
      }
      else
      {
        if ( (midiData_curval2 & 0xF0u) < 0x91 )
        {
          if ( midiData_curval2_msk != 0x80 )
          {
            midiData->readStatus = 2;
            return 0x8104002F;
          }
        }
        else
        {
          if ( midiData_curval2_msk != 0xA0 )
          {
            midiData->readStatus = 2;
            return 0x8104002F;
          }
          if ( !midiData->compMode )
          {
            endflg = 4;
          }
          else
          {
            midiData_curval3 = *midiData_offs;
            midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
            midiData->message[1] = midiData_curval3;
            originalMessageLength_1 = midiData->originalMessageLength;
            msg1_tmp1 = midiData->message[1];
            midiData->message[2] = 8 * (midiData_curval3 & 0xF);
            msg0_tmp1 = midiData->message[0];
            midiData->originalMessageLength = originalMessageLength_1 + 1;
            midiData->message[1] = msg1_tmp1 & 0x7F;
            someoffsx = 2 * ((msg0_tmp1 & 0xF) | (msg1_tmp1 & 0x70));
            midiData_offs_plusone = midiData_offs + 1;
            midiData->message[0] = *((u8 *)&midiData->midiData->compBlock[1].compOption + someoffsx);
            midiData->message[1] = *((u8 *)&midiData->midiData->compBlock[1].compOption + someoffsx + 1);
            midiData->messageLength = 3;
            endflg = 1;
          }
        }
      }
    }
    else
    {
      if ( midiData_curval2_msk != 208 )
      {
        if ( (midiData_curval2 & 0xF0u) < 0xD1 )
        {
          if ( midiData_curval2_msk != 192 )
          {
            midiData->readStatus = 2;
            return 0x8104002F;
          }
        }
        else
        {
          if ( midiData_curval2_msk == 224 )
          {
            endflg = 4;
          }
          else
          {
            if ( midiData_curval2_msk != 240 )
            {
              midiData->readStatus = 2;
              return 0x8104002F;
            }
            if ( midiData_curval2 != 255 )
            {
              midiData->readStatus = 2;
              return 0x8104002F;
            }
            midiData->messageLength = 1;
            midiData_curval6 = *midiData_offs;
            someaddoffsone = midiData_offs + 1;
            midiData->originalMessage[midiData->originalMessageLength] = midiData_curval6;
            messageLength = midiData->messageLength;
            somindx1 = 1;
            midiData->message[1] = midiData_curval6;
            addmsglen = midiData->originalMessageLength + 1;
            midiData->messageLength = messageLength + 1;
            midiData->originalMessageLength = addmsglen;
            midiData_curval7 = *someaddoffsone;
            midiData->originalMessage[addmsglen] = *someaddoffsone;
            somelsglenx = midiData->messageLength;
            midiData_offs_plusone = someaddoffsone + 1;
            midiData->message[2] = midiData_curval7;
            midiData->messageLength = somelsglenx + 1;
            ++midiData->originalMessageLength;
            for ( msg2ew = midiData_curval7; msg2ew >= somindx1; somindx1 += 1 )
            {
              midiData_curval8 = *midiData_offs_plusone++;
              midiData->originalMessage[midiData->originalMessageLength] = midiData_curval8;
              ptroffscw = (char *)midiData + somindx1;
              ptroffscw[46] = midiData_curval8;
              msg2ew = midiData->message[2];
              ++midiData->messageLength;
              ++midiData->originalMessageLength;
            }
            niceflag = 1;
            if ( (*(u32 *)midiData->message & 0xFFFFFF) == 0x2FFF )
              midiData->readStatus = 1;
            endflg = 1;
          }
        }
      }
    }
  }
  if ( endflg >= 4 )
  {
    midiData_curval4 = *midiData_offs;
    midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
    originalMessageLength_2 = midiData->originalMessageLength;
    currofssplusone = midiData_offs + 1;
    midiData->message[1] = midiData_curval4;
    midiData->originalMessageLength = ++originalMessageLength_2;
    midiData_curval5 = *currofssplusone;
    midiData->originalMessage[originalMessageLength_2] = *currofssplusone;
    originalMessageLength_3 = midiData->originalMessageLength;
    midiData_offs_plusone = currofssplusone + 1;
    midiData->message[2] = midiData_curval5;
    nextMessageLength = 3;
    endflg = 2;
  }
  if ( endflg >= 3 )
  {
    midiData_curval9 = *midiData_offs;
    midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
    originalMessageLength_3 = midiData->originalMessageLength;
    midiData_offs_plusone = midiData_offs + 1;
    midiData->message[1] = midiData_curval9;
    nextMessageLength = 2;
  }
  if ( endflg >= 2 )
  {
    midiData->messageLength = nextMessageLength;
    midiData->originalMessageLength = originalMessageLength_3 + 1;
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
  sceSeqSongChunk *m_song; // $v1
  unsigned int offs; // $a0
  struct sdsq_info dinfo; // [sp+10h] [-10h] BYREF

  result = do_get_vers_sequ_chunk((sceSeqVersionChunk *)addr, &dinfo);
  if ( !result )
  {
    result = do_get_song_chunk(addr, &dinfo);
    if ( !result )
    {
      if ( dinfo.m_song->maxSongNumber < songNumber )
        return 0x81049027;
      if ( dinfo.m_song->songOffsetAddr[songNumber] == -1 )
      {
        return 0x81049027;
      }
      else
      {
        // Unofficial: the following call was inlined
        memset(songData, 0, sizeof(SceSdSqSongData));
        songData->songNumber = songNumber;
        m_song = dinfo.m_song;
        offs = dinfo.m_song->songOffsetAddr[songNumber];
        result = 0;
        songData->readStatus = 0;
        songData->topAddr = (char *)m_song + offs;
      }
    }
  }
  return result;
}

//----- (004008F0) --------------------------------------------------------
int sceSdSqReadSongData(SceSdSqSongData *songData)
{
  u32 nextOffset; // $a0
  u8 *curOffset; // $a1

  if ( songData->readStatus )
    return 0x81048001;
  nextOffset = songData->nextOffset;
  curOffset = (u8 *)songData->topAddr + nextOffset;
  if ( (*curOffset & 0xF0) == 160 && (curOffset[1] & 0x80u) == 0 )
  {
    songData->offset = nextOffset;
    songData->message[0] = *curOffset;
    songData->message[1] = curOffset[1];
    songData->message[2] = curOffset[2];
    if ( (*(u32 *)songData->message & 0xFFFFFF) == 0x7F7FA0 )
      songData->readStatus = 1;
    else
      songData->nextOffset += 3;
    return 0;
  }
  else
  {
    songData->readStatus = 2;
    return 0x8104002F;
  }
}

//----- (004009B8) --------------------------------------------------------
int sceSdSqGetMaxCompTableIndex(void *addr, u32 midiNumber)
{
  int result; // $v0
  sceSeqMidiDataBlock *dblk; // [sp+10h] [-8h] BYREF

  result = do_get_midi_data_block(addr, midiNumber, &dblk);
  if ( !result )
  {
    if ( dblk->sequenceDataOffset == 6 )
      return 0x81049028;
    else
      return dblk->compBlock[0].compTableSize >> 1;
  }
  return result;
}

//----- (00400A0C) --------------------------------------------------------
int sceSdSqGetCompTableOffset(void *addr, u32 midiNumber, u32 *offset)
{
  int result; // $v0
  sceSeqMidiDataBlock *dblk; // [sp+10h] [-8h] BYREF

  result = do_get_midi_data_block(addr, midiNumber, &dblk);
  if ( !result )
  {
    if ( dblk->sequenceDataOffset == 6 )
    {
      return 0x81049028;
    }
    else
    {
      *offset = (char *)dblk - ((char *)addr - 10);
      return 0;
    }
  }
  return result;
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
  if ( !result )
  {
    if ( dblk->sequenceDataOffset == 6 )
    {
      return 0x81049028;
    }
    else if ( dblk->compBlock[0].compTableSize >> 1 < compTableIndex )
    {
      return 0x81049029;
    }
    else
    {
      data->status = *((u8 *)&dblk->compBlock[1].compOption + 2 * compTableIndex);
      result = 0;
      data->data = *((u8 *)&dblk->compBlock[1].compOption + 2 * compTableIndex + 1);
    }
  }
  return result;
}

//----- (00400B20) --------------------------------------------------------
int sceSdSqGetNoteOnEventByPolyKeyPress(
        void *addr,
        u32 midiNumber,
        SceSdSqPolyKeyData *pData,
        SceSdSqCompTableNoteOnEvent *kData)
{
  u8 status; // $a2
  u32 compTableIndex; // $a2
  int result; // $v0
  SceSdSqCompTableData data; // [sp+10h] [-8h] BYREF

  status = pData->status;
  if ( (status & 0xF0) != 160 )
    return 0x8104902A;
  compTableIndex = (status & 0xF) + (pData->data & 0xF0);
  if ( compTableIndex >= 0x80 )
    return 0x8104902A;
  result = sceSdSqGetCompTableDataByIndex(addr, midiNumber, compTableIndex, &data);
  if ( !result )
  {
    kData->status = data.status;
    kData->note = data.data;
    result = 0;
    kData->velocity = 8 * (pData->data & 0xF);
  }
  return result;
}

//----- (00400BC0) --------------------------------------------------------
int sceSdSqCopyMidiData(SceSdSqMidiData *to, const SceSdSqMidiData *from)
{
  const SceSdSqMidiData *endptr; // $v0
  u32 midiNumber; // $a2
  sceSeqMidiDataBlock *midiData; // $a3
  u32 offset; // $t0

  endptr = (const SceSdSqMidiData *)&from->originalMessage[8];
  while ( from != endptr )
  {
    midiNumber = from->midiNumber;
    midiData = from->midiData;
    offset = from->offset;
    to->readStatus = from->readStatus;
    to->midiNumber = midiNumber;
    to->midiData = midiData;
    to->offset = offset;
    from = (const SceSdSqMidiData *)((char *)from + 16);
    to = (SceSdSqMidiData *)((char *)to + 16);
  }
  to->readStatus = from->readStatus;
  return 0;
}

//----- (00400C04) --------------------------------------------------------
int sceSdSqCopySongData(SceSdSqSongData *to, const SceSdSqSongData *from)
{
  u32 songNumber; // $a2
  void *topAddr; // $a3
  u32 offset; // $t0
  int cpywtmp1; // $a2

  songNumber = from->songNumber;
  topAddr = from->topAddr;
  offset = from->offset;
  to->readStatus = from->readStatus;
  to->songNumber = songNumber;
  to->topAddr = topAddr;
  to->offset = offset;
  cpywtmp1 = *(u32 *)from->message;
  to->nextOffset = from->nextOffset;
  *(u32 *)to->message = cpywtmp1;
  return 0;
}

//----- (00400C40) --------------------------------------------------------
int _start(int ac)
{
  int unregres; // $s0
  int regres; // $s0
  int state; // [sp+10h] [-8h] BYREF

  if ( ac >= 0 )
  {
    CpuSuspendIntr(&state);
    regres = RegisterLibraryEntries(&_exp_sdsq);
    CpuResumeIntr(state);
    if ( !regres )
      return 2;
    return 1;
  }
  else
  {
    CpuSuspendIntr(&state);
    unregres = ReleaseLibraryEntries(&_exp_sdsq);
    CpuResumeIntr(state);
    if ( !unregres )
      return 1;
    return 2;
  }
}
