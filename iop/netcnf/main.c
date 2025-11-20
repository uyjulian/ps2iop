
#include "irx_imports.h"
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

u32 get_check_provider_eq_zero(void);
void do_print_usage(void);
int do_module_load(int ac, char **av);
int do_module_unload();
int _start(int ac, char **av);



















int do_read_ilink_id();
int do_read_netcnf_decode(const char *netcnf_path, char **netcnf_heap_ptr);
int do_write_netcnf_encode(const char *netcnf_path, void *buf, int netcnf_len);
int do_read_netcnf_no_decode(const char *netcnf_path, char **netcnf_heap_ptr);
void do_init_xor_magic(char *in_id_buf);
int magic_shift_write_netcnf_2(int inshft, int buflen);
int magic_shift_read_netcnf_2(int inshft, int buflen);
int magic_shift_write_netcnf_1(int inshft, int buflen);
int magic_shift_read_netcnf_1(int inshft, int buflen);
void do_safe_strcpy(char *dst, size_t maxlen, const char *src, int linenum);
void do_safe_strcat(char *dst, size_t maxlen, const char *src, int linenum);
void do_safe_make_pathname(char *dst, size_t maxlen, const char *srcdir, const char *srcbase);
void do_safe_make_name(char *dst, size_t maxlen, const char *src1, const char *src2);
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
void do_some_pair_handling(char *fpath, int type, const char *src, sceNetCnfEnv_t *e);
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
void do_init_ifc_inner(sceNetCnfInterface_t *ifc);
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
void do_address_to_string_inner(char *dst, unsigned int srcint);
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
void do_init_callback_handles(void);
int do_get_empty_callback_handle(int in_fd, int in_allocstate);
int do_filesize_callback_handles(int in_fd, int in_allocstate);
void do_clear_callback_handles(int fd, int allocmatch);
const char *do_colon_callback_handles(const char *netcnf_path, char *device);
int do_open_netcnf(const char *netcnf_path, int file_flags, int file_mode);
size_t do_read_callback_handles(int handlefd, int fd, void *ptr, size_t size);
size_t do_readfile_netcnf(int fd, void *ptr, int size);
int do_write_netcnf_no_encode(int fd, void *ptr, int size);
int do_dopen_wrap(const char *fn);
int do_dread_wrap(int fn, iox_dirent_t *buf);
int do_remove_wrap(const char *fn);
void do_close_netcnf(int fd);
void do_dclose_wrap(int fd);
int do_filesize_netcnf(int fd);
void do_getstat_wrap(const char *fn, iox_stat_t *stat);
void do_chstat_mode_copyprotect_wrap(const char *fn);
void do_set_callback_inner(sceNetCnfCallback_t *pcallback);
int do_init_heap(void);
void *do_alloc_heapmem(size_t nbytes);
void do_free_heapmem(void *ptr); // idb
void do_delete_heap(void);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_netcnf;
int g_null_string = 0; // weak
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
u32 get_check_provider_eq_zero(void)
{
  return g_no_check_provider == 0;
}
// 40AC6C: using guessed type int g_no_check_provider;

//----- (00400010) --------------------------------------------------------
void do_print_usage(void)
{
  printf("Usage: netcnf [<option>] icon=<icon-path> iconsys=<iconsys-path>\n");
  printf("  <option>:\n");
  printf("    -no_check_capacity        do not check capacity\n");
  printf("    -no_check_provider        do not check special provider\n");
}

