
#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

int start();
struct RomImgData *__fastcall GetIOPRPStat(u32 *start_addr, u32 *end_addr, struct RomImgData *rid);
struct RomdirFileStat *__fastcall GetFileStatFromImage(struct RomImgData *rid, char *filename, struct RomdirFileStat *rdfs);
const struct ExtInfoFieldEntry *__fastcall do_find_extinfo_entry(struct RomdirFileStat *rdfs, int extinfo_type);
int __fastcall unusedsub_4004B0(int);
int unusednullsub_4004FC();
int __fastcall unused_flash_reset(_DWORD *);
BOOL __fastcall unused_checksig(_DWORD *, _DWORD *, int);
BOOL __fastcall unused_flash_checksig(_DWORD *);
_DWORD *__fastcall unused_flash_probe(_DWORD *);
int *__cdecl QueryBootMode(int mode);
int printf(const char *format, ...);
int __cdecl CpuDisableIntr();
int __cdecl CpuEnableIntr();
int __cdecl write(int fd, void *ptr, int size);
u32 __cdecl QueryMemSize();
char *__cdecl rindex(const char *s, int c);
size_t __cdecl strlen(const char *s);

//-------------------------------------------------------------------------
// Data declarations

char *romgen_eq_str = " ROMGEN="; // idb
char *cpuid_eq_str = ", IOP info (CPUID="; // idb
char *cach_config_eq_str = ", CACH_CONFIG="; // idb


//----- (00400000) --------------------------------------------------------
int start()
{
  int *boot_mode_4; // $s0
  int boot_mode_4_val; // $v1
  int result; // $v0
  int cop0_processor_mode; // $s0
  int romgen_eq_str_len; // $v0
  int cpuid_eq_str_len; // $v0
  int cach_config_eq_str_len; // $v0
  u32 MemSize; // $v0
  char *iop_or_ps_mode_str; // $s0
  int iop_or_ps_mode_str_len; // $v0
  const struct ExtInfoFieldEntry *extinfo_entry; // $v0
  char *extinfo_id_str; // $s0
  char *comma_index; // $s1
  struct RomImgData rid; // [sp+10h] [-20h] BYREF
  struct RomdirFileStat rdfs; // [sp+20h] [-10h] BYREF

  boot_mode_4 = QueryBootMode(4);
  printf("\nPlayStation 2 ======== ");
  if ( !boot_mode_4 )
    goto LABEL_14;
  boot_mode_4_val = *(unsigned __int16 *)boot_mode_4;
  if ( boot_mode_4_val == 1 )
  {
    printf("Soft reboot");
  }
  else if ( *(unsigned __int16 *)boot_mode_4 >= 2u )
  {
    if ( boot_mode_4_val == 2 )
    {
      printf("Update rebooting..");
    }
    else if ( boot_mode_4_val == 3 )
    {
      printf("Update reboot complete");
    }
  }
  else if ( !*(_WORD *)boot_mode_4 )
  {
    printf("Hard reset boot");
  }
  printf("\n");
  result = 1;
  if ( !*(_WORD *)boot_mode_4 )
  {
LABEL_14:
    cop0_processor_mode = _mfc0(0xFu, 0);
    romgen_eq_str_len = strlen(romgen_eq_str);
    write(1, romgen_eq_str, romgen_eq_str_len);
    printf("%04x-%04x", MEMORY[0xBFC00102], MEMORY[0xBFC00100]);
    cpuid_eq_str_len = strlen(cpuid_eq_str);
    write(1, cpuid_eq_str, cpuid_eq_str_len);
    printf("%x", cop0_processor_mode);
    cach_config_eq_str_len = strlen(cach_config_eq_str);
    write(1, cach_config_eq_str, cach_config_eq_str_len);
    MemSize = QueryMemSize();
    printf("%lx, %ldMB", MEMORY[0xFFFE0130], (MemSize + 256) >> 20);
    if ( cop0_processor_mode >= 16 )
    {
      iop_or_ps_mode_str = ", IOP mode)\r\n";
      if ( (MEMORY[0xBF801450] & 8) != 0 )
        iop_or_ps_mode_str = ", PS mode)\r\n";
      iop_or_ps_mode_str_len = strlen(iop_or_ps_mode_str);
      write(1, iop_or_ps_mode_str, iop_or_ps_mode_str_len);
    }
    if ( GetIOPRPStat((u32 *)0xBFC00000, (u32 *)0xBFC10000, &rid) )
    {
      if ( GetFileStatFromImage(&rid, "ROMDIR", &rdfs) )
      {
        extinfo_entry = do_find_extinfo_entry(&rdfs, 3);
        extinfo_id_str = (char *)extinfo_entry->payload;
        if ( extinfo_entry )
        {
          comma_index = rindex((const char *)extinfo_entry->payload, ',');
          if ( !comma_index )
            strlen(extinfo_id_str);
          write(1, " <", 2);
          write(1, extinfo_id_str, comma_index - extinfo_id_str);
          printf(":%ld>\n", (unsigned __int16)extinfo_id_str);
        }
      }
    }
    return 1;
  }
  return result;
}
// 400000: using guessed type int rid[4];

