
#include <irx_imports.h>

IRX_ID("FILEIO_service", 2, 18);

#define __fastcall
#define __cdecl
#define __noreturn

#define _BYTE u8
#define _WORD u16
#define _DWORD u32

struct devctl_fs_blkio_param
{
  int m_lbn;
  unsigned int m_nblk;
  void *m_addr;
  int m_blksize;
  int m_type;
  int m_mode;
};

/* 174 */
struct fio_common_outbuf
{
  int m_taskdata1;
  int m_out_fno;
  int m_taskdata2;
  int m_in_fno;
};

/* 175 */
struct fio_smallbuf_outbuf
{
  struct fio_common_outbuf m_common;
  int m_retres;
  int m_x5;
  int m_x6;
  int m_x7;
};

/* 176 */
struct fio_largebuf_outbuf
{
  struct fio_common_outbuf m_common;
  int m_retres;
  int m_outbufsz;
  int m_inbufsz;
  char m_buf[1024];
};

/* 177 */
struct fio_dirent_outbuf
{
  struct fio_common_outbuf m_common;
  int m_retres;
  int m_eedestptr;
  iox_dirent_t m_dirent;
};

/* 178 */
struct fio_read_outbuf
{
  struct fio_common_outbuf m_common;
  int m_retres;
  int m_remainsz1;
  int m_remainsz2;
  int m_eeptr1;
  int m_eeptr2;
  char m_buf1[64];
  char m_buf2[64];
};

/* 179 */
struct fio_smallbuf64_outbuf
{
  struct fio_common_outbuf m_common;
  s64 m_retres;
  int m_x6;
  int m_x7;
};

/* 180 */
struct fio_common_inbuf
{
  int m_taskdata1;
  int m_taskdata2;
  int m_in_fno;
};

/* 181 */
struct fio_msgbox_inbuf
{
  struct fio_common_inbuf m_common;
  int m_mbxid;
  char m_taskbuf[];
};

/* 182 */
struct fio_fd_open_inbuf
{
  struct fio_common_inbuf m_common;
  int m_flags;
  int m_mode;
  char m_name[256];
};

/* 183 */
struct fio_fd_close_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
};

/* 184 */
struct fio_fd_read_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
  int m_eebuffer;
  int m_eebuffersz;
};

/* 185 */
struct fio_fd_write_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
  int m_eebuffer;
  int m_eebuffersz;
  int m_remainsz;
  char m_buf[64];
};

/* 186 */
struct fio_fd_lseek_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
  int m_pos;
  int m_mode;
};

/* 187 */
struct fio_fd_lseek64_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
  s64 m_pos;
  int m_mode;
};

/* 188 */
struct fio_ioctl_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
  int m_cmd;
  char m_buf[1024];
  int m_outbufsz;
  int m_inbufsz;
};

/* 189 */
struct fio_ioctl2_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
  int m_cmd;
  char m_buf[1024];
  int m_outbufsz;
  int m_inbufsz;
};

/* 190 */
struct fio_remove_inbuf
{
  struct fio_common_inbuf m_common;
  char m_name[256];
};

/* 191 */
struct fio_mkdir_inbuf
{
  struct fio_common_inbuf m_common;
  int m_mode;
  char m_name[256];
};

/* 192 */
struct fio_rmdir_inbuf
{
  struct fio_common_inbuf m_common;
  char m_name[256];
};

/* 193 */
struct fio_format_inbuf
{
  struct fio_common_inbuf m_common;
  char m_dev[1024];
  char m_blockdev[1024];
  char m_arg[1024];
  int m_arglen;
};

/* 194 */
struct fio_adddrv_inbuf
{
  struct fio_common_inbuf m_common;
  void *m_device;
};

/* 195 */
struct fio_deldrv_inbuf
{
  struct fio_common_inbuf m_common;
  void *m_device;
};

/* 196 */
struct fio_dopen_inbuf
{
  struct fio_common_inbuf m_common;
  char m_name[256];
};

/* 197 */
struct fio_dclose_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
};

/* 198 */
struct fio_dread_inbuf
{
  struct fio_common_inbuf m_common;
  int m_fd;
  int m_eedestptr;
};

/* 199 */
struct fio_getstat_inbuf
{
  struct fio_common_inbuf m_common;
  int m_eedestptr;
  char m_name[256];
};

/* 200 */
struct fio_chstat_inbuf
{
  struct fio_common_inbuf m_common;
  int m_statmask;
  iox_dirent_t m_dirent;
};

/* 201 */
struct fio_rename_inbuf
{
  struct fio_common_inbuf m_common;
  char m_oldname[1024];
  char m_newname[1024];
};

/* 202 */
struct fio_chdir_inbuf
{
  struct fio_common_inbuf m_common;
  char m_name[1024];
};

/* 203 */
struct fio_sync_inbuf
{
  struct fio_common_inbuf m_common;
  int m_unused;
  int m_flag;
  char m_dev[1024];
};

/* 204 */
struct fio_mount_inbuf
{
  struct fio_common_inbuf m_common;
  char m_fsname[1024];
  char m_devname[1024];
  char m_arg[1024];
  int m_flag;
  int m_arglen;
};

/* 205 */
struct fio_umount_inbuf
{
  struct fio_common_inbuf m_common;
  char m_fsname[1024];
};

/* 206 */
struct fio_devctl_inbuf
{
  struct fio_common_inbuf m_common;
  char m_name[1024];
  char m_arg[1024];
  int m_cmd;
  int m_arglen;
  int m_outbufsz;
  int m_inbufsz;
};

/* 207 */
struct fio_symlink_inbuf
{
  struct fio_common_inbuf m_common;
  char m_oldname[1024];
  char m_newname[1024];
};

/* 208 */
struct fio_readlink_inbuf
{
  struct fio_common_inbuf m_common;
  int m_inbufsz;
  int m_outbufsz;
  char m_path[1024];
};

//-------------------------------------------------------------------------
// Function declarations

