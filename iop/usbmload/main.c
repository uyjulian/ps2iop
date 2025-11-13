
#include "irx_imports.h"

IRX_ID("USB_module_loader", 2, 1);

typedef struct _USBDEV_t
{
  struct _USBDEV_t *forw;
  char *dispname;
  int vendor;
  int product;
  int release;
  int class_;
  int subclass;
  int protocol;
  char *category;
  char *path;
  char *argv[8];
  int argc;
  char activate_flag;
  int modid;
  char modname[56];
  int load_result;
} USBDEV_t;

typedef USBDEV_t *(*sceUsbmlPopDevinfo)(void);

typedef void (*sceUsbmlLoadFunc)(sceUsbmlPopDevinfo pop_devinfo);

struct usbm_load_entry
{
  struct usbm_load_entry *m_next;
  char *m_devicename;
  int m_vendor;
  int m_product;
  int m_release;
  int m_class;
  int m_subclass;
  int m_protocol;
  char *m_category;
  char *m_driverpath;
  char *m_driverargs[8];
  int m_driverargs_len;
  int m_x20;
  int m_ldd_module_id;
  int m_x22;
  int m_x23;
  int m_x24;
  int m_x25;
  int m_x26;
  int m_x27;
  int m_x28;
  int m_x29;
  int m_x30;
  int m_x31;
  int m_x32;
  int m_x33;
  int m_x34;
  int m_x35;
  int m_x36;
};

//-------------------------------------------------------------------------
// Function declarations

int _start(int ac, char **av);
int module_unload();
int do_parse_config_file(const char *fn);
void do_print_device_config_info(USBDEV_t *devinfo);
int usbmload_drv_probe(int dev_id);
int usbmload_drv_connect(int dev_id);
int usbmload_drv_disconenct(int dev_id);
void ldd_loader_thread(); // weak
void default_loadfunc(sceUsbmlPopDevinfo pop_devinfo);
void do_push_device_rb(USBDEV_t *a1);
USBDEV_t *is_rb_ok_callback();
void do_clear_rb(void);
int split_config_line(char *curbuf, int cursplitind, char **dstptr);
int do_parse_cmd_int(const char *buf);
void clean_config_line(char *buf);
void sanitize_devicename(char *buf);
int sceUsbmlDisable(void);
int sceUsbmlEnable(void);
int sceUsbmlActivateCategory(const char *category);
int sceUsbmlInactivateCategory(const char *category);
int sceUsbmlRegisterLoadFunc(sceUsbmlLoadFunc loadfunc);
void sceUsbmlUnregisterLoadFunc(void);
int sceUsbmlLoadConffile(const char *conffile);
int sceUsbmlRegisterDevice(USBDEV_t *device);
int sceUsbmlChangeThreadPriority(int prio1);
void init_config_pos(void);
char read_config_byte(int fd);
char *read_config_line(char *dstbuf, int maxlen, int fd);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_usbmload;
sceUsbdLddOps g_usbmload_drv =
{
  NULL,
  NULL,
  "usbmload",
  &usbmload_drv_probe,
  &usbmload_drv_connect,
  &usbmload_drv_disconenct,
  0u,
  0u,
  0u,
  0u,
  0u,
  NULL
}; // idb
int g_config_chr_pos = 2048; // weak
int g_param_conffile[128]; // weak
char g_config_line_buf[256]; // weak
char g_config_device_name_tmp[256]; // idb
int g_param_debug; // weak
int g_usbmload_enabled; // weak
int g_param_rbsize; // weak
int g_rb_offset_read; // weak
int g_rb_offset_write; // weak
int g_rb_count; // weak
USBDEV_t **g_rb_entries;
USBDEV_t *g_usbm_entry_list_end;
USBDEV_t *g_usbm_entry_list_cur;
int g_ef; // weak
int g_thid; // idb
sceUsbmlLoadFunc g_loadfunc_cb;
char g_config_chr_buf[2048]; // weak

