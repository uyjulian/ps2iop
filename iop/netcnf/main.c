
#include "irx_imports.h"
#include <stdbool.h>
#include <netcnf.h>

IRX_ID("NET_configuration", 2, 30);

struct netcnf_callback_handle_info
{
  int m_fd;
  char m_device[16];
  char m_pathname[256];
  void *m_buf;
  int m_filesize;
  int m_bufpos;
  int m_allocstate;
};

struct netcnf_option
{
  int m_type;
  int m_offset;
  const char *m_key;
};

//-------------------------------------------------------------------------
// Function declarations

u32 get_check_provider_eq_zero();
int do_print_usage();
int do_module_load(int ac, char **av);
int do_module_unload();
int _start(int ac, char **av);



















void netcnf_0();
int do_read_ilink_id();
int do_read_netcnf_decode(const char *netcnf_path, char **netcnf_heap_ptr);
int do_write_netcnf_encode(const char *netcnf_path, void *buf, int netcnf_len);
int do_read_netcnf_no_decode(const char *netcnf_path, char **netcnf_heap_ptr);
u32 do_init_xor_magic(char *in_id_buf);
int magic_shift_write_netcnf_2(int inshft, int buflen);
int magic_shift_read_netcnf_2(int inshft, int buflen);
int magic_shift_write_netcnf_1(int inshft, int buflen);
int magic_shift_read_netcnf_1(int inshft, int buflen);
int do_safe_strcpy(char *dst, size_t maxlen, const char *src, int linenum);
int do_safe_strcat(char *dst, size_t maxlen, const char *src, int linenum);
int do_safe_make_pathname(char *dst, size_t maxlen, const char *srcdir, const char *srcbase);
int do_safe_make_name(char *dst, size_t maxlen, const char *src1, const char *src2);
int do_check_capacity_inner2(const char *fpath, int minsize);
int do_check_capacity_inner(const char *fpath);
int do_handle_combination_path(int type, const char *fpath, char *dst, size_t maxlen, char *usr_name);
int do_copy_netcnf_path(const char *netcnf_path_1, const char *netcnf_path_2);
char *do_write_memcard_pathcopy(char *dst, size_t maxlen, const char *src);
int do_write_memcard_files(const char *fpath, const char *icon_value, const char *iconsys_value);
int do_handle_fname(char *fpath, size_t maxlen, const char *fname);
char *do_check_hoge_newline(char *buf);
int do_split_str_comma_index(char *dst, const char *src, int commaind);
int do_remove_old_config(const char *fpath, const char *netcnf_heap_buf, char *icon_value, char *iconsys_value);
int do_type_check(int type, const char *buf);
int do_read_current_netcnf_nodecode(const char *fpath, char **netcnf_heap_ptr);
int do_write_noencode_netcnf_atomic(const char *fpath, void *ptr, int size);
int do_remove_netcnf_dirname(char *dirpath, const char *entry_buffer);
int do_get_count_list_inner(char *fname, int type, sceNetCnfList_t *p);
int do_load_entry_inner(char *fname, int type, char *usr_name, sceNetCnfEnv_t *e);
void do_some_ifc_handling_hoge(const char *arg_fname);
int do_some_pair_handling(char *fpath, int type, const char *src, sceNetCnfEnv_t *e);
int do_add_entry_inner(char *fname, int type, char *usr_name, sceNetCnfEnv_t *e, char *icon_value, char *iconsys_value, int no_check_capacity);
int do_handle_set_usrname(const char *fpath, int type, const char *usrname_buf2, const char *usrname_bufnew);
int do_edit_entry_inner(char *fname, int type, char *usr_name, char *new_usr_name, sceNetCnfEnv_t *e, char *icon_value, char *iconsys_value, int no_check_capacity);
size_t do_delete_entry_inner(char *fname, int type, char *usr_name, char *icon_value, char *iconsys_value, int no_check_capacity);
size_t do_set_latest_entry_inner(char *fname, int type, char *usr_name);
int do_delete_all_inner(const char *dev);
int do_check_special_provider_inner(char *fname, int type, char *usr_name, sceNetCnfEnv_t *e);
char *do_alloc_mem_inner(sceNetCnfEnv_t *e, size_t size, char align);
const char *do_netcnf_parse_string(sceNetCnfEnv_t *e, const char *e_arg);
char *do_alloc_mem_for_write(sceNetCnfEnv_t *e, const char *str);
char *do_check_e_arg(sceNetCnfEnv_t *e, const char *e_arg);
int do_parse_number(sceNetCnfEnv_t *e, const char *e_arg, int *n_result);
int do_netcnfname2address_wrap(sceNetCnfEnv_t *e, char *buf, sceNetCnfAddress_t *paddr);
int do_parse_phone_stuff(sceNetCnfEnv_t *e, int opt_argc, const char **opt_argv, int *p_result);
int do_check_interface_keyword(sceNetCnfEnv_t *e, const char *display_name_arg, const char *attach_ifc_arg, const char *attach_dev_arg);
int do_check_nameserver(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc, int opt_argc, char **opt_argv);
int do_check_route(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc, int opt_argc, char **opt_argv);
const char *do_init_ifc_inner(sceNetCnfInterface_t *ifc);
int do_check_args(sceNetCnfEnv_t *e, struct sceNetCnfUnknownList *unknown_list);
int do_check_other_keywords(sceNetCnfEnv_t *e, struct netcnf_option *options, void *cnfdata, struct sceNetCnfUnknownList *unknown_list);
int do_handle_net_cnf(sceNetCnfEnv_t *e);
int do_handle_attach_cnf(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc);
int do_handle_dial_cnf(sceNetCnfEnv_t *e, struct sceNetCnfDial *dial);
int do_check_line_buffer(sceNetCnfEnv_t *e, u8 *lbuf, int (*readcb)(int, int), void *userdata);
int do_read_netcnf(sceNetCnfEnv_t *e, const char *netcnf_path, char **netcnf_heap_ptr, int is_attach_cnf);
char *do_handle_netcnf_prerw(sceNetCnfEnv_t *e, const char *entry_buffer);
int do_netcnf_read_related(sceNetCnfEnv_t *e, const char *path, int (*readcb)(), void *userdata);
int do_netcnf_dial_related(sceNetCnfEnv_t *e);
int do_netcnf_ifc_related(sceNetCnfEnv_t *e);
void do_dialauth_related(sceNetCnfInterface_t *ncid, struct sceNetCnfInterface *ncis);
int do_merge_conf_inner(sceNetCnfEnv_t *e);
int do_load_conf_inner(sceNetCnfEnv_t *e);
int do_load_dial_inner(sceNetCnfEnv_t *e, sceNetCnfPair_t *pair);
int do_netcnf_vsprintf_buffer(sceNetCnfEnv_t *e, char *fmt, unsigned int va);
int do_netcnf_sprintf_buffer(sceNetCnfEnv_t *e, const char *fmt, ...);
int do_netcnf_other_write(sceNetCnfEnv_t *e, struct netcnf_option *options, void *cnfdata);
int do_netcnf_net_write(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc);
int do_netcnf_phone_write(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc);
int do_netcnf_unknown_write(sceNetCnfEnv_t *e, struct sceNetCnfUnknownList *unknown_list);
int do_write_netcnf(sceNetCnfEnv_t *e, const char *path, int is_attach_cnf);
int do_export_netcnf_inner(sceNetCnfEnv_t *e, const char *arg_fname, struct sceNetCnfInterface *ifc);
int do_export_netcnf(sceNetCnfEnv_t *e);
char *do_address_to_string_inner_element(char *dst, int srcbyte);
char *do_address_to_string_inner(char *dst, unsigned int srcint);
int do_name_2_address_inner(unsigned int *dst, char *buf);
int do_conv_a2s_inner(char *sp_, char *dp_, int len);
int do_conv_s2a_inner(char *sp_, char *dp_, int len);
int do_check_aolnet(const char *auth_name);
int do_check_authnet(char *argst, char *arged);
int do_read_check_netcnf(const char *netcnf_path, int type, int no_check_magic, int no_decode);
int do_check_provider_inner(sceNetCnfEnv_t *e, int type);
char *do_handle_netcnf_dirname(char *fpath, const char *entry_buffer, char *netcnf_file_path);
int do_get_filesize_inner(int fd);
int is_special_file_path(const char *netcnf_path);
u32 do_init_callback_handles();
int do_get_empty_callback_handle(int in_fd, int in_allocstate);
int do_filesize_callback_handles(int in_fd, int in_allocstate);
int do_clear_callback_handles(int fd, int allocmatch);
const char *do_colon_callback_handles(const char *netcnf_path, char *device);
int do_open_netcnf(const char *netcnf_path, int file_flags, int file_mode);
size_t do_read_callback_handles(int handlefd, int fd, void *ptr, size_t size);
size_t do_readfile_netcnf(int fd, void *ptr, int size);
int do_write_netcnf_no_encode(int fd, void *ptr, int size);
int do_dopen_wrap(const char *fn);
int do_dread_wrap(int fn, iox_dirent_t *buf);
int do_remove_wrap(const char *fn);
int do_close_netcnf(int fd);
int do_dclose_wrap(int fd);
int do_filesize_netcnf(int fd);
int do_getstat_wrap(const char *fn, iox_stat_t *stat);
int do_chstat_mode_copyprotect_wrap(const char *fn);
u32 do_set_callback_inner(sceNetCnfCallback_t *pcallback);
int do_init_heap();
void *do_alloc_heapmem(size_t nbytes);
int do_free_heapmem(void *ptr); // idb
void do_delete_heap();

//-------------------------------------------------------------------------
// Data declarations

const struct irx_export_table exports =
{
  1103101952u,
  NULL,
  288u,
  0u,
  { 110u, 101u, 116u, 99u, 110u, 102u, 0u, 0u },
  { &netcnf_0 }
}; // idb
int g_null_string = 0; // weak
// FIXME jump table
#if 0
void *off_40A9B8 = &loc_40739C; // weak
#endif
int g_no_check_capacity = 0; // weak
int g_no_check_provider = 0; // weak
u32 g_id_result = 0u; // idb
char *g_count_list_heapptr = NULL;
char *g_load_entry_heapptr = NULL;
char *g_add_entry_heapptr = NULL;
char *g_edit_entry_heapptr = NULL;
char *g_delete_entry_heapptr = NULL;
char *g_set_latest_entry_heapptr = NULL;
char *g_check_special_provider_heapptr = NULL;
struct netcnf_option g_options_net_cnf[7] =
{
  { 112, 12, "chat_additional" },
  { 52, 16, "redial_count" },
  { 52, 20, "redial_interval" },
  { 112, 24, "outside_number" },
  { 112, 28, "outside_delay" },
  { 68, 32, "dialing_type" },
  { 0, 0, NULL }
}; // weak
struct netcnf_option g_options_attach_cnf[75] =
{
  { 84, 0, "type" },
  { 112, 4, "vendor" },
  { 112, 8, "product" },
  { 112, 12, "location" },
  { 98, 16, "dhcp" },
  { 112, 20, "dhcp_host_name" },
  { 98, 24, "dhcp_host_name_null_terminated" },
  { 98, 25, "dhcp_release_on_stop" },
  { 112, 28, "address" },
  { 112, 32, "netmask" },
  { 112, 36, "chat_additional" },
  { 52, 40, "redial_count" },
  { 52, 44, "redial_interval" },
  { 112, 48, "outside_number" },
  { 112, 52, "outside_delay" },
  { 98, 96, "answer_mode" },
  { 52, 100, "answer_timeout" },
  { 68, 104, "dialing_type" },
  { 112, 108, "chat_login" },
  { 112, 112, "auth_name" },
  { 112, 116, "auth_key" },
  { 112, 120, "peer_name" },
  { 112, 124, "peer_key" },
  { 52, 128, "lcp_timeout" },
  { 52, 132, "ipcp_timeout" },
  { 52, 136, "idle_timeout" },
  { 52, 140, "connect_timeout" },
  { 98, 144, "want.mru_nego" },
  { 98, 145, "want.accm_nego" },
  { 98, 146, "want.magic_nego" },
  { 98, 147, "want.prc_nego" },
  { 98, 148, "want.acc_nego" },
  { 98, 149, "want.address_nego" },
  { 98, 150, "want.vjcomp_nego" },
  { 98, 151, "want.dns1_nego" },
  { 98, 152, "want.dns2_nego" },
  { 77, 160, "want.mru" },
  { 67, 164, "want.accm" },
  { 65, 168, "want.auth" },
  { 112, 172, "want.ip_address" },
  { 112, 176, "want.ip_mask" },
  { 112, 180, "want.dns1" },
  { 112, 184, "want.dns2" },
  { 98, 220, "allow.mru_nego" },
  { 98, 221, "allow.accm_nego" },
  { 98, 222, "allow.magic_nego" },
  { 98, 223, "allow.prc_nego" },
  { 98, 224, "allow.acc_nego" },
  { 98, 225, "allow.address_nego" },
  { 98, 226, "allow.vjcomp_nego" },
  { 98, 227, "allow.dns1_nego" },
  { 98, 228, "allow.dns2_nego" },
  { 77, 236, "allow.mru" },
  { 67, 240, "allow.accm" },
  { 65, 244, "allow.auth" },
  { 112, 248, "allow.ip_address" },
  { 112, 252, "allow.ip_mask" },
  { 112, 256, "allow.dns1" },
  { 112, 260, "allow.dns2" },
  { 76, 296, "log_flags" },
  { 99, 300, "force_chap_type" },
  { 98, 301, "omit_empty_frame" },
  { 80, 332, "phy_config" },
  { 98, 302, "pppoe" },
  { 98, 303, "pppoe_host_uniq_auto" },
  { 112, 308, "pppoe_service_name" },
  { 112, 312, "pppoe_ac_name" },
  { 52, 316, "mtu" },
  { 49, 324, "auth_timeout" },
  { 49, 321, "lcp_max_terminate" },
  { 49, 323, "ipcp_max_terminate" },
  { 49, 320, "lcp_max_configure" },
  { 49, 322, "ipcp_max_configure" },
  { 49, 325, "auth_max_failure" },
  { 0, 0, NULL }
}; // weak
struct netcnf_option g_options_dial_cnf[5] =
{
  { 112, 12, "chat_init" },
  { 112, 16, "chat_dial" },
  { 112, 20, "chat_answer" },
  { 112, 24, "redial_string" },
  { 0, 0, NULL }
}; // weak
char a0123456789abcd[17] = "0123456789ABCDEF"; // weak
char a0123456789abcd_0[17] = "0123456789abcdef"; // weak
int g_callbacks_set = 0; // weak
void *g_netcnf_heap = NULL; // idb
int g_semid; // idb
char g_icon_value[0x100]; // idb
char g_iconsys_value[0x100]; // idb
char g_id_xorbuf[24]; // weak
char g_id_buffer[8]; // weak
char g_ifc_buffer[0x3e8]; // weak
char g_arg_fname[0x400]; // idb
char g_entry_buffer[0x400]; // weak
char g_netcnf_file_path[0x100]; // idb
char g_dir_name[0x100]; // idb
char g_combination_buf1[0x100]; // idb
char g_combination_buf2[0x100]; // idb
char *g_read_check_netcnf_heapptr;
sceNetCnfCallback_t g_callbacks; // weak
struct netcnf_callback_handle_info g_callback_handle_infos[4]; // weak
int g_open_callback_handle_count; // weak


//----- (00400000) --------------------------------------------------------
u32 get_check_provider_eq_zero()
{
  return g_no_check_provider == 0;
}
// 40AC6C: using guessed type int g_no_check_provider;

//----- (00400010) --------------------------------------------------------
int do_print_usage()
{
  printf("Usage: netcnf [<option>] icon=<icon-path> iconsys=<iconsys-path>\n");
  printf("  <option>:\n");
  printf("    -no_check_capacity        do not check capacity\n");
  printf("    -no_check_provider        do not check special provider\n");
  return -1;
}

//----- (00400068) --------------------------------------------------------
int do_module_load(int ac, char **av)
{
  int semid; // $v0
  int ac_cur; // $s1
  const char **av_cur; // $s0
  int heap_inited; // $v0
  int regres; // $v0
  iop_sema_t semaparam; // [sp+10h] [-10h] BYREF

  if ( ac < 3 )
  {
    do_print_usage();
    return 1;
  }
  semaparam.attr = 1;
  semaparam.initial = 1;
  semaparam.max = 1;
  semaparam.option = 0;
  semid = CreateSema(&semaparam);
  g_semid = semid;
  ac_cur = ac - 1;
  if ( semid <= 0 )
  {
    printf("netcnf: CreateSema (%d)\n", semid);
    return 1;
  }
  g_icon_value[0] = 0;
  g_iconsys_value[0] = 0;
  for ( av_cur = (const char **)(av + 1); ac_cur > 0; ++av_cur )
  {
    if ( !strncmp("icon=", *av_cur, 5) )
    {
      strcpy(g_icon_value, *av_cur + 5);
      --ac_cur;
    }
    else if ( !strncmp("iconsys=", *av_cur, 8) )
    {
      strcpy(g_iconsys_value, *av_cur + 8);
      --ac_cur;
    }
    else if ( !strcmp("-no_check_capacity", *av_cur) )
    {
      g_no_check_capacity = 1;
      --ac_cur;
    }
    else
    {
      --ac_cur;
      if ( strcmp("-no_check_provider", *av_cur) )
        goto LABEL_21;
      g_no_check_provider = 1;
    }
  }
  if ( g_icon_value[0] && g_iconsys_value[0] )
  {
    heap_inited = do_init_heap();
    if ( heap_inited >= 0 )
    {
      regres = RegisterLibraryEntries((struct irx_export_table *)&exports);
      if ( !regres )
        return 2;
      printf("netcnf: RegisterLibraryEntries(%d)\n", regres);
      do_delete_heap();
    }
    else
    {
      printf("netcnf: init_heap(%d)\n", heap_inited);
    }
  }
  else
  {
LABEL_21:
    do_print_usage();
  }
  DeleteSema(g_semid);
  return 1;
}
// 40AC68: using guessed type int g_no_check_capacity;
// 40AC6C: using guessed type int g_no_check_provider;

//----- (00400288) --------------------------------------------------------
int do_module_unload()
{
  int relres; // $v0
  int errstate; // $s0
  const char *errstr; // $a0
  int result; // $v0

  errstate = 0;
  relres = ReleaseLibraryEntries((struct irx_export_table *)&exports);
  errstr = "netcnf: ReleaseLibraryEntries (%d)\n";
  if ( relres )
    goto LABEL_4;
  errstate = 1;
  relres = DeleteSema(g_semid);
  if ( relres )
  {
    errstr = "netcnf: DeleteSema (%d)\n";
LABEL_4:
    printf(errstr, relres);
    goto LABEL_6;
  }
  errstate = 2;
LABEL_6:
  if ( errstate == 2 )
  {
    do_delete_heap();
    return 1;
  }
  else
  {
    result = 2;
    if ( errstate == 1 )
    {
      RegisterLibraryEntries((struct irx_export_table *)&exports);
      return 2;
    }
  }
  return result;
}

//----- (00400330) --------------------------------------------------------
int _start(int ac, char **av)
{
  if ( ac >= 0 )
    return do_module_load(ac, av);
  else
    return do_module_unload();
}

//----- (00400364) --------------------------------------------------------
int sceNetCnfGetCount(char *fname, int type)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_get_count_list_inner(fname, type, 0);
  SignalSema(g_semid);
  return retres;
}

//----- (004003DC) --------------------------------------------------------
int sceNetCnfGetList(char *fname, int type, sceNetCnfList_t *p)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_get_count_list_inner(fname, type, p);
  SignalSema(g_semid);
  return retres;
}

//----- (00400460) --------------------------------------------------------
int sceNetCnfLoadEntry(char *fname, int type, char *usr_name, sceNetCnfEnv_t *e)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_load_entry_inner(fname, type, usr_name, e);
  SignalSema(g_semid);
  return retres;
}

//----- (004004F4) --------------------------------------------------------
int sceNetCnfAddEntry(char *fname, int type, char *usr_name, sceNetCnfEnv_t *e)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_add_entry_inner(fname, type, usr_name, e, g_icon_value, g_iconsys_value, g_no_check_capacity);
  SignalSema(g_semid);
  return retres;
}
// 40AC68: using guessed type int g_no_check_capacity;

//----- (004005AC) --------------------------------------------------------
int sceNetCnfEditEntry(char *fname, int type, char *usr_name, char *new_usr_name, sceNetCnfEnv_t *e)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_edit_entry_inner(
             fname,
             type,
             usr_name,
             new_usr_name,
             e,
             g_icon_value,
             g_iconsys_value,
             g_no_check_capacity);
  SignalSema(g_semid);
  return retres;
}
// 40AC68: using guessed type int g_no_check_capacity;

//----- (00400674) --------------------------------------------------------
int sceNetCnfDeleteEntry(char *fname, int type, char *usr_name)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_delete_entry_inner(fname, type, usr_name, g_icon_value, g_iconsys_value, g_no_check_capacity);
  SignalSema(g_semid);
  return retres;
}
// 40AC68: using guessed type int g_no_check_capacity;

//----- (00400718) --------------------------------------------------------
int sceNetCnfSetLatestEntry(char *fname, int type, char *usr_name)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_set_latest_entry_inner(fname, type, usr_name);
  SignalSema(g_semid);
  return retres;
}

//----- (0040079C) --------------------------------------------------------
void *sceNetCnfAllocMem(sceNetCnfEnv_t *e, int size, int align)
{
  return do_alloc_mem_inner(e, size, align);
}

//----- (004007D0) --------------------------------------------------------
int sceNetCnfInitIFC(sceNetCnfInterface_t *ifc)
{
  if ( ifc )
  {
    bzero(ifc, 352);
    do_init_ifc_inner(ifc);
  }
  return 0;
}

//----- (00400824) --------------------------------------------------------
int sceNetCnfLoadConf(sceNetCnfEnv_t *e)
{
  return do_load_conf_inner(e);
}

//----- (00400858) --------------------------------------------------------
int sceNetCnfLoadDial(sceNetCnfEnv_t *e, sceNetCnfPair_t *pair)
{
  return do_load_dial_inner(e, pair);
}

//----- (0040088C) --------------------------------------------------------
int sceNetCnfMergeConf(sceNetCnfEnv_t *e)
{
  return do_merge_conf_inner(e);
}

//----- (004008C0) --------------------------------------------------------
int sceNetCnfName2Address(sceNetCnfAddress_t *paddr, char *buf)
{
  int retn1; // $s0
  unsigned int paddr_tmp[2]; // [sp+10h] [-8h] BYREF

  retn1 = -1;
  paddr_tmp[0] = 0;
  if ( !buf || do_name_2_address_inner(paddr_tmp, buf) )
  {
    bzero(paddr, 20);
    bcopy(paddr_tmp, paddr->data, 4);
    return 0;
  }
  return retn1;
}

//----- (00400940) --------------------------------------------------------
int sceNetCnfAddress2String(char *buf, int len, sceNetCnfAddress_t *paddr)
{
  int v5; // $s0
  int buflen; // $a2
  char buf_tmp[24]; // [sp+10h] [-20h] BYREF
  unsigned int srcintx; // [sp+28h] [-8h] BYREF

  v5 = -1;
  if ( !paddr->reserved )
  {
    bcopy(paddr->data, &srcintx, 4);
    do_address_to_string_inner(buf_tmp, srcintx);
    buflen = strlen(buf_tmp) + 1;
    if ( len >= buflen )
    {
      bcopy(buf_tmp, buf, buflen);
      return 0;
    }
  }
  return v5;
}

//----- (004009E0) --------------------------------------------------------
int sceNetCnfDeleteAll(char *dev)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_delete_all_inner(dev);
  SignalSema(g_semid);
  return retres;
}

//----- (00400A44) --------------------------------------------------------
int sceNetCnfCheckCapacity(char *fname)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_check_capacity_inner(fname);
  SignalSema(g_semid);
  return retres;
}

//----- (00400AA8) --------------------------------------------------------
int sceNetCnfConvA2S(char *sp_, char *dp_, int len)
{
  int retres; // $v0
  bool condtmp; // dc

  retres = do_conv_a2s_inner(sp_, dp_, len);
  if ( !retres )
  {
    condtmp = len < strlen(sp_) + 1;
    retres = -19;
    if ( !condtmp )
    {
      strcpy(dp_, sp_);
      return 0;
    }
  }
  return retres;
}

//----- (00400B20) --------------------------------------------------------
int sceNetCnfConvS2A(char *sp_, char *dp_, int len)
{
  int retres; // $v0
  bool condtmp; // dc

  retres = do_conv_s2a_inner(sp_, dp_, len);
  if ( !retres )
  {
    condtmp = len < strlen(sp_) + 1;
    retres = -19;
    if ( !condtmp )
    {
      strcpy(dp_, sp_);
      return 0;
    }
  }
  return retres;
}

//----- (00400B98) --------------------------------------------------------
int sceNetCnfCheckSpecialProvider(char *fname, int type, char *usr_name, sceNetCnfEnv_t *e)
{
  int retres; // $s0

  WaitSema(g_semid);
  retres = do_check_special_provider_inner(fname, type, usr_name, e);
  SignalSema(g_semid);
  return retres;
}

//----- (00400C2C) --------------------------------------------------------
void sceNetCnfSetCallback(sceNetCnfCallback_t *pcallback)
{
  WaitSema(g_semid);
  do_set_callback_inner(pcallback);
  SignalSema(g_semid);
}

//----- (00400D08) --------------------------------------------------------
void netcnf_0()
{
  ;
}

//----- (00400D10) --------------------------------------------------------
int do_read_ilink_id()
{
  int i; // $s0
  bool condtmp1; // dc
  u32 condtmp2; // $v0

  for ( i = 0; ; ++i )
  {
    g_id_result = 0;
    condtmp1 = sceCdRI((u8 *)g_id_buffer, &g_id_result) != 1;
    condtmp2 = i < 20;
    if ( !condtmp1 )
    {
      condtmp2 = i < 20;
      if ( !g_id_result )
        break;
    }
    if ( !condtmp2 )
      return -13;
    DelayThread(100000);
  }
  return 0;
}