int _start();
static void *__fastcall fileio_alloc_rwbuf(int *out_rwbuf_size);
static void __fastcall fileio_free_rwbuf(void *ptr);
static void fileio_rpc_dealloc_rwbuf();
static void *fileio_rpc_threadbuf_alloc();
static void __fastcall fileio_rpc_threadbuf_free(void *ptr);
static void __fastcall do_call_ee_rcv_res_intr(void *ptr, int sz);
static int __fastcall fileio_rpc_fd_open(struct fio_fd_open_inbuf *inbuf);
static void __fastcall fileio_rpc_fd_close(struct fio_fd_close_inbuf *inbuf);
static void __fastcall fileio_rpc_fd_lseek(struct fio_fd_lseek_inbuf *inbuf);
static void __fastcall fileio_rpc_fd_read(struct fio_fd_read_inbuf *inbuf);
static void __fastcall fileio_rpc_fd_write(struct fio_fd_write_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_devctl_blkio(struct fio_devctl_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_ioctl(struct fio_ioctl_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_ioctl2(struct fio_ioctl2_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_remove(struct fio_remove_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_mkdir(struct fio_mkdir_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_rmdir(struct fio_rmdir_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_format(struct fio_format_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_adddrv(struct fio_adddrv_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_deldrv(struct fio_deldrv_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_dopen(struct fio_dopen_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_dclose(struct fio_dclose_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_dread(struct fio_dread_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_getstat(struct fio_getstat_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_chstat(struct fio_chstat_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_rename(struct fio_rename_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_chdir(struct fio_chdir_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_sync(struct fio_sync_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_mount(struct fio_mount_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_umount(struct fio_umount_inbuf *inbuf);
static void __fastcall fileio_rpc_fd_lseek64(struct fio_fd_lseek64_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_devctl(struct fio_devctl_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_symlink(struct fio_symlink_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_readlink(struct fio_readlink_inbuf *inbuf);
static void __fastcall __noreturn fileio_rpc_open(struct fio_msgbox_inbuf *inbuf);
static void (__noreturn *__fastcall get_fileio_rpc_command_thfn(int cmd))();
static int *__fastcall fileio_rpc_service_handler(int fno, void *buffer, int length);
static void __noreturn power_off_event_handler();
static void fileio_rpc_start_thread(void *userdata);
static void __fastcall heap_rpc_load_iop_heap(int buffer, int length, int *outbuf);
static void __fastcall heap_rpc_alloc_iop_heap(const int *buffer, int length, void **outbuf);
static void __fastcall heap_rpc_alloc_iop_heap_ex(int buffer, int length, void **outbuf);
static void __fastcall heap_rpc_free_iop_heap(void **buffer, int length, int *outbuf);
static void __fastcall heap_rpc_query_mem_size(int buffer, int length, u32 *outbuf);
static void __fastcall heap_rpc_query_max_free_mem_size(int buffer, int length, u32 *outbuf);
static void __fastcall heap_rpc_query_total_free_mem_size(int buffer, int length, u32 *outbuf);
static void __fastcall heap_rpc_query_block_top_address(void **buffer, int length, void **outbuf);
static void __fastcall heap_rpc_query_block_size(void **buffer, int length, int *outbuf);
static int *__fastcall heap_rpc_service_handler(int fno, void *buffer, int length);
static void heap_rpc_start_thread(void *userdata);
#ifdef UNUSED_FUNC
static void __fastcall iopinfo_rpc_querybootmode(int buffer, int length, int *outbuf);
static int *__fastcall iopinfo_rpc_service_handler(int fno, void *buffer, int length);
static int iopinfo_rpc_service_start_thread_unused();
#endif

//-------------------------------------------------------------------------
// Data declarations

static int g_verstr = 808464691; // weak
static int g_fileio_verbose = 0; // weak
static int g_rwbuf_max_size = 16384; // weak
static int g_th_priority = 96; // weak
static int g_result_destbuf_ee_idx = 0; // weak
static unsigned int g_rwbuf_ptr_count_allowed = 4; // weak
static unsigned int g_rwbuf_uses = 0; // weak
static void *g_rwbuf_cur_ptr = NULL; // idb
static int g_rwbuf_size = 0; // weak
static int g_rwbuf_is_allocated = 0; // weak
static int g_thids_per_fd[32] =
{
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1,
  -1
};
static void *g_result_destbuf_ee[2];
static int g_sema_for_result_destbuf_ee; // idb
static int g_rwbuf_ef; // idb
static void *g_rwbuf_ptrs[10];
static int g_fileio_rpc_outbuf; // weak
static int g_fileio_rpc_outbuf_verres; // weak
static SifRpcDataQueue_t g_fileio_sif_qd; // weak
static SifRpcServerData_t g_fileio_sif_sd; // idb
static int fileio_rpc_service_in_buf[784]; // weak
static int heap_rpc_outbuf[4]; // weak
static SifRpcDataQueue_t g_heap_sif_qd; // weak
static SifRpcServerData_t g_heap_sif_sd; // idb
static int heap_rpc_service_in_buf[64]; // weak
#ifdef UNUSED_FUNC
static int iopinfo_rpc_outbuf[4]; // weak
static int iopinfo_rpc_service_in_buf[16]; // weak
static SifRpcDataQueue_t g_iopinfo_sif_qd; // weak
static SifRpcServerData_t g_iopinfo_sif_sd; // idb
#endif
static int g_mbxid_for_ee_fds[32];


//----- (00400000) --------------------------------------------------------
int _start()
{
  const int *BootMode; // $v0
  int thid_fio; // $a0
  int thid_heap; // $a0
  iop_thread_t thparam; // [sp+10h] [-18h] BYREF

  BootMode = QueryBootMode(3);
  if ( BootMode )
  {
    if ( (BootMode[1] & 1) != 0 )
    {
      printf(" No SIF service(fileio)\n");
      return 1;
    }
    if ( (BootMode[1] & 2) != 0 )
    {
      printf(" No FILEIO service\n");
      return 1;
    }
  }
  CpuEnableIntr();
  thparam.thread = fileio_rpc_start_thread;
  thparam.attr = 0x2000000;
  thparam.priority = 96;
  thparam.stacksize = 4096;
  thparam.option = 0;
  thid_fio = CreateThread(&thparam);
  if ( thid_fio <= 0 )
    return 1;
  StartThread(thid_fio, 0);
  thparam.thread = heap_rpc_start_thread;
  thparam.attr = 0x2000000;
  thparam.priority = 96;
  thparam.stacksize = 2048;
  thparam.option = 0;
  thid_heap = CreateThread(&thparam);
  if ( thid_heap <= 0 )
    return 1;
  StartThread(thid_heap, 0);
  return 0;
}

//----- (00400100) --------------------------------------------------------
static void *__fastcall fileio_alloc_rwbuf(int *out_rwbuf_size)
{
  void *rwbuf_cur_ptr; // $s2
  int rwbuf_size; // $s0
  u32 efbits; // [sp+10h] [-8h] BYREF
  int state; // [sp+14h] [-4h] BYREF

  WaitEventFlag(g_rwbuf_ef, 1u, 16, &efbits);
  CpuSuspendIntr(&state);
  
  rwbuf_cur_ptr = g_rwbuf_cur_ptr;
  rwbuf_size = g_rwbuf_size;
  if ( rwbuf_cur_ptr && rwbuf_size && !g_rwbuf_is_allocated )
  {
    g_rwbuf_is_allocated = 1;
    ++g_rwbuf_uses;
  }
  else
  {
    int try_cnt; // $s1

    *out_rwbuf_size = 0;
    rwbuf_size = g_rwbuf_max_size;
    for ( try_cnt = 0; try_cnt < 8; try_cnt += 1 )
    {
      rwbuf_cur_ptr = AllocSysMemory(1, rwbuf_size, 0);
      if ( rwbuf_cur_ptr )
      {
        unsigned int cur_ptr_count; // $v1
        ++g_rwbuf_uses;
        if ( !g_rwbuf_cur_ptr || !g_rwbuf_size )
        {
          g_rwbuf_cur_ptr = rwbuf_cur_ptr;
          g_rwbuf_size = rwbuf_size;
          g_rwbuf_is_allocated = 1;
        }
        for ( cur_ptr_count = 0; cur_ptr_count < g_rwbuf_ptr_count_allowed; cur_ptr_count += 1 )
        {
          if ( !g_rwbuf_ptrs[cur_ptr_count] )
          {
            g_rwbuf_ptrs[cur_ptr_count] = rwbuf_cur_ptr;
            break;
          }
        }
        break;
      }
      rwbuf_size /= 2;
    }
    if ( try_cnt == 8 )
    {
      SetEventFlag(g_rwbuf_ef, 1u);
      CpuResumeIntr(state);
      return 0;
    }
  }
  *out_rwbuf_size = rwbuf_size;
  if ( g_rwbuf_uses < (unsigned int)g_rwbuf_ptr_count_allowed )
    SetEventFlag(g_rwbuf_ef, 1u);
  CpuResumeIntr(state);
  return rwbuf_cur_ptr;
}
// 403244: using guessed type int g_rwbuf_max_size;
// 403250: using guessed type int g_rwbuf_ptr_count_allowed;
// 403254: using guessed type int g_rwbuf_uses;
// 40325C: using guessed type int g_rwbuf_size;
// 403260: using guessed type int g_rwbuf_is_allocated;

//----- (00400328) --------------------------------------------------------
static void __fastcall fileio_free_rwbuf(void *ptr)
{
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  if ( ptr == g_rwbuf_cur_ptr && ptr )
  {
    g_rwbuf_is_allocated = 0;
    --g_rwbuf_uses;
    SetEventFlag(g_rwbuf_ef, 1u);
  }
  else if ( !FreeSysMemory(ptr) )
  {
    unsigned int cur_ptr_count; // $a0

    --g_rwbuf_uses;
    for ( cur_ptr_count = 0; cur_ptr_count < g_rwbuf_ptr_count_allowed; cur_ptr_count += 1 )
    {
      if ( g_rwbuf_ptrs[cur_ptr_count] == ptr )
      {
        g_rwbuf_ptrs[cur_ptr_count] = 0;
        break;
      }
    }
    SetEventFlag(g_rwbuf_ef, 1u);
  }
  CpuResumeIntr(state);
}
// 403250: using guessed type int g_rwbuf_ptr_count_allowed;
// 403254: using guessed type int g_rwbuf_uses;
// 403260: using guessed type int g_rwbuf_is_allocated;

//----- (00400434) --------------------------------------------------------
static void fileio_rpc_dealloc_rwbuf()
{
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  if ( g_rwbuf_cur_ptr && g_rwbuf_size )
    FreeSysMemory(g_rwbuf_cur_ptr);
  g_rwbuf_is_allocated = 0;
  g_rwbuf_size = 0;
  g_rwbuf_cur_ptr = 0;
  CpuResumeIntr(state);
}
// 40325C: using guessed type int g_rwbuf_size;
// 403260: using guessed type int g_rwbuf_is_allocated;

//----- (004004A8) --------------------------------------------------------
static void *fileio_rpc_threadbuf_alloc()
{
  void *ptr; // $s0
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  ptr = AllocSysMemory(1, 3136, 0);
  CpuResumeIntr(state);
  return ptr;
}

//----- (004004EC) --------------------------------------------------------
static void __fastcall fileio_rpc_threadbuf_free(void *ptr)
{
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  FreeSysMemory(ptr);
  CpuResumeIntr(state);
}

//----- (00400528) --------------------------------------------------------
static void __fastcall do_call_ee_rcv_res_intr(void *ptr, int sz)
{
  int dmat; // $s0
  char cmdbuf[16]; // [sp+18h] [-18h] BYREF
  int state; // [sp+28h] [-8h] BYREF

  WaitSema(g_sema_for_result_destbuf_ee);
  while ( 1 )
  {
    CpuSuspendIntr(&state);
    *(_DWORD *)&cmdbuf[12] = g_result_destbuf_ee_idx;
    dmat = isceSifSendCmd(0x80000011, cmdbuf, 16, ptr, g_result_destbuf_ee[g_result_destbuf_ee_idx], sz);
    if ( dmat )
      g_result_destbuf_ee_idx ^= 1u;
    CpuResumeIntr(state);
    if ( dmat )
      break;
    DelayThread(2000);
  }
  while ( sceSifDmaStat(dmat) >= 0 );
  SignalSema(g_sema_for_result_destbuf_ee);
}
// 40324C: using guessed type int g_result_destbuf_ee_idx;

//----- (0040061C) --------------------------------------------------------
static int __fastcall fileio_rpc_fd_open(struct fio_fd_open_inbuf *inbuf)
{
  int fd; // $v0
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  if ( g_fileio_verbose > 0 )
    printf("open name %s flag 0x%x mode 0x%x\n", inbuf->m_name, inbuf->m_flags, inbuf->m_mode);
  fd = iomanX_open(inbuf->m_name, inbuf->m_flags, inbuf->m_mode);
  fbuf.m_common.m_out_fno = 0;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_retres = fd;
  memset(&fbuf.m_x5, 0, 12);
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  do_call_ee_rcv_res_intr(&fbuf, 32);
  return fd;
}
// 403240: using guessed type int g_fileio_verbose;

//----- (004006B4) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_close(struct fio_fd_close_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  if ( g_fileio_verbose > 0 )
    printf("close fd = %d\n", inbuf->m_fd);
  fbuf.m_common.m_out_fno = 1;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_close(inbuf->m_fd);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
}
// 403240: using guessed type int g_fileio_verbose;

//----- (00400744) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_lseek(struct fio_fd_lseek_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 4;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_lseek(inbuf->m_fd, inbuf->m_pos, inbuf->m_mode);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
}

//----- (004007B8) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_read(struct fio_fd_read_inbuf *inbuf)
{
  int read_res_last; // $s2
  void *rwbuf; // $fp
  int read_sz_end; // $s4
  int read_sz_begin; // $s7
  int read_sz_total; // $s6
  SifDmaTransfer_t dmat; // [sp+10h] [-D8h] BYREF
  struct fio_read_outbuf fbuf; // [sp+20h] [-C8h] BYREF
  int rwbuf_size; // [sp+C8h] [-20h] BYREF
  int state; // [sp+CCh] [-1Ch] BYREF
  int eedestptr1; // [sp+D4h] [-14h]
  int eedestptr2; // [sp+D8h] [-10h]

  read_res_last = 0;
  read_sz_end = 0;
  read_sz_begin = 0;
  read_sz_total = 0;
  eedestptr2 = 0;
  eedestptr1 = 0;
  rwbuf = fileio_alloc_rwbuf(&rwbuf_size);
  if ( !rwbuf )
  {
    read_res_last = -12;
    Kprintf("Error:Cannot alloc r/w buffer\n");
  }
  else
  {
    int m_eebuffersz; // $a1
    unsigned int m_eebuffer; // $a0
    char *eedest; // $s5
    signed int cur_read_remain; // $s3
    int trid; // $s0

    m_eebuffersz = inbuf->m_eebuffersz;
    m_eebuffer = inbuf->m_eebuffer;
    eedestptr1 = m_eebuffer;
    read_sz_begin = m_eebuffersz;
    read_sz_total = 0;
    eedest = 0;
    cur_read_remain = 0;
    read_sz_end = 0;
    eedestptr2 = 0;
    if ( m_eebuffersz >= 64 )
    {
      read_sz_begin = ( (m_eebuffer & 0x3F) != 0 ) ? ((m_eebuffer >> 6 << 6) - (m_eebuffer - 64)) : 0;
      eedest = (char *)(m_eebuffer + read_sz_begin);
      cur_read_remain = ((m_eebuffer + m_eebuffersz) >> 6 << 6) - (m_eebuffer + read_sz_begin);
      read_sz_end = m_eebuffer + m_eebuffersz - ((m_eebuffer + m_eebuffersz) >> 6 << 6);
      eedestptr2 = (m_eebuffer + m_eebuffersz) >> 6 << 6;
    }
    trid = 0;
    if ( read_sz_begin > 0 )
    {
      int read_res_begin; // $v0

      read_res_begin = iomanX_read(inbuf->m_fd, fbuf.m_buf1, read_sz_begin);
      read_res_last = read_res_begin;
      if ( read_sz_begin != read_res_begin )
      {
        read_sz_begin = ( read_res_begin > 0 ) ? read_res_begin : 0;
        cur_read_remain = 0;
        read_sz_end = 0;
      }
      read_sz_total += read_sz_begin;
    }
    if ( cur_read_remain > 0 )
    {
      while ( 1 )
      {
        int cur_rwbuf_sz; // $s1
        int read_res_main; // $v0

        cur_rwbuf_sz = ( rwbuf_size < cur_read_remain ) ? rwbuf_size : cur_read_remain;
        while ( sceSifDmaStat(trid) >= 0 );
        read_res_main = iomanX_read(inbuf->m_fd, rwbuf, cur_rwbuf_sz);
        read_res_last = read_res_main;
        if ( cur_rwbuf_sz != read_res_main )
        {
          if ( read_res_main > 0 )
          {
            int read_res_main_rounded; // $v0
            int outbuf_ind; // $a0

            read_res_main_rounded = read_res_main >> 6 << 6;
            read_sz_end = read_res_main - read_res_main_rounded;
            eedestptr2 = (int)&eedest[read_res_main_rounded];
            for ( outbuf_ind = 0; outbuf_ind < read_sz_end; outbuf_ind += 1 )
            {
              fbuf.m_buf2[outbuf_ind] = ((_BYTE *)rwbuf)[read_res_main_rounded + outbuf_ind];
            }
            if ( read_res_main_rounded )
            {
              dmat.src = rwbuf;
              dmat.dest = eedest;
              dmat.size = read_res_main_rounded;
              dmat.attr = 0;
              while ( 1 )
              {
                CpuSuspendIntr(&state);
                trid = sceSifSetDma(&dmat, 1);
                CpuResumeIntr(state);
                if ( trid )
                  break;
                DelayThread(2000);
              }
            }
            read_sz_total += read_res_main;
          }
          break;
        }
        dmat.src = rwbuf;
        dmat.dest = eedest;
        dmat.size = read_res_main;
        dmat.attr = 0;
        while ( 1 )
        {
          CpuSuspendIntr(&state);
          trid = sceSifSetDma(&dmat, 1);
          CpuResumeIntr(state);
          if ( trid )
            break;
          DelayThread(2000);
        }
        read_sz_total += read_res_main;
        cur_read_remain -= read_res_main;
        eedest += read_res_main;
        if ( cur_read_remain <= 0 )
          break;
      }
    }
    if ( cur_read_remain <= 0 && read_sz_end > 0 )
    {
      int read_res_end; // $v0

      read_res_end = iomanX_read(inbuf->m_fd, fbuf.m_buf2, read_sz_end);
      read_res_last = read_res_end;
      if ( read_sz_end != read_res_end )
        read_sz_end = ( read_res_end > 0 ) ? read_res_end : 0;
      read_sz_total += read_sz_end;
    }
  }
  fbuf.m_eeptr1 = eedestptr1;
  fbuf.m_eeptr2 = eedestptr2;
  fbuf.m_remainsz1 = read_sz_begin;
  fbuf.m_remainsz2 = read_sz_end;
  fbuf.m_common.m_out_fno = 2;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = ( read_res_last < 0 && read_sz_total <= 0 ) ? read_res_last : read_sz_total;
  do_call_ee_rcv_res_intr(&fbuf, 164);
  fileio_free_rwbuf(rwbuf);
}

//----- (00400B14) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_write(struct fio_fd_write_inbuf *inbuf)
{
  int write_res_last; // $s0
  void *rwbuf; // $s6
  int write_sz_total; // $s4
  struct fio_smallbuf_outbuf fbuf; // [sp+18h] [-48h] BYREF
  SifRpcReceiveData_t rdata; // [sp+38h] [-28h] BYREF
  int rwbuf_size; // [sp+58h] [-8h] BYREF

  write_res_last = 0;
  write_sz_total = 0;
  rwbuf = fileio_alloc_rwbuf(&rwbuf_size);
  if ( !rwbuf )
  {
    Kprintf("Error:Cannot alloc r/w buffer\n");
    write_res_last = -12;
  }
  else
  {
    int rwbuf_remain_sz; // $s2
    char *eebuffer_xptr; // $s3

    rwbuf_remain_sz = inbuf->m_eebuffersz - inbuf->m_remainsz;
    eebuffer_xptr = (char *)(inbuf->m_eebuffer + inbuf->m_remainsz);
    if ( inbuf->m_remainsz > 0 )
    {
      int write_res_begin; // $v0

      write_res_begin = iomanX_write(inbuf->m_fd, inbuf->m_buf, inbuf->m_remainsz);
      write_res_last = write_res_begin;
      if ( write_res_begin != inbuf->m_remainsz )
        rwbuf_remain_sz = 0;
      write_sz_total += ( write_res_begin > 0 ) ? write_res_begin : 0;
    }
    if ( rwbuf_remain_sz )
    {
      while ( 1 )
      {
        int bufsz; // $s1
        int write_res_main; // $v0

        bufsz = ( rwbuf_size < rwbuf_remain_sz ) ? rwbuf_size : rwbuf_remain_sz;
        while ( sceSifGetOtherData(&rdata, eebuffer_xptr, rwbuf, bufsz, 0) < 0 )
          DelayThread(2000);
        write_res_main = iomanX_write(inbuf->m_fd, rwbuf, bufsz);
        write_res_last = write_res_main;
        if ( write_res_main != bufsz )
        {
          write_sz_total += ( write_res_main > 0 ) ? write_res_main : 0;
          break;
        }
        write_sz_total += write_res_main;
        rwbuf_remain_sz -= write_res_main;
        eebuffer_xptr += write_res_main;
        if ( !rwbuf_remain_sz )
          break;
      }
    }
  }
  fbuf.m_common.m_out_fno = 3;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = ( write_res_last >= 0 || write_sz_total > 0 ) ? write_sz_total : write_res_last;
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_free_rwbuf(rwbuf);
}
// 400B14: using guessed type SifRpcReceiveData_t rdata;

//----- (00400CCC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_devctl_blkio(struct fio_devctl_inbuf *inbuf)
{
  int devctl_res; // $s2
  struct fio_largebuf_outbuf fbuf; // [sp+20h] [-478h] BYREF
  struct devctl_fs_blkio_param in_lbn; // [sp+440h] [-58h] BYREF
  SifDmaTransfer_t dmat; // [sp+458h] [-40h] BYREF
  SifRpcReceiveData_t rdata; // [sp+468h] [-30h] BYREF
  int rwbuf_size; // [sp+488h] [-10h] BYREF
  int state; // [sp+48Ch] [-Ch] BYREF
  void *rwbuf; // [sp+490h] [-8h]

  fbuf.m_common.m_out_fno = 23;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  devctl_res = 0;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  if ( g_fileio_verbose > 0 )
    Kprintf(
      "FsBlkIO LBN:%d NBLK:%d addr:%x BLKSIZE:%d TYPE:%d mode:%x\n",
      *(_DWORD *)inbuf->m_arg,
      *(_DWORD *)&inbuf->m_arg[4],
      *(_DWORD *)&inbuf->m_arg[8],
      *(_DWORD *)&inbuf->m_arg[12],
      *(_DWORD *)&inbuf->m_arg[16],
      *(_DWORD *)&inbuf->m_arg[20]);
  in_lbn.m_lbn = *(_DWORD *)inbuf->m_arg;
  in_lbn.m_nblk = *(_DWORD *)&inbuf->m_arg[4];
  in_lbn.m_addr = *(void **)&inbuf->m_arg[8];
  in_lbn.m_blksize = *(_DWORD *)&inbuf->m_arg[12];
  in_lbn.m_type = *(_DWORD *)&inbuf->m_arg[16];
  in_lbn.m_mode = *(_DWORD *)&inbuf->m_arg[20];
  rwbuf = fileio_alloc_rwbuf(&rwbuf_size);
  if ( rwbuf )
  {
    unsigned int rwbuf_size_in_blocks; // $s6
    unsigned int size_in_rwbuf_block_units; // $s5
    unsigned int size_in_rwbuf_remainder_block_units; // $fp
    unsigned int cur_block_unit; // $s1

    rwbuf_size_in_blocks = (unsigned int)rwbuf_size / in_lbn.m_blksize;
    size_in_rwbuf_block_units = in_lbn.m_nblk / rwbuf_size_in_blocks;
    size_in_rwbuf_remainder_block_units = in_lbn.m_nblk % rwbuf_size_in_blocks;
    if ( size_in_rwbuf_remainder_block_units )
      size_in_rwbuf_block_units += 1;
    else
      size_in_rwbuf_remainder_block_units = rwbuf_size_in_blocks;
    dmat.attr = 0;
    dmat.src = rwbuf;
    in_lbn.m_addr = rwbuf;
    cur_block_unit = 0;
    for ( dmat.dest = (void *)in_lbn.m_addr;
          cur_block_unit < size_in_rwbuf_block_units;
          dmat.dest = (char *)dmat.dest + dmat.size )
    {
      in_lbn.m_nblk = ( cur_block_unit + 1 == size_in_rwbuf_block_units ) ? size_in_rwbuf_remainder_block_units : rwbuf_size_in_blocks;
      dmat.size = in_lbn.m_nblk * in_lbn.m_blksize;
      if ( in_lbn.m_type )
      {
        while ( sceSifGetOtherData(&rdata, dmat.dest, dmat.src, dmat.size, 0) < 0 )
          DelayThread(2000);
        devctl_res = devctl(inbuf->m_name, inbuf->m_cmd, &in_lbn, inbuf->m_arglen, 0, 0);
        ++cur_block_unit;
        if ( devctl_res < 0 )
          break;
      }
      else
      {
        int trid; // $s0

        devctl_res = devctl(inbuf->m_name, inbuf->m_cmd, &in_lbn, inbuf->m_arglen, 0, 0);
        if ( devctl_res < 0 )
          break;
        while ( 1 )
        {
          CpuSuspendIntr(&state);
          trid = sceSifSetDma(&dmat, 1);
          CpuResumeIntr(state);
          if ( trid )
            break;
          DelayThread(2000);
        }
        while ( sceSifDmaStat(trid) >= 0 );
        ++cur_block_unit;
      }
      in_lbn.m_lbn += in_lbn.m_nblk;
    }
    fileio_free_rwbuf(rwbuf);
  }
  else
  {
    devctl_res = -12;
    Kprintf("Error:Cannot alloc r/w buffer\n");
  }
  fbuf.m_retres = devctl_res;
  do_call_ee_rcv_res_intr(&fbuf, 1052);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}
// 400DFC: conditional instruction was optimized away because $v0.4!=0
// 400E10: conditional instruction was optimized away because $s6.4!=0
// 403240: using guessed type int g_fileio_verbose;
// 400CCC: using guessed type SifRpcReceiveData_t rdata;

//----- (00400FE4) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_ioctl(struct fio_ioctl_inbuf *inbuf)
{
  struct fio_largebuf_outbuf fbuf; // [sp+10h] [-420h] BYREF

  fbuf.m_common.m_out_fno = 5;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  fbuf.m_retres = iomanX_ioctl(inbuf->m_fd, inbuf->m_cmd, inbuf[1].m_common.m_taskdata1 ? inbuf->m_buf : 0);
  do_call_ee_rcv_res_intr(&fbuf, 1052);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401094) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_ioctl2(struct fio_ioctl2_inbuf *inbuf)
{
  struct fio_largebuf_outbuf fbuf; // [sp+18h] [-420h] BYREF

  fbuf.m_common.m_out_fno = 26;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  fbuf.m_retres = iomanX_ioctl2(inbuf->m_fd, inbuf->m_cmd, inbuf[1].m_common.m_taskdata1 ? inbuf->m_buf : 0, inbuf[1].m_common.m_taskdata1, fbuf.m_buf, fbuf.m_inbufsz);
  do_call_ee_rcv_res_intr(&fbuf, 1052);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040116C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_remove(struct fio_remove_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 6;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_remove(inbuf->m_name);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004011E4) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_mkdir(struct fio_mkdir_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 7;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_mkdir(inbuf->m_name, inbuf->m_mode);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401264) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_rmdir(struct fio_rmdir_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 8;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_rmdir(inbuf->m_name);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004012DC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_format(struct fio_format_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 14;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_format(inbuf->m_dev, inbuf->m_blockdev, inbuf->m_arg, inbuf->m_arglen);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040135C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_adddrv(struct fio_adddrv_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 15;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_AddDrv((iop_device_t *)inbuf->m_device);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004013DC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_deldrv(struct fio_deldrv_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 16;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_DelDrv((const char *)&inbuf->m_device);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401454) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_dopen(struct fio_dopen_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 9;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_dopen(inbuf->m_name);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004014CC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_dclose(struct fio_dclose_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 10;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_dclose(inbuf->m_fd);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040154C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_dread(struct fio_dread_inbuf *inbuf)
{
  struct fio_dirent_outbuf fbuf; // [sp+10h] [-160h] BYREF

  fbuf.m_common.m_out_fno = 11;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_dread(inbuf->m_fd, &fbuf.m_dirent);
  fbuf.m_eedestptr = inbuf->m_eedestptr;
  do_call_ee_rcv_res_intr(&fbuf, 348);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004015C8) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_getstat(struct fio_getstat_inbuf *inbuf)
{
  struct fio_dirent_outbuf fbuf; // [sp+10h] [-160h] BYREF

  fbuf.m_common.m_out_fno = 12;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_getstat(inbuf->m_name, &fbuf.m_dirent.stat);
  fbuf.m_eedestptr = inbuf->m_eedestptr;
  do_call_ee_rcv_res_intr(&fbuf, 348);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040163C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_chstat(struct fio_chstat_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 13;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_chstat(inbuf->m_dirent.name, &inbuf->m_dirent.stat, inbuf->m_statmask);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004016BC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_rename(struct fio_rename_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 17;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_rename(inbuf->m_oldname, inbuf->m_newname);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401734) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_chdir(struct fio_chdir_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 18;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_chdir(inbuf->m_name);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004017AC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_sync(struct fio_sync_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 19;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_sync(inbuf->m_dev, inbuf->m_flag);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040182C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_mount(struct fio_mount_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+18h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 20;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_mount(inbuf->m_fsname, inbuf->m_devname, inbuf->m_flag, inbuf->m_arg, inbuf->m_arglen);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004018B8) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_umount(struct fio_umount_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 21;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_umount(inbuf->m_fsname);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401930) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_lseek64(struct fio_fd_lseek64_inbuf *inbuf)
{
  struct fio_smallbuf64_outbuf fbuf; // [sp+18h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 22;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_lseek64(inbuf->m_fd, inbuf->m_pos, inbuf->m_mode);
  fbuf.m_x7 = 0;
  fbuf.m_x6 = 0;
  do_call_ee_rcv_res_intr(&fbuf, 32);
}

//----- (004019A8) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_devctl(struct fio_devctl_inbuf *inbuf)
{
  struct fio_largebuf_outbuf fbuf; // [sp+18h] [-420h] BYREF

  fbuf.m_common.m_out_fno = 23;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  fbuf.m_retres = iomanX_devctl(inbuf->m_name, inbuf->m_cmd, inbuf->m_arglen ? inbuf->m_arg : 0, inbuf->m_arglen, fbuf.m_buf, fbuf.m_inbufsz);
  do_call_ee_rcv_res_intr(&fbuf, 1052);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401A7C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_symlink(struct fio_symlink_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  fbuf.m_common.m_out_fno = 24;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_symlink(inbuf->m_oldname, inbuf->m_newname);
  memset(&fbuf.m_x5, 0, 12);
  do_call_ee_rcv_res_intr(&fbuf, 32);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401AF4) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_readlink(struct fio_readlink_inbuf *inbuf)
{
  struct fio_largebuf_outbuf fbuf; // [sp+10h] [-420h] BYREF

  fbuf.m_common.m_out_fno = 25;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  fbuf.m_retres = iomanX_readlink(inbuf->m_path, fbuf.m_buf, fbuf.m_inbufsz);
  do_call_ee_rcv_res_intr(&fbuf, 1052);
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401B78) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_open(struct fio_msgbox_inbuf *inbuf)
{
  int m_mbxid; // $s1
  int fd; // $v0
  struct fio_msgbox_inbuf *threadbuf_2; // $s0

  m_mbxid = inbuf->m_mbxid;
  fd = fileio_rpc_fd_open((struct fio_fd_open_inbuf *)inbuf->m_taskbuf);
  fileio_rpc_threadbuf_free(inbuf);
  threadbuf_2 = NULL;
  if ( fd >= 0 )
  {
    while ( 1 )
    {
      if ( threadbuf_2 )
        fileio_rpc_threadbuf_free(threadbuf_2);
      ReceiveMbx((void **)&threadbuf_2, m_mbxid);
      if ( g_fileio_verbose > 0 )
        printf("ReceiveMbx mbxid= %08x fno= %d addr %08x\n", m_mbxid, threadbuf_2->m_common.m_in_fno, (unsigned int)threadbuf_2);
      switch ( threadbuf_2->m_common.m_in_fno )
      {
        case 1:
          fileio_rpc_fd_close((struct fio_fd_close_inbuf *)threadbuf_2->m_taskbuf);
          fileio_rpc_threadbuf_free(threadbuf_2);
          break;
        case 2:
          fileio_rpc_fd_read((struct fio_fd_read_inbuf *)threadbuf_2->m_taskbuf);
          continue;
        case 3:
          fileio_rpc_fd_write((struct fio_fd_write_inbuf *)threadbuf_2->m_taskbuf);
          continue;
        case 4:
          fileio_rpc_fd_lseek((struct fio_fd_lseek_inbuf *)threadbuf_2->m_taskbuf);
          continue;
        case 0x16:
          fileio_rpc_fd_lseek64((struct fio_fd_lseek64_inbuf *)threadbuf_2->m_taskbuf);
          continue;
        default:
          continue;
      }
      break;
    }
  }
  DeleteMbx(m_mbxid);
  ExitThread();
}
// 403240: using guessed type int g_fileio_verbose;

//----- (00401CA4) --------------------------------------------------------
static void (__noreturn *__fastcall get_fileio_rpc_command_thfn(int cmd))()
{
  switch ( cmd )
  {
    case 0:
      return (void (__noreturn *)())fileio_rpc_open;
    case 5:
      return (void (__noreturn *)())fileio_rpc_ioctl;
    case 6:
      return (void (__noreturn *)())fileio_rpc_remove;
    case 7:
      return (void (__noreturn *)())fileio_rpc_mkdir;
    case 8:
      return (void (__noreturn *)())fileio_rpc_rmdir;
    case 9:
      return (void (__noreturn *)())fileio_rpc_dopen;
    case 10:
      return (void (__noreturn *)())fileio_rpc_dclose;
    case 11:
      return (void (__noreturn *)())fileio_rpc_dread;
    case 12:
      return (void (__noreturn *)())fileio_rpc_getstat;
    case 13:
      return (void (__noreturn *)())fileio_rpc_chstat;
    case 14:
      return (void (__noreturn *)())fileio_rpc_format;
    case 15:
      return (void (__noreturn *)())fileio_rpc_adddrv;
    case 16:
      return (void (__noreturn *)())fileio_rpc_deldrv;
    case 17:
      return (void (__noreturn *)())fileio_rpc_rename;
    case 18:
      return (void (__noreturn *)())fileio_rpc_chdir;
    case 19:
      return (void (__noreturn *)())fileio_rpc_sync;
    case 20:
      return (void (__noreturn *)())fileio_rpc_mount;
    case 21:
      return (void (__noreturn *)())fileio_rpc_umount;
    case 23:
      return (void (__noreturn *)())fileio_rpc_devctl;
    case 24:
      return (void (__noreturn *)())fileio_rpc_symlink;
    case 25:
      return (void (__noreturn *)())fileio_rpc_readlink;
    case 26:
      return (void (__noreturn *)())fileio_rpc_ioctl2;
    case 28:
      return (void (__noreturn *)())fileio_rpc_devctl_blkio;
    default:
      printf("sce_fileio: unrecognized code %x\n", cmd);
      return 0;
  }
}

//----- (00401E68) --------------------------------------------------------
static int *__fastcall fileio_rpc_service_handler(int fno, void *buffer, int length)
{
  int i;
  int thids_per_fd_idx; // $s5
  struct fio_msgbox_inbuf *threadbuf; // $s3
  int param_for_mbx; // $s0
  iop_thread_t thparam; // [sp+18h] [-70h] BYREF
  iop_mbx_t mbxparam; // [sp+30h] [-58h] BYREF
  iop_thread_info_t thstatus; // [sp+38h] [-50h] BYREF
  int state; // [sp+80h] [-8h] BYREF

  g_fileio_rpc_outbuf = 1;
  if ( fno == 255 )
  {
    if ( length == 8 )
    {
      g_result_destbuf_ee[0] = *(void **)buffer;
      g_result_destbuf_ee[1] = *((void **)buffer + 1);
    }
    else
    {
      g_result_destbuf_ee[1] = *(void **)buffer;
      g_result_destbuf_ee[0] = g_result_destbuf_ee[1];
    }
    g_fileio_rpc_outbuf_verres = 2;
    g_fileio_rpc_outbuf = g_verstr;
    return &g_fileio_rpc_outbuf;
  }
  if ( fno == 254 )
  {
    int rwbuf_retres; // $s1

    CpuSuspendIntr(&state);
    rwbuf_retres = 0;
    if ( g_rwbuf_uses )
    {
      rwbuf_retres = -16;
    }
    else
    {
      fileio_rpc_dealloc_rwbuf();
      g_rwbuf_max_size = *(_DWORD *)buffer;
      g_rwbuf_ptr_count_allowed = *((_DWORD *)buffer + 1);
    }
    g_fileio_rpc_outbuf = rwbuf_retres;
    CpuResumeIntr(state);
    return &g_fileio_rpc_outbuf;
  }
  if ( fno == 253 )
  {
    int priority_retres; // $s1

    priority_retres = 0;
    if ( (unsigned int)(*(_DWORD *)buffer - 9) >= 0x73 )
    {
      priority_retres = -22;
    }
    else
    {
      g_th_priority = *(_DWORD *)buffer;
      ChangeThreadPriority(0, g_th_priority);
    }
    g_fileio_rpc_outbuf = priority_retres;
    return &g_fileio_rpc_outbuf;
  }
  thids_per_fd_idx = -1;
  for ( i = 0; i < 32; i += 1 )
  {
    if ( g_thids_per_fd[i] == -1 )
    {
      thids_per_fd_idx = i;
    }
    else
    {
      ReferThreadStatus(g_thids_per_fd[i], &thstatus);
      if ( thstatus.status == 16 )
      {
        thids_per_fd_idx = i;
        DeleteThread(g_thids_per_fd[i]);
        g_thids_per_fd[i] = -1;
      }
    }
  }
  if ( thids_per_fd_idx == -1 )
  {
    printf("fileio: Thread alloc fail\n");
    g_fileio_rpc_outbuf = 0;
    return &g_fileio_rpc_outbuf;
  }
  threadbuf = (struct fio_msgbox_inbuf *)fileio_rpc_threadbuf_alloc();
  if ( !threadbuf )
  {
    g_fileio_rpc_outbuf = 0;
    return &g_fileio_rpc_outbuf;
  }
  if ( (unsigned int)fno < 5 && fno != 22 )
  {
    if ( !fno )
    {
      int ee_fds; // $s0

      memcpy(threadbuf->m_taskbuf, buffer, length);
      mbxparam.attr = 0;
      mbxparam.option = 255;
      threadbuf->m_mbxid = CreateMbx(&mbxparam);
      if ( threadbuf->m_mbxid < 0 )
      {
        fileio_rpc_threadbuf_free(threadbuf);
        g_fileio_rpc_outbuf = 0;
        return &g_fileio_rpc_outbuf;
      }
      ee_fds = *((_DWORD *)buffer + 261);
      if ( g_fileio_verbose > 0 )
        printf("SCE_OPEN: ee_fds= %d mbxid= %08x\n", (int)ee_fds, threadbuf->m_mbxid);
      g_mbxid_for_ee_fds[ee_fds] = threadbuf->m_mbxid;
      threadbuf->m_common.m_in_fno = 0;
    }
    else
    {
      memcpy(threadbuf, buffer, length);
    }
    thparam.attr = 0x2000000;
    thparam.thread = (void (__cdecl *)(void *))get_fileio_rpc_command_thfn(fno);
    thparam.stacksize = 6144;
    thparam.option = 0;
    thparam.priority = g_th_priority;
    if ( thparam.thread )
    {
      int thid; // $s1

      thid = CreateThread(&thparam);
      if ( thid >= 0 )
      {
        g_thids_per_fd[thids_per_fd_idx] = thid;
        if ( StartThread(thid, threadbuf) >= 0 )
          return &g_fileio_rpc_outbuf;
      }
    }
    fileio_rpc_threadbuf_free(threadbuf);
    g_fileio_rpc_outbuf = 0;
    return &g_fileio_rpc_outbuf;
  }
  memcpy(threadbuf->m_taskbuf, buffer, length);
  switch ( fno )
  {
    case 1:
      param_for_mbx = *((_DWORD *)buffer + 4);
      break;
    case 2:
    case 22:
    default:
      param_for_mbx = *((_DWORD *)buffer + 7);
      break;
    case 3:
      param_for_mbx = *((_DWORD *)buffer + 11);
      break;
    case 4:
      param_for_mbx = *((_DWORD *)buffer + 6);
      break;
  }
  *(u8 *)&(threadbuf->m_common.m_taskdata2) = 0;
  threadbuf->m_common.m_in_fno = fno;
  threadbuf->m_mbxid = g_mbxid_for_ee_fds[param_for_mbx];
  g_thids_per_fd[thids_per_fd_idx] = -1;
  if ( g_fileio_verbose > 0 )
    printf("SendMbx ee_fds= %d mbxid= %08x fno= %d addr= %08x\n", param_for_mbx, threadbuf->m_mbxid, fno, (unsigned int)threadbuf);
  if ( !SendMbx(threadbuf->m_mbxid, threadbuf) )
    return &g_fileio_rpc_outbuf;
  fileio_rpc_threadbuf_free(threadbuf);
  g_fileio_rpc_outbuf = 0;
  return &g_fileio_rpc_outbuf;
}
// 402168: conditional instruction was optimized away because $s4.4==16
// 40323C: using guessed type int g_verstr;
// 403240: using guessed type int g_fileio_verbose;
// 403244: using guessed type int g_rwbuf_max_size;
// 403248: using guessed type int g_th_priority;
// 403250: using guessed type int g_rwbuf_ptr_count_allowed;
// 403254: using guessed type int g_rwbuf_uses;
// 403330: using guessed type int g_fileio_rpc_outbuf;
// 403334: using guessed type int g_fileio_rpc_outbuf_verres;

//----- (00402298) --------------------------------------------------------
static void __noreturn power_off_event_handler()
{
  int trid; // $s0
  char pkt[16]; // [sp+18h] [-18h] BYREF
  int ef; // [sp+28h] [-8h] BYREF
  u32 efres; // [sp+2Ch] [-4h] BYREF

  while ( iomanX_devctl("cdrom0:", 0x4391, 0, 0, &ef, 4u) < 0 )
  {
    if ( g_fileio_verbose > 0 )
      printf("FILEIO:PowerOff event flag get fail\n");
    DelayThread(128000);
  }
  while ( 1 )
  {
    ClearEventFlag(ef, 0xFFFFFFEF);
    WaitEventFlag(ef, 0x10u, 0, &efres);
    while ( 1 )
    {
      trid = sceSifSendCmd(0x80000013, pkt, 16, 0, 0, 0);
      if ( trid )
        break;
      DelayThread(2000);
    }
    while ( sceSifDmaStat(trid) >= 0 );
  }
}
// 403240: using guessed type int g_fileio_verbose;
// 402298: using guessed type char pkt[16];

//----- (00402384) --------------------------------------------------------
static void fileio_rpc_start_thread(void *userdata)
{
  iop_event_t efparam; // [sp+20h] [-80h] BYREF
  iop_sema_t semaparam; // [sp+30h] [-70h] BYREF
  iop_thread_t thparam; // [sp+40h] [-60h] BYREF
  iop_thread_info_t thinfo; // [sp+58h] [-48h] BYREF

  (void)userdata;
  if ( !sceSifCheckInit() )
    sceSifInit();
  printf("Multi Threaded Fileio module.(99/11/15) \n");
  sceSifInitRpc(0);
  efparam.attr = 2;
  efparam.bits = 0;
  efparam.option = 0;
  g_rwbuf_ef = CreateEventFlag(&efparam);
  SetEventFlag(g_rwbuf_ef, 1u);
  semaparam.attr = 1;
  semaparam.initial = 1;
  semaparam.max = 1;
  semaparam.option = 0;
  g_sema_for_result_destbuf_ee = CreateSema(&semaparam);
  ReferThreadStatus(0, &thinfo);
  thparam.attr = 0x2000000;
  thparam.thread = (void (__cdecl *)(void *))power_off_event_handler;
  thparam.stacksize = 2048;
  thparam.option = 0;
  thparam.priority = thinfo.initPriority;
  StartThread(CreateThread(&thparam), 0);
  sceSifSetRpcQueue(&g_fileio_sif_qd, GetThreadId());
  sceSifRegisterRpc(
    &g_fileio_sif_sd,
    0x80000001,
    (SifRpcFunc_t)fileio_rpc_service_handler,
    fileio_rpc_service_in_buf,
    0,
    0,
    &g_fileio_sif_qd);
  sceSifRpcLoop(&g_fileio_sif_qd);
}
// 403340: using guessed type SifRpcDataQueue_t g_fileio_sif_qd;
// 4033A0: using guessed type int fileio_rpc_service_in_buf[784];

//----- (004024C0) --------------------------------------------------------
static void __fastcall heap_rpc_load_iop_heap(int buffer, int length, int *outbuf)
{
  int fd; // $s2

  (void)length;
  fd = iomanX_open((const char *)(buffer + 4), 1);
  if ( fd >= 0 )
  {
    int endsz; // $s0

    endsz = iomanX_lseek(fd, 0, 2);
    iomanX_lseek(fd, 0, 0);
    *outbuf = ( endsz != iomanX_read(fd, *(void **)buffer, endsz) ) ? -2 : 0;
    iomanX_close(fd);
  }
  else
  {
    printf("load heap :error \n");
    *outbuf = -1;
  }
}

//----- (00402578) --------------------------------------------------------
static void __fastcall heap_rpc_alloc_iop_heap(const int *buffer, int length, void **outbuf)
{
  void *ptr; // $s0
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  ptr = AllocSysMemory(0, *buffer, 0);
  CpuResumeIntr(state);
  *outbuf = ptr;
}

//----- (004025CC) --------------------------------------------------------
static void __fastcall heap_rpc_alloc_iop_heap_ex(int buffer, int length, void **outbuf)
{
  void *ptr; // $s0
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  ptr = AllocSysMemory(*(_DWORD *)(buffer + 4), *(_DWORD *)buffer, *(void **)(buffer + 8));
  CpuResumeIntr(state);
  *outbuf = ptr;
}

//----- (00402624) --------------------------------------------------------
static void __fastcall heap_rpc_free_iop_heap(void **buffer, int length, int *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  *outbuf = FreeSysMemory(*buffer);
  CpuResumeIntr(state);
}

//----- (00402674) --------------------------------------------------------
static void __fastcall heap_rpc_query_mem_size(int buffer, int length, u32 *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)buffer;
  (void)length;
  CpuSuspendIntr(&state);
  *outbuf = QueryMemSize();
  CpuResumeIntr(state);
}

//----- (004026B4) --------------------------------------------------------
static void __fastcall heap_rpc_query_max_free_mem_size(int buffer, int length, u32 *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)buffer;
  (void)length;
  CpuSuspendIntr(&state);
  *outbuf = QueryMaxFreeMemSize();
  CpuResumeIntr(state);
}

//----- (004026F4) --------------------------------------------------------
static void __fastcall heap_rpc_query_total_free_mem_size(int buffer, int length, u32 *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)buffer;
  (void)length;
  CpuSuspendIntr(&state);
  *outbuf = QueryTotalFreeMemSize();
  CpuResumeIntr(state);
}

//----- (00402734) --------------------------------------------------------
static void __fastcall heap_rpc_query_block_top_address(void **buffer, int length, void **outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  *outbuf = QueryBlockTopAddress(*buffer);
  CpuResumeIntr(state);
}

//----- (00402784) --------------------------------------------------------
static void __fastcall heap_rpc_query_block_size(void **buffer, int length, int *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  *outbuf = QueryBlockSize(*buffer);
  CpuResumeIntr(state);
}

//----- (004027D4) --------------------------------------------------------
static int *__fastcall heap_rpc_service_handler(int fno, void *buffer, int length)
{
  switch ( fno )
  {
    case 1:
      heap_rpc_alloc_iop_heap((int *)buffer, length, (void **)heap_rpc_outbuf);
      break;
    case 2:
      heap_rpc_free_iop_heap((void **)buffer, length, (int *)heap_rpc_outbuf);
      break;
    case 3:
      heap_rpc_load_iop_heap((int)buffer, length, heap_rpc_outbuf);
      break;
    case 4:
      heap_rpc_alloc_iop_heap_ex((int)buffer, length, (void **)heap_rpc_outbuf);
      break;
    case 5:
      heap_rpc_query_mem_size((int)buffer, length, (u32 *)heap_rpc_outbuf);
      break;
    case 6:
      heap_rpc_query_max_free_mem_size((int)buffer, length, (u32 *)heap_rpc_outbuf);
      break;
    case 7:
      heap_rpc_query_total_free_mem_size((int)buffer, length, (u32 *)heap_rpc_outbuf);
      break;
    case 8:
      heap_rpc_query_block_top_address((void **)buffer, length, (void **)heap_rpc_outbuf);
      break;
    case 9:
      heap_rpc_query_block_size((void **)buffer, length, heap_rpc_outbuf);
      break;
    default:
      printf("sce_iopmem: unrecognized code %x\n", fno);
      break;
  }
  return heap_rpc_outbuf;
}
// 403FE0: using guessed type int heap_rpc_outbuf[4];

//----- (0040290C) --------------------------------------------------------
static void heap_rpc_start_thread(void *userdata)
{
  (void)userdata;
  if ( !sceSifCheckInit() )
    sceSifInit();
  printf("iop heap service (99/11/03)\n");
  sceSifInitRpc(0);
  sceSifSetRpcQueue(&g_heap_sif_qd, GetThreadId());
  sceSifRegisterRpc(
    &g_heap_sif_sd,
    0x80000003,
    (SifRpcFunc_t)heap_rpc_service_handler,
    heap_rpc_service_in_buf,
    0,
    0,
    &g_heap_sif_qd);
  sceSifRpcLoop(&g_heap_sif_qd);
}
// 403FF0: using guessed type SifRpcDataQueue_t g_heap_sif_qd;
// 404050: using guessed type int heap_rpc_service_in_buf[64];

#ifdef UNUSED_FUNC
//----- (004029B0) --------------------------------------------------------
static void __fastcall iopinfo_rpc_querybootmode(int buffer, int length, int *outbuf)
{
  int *BootMode; // $v0

  (void)buffer;
  (void)length;
  BootMode = QueryBootMode(6);
  *outbuf = BootMode ? (*(_WORD *)BootMode & 0xFFFC) : 2048;
}

//----- (004029F8) --------------------------------------------------------
static int *__fastcall iopinfo_rpc_service_handler(int fno, void *buffer, int length)
{
  if ( fno == 1 )
    iopinfo_rpc_querybootmode((int)buffer, length, iopinfo_rpc_outbuf);
  else
    printf("sce_iopinfo: unrecognized code %x\n", fno);
  return iopinfo_rpc_outbuf;
}
// 404150: using guessed type int iopinfo_rpc_outbuf[4];

//----- (00402A50) --------------------------------------------------------
static int iopinfo_rpc_service_start_thread_unused()
{
  if ( !sceSifCheckInit() )
    sceSifInit();
  printf("iop infomation service (00/02/29)\n");
  sceSifInitRpc(0);
  sceSifSetRpcQueue(&g_iopinfo_sif_qd, GetThreadId());
  sceSifRegisterRpc(
    &g_iopinfo_sif_sd,
    0x80000007,
    (SifRpcFunc_t)iopinfo_rpc_service_handler,
    iopinfo_rpc_service_in_buf,
    0,
    0,
    &g_iopinfo_sif_qd);
  sceSifRpcLoop(&g_iopinfo_sif_qd);
  return 0;
}
// 404160: using guessed type int iopinfo_rpc_service_in_buf[16];
// 4041A0: using guessed type SifRpcDataQueue_t g_iopinfo_sif_qd;
#endif
