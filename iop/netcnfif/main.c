
#include "irx_imports.h"

IRX_ID("Netcnf_Interface", 2, 30);

// TODO EE alignment 64
typedef struct __attribute__((aligned(16))) sceNetcnfifList
{
  int type;
  int stat;
  char sys_name[256];
  char usr_name[256];
  int padding[14];
} sceNetcnfifList_t;

// TODO EE alignment 64
typedef struct __attribute__((aligned(16))) sceNetcnfifData
{
  char attach_ifc[256];
  char attach_dev[256];
  char dhcp_host_name[256];
  char address[256];
  char netmask[256];
  char gateway[256];
  char dns1_address[256];
  char dns2_address[256];
  char phone_numbers1[256];
  char phone_numbers2[256];
  char phone_numbers3[256];
  char auth_name[256];
  char auth_key[256];
  char peer_name[256];
  char vendor[256];
  char product[256];
  char chat_additional[256];
  char outside_number[256];
  char outside_delay[256];
  int ifc_type;
  int mtu;
  int ifc_idle_timeout;
  int dev_type;
  int phy_config;
  int dialing_type;
  int dev_idle_timeout;
  int p0;
  u8 dhcp;
  u8 dns1_nego;
  u8 dns2_nego;
  u8 f_auth;
  u8 auth;
  u8 pppoe;
  u8 prc_nego;
  u8 acc_nego;
  u8 accm_nego;
  u8 p1;
  u8 p2;
  u8 p3;
  int p4[5];
} sceNetcnfifData_t;

typedef struct sceNetcnfifArg
{
  int data;
  int f_no_decode;
  int type;
  int addr;
  char fname[256];
  char usr_name[256];
  char new_usr_name[256];
} sceNetcnfifArg_t;

//-------------------------------------------------------------------------
// Function declarations

int _start(int argc, char *argv[]);
static void sceNetcnfifInterfaceStart(void *userdata);
static void sceNetcnfifInterfaceStop(void);
static void sceNetcnfifDataInit(sceNetcnfifData_t *data);
static void sceNetcnfifEnvInit(sceNetCnfEnv_t *env, void *mem_area, int size, int f_no_decode);
static int sceNetcnfifReadEnv(sceNetcnfifData_t *data, sceNetCnfEnv_t *e, int type);
static int sceNetcnfifWriteEnv(sceNetCnfEnv_t *e, sceNetcnfifData_t *data, int type);
static int sceNetcnfifSendEE(unsigned int data, unsigned int addr, unsigned int size);
static int sceNetcnfifDmaCheck(int id);
static void sce_callback_initialize(void);
static int sce_callback_open(const char *device, const char *pathname, int flags, int mode, int *filesize);
static int sce_callback_read(int fd, const char *device, const char *pathname, void *buf, int offset, int size);
static int sce_callback_close(int fd);
static int my_create_heap(void);
static void *my_alloc(int size);
static void my_free(void *ptr);
static void my_delete_heap(void);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_netcnfif;
static void *mem_area = NULL; // idb
static int mem_area_size = 0; // idb
static void *g_heap = NULL; // idb
static int g_tid; // idb
static sceNetCnfEnv_t env; // weak
static sceNetcnfifData_t data; // idb
static char dp[0x100]; // idb
static int rpc_buf[1024]; // weak
static SifRpcServerData_t sd; // idb
static SifRpcDataQueue_t qd; // weak
static int ns_count; // idb
static route_t gateway; // weak
static nameserver_t dns1; // weak
static nameserver_t dns2; // weak
static int oldstat; // idb
static SifRpcClientData_t gcd; // idb
static int gbuf[1024]; // weak


//----- (00400000) --------------------------------------------------------
static void usage(void)
{
  printf("Usage: netcnfif <option>\n");
  printf("    <option>:\n");
  printf("    thpri=<digit>     - set thread priority\n");
  printf("    thstack=<digit>KB - set thread stack size(Kbyte)\n");
  printf("    thstack=<digit>   - set thread stack size(byte)\n");
  printf("    -help             - print usage\n");
}