//----- (00400DA8) --------------------------------------------------------
int do_read_netcnf_decode(const char *netcnf_path, char **netcnf_heap_ptr)
{
  int result; // $v0
  int fd; // $s5
  int retres; // $v1
  int netcnf_size; // $v0
  int netcnf_size_1; // $s0
  char *heapmem; // $v0
  char *netcnf_data; // $s2
  int netcnf_size_2; // $s3
  int xorind1; // $s1
  int xoroffs; // $s4
  u32 condtmp1; // $v0
  size_t readres; // $s0
  u16 dataval1; // $v0
  int buflenx1; // $a1
  int xorind2_1; // $s1
  u16 bufresx1; // $v0
  int xorind3_1; // $v1
  u8 dataval2; // $v0
  int buflenx2; // $a1
  int xorind2_2; // $s1
  char bufresx2; // $v0
  int xorind3_2; // $v1

  *netcnf_heap_ptr = 0;
  result = do_read_ilink_id();
  if ( result < 0 )
    return result;
  do_init_xor_magic(g_id_buffer);
  fd = do_open_netcnf(netcnf_path, 1, 0);
  if ( fd < 0 )
  {
    retres = -3;
    if ( fd == -5 )
      return -18;
    return retres;
  }
  netcnf_size = do_filesize_netcnf(fd);
  netcnf_size_1 = netcnf_size;
  if ( netcnf_size < 0 )
  {
    do_close_netcnf(fd);
    return netcnf_size_1;
  }
  heapmem = (char *)do_alloc_heapmem(netcnf_size + 1);
  *netcnf_heap_ptr = heapmem;
  if ( !heapmem )
  {
    do_close_netcnf(fd);
    return -2;
  }
  netcnf_data = heapmem;
  netcnf_size_2 = netcnf_size_1;
  xorind1 = 0;
  xoroffs = 0;
  if ( !netcnf_size_1 )
  {
LABEL_24:
    (*netcnf_heap_ptr)[xoroffs] = 0;
    do_close_netcnf(fd);
    return xoroffs;
  }
  condtmp1 = netcnf_size_1 < 2;
  while ( !condtmp1 )
  {
    readres = do_readfile_netcnf(fd, netcnf_data, 2);
    if ( readres < 0 )
      goto LABEL_18;
    dataval1 = ~*(u16 *)netcnf_data;
    *(u16 *)netcnf_data = dataval1;
    buflenx1 = (u8)g_id_xorbuf[xorind1 + 2];
    xorind2_1 = xorind1 + 1;
    bufresx1 = magic_shift_read_netcnf_1(dataval1, buflenx1);
    xorind3_1 = 0;
    *(u16 *)netcnf_data = bufresx1;
    if ( xorind2_1 != 24 )
      xorind3_1 = xorind2_1;
    xorind1 = xorind3_1;
    netcnf_data += 2;
    netcnf_size_2 -= 2;
    xoroffs += 2;
LABEL_23:
    condtmp1 = netcnf_size_2 < 2;
    if ( !netcnf_size_2 )
      goto LABEL_24;
  }
  readres = do_readfile_netcnf(fd, netcnf_data, 1);
  if ( readres >= 0 )
  {
    dataval2 = ~*netcnf_data;
    *netcnf_data = dataval2;
    buflenx2 = (u8)g_id_xorbuf[xorind1 + 2];
    xorind2_2 = xorind1 + 1;
    bufresx2 = magic_shift_read_netcnf_2(dataval2, buflenx2);
    xorind3_2 = 0;
    *netcnf_data = bufresx2;
    if ( xorind2_2 != 24 )
      xorind3_2 = xorind2_2;
    xorind1 = xorind3_2;
    --netcnf_size_2;
    ++xoroffs;
    goto LABEL_23;
  }
LABEL_18:
  do_free_heapmem(*netcnf_heap_ptr);
  *netcnf_heap_ptr = 0;
  do_close_netcnf(fd);
  result = -18;
  if ( readres != -5 )
    return -4;
  return result;
}

//----- (00400FD4) --------------------------------------------------------
int do_write_netcnf_encode(const char *netcnf_path, void *buf, int netcnf_len)
{
  int result; // $v0
  int fd; // $s3
  u16 *buf_1; // $s5
  int retres; // $v1
  int netcnf_len_1; // $s2
  int xorind1; // $s1
  bool condtmp1; // dc
  int xoroffs; // $s4
  u32 condtmp2; // $v0
  int buflenx1; // $a1
  u16 bufresx1; // $v0
  int xorind2_1; // $s1
  int xorind3_1; // $v1
  int writeres; // $s0
  int buflenx2; // $a1
  char bufresx2; // $v0
  int xorind2_2; // $s1
  int xorind3_2; // $v1
  u16 bufflipx1; // [sp+10h] [-8h] BYREF
  char bufflipx2[6]; // [sp+12h] [-6h] BYREF

  result = do_read_ilink_id();
  if ( result < 0 )
    return result;
  do_init_xor_magic(g_id_buffer);
  fd = do_open_netcnf(netcnf_path, 1538, 511);
  buf_1 = (u16 *)buf;
  if ( fd < 0 )
  {
    retres = -3;
    if ( fd == -5 )
      return -18;
    return retres;
  }
  netcnf_len_1 = netcnf_len;
  xorind1 = 0;
  condtmp1 = netcnf_len == 0;
  xoroffs = 0;
  if ( condtmp1 )
  {
LABEL_20:
    do_close_netcnf(fd);
    return xoroffs;
  }
  condtmp2 = netcnf_len_1 < 2;
  while ( !condtmp2 )
  {
    buflenx1 = (u8)g_id_xorbuf[xorind1 + 2];
    xorind2_1 = xorind1 + 1;
    bufresx1 = magic_shift_write_netcnf_1(*buf_1, buflenx1);
    xorind3_1 = 0;
    bufflipx1 = bufresx1;
    if ( xorind2_1 != 24 )
      xorind3_1 = xorind2_1;
    xorind1 = xorind3_1;
    bufflipx1 = ~bufresx1;
    writeres = do_write_netcnf_no_encode(fd, &bufflipx1, 2);
    ++buf_1;
    if ( writeres < 0 )
      goto LABEL_16;
    netcnf_len_1 -= 2;
    xoroffs += 2;
LABEL_19:
    condtmp2 = netcnf_len_1 < 2;
    if ( !netcnf_len_1 )
      goto LABEL_20;
  }
  buflenx2 = (u8)g_id_xorbuf[xorind1 + 2];
  xorind2_2 = xorind1 + 1;
  bufresx2 = magic_shift_write_netcnf_2(*(u8 *)buf_1, buflenx2);
  xorind3_2 = 0;
  bufflipx2[0] = bufresx2;
  if ( xorind2_2 != 24 )
    xorind3_2 = xorind2_2;
  xorind1 = xorind3_2;
  bufflipx2[0] = ~bufresx2;
  writeres = do_write_netcnf_no_encode(fd, bufflipx2, 1);
  --netcnf_len_1;
  if ( writeres >= 0 )
  {
    ++xoroffs;
    goto LABEL_19;
  }
LABEL_16:
  do_close_netcnf(fd);
  result = -18;
  if ( writeres != -5 )
    return -5;
  return result;
}
// 400FD4: using guessed type char bufflipx2[6];

//----- (00401188) --------------------------------------------------------
int do_read_netcnf_no_decode(const char *netcnf_path, char **netcnf_heap_ptr)
{
  int fd; // $v0
  int fd_1; // $s0
  int result; // $v0
  int netcnf_size; // $v0
  int netcnf_size_1; // $s1
  int fd_2; // $a0
  char *netcnf_data; // $v0
  size_t readres; // $v0

  *netcnf_heap_ptr = 0;
  fd = do_open_netcnf(netcnf_path, 1, 0);
  fd_1 = fd;
  if ( fd < 0 )
  {
    result = -18;
    if ( fd_1 != -5 )
      return -3;
    return result;
  }
  netcnf_size = do_filesize_netcnf(fd);
  netcnf_size_1 = netcnf_size;
  fd_2 = fd_1;
  if ( netcnf_size < 0 )
  {
LABEL_9:
    do_close_netcnf(fd_2);
    return netcnf_size_1;
  }
  netcnf_data = (char *)do_alloc_heapmem(netcnf_size + 1);
  *netcnf_heap_ptr = netcnf_data;
  if ( !netcnf_data )
  {
    do_close_netcnf(fd_1);
    return -2;
  }
  readres = do_readfile_netcnf(fd_1, netcnf_data, netcnf_size_1);
  netcnf_size_1 = readres;
  fd_2 = fd_1;
  if ( readres >= 0 )
  {
    (*netcnf_heap_ptr)[readres] = 0;
    goto LABEL_9;
  }
  do_free_heapmem(*netcnf_heap_ptr);
  *netcnf_heap_ptr = 0;
  do_close_netcnf(fd_1);
  result = -18;
  if ( netcnf_size_1 != -5 )
    return -4;
  return result;
}

//----- (0040127C) --------------------------------------------------------
u32 do_init_xor_magic(char *in_id_buf)
{
  int curoffs2; // $a2
  int curoffs1; // $a1
  char curchr; // $v0
  u32 condtmp; // $v0

  curoffs2 = 0;
  curoffs1 = 2;
  do
  {
    g_id_xorbuf[curoffs1] = ((u8)in_id_buf[curoffs2] >> 5) + 1;
    g_id_xorbuf[curoffs1 + 1] = (((u8)in_id_buf[curoffs2] >> 2) & 7) + 1;
    curchr = in_id_buf[curoffs2++];
    g_id_xorbuf[curoffs1 + 2] = (curchr & 3) + 1;
    condtmp = curoffs2 < 8;
    curoffs1 += 3;
  }
  while ( curoffs2 < 8 );
  return condtmp;
}

//----- (004012F4) --------------------------------------------------------
int magic_shift_write_netcnf_2(int inshft, int buflen)
{
  for ( ; buflen; inshft = ((u8)inshft >> 7) | (2 * inshft) )
    --buflen;
  return (u8)inshft;
}

//----- (0040131C) --------------------------------------------------------
int magic_shift_read_netcnf_2(int inshft, int buflen)
{
  for ( ; buflen; inshft = ((u8)inshft >> 1) | (inshft << 7) )
    --buflen;
  return (u8)inshft;
}

//----- (00401344) --------------------------------------------------------
int magic_shift_write_netcnf_1(int inshft, int buflen)
{
  for ( ; buflen; inshft = ((u16)inshft >> 15) | (2 * inshft) )
    --buflen;
  return (u16)inshft;
}

//----- (0040136C) --------------------------------------------------------
int magic_shift_read_netcnf_1(int inshft, int buflen)
{
  for ( ; buflen; inshft = ((u16)inshft >> 1) | (inshft << 15) )
    --buflen;
  return (u16)inshft;
}

//----- (004013A0) --------------------------------------------------------
int do_safe_strcpy(char *dst, size_t maxlen, const char *src, int linenum)
{
  if ( strlen(src) < maxlen )
  {
    strcpy(dst, src);
    return 0;
  }
  else
  {
    printf("[netcnf] strcpy failed(%d)\n", linenum);
    return -1;
  }
}

//----- (0040141C) --------------------------------------------------------
int do_safe_strcat(char *dst, size_t maxlen, const char *src, int linenum)
{
  size_t curstrlen; // $s0

  curstrlen = strlen(dst);
  if ( curstrlen + strlen(src) < maxlen )
  {
    strcat(dst, src);
    return 0;
  }
  else
  {
    printf("[netcnf] strcat failed(%d)\n", linenum);
    return -1;
  }
}

//----- (004014AC) --------------------------------------------------------
int do_safe_make_pathname(char *dst, size_t maxlen, const char *srcdir, const char *srcbase)
{
  size_t curstrlen; // $s1

  curstrlen = strlen(srcdir);
  if ( curstrlen + strlen(srcbase) + 1 < maxlen )
  {
    strcpy(dst, srcdir);
    strcat(dst, "/");
    strcat(dst, srcbase);
    return 0;
  }
  else
  {
    printf("[netcnf] make_pathname failed\n");
    return -1;
  }
}

//----- (00401560) --------------------------------------------------------
int do_safe_make_name(char *dst, size_t maxlen, const char *src1, const char *src2)
{
  size_t curstrlen; // $s0

  curstrlen = strlen(src1);
  if ( curstrlen + strlen(src2) < maxlen )
  {
    strcpy(dst, src1);
    strcat(dst, src2);
    return 0;
  }
  else
  {
    printf("[netcnf] make_name failed\n");
    return -1;
  }
}

//----- (00401600) --------------------------------------------------------
int do_check_capacity_inner2(const char *fpath, int minsize)
{
  const char *fpath_1; // $t1
  int curdevnameind; // $t0
  int result; // $v0
  char fpath_curchr; // $v0
  int zonesz; // kr00_4
  int zonefree; // $t2
  char devname[8]; // [sp+18h] [-8h] BYREF

  fpath_1 = fpath;
  curdevnameind = 0;
  if ( *fpath == ':' )
  {
LABEL_5:
    *(u16 *)&devname[curdevnameind] = *(u8 *)fpath_1;
    zonesz = iomanX_devctl(devname, 0x5001, 0, 0, 0, 0);
    zonefree = iomanX_devctl(devname, 0x5002, 0, 0, 0, 0) * (zonesz / 1024);
    result = -16;
    if ( zonefree >= minsize )
      return 0;
  }
  else
  {
    while ( curdevnameind < 5 )
    {
      fpath_curchr = *fpath_1++;
      devname[curdevnameind++] = fpath_curchr;
      if ( *fpath_1 == ':' )
        goto LABEL_5;
    }
    return -9;
  }
  return result;
}
// 401600: using guessed type char devname[8];

//----- (004016F0) --------------------------------------------------------
int do_check_capacity_inner(const char *fpath)
{
  int cmptmp1; // $v0
  const char *fpath_1; // $a0
  int minsize; // $a1
  bool condtmp1; // dc
  int result; // $v0

  cmptmp1 = strncmp(fpath, "mc", 2);
  fpath_1 = fpath;
  if ( cmptmp1 )
  {
    condtmp1 = strncmp(fpath, "pfs", 3) != 0;
    result = -9;
    if ( condtmp1 )
      return result;
    fpath_1 = fpath;
    minsize = 0xF4;
  }
  else
  {
    minsize = 0x5E;
  }
  return do_check_capacity_inner2(fpath_1, minsize);
}

//----- (00401758) --------------------------------------------------------
int do_handle_combination_path(int type, const char *fpath, char *dst, size_t maxlen, char *usr_name)
{
  int result; // $v0
  char *i; // $s0
  int devnum_offs; // $s1
  char *p_devnum; // $v1
  char curdevnum; // $v0
  int devnr; // $s1
  u32 condtmp2; // $v0
  bool condtmp1; // dc
  unsigned int devnr2; // $v0
  char devnum[8]; // [sp+10h] [-8h] BYREF

  if ( !usr_name )
    return -11;
  do_safe_strcpy(dst, maxlen, usr_name, 139);
  result = 0;
  if ( type )
    return result;
  for ( i = dst; ; ++i )
  {
    devnum_offs = 0;
    if ( (look_ctype_table(*i) & 4) != 0 )
      break;
  }
  while ( (look_ctype_table(*i) & 4) != 0 )
  {
    p_devnum = &devnum[devnum_offs];
    if ( devnum_offs >= 4 )
      return -11;
    ++devnum_offs;
    curdevnum = *i++;
    *p_devnum = curdevnum;
  }
  devnum[devnum_offs] = 0;
  devnr = strtol(devnum, 0, 10);
  if ( !strncmp(fpath, "mc", 2) )
  {
    condtmp2 = (unsigned int)(devnr - 1) < 6;
  }
  else
  {
    condtmp1 = strncmp(fpath, "pfs", 3) != 0;
    devnr2 = devnr - 1;
    condtmp2 = condtmp1 ? devnr2 < 0x3E8 : devnr2 < 0xA;
  }
  if ( !condtmp2 )
    return -11;
  do_safe_make_name(dst, maxlen, "Combination", devnum);
  return 0;
}
// 401758: using guessed type char devnum[8];

//----- (004018B8) --------------------------------------------------------
int do_copy_netcnf_path(const char *netcnf_path_1, const char *netcnf_path_2)
{
  int fd2; // $s2
  int result; // $v0
  int fd1; // $s1
  int fd1_1; // $a0
  int readres; // $v0
  int readres_1; // $s0
  int writeres; // $v0
  char tmpbuf[512]; // [sp+10h] [-200h] BYREF

  fd2 = do_open_netcnf(netcnf_path_2, 1538, 511);
  if ( fd2 < 0 )
    return -3;
  fd1 = do_open_netcnf(netcnf_path_1, 1, 0);
  fd1_1 = fd1;
  if ( fd1 >= 0 )
  {
    while ( 1 )
    {
      readres = do_readfile_netcnf(fd1_1, tmpbuf, 512);
      readres_1 = readres;
      if ( readres <= 0 )
        break;
      writeres = do_write_netcnf_no_encode(fd2, tmpbuf, readres);
      fd1_1 = fd1;
      if ( readres_1 != writeres )
      {
        do_close_netcnf(fd2);
        do_close_netcnf(fd1);
        return -5;
      }
    }
    do_close_netcnf(fd2);
    do_close_netcnf(fd1);
    result = -4;
    if ( readres_1 >= 0 )
      return 0;
  }
  else
  {
    do_close_netcnf(fd2);
    return -3;
  }
  return result;
}

//----- (00401994) --------------------------------------------------------
char *do_write_memcard_pathcopy(char *dst, size_t maxlen, const char *src)
{
  char *dst_end_slash; // $a0
  char *dst_cur; // $a0
  int dstchr1; // $v1
  char *dst_cur1; // $a0
  int dstchr2; // $v0
  char *dst_end_notslash; // $a0
  char *result; // $v0

  do_safe_strcpy(dst, maxlen, src, 218);
  dst_end_slash = &dst[strlen(dst)];
  if ( *dst_end_slash != '/' )
  {
    dst_cur = dst_end_slash - 1;
    do
      dstchr1 = *dst_cur--;
    while ( dstchr1 != '/' );
    dst_end_slash = dst_cur + 1;
  }
  dst_cur1 = dst_end_slash - 1;
  do
    dstchr2 = *dst_cur1--;
  while ( dstchr2 == '/' );
  dst_end_notslash = dst_cur1 + 1;
  result = dst;
  if ( *dst_end_notslash == ':' )
    return 0;
  dst_end_notslash[1] = 0;
  return result;
}

//----- (00401A30) --------------------------------------------------------
int do_write_memcard_files(const char *fpath, const char *icon_value, const char *iconsys_value)
{
  int result; // $v0
  char cur_basepath[256]; // [sp+10h] [-200h] BYREF
  char cur_combpath[256]; // [sp+110h] [-100h] BYREF

  if ( !do_write_memcard_pathcopy(cur_basepath, 256, fpath) )
    return 0;
  do_safe_make_pathname(cur_combpath, 256, cur_basepath, "SYS_NET.ICO");
  result = do_copy_netcnf_path(icon_value, cur_combpath);
  if ( result >= 0 )
  {
    do_safe_make_pathname(cur_combpath, 256, cur_basepath, "icon.sys");
    result = do_copy_netcnf_path(iconsys_value, cur_combpath);
    if ( result >= 0 )
      return 0;
  }
  return result;
}

//----- (00401AE8) --------------------------------------------------------
int do_handle_fname(char *fpath, size_t maxlen, const char *fname)
{
  char *index_res; // $s0
  int result; // $v0
  int cmptmp1; // $v0
  char *fpath_1; // $a0
  size_t maxlen_1; // $a1
  const char *pathname; // $a2
  int maxbuf; // $a3
  bool condtmp1; // dc

  do_safe_strcpy(fpath, maxlen, fname, 266);
  index_res = index(fpath, ':');
  if ( !index_res )
    return -9;
  cmptmp1 = strncmp(fpath, "mc", 2);
  fpath_1 = fpath;
  if ( cmptmp1 )
  {
    condtmp1 = strncmp(fpath, "pfs", 3) != 0;
    result = 0;
    if ( condtmp1 )
      return result;
    index_res[1] = 0;
    fpath_1 = fpath;
    maxlen_1 = maxlen;
    pathname = "/etc/network/net.db";
    maxbuf = 279;
  }
  else
  {
    index_res[1] = 0;
    maxlen_1 = maxlen;
    pathname = "/BWNETCNF/BWNETCNF";
    maxbuf = 275;
  }
  do_safe_strcat(fpath_1, maxlen_1, pathname, maxbuf);
  return 0;
}

//----- (00401BB0) --------------------------------------------------------
char *do_check_hoge_newline(char *buf)
{
  int curbuf1; // $v0
  char curbuf2; // $v1

  curbuf1 = *buf;
  curbuf2 = *buf;
  if ( *buf )
  {
    do
    {
      if ( curbuf2 == '\n' )
        break;
      curbuf2 = *++buf;
    }
    while ( *buf );
    curbuf1 = *buf;
  }
  return &buf[curbuf1 == '\n'];
}

//----- (00401BFC) --------------------------------------------------------
int do_split_str_comma_index(char *dst, const char *src, int commaind)
{
  bool condtmp1; // dc
  int commatmp_end; // $a2
  int src_hichr1; // $v0
  int src_chr1; // $v0
  int src_chr2; // $a2
  int src_chr3; // $v1
  int src_hichr2; // $v0
  int src_chr4; // $v0

  condtmp1 = commaind <= 0;
  commatmp_end = commaind - 1;
  if ( !condtmp1 )
  {
    do
    {
      if ( *src )
      {
        if ( *src == ',' )
        {
          ++src;
          goto LABEL_11;
        }
        src_hichr1 = *(u8 *)src << 24;
        do
        {
          if ( src_hichr1 >> 24 == '\n' )
            break;
          if ( !*++src )
            break;
          src_hichr1 = *(u8 *)src << 24;
        }
        while ( *src != ',' );
      }
      src_chr1 = *src++;
      if ( src_chr1 != ',' )
        return -1;
LABEL_11:
      condtmp1 = commatmp_end-- > 0;
    }
    while ( condtmp1 );
  }
  src_chr2 = *src;
  src_chr3 = *(u8 *)src;
  if ( *src && src_chr2 != ',' && src_chr2 != '\n' )
  {
    src_hichr2 = src_chr3 << 24;
    do
    {
      ++src;
      if ( src_hichr2 >> 24 == '\r' )
        break;
      *dst = src_chr3;
      src_chr4 = *src;
      src_chr3 = *(u8 *)src;
      ++dst;
      if ( !*src )
        break;
      if ( src_chr4 == ',' )
        break;
      condtmp1 = src_chr4 != '\n';
      src_hichr2 = src_chr3 << 24;
    }
    while ( condtmp1 );
  }
  *dst = 0;
  return 0;
}

//----- (00401CE4) --------------------------------------------------------
int do_remove_old_config(
        const char *fpath,
        const char *netcnf_heap_buf,
        char *icon_value,
        char *iconsys_value)
{
  int sysneticoflag; // $fp
  bool condtmp1; // dc
  int result; // $v0
  int dfd; // $s4
  int retreszero; // $v1
  int dfd_1; // $a0
  int dread_res; // $s0
  char *curheapbuf1; // $s0
  int v13; // $s2
  int remove_res_2; // $v0
  int cmptmp1; // $v0
  const char *fpath_1; // $a0
  int remove_res_1; // $v0
  int cmptmp2; // $v0
  char cur_basepath[256]; // [sp+10h] [-390h] BYREF
  char cur_combpath[256]; // [sp+110h] [-290h] BYREF
  iox_dirent_t statname; // [sp+210h] [-190h] BYREF
  iox_stat_t statsize; // [sp+358h] [-48h] BYREF
  int iconsysflag; // [sp+398h] [-8h]

  sysneticoflag = 1;
  iconsysflag = 1;
  condtmp1 = do_write_memcard_pathcopy(cur_basepath, 256, fpath) == 0;
  result = 0;
  if ( condtmp1 )
    return result;
  dfd = do_dopen_wrap(cur_basepath);
  if ( dfd < 0 )
  {
    retreszero = 0;
    if ( dfd == -5 )
      return -18;
    return retreszero;
  }
LABEL_6:
  dfd_1 = dfd;
  while ( 1 )
  {
    dread_res = do_dread_wrap(dfd_1, &statname);
    if ( dread_res <= 0 )
      break;
    if ( strlen(statname.name) == 10 )
    {
      if ( !strncmp(&statname.name[6], ".cnf", 4) || !strncmp(&statname.name[6], ".dat", 4) )
      {
        curheapbuf1 = (char *)netcnf_heap_buf;
        v13 = 1;
        if ( netcnf_heap_buf )
        {
          do
          {
            if ( !*curheapbuf1 )
              break;
            do_split_str_comma_index(cur_combpath, curheapbuf1, 2);
            if ( !strcmp(statname.name, cur_combpath) )
              v13 = 0;
            curheapbuf1 = do_check_hoge_newline(curheapbuf1);
          }
          while ( curheapbuf1 );
        }
        if ( !v13 )
          goto LABEL_6;
      }
      goto LABEL_17;
    }
    cmptmp1 = strncmp(fpath, "mc", 2);
    fpath_1 = fpath;
    if ( !cmptmp1 )
    {
      if ( !strcmp(statname.name, "SYS_NET.ICO") )
      {
        do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
        do_getstat_wrap(cur_combpath, &statsize);
        if ( statsize.size != 0x8398 )
          goto LABEL_24;
        sysneticoflag = 0;
      }
      else if ( !strcmp(statname.name, "icon.sys") )
      {
        do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
        do_getstat_wrap(cur_combpath, &statsize);
        if ( statsize.size != 0x3C4 )
        {
LABEL_24:
          remove_res_1 = do_remove_wrap(cur_combpath);
          fpath_1 = fpath;
          if ( remove_res_1 == -5 )
            goto LABEL_36;
          goto LABEL_32;
        }
        iconsysflag = 0;
      }
      else if ( strcmp(statname.name, "BWNETCNF") )
      {
        do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
        if ( do_remove_wrap(cur_combpath) == -5 )
          goto LABEL_36;
      }
      fpath_1 = fpath;
    }
LABEL_32:
    cmptmp2 = strncmp(fpath_1, "pfs", 3);
    dfd_1 = dfd;
    if ( !cmptmp2 )
    {
      if ( !strcmp(statname.name, "net.db") )
        goto LABEL_6;
LABEL_17:
      do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
      remove_res_2 = do_remove_wrap(cur_combpath);
      dfd_1 = dfd;
      if ( remove_res_2 == -5 )
        goto LABEL_36;
    }
  }
  if ( dread_res == -5 )
  {
LABEL_36:
    do_dclose_wrap(dfd);
    return -18;
  }
  do_dclose_wrap(dfd);
  if ( !strncmp(fpath, "mc", 2) )
  {
    if ( sysneticoflag || iconsysflag )
      dread_res = do_write_memcard_files(fpath, icon_value, iconsys_value);
    do_chstat_mode_copyprotect_wrap(cur_basepath);
  }
  return dread_res;
}

//----- (00402060) --------------------------------------------------------
int do_type_check(int type, const char *buf)
{
  if ( do_split_str_comma_index(g_arg_fname, buf, 0) )
    return -1;
  else
    return strtol(g_arg_fname, 0, 10) == type;
}

