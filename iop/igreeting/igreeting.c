
#include "irx_imports.h"

#include <tamtypes.h>
#define __int8 char
#define __int16 short
#define __int32 int
#define BOOL u32
#define _BYTE u8
#define _WORD u16
#define _DWORD u32
#define __fastcall
#define MEMORY ((volatile unsigned int *)0x10000000)

#if 1
#define LAST_IND(x, part_type) (sizeof(x) / sizeof(part_type) - 1)
#define HIGH_IND(x, part_type) LAST_IND(x, part_type)

#define BYTEn(x, n) (*((_BYTE*)&(x) + n))
#define WORDn(x, n) (*((_WORD*)&(x) + n))
#define DWORDn(x, n) (*((_DWORD*)&(x) + n))
#endif

#if 1
#ifdef HIBYTE
#undef HIBYTE
#endif
#define HIBYTE(x) BYTEn(x, HIGH_IND(x, _BYTE))
#ifdef HIWORD
#undef HIWORD
#endif
#define HIWORD(x) WORDn(x, HIGH_IND(x, _WORD))
#endif


struct RomImgData
{
  const void *ImageStart;
  const void *RomdirStart;
  const void *RomdirEnd;
};

struct ImageData
{
  const char *filename;
  int fd;
  int size;
  struct RomImgData stat;
};


struct RomDirEntry
{
  char name[10];
  unsigned __int16 ExtInfoEntrySize;
  unsigned int size;
};

struct RomdirFileStat
{
  const struct RomDirEntry *romdirent;
  const void *data;
  const struct ExtInfoFieldEntry *extinfo;
  unsigned int padding;
};


struct ExtInfoFieldEntry
{
  u16 value;
  u8 ExtLength;
  u8 type;
  u8 payload[];
};