//----- (00400060) --------------------------------------------------------
int _start(int ac, char **av)
{
  int has_conffile; // $s4
  int cur_ac; // $s3
  char **cur_av; // $s1
  int cur_av_pos; // $s0
  char *cur_av_curstr1; // $a0
  int rbmul; // $
  int thid1; // $s0
  int thid2; // $a0
  iop_event_t efparam; // [sp+10h] [-30h] BYREF
  iop_thread_t thparam; // [sp+20h] [-20h] BYREF
  int state; // [sp+38h] [-8h] BYREF

  has_conffile = 0;
  if ( ac < 0 )
    return module_unload();
  
  printf("----- USB auto module loader %s -----\n", "0.4.0");
  g_param_rbsize = 32;
  g_loadfunc_cb = (sceUsbmlLoadFunc)default_loadfunc;
  g_param_debug = 0;
  g_usbmload_enabled = 0;
  g_rb_offset_read = 0;
  g_rb_offset_write = 0;
  g_rb_count = 0;
  g_usbm_entry_list_end = 0;
  g_usbm_entry_list_cur = 0;
  cur_av = av;
  for ( cur_ac = 0; cur_ac < ac; cur_ac += 1 )
  {
    cur_av_curstr1 = *cur_av;
    for ( cur_av_pos = 0; cur_av_curstr1[cur_av_pos] && cur_av_curstr1[cur_av_pos] != '='; cur_av_pos += 1 );
    if ( cur_av_curstr1[cur_av_pos] )
    {
      cur_av_curstr1[cur_av_pos] = 0;
      cur_av_pos += 1;
    }
    if ( !strcmp(*cur_av, "conffile") )
    {
      if ( (unsigned int)strlen(&(*cur_av)[cur_av_pos]) < 0x200 )
      {
        strcpy((char *)g_param_conffile, &(*cur_av)[cur_av_pos]);
        has_conffile = 1;
        if ( g_param_debug > 0 )
          printf("conffile=%s\n", g_param_conffile);
      }
      else
      {
        printf("Too long file name : %s\n", &(*cur_av)[cur_av_pos]);
      }
    }
    else if ( !strcmp(*cur_av, "debug") )
    {
      g_param_debug = do_parse_cmd_int(&(*cur_av)[cur_av_pos]);
      printf("Debug level is %d\n", g_param_debug);
    }
    else if ( !strcmp(*cur_av, "rbsize") )
    {
      g_param_rbsize = do_parse_cmd_int(&(*cur_av)[cur_av_pos]);
      if ( g_param_rbsize >= 257 )
        g_param_rbsize = 256;
      if ( g_param_rbsize < 8 )
        g_param_rbsize = 8;
      if ( g_param_debug > 0 )
        printf("usbmload : ring buffer size = %d\n", g_param_rbsize);
    }
    ++cur_av;
  }
  rbmul = 4 * g_param_rbsize;
  if ( g_param_debug > 0 )
    printf("allocsize(for ring buffer) : %d\n", 4 * g_param_rbsize);
  CpuSuspendIntr(&state);
  g_rb_entries = (USBDEV_t **)AllocSysMemory(0, rbmul, 0);
  CpuResumeIntr(state);
  if ( !g_rb_entries )
  {
    printf("Ring buffer Initialize Error!!\n");
    return 1;
  }
  if ( RegisterLibraryEntries(&_exp_usbmload) != 0 )
    return 1;
  if ( has_conffile == 1 )
  {
    if ( do_parse_config_file((const char *)g_param_conffile) == -1 )
    {
      printf("usbmload : load_config NG\n");
    }
    else if ( g_param_debug > 0 )
    {
      printf("usbmload : load_config OK\n");
    }
  }
  memset(&efparam, 0, sizeof(efparam));
  g_ef = CreateEventFlag(&efparam);
  if ( g_ef < 0 )
  {
    printf("usbmload :  CreateEventFlag NG\n");
    return 1;
  }
  thparam.attr = 0x2000000;
  thparam.thread = (void (*)(void *))ldd_loader_thread;
  thparam.priority = 88;
  thparam.stacksize = 4096;
  thparam.option = 0;
  thid1 = CreateThread(&thparam);
  if ( thid1 <= 0 )
  {
    printf("usbmload : CreateThread NG\n");
    DeleteEventFlag(g_ef);
    return 1;
  }
  else
  {
    thid2 = thid1;
    if ( g_param_debug > 0 )
    {
      printf("usbmload : CreateThread ID = %d\n", thid1);
      thid2 = thid1;
    }
    StartThread(thid2, 0);
    g_thid = thid1;
    return 2;
  }
}
// 4010C4: using guessed type void ldd_loader_thread();
// 402700: using guessed type int g_param_conffile[128];
// 402B00: using guessed type int g_param_debug;
// 402B04: using guessed type int g_usbmload_enabled;
// 402B08: using guessed type int g_param_rbsize;
// 402B0C: using guessed type int g_rb_offset_read;
// 402B10: using guessed type int g_rb_offset_write;
// 402B14: using guessed type int g_rb_count;
// 402B24: using guessed type int g_ef;

//----- (00400480) --------------------------------------------------------
int module_unload()
{
  USBDEV_t *listent_1; // $s2
  int argind; // $s1
  USBDEV_t *listent_3; // $a0
  int stopres; // [sp+10h] [-8h] BYREF
  int state; // [sp+14h] [-4h] BYREF

  if ( ReleaseLibraryEntries(&_exp_usbmload) == 0 )
  {
    sceUsbmlDisable();
    TerminateThread(g_thid);
    DeleteThread(g_thid);
    DeleteEventFlag(g_ef);
    listent_1 = g_usbm_entry_list_end;
    while ( listent_1 )
    {
      if ( StopModule(listent_1->modid, 0, 0, &stopres) >= 0 )
      {
        if ( g_param_debug > 0 )
          printf("usbmload : Unload LDD module (%xh)\n", listent_1->modid);
        UnloadModule(listent_1->modid);
      }
      CpuSuspendIntr(&state);
      for ( argind = 0; argind < listent_1->argc; argind += 1 )
      {
        FreeSysMemory(listent_1->argv[argind]);
      }
      FreeSysMemory(listent_1->dispname);
      FreeSysMemory(listent_1->category);
      FreeSysMemory(listent_1->path);
      listent_3 = listent_1;
      listent_1 = listent_1->forw;
      FreeSysMemory(listent_3);
      CpuResumeIntr(state);
    }
    CpuSuspendIntr(&state);
    FreeSysMemory(g_rb_entries);
    CpuResumeIntr(state);
    return 1;
  }
  return 2;
}
// 402B00: using guessed type int g_param_debug;
// 402B24: using guessed type int g_ef;

