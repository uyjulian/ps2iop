
#include "irx_imports.h"

IRX_ID("Sound_Data_SQ", 2, 1);

#define _BYTE u8
#define _WORD u16
#define _DWORD u32
#define BOOL _DWORD

#define __int8 char
#define __int16 short
#define __int32 int

#define u_char unsigned char
#define u_int unsigned int

#define __fastcall
#define __cdecl

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
  unsigned __int16 compOption;
  unsigned __int16 compTableSize;
  unsigned __int8 compTable[];
} sceSeqMidiCompBlock;

typedef struct sceSeqMidiDataBlock_
{
  unsigned int sequenceDataOffset;
  unsigned __int16 Division;
  sceSeqMidiCompBlock compBlock[];
} sceSeqMidiDataBlock;

typedef struct SceSdSqMidiData_
{
  u_int readStatus;
  u_int midiNumber;
  sceSeqMidiDataBlock *midiData;
  u_int offset;
  u_int nextOffset;
  u_int division;
  u_int compMode;
  u_int compTableSize;
  u_int deltaTime;
  u_char lastStatus;
  u_char reserve[3];
  u_int messageLength;
  u_char message[8];
  u_int originalMessageLength;
  u_char originalMessage[12];
} SceSdSqMidiData;

typedef struct SceSdSqSongData_
{
  u_int readStatus;
  u_int songNumber;
  void *topAddr;
  u_int offset;
  u_int nextOffset;
  u_char message[3];
  u_char reserve;
} SceSdSqSongData;

struct SceSdSqCompTableData_
{
  u_char status;
  u_char data;
};

typedef struct SceSdSqCompTableData_ SceSdSqCompTableData;
typedef struct SceSdSqCompTableData_ SceSdSqPolyKeyData;

typedef struct SceSdSqCompTableNoteOnEvent_
{
  u_char status;
  u_char note;
  u_char velocity;
  u_char reserve;
} SceSdSqCompTableNoteOnEvent;

