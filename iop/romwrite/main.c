
#include <irx_imports.h>

IRX_ID("ROMWRITE", 7, 1);

#define __int8 char
#define __int32 int
#define _BYTE u8
#define _DWORD u32
#define BOOL u32
#define _break(...) __builtin_trap()

typedef struct s147_dev9_mem_mmio_x
{
  vu8 m_unk00;
  vu8 m_led;
  vu8 m_security_unlock_unlock;
  vu8 m_unk03;
  vu8 m_rtc_flag;
  vu8 m_watchdog_flag2;
  vu8 m_unk06;
  vu8 m_sram_write_flag;
  vu8 m_pad08;
  vu8 m_pad09;
  vu8 m_pad0A;
  vu8 m_pad0B;
  vu8 m_security_unlock_set1;
  vu8 m_security_unlock_set2;
} s147_dev9_mem_mmio_;

typedef struct nand_id_desc_info_stru_x
{
  u32 m_id[5];
  const char *m_nand_name;
  const char *m_nand_desc;
  int m_page_size_noecc;
  int m_page_size_withecc;
  int m_pages_per_block;
  int m_block_size;
} nand_id_desc_info_stru_;

typedef struct nand_direntry_stru_x
{
  char m_name[16];
  u32 m_unk;
  u8 m_type;
  u8 m_pad[3];
  u32 m_size;
  u32 m_offset;
} nand_direntry_stru_;


typedef struct nand_dir_stru_x
{
  char m_sig[8];
  u16 m_ver;
  char m_unk0[6];
  u32 m_entrycnt;
  u32 m_unk1;
  u32 m_unk2;
  u32 m_unk3;
  nand_direntry_stru_ m_direntry[63];
} nand_dir_stru_;

typedef union romwrite_part_buf_x
{
  u8 m_buf[131072];
  nand_header_stru_ m_hdr;
  nand_dir_stru_ m_dir;
  nand_direntry_stru_ m_direntry[64];
} romwrite_part_buf_;



//-------------------------------------------------------------------------
// Function declarations

int do_format_nand_device(char devindchr);
char *do_read_product_code(int fd);
int _start(int ac, char **av);
void thread_proc(); // weak
BOOL do_toggle_dev9addr_inner(int len, int cnt);
unsigned int generate_acio_delay_val(char dmat_val, char rddl_val, char wrdl_val);
int set_send_print_to_osdsys(int flg);
int is_send_print_to_osdsys();
int set_boot_video_mode(int flg);
int do_set_flag(int flg);
int do_set_secr_code(char code1, unsigned __int8 code2);
int do_handle_atfile_image(int part, const char *str);
char *do_set_atfile_147_dir(const char *str);
int do_start_write_proc();
int do_format_device(int abspart);
int do_write_partition(int part);
int check_badblock_count();
int get_nand_partition_offset(int part, int abspart);
int get_nand_partition_size(int part, int abspart);
int get_nand_block_size_div_32_div_64();
int get_nand_block_size_div_32();
BOOL do_dma_write_bytes_multi(void *ptr, int pageoffs, int pagecnt);
int do_list_files(int part);
int do_output_bb_info(int blocksd, int abspart, int bboffs);
int do_verify(void *buf1, void *buf2, int len);
nand_id_desc_info_stru_ *do_parse_device_info(char *nandid);
#define some_blowfish_magic_1(...) do {} while(0)
#define some_blowfish_magic_2(...) do {} while(0)
#define set_sif_output_cmd(...) do {} while(0)
#define do_print_to_osdsys_2(...) do {} while(0)
#define do_print_to_osdsys_1(...) do {} while(0)

//-------------------------------------------------------------------------
// Data declarations

nand_id_desc_info_stru_ g_nand_type_info[4] =
{
  {
    { 236u, 218u, 4294967295u, 21u, 4294967295u },
    "SAMSUNG K9F2G08U0M",
    "8bit width, 256MBytes",
    2048,
    2112,
    64,
    2048
  },
  {
    { 236u, 220u, 16u, 149u, 84u },
    "SAMSUNG K9F4G08U0M",
    "8bit width, 512MBytes",
    2048,
    2112,
    64,
    4096
  },
  {
    { 236u, 211u, 81u, 149u, 88u },
    "SAMSUNG K9K8G08U0M",
    "8bit width, 1GBytes",
    2048,
    2112,
    64,
    8192
  },
  { { 0u, 0u, 0u, 0u, 0u }, NULL, NULL, 0, 0, 0, 0 }
}; // weak
char g_secr_code_1 = '\0'; // weak
char g_secr_code_2 = '\0'; // weak
int g_curflag = 0; // weak
int g_sent_print_to_osdsys = 0; // weak
int g_boot_video_mode = 0; // weak
void *g_part_buf = NULL; // idb
char *g_page_buf = NULL; // idb
int g_badblock_count = 1; // weak
char g_product_code_tmp[32]; // weak
u8 *g_blockinfo_str_buf;
u16 *g_blockinfo_dat_buf;
nand_id_desc_info_stru_ *g_device_info;
char g_atfile_part_image[8][256];
char g_atfile_info_image[0x100]; // idb
char g_atfile_147_dir[0x100]; // idb
romwrite_part_buf_ g_nand_partbuf; // weak
s147_dev9_mem_mmio_ s147_dev9_mem_mmio; // weak


//----- (00400000) --------------------------------------------------------
int do_format_nand_device(char devindchr)
{
  char tmp_devindchr; // [sp+10h] [+10h]

  tmp_devindchr = devindchr;
  switch (devindchr)
  {
  case '2':
    do_set_flag(0x10000);
    break;
  case '4':
    do_set_flag(0x20000);
    break;
  case '8':
    do_set_flag(0x30000);
    break;
  default:
    do_set_flag(0xF0000);
    tmp_devindchr = ' ';
    break;
  }
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2(" -f%c: Format NAND(atfile:) device\n", tmp_devindchr);
  else
    Kprintf(" -f%c: Format NAND(atfile:) device\n", tmp_devindchr);
  return 0;
}
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);

//----- (00400104) --------------------------------------------------------
char *do_read_product_code(int fd)
{
  read(fd, g_product_code_tmp, 32);
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("  ---> OK, set product code - \"%s\"\n", &g_product_code_tmp[16]);
  else
    Kprintf("  ---> OK, set product code - \"%s\"\n", &g_product_code_tmp[16]);
  some_blowfish_magic_1("S147NBGI", 8);
  some_blowfish_magic_2((int *)g_product_code_tmp, (int *)&g_product_code_tmp[4]);
  return &g_product_code_tmp[4];
}
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);