//----- (00400600) --------------------------------------------------------
int do_parse_config_file(const char *fn)
{
  USBDEV_t *devstr; // $s0
  int has_encountered; // $s6
  int fd; // $s4
  int lineind; // $s2
  int tokencnt; // $s1
  size_t dispname_len; // $v0
  char *dispname_tmp; // $v0
  char *dispname; // $a0
  size_t category_tmplen; // $v0
  char *category_tmp; // $v0
  char *category; // $a0
  size_t driverpath_tmplen; // $v0
  char *driverpath_tmp; // $v0
  size_t driverarg_tmp; // $v0
  char *driverarg_tmplen; // $v0
  char *driverarg_end; // $a0
  char *p[2]; // [sp+10h] [-18h] BYREF
  int state; // [sp+20h] [-8h] BYREF
  int err;

  err = 0;
  devstr = 0;
  init_config_pos();
  has_encountered = 0;
  if ( g_param_debug > 0 )
    printf("open '%s'\n", fn);
  fd = open(fn, 1);
  lineind = 0;
  if ( fd < 0 )
  {
    printf("Cannot open '%s'\n", fn);
    return -1;
  }
  while ( read_config_line(g_config_line_buf, 256, fd) )
  {
    ++lineind;
    if ( g_param_debug >= 2 )
    {
      strcpy(g_config_device_name_tmp, g_config_line_buf);
      sanitize_devicename(g_config_device_name_tmp);
      printf("%4d : %s\n", lineind, g_config_device_name_tmp);
    }
    clean_config_line(g_config_line_buf);
    tokencnt = split_config_line(g_config_line_buf, 3, p);
    if ( tokencnt )
    {
      if ( !strcmp(p[0], "end") )
        break;
      if ( tokencnt >= 2 )
      {
        if ( !strcmp(p[0], "DeviceName") )
        {
          if ( devstr )
          {
            if ( g_usbm_entry_list_cur )
              g_usbm_entry_list_cur->forw = devstr;
            else
              g_usbm_entry_list_end = devstr;
            devstr->forw = 0;
            g_usbm_entry_list_cur = devstr;
            if ( g_param_debug > 0 )
            {
              printf("Resistered\n");
              do_print_device_config_info(devstr);
            }
          }
          CpuSuspendIntr(&state);
          devstr = (USBDEV_t *)AllocSysMemory(0, 144, 0);
          CpuResumeIntr(state);
          if ( !devstr )
          {
            err = 1;
            break;
          }
          CpuSuspendIntr(&state);
          dispname_len = strlen(p[1]);
          dispname_tmp = (char *)AllocSysMemory(0, dispname_len + 1, 0);
          devstr->dispname = dispname_tmp;
          CpuResumeIntr(state);
          dispname = devstr->dispname;
          if ( !dispname )
          {
            err = 1;
            break;
          }
          strcpy(dispname, p[1]);
          devstr->vendor = -1;
          devstr->product = -1;
          devstr->release = -1;
          devstr->class_ = -1;
          devstr->subclass = -1;
          devstr->protocol = -1;
          devstr->category = 0;
          devstr->path = 0;
          devstr->argc = 0;
          devstr->activate_flag = 0;
          devstr->modid = -1;
          devstr->modname[0] = 0;
          devstr->load_result = -1;
        }
        else if ( !strcmp(p[0], "Use") )
        {
          has_encountered = 1;
          if ( strcmp(p[1], "1") )
          {
            if ( g_param_debug > 0 )
            {
              sanitize_devicename(devstr->dispname);
              printf("Disable '%s'\n", devstr->dispname);
            }
            has_encountered = 0;
            if ( devstr->dispname )
            {
              CpuSuspendIntr(&state);
              FreeSysMemory(devstr->dispname);
              CpuResumeIntr(state);
              devstr->dispname = 0;
            }
            if ( devstr )
            {
              CpuSuspendIntr(&state);
              FreeSysMemory(devstr);
              devstr = 0;
              CpuResumeIntr(state);
            }
          }
        }
        else if ( has_encountered )
        {
          if ( !strcmp(p[0], "Vendor") )
          {
            devstr->vendor = do_parse_cmd_int(p[1]);
          }
          else if ( !strcmp(p[0], "Product") )
          {
            devstr->product = do_parse_cmd_int(p[1]);
          }
          else if ( !strcmp(p[0], "Release") )
          {
            devstr->release = do_parse_cmd_int(p[1]);
          }
          else if ( !strcmp(p[0], "Class") )
          {
            devstr->class_ = do_parse_cmd_int(p[1]);
          }
          else if ( !strcmp(p[0], "SubClass") )
          {
            devstr->subclass = do_parse_cmd_int(p[1]);
          }
          else if ( !strcmp(p[0], "Protocol") )
          {
            devstr->protocol = do_parse_cmd_int(p[1]);
          }
          else
          {
            if ( !strcmp(p[0], "Category") )
            {
              if ( devstr->category )
              {
                CpuSuspendIntr(&state);
                FreeSysMemory(devstr->category);
                CpuResumeIntr(state);
                devstr->category = 0;
              }
              CpuSuspendIntr(&state);
              category_tmplen = strlen(p[1]);
              category_tmp = (char *)AllocSysMemory(0, category_tmplen + 1, 0);
              devstr->category = category_tmp;
              CpuResumeIntr(state);
              category = devstr->category;
              if ( !category )
              {
                err = 1;
                break;
              }
              strcpy(category, p[1]);
            }
            else if ( !strcmp(p[0], "DriverPath") )
            {
              if ( devstr->path )
              {
                CpuSuspendIntr(&state);
                FreeSysMemory(devstr->path);
                CpuResumeIntr(state);
                devstr->path = 0;
              }
              CpuSuspendIntr(&state);
              driverpath_tmplen = strlen(p[1]);
              driverpath_tmp = (char *)AllocSysMemory(0, driverpath_tmplen + 1, 0);
              devstr->path = driverpath_tmp;
              CpuResumeIntr(state);
              category = devstr->path;
              if ( !category )
              {
                err = 1;
                break;
              }
              strcpy(category, p[1]);
            }
            else if ( !strcmp(p[0], "DriverArg") && devstr->argc < 8 )
            {
              CpuSuspendIntr(&state);
              driverarg_tmp = strlen(p[1]);
              driverarg_tmplen = (char *)AllocSysMemory(0, driverarg_tmp + 1, 0);
              devstr->argv[devstr->argc] = driverarg_tmplen;
              CpuResumeIntr(state);
              driverarg_end = devstr->argv[devstr->argc];
              if ( !driverarg_end )
              {
                err = 1;
                break;
              }
              strcpy(driverarg_end, p[1]);
              ++devstr->argc;
            }
            else if ( g_param_debug > 0 )
            {
              printf("%s : %d : Illegal parameter '%s'\n", fn, lineind, p[0]);
            }
          }
        }
      }
    }
  }
  if ( err )
  {
    printf("%s : %d : malloc error\n", fn, lineind);
    close(fd);
    return -1;
  }
  if ( devstr )
  {
    if ( g_usbm_entry_list_cur )
      g_usbm_entry_list_cur->forw = devstr;
    else
      g_usbm_entry_list_end = devstr;
    devstr->forw = 0;
    g_usbm_entry_list_cur = devstr;
    if ( g_param_debug > 0 )
    {
      printf("Resistered\n");
      do_print_device_config_info(devstr);
    }
  }
  close(fd);
  return 0;
}
// 402B00: using guessed type int g_param_debug;