//----- (00400290) --------------------------------------------------------
struct RomImgData *__fastcall GetIOPRPStat(u32 *start_addr, u32 *end_addr, struct RomImgData *rid)
{
  u32 *cur_addr; // $a3
  int cur_offset; // $t0
  u32 *cur_addr_end; // $v1
  struct RomImgData *result; // $v0

  cur_addr = start_addr;
  cur_offset = 0;
  if ( start_addr >= end_addr )
  {
LABEL_9:
    rid->ImageStart = 0;
    return 0;
  }
  else
  {
    cur_addr_end = start_addr + 7;
    while ( 1 )
    {
      if ( *cur_addr == 0x45534552 && *(cur_addr_end - 6) == 0x54 && !*((_WORD *)cur_addr_end - 10) )
      {
        result = rid;
        if ( ((*(cur_addr_end - 4) + 15) & 0xFFFFFFF0) == cur_offset )
          break;
      }
      cur_addr_end += 4;
      cur_addr += 4;
      cur_offset += 16;
      if ( cur_addr >= end_addr )
        goto LABEL_9;
    }
    rid->ImageStart = start_addr;
    rid->RomdirStart = cur_addr;
    rid->RomdirEnd = (char *)cur_addr + *cur_addr_end;
  }
  return result;
}

//----- (00400338) --------------------------------------------------------
struct RomdirFileStat *__fastcall GetFileStatFromImage(
        struct RomImgData *rid,
        char *filename,
        struct RomdirFileStat *rdfs)
{
  int cur_addr_aligned; // $t1
  int total_extinfo_size; // $t2
  const struct RomDirEntry *RomdirStart; // $t0
  int romdir_name_i; // $a3
  struct RomdirFileStat *result; // $v0
  unsigned __int16 *p_ExtInfoEntrySize; // $a1
  char *ImageStart; // $v0
  int cur_romdir_size; // $v0
  int cur_extinfo_size; // $v1
  char cur_romdir_name[12]; // [sp+0h] [-10h] BYREF

  cur_addr_aligned = 0;
  total_extinfo_size = 0;
  RomdirStart = (const struct RomDirEntry *)rid->RomdirStart;
  romdir_name_i = 0;
  memset(cur_romdir_name, 0, sizeof(cur_romdir_name));
  do
  {
    if ( *filename < 33 )
      break;
    cur_romdir_name[romdir_name_i++] = *filename++;
  }
  while ( romdir_name_i < 12 );
  result = 0;
  if ( *(_DWORD *)RomdirStart->name )
  {
    p_ExtInfoEntrySize = &RomdirStart->ExtInfoEntrySize;
    while ( *(_DWORD *)RomdirStart->name != *(_DWORD *)cur_romdir_name
         || *(_DWORD *)(p_ExtInfoEntrySize - 3) != *(_DWORD *)&cur_romdir_name[4]
         || (__int16)*(p_ExtInfoEntrySize - 1) != *(__int16 *)&cur_romdir_name[8] )
    {
      cur_romdir_size = *(_DWORD *)(p_ExtInfoEntrySize + 1);
      cur_extinfo_size = (__int16)*p_ExtInfoEntrySize;
      p_ExtInfoEntrySize += 8;
      ++RomdirStart;
      cur_addr_aligned += (cur_romdir_size + 15) & 0xFFFFFFF0;
      total_extinfo_size += cur_extinfo_size;
      if ( !*(_DWORD *)RomdirStart->name )
        return 0;
    }
    rdfs->romdirent = RomdirStart;
    ImageStart = (char *)rid->ImageStart;
    rdfs->extinfo = 0;
    rdfs->data = &ImageStart[cur_addr_aligned];
    if ( *p_ExtInfoEntrySize )
      rdfs->extinfo = (const struct ExtInfoFieldEntry *)((char *)rid->RomdirEnd + total_extinfo_size);
    return rdfs;
  }
  return result;
}