//----- (00400064) --------------------------------------------------------
static int module_start(int argc, char *argv[])
{
  int thpri; // $s5
  int thstack; // $s4
  int i; // $s3
  int bp; // $s0
  int retres1; // $v0
  int retres2; // $v0
  iop_thread_t th_param; // [sp+10h] [-18h] BYREF

  thpri = 123;
  thstack = 4096;
  for ( i = 1; i < argc; i += 1 )
  {
    int xflg;

    xflg = 1;
    if ( !strncmp("thpri=", argv[i], 6) )
    {
      bp = 6;
      if ( !isdigit(argv[i][bp]) )
      {
        usage();
        return 1;
      }
      thpri = strtol(&argv[i][bp], 0, 10);
      if ( (unsigned int)(thpri - 9) >= 0x73 )
      {
        usage();
        return 1;
      }
      for ( ; argv[i][bp] && isdigit(argv[i][bp]); bp += 1 );
      if ( !argv[i][bp] )
      {
        xflg = 0;
      }
    }
    else if ( !strncmp("thstack=", argv[i], 8) )
    {
      bp = 8;
      if ( !isdigit(argv[i][bp]) )
      {
        usage();
        return 1;
      }
      thstack = strtol(&argv[i][bp], 0, 10);
      for ( ; argv[i][bp] && isdigit(argv[i][bp]); bp += 1 );
      if ( !strcmp(&argv[i][bp], "KB") )
      {
        thstack <<= 10;
        xflg = 0;
      }
    }
    else
    {
      usage();
      return 1;
    }
    if ( xflg && argv[i][bp] )
    {
      usage();
      return 1;
    }
  }
  retres1 = RegisterLibraryEntries(&_exp_netcnfif);
  if ( retres1 )
  {
    printf("netcnfif: RegisterLibraryEntries(%d)\n", retres1);
    return 1;
  }
  retres2 = my_create_heap();
  if ( retres2 >= 0 )
  {
    th_param.attr = 0x2000000;
    th_param.thread = sceNetcnfifInterfaceStart;
    th_param.priority = thpri;
    th_param.stacksize = thstack;
    th_param.option = 0;
    g_tid = CreateThread(&th_param);
    if ( g_tid >= 0 )
    {
      int retres3; // $v0

      retres3 = StartThread(g_tid, 0);
      if ( retres3 >= 0 )
        return 2;
      printf("netcnfif: s_thread(%d)\n", retres3);
      TerminateThread(g_tid);
      DeleteThread(g_tid);
    }
    else
    {
      printf("netcnfif: c_thread(%d)\n", g_tid);
    }
    my_delete_heap();
  }
  else
  {
    printf("netcnfif: c_heap(%d)\n", retres2);
  }
  ReleaseLibraryEntries(&_exp_netcnfif);
  return 1;
}

//----- (00400334) --------------------------------------------------------
static int module_stop(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  sceNetcnfifInterfaceStop();
  TerminateThread(g_tid);
  DeleteThread(g_tid);
  my_delete_heap();
  ReleaseLibraryEntries(&_exp_netcnfif);
  return 1;
}

//----- (0040038C) --------------------------------------------------------
int _start(int argc, char *argv[])
{
  return ( argc >= 0 ) ? module_start(argc, argv) : module_stop(-argc, argv);
}

