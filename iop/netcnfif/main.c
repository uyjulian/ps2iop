
#include "irx_imports.h"
#include <stdbool.h>

IRX_ID("Netcnf_Interface", 2, 30);

// TODO EE 64 byte alignment
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

typedef struct route
{
  sceNetCnfCommand_t cmd;
  sceNetCnfRoutingEntry_t re;
} route_t;

typedef struct nameserver
{
  sceNetCnfCommand_t cmd;
  sceNetCnfAddress_t address;
} nameserver_t;

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

void usage(void);
int module_start(int argc, char *argv[]);
int module_stop(int argc, char *argv[]);
int _start(int argc, char *argv[]);
void netcnfif_0();
void *sceNetcnfifInterfaceServer(int fno, sceNetcnfifArg_t *buf, int size);
void sceNetcnfifInterfaceStart(void);
void sceNetcnfifInterfaceStop(void);
void sceNetcnfifDataInit(sceNetcnfifData_t *data);
void sceNetcnfifEnvInit(sceNetCnfEnv_t *env, void *mem_area, int size, int f_no_decode);
int get_cmd(sceNetcnfifData_t *data, sceNetCnfCommand_t *p, int *ns_count);
int get_attach(sceNetcnfifData_t *data, sceNetCnfInterface_t *p, int type);
int get_net(sceNetcnfifData_t *data, sceNetCnfRoot_t *p);
int sceNetcnfifReadEnv(sceNetcnfifData_t *data, sceNetCnfEnv_t *e, int type);
u8 *dup_string(sceNetCnfEnv_t *e, u8 *str);
void init_usrntcnf(sceNetCnfInterface_t *ifc);
int check_address(char *str);
int put_gw(sceNetCnfEnv_t *e, char *gw);
int put_ns(sceNetCnfEnv_t *e, char *ns, int ns_count);
int put_cmd(sceNetCnfEnv_t *e, sceNetcnfifData_t *data);
int root_link(sceNetCnfEnv_t *e, int type);
int put_attach(sceNetCnfEnv_t *e, sceNetcnfifData_t *data, int type);
int put_net(sceNetCnfEnv_t *e, sceNetcnfifData_t *data);
int sceNetcnfifWriteEnv(sceNetCnfEnv_t *e, sceNetcnfifData_t *data, int type);
int sceNetcnfifSendEE(unsigned int data, unsigned int addr, unsigned int size);
int sceNetcnfifDmaCheck(int id);
void sce_callback_initialize(void);
int sce_callback_open(const char *device, const char *pathname, int flags, int mode, int *filesize);
int sce_callback_read(int fd, const char *device, const char *pathname, void *buf, int offset, int size);
int sce_callback_close(int fd);
int my_create_heap(void);
void *my_alloc(int size);
void my_free(void *ptr);
void my_delete_heap(void);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_netcnfif;
void *mem_area = NULL; // idb
int mem_area_size = 0; // idb
void *g_heap = NULL; // idb
int g_tid; // idb
sceNetCnfEnv_t env; // weak
sceNetcnfifData_t data; // idb
char dp[0x100]; // idb
int rpc_buf[1024]; // weak
SifRpcServerData_t sd; // idb
SifRpcDataQueue_t qd; // weak
int ns_count; // idb
route_t gateway; // weak
nameserver_t dns1; // weak
nameserver_t dns2; // weak
int oldstat; // idb
SifRpcClientData_t gcd; // idb
int gbuf[1024]; // weak


//----- (00400000) --------------------------------------------------------
void usage(void)
{
  printf("Usage: netcnfif <option>\n");
  printf("    <option>:\n");
  printf("    thpri=<digit>     - set thread priority\n");
  printf("    thstack=<digit>KB - set thread stack size(Kbyte)\n");
  printf("    thstack=<digit>   - set thread stack size(byte)\n");
  printf("    -help             - print usage\n");
}