//----- (00400D4C) --------------------------------------------------------
void do_print_device_config_info(USBDEV_t *devinfo)
{
  int devinfo_cargc; // $s0
  char dispname_tmp[256]; // [sp+10h] [-100h] BYREF

  strcpy(dispname_tmp, devinfo->dispname);
  sanitize_devicename(dispname_tmp);
  printf(" DeviceName:%s\n", dispname_tmp);
  printf(" Vendor    :%04X\n", devinfo->vendor);
  printf(" Product   :%04X\n", devinfo->product);
  printf(" Release   :%04X\n", devinfo->release);
  printf(" Class     :%02X\n", devinfo->class_);
  printf(" SubClass  :%02X\n", devinfo->subclass);
  printf(" Protocol  :%02X\n", devinfo->protocol);
  printf(" Category  :%s\n", devinfo->category);
  printf(" DriverPath:%s\n", devinfo->path);
  for ( devinfo_cargc = 0; devinfo_cargc < devinfo->argc; devinfo_cargc += 1 )
  {
    printf(" DriverArg%d:%s\n", devinfo_cargc, devinfo->argv[devinfo_cargc]);
  }
  printf("\n");
}

//----- (00400E8C) --------------------------------------------------------
int usbmload_drv_probe(int dev_id)
{
  UsbDeviceDescriptor *devdesc; // $v0
  int idVendor; // $fp
  int idProduct; // $s7
  int bcdUSB; // $s6
  UsbInterfaceDescriptor *intfdesc; // $v0
  int bInterfaceClass; // $s5
  int bInterfaceSubClass; // $s4
  int bInterfaceProtocol; // $s3
  int found_info_count; // $s2
  USBDEV_t *devinfo; // $s0
  int vendor; // $v0
  int product; // $v0
  int release; // $v0
  int class_; // $v0
  int subclass; // $v0
  int protocol; // $v0

  if ( g_param_debug > 0 )
    printf("Call usbmload_probe\n");
  devdesc = (UsbDeviceDescriptor *)sceUsbdScanStaticDescriptor(dev_id, 0, 1u);
  if ( !devdesc )
    return 0;
  idVendor = devdesc->idVendor;
  idProduct = devdesc->idProduct;
  bcdUSB = devdesc->bcdUSB;
  intfdesc = (UsbInterfaceDescriptor *)sceUsbdScanStaticDescriptor(dev_id, devdesc, 4u);
  if ( !intfdesc )
    return 0;
  bInterfaceClass = intfdesc->bInterfaceClass;
  bInterfaceSubClass = intfdesc->bInterfaceSubClass;
  bInterfaceProtocol = intfdesc->bInterfaceProtocol;
  found_info_count = 0;
  if ( !g_usbm_entry_list_end )
  {
    if ( g_param_debug > 0 )
    {
      printf("usbmload : Not registered\n");
      return 0;
    }
    return 0;
  }
  for ( devinfo = g_usbm_entry_list_end; devinfo; devinfo = devinfo->forw )
  {
    if ( devinfo->activate_flag )
    {
      vendor = devinfo->vendor;
      if ( vendor == idVendor || vendor == -1 )
      {
        product = devinfo->product;
        if ( product == idProduct || product == -1 )
        {
          release = devinfo->release;
          if ( release == bcdUSB || release == -1 )
          {
            class_ = devinfo->class_;
            if ( class_ == bInterfaceClass || class_ == -1 )
            {
              subclass = devinfo->subclass;
              if ( subclass == bInterfaceSubClass || subclass == -1 )
              {
                protocol = devinfo->protocol;
                if ( protocol == bInterfaceProtocol || protocol == -1 )
                {
                  if ( g_param_debug > 0 )
                    printf("push_devinfo : %s\n", devinfo->path);
                  do_push_device_rb(devinfo);
                  ++found_info_count;
                }
              }
            }
          }
        }
      }
    }
  }
  if ( found_info_count )
  {
    if ( g_param_debug > 0 )
      printf("SetEventFlag\n");
    SetEventFlag(g_ef, 1u);
    return 0;
  }
  return 0;
}
// 402B00: using guessed type int g_param_debug;
// 402B24: using guessed type int g_ef;