//----- (004003F0) --------------------------------------------------------
static void *sceNetcnfifInterfaceServer(int fno, sceNetcnfifArg_t *buf, int size)
{
  int retres1; // $s1
  sceNetCnfList_t *list_iop; // $s3
  sceNetcnfifList_t *list_ee; // $s4
  int i; // $a0
  int dmatid2; // $s0
  sceNetCnfCallback_t callback; // [sp+18h] [-10h] BYREF

  (void)size;
  retres1 = 0;
  switch ( fno )
  {
    case 0:
      retres1 = sceNetCnfGetCount(buf->fname, buf->type);
      break;
    case 1:
      retres1 = sceNetCnfGetCount(buf->fname, buf->type);
      if ( retres1 < 0 )
        break;
      list_iop = (sceNetCnfList_t *)my_alloc(sizeof(sceNetCnfList_t) * retres1);
      retres1 = -2;
      if ( !list_iop )
        break;
      list_ee = (sceNetcnfifList_t *)my_alloc(sizeof(sceNetcnfifList_t) * buf->data);
      if ( list_ee )
      {
        retres1 = sceNetCnfGetList(buf->fname, buf->type, list_iop);
        if ( retres1 >= 0 )
        {
          int dmatid1; // $s0

          for ( i = 0; i < buf->data && i < retres1; i += 1 )
          {
            // The following memcpy was inlined
            memcpy(&list_ee[i], &list_iop[i], sizeof(sceNetCnfList_t));
          }
          dmatid1 = sceNetcnfifSendEE((unsigned int)list_ee, buf->addr, sizeof(sceNetcnfifList_t) * buf->data);
          while ( sceNetcnfifDmaCheck(dmatid1) );
        }
        my_free(list_iop);
        my_free(list_ee);
      }
      else
      {
        my_free(list_iop);
        retres1 = -2;
      }
      break;
    case 2:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetCnfLoadEntry(buf->fname, buf->type, buf->usr_name, &env);
      if ( retres1 < 0 )
        break;
      sceNetcnfifDataInit(&data);
      retres1 = sceNetcnfifReadEnv(&data, &env, buf->type);
      if ( retres1 < 0 )
        break;
      dmatid2 = sceNetcnfifSendEE((unsigned int)&data, buf->addr, sizeof(sceNetcnfifData_t));
      while ( sceNetcnfifDmaCheck(dmatid2) );
      break;
    case 3:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetcnfifWriteEnv(&env, &data, buf->type);
      if ( retres1 >= 0 )
        retres1 = sceNetCnfAddEntry(buf->fname, buf->type, buf->usr_name, &env);
      break;
    case 4:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetCnfLoadEntry(buf->fname, buf->type, buf->usr_name, &env);
      if ( retres1 >= 0 )
      {
        env.mem_ptr = (void *)(((int)env.mem_ptr + 3) & 0xFFFFFFFC);
        env.mem_base = env.mem_ptr;
        retres1 = sceNetcnfifWriteEnv(&env, &data, buf->type);
        if ( retres1 >= 0 )
          retres1 = sceNetCnfEditEntry(buf->fname, buf->type, buf->usr_name, buf->new_usr_name, &env);
      }
      break;
    case 5:
      retres1 = sceNetCnfDeleteEntry(buf->fname, buf->type, buf->usr_name);
      break;
    case 6:
      retres1 = sceNetCnfSetLatestEntry(buf->fname, buf->type, buf->usr_name);
      break;
    case 7:
      retres1 = sceNetCnfDeleteAll(buf->fname);
      break;
    case 8:
      retres1 = sceNetCnfCheckCapacity(buf->fname);
      break;
    case 9:
      retres1 = sceNetCnfConvA2S(buf->fname, dp, sizeof(buf->fname));
      break;
    case 10:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetCnfCheckSpecialProvider(buf->fname, buf->type, buf->usr_name, &env);
      break;
    case 11:
      callback.open = sce_callback_open;
      callback.read = sce_callback_read;
      callback.close = sce_callback_close;
      callback.type = buf->type;
      sce_callback_initialize();
      sceNetCnfSetCallback(&callback);
      break;
    case 15:
      sceNetCnfSetCallback(0);
      break;
    case 100:
      buf->addr = (int)&data;
      break;
    case 101:
      if ( mem_area )
      {
        break;
      }
      mem_area_size = buf->data;
      mem_area = my_alloc(mem_area_size);
      if ( !mem_area )
        retres1 = -2;
      break;
    case 102:
      if ( mem_area )
        my_free(mem_area);
      mem_area_size = 0;
      mem_area = 0;
      break;
    case 103:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetcnfifWriteEnv(&env, &data, buf->type);
      if ( retres1 < 0 )
        break;
      if ( env.root && env.root->pair_head && env.root->pair_head->ifc )
      {
        int redial_count; // $a1

        redial_count = 0;
        for ( i = 0; i < (int)(sizeof(env.root->pair_head->ifc->phone_numbers)/sizeof(env.root->pair_head->ifc->phone_numbers[0])); i += 1 )
        {
          if ( i < 3 && i >= 0 && env.root->pair_head->ifc->phone_numbers[i] )
            redial_count += 1;
        }
        env.root->pair_head->ifc->redial_count = redial_count - 1;
        if ( env.root->pair_head->ifc->pppoe != 1 && env.root->pair_head->ifc->type != 2 )
          env.root->pair_head->ifc->type = env.root->pair_head->dev->type;
      }
      buf->addr = (int)&env;
      break;
    default:
      break;
  }
  buf->data = retres1;
  return buf;
}
// 402880: using guessed type sceNetCnfEnv_t env;

//----- (00400A10) --------------------------------------------------------
static void sceNetcnfifInterfaceStart(void *userdata)
{
  (void)userdata;

  sceSifInitRpc(0);
  sceSifSetRpcQueue(&qd, GetThreadId());
  sceSifRegisterRpc(&sd, 0x80001101, (SifRpcFunc_t)sceNetcnfifInterfaceServer, rpc_buf, 0, 0, &qd);
  sceSifRpcLoop(&qd);
}
// 404530: using guessed type int rpc_buf[1024];
// 405578: using guessed type SifRpcDataQueue_t qd;

//----- (00400A88) --------------------------------------------------------
static void sceNetcnfifInterfaceStop(void)
{
  if ( mem_area )
  {
    my_free(mem_area);
    mem_area_size = 0;
    mem_area = 0;
  }
  sceSifRemoveRpc(&sd, &qd);
  sceSifRemoveRpcQueue(&qd);
}
// 405578: using guessed type SifRpcDataQueue_t qd;

//----- (00400AF0) --------------------------------------------------------
static void sceNetcnfifDataInit(sceNetcnfifData_t *data)
{
  memset(data, 0, sizeof(sceNetcnfifData_t));
  data->ifc_type = -1;
  data->mtu = -1;
  data->ifc_idle_timeout = -1;
  data->dev_type = -1;
  data->phy_config = -1;
  data->dialing_type = -1;
  data->dev_idle_timeout = -1;
  data->dhcp = -1;
  data->dns1_nego = -1;
  *(u16 *)&data->dns2_nego = 255;
  data->auth = 4;
  data->pppoe = -1;
  data->prc_nego = -1;
  data->acc_nego = -1;
  data->accm_nego = -1;
}

//----- (00400B70) --------------------------------------------------------
static void sceNetcnfifEnvInit(sceNetCnfEnv_t *env, void *mem_area, int size, int f_no_decode)
{
  memset(env, 0, sizeof(sceNetCnfEnv_t));
  env->mem_ptr = mem_area;
  env->mem_base = mem_area;
  env->mem_last = (char *)mem_area + size;
  env->f_no_decode = f_no_decode;
}