//----- (00400448) --------------------------------------------------------
const struct ExtInfoFieldEntry *__fastcall do_find_extinfo_entry(struct RomdirFileStat *rdfs, int extinfo_type)
{
  unsigned int ExtInfoEntrySize; // $v0
  const struct ExtInfoFieldEntry *extinfo; // $a0
  const struct ExtInfoFieldEntry *extinfo_end; // $a2

  ExtInfoEntrySize = (__int16)rdfs->romdirent->ExtInfoEntrySize;
  extinfo = rdfs->extinfo;
  extinfo_end = &extinfo[ExtInfoEntrySize >> 2];
  if ( extinfo >= extinfo_end )
    return 0;
  while ( HIBYTE(*(unsigned int *)extinfo) != extinfo_type )
  {
    extinfo = (const struct ExtInfoFieldEntry *)((char *)extinfo + (HIWORD(*(unsigned int *)extinfo) & 0xFC) + 4);
    if ( extinfo >= extinfo_end )
      return 0;
  }
  return extinfo;
}

//----- (004004B0) --------------------------------------------------------
int __fastcall unusedsub_4004B0(int a1)
{
  int result; // $v0
  int v2; // [sp+0h] [+0h]

  v2 = a1 - 1;
  result = -1;
  if ( a1 )
  {
    do
      result = --v2;
    while ( v2 != -1 );
  }
  return result;
}

//----- (004004FC) --------------------------------------------------------
int unusednullsub_4004FC()
{
  return 0;
}

//----- (00400504) --------------------------------------------------------
int __fastcall unused_flash_reset(_DWORD *a1)
{
  int v2; // $v1

  CpuDisableIntr();
  v2 = a1[10];
  if ( v2 == 8 )
  {
    *(_BYTE *)(a1[3] + a1[5]) = -16;
  }
  else if ( v2 == 16 )
  {
    *(_WORD *)(2 * a1[5] + a1[3]) = 240;
  }
  CpuEnableIntr();
  return 0;
}

//----- (00400584) --------------------------------------------------------
BOOL __fastcall unused_checksig(_DWORD *a1, _DWORD *a2, int a3)
{
  int v4; // $v1
  int v6; // $v1
  int v7; // $v0
  unsigned __int8 *v8; // $v1
  int v9; // $v0
  unsigned __int8 *v10; // $v1
  int v11; // $v1
  int v12; // $v0
  unsigned __int16 *v13; // $v1
  int v14; // $v0
  unsigned __int16 *v15; // $v1
  int v16; // $v1
  int v17; // $a0

  v4 = a1[10];
  if ( v4 == 8 )
  {
    v6 = a1[3] + a3;
    *a2 = v6 + a1[5];
    v7 = a1[6];
    a2[2] = v6;
    a2[1] = v6 + v7;
    a2[3] = v6 + a1[4];
    *(_BYTE *)*a2 = -86;
    *(_BYTE *)a2[1] = 85;
    *(_BYTE *)*a2 = -112;
    v8 = (unsigned __int8 *)a2[2];
    MEMORY[0xBF803100] = -145;
    v9 = *v8;
    v10 = (unsigned __int8 *)a2[3];
    a2[4] = v9;
    a2[5] = *v10;
  }
  else if ( v4 == 16 )
  {
    v11 = a1[3] + a3;
    *a2 = v11 + 2 * a1[5];
    v12 = a1[6];
    a2[2] = v11;
    a2[1] = v11 + 2 * v12;
    a2[3] = v11 + 2 * a1[4];
    *(_WORD *)*a2 = 170;
    *(_WORD *)a2[1] = 85;
    *(_WORD *)*a2 = 144;
    v13 = (unsigned __int16 *)a2[2];
    MEMORY[0xBF803100] = -145;
    v14 = *v13;
    v15 = (unsigned __int16 *)a2[3];
    a2[4] = v14;
    a2[5] = *v15;
  }
  unused_flash_reset(a1);
  if ( a1[8] )
    goto LABEL_9;
  v16 = a2[4];
  if ( v16 == 1 || v16 == 4 )
  {
    a1[8] = v16;
LABEL_9:
    v16 = a2[4];
  }
  v17 = 0;
  if ( v16 == a1[8] )
    return a2[5] == a1[9];
  return v17;
}