#define _mfc0(reg)                                                                                                     \
  ({                                                                                                                   \
    u32 val;                                                                                                           \
    __asm__ volatile("mfc0 %0, " #reg : "=r"(val));                                                                    \
    val;                                                                                                               \
  })

#define mfc0(reg) _mfc0(reg)



//-------------------------------------------------------------------------
// Function declarations

int _start();
struct RomImgData *__fastcall GetIOPRPStat(u32 *start_addr, u32 *end_addr, struct RomImgData *rid);
struct RomdirFileStat *__fastcall GetFileStatFromImage(struct RomImgData *rid, char *filename, struct RomdirFileStat *rdfs);
const struct ExtInfoFieldEntry *__fastcall do_find_extinfo_entry(struct RomdirFileStat *rdfs, int extinfo_type);

//-------------------------------------------------------------------------
// Data declarations

char *romgen_eq_str = " ROMGEN="; // idb
char *cpuid_eq_str = ", IOP info (CPUID="; // idb
char *cach_config_eq_str = ", CACH_CONFIG="; // idb


//----- (00400000) --------------------------------------------------------
int _start()
{
  int *boot_mode_4; // $s0
  int cop0_processor_mode; // $s0
  char *iop_or_ps_mode_str; // $s0
  const struct ExtInfoFieldEntry *extinfo_entry; // $v0
  char *extinfo_id_str; // $s0
  char *comma_index; // $s1
  struct RomImgData rid; // [sp+10h] [-20h] BYREF
  struct RomdirFileStat rdfs; // [sp+20h] [-10h] BYREF

  boot_mode_4 = QueryBootMode(4);
  printf("\nPlayStation 2 ======== ");
  if ( boot_mode_4 )
  {
    switch (*(unsigned __int16 *)boot_mode_4)
    {
      case 0:
        printf("Hard reset boot");
        break;
      case 1:
        printf("Soft reboot");
        break;
      case 2:
        printf("Update rebooting..");
        break;
      case 3:
        printf("Update reboot complete");
        break;
      default:
        break;
    }
    printf("\n");
  }
  if ( !boot_mode_4 || !*(_WORD *)boot_mode_4 )
  {
    cop0_processor_mode = mfc0($15);
    write(1, romgen_eq_str, strlen(romgen_eq_str));
    printf("%04x-%04x", MEMORY[0xBFC00102], MEMORY[0xBFC00100]);
    write(1, cpuid_eq_str, strlen(cpuid_eq_str));
    printf("%x", cop0_processor_mode);
    write(1, cach_config_eq_str, strlen(cach_config_eq_str));
    printf("%lx, %ldMB", MEMORY[0xFFFE0130], ((u32)QueryMemSize() + 256) >> 20);
    if ( cop0_processor_mode >= 16 )
    {
      iop_or_ps_mode_str = ((MEMORY[0xBF801450] & 8) != 0) ? ", PS mode)\r\n" : ", IOP mode)\r\n";
      write(1, iop_or_ps_mode_str, strlen(iop_or_ps_mode_str));
    }
    if ( GetIOPRPStat((u32 *)0xBFC00000, (u32 *)0xBFC10000, &rid) && GetFileStatFromImage(&rid, "ROMDIR", &rdfs) )
    {
      extinfo_entry = do_find_extinfo_entry(&rdfs, 3);
      if ( extinfo_entry )
      {
        extinfo_id_str = (char *)extinfo_entry->payload;
        comma_index = rindex((const char *)extinfo_entry->payload, ',');
        write(1, " <", 2);
        // Unofficial: if commaa not found, just write the whole thing
        write(1, extinfo_id_str, comma_index ? (comma_index - extinfo_id_str) : strlen(extinfo_id_str));
        printf(":%ld>\n", (unsigned __int16)(uiptr)extinfo_id_str);
      }
    }
  }
  return 1;
}
// 400000: using guessed type int rid[4];

//----- (00400290) --------------------------------------------------------
struct RomImgData *__fastcall GetIOPRPStat(u32 *start_addr, u32 *end_addr, struct RomImgData *rid)
{
  u32 *cur_addr; // $a3
  int cur_offset; // $t0

  cur_addr = start_addr;
  cur_offset = 0;
  while ( cur_addr < end_addr )
  {
    if ( *cur_addr == 0x45534552 && *((cur_addr + 7) - 6) == 0x54 && !*((_WORD *)(cur_addr + 7) - 10) && ((*((cur_addr + 7) - 4) + 15) & 0xFFFFFFF0) == cur_offset )
    {
      rid->ImageStart = start_addr;
      rid->RomdirStart = cur_addr;
      rid->RomdirEnd = (char *)cur_addr + *(cur_addr + 7);
      return rid;
    }
    cur_addr += 4;
    cur_offset += 16;
  }
  rid->ImageStart = 0;
  return 0;
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
  const unsigned __int16 *p_ExtInfoEntrySize; // $a1
  int cur_romdir_size; // $v0
  int cur_extinfo_size; // $v1
  char cur_romdir_name[12]; // [sp+0h] [-10h] BYREF

  cur_addr_aligned = 0;
  total_extinfo_size = 0;
  RomdirStart = (const struct RomDirEntry *)rid->RomdirStart;
  romdir_name_i = 0;
  memset(cur_romdir_name, 0, sizeof(cur_romdir_name));
  while ( romdir_name_i < 12 && *filename < 33 )
  {
    cur_romdir_name[romdir_name_i++] = *filename++;
  }
  p_ExtInfoEntrySize = &RomdirStart->ExtInfoEntrySize;
  while ( *(_DWORD *)RomdirStart->name && (*(_DWORD *)RomdirStart->name != *(_DWORD *)cur_romdir_name
       || *(_DWORD *)(p_ExtInfoEntrySize - 3) != *(_DWORD *)&cur_romdir_name[4]
       || (__int16)*(p_ExtInfoEntrySize - 1) != *(__int16 *)&cur_romdir_name[8]) )
  {
    cur_romdir_size = *(_DWORD *)(p_ExtInfoEntrySize + 1);
    cur_extinfo_size = (__int16)*p_ExtInfoEntrySize;
    p_ExtInfoEntrySize += 8;
    ++RomdirStart;
    cur_addr_aligned += (cur_romdir_size + 15) & 0xFFFFFFF0;
    total_extinfo_size += cur_extinfo_size;

  }
  if ( !*(_DWORD *)RomdirStart->name )
    return 0;
  rdfs->romdirent = RomdirStart;
  rdfs->extinfo = 0;
  rdfs->data = &((char *)rid->ImageStart)[cur_addr_aligned];
  if ( *p_ExtInfoEntrySize )
    rdfs->extinfo = (const struct ExtInfoFieldEntry *)((char *)rid->RomdirEnd + total_extinfo_size);
  return rdfs;
}

//----- (00400448) --------------------------------------------------------
const struct ExtInfoFieldEntry *__fastcall do_find_extinfo_entry(struct RomdirFileStat *rdfs, int extinfo_type)
{
  const struct ExtInfoFieldEntry *extinfo; // $a0
  const struct ExtInfoFieldEntry *extinfo_end; // $a2

  extinfo = rdfs->extinfo;
  extinfo_end = &extinfo[(unsigned int)((__int16)rdfs->romdirent->ExtInfoEntrySize) >> 2];
  while ( extinfo < extinfo_end && HIBYTE(*(unsigned int *)extinfo) != extinfo_type )
  {
    extinfo = (const struct ExtInfoFieldEntry *)((char *)extinfo + (HIWORD(*(unsigned int *)extinfo) & 0xFC) + 4);
  }
  return ( extinfo < extinfo_end ) ? extinfo : 0;
}