//----- (004001E0) --------------------------------------------------------
int _start(int ac, char **av)
{
  iop_thread_t thparam; // [sp+10h] [+10h] BYREF
  int thid; // [sp+28h] [+28h]
  int i; // [sp+2Ch] [+2Ch]
  int tmp_secrcode; // [sp+30h] [+30h]
  char secrcode1; // [sp+34h] [+34h]
  char secrcode2; // [sp+35h] [+35h]
  int fd; // [sp+38h] [+38h]
  int product_code; // [sp+3Ch] [+3Ch]

  set_sif_output_cmd(30);
  if ( ac >= 2 )
  {
    do_print_to_osdsys_1("\n====== romwrite(version 0x%04x): Check argument ======\n", 0x701);
    DelayThread(10000);
    for ( i = 1; i < ac; ++i )
    {
      if ( !strcmp(av[i], "-m") || !strcmp(av[i], "--main") )
      {
        do_print_to_osdsys_1(" -m, --main : MainPCB mode (Send PRINTF to EE)\n");
        DelayThread(10000);
        set_send_print_to_osdsys(1);
        break;
      }
      if ( !strcmp(av[i], "-v") || !strcmp(av[i], "--vga") )
      {
        do_print_to_osdsys_1(" -v, --vga : Set boot video mode (VGA)\n");
        DelayThread(10000);
        set_boot_video_mode(2);
        break;
      }
    }
    for ( i = 1; i < ac; ++i )
    {
      if ( *av[i] == '-' )
      {
        switch ( av[i][1] )
        {
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
            product_code = strtol(av[i] + 1, 0, 10);
            if ( is_send_print_to_osdsys() == 1 )
              do_print_to_osdsys_2(" -%d : Write \"atfile%d:\" image file\n", product_code, product_code);
            else
              Kprintf(" -%d : Write \"atfile%d:\" image file\n", product_code, product_code);
            do_set_flag(1 << product_code);
            do_handle_atfile_image(product_code, av[++i]);
            break;
          case 'd':
            if ( is_send_print_to_osdsys() == 1 )
              do_print_to_osdsys_2(" -d : Search \"atfile*.147\" in the directory and Write\n");
            else
              Kprintf(" -d : Search \"atfile*.147\" in the directory and Write\n");
            ++i;
            do_set_flag(0x2000000);
            do_set_atfile_147_dir(av[i]);
            break;
          case 'f':
            do_format_nand_device(av[i][2]);
            break;
          case 'i':
            if ( is_send_print_to_osdsys() == 1 )
              do_print_to_osdsys_2(" -i : Write \"atfile9:info\" image\n");
            else
              Kprintf(" -i : Write \"atfile9:info\" image\n");
            do_set_flag(0x200);
            do_handle_atfile_image(9, av[++i]);
            break;
          case 'l':
            if ( is_send_print_to_osdsys() == 1 )
              do_print_to_osdsys_2(" -l : Read NAND device and Display all file list\n");
            else
              Kprintf(" -l : Read NAND device and Display all file list\n");
            do_set_flag(0x4000000);
            break;
          case 's':
            if ( av[i][2] == '0' )
            {
              if ( is_send_print_to_osdsys() == 1 )
                do_print_to_osdsys_2(" -s0: Set default security code\n");
              else
                Kprintf(" -s0: Set default security code\n");
              do_set_flag(0x1000000);
              do_set_secr_code(0xFF, 0xFFu);
            }
            else if ( av[i][2] == 'r' )
            {
              if ( is_send_print_to_osdsys() == 1 )
                do_print_to_osdsys_2(" -sr: Read \"s147secr.147\" file\n");
              else
                Kprintf(" -sr: Read \"s147secr.147\" file\n");
              do_set_flag(0x1000000);
              fd = open(av[++i], 1);
              if ( fd >= 0 )
              {
                product_code = (int)do_read_product_code(fd);
                do_set_secr_code(*(_BYTE *)product_code, *(_BYTE *)(product_code + 1));
                close(fd);
              }
              else
              {
                if ( is_send_print_to_osdsys() == 1 )
                  do_print_to_osdsys_2("  ---> File not found, set default code\n");
                else
                  Kprintf("  ---> File not found, set default code\n");
                do_set_secr_code(0xFF, 0xFFu);
              }
            }
            else
            {
              if ( is_send_print_to_osdsys() == 1 )
                do_print_to_osdsys_2(" -s : Set immediate secrity code\n");
              else
                Kprintf(" -s : Set immediate secrity code\n");
              tmp_secrcode = strtol(av[++i], 0, 10);
              secrcode1 = tmp_secrcode;
              tmp_secrcode = strtol(av[++i], 0, 10);
              secrcode2 = tmp_secrcode;
              do_set_flag(0x1000000);
              do_set_secr_code(secrcode1, secrcode2);
            }
            break;
          default:
            continue;
        }
      }
    }
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2("\n");
    else
      Kprintf("\n");
    thparam.attr = 0x2000000;
    thparam.thread = (void (*)(void *))thread_proc;
    thparam.priority = 0x7A;
    thparam.stacksize = 0x80000;
    thparam.option = 0;
    thid = CreateThread(&thparam);
    if ( thid <= 0 )
    {
      return 1;
    }
    else
    {
      StartThread(thid, 0);
      return 0;
    }
  }
  else
  {
    do_print_to_osdsys_1("SYS147 ROM Writer (version 0x%04x)\n\n", 0x701);
    DelayThread(10000);
    do_print_to_osdsys_1("usage: %s [OPTION]... [FILE]...\n", "romwrite.irx");
    DelayThread(10000);
    do_print_to_osdsys_1("  -m, --main ............. MainPCB mode (Send PRINTF to EE)\n");
    DelayThread(10000);
    do_print_to_osdsys_1("  -s0 .................... Set default security code\n");
    DelayThread(10000);
    do_print_to_osdsys_1("  -sr .................... Read \"s147secr.147\" and set security code\n");
    DelayThread(10000);
    do_print_to_osdsys_1("  -f(f2, f4, f8) ......... Format NAND(atfile:) device\n");
    DelayThread(10000);
    do_print_to_osdsys_1("  -0([1..7]) filename .... Write \"atfile[0..7]:\" image file\n");
    DelayThread(10000);
    do_print_to_osdsys_1("  -d directory ........... Search \"atfile*.147\" in the directory and Write\n");
    DelayThread(10000);
    do_print_to_osdsys_1("  -i filename ............ Write \"atfile9:info\" image from file\n");
    DelayThread(10000);
    do_print_to_osdsys_1("  -l ..................... Read NAND device and Display all file list\n");
    DelayThread(10000);
    do_print_to_osdsys_1("  -v, --vga .............. Set boot video mode (VGA)\n");
    DelayThread(10000);
    return 1;
  }
}
// 400B40: using guessed type void __noreturn thread_proc();
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);