//----- (00400BE0) --------------------------------------------------------
static int get_cmd(sceNetcnfifData_t *data, sceNetCnfCommand_t *p, int *ns_count)
{
  switch ( p->code )
  {
    case 1:
    {
      int retres; // $a1

      switch ( *ns_count )
      {
        case 0:
          retres = sceNetCnfAddress2String(data->dns1_address, sizeof(data->dns1_address), &((nameserver_t *)p)->address);
          break;
        case 1:
          retres = sceNetCnfAddress2String(data->dns2_address, sizeof(data->dns2_address), &((nameserver_t *)p)->address);
          break;
        default:
          return 0;
      }
      *ns_count += 1;
      return retres;
    }
    case 3:
      return sceNetCnfAddress2String(data->gateway, sizeof(data->gateway), &((route_t *)p)->re.gateway);
    default:
      break;
  }
  return 0;
}

//----- (00400C80) --------------------------------------------------------
static int get_attach(sceNetcnfifData_t *data, sceNetCnfInterface_t *p, int type)
{
  int cmd; // $s4
  struct sceNetCnfCommand *cmd_head; // $s0

  cmd = 0;
  switch ( type )
  {
    case 1:
    {
      int i; // $s0

      data->ifc_type = p->type;
      data->dhcp = p->dhcp;
      if ( p->dhcp_host_name )
        strcpy(data->dhcp_host_name, (const char *)p->dhcp_host_name);
      if ( p->address )
        strcpy(data->address, (const char *)p->address);
      if ( p->netmask )
        strcpy(data->netmask, (const char *)p->netmask);
      ns_count = 0;
      for ( cmd_head = p->cmd_head; cmd_head; cmd_head = cmd_head->forw )
      {
        cmd = get_cmd(data, cmd_head, &ns_count);
        if ( cmd < 0 )
          return cmd;
      }
      for ( i = 0; i < (int)(sizeof(p->phone_numbers)/sizeof(p->phone_numbers[0])); i += 1 )
      {
        if ( !p->phone_numbers[i] )
        {
          continue;
        }
        switch ( i )
        {
          case 0:
            strcpy(data->phone_numbers1, (const char *)p->phone_numbers[i]);
            break;
          case 1:
            strcpy(data->phone_numbers2, (const char *)p->phone_numbers[i]);
            break;
          case 2:
            strcpy(data->phone_numbers3, (const char *)p->phone_numbers[i]);
            break;
        }
      }
      if ( p->auth_name )
        strcpy(data->auth_name, (const char *)p->auth_name);
      if ( p->auth_key )
        strcpy(data->auth_key, (const char *)p->auth_key);
      if ( p->peer_name )
        strcpy(data->peer_name, (const char *)p->peer_name);
      data->dns1_nego = p->want.dns1_nego;
      data->dns2_nego = p->want.dns2_nego;
      data->f_auth = p->allow.f_auth;
      data->auth = p->allow.auth;
      data->pppoe = p->pppoe;
      data->prc_nego = p->want.prc_nego;
      data->acc_nego = p->want.acc_nego;
      data->accm_nego = p->want.accm_nego;
      data->mtu = p->mtu;
      data->ifc_idle_timeout = p->idle_timeout;
    }
    break;
    case 2:
    {
      data->dev_type = p->type;
      if ( p->vendor )
        strcpy(data->vendor, (const char *)p->vendor);
      if ( p->product )
        strcpy(data->product, (const char *)p->product);
      data->phy_config = p->phy_config;
      if ( !((char *)p->chat_additional)
        || (cmd = sceNetCnfConvS2A((char *)p->chat_additional, data->chat_additional, sizeof(p->chat_additional)), cmd >= 0) )
      {
        if ( p->outside_number )
          strcpy(data->outside_number, (const char *)p->outside_number);
        if ( p->outside_delay )
          strcpy(data->outside_delay, (const char *)p->outside_delay);
        data->dialing_type = p->dialing_type;
        data->dev_idle_timeout = p->idle_timeout;
      }
      break;
    }
    default:
      break;
  }
  return cmd;
}

//----- (00400F7C) --------------------------------------------------------
static int get_net(sceNetcnfifData_t *data, sceNetCnfRoot_t *p)
{
  struct sceNetCnfPair *pair; // $s0
  int i; // $s1

  i = 0;
  for ( pair = p->pair_head; pair; pair = pair->forw )
  {
    sceNetcnfifDataInit(data);
    strcpy(data->attach_ifc, (const char *)pair->attach_ifc);
    strcpy(data->attach_dev, (const char *)pair->attach_dev);
    if ( pair->ifc )
      i = get_attach(data, pair->ifc, 1);
    if ( pair->dev )
      i = get_attach(data, pair->dev, 2);
  }
  return i;
}

