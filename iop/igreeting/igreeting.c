
#include "irx_imports.h"

#include <tamtypes.h>

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
  u16 ExtInfoEntrySize;
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
struct RomImgData *GetIOPRPStat(u32 *start_addr, u32 *end_addr, struct RomImgData *rid);
struct RomdirFileStat *GetFileStatFromImage(struct RomImgData *rid, char *filename, struct RomdirFileStat *rdfs);
const struct ExtInfoFieldEntry *do_find_extinfo_entry(struct RomdirFileStat *rdfs, int extinfo_type);

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
    switch (*(u16 *)boot_mode_4)
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
  if ( !boot_mode_4 || !*(u16 *)boot_mode_4 )
  {
    cop0_processor_mode = mfc0($15);
    write(1, romgen_eq_str, strlen(romgen_eq_str));
    printf("%04x-%04x", *(vu16 *)(0xBFC00102), *(vu16 *)(0xBFC00100));
    write(1, cpuid_eq_str, strlen(cpuid_eq_str));
    printf("%x", cop0_processor_mode);
    write(1, cach_config_eq_str, strlen(cach_config_eq_str));
    printf("%lx, %ldMB", *(vu32 *)(0xFFFE0130), ((u32)QueryMemSize() + 256) >> 20);
    if ( cop0_processor_mode >= 16 )
    {
      iop_or_ps_mode_str = ((*(vu8 *)(0xBF801450) & 8) != 0) ? ", PS mode)\r\n" : ", IOP mode)\r\n";
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
        printf(":%ld>\n", (u16)(uiptr)extinfo_id_str);
      }
    }
  }
  return 1;
}
// 400000: using guessed type int rid[4];

//----- (00400290) --------------------------------------------------------
struct RomImgData *GetIOPRPStat(u32 *start_addr, u32 *end_addr, struct RomImgData *rid)
{
  u32 *cur_addr; // $a3
  int cur_offset; // $t0

  cur_addr = start_addr;
  cur_offset = 0;
  while ( cur_addr < end_addr )
  {
    if ( *cur_addr == 0x45534552 && *((cur_addr + 7) - 6) == 0x54 && !*((u16 *)(cur_addr + 7) - 10) && ((*((cur_addr + 7) - 4) + 15) & 0xFFFFFFF0) == cur_offset )
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
struct RomdirFileStat *GetFileStatFromImage(
        struct RomImgData *rid,
        char *filename,
        struct RomdirFileStat *rdfs)
{
  int cur_addr_aligned; // $t1
  int total_extinfo_size; // $t2
  const struct RomDirEntry *RomdirStart; // $t0
  int romdir_name_i; // $a3
  const u16 *p_ExtInfoEntrySize; // $a1
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
  while ( *(u32 *)RomdirStart->name && (*(u32 *)RomdirStart->name != *(u32 *)cur_romdir_name
       || *(u32 *)(p_ExtInfoEntrySize - 3) != *(u32 *)&cur_romdir_name[4]
       || (u16)*(p_ExtInfoEntrySize - 1) != *(u16 *)&cur_romdir_name[8]) )
  {
    cur_romdir_size = *(u32 *)(p_ExtInfoEntrySize + 1);
    cur_extinfo_size = (s16)*p_ExtInfoEntrySize;
    p_ExtInfoEntrySize += 8;
    ++RomdirStart;
    cur_addr_aligned += (cur_romdir_size + 15) & 0xFFFFFFF0;
    total_extinfo_size += cur_extinfo_size;

  }
  if ( !*(u32 *)RomdirStart->name )
    return 0;
  rdfs->romdirent = RomdirStart;
  rdfs->extinfo = 0;
  rdfs->data = &((char *)rid->ImageStart)[cur_addr_aligned];
  if ( *p_ExtInfoEntrySize )
    rdfs->extinfo = (const struct ExtInfoFieldEntry *)((char *)rid->RomdirEnd + total_extinfo_size);
  return rdfs;
}

//----- (00400448) --------------------------------------------------------
const struct ExtInfoFieldEntry *do_find_extinfo_entry(struct RomdirFileStat *rdfs, int extinfo_type)
{
  const struct ExtInfoFieldEntry *extinfo; // $a0
  const struct ExtInfoFieldEntry *extinfo_end; // $a2

  extinfo = rdfs->extinfo;
  extinfo_end = &extinfo[(unsigned int)((s16)rdfs->romdirent->ExtInfoEntrySize) >> 2];
  while ( extinfo < extinfo_end && ((*(unsigned int *)extinfo) >> 24) != extinfo_type )
  {
    extinfo = (const struct ExtInfoFieldEntry *)((char *)extinfo + (((*(unsigned int *)extinfo) >> 16) & 0xFC) + 4);
  }
  return ( extinfo < extinfo_end ) ? extinfo : 0;
}