//----- (00400730) --------------------------------------------------------
BOOL __fastcall unused_flash_checksig(_DWORD *a1)
{
  int v2; // $s5
  int v3; // $s4
  int *v4; // $v1
  BOOL v5; // $a0
  unsigned int v6; // $v1
  int v7; // $lo
  unsigned int v8; // $s1
  int v9; // $s0
  _DWORD *v10; // $v0
  int v12[6]; // [sp+10h] [-18h] BYREF

  v2 = 0;
  v3 = 0;
  if ( a1[11] )
  {
    v2 = MEMORY[0xBF801400];
    MEMORY[0xBF801400] = a1[11];
  }
  v4 = (int *)a1[1];
  if ( v4 )
  {
    v3 = *v4;
    *v4 = a1[2];
    MEMORY[0xBF803100] = *(_DWORD *)a1[1];
  }
  v5 = unused_checksig(a1, v12, 0);
  if ( !v5 )
    goto LABEL_11;
  v6 = a1[13];
  if ( v6 )
  {
    v8 = 1;
    v7 = a1[7] / v6;
    v9 = v7;
    do
    {
      if ( v8 >= a1[13] )
        break;
      v5 = unused_checksig(a1, v12, v9);
      v9 += v7;
      ++v8;
    }
    while ( v5 );
  }
  if ( !v5 )
  {
LABEL_11:
    v10 = (_DWORD *)a1[1];
    if ( v10 )
    {
      *v10 = v3;
      MEMORY[0xBF803100] = *(_DWORD *)a1[1];
    }
    if ( a1[11] )
      MEMORY[0xBF801400] = v2;
  }
  return v5;
}
// 4007D8: conditional instruction was optimized away because $v1.4!=0
// 400850: conditional instruction was optimized away because $a0.4==0
// 400730: using guessed type _DWORD var_18[6];

//----- (00400898) --------------------------------------------------------
_DWORD *__fastcall unused_flash_probe(_DWORD *a1)
{
  CpuDisableIntr();
  if ( a1[10] )
  {
    while ( !unused_flash_checksig(a1) )
    {
      a1 += 14;
      if ( !a1[10] )
        goto LABEL_5;
    }
    CpuEnableIntr();
    return a1;
  }
  else
  {
LABEL_5:
    CpuEnableIntr();
    return 0;
  }
}

//----- (00400924) --------------------------------------------------------
int *__cdecl QueryBootMode(int mode)
{
  int *result; // $v0

  return result;
}
// 400924: variable 'result' is possibly undefined

//----- (00400948) --------------------------------------------------------
int printf(const char *format, ...)
{
  int result; // $v0

  return result;
}
// 400948: variable 'result' is possibly undefined

//----- (0040096C) --------------------------------------------------------
int __cdecl CpuDisableIntr()
{
  int result; // $v0

  return result;
}
// 40096C: variable 'result' is possibly undefined

//----- (00400974) --------------------------------------------------------
int __cdecl CpuEnableIntr()
{
  int result; // $v0

  return result;
}
// 400974: variable 'result' is possibly undefined

//----- (00400998) --------------------------------------------------------
int __cdecl write(int fd, void *ptr, int size)
{
  int result; // $v0

  return result;
}
// 400998: variable 'result' is possibly undefined

//----- (004009BC) --------------------------------------------------------
u32 __cdecl QueryMemSize()
{
  u32 result; // $v0

  return result;
}
// 4009BC: variable 'result' is possibly undefined

//----- (004009E0) --------------------------------------------------------
char *__cdecl rindex(const char *s, int c)
{
  char *result; // $v0

  return result;
}
// 4009E0: variable 'result' is possibly undefined

//----- (004009E8) --------------------------------------------------------
size_t __cdecl strlen(const char *s)
{
  size_t result; // $v0

  return result;
}
// 4009E8: variable 'result' is possibly undefined

// nfuncs=18 queued=18 decompiled=18 lumina nreq=0 worse=0 better=0
// ALL OK, 18 function(s) have been successfully decompiled
