
#include <irx_imports.h>
#include <blkio-ioctl.h>
#include <errno.h>

IRX_ID("FILEIO_service", 2, 18);

#define __fastcall
#define __cdecl
#define __noreturn

#define _BYTE u8
#define _WORD u16
#define _DWORD u32

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
  char m_taskbuf[3120];
};

/* 182 */
struct fio_fd_open_inbuf
{
  struct fio_common_inbuf m_common;
  int m_flags;
  int m_mode;
  char m_name[1024];
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
  int m_inoutbufsz;
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
  int m_inoutbufsz;
};

/* 190 */
struct fio_remove_inbuf
{
  struct fio_common_inbuf m_common;
  char m_name[1024];
};

/* 191 */
struct fio_mkdir_inbuf
{
  struct fio_common_inbuf m_common;
  int m_mode;
  char m_name[1024];
};

/* 192 */
struct fio_rmdir_inbuf
{
  struct fio_common_inbuf m_common;
  char m_name[1024];
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
  char m_name[1024];
};

/* 196 */
struct fio_dopen_inbuf
{
  struct fio_common_inbuf m_common;
  char m_name[1024];
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
  char m_name[1024];
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

enum fio_fno
{
  FILEIO_FNO_OPEN,
  FILEIO_FNO_CLOSE,
  FILEIO_FNO_READ,
  FILEIO_FNO_WRITE,
  FILEIO_FNO_LSEEK,
  FILEIO_FNO_IOCTL,
  FILEIO_FNO_REMOVE,
  FILEIO_FNO_MKDIR,
  FILEIO_FNO_RMDIR,
  FILEIO_FNO_DOPEN,
  FILEIO_FNO_DCLOSE,
  FILEIO_FNO_DREAD,
  FILEIO_FNO_GETSTAT,
  FILEIO_FNO_CHSTAT,
  FILEIO_FNO_FORMAT,
  FILEIO_FNO_ADDDRV,
  FILEIO_FNO_DELDRV,
  FILEIO_FNO_RENAME,
  FILEIO_FNO_CHDIR,
  FILEIO_FNO_SYNC,
  FILEIO_FNO_MOUNT,
  FILEIO_FNO_UMOUNT,
  FILEIO_FNO_LSEEK64,
  FILEIO_FNO_DEVCTL,
  FILEIO_FNO_SYMLINK,
  FILEIO_FNO_READLINK,
  FILEIO_FNO_IOCTL2,
  FILEIO_FNO_DEVCTL_BLKIO = 28,
  FILEIO_FNO_SET_RPC_THREAD_PRIORITY = 253,
  FILEIO_FNO_SET_RWBUF_PARAM = 254,
  FILEIO_FNO_GET_VERSION_SET_EE_BUFFER = 255,
};

//-------------------------------------------------------------------------
// Function declarations

int _start();
static void *__fastcall fileio_alloc_rwbuf(int *out_rwbuf_size);
static void __fastcall fileio_free_rwbuf(void *ptr);
static void fileio_rpc_dealloc_rwbuf();
static struct fio_msgbox_inbuf *fileio_rpc_threadbuf_alloc(void);
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
static void *get_fileio_rpc_command_thfn(int cmd);
static int *__fastcall fileio_rpc_service_handler(int fno, void *buffer, int length);
static void __noreturn power_off_event_handler(void *userdata);
static void fileio_rpc_start_thread(void *userdata);
static void __fastcall heap_rpc_load_iop_heap(void *buffer, int length, void *outbuf);
static void __fastcall heap_rpc_alloc_iop_heap(void *buffer, int length, void *outbuf);
static void __fastcall heap_rpc_alloc_iop_heap_ex(void *buffer, int length, void *outbuf);
static void __fastcall heap_rpc_free_iop_heap(void *buffer, int length, void *outbuf);
static void __fastcall heap_rpc_query_mem_size(void *buffer, int length, void *outbuf);
static void __fastcall heap_rpc_query_max_free_mem_size(void *buffer, int length, void *outbuf);
static void __fastcall heap_rpc_query_total_free_mem_size(void *buffer, int length, void *outbuf);
static void __fastcall heap_rpc_query_block_top_address(void *buffer, int length, void *outbuf);
static void __fastcall heap_rpc_query_block_size(void *buffer, int length, void *outbuf);
static int *__fastcall heap_rpc_service_handler(int fno, void *buffer, int length);
static void heap_rpc_start_thread(void *userdata);
#ifdef UNUSED_FUNC
static void __fastcall iopinfo_rpc_querybootmode(void *buffer, int length, void *outbuf);
static int *__fastcall iopinfo_rpc_service_handler(int fno, void *buffer, int length);
static int iopinfo_rpc_service_start_thread_unused();
#endif

//-------------------------------------------------------------------------
// Data declarations

static const int g_verstr = 0x30303133; // weak
static int g_fileio_verbose = 0; // weak
// Unofficial: move to bss
static int g_rwbuf_max_size; // weak
// Unofficial: move to bss
static int g_th_priority; // weak
static int g_result_destbuf_ee_idx = 0; // weak
// Unofficial: move to bss
static unsigned int g_rwbuf_ptr_count_allowed; // weak
static unsigned int g_rwbuf_uses = 0; // weak
static void *g_rwbuf_cur_ptr = NULL; // idb
static int g_rwbuf_size = 0; // weak
static int g_rwbuf_is_allocated = 0; // weak
// Unofficial: move to bss
static int g_thids_per_fd[32];
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
  int i;
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
  g_rwbuf_max_size = 16384;
  g_th_priority = 96;
  g_rwbuf_ptr_count_allowed = 4;
  for ( i = 0; i < (int)(sizeof(g_thids_per_fd)/sizeof(g_thids_per_fd[0])); i += 1 )
    g_thids_per_fd[i] = -1;
  CpuEnableIntr();
  thparam.thread = fileio_rpc_start_thread;
  thparam.attr = TH_C;
  thparam.priority = 96;
  thparam.stacksize = 4096;
  thparam.option = 0;
  thid_fio = CreateThread(&thparam);
  if ( thid_fio <= 0 )
    return 1;
  StartThread(thid_fio, 0);
  thparam.thread = heap_rpc_start_thread;
  thparam.attr = TH_C;
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