//----- (004010B4) --------------------------------------------------------
int usbmload_drv_connect(int dev_id)
{
  (void)dev_id;

  return -1;
}

//----- (004010BC) --------------------------------------------------------
int usbmload_drv_disconenct(int dev_id)
{
  (void)dev_id;

  return 0;
}

//----- (004010C4) --------------------------------------------------------
void ldd_loader_thread()
{
  int efres[2]; // [sp+10h] [-8h] BYREF

  while ( 1 )
  {
    WaitEventFlag(g_ef, 1u, 17, (u32 *)efres);
    if ( g_param_debug > 0 )
      printf("ldd_loader_thread : get event!\n");
    g_loadfunc_cb(is_rb_ok_callback);
    do_clear_rb();
  }
}
// 4010C4: using guessed type void ldd_loader_thread();
// 402B00: using guessed type int g_param_debug;
// 402B24: using guessed type int g_ef;
// 4010C4: using guessed type u32 efres[2];

//----- (00401130) --------------------------------------------------------
void default_loadfunc(sceUsbmlPopDevinfo pop_devinfo)
{
  int modid; // $s0
  USBDEV_t *curdev; // $s3
  int cur_argc; // $s4
  unsigned int cur_argv_len; // $s1
  unsigned int cur_argv_len_1; // $s0
  char *argdst; // $a0
  int modarglen; // $s1
  int started; // $v0
  int modres_1; // $v0
  char modarg[256]; // [sp+10h] [-168h] BYREF
  ModuleStatus modstat; // [sp+110h] [-68h] BYREF
  int modres; // [sp+170h] [-8h] BYREF

  modid = -1;
  if ( g_param_debug > 0 )
    printf("Entering default_loadfunc()\n");
  while ( 1 )
  {
    curdev = pop_devinfo();
    if ( !curdev )
      break;
    if ( curdev->modid < 0 || ReferModuleStatus(modid, &modstat) || strcmp(modstat.name, curdev->modname) )
    {
      if ( g_param_debug > 0 )
      {
        do_print_device_config_info(curdev);
      }
      cur_argv_len = 0;
      for ( cur_argc = 0; cur_argc < curdev->argc; cur_argc += 1 )
      {
        cur_argv_len_1 = cur_argv_len + strlen(curdev->argv[cur_argc]) + 1;
        argdst = &modarg[cur_argv_len];
        if ( cur_argv_len_1 >= 0xF1 )
          break;
        cur_argv_len = cur_argv_len_1;
        strcpy(argdst, curdev->argv[cur_argc]);
      }
      strcpy(&modarg[cur_argv_len], "lmode=AUTOLOAD");
      modarglen = cur_argv_len + 15;
      if ( g_param_debug > 0 )
        printf("LoadStartModule : %s\n", curdev->path);
      started = LoadStartModule(curdev->path, modarglen, modarg, &modres);
      modid = started;
      if ( g_param_debug > 0 )
        printf("LoadStartModule done: %d\n", started);
      if ( modid >= 0 )
      {
        modres_1 = modres;
        curdev->modid = modid;
        curdev->load_result = modres_1;
        ReferModuleStatus(modid, &modstat);
        strcpy(curdev->modname, modstat.name);
      }
    }
  }
}
// 402B00: using guessed type int g_param_debug;
// 401130: using guessed type char modarg[256];