//----- (00401028) --------------------------------------------------------
static int sceNetcnfifReadEnv(sceNetcnfifData_t *data, sceNetCnfEnv_t *e, int type)
{
  if ( !type )
    return get_net(data, e->root);
  if ( type >= 0 && type < 3 )
    return get_attach(data, e->ifc, type);
  printf("[%s] unknown type (%d)\n", "sceNetcnfifReadEnv", type);
  return 0;
}

//----- (004010A0) --------------------------------------------------------
static u8 *dup_string(sceNetCnfEnv_t *e, u8 *str)
{
  char *retval; // $s0

  retval = (char *)sceNetCnfAllocMem(e, strlen((const char *)str) + 1, 0);
  if ( !retval )
    return 0;
  strcpy(retval, (const char *)str);
  return (u8 *)retval;
}

//----- (00401104) --------------------------------------------------------
static void init_usrntcnf(sceNetCnfInterface_t *ifc)
{
  int i; // $a1

  ifc->type = -1;
  ifc->dhcp = -1;
  ifc->dhcp_host_name = 0;
  ifc->address = 0;
  ifc->netmask = 0;
  ifc->cmd_head = 0;
  ifc->cmd_tail = 0;
  for ( i = 0; i < 3; i += 1 )
  {
    ifc->phone_numbers[i] = 0;
  }
  ifc->want.dns1_nego = -1;
  ifc->want.dns2_nego = -1;
  ifc->pppoe = -1;
  ifc->want.prc_nego = -1;
  ifc->want.acc_nego = -1;
  ifc->want.accm_nego = -1;
  ifc->auth_name = 0;
  ifc->auth_key = 0;
  ifc->peer_name = 0;
  ifc->allow.f_auth = 0;
  ifc->allow.auth = 4;
  ifc->mtu = -1;
  ifc->phy_config = -1;
  ifc->vendor = 0;
  ifc->product = 0;
  ifc->chat_additional = 0;
  ifc->outside_number = 0;
  ifc->outside_delay = 0;
  ifc->dialing_type = -1;
  ifc->idle_timeout = -1;
}

//----- (004011A0) --------------------------------------------------------
static int check_address(char *str)
{
  int retres; // $a1

  retres = 0;
  for ( ; *str; str += 1 )
  {
    if ( *str != '.' && *str != '0' )
      retres = 1;
  }
  return retres;
}

//----- (004011F0) --------------------------------------------------------
static int put_gw(sceNetCnfEnv_t *e, const char *gw)
{
  int retres; // $v1

  bzero(&gateway, sizeof(gateway));
  gateway.cmd.code = 3;
  gateway.cmd.back = e->ifc->cmd_tail;
  if ( gateway.cmd.back )
    gateway.cmd.back->forw = &gateway.cmd;
  else
    e->ifc->cmd_head = &gateway.cmd;
  gateway.cmd.forw = 0;
  e->ifc->cmd_tail = &gateway.cmd;
  if ( gw )
  {
    retres = sceNetCnfName2Address(&gateway.re.dstaddr, 0);
    if ( retres < 0 )
      return retres;
    retres = sceNetCnfName2Address(&gateway.re.gateway, gw);
    if ( retres < 0 )
      return retres;
    retres = sceNetCnfName2Address(&gateway.re.genmask, 0);
    if ( retres < 0 )
      return retres;
    gateway.re.flags |= 4u;
  }
  else
  {
    retres = sceNetCnfName2Address(&gateway.re.dstaddr, 0);
    if ( retres < 0 )
      return retres;
    retres = sceNetCnfName2Address(&gateway.re.gateway, 0);
    if ( retres < 0 )
      return retres;
    retres = sceNetCnfName2Address(&gateway.re.genmask, 0);
    if ( retres < 0 )
      return retres;
    gateway.re.flags = 0;
  }
  return retres;
}
// 4055A0: using guessed type route_t gateway;

//----- (0040131C) --------------------------------------------------------
static int put_ns(sceNetCnfEnv_t *e, const char *ns, int ns_count)
{
  nameserver_t *ns1; // $s0
  nameserver_t *ns2; // $a0

  ns1 = 0;
  switch ( ns_count )
  {
    case 1:
      ns1 = &dns1;
      ns2 = &dns1;
      break;
    case 2:
      ns1 = &dns2;
      ns2 = &dns2;
      break;
    default:
      // Unofficial: return error instead of writing 1 to 0x00000008
      return -1;
  }
  bzero(ns2, sizeof(nameserver_t));
  ns1->cmd.code = 1;
  ns1->cmd.back = e->ifc->cmd_tail;
  if ( e->ifc->cmd_tail )
    e->ifc->cmd_tail->forw = &ns1->cmd;
  else
    e->ifc->cmd_head = &ns1->cmd;
  ns1->cmd.forw = 0;
  e->ifc->cmd_tail = &ns1->cmd;
  return sceNetCnfName2Address(&ns1->address, ns);
}
// 405600: using guessed type nameserver_t dns1;
// 405620: using guessed type nameserver_t dns2;