//----- (00400B40) --------------------------------------------------------
void thread_proc()
{
  int i; // [sp+10h] [+10h]
  int j; // [sp+10h] [+10h]

  if ( do_start_write_proc() )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2("\n****** Aborted ******\n\n");
    else
      Kprintf("\n****** Aborted ******\n\n");
    while ( 1 )
    {
      s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
      s147_dev9_mem_mmio.m_led = 1;
      DelayThread(250000);
      s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
      s147_dev9_mem_mmio.m_led = 0;
      DelayThread(250000);
    }
  }
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("====== Completed ======\n\n");
  else
    Kprintf("====== Completed ======\n\n");
  while ( 1 )
  {
    for ( i = 1; i < 20; ++i )
    {
      s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
      do_toggle_dev9addr_inner(5 * i, 50);
    }
    for ( j = 20; j > 0; --j )
    {
      s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
      do_toggle_dev9addr_inner(5 * j, 50);
    }
  }
}
// 400B40: using guessed type void __noreturn thread_proc();
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00400D00) --------------------------------------------------------
BOOL do_toggle_dev9addr_inner(int len, int cnt)
{
  BOOL result; // $v0
  int i; // [sp+10h] [+10h]

  for ( i = 0; ; ++i )
  {
    result = i < cnt;
    if ( i >= cnt )
      break;
    if ( len > 0 )
    {
      s147_dev9_mem_mmio.m_led = 3;
      DelayThread(10 * len);
    }
    if ( len < 100 )
    {
      s147_dev9_mem_mmio.m_led = 0;
      DelayThread(10 * (100 - len));
    }
  }
  return result;
}
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

// Unused function omitted

//----- (00400E6C) --------------------------------------------------------
unsigned int generate_acio_delay_val(char dmat_val, char rddl_val, char wrdl_val)
{
  return (((dmat_val - 1) & 0xF) << 24) | (16 * ((rddl_val - 1) & 0xF)) | 0xA01A0100 | ((wrdl_val - 1) & 0xF);
}

// Unused function omitted

//----- (00400F7C) --------------------------------------------------------
int set_send_print_to_osdsys(int flg)
{
  int result; // $v0

  result = flg;
  g_sent_print_to_osdsys = flg;
  return result;
}
// 407CA8: using guessed type int g_sent_print_to_osdsys;

//----- (00400FA8) --------------------------------------------------------
int is_send_print_to_osdsys()
{
  return g_sent_print_to_osdsys;
}
// 407CA8: using guessed type int g_sent_print_to_osdsys;

//----- (00400FD8) --------------------------------------------------------
int set_boot_video_mode(int flg)
{
  int result; // $v0

  result = flg;
  g_boot_video_mode = flg;
  return result;
}
// 407CAC: using guessed type int g_boot_video_mode;

//----- (00401004) --------------------------------------------------------
int do_set_flag(int flg)
{
  int result; // $v0

  result = g_curflag | flg;
  g_curflag |= flg;
  return result;
}
// 407CA4: using guessed type int g_curflag;

//----- (00401040) --------------------------------------------------------
int do_set_secr_code(char code1, unsigned __int8 code2)
{
  int result; // $v0

  g_secr_code_1 = code1;
  result = code2;
  g_secr_code_2 = code2;
  return result;
}
// 407CA0: using guessed type char g_secr_code_1;
// 407CA1: using guessed type char g_secr_code_2;

//----- (00401084) --------------------------------------------------------
int do_handle_atfile_image(int part, const char *str)
{
  int result; // $v0

  if ( part == 9 )
    return (int)strcpy(g_atfile_info_image, str);
  result = part;
  if ( part >= 0 )
  {
    result = part;
    if ( part < 8 )
      return (int)strcpy(g_atfile_part_image[part], str);
  }
  return result;
}

//----- (0040113C) --------------------------------------------------------
char *do_set_atfile_147_dir(const char *str)
{
  return strcpy(g_atfile_147_dir, str);
}