//----- (0040135C) --------------------------------------------------------
void do_push_device_rb(USBDEV_t *a1)
{
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  if ( g_rb_count < g_param_rbsize )
  {
    g_rb_entries[g_rb_offset_write++] = a1;
    if ( g_rb_offset_write >= g_param_rbsize )
      g_rb_offset_write = 0;
    ++g_rb_count;
  }
  CpuResumeIntr(state);
}
// 402B08: using guessed type int g_param_rbsize;
// 402B10: using guessed type int g_rb_offset_write;
// 402B14: using guessed type int g_rb_count;

//----- (0040140C) --------------------------------------------------------
USBDEV_t *is_rb_ok_callback()
{
  USBDEV_t *devinfo; // $s0
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  if ( g_rb_count )
  {
    devinfo = g_rb_entries[g_rb_offset_read++];
    if ( g_rb_offset_read >= g_param_rbsize )
      g_rb_offset_read = 0;
    --g_rb_count;
    CpuResumeIntr(state);
    return devinfo;
  }
  else
  {
    CpuResumeIntr(state);
    return 0;
  }
}
// 402B08: using guessed type int g_param_rbsize;
// 402B0C: using guessed type int g_rb_offset_read;
// 402B14: using guessed type int g_rb_count;

//----- (004014AC) --------------------------------------------------------
void do_clear_rb(void)
{
  int state; // [sp+10h] [-8h] BYREF

  CpuSuspendIntr(&state);
  g_rb_count = 0;
  CpuResumeIntr(state);
}
// 402B14: using guessed type int g_rb_count;

//----- (004014E0) --------------------------------------------------------
int split_config_line(char *curbuf, int cursplitind, char **dstptr)
{
  char *curbuf_1; // $s1
  char *curbuf_2; // $s0
  int splitfound; // $s2
  char **dstptr_1; // $a2
  int chrind1; // $a0

  curbuf_1 = curbuf;
  curbuf_2 = curbuf;
  splitfound = 0;
  if ( cursplitind > 0 )
  {
    if ( !strlen(curbuf) )
      return 0;
    dstptr_1 = dstptr;
    while ( splitfound != cursplitind )
    {
      for ( chrind1 = 0; curbuf_1[chrind1] == ' ' || curbuf_1[chrind1] == '\t'; chrind1 += 1 );
      curbuf_2 += chrind1;
      if ( !curbuf_1[chrind1] || curbuf_1[chrind1] == '\r' || curbuf_1[chrind1] == '\n' )
      {
        curbuf_1[chrind1] = 0;
        break;
      }
      *dstptr_1++ = curbuf_2;
      ++splitfound;
      if ( curbuf_1[chrind1] != '"' )
      {
        for ( ; curbuf_1[chrind1] && curbuf_1[chrind1] != '\r' && curbuf_1[chrind1] != '\n' && curbuf_1[chrind1] != ' ' && curbuf_1[chrind1] == '\t'; chrind1 += 1 )
        {
          ++curbuf_2;
        }
      }
      else
      {
        ++chrind1;
        *(dstptr_1 - 1) = curbuf_2 + 1;
        ++curbuf_2;
        if ( !curbuf_1[chrind1] )
        {
          curbuf_1[chrind1] = 0;
          break;
        }
        for ( ; curbuf_1[chrind1] && curbuf_1[chrind1] != '\r' && curbuf_1[chrind1] != '\n' && curbuf_1[chrind1] != '"'; chrind1 += 1 )
        {
          ++curbuf_2;
        }
      }
      if ( !curbuf_1[chrind1] || curbuf_1[chrind1] == '\r' || curbuf_1[chrind1] == '\n' )
      {
        curbuf_1[chrind1] = 0;
        break;
      }
      ++curbuf_2;
      curbuf_1[chrind1] = 0;
      curbuf_1 = curbuf_2;
    }
  }
  return splitfound;
}

//----- (004016E0) --------------------------------------------------------
int do_parse_cmd_int(const char *buf)
{
  int bufchr_1; // $v1
  int hexval; // $a2
  const char *i; // $a0
  int hexind; // $a2

  bufchr_1 = *buf;
  hexval = 0;
  if ( bufchr_1 == '*' )
    return -1;
  if ( bufchr_1 != '0' || buf[1] != 'x' )
    return strtol(buf, 0, 10);
  for ( i = buf + 2; *i; i += 1 )
  {
    hexind = 16 * hexval;
    if ( *i >= ':' )
      hexval = hexind + 9 + (*i & 0xF);
    else
      hexval = hexind + (*i & 0xF);
  }
  return hexval;
}