//----- (004013E4) --------------------------------------------------------
static int put_cmd(sceNetCnfEnv_t *e, sceNetcnfifData_t *data)
{
  int retres; // $s0

  retres = !data->dhcp ? put_gw(e, ( data->gateway[0] && check_address(data->gateway) ) ? data->gateway : 0) : 0;
  if ( data->dns1_address[0] && check_address(data->dns1_address) )
  {
    retres = put_ns(e, data->dns1_address, 1);
    if ( data->dns2_address[0] && check_address(data->dns2_address) )
      return put_ns(e, data->dns2_address, 2);
  }
  return retres;
}

//----- (004014D0) --------------------------------------------------------
static int root_link(sceNetCnfEnv_t *e, int type)
{
  struct sceNetCnfRoot *root; // $v0
  struct sceNetCnfPair *p; // $v1
  struct sceNetCnfPair *pair_tail; // $v0

  if ( !e->ifc )
    return 0;
  root = e->root;
  if ( !root )
  {
    e->root = (sceNetCnfRoot_t *)sceNetCnfAllocMem(e, sizeof(sceNetCnfRoot_t), 2);
    if ( !e->root )
      return -2;
    e->root->version = 3;
    e->root->redial_count = -1;
    e->root->redial_interval = -1;
    e->root->dialing_type = -1;
  }
  if ( !root || !root->pair_head )
  {
    p = (sceNetCnfPair_t *)sceNetCnfAllocMem(e, sizeof(sceNetCnfPair_t), 2);
    if ( !p )
      return -2;
    switch ( type )
    {
      case 1:
        p->ifc = e->ifc;
        break;
      case 2:
        p->dev = e->ifc;
        break;
      default:
        break;
    }
    pair_tail = e->root->pair_tail;
    p->back = pair_tail;
    if ( !pair_tail )
      pair_tail = (sceNetCnfPair_t *)e->root;
    pair_tail->forw = p;
    p->forw = 0;
    e->root->pair_tail = p;
    return 0;
  }
  switch ( type )
  {
    case 1:
      root->pair_head->ifc = e->ifc;
      break;
    case 2:
      e->root->pair_head->dev = e->ifc;
      break;
    default:
      break;
  }
  return 0;
}