//----- (00401178) --------------------------------------------------------
int do_start_write_proc()
{
  unsigned int flgtmp; // $v0
  nand_info_stru_ *nandinf; // [sp+18h] [+18h]
  int state; // [sp+1Ch] [+1Ch] BYREF
  int part; // [sp+20h] [+20h]
  int fd1; // [sp+24h] [+24h]
  int logaddrtable; // [sp+28h] [+28h]
  u8 nandid[5]; // [sp+30h] [+30h] BYREF
  int fd2; // [sp+38h] [+38h]

  fd1 = open("ctrl99:watchdog-stop", 1);
  close(fd1);
  if ( (g_curflag & 0x1000000) != 0 )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2("====== Set security code ======\n");
    else
      Kprintf("====== Set security code ======\n");
    s147_dev9_mem_mmio.m_security_unlock_set1 = g_secr_code_1;
    s147_dev9_mem_mmio.m_security_unlock_set2 = g_secr_code_2;
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2("\n");
    else
      Kprintf("\n");
  }
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("====== Device information ======\n");
  else
    Kprintf("====== Device information ======\n");
  s147nand_26_nand_readid(nandid);
  g_device_info = do_parse_device_info((char *)nandid);
  if ( g_device_info )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" ID = %02X/%02X/%02X/%02X/%02X\n", nandid[0], nandid[1], nandid[2], nandid[3], nandid[4]);
    else
      Kprintf(" ID = %02X/%02X/%02X/%02X/%02X\n", nandid[0], nandid[1], nandid[2], nandid[3], nandid[4]);
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" \"%s\", %s\n", g_device_info->m_nand_name, g_device_info->m_nand_desc);
    else
      Kprintf(" \"%s\", %s\n", g_device_info->m_nand_name, g_device_info->m_nand_desc);
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(
        " PageSize    = %d + %d (Bytes)\n",
        g_device_info->m_page_size_noecc,
        g_device_info->m_page_size_withecc - g_device_info->m_page_size_noecc);
    else
      Kprintf(
        " PageSize    = %d + %d (Bytes)\n",
        g_device_info->m_page_size_noecc,
        g_device_info->m_page_size_withecc - g_device_info->m_page_size_noecc);
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" Pages/Block = %d (Pages)\n", g_device_info->m_pages_per_block);
    else
      Kprintf(" Pages/Block = %d (Pages)\n", g_device_info->m_pages_per_block);
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" BlockSize   = %d (Blocks)\n", g_device_info->m_block_size);
    else
      Kprintf(" BlockSize   = %d (Blocks)\n", g_device_info->m_block_size);
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2("\n");
    else
      Kprintf("\n");
    CpuSuspendIntr(&state);
    g_blockinfo_str_buf = (u8 *)AllocSysMemory(0, g_device_info->m_block_size, 0);
    g_blockinfo_dat_buf = (u16 *)AllocSysMemory(0, 2 * g_device_info->m_block_size, 0);
    CpuResumeIntr(state);
    if ( !g_blockinfo_str_buf || !g_blockinfo_dat_buf )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2("\nError: AllocSysMemory failed\n\n");
      else
        Kprintf("\nError: AllocSysMemory failed\n\n");
      return -1;
    }
    nandinf = s147nand_16_getnandinfo();
    CpuSuspendIntr(&state);
    nandinf->m_page_size_noecc = g_device_info->m_page_size_noecc;
    nandinf->m_page_size_withecc = g_device_info->m_page_size_withecc;
    nandinf->m_pages_per_block = g_device_info->m_pages_per_block;
    nandinf->m_block_size = g_device_info->m_block_size;
    nandinf->m_page_count = g_device_info->m_block_size * g_device_info->m_pages_per_block;
    CpuResumeIntr(state);
    flgtmp = g_curflag & 0xFF0000;
    if ( (g_curflag & 0xFF0000) == 0x20000 )
    {
      logaddrtable = do_format_device(4);
      if ( logaddrtable )
        return logaddrtable;
    }
    else if ( flgtmp > 0x20000 )
    {
      if ( flgtmp == 0x30000 )
      {
        logaddrtable = do_format_device(8);
        if ( logaddrtable )
          return logaddrtable;
      }
      else if ( flgtmp == 0xF0000 )
      {
        logaddrtable = do_format_device(0);
        if ( logaddrtable )
          return logaddrtable;
      }
    }
    else if ( flgtmp == 0x10000 )
    {
      logaddrtable = do_format_device(2);
      if ( logaddrtable )
        return logaddrtable;
    }
    s147nand_6_checkformat();
    fd2 = open("atfile9:acdelay", 1);
    close(fd2);
    if ( (g_curflag & 0x2000000) != 0 )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2("====== Search directory ======\n");
      else
        Kprintf("====== Search directory ======\n");
      for ( part = 0; part < 8; ++part )
      {
        if ( s147nand_10_get_nand_partition_size(part) > 0 )
        {
          sprintf(g_atfile_part_image[part], "%satfile%d.147", g_atfile_147_dir, part);
          fd1 = open(g_atfile_part_image[part], 1);
          if ( fd1 < 0 )
          {
            DelayThread(10000);
          }
          else
          {
            do_set_flag(1 << part);
            do_handle_atfile_image(part, g_atfile_part_image[part]);
            close(fd1);
            if ( is_send_print_to_osdsys() == 1 )
              do_print_to_osdsys_2(" \"%s\" is found\n", g_atfile_part_image[part]);
            else
              Kprintf(" \"%s\" is found\n", g_atfile_part_image[part]);
          }
        }
        else if ( is_send_print_to_osdsys() == 1 )
        {
          do_print_to_osdsys_2(" atfile%d: Unformatted - Do nothing\n", part);
        }
        else
        {
          Kprintf(" atfile%d: Unformatted - Do nothing\n", part);
        }
      }
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2(" \n");
      else
        Kprintf(" \n");
    }
    for ( part = 0; part < 8; ++part )
    {
      if ( ((1 << part) & g_curflag) != 0 )
      {
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2("====== Write \"%s\" to atfile%d: ======\n", g_atfile_part_image[part], part);
        else
          Kprintf("====== Write \"%s\" to atfile%d: ======\n", g_atfile_part_image[part], part);
        logaddrtable = do_write_partition(part);
        if ( logaddrtable )
          return logaddrtable;
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" \n");
        else
          Kprintf(" \n");
      }
    }
    if ( (g_curflag & 0x200) != 0 )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2("====== Write \"%s\" to \"atfile9:info\" ======\n", g_atfile_info_image);
      else
        Kprintf("====== Write \"%s\" to \"atfile9:info\" ======\n", g_atfile_info_image);
      logaddrtable = do_write_partition(9);
      if ( logaddrtable )
        return logaddrtable;
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2(" \n");
      else
        Kprintf(" \n");
    }
    if ( (g_curflag & 0x4000000) != 0 )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2("====== Display file list ======\n");
      else
        Kprintf("====== Display file list ======\n");
      logaddrtable = s147nand_12_load_logaddrtable();
      if ( logaddrtable )
      {
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" Error: Unformatted device (%d)\n", logaddrtable);
        else
          Kprintf(" Error: Unformatted device (%d)\n", logaddrtable);
        return logaddrtable;
      }
      for ( part = 0; part < 8; ++part )
        do_list_files(part);
    }
    return 0;
  }
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2(" ID = %02X/%02X/%02X/%02X/%02X\n", nandid[0], nandid[1], nandid[2], nandid[3], nandid[4]);
  else
    Kprintf(" ID = %02X/%02X/%02X/%02X/%02X\n", nandid[0], nandid[1], nandid[2], nandid[3], nandid[4]);
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("\nError: Unknown Device\n");
  else
    Kprintf("\nError: Unknown Device\n");
  return -1;
}
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);
// 407CA0: using guessed type char g_secr_code_1;
// 407CA1: using guessed type char g_secr_code_2;
// 407CA4: using guessed type int g_curflag;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00401E5C) --------------------------------------------------------
int do_format_device(int abspart)
{
  int xpages2; // $v0
  int xpages1; // $v0
  int blocks; // [sp+18h] [+18h]
  int blocksa; // [sp+18h] [+18h]
  int blocksb; // [sp+18h] [+18h]
  int blocksc; // [sp+18h] [+18h]
  int blocksd; // [sp+18h] [+18h]
  int bboffs; // [sp+1Ch] [+1Ch]
  int nand_partition_offset; // [sp+20h] [+20h]
  int bbcnt1; // [sp+24h] [+24h]
  int eraseres; // [sp+28h] [+28h]
  int i; // [sp+30h] [+30h]
  int xnand_partition_offset; // [sp+34h] [+34h]
  int xnand_partition_size; // [sp+38h] [+38h]

  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("====== Format NAND device ======\n");
  else
    Kprintf("====== Format NAND device ======\n");
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2(" [1/3]Block Erase and Check Bad Blocks\n");
  else
    Kprintf(" [1/3]Block Erase and Check Bad Blocks\n");
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2(" BadBlock =");
  else
    Kprintf(" BadBlock =");
  for ( blocks = 0; blocks < g_device_info->m_block_size; ++blocks )
  {
    s147_dev9_mem_mmio.m_led = (blocks >> 4) & 3;
    if ( blocks )
    {
      xpages1 = s147nand_27_blocks2pages(blocks);
      eraseres = s147nand_24_eraseoffset(xpages1);
    }
    else
    {
      xpages2 = s147nand_27_blocks2pages(0);
      eraseres = s147nand_25_nand_blockerase(xpages2);
    }
    if ( eraseres == -1470020 )
    {
      g_blockinfo_str_buf[blocks] = 'X';
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2(" %d", blocks);
      else
        Kprintf(" %d", blocks);
    }
    else if ( eraseres )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2(" %d*(%d)", blocks, eraseres);
      else
        Kprintf(" %d*(%d)", blocks, eraseres);
    }
    else
    {
      g_blockinfo_str_buf[blocks] = '=';
    }
  }
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("\n\n");
  else
    Kprintf("\n\n");
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2(" [2/3]Replace Bad Blocks ('B':Boot, 'I':Info, 'X':Broken, 'R':Reserved, '@':Occupied)\n");
  else
    Kprintf(" [2/3]Replace Bad Blocks ('B':Boot, 'I':Info, 'X':Broken, 'R':Reserved, '@':Occupied)\n");
  *g_blockinfo_dat_buf = 0xEEEE;
  *g_blockinfo_str_buf = 'B';
  nand_partition_offset = get_nand_partition_offset(8, 8);
  for ( blocksa = 1; blocksa < nand_partition_offset - 1; ++blocksa )
  {
    if ( g_blockinfo_str_buf[blocksa] == '=' )
    {
      g_blockinfo_dat_buf[blocksa] = 0xEEEE;
      g_blockinfo_str_buf[blocksa] = 'R';
    }
  }
  blocksb = nand_partition_offset - 1;
  bbcnt1 = 0;
  if ( g_blockinfo_str_buf[nand_partition_offset - 1] == 'X' )
  {
    bbcnt1 = check_badblock_count();
    if ( bbcnt1 >= 0 )
    {
      g_blockinfo_dat_buf[blocksb] = bbcnt1;
      g_blockinfo_dat_buf[bbcnt1] = 0xCCCC;
      g_blockinfo_str_buf[bbcnt1] = '@';
      bboffs = bbcnt1;
    }
  }
  else
  {
    g_blockinfo_dat_buf[blocksb] = 0xAAAA;
    bboffs = nand_partition_offset - 1;
  }
  if ( bbcnt1 >= 0 )
  {
    for ( blocksc = nand_partition_offset; blocksc < g_device_info->m_block_size; ++blocksc )
    {
      if ( g_blockinfo_str_buf[blocksc] == 'X' )
      {
        bbcnt1 = check_badblock_count();
        if ( bbcnt1 < 0 )
          break;
        g_blockinfo_dat_buf[blocksc] = bbcnt1;
        g_blockinfo_dat_buf[bbcnt1] = 0xCCCC;
        g_blockinfo_str_buf[bbcnt1] = '@';
      }
      else
      {
        g_blockinfo_dat_buf[blocksc] = 0xAAAA;
      }
    }
  }
  if ( bbcnt1 < 0 )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" Error: Too many bad blocks to replace\n");
    else
      Kprintf(" Error: Too many bad blocks to replace\n");
    return -1;
  }
  for ( blocksd = 0; blocksd < g_device_info->m_block_size; ++blocksd )
  {
    do_output_bb_info(blocksd, abspart, bboffs);
    s147_dev9_mem_mmio.m_watchdog_flag2 = 0;
  }
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("\n");
  else
    Kprintf("\n");
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2(" [3/3]Write Boot Sector and Logical Address Table\n");
  else
    Kprintf(" [3/3]Write Boot Sector and Logical Address Table\n");
  memset(&g_nand_partbuf, 0, 160);
  strncpy((char *)&g_nand_partbuf, "S147NAND", 9);
  g_nand_partbuf.m_hdr.m_bootsector_ver_1 = 3;
  g_nand_partbuf.m_hdr.m_bootsector_ver_2 = 0;
  for ( i = 0; i < 8; ++i )
  {
    xnand_partition_offset = get_nand_partition_offset(i, abspart);
    xnand_partition_size = get_nand_partition_size(i, abspart);
    g_nand_partbuf.m_hdr.m_nand_partition_info[2 * i] = xnand_partition_offset;
    g_nand_partbuf.m_hdr.m_nand_partition_info[2 * i + 1] = xnand_partition_size;
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(
        " atfile%d: StartBlock = 0x%04x(%4d) / BlockSize = 0x%04x(%4d)\n",
        i,
        xnand_partition_offset,
        xnand_partition_offset,
        xnand_partition_size,
        xnand_partition_size);
    else
      Kprintf(
        " atfile%d: StartBlock = 0x%04x(%4d) / BlockSize = 0x%04x(%4d)\n",
        i,
        xnand_partition_offset,
        xnand_partition_offset,
        xnand_partition_size,
        xnand_partition_size);
  }
  g_nand_partbuf.m_hdr.m_nand_partition_8 = get_nand_partition_offset(8, abspart);
  g_nand_partbuf.m_hdr.m_nand_partition_8_size = get_nand_partition_size(8, abspart);
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2(
      " system : StartBlock = 0x%04x(%4d) / BlockSize = 0x%04x(%4d)\n",
      g_nand_partbuf.m_hdr.m_nand_partition_8,
      g_nand_partbuf.m_hdr.m_nand_partition_8,
      g_nand_partbuf.m_hdr.m_nand_partition_8_size,
      g_nand_partbuf.m_hdr.m_nand_partition_8_size);
  else
    Kprintf(
      " system : StartBlock = 0x%04x(%4d) / BlockSize = 0x%04x(%4d)\n",
      g_nand_partbuf.m_hdr.m_nand_partition_8,
      g_nand_partbuf.m_hdr.m_nand_partition_8,
      g_nand_partbuf.m_hdr.m_nand_partition_8_size,
      g_nand_partbuf.m_hdr.m_nand_partition_8_size);
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("\n");
  else
    Kprintf("\n");
  g_nand_partbuf.m_hdr.m_nand_seccode[0] = g_secr_code_1;
  g_nand_partbuf.m_hdr.m_nand_seccode[1] = g_secr_code_2;
  g_nand_partbuf.m_hdr.m_nand_vidmode[0] = g_boot_video_mode;
  strncpy((char *)g_nand_partbuf.m_hdr.m_nand_desc, g_device_info->m_nand_name, 32);
  g_nand_partbuf.m_hdr.m_page_size_noecc = g_device_info->m_page_size_noecc;
  g_nand_partbuf.m_hdr.m_page_size_withecc = g_device_info->m_page_size_withecc;
  g_nand_partbuf.m_hdr.m_pages_per_block = g_device_info->m_pages_per_block;
  g_nand_partbuf.m_hdr.m_block_size = g_device_info->m_block_size;
  g_nand_partbuf.m_hdr.m_acmem_delay_val = 0;
  g_nand_partbuf.m_hdr.m_acio_delay_val = generate_acio_delay_val(3, 3, 3);
  s147nand_22_nand_write_dma(&g_nand_partbuf, 0, 0, 160);
  do_dma_write_bytes_multi(g_blockinfo_dat_buf, 1, 2 * g_device_info->m_block_size);
  return 0;
}
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);
// 407CA0: using guessed type char g_secr_code_1;
// 407CA1: using guessed type char g_secr_code_2;
// 407CAC: using guessed type int g_boot_video_mode;
// 408700: using guessed type romwrite_part_buf_ g_nand_partbuf;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (004028F4) --------------------------------------------------------
int do_write_partition(int part)
{
  int blockoffs1; // $s0
  int blockoffs2; // $v0
  int tblockoffs2; // $v0
  int blockoffs5; // $v0
  int fd1; // [sp+1Ch] [+1Ch]
  int state; // [sp+20h] [+20h] BYREF
  int bytes; // [sp+24h] [+24h]
  int partsizebytes; // [sp+28h] [+28h]
  int xind2; // [sp+2Ch] [+2Ch]
  int xind1; // [sp+30h] [+30h]
  int pages; // [sp+34h] [+34h]
  int blocks; // [sp+38h] [+38h]
  int pageoffs; // [sp+3Ch] [+3Ch]
  int partblocks1; // [sp+40h] [+40h]
  int readres; // [sp+44h] [+44h]
  int xind3; // [sp+48h] [+48h]
  int xindbytes; // [sp+4Ch] [+4Ch]
  int i; // [sp+54h] [+54h]
  int finished;
  int actual_readres;
  int expected_readres;
  int err;

  actual_readres = 0;
  expected_readres = 0;
  err = 0;
  if ( part == 9 )
  {
    partblocks1 = (s147nand_9_get_nand_partition(8) - 1) * g_device_info->m_pages_per_block;
    if ( partblocks1 < 0 )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2(" Error: No partition #0 table\n");
      else
        Kprintf(" Error: No partition #0 table\n");
      return -1;
    }
    fd1 = open(g_atfile_info_image, 1);
    if ( fd1 < 0 )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2(" Error: File not found - \"%s\"\n", g_atfile_info_image);
      else
        Kprintf(" Error: File not found - \"%s\"\n", g_atfile_info_image);
      return -1;
    }
  }
  else
  {
    partblocks1 = s147nand_9_get_nand_partition(part) * g_device_info->m_pages_per_block;
    if ( partblocks1 < 0 )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2(" Error: Invalid unit number\n");
      else
        Kprintf(" Error: Invalid unit number\n");
      return -1;
    }
    fd1 = open(g_atfile_part_image[part], 1);
    if ( fd1 < 0 )
    {
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2(" Error: File not found - \"%s\"\n", g_atfile_part_image[part]);
      else
        Kprintf(" Error: File not found - \"%s\"\n", g_atfile_part_image[part]);
      return -1;
    }
  }
  CpuSuspendIntr(&state);
  g_page_buf = (char *)AllocSysMemory(0, g_device_info->m_page_size_noecc, 0);
  CpuResumeIntr(state);
  if ( !g_page_buf )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2("\nError: AllocSysMemory failed\n\n");
    else
      Kprintf("\nError: AllocSysMemory failed\n\n");
    err = 1;
  }
  if ( !err )
  {
    if ( part == 9 )
    {
      bytes = lseek(fd1, 0, 2);
      if ( g_device_info->m_page_size_noecc < bytes )
      {
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" Error: INFO image file is too large - \"%s\"\n", g_atfile_info_image);
        else
          Kprintf(" Error: INFO image file is too large - \"%s\"\n", g_atfile_info_image);
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" FileSize(%d) > info(%d)\n", bytes, g_device_info->m_page_size_noecc);
        else
          Kprintf(" FileSize(%d) > info(%d)\n", bytes, g_device_info->m_page_size_noecc);
        err = 1;
      }
      if ( !err )
      {
        lseek(fd1, 0, 0);
        expected_readres = 8;
        actual_readres = read(fd1, g_page_buf, expected_readres);
        if ( actual_readres < expected_readres )
        {
          err = 1;
        }
        if ( !err )
        {
          if ( strncmp(g_page_buf, "S147INFO", 8) )
          {
            if ( is_send_print_to_osdsys() == 1 )
              do_print_to_osdsys_2(" Error: \"%s\" is not a S147INFO-image file\n", g_atfile_info_image);
            else
              Kprintf(" Error: \"%s\" is not a S147INFO-image file\n", g_atfile_info_image);
            err = 1;
          }
          if ( !err )
          {
            pages = 1;
            blocks = 1;
          }
        }
      }
    }
    else
    {
      bytes = lseek(fd1, 0, 2);
      partsizebytes = s147nand_10_get_nand_partition_size(part)
                    * g_device_info->m_pages_per_block
                    * g_device_info->m_page_size_noecc;
      if ( partsizebytes < bytes )
      {
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" Error: ROM image file is too large - \"%s\"\n", g_atfile_part_image[part]);
        else
          Kprintf(" Error: ROM image file is too large - \"%s\"\n", g_atfile_part_image[part]);
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" FileSize(%d) > atfile%d(%d)\n", bytes, part, partsizebytes);
        else
          Kprintf(" FileSize(%d) > atfile%d(%d)\n", bytes, part, partsizebytes);
        err = 1;
      }
      if ( !err )
      {
        lseek(fd1, 0, 0);
        expected_readres = 0x20;
        actual_readres = read(fd1, g_page_buf, expected_readres);
        if ( actual_readres < expected_readres )
        {
          err = 1;
        }
        if ( !err )
        {
          if ( strncmp(g_page_buf, "S147ROM", 8) )
          {
            if ( is_send_print_to_osdsys() == 1 )
              do_print_to_osdsys_2(" Error: \"%s\" is not a S147ROM-image file\n", g_atfile_part_image[part]);
            else
              Kprintf(" Error: \"%s\" is not a S147ROM-image file\n", g_atfile_part_image[part]);
            err = 1;
          }
          if ( !err )
          {
            pages = s147nand_30_bytes2pagesnoeccround(bytes);
            blocks = s147nand_29_pages2blockround(pages);
          }
        }
      }
    }
  }
  if ( !err )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" FileSize = %dbytes SectorSize=%dsectors BlockSize=%dblocks\n", bytes, pages, blocks);
    else
      Kprintf(" FileSize = %dbytes SectorSize=%dsectors BlockSize=%dblocks\n", bytes, pages, blocks);
    lseek(fd1, 0, 0);
    xind2 = 0;
    pageoffs = partblocks1;
    finished = 0;
    for ( xind1 = 0; xind1 < blocks; xind1 += 1 )
    {
      blockoffs1 = s147nand_28_pages2blocks(pageoffs);
      blockoffs2 = s147nand_28_pages2blocks(pageoffs);
      tblockoffs2 = s147nand_13_translate_blockoffs(blockoffs2);
      if ( is_send_print_to_osdsys() == 1 )
      {
        do_print_to_osdsys_2(
          " atfile%d(%d/%d): LogBlock=%d (PhyBlock=%d) ",
          part,
          xind1,
          blocks - 1,
          blockoffs1,
          tblockoffs2);
      }
      else
      {
        Kprintf(" atfile%d(%d/%d): LogBlock=%d (PhyBlock=%d) ", part, xind1, blocks - 1, blockoffs1, tblockoffs2);
      }
      s147_dev9_mem_mmio.m_led = s147nand_28_pages2blocks(pageoffs) & 3;
      if ( (g_curflag & 0xFF0000) == 0 )
      {
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2("Erase -> ");
        else
          Kprintf("Erase -> ");
        readres = s147nand_11_erasetranslatepageoffs(pageoffs);
        if ( readres == -1470020 )
        {
          if ( is_send_print_to_osdsys() == 1 )
            do_print_to_osdsys_2("\nromwrite: Bad block error, use \"-f\" option.\n");
          else
            Kprintf("\nromwrite: Bad block error, use \"-f\" option.\n");
          err = 1;
          finished = 1;
          break;
        }
      }
      if ( is_send_print_to_osdsys() == 1 )
        do_print_to_osdsys_2("Write -> Verify\n");
      else
        Kprintf("Write -> Verify\n");
      xind3 = 0;
      while ( xind3 < g_device_info->m_pages_per_block )
      {
        g_part_buf = &g_nand_partbuf;
        if ( part != 9 )
        {
          xindbytes = bytes - xind2 * g_device_info->m_page_size_noecc;
          if ( xindbytes > 0x20000 )
            expected_readres = 0x20000;
          else
            expected_readres = xindbytes;
        }
        else
        {
          memset(g_part_buf, 0, g_device_info->m_page_size_noecc);
          if ( g_device_info->m_page_size_noecc < bytes )
            expected_readres = g_device_info->m_page_size_noecc;
          else
            expected_readres = bytes;
        }
        // Unofficial: check against read bytes instead of 0
        actual_readres = read(fd1, g_part_buf, expected_readres);
        if ( actual_readres < expected_readres )
        {
          err = 1;
          finished = 1;
          break;
        }
        for ( i = 0; i <= 0x1FFFF; i += g_device_info->m_page_size_noecc )
        {
          s147nand_8_multi_write_dma((char *)g_part_buf + i, pageoffs, 1);
          s147nand_7_multi_read_dma(g_page_buf, pageoffs, 1);
          readres = do_verify((char *)g_part_buf + i, g_page_buf, g_device_info->m_page_size_noecc);
          if ( readres )
          {
            if ( is_send_print_to_osdsys() == 1 )
            {
              blockoffs5 = s147nand_28_pages2blocks(pageoffs);
              do_print_to_osdsys_2("romwrite: Verify error - LogBlock=%d LogPage=%d\n", blockoffs5, pageoffs);
            }
            else
            {
              blockoffs5 = s147nand_28_pages2blocks(pageoffs);
              Kprintf("romwrite: Verify error - LogBlock=%d LogPage=%d\n", blockoffs5, pageoffs);
            }
            err = 1;
            finished = 1;
            break;
          }
          ++pageoffs;
          ++xind2;
          ++xind3;
          if ( xind2 >= pages )
          {
            finished = 1;
            break;
          }
        }
        if ( finished )
          break;
      }
      if ( finished )
        break;
    }
  }
  if ( actual_readres < expected_readres )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" Error: File-I/O fault (%d)\n", actual_readres);
    else
      Kprintf(" Error: File-I/O fault (%d)\n", actual_readres);
  }
  if ( fd1 >= 0 )
  {
    close(fd1);
  }
  if ( err )
  {
    CpuSuspendIntr(&state);
    if ( g_part_buf )
      FreeSysMemory(g_part_buf);
    if ( g_page_buf )
      FreeSysMemory(g_page_buf);
    CpuResumeIntr(state);
  }
  return err ? -1 : 0;
}
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);
// 407CA4: using guessed type int g_curflag;
// 408700: using guessed type romwrite_part_buf_ g_nand_partbuf;
// B0000000: using guessed type s147_dev9_mem_mmio_ s147_dev9_mem_mmio;