//----- (004020C0) --------------------------------------------------------
int do_read_current_netcnf_nodecode(const char *fpath, char **netcnf_heap_ptr)
{
  int result; // $v0
  int retres; // $a0

  if ( !fpath )
    return -9;
  result = do_read_netcnf_no_decode(fpath, netcnf_heap_ptr);
  retres = result;
  if ( result < 0 )
  {
    result = 0;
    if ( retres != -3 )
      return retres;
  }
  return result;
}

//----- (00402104) --------------------------------------------------------
int do_write_noencode_netcnf_atomic(const char *fpath, void *ptr, int size)
{
  int result; // $v0
  int fd; // $s0
  int retres; // $v1
  int writeres; // $s1
  int fpath_colon_ind; // $a0
  int fpath_curind; // $a0
  int fpatcurchr; // $v0
  u8 fixme_wrong_offset_fpath[16]; // [sp+0h] [-110h] BYREF
  char fpath_comb[256]; // [sp+10h] [-100h] BYREF

  if ( !fpath )
    return -9;
  do_safe_make_name(fpath_comb, 256, fpath, ".tmp");
  fd = do_open_netcnf(fpath_comb, 1538, 511);
  if ( fd < 0 )
  {
    retres = -3;
    if ( fd == -5 )
      return -18;
    return retres;
  }
  writeres = do_write_netcnf_no_encode(fd, ptr, size);
  if ( size != writeres )
  {
    do_close_netcnf(fd);
    result = -5;
    if ( writeres != -5 )
      return result;
    return -18;
  }
  do_close_netcnf(fd);
  if ( iomanX_rename(fpath_comb, fpath) == -5 )
    return -18;
  fpath_colon_ind = 0;
  if ( fpath_comb[0] != ':' )
  {
    fpath_curind = 1;
    do
      fpatcurchr = fpath_comb[fpath_curind++];
    while ( fpatcurchr != ':' );
    fpath_colon_ind = fpath_curind - 1;
  }
  fixme_wrong_offset_fpath[fpath_colon_ind + 17] = 0;
  return 0;
}
// 402104: using guessed type char fpath_comb[256];

//----- (00402230) --------------------------------------------------------
int do_remove_netcnf_dirname(char *dirpath, const char *entry_buffer)
{
  char *p_dirname; // $v0
  int remove_res_1; // $a0
  int retres; // $v1

  p_dirname = do_handle_netcnf_dirname(dirpath, entry_buffer, g_netcnf_file_path);
  if ( !p_dirname )
    return -7;
  remove_res_1 = do_remove_wrap(p_dirname);
  retres = 0;
  if ( remove_res_1 < 0 )
  {
    retres = -7;
    if ( remove_res_1 == -5 )
      return -18;
  }
  return retres;
}

//----- (00402290) --------------------------------------------------------
int do_get_count_list_inner(char *fname, int type, sceNetCnfList_t *p)
{
  int result; // $v0
  char *curheapbuf1; // $s0
  int curind1; // $s3
  char *usr_name; // $s1
  int type_1; // $a0

  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result >= 0 )
  {
    result = do_read_current_netcnf_nodecode(g_dir_name, &g_count_list_heapptr);
    if ( result > 0 )
    {
      curheapbuf1 = g_count_list_heapptr;
      curind1 = 0;
      if ( *g_count_list_heapptr )
      {
        usr_name = p->usr_name;
        type_1 = type;
        do
        {
          if ( do_type_check(type_1, curheapbuf1) > 0 )
          {
            ++curind1;
            if ( p )
            {
              p->type = type;
              if ( !do_split_str_comma_index(g_arg_fname, curheapbuf1, 1) )
              {
                *((u32 *)usr_name - 65) = strtol(g_arg_fname, 0, 10);
                if ( !do_split_str_comma_index(p->sys_name, curheapbuf1, 2)
                  && !do_split_str_comma_index(usr_name, curheapbuf1, 3) )
                {
                  usr_name += 520;
                  ++p;
                }
              }
            }
          }
          curheapbuf1 = do_check_hoge_newline(curheapbuf1);
          type_1 = type;
        }
        while ( *curheapbuf1 );
      }
      do_free_heapmem(g_count_list_heapptr);
      return curind1;
    }
  }
  return result;
}

//----- (004023F0) --------------------------------------------------------
int do_load_entry_inner(char *fname, int type, char *usr_name, sceNetCnfEnv_t *e)
{
  int result; // $v0
  bool condtmp; // dc
  char *curheapbuf1; // $s0
  int type_1; // $a0

  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result >= 0 )
  {
    result = do_handle_combination_path(type, g_dir_name, g_combination_buf1, 256, usr_name);
    if ( result >= 0 )
    {
      result = do_read_current_netcnf_nodecode(g_dir_name, &g_load_entry_heapptr);
      if ( result >= 0 )
      {
        condtmp = result == 0;
        result = -8;
        if ( !condtmp )
        {
          curheapbuf1 = g_load_entry_heapptr;
          if ( *g_load_entry_heapptr )
          {
            type_1 = type;
            while ( do_type_check(type_1, curheapbuf1) <= 0
                 || do_split_str_comma_index(g_arg_fname, curheapbuf1, 3)
                 || strcmp(g_arg_fname, g_combination_buf1)
                 || do_split_str_comma_index(g_arg_fname, curheapbuf1, 2) )
            {
              curheapbuf1 = do_check_hoge_newline(curheapbuf1);
              type_1 = type;
              if ( !*curheapbuf1 )
                goto LABEL_16;
            }
            do_free_heapmem(g_load_entry_heapptr);
            e->dir_name = g_dir_name;
            e->arg_fname = g_arg_fname;
            if ( type )
              e->req = 2;
            else
              e->req = 1;
            return do_load_conf_inner(e);
          }
          else
          {
LABEL_16:
            do_free_heapmem(g_load_entry_heapptr);
            return -8;
          }
        }
      }
    }
  }
  return result;
}

//----- (00402590) --------------------------------------------------------
void do_some_ifc_handling_hoge(const char *arg_fname)
{
  const char *i; // $s0
  int curi1; // $v1
  char *curptr1; // $s0
  unsigned int curbufsz1; // $s2
  int curindx; // $s1
  bool condtmp1; // dc
  u32 condtmp2; // $v0
  int curbufadd; // $lo

  if ( arg_fname && *arg_fname )
  {
    for ( i = &arg_fname[strlen(arg_fname) - 1]; i >= arg_fname; --i )
    {
      if ( *i == '.' )
        break;
    }
    curi1 = *i;
    curptr1 = (char *)(i - 1);
    if ( curi1 == '.' && curptr1 >= arg_fname )
    {
      curbufsz1 = 0;
      if ( (look_ctype_table(*curptr1) & 4) != 0 )
      {
        curindx = 1;
        while ( 1 )
        {
          condtmp1 = (look_ctype_table(*curptr1) & 4) == 0;
          condtmp2 = curbufsz1 < 0x3E8;
          if ( condtmp1 )
            break;
          curbufadd = curindx * (*curptr1-- - '0');
          curindx *= 10;
          curbufsz1 += curbufadd;
          if ( curptr1 < arg_fname )
          {
            condtmp2 = curbufsz1 < 0x3E8;
            break;
          }
        }
        if ( condtmp2 )
          g_ifc_buffer[curbufsz1] = 1;
      }
    }
  }
}

//----- (004026B0) --------------------------------------------------------
int do_some_pair_handling(char *fpath, int type, const char *src, sceNetCnfEnv_t *e)
{
  int result; // $v0
  sceNetCnfEnv_t *heapmem; // $s1
  int conf_inner; // $v1
  struct sceNetCnfRoot *root; // $v0
  struct sceNetCnfPair *i; // $s0
  const char *attach_ifc; // $a0

  result = do_split_str_comma_index(g_arg_fname, src, 2);
  if ( !result )
  {
    heapmem = (sceNetCnfEnv_t *)do_alloc_heapmem(6256);
    result = 1;
    if ( heapmem )
    {
      heapmem->req = 1;
      heapmem->mem_ptr = &heapmem[1];
      heapmem->mem_base = &heapmem[1];
      heapmem->dir_name = fpath;
      heapmem->arg_fname = g_arg_fname;
      heapmem->mem_last = &heapmem[2].dbuf[848];
      heapmem->f_no_check_magic = e->f_no_check_magic;
      heapmem->f_no_decode = e->f_no_decode;
      heapmem->f_verbose = e->f_verbose;
      conf_inner = do_load_conf_inner(heapmem);
      if ( !conf_inner || conf_inner == -21 )
      {
        root = heapmem->root;
        if ( root )
        {
          for ( i = root->pair_head; i; i = i->forw )
          {
            if ( type == 1 )
            {
              attach_ifc = (const char *)i->attach_ifc;
            }
            else
            {
              if ( type != 2 )
                continue;
              attach_ifc = (const char *)i->attach_dev;
            }
            do_some_ifc_handling_hoge(attach_ifc);
          }
        }
      }
      return do_free_heapmem(heapmem);
    }
  }
  return result;
}

//----- (004027F4) --------------------------------------------------------
int do_add_entry_inner(
        char *fname,
        int type,
        char *usr_name,
        sceNetCnfEnv_t *e,
        char *icon_value,
        char *iconsys_value,
        int no_check_capacity)
{
  int fd_1; // $s3
  int result; // $v0
  int type_1; // $a0
  int retres2; // $s1
  char *curentry1; // $s0
  int i; // $s2
  u32 condtmp1; // $v0
  char *curentry2; // $s0
  int j; // $s2
  u32 condtmp2; // $v0
  char *k; // $s0
  char *endbuf; // $s0
  int endbuf_chr1; // $v1
  int endbuf_hichr1; // $v0
  int endbuf_chr2; // $v0
  bool condtmp3; // dc
  int endbuf_chr3; // $v1
  int nrind; // $s0
  const char *fileext; // $s1
  int fd; // $v0
  char *dirname_buf1; // $s0
  char *cur_entry_buffer; // $s2
  char dirname_chrbeg; // $v1
  char dirname_buf1chr; // $v0
  int req_tmp; // $v0
  size_t pathlen; // $v0
  int strlenx; // $s0
  int writeres; // $s1
  int curatomicnamepath_2; // $s2
  int curindatomicrenamepath_1; // $s2
  int curatomicnamepath_1; // $v0
  u8 fixme_renamepath[16]; // [sp+0h] [-120h] BYREF
  char atomicrenamepath[256]; // [sp+18h] [-108h] BYREF
  int retres1; // [sp+118h] [-8h]

  fd_1 = -1;
  if ( get_check_provider_eq_zero() )
  {
    result = do_check_provider_inner(e, type);
    if ( result < 0 )
      return result;
  }
  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result < 0 )
    return result;
  type_1 = type;
  if ( !no_check_capacity )
  {
    result = do_check_capacity_inner(g_dir_name);
    type_1 = type;
    if ( result < 0 )
      return result;
  }
  atomicrenamepath[0] = 0;
  result = do_handle_combination_path(type_1, g_dir_name, g_combination_buf1, 256, usr_name);
  if ( result < 0 )
    return result;
  result = do_read_current_netcnf_nodecode(g_dir_name, &g_add_entry_heapptr);
  retres1 = result;
  if ( result < 0 )
    return result;
  retres2 = do_remove_old_config(g_dir_name, g_add_entry_heapptr, icon_value, iconsys_value);
  if ( retres2 < 0 )
    goto LABEL_95;
  bzero(g_ifc_buffer, 1000);
  if ( retres1 )
  {
    if ( !strncmp(g_dir_name, "mc", 2) )
    {
      curentry1 = g_add_entry_heapptr;
      for ( i = 0; *curentry1; curentry1 = do_check_hoge_newline(curentry1) )
      {
        if ( do_type_check(type, curentry1) == 1 )
          ++i;
      }
      condtmp1 = i < 6;
      if ( !type || type >= 0 && (condtmp1 = i < 4, type < 3) )
      {
        retres2 = -12;
        if ( !condtmp1 )
          goto LABEL_95;
      }
    }
    if ( !strncmp(g_dir_name, "pfs", 3) )
    {
      curentry2 = g_add_entry_heapptr;
      for ( j = 0; *curentry2; curentry2 = do_check_hoge_newline(curentry2) )
      {
        if ( do_type_check(type, curentry2) == 1 )
          ++j;
      }
      condtmp2 = j < 10;
      if ( !type || type >= 0 && (condtmp2 = j < 30, type < 3) )
      {
        retres2 = -12;
        if ( !condtmp2 )
          goto LABEL_95;
      }
    }
    for ( k = g_add_entry_heapptr; *k; k = do_check_hoge_newline(k) )
    {
      if ( (unsigned int)(type - 1) < 2 && do_type_check(0, k) > 0 )
        do_some_pair_handling(g_dir_name, type, k, e);
      if ( do_type_check(type, k) > 0
        && !do_split_str_comma_index(g_arg_fname, k, 1)
        && strtol(g_arg_fname, 0, 10) == 1
        && !do_split_str_comma_index(g_arg_fname, k, 2) )
      {
        do_some_ifc_handling_hoge(g_arg_fname);
        if ( !do_split_str_comma_index(g_arg_fname, k, 3) && !strcmp(g_combination_buf1, g_arg_fname) )
        {
          do_free_heapmem(g_add_entry_heapptr);
          return -11;
        }
      }
    }
  }
  do_safe_strcpy(g_arg_fname, 256, g_dir_name, 740);
  endbuf = &g_ifc_buffer[strlen(g_arg_fname) + 999];
  if ( endbuf >= g_arg_fname )
  {
    endbuf_chr1 = *endbuf;
    if ( endbuf_chr1 == ':' )
      goto LABEL_50;
    if ( endbuf_chr1 != '/' )
    {
      endbuf_hichr1 = (u8)*endbuf << 24;
      do
      {
        if ( endbuf_hichr1 >> 24 == '\\' )
          break;
        if ( --endbuf < g_arg_fname )
          break;
        endbuf_chr2 = *endbuf;
        if ( endbuf_chr2 == ':' )
          goto LABEL_50;
        condtmp3 = endbuf_chr2 != '/';
        endbuf_hichr1 = (u8)*endbuf << 24;
      }
      while ( condtmp3 );
    }
  }
  endbuf_chr3 = *endbuf;
  if ( endbuf_chr3 != ':' && endbuf_chr3 != '/' && endbuf_chr3 != '\\' )
  {
    *endbuf = 0;
    goto LABEL_52;
  }
LABEL_50:
  endbuf[1] = 0;
LABEL_52:
  if ( type && (nrind = 0, !e->f_no_decode) )
  {
    fileext = ".dat";
  }
  else
  {
    fileext = ".cnf";
    nrind = 0;
  }
  while ( g_ifc_buffer[nrind] )
  {
LABEL_72:
    if ( ++nrind >= 1000 )
      goto LABEL_73;
  }
  if ( type == 1 )
  {
    sprintf(g_netcnf_file_path, "%sifc%03d%s", g_arg_fname, nrind, fileext);
  }
  else if ( type >= 2 )
  {
    if ( type != 2 )
    {
LABEL_67:
      do_free_heapmem(g_add_entry_heapptr);
      return -10;
    }
    sprintf(g_netcnf_file_path, "%sdev%03d%s", g_arg_fname, nrind, fileext);
  }
  else
  {
    if ( type )
      goto LABEL_67;
    sprintf(g_netcnf_file_path, "%snet%03d%s", g_arg_fname, nrind, fileext);
  }
  fd = do_open_netcnf(g_netcnf_file_path, 1, 0);
  fd_1 = fd;
  if ( fd >= 0 )
  {
    do_close_netcnf(fd);
    goto LABEL_72;
  }
  result = -18;
  if ( fd_1 == -5 )
    return result;
LABEL_73:
  retres2 = -12;
  if ( nrind < 1000 )
  {
    dirname_buf1 = g_dir_name;
    cur_entry_buffer = g_entry_buffer;
    dirname_chrbeg = g_dir_name[0];
    if ( g_dir_name[0] )
    {
      while ( 1 )
      {
        if ( dirname_chrbeg == '/' || dirname_chrbeg == '\\' )
        {
          if ( dirname_buf1[1] )
          {
            *cur_entry_buffer = 0;
            retres2 = mkdir(g_entry_buffer, 511);
            if ( !retres2 && !strncmp(g_dir_name, "mc", 2) )
            {
              do_chstat_mode_copyprotect_wrap(g_entry_buffer);
              retres2 = do_write_memcard_files(g_dir_name, icon_value, iconsys_value);
              if ( retres2 < 0 )
                break;
            }
            condtmp3 = retres2 == -5;
            retres2 = -18;
            if ( condtmp3 )
              break;
          }
        }
        dirname_buf1chr = *dirname_buf1++;
        *cur_entry_buffer = dirname_buf1chr;
        dirname_chrbeg = *dirname_buf1;
        ++cur_entry_buffer;
        if ( !*dirname_buf1 )
          goto LABEL_83;
      }
    }
    else
    {
LABEL_83:
      e->dir_name = g_dir_name;
      e->arg_fname = &g_netcnf_file_path[strlen(g_arg_fname)];
      if ( type )
        req_tmp = 2;
      else
        req_tmp = 1;
      e->req = req_tmp;
      retres2 = -1;
      if ( !do_export_netcnf(e) )
      {
        do_safe_make_name(atomicrenamepath, 256, g_dir_name, ".tmp");
        fd_1 = do_open_netcnf(atomicrenamepath, 1538, 511);
        if ( fd_1 >= 0 )
        {
          pathlen = strlen(g_arg_fname);
          strlenx = sprintf(g_entry_buffer, "%d,%d,%s,%s\n", type, 1, &g_netcnf_file_path[pathlen], g_combination_buf1);
          writeres = do_write_netcnf_no_encode(fd_1, g_entry_buffer, strlenx);
          if ( strlenx == writeres
            && (writeres = do_write_netcnf_no_encode(fd_1, g_add_entry_heapptr, retres1), retres1 == writeres) )
          {
            retres2 = 0;
          }
          else
          {
            condtmp3 = writeres != -5;
            retres2 = -5;
            if ( !condtmp3 )
              retres2 = -18;
          }
        }
        else
        {
          retres2 = -3;
          if ( fd_1 == -5 )
            retres2 = -18;
        }
      }
    }
  }
LABEL_95:
  do_free_heapmem(g_add_entry_heapptr);
  if ( fd_1 >= 0 )
    do_close_netcnf(fd_1);
  if ( atomicrenamepath[0] )
  {
    if ( iomanX_rename(atomicrenamepath, g_dir_name) == -5 )
      return -18;
    curatomicnamepath_2 = 0;
    if ( atomicrenamepath[0] != ':' )
    {
      curindatomicrenamepath_1 = 1;
      do
        curatomicnamepath_1 = atomicrenamepath[curindatomicrenamepath_1++];
      while ( curatomicnamepath_1 != ':' );
      curatomicnamepath_2 = curindatomicrenamepath_1 - 1;
    }
    fixme_renamepath[curatomicnamepath_2 + 25] = 0;
  }
  if ( strncmp(g_dir_name, "pfs", 3) )
    return retres2;
  condtmp3 = iomanX_sync(g_dir_name, 0) == -5;
  result = -18;
  if ( !condtmp3 )
    return retres2;
  return result;
}
// 4027F4: using guessed type char atomicrenamepath[256];

//----- (00403070) --------------------------------------------------------
int do_handle_set_usrname(const char *fpath, int type, const char *usrname_buf2, const char *usrname_bufnew)
{
  int result; // $v0
  int retres1; // $s0
  size_t usrnamelen; // $v0
  char *heapmem; // $s2
  char *ptr_1; // $s0
  char *heapmem_1; // $s1
  char ptrchr1; // $v1
  int ptrchr2; // $v0
  char ptrchr3; // $v0
  int writeres1; // $s0
  char *ptr; // [sp+18h] [-8h] BYREF

  ptr = 0;
  if ( !usrname_buf2 )
    return -11;
  result = do_handle_combination_path(type, g_dir_name, g_combination_buf1, 256, (char *)usrname_bufnew);
  if ( result >= 0 )
  {
    result = do_read_current_netcnf_nodecode(fpath, &ptr);
    retres1 = result;
    if ( result <= 0 )
    {
      if ( !result )
        return -3;
      return result;
    }
    usrnamelen = strlen(usrname_bufnew);
    heapmem = (char *)do_alloc_heapmem(retres1 + usrnamelen + 1);
    if ( !heapmem )
    {
      do_free_heapmem(ptr);
      return -2;
    }
    ptr_1 = ptr;
    heapmem_1 = heapmem;
    if ( !*ptr )
    {
LABEL_24:
      do_free_heapmem(ptr);
      writeres1 = do_write_noencode_netcnf_atomic(fpath, heapmem, heapmem_1 - heapmem);
      do_free_heapmem(heapmem);
      return writeres1;
    }
    while ( 1 )
    {
      if ( do_type_check(type, ptr_1) <= 0 || do_split_str_comma_index(g_arg_fname, ptr_1, 3) )
      {
LABEL_19:
        while ( 1 )
        {
          ptrchr1 = *ptr_1;
          if ( !*ptr_1 )
            break;
          if ( ptrchr1 == '\n' )
            goto LABEL_21;
          ++ptr_1;
          *heapmem_1++ = ptrchr1;
        }
        ptrchr2 = *ptr_1;
        if ( ptrchr2 != '\n' )
          goto LABEL_23;
LABEL_21:
        ptrchr3 = *ptr_1++;
        *heapmem_1++ = ptrchr3;
      }
      else
      {
        if ( strcmp(g_arg_fname, usrname_buf2) )
        {
          if ( strcmp(g_arg_fname, g_combination_buf1) )
            goto LABEL_19;
          do_free_heapmem(ptr);
          do_free_heapmem(heapmem);
          return -11;
        }
        if ( do_split_str_comma_index(g_arg_fname, ptr_1, 2) )
          goto LABEL_19;
        heapmem_1 += sprintf(heapmem_1, "%d,%d,%s,%s\n", type, 1, g_arg_fname, g_combination_buf1);
        ptr_1 = do_check_hoge_newline(ptr_1);
      }
      ptrchr2 = *ptr_1;
LABEL_23:
      if ( !ptrchr2 )
        goto LABEL_24;
    }
  }
  return result;
}

//----- (004032CC) --------------------------------------------------------
int do_edit_entry_inner(
        char *fname,
        int type,
        char *usr_name,
        char *new_usr_name,
        sceNetCnfEnv_t *e,
        char *icon_value,
        char *iconsys_value,
        int no_check_capacity)
{
  int result; // $v0
  int rmoldcfgres; // $s1
  char *curentry1; // $s0
  int type_1; // $a0
  int req_tmp; // $v0
  char *curfilepath1end; // $s0
  int curfilepath1chr; // $v0
  bool condtmp1; // dc
  char curentrybuf1[256]; // [sp+18h] [-200h] BYREF
  char curfilepath1[256]; // [sp+118h] [-100h] BYREF

  if ( get_check_provider_eq_zero() )
  {
    result = do_check_provider_inner(e, type);
    if ( result < 0 )
      return result;
  }
  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result < 0 )
    return result;
  if ( !no_check_capacity )
  {
    result = do_check_capacity_inner(g_dir_name);
    if ( result < 0 )
      return result;
  }
  result = do_handle_combination_path(type, g_dir_name, g_combination_buf2, 256, usr_name);
  if ( result < 0 )
    return result;
  result = do_read_current_netcnf_nodecode(g_dir_name, &g_edit_entry_heapptr);
  if ( result <= 0 )
  {
    if ( !result )
      return -3;
    return result;
  }
  rmoldcfgres = do_remove_old_config(g_dir_name, g_edit_entry_heapptr, icon_value, iconsys_value);
  if ( rmoldcfgres >= 0 )
  {
    curentry1 = g_edit_entry_heapptr;
    rmoldcfgres = 0;
    if ( *g_edit_entry_heapptr )
    {
      type_1 = type;
      do
      {
        if ( do_type_check(type_1, curentry1) > 0
          && !do_split_str_comma_index(g_arg_fname, curentry1, 3)
          && !strcmp(g_arg_fname, g_combination_buf2)
          && !do_split_str_comma_index(curentrybuf1, curentry1, 2) )
        {
          ++rmoldcfgres;
        }
        curentry1 = do_check_hoge_newline(curentry1);
        type_1 = type;
      }
      while ( *curentry1 );
    }
    if ( !rmoldcfgres )
    {
      rmoldcfgres = -8;
      goto LABEL_37;
    }
    if ( !get_check_provider_eq_zero() )
      goto LABEL_25;
    if ( !do_handle_netcnf_dirname(g_dir_name, curentrybuf1, curfilepath1) )
    {
      rmoldcfgres = -11;
      goto LABEL_37;
    }
    rmoldcfgres = do_read_check_netcnf(curfilepath1, type, e->f_no_check_magic, e->f_no_decode);
    if ( rmoldcfgres >= 0 )
    {
LABEL_25:
      do_safe_make_name(curfilepath1, 256, curentrybuf1, ".tmp");
      e->dir_name = g_dir_name;
      e->arg_fname = curfilepath1;
      if ( type )
        req_tmp = 2;
      else
        req_tmp = 1;
      e->req = req_tmp;
      if ( do_export_netcnf(e) )
      {
        rmoldcfgres = -1;
      }
      else
      {
        do_safe_strcpy(curfilepath1, 256, g_dir_name, 1010);
        curfilepath1end = &curfilepath1[strlen(curfilepath1)];
        if ( curfilepath1end != curfilepath1 )
        {
          while ( 1 )
          {
            curfilepath1chr = *curfilepath1end;
            if ( curfilepath1chr == '/' || curfilepath1chr == '\\' )
              break;
            if ( --curfilepath1end == curfilepath1 )
              goto LABEL_35;
          }
          curfilepath1end[1] = 0;
        }
LABEL_35:
        do_safe_strcat(curfilepath1, 256, curentrybuf1, 1017);
        do_safe_strcpy(curentrybuf1, 256, curfilepath1, 1018);
        do_safe_strcat(curfilepath1, 256, ".tmp", 1019);
        if ( iomanX_rename(curfilepath1, curentrybuf1) == -5 )
          rmoldcfgres = -18;
      }
    }
  }
LABEL_37:
  do_free_heapmem(g_edit_entry_heapptr);
  if ( rmoldcfgres >= 0 )
  {
    do_set_latest_entry_inner(g_dir_name, type, g_combination_buf2);
    if ( new_usr_name )
      rmoldcfgres = do_handle_set_usrname(g_dir_name, type, g_combination_buf2, new_usr_name);
  }
  condtmp1 = strncmp(g_dir_name, "pfs", 3) != 0;
  result = rmoldcfgres;
  if ( !condtmp1 )
  {
    condtmp1 = iomanX_sync(g_dir_name, 0) != -5;
    result = rmoldcfgres;
    if ( !condtmp1 )
      return -18;
  }
  return result;
}
// 4032CC: using guessed type char curfilepath1[256];