//----- (00401628) --------------------------------------------------------
static int put_attach(sceNetCnfEnv_t *e, sceNetcnfifData_t *data, int type)
{
  int retres; // $s3
  int init_flag; // $s0
  char chat_additional[256]; // [sp+10h] [-100h] BYREF

  retres = 0;
  if ( !e->ifc )
  {
    e->ifc = (sceNetCnfInterface_t *)sceNetCnfAllocMem(e, sizeof(sceNetCnfInterface_t), 2);
    if ( !e->ifc )
      return -2;
    sceNetCnfInitIFC(e->ifc);
  }
  init_flag = 1;
  init_usrntcnf(e->ifc);
  switch ( type )
  {
    case 1:
      if ( data->ifc_type != -1 )
      {
        init_flag = 0;
        e->ifc->type = data->ifc_type;
      }
      if ( data->dhcp != 255 )
      {
        init_flag = 0;
        e->ifc->dhcp = data->dhcp;
      }
      if ( data->dhcp_host_name[0] )
      {
        init_flag = 0;
        e->ifc->dhcp_host_name = dup_string(e, (u8 *)data->dhcp_host_name);
      }
      if ( data->address[0] )
      {
        init_flag = 0;
        e->ifc->address = dup_string(e, (u8 *)data->address);
      }
      if ( data->netmask[0] )
      {
        init_flag = 0;
        e->ifc->netmask = dup_string(e, (u8 *)data->netmask);
      }
      retres = put_cmd(e, data);
      if ( retres < 0 )
      {
        return retres;
      }
      if ( retres )
        init_flag = 0;
      if ( data->phone_numbers1[0] )
      {
        init_flag = 0;
        e->ifc->phone_numbers[0] = dup_string(e, (u8 *)data->phone_numbers1);
      }
      if ( data->phone_numbers2[0] )
      {
        init_flag = 0;
        e->ifc->phone_numbers[1] = dup_string(e, (u8 *)data->phone_numbers2);
      }
      if ( data->phone_numbers3[0] )
      {
        init_flag = 0;
        e->ifc->phone_numbers[2] = dup_string(e, (u8 *)data->phone_numbers3);
      }
      if ( data->auth_name[0] )
      {
        init_flag = 0;
        e->ifc->auth_name = dup_string(e, (u8 *)data->auth_name);
      }
      if ( data->auth_key[0] )
      {
        init_flag = 0;
        e->ifc->auth_key = dup_string(e, (u8 *)data->auth_key);
      }
      if ( data->peer_name[0] )
      {
        init_flag = 0;
        e->ifc->peer_name = dup_string(e, (u8 *)data->peer_name);
      }
      if ( data->dns1_nego != 255 )
      {
        init_flag = 0;
        e->ifc->want.dns1_nego = data->dns1_nego;
      }
      if ( data->dns2_nego != 255 )
      {
        init_flag = 0;
        e->ifc->want.dns2_nego = data->dns2_nego;
      }
      if ( data->f_auth )
      {
        init_flag = 0;
        e->ifc->allow.f_auth = data->f_auth;
      }
      e->ifc->allow.auth = data->auth;
      if ( data->pppoe != 255 )
      {
        init_flag = 0;
        e->ifc->pppoe = data->pppoe;
      }
      if ( data->prc_nego != 255 )
      {
        init_flag = 0;
        e->ifc->want.prc_nego = data->prc_nego;
      }
      if ( data->acc_nego != 255 )
      {
        init_flag = 0;
        e->ifc->want.acc_nego = data->acc_nego;
      }
      if ( data->accm_nego != 255 )
      {
        init_flag = 0;
        e->ifc->want.accm_nego = data->accm_nego;
      }
      if ( data->mtu != -1 )
      {
        init_flag = 0;
        e->ifc->mtu = data->mtu;
      }
      if ( data->ifc_idle_timeout != -1 )
      {
        init_flag = 0;
        e->ifc->idle_timeout = data->ifc_idle_timeout;
      }
      break;
    case 2:
      if ( data->dev_type != -1 )
      {
        init_flag = 0;
        e->ifc->type = data->dev_type;
      }
      if ( data->vendor[0] )
      {
        init_flag = 0;
        e->ifc->vendor = dup_string(e, (u8 *)data->vendor);
      }
      if ( data->product[0] )
      {
        init_flag = 0;
        e->ifc->product = dup_string(e, (u8 *)data->product);
      }
      if ( data->phy_config != -1 )
      {
        init_flag = 0;
        e->ifc->phy_config = data->phy_config;
      }
      if ( data->chat_additional[0] )
      {
        retres = sceNetCnfConvA2S(data->chat_additional, chat_additional, sizeof(data->chat_additional));
        if ( retres < 0 )
          return retres;
        init_flag = 0;
        e->ifc->chat_additional = dup_string(e, (u8 *)chat_additional);
      }
      if ( data->outside_number[0] )
      {
        init_flag = 0;
        e->ifc->outside_number = dup_string(e, (u8 *)data->outside_number);
      }
      if ( data->outside_delay[0] )
      {
        init_flag = 0;
        e->ifc->outside_delay = dup_string(e, (u8 *)data->outside_delay);
      }
      if ( data->dialing_type != -1 )
      {
        init_flag = 0;
        e->ifc->dialing_type = data->dialing_type;
      }
      if ( data->dev_idle_timeout != -1 )
      {
        init_flag = 0;
        e->ifc->idle_timeout = data->dev_idle_timeout;
      }
      break;
    default:
      break;
  }
  if ( init_flag )
  {
    e->ifc = 0;
  }
  return ( !init_flag ) ? (( !e->alloc_err ) ? retres : -2) : -100;
}

//----- (00401AC4) --------------------------------------------------------
static int put_net(sceNetCnfEnv_t *e, sceNetcnfifData_t *data)
{
  struct sceNetCnfPair *p; // $s1
  struct sceNetCnfPair *pair_tail; // $v0
  int i; // $s0
  int attachres1; // $v0
  char display_name[256]; // [sp+10h] [-100h] BYREF

  if ( !data->attach_ifc[0] || !data->attach_dev[0] )
    return -100;
  if ( !e->root )
  {
    e->root = (sceNetCnfRoot_t *)sceNetCnfAllocMem(e, sizeof(sceNetCnfRoot_t), 2);
    if ( !e->root )
      return -2;
  }
  e->root->version = 3;
  e->root->redial_count = -1;
  e->root->redial_interval = -1;
  e->root->dialing_type = -1;
  p = e->root->pair_head;
  if ( !p )
  {
    p = (sceNetCnfPair_t *)sceNetCnfAllocMem(e, sizeof(sceNetCnfPair_t), 2);
    if ( !p )
      return -2;
    pair_tail = e->root->pair_tail;
    p->back = pair_tail;
    if ( !pair_tail )
      pair_tail = (sceNetCnfPair_t *)e->root;
    pair_tail->forw = p;
    p->forw = 0;
    e->root->pair_tail = p;
  }
  strcpy(display_name, data->attach_ifc);
  strcat(display_name, " + ");
  strcat(display_name, data->attach_dev);
  p->display_name = dup_string(e, (u8 *)display_name);
  p->attach_ifc = dup_string(e, (u8 *)data);
  p->attach_dev = dup_string(e, (u8 *)data->attach_dev);
  for ( i = 0; i < 2; i += 1 )
  {
    e->ifc = 0;
    attachres1 = put_attach(e, data, i + 1);
    if ( attachres1 < 0 && attachres1 != -100 )
      break;
    attachres1 = root_link(e, i + 1);
    if ( attachres1 < 0 )
      break;
  }
  return ( !e->alloc_err ) ? attachres1 : -2;
}