//----- (00400068) --------------------------------------------------------
int do_module_load(int ac, char **av)
{
  int semid; // $v0
  int ac_cur; // $s1
  int heap_inited; // $v0
  int regres; // $v0
  iop_sema_t semaparam; // [sp+10h] [-10h] BYREF
  int err;

  if ( ac < 3 )
  {
    do_print_usage();
    return 1;
  }
  err = 0;
  semaparam.attr = 1;
  semaparam.initial = 1;
  semaparam.max = 1;
  semaparam.option = 0;
  semid = CreateSema(&semaparam);
  g_semid = semid;
  if ( semid <= 0 )
  {
    printf("netcnf: CreateSema (%d)\n", semid);
    return 1;
  }
  g_icon_value[0] = 0;
  g_iconsys_value[0] = 0;
  for ( ac_cur = 1; ac_cur < ac; ac_cur += 1 )
  {
    if ( !strncmp("icon=", av[ac_cur], 5) )
    {
      strcpy(g_icon_value, av[ac_cur] + 5);
    }
    else if ( !strncmp("iconsys=", av[ac_cur], 8) )
    {
      strcpy(g_iconsys_value, av[ac_cur] + 8);
    }
    else if ( !strcmp("-no_check_capacity", av[ac_cur]) )
    {
      g_no_check_capacity = 1;
    }
    else if ( !strcmp("-no_check_provider", av[ac_cur]) )
    {
      g_no_check_provider = 1;
    }
    else
    {
      err = 1;
      break;
    }
  }
  if ( !g_icon_value[0] || !g_iconsys_value[0] )
  {
    err = 1;
  }
  if ( !err )
  {
    heap_inited = do_init_heap();
    if ( heap_inited < 0 )
    {
      printf("netcnf: init_heap(%d)\n", heap_inited);
    }
    else
    {
      regres = RegisterLibraryEntries(&_exp_netcnf);
      if ( !regres )
        return 2;
      printf("netcnf: RegisterLibraryEntries(%d)\n", regres);
      do_delete_heap();
    }
  }
  if ( err == 1 )
  {
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

  errstate = 0;
  relres = ReleaseLibraryEntries(&_exp_netcnf);
  if ( relres )
  {
    printf("netcnf: ReleaseLibraryEntries (%d)\n", relres);
  }
  else
  {
    errstate = 1;
    relres = DeleteSema(g_semid);
    if ( relres )
    {
      printf("netcnf: DeleteSema (%d)\n", relres);
    }
    else
    {
      errstate = 2;
    }
  }
  if ( errstate == 2 )
  {
    do_delete_heap();
    return 1;
  }
  else if ( errstate == 1 )
  {
    RegisterLibraryEntries(&_exp_netcnf);
  }
  return 2;
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
  unsigned int paddr_tmp; // [sp+10h] [-8h] BYREF

  paddr_tmp = 0;
  if ( !buf || do_name_2_address_inner(&paddr_tmp, buf) )
  {
    bzero(paddr, 20);
    bcopy(&paddr_tmp, paddr->data, 4);
    return 0;
  }
  return -1;
}

//----- (00400940) --------------------------------------------------------
int sceNetCnfAddress2String(char *buf, int len, sceNetCnfAddress_t *paddr)
{
  int buflen; // $a2
  char buf_tmp[24]; // [sp+10h] [-20h] BYREF
  unsigned int srcintx; // [sp+28h] [-8h] BYREF

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
  return -1;
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

  retres = do_conv_a2s_inner(sp_, dp_, len);
  if ( !retres )
  {
    if ( len >= strlen(sp_) + 1 )
    {
      strcpy(dp_, sp_);
      return 0;
    }
    return -19;
  }
  return retres;
}

//----- (00400B20) --------------------------------------------------------
int sceNetCnfConvS2A(char *sp_, char *dp_, int len)
{
  int retres; // $v0

  retres = do_conv_s2a_inner(sp_, dp_, len);
  if ( !retres )
  {
    if ( len >= strlen(sp_) + 1 )
    {
      strcpy(dp_, sp_);
      return 0;
    }
    return -19;
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

//----- (00400D10) --------------------------------------------------------
int do_read_ilink_id()
{
  int i; // $s0

  for ( i = 0; i < 20; i += 1 )
  {
    g_id_result = 0;
    if ( sceCdRI((u8 *)g_id_buffer, &g_id_result) == 1 )
    {
      if ( !g_id_result )
        return 0;
    }
    DelayThread(100000);
  }
  return -13;
}

//----- (00400DA8) --------------------------------------------------------
int do_read_netcnf_decode(const char *netcnf_path, char **netcnf_heap_ptr)
{
  int result; // $v0
  int fd; // $s5
  int netcnf_size; // $v0
  char *heapmem; // $v0
  char *netcnf_data; // $s2
  int xorind1; // $s1
  int xoroffs; // $s4
  size_t readres; // $s0
  int xorind2_1; // $s1
  int xorind3_1; // $v1
  int xorind2_2; // $s1
  int xorind3_2; // $v1

  *netcnf_heap_ptr = 0;
  result = do_read_ilink_id();
  if ( result < 0 )
    return result;
  do_init_xor_magic(g_id_buffer);
  fd = do_open_netcnf(netcnf_path, 1, 0);
  if ( fd < 0 )
  {
    if ( fd == -5 )
      return -18;
    return -3;
  }
  netcnf_size = do_filesize_netcnf(fd);
  if ( netcnf_size < 0 )
  {
    do_close_netcnf(fd);
    return netcnf_size;
  }
  heapmem = (char *)do_alloc_heapmem(netcnf_size + 1);
  *netcnf_heap_ptr = heapmem;
  if ( !heapmem )
  {
    do_close_netcnf(fd);
    return -2;
  }
  netcnf_data = heapmem;
  xorind1 = 0;
  xoroffs = 0;
  readres = 0;
  while ( netcnf_size >= 2 )
  {
    readres = do_readfile_netcnf(fd, netcnf_data, 2);
    if ( readres < 0 )
      break;
    *(u16 *)netcnf_data = ~*(u16 *)netcnf_data;
    *(u16 *)netcnf_data = magic_shift_read_netcnf_1(*(u16 *)netcnf_data, (u8)g_id_xorbuf[xorind1 + 2]);
    xorind2_1 = xorind1 + 1;
    xorind3_1 = 0;
    if ( xorind2_1 != 24 )
      xorind3_1 = xorind2_1;
    xorind1 = xorind3_1;
    netcnf_data += 2;
    netcnf_size -= 2;
    xoroffs += 2;
    if ( !netcnf_size )
      break;
  }
  if ( readres >= 0 )
  {
    if ( netcnf_size )
    {
      readres = do_readfile_netcnf(fd, netcnf_data, 1);
      if ( readres >= 0 )
      {
        *netcnf_data = ~*netcnf_data;
        *netcnf_data = magic_shift_read_netcnf_2(*netcnf_data, (u8)g_id_xorbuf[xorind1 + 2]);
        xorind2_2 = xorind1 + 1;
        xorind3_2 = 0;
        if ( xorind2_2 != 24 )
          xorind3_2 = xorind2_2;
        xorind1 = xorind3_2;
        --netcnf_size;
        ++xoroffs;
      }
    }
    if ( !netcnf_size )
    {
      netcnf_data[xoroffs] = 0;
      do_close_netcnf(fd);
      return xoroffs;
    }
  }
  do_free_heapmem(netcnf_data);
  *netcnf_heap_ptr = 0;
  do_close_netcnf(fd);
  if ( readres != -5 )
    return -4;
  return -18;
}

//----- (00400FD4) --------------------------------------------------------
int do_write_netcnf_encode(const char *netcnf_path, void *buf, int netcnf_len)
{
  int result; // $v0
  int fd; // $s3
  u16 *buf_1; // $s5
  int netcnf_len_1; // $s2
  int xorind1; // $s1
  int xoroffs; // $s4
  int xorind2_1; // $s1
  int xorind3_1; // $v1
  int writeres; // $s0
  int xorind2_2; // $s1
  int xorind3_2; // $v1
  u16 bufflipx1; // [sp+10h] [-8h] BYREF
  char bufflipx2; // [sp+12h] [-6h] BYREF

  result = do_read_ilink_id();
  if ( result < 0 )
    return result;
  do_init_xor_magic(g_id_buffer);
  fd = do_open_netcnf(netcnf_path, 1538, 511);
  buf_1 = (u16 *)buf;
  if ( fd < 0 )
  {
    if ( fd == -5 )
      return -18;
    return -3;
  }
  netcnf_len_1 = netcnf_len;
  xorind1 = 0;
  xoroffs = 0;
  writeres = 0;
  while ( writeres >= 0 )
  {
    while ( netcnf_len_1 >= 2 )
    {
      xorind2_1 = xorind1 + 1;
      xorind3_1 = 0;
      bufflipx1 = magic_shift_write_netcnf_1(*buf_1, (u8)g_id_xorbuf[xorind1 + 2]);
      if ( xorind2_1 != 24 )
        xorind3_1 = xorind2_1;
      xorind1 = xorind3_1;
      bufflipx1 = ~bufflipx1;
      writeres = do_write_netcnf_no_encode(fd, &bufflipx1, 2);
      ++buf_1;
      if ( writeres < 0 )
        break;
      netcnf_len_1 -= 2;
      xoroffs += 2;
    }
    if ( writeres >= 0 && !netcnf_len_1 )
    {
      do_close_netcnf(fd);
      return xoroffs;
    }
    if ( writeres >= 0 )
    {
      xorind2_2 = xorind1 + 1;
      xorind3_2 = 0;
      bufflipx2 = magic_shift_write_netcnf_2(*(u8 *)buf_1, (u8)g_id_xorbuf[xorind1 + 2]);
      if ( xorind2_2 != 24 )
        xorind3_2 = xorind2_2;
      xorind1 = xorind3_2;
      bufflipx2 = ~bufflipx2;
      writeres = do_write_netcnf_no_encode(fd, &bufflipx2, 1);
      --netcnf_len_1;
      ++xoroffs;
    }    
  }
  do_close_netcnf(fd);
  if ( writeres != -5 )
    return -5;
  return -18;
}
// 400FD4: using guessed type char bufflipx2[6];

//----- (00401188) --------------------------------------------------------
int do_read_netcnf_no_decode(const char *netcnf_path, char **netcnf_heap_ptr)
{
  int fd; // $v0
  int netcnf_size; // $v0
  char *netcnf_data; // $v0

  *netcnf_heap_ptr = 0;
  fd = do_open_netcnf(netcnf_path, 1, 0);
  fd = fd;
  if ( fd < 0 )
  {
    if ( fd != -5 )
      return -3;
    return -18;
  }
  netcnf_size = do_filesize_netcnf(fd);
  if ( netcnf_size < 0 )
  {
    do_close_netcnf(fd);
    return netcnf_size;
  }
  netcnf_data = (char *)do_alloc_heapmem(netcnf_size + 1);
  *netcnf_heap_ptr = netcnf_data;
  if ( !netcnf_data )
  {
    do_close_netcnf(fd);
    return -2;
  }
  netcnf_size = do_readfile_netcnf(fd, netcnf_data, netcnf_size);
  if ( netcnf_size < 0 )
  {
    do_free_heapmem(*netcnf_heap_ptr);
    *netcnf_heap_ptr = 0;
    do_close_netcnf(fd);
    if ( netcnf_size != -5 )
      return -4;
    return -18;
  }
  (*netcnf_heap_ptr)[netcnf_size] = 0;
  do_close_netcnf(fd);
  return netcnf_size;
}

//----- (0040127C) --------------------------------------------------------
void do_init_xor_magic(char *in_id_buf)
{
  int curoffs2; // $a2

  for ( curoffs2 = 0; (curoffs2 + 1) < 8; curoffs2 += 1 )
  {
    g_id_xorbuf[(curoffs2 * 3) + 2] = ((u8)in_id_buf[curoffs2] >> 5) + 1;
    g_id_xorbuf[(curoffs2 * 3) + 3] = (((u8)in_id_buf[curoffs2] >> 2) & 7) + 1;
    g_id_xorbuf[(curoffs2 * 3) + 4] = (in_id_buf[curoffs2] & 3) + 1;
  }
}

//----- (004012F4) --------------------------------------------------------
int magic_shift_write_netcnf_2(int inshft, int buflen)
{
  for ( ; buflen; buflen -= 1 )
    inshft = ((u8)inshft >> 7) | (2 * inshft);
  return (u8)inshft;
}

//----- (0040131C) --------------------------------------------------------
int magic_shift_read_netcnf_2(int inshft, int buflen)
{
  for ( ; buflen; buflen -= 1 )
    inshft = ((u8)inshft >> 1) | (inshft << 7);
  return (u8)inshft;
}

//----- (00401344) --------------------------------------------------------
int magic_shift_write_netcnf_1(int inshft, int buflen)
{
  for ( ; buflen; buflen -= 1 )
    inshft = ((u16)inshft >> 15) | (2 * inshft);
  return (u16)inshft;
}

//----- (0040136C) --------------------------------------------------------
int magic_shift_read_netcnf_1(int inshft, int buflen)
{
  for ( ; buflen; buflen -= 1 )
    inshft = ((u16)inshft >> 1) | (inshft << 15);
  return (u16)inshft;
}

//----- (004013A0) --------------------------------------------------------
void do_safe_strcpy(char *dst, size_t maxlen, const char *src, int linenum)
{
  if ( strlen(src) < maxlen )
  {
    strcpy(dst, src);
  }
  else
  {
    printf("[netcnf] strcpy failed(%d)\n", linenum);
  }
}

//----- (0040141C) --------------------------------------------------------
void do_safe_strcat(char *dst, size_t maxlen, const char *src, int linenum)
{
  if ( strlen(dst) + strlen(src) < maxlen )
  {
    strcat(dst, src);
  }
  else
  {
    printf("[netcnf] strcat failed(%d)\n", linenum);
  }
}

//----- (004014AC) --------------------------------------------------------
void do_safe_make_pathname(char *dst, size_t maxlen, const char *srcdir, const char *srcbase)
{
  if ( strlen(srcdir) + strlen(srcbase) + 1 < maxlen )
  {
    strcpy(dst, srcdir);
    strcat(dst, "/");
    strcat(dst, srcbase);
  }
  else
  {
    printf("[netcnf] make_pathname failed\n");
  }
}

//----- (00401560) --------------------------------------------------------
void do_safe_make_name(char *dst, size_t maxlen, const char *src1, const char *src2)
{
  if ( strlen(src1) + strlen(src2) < maxlen )
  {
    strcpy(dst, src1);
    strcat(dst, src2);
  }
  else
  {
    printf("[netcnf] make_name failed\n");
  }
}

//----- (00401600) --------------------------------------------------------
int do_check_capacity_inner2(const char *fpath, int minsize)
{
  int curdevnameind; // $t0
  int zonesz; // kr00_4
  int zonefree; // $t2
  char devname[8]; // [sp+18h] [-8h] BYREF

  for ( curdevnameind = 0; curdevnameind < 5; curdevnameind += 1 )
  {
    if ( fpath[curdevnameind] == ':' )
    {
      *(u16 *)&devname[curdevnameind] = fpath[curdevnameind];
      zonesz = iomanX_devctl(devname, 0x5001, 0, 0, 0, 0);
      zonefree = iomanX_devctl(devname, 0x5002, 0, 0, 0, 0) * (zonesz / 1024);
      if ( zonefree < minsize )
        return -16;
      return 0;
    }
    devname[curdevnameind] = fpath[curdevnameind];
  }
  return -9;
}
// 401600: using guessed type char devname[8];

//----- (004016F0) --------------------------------------------------------
int do_check_capacity_inner(const char *fpath)
{
  int minsize; // $a1

  if ( strncmp(fpath, "mc", 2) )
  {
    if ( strncmp(fpath, "pfs", 3) != 0 )
      return -9;
    minsize = 0xF4;
  }
  else
  {
    minsize = 0x5E;
  }
  return do_check_capacity_inner2(fpath, minsize);
}

//----- (00401758) --------------------------------------------------------
int do_handle_combination_path(int type, const char *fpath, char *dst, size_t maxlen, char *usr_name)
{
  char *i; // $s0
  int devnum_offs; // $s1
  int devnr; // $s1
  char devnum[8]; // [sp+10h] [-8h] BYREF

  if ( !usr_name )
    return -11;
  do_safe_strcpy(dst, maxlen, usr_name, 139);
  if ( type )
    return 0;
  for ( i = dst; !isdigit(*i); i += 1 );
  for ( devnum_offs = 0; devnum_offs < 4 && isdigit(i[devnum_offs]); devnum_offs += 1 )
  {
    devnum[devnum_offs] = i[devnum_offs];
  }
  if ( devnum_offs >= 4 )
    return -11;
  devnum[devnum_offs] = 0;
  devnr = strtol(devnum, 0, 10);
  if ( !strncmp(fpath, "mc", 2) ? ((unsigned int)(devnr - 1) >= 6) : ((!strncmp(fpath, "pfs", 3) != 0) ? (unsigned int)(devnr - 1) >= 0xA : (unsigned int)(devnr - 1) >= 0x3E8) )
    return -11;
  do_safe_make_name(dst, maxlen, "Combination", devnum);
  return 0;
}
// 401758: using guessed type char devnum[8];

//----- (004018B8) --------------------------------------------------------
int do_copy_netcnf_path(const char *netcnf_path_1, const char *netcnf_path_2)
{
  int fd2; // $s2
  int fd1; // $s1
  int readres; // $v0
  int writeres; // $v0
  char tmpbuf[512]; // [sp+10h] [-200h] BYREF

  fd2 = do_open_netcnf(netcnf_path_2, 1538, 511);
  if ( fd2 < 0 )
    return -3;
  fd1 = do_open_netcnf(netcnf_path_1, 1, 0);
  if ( fd1 >= 0 )
  {
    while ( 1 )
    {
      readres = do_readfile_netcnf(fd1, tmpbuf, 512);
      if ( readres <= 0 )
        break;
      writeres = do_write_netcnf_no_encode(fd2, tmpbuf, readres);
      if ( readres != writeres )
      {
        do_close_netcnf(fd2);
        do_close_netcnf(fd1);
        return -5;
      }
    }
    do_close_netcnf(fd2);
    do_close_netcnf(fd1);
    if ( readres >= 0 )
      return 0;
  }
  else
  {
    do_close_netcnf(fd2);
    return -3;
  }
  return -4;
}

//----- (00401994) --------------------------------------------------------
char *do_write_memcard_pathcopy(char *dst, size_t maxlen, const char *src)
{
  char *dst_end_slash; // $a0

  do_safe_strcpy(dst, maxlen, src, 218);
  for ( dst_end_slash = &dst[strlen(dst)]; *dst_end_slash != '/'; dst_end_slash -= 1 );
  for ( ; *dst_end_slash == '/'; dst_end_slash -= 1 );
  if ( *dst_end_slash == ':' )
    return 0;
  dst_end_slash[1] = 0;
  return dst;
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
  const char *pathname; // $a2
  int maxbuf; // $a3

  do_safe_strcpy(fpath, maxlen, fname, 266);
  index_res = index(fpath, ':');
  if ( !index_res )
    return -9;
  if ( strncmp(fpath, "mc", 2) )
  {
    if ( strncmp(fpath, "pfs", 3) != 0 )
      return 0;
    index_res[1] = 0;
    pathname = "/etc/network/net.db";
    maxbuf = 279;
  }
  else
  {
    index_res[1] = 0;
    pathname = "/BWNETCNF/BWNETCNF";
    maxbuf = 275;
  }
  do_safe_strcat(fpath, maxlen, pathname, maxbuf);
  return 0;
}

//----- (00401BB0) --------------------------------------------------------
char *do_check_hoge_newline(char *buf)
{
  for ( ; *buf && *buf != '\n'; buf += 1 );
  return &buf[*buf == '\n'];
}

//----- (00401BFC) --------------------------------------------------------
int do_split_str_comma_index(char *dst, const char *src, int commaind)
{
  int commatmp_end; // $a2

  for ( commatmp_end = commaind; commatmp_end > 0; commatmp_end -= 1 )
  {
    for ( ; *src && *src != '\n' && *src != ','; src += 1 );
    if ( *src++ != ',' )
      return -1;
  }
  for ( ; *src && *src != ',' && *src != '\n' && *src != '\r'; src += 1 )
  {
    *dst = *src;
    ++dst;
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
  int dfd; // $s4
  int fileop_res; // $s0
  char *curheapbuf1; // $s0
  char cur_basepath[256]; // [sp+10h] [-390h] BYREF
  char cur_combpath[256]; // [sp+110h] [-290h] BYREF
  iox_dirent_t statname; // [sp+210h] [-190h] BYREF
  iox_stat_t statsize; // [sp+358h] [-48h] BYREF
  int iconsysflag; // [sp+398h] [-8h]
  int sizeflag;

  sysneticoflag = 1;
  iconsysflag = 1;
  if ( do_write_memcard_pathcopy(cur_basepath, 256, fpath) == 0 )
    return 0;
  dfd = do_dopen_wrap(cur_basepath);
  if ( dfd < 0 )
  {
    if ( dfd == -5 )
      return -18;
    return 0;
  }
  while ( 1 )
  {
    fileop_res = do_dread_wrap(dfd, &statname);
    if ( fileop_res <= 0 )
      break;
    sizeflag = 1;
    if ( strlen(statname.name) == 10 )
    {
      if ( !strncmp(&statname.name[6], ".cnf", 4) || !strncmp(&statname.name[6], ".dat", 4) )
      {
        for ( curheapbuf1 = (char *)netcnf_heap_buf; curheapbuf1 && *curheapbuf1; curheapbuf1 = do_check_hoge_newline(curheapbuf1) )
        {
          do_split_str_comma_index(cur_combpath, curheapbuf1, 2);
          if ( !strcmp(statname.name, cur_combpath) )
          {
            do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
            sizeflag = 0;
            break;
          }
        }
      }
    }
    else if ( !strncmp(fpath, "mc", 2) )
    {
      if ( !strcmp(statname.name, "SYS_NET.ICO") )
      {
        do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
        do_getstat_wrap(cur_combpath, &statsize);
        if ( statsize.size != 0x8398 )
        {
          sizeflag = 0;
        }
        else
        {
          sysneticoflag = 0;
        }
      }
      else if ( !strcmp(statname.name, "icon.sys") )
      {
        do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
        do_getstat_wrap(cur_combpath, &statsize);
        if ( statsize.size != 0x3C4 )
        {
          sizeflag = 0;
        }
        else
        {
          iconsysflag = 0;
        }
      }
      else if ( strcmp(statname.name, "BWNETCNF") )
      {
        do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
        sizeflag = 0;
      }
    }
    else if ( !strncmp(fpath, "pfs", 3) && strcmp(statname.name, "net.db") )
    {
      do_safe_make_pathname(cur_combpath, 256, cur_basepath, statname.name);
      sizeflag = 0;
    }
    if ( !sizeflag )
    {
      fileop_res = do_remove_wrap(cur_combpath);
      if ( fileop_res == -5 )
        break;
    }
  }
  if ( fileop_res == -5 )
  {
    do_dclose_wrap(dfd);
    return -18;
  }
  do_dclose_wrap(dfd);
  if ( !strncmp(fpath, "mc", 2) )
  {
    if ( sysneticoflag || iconsysflag )
      fileop_res = do_write_memcard_files(fpath, icon_value, iconsys_value);
    do_chstat_mode_copyprotect_wrap(cur_basepath);
  }
  return fileop_res;
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
  int retres; // $a0

  if ( !fpath )
    return -9;
  retres = do_read_netcnf_no_decode(fpath, netcnf_heap_ptr);
  if ( retres < 0 )
  {
    if ( retres != -3 )
      return retres;
    return 0;
  }
  return retres;
}

//----- (00402104) --------------------------------------------------------
int do_write_noencode_netcnf_atomic(const char *fpath, void *ptr, int size)
{
  int fd; // $s0
  int writeres; // $s1
  char fpath_comb[256]; // [sp+10h] [-100h] BYREF

  if ( !fpath )
    return -9;
  do_safe_make_name(fpath_comb, 256, fpath, ".tmp");
  fd = do_open_netcnf(fpath_comb, 1538, 511);
  if ( fd < 0 )
  {
    if ( fd == -5 )
      return -18;
    return -3;
  }
  writeres = do_write_netcnf_no_encode(fd, ptr, size);
  if ( size != writeres )
  {
    do_close_netcnf(fd);
    if ( writeres != -5 )
      return -5;
    return -18;
  }
  do_close_netcnf(fd);
  if ( iomanX_rename(fpath_comb, fpath) == -5 )
    return -18;
  // Unofficial: dead code removed
  return 0;
}
// 402104: using guessed type char fpath_comb[256];

//----- (00402230) --------------------------------------------------------
int do_remove_netcnf_dirname(char *dirpath, const char *entry_buffer)
{
  char *p_dirname; // $v0
  int remove_res_1; // $a0

  p_dirname = do_handle_netcnf_dirname(dirpath, entry_buffer, g_netcnf_file_path);
  if ( !p_dirname )
    return -7;
  remove_res_1 = do_remove_wrap(p_dirname);
  if ( remove_res_1 < 0 )
  {
    if ( remove_res_1 == -5 )
      return -18;
    return -7;
  }
  return 0;
}

//----- (00402290) --------------------------------------------------------
int do_get_count_list_inner(char *fname, int type, sceNetCnfList_t *p)
{
  int result; // $v0
  char *curheapbuf1; // $s0
  int curind1; // $s3
  char *usr_name; // $s1

  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result >= 0 )
  {
    result = do_read_current_netcnf_nodecode(g_dir_name, &g_count_list_heapptr);
    if ( result > 0 )
    {
      curind1 = 0;
      usr_name = p->usr_name;
      for ( curheapbuf1 = g_count_list_heapptr; *curheapbuf1; curheapbuf1 = do_check_hoge_newline(curheapbuf1) )
      {
        if ( do_type_check(type, curheapbuf1) > 0 )
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
  char *curheapbuf1; // $s0

  result = do_handle_fname(g_dir_name, 256, fname);
  if ( result >= 0 )
  {
    result = do_handle_combination_path(type, g_dir_name, g_combination_buf1, 256, usr_name);
    if ( result >= 0 )
    {
      result = do_read_current_netcnf_nodecode(g_dir_name, &g_load_entry_heapptr);
      if ( result >= 0 )
      {
        result = -8;
        if ( result != 0 )
        {
          for ( curheapbuf1 = g_load_entry_heapptr; *curheapbuf1; curheapbuf1 = do_check_hoge_newline(curheapbuf1) )
          {
            if ( do_type_check(type, curheapbuf1) >= 0
               && !do_split_str_comma_index(g_arg_fname, curheapbuf1, 3)
               && !strcmp(g_arg_fname, g_combination_buf1)
               && !do_split_str_comma_index(g_arg_fname, curheapbuf1, 2) )
            {
              do_free_heapmem(g_load_entry_heapptr);
              e->dir_name = g_dir_name;
              e->arg_fname = g_arg_fname;
              if ( type )
                e->req = 2;
              else
                e->req = 1;
              return do_load_conf_inner(e);
            }
          }
          do_free_heapmem(g_load_entry_heapptr);
          return -8;
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
  char *curptr1; // $s0
  unsigned int curbufsz1; // $s2
  int curindx; // $s1

  if ( arg_fname && *arg_fname )
  {
    for ( i = &arg_fname[strlen(arg_fname) - 1]; i >= arg_fname && *i != '.'; i -= 1 );
    curptr1 = (char *)(i - 1);
    if ( *i == '.' && curptr1 >= arg_fname )
    {
      curbufsz1 = 0;
      if ( isdigit(*curptr1) )
      {
        curindx = 1;
        for ( ; curptr1 >= arg_fname && isdigit(*curptr1); curptr1 -= 1 )
        {
          curbufsz1 += curindx * (*curptr1 - '0');
          curindx *= 10;
        }
        if ( curbufsz1 < 0x3E8 )
          g_ifc_buffer[curbufsz1] = 1;
      }
    }
  }
}

//----- (004026B0) --------------------------------------------------------
void do_some_pair_handling(char *fpath, int type, const char *src, sceNetCnfEnv_t *e)
{
  sceNetCnfEnv_t *heapmem; // $s1
  int conf_inner; // $v1
  struct sceNetCnfPair *i; // $s0
  const char *attach_ifc; // $a0

  if ( !do_split_str_comma_index(g_arg_fname, src, 2) )
  {
    heapmem = (sceNetCnfEnv_t *)do_alloc_heapmem(6256);
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
        if ( heapmem->root )
        {
          for ( i = heapmem->root->pair_head; i; i = i->forw )
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
      do_free_heapmem(heapmem);
    }
  }
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
  int result; // $v0
  int retres2; // $s1
  char *curentry1; // $s0
  int i; // $s2
  char *curentry2; // $s0
  int j; // $s2
  char *k; // $s0
  char *endbuf; // $s0
  int nrind; // $s0
  const char *fileext; // $s1
  int fd; // $v0
  char *dirname_buf1; // $s0
  char *cur_entry_buffer; // $s2
  int strlenx; // $s0
  int writeres; // $s1
  char atomicrenamepath[256]; // [sp+18h] [-108h] BYREF
  int retres1; // [sp+118h] [-8h]
  int maxflag;

  maxflag = 1;
  fd = -1;
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
  atomicrenamepath[0] = 0;
  result = do_handle_combination_path(type, g_dir_name, g_combination_buf1, 256, usr_name);
  if ( result < 0 )
    return result;
  retres1 = do_read_current_netcnf_nodecode(g_dir_name, &g_add_entry_heapptr);
  if ( retres1 < 0 )
    return result;
  retres2 = do_remove_old_config(g_dir_name, g_add_entry_heapptr, icon_value, iconsys_value);
  if ( retres2 < 0 )
    maxflag = 0;
  if ( maxflag )
  {
    bzero(g_ifc_buffer, 1000);
    if ( retres1 )
    {
      if ( !strncmp(g_dir_name, "mc", 2) )
      {
        i = 0;
        for ( curentry1 = g_add_entry_heapptr; *curentry1; curentry1 = do_check_hoge_newline(curentry1) )
        {
          if ( do_type_check(type, curentry1) == 1 )
            ++i;
        }
        if ( !type )
        {
          retres2 = -12;
          if ( i >= 6 )
            maxflag = 0;
        }
        else if ( type >= 0 && type < 3 )
        {
          retres2 = -12;
          if ( i >= 4 )
            maxflag = 0;
        }
      }
      else if ( !strncmp(g_dir_name, "pfs", 3) )
      {
        j = 0;
        for ( curentry2 = g_add_entry_heapptr; *curentry2; curentry2 = do_check_hoge_newline(curentry2) )
        {
          if ( do_type_check(type, curentry2) == 1 )
            ++j;
        }
        if ( !type )
        {
          retres2 = -12;
          if ( j >= 10 )
            maxflag = 0;
        }
        else if ( type >= 0 && type < 3 )
        {
          retres2 = -12;
          if ( j >= 30 )
            maxflag = 0;
        }
      }
      if ( maxflag )
      {
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
    }
  }
  if ( maxflag )
  {
    do_safe_strcpy(g_arg_fname, 256, g_dir_name, 740);
    for ( endbuf = &g_ifc_buffer[strlen(g_arg_fname) + 999]; endbuf >= g_arg_fname && *endbuf != ':' && *endbuf != '/' && *endbuf != '\\'; endbuf -= 1 );
    if ( *endbuf != ':' && *endbuf != '/' && *endbuf != '\\' )
    {
      *endbuf = 0;
    }
    else
    {
      endbuf[1] = 0;
    }
    if ( type && !e->f_no_decode )
    {
      fileext = ".dat";
    }
    else
    {
      fileext = ".cnf";
    }
    for ( nrind = 0; nrind < 1000; nrind += 1 )
    {
      if ( !g_ifc_buffer[nrind] )
      {
        switch ( type )
        {
          case 1:
            sprintf(g_netcnf_file_path, "%sifc%03d%s", g_arg_fname, nrind, fileext);
            break;
          case 2:
            sprintf(g_netcnf_file_path, "%sdev%03d%s", g_arg_fname, nrind, fileext);
            break;
          case 3:
            sprintf(g_netcnf_file_path, "%snet%03d%s", g_arg_fname, nrind, fileext);
            break;
          default:
            do_free_heapmem(g_add_entry_heapptr);
            return -10;
        }
        fd = do_open_netcnf(g_netcnf_file_path, 1, 0);
        if ( fd < 0 )
        {
          if ( fd == -5 )
            return -18;
          break;
        }
        do_close_netcnf(fd);
      }
    }
    retres2 = -12;
    if ( nrind < 1000 )
    {
      cur_entry_buffer = g_entry_buffer;
      for ( dirname_buf1 = g_dir_name; *dirname_buf1; dirname_buf1 += 1 )
      {
        if ( *dirname_buf1 == '/' || *dirname_buf1 == '\\' )
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
            if ( retres2 == -5 )
              break;
            retres2 = -18;
          }
        }
        *cur_entry_buffer = *dirname_buf1;
        ++cur_entry_buffer;
      }
      if ( *dirname_buf1 )
      {
        e->dir_name = g_dir_name;
        e->arg_fname = &g_netcnf_file_path[strlen(g_arg_fname)];
        if ( type )
          e->req = 2;
        else
          e->req = 1;
        retres2 = -1;
        if ( !do_export_netcnf(e) )
        {
          do_safe_make_name(atomicrenamepath, 256, g_dir_name, ".tmp");
          fd = do_open_netcnf(atomicrenamepath, 1538, 511);
          if ( fd >= 0 )
          {
            strlenx = sprintf(g_entry_buffer, "%d,%d,%s,%s\n", type, 1, &g_netcnf_file_path[strlen(g_arg_fname)], g_combination_buf1);
            writeres = do_write_netcnf_no_encode(fd, g_entry_buffer, strlenx);
            if ( strlenx == writeres
              && (writeres = do_write_netcnf_no_encode(fd, g_add_entry_heapptr, retres1), retres1 == writeres) )
            {
              retres2 = 0;
            }
            else
            {
              retres2 = -5;
              if ( writeres == -5 )
                retres2 = -18;
            }
          }
          else
          {
            retres2 = -3;
            if ( fd == -5 )
              retres2 = -18;
          }
        }
      }
    }
  }
  do_free_heapmem(g_add_entry_heapptr);
  if ( fd >= 0 )
    do_close_netcnf(fd);
  if ( atomicrenamepath[0] )
  {
    if ( iomanX_rename(atomicrenamepath, g_dir_name) == -5 )
      return -18;
    // Unofficial: dead code removed
  }
  if ( strncmp(g_dir_name, "pfs", 3) )
    return retres2;
  if ( iomanX_sync(g_dir_name, 0) != -5 )
    return retres2;
  return -18;
}
// 4027F4: using guessed type char atomicrenamepath[256];

//----- (00403070) --------------------------------------------------------
int do_handle_set_usrname(const char *fpath, int type, const char *usrname_buf2, const char *usrname_bufnew)
{
  int result; // $v0
  int retres1; // $s0
  char *heapmem; // $s2
  char *ptr_1; // $s0
  char *heapmem_1; // $s1
  int writeres1; // $s0
  char *ptr; // [sp+18h] [-8h] BYREF

  ptr = 0;
  if ( !usrname_buf2 )
    return -11;
  result = do_handle_combination_path(type, g_dir_name, g_combination_buf1, 256, (char *)usrname_bufnew);
  if ( result >= 0 )
  {
    retres1 = do_read_current_netcnf_nodecode(fpath, &ptr);
    if ( retres1 <= 0 )
    {
      if ( !retres1 )
        return -3;
      return retres1;
    }
    heapmem = (char *)do_alloc_heapmem(retres1 + strlen(usrname_bufnew) + 1);
    if ( !heapmem )
    {
      do_free_heapmem(ptr);
      return -2;
    }
    ptr_1 = ptr;
    heapmem_1 = heapmem;
    while ( *ptr_1 )
    {
      if ( do_type_check(type, ptr_1) > 0 && !do_split_str_comma_index(g_arg_fname, ptr_1, 3) )
      {
        if ( !strcmp(g_arg_fname, usrname_buf2) )
        {
          if ( !do_split_str_comma_index(g_arg_fname, ptr_1, 2) )
          {
            heapmem_1 += sprintf(heapmem_1, "%d,%d,%s,%s\n", type, 1, g_arg_fname, g_combination_buf1);
            ptr_1 = do_check_hoge_newline(ptr_1);
            continue;
          }
        }
        else if ( !strcmp(g_arg_fname, g_combination_buf1) )
        {
          do_free_heapmem(ptr);
          do_free_heapmem(heapmem);
          return -11;
        }
      }
      for ( ; *ptr_1 && *ptr_1 != '\n'; ptr_1 += 1 )
      {
        *heapmem_1++ = *ptr_1;
      }
      if ( *ptr_1 == '\n' )
      {
        *heapmem_1++ = *ptr_1++;
      }
    }
    do_free_heapmem(ptr);
    writeres1 = do_write_noencode_netcnf_atomic(fpath, heapmem, heapmem_1 - heapmem);
    do_free_heapmem(heapmem);
    return writeres1;
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
  char *curfilepath1end; // $s0
  char curentrybuf1[256]; // [sp+18h] [-200h] BYREF
  char curfilepath1[256]; // [sp+118h] [-100h] BYREF
  int flg;

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
    rmoldcfgres = 0;
    for ( curentry1 = g_edit_entry_heapptr; *curentry1; curentry1 = do_check_hoge_newline(curentry1) )
    {
      if ( do_type_check(type, curentry1) > 0
        && !do_split_str_comma_index(g_arg_fname, curentry1, 3)
        && !strcmp(g_arg_fname, g_combination_buf2)
        && !do_split_str_comma_index(curentrybuf1, curentry1, 2) )
      {
        ++rmoldcfgres;
      }
    }
    flg = 0;
    if ( !rmoldcfgres )
    {
      rmoldcfgres = -8;
    }
    else
    {
      if ( !get_check_provider_eq_zero() )
      {
        flg = 1;
      }
      if ( !flg )
      {
        if ( !do_handle_netcnf_dirname(g_dir_name, curentrybuf1, curfilepath1) )
        {
          rmoldcfgres = -11;
        }
        else
        {
          rmoldcfgres = do_read_check_netcnf(curfilepath1, type, e->f_no_check_magic, e->f_no_decode);
        }
      }
    }
    if ( flg || rmoldcfgres >= 0 )
    {
      do_safe_make_name(curfilepath1, 256, curentrybuf1, ".tmp");
      e->dir_name = g_dir_name;
      e->arg_fname = curfilepath1;
      if ( type )
        e->req = 2;
      else
        e->req = 1;
      if ( do_export_netcnf(e) )
      {
        rmoldcfgres = -1;
      }
      else
      {
        do_safe_strcpy(curfilepath1, 256, g_dir_name, 1010);
        for ( curfilepath1end = &curfilepath1[strlen(curfilepath1)]; curfilepath1end != curfilepath1; curfilepath1end -= 1 )
        {
          if ( *curfilepath1end == '/' || *curfilepath1end == '\\' )
          {
            curfilepath1end[1] = 0;
            break;
          }
        }
        do_safe_strcat(curfilepath1, 256, curentrybuf1, 1017);
        do_safe_strcpy(curentrybuf1, 256, curfilepath1, 1018);
        do_safe_strcat(curfilepath1, 256, ".tmp", 1019);
        if ( iomanX_rename(curfilepath1, curentrybuf1) == -5 )
          rmoldcfgres = -18;
      }
    }
  }
  do_free_heapmem(g_edit_entry_heapptr);
  if ( rmoldcfgres >= 0 )
  {
    do_set_latest_entry_inner(g_dir_name, type, g_combination_buf2);
    if ( new_usr_name )
      rmoldcfgres = do_handle_set_usrname(g_dir_name, type, g_combination_buf2, new_usr_name);
  }
  if ( strncmp(g_dir_name, "pfs", 3) == 0 )
  {
    if ( iomanX_sync(g_dir_name, 0) == -5 )
      return -18;
  }
  return rmoldcfgres;
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
              while ( *curentry1 )
              {
                if ( do_type_check(type, curentry1) <= 0
                  || do_split_str_comma_index(g_arg_fname, curentry1, 3)
                  || strcmp(g_arg_fname, g_combination_buf1) )
                {
                  for ( ; *curentry1 && *curentry1 != '\n'; curentry1 += 1 )
                  {
                    *heapmem_1++ = *curentry1;
                  }
                  if ( *curentry1 == '\n' )
                  {
                    *heapmem_1++ = *curentry1++;
                  }
                }
                else
                {
                  if ( !do_split_str_comma_index(g_entry_buffer, curentry1, 2) )
                    has_comma = 1;
                  curentry1 = do_check_hoge_newline(curentry1);
                }
              }
              remove_old_config_res = do_write_noencode_netcnf_atomic(g_dir_name, heapmem, heapmem_1 - heapmem);
              if ( remove_old_config_res >= 0 && has_comma )
                remove_old_config_res = do_remove_netcnf_dirname(g_dir_name, g_entry_buffer);
            }
            do_free_heapmem(g_delete_entry_heapptr);
            do_free_heapmem(heapmem);
            result = remove_old_config_res;
            if ( strncmp(g_dir_name, "pfs", 3) == 0 )
            {
              result = remove_old_config_res;
              if ( iomanX_sync(g_dir_name, 0) == -5 )
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
            while ( *curentry1 )
            {
              if ( do_type_check(type, curentry1) > 0
                && !do_split_str_comma_index(g_arg_fname, curentry1, 3)
                && !strcmp(g_arg_fname, g_combination_buf1) )
              {
                for ( ; *curentry1 && *curentry1 != '\n'; curentry1 += 1 )
                {
                  *heapmem1_1++ = *curentry1;
                }
                if ( *curentry1 == '\n' )
                {
                  *heapmem1_1++ = *curentry1++;
                }
                ++retres1;
                if ( heapmem2 < heapmem2_1 )
                  isbeforeend1 = 1;
              }
              else
              {
                for ( ; *curentry1 && *curentry1 != '\n'; curentry1 += 1 )
                {
                  *heapmem2_1++ = *curentry1;
                }
                if ( *curentry1 == '\n' )
                {
                  *heapmem2_1++ = *curentry1++;
                }
              }
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
        result = retres1;
        if ( strncmp(g_dir_name, "pfs", 3) == 0 )
        {
          result = retres1;
          if ( iomanX_sync(g_dir_name, 0) == -5 )
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
  int i; // $t0
  int dfd1; // $s1
  int result; // $v0
  int j; // $t0
  int dfd2; // $s1
  int dread_res; // $v0
  int remove_res2; // $s0
  int rmdir_res1; // $s0
  iox_dirent_t v21; // [sp+10h] [-148h] BYREF

  if ( !strncmp(dev, "mc", 2) )
  {
    for ( i = 0; dev[i] != ':'; i += 1 )
    {
      g_netcnf_file_path[i] = dev[i];
    }
    g_netcnf_file_path[i] = dev[i];
    g_netcnf_file_path[i + 1] = 0;
    do_safe_strcat(g_netcnf_file_path, 256, "/BWNETCNF", 1199);
    dfd1 = do_dopen_wrap(g_netcnf_file_path);
    if ( dfd1 < 0 )
      return 0;
    while ( 1 )
    {
      dread_res = do_dread_wrap(dfd1, &v21);
      if ( dread_res <= 0 )
        break;
      if ( strcmp(v21.name, ".") && strcmp(v21.name, "..") )
      {
        do_safe_make_pathname(g_dir_name, 256, g_netcnf_file_path, v21.name);
        if ( do_remove_wrap(g_dir_name) < 0 )
        {
          do_dclose_wrap(dfd1);
          return -7;
        }
      }
    }
    do_dclose_wrap(dfd1);
    result = -7;
    if ( rmdir(g_netcnf_file_path) >= 0 )
      return 0;
  }
  else
  {
    result = -17;
    if ( strncmp(dev, "pfs", 3) == 0 )
    {
      for ( j = 0; dev[j] != ':'; j += 1 )
      {
        g_netcnf_file_path[j] = dev[j];
      }
      g_netcnf_file_path[j] = dev[j];
      g_netcnf_file_path[j + 1] = 0;
      do_safe_strcat(g_netcnf_file_path, 256, "/etc/network", 1229);
      dfd2 = do_dopen_wrap(g_netcnf_file_path);
      if ( dfd2 >= 0 )
      {
        while ( 1 )
        {
          dread_res = do_dread_wrap(dfd2, &v21);
          if ( dread_res <= 0 )
            break;
          if ( strcmp(v21.name, ".") && strcmp(v21.name, "..") )
          {
            do_safe_make_pathname(g_dir_name, 256, g_netcnf_file_path, v21.name);
            remove_res2 = do_remove_wrap(g_dir_name);
            if ( remove_res2 < 0 )
            {
              do_dclose_wrap(dfd2);
              if ( remove_res2 == -5 )
                return -18;
              return -7;
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
            result = -18;
            if ( iomanX_sync(g_netcnf_file_path, 0) != -5 )
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
        if ( dfd2 == -5 )
          return -18;
        return 0;
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
        curentcount = 0;
        for ( curentry1 = g_check_special_provider_heapptr; *curentry1; curentry1 = do_check_hoge_newline(curentry1) )
        {
          if ( do_type_check(type, curentry1) > 0
            && !do_split_str_comma_index(g_arg_fname, curentry1, 3)
            && !strcmp(g_arg_fname, g_combination_buf2)
            && !do_split_str_comma_index((char *)e->lbuf, curentry1, 2) )
          {
            ++curentcount;
          }
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

  // TODO check struct sizes and correct types for callers calling into this function
  mem_ptr = e->mem_ptr;
  if ( mem_ptr
    && (retptrbegin = (char *)(((unsigned int)mem_ptr + (1 << align) - 1) & ~((1 << align) - 1)),
        &retptrbegin[size] < (char *)e->mem_last) )
  {
    e->mem_ptr = &retptrbegin[size];
    bzero(retptrbegin, size);
    return retptrbegin;
  }
  else
  {
    ++e->alloc_err;
  }
  return 0;
}

//----- (004041D8) --------------------------------------------------------
const char *do_netcnf_parse_string(sceNetCnfEnv_t *e, const char *e_arg)
{
  u8 *dbuf; // $s3
  const char *argbegin; // $s0
  sceNetCnfEnv_t *e_1; // $v0
  int argchr_1; // $s1
  int argind_1; // $s2
  int i; // $s2
  int hexnum; // $v0
  int err;

  dbuf = e->dbuf;
  if ( *e_arg != '"' )
    return e_arg;
  err = 0;
  argbegin = e_arg + 1;
  for ( e_1 = e; *argbegin && *argbegin != '"' && (char *)e_1 - (char *)e < 1022; e_1 = (sceNetCnfEnv_t *)(dbuf - 1088) )
  {
    argchr_1 = *(u8 *)argbegin++;
    if ( argchr_1 == '\\' )
    {
      if ( *(u8 *)argbegin == 0 )
      {
        err = 1;
        break;
      }
      argchr_1 = 0;
      if ( (unsigned int)(*(u8 *)argbegin - '0') >= 8 )
      {
        if ( *(u8 *)argbegin == 'x' || *(u8 *)argbegin == 'X' )
        {
          ++argbegin;
          argchr_1 = 0;
          if ( !isxdigit(*argbegin) )
          {
            err = 2;
            break;
          }
          for ( i = 0; i < 2 && isxdigit(*argbegin); i += 1 )
          {
            if ( isdigit(*argbegin) )
            {
              argchr_1 = 16 * argchr_1 + *(u8 *)argbegin - '0';
            }
            else
            {
              hexnum = 16 * argchr_1;
              argchr_1 = (!islower(*argbegin)) ? hexnum + *(u8 *)argbegin - '7' : hexnum + *(u8 *)argbegin - 'W';
            }
            argbegin++;
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
        for ( argind_1 = 0; argind_1 < 3 && ( *(u8 *)argbegin - (unsigned int)'0' < 8 ); argind_1 += 1 )
        {
          argchr_1 = 8 * argchr_1 + *argbegin - '0';
          argbegin++;
        }
      }
    }
    else if ( (unsigned int)(argchr_1 - 129) < 0x1F || (unsigned int)(argchr_1 - 224) < 0x1D )
    {
      if ( (u8)(*(u8 *)argbegin - 64) < 0xBDu && *(u8 *)argbegin != 127 )
      {
        *dbuf++ = argchr_1;
        argchr_1 = *argbegin++;
      }
    }
    *dbuf = argchr_1;
    ++dbuf;
  }
  if ( !err )
  {
    if ( *(u8 *)argbegin != '"' )
    {
      err = 3;    
    }
    else if ( argbegin[1] )
    {
      err = 4;
    }
  }
  if ( err )
  {
    printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
    switch ( err )
    {
      case 1:
        printf("invalid escape (%s)", e_arg);
        break;
      case 2:
        printf("missing hexa-decimal(%s)", e_arg);
        break;
      case 3:
        printf("invalid quote (%s)", e_arg);
        break;
      case 4:
        printf("invalid extra chars (%s)", e_arg);
        break;
      default:
        break;
    }
    printf("\n");
    ++e->syntax_err;
    return 0;
  }
  *dbuf = 0;
  return (const char *)e->dbuf;
}

//----- (00404568) --------------------------------------------------------
char *do_alloc_mem_for_write(sceNetCnfEnv_t *e, const char *str)
{
  char *strptr; // $s0

  strptr = do_alloc_mem_inner(e, strlen(str) + 1, 0);
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
      if ( *(u8 *)e_arg_1 - (unsigned int)'0' >= 0xA )
      {
        if ( *(u8 *)e_arg_1 - (unsigned int)'a' >= 6 )
          break;
        e_arg_1_num = (char)(*(u8 *)e_arg_1) - 'W';
      }
      else
      {
        e_arg_1_num = (char)(*(u8 *)e_arg_1) - '0';
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
  ++e->syntax_err;
  return -1;
}

//----- (00404738) --------------------------------------------------------
int do_netcnfname2address_wrap(sceNetCnfEnv_t *e, char *buf, sceNetCnfAddress_t *paddr)
{
  int errret; // $s0

  errret = sceNetCnfName2Address(paddr, buf);
  if ( errret < 0 )
  {
    printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
    printf("sceNetCnfName2Address(%s) -> %d\n", buf, errret);
    printf("\n");
    ++e->syntax_err;
    return -1;
  }
  return 0;
}

//----- (004047CC) --------------------------------------------------------
int do_parse_phone_stuff(sceNetCnfEnv_t *e, int opt_argc, const char **opt_argv, int *p_result)
{
  int opt_argc_1; // $s2
  int bitflags1; // $s0
  int numval; // [sp+10h] [-8h] BYREF

  bitflags1 = 0;
  for ( opt_argc_1 = 0; opt_argc_1 < opt_argc; opt_argc_1 += 1 )
  {
    if ( !strcmp("phase", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 1u;
    }
    else if ( !strcmp("cp", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 2u;
    }
    else if ( !strcmp("auth", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 4u;
    }
    else if ( !strcmp("chat", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 8u;
    }
    else if ( !strcmp("private", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 0x10u;
    }
    else if ( !strcmp("dll", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 0x20u;
    }
    else if ( !strcmp("dump", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 0x40u;
    }
    else if ( !strcmp("timer", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 0x10000;
    }
    else if ( !strcmp("event", opt_argv[opt_argc_1]) )
    {
      bitflags1 |= 0x20000;
    }
    else if ( do_parse_number(e, opt_argv[opt_argc_1], &numval) )
      return -1;
  }
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
  struct sceNetCnfPair *pair_tail; // $v0

  cnfpair1 = (struct sceNetCnfPair *)do_alloc_mem_inner(e, 40, 2);
  if ( !cnfpair1 )
    return -1;
  cnfpair1->display_name = (u8 *)do_check_e_arg(e, display_name_arg);
  if ( !cnfpair1->display_name )
    return -1;
  cnfpair1->attach_ifc = (u8 *)do_check_e_arg(e, attach_ifc_arg);
  if ( !cnfpair1->attach_ifc )
    return -1;
  if ( attach_dev_arg )
  {
    if ( *attach_dev_arg )
    {
      cnfpair1->attach_dev = (u8 *)do_check_e_arg(e, attach_dev_arg);
      if ( !cnfpair1->attach_dev )
        return -1;
    }
  }
  pair_tail = e->root->pair_tail;
  cnfpair1->back = pair_tail;
  if ( !pair_tail )
    pair_tail = (struct sceNetCnfPair *)e->root;
  pair_tail->forw = cnfpair1;
  cnfpair1->forw = 0;
  e->root->pair_tail = cnfpair1;
  return 0;
}

//----- (00404A78) --------------------------------------------------------
int do_check_nameserver(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc, int opt_argc, char **opt_argv)
{
  int addordel; // $s1
  struct sceNetCnfCommand *nameservermem_1; // $v0

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
  if ( !nameservermem_1 )
    return -1;
  nameservermem_1->code = addordel;
  if ( do_netcnfname2address_wrap(e, opt_argv[2], (sceNetCnfAddress_t *)&nameservermem_1[1]) )
    return -1;
  nameservermem_1->back = ifc->cmd_tail;
  if ( ifc->cmd_tail )
    ifc->cmd_tail->forw = nameservermem_1;
  else
    ifc->cmd_head = nameservermem_1;
  nameservermem_1->forw = 0;
  ifc->cmd_tail = nameservermem_1;
  return 0;
}

//----- (00404B6C) --------------------------------------------------------
int do_check_route(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc, int opt_argc, char **opt_argv)
{
  int addordel; // $s0
  struct sceNetCnfCommand *route_mem_1; // $v0
  int cur_argc; // $s3

  if ( opt_argc < 3 )
    return 0;
  addordel = 3;
  if ( strcmp("add", opt_argv[1]) )
  {
    if ( strcmp("del", opt_argv[1]) != 0 )
      return 0;
    addordel = 4;
  }
  route_mem_1 = (struct sceNetCnfCommand *)do_alloc_mem_inner(e, 96, 2);
  if ( !route_mem_1 )
    return -1;
  cur_argc = 2;
  route_mem_1->code = addordel;
  if ( !strcmp("-net", opt_argv[cur_argc]) )
  {
    cur_argc += 1;
    route_mem_1[6].forw = (struct sceNetCnfCommand *)((int)route_mem_1[6].forw & 0xFFFFFFFD);
  }
  else if ( !strcmp("-host", opt_argv[cur_argc]) )
  {
    cur_argc += 1;
    route_mem_1[6].forw = (struct sceNetCnfCommand *)((int)route_mem_1[6].forw | 2);
  }
  if ( cur_argc >= opt_argc )
    return 0;
  if ( do_netcnfname2address_wrap(e, 0, (sceNetCnfAddress_t *)&route_mem_1[1]) == 0 )
  {
    if ( do_netcnfname2address_wrap(e, 0, (sceNetCnfAddress_t *)&route_mem_1[2].code) == 0 )
    {
      if ( do_netcnfname2address_wrap(e, 0, (sceNetCnfAddress_t *)&route_mem_1[4].back) == 0 )
      {
        if ( !strcmp("default", opt_argv[cur_argc])
          || (do_netcnfname2address_wrap(e, (char *)opt_argv[cur_argc], (sceNetCnfAddress_t *)&route_mem_1[1]) == 0) )
        {
          cur_argc += 1;
          for ( ; cur_argc < opt_argc; cur_argc += 2 )
          {
            if ( !strcmp("gw", opt_argv[cur_argc]) )
            {
              if ( do_netcnfname2address_wrap(e, opt_argv[cur_argc + 1], (sceNetCnfAddress_t *)&route_mem_1[2].code) != 0 )
                return -1;
              route_mem_1[6].forw = (struct sceNetCnfCommand *)((int)route_mem_1[6].forw | 4);
            }
            else if ( !strcmp("netmask", opt_argv[cur_argc]) )
            {
              if ( do_netcnfname2address_wrap(e, opt_argv[cur_argc + 1], (sceNetCnfAddress_t *)&route_mem_1[4].back) != 0 )
                return -1;
            }
          }
          route_mem_1->back = ifc->cmd_tail;
          if ( ifc->cmd_tail )
            ifc->cmd_tail->forw = route_mem_1;
          else
            ifc->cmd_head = route_mem_1;
          route_mem_1->forw = 0;
          ifc->cmd_tail = route_mem_1;
          return 0;
        }
      }
    }
  }
  return -1;
}

//----- (00404DE0) --------------------------------------------------------
void do_init_ifc_inner(sceNetCnfInterface_t *ifc)
{
  struct netcnf_option *curentry1; // $a2

  for ( curentry1 = g_options_attach_cnf; curentry1->m_key; curentry1 += 1 )
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
  }
}

//----- (00404E74) --------------------------------------------------------
int do_check_args(sceNetCnfEnv_t *e, struct sceNetCnfUnknownList *unknown_list)
{
  int lenx1; // $s1
  int curindx1; // $s0
  struct sceNetCnfUnknown *listtmp; // $s4
  struct sceNetCnfUnknown *cpydst_1; // $s2
  int cuindx2; // $s0
  size_t cpysz; // $v0

  lenx1 = 0;
  for ( curindx1 = 0; curindx1 < e->ac; curindx1 += 1 )
  {
    lenx1 += 3 + strlen(e->av[curindx1]);
  }
  listtmp = (struct sceNetCnfUnknown *)do_alloc_mem_inner(e, lenx1 + 8, 2);
  cpydst_1 = listtmp + 1;
  if ( !listtmp )
    return -1;
  for ( cuindx2 = 0; cuindx2 < e->ac; cuindx2 += 1 )
  {
    cpysz = strlen(e->av[cuindx2]);
    bcopy(e->av[cuindx2], cpydst_1, cpysz);
    ((char *)cpydst_1)[cpysz] = 32 * (cuindx2 < e->ac - 1);
    cpydst_1 = (struct sceNetCnfUnknown *)&((char *)cpydst_1)[cpysz + 1];
  }
  listtmp->back = unknown_list->tail;
  if ( unknown_list->tail )
    unknown_list->tail->forw = listtmp;
  else
    unknown_list->head = listtmp;
  listtmp->forw = 0;
  unknown_list->tail = listtmp;
  return 0;
}

//----- (00404FC0) --------------------------------------------------------
int do_check_other_keywords(
        sceNetCnfEnv_t *e,
        struct netcnf_option *options,
        void *cnfdata,
        struct sceNetCnfUnknownList *unknown_list)
{
  int wasprefixed; // $s3
  int numval; // [sp+10h] [-8h] BYREF

  wasprefixed = 0;
  if ( e->av[0][0] == '-' )
  {
    wasprefixed = 1;
  }
  if ( e->av[0][wasprefixed] )
  {
    for ( ; options->m_key && strcmp(&(e->av[0])[wasprefixed], options->m_key); options += 1 );
    if ( !options->m_key )
      return do_check_args(e, unknown_list);
    switch ( options->m_type )
    {
      case '1':
        numval = 255;
        if ( !wasprefixed )
        {
          if ( e->ac < 2 || do_parse_number(e, e->av[1], &numval) )
            break;
        }
        *((u8 *)cnfdata + options->m_offset) = numval;
        return 0;
      case '4':
        numval = -1;
        if ( !wasprefixed )
        {
          if ( e->ac < 2 || do_parse_number(e, e->av[1], &numval) )
            break;
        }
        *(u32 *)((char *)cnfdata + options->m_offset) = numval;
        return 0;
      case 'A':
        if ( !wasprefixed )
        {
          if ( e->ac < 2 )
            break;
          if ( !strcmp("any", (const char *)e->av[1]) )
          {
            numval = 0;
          }
          else if ( !strcmp("pap", (const char *)e->av[1]) )
          {
            numval = 1;
          }
          else if ( !strcmp("chap", (const char *)e->av[1]) )
          {
            numval = 2;
          }
          else if ( !strcmp("pap/chap", (const char *)e->av[1]) )
          {
            numval = 3;
          }
          else if ( !strcmp("chap/pap", (const char *)e->av[1]) )
          {
            numval = 4;
          }
          else if ( do_parse_number(e, e->av[1], &numval) != 0 )
          {
            return -1;
          }
          *((u8 *)cnfdata + options->m_offset) = numval;
        }
        if ( !strcmp("want.auth", (const char *)e->av[0]) )
          *((u8 *)cnfdata + 171) = wasprefixed == 0;
        else
          *((u8 *)cnfdata + 247) = wasprefixed == 0;
        return 0;
      case 'C':
        if ( !wasprefixed )
        {
          if ( e->ac < 2 || do_parse_number(e, e->av[1], &numval) )
            break;
          *(u32 *)((char *)cnfdata + options->m_offset) = numval;
        }
        if ( !strcmp("want.accm", (const char *)e->av[0]) )
          *((u8 *)cnfdata + 170) = wasprefixed == 0;
        else
          *((u8 *)cnfdata + 246) = wasprefixed == 0;
        return 0;
      case 'D':
        numval = -1;
        if ( !wasprefixed )
        {
          if ( e->ac < 2 )
            break;
          if ( !strcmp("tone", (const char *)e->av[1]) )
          {
            numval = 0;
          }
          else if ( !strcmp("pulse", (const char *)e->av[1]) )
          {
            numval = 1;
          }
          else if ( !strcmp("any", (const char *)e->av[1]) )
          {
            numval = 2;
          }
          else if ( do_parse_number(e, e->av[1], &numval) != 0 )
          {
            return -1;
          }
        }
        *(u32 *)((char *)cnfdata + options->m_offset) = numval;
        return 0;
      case 'L':
        numval = -1;
        if ( !wasprefixed )
        {
          if ( do_parse_phone_stuff(e, e->ac - 1, (const char **)&e->av[1], &numval) != 0 )
            return -1;
        }
        *(u32 *)((char *)cnfdata + options->m_offset) = numval;
        return 0;
      case 'M':
        if ( !wasprefixed )
        {
          if ( e->ac < 2 || do_parse_number(e, e->av[1], &numval) )
            break;
          *(u16 *)((char *)cnfdata + options->m_offset) = numval;
        }
        if ( !strcmp("want.mru", (const char *)e->av[0]) )
          *((u8 *)cnfdata + 169) = wasprefixed == 0;
        else
          *((u8 *)cnfdata + 245) = wasprefixed == 0;
        return 0;
      case 'P':
        numval = -1;
        if ( !wasprefixed )
        {
          if ( e->ac < 2 )
            break;
          if ( !strcmp("auto", (const char *)e->av[1]) )
          {
            numval = 1;
          }
          else if ( !strcmp("10", (const char *)e->av[1]) )
          {
            numval = 2;
          }
          else if ( !strcmp("10_fd", (const char *)e->av[1]) )
          {
            numval = 3;
          }
          else if ( !strcmp("10_fd_pause", (const char *)e->av[1]) )
          {
            numval = 4;
          }
          else if ( !strcmp("tx", (const char *)e->av[1]) )
          {
            numval = 5;
          }
          else if ( !strcmp("tx_fd", (const char *)e->av[1]) )
          {
            numval = 6;
          }
          else if ( !strcmp("tx_fd_pause", (const char *)e->av[1]) )
          {
            numval = 7;
          }
          else if ( do_parse_number(e, e->av[1], &numval) != 0 )
          {
            return -1;
          }
        }
        *(u32 *)((char *)cnfdata + options->m_offset) = numval;
        return 0;
      case 'T':
        numval = -1;
        if ( !wasprefixed )
        {
          if ( e->ac < 2 )
            break;
          if ( !strcmp("any", (const char *)e->av[1]) )
          {
            numval = 0;
          }
          if ( !strcmp("eth", (const char *)e->av[1]) )
          {
            numval = 1;
          }
          else if ( !strcmp("ppp", (const char *)e->av[1]) )
          {
            numval = 2;
          }
          else if ( !strcmp("nic", (const char *)e->av[1]) )
          {
            numval = 3;
          }
          else if ( do_parse_number(e, e->av[1], &numval) != 0 )
          {
            return -1;
          }
        }
        *(u32 *)((char *)cnfdata + options->m_offset) = numval;
        return 0;
      case 'b':
        numval = wasprefixed == 0;
        *((u8 *)cnfdata + options->m_offset) = numval;
        return 0;
      case 'c':
        numval = 255;
        if ( !wasprefixed )
        {
          if ( e->ac < 2 )
            break;
          if ( !strcmp("no", (const char *)e->av[1]) )
          {
            numval = 0;
          }
          else if ( !strcmp("md5", (const char *)e->av[1]) )
          {
            numval = 5;
          }
          else if ( !strcmp("ms", (const char *)e->av[1]) )
          {
            numval = 128;
          }
          else if ( !strcmp("ms-v1", (const char *)e->av[1]) )
          {
            numval = 128;
          }
          else if ( !strcmp("ms-v2", (const char *)e->av[1]) )
          {
            numval = 129;
          }
          else if ( do_parse_number(e, e->av[1], &numval) != 0 )
          {
            return -1;
          }
        }
        *((u8 *)cnfdata + options->m_offset) = numval;
        return 0;
      case 'p':
        if ( !wasprefixed )
        {
          if ( e->ac < 2 )
          {
            break;
          }
          *(char **)((char *)cnfdata + options->m_offset) = do_check_e_arg(e, e->av[1]);
          if ( !*(char **)((char *)cnfdata + options->m_offset) )
            return -1;
          return 0;
        }
        *(u32 *)((char *)cnfdata + options->m_offset) = 0;
        return 0;
      default:
        return printf("netcnf: internal load err (%d, type=%c)\n", 606, options->m_type);
    }
  }
  printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
  printf("ac=%d", e->ac);
  printf("\n");
  ++e->syntax_err;
  return -1;
}

//----- (0040575C) --------------------------------------------------------
int do_handle_net_cnf(sceNetCnfEnv_t *e)
{
  int wasprefixed; // $s2

  wasprefixed = 0;
  if ( e->av[0][0] == '-' )
  {
    wasprefixed = 1;
  }
  if ( strcmp("interface", &(e->av[0])[wasprefixed]) )
  {
    if ( strcmp("zero_prefix", &(e->av[0])[wasprefixed]) )
      return do_check_other_keywords(e, g_options_net_cnf, e->root, &e->root->unknown_list);
    printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
    printf("obsoleted keyword (%s)", &(e->av[0])[wasprefixed]);
    printf("\n");
    ++e->syntax_err;
    return 0;
  }
  if ( wasprefixed )
    return 0;
  if ( e->ac < 3 )
  {
    printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
    printf("ac=%d", e->ac);
    printf("\n");
    ++e->syntax_err;
    return -1;
  }
  if ( do_check_interface_keyword(e, e->av[1], e->av[2], ( e->ac >= 4 ) ? e->av[3] : 0) == 0 )
    return 0;
  return -1;
}

//----- (004058E0) --------------------------------------------------------
int do_handle_attach_cnf(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc)
{
  int wasprefixed; // $s2
  int keyasnum; // $s0

  wasprefixed = 0;
  if ( e->av[0][0] == '-' )
  {
    wasprefixed = 1;
  }
  if ( !strncmp("phone_number", &(e->av[0])[wasprefixed], 12) )
  {
    if ( e->av[0][wasprefixed + 12] )
    {
      if ( !isdigit(e->av[0][wasprefixed + 12]) )
        return 0;
      if ( e->av[0][wasprefixed + 13] )
        return 0;
      keyasnum = e->av[0][wasprefixed + 12] - 48;
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
    if ( e->ac >= 2 )
    {
      ifc->phone_numbers[keyasnum] = (u8 *)do_check_e_arg(e, e->av[1]);
      if ( ifc->phone_numbers[keyasnum] )
        return 0;
      return -1;
    }
  }
  else if ( !strcmp("nameserver", &(e->av[0])[wasprefixed]) )
  {
    if ( !wasprefixed )
      return do_check_nameserver(e, ifc, e->ac, (char **)e->av);
  }
  else
  {
    if ( strcmp("route", &(e->av[0])[wasprefixed]) )
    {
      if ( strcmp("zero_prefix", &(e->av[0])[wasprefixed]) && strcmp("dial_cnf", &(e->av[0])[wasprefixed]) )
        return do_check_other_keywords(e, g_options_attach_cnf, ifc, &ifc->unknown_list);
      printf("netcnf: \"%s\" line %d: ", e->fname, e->lno);
      printf("obsoleted keyword (%s)", &(e->av[0])[wasprefixed]);
      printf("\n");
      ++e->syntax_err;
      return 0;
    }
    if ( !wasprefixed )
      return do_check_route(e, ifc, e->ac, (char **)e->av);
  }
  return 0;
}

//----- (00405B08) --------------------------------------------------------
int do_handle_dial_cnf(sceNetCnfEnv_t *e, struct sceNetCnfDial *dial)
{
  int wasprefixed; // $s1

  wasprefixed = 0;
  if ( e->av[0][0] == '-' )
  {
    wasprefixed = 1;
  }
  if ( strcmp("dialing_type_string", &(e->av[0])[wasprefixed]) )
    return do_check_other_keywords(e, g_options_dial_cnf, dial, &dial->unknown_list);
  if ( !wasprefixed )
  {
    if ( e->ac >= 2 )
    {
      dial->tone_dial = (u8 *)do_check_e_arg(e, e->av[1]);
      if ( !dial->tone_dial )
        return -1;
      if ( e->ac < 3 )
        return 0;
      dial->pulse_dial = (u8 *)do_check_e_arg(e, e->av[2]);
      if ( dial->pulse_dial )
      {
        if ( e->ac >= 4 )
        {
          dial->any_dial = (u8 *)do_check_e_arg(e, e->av[3]);
          if ( dial->any_dial  )
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
  return 0;
}

//----- (00405C24) --------------------------------------------------------
int do_check_line_buffer(sceNetCnfEnv_t *e, u8 *lbuf, int (*readcb)(int, int), void *userdata)
{
  u8 *i; // $s0
  char *j; // $s0
  u32 condtmp1; // $s1

  for ( i = lbuf; e->lbuf < i && *(i - 1) < 0x21u; i -= 1 );
  *i = 0;
  for ( j = (char *)e->lbuf; *j && isspace(*j); j += 1 );
  e->ac = 0;
  while ( *j )
  {
    if ( e->ac >= '\n' || (u8)*j == '#' )
      break;
    e->av[e->ac] = j;
    condtmp1 = 0;
    if ( *j )
    {
      if ( *j == '#' )
      {
        *j = 0;
        break;
      }
      if ( !isspace(*j) )
      {
        while ( *j )
        {
          if ( *j == '\\' )
          {
            if ( j[1] )
              ++j;
          }
          else if ( condtmp1 )
          {
            if ( *j == '"' )
              condtmp1 = 0;
          }
          else
          {
            condtmp1 = *j == '"';
          }
          j++;
          if ( !condtmp1 )
          {
            if ( *j != '#' )
            {
              if ( !isspace(*j) )
                continue;
            }
            break;
          }
        }
      }
    }
    if ( *j == '#' )
    {
      *j = 0;
      break;
    }
    if ( *j )
    {
      *j = 0;
      ++j;
    }
    for ( ; *j && isspace(*j); j += 1 );
    ++e->ac;
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
  char *result; // $v0

  result = do_handle_netcnf_dirname(e->dir_name, entry_buffer, (char *)e->lbuf);
  if ( result == (char *)e->lbuf )
    return do_alloc_mem_for_write(e, result);
  return result;
}

//----- (00405F3C) --------------------------------------------------------
int do_netcnf_read_related(sceNetCnfEnv_t *e, const char *path, int (*readcb)(), void *userdata)
{
  int cur_linelen; // $s4
  char *fullpath; // $s0
  int read_res1; // $v0
  u8 *lbuf; // $s0
  int curchind; // $s0
  char *ptr; // [sp+10h] [-8h] BYREF

  cur_linelen = 0;
  if ( e->f_verbose )
  {
    printf("netcnf: dir=%s path=%s\n", e->dir_name ? e->dir_name : "NULL", path ? path : "NULL");
  }
  fullpath = do_handle_netcnf_prerw(e, path);
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
      else if ( (char *)readcb == (char *)do_handle_dial_cnf )
      {
        printf("DIAL_CNF");
      }
      else
      {
        printf("???");
      }
      printf("\n");
    }
    e->fname = fullpath;
    read_res1 = do_read_netcnf(e, fullpath, &ptr, readcb == (int (*)())do_handle_attach_cnf);
    if ( read_res1 < 0 )
    {
      printf("netcnf: can't load %s (%d)\n", e->fname, read_res1);
      return -1;
    }
    e->lno = 0;
    if ( e->f_no_check_magic )
    {
    }
    else if ( read_res1 < 36
           || (strncmp(ptr, "# <Sony Computer Entertainment Inc.>", 36) != 0) )
    {
      printf("netcnf: decoding error (magic=\"");
      for ( curchind = 0; curchind < read_res1 && curchind < '$'; curchind += 1 )
      {
        printf("%c", ((u8)ptr[curchind] - (unsigned int)' ' < '_') ? ((u8)ptr[curchind]) : '?');
      }
      printf("\")\n");
      do_free_heapmem(ptr);
      return -15;
    }
    lbuf = e->lbuf;
    read_res1 -= 1;
    while ( (read_res1 + 1) > 0 )
    {
      if ( *ptr == '\n' )
      {
        ++e->lno;
        if ( e->lbuf < lbuf && *(lbuf - 1) == '\\' )
        {
          --lbuf;
        }
        else
        {
          cur_linelen += do_check_line_buffer(e, lbuf, (int (*)(int, int))readcb, userdata);
          lbuf = e->lbuf;
        }
      }
      else
      {
        if ( lbuf < &e->lbuf[1023] && *ptr != '\r' )
          *lbuf++ = *ptr;
      }
      ptr++;
      read_res1 -= 1;
    }
    if ( e->lbuf < lbuf )
      cur_linelen += do_check_line_buffer(e, lbuf, (int (*)(int, int))readcb, userdata);
    do_free_heapmem(ptr);
    return cur_linelen;
  }
  return -1;
}

//----- (0040627C) --------------------------------------------------------
int do_netcnf_dial_related(sceNetCnfEnv_t *e)
{
  e->root = (struct sceNetCnfRoot *)do_alloc_mem_inner(e, 44, 2);
  if ( !e->root )
    return -2;
  e->root->version = 3;
  e->root->redial_count = -1;
  e->root->redial_interval = -1;
  e->root->dialing_type = -1;
  return do_netcnf_read_related(e, e->arg_fname, (int (*)())do_handle_net_cnf, 0);
}

//----- (004062FC) --------------------------------------------------------
int do_netcnf_ifc_related(sceNetCnfEnv_t *e)
{
  e->ifc = (sceNetCnfInterface_t *)do_alloc_mem_inner(e, 352, 2);
  if ( !e->ifc )
    return -2;
  do_init_ifc_inner(e->ifc);
  return do_netcnf_read_related(e, e->arg_fname, (int (*)())do_handle_attach_cnf, e->ifc);
}

//----- (00406360) --------------------------------------------------------
void do_dialauth_related(sceNetCnfInterface_t *ncid, struct sceNetCnfInterface *ncis)
{
  int curindx; // $a2
  int typadd1_1; // $v1
  int typadd1_3; // $v1
  int typadd1; // $v1

  if ( ncis )
  {
    for ( curindx = 0; g_options_attach_cnf[curindx].m_key; curindx += 1 )
    {
      switch ( g_options_attach_cnf[curindx].m_type )
      {
        case '1':
        case 'b':
        case 'c':
          typadd1 = *((u8 *)&ncis->type + g_options_attach_cnf[curindx].m_offset);
          if ( typadd1 != 255 )
            *((u8 *)&ncid->type + g_options_attach_cnf[curindx].m_offset) = typadd1;
          break;
        case '4':
        case 'D':
        case 'L':
        case 'P':
        case 'T':
          typadd1_1 = *(int *)((char *)&ncis->type + g_options_attach_cnf[curindx].m_offset);
          if ( typadd1_1 != -1 )
            *(int *)((char *)&ncid->type + g_options_attach_cnf[curindx].m_offset) = typadd1_1;
          break;
        case 'A':
          if ( !strcmp("want.auth", g_options_attach_cnf[curindx].m_key) )
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
          if ( !strcmp("want.accm", g_options_attach_cnf[curindx].m_key) )
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
          if ( !strcmp("want.mru", g_options_attach_cnf[curindx].m_key) )
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
          typadd1_3 = *(int *)((char *)&ncis->type + g_options_attach_cnf[curindx].m_offset);
          if ( typadd1_3 )
            *(int *)((char *)&ncid->type + g_options_attach_cnf[curindx].m_offset) = typadd1_3;
          break;
        default:
          break;
      }
    }
    for ( curindx = 0; curindx < 10; curindx += 1 )
    {
      if ( ncis->phone_numbers[curindx] )
        ncid->phone_numbers[curindx] = ncis->phone_numbers[curindx];
    }
  }
}

//----- (004065CC) --------------------------------------------------------
int do_merge_conf_inner(sceNetCnfEnv_t *e)
{
  struct sceNetCnfPair *pair_head; // $s2
  int type; // $s0

  if ( e->root )
  {
    for ( pair_head = e->root->pair_head; pair_head; pair_head = pair_head->forw )
    {
      if ( !pair_head->ctl )
      {
        pair_head->ctl = (struct sceNetCnfCtl *)do_alloc_mem_inner(e, 32, 2);
        if ( !pair_head->ctl )
          return -2;
      }
      if ( !pair_head->ctl->dial )
      {
        pair_head->ctl->dial = (struct sceNetCnfDial *)do_alloc_mem_inner(e, 36, 2);
        if ( !pair_head->ctl->dial )
          return -2;
      }
      if ( !pair_head->ctl->ifc )
      {
        pair_head->ctl->ifc = (sceNetCnfInterface_t *)do_alloc_mem_inner(e, 352, 2);
        if ( !pair_head->ctl->ifc )
          return -2;
      }
      do_init_ifc_inner(pair_head->ctl->ifc);
      pair_head->ctl->ifc->chat_additional = e->root->chat_additional;
      pair_head->ctl->ifc->redial_count = e->root->redial_count;
      pair_head->ctl->ifc->redial_interval = e->root->redial_interval;
      pair_head->ctl->ifc->outside_number = e->root->outside_number;
      pair_head->ctl->ifc->outside_delay = e->root->outside_delay;
      pair_head->ctl->ifc->dialing_type = e->root->dialing_type;
      do_dialauth_related(pair_head->ctl->ifc, pair_head->ifc);
      type = pair_head->dev->type;
      pair_head->dev->type = -1;
      do_dialauth_related(pair_head->ctl->ifc, pair_head->dev);
      pair_head->dev->type = type;
    }
    return 0;
  }
  return -1;
}

//----- (00406750) --------------------------------------------------------
int do_load_conf_inner(sceNetCnfEnv_t *e)
{
  int retres1; // $s3
  int ifcres1_1; // $s1
  struct sceNetCnfPair *pair_head; // $s0

  retres1 = 0;
  if ( e->req == 1 )
  {
    ifcres1_1 = do_netcnf_dial_related(e);
    if ( ifcres1_1 )
      return ifcres1_1;
    if ( !e->root )
      return -14;
    pair_head = e->root->pair_head;
    if ( !pair_head )
      return -14;
    if ( index(e->arg_fname, ':') )
      e->dir_name = e->arg_fname;
    for ( ; pair_head; pair_head = pair_head->forw )
    {
      if ( pair_head->attach_ifc )
      {
        e->arg_fname = (char *)pair_head->attach_ifc;
        ifcres1_1 = do_netcnf_ifc_related(e);
        if ( ifcres1_1 )
        {
          printf("netcnf: load_attach ifc(%d)\n", ifcres1_1);
          pair_head->ifc = 0;
          if ( (unsigned int)(ifcres1_1 + 15) < 2 )
          {
            pair_head->dev = 0;
            break;
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
      if ( pair_head->attach_dev )
      {
        e->arg_fname = (char *)pair_head->attach_dev;
        ifcres1_1 = do_netcnf_ifc_related(e);
        if ( ifcres1_1 )
        {
          printf("netcnf: load_attach dev(%d)\n", ifcres1_1);
          pair_head->dev = 0;
          if ( (unsigned int)(ifcres1_1 + 15) < 2 )
            break;
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
    }
    if ( retres1 == -21 )
      return -21;
    return ifcres1_1;
  }
  if ( e->req == 2 )
    return do_netcnf_ifc_related(e);
  return -1;
}

//----- (0040690C) --------------------------------------------------------
int do_load_dial_inner(sceNetCnfEnv_t *e, sceNetCnfPair_t *pair)
{
  if ( !pair->ctl )
    return -1;
  pair->ctl->dial = (struct sceNetCnfDial *)do_alloc_mem_inner(e, 36, 2);
  if ( pair->ctl->dial )
    return do_netcnf_read_related(e, e->arg_fname, (int (*)())do_handle_dial_cnf, pair->ctl->dial);
  else
    return -2;
}

//----- (00406990) --------------------------------------------------------
int do_netcnf_vsprintf_buffer(sceNetCnfEnv_t *e, char *fmt, unsigned int va)
{
  char *mem_ptr_03; // $v1
  void *mem_ptr_rval_04; // $v0
  int has_negative; // $s7
  int has_sero; // $s5
  int strlened; // $s3
  int fmt_flag_str; // $fp
  char *mem_ptr_01; // $v1
  char **cur_va2; // $v0
  char *strptr1; // $s0
  int strlenmax; // $s4
  unsigned int strpad1; // $a2
  int cur_va1; // $a1
  int valmod1; // $hi
  char *curnumvals; // $a0
  size_t strlen1; // $v0
  int strlencalc; // $s3
  char *mem_ptr_02; // $v1
  char *mem_ptr_04; // $v1
  char *mem_ptr_05; // $v1
  char *i; // $s0
  char *mem_ptr_0a; // $a0
  void *mem_ptr_rval_02; // $v0
  char i_curchr2; // $a1
  void *mem_ptr_rval_03; // $v0
  char *mem_ptr_07; // $a0
  char *mem_ptr_09; // $a1
  void *mem_ptr_rval_01; // $v0
  char *mem_ptr_08; // $v1
  char strptr_curchr1; // $a0
  char *mem_ptr_06; // $v1
  char *mem_ptr_0b; // $v1
  char stkstr1; // [sp+23h] [-5h] BYREF

  while ( *fmt )
  {
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
      strlened = 0;
      for ( ; isdigit(*fmt); fmt += 1 )
      {
        strlened = 10 * strlened - '0' + *fmt;
      }
      if ( *fmt == 'l' )
        ++fmt;
      fmt_flag_str = -1;
      strpad1 = 0;
      switch ( *fmt )
      {
        case 'c':
          va = ((va + 3) & 0xFFFFFFFC) + 4;
          mem_ptr_01 = e->mem_ptr;
          mem_ptr_rval_04 = mem_ptr_01 + 1;
          if ( mem_ptr_01 >= (char *)e->mem_last )
            return -2;
          *mem_ptr_01 = *(u32 *)(va - 4);
          e->mem_ptr = mem_ptr_rval_04;
          ++fmt;
          continue;
        case 'p':
          has_sero = '0';
          if ( strlened < 8 )
            strlened = 8;
          strpad1 = 16;
          break;
        case 'X':
        case 'x':
          strpad1 = 16;
          break;
        case 'd':
        case 'u':
          strpad1 = 10;
          break;
        case 'o':
          strpad1 = 8;
          break;
        case 'S':
          fmt_flag_str = 1;
          break;
        case 's':
          fmt_flag_str = 0;
          break;
        default:
          mem_ptr_03 = (char *)e->mem_ptr;
          mem_ptr_rval_04 = mem_ptr_03 + 1;
          if ( mem_ptr_03 >= (char *)e->mem_last )
            return -2;
          *mem_ptr_03 = *fmt;
          e->mem_ptr = mem_ptr_rval_04;
          ++fmt;
          continue;
      }
      if ( fmt_flag_str != -1 )
      {
        cur_va2 = (char **)((va + 3) & 0xFFFFFFFC);
        va = (unsigned int)(cur_va2 + 1);
        strptr1 = *cur_va2;
        strlenmax = 0;
        if ( !strptr1 )
          strpad1 = 0;
      }
      if ( strpad1 )
      {
        va = ((va + 3) & 0xFFFFFFFC) + 4;
        cur_va1 = *(u32 *)(va - 4);
        stkstr1 = 0;
        strptr1 = &stkstr1;
        strlenmax = 0;
        if ( *fmt == 'd' )
        {
          if ( cur_va1 < 0 )
          {
            cur_va1 = -cur_va1;
            strlenmax = 1;
          }
        }
        while ( 1 )
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
          if ( !cur_va1 )
            break;
        }
      }
      if ( strptr1 )
      {
        strlen1 = strlen(strptr1);
        if ( strlenmax )
          strlencalc = strlened + 1 - strlen1;
        else
          strlencalc = strlened - strlen1;
        if ( has_sero == '0' && strlenmax )
        {
          mem_ptr_02 = e->mem_ptr;
          if ( mem_ptr_02 >= (char *)e->mem_last )
            return -2;
          *mem_ptr_02 = '-';
          e->mem_ptr = mem_ptr_02 + 1;
        }
        if ( !has_negative )
        {
          for ( ; strlencalc > 0; strlencalc -= 1 )
          {
            mem_ptr_04 = e->mem_ptr;
            if ( mem_ptr_04 >= (char *)e->mem_last )
              return -2;
            *mem_ptr_04 = has_sero;
            e->mem_ptr = mem_ptr_04 + 1;
          }
        }
        if ( has_sero != '0' && strlenmax )
        {
          mem_ptr_05 = e->mem_ptr;
          if ( mem_ptr_05 >= (char *)e->mem_last )
            return -2;
          *mem_ptr_05 = '-';
          e->mem_ptr = mem_ptr_05 + 1;
        }
        if ( fmt_flag_str != 1 )
        {
          for ( ; *strptr1; strptr1 += 1 )
          {
            strptr_curchr1 = *strptr1;
            mem_ptr_06 = (char *)e->mem_ptr;
            if ( mem_ptr_06 >= (char *)e->mem_last )
              return -2;
            *mem_ptr_06 = strptr_curchr1;
            e->mem_ptr = mem_ptr_06 + 1;
          }
        }
        else
        {
          for ( i = strptr1; *i; i += 1 )
          {
            if ( (((u8)*i - 0x81 >= 0x1F) && ((u8)*i - 0xE0 >= 0x1D))
              || ((u8)((int)*i - 64) >= 0xBDu)
              || (u8)*i == 0x7F )
            {
              if ( (u8)*i == '"' || (u8)*i == '\\' )
              {
                mem_ptr_07 = e->mem_ptr;
                if ( mem_ptr_07 >= (char *)e->mem_last )
                  return -2;
                *mem_ptr_07 = '\\';
                e->mem_ptr = mem_ptr_07 + 1;
                mem_ptr_rval_03 = mem_ptr_07 + 2;
                if ( mem_ptr_07 + 1 >= (char *)e->mem_last )
                  return -2;
                mem_ptr_07[1] = (u8)*i;
              }
              else if ( (u8)*i - ' ' < '_' )
              {
                mem_ptr_08 = e->mem_ptr;
                mem_ptr_rval_03 = mem_ptr_08 + 1;
                if ( mem_ptr_08 >= (char *)e->mem_last )
                  return -2;
                *mem_ptr_08 = (u8)*i;
              }
              else
              {
                mem_ptr_09 = e->mem_ptr;
                if ( mem_ptr_09 >= (char *)e->mem_last )
                  return -2;
                *mem_ptr_09 = '\\';
                e->mem_ptr = mem_ptr_09 + 1;
                if ( mem_ptr_09 + 1 >= (char *)e->mem_last )
                  return -2;
                mem_ptr_09[1] = 'x';
                e->mem_ptr = mem_ptr_09 + 2;
                mem_ptr_rval_01 = mem_ptr_09 + 3;
                if ( mem_ptr_09 + 2 >= (char *)e->mem_last )
                  return -2;
                mem_ptr_09[2] = a0123456789abcd_0[(u8)*i >> 4];
                e->mem_ptr = mem_ptr_rval_01;
                mem_ptr_rval_03 = mem_ptr_09 + 4;
                if ( (char *)mem_ptr_rval_01 >= (char *)e->mem_last )
                  return -2;
                mem_ptr_09[3] = a0123456789abcd_0[(u8)*i & 0xF];
              }
            }
            else
            {
              mem_ptr_0a = e->mem_ptr;
              mem_ptr_rval_02 = mem_ptr_0a + 1;
              if ( mem_ptr_0a >= (char *)e->mem_last )
                return -2;
              *mem_ptr_0a = (u8)*i;
              e->mem_ptr = mem_ptr_rval_02;
              i_curchr2 = *i++;
              if ( (char *)mem_ptr_rval_02 >= (char *)e->mem_last )
                return -2;
              mem_ptr_rval_03 = mem_ptr_0a + 2;
              mem_ptr_0a[1] = i_curchr2;
            }
            e->mem_ptr = mem_ptr_rval_03;
          }
        }
        for ( ; has_negative && strlencalc > 0; strlencalc -= 1 )
        {
          mem_ptr_0b = e->mem_ptr;
          if ( mem_ptr_0b >= (char *)e->mem_last )
            return -2;
          *mem_ptr_0b = ' ';
          e->mem_ptr = mem_ptr_0b + 1;
        }
      }
    }
    else
    {
      mem_ptr_03 = (char *)e->mem_ptr;
      mem_ptr_rval_04 = mem_ptr_03 + 1;
      if ( mem_ptr_03 >= (char *)e->mem_last )
        return -2;
      *mem_ptr_03 = *fmt;
      e->mem_ptr = mem_ptr_rval_04;
    }
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
  int offsptr3; // $s1
  const char *lbuf; // $s0
  char *offsptr1; // $v0
  int offsptr6; // $s0
  int offsptr4; // $s1
  int curjptoffs; // $s2

  for ( ; options->m_key; options += 1 )
  {
    result = 0;
    lbuf = (const char *)e->lbuf;
    switch ( options->m_type )
    {
      case '1':
        if ( *((u8 *)cnfdata + options->m_offset) == 255 )
        {
          lbuf = 0;
          break;
        }
        result = do_netcnf_sprintf_buffer(
                   e,
                   "%s %d\n",
                   options->m_key,
                   *((u8 *)cnfdata + options->m_offset));
        lbuf = 0;
        break;
      case '4':
        offsptr1 = (char *)cnfdata + options->m_offset;
        if ( *(int *)offsptr1 < 0 )
        {
          lbuf = 0;
          break;
        }
        result = do_netcnf_sprintf_buffer(e, "%s %d\n", options->m_key, *(u32 *)offsptr1);
        lbuf = 0;
        break;
      case 'A':
        if ( !strcmp("want.auth", options->m_key) ? !*((u8 *)cnfdata + 171) : !*((u8 *)cnfdata + 247) )
        {
          lbuf = 0;
          break;
        }
        offsptr3 = (u8)*((char *)cnfdata + options->m_offset);
        switch ( offsptr3 )
        {
          case 0:
            lbuf = "any";
            break;
          case 1:
            lbuf = "pap";
            break;
          case 2:
            lbuf = "chap";
            break;
          case 3:
            lbuf = "pap/chap";
            break;
          case 4:
            lbuf = "chap/pap";
            break;
          default:
            break;
        }
        break;
      case 'C':
        if ( !strcmp("want.accm", options->m_key) ? !*((u8 *)cnfdata + 170) : !*((u8 *)cnfdata + 246) )
        {
          lbuf = 0;
          break;
        }
        result = do_netcnf_sprintf_buffer(
                   e,
                   "%s 0x%08x\n",
                   options->m_key,
                   *(u32 *)((char *)cnfdata + options->m_offset));
        lbuf = 0;
        break;
      case 'D':
        offsptr3 = *(u32 *)((char *)cnfdata + options->m_offset);
        switch ( offsptr3 )
        {
          case -1:
          {
            lbuf = 0;
            break;
          }
          case 0:
            lbuf = "tone";
            break;
          case 1:
            lbuf = "pulse";
            break;
          case 2:
            lbuf = "any";
            break;
          default:
            break;
        }
        break;
      case 'L':
        offsptr4 = *(u32 *)((char *)cnfdata + options->m_offset);
        if ( offsptr4 == -1 )
        {
          lbuf = 0;
          break;
        }
        result = do_netcnf_sprintf_buffer(e, "%s", options->m_key);
        if ( result < 0 )
          return result;
        for ( curjptoffs = 0; curjptoffs < 32; curjptoffs += 1 )
        {
          lbuf = 0;
          switch ( (1 << curjptoffs) & offsptr4 )
          {
            case 1u:
              lbuf = "phase";
              break;
            case 2u:
              lbuf = "cp";
              break;
            case 4u:
              lbuf = "auth";
              break;
            case 8u:
              lbuf = "chat";
              break;
            case 0x10u:
              lbuf = "private";
              break;
            case 0x20u:
              lbuf = "dll";
              break;
            case 0x40u:
              lbuf = "dump";
              break;
            case 0x10000:
              lbuf = "timer";
              break;
            case 0x20000:
              lbuf = "event";
              break;
            default:
              break;
          }
          if ( lbuf )
          {
            offsptr4 &= ~(1 << curjptoffs);
            result = do_netcnf_sprintf_buffer(e, " %s", lbuf);
            if ( result < 0 )
              return result;
          }
        }
        if ( offsptr4 )
        {
          result = do_netcnf_sprintf_buffer(e, " 0x%x", offsptr4);
          if ( result < 0 )
            return result;
        }
        result = do_netcnf_sprintf_buffer(e, "\n");
        lbuf = 0;
        break;
      case 'M':
        if ( !strcmp("want.mru", options->m_key) ? !*((u8 *)cnfdata + 169) : !*((u8 *)cnfdata + 245) )
        {
          lbuf = 0;
          break;
        }
        result = do_netcnf_sprintf_buffer(
                   e,
                   "%s %d\n",
                   options->m_key,
                   *(u16 *)((char *)cnfdata + options->m_offset));
        lbuf = 0;
        break;
      case 'P':
        offsptr3 = *(u32 *)((char *)cnfdata + options->m_offset);
        switch ( offsptr3 )
        {
          case -1:
          {
            lbuf = 0;
            break;
          }
          case 1:
            lbuf = "auto";
            break;
          case 2:
            lbuf = "10";
            break;
          case 3:
            lbuf = "10_fd";
            break;
          case 4:
            lbuf = "10_fd_pause";
            break;
          case 5:
            lbuf = "tx";
            break;
          case 6:
            lbuf = "tx_fd";
            break;
          case 7:
            lbuf = "tx_fd_pause";
            break;
          default:
            break;
        }
        break;
      case 'T':
        offsptr3 = *(u32 *)((char *)cnfdata + options->m_offset);
        switch ( offsptr3 )
        {
          case -1:
          {
            lbuf = 0;
            break;
          }
          case 0:
            lbuf = "any";
            break;
          case 1:
            lbuf = "eth";
            break;
          case 2:
            lbuf = "ppp";
            break;
          case 3:
            lbuf = "nic";
            break;
          default:
            break;
        }
        break;
      case 'b':
        if ( *((u8 *)cnfdata + options->m_offset) == 255 )
        {
          lbuf = 0;
          break;
        }
        result = do_netcnf_sprintf_buffer(e, "%s%s\n", *((u8 *)cnfdata + options->m_offset) ? &g_null_string : (int *)"-", options->m_key);
        lbuf = 0;
        break;
      case 'c':
        offsptr3 = *((u8 *)cnfdata + options->m_offset);
        switch ( offsptr3 )
        {
          case 255:
          {
            lbuf = 0;
            break;
          }
          case 0:
            lbuf = "no";
            break;
          case 5:
            lbuf = "md5";
            break;
          case 128:
            lbuf = "ms-v1";
            break;
          case 129:
            lbuf = "ms-v2";
            break;
          default:
            break;
        }
        break;
      case 'p':
        offsptr6 = *(u32 *)((char *)cnfdata + options->m_offset);
        if ( !offsptr6 )
        {
          lbuf = 0;
          break;
        }
        result = do_netcnf_sprintf_buffer(e, "%s \"%S\"\n", options->m_key, offsptr6);
        lbuf = 0;
        break;
      default:
        return printf("netcnf: internal save error (%d, type=%c)\n", 302, options->m_type);
    }
    if ( lbuf )
    {
      if ( (char *)e->lbuf == (char *)lbuf )
      {
        sprintf((char *)e->lbuf, "0x%x", offsptr3);
      }
      result = do_netcnf_sprintf_buffer(e, "%s %s\n", options->m_key, lbuf);
    }
    if ( result < 0 )
      return result;
  }
  return 0;
}
// 40A728: using guessed type int g_null_string;

//----- (00407688) --------------------------------------------------------
int do_netcnf_net_write(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc)
{
  struct sceNetCnfCommand *cmd_head; // $s2
  int nameserverflag; // $s0
  int result; // $v0

  for ( cmd_head = ifc->cmd_head; cmd_head; cmd_head = cmd_head->forw )
  {
    nameserverflag = -1;
    switch ( cmd_head->code )
    {
      case 1:
        nameserverflag = 1;
        break;
      case 2:
        nameserverflag = 0;
        break;
      case 3:
      {
        result = do_netcnf_sprintf_buffer(e, "route add -%s", ( ((int)cmd_head[6].forw & 2) != 0 ) ? "host" : "net");
        if ( result < 0 )
          return result;
        if ( sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[1]) != 0 )
          return -1;
        result = do_netcnf_sprintf_buffer(e, " %s", (const char *)e->lbuf);
        if ( result < 0 )
          return result;
        if ( ((int)cmd_head[6].forw & 4) != 0 )
        {
          if ( sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[2].code) != 0 )
            return -1;
          result = do_netcnf_sprintf_buffer(e, " gw %s", (const char *)e->lbuf);
          if ( result < 0 )
            return result;
        }
        if ( sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[4].back) != 0 )
          return -1;
        result = do_netcnf_sprintf_buffer(e, " netmask %s", (const char *)e->lbuf);
        if ( result < 0 )
          return result;
        result = do_netcnf_sprintf_buffer(e, "\n");
        if ( result < 0 )
          return result;
      }
      case 4:
      {
        if ( sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[1]) != 0 )
          return -1;
        result = do_netcnf_sprintf_buffer(e, "route del %s\n", (const char *)e->lbuf);
        if ( result < 0 )
          return result;
      }
      default:
        return -1;
    }
    if ( nameserverflag != -1 )
    {
      if ( sceNetCnfAddress2String((char *)e->lbuf, 1024, (sceNetCnfAddress_t *)&cmd_head[1]) != 0 )
        return -1;
      result = do_netcnf_sprintf_buffer(e, "nameserver %s %s\n", nameserverflag ? "add" : "del", (const char *)e->lbuf);
      if ( result < 0 )
        return result;
    }
  }
  return 0;
}

//----- (004078CC) --------------------------------------------------------
int do_netcnf_phone_write(sceNetCnfEnv_t *e, struct sceNetCnfInterface *ifc)
{
  int ind1; // $s0
  int result; // $v0

  for ( ind1 = 0; ind1 < 10; ind1 += 1 )
  {
    if ( ifc->phone_numbers[ind1] )
    {
      result = do_netcnf_sprintf_buffer(e, "phone_number%d \"%S\"\n", ind1, ifc->phone_numbers[ind1]);
      if ( result < 0 )
        return result;
    }
  }
  return 0;
}

//----- (00407940) --------------------------------------------------------
int do_netcnf_unknown_write(sceNetCnfEnv_t *e, struct sceNetCnfUnknownList *unknown_list)
{
  struct sceNetCnfUnknown *head; // $s0
  int result; // $v0

  for ( head = unknown_list->head; head; head = head->forw )
  {
    result = do_netcnf_sprintf_buffer(e, "%s\n", (const char *)&head[1]);
    if ( result < 0 )
      return result;
  }
  return 0;
}

//----- (004079A4) --------------------------------------------------------
int do_write_netcnf(sceNetCnfEnv_t *e, const char *path, int is_attach_cnf)
{
  int memsize; // $s3
  char *fullpath; // $s0
  int result; // $v0
  int fd; // $v0
  int writeres; // $s0

  memsize = e->mem_ptr - e->mem_base;
  if ( e->f_verbose )
  {
    printf("netcnf: dir=%s path=%s\n", e->dir_name ? e->dir_name : "NULL", path ? path : "NULL");
  }
  fullpath = do_handle_netcnf_prerw(e, path);
  result = -1;
  if ( fullpath )
  {
    if ( e->f_verbose )
    {
      printf("netcnf: writing \"%s\" as ", fullpath);
      if ( is_attach_cnf )
        printf("ATTACH_CNF");
      else
        printf("NET_CNF");
      printf("\n");
    }
    if ( !is_attach_cnf || e->f_no_decode )
    {
      fd = do_open_netcnf(fullpath, 1538, 511);
      if ( fd >= 0 )
      {
        writeres = do_write_netcnf_no_encode(fd, e->mem_base, memsize);
        if ( memsize == writeres )
        {
          do_close_netcnf(fd);
          return 0;
        }
        else
        {
          ++e->file_err;
          do_close_netcnf(fd);
          result = -5;
          if ( writeres == -5 )
            return -18;
        }
      }
      else
      {
        ++e->file_err;
        if ( fd == -5 )
          return -18;
        return -3;
      }
    }
    else
    {
      result = 0;
      if ( do_write_netcnf_encode(fullpath, e->mem_base, memsize) < 0 )
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
            if ( result >= 0 )
            {
              return do_write_netcnf(e, arg_fname, 1);
            }
          }
        }
      }
    }
    else
    {
      for ( pair_head = e->root->pair_head; pair_head; pair_head = pair_head->forw )
      {
        result = do_netcnf_sprintf_buffer(
                   e,
                   "interface \"%S\" \"%S\" \"%S\"\n",
                   pair_head->display_name,
                   pair_head->attach_ifc,
                   pair_head->attach_dev);
        if ( result < 0 )
          return result;
      }
      result = do_netcnf_other_write(e, g_options_net_cnf, e->root);
      if ( result >= 0 )
      {
        result = do_netcnf_unknown_write(e, &e->root->unknown_list);
        if ( result >= 0 )
        {
          return do_write_netcnf(e, arg_fname, 0);
        }
      }
    }
  }
  return result;
}

//----- (00407CCC) --------------------------------------------------------
int do_export_netcnf(sceNetCnfEnv_t *e)
{
  if ( e->req != 1 && e->req != 2 )
  {
    return -1;
  }
  else
  {
    if ( e->req != 2 )
      return -1;
  }
  if ( do_export_netcnf_inner(e, e->arg_fname, ( e->req == 1 ) ? 0 : e->ifc) != 0 )
    return -1;
  return 0;
}

//----- (00407D40) --------------------------------------------------------
char *do_address_to_string_inner_element(char *dst, int srcbyte)
{
  u8 *tmpstk_ptr; // $a2
  u8 tmpstk[16]; // [sp+0h] [-10h] BYREF

  tmpstk_ptr = tmpstk;
  if ( srcbyte < 0 )
  {
    *dst++ = '-';
    srcbyte = -srcbyte;
  }
  for ( ; srcbyte > 0; srcbyte /= 10 )
  {
    *tmpstk_ptr = srcbyte % 10 + 48;
    ++tmpstk_ptr;
  }
  for ( ; tmpstk < tmpstk_ptr; tmpstk_ptr -= 1 )
    *dst++ = *(tmpstk_ptr - 1);
  return dst;
}

//----- (00407DD0) --------------------------------------------------------
void do_address_to_string_inner(char *dst, unsigned int srcint)
{
  char *elm1; // $v0

  elm1 = do_address_to_string_inner_element(dst, (srcint >> 24) & 0xFF);
  *elm1 = '.';
  elm1 = do_address_to_string_inner_element(elm1 + 1, (srcint >> 16) & 0xFF);
  *elm1 = '.';
  elm1 = do_address_to_string_inner_element(elm1 + 1, (srcint >> 8) & 0xFF);
  *elm1 = '.';
  elm1 = do_address_to_string_inner_element(elm1 + 1, srcint & 0xFF);
  *elm1 = 0;
}

//----- (00407E50) --------------------------------------------------------
int do_name_2_address_inner(unsigned int *dst, char *buf)
{
  int prefixchkn; // $s4
  int curindx2; // $s6
  int base; // $s2
  unsigned int i; // $s3
  int offsbase1; // $a0
  int tmpstk1[3]; // [sp+10h] [-10h] BYREF

  prefixchkn = 0;
  curindx2 = -1;
  while ( 1 )
  {
    base = 10;
    if ( *buf == '0' )
    {
      base = 8;
      buf++;
      if ( *buf == 'x' || *buf == 'X' )
      {
        buf++;
        base = 16;
      }
    }
    for ( i = 0; isxdigit(*buf); i = i * base + offsbase1 )
    {
      offsbase1 = *buf - '0';
      if ( !isdigit(*buf) )
      {
        offsbase1 = *buf - '7';
        if ( !isupper(*buf) )
          offsbase1 = *buf - 'W';
      }
      if ( offsbase1 >= base )
        break;
      ++buf;
    }
    if ( prefixchkn > 0 )
    {
      if ( (unsigned int)tmpstk1[curindx2] >= 0x100 )
        return 0;
    }
    tmpstk1[curindx2] = i;
    ++curindx2;
    ++prefixchkn;
    if ( *buf != '.' || prefixchkn >= 4 )
      break;
    ++buf;
  }
  if ( !*buf || *buf == ' ' )
  {
    switch ( prefixchkn )
    {
      case 1:
        break;
      case 2:
        if ( (i >> 24) )
          return 0;
        i |= tmpstk1[0] << 24;
        break;
      case 3:
        if ( (i >> 16) )
          return 0;
        i |= (tmpstk1[0] << 24) | (tmpstk1[1] << 16);
        break;
      case 4:
        if ( (i >> 8) )
          return 0;
        i |= (tmpstk1[0] << 24) | (tmpstk1[1] << 16) | (tmpstk1[2] << 8);
        break;
      default:
        return 0;
    }
    *dst = i;
    return 1;
  }
  return 0;
}

//----- (00408080) --------------------------------------------------------
int do_conv_a2s_inner(char *sp_, char *dp_, int len)
{
  int len_minus_three; // $a2
  int curindx1; // $t2
  char *dp_ptroffs1; // $a1
  char *dp_ptroffs2; // $a1
  char *dp_ptroffs3; // $a1

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
    for ( ; *sp_ == ' ' || *sp_ == '\t'; sp_ += 1 );
    if ( !*sp_ )
      break;
    if ( *sp_ != 'A' && *sp_ != 'a' )
      return 0;
    if ( sp_[1] != 'T' && sp_[1] != 't' )
      return 0;
    for ( ; *sp_ && *sp_ != ' ' && *sp_ != '\t'; sp_ += 1 )
    {
      if ( --len_minus_three <= 0 )
        return -19;
      if ( *sp_ == '-' || *sp_ == '\\' || *sp_ == '"' || *sp_ == '^' )
      {
        --len_minus_three;
        if ( len_minus_three <= 0 )
          return -19;
        *dp_ptroffs2++ = '\\';
      }
      *dp_ptroffs2++ = *sp_;
    }
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
  if ( curindx1 <= 0 )
    return 0;
  if ( (len_minus_three - 2) <= 0 )
    return -19;
  strcpy(dp_ptroffs2, "\\c");
  return 1;
}
// 408134: conditional instruction was optimized away because $a3.4 is in (==41|==61)

//----- (0040822C) --------------------------------------------------------
int do_conv_s2a_inner(char *sp_, char *dp_, int len)
{
  int curindx1; // $t2
  char *sp_minus_one1; // $a0
  char *sp_ptroffs1; // $a0
  char *sp_ptroffs2; // $a0
  char *sp_ptroffs3; // $a0
  char *sp_ptroffs4; // $a0

  curindx1 = 0;
  for ( ; *sp_ == ' ' || *sp_ == '\t'; sp_ += 1 );
  sp_minus_one1 = sp_;
  if ( *sp_minus_one1 != '"' )
    return 0;
  if ( sp_minus_one1[1] != '"' )
    return 0;
  if ( sp_minus_one1[2] != ' ' && sp_minus_one1[2] != '\t' )
    return 0;
  sp_ptroffs1 = sp_minus_one1 + 3;
  while ( 1 )
  {
    for ( ; *sp_ptroffs1 == ' ' || *sp_ptroffs1 == '\t'; sp_ptroffs1 += 1 );
    sp_ptroffs2 = sp_ptroffs1;
    if ( !*sp_ptroffs2 || *sp_ptroffs2 == '\\' )
    {
      if ( *sp_ptroffs2 != '\\' )
        return 0;
      if ( sp_ptroffs2[1] != 'c' )
        return 0;
      sp_ptroffs4 = sp_ptroffs2 + 2;
      for ( ; *sp_ptroffs4 == ' ' || *sp_ptroffs4 == '\t'; sp_ptroffs4 += 1 );
      if ( *sp_ptroffs4 )
        return -19;
      if ( curindx1 <= 0 )
        return 0;
      if ( (int)(len - 1) < 0 )
        return -19;
      *dp_ = 0;
      return 1;
    }
    if ( *sp_ptroffs2 != 'A' && *sp_ptroffs2 != 'a' )
      return 0;
    if ( sp_ptroffs2[1] != 'T' && sp_ptroffs2[1] != 't' )
      return 0;
    if ( curindx1 > 0 )
    {
      if ( --len <= 0 )
        return -19;
      *dp_++ = ' ';
    }
    if ( *sp_ptroffs2 )
    {
      ++sp_ptroffs2;
      if ( (*(sp_ptroffs2 - 1)) != ' ' )
      {
        --sp_ptroffs2;
        while ( *sp_ptroffs2 != '\t' )
        {
          if ( --len <= 0 )
            return -19;
          if ( *sp_ptroffs2 == '\\' )
          {
            if ( sp_ptroffs2[1] != '-' && sp_ptroffs2[1] != '\\' && sp_ptroffs2[1] != '"' && sp_ptroffs2[1] != '^' )
              return 0;
            ++sp_ptroffs2;
          }
          *dp_++ = *sp_ptroffs2++;
          if ( *sp_ptroffs2 )
          {
            if ( *sp_ptroffs2 != ' ' )
              continue;
          }
          break;
        }
      }
    }
    for ( ; *sp_ptroffs2 == ' ' || *sp_ptroffs2 == '\t'; sp_ptroffs2 += 1 );
    sp_ptroffs3 = sp_ptroffs2;
    if ( *sp_ptroffs3 != 'O' )
      return 0;
    if ( sp_ptroffs3[1] != 'K' )
      return 0;
    if ( sp_ptroffs3[2] != ' ' && sp_ptroffs3[2] != '\t' )
      return 0;
    sp_ptroffs1 = sp_ptroffs3 + 3;
    ++curindx1;
  }
}

//----- (004084A0) --------------------------------------------------------
int do_check_aolnet(const char *auth_name)
{
  int i; // $s1
  const char *periodpos; // $v0

  if ( strncmp(auth_name, "aolnet/", 7) == 0 )
  {
    periodpos = auth_name;
    for ( i = 0; periodpos; i += 1 )
    {
      periodpos = strchr(periodpos, '.');
      if ( periodpos )
        periodpos += 1;
    }
    if ( i != 5 )
      return 0;
    return -20;
  }
  return 0;
}

//----- (00408514) --------------------------------------------------------
int do_check_authnet(char *argst, char *arged)
{
  char *i; // $s0
  char *j; // $s0
  int result; // $v0

  for ( i = arged; argst < i && *(i - 1) < '!'; i -= 1 );
  *i = 0;
  for ( j = argst; *j && isspace(*j); j += 1 );
  if ( !strncmp(j, "auth_name", 9) )
  {
    for ( ; *j && !isspace(*j); j += 1 );
    for ( ; *j && isspace(*j); j += 1 );
    if ( *j == '"' )
      ++j;
    result = do_check_aolnet(j);
    if ( result < 0 )
      return result;
  }
  return 0;
}

//----- (00408644) --------------------------------------------------------
int do_read_check_netcnf(const char *netcnf_path, int type, int no_check_magic, int no_decode)
{
  int read_res2; // $s1
  char *heapmem; // $v0
  int errretres; // $s2
  char *curheapptr1; // $s4
  char *heapmem_2; // $s0
  int curchind; // $s0

  switch ( type )
  {
    case 0:
    case 2:
      return 0;
    default:
      return -10;
    case 1:
      break;
  }
  if ( no_decode )
    read_res2 = do_read_netcnf_no_decode(netcnf_path, &g_read_check_netcnf_heapptr);
  else
    read_res2 = do_read_netcnf_decode(netcnf_path, &g_read_check_netcnf_heapptr);
  if ( read_res2 < 0 )
    return read_res2;
  heapmem = (char *)do_alloc_heapmem(1024);
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
      || (strncmp(g_read_check_netcnf_heapptr, "# <Sony Computer Entertainment Inc.>", 36) != 0) )
    {
      printf("netcnf: decoding error (magic=\"");
      for ( curchind = 0; curchind < read_res2 && curchind < 36; curchind += 1 )
      {
        printf("%c", (unsigned int)((u8)curheapptr1[curchind] - 32) >= 0x5F ? '?' : (char)(u8)curheapptr1[curchind]);
      }
      errretres = -15;
      printf("\")\n");
    }
  }
  if ( !errretres && read_res2 > 0 )
  {
    read_res2--;
    for ( ; read_res2 > 0; read_res2 -= 1 )
    {
      if ( *curheapptr1 == '\n' )
      {
        if ( heapmem < heapmem_2 && *(heapmem_2 - 1) == '\\' )
        {
          --heapmem_2;
        }
        else
        {
          *heapmem_2 = 0;
          errretres = do_check_authnet(heapmem, heapmem_2);
          heapmem_2 = heapmem;
          if ( errretres < 0 )
            break;
        }
      }
      else
      {
        if ( heapmem_2 < heapmem + 1023 && *curheapptr1 != '\r' )
          *heapmem_2++ = *curheapptr1;
      }
      curheapptr1++;
    }
  }
  if ( !errretres && heapmem < heapmem_2 )
    errretres = do_check_authnet(heapmem, heapmem_2);
  do_free_heapmem(g_read_check_netcnf_heapptr);
  do_free_heapmem(heapmem);
  return errretres;
}

//----- (004088DC) --------------------------------------------------------
int do_check_provider_inner(sceNetCnfEnv_t *e, int type)
{
  int result; // $v0

  if ( type == 1 )
  {
    if ( e )
    {
      if ( e->ifc )
      {
        if ( e->ifc->auth_name )
        {
          result = do_check_aolnet((const char *)e->ifc->auth_name);
          if ( result < 0 )
            return result;
        }
        return 0;
      }
    }
    return -14;
  }
  else
  {
    if ( type < 2 )
    {
      if ( type )
        return -10;
      return 0;
    }
    if ( type == 2 )
      return 0;
    return -10;
  }
}

//----- (00408970) --------------------------------------------------------
char *do_handle_netcnf_dirname(char *fpath, const char *entry_buffer, char *netcnf_file_path)
{
  const char *entry_buffer_1; // $v1
  char *fpath_1; // $a3
  char *fpath_1_minus_1; // $a3
  char *fpath_2; // $v1
  char *i; // $t0
  const char *entry_buffer_2; // $v1

  if ( !entry_buffer || !*entry_buffer )
    return 0;
  for ( entry_buffer_1 = entry_buffer; *entry_buffer_1; entry_buffer_1 += 1 )
  {
    if ( *entry_buffer_1 == ':' )
      return (char *)entry_buffer;
  }
  if ( !fpath || !*fpath )
    return (char *)entry_buffer;
  for ( fpath_1 = fpath; fpath_1[1]; fpath_1 += 1 );
  fpath_1_minus_1 = fpath_1 - 1;
  if ( fpath < fpath_1_minus_1 || *entry_buffer == '/' || *entry_buffer == '\\' )
  {
    for ( ; fpath < fpath_1_minus_1 && *fpath_1_minus_1 != ':'; fpath_1_minus_1 -= 1 );
    if ( *fpath_1_minus_1 == ':' || *fpath_1_minus_1 == '/' || *fpath_1_minus_1 == '\\' )
    {
      ++fpath_1_minus_1;
    }
  }
  else if ( *fpath_1_minus_1 != ':' )
  {
    for ( ; fpath < fpath_1_minus_1 && *fpath_1_minus_1 != ':' && *fpath_1_minus_1 != '/' && *fpath_1_minus_1 != '\\'; fpath_1_minus_1 -= 1 );
    if ( *fpath_1_minus_1 == ':' || *fpath_1_minus_1 == '/' || *fpath_1_minus_1 == '\\' )
    {
      ++fpath_1_minus_1;
    }
  }
  fpath_2 = fpath;
  for ( i = netcnf_file_path; fpath_2 < fpath_1_minus_1; i += 1 )
  {
    *i = *fpath_2++;
  }
  for ( entry_buffer_2 = entry_buffer; *entry_buffer_2; entry_buffer_2 += 1 )
  {
    *i++ = *entry_buffer_2;
  }
  *i = 0;
  return netcnf_file_path;
}

//----- (00408B20) --------------------------------------------------------
int do_get_filesize_inner(int fd)
{
  int lseek_end_res; // $s0
  int lseek_start_res; // $a0

  lseek_end_res = lseek(fd, 0, 2);
  if ( lseek_end_res >= 0 )
  {
    lseek_start_res = lseek(fd, 0, 0);
    if ( lseek_start_res < 0 )
    {
      if ( lseek_start_res != -5 )
        return -6;
      return -18;
    }
    return lseek_end_res;
  }
  else
  {
    if ( lseek_end_res != -5 )
      return -6;
    return -18;
  }
}

//----- (00408B9C) --------------------------------------------------------
int is_special_file_path(const char *netcnf_path)
{
  if ( g_callbacks.type == 1 )
  {
    if ( strncmp(netcnf_path, "mc", 2) == 0 )
      return 1;
  }
  else
  {
    if ( g_callbacks.type != 2 )
      return 1;
    if ( strncmp(netcnf_path, "ext", 3) == 0 )
      return 1;
  }
  return 0;
}
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (00408C18) --------------------------------------------------------
void do_init_callback_handles(void)
{
  int handleind1; // $v1

  for ( handleind1 = 0; handleind1 < 4; handleind1 += 1 )
  {
    g_callback_handle_infos[handleind1].m_fd = -1;
    g_callback_handle_infos[handleind1].m_filesize = 0;
    g_callback_handle_infos[handleind1].m_allocstate = 0;
  }
}

//----- (00408C60) --------------------------------------------------------
int do_get_empty_callback_handle(int in_fd, int in_allocstate)
{
  int indtmp1; // $a3

  for ( indtmp1 = 0; indtmp1 < 4; indtmp1 += 1 )
  {
    if ( g_callback_handle_infos[indtmp1].m_fd == -1 )
    {
      g_callback_handle_infos[indtmp1].m_fd = in_fd;
      g_callback_handle_infos[indtmp1].m_allocstate = in_allocstate;
      g_open_callback_handle_count += 1;
      return indtmp1;
    }
  }
  return -1;
}
// 40C7E0: using guessed type int g_open_callback_handle_count;

//----- (00408CCC) --------------------------------------------------------
int do_filesize_callback_handles(int in_fd, int in_allocstate)
{
  int indtmp1; // $a2

  for ( indtmp1 = 0; indtmp1 < 4; indtmp1 += 1 )
  {
    if ( g_callback_handle_infos[indtmp1].m_fd == in_fd
      && (g_callback_handle_infos[indtmp1].m_allocstate == in_allocstate || !in_allocstate) )
    {
      return indtmp1;
    }
  }
  return -1;
}

//----- (00408D2C) --------------------------------------------------------
void do_clear_callback_handles(int fd, int allocmatch)
{
  int indtmp; // $a3

  for ( indtmp = 0; indtmp < 4; indtmp += 1 )
  {
    if ( g_callback_handle_infos[indtmp].m_fd == fd && g_callback_handle_infos[indtmp].m_allocstate == allocmatch )
    {
      g_callback_handle_infos[indtmp].m_fd = -1;
      g_callback_handle_infos[indtmp].m_allocstate = 0;
      g_open_callback_handle_count -= 1;
      break;
    }
  }
}
// 40C7E0: using guessed type int g_open_callback_handle_count;

//----- (00408DA0) --------------------------------------------------------
const char *do_colon_callback_handles(const char *netcnf_path, char *device)
{
  char *index_res; // $s1
  int devnameend; // $s0

  index_res = index(netcnf_path, ':');
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
      if ( strlen(index_res + 1) + 1 < 257 )
        return index_res + 1;
    }
  }
  return 0;
}

//----- (00408E40) --------------------------------------------------------
int do_open_netcnf(const char *netcnf_path, int file_flags, int file_mode)
{
  const char *cbind; // $v0
  int openret1; // $s2
  int empty_callback_handle; // $s0
  char pathconcat[16]; // [sp+18h] [-18h] BYREF
  int filesz1; // [sp+28h] [-8h] BYREF

  if ( !g_callbacks.open )
    return open(netcnf_path, file_flags, file_mode);
  if ( !is_special_file_path(netcnf_path) )
    return open(netcnf_path, file_flags, file_mode);
  if ( g_open_callback_handle_count < 4 )
  {
    cbind = do_colon_callback_handles(netcnf_path, pathconcat);
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
        strcpy(g_callback_handle_infos[empty_callback_handle].m_pathname, cbind);
        g_callback_handle_infos[empty_callback_handle].m_buf = 0;
        g_callback_handle_infos[empty_callback_handle].m_bufpos = 0;
        g_callback_handle_infos[empty_callback_handle].m_filesize = filesz1;
      }
      return openret1;
    }
    else
    {
      return -1;
    }
  }
  return -1;
}
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;
// 40C344: using guessed type int (*)(u32, u32, u32, u32, u32);
// 40C7E0: using guessed type int g_open_callback_handle_count;

//----- (00408F8C) --------------------------------------------------------
size_t do_read_callback_handles(int handlefd, int fd, void *ptr, size_t size)
{
  struct netcnf_callback_handle_info *cbh; // $s0

  cbh = &g_callback_handle_infos[handlefd];
  if ( cbh->m_bufpos )
  {
  }
  else
  {
    cbh->m_buf = do_alloc_heapmem(cbh->m_filesize);
    if ( !cbh->m_buf )
      return -1;
    if ( ((int (*)(int, char *, char *, void *, u32, int))g_callbacks.read)(fd, cbh->m_device, cbh->m_pathname, cbh->m_buf, 0, cbh->m_filesize) != cbh->m_filesize )
    {
      do_free_heapmem(cbh->m_buf);
      cbh->m_buf = 0;
      return -1;
    }
  }
  memcpy(ptr, (char *)cbh->m_buf + cbh->m_bufpos, size);
  cbh->m_bufpos += size;
  return size;
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
void do_close_netcnf(int fd)
{
  int cbind; // $s1

  if ( !g_callbacks.close )
  {
    close(fd);
    return;
  }
  cbind = do_filesize_callback_handles(fd, 1);
  if ( cbind == -1 )
  {
    close(fd);
    return;
  }
  ((int (*)(int))g_callbacks.close)(fd);
  do_free_heapmem(g_callback_handle_infos[cbind].m_buf);
  g_callback_handle_infos[cbind].m_buf = 0;
  do_clear_callback_handles(fd, 1);
}
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;
// 40C34C: using guessed type int (*)(u32);

//----- (00409328) --------------------------------------------------------
void do_dclose_wrap(int fd)
{
  if ( !g_callbacks_set || g_callbacks.type == 2 )
    dclose(fd);
  else
    printf("[err] netcnf dclose()\n");
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
void do_getstat_wrap(const char *fn, iox_stat_t *stat)
{
  if ( !g_callbacks_set || g_callbacks.type == 2 )
    getstat(fn, stat);
  else
    printf("[err] netcnf getstat()\n");
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (0040943C) --------------------------------------------------------
void do_chstat_mode_copyprotect_wrap(const char *fn)
{
  iox_stat_t statmode; // [sp+10h] [-40h] BYREF

  if ( !g_callbacks_set || g_callbacks.type == 2 )
  {
    do_getstat_wrap(fn, &statmode);
    statmode.mode |= 8u;
    chstat(fn, &statmode, 1u);
  }
  else
  {
    printf("[err] netcnf chstat()\n");
  }
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;

//----- (004094C0) --------------------------------------------------------
void do_set_callback_inner(sceNetCnfCallback_t *pcallback)
{
  if ( pcallback )
  {
    g_callbacks.type = pcallback->type;
    g_callbacks.open = pcallback->open;
    g_callbacks.read = pcallback->read;
    g_callbacks.close = pcallback->close;
    g_callbacks_set = 1;
  }
  else
  {
    memset(&g_callbacks, 0, sizeof(g_callbacks));
    g_callbacks_set = 0;
  }
  do_init_callback_handles();
}
// 40B0F0: using guessed type int g_callbacks_set;
// 40C340: using guessed type sceNetCnfCallback_t g_callbacks;
// 40C344: using guessed type int (*)(u32, u32, u32, u32, u32);
// 40C348: using guessed type int (*)(u32, u32, u32, u32, u32, u32);
// 40C34C: using guessed type int (*)(u32);

//----- (00409540) --------------------------------------------------------
int do_init_heap(void)
{
  if ( g_netcnf_heap )
    return -2;
  g_netcnf_heap = CreateHeap(1024, 1);
  if ( g_netcnf_heap )
    return 0;
  return -1;
}

//----- (00409590) --------------------------------------------------------
void *do_alloc_heapmem(size_t nbytes)
{
  return AllocHeapMemory(g_netcnf_heap, nbytes);
}

//----- (004095BC) --------------------------------------------------------
void do_free_heapmem(void *ptr)
{
  if ( ptr )
    FreeHeapMemory(g_netcnf_heap, ptr);
}

//----- (004095EC) --------------------------------------------------------
void do_delete_heap(void)
{
  DeleteHeap(g_netcnf_heap);
  g_netcnf_heap = 0;
}