//----- (004036BC) --------------------------------------------------------
size_t do_delete_entry_inner(
        char *fname,
        int type,
        char *usr_name,
        char *icon_value,
        char *iconsys_value,
        int no_check_capacity)
{
  int has_comma; // $s5
  size_t result; // $v0
  char *heapmem; // $s3
  int remove_old_config_res; // $s0
  char *curentry1; // $s0
  char *heapmem_1; // $s1
  int type_1; // $a0
  char curentry1_chr1; // $v1
  int curentry1_chr2; // $v0
  char curentry1_chr3; // $v0
  bool condtmp1; // dc

  has_comma = 0;
  g_delete_entry_heapptr = 0;
  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result >= 0 )
  {
    if ( no_check_capacity || (result = do_check_capacity_inner(g_dir_name), result >= 0) )
    {
      result = do_handle_combination_path(type, g_dir_name, g_combination_buf1, 256, usr_name);
      if ( result >= 0 )
      {
        result = do_read_current_netcnf_nodecode(g_dir_name, &g_delete_entry_heapptr);
        if ( result > 0 )
        {
          heapmem = (char *)do_alloc_heapmem(result);
          if ( heapmem )
          {
            remove_old_config_res = do_remove_old_config(g_dir_name, g_delete_entry_heapptr, icon_value, iconsys_value);
            if ( remove_old_config_res >= 0 )
            {
              curentry1 = g_delete_entry_heapptr;
              heapmem_1 = heapmem;
              if ( *g_delete_entry_heapptr )
              {
                type_1 = type;
                do
                {
                  if ( do_type_check(type_1, curentry1) <= 0
                    || do_split_str_comma_index(g_arg_fname, curentry1, 3)
                    || strcmp(g_arg_fname, g_combination_buf1) )
                  {
                    while ( 1 )
                    {
                      curentry1_chr1 = *curentry1;
                      if ( !*curentry1 )
                        break;
                      if ( curentry1_chr1 == '\n' )
                        goto LABEL_23;
                      ++curentry1;
                      *heapmem_1++ = curentry1_chr1;
                    }
                    curentry1_chr2 = *curentry1;
                    if ( curentry1_chr2 != '\n' )
                      goto LABEL_25;
LABEL_23:
                    curentry1_chr3 = *curentry1++;
                    *heapmem_1++ = curentry1_chr3;
                  }
                  else
                  {
                    if ( !do_split_str_comma_index(g_entry_buffer, curentry1, 2) )
                      has_comma = 1;
                    curentry1 = do_check_hoge_newline(curentry1);
                  }
                  curentry1_chr2 = *curentry1;
LABEL_25:
                  type_1 = type;
                }
                while ( curentry1_chr2 );
              }
              remove_old_config_res = do_write_noencode_netcnf_atomic(g_dir_name, heapmem, heapmem_1 - heapmem);
              if ( remove_old_config_res >= 0 && has_comma )
                remove_old_config_res = do_remove_netcnf_dirname(g_dir_name, g_entry_buffer);
            }
            do_free_heapmem(g_delete_entry_heapptr);
            do_free_heapmem(heapmem);
            condtmp1 = strncmp(g_dir_name, "pfs", 3) != 0;
            result = remove_old_config_res;
            if ( !condtmp1 )
            {
              condtmp1 = iomanX_sync(g_dir_name, 0) != -5;
              result = remove_old_config_res;
              if ( !condtmp1 )
                return -18;
            }
          }
          else
          {
            do_free_heapmem(g_delete_entry_heapptr);
            return -2;
          }
        }
        else if ( !result )
        {
          return -3;
        }
      }
    }
  }
  return result;
}

//----- (00403998) --------------------------------------------------------
size_t do_set_latest_entry_inner(char *fname, int type, char *usr_name)
{
  int isbeforeend1; // $fp
  size_t result; // $v0
  char *heapmem2; // $s4
  size_t readsz; // $s0
  int retres1; // $s3
  char *heapmem1; // $s6
  char *heapmem1_1; // $s2
  char *heapmem2_1; // $s1
  char *curentry1; // $s0
  char curentry1_chr1; // $v1
  u32 condtmp2; // $v0
  char curentry1_chr2; // $v0
  char curentry1_chr3; // $v1
  int curentry1_chr4; // $v0
  char curentry1_chr5; // $v0
  bool condtmp1; // dc

  isbeforeend1 = 0;
  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result >= 0 )
  {
    result = do_handle_combination_path(type, g_dir_name, g_combination_buf1, 256, usr_name);
    heapmem2 = 0;
    if ( result >= 0 )
    {
      g_set_latest_entry_heapptr = 0;
      result = do_read_current_netcnf_nodecode(g_dir_name, &g_set_latest_entry_heapptr);
      readsz = result;
      retres1 = -2;
      if ( result > 0 )
      {
        heapmem1 = (char *)do_alloc_heapmem(result);
        heapmem1_1 = heapmem1;
        if ( heapmem1 )
        {
          heapmem2 = (char *)do_alloc_heapmem(readsz);
          heapmem2_1 = heapmem2;
          if ( heapmem2 )
          {
            curentry1 = g_set_latest_entry_heapptr;
            retres1 = 0;
            if ( *g_set_latest_entry_heapptr )
            {
              do
              {
                if ( do_type_check(type, curentry1) > 0
                  && !do_split_str_comma_index(g_arg_fname, curentry1, 3)
                  && !strcmp(g_arg_fname, g_combination_buf1) )
                {
                  while ( 1 )
                  {
                    curentry1_chr1 = *curentry1;
                    if ( !*curentry1 )
                      break;
                    if ( curentry1_chr1 == '\n' )
                      goto LABEL_17;
                    ++curentry1;
                    *heapmem1_1++ = curentry1_chr1;
                  }
                  condtmp2 = heapmem2 < heapmem2_1;
                  if ( *curentry1 != '\n' )
                    goto LABEL_18;
LABEL_17:
                  curentry1_chr2 = *curentry1++;
                  *heapmem1_1++ = curentry1_chr2;
                  condtmp2 = heapmem2 < heapmem2_1;
LABEL_18:
                  ++retres1;
                  if ( condtmp2 )
                    isbeforeend1 = 1;
                }
                else
                {
                  while ( 1 )
                  {
                    curentry1_chr3 = *curentry1;
                    if ( !*curentry1 )
                      break;
                    if ( curentry1_chr3 == '\n' )
                      goto LABEL_24;
                    ++curentry1;
                    *heapmem2_1++ = curentry1_chr3;
                  }
                  curentry1_chr4 = *curentry1;
                  if ( curentry1_chr4 != '\n' )
                    continue;
LABEL_24:
                  curentry1_chr5 = *curentry1++;
                  *heapmem2_1++ = curentry1_chr5;
                }
                curentry1_chr4 = *curentry1;
              }
              while ( curentry1_chr4 );
            }
            if ( isbeforeend1 )
            {
              bcopy(heapmem2, heapmem1_1, heapmem2_1 - heapmem2);
              retres1 = do_write_noencode_netcnf_atomic(
                          g_dir_name,
                          heapmem1,
                          heapmem1_1 - heapmem1 + heapmem2_1 - heapmem2);
            }
          }
        }
        do_free_heapmem(g_set_latest_entry_heapptr);
        do_free_heapmem(heapmem1);
        do_free_heapmem(heapmem2);
        condtmp1 = strncmp(g_dir_name, "pfs", 3) != 0;
        result = retres1;
        if ( !condtmp1 )
        {
          condtmp1 = iomanX_sync(g_dir_name, 0) != -5;
          result = retres1;
          if ( !condtmp1 )
            return -18;
        }
      }
      else if ( !result )
      {
        return -3;
      }
    }
  }
  return result;
}

//----- (00403C5C) --------------------------------------------------------
int do_delete_all_inner(const char *dev)
{
  const char *devtmp_1; // $a3
  char devtmp_1_curchr; // $a0
  int i; // $t0
  int dfd1; // $s1
  int dfd1_1; // $a0
  int cmpres1; // $v0
  int remove_res1; // $v0
  int result; // $v0
  bool condtmp1; // dc
  const char *devtmp_2; // $a3
  char devtmp_2_curchr; // $a0
  int j; // $t0
  int dfd2; // $s1
  int xretzero; // $v1
  int dfd2_1; // $a0
  int dread_res; // $v0
  int cmpres2; // $v0
  int remove_res2; // $s0
  int rmdir_res1; // $s0
  iox_dirent_t v21; // [sp+10h] [-148h] BYREF

  if ( !strncmp(dev, "mc", 2) )
  {
    devtmp_1 = dev;
    devtmp_1_curchr = *dev;
    for ( i = 0; *devtmp_1 != ':'; ++i )
    {
      ++devtmp_1;
      g_netcnf_file_path[i] = devtmp_1_curchr;
      devtmp_1_curchr = *devtmp_1;
    }
    g_netcnf_file_path[i] = *devtmp_1;
    g_netcnf_file_path[i + 1] = 0;
    do_safe_strcat(g_netcnf_file_path, 256, "/BWNETCNF", 1199);
    dfd1 = do_dopen_wrap(g_netcnf_file_path);
    if ( dfd1 < 0 )
      return 0;
LABEL_5:
    dfd1_1 = dfd1;
    while ( do_dread_wrap(dfd1_1, &v21) > 0 )
    {
      cmpres1 = strcmp(v21.name, ".");
      dfd1_1 = dfd1;
      if ( cmpres1 )
      {
        if ( !strcmp(v21.name, "..") )
          goto LABEL_5;
        do_safe_make_pathname(g_dir_name, 256, g_netcnf_file_path, v21.name);
        remove_res1 = do_remove_wrap(g_dir_name);
        dfd1_1 = dfd1;
        if ( remove_res1 < 0 )
        {
          do_dclose_wrap(dfd1);
          return -7;
        }
      }
    }
    do_dclose_wrap(dfd1);
    condtmp1 = rmdir(g_netcnf_file_path) < 0;
    result = -7;
    if ( !condtmp1 )
      return 0;
  }
  else
  {
    condtmp1 = strncmp(dev, "pfs", 3) != 0;
    result = -17;
    if ( !condtmp1 )
    {
      devtmp_2 = dev;
      devtmp_2_curchr = *dev;
      for ( j = 0; *devtmp_2 != ':'; ++j )
      {
        ++devtmp_2;
        g_netcnf_file_path[j] = devtmp_2_curchr;
        devtmp_2_curchr = *devtmp_2;
      }
      g_netcnf_file_path[j] = *devtmp_2;
      g_netcnf_file_path[j + 1] = 0;
      do_safe_strcat(g_netcnf_file_path, 256, "/etc/network", 1229);
      dfd2 = do_dopen_wrap(g_netcnf_file_path);
      if ( dfd2 >= 0 )
      {
LABEL_20:
        dfd2_1 = dfd2;
        while ( 1 )
        {
          dread_res = do_dread_wrap(dfd2_1, &v21);
          if ( dread_res <= 0 )
            break;
          cmpres2 = strcmp(v21.name, ".");
          dfd2_1 = dfd2;
          if ( cmpres2 )
          {
            if ( !strcmp(v21.name, "..") )
              goto LABEL_20;
            do_safe_make_pathname(g_dir_name, 256, g_netcnf_file_path, v21.name);
            remove_res2 = do_remove_wrap(g_dir_name);
            dfd2_1 = dfd2;
            if ( remove_res2 < 0 )
            {
              do_dclose_wrap(dfd2);
              result = -7;
              if ( remove_res2 == -5 )
                return -18;
              return result;
            }
          }
        }
        if ( dread_res == -5 )
        {
          do_dclose_wrap(dfd2);
          return -18;
        }
        else
        {
          do_dclose_wrap(dfd2);
          rmdir_res1 = rmdir(g_netcnf_file_path);
          if ( rmdir_res1 >= 0 )
          {
            condtmp1 = iomanX_sync(g_netcnf_file_path, 0) == -5;
            result = -18;
            if ( !condtmp1 )
              return 0;
          }
          else
          {
            result = -7;
            if ( rmdir_res1 == -5 )
              return -18;
          }
        }
      }
      else
      {
        xretzero = 0;
        if ( dfd2 == -5 )
          return -18;
        return xretzero;
      }
    }
  }
  return result;
}

//----- (00403FA8) --------------------------------------------------------
int do_check_special_provider_inner(char *fname, int type, char *usr_name, sceNetCnfEnv_t *e)
{
  int result; // $v0
  char *curentry1; // $s1
  int curentcount; // $s0
  int type_1; // $a0
  int retres; // $s0

  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result >= 0 )
  {
    result = do_handle_combination_path(type, g_dir_name, g_combination_buf2, 256, usr_name);
    if ( result >= 0 )
    {
      result = do_read_current_netcnf_nodecode(g_dir_name, &g_check_special_provider_heapptr);
      if ( result > 0 )
      {
        curentry1 = g_check_special_provider_heapptr;
        curentcount = 0;
        if ( *g_check_special_provider_heapptr )
        {
          type_1 = type;
          do
          {
            if ( do_type_check(type_1, curentry1) > 0
              && !do_split_str_comma_index(g_arg_fname, curentry1, 3)
              && !strcmp(g_arg_fname, g_combination_buf2)
              && !do_split_str_comma_index((char *)e->lbuf, curentry1, 2) )
            {
              ++curentcount;
            }
            curentry1 = do_check_hoge_newline(curentry1);
            type_1 = type;
          }
          while ( *curentry1 );
        }
        if ( curentcount )
        {
          if ( do_handle_netcnf_dirname(g_dir_name, (const char *)e->lbuf, (char *)e->dbuf) )
            retres = do_read_check_netcnf((const char *)e->dbuf, type, e->f_no_check_magic, e->f_no_decode);
          else
            retres = -11;
        }
        else
        {
          retres = -8;
        }
        do_free_heapmem(g_check_special_provider_heapptr);
        return retres;
      }
      else if ( !result )
      {
        return -3;
      }
    }
  }
  return result;
}

//----- (00404160) --------------------------------------------------------
char *do_alloc_mem_inner(sceNetCnfEnv_t *e, size_t size, char align)
{
  void *mem_ptr; // $v1
  char *retptrbegin; // $s0
  char *result; // $v0

  // TODO check struct sizes and correct types for callers calling into this function
  mem_ptr = e->mem_ptr;
  if ( mem_ptr
    && (retptrbegin = (char *)(((unsigned int)mem_ptr + (1 << align) - 1) & ~((1 << align) - 1)),
        &retptrbegin[size] < e->mem_last) )
  {
    e->mem_ptr = &retptrbegin[size];
    bzero(retptrbegin, size);
    return retptrbegin;
  }
  else
  {
    result = 0;
    ++e->alloc_err;
  }
  return result;
}

//----- (004041D8) --------------------------------------------------------
const char *do_netcnf_parse_string(sceNetCnfEnv_t *e, const char *e_arg)
{
  u8 *dbuf; // $s3
  const char *argbegin; // $s0
  const char *result; // $v0
  sceNetCnfEnv_t *e_1; // $v0
  int argchr_1; // $s1
  int argchr_7; // $v1
  int argchr_2; // $v0
  bool condtmp1; // dc
  unsigned int argnumchk; // $v0
  int argind_1; // $s2
  char argchr_6; // $v0
  int argchr_3; // $v1
  int i; // $s2
  int argchr_4; // $v1
  int hexnum; // $v0
  int argchr_5; // $v1
  int argchr_8; // $v1

  dbuf = e->dbuf;
  argbegin = e_arg + 1;
  if ( *e_arg != '"' )
    return e_arg;
  if ( e_arg[1] )
  {
    e_1 = e;
    if ( e_arg[1] == '"' )
      goto LABEL_43;
    while ( (char *)e_1 - (char *)e < 1022 )
    {
      argchr_1 = *(u8 *)argbegin++;
      if ( argchr_1 == '\\' )
      {
        argchr_2 = *(u8 *)argbegin;
        condtmp1 = argchr_2 == 0;
        argnumchk = argchr_2 - '0';
        if ( condtmp1 )
        {
          printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
          printf("invalid escape (%s)", e_arg);
          goto LABEL_48;
        }
        argchr_1 = 0;
        if ( argnumchk >= 8 )
        {
          argchr_3 = *(u8 *)argbegin;
          if ( argchr_3 == 'x' || argchr_3 == 'X' )
          {
            ++argbegin;
            argchr_1 = 0;
            if ( (look_ctype_table(*argbegin) & 0x44) == 0 )
            {
              printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
              printf("missing hexa-decimal(%s)", e_arg);
              goto LABEL_48;
            }
            for ( i = 0; i < 2; ++i )
            {
              if ( (look_ctype_table(*argbegin) & 0x44) == 0 )
                break;
              if ( (look_ctype_table(*argbegin) & 4) != 0 )
              {
                argchr_4 = *(u8 *)argbegin++;
                argchr_1 = 16 * argchr_1 + argchr_4 - '0';
              }
              else
              {
                condtmp1 = (look_ctype_table(*argbegin) & 2) == 0;
                hexnum = 16 * argchr_1;
                argchr_5 = *(u8 *)argbegin++;
                argchr_1 = condtmp1 ? hexnum + argchr_5 - '7' : hexnum + argchr_5 - 'W';
              }
            }
          }
          else
          {
            argchr_1 = *(u8 *)argbegin++;
            switch ( argchr_1 )
            {
              case 'a':
                argchr_1 = 7;
                break;
              case 'b':
                argchr_1 = 8;
                break;
              case 'f':
                argchr_1 = 12;
                break;
              case 'n':
                argchr_1 = 10;
                break;
              case 'r':
                argchr_1 = 13;
                break;
              case 't':
                argchr_1 = 9;
                break;
              case 'v':
                argchr_1 = 11;
                break;
              default:
                break;
            }
          }
        }
        else
        {
          argind_1 = 0;
          do
          {
            ++argind_1;
            if ( *(u8 *)argbegin - (unsigned int)'0' >= 8 )
              break;
            argchr_6 = *argbegin++;
            argchr_1 = 8 * argchr_1 + argchr_6 - '0';
          }
          while ( argind_1 < 3 );
        }
      }
      else if ( (unsigned int)(argchr_1 - 129) < 0x1F || (unsigned int)(argchr_1 - 224) < 0x1D )
      {
        argchr_7 = *(u8 *)argbegin;
        if ( (u8)(argchr_7 - 64) < 0xBDu && argchr_7 != 127 )
        {
          *dbuf++ = argchr_1;
          argchr_1 = *argbegin++;
        }
      }
      *dbuf = argchr_1;
      argchr_8 = *(u8 *)argbegin;
      ++dbuf;
      if ( !*argbegin )
        goto LABEL_41;
      e_1 = (sceNetCnfEnv_t *)(dbuf - 1088);
      if ( argchr_8 == '"' )
        break;
    }
  }
  argchr_8 = *(u8 *)argbegin;
LABEL_41:
  if ( argchr_8 != '"' )
  {
    printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
    printf("invalid quote (%s)", e_arg);
    goto LABEL_48;
  }
LABEL_43:
  result = (const char *)e->dbuf;
  if ( !argbegin[1] )
  {
    *dbuf = 0;
    return result;
  }
  printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
  printf("invalid extra chars (%s)", e_arg);
LABEL_48:
  printf("\n");
  result = 0;
  ++e->syntax_err;
  return result;
}

//----- (00404568) --------------------------------------------------------
char *do_alloc_mem_for_write(sceNetCnfEnv_t *e, const char *str)
{
  size_t strsz; // $v0
  char *strptr; // $s0

  strsz = strlen(str);
  strptr = do_alloc_mem_inner(e, strsz + 1, 0);
  if ( !strptr )
    return 0;
  strcpy(strptr, str);
  return strptr;
}

//----- (004045CC) --------------------------------------------------------
char *do_check_e_arg(sceNetCnfEnv_t *e, const char *e_arg)
{
  const char *strptr; // $v0

  strptr = do_netcnf_parse_string(e, e_arg);
  if ( strptr )
    return do_alloc_mem_for_write(e, strptr);
  else
    return 0;
}

//----- (0040460C) --------------------------------------------------------
int do_parse_number(sceNetCnfEnv_t *e, const char *e_arg, int *n_result)
{
  const char *e_arg_1; // $a0
  int curbasex; // $a3
  int curnum; // $a1
  int result; // $v0
  int e_arg_1_chr; // $v1
  int e_arg_1_num; // $v1

  e_arg_1 = e_arg;
  curbasex = 10;
  if ( *e_arg == '0' && e_arg[1] )
  {
    e_arg_1 = e_arg + 1;
    curbasex = 8;
    if ( e_arg[1] == 'x' )
    {
      e_arg_1 = e_arg + 2;
      curbasex = 16;
    }
  }
  curnum = 0;
  if ( *e_arg_1 )
  {
    while ( 1 )
    {
      e_arg_1_chr = *(u8 *)e_arg_1;
      if ( e_arg_1_chr - (unsigned int)'0' >= 0xA )
      {
        if ( e_arg_1_chr - (unsigned int)'a' >= 6 )
          break;
        e_arg_1_num = (char)e_arg_1_chr - 'W';
      }
      else
      {
        e_arg_1_num = (char)e_arg_1_chr - '0';
      }
      if ( e_arg_1_num >= curbasex )
        break;
      ++e_arg_1;
      curnum = curnum * curbasex + e_arg_1_num;
      if ( !*e_arg_1 )
      {
        *n_result = curnum;
        return 0;
      }
    }
  }
  printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
  printf("invalid digit (%s)", e_arg);
  printf("\n");
  result = -1;
  ++e->syntax_err;
  return result;
}

//----- (00404738) --------------------------------------------------------
int do_netcnfname2address_wrap(sceNetCnfEnv_t *e, char *buf, sceNetCnfAddress_t *paddr)
{
  int errret; // $s0
  int result; // $v0

  errret = sceNetCnfName2Address(paddr, buf);
  result = 0;
  if ( errret < 0 )
  {
    printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
    printf("sceNetCnfName2Address(%s) -> %d\n", buf, errret);
    printf("\n");
    result = -1;
    ++e->syntax_err;
  }
  return result;
}

//----- (004047CC) --------------------------------------------------------
int do_parse_phone_stuff(sceNetCnfEnv_t *e, int opt_argc, const char **opt_argv, int *p_result)
{
  int opt_argc_1; // $s2
  int bitflags1; // $s0
  bool condtmp1; // dc
  int bitflagstmpx; // $v0
  int numval; // [sp+10h] [-8h] BYREF

  opt_argc_1 = opt_argc;
  bitflags1 = 0;
  if ( opt_argc > 0 )
  {
    while ( strcmp("phase", *opt_argv) )
    {
      if ( !strcmp("cp", *opt_argv) )
      {
        bitflags1 |= 2u;
        goto LABEL_22;
      }
      if ( !strcmp("auth", *opt_argv) )
      {
        bitflags1 |= 4u;
        goto LABEL_22;
      }
      if ( !strcmp("chat", *opt_argv) )
      {
        bitflags1 |= 8u;
        goto LABEL_22;
      }
      if ( !strcmp("private", *opt_argv) )
      {
        bitflags1 |= 0x10u;
        goto LABEL_22;
      }
      if ( !strcmp("dll", *opt_argv) )
      {
        bitflags1 |= 0x20u;
        goto LABEL_22;
      }
      if ( !strcmp("dump", *opt_argv) )
      {
        bitflags1 |= 0x40u;
        goto LABEL_22;
      }
      condtmp1 = strcmp("timer", *opt_argv) == 0;
      bitflagstmpx = 0x10000;
      if ( condtmp1 )
        goto LABEL_21;
      if ( !strcmp("event", *opt_argv) )
      {
        bitflagstmpx = 0x20000;
LABEL_21:
        bitflags1 |= bitflagstmpx;
LABEL_22:
        --opt_argc_1;
        goto LABEL_23;
      }
      --opt_argc_1;
      if ( do_parse_number(e, *opt_argv, &numval) )
        return -1;
LABEL_23:
      ++opt_argv;
      if ( opt_argc_1 <= 0 )
        goto LABEL_24;
    }
    bitflags1 |= 1u;
    goto LABEL_22;
  }
LABEL_24:
  *p_result = bitflags1;
  return 0;
}

//----- (0040498C) --------------------------------------------------------
int do_check_interface_keyword(
        sceNetCnfEnv_t *e,
        const char *display_name_arg,
        const char *attach_ifc_arg,
        const char *attach_dev_arg)
{
  struct sceNetCnfPair *cnfpair1; // $s0
  char *str_display_name; // $v0
  char *str_attach_ifc; // $v0
  char *str_attach_dev; // $v0
  int result; // $v0
  struct sceNetCnfPair *pair_tail; // $v0

  cnfpair1 = (struct sceNetCnfPair *)do_alloc_mem_inner(e, 40, 2);
  if ( !cnfpair1 )
    return -1;
  str_display_name = do_check_e_arg(e, display_name_arg);
  cnfpair1->display_name = (u8 *)str_display_name;
  if ( !str_display_name )
    return -1;
  str_attach_ifc = do_check_e_arg(e, attach_ifc_arg);
  cnfpair1->attach_ifc = (u8 *)str_attach_ifc;
  if ( !str_attach_ifc )
    return -1;
  if ( attach_dev_arg )
  {
    if ( *attach_dev_arg )
    {
      str_attach_dev = do_check_e_arg(e, attach_dev_arg);
      cnfpair1->attach_dev = (u8 *)str_attach_dev;
      if ( !str_attach_dev )
        return -1;
    }
  }
  pair_tail = e->root->pair_tail;
  cnfpair1->back = pair_tail;
  if ( !pair_tail )
    pair_tail = (struct sceNetCnfPair *)e->root;
  pair_tail->forw = cnfpair1;
  cnfpair1->forw = 0;
  result = 0;
  e->root->pair_tail = cnfpair1;
  return result;
}