//----- (00403758) --------------------------------------------------------
int check_badblock_count()
{
  while ( g_badblock_count < get_nand_partition_offset(8, 8) - 1 )
  {
    if ( g_blockinfo_str_buf[g_badblock_count] == 'R' )
      return g_badblock_count++;
    ++g_badblock_count;
  }
  return -1;
}
// 407CB8: using guessed type int g_badblock_count;

//----- (00403834) --------------------------------------------------------
int get_nand_partition_offset(int part, int abspart)
{
  int m_block_size; // $v1

  if ( part == 8 )
    return get_nand_block_size_div_32();
  if ( abspart )
  {
    if ( part < 0 || part >= abspart )
      return -1;
    m_block_size = g_device_info->m_block_size;
    if ( abspart == -1 && m_block_size == (int)0x80000000 )
      _break(6u, 0);
    if ( part )
      return m_block_size / abspart * part;
    return get_nand_block_size_div_32_div_64();
  }
  if ( !part )
    return get_nand_block_size_div_32_div_64();
  if ( part == 1 )
    return g_device_info->m_block_size / 4;
  else
    return -1;
}
// 403940: conditional instruction was optimized away because $a1.4!=0

//----- (004039D0) --------------------------------------------------------
int get_nand_partition_size(int part, int abspart)
{
  int xret; // $s0
  int m_block_size; // $v1

  if ( part == 8 )
  {
    xret = get_nand_block_size_div_32_div_64();
    return xret - get_nand_block_size_div_32();
  }
  else if ( abspart )
  {
    if ( part >= 0 && part < abspart )
    {
      m_block_size = g_device_info->m_block_size;
      if ( abspart == -1 && m_block_size == (int)0x80000000 )
        _break(6u, 0);
      if ( part )
        return m_block_size / abspart;
      else
        return m_block_size / abspart - get_nand_block_size_div_32_div_64();
    }
    else
    {
      return 0;
    }
  }
  else if ( part )
  {
    if ( part == 1 )
      return 3 * (g_device_info->m_block_size / 4);
    else
      return 0;
  }
  else
  {
    return g_device_info->m_block_size / 4 - get_nand_block_size_div_32_div_64();
  }
}
// 403B1C: conditional instruction was optimized away because $a1.4!=0