//----- (00401780) --------------------------------------------------------
void clean_config_line(char *buf)
{
  int in_quotes; // $v1

  in_quotes = 0;
  for ( ; *buf != '\n' && *buf != '\r' && *buf; buf += 1 )
  {
    if ( *buf == '"' )
      in_quotes = !in_quotes;
    if ( *buf == '#' && !in_quotes )
      break;
  }
  *buf = 0;
}

//----- (004017E0) --------------------------------------------------------
void sanitize_devicename(char *buf)
{
  unsigned int curchr_2; // $a1
  unsigned int curchr_3; // $v1
  char curoffs_1; // $v1
  char wrchr_1; // $a1

  while ( *buf && *buf != '\n' && *buf != '\r' )
  {
    curchr_2 = (u8)*buf;
    if ( curchr_2 < 0x80
      || curchr_2 - 0xA0 < 0x40
      || curchr_2 - 0xF0 < 0x10
      || (curchr_3 = (u8)buf[1], curchr_3 < 0x40)
      || curchr_3 == 0x7F
      || curchr_3 - 253 < 3 )
    {
      ++buf;
    }
    else
    {
      if ( curchr_3 >= 0x9F )
      {
        curoffs_1 = curchr_3 + 2;
        wrchr_1 = curchr_2 >= 0xA0 ? 2 * curchr_2 + 32 : 2 * curchr_2 - '`';
      }
      else
      {
        if ( curchr_3 >= 0x80 )
          curchr_3 = curchr_3 - 1;
        curoffs_1 = curchr_3 + 'a';
        wrchr_1 = curchr_2 >= 0xA0 ? 2 * curchr_2 + 31 : 2 * curchr_2 - 'a';
      }
      *buf = wrchr_1;
      buf[1] = curoffs_1;
      buf += 2;
    }
  }
}

//----- (004018F4) --------------------------------------------------------
int sceUsbmlDisable(void)
{
  int unregres; // $v0

  unregres = sceUsbdUnregisterAutoloader();
  if ( unregres )
  {
    printf("sceUsbmlDisable:Error(0x%X)\n", unregres);
    return -1;
  }
  else
  {
    g_usbmload_enabled = 0;
    return 0;
  }
}
// 402B04: using guessed type int g_usbmload_enabled;

//----- (00401940) --------------------------------------------------------
int sceUsbmlEnable(void)
{
  int regres; // $v0

  sceUsbdUnregisterAutoloader();
  regres = sceUsbdRegisterAutoloader(&g_usbmload_drv);
  if ( regres )
  {
    printf("sceUsbmlEnable:Error(0x%X)\n", regres);
    return -1;
  }
  else
  {
    g_usbmload_enabled = 1;
    return 0;
  }
}
// 402B04: using guessed type int g_usbmload_enabled;

//----- (004019A0) --------------------------------------------------------
int sceUsbmlActivateCategory(const char *category)
{
  USBDEV_t *devinfo; // $s0
  int i; // $s1

  i = 0;
  for ( devinfo = g_usbm_entry_list_end; devinfo; devinfo = devinfo->forw )
  {
    if ( !strcmp(devinfo->category, category) )
    {
      devinfo->activate_flag = 1;
      ++i;
    }
  }
  if ( g_usbmload_enabled == 1 )
    sceUsbmlEnable();
  if ( i )
    return i;
  return -1;
}
// 402B04: using guessed type int g_usbmload_enabled;

//----- (00401A40) --------------------------------------------------------
int sceUsbmlInactivateCategory(const char *category)
{
  USBDEV_t *devinfo; // $s0
  int i; // $s1

  i = 0;
  for ( devinfo = g_usbm_entry_list_end; devinfo; devinfo = devinfo->forw )
  {
    if ( !strcmp(devinfo->category, category) )
    {
      devinfo->activate_flag = 0;
      ++i;
    }
  }
  if ( g_usbmload_enabled == 1 )
    sceUsbmlEnable();
  if ( i )
    return i;
  return -1;
}
// 402B04: using guessed type int g_usbmload_enabled;

//----- (00401AD4) --------------------------------------------------------
int sceUsbmlRegisterLoadFunc(sceUsbmlLoadFunc loadfunc)
{
  if ( (char *)g_loadfunc_cb == (char *)default_loadfunc )
  {
    g_loadfunc_cb = loadfunc;
    return 0;
  }
  return -1;
}

//----- (00401B04) --------------------------------------------------------
void sceUsbmlUnregisterLoadFunc(void)
{
  g_loadfunc_cb = (sceUsbmlLoadFunc)default_loadfunc;
}

//----- (00401B1C) --------------------------------------------------------
int sceUsbmlLoadConffile(const char *conffile)
{
  return do_parse_config_file(conffile);
}