//----- (00404A78) --------------------------------------------------------
int do_check_nameserver(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc, int opt_argc, char **opt_argv)
{
  int addordel; // $s1
  int result; // $v0
  struct sceNetCnfCommand *nameservermem_1; // $v0
  struct sceNetCnfCommand *nameservermem_2; // $s0
  struct sceNetCnfCommand *cmd_tail; // $v0

  if ( opt_argc < 3 )
    return 0;
  addordel = 1;
  if ( strcmp("add", opt_argv[1]) )
  {
    addordel = 2;
    if ( strcmp("del", opt_argv[1]) )
      return 0;
  }
  nameservermem_1 = (struct sceNetCnfCommand *)do_alloc_mem_inner(e, 32, 2);
  nameservermem_2 = nameservermem_1;
  if ( !nameservermem_1 )
    return -1;
  nameservermem_1->code = addordel;
  if ( do_netcnfname2address_wrap(e, opt_argv[2], (sceNetCnfAddress_t *)&nameservermem_1[1]) )
    return -1;
  cmd_tail = ifc->cmd_tail;
  nameservermem_2->back = cmd_tail;
  if ( cmd_tail )
    cmd_tail->forw = nameservermem_2;
  else
    ifc->cmd_head = nameservermem_2;
  result = 0;
  nameservermem_2->forw = 0;
  ifc->cmd_tail = nameservermem_2;
  return result;
}

//----- (00404B6C) --------------------------------------------------------
int do_check_route(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc, int opt_argc, char **opt_argv)
{
  int addordel; // $s0
  bool condres1; // dc
  int result; // $v0
  struct sceNetCnfCommand *route_mem_1; // $v0
  struct sceNetCnfCommand *route_mem_2; // $s4
  int argc_minus_two; // $s3
  const char **argv_plus_two; // $s1
  unsigned int routetmp1; // $v0
  int argcx1; // $s3
  const char **argvx1; // $s1
  char **argvx2; // $s0
  struct sceNetCnfCommand *cmd_tail; // $v0

  if ( opt_argc < 3 )
    return 0;
  addordel = 3;
  if ( strcmp("add", opt_argv[1]) )
  {
    condres1 = strcmp("del", opt_argv[1]) != 0;
    result = 0;
    if ( condres1 )
      return result;
    addordel = 4;
  }
  route_mem_1 = (struct sceNetCnfCommand *)do_alloc_mem_inner(e, 96, 2);
  route_mem_2 = route_mem_1;
  argc_minus_two = opt_argc - 2;
  if ( !route_mem_1 )
    return -1;
  argv_plus_two = (const char **)(opt_argv + 2);
  route_mem_1->code = addordel;
  if ( !strcmp("-net", *argv_plus_two) )
  {
    --argc_minus_two;
    ++argv_plus_two;
    routetmp1 = (int)route_mem_2[6].forw & 0xFFFFFFFD;
LABEL_10:
    route_mem_2[6].forw = (struct sceNetCnfCommand *)routetmp1;
    goto LABEL_11;
  }
  if ( !strcmp("-host", *argv_plus_two) )
  {
    --argc_minus_two;
    ++argv_plus_two;
    routetmp1 = (int)route_mem_2[6].forw | 2;
    goto LABEL_10;
  }
LABEL_11:
  if ( argc_minus_two <= 0 )
    return 0;
  condres1 = do_netcnfname2address_wrap(e, 0, (sceNetCnfAddress_t *)&route_mem_2[1]) != 0;
  result = -1;
  if ( !condres1 )
  {
    condres1 = do_netcnfname2address_wrap(e, 0, (sceNetCnfAddress_t *)&route_mem_2[2].code) != 0;
    result = -1;
    if ( !condres1 )
    {
      condres1 = do_netcnfname2address_wrap(e, 0, (sceNetCnfAddress_t *)&route_mem_2[4].back) != 0;
      result = -1;
      if ( !condres1 )
      {
        if ( !strcmp("default", *argv_plus_two)
          || (condres1 = do_netcnfname2address_wrap(e, (char *)*argv_plus_two, (sceNetCnfAddress_t *)&route_mem_2[1]) != 0,
              result = -1,
              !condres1) )
        {
          argcx1 = argc_minus_two - 1;
          argvx1 = argv_plus_two + 1;
          if ( argcx1 >= 2 )
          {
            argvx2 = (char **)(argvx1 + 1);
            do
            {
              if ( !strcmp("gw", *argvx1) )
              {
                condres1 = do_netcnfname2address_wrap(e, *argvx2, (sceNetCnfAddress_t *)&route_mem_2[2].code) != 0;
                result = -1;
                if ( condres1 )
                  return result;
                route_mem_2[6].forw = (struct sceNetCnfCommand *)((int)route_mem_2[6].forw | 4);
              }
              else if ( !strcmp("netmask", *argvx1) )
              {
                condres1 = do_netcnfname2address_wrap(e, *argvx2, (sceNetCnfAddress_t *)&route_mem_2[4].back) != 0;
                result = -1;
                if ( condres1 )
                  return result;
              }
              argcx1 -= 2;
              argvx2 += 2;
              argvx1 += 2;
            }
            while ( argcx1 >= 2 );
          }
          cmd_tail = ifc->cmd_tail;
          route_mem_2->back = cmd_tail;
          if ( cmd_tail )
            cmd_tail->forw = route_mem_2;
          else
            ifc->cmd_head = route_mem_2;
          result = 0;
          route_mem_2->forw = 0;
          ifc->cmd_tail = route_mem_2;
        }
      }
    }
  }
  return result;
}

//----- (00404DE0) --------------------------------------------------------
const char *do_init_ifc_inner(sceNetCnfInterface_t *ifc)
{
  struct netcnf_option *curentry1; // $a2

  curentry1 = g_options_attach_cnf;
  if ( curentry1->m_key )
  {
    do
    {
      switch ( curentry1->m_type )
      {
        case '1':
        case 'b':
        case 'c':
          *((char *)ifc + curentry1->m_offset) = -1;
          break;
        case '4':
        case 'D':
        case 'L':
        case 'P':
        case 'T':
          *(u32 *)((char *)ifc + curentry1->m_offset) = -1;
          break;
        default:
          break;
      }
      ++curentry1;
    }
    while ( curentry1->m_key );
  }
  return 0;
}

//----- (00404E74) --------------------------------------------------------
int do_check_args(sceNetCnfEnv_t *e, struct sceNetCnfUnknownList *unknown_list)
{
  int lenx1; // $s1
  int curindx1; // $s0
  sceNetCnfEnv_t *e_tmp2; // $s2
  const char *avtmp1; // $a0
  struct sceNetCnfUnknown *listtmp; // $s4
  struct sceNetCnfUnknown *cpydst_1; // $s2
  int result; // $v0
  int cuindx2; // $s0
  sceNetCnfEnv_t *e_tmp1; // $s3
  size_t cpysz; // $v0
  struct sceNetCnfUnknown *cpydst; // $a1
  char *cpydst_curptr; // $s2
  char *cpysrc; // $a0
  struct sceNetCnfUnknown *tail; // $v0

  lenx1 = 0;
  curindx1 = 0;
  if ( e->ac > 0 )
  {
    e_tmp2 = e;
    do
    {
      avtmp1 = e_tmp2->av[0];
      e_tmp2 = (sceNetCnfEnv_t *)((char *)e_tmp2 + 4);
      ++curindx1;
      lenx1 += 3 + strlen(avtmp1);
    }
    while ( curindx1 < e->ac );
  }
  listtmp = (struct sceNetCnfUnknown *)do_alloc_mem_inner(e, lenx1 + 8, 2);
  cpydst_1 = listtmp + 1;
  if ( !listtmp )
    return -1;
  cuindx2 = 0;
  if ( e->ac > 0 )
  {
    e_tmp1 = e;
    do
    {
      cpysz = strlen(e_tmp1->av[0]);
      cpydst = cpydst_1;
      cpydst_curptr = (char *)cpydst_1 + cpysz;
      cpysrc = e_tmp1->av[0];
      e_tmp1 = (sceNetCnfEnv_t *)((char *)e_tmp1 + 4);
      bcopy(cpysrc, cpydst, cpysz);
      *cpydst_curptr = 32 * (cuindx2++ < e->ac - 1);
      cpydst_1 = (struct sceNetCnfUnknown *)(cpydst_curptr + 1);
    }
    while ( cuindx2 < e->ac );
  }
  tail = unknown_list->tail;
  listtmp->back = tail;
  if ( tail )
    tail->forw = listtmp;
  else
    unknown_list->head = listtmp;
  result = 0;
  listtmp->forw = 0;
  unknown_list->tail = listtmp;
  return result;
}

//----- (00404FC0) --------------------------------------------------------
int do_check_other_keywords(
        sceNetCnfEnv_t *e,
        struct netcnf_option *options,
        void *cnfdata,
        struct sceNetCnfUnknownList *unknown_list)
{
  struct netcnf_option *options_1; // $s4
  const char *cur_avx; // $s2
  int has_flagged; // $s3
  int result; // $v0
  const char **p_m_key; // $s0
  bool condtmp1; // dc
  int authtypenum; // $v0
  int conntypenum; // $v0
  int condtmp2; // $v0
  sceNetCnfEnv_t *e_tmp1; // $a0
  int condtmp3; // $v0
  int m_offset; // $v0
  char numvalx; // $v1
  int loginhashx; // $v0
  char *e_arg_chkres; // $v0
  int parseres; // $v0
  int condtmp4; // $v0
  int numval[2]; // [sp+10h] [-8h] BYREF

  options_1 = options;
  cur_avx = (const char *)e->av[0];
  if ( *cur_avx == '-' )
  {
    ++cur_avx;
    has_flagged = 1;
  }
  else
  {
    has_flagged = 0;
  }
  result = 0;
  if ( *cur_avx )
  {
    p_m_key = &options->m_key;
    if ( !options->m_key )
      return do_check_args(e, unknown_list);
    do
    {
      if ( !strcmp(cur_avx, *p_m_key) )
        break;
      p_m_key += 3;
      ++options_1;
    }
    while ( *p_m_key );
    if ( !options_1->m_key )
      return do_check_args(e, unknown_list);
    switch ( options_1->m_type )
    {
      case '1':
        loginhashx = 255;
        if ( has_flagged )
          goto LABEL_82;
        if ( e->ac >= 2 && !do_parse_number(e, e->av[1], numval) )
          goto LABEL_83;
        goto LABEL_87;
      case '4':
        conntypenum = -1;
        if ( has_flagged )
          goto LABEL_99;
        if ( e->ac < 2 || do_parse_number(e, e->av[1], numval) )
          goto LABEL_87;
        goto LABEL_100;
      case 'A':
        if ( has_flagged )
          goto LABEL_38;
        if ( e->ac < 2 )
          goto LABEL_87;
        if ( !strcmp("any", (const char *)e->av[1]) )
        {
          numval[0] = 0;
          goto LABEL_37;
        }
        condtmp1 = strcmp("pap", (const char *)e->av[1]) == 0;
        authtypenum = 1;
        if ( condtmp1 )
          goto LABEL_36;
        condtmp1 = strcmp("chap", (const char *)e->av[1]) == 0;
        authtypenum = 2;
        if ( condtmp1 )
          goto LABEL_36;
        condtmp1 = strcmp("pap/chap", (const char *)e->av[1]) == 0;
        authtypenum = 3;
        if ( condtmp1 )
          goto LABEL_36;
        if ( !strcmp("chap/pap", (const char *)e->av[1]) )
        {
          authtypenum = 4;
LABEL_36:
          numval[0] = authtypenum;
        }
        else
        {
          condtmp1 = do_parse_number(e, e->av[1], numval) == 0;
          result = -1;
          if ( !condtmp1 )
            return result;
        }
LABEL_37:
        *((u8 *)cnfdata + options_1->m_offset) = numval[0];
LABEL_38:
        if ( !strcmp("want.auth", (const char *)e->av[0]) )
          *((u8 *)cnfdata + 171) = has_flagged == 0;
        else
          *((u8 *)cnfdata + 247) = has_flagged == 0;
        return 0;
      case 'C':
        if ( has_flagged )
          goto LABEL_22;
        if ( e->ac < 2 || do_parse_number(e, e->av[1], numval) )
          goto LABEL_87;
        *(u32 *)((char *)cnfdata + options_1->m_offset) = numval[0];
LABEL_22:
        if ( !strcmp("want.accm", (const char *)e->av[0]) )
          *((u8 *)cnfdata + 170) = has_flagged == 0;
        else
          *((u8 *)cnfdata + 246) = has_flagged == 0;
        return 0;
      case 'D':
        conntypenum = -1;
        if ( has_flagged )
          goto LABEL_99;
        if ( e->ac < 2 )
          goto LABEL_87;
        if ( !strcmp("tone", (const char *)e->av[1]) )
          goto LABEL_44;
        condtmp1 = strcmp("pulse", (const char *)e->av[1]) == 0;
        conntypenum = 1;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp2 = strcmp("any", (const char *)e->av[1]);
        e_tmp1 = e;
        if ( condtmp2 )
          goto LABEL_95;
        conntypenum = 2;
        goto LABEL_99;
      case 'L':
        conntypenum = -1;
        if ( has_flagged )
          goto LABEL_99;
        parseres = do_parse_phone_stuff(e, e->ac - 1, (const char **)&e->av[1], numval);
        goto LABEL_96;
      case 'M':
        if ( has_flagged )
          goto LABEL_15;
        if ( e->ac < 2 || do_parse_number(e, e->av[1], numval) )
          goto LABEL_87;
        *(u16 *)((char *)cnfdata + options_1->m_offset) = numval[0];
LABEL_15:
        if ( !strcmp("want.mru", (const char *)e->av[0]) )
          *((u8 *)cnfdata + 169) = has_flagged == 0;
        else
          *((u8 *)cnfdata + 245) = has_flagged == 0;
        return 0;
      case 'P':
        conntypenum = -1;
        if ( has_flagged )
          goto LABEL_99;
        if ( e->ac < 2 )
          goto LABEL_87;
        condtmp1 = strcmp("auto", (const char *)e->av[1]) == 0;
        conntypenum = 1;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp1 = strcmp("10", (const char *)e->av[1]) == 0;
        conntypenum = 2;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp1 = strcmp("10_fd", (const char *)e->av[1]) == 0;
        conntypenum = 3;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp1 = strcmp("10_fd_pause", (const char *)e->av[1]) == 0;
        conntypenum = 4;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp1 = strcmp("tx", (const char *)e->av[1]) == 0;
        conntypenum = 5;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp1 = strcmp("tx_fd", (const char *)e->av[1]) == 0;
        conntypenum = 6;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp4 = strcmp("tx_fd_pause", (const char *)e->av[1]);
        e_tmp1 = e;
        if ( condtmp4 )
          goto LABEL_95;
        conntypenum = 7;
        goto LABEL_99;
      case 'T':
        conntypenum = -1;
        if ( has_flagged )
          goto LABEL_99;
        if ( e->ac < 2 )
          goto LABEL_87;
        if ( !strcmp("any", (const char *)e->av[1]) )
        {
LABEL_44:
          numval[0] = 0;
LABEL_100:
          *(u32 *)((char *)cnfdata + options_1->m_offset) = numval[0];
          return 0;
        }
        condtmp1 = strcmp("eth", (const char *)e->av[1]) == 0;
        conntypenum = 1;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp1 = strcmp("ppp", (const char *)e->av[1]) == 0;
        conntypenum = 2;
        if ( condtmp1 )
          goto LABEL_99;
        condtmp3 = strcmp("nic", (const char *)e->av[1]);
        e_tmp1 = e;
        if ( !condtmp3 )
        {
          conntypenum = 3;
LABEL_99:
          numval[0] = conntypenum;
          goto LABEL_100;
        }
LABEL_95:
        parseres = do_parse_number(e_tmp1, e_tmp1->av[1], numval);
LABEL_96:
        condtmp1 = parseres == 0;
        result = -1;
        if ( condtmp1 )
          goto LABEL_100;
        break;
      case 'b':
        m_offset = options_1->m_offset;
        numvalx = has_flagged == 0;
        goto LABEL_84;
      case 'c':
        loginhashx = 255;
        if ( has_flagged )
          goto LABEL_82;
        if ( e->ac < 2 )
          goto LABEL_87;
        if ( !strcmp("no", (const char *)e->av[1]) )
        {
          numval[0] = 0;
          goto LABEL_83;
        }
        condtmp1 = strcmp("md5", (const char *)e->av[1]) == 0;
        loginhashx = 5;
        if ( condtmp1 )
          goto LABEL_82;
        condtmp1 = strcmp("ms", (const char *)e->av[1]) == 0;
        loginhashx = 128;
        if ( condtmp1 )
          goto LABEL_82;
        condtmp1 = strcmp("ms-v1", (const char *)e->av[1]) == 0;
        loginhashx = 128;
        if ( condtmp1 )
          goto LABEL_82;
        if ( !strcmp("ms-v2", (const char *)e->av[1]) )
        {
          loginhashx = 129;
LABEL_82:
          numval[0] = loginhashx;
        }
        else
        {
          condtmp1 = do_parse_number(e, e->av[1], numval) == 0;
          result = -1;
          if ( !condtmp1 )
            return result;
        }
LABEL_83:
        m_offset = options_1->m_offset;
        numvalx = numval[0];
LABEL_84:
        *((u8 *)cnfdata + m_offset) = numvalx;
        return 0;
      case 'p':
        if ( has_flagged )
        {
          *(u32 *)((char *)cnfdata + options_1->m_offset) = 0;
        }
        else
        {
          if ( e->ac < 2 )
          {
LABEL_87:
            printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
            printf("ac=%d", e->ac);
            printf("\n");
            result = -1;
            ++e->syntax_err;
            return result;
          }
          e_arg_chkres = do_check_e_arg(e, e->av[1]);
          *(char **)((char *)cnfdata + options_1->m_offset) = e_arg_chkres;
          if ( !e_arg_chkres )
            return -1;
        }
        return 0;
      default:
        return printf("netcnf: internal load err (%d, type=%c)\n", 606, options_1->m_type);
    }
  }
  return result;
}

//----- (0040575C) --------------------------------------------------------
int do_handle_net_cnf(sceNetCnfEnv_t *e)
{
  char *av_tmp; // $s0
  int wasprefixxed; // $s2
  int result; // $v0
  int ac; // $v1
  const char *attach_devarg; // $a3
  bool retres1; // dc

  av_tmp = e->av[0];
  wasprefixxed = 0;
  if ( *av_tmp == '-' )
  {
    ++av_tmp;
    wasprefixxed = 1;
  }
  if ( strcmp("interface", av_tmp) )
  {
    if ( strcmp("zero_prefix", av_tmp) )
      return do_check_other_keywords(e, g_options_net_cnf, e->root, &e->root->unknown_list);
    printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
    printf("obsoleted keyword (%s)", av_tmp);
    printf("\n");
    ++e->syntax_err;
    return 0;
  }
  result = 0;
  if ( wasprefixxed )
    return result;
  ac = e->ac;
  if ( ac < 3 )
  {
    printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
    printf("ac=%d", e->ac);
    printf("\n");
    result = -1;
    ++e->syntax_err;
    return result;
  }
  attach_devarg = 0;
  if ( ac >= 4 )
    attach_devarg = e->av[3];
  retres1 = do_check_interface_keyword(e, e->av[1], e->av[2], attach_devarg) == 0;
  result = -1;
  if ( retres1 )
    return 0;
  return result;
}

//----- (004058E0) --------------------------------------------------------
int do_handle_attach_cnf(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc)
{
  char *curkey; // $s0
  int wasprefixed; // $s2
  int keyasnum; // $s0
  bool condtmp1; // dc
  int result; // $v0
  u8 *eargext; // $a0

  curkey = (char *)e->av[0];
  if ( *curkey == '-' )
  {
    ++curkey;
    wasprefixed = 1;
  }
  else
  {
    wasprefixed = 0;
  }
  if ( !strncmp("phone_number", curkey, 12) )
  {
    if ( curkey[12] )
    {
      condtmp1 = (look_ctype_table(curkey[12]) & 4) == 0;
      result = 0;
      if ( condtmp1 )
        return result;
      result = 0;
      if ( curkey[13] )
        return result;
      keyasnum = curkey[12] - 48;
    }
    else
    {
      keyasnum = 0;
    }
    if ( wasprefixed )
    {
      ifc->phone_numbers[keyasnum] = 0;
      return 0;
    }
    result = 0;
    if ( e->ac >= 2 )
    {
      eargext = (u8 *)do_check_e_arg(e, e->av[1]);
      result = -1;
      ifc->phone_numbers[keyasnum] = eargext;
      if ( eargext )
        return 0;
    }
  }
  else if ( !strcmp("nameserver", curkey) )
  {
    result = 0;
    if ( !wasprefixed )
      return do_check_nameserver(e, ifc, e->ac, (char **)e->av);
  }
  else
  {
    if ( strcmp("route", curkey) )
    {
      if ( strcmp("zero_prefix", curkey) && strcmp("dial_cnf", curkey) )
        return do_check_other_keywords(e, g_options_attach_cnf, ifc, &ifc->unknown_list);
      printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
      printf("obsoleted keyword (%s)", curkey);
      printf("\n");
      ++e->syntax_err;
      return 0;
    }
    result = 0;
    if ( !wasprefixed )
      return do_check_route(e, ifc, e->ac, (char **)e->av);
  }
  return result;
}

//----- (00405B08) --------------------------------------------------------
int do_handle_dial_cnf(sceNetCnfEnv_t *e, struct sceNetCnfDial *dial)
{
  const char *av_tmp; // $a1
  int wasprefixed; // $s1
  int result; // $v0
  u8 *tone_dial1; // $v0
  u8 *pulse_dial1; // $v0
  u8 *any_dial1; // $v0

  av_tmp = (const char *)e->av[0];
  wasprefixed = 0;
  if ( *av_tmp == '-' )
  {
    ++av_tmp;
    wasprefixed = 1;
  }
  if ( strcmp("dialing_type_string", av_tmp) )
    return do_check_other_keywords(e, g_options_dial_cnf, dial, &dial->unknown_list);
  result = 0;
  if ( !wasprefixed )
  {
    result = 0;
    if ( e->ac >= 2 )
    {
      tone_dial1 = (u8 *)do_check_e_arg(e, e->av[1]);
      dial->tone_dial = tone_dial1;
      if ( !tone_dial1 )
        return -1;
      result = 0;
      if ( e->ac < 3 )
        return result;
      pulse_dial1 = (u8 *)do_check_e_arg(e, e->av[2]);
      dial->pulse_dial = pulse_dial1;
      if ( pulse_dial1 )
      {
        result = 0;
        if ( e->ac >= 4 )
        {
          any_dial1 = (u8 *)do_check_e_arg(e, e->av[3]);
          dial->any_dial = any_dial1;
          if ( any_dial1 )
            return 0;
          else
            return -1;
        }
      }
      else
      {
        return -1;
      }
    }
  }
  return result;
}

//----- (00405C24) --------------------------------------------------------
int do_check_line_buffer(sceNetCnfEnv_t *e, u8 *lbuf, int (*readcb)(int, int), void *userdata)
{
  u8 *i; // $s0
  char *j; // $s0
  int j_curchr1; // $a0
  int ac; // $v1
  int j_curchr2; // $v0
  u32 condtmp1; // $s1

  for ( i = lbuf; e->lbuf < i; --i )
  {
    if ( *(i - 1) >= 0x21u )
      break;
  }
  *i = 0;
  for ( j = (char *)e->lbuf; *j; ++j )
  {
    if ( (look_ctype_table(*j) & 8) == 0 )
      break;
  }
  e->ac = 0;
  j_curchr1 = (u8)*j;
  while ( *j )
  {
    ac = e->ac;
    if ( ac >= '\n' || j_curchr1 == '#' )
      break;
    e->av[ac] = j;
    j_curchr2 = (u8)*j;
    condtmp1 = 0;
    if ( *j )
    {
      if ( j_curchr2 == '#' )
        goto LABEL_26;
LABEL_12:
      if ( (look_ctype_table(*j) & 8) != 0 )
      {
LABEL_24:
        j_curchr2 = (u8)*j;
      }
      else
      {
        j_curchr2 = (u8)*j;
        while ( 1 )
        {
          if ( j_curchr2 == '\\' )
          {
            if ( j[1] )
              ++j;
          }
          else if ( condtmp1 )
          {
            if ( j_curchr2 == '"' )
              condtmp1 = 0;
          }
          else
          {
            condtmp1 = j_curchr2 == '"';
          }
          j_curchr2 = (u8)*++j;
          if ( !*j )
            break;
          if ( !condtmp1 )
          {
            if ( j_curchr2 != 35 )
              goto LABEL_12;
            goto LABEL_24;
          }
        }
      }
    }
    if ( j_curchr2 == '#' )
    {
LABEL_26:
      *j = 0;
      break;
    }
    if ( j_curchr2 )
    {
      *j = 0;
      do
        ++j;
      while ( *j && (look_ctype_table(*j) & 8) != 0 );
    }
    ++e->ac;
    j_curchr1 = (u8)*j;
  }
  *j = 0;
  if ( e->ac <= 0 )
    return 0;
  else
    return readcb((int)e, (int)userdata);
}

//----- (00405E88) --------------------------------------------------------
int do_read_netcnf(sceNetCnfEnv_t *e, const char *netcnf_path, char **netcnf_heap_ptr, int is_attach_cnf)
{
  int result; // $v0

  if ( !is_attach_cnf || e->f_no_decode )
    result = do_read_netcnf_no_decode(netcnf_path, netcnf_heap_ptr);
  else
    result = do_read_netcnf_decode(netcnf_path, netcnf_heap_ptr);
  if ( result < 0 )
    ++e->file_err;
  return result;
}

//----- (00405EF4) --------------------------------------------------------
char *do_handle_netcnf_prerw(sceNetCnfEnv_t *e, const char *entry_buffer)
{
  u8 *lbuf; // $s0
  char *result; // $v0

  lbuf = e->lbuf;
  result = do_handle_netcnf_dirname(e->dir_name, entry_buffer, (char *)e->lbuf);
  if ( result == (char *)lbuf )
    return do_alloc_mem_for_write(e, result);
  return result;
}