  WaitEventFlag(g_rwbuf_ef, 1u, WEF_AND | WEF_CLEAR, &efbits);
  CpuSuspendIntr(&state);
  
  rwbuf_cur_ptr = g_rwbuf_cur_ptr;
  rwbuf_size = g_rwbuf_size;
  if ( rwbuf_cur_ptr && rwbuf_size && !g_rwbuf_is_allocated )
  {
    g_rwbuf_is_allocated = 1;
    g_rwbuf_uses += 1;
  }
  else
  {
    int try_cnt; // $s1

    *out_rwbuf_size = 0;
    for ( try_cnt = 0; try_cnt < 8; try_cnt += 1 )
    {
      rwbuf_size = g_rwbuf_max_size >> try_cnt;
      rwbuf_cur_ptr = AllocSysMemory(1, rwbuf_size, 0);
      if ( rwbuf_cur_ptr )
      {
        unsigned int cur_ptr_count; // $v1
        g_rwbuf_uses += 1;
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
    g_rwbuf_uses -= 1;
    SetEventFlag(g_rwbuf_ef, 1u);
  }
  else if ( !FreeSysMemory(ptr) )
  {
    unsigned int cur_ptr_count; // $a0

    g_rwbuf_uses -= 1;
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
static struct fio_msgbox_inbuf *fileio_rpc_threadbuf_alloc(void)
{
  struct fio_msgbox_inbuf *ptr; // $s0
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  ptr = AllocSysMemory(ALLOC_LAST, sizeof(*ptr), 0);
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
    dmat = isceSifSendCmd(0x80000011, cmdbuf, sizeof(cmdbuf), ptr, g_result_destbuf_ee[g_result_destbuf_ee_idx], sz);
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
  memset(&fbuf, 0, sizeof(fbuf));
  fd = iomanX_open(inbuf->m_name, inbuf->m_flags, inbuf->m_mode);
  fbuf.m_common.m_out_fno = FILEIO_FNO_OPEN;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_retres = fd;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  return fd;
}
// 403240: using guessed type int g_fileio_verbose;

//----- (004006B4) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_close(struct fio_fd_close_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  if ( g_fileio_verbose > 0 )
    printf("close fd = %d\n", inbuf->m_fd);
  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_CLOSE;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_close(inbuf->m_fd);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
}
// 403240: using guessed type int g_fileio_verbose;

//----- (00400744) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_lseek(struct fio_fd_lseek_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_LSEEK;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_lseek(inbuf->m_fd, inbuf->m_pos, inbuf->m_mode);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
}

//----- (004007B8) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_read(struct fio_fd_read_inbuf *inbuf)
{
  int read_res_last; // $s2
  void *rwbuf; // $fp
  int read_sz_end; // $s4
  int read_sz_begin; // $s7
  int read_sz_total; // $s6
  struct fio_read_outbuf fbuf; // [sp+20h] [-C8h] BYREF
  int rwbuf_size; // [sp+C8h] [-20h] BYREF
  int state; // [sp+CCh] [-1Ch] BYREF
  int eedestptr1; // [sp+D4h] [-14h]
  int eedestptr2; // [sp+D8h] [-10h]

  memset(&fbuf, 0, sizeof(fbuf));
  read_res_last = 0;
  read_sz_end = 0;
  read_sz_begin = 0;
  read_sz_total = 0;
  eedestptr2 = 0;
  eedestptr1 = 0;
  rwbuf = fileio_alloc_rwbuf(&rwbuf_size);
  if ( !rwbuf )
  {
    read_res_last = -ENOMEM;
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
    if ( m_eebuffersz >= (int)(sizeof(fbuf.m_buf2)) )
    {
      read_sz_begin = ( (m_eebuffer & (sizeof(fbuf.m_buf2) - 1)) != 0 ) ? ((m_eebuffer & ~(sizeof(fbuf.m_buf2) - 1)) - (m_eebuffer - (sizeof(fbuf.m_buf2)))) : 0;
      eedest = (char *)(m_eebuffer + read_sz_begin);
      cur_read_remain = ((m_eebuffer + m_eebuffersz) & ~(sizeof(fbuf.m_buf2) - 1)) - (m_eebuffer + read_sz_begin);
      read_sz_end = m_eebuffer + m_eebuffersz - ((m_eebuffer + m_eebuffersz) & ~(sizeof(fbuf.m_buf2) - 1));
      eedestptr2 = (m_eebuffer + m_eebuffersz) & ~(sizeof(fbuf.m_buf2) - 1);
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
    while ( cur_read_remain > 0 )
    {
      int cur_rwbuf_sz; // $s1
      int read_res_main; // $v0
      SifDmaTransfer_t dmat[1]; // [sp+10h] [-D8h] BYREF

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

          read_res_main_rounded = read_res_main & ~(sizeof(fbuf.m_buf2) - 1);
          read_sz_end = read_res_main - read_res_main_rounded;
          eedestptr2 = (int)&eedest[read_res_main_rounded];
          for ( outbuf_ind = 0; outbuf_ind < read_sz_end; outbuf_ind += 1 )
            fbuf.m_buf2[outbuf_ind] = ((_BYTE *)rwbuf)[read_res_main_rounded + outbuf_ind];
          if ( read_res_main_rounded )
          {
            dmat[0].src = rwbuf;
            dmat[0].dest = eedest;
            dmat[0].size = read_res_main_rounded;
            dmat[0].attr = 0;
            while ( 1 )
            {
              CpuSuspendIntr(&state);
              trid = sceSifSetDma(dmat, sizeof(dmat)/sizeof(dmat[0]));
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
      dmat[0].src = rwbuf;
      dmat[0].dest = eedest;
      dmat[0].size = read_res_main;
      dmat[0].attr = 0;
      while ( 1 )
      {
        CpuSuspendIntr(&state);
        trid = sceSifSetDma(dmat, sizeof(dmat)/sizeof(dmat[0]));
        CpuResumeIntr(state);
        if ( trid )
          break;
        DelayThread(2000);
      }
      read_sz_total += read_res_main;
      cur_read_remain -= read_res_main;
      eedest += read_res_main;
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
  fbuf.m_common.m_out_fno = FILEIO_FNO_READ;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = ( read_res_last < 0 && read_sz_total <= 0 ) ? read_res_last : read_sz_total;
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
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

  memset(&fbuf, 0, sizeof(fbuf));
  write_res_last = 0;
  write_sz_total = 0;
  rwbuf = fileio_alloc_rwbuf(&rwbuf_size);
  if ( !rwbuf )
  {
    Kprintf("Error:Cannot alloc r/w buffer\n");
    write_res_last = -ENOMEM;
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
    while ( rwbuf_remain_sz )
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
    }
  }
  fbuf.m_common.m_out_fno = FILEIO_FNO_WRITE;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = ( write_res_last >= 0 || write_sz_total > 0 ) ? write_sz_total : write_res_last;
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_free_rwbuf(rwbuf);
}
// 400B14: using guessed type SifRpcReceiveData_t rdata;

//----- (00400CCC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_devctl_blkio(struct fio_devctl_inbuf *inbuf)
{
  int devctl_res; // $s2
  struct fio_largebuf_outbuf fbuf; // [sp+20h] [-478h] BYREF
  sceFsDevctlBlkIO bio_arg; // [sp+440h] [-58h] BYREF
  SifDmaTransfer_t dmat[1]; // [sp+458h] [-40h] BYREF
  SifRpcReceiveData_t rdata; // [sp+468h] [-30h] BYREF
  int rwbuf_size; // [sp+488h] [-10h] BYREF
  int state; // [sp+48Ch] [-Ch] BYREF
  void *rwbuf; // [sp+490h] [-8h]

  memset(&fbuf, 0, sizeof(fbuf));
  // The following is intentional (not FILEIO_FNO_DEVCTL_BLKIO)
  fbuf.m_common.m_out_fno = FILEIO_FNO_DEVCTL;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  devctl_res = 0;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  bio_arg = *(sceFsDevctlBlkIO *)(inbuf->m_arg);
  if ( g_fileio_verbose > 0 )
    Kprintf(
      "FsBlkIO LBN:%d NBLK:%d addr:%x BLKSIZE:%d TYPE:%d mode:%x\n",
      bio_arg.lbn,
      bio_arg.nblk,
      (u32)bio_arg.addr,
      bio_arg.blksiz,
      bio_arg.type,
      bio_arg.mode);
  rwbuf = fileio_alloc_rwbuf(&rwbuf_size);
  if ( !rwbuf )
  {
    devctl_res = -ENOMEM;
    Kprintf("Error:Cannot alloc r/w buffer\n");
  }
  else
  {
    unsigned int rwbuf_size_in_blocks; // $s6
    unsigned int size_in_rwbuf_block_units; // $s5
    unsigned int size_in_rwbuf_remainder_block_units; // $fp
    unsigned int cur_block_unit; // $s1

    rwbuf_size_in_blocks = (unsigned int)rwbuf_size / bio_arg.blksiz;
    size_in_rwbuf_block_units = bio_arg.nblk / rwbuf_size_in_blocks;
    size_in_rwbuf_remainder_block_units = bio_arg.nblk % rwbuf_size_in_blocks;
    if ( size_in_rwbuf_remainder_block_units )
      size_in_rwbuf_block_units += 1;
    else
      size_in_rwbuf_remainder_block_units = rwbuf_size_in_blocks;
    dmat[0].attr = 0;
    dmat[0].src = rwbuf;
    dmat[0].dest = (void *)bio_arg.addr;
    bio_arg.addr = rwbuf;
    for ( cur_block_unit = 0; cur_block_unit < size_in_rwbuf_block_units; cur_block_unit += 1 )
    {
      bio_arg.nblk = ( cur_block_unit + 1 == size_in_rwbuf_block_units ) ? size_in_rwbuf_remainder_block_units : rwbuf_size_in_blocks;
      dmat[0].size = bio_arg.nblk * bio_arg.blksiz;
      switch ( bio_arg.type )
      {
      case sceFsREADING:
        {
          int trid; // $s0

          devctl_res = devctl(inbuf->m_name, inbuf->m_cmd, &bio_arg, inbuf->m_arglen, 0, 0);
          if ( devctl_res < 0 )
            break;
          while ( 1 )
          {
            CpuSuspendIntr(&state);
            trid = sceSifSetDma(dmat, sizeof(dmat)/sizeof(dmat[0]));
            CpuResumeIntr(state);
            if ( trid )
              break;
            DelayThread(2000);
          }
          while ( sceSifDmaStat(trid) >= 0 );
          break;
        }
      case sceFsWRITING:
      default:
        {
          while ( sceSifGetOtherData(&rdata, dmat[0].dest, dmat[0].src, dmat[0].size, 0) < 0 )
            DelayThread(2000);
          devctl_res = devctl(inbuf->m_name, inbuf->m_cmd, &bio_arg, inbuf->m_arglen, 0, 0);
          break;
        }
      }
      if ( devctl_res < 0 )
        break;
      bio_arg.lbn += bio_arg.nblk;
      dmat[0].dest = (char *)dmat[0].dest + dmat[0].size;
    }
    fileio_free_rwbuf(rwbuf);
  }
  fbuf.m_retres = devctl_res;
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
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

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_IOCTL;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  fbuf.m_retres = iomanX_ioctl(inbuf->m_fd, inbuf->m_cmd, inbuf->m_inoutbufsz ? inbuf->m_buf : 0);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401094) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_ioctl2(struct fio_ioctl2_inbuf *inbuf)
{
  struct fio_largebuf_outbuf fbuf; // [sp+18h] [-420h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_IOCTL2;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  fbuf.m_retres = iomanX_ioctl2(inbuf->m_fd, inbuf->m_cmd, inbuf->m_inoutbufsz ? inbuf->m_buf : 0, inbuf->m_inoutbufsz, fbuf.m_buf, fbuf.m_inbufsz);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040116C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_remove(struct fio_remove_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_REMOVE;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_remove(inbuf->m_name);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004011E4) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_mkdir(struct fio_mkdir_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_MKDIR;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_mkdir(inbuf->m_name, inbuf->m_mode);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401264) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_rmdir(struct fio_rmdir_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_RMDIR;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_rmdir(inbuf->m_name);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004012DC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_format(struct fio_format_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_FORMAT;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_format(inbuf->m_dev, inbuf->m_blockdev, inbuf->m_arg, inbuf->m_arglen);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040135C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_adddrv(struct fio_adddrv_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_ADDDRV;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_AddDrv((iop_device_t *)inbuf->m_device);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004013DC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_deldrv(struct fio_deldrv_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_DELDRV;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_DelDrv(inbuf->m_name);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401454) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_dopen(struct fio_dopen_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_DOPEN;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_dopen(inbuf->m_name);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004014CC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_dclose(struct fio_dclose_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_DCLOSE;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_dclose(inbuf->m_fd);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040154C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_dread(struct fio_dread_inbuf *inbuf)
{
  struct fio_dirent_outbuf fbuf; // [sp+10h] [-160h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_DREAD;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_dread(inbuf->m_fd, &fbuf.m_dirent);
  fbuf.m_eedestptr = inbuf->m_eedestptr;
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004015C8) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_getstat(struct fio_getstat_inbuf *inbuf)
{
  struct fio_dirent_outbuf fbuf; // [sp+10h] [-160h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_GETSTAT;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_getstat(inbuf->m_name, &fbuf.m_dirent.stat);
  fbuf.m_eedestptr = inbuf->m_eedestptr;
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040163C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_chstat(struct fio_chstat_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_CHSTAT;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_chstat(inbuf->m_dirent.name, &inbuf->m_dirent.stat, inbuf->m_statmask);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004016BC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_rename(struct fio_rename_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_RENAME;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_rename(inbuf->m_oldname, inbuf->m_newname);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401734) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_chdir(struct fio_chdir_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_CHDIR;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_chdir(inbuf->m_name);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004017AC) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_sync(struct fio_sync_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_SYNC;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_sync(inbuf->m_dev, inbuf->m_flag);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (0040182C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_mount(struct fio_mount_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+18h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_MOUNT;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_mount(inbuf->m_fsname, inbuf->m_devname, inbuf->m_flag, inbuf->m_arg, inbuf->m_arglen);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (004018B8) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_umount(struct fio_umount_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_UMOUNT;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_umount(inbuf->m_fsname);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401930) --------------------------------------------------------
static void __fastcall fileio_rpc_fd_lseek64(struct fio_fd_lseek64_inbuf *inbuf)
{
  struct fio_smallbuf64_outbuf fbuf; // [sp+18h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_LSEEK64;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_lseek64(inbuf->m_fd, inbuf->m_pos, inbuf->m_mode);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
}

//----- (004019A8) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_devctl(struct fio_devctl_inbuf *inbuf)
{
  struct fio_largebuf_outbuf fbuf; // [sp+18h] [-420h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_DEVCTL;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  fbuf.m_retres = iomanX_devctl(inbuf->m_name, inbuf->m_cmd, inbuf->m_arglen ? inbuf->m_arg : 0, inbuf->m_arglen, fbuf.m_buf, fbuf.m_inbufsz);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401A7C) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_symlink(struct fio_symlink_inbuf *inbuf)
{
  struct fio_smallbuf_outbuf fbuf; // [sp+10h] [-20h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_SYMLINK;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_retres = iomanX_symlink(inbuf->m_oldname, inbuf->m_newname);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401AF4) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_readlink(struct fio_readlink_inbuf *inbuf)
{
  struct fio_largebuf_outbuf fbuf; // [sp+10h] [-420h] BYREF

  memset(&fbuf, 0, sizeof(fbuf));
  fbuf.m_common.m_out_fno = FILEIO_FNO_READLINK;
  fbuf.m_common.m_taskdata1 = inbuf->m_common.m_taskdata1;
  fbuf.m_common.m_taskdata2 = inbuf->m_common.m_taskdata2;
  fbuf.m_common.m_in_fno = inbuf->m_common.m_in_fno;
  fbuf.m_outbufsz = inbuf->m_outbufsz;
  fbuf.m_inbufsz = inbuf->m_inbufsz;
  fbuf.m_retres = iomanX_readlink(inbuf->m_path, fbuf.m_buf, fbuf.m_inbufsz);
  do_call_ee_rcv_res_intr(&fbuf, sizeof(fbuf));
  fileio_rpc_threadbuf_free(inbuf);
  ExitThread();
}

//----- (00401B78) --------------------------------------------------------
static void __fastcall __noreturn fileio_rpc_open(struct fio_msgbox_inbuf *inbuf)
{
  int m_mbxid; // $s1
  int fd; // $v0
  struct fio_msgbox_inbuf *threadbuf; // $s0

  m_mbxid = inbuf->m_mbxid;
  fd = fileio_rpc_fd_open((struct fio_fd_open_inbuf *)inbuf->m_taskbuf);
  fileio_rpc_threadbuf_free(inbuf);
  threadbuf = NULL;
  if ( fd >= 0 )
  {
    while ( 1 )
    {
      if ( threadbuf )
        fileio_rpc_threadbuf_free(threadbuf);
      ReceiveMbx((void **)&threadbuf, m_mbxid);
      if ( g_fileio_verbose > 0 )
        printf("ReceiveMbx mbxid= %08x fno= %d addr %08x\n", m_mbxid, threadbuf->m_common.m_in_fno, (unsigned int)threadbuf);
      switch ( threadbuf->m_common.m_in_fno )
      {
        case FILEIO_FNO_CLOSE:
          fileio_rpc_fd_close((struct fio_fd_close_inbuf *)threadbuf->m_taskbuf);
          fileio_rpc_threadbuf_free(threadbuf);
          break;
        case FILEIO_FNO_READ:
          fileio_rpc_fd_read((struct fio_fd_read_inbuf *)threadbuf->m_taskbuf);
          continue;
        case FILEIO_FNO_WRITE:
          fileio_rpc_fd_write((struct fio_fd_write_inbuf *)threadbuf->m_taskbuf);
          continue;
        case FILEIO_FNO_LSEEK:
          fileio_rpc_fd_lseek((struct fio_fd_lseek_inbuf *)threadbuf->m_taskbuf);
          continue;
        case FILEIO_FNO_LSEEK64:
          fileio_rpc_fd_lseek64((struct fio_fd_lseek64_inbuf *)threadbuf->m_taskbuf);
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
static void *get_fileio_rpc_command_thfn(int cmd)
{
  switch ( cmd )
  {
    case FILEIO_FNO_OPEN:
      return fileio_rpc_open;
    case FILEIO_FNO_IOCTL:
      return fileio_rpc_ioctl;
    case FILEIO_FNO_REMOVE:
      return fileio_rpc_remove;
    case FILEIO_FNO_MKDIR:
      return fileio_rpc_mkdir;
    case FILEIO_FNO_RMDIR:
      return fileio_rpc_rmdir;
    case FILEIO_FNO_DOPEN:
      return fileio_rpc_dopen;
    case FILEIO_FNO_DCLOSE:
      return fileio_rpc_dclose;
    case FILEIO_FNO_DREAD:
      return fileio_rpc_dread;
    case FILEIO_FNO_GETSTAT:
      return fileio_rpc_getstat;
    case FILEIO_FNO_CHSTAT:
      return fileio_rpc_chstat;
    case FILEIO_FNO_FORMAT:
      return fileio_rpc_format;
    case FILEIO_FNO_ADDDRV:
      return fileio_rpc_adddrv;
    case FILEIO_FNO_DELDRV:
      return fileio_rpc_deldrv;
    case FILEIO_FNO_RENAME:
      return fileio_rpc_rename;
    case FILEIO_FNO_CHDIR:
      return fileio_rpc_chdir;
    case FILEIO_FNO_SYNC:
      return fileio_rpc_sync;
    case FILEIO_FNO_MOUNT:
      return fileio_rpc_mount;
    case FILEIO_FNO_UMOUNT:
      return fileio_rpc_umount;
    case FILEIO_FNO_DEVCTL:
      return fileio_rpc_devctl;
    case FILEIO_FNO_SYMLINK:
      return fileio_rpc_symlink;
    case FILEIO_FNO_READLINK:
      return fileio_rpc_readlink;
    case FILEIO_FNO_IOCTL2:
      return fileio_rpc_ioctl2;
    case FILEIO_FNO_DEVCTL_BLKIO:
      return fileio_rpc_devctl_blkio;
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
  int state; // [sp+80h] [-8h] BYREF

  switch ( fno )
  {
  case FILEIO_FNO_SET_RPC_THREAD_PRIORITY:
    {
      int priority_retres; // $s1

      priority_retres = ( (unsigned int)(*(_DWORD *)buffer - 9) < 0x73 ) ? 0 : -EINVAL;
      if ( !priority_retres )
      {
        g_th_priority = *(_DWORD *)buffer;
        ChangeThreadPriority(TH_SELF, g_th_priority);
      }
      g_fileio_rpc_outbuf = priority_retres;
      return &g_fileio_rpc_outbuf;
    }
  case FILEIO_FNO_SET_RWBUF_PARAM:
    {
      int rwbuf_retres; // $s1

      CpuSuspendIntr(&state);
      rwbuf_retres = !g_rwbuf_uses ? 0 : -EBUSY;
      if ( !rwbuf_retres )
      {
        fileio_rpc_dealloc_rwbuf();
        g_rwbuf_max_size = *(_DWORD *)buffer;
        g_rwbuf_ptr_count_allowed = *((_DWORD *)buffer + 1);
      }
      g_fileio_rpc_outbuf = rwbuf_retres;
      CpuResumeIntr(state);
      return &g_fileio_rpc_outbuf;
    }
  case FILEIO_FNO_GET_VERSION_SET_EE_BUFFER:
    {
      g_result_destbuf_ee[0] = *(void **)buffer;
      g_result_destbuf_ee[1] = ( length == 8 ) ? *((void **)buffer + 1) : g_result_destbuf_ee[0];
      g_fileio_rpc_outbuf_verres = 2;
      g_fileio_rpc_outbuf = g_verstr;
      return &g_fileio_rpc_outbuf;
    }
  default:
    break;
  }
  thids_per_fd_idx = -1;
  for ( i = 0; i < (int)(sizeof(g_thids_per_fd)/sizeof(g_thids_per_fd[0])); i += 1 )
  {
    if ( g_thids_per_fd[i] != -1 )
    {
      iop_thread_info_t thstatus; // [sp+38h] [-50h] BYREF

      ReferThreadStatus(g_thids_per_fd[i], &thstatus);
      if ( thstatus.status == THS_DORMANT )
      {
        DeleteThread(g_thids_per_fd[i]);
        g_thids_per_fd[i] = -1;
      }
    }
    if ( g_thids_per_fd[i] == -1 )
      thids_per_fd_idx = i;
  }
  if ( thids_per_fd_idx == -1 )
  {
    printf("fileio: Thread alloc fail\n");
    g_fileio_rpc_outbuf = 0;
    return &g_fileio_rpc_outbuf;
  }
  threadbuf = fileio_rpc_threadbuf_alloc();
  if ( threadbuf )
  {
    int ee_fds; // $s0

    threadbuf->m_common.m_in_fno = fno;
    threadbuf->m_mbxid = -1;
    switch ( threadbuf->m_common.m_in_fno )
    {
    case FILEIO_FNO_OPEN:
      ee_fds = *((_DWORD *)buffer + 261);
      break;
    case FILEIO_FNO_CLOSE:
      ee_fds = *((_DWORD *)buffer + 4);
      break;
    case FILEIO_FNO_READ:
      ee_fds = *((_DWORD *)buffer + 7);
      break;
    case FILEIO_FNO_WRITE:
      ee_fds = *((_DWORD *)buffer + 11);
      break;
    case FILEIO_FNO_LSEEK:
      ee_fds = *((_DWORD *)buffer + 6);
      break;
    case FILEIO_FNO_LSEEK64:
      ee_fds = *((_DWORD *)buffer + 7);
      break;
    default:
      ee_fds = -1;
      break;
    }
    if ( ee_fds >= 0 )
    {
      memcpy(threadbuf->m_taskbuf, buffer, length);
      if ( fno == FILEIO_FNO_OPEN )
      {
        iop_mbx_t mbxparam; // [sp+30h] [-58h] BYREF

        mbxparam.attr = 0;
        mbxparam.option = 255;
        threadbuf->m_mbxid = CreateMbx(&mbxparam);
        if ( threadbuf->m_mbxid < 0 )
        {
          fileio_rpc_threadbuf_free(threadbuf);
          g_fileio_rpc_outbuf = 0;
          return &g_fileio_rpc_outbuf;
        }
        if ( g_fileio_verbose > 0 )
          printf("SCE_OPEN: ee_fds= %d mbxid= %08x\n", ee_fds, threadbuf->m_mbxid);
        g_mbxid_for_ee_fds[ee_fds] = threadbuf->m_mbxid;
      }
      else
      {
        *(u8 *)&(threadbuf->m_common.m_taskdata2) = 0;
        threadbuf->m_mbxid = g_mbxid_for_ee_fds[ee_fds];
        if ( g_fileio_verbose > 0 )
          printf("SendMbx ee_fds= %d mbxid= %08x fno= %d addr= %08x\n", ee_fds, threadbuf->m_mbxid, fno, (unsigned int)threadbuf);
        if ( !SendMbx(threadbuf->m_mbxid, threadbuf) )
        {
          g_fileio_rpc_outbuf = 1;
          return &g_fileio_rpc_outbuf;
        }
        fno = -1;
        threadbuf->m_mbxid = -1;
      }
    }
    else
    {
      memcpy(threadbuf, buffer, length);
    }
    if ( fno >= 0 )
    {
      iop_thread_t thparam; // [sp+18h] [-70h] BYREF

      thparam.attr = TH_C;
      thparam.thread = get_fileio_rpc_command_thfn(fno);
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
          {
            g_fileio_rpc_outbuf = 1;
            return &g_fileio_rpc_outbuf;
          }
          // Unofficial: cleanup here
          DeleteThread(thid);
        }
      }
    }
  }
  // Unofficial: cleanup here
  if ( thids_per_fd_idx >= 0 )
    g_thids_per_fd[thids_per_fd_idx] = -1;
  if ( threadbuf )
  {
    if ( threadbuf->m_mbxid >= 0 )
      DeleteMbx(threadbuf->m_mbxid);
    fileio_rpc_threadbuf_free(threadbuf);
  }
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
static void __noreturn power_off_event_handler(void *userdata)
{
  int trid; // $s0
  char pkt[16]; // [sp+18h] [-18h] BYREF
  int ef; // [sp+28h] [-8h] BYREF
  u32 efres; // [sp+2Ch] [-4h] BYREF

  (void)userdata;
  while ( iomanX_devctl("cdrom0:", 0x4391, 0, 0, &ef, sizeof(ef)) < 0 )
  {
    if ( g_fileio_verbose > 0 )
      printf("FILEIO:PowerOff event flag get fail\n");
    DelayThread(128000);
  }
  while ( 1 )
  {
    ClearEventFlag(ef, 0xFFFFFFEF);
    WaitEventFlag(ef, 0x10u, WEF_AND, &efres);
    while ( 1 )
    {
      trid = sceSifSendCmd(0x80000013, pkt, sizeof(pkt), 0, 0, 0);
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
  efparam.attr = EA_MULTI;
  efparam.bits = 0;
  efparam.option = 0;
  g_rwbuf_ef = CreateEventFlag(&efparam);
  SetEventFlag(g_rwbuf_ef, 1u);
  semaparam.attr = SA_THPRI;
  semaparam.initial = 1;
  semaparam.max = 1;
  semaparam.option = 0;
  g_sema_for_result_destbuf_ee = CreateSema(&semaparam);
  ReferThreadStatus(TH_SELF, &thinfo);
  thparam.attr = TH_C;
  thparam.thread = power_off_event_handler;
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
static void __fastcall heap_rpc_load_iop_heap(void *buffer, int length, void *outbuf)
{
  int fd; // $s2

  (void)length;
  fd = iomanX_open((const char *)((char *)buffer + 4), 1);
  if ( fd >= 0 )
  {
    int endsz; // $s0

    endsz = iomanX_lseek(fd, 0, FIO_SEEK_END);
    iomanX_lseek(fd, 0, FIO_SEEK_SET);
    *(int *)outbuf = ( endsz != iomanX_read(fd, *(void **)buffer, endsz) ) ? -2 : 0;
    iomanX_close(fd);
  }
  else
  {
    printf("load heap :error \n");
    *(int *)outbuf = -1;
  }
}

//----- (00402578) --------------------------------------------------------
static void __fastcall heap_rpc_alloc_iop_heap(void *buffer, int length, void *outbuf)
{
  void *ptr; // $s0
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  ptr = AllocSysMemory(ALLOC_FIRST, *(int *)buffer, 0);
  CpuResumeIntr(state);
  *(void **)outbuf = ptr;
}

//----- (004025CC) --------------------------------------------------------
static void __fastcall heap_rpc_alloc_iop_heap_ex(void *buffer, int length, void *outbuf)
{
  void *ptr; // $s0
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  ptr = AllocSysMemory(*(_DWORD *)((char *)buffer + 4), *(_DWORD *)buffer, *(void **)((char *)buffer + 8));
  CpuResumeIntr(state);
  *(void **)outbuf = ptr;
}

//----- (00402624) --------------------------------------------------------
static void __fastcall heap_rpc_free_iop_heap(void *buffer, int length, void *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  *(int *)outbuf = FreeSysMemory(*(void **)buffer);
  CpuResumeIntr(state);
}

//----- (00402674) --------------------------------------------------------
static void __fastcall heap_rpc_query_mem_size(void *buffer, int length, void *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)buffer;
  (void)length;
  CpuSuspendIntr(&state);
  *(u32 *)outbuf = QueryMemSize();
  CpuResumeIntr(state);
}

//----- (004026B4) --------------------------------------------------------
static void __fastcall heap_rpc_query_max_free_mem_size(void *buffer, int length, void *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)buffer;
  (void)length;
  CpuSuspendIntr(&state);
  *(u32 *)outbuf = QueryMaxFreeMemSize();
  CpuResumeIntr(state);
}

//----- (004026F4) --------------------------------------------------------
static void __fastcall heap_rpc_query_total_free_mem_size(void *buffer, int length, void *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)buffer;
  (void)length;
  CpuSuspendIntr(&state);
  *(u32 *)outbuf = QueryTotalFreeMemSize();
  CpuResumeIntr(state);
}

//----- (00402734) --------------------------------------------------------
static void __fastcall heap_rpc_query_block_top_address(void *buffer, int length, void *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  *(void **)outbuf = QueryBlockTopAddress(*(void **)buffer);
  CpuResumeIntr(state);
}

//----- (00402784) --------------------------------------------------------
static void __fastcall heap_rpc_query_block_size(void *buffer, int length, void *outbuf)
{
  int state; // [sp+10h] [-8h] BYREF

  (void)length;
  CpuSuspendIntr(&state);
  *(int *)outbuf = QueryBlockSize(*(void **)buffer);
  CpuResumeIntr(state);
}

//----- (004027D4) --------------------------------------------------------
static int *__fastcall heap_rpc_service_handler(int fno, void *buffer, int length)
{
  switch ( fno )
  {
    case 1:
      heap_rpc_alloc_iop_heap(buffer, length, heap_rpc_outbuf);
      break;
    case 2:
      heap_rpc_free_iop_heap(buffer, length, heap_rpc_outbuf);
      break;
    case 3:
      heap_rpc_load_iop_heap(buffer, length, heap_rpc_outbuf);
      break;
    case 4:
      heap_rpc_alloc_iop_heap_ex(buffer, length, heap_rpc_outbuf);
      break;
    case 5:
      heap_rpc_query_mem_size(buffer, length, heap_rpc_outbuf);
      break;
    case 6:
      heap_rpc_query_max_free_mem_size(buffer, length, heap_rpc_outbuf);
      break;
    case 7:
      heap_rpc_query_total_free_mem_size(buffer, length, heap_rpc_outbuf);
      break;
    case 8:
      heap_rpc_query_block_top_address(buffer, length, heap_rpc_outbuf);
      break;
    case 9:
      heap_rpc_query_block_size(buffer, length, heap_rpc_outbuf);
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
static void __fastcall iopinfo_rpc_querybootmode(void *buffer, int length, void *outbuf)
{
  int *BootMode; // $v0

  (void)buffer;
  (void)length;
  BootMode = QueryBootMode(6);
  *(int *)outbuf = BootMode ? (*(_WORD *)BootMode & 0xFFFC) : 2048;
}

//----- (004029F8) --------------------------------------------------------
static int *__fastcall iopinfo_rpc_service_handler(int fno, void *buffer, int length)
{
  if ( fno == 1 )
    iopinfo_rpc_querybootmode(buffer, length, iopinfo_rpc_outbuf);
  else
    printf("sce_iopinfo: unrecognized code %x\n", fno);
  return iopinfo_rpc_outbuf;
}
// 404150: using guessed type int iopinfo_rpc_outbuf[4];

//----- (00402A50) --------------------------------------------------------
static void iopinfo_rpc_service_start_thread_unused()
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
}
// 404160: using guessed type int iopinfo_rpc_service_in_buf[16];
// 4041A0: using guessed type SifRpcDataQueue_t g_iopinfo_sif_qd;
#endif