//----- (00400064) --------------------------------------------------------
int module_start(int argc, char *argv[])
{
  int thpri; // $s5
  int thstack; // $s4
  int cur_argc; // $s3
  const char **cur_argv; // $s2
  const char *thpri_argv_cur; // $s1
  char *bp; // $s0
  int bp_curchr; // $v0
  const char *thstack_argv_cur; // $s1
  int retres1; // $v0
  int retres2; // $v0
  int tid; // $v0
  int retres3; // $v0
  iop_thread_t th_param; // [sp+10h] [-18h] BYREF

  thpri = 123;
  thstack = 4096;
  cur_argc = argc - 1;
  cur_argv = (const char **)(argv + 1);
  while ( cur_argc > 0 )
  {
    if ( !strncmp("thpri=", *cur_argv, 6) )
    {
      thpri_argv_cur = *cur_argv;
      bp = (char *)(*cur_argv + 6);
      if ( (look_ctype_table(*bp) & 4) == 0 )
        goto LABEL_30;
      thpri = strtol(bp, 0, 10);
      if ( (unsigned int)(thpri - 9) >= 0x73 )
        goto LABEL_30;
      if ( !thpri_argv_cur[6] )
        goto LABEL_18;
      while ( (look_ctype_table(*bp) & 4) != 0 )
      {
        bp_curchr = *++bp;
        if ( !*bp )
          goto LABEL_17;
      }
    }
    else
    {
      if ( strncmp("thstack=", *cur_argv, 8) )
        goto LABEL_30;
      thstack_argv_cur = *cur_argv;
      bp = (char *)(*cur_argv + 8);
      if ( (look_ctype_table(*bp) & 4) == 0 )
        goto LABEL_30;
      thstack = strtol(bp, 0, 10);
      if ( thstack_argv_cur[8] )
      {
        do
        {
          if ( (look_ctype_table(*bp) & 4) == 0 )
            break;
          ++bp;
        }
        while ( *bp );
      }
      if ( !strcmp(bp, "KB") )
      {
        thstack <<= 10;
        goto LABEL_18;
      }
    }
    bp_curchr = *bp;
LABEL_17:
    if ( bp_curchr )
    {
LABEL_30:
      usage();
      return 1;
    }
LABEL_18:
    --cur_argc;
    ++cur_argv;
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
    th_param.thread = (void (*)(void *))sceNetcnfifInterfaceStart;
    th_param.priority = thpri;
    th_param.stacksize = thstack;
    th_param.option = 0;
    tid = CreateThread(&th_param);
    g_tid = tid;
    if ( tid >= 0 )
    {
      retres3 = StartThread(tid, 0);
      if ( retres3 >= 0 )
        return 2;
      printf("netcnfif: s_thread(%d)\n", retres3);
      TerminateThread(g_tid);
      DeleteThread(g_tid);
    }
    else
    {
      printf("netcnfif: c_thread(%d)\n", tid);
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
int module_stop(int argc, char *argv[])
{
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
  if ( argc >= 0 )
    return module_start(argc, argv);
  else
    return module_stop(-argc, argv);
}

//----- (004003E8) --------------------------------------------------------
void netcnfif_0()
{
  ;
}

//----- (004003F0) --------------------------------------------------------
void *sceNetcnfifInterfaceServer(int fno, sceNetcnfifArg_t *buf, int size)
{
  int retres1; // $s1
  int retres2; // $v0
  sceNetCnfList_t *list_iop; // $s3
  int *list_ee; // $s4
  int dataind1; // $a0
  sceNetCnfList_t *p_list_iop; // $a2
  int *p_list_ee; // $a3
  int *p2_list_ee; // $v1
  sceNetCnfList_t *p2_list_iop; // $v0
  int cpywtmp1; // $t1
  int cpywtmp2; // $t2
  int cpywtmp3; // $t3
  int p2_stat_tmp; // $t1
  int dmatid1; // $s0
  void *result; // $v0
  int dmatid2; // $s0
  bool condtmp1; // dc
  int typetmp; // $v1
  int redial_count; // $a1
  int dialind; // $a0
  struct sceNetCnfInterface *ifc; // $v1
  struct sceNetCnfInterface *ifc_1; // $a0
  sceNetCnfCallback_t callback; // [sp+18h] [-10h] BYREF

  retres1 = 0;
  switch ( fno )
  {
    case 0:
      retres1 = sceNetCnfGetCount(buf->fname, buf->type);
      goto LABEL_56;
    case 1:
      retres2 = sceNetCnfGetCount(buf->fname, buf->type);
      retres1 = retres2;
      if ( retres2 < 0 )
        goto LABEL_56;
      list_iop = (sceNetCnfList_t *)my_alloc(520 * retres2);
      retres1 = -2;
      if ( !list_iop )
        goto LABEL_56;
      list_ee = (int *)my_alloc(576 * buf->data);
      if ( list_ee )
      {
        retres1 = sceNetCnfGetList(buf->fname, buf->type, list_iop);
        if ( retres1 >= 0 )
        {
          dataind1 = 0;
          if ( buf->data > 0 )
          {
            p_list_iop = list_iop;
            p_list_ee = list_ee;
            do
            {
              p2_list_ee = p_list_ee;
              if ( dataind1 >= retres1 )
                break;
              p2_list_iop = p_list_iop;
              do
              {
                cpywtmp1 = p2_list_iop->stat;
                cpywtmp2 = *(u32 *)p2_list_iop->sys_name;
                cpywtmp3 = *(u32 *)&p2_list_iop->sys_name[4];
                *p2_list_ee = p2_list_iop->type;
                p2_list_ee[1] = cpywtmp1;
                p2_list_ee[2] = cpywtmp2;
                p2_list_ee[3] = cpywtmp3;
                p2_list_iop = (sceNetCnfList_t *)((char *)p2_list_iop + 16);
                p2_list_ee += 4;
              }
              while ( p2_list_iop != (sceNetCnfList_t *)&p_list_iop->usr_name[248] );
              ++p_list_iop;
              p2_stat_tmp = p2_list_iop->stat;
              *p2_list_ee = p2_list_iop->type;
              p2_list_ee[1] = p2_stat_tmp;
              ++dataind1;
              p_list_ee += 144;
            }
            while ( dataind1 < buf->data );
          }
          dmatid1 = sceNetcnfifSendEE((unsigned int)list_ee, buf->addr, 576 * buf->data);
          while ( sceNetcnfifDmaCheck(dmatid1) )
            ;
        }
        my_free(list_iop);
        my_free(list_ee);
        result = buf;
      }
      else
      {
        my_free(list_iop);
        retres1 = -2;
LABEL_56:
        result = buf;
      }
LABEL_57:
      buf->data = retres1;
      break;
    case 2:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetCnfLoadEntry(buf->fname, buf->type, buf->usr_name, &env);
      result = buf;
      if ( retres1 < 0 )
        goto LABEL_57;
      sceNetcnfifDataInit(&data);
      retres1 = sceNetcnfifReadEnv(&data, &env, buf->type);
      if ( retres1 < 0 )
        goto LABEL_56;
      dmatid2 = sceNetcnfifSendEE((unsigned int)&data, buf->addr, 0x1340u);
      do
      {
        condtmp1 = sceNetcnfifDmaCheck(dmatid2) != 0;
        result = buf;
      }
      while ( condtmp1 );
      buf->data = retres1;
      break;
    case 3:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetcnfifWriteEnv(&env, &data, buf->type);
      if ( retres1 >= 0 )
        retres1 = sceNetCnfAddEntry(buf->fname, buf->type, buf->usr_name, &env);
      goto LABEL_56;
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
      goto LABEL_56;
    case 5:
      retres1 = sceNetCnfDeleteEntry(buf->fname, buf->type, buf->usr_name);
      goto LABEL_56;
    case 6:
      retres1 = sceNetCnfSetLatestEntry(buf->fname, buf->type, buf->usr_name);
      goto LABEL_56;
    case 7:
      retres1 = sceNetCnfDeleteAll(buf->fname);
      goto LABEL_56;
    case 8:
      retres1 = sceNetCnfCheckCapacity(buf->fname);
      goto LABEL_56;
    case 9:
      retres1 = sceNetCnfConvA2S(buf->fname, dp, 256);
      goto LABEL_56;
    case 10:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetCnfCheckSpecialProvider(buf->fname, buf->type, buf->usr_name, &env);
      goto LABEL_56;
    case 11:
      typetmp = buf->type;
      callback.open = sce_callback_open;
      callback.read = sce_callback_read;
      callback.close = sce_callback_close;
      callback.type = typetmp;
      sce_callback_initialize();
      sceNetCnfSetCallback(&callback);
      result = buf;
      goto LABEL_57;
    case 15:
      sceNetCnfSetCallback(0);
      result = buf;
      goto LABEL_57;
    case 100:
      buf->addr = (int)&data;
      goto LABEL_56;
    case 101:
      result = buf;
      if ( !mem_area )
      {
        mem_area_size = buf->data;
        mem_area = my_alloc(mem_area_size);
        result = buf;
        if ( !mem_area )
          retres1 = -2;
      }
      goto LABEL_57;
    case 102:
      if ( mem_area )
        my_free(mem_area);
      mem_area_size = 0;
      mem_area = 0;
      result = buf;
      goto LABEL_57;
    case 103:
      sceNetcnfifEnvInit(&env, mem_area, mem_area_size, buf->f_no_decode);
      retres1 = sceNetcnfifWriteEnv(&env, &data, buf->type);
      result = buf;
      if ( retres1 < 0 )
        goto LABEL_57;
      if ( env.root )
      {
        if ( env.root->pair_head )
        {
          redial_count = 0;
          if ( env.root->pair_head->ifc )
          {
            dialind = 0;
            ifc = env.root->pair_head->ifc;
            do
            {
              if ( ifc->phone_numbers[0] && dialind < 3 && dialind >= 0 )
                ++redial_count;
              ++dialind;
              ifc = (struct sceNetCnfInterface *)((char *)ifc + 4);
            }
            while ( dialind < 10 );
            env.root->pair_head->ifc->redial_count = redial_count - 1;
            ifc_1 = env.root->pair_head->ifc;
            if ( ifc_1->pppoe != 1 && ifc_1->type != 2 )
              ifc_1->type = env.root->pair_head->dev->type;
          }
        }
      }
      buf->addr = (int)&env;
      goto LABEL_56;
    default:
      goto LABEL_56;
  }
  return result;
}
// 402880: using guessed type sceNetCnfEnv_t env;

//----- (00400A10) --------------------------------------------------------
void sceNetcnfifInterfaceStart(void)
{
  int ThreadId; // $v0

  sceSifInitRpc(0);
  ThreadId = GetThreadId();
  sceSifSetRpcQueue(&qd, ThreadId);
  sceSifRegisterRpc(&sd, 0x80001101, (SifRpcFunc_t)sceNetcnfifInterfaceServer, rpc_buf, 0, 0, &qd);
  sceSifRpcLoop(&qd);
}
// 404530: using guessed type int rpc_buf[1024];
// 405578: using guessed type SifRpcDataQueue_t qd;

//----- (00400A88) --------------------------------------------------------
void sceNetcnfifInterfaceStop(void)
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
void sceNetcnfifDataInit(sceNetcnfifData_t *data)
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
void sceNetcnfifEnvInit(sceNetCnfEnv_t *env, void *mem_area, int size, int f_no_decode)
{
  memset(env, 0, sizeof(sceNetCnfEnv_t));
  env->mem_ptr = mem_area;
  env->mem_base = mem_area;
  env->mem_last = (char *)mem_area + size;
  env->f_no_decode = f_no_decode;
}

//----- (00400BE0) --------------------------------------------------------
int get_cmd(sceNetcnfifData_t *data, sceNetCnfCommand_t *p, int *ns_count)
{
  int code; // $v1
  int retres; // $a1
  char *gateway; // $a0
  char *dns_address; // $a0

  code = p->code;
  retres = 0;
  if ( code == 1 )
  {
    if ( *ns_count )
    {
      dns_address = data->dns2_address;
      if ( *ns_count != 1 )
        return retres;
    }
    else
    {
      dns_address = data->dns1_address;
    }
    retres = sceNetCnfAddress2String(dns_address, 256, (sceNetCnfAddress_t *)&p[1]);
    ++*ns_count;
  }
  else
  {
    gateway = data->gateway;
    if ( code == 3 )
      return sceNetCnfAddress2String(gateway, 256, (sceNetCnfAddress_t *)&p[2].code);
  }
  return retres;
}

//----- (00400C80) --------------------------------------------------------
int get_attach(sceNetcnfifData_t *data, sceNetCnfInterface_t *p, int type)
{
  int cmd; // $s4
  int result; // $v0
  u8 *dhcp_host_name; // $a1
  u8 *address; // $a1
  u8 *netmask; // $a1
  struct sceNetCnfCommand *cmd_head; // $s0
  sceNetcnfifData_t *i; // $a0
  int numind; // $s0
  sceNetCnfInterface_t *p_1; // $s2
  const char *str; // $a1
  char *phone_numbers2; // $a0
  u8 *auth_name; // $a1
  u8 *auth_key; // $a1
  u8 *peer_name; // $a1
  u8 *vendor; // $a1
  u8 *product; // $a1
  char *chat_additional; // $a0
  u8 *outside_number; // $a1
  u8 *outside_delay; // $a1

  cmd = 0;
  if ( type != 1 )
  {
    result = 0;
    if ( type == 2 )
    {
      data->dev_type = p->type;
      vendor = p->vendor;
      if ( vendor )
        strcpy(data->vendor, (const char *)vendor);
      product = p->product;
      if ( product )
        strcpy(data->product, (const char *)product);
      data->phy_config = p->phy_config;
      chat_additional = (char *)p->chat_additional;
      if ( !chat_additional
        || (result = sceNetCnfConvS2A(chat_additional, data->chat_additional, 256), cmd = result, result >= 0) )
      {
        outside_number = p->outside_number;
        if ( outside_number )
          strcpy(data->outside_number, (const char *)outside_number);
        outside_delay = p->outside_delay;
        if ( outside_delay )
          strcpy(data->outside_delay, (const char *)outside_delay);
        data->dialing_type = p->dialing_type;
        data->dev_idle_timeout = p->idle_timeout;
        return cmd;
      }
    }
    return result;
  }
  data->ifc_type = p->type;
  data->dhcp = p->dhcp;
  dhcp_host_name = p->dhcp_host_name;
  if ( dhcp_host_name )
    strcpy(data->dhcp_host_name, (const char *)dhcp_host_name);
  address = p->address;
  if ( address )
    strcpy(data->address, (const char *)address);
  netmask = p->netmask;
  if ( netmask )
    strcpy(data->netmask, (const char *)netmask);
  cmd_head = p->cmd_head;
  ns_count = 0;
  for ( i = data; cmd_head; i = data )
  {
    cmd = get_cmd(i, cmd_head, &ns_count);
    if ( cmd < 0 )
      return cmd;
    cmd_head = cmd_head->forw;
  }
  numind = 0;
  p_1 = p;
  do
  {
    str = (const char *)p_1->phone_numbers[0];
    if ( str )
    {
      if ( numind == 1 )
      {
        phone_numbers2 = data->phone_numbers2;
      }
      else if ( numind >= 2 )
      {
        phone_numbers2 = data->phone_numbers3;
        if ( numind != 2 )
        {
          p_1 = (sceNetCnfInterface_t *)((char *)p_1 + 4);
          goto LABEL_24;
        }
      }
      else
      {
        phone_numbers2 = data->phone_numbers1;
        if ( numind )
        {
          p_1 = (sceNetCnfInterface_t *)((char *)p_1 + 4);
          goto LABEL_24;
        }
      }
      strcpy(phone_numbers2, str);
    }
    p_1 = (sceNetCnfInterface_t *)((char *)p_1 + 4);
LABEL_24:
    ++numind;
  }
  while ( numind < 10 );
  auth_name = p->auth_name;
  if ( auth_name )
    strcpy(data->auth_name, (const char *)auth_name);
  auth_key = p->auth_key;
  if ( auth_key )
    strcpy(data->auth_key, (const char *)auth_key);
  peer_name = p->peer_name;
  if ( peer_name )
    strcpy(data->peer_name, (const char *)peer_name);
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
  return cmd;
}

//----- (00400F7C) --------------------------------------------------------
int get_net(sceNetcnfifData_t *data, sceNetCnfRoot_t *p)
{
  struct sceNetCnfPair *pair; // $s0
  int i; // $s1
  sceNetCnfInterface_t *ifc; // $a1
  sceNetCnfInterface_t *dev; // $a1

  pair = p->pair_head;
  for ( i = 0; pair; pair = pair->forw )
  {
    sceNetcnfifDataInit(data);
    strcpy(data->attach_ifc, (const char *)pair->attach_ifc);
    strcpy(data->attach_dev, (const char *)pair->attach_dev);
    ifc = pair->ifc;
    if ( ifc )
      i = get_attach(data, ifc, 1);
    dev = pair->dev;
    if ( dev )
      i = get_attach(data, dev, 2);
  }
  return i;
}

//----- (00401028) --------------------------------------------------------
int sceNetcnfifReadEnv(sceNetcnfifData_t *data, sceNetCnfEnv_t *e, int type)
{
  int retzero; // $s0

  retzero = 0;
  if ( !type )
    return get_net(data, e->root);
  if ( type >= 0 && type < 3 )
    return get_attach(data, e->ifc, type);
  printf("[%s] unknown type (%d)\n", "sceNetcnfifReadEnv", type);
  return retzero;
}

//----- (004010A0) --------------------------------------------------------
u8 *dup_string(sceNetCnfEnv_t *e, u8 *str)
{
  size_t strlenval; // $v0
  char *retval; // $s0

  strlenval = strlen((const char *)str);
  retval = (char *)sceNetCnfAllocMem(e, strlenval + 1, 0);
  if ( !retval )
    return 0;
  strcpy(retval, (const char *)str);
  return (u8 *)retval;
}

//----- (00401104) --------------------------------------------------------
void init_usrntcnf(sceNetCnfInterface_t *ifc)
{
  int ind; // $a1
  u8 **p_product; // $v1

  ind = 2;
  p_product = &ifc->product;
  ifc->type = -1;
  ifc->dhcp = -1;
  ifc->dhcp_host_name = 0;
  ifc->address = 0;
  ifc->netmask = 0;
  ifc->cmd_head = 0;
  ifc->cmd_tail = 0;
  do
  {
    p_product[14] = 0;
    --ind;
    --p_product;
  }
  while ( ind >= 0 );
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
int check_address(char *str)
{
  int retres; // $a1
  int str_hichr; // $v0
  int str_lochr; // $v0

  retres = 0;
  if ( *str )
  {
    str_hichr = (u8)*str << 24;
    do
    {
      str_lochr = str_hichr >> 24;
      if ( str_lochr != '.' && str_lochr != '0' )
        retres = 1;
      str_hichr = (u8)*++str << 24;
    }
    while ( *str );
  }
  return retres;
}

//----- (004011F0) --------------------------------------------------------
int put_gw(sceNetCnfEnv_t *e, char *gw)
{
  int result; // $v0
  int retres; // $v1

  bzero(&gateway, 96);
  gateway.cmd.code = 3;
  gateway.cmd.back = e->ifc->cmd_tail;
  if ( gateway.cmd.back )
    gateway.cmd.back->forw = (struct sceNetCnfCommand *)&gateway;
  else
    e->ifc->cmd_head = (struct sceNetCnfCommand *)&gateway;
  gateway.cmd.forw = 0;
  e->ifc->cmd_tail = (struct sceNetCnfCommand *)&gateway;
  if ( gw )
  {
    result = sceNetCnfName2Address(&gateway.re.dstaddr, 0);
    if ( result >= 0 )
    {
      result = sceNetCnfName2Address(&gateway.re.gateway, gw);
      if ( result >= 0 )
      {
        result = sceNetCnfName2Address(&gateway.re.genmask, 0);
        retres = result;
        if ( result >= 0 )
        {
          gateway.re.flags |= 4u;
          return retres;
        }
      }
    }
  }
  else
  {
    result = sceNetCnfName2Address(&gateway.re.dstaddr, 0);
    if ( result >= 0 )
    {
      result = sceNetCnfName2Address(&gateway.re.gateway, 0);
      if ( result >= 0 )
      {
        result = sceNetCnfName2Address(&gateway.re.genmask, 0);
        retres = result;
        if ( result >= 0 )
        {
          gateway.re.flags = 0;
          return retres;
        }
      }
    }
  }
  return result;
}
// 4055A0: using guessed type route_t gateway;

//----- (0040131C) --------------------------------------------------------
int put_ns(sceNetCnfEnv_t *e, char *ns, int ns_count)
{
  nameserver_t *ns1; // $s0
  nameserver_t *ns2; // $a0
  struct sceNetCnfCommand *cmd_tail; // $v0

  ns1 = 0;
  if ( ns_count == 1 )
  {
    ns1 = &dns1;
    ns2 = &dns1;
  }
  else
  {
    if ( ns_count != 2 )
    {
#if 0
      MEMORY[8] = 1;
#endif
      goto LABEL_7;
    }
    ns1 = &dns2;
    ns2 = &dns2;
  }
  bzero(ns2, 32);
  ns1->cmd.code = 1;
LABEL_7:
  cmd_tail = e->ifc->cmd_tail;
  ns1->cmd.back = cmd_tail;
  if ( cmd_tail )
    cmd_tail->forw = &ns1->cmd;
  else
    e->ifc->cmd_head = &ns1->cmd;
  ns1->cmd.forw = 0;
  e->ifc->cmd_tail = &ns1->cmd;
  return sceNetCnfName2Address(&ns1->address, ns);
}
// 405600: using guessed type nameserver_t dns1;
// 405620: using guessed type nameserver_t dns2;

//----- (004013E4) --------------------------------------------------------
int put_cmd(sceNetCnfEnv_t *e, sceNetcnfifData_t *data)
{
  int retres; // $s0
  int addrres; // $v0
  sceNetCnfEnv_t *e_1; // $a0
  char *gateway; // $a1

  retres = 0;
  if ( !data->dhcp )
  {
    if ( data->gateway[0] && (addrres = check_address(data->gateway), e_1 = e, addrres) )
    {
      gateway = data->gateway;
    }
    else
    {
      e_1 = e;
      gateway = 0;
    }
    retres = put_gw(e_1, gateway);
  }
  if ( data->dns1_address[0] )
  {
    if ( check_address(data->dns1_address) )
    {
      retres = put_ns(e, data->dns1_address, 1);
      if ( data->dns2_address[0] )
      {
        if ( check_address(data->dns2_address) )
          return put_ns(e, data->dns2_address, 2);
      }
    }
  }
  return retres;
}

//----- (004014D0) --------------------------------------------------------
int root_link(sceNetCnfEnv_t *e, int type)
{
  struct sceNetCnfInterface *ifc; // $a0
  int result; // $v0
  struct sceNetCnfRoot *root; // $v0
  struct sceNetCnfRoot *rootmem; // $v1
  struct sceNetCnfPair *p; // $v1
  struct sceNetCnfPair *pair_tail; // $v0

  ifc = e->ifc;
  result = 0;
  if ( !ifc )
    return result;
  root = e->root;
  if ( !root )
  {
    rootmem = (struct sceNetCnfRoot *)sceNetCnfAllocMem(e, 44, 2);
    e->root = rootmem;
    result = -2;
    if ( !rootmem )
      return result;
    rootmem->version = 3;
    e->root->redial_count = -1;
    e->root->redial_interval = -1;
    e->root->dialing_type = -1;
    goto LABEL_10;
  }
  if ( !root->pair_head )
  {
LABEL_10:
    p = (struct sceNetCnfPair *)sceNetCnfAllocMem(e, 40, 2);
    result = -2;
    if ( !p )
      return result;
    if ( type == 1 )
      p->ifc = e->ifc;
    if ( type == 2 )
      p->dev = e->ifc;
    pair_tail = e->root->pair_tail;
    p->back = pair_tail;
    if ( !pair_tail )
      pair_tail = (struct sceNetCnfPair *)e->root;
    pair_tail->forw = p;
    p->forw = 0;
    e->root->pair_tail = p;
    return 0;
  }
  if ( type == 1 )
    root->pair_head->ifc = ifc;
  result = 0;
  if ( type == 2 )
  {
    e->root->pair_head->dev = e->ifc;
    return 0;
  }
  return result;
}

//----- (00401628) --------------------------------------------------------
int put_attach(sceNetCnfEnv_t *e, sceNetcnfifData_t *data, int type)
{
  int retres; // $s3
  sceNetCnfInterface_t *ifctmp; // $v0
  int result; // $v0
  int init_flag; // $s0
  int ifc_type; // $v1
  int dhcp; // $v1
  int dns1_nego; // $v1
  int dns2_nego; // $v1
  int pppoe; // $v1
  int prc_nego; // $v1
  int acc_nego; // $v1
  int accm_nego; // $v1
  int mtu; // $v1
  int dev_idle_timeout; // $a0
  int dev_type; // $v1
  int phy_config; // $v1
  int dialing_type; // $v1
  char chat_additional[256]; // [sp+10h] [-100h] BYREF

  retres = 0;
  if ( !e->ifc )
  {
    ifctmp = (sceNetCnfInterface_t *)sceNetCnfAllocMem(e, 352, 2);
    e->ifc = ifctmp;
    if ( !ifctmp )
      return -2;
    sceNetCnfInitIFC(ifctmp);
  }
  init_flag = 1;
  init_usrntcnf(e->ifc);
  if ( type != 1 )
  {
    if ( type != 2 )
    {
LABEL_70:
      result = -100;
      if ( init_flag )
      {
        e->ifc = 0;
      }
      else
      {
        result = -2;
        if ( !e->alloc_err )
          return retres;
      }
      return result;
    }
    dev_type = data->dev_type;
    if ( dev_type != -1 )
    {
      init_flag = 0;
      e->ifc->type = dev_type;
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
    phy_config = data->phy_config;
    if ( phy_config != -1 )
    {
      init_flag = 0;
      e->ifc->phy_config = phy_config;
    }
    if ( data->chat_additional[0] )
    {
      result = sceNetCnfConvA2S(data->chat_additional, chat_additional, 256);
      retres = result;
      if ( result < 0 )
        return result;
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
    dialing_type = data->dialing_type;
    if ( dialing_type != -1 )
    {
      init_flag = 0;
      e->ifc->dialing_type = dialing_type;
    }
    dev_idle_timeout = data->dev_idle_timeout;
LABEL_68:
    if ( dev_idle_timeout != -1 )
    {
      init_flag = 0;
      e->ifc->idle_timeout = dev_idle_timeout;
    }
    goto LABEL_70;
  }
  ifc_type = data->ifc_type;
  if ( ifc_type != -1 )
  {
    init_flag = 0;
    e->ifc->type = ifc_type;
  }
  dhcp = data->dhcp;
  if ( dhcp != 255 )
  {
    init_flag = 0;
    e->ifc->dhcp = dhcp;
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
  result = put_cmd(e, data);
  retres = result;
  if ( result >= 0 )
  {
    if ( result )
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
    dns1_nego = data->dns1_nego;
    if ( dns1_nego != 255 )
    {
      init_flag = 0;
      e->ifc->want.dns1_nego = dns1_nego;
    }
    dns2_nego = data->dns2_nego;
    if ( dns2_nego != 255 )
    {
      init_flag = 0;
      e->ifc->want.dns2_nego = dns2_nego;
    }
    if ( data->f_auth )
    {
      init_flag = 0;
      e->ifc->allow.f_auth = data->f_auth;
    }
    e->ifc->allow.auth = data->auth;
    pppoe = data->pppoe;
    if ( pppoe != 255 )
    {
      init_flag = 0;
      e->ifc->pppoe = pppoe;
    }
    prc_nego = data->prc_nego;
    if ( prc_nego != 255 )
    {
      init_flag = 0;
      e->ifc->want.prc_nego = prc_nego;
    }
    acc_nego = data->acc_nego;
    if ( acc_nego != 255 )
    {
      init_flag = 0;
      e->ifc->want.acc_nego = acc_nego;
    }
    accm_nego = data->accm_nego;
    if ( accm_nego != 255 )
    {
      init_flag = 0;
      e->ifc->want.accm_nego = accm_nego;
    }
    mtu = data->mtu;
    if ( mtu != -1 )
    {
      init_flag = 0;
      e->ifc->mtu = mtu;
    }
    dev_idle_timeout = data->ifc_idle_timeout;
    goto LABEL_68;
  }
  return result;
}

//----- (00401AC4) --------------------------------------------------------
int put_net(sceNetCnfEnv_t *e, sceNetcnfifData_t *data)
{
  int result; // $v0
  struct sceNetCnfRoot *rootmem; // $v0
  struct sceNetCnfPair *p; // $s1
  struct sceNetCnfPair *pair_tail; // $v0
  u8 *attach_dev_tmp; // $v0
  int indx1; // $a2
  int indx2; // $s0
  int attachres1; // $v0
  int linkres1; // $a0
  char display_name[256]; // [sp+10h] [-100h] BYREF

  if ( !data->attach_ifc[0] || !data->attach_dev[0] )
    return -100;
  if ( !e->root )
  {
    rootmem = (struct sceNetCnfRoot *)sceNetCnfAllocMem(e, 44, 2);
    e->root = rootmem;
    if ( !rootmem )
      return -2;
  }
  e->root->version = 3;
  e->root->redial_count = -1;
  e->root->redial_interval = -1;
  e->root->dialing_type = -1;
  p = e->root->pair_head;
  if ( !p )
  {
    p = (struct sceNetCnfPair *)sceNetCnfAllocMem(e, 40, 2);
    if ( !p )
      return -2;
    pair_tail = e->root->pair_tail;
    p->back = pair_tail;
    if ( !pair_tail )
      pair_tail = (struct sceNetCnfPair *)e->root;
    pair_tail->forw = p;
    p->forw = 0;
    e->root->pair_tail = p;
  }
  strcpy(display_name, data->attach_ifc);
  strcat(display_name, " + ");
  strcat(display_name, data->attach_dev);
  p->display_name = dup_string(e, (u8 *)display_name);
  p->attach_ifc = dup_string(e, (u8 *)data);
  attach_dev_tmp = dup_string(e, (u8 *)data->attach_dev);
  indx1 = 0;
  p->attach_dev = attach_dev_tmp;
  do
  {
    e->ifc = 0;
    indx2 = indx1 + 1;
    attachres1 = put_attach(e, data, indx1 + 1);
    linkres1 = attachres1;
    if ( attachres1 < 0 && attachres1 != -100 )
      break;
    linkres1 = root_link(e, indx2);
    if ( linkres1 < 0 )
      break;
    indx1 = indx2;
  }
  while ( indx2 < 2 );
  result = -2;
  if ( !e->alloc_err )
    return linkres1;
  return result;
}

//----- (00401CB4) --------------------------------------------------------
int sceNetcnfifWriteEnv(sceNetCnfEnv_t *e, sceNetcnfifData_t *data, int type)
{
  int retres1; // $s0
  void *ptraligned; // $v0

  retres1 = 0;
  if ( type )
  {
    if ( type < 0 || type >= 3 )
    {
      printf("[%s] unknown type (%d)\n", "sceNetcnfifWriteEnv", type);
    }
    else
    {
      retres1 = put_attach(e, data, type);
      if ( retres1 < 0 )
        return retres1;
      retres1 = root_link(e, type);
    }
  }
  else
  {
    retres1 = put_net(e, data);
  }
  if ( retres1 >= 0 )
  {
    ptraligned = (void *)(((int)e->mem_ptr + 3) & 0xFFFFFFFC);
    e->mem_ptr = ptraligned;
    e->mem_base = ptraligned;
  }
  return retres1;
}

//----- (00401D70) --------------------------------------------------------
int sceNetcnfifSendEE(unsigned int data, unsigned int addr, unsigned int size)
{
  int dmatid; // $s0
  int result; // $v0
  SifDmaTransfer_t dmat; // [sp+10h] [-10h] BYREF

  dmat.src = (void *)data;
  dmat.dest = (void *)addr;
  dmat.size = size & 0xFFFFFFC0;
  if ( (size & 0x3F) != 0 )
    dmat.size = (size & 0xFFFFFFC0) + 64;
  dmat.attr = 0;
  do
  {
    CpuSuspendIntr(&oldstat);
    dmatid = sceSifSetDma(&dmat, 1);
    CpuResumeIntr(oldstat);
    result = dmatid;
  }
  while ( !dmatid );
  return result;
}

//----- (00401DE4) --------------------------------------------------------
int sceNetcnfifDmaCheck(int id)
{
  return sceSifDmaStat(id) >= 0;
}

//----- (00401E10) --------------------------------------------------------
void sce_callback_initialize(void)
{
  int ind; // $v0

  while ( 1 )
  {
    if ( sceSifBindRpc(&gcd, 0x80001101, 0) < 0 )
    {
      while ( 1 )
        ;
    }
    while ( sceSifCheckStatRpc(&gcd) )
      ;
    if ( gcd.server )
      break;
    ind = 0xFFFE;
    while ( ind-- != -1 )
      ;
  }
}

//----- (00401E94) --------------------------------------------------------
int sce_callback_open(const char *device, const char *pathname, int flags, int mode, int *filesize)
{
  size_t pathname_len_0; // $v0
  size_t devicelen; // $s1
  const char *device_1; // $a1
  size_t pathname_len_1; // $s0
  size_t pathnamelen; // $s2
  bool condtmp1; // dc
  int result; // $v0

  gbuf[0] = flags;
  gbuf[1] = mode;
  devicelen = strlen(device) + 1;
  pathname_len_0 = strlen(pathname);
  device_1 = device;
  pathname_len_1 = pathname_len_0;
  pathnamelen = pathname_len_0 + 1;
  gbuf[2] = devicelen;
  gbuf[3] = pathname_len_0 + 1;
  memcpy(&gbuf[4], device_1, devicelen);
  memcpy((char *)&gbuf[4] + devicelen, pathname, pathnamelen);
  condtmp1 = sceSifCallRpc(&gcd, 12, 0, gbuf, (pathname_len_1 + devicelen + 80) & 0xFFFFFFC0, gbuf, 64, 0, 0) < 0;
  result = -1;
  if ( !condtmp1 )
  {
    *filesize = gbuf[1];
    return gbuf[0];
  }
  return result;
}
// 405678: using guessed type int gbuf[1024];

//----- (00401F88) --------------------------------------------------------
int sce_callback_read(int fd, const char *device, const char *pathname, void *buf, int offset, int size)
{
  size_t pathname_len_0; // $v0
  size_t devicelen; // $s1
  const char *device_1; // $a1
  size_t pathname_len_1; // $s0
  size_t pathnamelen; // $s2

  gbuf[0] = fd;
  devicelen = strlen(device) + 1;
  pathname_len_0 = strlen(pathname);
  device_1 = device;
  pathname_len_1 = pathname_len_0;
  pathnamelen = pathname_len_0 + 1;
  gbuf[1] = devicelen;
  gbuf[2] = pathname_len_0 + 1;
  gbuf[3] = offset;
  gbuf[4] = size;
  memcpy(&gbuf[5], device_1, devicelen);
  memcpy((char *)&gbuf[5] + devicelen, pathname, pathnamelen);
  if ( sceSifCallRpc(
         &gcd,
         13,
         0,
         gbuf,
         (pathname_len_1 + devicelen + 84) & 0xFFFFFFC0,
         gbuf,
         (size + 67) & 0xFFFFFFC0,
         0,
         0) < 0 )
    return -1;
  memcpy(buf, &gbuf[1], size);
  return gbuf[0];
}
// 405678: using guessed type int gbuf[1024];

//----- (004020B4) --------------------------------------------------------
int sce_callback_close(int fd)
{
  bool condtmp; // dc
  int result; // $v0

  gbuf[0] = fd;
  condtmp = sceSifCallRpc(&gcd, 14, 0, gbuf, 64, gbuf, 64, 0, 0) < 0;
  result = -1;
  if ( !condtmp )
    return gbuf[0];
  return result;
}
// 405678: using guessed type int gbuf[1024];

//----- (00402120) --------------------------------------------------------
int my_create_heap(void)
{
  int result; // $v0

  if ( g_heap )
    return -2;
  g_heap = CreateHeap(1024, 1);
  result = -1;
  if ( g_heap )
    return 0;
  return result;
}

//----- (00402170) --------------------------------------------------------
void *my_alloc(int size)
{
  return AllocHeapMemory(g_heap, size);
}

//----- (0040219C) --------------------------------------------------------
void my_free(void *ptr)
{
  if ( ptr )
    FreeHeapMemory(g_heap, ptr);
}

//----- (004021CC) --------------------------------------------------------
void my_delete_heap(void)
{
  DeleteHeap(g_heap);
  g_heap = 0;
}