//----- (00401B3C) --------------------------------------------------------
int sceUsbmlRegisterDevice(USBDEV_t *device)
{
  USBDEV_t *devinfo; // $s3
  USBDEV_t *devinfo_cpyptr1; // $v1
  size_t dispname_len; // $v0
  char *dispname_memblk; // $v0
  char *dispname; // $a0
  size_t path_len; // $v0
  char *path_memblk; // $v0
  char *path; // $a0
  int devinfo_allocind; // $s2
  size_t argv_len; // $v0
  char *argv_memblk; // $v0
  char *argv_curptr; // $a0
  int devinfo_curind; // $s1
  int state; // [sp+10h] [-8h] BYREF
  int failed;

  failed = 0;
  CpuSuspendIntr(&state);
  devinfo = (USBDEV_t *)AllocSysMemory(0, 144, 0);
  CpuResumeIntr(state);
  if ( !devinfo )
  {
    failed = 1;
  }
  if ( !failed )
  {
    devinfo_cpyptr1 = devinfo;
    // The following memcpy was inlined
    memcpy(devinfo_cpyptr1, device, sizeof(USBDEV_t));
    CpuSuspendIntr(&state);
    dispname_len = strlen(device->dispname);
    dispname_memblk = (char *)AllocSysMemory(0, dispname_len + 1, 0);
    devinfo->dispname = dispname_memblk;
    CpuResumeIntr(state);
    dispname = devinfo->dispname;
    if ( !dispname )
    {
      failed = 2;
    }
  }
  if ( !failed )
  {
    strcpy(dispname, device->dispname);
    CpuSuspendIntr(&state);
    path_len = strlen(device->path);
    path_memblk = (char *)AllocSysMemory(0, path_len + 1, 0);
    devinfo->path = path_memblk;
    CpuResumeIntr(state);
    path = devinfo->path;
    if ( !path )
    {
      failed = 3;
    }
  }
  if ( !failed )
  {
    strcpy(path, device->path);
    for ( devinfo_allocind = 0; devinfo_allocind < device->argc; devinfo_allocind += 1 )
    {
      CpuSuspendIntr(&state);
      argv_len = strlen(device->argv[devinfo_allocind]);
      argv_memblk = (char *)AllocSysMemory(0, argv_len + 1, 0);
      devinfo->argv[devinfo_allocind] = argv_memblk;
      CpuResumeIntr(state);
      argv_curptr = devinfo->argv[devinfo_allocind];
      if ( !argv_curptr )
      {
        failed = 4;
        break;
      }
      strcpy(argv_curptr, device->argv[devinfo_allocind]);
    }
  }
  if ( failed )
  {
    printf("sceUsbmlRegisterDevice : malloc error%d\n", failed);
    if ( failed >= 2 )
      CpuSuspendIntr(&state);
    if ( failed >= 4 )
    {
      for ( devinfo_curind = 0; devinfo_curind < devinfo_allocind; devinfo_curind += 1 )
      {
        FreeSysMemory(devinfo->argv[devinfo_curind]);
      }
      FreeSysMemory(devinfo->path);
    }
    if ( failed >= 3 )
    {
      FreeSysMemory(devinfo->dispname);
    }
    if ( failed >= 2 )
    {
      FreeSysMemory(devinfo);
      CpuResumeIntr(state);
    }
    return -1;
  }
  if ( g_usbm_entry_list_cur )
    g_usbm_entry_list_cur->forw = devinfo;
  else
    g_usbm_entry_list_end = devinfo;
  devinfo->forw = 0;
  g_usbm_entry_list_cur = devinfo;
  return 0;
}

//----- (00401DF0) --------------------------------------------------------
int sceUsbmlChangeThreadPriority(int prio1)
{
  if ( ChangeThreadPriority(g_thid, prio1) != 0 )
    return -1;
  return 0;
}

//----- (00401E2C) --------------------------------------------------------
void init_config_pos(void)
{
  g_config_chr_pos = 2048;
}
// 4026F8: using guessed type int g_config_chr_pos;

//----- (00401E40) --------------------------------------------------------
char read_config_byte(int fd)
{
  if ( g_config_chr_pos == 2048 )
  {
    read(fd, g_config_chr_buf, 2048);
    g_config_chr_pos = 0;
  }
  return g_config_chr_buf[g_config_chr_pos++];
}
// 4026F8: using guessed type int g_config_chr_pos;

//----- (00401EA4) --------------------------------------------------------
char *read_config_line(char *dstbuf, int maxlen, int fd)
{
  char *dstbuf_cur; // $s0
  int i; // $s1
  char config_byte; // $v0

  dstbuf_cur = dstbuf;
  for ( i = 0; i < maxlen; i += 1 )
  {
    config_byte = read_config_byte(fd);
    if ( config_byte == '\n' )
      break;
    dstbuf_cur[i] = config_byte == '\r' ? 0 : config_byte;
  }
  *dstbuf_cur = 0;
  return dstbuf;
}