//----- (00405F3C) --------------------------------------------------------
int do_netcnf_read_related(sceNetCnfEnv_t *e, const char *path, int (*readcb)(), void *userdata)
{
  int cur_linelen; // $s4
  char *dir_name_or_null; // $a1
  const char *path_or_null; // $a2
  char *fullpath; // $s0
  int result; // $v0
  const char *dial_cnf_or_unk; // $a0
  int read_res1; // $v0
  int read_res2; // $s1
  u8 *lbuf; // $s0
  char *ptr_1; // $s2
  int f_no_check_magic; // $v0
  bool condtmp1; // dc
  int read_res3; // $v0
  int curchind; // $s0
  u32 condtmp2; // $v0
  char *curptr_1; // $v1
  int curchr; // $a1
  int curresptrx; // $s1
  int curptr_chr1; // $v1
  sceNetCnfEnv_t *e_tmp1; // $a0
  int curresptrx1; // $v0
  char *ptr; // [sp+10h] [-8h] BYREF

  cur_linelen = 0;
  if ( e->f_verbose )
  {
    dir_name_or_null = e->dir_name;
    if ( !e->dir_name )
      dir_name_or_null = "NULL";
    path_or_null = path;
    if ( !path )
      path_or_null = "NULL";
    printf("netcnf: dir=%s path=%s\n", dir_name_or_null, path_or_null);
  }
  fullpath = do_handle_netcnf_prerw(e, path);
  result = -1;
  if ( fullpath )
  {
    if ( e->f_verbose )
    {
      printf("netcnf: reading \"%s\" as ", fullpath);
      if ( (char *)readcb == (char *)do_handle_net_cnf )
      {
        printf("NET_CNF");
      }
      else if ( (char *)readcb == (char *)do_handle_attach_cnf )
      {
        printf("ATTACH_CNF");
      }
      else
      {
        dial_cnf_or_unk = "???";
        if ( (char *)readcb == (char *)do_handle_dial_cnf )
          dial_cnf_or_unk = "DIAL_CNF";
        printf(dial_cnf_or_unk);
      }
      printf("\n");
    }
    e->fname = fullpath;
    read_res1 = do_read_netcnf(e, fullpath, &ptr, readcb == (int (*)())do_handle_attach_cnf);
    read_res2 = read_res1;
    lbuf = e->lbuf;
    if ( read_res1 < 0 )
    {
      printf("netcnf: can't load %s (%d)\n", e->fname, read_res1);
      return -1;
    }
    ptr_1 = ptr;
    f_no_check_magic = e->f_no_check_magic;
    e->lno = 0;
    if ( f_no_check_magic )
    {
      read_res3 = read_res2;
    }
    else if ( read_res2 < 36
           || (condtmp1 = strncmp(ptr_1, "# <Sony Computer Entertainment Inc.>", 36) == 0,
               read_res3 = read_res2,
               !condtmp1) )
    {
      curchind = 0;
      printf("netcnf: decoding error (magic=\"");
      condtmp2 = 1;
      if ( read_res2 > 0 )
      {
        do
        {
          curptr_1 = &ptr_1[curchind];
          if ( !condtmp2 )
            break;
          curchr = '?';
          if ( (u8)*curptr_1 - (unsigned int)' ' < '_' )
            curchr = (u8)*curptr_1;
          printf("%c", curchr);
          condtmp2 = ++curchind < '$';
        }
        while ( curchind < read_res2 );
      }
      printf("\")\n");
      do_free_heapmem(ptr);
      return -15;
    }
    curresptrx = read_res2 - 1;
    if ( read_res3 > 0 )
    {
      do
      {
        curptr_chr1 = (u8)*ptr_1++;
        if ( curptr_chr1 == 10 )
        {
          ++e->lno;
          if ( e->lbuf >= lbuf )
          {
            e_tmp1 = e;
LABEL_35:
            cur_linelen += do_check_line_buffer(e_tmp1, lbuf, (int (*)(int, int))readcb, userdata);
            lbuf = e->lbuf;
            goto LABEL_39;
          }
          e_tmp1 = e;
          if ( *(lbuf - 1) != '\\' )
            goto LABEL_35;
          --lbuf;
        }
        else
        {
          curresptrx1 = curresptrx;
          if ( lbuf >= &e->lbuf[1023] || curptr_chr1 == '\r' )
            goto LABEL_40;
          *lbuf++ = curptr_chr1;
        }
LABEL_39:
        curresptrx1 = curresptrx;
LABEL_40:
        --curresptrx;
      }
      while ( curresptrx1 > 0 );
    }
    if ( e->lbuf < lbuf )
      cur_linelen += do_check_line_buffer(e, lbuf, (int (*)(int, int))readcb, userdata);
    do_free_heapmem(ptr);
    return cur_linelen;
  }
  return result;
}

//----- (0040627C) --------------------------------------------------------
int do_netcnf_dial_related(sceNetCnfEnv_t *e)
{
  struct sceNetCnfRoot *rootdial; // $v0

  rootdial = (struct sceNetCnfRoot *)do_alloc_mem_inner(e, 44, 2);
  e->root = rootdial;
  if ( !rootdial )
    return -2;
  rootdial->version = 3;
  e->root->redial_count = -1;
  e->root->redial_interval = -1;
  e->root->dialing_type = -1;
  return do_netcnf_read_related(e, e->arg_fname, (int (*)())do_handle_net_cnf, 0);
}

//----- (004062FC) --------------------------------------------------------
int do_netcnf_ifc_related(sceNetCnfEnv_t *e)
{
  sceNetCnfInterface_t *rootifc; // $v0

  rootifc = (sceNetCnfInterface_t *)do_alloc_mem_inner(e, 352, 2);
  e->ifc = rootifc;
  if ( !rootifc )
    return -2;
  do_init_ifc_inner(rootifc);
  return do_netcnf_read_related(e, e->arg_fname, (int (*)())do_handle_attach_cnf, e->ifc);
}

//----- (00406360) --------------------------------------------------------
void do_dialauth_related(sceNetCnfInterface_t *ncid, struct sceNetCnfInterface *ncis)
{
  struct netcnf_option *optx1; // $s3
  int curindx; // $a2
  const char **p_m_key; // $s0
  int strptr2_1; // $a0
  int typadd1_1; // $v1
  int strptr2_2; // $a0
  int typadd1_3; // $v1
  int strptr2; // $a0
  int typadd1; // $v1
  sceNetCnfInterface_t *ncid_1; // $a0
  struct sceNetCnfInterface *ncis_1; // $a1
  u8 *curnumx; // $v1

  if ( ncis )
  {
    optx1 = g_options_attach_cnf;
    curindx = 0;
    if ( g_options_attach_cnf[0].m_key )
    {
      p_m_key = &g_options_attach_cnf[0].m_key;
      do
      {
        switch ( optx1->m_type )
        {
          case '1':
          case 'b':
          case 'c':
            strptr2 = (int)*(p_m_key - 1);
            typadd1 = *((u8 *)&ncis->type + strptr2);
            if ( typadd1 != 255 )
              *((u8 *)&ncid->type + strptr2) = typadd1;
            break;
          case '4':
          case 'D':
          case 'L':
          case 'P':
          case 'T':
            strptr2_1 = (int)*(p_m_key - 1);
            typadd1_1 = *(int *)((char *)&ncis->type + strptr2_1);
            if ( typadd1_1 != -1 )
              *(int *)((char *)&ncid->type + strptr2_1) = typadd1_1;
            break;
          case 'A':
            if ( !strcmp("want.auth", *p_m_key) )
            {
              if ( ncis->want.f_auth )
              {
                ncid->want.f_auth = 1;
                ncid->want.auth = ncis->want.auth;
              }
            }
            else if ( ncis->allow.f_auth )
            {
              ncid->allow.f_auth = 1;
              ncid->allow.auth = ncis->allow.auth;
            }
            break;
          case 'C':
            if ( !strcmp("want.accm", *p_m_key) )
            {
              if ( ncis->want.f_accm )
              {
                ncid->want.f_accm = 1;
                ncid->want.accm = ncis->want.accm;
              }
            }
            else if ( ncis->allow.f_accm )
            {
              ncid->allow.f_accm = 1;
              ncid->allow.accm = ncis->allow.accm;
            }
            break;
          case 'M':
            if ( !strcmp("want.mru", *p_m_key) )
            {
              if ( ncis->want.f_mru )
              {
                ncid->want.f_mru = 1;
                ncid->want.mru = ncis->want.mru;
              }
            }
            else if ( ncis->allow.f_mru )
            {
              ncid->allow.f_mru = 1;
              ncid->allow.mru = ncis->allow.mru;
            }
            break;
          case 'p':
            strptr2_2 = (int)*(p_m_key - 1);
            typadd1_3 = *(int *)((char *)&ncis->type + strptr2_2);
            if ( typadd1_3 )
              *(int *)((char *)&ncid->type + strptr2_2) = typadd1_3;
            break;
          default:
            break;
        }
        p_m_key += 3;
        ++optx1;
      }
      while ( *p_m_key );
      curindx = 0;
    }
    ncid_1 = ncid;
    ncis_1 = ncis;
    do
    {
      curnumx = ncis_1->phone_numbers[0];
      if ( curnumx )
        ncid_1->phone_numbers[0] = curnumx;
      ncid_1 = (sceNetCnfInterface_t *)((char *)ncid_1 + 4);
      ++curindx;
      ncis_1 = (struct sceNetCnfInterface *)((char *)ncis_1 + 4);
    }
    while ( curindx < 10 );
  }
}

//----- (004065CC) --------------------------------------------------------
int do_merge_conf_inner(sceNetCnfEnv_t *e)
{
  struct sceNetCnfRoot *root; // $s3
  int result; // $v0
  struct sceNetCnfPair *pair_head; // $s2
  struct sceNetCnfCtl *ctl; // $s0
  struct sceNetCnfDial *dial; // $v0
  sceNetCnfInterface_t *ifmem2; // $s1
  struct sceNetCnfInterface *dev; // $v0
  int type; // $s0

  root = e->root;
  result = -1;
  if ( root )
  {
    pair_head = root->pair_head;
    if ( root->pair_head )
    {
      while ( 1 )
      {
        ctl = pair_head->ctl;
        if ( !ctl )
        {
          ctl = (struct sceNetCnfCtl *)do_alloc_mem_inner(e, 32, 2);
          pair_head->ctl = ctl;
          if ( !ctl )
            break;
        }
        if ( !ctl->dial )
        {
          dial = (struct sceNetCnfDial *)do_alloc_mem_inner(e, 36, 2);
          ctl->dial = dial;
          if ( !dial )
            break;
        }
        ifmem2 = ctl->ifc;
        if ( !ifmem2 )
        {
          ifmem2 = (sceNetCnfInterface_t *)do_alloc_mem_inner(e, 352, 2);
          ctl->ifc = ifmem2;
          if ( !ifmem2 )
            break;
        }
        do_init_ifc_inner(ifmem2);
        ifmem2->chat_additional = root->chat_additional;
        ifmem2->redial_count = root->redial_count;
        ifmem2->redial_interval = root->redial_interval;
        ifmem2->outside_number = root->outside_number;
        ifmem2->outside_delay = root->outside_delay;
        ifmem2->dialing_type = root->dialing_type;
        do_dialauth_related(ifmem2, pair_head->ifc);
        dev = pair_head->dev;
        type = dev->type;
        dev->type = -1;
        do_dialauth_related(ifmem2, pair_head->dev);
        pair_head->dev->type = type;
        pair_head = pair_head->forw;
        if ( !pair_head )
          return 0;
      }
      return -2;
    }
    else
    {
      return 0;
    }
  }
  return result;
}

//----- (00406750) --------------------------------------------------------
int do_load_conf_inner(sceNetCnfEnv_t *e)
{
  int req; // $v1
  int retres1; // $s3
  int result; // $v0
  int ifcres1_1; // $s1
  struct sceNetCnfRoot *root; // $v0
  struct sceNetCnfPair *pair_head; // $s0
  char *attach_ifc; // $v0
  int ifcres1; // $v0
  char *attach_dev; // $v0
  int ifcres2; // $v0

  req = e->req;
  retres1 = 0;
  if ( req == 1 )
  {
    result = do_netcnf_dial_related(e);
    ifcres1_1 = result;
    if ( result )
      return result;
    root = e->root;
    if ( !root )
      return -14;
    pair_head = root->pair_head;
    if ( !root->pair_head )
      return -14;
    if ( index(e->arg_fname, ':') )
      e->dir_name = e->arg_fname;
    while ( 1 )
    {
      attach_ifc = (char *)pair_head->attach_ifc;
      if ( attach_ifc )
      {
        e->arg_fname = attach_ifc;
        ifcres1 = do_netcnf_ifc_related(e);
        ifcres1_1 = ifcres1;
        if ( ifcres1 )
        {
          printf("netcnf: load_attach ifc(%d)\n", ifcres1);
          pair_head->ifc = 0;
          if ( (unsigned int)(ifcres1_1 + 15) < 2 )
          {
            pair_head->dev = 0;
LABEL_24:
            if ( retres1 == -21 )
              return -21;
            return ifcres1_1;
          }
          retres1 = -21;
        }
        else
        {
          pair_head->ifc = e->ifc;
        }
      }
      else
      {
        pair_head->ifc = 0;
      }
      attach_dev = (char *)pair_head->attach_dev;
      if ( attach_dev )
      {
        e->arg_fname = attach_dev;
        ifcres2 = do_netcnf_ifc_related(e);
        ifcres1_1 = ifcres2;
        if ( ifcres2 )
        {
          printf("netcnf: load_attach dev(%d)\n", ifcres2);
          pair_head->dev = 0;
          if ( (unsigned int)(ifcres1_1 + 15) < 2 )
            goto LABEL_24;
          retres1 = -21;
        }
        else
        {
          pair_head->dev = e->ifc;
        }
      }
      else
      {
        pair_head->dev = 0;
      }
      pair_head = pair_head->forw;
      if ( !pair_head )
        goto LABEL_24;
    }
  }
  if ( req == 2 )
    return do_netcnf_ifc_related(e);
  return -1;
}

//----- (0040690C) --------------------------------------------------------
int do_load_dial_inner(sceNetCnfEnv_t *e, sceNetCnfPair_t *pair)
{
  struct sceNetCnfCtl *ctl; // $s0
  struct sceNetCnfDial *dialresx; // $v0

  ctl = pair->ctl;
  if ( !ctl )
    return -1;
  dialresx = (struct sceNetCnfDial *)do_alloc_mem_inner(e, 36, 2);
  ctl->dial = dialresx;
  if ( dialresx )
    return do_netcnf_read_related(e, e->arg_fname, (int (*)())do_handle_dial_cnf, dialresx);
  else
    return -2;
}

//----- (00406990) --------------------------------------------------------
int do_netcnf_vsprintf_buffer(sceNetCnfEnv_t *e, char *fmt, unsigned int va)
{
  char fmt_curchr3; // $a0
  char *mem_ptr_03; // $v1
  void *mem_ptr_rval_04; // $v0
  int has_negative; // $s7
  int has_sero; // $s5
  char fmt_curchr1; // $a0
  int strlened; // $s3
  int fmt_curchr2; // $v0
  int fmt_flag_capital_s; // $fp
  int minpad1; // $a2
  u8 *mem_ptr_01; // $v1
  char **cur_va2; // $v0
  char *strptr1; // $s0
  int strlenmax; // $s4
  unsigned int strpad1; // $a2
  int cur_va1; // $a1
  int valmod1; // $hi
  char *curnumvals; // $a0
  size_t strlen1; // $v0
  int strlencalc; // $s3
  u8 *mem_ptr_02; // $v1
  bool condtmp1; // dc
  u8 *mem_ptr_04; // $v1
  u8 *mem_ptr_05; // $v1
  unsigned int strptr_curchr2; // $a2
  char *i; // $s0
  int i_curchr1; // $v1
  u8 *mem_ptr_0a; // $a0
  void *mem_ptr_rval_02; // $v0
  char i_curchr2; // $a1
  void *mem_ptr_rval_03; // $v0
  u8 *mem_ptr_07; // $a0
  u8 *mem_last_01; // $v1
  u8 *mem_ptr_09; // $a1
  u8 *mem_last_02; // $v1
  u8 *mem_last_03; // $v1
  void *mem_ptr_rval_01; // $v0
  void *mem_last_04; // $v1
  u8 *mem_ptr_08; // $v1
  char strptr_curchr1; // $a0
  char *mem_ptr_06; // $v1
  int strlencalc_1; // $v0
  u8 *mem_ptr_0b; // $v1
  char stkstr1; // [sp+23h] [-5h] BYREF

  while ( *fmt )
  {
    fmt_curchr3 = *fmt;
    if ( *fmt == '%' )
    {
      ++fmt;
      has_negative = 0;
      if ( *fmt == '-' )
      {
        ++fmt;
        has_negative = 1;
      }
      has_sero = ' ';
      if ( *fmt == '0' )
      {
        has_sero = '0';
        ++fmt;
      }
      fmt_curchr1 = *fmt;
      strlened = 0;
      while ( (look_ctype_table(fmt_curchr1) & 4) != 0 )
      {
        fmt_curchr2 = *fmt++;
        fmt_curchr1 = *fmt;
        strlened = 10 * strlened - '0' + fmt_curchr2;
      }
      fmt_flag_capital_s = 0;
      if ( *fmt == 'l' )
        ++fmt;
      minpad1 = 0;
      switch ( *fmt )
      {
        case 'S':
          fmt_flag_capital_s = 1;
          goto LABEL_18;
        case 'X':
        case 'x':
          goto LABEL_22;
        case 'c':
          va = ((va + 3) & 0xFFFFFFFC) + 4;
          mem_ptr_01 = e->mem_ptr;
          mem_ptr_rval_04 = mem_ptr_01 + 1;
          if ( mem_ptr_01 >= e->mem_last )
            return -2;
          *mem_ptr_01 = *(u32 *)(va - 4);
          goto LABEL_82;
        case 'd':
        case 'u':
          goto LABEL_23;
        case 'o':
          goto LABEL_24;
        case 'p':
          has_sero = '0';
          if ( strlened < 8 )
            strlened = 8;
LABEL_22:
          minpad1 = 6;
LABEL_23:
          minpad1 += 2;
LABEL_24:
          strpad1 = minpad1 + 8;
          va = ((va + 3) & 0xFFFFFFFC) + 4;
          cur_va1 = *(u32 *)(va - 4);
          stkstr1 = 0;
          strptr1 = &stkstr1;
          if ( *fmt == 'd' )
          {
            strlenmax = 0;
            if ( cur_va1 < 0 )
            {
              cur_va1 = -cur_va1;
              strlenmax = 1;
            }
          }
          else
          {
            strlenmax = 0;
          }
          do
          {
            if ( !strpad1 )
              __builtin_trap();
            valmod1 = cur_va1 % strpad1;
            --strptr1;
            if ( *fmt == 'X' )
              curnumvals = &a0123456789abcd[valmod1];
            else
              curnumvals = &a0123456789abcd_0[valmod1];
            *strptr1 = *curnumvals;
            cur_va1 /= strpad1;
          }
          while ( cur_va1 );
          goto LABEL_34;
        case 's':
LABEL_18:
          cur_va2 = (char **)((va + 3) & 0xFFFFFFFC);
          va = (unsigned int)(cur_va2 + 1);
          strptr1 = *cur_va2;
          strlenmax = 0;
          if ( !*cur_va2 )
            goto LABEL_83;
LABEL_34:
          strlen1 = strlen(strptr1);
          if ( strlenmax )
            strlencalc = strlened + 1 - strlen1;
          else
            strlencalc = strlened - strlen1;
          if ( has_sero != '0' || !strlenmax )
            goto LABEL_41;
          mem_ptr_02 = e->mem_ptr;
          if ( mem_ptr_02 >= e->mem_last )
            return -2;
          *mem_ptr_02 = '-';
          e->mem_ptr = mem_ptr_02 + 1;
LABEL_41:
          if ( has_negative )
            goto LABEL_45;
          break;
        default:
          mem_ptr_03 = (char *)e->mem_ptr;
          fmt_curchr3 = *fmt;
          mem_ptr_rval_04 = mem_ptr_03 + 1;
          if ( mem_ptr_03 < e->mem_last )
            goto LABEL_81;
          return -2;
      }
      while ( 1 )
      {
        condtmp1 = strlencalc-- <= 0;
        if ( condtmp1 )
          break;
        mem_ptr_04 = e->mem_ptr;
        if ( mem_ptr_04 >= e->mem_last )
          return -2;
        *mem_ptr_04 = has_sero;
        e->mem_ptr = mem_ptr_04 + 1;
      }
LABEL_45:
      if ( has_sero != '0' && strlenmax )
      {
        mem_ptr_05 = e->mem_ptr;
        if ( mem_ptr_05 >= e->mem_last )
          return -2;
        *mem_ptr_05 = '-';
        e->mem_ptr = mem_ptr_05 + 1;
      }
      if ( !fmt_flag_capital_s )
      {
        while ( 1 )
        {
          if ( !*strptr1 )
            goto LABEL_76;
          strptr_curchr1 = *strptr1;
          mem_ptr_06 = (char *)e->mem_ptr;
          ++strptr1;
          if ( mem_ptr_06 >= e->mem_last )
            return -2;
          *mem_ptr_06 = strptr_curchr1;
          e->mem_ptr = mem_ptr_06 + 1;
        }
      }
      strptr_curchr2 = (u8)*strptr1;
      for ( i = strptr1 + 1; strptr_curchr2; strptr_curchr2 = (u8)*i++ )
      {
        if ( strptr_curchr2 - 0x81 >= 0x1F && strptr_curchr2 - 0xE0 >= 0x1D
          || (i_curchr1 = (u8)*i, (u8)(i_curchr1 - 64) >= 0xBDu)
          || i_curchr1 == 0x7F )
        {
          if ( strptr_curchr2 == '"' || strptr_curchr2 == '\\' )
          {
            mem_ptr_07 = e->mem_ptr;
            if ( mem_ptr_07 >= e->mem_last )
              return -2;
            *mem_ptr_07 = '\\';
            mem_last_01 = e->mem_last;
            e->mem_ptr = mem_ptr_07 + 1;
            mem_ptr_rval_03 = mem_ptr_07 + 2;
            if ( mem_ptr_07 + 1 >= mem_last_01 )
              return -2;
            mem_ptr_07[1] = strptr_curchr2;
          }
          else if ( strptr_curchr2 - ' ' < '_' )
          {
            mem_ptr_08 = e->mem_ptr;
            mem_ptr_rval_03 = mem_ptr_08 + 1;
            if ( mem_ptr_08 >= e->mem_last )
              return -2;
            *mem_ptr_08 = strptr_curchr2;
          }
          else
          {
            mem_ptr_09 = e->mem_ptr;
            if ( mem_ptr_09 >= e->mem_last )
              return -2;
            *mem_ptr_09 = 92;
            mem_last_02 = e->mem_last;
            e->mem_ptr = mem_ptr_09 + 1;
            if ( mem_ptr_09 + 1 >= mem_last_02 )
              return -2;
            mem_ptr_09[1] = 'x';
            mem_last_03 = e->mem_last;
            e->mem_ptr = mem_ptr_09 + 2;
            mem_ptr_rval_01 = mem_ptr_09 + 3;
            if ( mem_ptr_09 + 2 >= mem_last_03 )
              return -2;
            mem_ptr_09[2] = a0123456789abcd_0[strptr_curchr2 >> 4];
            mem_last_04 = e->mem_last;
            e->mem_ptr = mem_ptr_rval_01;
            condtmp1 = mem_ptr_rval_01 >= mem_last_04;
            mem_ptr_rval_03 = mem_ptr_09 + 4;
            if ( condtmp1 )
              return -2;
            mem_ptr_09[3] = a0123456789abcd_0[strptr_curchr2 & 0xF];
          }
        }
        else
        {
          mem_ptr_0a = e->mem_ptr;
          mem_ptr_rval_02 = mem_ptr_0a + 1;
          if ( mem_ptr_0a >= e->mem_last )
            return -2;
          *mem_ptr_0a = strptr_curchr2;
          e->mem_ptr = mem_ptr_rval_02;
          i_curchr2 = *i++;
          if ( mem_ptr_rval_02 >= e->mem_last )
            return -2;
          mem_ptr_rval_03 = mem_ptr_0a + 2;
          mem_ptr_0a[1] = i_curchr2;
        }
        e->mem_ptr = mem_ptr_rval_03;
      }
LABEL_76:
      while ( 1 )
      {
        strlencalc_1 = strlencalc;
        if ( !has_negative )
          break;
        --strlencalc;
        if ( strlencalc_1 <= 0 )
          break;
        mem_ptr_0b = e->mem_ptr;
        if ( mem_ptr_0b >= e->mem_last )
          return -2;
        *mem_ptr_0b = 32;
        e->mem_ptr = mem_ptr_0b + 1;
      }
    }
    else
    {
      mem_ptr_03 = (char *)e->mem_ptr;
      mem_ptr_rval_04 = mem_ptr_03 + 1;
      if ( mem_ptr_03 >= e->mem_last )
        return -2;
LABEL_81:
      *mem_ptr_03 = fmt_curchr3;
LABEL_82:
      e->mem_ptr = mem_ptr_rval_04;
    }
LABEL_83:
    ++fmt;
  }
  return 0;
}
// 406BA8: conditional instruction was optimized away because $a2.4!=0
// 406C54: conditional instruction was optimized away because $s7.4==0

//----- (00406F30) --------------------------------------------------------
int do_netcnf_sprintf_buffer(sceNetCnfEnv_t *e, const char *fmt, ...)
{
  va_list va; // [sp+20h] [+10h] BYREF

  va_start(va, fmt);
  return do_netcnf_vsprintf_buffer(e, (char *)fmt, (unsigned int)va);
}