typedef struct sceSeqSeSequenceChunk_
{
  unsigned int Creator;
  unsigned int Type;
  unsigned int chunkSize;
  unsigned int maxSeSequenceSetNumber;
  unsigned int tableOffset;
  unsigned __int8 seSequenceMasterVolume;
  char seSequenceMasterPanpot;
  unsigned __int16 seSequenceMasterTimeScale;
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

void sdsq_1();
int __fastcall do_get_vers_sequ_chunk(sceSeqVersionChunk *indata, struct sdsq_info *dinfo);
int __fastcall do_get_midi_chunk(void *indata, struct sdsq_info *dinfo);
int __fastcall do_get_song_chunk(void *indata, struct sdsq_info *dinfo);
int __fastcall do_get_midi_data_block(void *indata, unsigned int idx, sceSeqMidiDataBlock **datablk);
int __cdecl sceSdSqGetMaxMidiNumber(void *addr);
int __cdecl sceSdSqGetMaxSongNumber(void *addr);
int __cdecl sceSdSqInitMidiData(void *addr, u_int midiNumber, SceSdSqMidiData *midiData);
int __cdecl sceSdSqReadMidiData(SceSdSqMidiData *midiData);
int __cdecl sceSdSqInitSongData(void *addr, u_int songNumber, SceSdSqSongData *songData);
int __cdecl sceSdSqReadSongData(SceSdSqSongData *songData);
int __cdecl sceSdSqGetMaxCompTableIndex(void *addr, u_int midiNumber);
int __cdecl sceSdSqGetCompTableOffset(void *addr, u_int midiNumber, u_int *offset);
int __cdecl sceSdSqGetCompTableDataByIndex(void *addr, u_int midiNumber, u_int compTableIndex, SceSdSqCompTableData *data);
int __cdecl sceSdSqGetNoteOnEventByPolyKeyPress(void *addr, u_int midiNumber, SceSdSqPolyKeyData *pData, SceSdSqCompTableNoteOnEvent *kData);
int __cdecl sceSdSqCopyMidiData(SceSdSqMidiData *to, const SceSdSqMidiData *from);
int __cdecl sceSdSqCopySongData(SceSdSqSongData *to, const SceSdSqSongData *from);
int __fastcall _start(int ac);

//-------------------------------------------------------------------------
// Data declarations

const struct irx_export_table exports =
{
  1103101952u,
  NULL,
  257u,
  0u,
  { 115u, 100u, 115u, 113u, 0u, 0u, 0u, 0u },
  { &_start }
}; // idb


//----- (00400058) --------------------------------------------------------
void sdsq_1()
{
  ;
}

//----- (00400060) --------------------------------------------------------
int __fastcall do_get_vers_sequ_chunk(sceSeqVersionChunk *indata, struct sdsq_info *dinfo)
{
  int result; // $v0
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
        result = 0x8104002F;
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
  return result;
}

//----- (00400108) --------------------------------------------------------
int __fastcall do_get_midi_chunk(void *indata, struct sdsq_info *dinfo)
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
int __fastcall do_get_song_chunk(void *indata, struct sdsq_info *dinfo)
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
int __fastcall do_get_midi_data_block(void *indata, unsigned int idx, sceSeqMidiDataBlock **datablk)
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
// 4001E0: using guessed type _DWORD dinfo[2];

//----- (00400280) --------------------------------------------------------
int __cdecl sceSdSqGetMaxMidiNumber(void *addr)
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
int __cdecl sceSdSqGetMaxSongNumber(void *addr)
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
int __cdecl sceSdSqInitMidiData(void *addr, u_int midiNumber, SceSdSqMidiData *midiData)
{
  int result; // $v0
  unsigned int offs; // $a0
  sceSeqMidiDataBlock *dblk; // $a1
  u_int Division; // $v0
  u_int nextOffset; // $v1
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
// 400318: using guessed type _DWORD dinfo[2];

//----- (00400424) --------------------------------------------------------
int __cdecl sceSdSqReadMidiData(SceSdSqMidiData *midiData)
{
  char niceflag; // $t1
  int result; // $v0
  u_int originalMessageLength; // $v0
  u_char cur_message; // $a0
  sceSeqMidiDataBlock *midiData_1; // $a1
  u_int nextOffset; // $v0
  u_char lastStatus; // $t0
  u_char *midiData_offs; // $a1
  u_char midiData_curval1; // $v1
  int midiData_curval1_1; // $a0
  u_char midiData_curvaladd; // $v1
  u_char midiData_curval2; // $a0
  int midiData_curval2_msk; // $v1
  u_char midiData_curval9; // $v1
  u_int originalMessageLength_3; // $v0
  u_char *midiData_offs_plusone; // $a1
  u_int nextMessageLength; // $v1
  u_char midiData_curval4; // $v1
  u_int originalMessageLength_2; // $v0
  u_char *currofssplusone; // $a1
  u_char midiData_curval5; // $v1
  u_char midiData_curval3; // $v1
  u_int originalMessageLength_1; // $v0
  u_char msg1_tmp1; // $a0
  u_char msg0_tmp1; // $v1
  int someoffsx; // $v1
  u_char midiData_curval6; // $v1
  u_char *someaddoffsone; // $a1
  u_int messageLength; // $v0
  int somindx1; // $a3
  u_int addmsglen; // $v1
  u_char midiData_curval7; // $a0
  u_int somelsglenx; // $v0
  u_char midiData_curval8; // $v1
  char *ptroffscw; // $v0
  int msg2ew; // $v1

  niceflag = 0;
  if ( midiData->readStatus )
    return 0x81048001;
  originalMessageLength = midiData->originalMessageLength;
  if ( !originalMessageLength )
    goto LABEL_42;
  cur_message = midiData->message[originalMessageLength + 11];
  midiData_1 = midiData->midiData;
  nextOffset = midiData->nextOffset;
  lastStatus = midiData->lastStatus;
  midiData->originalMessageLength = 0;
  midiData->messageLength = 0;
  midiData_offs = (u_char *)midiData_1 + nextOffset;
  midiData->offset = nextOffset;
  if ( (cur_message & 0x80) == 0 || lastStatus == 255 )
  {
    midiData_curval1 = *midiData_offs;
    midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
    midiData_curval1_1 = midiData_curval1;
    ++midiData->originalMessageLength;
    ++midiData_offs;
    if ( (midiData_curval1 & 0x80) != 0 )
    {
      midiData_curval1_1 = midiData_curval1 & 0x7F;
      do
      {
        midiData_curvaladd = *midiData_offs++;
        midiData->originalMessage[midiData->originalMessageLength++] = midiData_curvaladd;
        midiData_curval1_1 = (midiData_curval1_1 << 7) + (midiData_curvaladd & 0x7F);
      }
      while ( (midiData_curvaladd & 0x80) != 0 );
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
    goto LABEL_31;
  if ( (midiData_curval2 & 0xF0u) < 0xB1 )
  {
    if ( midiData_curval2_msk != 0x90 )
    {
      if ( (midiData_curval2 & 0xF0u) < 0x91 )
      {
        if ( midiData_curval2_msk != 0x80 )
        {
          midiData->readStatus = 2;
          return 0x8104002F;
        }
        goto LABEL_29;
      }
      if ( midiData_curval2_msk != 0xA0 )
      {
        midiData->readStatus = 2;
        return 0x8104002F;
      }
      if ( midiData->compMode )
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
        midiData->message[0] = *((_BYTE *)&midiData->midiData->compBlock[1].compOption + someoffsx);
        midiData->message[1] = *((_BYTE *)&midiData->midiData->compBlock[1].compOption + someoffsx + 1);
        midiData->messageLength = 3;
        goto LABEL_39;
      }
    }
LABEL_31:
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
    goto LABEL_32;
  }
  if ( midiData_curval2_msk != 208 )
  {
    if ( (midiData_curval2 & 0xF0u) < 0xD1 )
    {
      if ( midiData_curval2_msk != 192 )
      {
        midiData->readStatus = 2;
        return 0x8104002F;
      }
      goto LABEL_29;
    }
    if ( midiData_curval2_msk == 224 )
      goto LABEL_31;
    if ( midiData_curval2_msk != 240 )
    {
      midiData->readStatus = 2;
      return 0x8104002F;
    }
    if ( midiData_curval2 == 255 )
    {
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
      if ( midiData_curval7 )
      {
        do
        {
          midiData_curval8 = *midiData_offs_plusone++;
          midiData->originalMessage[midiData->originalMessageLength] = midiData_curval8;
          ptroffscw = (char *)midiData + somindx1++;
          ptroffscw[46] = midiData_curval8;
          msg2ew = midiData->message[2];
          ++midiData->messageLength;
          ++midiData->originalMessageLength;
        }
        while ( msg2ew >= somindx1 );
      }
      niceflag = 1;
      if ( (*(_DWORD *)midiData->message & 0xFFFFFF) == 0x2FFF )
        midiData->readStatus = 1;
      goto LABEL_39;
    }
LABEL_42:
    midiData->readStatus = 2;
    return 0x8104002F;
  }
LABEL_29:
  midiData_curval9 = *midiData_offs;
  midiData->originalMessage[midiData->originalMessageLength] = *midiData_offs;
  originalMessageLength_3 = midiData->originalMessageLength;
  midiData_offs_plusone = midiData_offs + 1;
  midiData->message[1] = midiData_curval9;
  nextMessageLength = 2;
LABEL_32:
  midiData->messageLength = nextMessageLength;
  midiData->originalMessageLength = originalMessageLength_3 + 1;
LABEL_39:
  if ( !niceflag )
    midiData->reserve[midiData->messageLength + 6] &= ~0x80u;
  result = 0;
  midiData->nextOffset = midiData_offs_plusone - (u_char *)midiData->midiData;
  return result;
}

//----- (0040081C) --------------------------------------------------------
int __cdecl sceSdSqInitSongData(void *addr, u_int songNumber, SceSdSqSongData *songData)
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
// 40081C: using guessed type _DWORD dinfo[3];

//----- (004008F0) --------------------------------------------------------
int __cdecl sceSdSqReadSongData(SceSdSqSongData *songData)
{
  u_int nextOffset; // $a0
  u_char *curOffset; // $a1

  if ( songData->readStatus )
    return 0x81048001;
  nextOffset = songData->nextOffset;
  curOffset = (u_char *)songData->topAddr + nextOffset;
  if ( (*curOffset & 0xF0) == 160 && (curOffset[1] & 0x80u) == 0 )
  {
    songData->offset = nextOffset;
    songData->message[0] = *curOffset;
    songData->message[1] = curOffset[1];
    songData->message[2] = curOffset[2];
    if ( (*(_DWORD *)songData->message & 0xFFFFFF) == 0x7F7FA0 )
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
int __cdecl sceSdSqGetMaxCompTableIndex(void *addr, u_int midiNumber)
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
int __cdecl sceSdSqGetCompTableOffset(void *addr, u_int midiNumber, u_int *offset)
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
int __cdecl sceSdSqGetCompTableDataByIndex(
        void *addr,
        u_int midiNumber,
        u_int compTableIndex,
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
      data->status = *((_BYTE *)&dblk->compBlock[1].compOption + 2 * compTableIndex);
      result = 0;
      data->data = *((_BYTE *)&dblk->compBlock[1].compOption + 2 * compTableIndex + 1);
    }
  }
  return result;
}

//----- (00400B20) --------------------------------------------------------
int __cdecl sceSdSqGetNoteOnEventByPolyKeyPress(
        void *addr,
        u_int midiNumber,
        SceSdSqPolyKeyData *pData,
        SceSdSqCompTableNoteOnEvent *kData)
{
  u_char status; // $a2
  u_int compTableIndex; // $a2
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
int __cdecl sceSdSqCopyMidiData(SceSdSqMidiData *to, const SceSdSqMidiData *from)
{
  const SceSdSqMidiData *endptr; // $v0
  u_int midiNumber; // $a2
  sceSeqMidiDataBlock *midiData; // $a3
  u_int offset; // $t0

  endptr = (const SceSdSqMidiData *)&from->originalMessage[8];
  do
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
  while ( from != endptr );
  to->readStatus = from->readStatus;
  return 0;
}

//----- (00400C04) --------------------------------------------------------
int __cdecl sceSdSqCopySongData(SceSdSqSongData *to, const SceSdSqSongData *from)
{
  u_int songNumber; // $a2
  void *topAddr; // $a3
  u_int offset; // $t0
  int cpywtmp1; // $a2

  songNumber = from->songNumber;
  topAddr = from->topAddr;
  offset = from->offset;
  to->readStatus = from->readStatus;
  to->songNumber = songNumber;
  to->topAddr = topAddr;
  to->offset = offset;
  cpywtmp1 = *(_DWORD *)from->message;
  to->nextOffset = from->nextOffset;
  *(_DWORD *)to->message = cpywtmp1;
  return 0;
}

//----- (00400C40) --------------------------------------------------------
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