//----- (00401CB4) --------------------------------------------------------
static int sceNetcnfifWriteEnv(sceNetCnfEnv_t *e, sceNetcnfifData_t *data, int type)
{
  int retres1; // $s0

  retres1 = 0;
  switch ( type )
  {
    case 0:
      retres1 = put_net(e, data);
      break;
    case 1:
    case 2:
    case 3:
    {
      retres1 = put_attach(e, data, type);
      if ( retres1 < 0 )
        return retres1;
      retres1 = root_link(e, type);
      break;
    }
    default:
      printf("[%s] unknown type (%d)\n", "sceNetcnfifWriteEnv", type);
      break;
  }
  if ( retres1 >= 0 )
  {
    e->mem_ptr = (void *)(((int)e->mem_ptr + 3) & 0xFFFFFFFC);
    e->mem_base = e->mem_ptr;
  }
  return retres1;
}

//----- (00401D70) --------------------------------------------------------
static int sceNetcnfifSendEE(unsigned int data, unsigned int addr, unsigned int size)
{
  int dmatid; // $s0
  SifDmaTransfer_t dmat; // [sp+10h] [-10h] BYREF

  dmat.src = (void *)data;
  dmat.dest = (void *)addr;
  dmat.size = (size & 0xFFFFFFC0) + ((size & 0x3F) ? 64 : 0);
  dmat.attr = 0;
  dmatid = 0;
  while ( !dmatid )
  {
    CpuSuspendIntr(&oldstat);
    dmatid = sceSifSetDma(&dmat, 1);
    CpuResumeIntr(oldstat);
  }
  return dmatid;
}

//----- (00401DE4) --------------------------------------------------------
static int sceNetcnfifDmaCheck(int id)
{
  return sceSifDmaStat(id) >= 0;
}

//----- (00401E10) --------------------------------------------------------
static void sce_callback_initialize(void)
{
  int i; // $v0

  while ( 1 )
  {
    if ( sceSifBindRpc(&gcd, 0x80001101, 0) < 0 )
    {
      while ( 1 );
    }
    while ( sceSifCheckStatRpc(&gcd) );
    if ( gcd.server )
      break;
    for ( i = 0xFFFE; i != -1; i -= 1 );
  }
}

//----- (00401E94) --------------------------------------------------------
static int sce_callback_open(const char *device, const char *pathname, int flags, int mode, int *filesize)
{
  gbuf[0] = flags;
  gbuf[1] = mode;
  gbuf[2] = strlen(device) + 1;
  gbuf[3] = strlen(pathname) + 1;
  memcpy(&gbuf[4], device, strlen(device) + 1);
  memcpy((char *)&gbuf[4] + strlen(device) + 1, pathname, strlen(pathname) + 1);
  if ( sceSifCallRpc(&gcd, 12, 0, gbuf, (strlen(pathname) + strlen(device) + 1 + 80) & 0xFFFFFFC0, gbuf, 64, 0, 0) >= 0 )
  {
    *filesize = gbuf[1];
    return gbuf[0];
  }
  return -1;
}
// 405678: using guessed type int gbuf[1024];

//----- (00401F88) --------------------------------------------------------
static int sce_callback_read(int fd, const char *device, const char *pathname, void *buf, int offset, int size)
{
  gbuf[0] = fd;
  gbuf[1] = strlen(device) + 1;
  gbuf[2] = strlen(pathname) + 1;
  gbuf[3] = offset;
  gbuf[4] = size;
  memcpy(&gbuf[5], device, strlen(device) + 1);
  memcpy((char *)&gbuf[5] + strlen(device) + 1, pathname, strlen(pathname) + 1);
  if ( sceSifCallRpc(&gcd, 13, 0, gbuf, (strlen(pathname) + strlen(device) + 1 + 84) & 0xFFFFFFC0, gbuf, (size + 67) & 0xFFFFFFC0, 0, 0) < 0 )
    return -1;
  memcpy(buf, &gbuf[1], size);
  return gbuf[0];
}
// 405678: using guessed type int gbuf[1024];

//----- (004020B4) --------------------------------------------------------
static int sce_callback_close(int fd)
{
  gbuf[0] = fd;
  return (sceSifCallRpc(&gcd, 14, 0, gbuf, 64, gbuf, 64, 0, 0) >= 0) ? gbuf[0] : -1;
}
// 405678: using guessed type int gbuf[1024];

//----- (00402120) --------------------------------------------------------
static int my_create_heap(void)
{
  if ( g_heap )
    return -2;
  g_heap = CreateHeap(1024, 1);
  return g_heap ? 0 : -1;
}

//----- (00402170) --------------------------------------------------------
static void *my_alloc(int size)
{
  return AllocHeapMemory(g_heap, size);
}

//----- (0040219C) --------------------------------------------------------
static void my_free(void *ptr)
{
  if ( ptr )
    FreeHeapMemory(g_heap, ptr);
}

//----- (004021CC) --------------------------------------------------------
static void my_delete_heap(void)
{
  DeleteHeap(g_heap);
  g_heap = 0;
}