//----- (00403BA4) --------------------------------------------------------
int get_nand_block_size_div_32_div_64()
{
  return get_nand_block_size_div_32() + g_device_info->m_block_size / 64;
}

//----- (00403C18) --------------------------------------------------------
int get_nand_block_size_div_32()
{
  return g_device_info->m_block_size / 32;
}

//----- (00403C64) --------------------------------------------------------
BOOL do_dma_write_bytes_multi(void *ptr, int pageoffs, int pagecnt)
{
  BOOL result; // $v0
  int i; // [sp+10h] [+10h]
  int bytecnt; // [sp+14h] [+14h]

  bytecnt = s147nand_30_bytes2pagesnoeccround(pagecnt);
  for ( i = 0; ; ++i )
  {
    result = i < bytecnt;
    if ( i >= bytecnt )
      break;
    s147nand_22_nand_write_dma(
      (char *)ptr + 4 * (g_device_info->m_page_size_noecc >> 2) * i,
      pageoffs + i,
      0,
      g_device_info->m_page_size_noecc);
  }
  return result;
}

//----- (00403D40) --------------------------------------------------------
int do_list_files(int part)
{
  signed __int32 m_entrycnt; // [sp+1Ch] [+1Ch]
  int pageoffs; // [sp+20h] [+20h]
  int xind1; // [sp+28h] [+28h]
  int i; // [sp+2Ch] [+2Ch]
  int dircnt; // [sp+30h] [+30h]
  int filcnt; // [sp+34h] [+34h]
  int finished;
  char pathtmp[24]; // [sp+38h] [+38h] BYREF

  m_entrycnt = -1;
  dircnt = 0;
  filcnt = 0;
  finished = 0;
  pageoffs = s147nand_9_get_nand_partition(part) * g_device_info->m_pages_per_block;
  if ( pageoffs < 0 )
    return -19;
  for ( xind1 = 0; xind1 < 64; ++xind1 )
  {
    s147nand_7_multi_read_dma(&g_nand_partbuf, pageoffs + xind1, 1);
    for ( i = 0; i < 64; ++i )
    {
      if ( (xind1 << 6) - 1 + i == -1 )
      {
        if ( strncmp((const char *)&g_nand_partbuf, "S147ROM", 8) )
        {
          if ( is_send_print_to_osdsys() == 1 )
            do_print_to_osdsys_2(" \"%s%d:\" ... No data\n", "atfile", part);
          else
            Kprintf(" \"%s%d:\" ... No data\n", "atfile", part);
          if ( is_send_print_to_osdsys() == 1 )
            do_print_to_osdsys_2(" -----------------------------\n\n");
          else
            Kprintf(" -----------------------------\n\n");
          return -19;
        }
        m_entrycnt = g_nand_partbuf.m_dir.m_entrycnt;
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" \"%s%d:\"\n", "atfile", part);
        else
          Kprintf(" \"%s%d:\"\n", "atfile", part);
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" -----------------------------\n");
        else
          Kprintf(" -----------------------------\n");
      }
      else
      {
        if ( (xind1 << 6) - 1 + i >= m_entrycnt )
        {
          finished = 1;
          break;
        }
        strcpy(pathtmp, (const char *)&g_nand_partbuf + 32 * i);
        if ( g_nand_partbuf.m_direntry[i].m_type == 'D' )
        {
          strcat(pathtmp, "/");
          ++dircnt;
        }
        else
        {
          ++filcnt;
        }
        if ( is_send_print_to_osdsys() == 1 )
          do_print_to_osdsys_2(" %9d  %s\n", g_nand_partbuf.m_direntry[i].m_size, pathtmp);
        else
          Kprintf(" %9d  %s\n", g_nand_partbuf.m_direntry[i].m_size, pathtmp);
        DelayThread(20000);
      }
    }
    if ( finished )
    {
      break;
    }
  }
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2(" -----------------------------\n");
  else
    Kprintf(" -----------------------------\n");
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("   %d directories, %d files\n", dircnt, filcnt);
  else
    Kprintf("   %d directories, %d files\n", dircnt, filcnt);
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("\n");
  else
    Kprintf("\n");
  return m_entrycnt;
}
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);
// 408700: using guessed type romwrite_part_buf_ g_nand_partbuf;