//----- (00406F5C) --------------------------------------------------------
int do_netcnf_other_write(sceNetCnfEnv_t *e, struct netcnf_option *options, void *cnfdata)
{
  int result; // $v0
  char *offsptr2; // $v0
  int offsptr3; // $s1
  const char *lbuf; // $s0
  sceNetCnfEnv_t *e_1; // $a0
  u8 *lbuf_1; // $a0
  int *offsptr5; // $a2
  char *offsptr1; // $v0
  int offsptr6; // $s0
  int offsptr4; // $s1
  int curjptoffs; // $s2
  void **curjptx; // $s4

  while ( 1 )
  {
    result = 0;
    if ( !options->m_key )
      return result;
    switch ( options->m_type )
    {
      case '1':
        if ( *((u8 *)cnfdata + options->m_offset) == 255 )
          goto LABEL_91;
        result = do_netcnf_sprintf_buffer(
                   e,
                   "%s %d\n",
                   options->m_key,
                   *((u8 *)cnfdata + options->m_offset));
        goto LABEL_88;
      case '4':
        offsptr1 = (char *)cnfdata + options->m_offset;
        if ( *(int *)offsptr1 < 0 )
          goto LABEL_91;
        result = do_netcnf_sprintf_buffer(e, "%s %d\n", options->m_key, *(u32 *)offsptr1);
        goto LABEL_88;
      case 'A':
        if ( !strcmp("want.auth", options->m_key) )
        {
          if ( !*((u8 *)cnfdata + 171) )
          {
            ++options;
            continue;
          }
        }
        else if ( !*((u8 *)cnfdata + 247) )
        {
          goto LABEL_91;
        }
        offsptr2 = (char *)cnfdata + options->m_offset;
        offsptr3 = (u8)*offsptr2;
        switch ( *offsptr2 )
        {
          case 0:
            goto LABEL_18;
          case 1:
            lbuf = "pap";
            e_1 = e;
            break;
          case 2:
            lbuf = "chap";
            e_1 = e;
            break;
          case 3:
            lbuf = "pap/chap";
            e_1 = e;
            break;
          case 4:
            lbuf = "chap/pap";
            e_1 = e;
            break;
          default:
            goto LABEL_85;
        }
LABEL_87:
        result = do_netcnf_sprintf_buffer(e_1, "%s %s\n", options->m_key, lbuf);
        goto LABEL_88;
      case 'C':
        if ( !strcmp("want.accm", options->m_key) )
        {
          if ( !*((u8 *)cnfdata + 170) )
          {
            ++options;
            continue;
          }
        }
        else if ( !*((u8 *)cnfdata + 246) )
        {
          goto LABEL_91;
        }
        result = do_netcnf_sprintf_buffer(
                   e,
                   "%s 0x%08x\n",
                   options->m_key,
                   *(u32 *)((char *)cnfdata + options->m_offset));
        goto LABEL_88;
      case 'D':
        offsptr3 = *(u32 *)((char *)cnfdata + options->m_offset);
        if ( offsptr3 == -1 )
          goto LABEL_91;
        if ( offsptr3 == 1 )
        {
          lbuf = "pulse";
          e_1 = e;
          goto LABEL_87;
        }
        if ( offsptr3 < 2 )
        {
          lbuf = (const char *)e->lbuf;
          if ( offsptr3 )
          {
            lbuf_1 = e->lbuf;
            goto LABEL_86;
          }
          lbuf = "tone";
          e_1 = e;
          goto LABEL_87;
        }
        lbuf = (const char *)e->lbuf;
        if ( offsptr3 == 2 )
          goto LABEL_18;
        lbuf_1 = e->lbuf;
        goto LABEL_86;
      case 'L':
        offsptr4 = *(u32 *)((char *)cnfdata + options->m_offset);
        if ( offsptr4 == -1 )
          goto LABEL_91;
        result = do_netcnf_sprintf_buffer(e, "%s", options->m_key);
        curjptoffs = 0;
        if ( result < 0 )
          return result;
#if 0
        curjptx = &off_40A9B8;
#endif
        do
        {
#if 0
          if ( ((offsptr4 >> curjptoffs) & 1) != 0 && (unsigned int)curjptoffs < 0x12 )
            __asm { jr      $v0 }
#endif
          ++curjptoffs;
          ++curjptx;
        }
        while ( curjptoffs < 32 );
        if ( offsptr4 )
        {
          result = do_netcnf_sprintf_buffer(e, " 0x%x", offsptr4);
          if ( result < 0 )
            return result;
        }
        result = do_netcnf_sprintf_buffer(e, "\n");
        ++options;
        if ( result < 0 )
          return result;
        continue;
      case 'M':
        if ( !strcmp("want.mru", options->m_key) )
        {
          if ( !*((u8 *)cnfdata + 169) )
          {
            ++options;
            continue;
          }
        }
        else if ( !*((u8 *)cnfdata + 245) )
        {
LABEL_91:
          ++options;
          continue;
        }
        result = do_netcnf_sprintf_buffer(
                   e,
                   "%s %d\n",
                   options->m_key,
                   *(u16 *)((char *)cnfdata + options->m_offset));
LABEL_88:
        ++options;
        if ( result < 0 )
          return result;
        break;
      case 'P':
        offsptr3 = *(u32 *)((char *)cnfdata + options->m_offset);
        if ( offsptr3 == -1 )
          goto LABEL_91;
        switch ( offsptr3 )
        {
          case 1:
            lbuf = "auto";
            e_1 = e;
            break;
          case 2:
            lbuf = "10";
            e_1 = e;
            break;
          case 3:
            lbuf = "10_fd";
            e_1 = e;
            break;
          case 4:
            lbuf = "10_fd_pause";
            e_1 = e;
            break;
          case 5:
            lbuf = "tx";
            e_1 = e;
            break;
          case 6:
            lbuf = "tx_fd";
            e_1 = e;
            break;
          case 7:
            lbuf = "tx_fd_pause";
            e_1 = e;
            break;
          default:
LABEL_85:
            lbuf = (const char *)e->lbuf;
            lbuf_1 = e->lbuf;
            goto LABEL_86;
        }
        goto LABEL_87;
      case 'T':
        offsptr3 = *(u32 *)((char *)cnfdata + options->m_offset);
        if ( offsptr3 == -1 )
          goto LABEL_91;
        if ( offsptr3 == 1 )
        {
          lbuf = "eth";
          e_1 = e;
          goto LABEL_87;
        }
        if ( offsptr3 < 2 )
        {
          lbuf = (const char *)e->lbuf;
          if ( !offsptr3 )
          {
LABEL_18:
            lbuf = "any";
            e_1 = e;
            goto LABEL_87;
          }
          lbuf_1 = e->lbuf;
          goto LABEL_86;
        }
        if ( offsptr3 == 2 )
        {
          lbuf = "ppp";
          e_1 = e;
        }
        else
        {
          lbuf = (const char *)e->lbuf;
          if ( offsptr3 != 3 )
          {
            lbuf_1 = e->lbuf;
            goto LABEL_86;
          }
          lbuf = "nic";
          e_1 = e;
        }
        goto LABEL_87;
      case 'b':
        if ( *((u8 *)cnfdata + options->m_offset) == 255 )
          goto LABEL_91;
        offsptr5 = (int *)"-";
        if ( *((u8 *)cnfdata + options->m_offset) )
          offsptr5 = &g_null_string;
        result = do_netcnf_sprintf_buffer(e, "%s%s\n", offsptr5, options->m_key);
        goto LABEL_88;
      case 'c':
        offsptr3 = *((u8 *)cnfdata + options->m_offset);
        if ( offsptr3 == 255 )
          goto LABEL_91;
        if ( offsptr3 == 5 )
        {
          lbuf = "md5";
          e_1 = e;
          goto LABEL_87;
        }
        if ( *((u8 *)cnfdata + options->m_offset) >= 6u )
        {
          if ( offsptr3 == 128 )
          {
            lbuf = "ms-v1";
            e_1 = e;
            goto LABEL_87;
          }
          lbuf = (const char *)e->lbuf;
          if ( offsptr3 == 129 )
          {
            lbuf = "ms-v2";
            e_1 = e;
            goto LABEL_87;
          }
          lbuf_1 = e->lbuf;
        }
        else
        {
          lbuf = (const char *)e->lbuf;
          if ( !*((u8 *)cnfdata + options->m_offset) )
          {
            lbuf = "no";
            e_1 = e;
            goto LABEL_87;
          }
          lbuf_1 = e->lbuf;
        }
LABEL_86:
        sprintf((char *)lbuf_1, "0x%x", offsptr3);
        e_1 = e;
        goto LABEL_87;
      case 'p':
        offsptr6 = *(u32 *)((char *)cnfdata + options->m_offset);
        if ( !offsptr6 )
          goto LABEL_91;
        result = do_netcnf_sprintf_buffer(e, "%s \"%S\"\n", options->m_key, offsptr6);
        goto LABEL_88;
      default:
        return printf("netcnf: internal save error (%d, type=%c)\n", 302, options->m_type);
    }
  }
}
// 40A728: using guessed type int g_null_string;
// 40A9B8: using guessed type void *off_40A9B8;

//----- (00407688) --------------------------------------------------------
int do_netcnf_net_write(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc)
{
  struct sceNetCnfCommand *cmd_head; // $s2
  int code; // $v1
  int nameserverflag; // $s0
  int result; // $v0
  bool condtmp1; // dc
  const char *del_or_add; // $a2
  const char *net_or_host; // $a2

  cmd_head = ifc->cmd_head;
  if ( cmd_head )
  {
    while ( 1 )
    {
      code = cmd_head->code;
      nameserverflag = 0;
      if ( code == 2 )
        goto LABEL_10;
      if ( code < 3 )
        break;
      if ( code == 3 )
      {
        net_or_host = "net";
        if ( ((int)cmd_head[6].forw & 2) != 0 )
          net_or_host = "host";
        result = do_netcnf_sprintf_buffer(e, "route add -%s", net_or_host);
        if ( result < 0 )
          return result;
        condtmp1 = sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[1]) != 0;
        result = -1;
        if ( condtmp1 )
          return result;
        result = do_netcnf_sprintf_buffer(e, " %s", (const char *)e->lbuf);
        if ( result < 0 )
          return result;
        if ( ((int)cmd_head[6].forw & 4) != 0 )
        {
          condtmp1 = sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[2].code) != 0;
          result = -1;
          if ( condtmp1 )
            return result;
          result = do_netcnf_sprintf_buffer(e, " gw %s", (const char *)e->lbuf);
          if ( result < 0 )
            return result;
        }
        condtmp1 = sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[4].back) != 0;
        result = -1;
        if ( condtmp1 )
          return result;
        result = do_netcnf_sprintf_buffer(e, " netmask %s", (const char *)e->lbuf);
        if ( result < 0 )
          return result;
        result = do_netcnf_sprintf_buffer(e, "\n");
        if ( result < 0 )
          return result;
      }
      else
      {
        result = -1;
        if ( code != 4 )
          return result;
        condtmp1 = sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[1]) != 0;
        result = -1;
        if ( condtmp1 )
          return result;
        result = do_netcnf_sprintf_buffer(e, "route del %s\n", (const char *)e->lbuf);
        if ( result < 0 )
          return result;
      }
LABEL_29:
      cmd_head = cmd_head->forw;
      if ( !cmd_head )
        return 0;
    }
    result = -1;
    if ( code != 1 )
      return result;
    nameserverflag = 1;
LABEL_10:
    condtmp1 = sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[1]) != 0;
    result = -1;
    if ( condtmp1 )
      return result;
    del_or_add = "del";
    if ( nameserverflag )
      del_or_add = "add";
    result = do_netcnf_sprintf_buffer(e, "nameserver %s %s\n", del_or_add, (const char *)e->lbuf);
    if ( result < 0 )
      return result;
    goto LABEL_29;
  }
  return 0;
}

//----- (004078CC) --------------------------------------------------------
int do_netcnf_phone_write(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc)
{
  int ind1; // $s0
  u8 *ifcnum; // $a3
  int result; // $v0

  ind1 = 0;
  while ( 1 )
  {
    ifcnum = ifc->phone_numbers[0];
    if ( ifcnum )
    {
      result = do_netcnf_sprintf_buffer(e, "phone_number%d \"%S\"\n", ind1, ifcnum);
      if ( result < 0 )
        break;
    }
    ++ind1;
    ifc = (struct sceNetCnfInterface *)((char *)ifc + 4);
    if ( ind1 >= 10 )
      return 0;
  }
  return result;
}

//----- (00407940) --------------------------------------------------------
int do_netcnf_unknown_write(sceNetCnfEnv_t *e, struct sceNetCnfUnknownList *unknown_list)
{
  struct sceNetCnfUnknown *head; // $s0
  sceNetCnfEnv_t *e_1; // $s1
  int result; // $v0

  head = unknown_list->head;
  e_1 = e;
  if ( !unknown_list->head )
    return 0;
  while ( 1 )
  {
    result = do_netcnf_sprintf_buffer(e, "%s\n", (const char *)&head[1]);
    if ( result < 0 )
      break;
    head = head->forw;
    e = e_1;
    if ( !head )
      return 0;
  }
  return result;
}

//----- (004079A4) --------------------------------------------------------
int do_write_netcnf(sceNetCnfEnv_t *e, const char *path, int is_attach_cnf)
{
  int memsize; // $s3
  char *dir_name_or_null; // $a1
  const char *path_or_null; // $a2
  char *fullpath; // $s0
  int result; // $v0
  const char *attach_or_net_cnf; // $a0
  bool writerese; // dc
  int fd; // $v0
  int fd_1; // $s1
  int retres; // $v1
  int writeres; // $s0

  memsize = e->mem_ptr - e->mem_base;
  if ( e->f_verbose )
  {
    dir_name_or_null = e->dir_name;
    if ( !e->dir_name )
      dir_name_or_null = "NULL";
    path_or_null = path;
    if ( !path )
      path_or_null = "NULL";
    printf("netcnf: dir=%s path=%s\n", dir_name_or_null, path_or_null);
  }
  fullpath = do_handle_netcnf_prerw(e, path);
  result = -1;
  if ( fullpath )
  {
    if ( e->f_verbose )
    {
      printf("netcnf: writing \"%s\" as ", fullpath);
      attach_or_net_cnf = "NET_CNF";
      if ( is_attach_cnf )
        attach_or_net_cnf = "ATTACH_CNF";
      printf(attach_or_net_cnf);
      printf("\n");
    }
    if ( !is_attach_cnf || e->f_no_decode )
    {
      fd = do_open_netcnf(fullpath, 1538, 511);
      fd_1 = fd;
      if ( fd >= 0 )
      {
        writeres = do_write_netcnf_no_encode(fd, e->mem_base, memsize);
        if ( memsize == writeres )
        {
          do_close_netcnf(fd_1);
          return 0;
        }
        else
        {
          ++e->file_err;
          do_close_netcnf(fd_1);
          result = -5;
          if ( writeres == -5 )
            return -18;
        }
      }
      else
      {
        ++e->file_err;
        retres = -3;
        if ( fd == -5 )
          return -18;
        return retres;
      }
    }
    else
    {
      writerese = do_write_netcnf_encode(fullpath, e->mem_base, memsize) >= 0;
      result = 0;
      if ( !writerese )
      {
        result = -1;
        ++e->file_err;
      }
    }
  }
  return result;
}

//----- (00407B70) --------------------------------------------------------
int do_export_netcnf_inner(sceNetCnfEnv_t *e, const char *arg_fname, struct sceNetCnfInterface *ifc)
{
  void *memalign; // $v0
  int result; // $v0
  sceNetCnfEnv_t *e_1; // $a0
  const char *arg_fname_1; // $a1
  int isattachcnf; // $a2
  struct sceNetCnfPair *pair_head; // $s0

  memalign = (void *)(((int)e->mem_base + 3) & 0xFFFFFFFC);
  e->mem_base = memalign;
  e->mem_ptr = memalign;
  result = do_netcnf_sprintf_buffer(e, "%s\n\n", "# <Sony Computer Entertainment Inc.>");
  if ( result >= 0 )
  {
    if ( ifc )
    {
      result = do_netcnf_other_write(e, g_options_attach_cnf, ifc);
      if ( result >= 0 )
      {
        result = do_netcnf_phone_write(e, ifc);
        if ( result >= 0 )
        {
          result = do_netcnf_net_write(e, ifc);
          if ( result >= 0 )
          {
            result = do_netcnf_unknown_write(e, &ifc->unknown_list);
            e_1 = e;
            if ( result >= 0 )
            {
              arg_fname_1 = arg_fname;
              isattachcnf = 1;
              return do_write_netcnf(e_1, arg_fname_1, isattachcnf);
            }
          }
        }
      }
    }
    else
    {
      pair_head = e->root->pair_head;
      if ( pair_head )
      {
        while ( 1 )
        {
          result = do_netcnf_sprintf_buffer(
                     e,
                     "interface \"%S\" \"%S\" \"%S\"\n",
                     pair_head->display_name,
                     pair_head->attach_ifc,
                     pair_head->attach_dev);
          if ( result < 0 )
            break;
          pair_head = pair_head->forw;
          if ( !pair_head )
            goto LABEL_11;
        }
      }
      else
      {
LABEL_11:
        result = do_netcnf_other_write(e, g_options_net_cnf, e->root);
        if ( result >= 0 )
        {
          result = do_netcnf_unknown_write(e, &e->root->unknown_list);
          e_1 = e;
          if ( result >= 0 )
          {
            arg_fname_1 = arg_fname;
            isattachcnf = 0;
            return do_write_netcnf(e_1, arg_fname_1, isattachcnf);
          }
        }
      }
    }
  }
  return result;
}

//----- (00407CCC) --------------------------------------------------------
int do_export_netcnf(sceNetCnfEnv_t *e)
{
  int req; // $v1
  int result; // $v0
  char *arg_fname; // $a1
  struct sceNetCnfInterface *ifc; // $a2
  bool condtmp1; // dc

  req = e->req;
  if ( req == 1 )
  {
    arg_fname = e->arg_fname;
    ifc = 0;
  }
  else
  {
    if ( req != 2 )
      return -1;
    arg_fname = e->arg_fname;
    ifc = e->ifc;
  }
  condtmp1 = do_export_netcnf_inner(e, arg_fname, ifc) == 0;
  result = 0;
  if ( !condtmp1 )
    return -1;
  return result;
}

//----- (00407D40) --------------------------------------------------------
char *do_address_to_string_inner_element(char *dst, int srcbyte)
{
  u8 *tmpstk_ptr; // $a2
  char *result; // $v0
  u8 tmpstk[16]; // [sp+0h] [-10h] BYREF

  tmpstk_ptr = tmpstk;
  if ( srcbyte < 0 )
  {
    *dst++ = '-';
    srcbyte = -srcbyte;
  }
  do
  {
    *tmpstk_ptr = srcbyte % 10 + 48;
    srcbyte /= 10;
    ++tmpstk_ptr;
  }
  while ( srcbyte > 0 );
  result = dst;
  if ( tmpstk < tmpstk_ptr )
  {
    do
      *dst++ = *--tmpstk_ptr;
    while ( tmpstk < tmpstk_ptr );
    return dst;
  }
  return result;
}

//----- (00407DD0) --------------------------------------------------------
char *do_address_to_string_inner(char *dst, unsigned int srcint)
{
  char *elm1; // $v0
  char *elm2; // $v0
  char *elm3; // $v0

  elm1 = do_address_to_string_inner_element(dst, (srcint >> 24) & 0xFF);
  *elm1 = '.';
  elm2 = do_address_to_string_inner_element(elm1 + 1, (srcint >> 16) & 0xFF);
  *elm2 = '.';
  elm3 = do_address_to_string_inner_element(elm2 + 1, (srcint >> 8) & 0xFF);
  *elm3 = '.';
  *do_address_to_string_inner_element(elm3 + 1, srcint & 0xFF) = 0;
  return dst;
}

//----- (00407E50) --------------------------------------------------------
int do_name_2_address_inner(unsigned int *dst, char *buf)
{
  int prefixchkn; // $s4
  int *tmpstk1_ptr; // $s5
  int curindx2; // $s6
  int base; // $s2
  int buf_curchr1; // $v1
  unsigned int i; // $s3
  int buf_curchr2; // $s0
  u8 ctypeind1; // $v0
  int offsbase1; // $a0
  u8 ctypeind2; // $v0
  int result; // $v0
  int tmkstk_hi1; // $v0
  int tmpstk1[3]; // [sp+10h] [-10h] BYREF

  prefixchkn = 0;
  tmpstk1_ptr = tmpstk1;
  curindx2 = -1;
  while ( 1 )
  {
    base = 10;
    if ( *buf == '0' )
    {
      buf_curchr1 = *++buf;
      if ( buf_curchr1 == 'x' || (base = 8, buf_curchr1 == 'X') )
      {
        ++buf;
        base = 16;
      }
    }
    for ( i = 0; ; i = i * base + offsbase1 )
    {
      buf_curchr2 = *buf;
      if ( (look_ctype_table(*buf) & 0x44) == 0 )
        break;
      ctypeind1 = look_ctype_table(buf_curchr2);
      offsbase1 = buf_curchr2 - '0';
      if ( (ctypeind1 & 4) == 0 )
      {
        ctypeind2 = look_ctype_table(buf_curchr2);
        offsbase1 = buf_curchr2 - '7';
        if ( (ctypeind2 & 1) == 0 )
          offsbase1 = buf_curchr2 - 'W';
      }
      if ( offsbase1 >= base )
        break;
      ++buf;
    }
    if ( prefixchkn > 0 )
    {
      result = 0;
      if ( (unsigned int)tmpstk1[curindx2] >= 0x100 )
        return result;
    }
    *tmpstk1_ptr++ = i;
    ++curindx2;
    ++prefixchkn;
    if ( *buf != '.' || prefixchkn >= 4 )
      break;
    ++buf;
  }
  if ( !*buf || (result = 0, *buf == ' ') )
  {
    if ( prefixchkn == 2 )
    {
      if ( (i >> 24) )
        return 0;
      tmkstk_hi1 = tmpstk1[0] << 24;
      goto LABEL_34;
    }
    if ( prefixchkn < 3 )
    {
      result = 0;
      if ( prefixchkn != 1 )
        return result;
      goto LABEL_35;
    }
    if ( prefixchkn == 3 )
    {
      result = 0;
      if ( (i >> 16) )
        return result;
      i |= (tmpstk1[0] << 24) | (tmpstk1[1] << 16);
      goto LABEL_35;
    }
    result = 0;
    if ( prefixchkn == 4 )
    {
      result = 0;
      if ( !(i >> 8) )
      {
        tmkstk_hi1 = (tmpstk1[0] << 24) | (tmpstk1[1] << 16) | (tmpstk1[2] << 8);
LABEL_34:
        i |= tmkstk_hi1;
LABEL_35:
        *dst = i;
        return 1;
      }
    }
  }
  return result;
}

//----- (00408080) --------------------------------------------------------
int do_conv_a2s_inner(char *sp_, char *dp_, int len)
{
  int len_minus_three; // $a2
  int curindx1; // $t2
  char *dp_ptroffs1; // $a1
  char *dp_ptroffs2; // $a1
  int sp_curchr1; // $v0
  int sp_curchr2; // $a3
  int sp_curchr3; // $v1
  int sp_hichr1; // $v0
  int sp_lochr1; // $v0
  int result; // $v0
  char sp_curchr4; // $v0
  char *dp_ptroffs3; // $a1
  int len_minus_three_minus_five; // $a2

  len_minus_three = len - 3;
  curindx1 = 0;
  if ( len_minus_three <= 0 )
    return -19;
  *dp_ = '"';
  dp_ptroffs1 = dp_ + 1;
  *dp_ptroffs1++ = '"';
  *dp_ptroffs1 = ' ';
  dp_ptroffs2 = dp_ptroffs1 + 1;
  while ( 1 )
  {
    do
    {
      do
        sp_curchr1 = *sp_++;
      while ( sp_curchr1 == ' ' );
    }
    while ( sp_curchr1 == '\t' );
    sp_curchr2 = *--sp_;
    if ( !*sp_ )
      break;
    if ( sp_curchr2 != 'A' && sp_curchr2 != 'a' )
      return 0;
    sp_curchr3 = sp_[1];
    if ( sp_curchr3 != 'T' && sp_curchr3 != 't' )
      return 0;
    sp_hichr1 = (u8)*sp_ << 24;
    do
    {
      sp_lochr1 = sp_hichr1 >> 24;
      if ( sp_lochr1 == '\t' )
        break;
      if ( --len_minus_three <= 0 )
        return -19;
      if ( sp_lochr1 == '-' || sp_lochr1 == '\\' || sp_lochr1 == '"' || sp_lochr1 == '^' )
      {
        --len_minus_three;
        result = -19;
        if ( len_minus_three <= 0 )
          return result;
        *dp_ptroffs2++ = '\\';
      }
      sp_curchr4 = *sp_++;
      *dp_ptroffs2++ = sp_curchr4;
      if ( !*sp_ )
        break;
      sp_hichr1 = (u8)*sp_ << 24;
    }
    while ( *sp_ != ' ' );
    len_minus_three -= 4;
    if ( len_minus_three <= 0 )
      return -19;
    *dp_ptroffs2 = ' ';
    dp_ptroffs3 = dp_ptroffs2 + 1;
    *dp_ptroffs3++ = 'O';
    *dp_ptroffs3++ = 'K';
    *dp_ptroffs3 = ' ';
    dp_ptroffs2 = dp_ptroffs3 + 1;
    ++curindx1;
  }
  len_minus_three_minus_five = len_minus_three - 2;
  if ( curindx1 <= 0 )
    return 0;
  if ( len_minus_three_minus_five <= 0 )
    return -19;
  strcpy(dp_ptroffs2, "\\c");
  return 1;
}
// 408134: conditional instruction was optimized away because $a3.4 is in (==41|==61)

//----- (0040822C) --------------------------------------------------------
int do_conv_s2a_inner(char *sp_, char *dp_, int len)
{
  int curindx1; // $t2
  int sp_curchr1; // $v1
  char *sp_minus_one1; // $a0
  int result; // $v0
  int sp_chr2_1; // $v1
  char *sp_ptroffs1; // $a0
  int sp_curchr2; // $v0
  char *sp_ptroffs2; // $a0
  int sp_curchr3; // $v1
  int sp_curchr4; // $v1
  int sp_curchr5; // $v1
  int sp_curchr6; // $v0
  int sp_hichr1; // $v0
  int sp_lochr1; // $v0
  int sp_curchr7; // $v1
  char sp_curchr8; // $v0
  int sp_curchr9; // $v0
  char *sp_ptroffs3; // $a0
  int sp_curchra; // $v0
  int sp_curchrb; // $v1
  char *sp_ptroffs4; // $a0
  int sp_curchrc; // $v1
  int len_minus_one; // $a2

  curindx1 = 0;
  do
  {
    do
      sp_curchr1 = *sp_++;
    while ( sp_curchr1 == ' ' );
  }
  while ( sp_curchr1 == '\t' );
  sp_minus_one1 = sp_ - 1;
  if ( *sp_minus_one1 != '"' )
    return 0;
  if ( sp_minus_one1[1] != '"' )
    return 0;
  sp_chr2_1 = sp_minus_one1[2];
  if ( sp_chr2_1 != ' ' && sp_chr2_1 != '\t' )
    return 0;
  sp_ptroffs1 = sp_minus_one1 + 3;
  while ( 1 )
  {
    do
    {
      do
        sp_curchr2 = *sp_ptroffs1++;
      while ( sp_curchr2 == ' ' );
    }
    while ( sp_curchr2 == '\t' );
    sp_ptroffs2 = sp_ptroffs1 - 1;
    sp_curchr3 = *sp_ptroffs2;
    if ( !*sp_ptroffs2 )
      break;
    if ( sp_curchr3 == '\\' )
      goto LABEL_42;
    if ( sp_curchr3 != 'A' && sp_curchr3 != 'a' )
      return 0;
    sp_curchr4 = sp_ptroffs2[1];
    if ( sp_curchr4 != 'T' && sp_curchr4 != 't' )
      return 0;
    if ( curindx1 > 0 )
    {
      if ( --len <= 0 )
        return -19;
      *dp_++ = ' ';
    }
    sp_curchr5 = *sp_ptroffs2;
    sp_curchr6 = (u8)*sp_ptroffs2;
    if ( *sp_ptroffs2 )
    {
      ++sp_ptroffs2;
      if ( sp_curchr5 != ' ' )
      {
        --sp_ptroffs2;
        sp_hichr1 = sp_curchr6 << 24;
        while ( 1 )
        {
          sp_lochr1 = sp_hichr1 >> 24;
          if ( sp_lochr1 == '\t' )
            break;
          if ( --len <= 0 )
            return -19;
          if ( sp_lochr1 == '\\' )
          {
            sp_curchr7 = sp_ptroffs2[1];
            if ( sp_curchr7 != '-' && sp_curchr7 != '\\' && sp_curchr7 != '"' && sp_curchr7 != '^' )
              return 0;
            ++sp_ptroffs2;
          }
          sp_curchr8 = *sp_ptroffs2++;
          *dp_++ = sp_curchr8;
          if ( *sp_ptroffs2 )
          {
            sp_hichr1 = (u8)*sp_ptroffs2 << 24;
            if ( *sp_ptroffs2 != ' ' )
              continue;
          }
          goto LABEL_34;
        }
      }
    }
    do
    {
      do
LABEL_34:
        sp_curchr9 = *sp_ptroffs2++;
      while ( sp_curchr9 == ' ' );
    }
    while ( sp_curchr9 == '\t' );
    sp_ptroffs3 = sp_ptroffs2 - 1;
    if ( *sp_ptroffs3 != 'O' )
      return 0;
    if ( sp_ptroffs3[1] != 'K' )
      return 0;
    sp_curchra = sp_ptroffs3[2];
    if ( sp_curchra != ' ' && sp_curchra != '\t' )
      return 0;
    sp_ptroffs1 = sp_ptroffs3 + 3;
    ++curindx1;
  }
  if ( sp_curchr3 != '\\' )
    return 0;
LABEL_42:
  sp_curchrb = sp_ptroffs2[1];
  sp_ptroffs4 = sp_ptroffs2 + 2;
  if ( sp_curchrb != 'c' )
    return 0;
  do
  {
    do
      sp_curchrc = *sp_ptroffs4++;
    while ( sp_curchrc == ' ' );
  }
  while ( sp_curchrc == '\t' );
  if ( *(sp_ptroffs4 - 1) )
    return -19;
  len_minus_one = len - 1;
  if ( curindx1 <= 0 )
    return 0;
  result = 1;
  if ( len_minus_one < 0 )
    return -19;
  *dp_ = 0;
  return result;
}

