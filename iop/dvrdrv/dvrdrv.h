
int DvrdrvResetSystem();
int DvrdrvEnableIntr(u16 a1);
int DvrdrvDisableIntr(u16 a1);
int DvrdrvRegisterIntrHandler(int a1, int a2, void (*a3)(int, int));
int DvrdrvUnregisterIntrHandler(void (*a1)(int, int));
int DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1);
int DvrdrvExecCmdAckComp(drvdrv_exec_cmd_ack *a1);
int DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1);
int DvrdrvExecCmdAckDmaRecvComp(drvdrv_exec_cmd_ack *a1);
int DvrdrvExecCmdAckDma2Comp(drvdrv_exec_cmd_ack *a1);


struct __attribute__((aligned(4))) drvdrv_exec_cmd_ack
{
  u16 command;
  u16 input_word[64];
  u32 input_word_count;
  u16 field_88;
  u16 ack_status;
  u16 output_word[64];
  u32 field_10C;
  u8 field_110;
  u8 field_111;
  u16 comp_status;
  u16 return_result_word[64];
  s32 field_194;
  u32 timeout;
  u32 input_buffer;
  u32 input_buffer_length;
  u32 output_buffer;
  s32 field_1A8;
  s32 phase;
};

struct __attribute__((packed)) __attribute__((aligned(1))) struct_itr_sid_tbl
{
  u16 word0;
  u8 gap2[2];
  u32 dword4;
  u16 word8;
  u8 byteA;
  u8 byteB;
};

#define pvrdrv_IMPORTS_start DECLARE_IMPORT_TABLE(pvrdrv, 1, 1)
#define pvrdrv_IMPORTS_end END_IMPORT_TABLE

#define I_DvrdrvResetSystem DECLARE_IMPORT(4, DvrdrvResetSystem)
#define I_DvrdrvEnableIntr DECLARE_IMPORT(5, DvrdrvEnableIntr)
#define I_DvrdrvDisableIntr DECLARE_IMPORT(6, DvrdrvDisableIntr)
#define I_DvrdrvRegisterIntrHandler DECLARE_IMPORT(7, DvrdrvRegisterIntrHandler)
#define I_DvrdrvUnregisterIntrHandler DECLARE_IMPORT(8, DvrdrvUnregisterIntrHandler)
#define I_DvrdrvExecCmdAck DECLARE_IMPORT(9, DvrdrvExecCmdAck)
#define I_DvrdrvExecCmdAckComp DECLARE_IMPORT(10, DvrdrvExecCmdAckComp)
#define I_DvrdrvExecCmdAckDmaSendComp DECLARE_IMPORT(11, DvrdrvExecCmdAckDmaSendComp)
#define I_DvrdrvExecCmdAckDmaRecvComp DECLARE_IMPORT(12, DvrdrvExecCmdAckDmaRecvComp)
#define I_DvrdrvExecCmdAckDma2Comp DECLARE_IMPORT(13, DvrdrvExecCmdAckDma2Comp)