//----- (004041F4) --------------------------------------------------------
int do_output_bb_info(int blocksd, int abspart, int bboffs)
{
  int result; // $v0
  signed __int8 chrval; // [sp+10h] [+10h]

  (void)abspart;
  chrval = g_blockinfo_str_buf[blocksd];
  if ( blocksd == bboffs )
    chrval = 'I';
  if ( (blocksd & 0x3F) == 0 )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" %04X(%4d):", blocksd, blocksd);
    else
      Kprintf(" %04X(%4d):", blocksd, blocksd);
  }
  if ( is_send_print_to_osdsys() == 1 )
    do_print_to_osdsys_2("%c", chrval);
  else
    Kprintf("%c", chrval);
  if ( (blocksd & 0xF) == 15 )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2(" ");
    else
      Kprintf(" ");
  }
  result = blocksd & 0x3F;
  if ( result == '?' )
  {
    if ( is_send_print_to_osdsys() == 1 )
      do_print_to_osdsys_2("\n");
    else
      Kprintf("\n");
  }
  return result;
}
// 4055CC: using guessed type int do_print_to_osdsys_2(const char *, ...);

//----- (00404380) --------------------------------------------------------
int do_verify(void *buf1, void *buf2, int len)
{
  int i; // [sp+0h] [+0h]

  for ( i = 0; i < len / 4; ++i )
  {
    if ( *((_DWORD *)buf1 + i) != *((_DWORD *)buf2 + i) )
      return *((_DWORD *)buf1 + i) - *((_DWORD *)buf2 + i);
  }
  return 0;
}

//----- (00404454) --------------------------------------------------------
nand_id_desc_info_stru_ *do_parse_device_info(char *nandid)
{
  int i; // [sp+0h] [+0h]
  int cmpval; // [sp+4h] [+4h]
  int j; // [sp+8h] [+8h]
  u32 idval; // [sp+Ch] [+Ch]

  for ( i = 0; g_nand_type_info[i].m_nand_name; ++i )
  {
    cmpval = 0;
    for ( j = 0; j < 5; ++j )
    {
      idval = g_nand_type_info[i].m_id[j];
      if ( (int)idval == -1 )
      {
        ++cmpval;
      }
      else if ( (unsigned __int8)idval == (unsigned __int8)nandid[j] )
      {
        ++cmpval;
      }
    }
    if ( cmpval == 5 )
      return &g_nand_type_info[i];
  }
  return 0;
}
// 4060B0: using guessed type nand_id_desc_info_stru_ g_nand_type_info[4];