//----- (004084A0) --------------------------------------------------------
int do_check_aolnet(const char *auth_name)
{
  const char *auth_name_1; // $s0
  bool condtmp1; // dc
  int result; // $v0
  int i; // $s1
  char *periodpos; // $v0

  auth_name_1 = auth_name;
  condtmp1 = strncmp(auth_name, "aolnet/", 7) != 0;
  result = 0;
  if ( !condtmp1 )
  {
    for ( i = 0; ; ++i )
    {
      periodpos = strchr(auth_name_1, '.');
      auth_name_1 = periodpos + 1;
      if ( !periodpos )
        break;
    }
    result = -20;
    if ( i != 5 )
      return 0;
  }
  return result;
}

//----- (00408514) --------------------------------------------------------
int do_check_authnet(char *argst, char *arged)
{
  char *i; // $s0
  char *j; // $s0
  u8 ctypetmp1; // $v0
  const char *j_1; // $a0
  bool condtmp1; // dc
  int result; // $v0
  int j_hichr1; // $a0
  int j_curchr1; // $v0
  int j_curchr2; // $a0
  int j_hichr2; // $a0

  for ( i = arged; argst < i; --i )
  {
    if ( *(i - 1) >= '!' )
      break;
  }
  *i = 0;
  for ( j = argst; *j; ++j )
  {
    ctypetmp1 = look_ctype_table(*j);
    j_1 = j;
    if ( (ctypetmp1 & 8) == 0 )
      goto LABEL_9;
  }
  j_1 = j;
LABEL_9:
  condtmp1 = strncmp(j_1, "auth_name", 9) != 0;
  result = 0;
  if ( !condtmp1 )
  {
    j_hichr1 = (u8)*j << 24;
    if ( *j )
    {
      while ( 1 )
      {
        if ( (look_ctype_table((j_hichr1 >> 24)) & 8) != 0 )
          goto LABEL_16;
        j_curchr1 = *++j;
        j_curchr2 = (u8)*j;
        if ( !*j )
          break;
        j_hichr1 = j_curchr2 << 24;
      }
      while ( 1 )
      {
        j_hichr2 = j_curchr2 << 24;
        if ( !j_curchr1 || (look_ctype_table((j_hichr2 >> 24)) & 8) == 0 )
          break;
        ++j;
LABEL_16:
        j_curchr1 = *j;
        j_curchr2 = (u8)*j;
      }
    }
    if ( *j == 34 )
      ++j;
    result = do_check_aolnet(j);
    if ( result >= 0 )
      return 0;
  }
  return result;
}

//----- (00408644) --------------------------------------------------------
int do_read_check_netcnf(const char *netcnf_path, int type, int no_check_magic, int no_decode)
{
  int result; // $v0
  int read_res2; // $s1
  char *heapmem; // $v0
  char *heapmem_1; // $s3
  int errretres; // $s2
  char *curheapptr1; // $s4
  char *heapmem_2; // $s0
  bool condtmp1; // dc
  int read_res3; // $v0
  int curchind; // $s0
  u32 condtmp2; // $v0
  int curchr2; // $v1
  int curchr; // $a1
  int curresptrx; // $s1
  char curptr_chr1; // $a0
  int curptr_chr2; // $v1
  int curresptrx_1; // $v0

  if ( type == 1 )
  {
    if ( no_decode )
      result = do_read_netcnf_no_decode(netcnf_path, &g_read_check_netcnf_heapptr);
    else
      result = do_read_netcnf_decode(netcnf_path, &g_read_check_netcnf_heapptr);
    read_res2 = result;
    if ( result < 0 )
      return result;
    heapmem = (char *)do_alloc_heapmem(1024);
    heapmem_1 = heapmem;
    errretres = 0;
    if ( !heapmem )
    {
      do_free_heapmem(g_read_check_netcnf_heapptr);
      return -2;
    }
    curheapptr1 = g_read_check_netcnf_heapptr;
    heapmem_2 = heapmem;
    if ( no_check_magic )
    {
      if ( read_res2 < 36
        || (condtmp1 = strncmp(g_read_check_netcnf_heapptr, "# <Sony Computer Entertainment Inc.>", 36) == 0,
            read_res3 = read_res2,
            !condtmp1) )
      {
        curchind = 0;
        printf("netcnf: decoding error (magic=\"");
        condtmp2 = 1;
        if ( read_res2 > 0 )
        {
          do
          {
            if ( !condtmp2 )
              break;
            curchr2 = (u8)curheapptr1[curchind];
            curchr = (unsigned int)(curchr2 - 32) >= 0x5F ? '?' : (char)curchr2;
            printf("%c", curchr);
            condtmp2 = ++curchind < 36;
          }
          while ( curchind < read_res2 );
        }
        errretres = -15;
        printf("\")\n");
LABEL_40:
        do_free_heapmem(g_read_check_netcnf_heapptr);
        do_free_heapmem(heapmem_1);
        return errretres;
      }
    }
    else
    {
      read_res3 = read_res2;
    }
    curresptrx = read_res2 - 1;
    if ( read_res3 <= 0 )
    {
LABEL_38:
      if ( heapmem_1 < heapmem_2 )
        errretres = do_check_authnet(heapmem_1, heapmem_2);
      goto LABEL_40;
    }
    while ( 1 )
    {
      curptr_chr1 = *curheapptr1;
      curptr_chr2 = *curheapptr1++;
      if ( curptr_chr2 == '\n' )
      {
        if ( heapmem_1 >= heapmem_2 || *(heapmem_2 - 1) != '\\' )
        {
          *heapmem_2 = 0;
          errretres = do_check_authnet(heapmem_1, heapmem_2);
          heapmem_2 = heapmem_1;
          if ( errretres < 0 )
            goto LABEL_40;
          curresptrx_1 = curresptrx;
          goto LABEL_37;
        }
        --heapmem_2;
      }
      else
      {
        curresptrx_1 = curresptrx;
        if ( heapmem_2 >= heapmem_1 + 1023 || curptr_chr2 == '\r' )
          goto LABEL_37;
        *heapmem_2++ = curptr_chr1;
      }
      curresptrx_1 = curresptrx;
LABEL_37:
      --curresptrx;
      if ( curresptrx_1 <= 0 )
        goto LABEL_38;
    }
  }
  if ( type < 2 )
  {
    result = -10;
    if ( type )
      return result;
    return 0;
  }
  result = -10;
  if ( type == 2 )
    return 0;
  return result;
}

//----- (004088DC) --------------------------------------------------------
int do_check_provider_inner(sceNetCnfEnv_t *e, int type)
{
  int result; // $v0
  struct sceNetCnfInterface *ifc; // $a0
  const char *auth_name; // $a0

  if ( type == 1 )
  {
    result = -14;
    if ( e )
    {
      ifc = e->ifc;
      if ( ifc )
      {
        auth_name = (const char *)ifc->auth_name;
        result = 0;
        if ( auth_name )
        {
          result = do_check_aolnet(auth_name);
          if ( result >= 0 )
            return 0;
        }
      }
    }
  }
  else
  {
    if ( type < 2 )
    {
      result = -10;
      if ( type )
        return result;
      return 0;
    }
    result = -10;
    if ( type == 2 )
      return 0;
  }
  return result;
}

//----- (00408970) --------------------------------------------------------
char *do_handle_netcnf_dirname(char *fpath, const char *entry_buffer, char *netcnf_file_path)
{
  const char *entry_buffer_1; // $v1
  int entry_buffer_curchr1; // $v0
  char *fpath_1; // $a3
  char *fpath_1_minus_1; // $a3
  int entry_buffer_curchr2; // $v1
  int fpath_1_curchr2; // $t0
  int fpath_1_curchrhi1; // $v0
  int fpath_1_curchr3; // $v0
  bool condtmp1; // dc
  int fpath_1_curchr1; // $v1
  char *fpath_2; // $v1
  char *i; // $t0
  char fpath_2_curchr1; // $v0
  const char *entry_buffer_2; // $v1
  int entry_buffer_curchr3; // $v0
  char entry_buffer_curchr4; // $a0

  if ( !entry_buffer )
    return 0;
  entry_buffer_1 = entry_buffer;
  if ( !*entry_buffer )
    return 0;
  do
  {
    entry_buffer_curchr1 = *entry_buffer_1++;
    if ( entry_buffer_curchr1 == ':' )
      return (char *)entry_buffer;
  }
  while ( *entry_buffer_1 );
  fpath_1 = fpath;
  if ( !fpath || !*fpath )
    return (char *)entry_buffer;
  while ( *++fpath_1 )
    ;
  fpath_1_minus_1 = fpath_1 - 1;
  entry_buffer_curchr2 = *entry_buffer;
  if ( entry_buffer_curchr2 == '/' || entry_buffer_curchr2 == '\\' )
  {
    if ( fpath < fpath_1_minus_1 )
    {
      while ( *fpath_1_minus_1 != ':' )
      {
        if ( fpath >= --fpath_1_minus_1 )
          goto LABEL_24;
      }
      goto LABEL_27;
    }
LABEL_24:
    fpath_1_curchr1 = *fpath_1_minus_1;
    if ( fpath_1_curchr1 != ':' && fpath_1_curchr1 != '/' )
    {
      condtmp1 = fpath_1_curchr1 != '\\';
      fpath_2 = fpath;
      if ( condtmp1 )
        goto LABEL_28;
    }
    goto LABEL_27;
  }
  if ( fpath >= fpath_1_minus_1 )
    goto LABEL_24;
  fpath_1_curchr2 = *fpath_1_minus_1;
  if ( fpath_1_curchr2 != ':' )
  {
    if ( fpath_1_curchr2 != '/' )
    {
      fpath_1_curchrhi1 = (u8)*fpath_1_minus_1 << 24;
      do
      {
        if ( fpath_1_curchrhi1 >> 24 == '\\' )
          break;
        if ( fpath >= --fpath_1_minus_1 )
          break;
        fpath_1_curchr3 = *fpath_1_minus_1;
        if ( fpath_1_curchr3 == ':' )
          goto LABEL_27;
        condtmp1 = fpath_1_curchr3 != '/';
        fpath_1_curchrhi1 = (u8)*fpath_1_minus_1 << 24;
      }
      while ( condtmp1 );
    }
    goto LABEL_24;
  }
LABEL_27:
  ++fpath_1_minus_1;
  fpath_2 = fpath;
LABEL_28:
  for ( i = netcnf_file_path; fpath_2 < fpath_1_minus_1; ++i )
  {
    fpath_2_curchr1 = *fpath_2++;
    *i = fpath_2_curchr1;
  }
  entry_buffer_2 = entry_buffer;
  while ( 1 )
  {
    entry_buffer_curchr3 = *entry_buffer_2;
    entry_buffer_curchr4 = *entry_buffer_2++;
    if ( !entry_buffer_curchr3 )
      break;
    *i++ = entry_buffer_curchr4;
  }
  *i = 0;
  return netcnf_file_path;
}

//----- (00408B20) --------------------------------------------------------
int do_get_filesize_inner(int fd)
{
  int lseek_end_res; // $s0
  int result; // $v0
  int lseek_start_res; // $a0

  lseek_end_res = lseek(fd, 0, 2);
  if ( lseek_end_res >= 0 )
  {
    lseek_start_res = lseek(fd, 0, 0);
    result = lseek_end_res;
    if ( lseek_start_res < 0 )
    {
      result = -18;
      if ( lseek_start_res != -5 )
        return -6;
    }
  }
  else
  {
    result = -18;
    if ( lseek_end_res != -5 )
      return -6;
  }
  return result;
}

//----- (00408B9C) --------------------------------------------------------
int is_special_file_path(const char *netcnf_path)
{
  int result; // $v0
  bool condtmp1; // dc

  if ( g_callbacks.type == 1 )
  {
    condtmp1 = strncmp(netcnf_path, "mc", 2) == 0;
    result = 0;
    if ( condtmp1 )
      return 1;
  }
  else
  {
    if ( g_callbacks.type != 2 )
      return 1;
    condtmp1 = strncmp(netcnf_path, "ext", 3) != 0;
    result = 0;
    if ( !condtmp1 )
      return 1;
  }
  return result;
}
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (00408C18) --------------------------------------------------------
u32 do_init_callback_handles()
{
  int handleind2; // $a0
  int handleind1; // $v1
  u32 result; // $v0

  handleind2 = 0;
  handleind1 = 0;
  do
  {
    g_callback_handle_infos[handleind1].m_fd = -1;
    g_callback_handle_infos[handleind1].m_filesize = 0;
    g_callback_handle_infos[handleind1].m_allocstate = 0;
    result = ++handleind2 < 4;
    ++handleind1;
  }
  while ( handleind2 < 4 );
  return result;
}

//----- (00408C60) --------------------------------------------------------
int do_get_empty_callback_handle(int in_fd, int in_allocstate)
{
  int indtmp1; // $a3
  struct netcnf_callback_handle_info *curhandle; // $a2
  int indtmp2; // $t0
  int result; // $v0
  int handlecnt; // $v1

  indtmp1 = 0;
  curhandle = g_callback_handle_infos;
  indtmp2 = 0;
  do
  {
    result = indtmp1;
    if ( curhandle->m_fd == -1 )
    {
      handlecnt = g_open_callback_handle_count;
      curhandle->m_fd = in_fd;
      g_callback_handle_infos[indtmp2].m_allocstate = in_allocstate;
      g_open_callback_handle_count = handlecnt + 1;
      return result;
    }
    ++curhandle;
    ++indtmp1;
    ++indtmp2;
  }
  while ( indtmp1 < 4 );
  return -1;
}
// 40C7E0: using guessed type int g_open_callback_handle_count;

//----- (00408CCC) --------------------------------------------------------
int do_filesize_callback_handles(int in_fd, int in_allocstate)
{
  int indtmp1; // $a2
  int indtmp2; // $v1

  indtmp1 = 0;
  indtmp2 = 0;
  do
  {
    if ( g_callback_handle_infos[indtmp2].m_fd == in_fd
      && (g_callback_handle_infos[indtmp2].m_allocstate == in_allocstate || !in_allocstate) )
    {
      return indtmp1;
    }
    ++indtmp1;
    ++indtmp2;
  }
  while ( indtmp1 < 4 );
  return -1;
}

//----- (00408D2C) --------------------------------------------------------
int do_clear_callback_handles(int fd, int allocmatch)
{
  int indtmp; // $a3
  int *p_m_allocstate; // $a2
  struct netcnf_callback_handle_info *i; // $v1
  int count_tmp; // $v0
  int condtmp; // $v0

  indtmp = 0;
  p_m_allocstate = &g_callback_handle_infos[0].m_allocstate;
  for ( i = g_callback_handle_infos; i->m_fd != fd || *p_m_allocstate != allocmatch; ++i )
  {
    p_m_allocstate += 73;
    condtmp = ++indtmp < 4;
    if ( indtmp >= 4 )
      return condtmp;
  }
  count_tmp = g_open_callback_handle_count;
  i->m_fd = -1;
  *p_m_allocstate = 0;
  condtmp = count_tmp - 1;
  g_open_callback_handle_count = condtmp;
  return condtmp;
}
// 40C7E0: using guessed type int g_open_callback_handle_count;

//----- (00408DA0) --------------------------------------------------------
const char *do_colon_callback_handles(const char *netcnf_path, char *device)
{
  char *index_res; // $s1
  const char *result; // $v0
  int devnameend; // $s0
  const char *pathportionstart; // $s1
  bool condtmp1; // dc

  index_res = index(netcnf_path, ':');
  result = 0;
  if ( index_res )
  {
    devnameend = index_res - netcnf_path + 1;
    if ( devnameend >= 17 )
    {
      return 0;
    }
    else
    {
      memcpy(device, netcnf_path, index_res - netcnf_path + 1);
      device[devnameend] = 0;
      pathportionstart = index_res + 1;
      condtmp1 = strlen(pathportionstart) + 1 >= 257;
      result = 0;
      if ( !condtmp1 )
        return pathportionstart;
    }
  }
  return result;
}

//----- (00408E40) --------------------------------------------------------
int do_open_netcnf(const char *netcnf_path, int file_flags, int file_mode)
{
  const char *netcnf_path_1; // $s0
  int special_pathcond; // $v0
  int result; // $v0
  const char *cbind; // $v0
  const char *cbind_1; // $s3
  int openret1; // $s2
  int empty_callback_handle; // $s0
  int filesz2; // $v0
  char pathconcat[16]; // [sp+18h] [-18h] BYREF
  int filesz1; // [sp+28h] [-8h] BYREF

  netcnf_path_1 = netcnf_path;
  if ( !g_callbacks.open )
    return open(netcnf_path, file_flags, file_mode);
  special_pathcond = is_special_file_path(netcnf_path);
  netcnf_path = netcnf_path_1;
  if ( !special_pathcond )
    return open(netcnf_path, file_flags, file_mode);
  result = -1;
  if ( g_open_callback_handle_count < 4 )
  {
    cbind = do_colon_callback_handles(netcnf_path_1, pathconcat);
    cbind_1 = cbind;
    if ( cbind )
    {
      openret1 = ((int (*)(char *, const char *, int, int, int *))g_callbacks.open)(
                   pathconcat,
                   cbind,
                   file_flags,
                   file_mode,
                   &filesz1);
      if ( openret1 >= 0 )
      {
        empty_callback_handle = do_get_empty_callback_handle(openret1, 1);
        strcpy(g_callback_handle_infos[empty_callback_handle].m_device, pathconcat);
        strcpy(g_callback_handle_infos[empty_callback_handle].m_pathname, cbind_1);
        filesz2 = filesz1;
        g_callback_handle_infos[empty_callback_handle].m_buf = 0;
        g_callback_handle_infos[empty_callback_handle].m_bufpos = 0;
        g_callback_handle_infos[empty_callback_handle].m_filesize = filesz2;
      }
      return openret1;
    }
    else
    {
      return -1;
    }
  }
  return result;
}
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;
// 40C344: using guessed type int (*)(u32, u32, u32, u32, u32);
// 40C7E0: using guessed type int g_open_callback_handle_count;

//----- (00408F8C) --------------------------------------------------------
size_t do_read_callback_handles(int handlefd, int fd, void *ptr, size_t size)
{
  struct netcnf_callback_handle_info *cbh; // $s0
  void *heapmem; // $v0
  size_t result; // $v0
  int readres1; // $v0
  void *ptr_1; // $a0

  cbh = &g_callback_handle_infos[handlefd];
  if ( cbh->m_bufpos )
  {
    ptr_1 = ptr;
  }
  else
  {
    heapmem = do_alloc_heapmem(cbh->m_filesize);
    cbh->m_buf = heapmem;
    if ( !heapmem )
      return -1;
    readres1 = ((int (*)(int, char *, char *, void *, u32, int))g_callbacks.read)(
                 fd,
                 cbh->m_device,
                 cbh->m_pathname,
                 cbh->m_buf,
                 0,
                 cbh->m_filesize);
    ptr_1 = ptr;
    if ( readres1 != cbh->m_filesize )
    {
      do_free_heapmem(cbh->m_buf);
      result = -1;
      cbh->m_buf = 0;
      return result;
    }
  }
  memcpy(ptr_1, (char *)cbh->m_buf + cbh->m_bufpos, size);
  result = size;
  cbh->m_bufpos += size;
  return result;
}
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;
// 40C348: using guessed type int (*)(u32, u32, u32, u32, u32, u32);

//----- (0040908C) --------------------------------------------------------
size_t do_readfile_netcnf(int fd, void *ptr, int size)
{
  int cbind; // $a0

  if ( !g_callbacks.read )
    return read(fd, ptr, size);
  cbind = do_filesize_callback_handles(fd, 1);
  if ( cbind == -1 )
    return read(fd, ptr, size);
  else
    return do_read_callback_handles(cbind, fd, ptr, size);
}
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (0040910C) --------------------------------------------------------
int do_write_netcnf_no_encode(int fd, void *ptr, int size)
{
  if ( !g_callbacks_set || g_callbacks.type == 2 )
    return write(fd, ptr, size);
  printf("[err] netcnf write()\n");
  return -1;
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (00409164) --------------------------------------------------------
int do_dopen_wrap(const char *fn)
{
  if ( !g_callbacks_set || g_callbacks.type == 2 )
    return dopen(fn);
  printf("[err] netcnf dopen()\n");
  return -1;
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (004091BC) --------------------------------------------------------
int do_dread_wrap(int fn, iox_dirent_t *buf)
{
  if ( !g_callbacks_set || g_callbacks.type == 2 )
    return dread(fn, buf);
  printf("[err] netcnf dread()\n");
  return -1;
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (00409214) --------------------------------------------------------
int do_remove_wrap(const char *fn)
{
  if ( !g_callbacks_set || g_callbacks.type == 2 )
    return remove(fn);
  printf("[err] netcnf remove()\n");
  return -1;
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (0040926C) --------------------------------------------------------
int do_close_netcnf(int fd)
{
  int cbind; // $s1
  int closeret; // $v0
  int cbind_1; // $s0
  void *m_buf; // $a0
  int closeret_1; // $s1

  if ( !g_callbacks.close )
    return close(fd);
  cbind = do_filesize_callback_handles(fd, 1);
  if ( cbind == -1 )
    return close(fd);
  closeret = ((int (*)(int))g_callbacks.close)(fd);
  cbind_1 = cbind;
  m_buf = g_callback_handle_infos[cbind].m_buf;
  closeret_1 = closeret;
  do_free_heapmem(m_buf);
  g_callback_handle_infos[cbind_1].m_buf = 0;
  do_clear_callback_handles(fd, 1);
  return closeret_1;
}
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;
// 40C34C: using guessed type int (*)(u32);

//----- (00409328) --------------------------------------------------------
int do_dclose_wrap(int fd)
{
  if ( !g_callbacks_set || g_callbacks.type == 2 )
    return dclose(fd);
  printf("[err] netcnf dclose()\n");
  return -1;
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (00409380) --------------------------------------------------------
int do_filesize_netcnf(int fd)
{
  int cbind; // $v1

  cbind = do_filesize_callback_handles(fd, 0);
  if ( cbind == -1 )
    return do_get_filesize_inner(fd);
  else
    return g_callback_handle_infos[cbind].m_filesize;
}

//----- (004093E4) --------------------------------------------------------
int do_getstat_wrap(const char *fn, iox_stat_t *stat)
{
  if ( !g_callbacks_set || g_callbacks.type == 2 )
    return getstat(fn, stat);
  printf("[err] netcnf getstat()\n");
  return -1;
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (0040943C) --------------------------------------------------------
int do_chstat_mode_copyprotect_wrap(const char *fn)
{
  iox_stat_t statmode; // [sp+10h] [-40h] BYREF

  if ( !g_callbacks_set || g_callbacks.type == 2 )
  {
    do_getstat_wrap(fn, &statmode);
    statmode.mode |= 8u;
    chstat(fn, &statmode, 1u);
    return 0;
  }
  else
  {
    printf("[err] netcnf chstat()\n");
    return -1;
  }
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (004094C0) --------------------------------------------------------
u32 do_set_callback_inner(sceNetCnfCallback_t *pcallback)
{
  int (*open)(const char *, const char *, int, int, int *); // $a3
  int (*read)(int, const char *, const char *, void *, int, int); // $t0

  if ( pcallback )
  {
    open = pcallback->open;
    read = pcallback->read;
    g_callbacks.type = pcallback->type;
    g_callbacks.open = open;
    g_callbacks.read = read;
    g_callbacks.close = pcallback->close;
    g_callbacks_set = 1;
  }
  else
  {
    memset(&g_callbacks, 0, sizeof(g_callbacks));
    g_callbacks_set = 0;
  }
  return do_init_callback_handles();
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;
// 40C344: using guessed type int (*)(u32, u32, u32, u32, u32);
// 40C348: using guessed type int (*)(u32, u32, u32, u32, u32, u32);
// 40C34C: using guessed type int (*)(u32);

//----- (00409540) --------------------------------------------------------
int do_init_heap()
{
  int result; // $v0

  if ( g_netcnf_heap )
    return -2;
  g_netcnf_heap = CreateHeap(1024, 1);
  result = -1;
  if ( g_netcnf_heap )
    return 0;
  return result;
}

//----- (00409590) --------------------------------------------------------
void *do_alloc_heapmem(size_t nbytes)
{
  return AllocHeapMemory(g_netcnf_heap, nbytes);
}

//----- (004095BC) --------------------------------------------------------
int do_free_heapmem(void *ptr)
{
  int result; // $v0

  if ( ptr )
    return FreeHeapMemory(g_netcnf_heap, ptr);
  return result;
}

//----- (004095EC) --------------------------------------------------------
void do_delete_heap()
{
  DeleteHeap(g_netcnf_heap);
  g_netcnf_heap = 0;
}
