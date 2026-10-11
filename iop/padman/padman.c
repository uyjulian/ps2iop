
#include <irx_imports.h>
#include <xpadman.h>

#define __fastcall
#define __cdecl
#define __noreturn
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
#define _BYTE u8
#define _WORD u16
#define _DWORD u32

#define padInit padInit_
#define padPortOpen padPortOpen_
#define padSetupEEButtonData padSetupEEButtonData_

typedef struct sio2Cmds_
{
	u8 id;
	u8 pad[3];
	void (__cdecl *readdata)(u8 *);
	u32 (__cdecl *getportctrl1)(u32, u32);
	u32 (__cdecl *getportctrl2)(u32);
	u32 (*reg_data)(void);
	u32 (*size1)(void);
	u32 (*size2)(void);
	u32 (__cdecl *enterconfigmode)(u8 *);
	u32 (__cdecl *exitconfigmode)(u8 *);
	u32 (__cdecl *querymodel)(u8 *);
	u32 (__cdecl *queryact)(u8 *);
	u32 (__cdecl *querycomb)(u8 *);
	u32 (__cdecl *querymode)(u8 *);
	u32 (__cdecl *querybuttonmask)(u8 *);
	u32 (__cdecl *setbuttoninfo)(u8 *);
	u32 (__cdecl *setvrefparam)(u8 *);
	u32 (__cdecl *setmainmode)(u8 *);
	u32 (__cdecl *setactalign)(u8 *);
} sio2Cmds_t;

typedef struct padData_
{
	u32 active;
	u32 unused_4;
	u32 unused_8;
	u32 stat70bit;
	u32 in_size;
	u32 out_size;
	u8 in_buffer[32];
	u8 out_buffer[32];
	u32 port_ctrl1;
	u32 port_ctrl2;
	u32 reg_data;
	u32 error;
} padData_t;

typedef struct vblankData_
{
	int padEnd;
	int eventflag;
	int init;
	int stopTransfer;
	int tid_1;
	int tid_2;
} vblankData_t;

typedef struct ee_paddata_
{
	u8 data[32];
	u32 actDirData[2];
	u32 actAlignData[2];
	u32 actData[4];
	u32 combData[4];
	u32 modeTable[2];
	u32 frame;
	u32 findPadRetries;
	u32 length;
	u8 modeConfig;
	u8 modeCurId;
	u8 model;
	u8 buttonDataReady;
	u8 nrOfModes;
	u8 modeCurOffs;
	u8 nrOfActuators;
	u8 numActComb;
	u8 val_c6;
	u8 mode;
	u8 lock;
	u8 actDirSize;
	u8 state;
	u8 reqState;
	u8 currentTask;
	u8 runTask;
	u8 stat70bit;
	u8 padding[11];
} ee_paddata_t;

struct libpad_dma_act_direct_state
{
	u32 m_frame;
	u32 m_unhandled;
	u32 m_unused;
	u8 m_actdata[6];
	u8 m_padding[14];
};

typedef struct padstate_
{
	__attribute__((aligned(4))) ee_paddata_t ee_pdata;
	struct libpad_dma_act_direct_state m_dma_act_direct_state[2];
	u8 modeConfig;
	u8 modeCurId;
	u8 model;
	u8 numModes;
	u8 modeCurOffs;
	u8 numActuators;
	u8 numActComb;
	u8 disconnected;
	u8 actData[4][4];
	u8 combData[4][4];
	u16 modeTable[4];
	u8 buttonInfo[4];
	u8 buttonMask[4];
	u8 modeParam[4];
	u8 m_xpadding[10];
	u16 val_c6;
	u8 inbuffer[32];
	u8 outbuffer[32];
	u8 buttonStatus[32];
	u16 buttonDataReady;
	u8 mode;
	u8 lock;
	u8 ee_actDirectData[6];
	u16 m_unused172;
	u16 ee_actDirectSize;
	u8 ee_actAlignData[6];
	u16 state;
	u16 reqState;
	u32 frame;
	u32 padarea_ee_addr;
	u32 findPadRetries;
	s32 updatepadTid;
	s32 querypadTid;
	u32 m_unused194;
	s32 setmainmodeTid;
	s32 setactalignTid;
	s32 setbuttoninfoTid;
	s32 setvrefparamTid;
	int eventflag;
	u16 port;
	u16 slot;
	u16 currentTask;
	u16 runTask;
	u32 taskTid;
	u32 stat70bit;
	u32 m_unused1bc;
	u32 m_close_wait_blocking;
} padState_t;

// Based on the module from SDK 3.1.0
IRX_ID("padman", 4, 34);

//-------------------------------------------------------------------------
// Function declarations

u32 __fastcall ApplyActDirectFromDmaBuf(padState_t *pstate);
void __cdecl WaitClearEvent(int eventflag, u32 bits);
s32 __cdecl VbReferThreadStatus(vblankData_t *vData);
void __cdecl DeleteThreadsEventFlag(vblankData_t *vbdat);
u32 __cdecl GetThreadsStatus(padState_t *state);
void __cdecl DeleteThreads(padState_t *state);
void __cdecl ee_dma_send_completion_cb(void *userdata);
void DmaSendEE(void);
void __cdecl shiftarray(u8 *buf);
int __cdecl VblankEnd(void *arg);
int __cdecl VblankStart(vblankData_t *vData);
void __cdecl __noreturn TransferThread(void *arg);
void __cdecl __noreturn MainThread(void *arg);
u32 __cdecl ReadData(padState_t *pstate);
u32 __cdecl PadIsSupported(padState_t *pstate);
u32 __cdecl EnterConfigMode(u8 val, padState_t *pstate);
u32 __cdecl ExitConfigMode(padState_t *pstate);
u32 __cdecl SetMainMode(padState_t *pstate);
u32 __cdecl SetActAlign(padState_t *pstate);
u32 __cdecl QueryModel(padState_t *pstate);
u32 __cdecl QueryAct(u32 actuator, padState_t *pstate);
u32 __cdecl QueryComb(u32 val, padState_t *pstate);
u32 __cdecl QueryMode(u32 val, padState_t *pstate);
u32 __cdecl VrefParam(u32 val, padState_t *pstate);
u32 __cdecl QueryButtonMask(padState_t *pstate);
u32 __cdecl SetButtonInfo(padState_t *pstate);
u32 __cdecl ActDirectTotal(u32 port, u32 slot);
u32 __cdecl CheckAirDirectTotal(u32 port, u32 slot, u8 *actData);
void __cdecl UpdatePadThread(void *arg);
void __cdecl QueryPadThread(void *arg);
void __cdecl SetMainModeThread(void *arg);
void __cdecl SetActAlignThread(void *arg);
void __cdecl SetButtonInfoThread(void *arg);
void __cdecl SetVrefParamThread(void *arg);
void __cdecl do_set_timer(int timer_mode, u32 timer_compare);
int __cdecl ParseParams(int argc, char *argv[]);
s32 __cdecl padInit(void *ee_addr, int timer_interval);
s32 __cdecl padEnd();
s32 __cdecl padPortOpen(s32 port, s32 slot, s32 pad_area_ee_addr, struct libpad_dma_act_direct_state **buf);
s32 __cdecl padPortClose(s32 port, s32 slot, s32 wait);
u32 __cdecl padSetupEEButtonData(u32 port, u32 slot, padState_t *pstate);
u32 __cdecl padGetModeConfig(u32 port, u32 slot);
s32 __cdecl padInfoAct(u32 port, u32 slot, s32 act, u32 val);
s32 __cdecl padInfoComb(u32 port, u32 slot, s32 val1, u32 val2);
s32 __cdecl padInfoMode(u32 port, u32 slot, s32 val1, u32 val2);
u32 __cdecl padSetActDirect(u32 port, u32 slot, u8 *actData);
u32 __cdecl padSetMainMode(u32 port, u32 slot, u32 mode, u32 lock);
u32 __cdecl padSetActAlign(u32 port, u32 slot, const u8 *actData);
u32 __cdecl padSetVrefParam(u32 port, u32 slot, const u8 *vparam);
u32 __cdecl padSetButtonInfo(u32 port, u32 slot, u32 info);
u32 __cdecl padGetButtonMask(u32 port, u32 slot);
u32 padGetPortMax(void);
u32 __cdecl padGetSlotMax(u32 port);
int padGetVersion(void);
int __cdecl padSetVerbose(int val);
int __cdecl padSetNonblockDma(int val);
u32 __cdecl readStat6cBit(u32 bit, sio2_transfer_data_t *td);
void pdReset(void);
void __cdecl do_set_unused_4_pad(int port, int slot, u32 val);
u32 __cdecl pdSetActive(u32 port, u32 slot, u32 active);
u32 __cdecl pdIsActive(u32 port, u32 slot);
u32 __cdecl pdSetStat70bit(u32 port, u32 slot, u32 val);
u32 __cdecl pdGetStat70bit(u32 port, u32 slot);
u32 __cdecl setupTransferData(u32 index, u32 port, u32 slot);
u32 __cdecl readSio2OutBuffer(u32 bit, u32 port, u32 slot);
u32 __cdecl padTransfer(u32 slot);
u32 __cdecl mtapChangeSlot(u32 slot);
void pdTransfer(void);
u32 __cdecl pdSetCtrl1(u32 port, u32 slot, u32 ctrl);
u32 __cdecl pdSetCtrl2(u32 port, u32 slot, u32 ctrl);
u32 __cdecl pdSetRegData(u32 port, u32 slot, u32 reg_data);
s32 __cdecl pdGetError(u32 port, u32 slot);
u32 __cdecl pdSetInSize(u32 port, u32 slot, u32 size);
u32 __cdecl pdSetInBuffer(u32 port, u32 slot, u32 size, const u8 *buf);
u32 __cdecl pdSetOutSize(u32 port, u32 slot, u32 size);
u32 __cdecl pdGetOutBuffer(u32 port, u32 slot, u32 size, u8 *buf);
int __fastcall unusedref_4055A0(unsigned int port, u32 slot, u32 port_ctrl);
int __fastcall unusedref_405680(u32 port, u32 slot);
int __fastcall unused_4057D4(u32 port, s32 slot);
void sio2cmdReset(void);
int __cdecl SetupCmds(const sio2Cmds_t *s);
u32 __cdecl sio2cmdCheckId(u8 id);
void __cdecl sio2CmdSetReadData(u32 id, u8 *buf);
u32 __cdecl sio2CmdGetPortCtrl1(u8 id, u32 b, u8 c);
u32 __cdecl sio2CmdGetPortCtrl2(u32 id, u32 b);
u32 __cdecl pdGetInSize(u8 id);
u32 __cdecl pdGetOutSize(u8 id);
u32 __cdecl pdGetRegData(u32 id);
u32 __cdecl sio2CmdSetEnterConfigMode(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetExitConfigMode(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetQueryModel(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetQueryAct(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetQueryComb(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetQueryMode(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetQueryButtonMask(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetSetButtonInfo(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetSetVrefParam(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetSetMainMode(u32 id, u8 *buf);
u32 __cdecl sio2CmdSetSetActAlign(u32 id, u8 *buf);
void __cdecl FindPadsReadData(u8 *a);
u32 __cdecl FindPadsGetPortCtrl1(u32 a, u32 b);
u32 __cdecl FindPadsGetPortCtrl2(u32 a);
u32 FindPadsGetSize1(void);
u32 FindPadsGetSize2(void);
u32 FindPadsRegData(void);
u32 __cdecl FindPadsEnterConfigMode(u8 *a);
void sio2cmdInitFindPads(void);
void __cdecl MouseReadData(u8 *a);
u32 __cdecl MouseGetPortCtrl1(u32 a, u32 b);
u32 __cdecl MouseGetPortCtrl2(u32 a);
u32 MouseRegData(void);
u32 MouseSize1(void);
u32 MouseSize2(void);
u32 __cdecl MouseEnterConfigMode(u8 *a);
void sio2cmdInitMouse(void);
void __cdecl DigitalReadData(u8 *a);
u32 __cdecl DigitalGetPortCtrl1(u32 a, u32 b);
u32 __cdecl DigitalGetPortCtrl2(u32 a);
u32 DigitalRegData(void);
u32 DigitalSize1(void);
u32 DigitalSize2(void);
u32 __cdecl DigitalEnterConfigMode(u8 *a);
void sio2cmdInitDigital(void);
void __cdecl AnalogReadData(u8 *a);
u32 __cdecl AnalogGetPortCtrl1(u32 a, u32 b);
u32 __cdecl AnalogGetPortCtrl2(u32 a);
u32 __cdecl AnalogEnterConfigMode(u8 *a);
void sio2cmdInitAnalog(void);
void __cdecl NegiconReadData(u8 *a);
u32 __cdecl NegiconGetPortCtrl1(u32 a, u32 b);
u32 __cdecl NegiconGetPortCtrl2(u32 a);
u32 NegiconRegData(void);
u32 NegiconSize1(void);
u32 NegiconSize2(void);
u32 __cdecl NegiconEnterConfigMode(u8 *a);
void sio2cmdInitNegicon(void);
void __cdecl JoystickReadData(u8 *a);
u32 __cdecl JoystickGetPortCtrl1(u32 a, u32 b);
u32 __cdecl JoystickGetPortCtrl2(u32 a);
u32 JoystickRegData(void);
u32 JoystickSize1(void);
u32 JoystickSize2(void);
u32 __cdecl JoystickEnterConfigMode(u8 *a);
void sio2cmdInitJoystick(void);
void __cdecl KonamiGunReadData(u8 *a);
u32 __cdecl KonamiGunGetPortCtrl1(u32 a, u32 b);
u32 __cdecl KonamiGunGetPortCtrl2(u32 a);
u32 KonamiGunRegData(void);
u32 KonamiGunSize1(void);
u32 KonamiGunSize2(void);
u32 __cdecl KonamiGunEnterConfigMode(u8 *a);
void sio2cmdInitKonamiGun(void);
void __cdecl NamcoGunReadData(u8 *a);
u32 __cdecl NamcoGunGetPortCtrl1(u32 a, u32 b);
u32 __cdecl NamcoGunGetPortCtrl2(u32 a);
u32 NamcoGunRegData(void);
u32 NamcoGunSize1(void);
u32 NamcoGunSize2(void);
u32 __cdecl NamcoGunEnterConfigMode(u8 *a);
void sio2cmdInitNamcoGun(void);
void __cdecl JogconReadData(u8 *a);
u32 __cdecl JogconGetPortCtrl1(u32 a, u32 b);
u32 __cdecl JogconGetPortCtrl2(u32 a);
u32 JogconRegData(void);
u32 JogconSize1(void);
u32 JogconSize2(void);
u32 __cdecl JogconEnterConfigMode(u8 *a);
void sio2cmdInitJogcon(void);
void __cdecl ConfigReadData(u8 *a);
u32 __cdecl ConfigGetPortCtrl1(u32 a, u32 b);
u32 __cdecl ConfigGetPortCtrl2(u32 a);
u32 ConfigRegData(void);
u32 ConfigSize1(void);
u32 ConfigSize2(void);
u32 __cdecl ConfigExitConfigMode(u8 *a);
u32 __cdecl ConfigQueryModel(u8 *a);
u32 __cdecl ConfigQueryAct(u8 *a);
u32 __cdecl ConfigQueryComb(u8 *a);
u32 __cdecl ConfigQueryMode(u8 *a);
u32 __cdecl ConfigQueryButtonMask(u8 *a);
u32 __cdecl ConfigSetButtonInfo(u8 *a);
u32 __cdecl ConfigSetVrefParam(u8 *a);
u32 __cdecl ConfigSetMainMode(u8 *a);
u32 __cdecl ConfigSetSetActAlign(u8 *a);
void sio2cmdInitConfig(void);
void *__cdecl RpcPadInit(u32 *data);
void *__cdecl RpcPadEnd(u32 *data);
void *__cdecl RpcSetVerbose(u32 *data);
void *__cdecl RpcGetModVersion(u32 *data);
void *__cdecl RpcPadOpen(u32 *data);
void *__cdecl RpcPadClose(u32 *data);
void *__cdecl RpcPadInfoAct(u32 *data);
void *__cdecl RpcPadInfoComb(u32 *data);
void *__cdecl RpcPadInfoMode(u32 *data);
void *__cdecl RpcPadSetMainMode(u32 *data);
void *__cdecl RpcPadSetActDirect(u32 *data);
void *__cdecl RpcPadSetActAlign(u32 *data);
void *__cdecl RpcPadGetButtonMask(u32 *data);
void *__cdecl RpcPadSetButtonInfo(u32 *data);
void *__cdecl RpcPadSetVrefParam(u32 *data);
void *__cdecl RpcPadGetPortMax(u32 *data);
void *__cdecl RpcPadGetSlotMax(u32 *data);
void *__cdecl RpcSetNonblockDma(u32 *a1);
void *__cdecl RpcServer(int fno, void *buffer, int length);
void __cdecl RpcThread(void *arg);
void *__cdecl RpcServerExt(int fno, void *buffer, int length);
void __cdecl RpcThreadExt(void *arg);
int __cdecl InitRpcServers(int prio);

//-------------------------------------------------------------------------
// Data declarations

extern struct irx_export_table _exp_padman;
int g_padman_verbose = 1; // weak
int vblankStartCount = 0; // weak
int frame_count = 0; // weak
int mainThreadCount = 0; // weak
int transferCount = 0; // weak
int vblank_end; // weak
SifDmaTransfer_t sifdma_td[16];
int g_dma_buf[4]; // weak
padState_t g_pad_state[2][4];
int openSlots[2]; // weak
vblankData_t vblankdata; // weak
int g_readxfertimer_timid; // idb
int g_readxfertimer_irq; // idb
int padman_init; // weak
int g_padman_unk_40928C; // weak
int g_padman_ee_addr; // weak
int thpri_hi; // weak
int thpri_lo; // idb
int g_padman_nonblock_dma; // weak
int g_readxfertimer_val; // weak
int sifdma_id; // weak
int g_sema; // weak
padData_t padData[2][4];
sio2_transfer_data_t sio2_td; // weak
s32 change_slot_buffer[8];
int g_td_in_buf[64]; // weak
int g_td_out_buf[66]; // weak
sio2Cmds_t sio2Cmds[16]; // weak
int numControllers; // weak
int ThreadIdRpcServer; // weak
SifRpcDataQueue_t rpc_qd; // weak
SifRpcServerData_t rpc_sd; // weak
int rpc_buf[32]; // weak
int ThreadIdRpcServerExt; // weak
SifRpcDataQueue_t rpcext_qd; // weak
SifRpcServerData_t rpcext_sd; // weak
int rpcext_buf[32]; // weak


//----- (00400000) --------------------------------------------------------
u32 __fastcall ApplyActDirectFromDmaBuf(padState_t *pstate)
{
	struct libpad_dma_act_direct_state *astate; // $s0
	u32 framecmp; // $s1

	astate = &pstate->m_dma_act_direct_state[pstate->m_dma_act_direct_state[0].m_frame < pstate->m_dma_act_direct_state[1].m_frame];
	framecmp = pstate->m_dma_act_direct_state[0].m_frame < pstate->m_dma_act_direct_state[1].m_frame;
	if ( astate->m_unhandled )
	{
		padSetActDirect(pstate->port, pstate->slot, astate->m_actdata);
		astate->m_unhandled = 0;
	}
	return framecmp;
}

//----- (0040006C) --------------------------------------------------------
void __cdecl WaitClearEvent(int eventflag, u32 bits)
{
	iop_thread_info_t tinfo; // [sp+10h] [-50h] BYREF
	u32 resbits[2]; // [sp+58h] [-8h] BYREF

	WaitEventFlag(eventflag, bits | 0x1000, 1, resbits);
	if ( (resbits[0] & 0x1000) != 0 )
	{
		ReferThreadStatus(0, &tinfo);
		SetEventFlag(eventflag, 0x1000u);
		ExitThread();
	}
	ClearEventFlag(eventflag, ~bits);
}
// 40006C: using guessed type iop_thread_info_t tinfo;

//----- (004000E4) --------------------------------------------------------
s32 __cdecl VbReferThreadStatus(vblankData_t *vData)
{
	u32 ret2; // $s0
	iop_thread_info_t tinfo; // [sp+10h] [-48h] BYREF

	ret2 = 0;
	if ( !iReferThreadStatus(vData->tid_1, &tinfo) )
		ret2 = (tinfo.status & 0x10) == 0;
	if ( !(iReferThreadStatus(vData->tid_2, &tinfo) != 0) )
	{
		if ( (tinfo.status & 0x10) == 0 )
			return ret2 + 1;
	}
	return ret2;
}

//----- (00400164) --------------------------------------------------------
void __cdecl DeleteThreadsEventFlag(vblankData_t *vbdat)
{
	DeleteThread(vbdat->tid_1);
	DeleteThread(vbdat->tid_2);
	DeleteEventFlag(vbdat->eventflag);
}

//----- (004001A8) --------------------------------------------------------
u32 __cdecl GetThreadsStatus(padState_t *state)
{
	int count; // $s0
	iop_thread_info_t tinfo; // [sp+10h] [-48h] BYREF

	count = 0;
	if ( !ReferThreadStatus(state->updatepadTid, &tinfo) )
		count = (tinfo.status & 0x10) == 0;
	if ( !ReferThreadStatus(state->querypadTid, &tinfo) && (tinfo.status & 0x10) == 0 )
		++count;
	if ( !ReferThreadStatus(state->setmainmodeTid, &tinfo) && (tinfo.status & 0x10) == 0 )
		++count;
	if ( !ReferThreadStatus(state->setactalignTid, &tinfo) && (tinfo.status & 0x10) == 0 )
		++count;
	if ( !ReferThreadStatus(state->setbuttoninfoTid, &tinfo) && (tinfo.status & 0x10) == 0 )
		++count;
	if ( !(ReferThreadStatus(state->setvrefparamTid, &tinfo) != 0) )
	{
		if ( (tinfo.status & 0x10) == 0 )
			return count + 1 < 1;
	}
	return count < 1;
}

//----- (004002D8) --------------------------------------------------------
void __cdecl DeleteThreads(padState_t *state)
{
	DeleteThread(state->updatepadTid);
	DeleteThread(state->querypadTid);
	DeleteThread(state->setmainmodeTid);
	DeleteThread(state->setactalignTid);
	DeleteThread(state->setbuttoninfoTid);
	DeleteThread(state->setvrefparamTid);
}

//----- (00400340) --------------------------------------------------------
void __cdecl ee_dma_send_completion_cb(void *userdata)
{
	iSignalSema((int)userdata);
}

//----- (00400360) --------------------------------------------------------
void DmaSendEE(void)
{
	int dmat_count_2; // $s7
	int dma_stat; // $a2
	signed __int32 port; // $t8
	signed __int32 slot; // $s5
	int xidx; // $fp
	void **p_dest; // $s6
	padState_t *p; // $s4
	u32 frame_tmp; // $v1
	u32 findPadRetries; // $a0
	u8 modeConfig; // $a1
	u8 modeCurId; // $a2
	u8 model; // $a3
	u8 buttonDataReady; // $t0
	u8 numModes; // $t1
	u8 modeCurOffs; // $t3
	u8 numActuators; // $t4
	u8 numActComb; // $t9
	u8 buttonstatus_tmp; // $t5
	u8 mode; // $t6
	u8 lock; // $t7
	u8 ee_actDirectSize; // $s0
	u8 state_1; // $s1
	u8 reqState; // $s2
	u8 currentTask; // $s3
	int tmp1; // $s1
	u32 directtmp; // $t3
	u32 aligntmp; // $t3
	u32 acttmp1; // $t3
	u32 acttmp2; // $t4
	u32 acttmp3; // $t9
	u32 combtmp1; // $t3
	u32 combtmp2; // $t4
	u32 combtmp3; // $t9
	int readytmp; // $v1
	u32 padarea_ee_addr; // $v0
	int dmat_count_1; // $v1
	int trid3; // $s0
	int trid2; // $s0
	int trid1; // $s0
	int state; // [sp+20h] [-20h] BYREF
	int *slotptr; // [sp+24h] [-1Ch]
	int xstate1; // [sp+28h] [-18h]
	int port_tmp1; // [sp+30h] [-10h]
	int xstate2; // [sp+38h] [-8h]

	dmat_count_2 = 0;
	state = 0;
	if ( sifdma_id )
	{
		dma_stat = sceSifDmaStat(sifdma_id);
		port = 0;
		if ( dma_stat >= 0 )
		{
			if ( g_padman_verbose )
			{
#ifdef FIXME
				if ( vblankStartCount == 240 * (vblankStartCount / 240) )
				{
					Kprintf("padman: DMA Busy ID = %08x ret = %d\n", sifdma_id, dma_stat);
					Kprintf("        SB_STAT = %08x\n", MEMORY[0xBD000040]);
				}
#endif
			}
			return;
		}
	}
	else
	{
		port = 0;
	}
	xstate2 = 0;
	do
	{
		slot = 0;
		xidx = 0;
		p_dest = &sifdma_td[dmat_count_2].dest;
		slotptr = &openSlots[port];
		xstate1 = xstate2;
		do
		{
			if ( ((*slotptr >> slot) & 1) != 0 )
			{
				p = (padState_t *)((char *)&g_pad_state[0][xidx] + xstate1);
				frame_tmp = p->frame;
				findPadRetries = p->findPadRetries;
				modeConfig = p->modeConfig;
				modeCurId = p->modeCurId;
				model = p->model;
				buttonDataReady = p->buttonDataReady;
				numModes = p->numModes;
				modeCurOffs = p->modeCurOffs;
				numActuators = p->numActuators;
				numActComb = p->numActComb;
				buttonstatus_tmp = p->val_c6;
				mode = p->mode;
				lock = p->lock;
				ee_actDirectSize = p->ee_actDirectSize;
				state_1 = p->state;
				reqState = p->reqState;
				currentTask = p->currentTask;
				p->ee_pdata.frame = frame_tmp;
				p->ee_pdata.modeCurOffs = modeCurOffs;
				p->ee_pdata.nrOfActuators = numActuators;
				p->ee_pdata.numActComb = numActComb;
				p->frame = frame_tmp + 1;
				p->ee_pdata.findPadRetries = findPadRetries;
				p->ee_pdata.modeConfig = modeConfig;
				p->ee_pdata.modeCurId = modeCurId;
				p->ee_pdata.model = model;
				p->ee_pdata.buttonDataReady = buttonDataReady;
				p->ee_pdata.nrOfModes = numModes;
				p->ee_pdata.val_c6 = buttonstatus_tmp;
				p->ee_pdata.mode = mode;
				p->ee_pdata.lock = lock;
				p->ee_pdata.actDirSize = ee_actDirectSize;
				p->ee_pdata.state = state_1;
				p->ee_pdata.reqState = reqState;
				p->ee_pdata.currentTask = currentTask;
				tmp1 = frame_tmp & 1;
				p->ee_pdata.runTask = p->runTask;
				directtmp = *(_DWORD *)&p->ee_actDirectData[4];
				p->ee_pdata.actDirData[0] = *(_DWORD *)p->ee_actDirectData;
				p->ee_pdata.actDirData[1] = directtmp;
				aligntmp = *(_DWORD *)&p->ee_actAlignData[4];
				p->ee_pdata.actAlignData[0] = *(_DWORD *)p->ee_actAlignData;
				p->ee_pdata.actAlignData[1] = aligntmp;
				acttmp1 = *(_DWORD *)&p->actData[1][0];
				acttmp2 = *(_DWORD *)&p->actData[2][0];
				acttmp3 = *(_DWORD *)&p->actData[3][0];
				p->ee_pdata.actData[0] = *(_DWORD *)&p->actData[0][0];
				p->ee_pdata.actData[1] = acttmp1;
				p->ee_pdata.actData[2] = acttmp2;
				p->ee_pdata.actData[3] = acttmp3;
				combtmp1 = *(_DWORD *)&p->combData[1][0];
				combtmp2 = *(_DWORD *)&p->combData[2][0];
				combtmp3 = *(_DWORD *)&p->combData[3][0];
				p->ee_pdata.combData[0] = *(_DWORD *)&p->combData[0][0];
				p->ee_pdata.combData[1] = combtmp1;
				p->ee_pdata.combData[2] = combtmp2;
				p->ee_pdata.combData[3] = combtmp3;
				memcpy(&p->ee_pdata.modeTable[0], &p->modeTable[0], sizeof(p->ee_pdata.modeTable));
				*(_DWORD *)&p->ee_pdata.padding[4] = *(_DWORD *)p->buttonMask;
				*(_DWORD *)p->ee_pdata.padding = *(_DWORD *)p->buttonInfo;
				readytmp = p->buttonDataReady;
				p->ee_pdata.stat70bit = p->stat70bit;
				if ( readytmp == 1 )
				{
					port_tmp1 = port;
					p->ee_pdata.length = padSetupEEButtonData(port, slot, p);
					port = port_tmp1;
				}
				else
				{
					p->ee_pdata.length = 0;
				}
				padarea_ee_addr = p->padarea_ee_addr;
				dmat_count_1 = dmat_count_2;
				*p_dest = (void *)padarea_ee_addr;
				if ( tmp1 )
					*p_dest = (void *)(padarea_ee_addr + 128);
				p_dest += 4;
				++dmat_count_2;
				sifdma_td[dmat_count_1].src = p;
				sifdma_td[dmat_count_1].size = 128;
				sifdma_td[dmat_count_1].attr = 0;
			}
			++slot;
			++xidx;
		}
		while ( slot < 4 );
		++port;
		xstate2 += 1808;
	}
	while ( port < 2 );
	if ( dmat_count_2 )
	{
		if ( g_padman_nonblock_dma == 1 )
		{
			CpuSuspendIntr(&state);
			trid3 = sceSifSetDmaIntr(sifdma_td, dmat_count_2, ee_dma_send_completion_cb, (void *)g_sema);
			sifdma_id = trid3;
			CpuResumeIntr(state);
			if ( trid3 )
			{
				WaitSema(g_sema);
				if ( sceSifDmaStat(trid3) >= 0 && g_padman_verbose >= 2 )
					Kprintf("padman: SIFDMA PANIC!\n");
				CpuSuspendIntr(&state);
				g_dma_buf[3] = vblankStartCount;
				trid2 = sceSifSendCmdIntr(0x80000019, g_dma_buf, 16, NULL, NULL, 0, ee_dma_send_completion_cb, (void *)g_sema);
				sifdma_id = trid2;
				CpuResumeIntr(state);
				if ( trid2 )
				{
					WaitSema(g_sema);
					if ( sceSifDmaStat(trid2) >= 0 && g_padman_verbose >= 2 )
						Kprintf("padman: SIFCMD PANIC!\n");
				}
				else if ( g_padman_verbose >= 2 )
				{
					Kprintf("padman: SIFCMD faild\n");
				}
				return;
			}
		}
		else
		{
			CpuSuspendIntr(&state);
			trid1 = sceSifSetDma(sifdma_td, dmat_count_2);
			sifdma_id = trid1;
			CpuResumeIntr(state);
			if ( trid1 )
				return;
		}
		if ( g_padman_verbose >= 2 )
			Kprintf("padman: SIFDMA faild\n");
	}
}
// 4082F8: using guessed type int g_padman_verbose;
// 4082FC: using guessed type int vblankStartCount;
// 408430: using guessed type int g_dma_buf[4];
// 409260: using guessed type int openSlots[];
// 40929C: using guessed type int g_padman_nonblock_dma;
// 4092A4: using guessed type int sifdma_id;
// 4092A8: using guessed type int g_sema;

//----- (004008B4) --------------------------------------------------------
void __cdecl shiftarray(u8 *buf)
{
	int i1; // $a1
	u8 *tempptr1; // $v1
	u8 valtmp; // $v0
	int i; // $a1
	u8 *bufptr2; // $v1
	_BYTE *tempptr2; // $v0
	_BYTE temp[32]; // [sp+0h] [-20h] BYREF

	i1 = 0;
	tempptr1 = temp;
	do
	{
		valtmp = buf[i1++];
		*tempptr1 = valtmp;
		tempptr1 = &temp[i1];
	}
	while ( i1 < 32 );
	*buf = -1;
	for ( i = 1; i < 32; ++i )
	{
		bufptr2 = &buf[i];
		tempptr2 = &temp[i];
		*bufptr2 = *(tempptr2 - 1);
	}
}

//----- (00400910) --------------------------------------------------------
int __cdecl VblankEnd(void *arg)
{
	(void)arg;
	vblank_end = 1;
	return 1;
}
// 408320: using guessed type int vblank_end;

//----- (00400924) --------------------------------------------------------
int __cdecl VblankStart(vblankData_t *vData)
{
	int init; // $v1
	unsigned int cur_frame_count; // $a0

	vblank_end = 0;
	++vblankStartCount;
	init = vData->init;
	cur_frame_count = ++frame_count;
	if ( init )
	{
		if ( vData->stopTransfer )
		{
			if ( cur_frame_count >= 0x12C )
			{
				if ( g_padman_verbose )
					Kprintf("padman: *** VBLANK OVERLAP ***\n");
				frame_count = 0;
			}
		}
		else
		{
			vData->stopTransfer = 1;
			iSetEventFlag(vData->eventflag, 1u);
		}
	}
	if ( vData->padEnd == 1 && !VbReferThreadStatus(vData) )
		iSetEventFlag(vData->eventflag, 8u);
	return 1;
}
// 4082F8: using guessed type int g_padman_verbose;
// 4082FC: using guessed type int vblankStartCount;
// 408300: using guessed type int frame_count;
// 408320: using guessed type int vblank_end;

//----- (00400A10) --------------------------------------------------------
void __cdecl __noreturn TransferThread(void *arg)
{
	(void)arg;
	while ( 1 )
	{
		WaitClearEvent(vblankdata.eventflag, 1u);
		pdTransfer();
		SetEventFlag(vblankdata.eventflag, 4u);
	}
}
// 409268: using guessed type vblankData_t vblankdata;

//----- (00400A54) --------------------------------------------------------
void __cdecl __noreturn MainThread(void *arg)
{
	__int64 update_slots_cond; // kr00_8
	int update_shots_count_x; // $v1
	signed __int32 port; // $s3
	int pad_state_add; // $s5
	int *openslot_tmp; // $s4
	signed __int32 slot; // $s1
	int task_3_count; // $s2
	u32 port_tmp1; // $a0
	padState_t *padstate_p; // $s0
	u32 Stat70bit; // $v0
	u16 runTask; // $a2
	int eventflag; // $a0
	u16 runtask_t; // $v0
	int ef_tmp; // $a0
	u32 flag_to_set; // $a1
	signed __int32 port_2; // $s3
	int padstate_offs; // $s4
	signed __int32 slot_2; // $s1
	padState_t *padstate_p2; // $s2
	padState_t *padstate_elm; // $s0

	(void)arg;
	while ( 1 )
	{
		update_slots_cond = 0x55555556LL * (mainThreadCount + 1);
		update_shots_count_x = ++mainThreadCount >> 31;
		port = 0;
		if ( mainThreadCount == 3 * ((update_slots_cond >> 32) - update_shots_count_x) )
			sio2_mtap_update_slots();
		pad_state_add = 0;
		do
		{
			openslot_tmp = &openSlots[port];
			slot = 0;
			task_3_count = 0;
			port_tmp1 = port;
			do
			{
				pdSetActive(port_tmp1, slot, 0);
				if ( ((*openslot_tmp >> slot) & 1) != 0 )
				{
					padstate_p = &g_pad_state[0][task_3_count + pad_state_add];
					Stat70bit = pdGetStat70bit(port, slot);
					runTask = padstate_p->runTask;
					padstate_p->stat70bit = Stat70bit;
					if ( runTask )
					{
						if ( runTask == 3 )
						{
							eventflag = padstate_p->eventflag;
							padstate_p->currentTask = runTask;
							padstate_p->runTask = 0;
							padstate_p->reqState = 2;
							SetEventFlag(eventflag, 0x1000u);
						}
						else if ( padstate_p->currentTask == 1 )
						{
							StartThread(padstate_p->taskTid, NULL);
							runtask_t = padstate_p->runTask;
							padstate_p->runTask = 0;
							padstate_p->reqState = 2;
							padstate_p->currentTask = runtask_t;
						}
						else
						{
							padstate_p->runTask = 0;
							padstate_p->reqState = 1;
						}
					}
					switch ( padstate_p->currentTask )
					{
						case 1u:
							ef_tmp = padstate_p->eventflag;
							flag_to_set = 1;
							goto LABEL_24;
						case 2u:
							ef_tmp = padstate_p->eventflag;
							flag_to_set = 2;
							goto LABEL_23;
						case 3u:
							padstate_p->buttonDataReady = 0;
							if ( GetThreadsStatus(&g_pad_state[0][task_3_count + pad_state_add]) != 1 )
								break;
							padstate_p->currentTask = 0;
							padstate_p->reqState = 0;
							*openslot_tmp ^= 1 << slot;
							DeleteThreads(&g_pad_state[0][task_3_count + pad_state_add]);
							if ( padstate_p->m_close_wait_blocking )
							{
								SetEventFlag(padstate_p->eventflag, 0x400u);
								++task_3_count;
							}
							else
							{
								++task_3_count;
								DeleteEventFlag(padstate_p->eventflag);
								padstate_p->eventflag = 0;
							}
							goto LABEL_26;
						case 4u:
							ef_tmp = padstate_p->eventflag;
							flag_to_set = 8;
							goto LABEL_23;
						case 5u:
							ef_tmp = padstate_p->eventflag;
							flag_to_set = 16;
							goto LABEL_23;
						case 6u:
							ef_tmp = padstate_p->eventflag;
							flag_to_set = 32;
							goto LABEL_23;
						case 7u:
							ef_tmp = padstate_p->eventflag;
							flag_to_set = 64;
LABEL_23:
							padstate_p->buttonDataReady = 0;
LABEL_24:
							SetEventFlag(ef_tmp, flag_to_set);
							WaitEventFlag(padstate_p->eventflag, 0x80u, 16, NULL);
							pdSetActive(port, slot, 1u);
							break;
						default:
							break;
					}
				}
				++task_3_count;
LABEL_26:
				++slot;
				port_tmp1 = port;
			}
			while ( slot < 4 );
			++port;
			pad_state_add += 4;
		}
		while ( port < 2 );
		vblankdata.stopTransfer = 0;
		WaitClearEvent(vblankdata.eventflag, 4u);
		if ( openSlots[0] || openSlots[1] )
		{
			port_2 = 0;
			padstate_offs = 0;
			do
			{
				slot_2 = 0;
				padstate_p2 = g_pad_state[0];
				do
				{
					padstate_elm = &padstate_p2[padstate_offs];
					if ( pdIsActive(port_2, slot_2) == 1 )
					{
						SetEventFlag(padstate_elm->eventflag, 0x100u);
						WaitEventFlag(padstate_elm->eventflag, 0x200u, 16, NULL);
					}
					++slot_2;
					++padstate_p2;
				}
				while ( slot_2 < 4 );
				++port_2;
				padstate_offs += 4;
			}
			while ( port_2 < 2 );
		}
		DmaSendEE();
	}
}
// 408304: using guessed type int mainThreadCount;
// 409260: using guessed type int openSlots[];
// 409268: using guessed type vblankData_t vblankdata;

//----- (00400D98) --------------------------------------------------------
u32 __cdecl ReadData(padState_t *pstate)
{
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 has_result_flag; // $s3
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 insizetmp; // $v0
	u32 OutSize; // $v0
	int i1; // $a0
	padState_t *pstatetmp; // $v0
	int i2; // $a0
	int i3; // $a1
	u8 *padmoreextra; // $v0

	port = pstate->port;
	slot = pstate->slot;
	has_result_flag = 0;
	PortCtrl1 = sio2CmdGetPortCtrl1(pstate->modeCurId, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(pstate->modeCurId, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(pstate->modeCurId);
	pdSetRegData(port, slot, RegData);
	insizetmp = pdGetInSize(pstate->modeCurId);
	pdSetInSize(port, slot, insizetmp);
	OutSize = pdGetOutSize(pstate->modeCurId);
	pdSetOutSize(port, slot, OutSize);
	i1 = 0;
	pstatetmp = pstate;
	do
	{
		++i1;
		pstatetmp->inbuffer[0] = 0;
		pstatetmp->outbuffer[0] = 0;
		pstatetmp = (padState_t *)((char *)pstate + i1);
	}
	while ( i1 < 32 );
	sio2CmdSetReadData(pstate->modeCurId, pstate->inbuffer);
	i2 = 0;
	if ( pstate->ee_actDirectSize )
	{
		i3 = 3;
		do
		{
			padmoreextra = &pstate->ee_pdata.data[i3];
			if ( pstate->ee_actAlignData[i2] == 255 )
				padmoreextra[264] = 0;
			else
				padmoreextra[264] = pstate->ee_actDirectData[i2];
			++i2;
			++i3;
		}
		while ( i2 < pstate->ee_actDirectSize );
	}
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		has_result_flag = 1;
		if ( pstate->stat70bit == 1 )
		{
			shiftarray(pstate->outbuffer);
			has_result_flag = 1;
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return has_result_flag;
}

//----- (00400F74) --------------------------------------------------------
u32 __cdecl PadIsSupported(padState_t *pstate)
{
	u32 retflag; // $s6
	u32 port; // $s3
	u32 slot; // $s4
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 in_size_tmp; // $v0
	u32 OutSize; // $v0
	u8 out_buffer_1_val; // $s0

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0);
	pdSetRegData(port, slot, RegData);
	in_size_tmp = pdGetInSize(0);
	pdSetInSize(port, slot, in_size_tmp);
	OutSize = pdGetOutSize(0);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetReadData(0, pstate->inbuffer);
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] )
		{
			if ( sio2cmdCheckId(pstate->outbuffer[1]) == 1 )
			{
				out_buffer_1_val = pstate->outbuffer[1];
				if ( out_buffer_1_val )
				{
					if ( sio2cmdCheckId(pstate->outbuffer[1]) == 1 )
					{
						retflag = 1;
						pstate->modeCurId = out_buffer_1_val;
						do_set_unused_4_pad(port, slot, out_buffer_1_val);
					}
				}
			}
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401140) --------------------------------------------------------
u32 __cdecl EnterConfigMode(u8 val, padState_t *pstate)
{
	u32 retflag; // $s4
	u32 val_tmp; // $s0
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 in_size_tmp; // $v0
	u32 OutSize; // $v0

	retflag = 0;
	val_tmp = val;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(val, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(val_tmp, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(val_tmp);
	pdSetRegData(port, slot, RegData);
	in_size_tmp = pdGetInSize(val_tmp);
	pdSetInSize(port, slot, in_size_tmp);
	OutSize = pdGetOutSize(val_tmp);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetEnterConfigMode(val_tmp, pstate->inbuffer);
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		retflag = 1;
		if ( pstate->stat70bit == 1 )
		{
			shiftarray(pstate->outbuffer);
			retflag = 1;
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (004012AC) --------------------------------------------------------
u32 __cdecl ExitConfigMode(padState_t *pstate)
{
	u32 retflag; // $s4
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 in_size_tmp; // $v0
	u32 OutSize; // $v0

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	in_size_tmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, in_size_tmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetExitConfigMode(0xF3u, pstate->inbuffer);
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		retflag = 1;
		if ( pstate->stat70bit == 1 )
		{
			shiftarray(pstate->outbuffer);
			retflag = 1;
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401414) --------------------------------------------------------
u32 __cdecl SetMainMode(padState_t *pstate)
{
	u32 retflag; // $s4
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 in_size_tmp; // $v0
	u32 OutSize; // $v0
	u8 lock; // $v1

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	in_size_tmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, in_size_tmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetSetMainMode(0xF3u, pstate->inbuffer);
	lock = pstate->lock;
	pstate->inbuffer[3] = pstate->mode;
	pstate->inbuffer[4] = lock;
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 0xF3 )
			retflag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (0040159C) --------------------------------------------------------
u32 __cdecl SetActAlign(padState_t *pstate)
{
	u32 retflag; // $s3
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 in_size_tmp; // $v0
	u32 OutSize; // $v0
	int i1; // $a0
	padState_t *pstatetmp; // $v1
	u8 valtmp; // $v0

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	in_size_tmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, in_size_tmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetSetActAlign(0xF3u, pstate->inbuffer);
	i1 = 0;
	pstatetmp = pstate;
	do
	{
		valtmp = pstate->ee_actAlignData[i1++];
		pstatetmp->inbuffer[3] = valtmp;
		pstatetmp = (padState_t *)((char *)pstate + i1);
	}
	while ( i1 < 6 );
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
			retflag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (0040172C) --------------------------------------------------------
u32 __cdecl QueryModel(padState_t *pstate)
{
	u32 retflag; // $s4
	u32 port; // $s2
	u32 slot; // $s3
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 in_size_tmp; // $v0
	u32 OutSize; // $v0
	u8 valtmp1; // $v0
	u8 valtmp2; // $v1
	u8 valtmp3; // $a0
	u8 valtmp4; // $a1
	u8 valtmp5; // $a2

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	in_size_tmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, in_size_tmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetQueryModel(0xF3u, pstate->inbuffer);
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
		{
			valtmp1 = pstate->outbuffer[6];
			valtmp2 = pstate->outbuffer[3];
			valtmp3 = pstate->outbuffer[4];
			valtmp4 = pstate->outbuffer[5];
			valtmp5 = pstate->outbuffer[7];
			pstate->numActuators = valtmp1;
			pstate->model = valtmp2;
			pstate->numModes = valtmp3;
			pstate->modeCurOffs = valtmp4;
			pstate->numActComb = valtmp5;
			if ( valtmp1 >= 4u )
				pstate->numActuators = 4;
			if ( pstate->numActComb >= 4u )
				pstate->numActComb = 4;
			retflag = 1;
			if ( pstate->numModes >= 4u )
				pstate->numModes = 4;
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401910) --------------------------------------------------------
u32 __cdecl QueryAct(u32 actuator, padState_t *pstate)
{
	u32 retflag; // $s4
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 insizetmp; // $v0
	u32 OutSize; // $v0
	padState_t *padstatetmp; // $v1

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	insizetmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, insizetmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetQueryAct(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = actuator;
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
		{
			padstatetmp = (padState_t *)((char *)pstate + 4 * actuator);
			padstatetmp->actData[0][0] = pstate->outbuffer[5];
			padstatetmp->actData[0][1] = pstate->outbuffer[6];
			padstatetmp->actData[0][2] = pstate->outbuffer[7];
			retflag = 1;
			padstatetmp->actData[0][3] = pstate->outbuffer[8];
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401AC4) --------------------------------------------------------
u32 __cdecl QueryComb(u32 val, padState_t *pstate)
{
	u32 retflag; // $s4
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 insizetmp; // $v0
	u32 OutSize; // $v0
	padState_t *padstatetmp; // $v1

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	insizetmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, insizetmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetQueryComb(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = val;
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
		{
			padstatetmp = (padState_t *)((char *)pstate + 4 * val);
			padstatetmp->combData[0][0] = pstate->outbuffer[5];
			padstatetmp->combData[0][1] = pstate->outbuffer[6];
			padstatetmp->combData[0][2] = pstate->outbuffer[7];
			retflag = 1;
			padstatetmp->combData[0][3] = pstate->outbuffer[8];
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401C78) --------------------------------------------------------
u32 __cdecl QueryMode(u32 val, padState_t *pstate)
{
	u32 retflag; // $s4
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 insizetmp; // $v0
	u32 OutSize; // $v0

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	insizetmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, insizetmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetQueryMode(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = val;
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
		{
			retflag = 1;
			pstate->modeTable[val] = pstate->outbuffer[6] + (pstate->outbuffer[5] << 8);
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401E1C) --------------------------------------------------------
u32 __cdecl VrefParam(u32 val, padState_t *pstate)
{
	u32 retflag; // $s5
	u32 port; // $s2
	u32 slot; // $s3
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	pdSetInSize(port, slot, 9u);
	pdSetOutSize(port, slot, 9u);
	sio2CmdSetSetVrefParam(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = val;
	pstate->inbuffer[4] = pstate->modeParam[val];
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
			retflag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401FA0) --------------------------------------------------------
u32 __cdecl QueryButtonMask(padState_t *pstate)
{
	u32 retflag; // $s4
	u32 port; // $s2
	u32 slot; // $s3
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 insizetmp; // $v0
	u32 OutSize; // $v0
	u8 valtmp1; // $v1
	u8 valtmp2; // $a0
	u8 valtmp3; // $a1

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	insizetmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, insizetmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetQueryButtonMask(0xF3u, pstate->inbuffer);
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[8] == 90 )
		{
			valtmp1 = pstate->outbuffer[4];
			valtmp2 = pstate->outbuffer[5];
			valtmp3 = pstate->outbuffer[6];
			pstate->buttonMask[0] = pstate->outbuffer[3];
			pstate->buttonMask[1] = valtmp1;
			pstate->buttonMask[2] = valtmp2;
			pstate->buttonMask[3] = valtmp3;
		}
		else
		{
			pstate->buttonMask[0] = 0;
			pstate->buttonMask[1] = 0;
			pstate->buttonMask[2] = 0;
			pstate->buttonMask[3] = 0;
		}
		retflag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (0040214C) --------------------------------------------------------
u32 __cdecl SetButtonInfo(padState_t *pstate)
{
	u32 retflag; // $s3
	u32 port; // $s1
	u32 slot; // $s2
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 insizetmp; // $v0
	u32 OutSize; // $v0
	int i1; // $a0
	padState_t *pstatetmp; // $v1
	u8 valtmp; // $v0

	retflag = 0;
	port = pstate->port;
	slot = pstate->slot;
	PortCtrl1 = sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0xF3u);
	pdSetRegData(port, slot, RegData);
	insizetmp = pdGetInSize(0xF3u);
	pdSetInSize(port, slot, insizetmp);
	OutSize = pdGetOutSize(0xF3u);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetSetButtonInfo(0xF3u, pstate->inbuffer);
	i1 = 0;
	pstatetmp = pstate;
	do
	{
		valtmp = pstate->buttonInfo[i1++];
		pstatetmp->inbuffer[3] = valtmp;
		pstatetmp = (padState_t *)((char *)pstate + i1);
	}
	while ( i1 < 4 );
	pdSetInBuffer(port, slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(port, slot) )
	{
		pdGetOutBuffer(port, slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
			retflag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (004022DC) --------------------------------------------------------
u32 __cdecl ActDirectTotal(u32 port, u32 slot)
{
	u32 retval_r; // $s3
	u32 p; // $s1
	int ind2; // $s4
	u32 s; // $s0
	int ind1; // $s2
	padState_t *pstate_tmp1; // $a1
	int i1; // $a0
	padState_t *pstate_tmp2; // $v0
	int data_tmp1; // $v1

	retval_r = 0;
	p = 0;
	ind2 = 0;
	while ( (int)p < (int)padGetPortMax() )
	{
		s = 0;
		ind1 = 0;
		while ( (int)s < (int)padGetSlotMax(p) )
		{
			if ( (port != p || slot != s) && ((openSlots[p] >> s) & 1) != 0 )
			{
				pstate_tmp1 = &g_pad_state[0][ind1 + ind2];
				if ( pstate_tmp1->modeCurId )
				{
					i1 = 0;
					if ( pstate_tmp1->ee_actDirectSize )
					{
						pstate_tmp2 = &g_pad_state[0][ind1 + ind2];
						do
						{
							data_tmp1 = pstate_tmp2->ee_actAlignData[0];
							if ( data_tmp1 != 255 )
							{
								if ( pstate_tmp1->ee_actDirectData[data_tmp1] )
									retval_r += pstate_tmp1->actData[data_tmp1][3];
							}
							++i1;
							pstate_tmp2 = (padState_t *)((char *)pstate_tmp1 + i1);
						}
						while ( i1 < pstate_tmp1->ee_actDirectSize );
					}
				}
			}
			++ind1;
			++s;
		}
		ind2 += 4;
		++p;
	}
	return retval_r;
}
// 409260: using guessed type int openSlots[];

//----- (00402448) --------------------------------------------------------
u32 __cdecl CheckAirDirectTotal(u32 port, u32 slot, u8 *actData)
{
	u32 total; // $s3
	padState_t *padstate_p; // $s2
	int i1; // $s0
	padState_t *padstate_p2; // $v0
	int itmp; // $v1
	u8 *act; // $s1
	int totaltmp; // $v1

	total = ActDirectTotal(port, slot);
	padstate_p = &g_pad_state[port][slot];
	i1 = 0;
	padstate_p2 = padstate_p;
	do
	{
		itmp = padstate_p2->ee_actAlignData[0];
		act = &actData[itmp];
		if ( itmp != 255 && *act )
		{
			totaltmp = total + padstate_p->actData[itmp][3];
			if ( totaltmp < 61 )
			{
				total = totaltmp;
			}
			else
			{
				if ( g_padman_verbose )
					Kprintf("padman: Over Consumpt Max [%d][%d]\n", port, slot);
				*act = 0;
			}
		}
		++i1;
		padstate_p2 = (padState_t *)((char *)padstate_p + i1);
	}
	while ( i1 < 6 );
	return 1;
}
// 4082F8: using guessed type int g_padman_verbose;

//----- (00402574) --------------------------------------------------------
void __cdecl __noreturn UpdatePadThread(void *arg)
{
	int retval; // $s1
	padState_t *pstate; // $s0
	u32 port; // $s6
	u32 slot; // $s5
	int querypadTid; // $a0
	int curid_tmp; // $v1
	int i1; // $a0
	padState_t *pstate_tmp1; // $v0
	int modeConfig; // $v0
	u32 findPadRetries; // $v0
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	retval = 0;
	ReferThreadStatus(0, &thinfo);
	pstate = (padState_t *)thinfo.option;
	port = *(unsigned __int16 *)(thinfo.option + 428);
	slot = *(unsigned __int16 *)(thinfo.option + 430);
	while ( 1 )
	{
		while ( 1 )
		{
			WaitClearEvent(pstate->eventflag, 1u);
			ApplyActDirectFromDmaBuf(pstate);
			if ( ReadData(pstate) != 1 )
				break;
			retval = 0;
			if ( pstate->outbuffer[2] != 90 )
			{
				querypadTid = pstate->querypadTid;
				pstate->buttonDataReady = 0;
				pstate->state = 5;
				goto LABEL_19;
			}
			curid_tmp = pstate->outbuffer[1];
			if ( curid_tmp != pstate->modeCurId )
			{
				querypadTid = pstate->querypadTid;
				pstate->buttonDataReady = 0;
				pstate->state = 5;
				goto LABEL_19;
			}
			if ( curid_tmp == 243 )
			{
				querypadTid = pstate->querypadTid;
				pstate->buttonDataReady = 0;
				pstate->state = 5;
				goto LABEL_19;
			}
			i1 = 0;
			pstate_tmp1 = pstate;
			do
			{
				++i1;
				pstate_tmp1->buttonStatus[0] = pstate_tmp1->outbuffer[0];
				pstate_tmp1 = (padState_t *)((char *)pstate + i1);
			}
			while ( i1 < 32 );
			modeConfig = pstate->modeConfig;
			pstate->buttonDataReady = 1;
			if ( modeConfig == 1 )
				pstate->state = 2;
			else
				pstate->state = 6;
			if ( pstate->reqState == 2 && !pstate->runTask )
				pstate->reqState = 0;
		}
		findPadRetries = pstate->findPadRetries;
		pstate->buttonDataReady = 0;
		pstate->state = 7;
		pstate->findPadRetries = findPadRetries + 1;
		retval += pdGetError(port, slot);
		if ( retval >= 10 )
		{
			retval = 0;
			querypadTid = pstate->querypadTid;
LABEL_19:
			pstate->currentTask = 2;
			StartThread(querypadTid, NULL);
		}
	}
}

//----- (00402704) --------------------------------------------------------
void __cdecl __noreturn QueryPadThread(void *arg)
{
	padState_t *option; // $s0
	int i1; // $v1
	padState_t *pstate_p1; // $v0
	int i2; // $v1
	int i3; // $v1
	u8 *otherclear1; // $v0
	u8 modeCurId; // $s2
	int i4; // $v1
	u8 *otherclear2; // $v0
	int i5; // $s1
	int i6; // $s1
	int i7; // $s1
	unsigned __int8 i9; // $s2
	int i8; // $s1
	unsigned __int8 i11; // $s2
	int i10; // $s1
	unsigned __int8 i13; // $s2
	int i12; // $s1
	int i14; // $s1
	int i15; // $s1
	int i16; // $s1
	u8 cur_id_tmp; // $s2
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	ReferThreadStatus(0, &thinfo);
	option = (padState_t *)thinfo.option;
	i1 = 0;
	*(_BYTE *)(thinfo.option + 193) = 0;
	option->modeConfig = 0;
	option->model = 0;
	option->numModes = 0;
	option->numActuators = 0;
	option->numActComb = 0;
	option->buttonDataReady = 0;
	option->ee_actDirectSize = 0;
	option->findPadRetries = 0;
	pstate_p1 = option;
	do
	{
		++i1;
		pstate_p1->buttonInfo[0] = 0;
		pstate_p1->buttonMask[0] = 0;
		pstate_p1 = (padState_t *)((char *)option + i1);
	}
	while ( i1 < 4 );
	i2 = 2;
	option->ee_actAlignData[0] = 0;
	option->ee_actAlignData[1] = 1;
	do
		option->ee_actAlignData[i2++] = -1;
	while ( i2 < 6 );
	i3 = 5;
	otherclear1 = &option->ee_pdata.data[5];
	do
	{
		otherclear1[364] = 0;
		--i3;
		--otherclear1;
	}
	while ( i3 >= 0 );
	option->modeCurId = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 2u);
		if ( PadIsSupported(option) == 1 && option->modeCurId != 255 )
			break;
		option->state = 0;
		option->disconnected = 1;
	}
	modeCurId = option->modeCurId;
	option->modeCurId = 0;
	option->state = 5;
	if ( option->disconnected )
	{
		i4 = 5;
		otherclear2 = &option->ee_pdata.data[5];
		do
		{
			otherclear2[374] = -1;
			--i4;
			--otherclear2;
		}
		while ( i4 >= 0 );
	}
	i5 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 2u);
		++i5;
		if ( EnterConfigMode(modeCurId, option) == 1 )
			break;
		if ( i5 >= 10 )
		{
			option->modeConfig = 1;
			option->modeCurId = modeCurId;
			option->currentTask = 1;
			ExitThread();
		}
	}
	option->modeConfig = 2;
	i6 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 2u);
		++i6;
		if ( QueryModel(option) == 1 )
			break;
		if ( i6 >= 10 )
		{
			option->modeCurId = 0;
			option->currentTask = 1;
			ExitThread();
		}
	}
	if ( option->disconnected == 1 )
	{
		i7 = 0;
		if ( option->modeCurOffs )
		{
			option->mode = 0;
			option->lock = 0;
			while ( 1 )
			{
				WaitClearEvent(option->eventflag, 2u);
				++i7;
				if ( SetMainMode(option) == 1 )
					break;
				if ( i7 >= 10 )
				{
					option->reqState = 1;
					option->currentTask = 1;
					ExitThread();
				}
			}
			option->modeCurId = 0;
			option->currentTask = 1;
			option->disconnected = 0;
			ExitThread();
		}
	}
	i9 = 0;
	if ( option->numActuators )
	{
		i8 = 0;
		do
		{
			while ( 1 )
			{
				WaitClearEvent(option->eventflag, 2u);
				++i8;
				if ( QueryAct(i9, option) == 1 )
					break;
				if ( i8 >= 10 )
				{
					option->modeCurId = 0;
					option->currentTask = 1;
					ExitThread();
				}
			}
			++i9;
			i8 = 0;
		}
		while ( i9 < (unsigned int)option->numActuators );
	}
	i11 = 0;
	if ( option->numActComb )
	{
		i10 = 0;
		do
		{
			while ( 1 )
			{
				WaitClearEvent(option->eventflag, 2u);
				++i10;
				if ( QueryComb(i11, option) == 1 )
					break;
				if ( i10 >= 10 )
				{
					option->modeCurId = 0;
					option->currentTask = 1;
					ExitThread();
				}
			}
			++i11;
			i10 = 0;
		}
		while ( i11 < (unsigned int)option->numActComb );
	}
	i13 = 0;
	if ( option->numModes )
	{
		i12 = 0;
		do
		{
			while ( 1 )
			{
				WaitClearEvent(option->eventflag, 2u);
				++i12;
				if ( QueryMode(i13, option) == 1 )
					break;
				if ( i12 >= 10 )
				{
					option->modeCurId = 0;
					option->currentTask = 1;
					ExitThread();
				}
			}
			++i13;
			i12 = 0;
		}
		while ( i13 < (unsigned int)option->numModes );
	}
	i14 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 2u);
		++i14;
		if ( SetActAlign(option) == 1 )
			break;
		if ( i14 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	i15 = 0;
	if ( (*(_DWORD *)&option->modeConfig & 0x200FF) == 0x20002 )
	{
		while ( 1 )
		{
			WaitClearEvent(option->eventflag, 2u);
			++i15;
			if ( QueryButtonMask(option) == 1 )
				break;
			if ( i15 >= 10 )
			{
				option->modeCurId = 0;
				option->currentTask = 1;
				ExitThread();
			}
		}
		i15 = 0;
	}
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 2u);
		++i15;
		if ( ExitConfigMode(option) == 1 )
			break;
		if ( i15 >= 10 )
		{
			option->modeCurId = 0;
			option->currentTask = 1;
			ExitThread();
		}
	}
	i16 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 2u);
		++i16;
		if ( PadIsSupported(option) == 1 )
			break;
		if ( i16 >= 10 )
		{
			option->modeCurId = 0;
			option->currentTask = 1;
			ExitThread();
		}
	}
	cur_id_tmp = option->modeCurId;
	option->state = 5;
	option->modeCurId = 0;
	option->currentTask = 1;
	option->disconnected = 0;
	option->modeCurId = cur_id_tmp;
	ExitThread();
}

//----- (00402C54) --------------------------------------------------------
void __cdecl __noreturn SetMainModeThread(void *arg)
{
	int tries1; // $s1
	padState_t *option; // $s0
	int tries2; // $s1
	int tries3; // $s1
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	tries1 = 0;
	ReferThreadStatus(0, &thinfo);
	option = (padState_t *)thinfo.option;
	*(_WORD *)(thinfo.option + 360) = 0;
	option->state = 5;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 8u);
		++tries1;
		if ( EnterConfigMode(option->modeCurId, option) == 1 )
			break;
		if ( tries1 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	tries2 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 8u);
		++tries2;
		if ( SetMainMode(option) == 1 )
			break;
		if ( tries2 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	tries3 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 8u);
		++tries3;
		if ( ExitConfigMode(option) == 1 )
			break;
		if ( tries3 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	option->currentTask = 1;
	ExitThread();
}

//----- (00402D8C) --------------------------------------------------------
void __cdecl __noreturn SetActAlignThread(void *arg)
{
	int tries1; // $s1
	padState_t *option; // $s0
	int tries2; // $s1
	int tries3; // $s1
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	tries1 = 0;
	ReferThreadStatus(0, &thinfo);
	option = (padState_t *)thinfo.option;
	*(_WORD *)(thinfo.option + 360) = 0;
	option->state = 5;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 0x10u);
		++tries1;
		if ( EnterConfigMode(option->modeCurId, option) == 1 )
			break;
		if ( tries1 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	tries2 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 0x10u);
		++tries2;
		if ( SetActAlign(option) == 1 )
			break;
		if ( tries2 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	tries3 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 0x10u);
		++tries3;
		if ( ExitConfigMode(option) == 1 )
			break;
		if ( tries3 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	option->currentTask = 1;
	ExitThread();
}

//----- (00402EC4) --------------------------------------------------------
void __cdecl __noreturn SetButtonInfoThread(void *arg)
{
	int tries1; // $s1
	padState_t *option; // $s0
	int tries2; // $s1
	signed __int32 tries4; // $s2
	int tries3; // $s1
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	tries1 = 0;
	ReferThreadStatus(0, &thinfo);
	option = (padState_t *)thinfo.option;
	*(_WORD *)(thinfo.option + 360) = 0;
	option->state = 5;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 0x20u);
		++tries1;
		if ( EnterConfigMode(option->modeCurId, option) == 1 )
			break;
		if ( tries1 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	tries2 = 0;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 0x20u);
		++tries2;
		if ( SetButtonInfo(option) == 1 )
			break;
		if ( tries2 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	tries4 = 0;
	tries3 = 0;
	do
	{
		while ( 1 )
		{
			WaitClearEvent(option->eventflag, 0x20u);
			++tries3;
			if ( VrefParam(tries4, option) == 1 )
				break;
			if ( tries3 >= 10 )
			{
				option->reqState = 1;
				option->currentTask = 1;
				ExitThread();
			}
		}
		++tries4;
		tries3 = 0;
	}
	while ( tries4 < 12 );
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 0x20u);
		++tries3;
		if ( ExitConfigMode(option) == 1 )
			break;
		if ( tries3 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	option->val_c6 = 1;
	option->currentTask = 1;
	ExitThread();
}

//----- (00403068) --------------------------------------------------------
void __cdecl __noreturn SetVrefParamThread(void *arg)
{
	int tries1; // $s1
	padState_t *option; // $s0
	signed __int32 tries3; // $s2
	int tries2; // $s1
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	tries1 = 0;
	ReferThreadStatus(0, &thinfo);
	option = (padState_t *)thinfo.option;
	*(_WORD *)(thinfo.option + 360) = 0;
	option->state = 5;
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 0x40u);
		++tries1;
		if ( EnterConfigMode(option->modeCurId, option) == 1 )
			break;
		if ( tries1 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	tries3 = 0;
	tries2 = 0;
	do
	{
		while ( 1 )
		{
			WaitClearEvent(option->eventflag, 0x40u);
			++tries2;
			if ( VrefParam(tries3, option) == 1 )
				break;
			if ( tries2 >= 10 )
			{
				option->reqState = 1;
				option->currentTask = 1;
				ExitThread();
			}
		}
		++tries3;
		tries2 = 0;
	}
	while ( tries3 < 12 );
	while ( 1 )
	{
		WaitClearEvent(option->eventflag, 0x40u);
		++tries2;
		if ( ExitConfigMode(option) == 1 )
			break;
		if ( tries2 >= 10 )
		{
			option->reqState = 1;
			option->currentTask = 1;
			ExitThread();
		}
	}
	option->currentTask = 1;
	ExitThread();
}

//----- (004031BC) --------------------------------------------------------
void __cdecl do_set_timer(int timer_mode, u32 timer_compare)
{
	int timerid; // $s2
	int HardTimerIntrCode; // $s1

	timerid = AllocHardTimer(4, 32, 1);
	if ( timerid >= 0 || (timerid = AllocHardTimer(4, 32, 1), timerid >= 0) )
	{
		HardTimerIntrCode = GetHardTimerIntrCode(timerid);
		RegisterIntrHandler(HardTimerIntrCode, 1, (int (__cdecl *)(void *))VblankStart, &vblankdata);
		SetTimerMode(timerid, 0);
		SetTimerCompare(timerid, timer_compare);
		SetTimerCounter(timerid, 0);
		SetTimerMode(timerid, timer_mode);
		EnableIntr(HardTimerIntrCode);
		g_readxfertimer_timid = timerid;
		g_readxfertimer_irq = HardTimerIntrCode;
	}
	else
	{
		Kprintf("Timer alloc faild\n");
	}
}
// 409268: using guessed type vblankData_t vblankdata;

//----- (004032BC) --------------------------------------------------------
int __cdecl ParseParams(int argc, char *argv[])
{
	int new_thpri_hi; // $s3
	int new_thpri_lo; // $s2
	int ac_tmp; // $s4
	const char **av_tmp; // $s1
	int thparam_after; // $s0

	new_thpri_hi = 20;
	new_thpri_lo = 46;
	ac_tmp = 1;
	if ( argc <= 1 )
	{
LABEL_18:
		thpri_hi = new_thpri_hi;
		thpri_lo = new_thpri_lo;
		return 1;
	}
	av_tmp = (const char **)(argv + 1);
	while ( strncmp("thpri=", *av_tmp, 6) )
	{
LABEL_17:
		++ac_tmp;
		++av_tmp;
		if ( ac_tmp >= argc )
			goto LABEL_18;
	}
	thparam_after = (int)(*av_tmp + 6);
	if ( (look_ctype_table(*(_BYTE *)thparam_after) & 4) != 0 )
	{
		new_thpri_hi = strtol((const char *)thparam_after, NULL, 10);
		if ( (unsigned int)(new_thpri_hi - 9) >= 0x73 )
		{
			printf("PADMAN : invalid priority %d\n");
			return 0;
		}
	}
	while ( (look_ctype_table(*(_BYTE *)thparam_after) & 4) != 0 )
		++thparam_after;
	if ( *(_BYTE *)thparam_after != 44 )
	{
LABEL_15:
		if ( new_thpri_lo < new_thpri_hi )
		{
			new_thpri_lo = new_thpri_hi;
			printf("PADMAN : high prio thread must be higher than low prio thread\n");
		}
		goto LABEL_17;
	}
	if ( (look_ctype_table(*(_BYTE *)(thparam_after + 1)) & 4) == 0
		|| (new_thpri_lo = strtol((const char *)(thparam_after + 1), NULL, 10), (unsigned int)(new_thpri_lo - 9) < 0x73) )
	{
		goto LABEL_15;
	}
	printf(" SDR driver error: invalid priority %d\n");
	return 0;
}
// 409294: using guessed type int thpri_hi;

//----- (00403448) --------------------------------------------------------
int __cdecl _start(int ac, char **av)
{
	vblank_end = 0;
	padman_init = 0;
	sifdma_id = 0;
	g_readxfertimer_val = 0;
	thpri_hi = 20;
	thpri_lo = 46;
	if ( ac >= 2 )
		ParseParams(ac, av);
	if ( (thpri_hi != 20 || thpri_lo != 46) && g_padman_verbose )
		Kprintf("padman: thread priority: high=%d, low=%d\n", thpri_hi, thpri_lo);
	if ( RegisterLibraryEntries(&_exp_padman) )
	{
		if ( g_padman_verbose )
		{
			Kprintf("padman: RegisterLibraryEntries Faild\n");
		}
	}
	else
	{
		if ( !(SetRebootTimeLibraryHandlingMode(&_exp_padman, 2) != 0) )
		{
			if ( !(InitRpcServers(thpri_lo) != 0) )
			{
				if ( g_padman_verbose )
				{
					Kprintf("padman: sif_init Faild\n");
				}
				return 1;
			}
			return 0;
		}
	}
	return 1;
}
// 4082F8: using guessed type int g_padman_verbose;
// 408320: using guessed type int vblank_end;
// 409288: using guessed type int padman_init;
// 409294: using guessed type int thpri_hi;
// 4092A0: using guessed type int g_readxfertimer_val;
// 4092A4: using guessed type int sifdma_id;

//----- (00403590) --------------------------------------------------------
s32 _deinit()
{
	return padEnd();
}

//----- (004035B0) --------------------------------------------------------
s32 __cdecl padInit(void *ee_addr, int timer_interval)
{
	int thid2; // $v0
	int thid1; // $v0
	iop_event_t evparam; // [sp+10h] [-40h] BYREF
	iop_thread_t thparam; // [sp+20h] [-30h] BYREF
	iop_sema_t semaparam; // [sp+38h] [-18h] BYREF
	int state[2]; // [sp+48h] [-8h] BYREF

	if ( padman_init == 1 )
		padEnd();
	g_padman_unk_40928C = 0;
	g_padman_verbose = 1;
	vblankdata.init = 0;
	vblankdata.stopTransfer = 1;
	vblankdata.padEnd = 0;
	g_padman_nonblock_dma = 0;
	g_readxfertimer_val = timer_interval;
	g_sema = -1;
	g_padman_ee_addr = (int)ee_addr;
	sio2cmdReset();
	sio2cmdInitFindPads();
	sio2cmdInitMouse();
	sio2cmdInitNegicon();
	sio2cmdInitKonamiGun();
	sio2cmdInitDigital();
	sio2cmdInitJoystick();
	sio2cmdInitNamcoGun();
	sio2cmdInitAnalog();
	sio2cmdInitJogcon();
	sio2cmdInitConfig();
	pdReset();
	openSlots[0] = 0;
	openSlots[1] = 0;
	evparam.attr = 2;
	evparam.bits = 0;
	vblankdata.eventflag = CreateEventFlag(&evparam);
	if ( !vblankdata.eventflag )
		return 0;
	thparam.attr = 0x2000000;
	thparam.thread = (void (__cdecl *)(void *))TransferThread;
	thparam.option = 0;
	thparam.stacksize = 2048;
	thparam.priority = thpri_hi;
	thid2 = CreateThread(&thparam);
	vblankdata.tid_2 = thid2;
	if ( !thid2 )
		return 0;
	StartThread(thid2, NULL);
	thparam.attr = 0x2000000;
	thparam.thread = (void (__cdecl *)(void *))MainThread;
	thparam.option = 1;
	thparam.stacksize = 4096;
	thparam.priority = thpri_lo;
	thid1 = CreateThread(&thparam);
	vblankdata.tid_1 = thid1;
	if ( !thid1 )
		return 0;
	StartThread(thid1, NULL);
	semaparam.attr = 0;
	semaparam.initial = 0;
	semaparam.max = 16;
	g_sema = CreateSema(&semaparam);
	if ( g_sema < 0 )
		return 0;
	if ( timer_interval <= 0 )
	{
		CpuSuspendIntr(state);
		RegisterVblankHandler(0, 16, (int (__cdecl *)(void *))VblankStart, &vblankdata);
		RegisterVblankHandler(1, 16, VblankEnd, &vblankdata);
	}
	else
	{
		if ( (unsigned int)(timer_interval - 0x4123) > 0xC348 )
			return 0;
		g_readxfertimer_val = 0x3D76 * timer_interval / 1000000;
		CpuSuspendIntr(state);
		do_set_timer(346, g_readxfertimer_val);
	}
	CpuResumeIntr(state[0]);
	vblankdata.init = 1;
	padman_init = 1;
	return 1;
}
// 4082F8: using guessed type int g_padman_verbose;
// 409260: using guessed type int openSlots[];
// 409268: using guessed type vblankData_t vblankdata;
// 409288: using guessed type int padman_init;
// 40928C: using guessed type int g_padman_unk_40928C;
// 409290: using guessed type int g_padman_ee_addr;
// 409294: using guessed type int thpri_hi;
// 40929C: using guessed type int g_padman_nonblock_dma;
// 4092A0: using guessed type int g_readxfertimer_val;
// 4092A8: using guessed type int g_sema;

//----- (00403858) --------------------------------------------------------
s32 __cdecl padEnd()
{
	s32 i1; // $s1
	int *slot_tmp; // $s2
	s32 i; // $s0

	if ( !padman_init )
		return 1;
	i1 = 0;
	slot_tmp = openSlots;
	do
	{
		for ( i = 0; i < 4; ++i )
		{
			if ( ((*slot_tmp >> i) & 1) != 0 )
				padPortClose(i1, i, 1);
		}
		++i1;
		++slot_tmp;
	}
	while ( i1 < 2 );
	SetEventFlag(vblankdata.eventflag, 0x1000u);
	vblankdata.padEnd = 1;
	WaitEventFlag(vblankdata.eventflag, 8u, 17, NULL);
	DeleteThreadsEventFlag(&vblankdata);
	if ( g_readxfertimer_val <= 0 )
	{
		while ( ReleaseVblankHandler(0, (int (__cdecl *)(void *))VblankStart) )
			;
		while ( ReleaseVblankHandler(1, VblankEnd) )
			;
	}
	else
	{
		while ( ReleaseIntrHandler(g_readxfertimer_irq) )
			;
		FreeHardTimer(g_readxfertimer_timid);
	}
	if ( g_sema >= 0 )
	{
		DeleteSema(g_sema);
		g_sema = -1;
	}
	padman_init = 0;
	g_padman_nonblock_dma = 0;
	return 1;
}
// 409260: using guessed type int openSlots[];
// 409268: using guessed type vblankData_t vblankdata;
// 409288: using guessed type int padman_init;
// 40929C: using guessed type int g_padman_nonblock_dma;
// 4092A0: using guessed type int g_readxfertimer_val;
// 4092A8: using guessed type int g_sema;

//----- (004039CC) --------------------------------------------------------
s32 __cdecl padPortOpen(s32 port, s32 slot, s32 pad_area_ee_addr, struct libpad_dma_act_direct_state **buf)
{
	padState_t *padstate_tmp; // $s0
	int *slot_buf_tmp; // $a3
	int ef_tmp; // $v0
	int th_tmp1; // $v0
	int th_tmp2; // $v0
	int th_tmp3; // $v0
	int th_tmp4; // $v0
	int th_tmp5; // $v0
	int th_tmp6; // $v0
	int updatepadTid; // $a0
	iop_event_t efparam; // [sp+10h] [-28h] BYREF
	iop_thread_t thparam; // [sp+20h] [-18h] BYREF

	if ( (unsigned int)port >= 2 || (unsigned int)slot >= 4 )
		return 0;
	padstate_tmp = &g_pad_state[port][slot];
	*buf = padstate_tmp->m_dma_act_direct_state;
	slot_buf_tmp = &openSlots[port];
	padstate_tmp->m_dma_act_direct_state[0].m_frame = 0;
	padstate_tmp->m_dma_act_direct_state[1].m_frame = 0;
	padstate_tmp->m_dma_act_direct_state[0].m_unhandled = 0;
	padstate_tmp->m_dma_act_direct_state[1].m_unhandled = 0;
	padstate_tmp->m_dma_act_direct_state[0].m_unused = 0;
	padstate_tmp->m_dma_act_direct_state[1].m_unused = 0;
	if ( ((*slot_buf_tmp >> slot) & 1) != 0 )
		return 0;
	padstate_tmp->port = port;
	padstate_tmp->slot = slot;
	*slot_buf_tmp |= 1 << slot;
	padstate_tmp->state = 5;
	padstate_tmp->modeCurId = 0;
	padstate_tmp->reqState = 0;
	padstate_tmp->frame = 0;
	padstate_tmp->padarea_ee_addr = pad_area_ee_addr;
	padstate_tmp->buttonDataReady = 0;
	padstate_tmp->ee_actDirectSize = 0;
	padstate_tmp->val_c6 = 0;
	padstate_tmp->currentTask = 0;
	padstate_tmp->runTask = 0;
	padstate_tmp->m_unused1bc = 0;
	padstate_tmp->disconnected = 1;
	padstate_tmp->stat70bit = 0;
	efparam.attr = 2;
	efparam.bits = 0;
	ef_tmp = CreateEventFlag(&efparam);
	padstate_tmp->eventflag = ef_tmp;
	if ( !ef_tmp )
		return 0;
	thparam.option = (u32)padstate_tmp;
	thparam.attr = 0x2000000;
	thparam.thread = UpdatePadThread;
	thparam.stacksize = 1536;
	thparam.priority = thpri_lo;
	th_tmp1 = CreateThread(&thparam);
	padstate_tmp->updatepadTid = th_tmp1;
	if ( !th_tmp1 )
		return 0;
	thparam.option = (u32)padstate_tmp;
	thparam.attr = 0x2000000;
	thparam.thread = QueryPadThread;
	thparam.stacksize = 1536;
	thparam.priority = thpri_lo;
	th_tmp2 = CreateThread(&thparam);
	padstate_tmp->querypadTid = th_tmp2;
	if ( !th_tmp2 )
		return 0;
	thparam.option = (u32)padstate_tmp;
	thparam.attr = 0x2000000;
	thparam.thread = SetMainModeThread;
	thparam.stacksize = 1024;
	thparam.priority = thpri_lo;
	th_tmp3 = CreateThread(&thparam);
	padstate_tmp->setmainmodeTid = th_tmp3;
	if ( !th_tmp3 )
		return 0;
	thparam.option = (u32)padstate_tmp;
	thparam.attr = 0x2000000;
	thparam.thread = SetActAlignThread;
	thparam.stacksize = 1024;
	thparam.priority = thpri_lo;
	th_tmp4 = CreateThread(&thparam);
	padstate_tmp->setactalignTid = th_tmp4;
	if ( !th_tmp4 )
		return 0;
	thparam.option = (u32)padstate_tmp;
	thparam.attr = 0x2000000;
	thparam.thread = SetButtonInfoThread;
	thparam.stacksize = 1024;
	thparam.priority = thpri_lo;
	th_tmp5 = CreateThread(&thparam);
	padstate_tmp->setbuttoninfoTid = th_tmp5;
	if ( !th_tmp5 )
		return 0;
	thparam.option = (u32)padstate_tmp;
	thparam.attr = 0x2000000;
	thparam.thread = SetVrefParamThread;
	thparam.stacksize = 1024;
	thparam.priority = thpri_lo;
	th_tmp6 = CreateThread(&thparam);
	padstate_tmp->setvrefparamTid = th_tmp6;
	if ( !th_tmp6 || padstate_tmp->currentTask >= 2u )
		return 0;
	updatepadTid = padstate_tmp->updatepadTid;
	padstate_tmp->currentTask = 1;
	StartThread(updatepadTid, NULL);
	return 1;
}
// 409260: using guessed type int openSlots[];

//----- (00403C78) --------------------------------------------------------
s32 __cdecl padPortClose(s32 port, s32 slot, s32 wait)
{
	padState_t *padstate_tmp; // $s0
	int efres[2]; // [sp+10h] [-8h] BYREF

	efres[0] = 0;
	padstate_tmp = &g_pad_state[port][slot];
	if ( ((openSlots[port] >> slot) & 1) != 0 )
	{
		if ( padstate_tmp->reqState == 2 )
		{
			return 0;
		}
		else
		{
			padstate_tmp->runTask = 3;
			padstate_tmp->taskTid = 0;
			padstate_tmp->reqState = 2;
			padstate_tmp->m_close_wait_blocking = wait;
			if ( wait )
			{
				WaitEventFlag(padstate_tmp->eventflag, 0x400u, 16, (u32 *)efres);
				DeleteEventFlag(padstate_tmp->eventflag);
				padstate_tmp->eventflag = 0;
			}
			return 1;
		}
	}
	return 0;
}
// 409260: using guessed type int openSlots[];
// 403C78: using guessed type u32 efres[2];

#define BSWAP16(x) ((((unsigned short int)x) << 8) | (x >> 8))

//----- (00403D48) --------------------------------------------------------
u32 __cdecl padSetupEEButtonData(u32 port, u32 slot, padState_t *pstate)
{
	padState_t *padstate_tmp; // $a1
	int i1; // $v1
	u8 *plvar; // $a0
	int modeCurId; // $v1
	__int16 swapval2; // $v1
	int bmask1; // $v0
	int bmask2; // $v0
	int bmask3; // $v0
	int bmask4; // $v0
	int bmask5; // $v0
	int bmask6; // $v0
	int bmask7; // $v0
	int bmask8; // $v0
	int bmask9; // $v0
	int bmask10; // $v0
	int bmask11; // $v0
	int i2; // $v1
	u8 *lval_tmp; // $v0

	padstate_tmp = &g_pad_state[port][slot];
	if ( padstate_tmp->buttonDataReady == 1 )
	{
		pstate->ee_pdata.data[0] = 0;
		pstate->ee_pdata.data[1] = padstate_tmp->modeCurId;
		i1 = 2;
		pstate->ee_pdata.data[31] = padstate_tmp->buttonStatus[2];
		do
		{
			plvar = &pstate->ee_pdata.data[i1++];
			*plvar = padstate_tmp->buttonStatus[i1];
		}
		while ( i1 < 31 );
		modeCurId = padstate_tmp->modeCurId;
		if ( modeCurId == 18 )
		{
			pstate->ee_pdata.data[2] = -1;
			pstate->ee_pdata.data[3] = -1;
			pstate->ee_pdata.data[4] = 0;
			pstate->ee_pdata.data[5] = 0;
			modeCurId = padstate_tmp->modeCurId;
		}
		if ( modeCurId != 121 )
			return 32;
		swapval2 = ~BSWAP16(*(_WORD *)&pstate->ee_pdata.data[2]);
		if ( (swapval2 & 0x2000) != 0 )
		{
			bmask1 = swapval2 & 0x8000;
			if ( pstate->ee_pdata.data[8] )
				goto LABEL_13;
			pstate->ee_pdata.data[8] = 1;
		}
		else
		{
			bmask1 = swapval2 & 0x8000;
			if ( !pstate->ee_pdata.data[8] )
				goto LABEL_13;
			pstate->ee_pdata.data[8] = 0;
		}
		bmask1 = swapval2 & 0x8000;
LABEL_13:
		if ( bmask1 )
		{
			bmask2 = swapval2 & 0x1000;
			if ( pstate->ee_pdata.data[9] )
				goto LABEL_19;
			pstate->ee_pdata.data[9] = 1;
		}
		else
		{
			bmask2 = swapval2 & 0x1000;
			if ( !pstate->ee_pdata.data[9] )
				goto LABEL_19;
			pstate->ee_pdata.data[9] = 0;
		}
		bmask2 = swapval2 & 0x1000;
LABEL_19:
		if ( bmask2 )
		{
			bmask3 = swapval2 & 0x4000;
			if ( pstate->ee_pdata.data[10] )
				goto LABEL_25;
			pstate->ee_pdata.data[10] = 1;
		}
		else
		{
			bmask3 = swapval2 & 0x4000;
			if ( !pstate->ee_pdata.data[10] )
				goto LABEL_25;
			pstate->ee_pdata.data[10] = 0;
		}
		bmask3 = swapval2 & 0x4000;
LABEL_25:
		if ( bmask3 )
		{
			bmask4 = swapval2 & 0x10;
			if ( pstate->ee_pdata.data[11] )
				goto LABEL_31;
			pstate->ee_pdata.data[11] = 1;
		}
		else
		{
			bmask4 = swapval2 & 0x10;
			if ( !pstate->ee_pdata.data[11] )
				goto LABEL_31;
			pstate->ee_pdata.data[11] = 0;
		}
		bmask4 = swapval2 & 0x10;
LABEL_31:
		if ( bmask4 )
		{
			bmask5 = swapval2 & 0x20;
			if ( pstate->ee_pdata.data[12] )
				goto LABEL_37;
			pstate->ee_pdata.data[12] = 1;
		}
		else
		{
			bmask5 = swapval2 & 0x20;
			if ( !pstate->ee_pdata.data[12] )
				goto LABEL_37;
			pstate->ee_pdata.data[12] = 0;
		}
		bmask5 = swapval2 & 0x20;
LABEL_37:
		if ( bmask5 )
		{
			bmask6 = swapval2 & 0x40;
			if ( pstate->ee_pdata.data[13] )
				goto LABEL_43;
			pstate->ee_pdata.data[13] = 1;
		}
		else
		{
			bmask6 = swapval2 & 0x40;
			if ( !pstate->ee_pdata.data[13] )
				goto LABEL_43;
			pstate->ee_pdata.data[13] = 0;
		}
		bmask6 = swapval2 & 0x40;
LABEL_43:
		if ( bmask6 )
		{
			bmask7 = swapval2 & 0x80;
			if ( pstate->ee_pdata.data[14] )
				goto LABEL_49;
			pstate->ee_pdata.data[14] = 1;
		}
		else
		{
			bmask7 = swapval2 & 0x80;
			if ( !pstate->ee_pdata.data[14] )
				goto LABEL_49;
			pstate->ee_pdata.data[14] = 0;
		}
		bmask7 = swapval2 & 0x80;
LABEL_49:
		if ( bmask7 )
		{
			bmask8 = swapval2 & 4;
			if ( pstate->ee_pdata.data[15] )
				goto LABEL_55;
			pstate->ee_pdata.data[15] = 1;
		}
		else
		{
			bmask8 = swapval2 & 4;
			if ( !pstate->ee_pdata.data[15] )
				goto LABEL_55;
			pstate->ee_pdata.data[15] = 0;
		}
		bmask8 = swapval2 & 4;
LABEL_55:
		if ( bmask8 )
		{
			bmask9 = swapval2 & 8;
			if ( pstate->ee_pdata.data[16] )
				goto LABEL_61;
			pstate->ee_pdata.data[16] = 1;
		}
		else
		{
			bmask9 = swapval2 & 8;
			if ( !pstate->ee_pdata.data[16] )
				goto LABEL_61;
			pstate->ee_pdata.data[16] = 0;
		}
		bmask9 = swapval2 & 8;
LABEL_61:
		if ( bmask9 )
		{
			bmask10 = swapval2 & 1;
			if ( pstate->ee_pdata.data[17] )
				goto LABEL_67;
			pstate->ee_pdata.data[17] = 1;
		}
		else
		{
			bmask10 = swapval2 & 1;
			if ( !pstate->ee_pdata.data[17] )
				goto LABEL_67;
			pstate->ee_pdata.data[17] = 0;
		}
		bmask10 = swapval2 & 1;
LABEL_67:
		if ( bmask10 )
		{
			bmask11 = swapval2 & 2;
			if ( pstate->ee_pdata.data[18] )
				goto LABEL_73;
			pstate->ee_pdata.data[18] = 1;
		}
		else
		{
			bmask11 = swapval2 & 2;
			if ( !pstate->ee_pdata.data[18] )
				goto LABEL_73;
			pstate->ee_pdata.data[18] = 0;
		}
		bmask11 = swapval2 & 2;
LABEL_73:
		if ( bmask11 )
		{
			if ( !pstate->ee_pdata.data[19] )
				pstate->ee_pdata.data[19] = 1;
		}
		else if ( pstate->ee_pdata.data[19] )
		{
			pstate->ee_pdata.data[19] = 0;
		}
		return 32;
	}
	pstate->ee_pdata.data[0] = -1;
	i2 = 1;
	lval_tmp = &pstate->ee_pdata.data[1];
	do
	{
		*lval_tmp = 0;
		lval_tmp = &pstate->ee_pdata.data[++i2];
	}
	while ( i2 < 32 );
	return 0;
}

//----- (00404114) --------------------------------------------------------
u32 __cdecl padGetModeConfig(u32 port, u32 slot)
{
	return g_pad_state[port][slot].modeConfig;
}

//----- (00404158) --------------------------------------------------------
s32 __cdecl padInfoAct(u32 port, u32 slot, s32 act, u32 val)
{
	padState_t *padstate_tmp; // $v1

	padstate_tmp = &g_pad_state[port][slot];
	if ( padstate_tmp->currentTask != 1 || padstate_tmp->modeConfig < 2u )
		return 0;
	if ( act == -1 )
		return padstate_tmp->numActuators;
	if ( act >= padstate_tmp->numActuators )
		return -1;
	switch ( val )
	{
		case 1u:
			return padstate_tmp->actData[act][0];
		case 2u:
			return padstate_tmp->actData[act][1];
		case 3u:
			return padstate_tmp->actData[act][2];
		case 4u:
			return padstate_tmp->actData[act][3];
		default:
			return -1;
	}
}

//----- (00404258) --------------------------------------------------------
s32 __cdecl padInfoComb(u32 port, u32 slot, s32 val1, u32 val2)
{
	padState_t *padstate_tmp; // $v1
	s32 listno; // $v0
	u8 *combData; // $v0

	padstate_tmp = &g_pad_state[port][slot];
	if ( padstate_tmp->currentTask == 1 )
	{
		if ( padstate_tmp->modeConfig >= 2u )
		{
			if ( val1 == -1 )
				return padstate_tmp->numActComb;
			if ( val1 < padstate_tmp->numActComb )
			{
				listno = val1;
				if ( val2 == (u32)-1 )
					return padstate_tmp->combData[listno][0];
				combData = &padstate_tmp->ee_pdata.data[listno * 4];
				switch ( val2 )
				{
					case 0u:
						return combData[217];
					case 1u:
						return padstate_tmp->combData[val1][2];
					case 2u:
						return padstate_tmp->combData[val1][3];
				}
			}
		}
		return -1;
	}
	return 0;
}

//----- (00404344) --------------------------------------------------------
s32 __cdecl padInfoMode(u32 port, u32 slot, s32 val1, u32 val2)
{
	padState_t *padstate_tmp; // $v1
	unsigned int modeCurId; // $v1
	int modeCurOffs; // $v0

	padstate_tmp = &g_pad_state[port][slot];
	if ( padstate_tmp->currentTask != 1 || padstate_tmp->reqState == 2 )
		return 0;
	if ( val1 == 2 )
	{
		if ( padstate_tmp->modeConfig == 1 )
			return 0;
		modeCurOffs = padstate_tmp->modeCurOffs;
		return padstate_tmp->modeTable[modeCurOffs];
	}
	if ( val1 >= 3 )
	{
		if ( val1 == 3 )
		{
			if ( padstate_tmp->modeConfig != 1 )
				return padstate_tmp->modeCurOffs;
			return 0;
		}
		if ( val1 != 4 )
			return -1;
		if ( padstate_tmp->modeConfig == 1 )
			return 0;
		if ( val2 == (u32)-1 )
			return padstate_tmp->numModes;
		modeCurOffs = val2;
		if ( (int)val2 >= padstate_tmp->numModes )
			return 0;
		return padstate_tmp->modeTable[modeCurOffs];
	}
	if ( val1 == 1 )
	{
		modeCurId = padstate_tmp->modeCurId;
		if ( modeCurId == 243 )
			return 0;
		return modeCurId >> 4;
	}
	return -1;
}

//----- (0040447C) --------------------------------------------------------
u32 __cdecl padSetActDirect(u32 port, u32 slot, u8 *actData)
{
	padState_t *padstate_tmp1; // $s0
	int i1; // $a0
	padState_t *padstate_tmp2; // $v1
	u8 valtmp; // $v0

	padstate_tmp1 = &g_pad_state[port][slot];
	if ( padstate_tmp1->modeConfig == 1 || padstate_tmp1->currentTask != 1 )
		return 0;
	CheckAirDirectTotal(port, slot, actData);
	i1 = 0;
	padstate_tmp2 = padstate_tmp1;
	do
	{
		valtmp = actData[i1++];
		padstate_tmp2->ee_actDirectData[0] = valtmp;
		padstate_tmp2 = (padState_t *)((char *)padstate_tmp1 + i1);
	}
	while ( i1 < 6 );
	padstate_tmp1->ee_actDirectSize = 6;
	return 1;
}

//----- (0040453C) --------------------------------------------------------
u32 __cdecl padSetMainMode(u32 port, u32 slot, u32 mode, u32 lock)
{
	padState_t *padstate_tmp; // $a1
	u32 setmainmodeTid; // $a0

	padstate_tmp = &g_pad_state[port][slot];
	if ( padstate_tmp->currentTask != 1 || padstate_tmp->modeConfig < 2u || (int)mode >= padstate_tmp->numModes )
		return 0;
	if ( padstate_tmp->reqState == 2 )
		return 0;
	setmainmodeTid = padstate_tmp->setmainmodeTid;
	padstate_tmp->mode = mode;
	padstate_tmp->lock = lock;
	padstate_tmp->runTask = 4;
	padstate_tmp->reqState = 2;
	padstate_tmp->taskTid = setmainmodeTid;
	return 1;
}

//----- (004045EC) --------------------------------------------------------
u32 __cdecl padSetActAlign(u32 port, u32 slot, const u8 *actData)
{
	padState_t *padstate_tmp1; // $a1
	int i1; // $a0
	padState_t *padstate_tmp2; // $v1
	u8 valtmp; // $v0
	u32 setactalignTid; // $a0

	padstate_tmp1 = &g_pad_state[port][slot];
	if ( padstate_tmp1->currentTask != 1 )
		return 0;
	if ( padstate_tmp1->modeConfig < 2u )
		return 0;
	i1 = 0;
	if ( padstate_tmp1->reqState == 2 )
		return 0;
	padstate_tmp2 = padstate_tmp1;
	do
	{
		valtmp = actData[i1++];
		padstate_tmp2->ee_actAlignData[0] = valtmp;
		padstate_tmp2 = (padState_t *)((char *)padstate_tmp1 + i1);
	}
	while ( i1 < 6 );
	setactalignTid = padstate_tmp1->setactalignTid;
	padstate_tmp1->reqState = 2;
	padstate_tmp1->runTask = 5;
	padstate_tmp1->taskTid = setactalignTid;
	return 1;
}

//----- (004046A0) --------------------------------------------------------
u32 __cdecl padSetVrefParam(u32 port, u32 slot, const u8 *vparam)
{
	padState_t *padstate_tmp1; // $a1
	int i1; // $a0
	padState_t *padstate_tmp2; // $v1
	u8 valtmp; // $v0
	u32 setvrefparamTid; // $a0

	padstate_tmp1 = &g_pad_state[port][slot];
	if ( padstate_tmp1->currentTask != 1 )
		return 0;
	if ( padstate_tmp1->modeConfig < 2u )
		return 0;
	if ( padstate_tmp1->model < 2u )
		return 0;
	i1 = 0;
	if ( padstate_tmp1->reqState == 2 )
		return 0;
	padstate_tmp2 = padstate_tmp1;
	do
	{
		valtmp = vparam[i1++];
		padstate_tmp2->modeParam[0] = valtmp;
		padstate_tmp2 = (padState_t *)((char *)padstate_tmp1 + i1);
	}
	while ( i1 < 12 );
	setvrefparamTid = padstate_tmp1->setvrefparamTid;
	padstate_tmp1->runTask = 7;
	padstate_tmp1->reqState = 2;
	padstate_tmp1->taskTid = setvrefparamTid;
	return 1;
}

//----- (00404768) --------------------------------------------------------
u32 __cdecl padSetButtonInfo(u32 port, u32 slot, u32 info)
{
	padState_t *padstate_tmp; // $a1
	u32 infotmp; // $v0
	int i1; // $a0
	u8 *padbuf; // $v1
	u32 setbuttoninfoTid; // $a0

	padstate_tmp = &g_pad_state[port][slot];
	if ( padstate_tmp->currentTask != 1 )
		return 0;
	if ( padstate_tmp->modeConfig < 2u )
		return 0;
	if ( (padstate_tmp->model & 2) == 0 )
		return 0;
	infotmp = info << 6;
	if ( padstate_tmp->reqState == 2 )
		return 0;
	i1 = 11;
	padbuf = &padstate_tmp->ee_pdata.data[11];
	padstate_tmp->buttonInfo[1] = (unsigned __int16)(infotmp | 0x3F) >> 8;
	padstate_tmp->buttonInfo[2] = (infotmp | 0x3F) >> 16;
	padstate_tmp->buttonInfo[0] = infotmp | 0x3F;
	padstate_tmp->buttonInfo[3] = (infotmp | 0x3F) >> 24;
	do
	{
		padbuf[248] = 2;
		--i1;
		--padbuf;
	}
	while ( i1 >= 0 );
	setbuttoninfoTid = padstate_tmp->setbuttoninfoTid;
	padstate_tmp->runTask = 6;
	padstate_tmp->reqState = 2;
	padstate_tmp->taskTid = setbuttoninfoTid;
	return 1;
}

//----- (0040484C) --------------------------------------------------------
u32 __cdecl padGetButtonMask(u32 port, u32 slot)
{
	padState_t *padstate_tmp; // $a1

	padstate_tmp = &g_pad_state[port][slot];
	if ( padstate_tmp->currentTask == 1 && padstate_tmp->modeConfig >= 2u && padstate_tmp->model >= 2u )
		return padstate_tmp->buttonMask[0]
				 + (padstate_tmp->buttonMask[1] << 8)
				 + (padstate_tmp->buttonMask[2] << 16)
				 + (padstate_tmp->buttonMask[3] << 24);
	else
		return 0;
}

//----- (004048F0) --------------------------------------------------------
u32 padGetPortMax(void)
{
	return 2;
}

//----- (004048F8) --------------------------------------------------------
u32 __cdecl padGetSlotMax(u32 port)
{
	return sio2_mtap_get_slot_max(port);
}

//----- (00404918) --------------------------------------------------------
int padGetVersion(void)
{
	return (unsigned __int16)_irx_id.v;
}

//----- (00404928) --------------------------------------------------------
int __cdecl padSetVerbose(int val)
{
	g_padman_verbose = val;
	return 1;
}
// 4082F8: using guessed type int g_padman_verbose;

//----- (00404938) --------------------------------------------------------
int __cdecl padSetNonblockDma(int val)
{
	g_padman_nonblock_dma = val;
	return 1;
}
// 40929C: using guessed type int g_padman_nonblock_dma;

//----- (00404950) --------------------------------------------------------
u32 __cdecl readStat6cBit(u32 bit, sio2_transfer_data_t *td)
{
	return (td->stat6c & (0x10000 << bit)) != 0;
}

//----- (00404968) --------------------------------------------------------
void pdReset(void)
{
	int i1; // $a1
	int indexi; // $a0
	int i2; // $v1
	int ptroffs; // $v0

	i1 = 0;
	indexi = 0;
	i2 = 3;
	do
	{
		ptroffs = indexi * 416 + 312;
		do
		{
			*(u32 *)((char *)&padData[0][0].active + ptroffs) = 0;
			--i2;
			ptroffs -= 104;
		}
		while ( i2 >= 0 );
		padData[++indexi][0].stat70bit = 0;
		++i1;
		i2 = 3;
	}
	while ( i1 < 2 );
	sio2_td.in = (u8 *)g_td_in_buf;
	sio2_td.out = (u8 *)g_td_out_buf;
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;
// 4096A8: using guessed type int g_td_in_buf[64];
// 4097A8: using guessed type int g_td_out_buf[66];

//----- (004049D8) --------------------------------------------------------
void __cdecl do_set_unused_4_pad(int port, int slot, u32 val)
{
	padData[port][slot].unused_4 = val;
}

//----- (00404A18) --------------------------------------------------------
u32 __cdecl pdSetActive(u32 port, u32 slot, u32 active)
{
	u32 ptroffs; // $v1
	u32 result; // $v0

	ptroffs = 104 * slot + 416 * port;
	result = *(u32 *)((char *)&padData[0][0].active + ptroffs);
	*(u32 *)((char *)&padData[0][0].active + ptroffs) = active;
	return result;
}

//----- (00404A64) --------------------------------------------------------
u32 __cdecl pdIsActive(u32 port, u32 slot)
{
	return padData[port][slot].active;
}

//----- (00404AA4) --------------------------------------------------------
u32 __cdecl pdSetStat70bit(u32 port, u32 slot, u32 val)
{
	u32 ptroffs; // $v1
	u32 result; // $v0

	ptroffs = 104 * slot + 416 * port;
	result = *(u32 *)((char *)&padData[0][0].stat70bit + ptroffs);
	*(u32 *)((char *)&padData[0][0].stat70bit + ptroffs) = val;
	return result;
}

//----- (00404AF0) --------------------------------------------------------
u32 __cdecl pdGetStat70bit(u32 port, u32 slot)
{
	return padData[port][slot].stat70bit;
}

//----- (00404B30) --------------------------------------------------------
u32 __cdecl setupTransferData(u32 index, u32 port, u32 slot)
{
	padData_t *p_padData; // $s0
	u32 port_cur; // $v1
	u32 index_cur; // $a0

	p_padData = &padData[port][slot];
	memcpy(&sio2_td.in[sio2_td.in_size], p_padData->in_buffer, p_padData->in_size);
	sio2_td.in_size += p_padData->in_size;
	port_cur = port;
	sio2_td.out_size += p_padData->out_size;
	index_cur = index++;
	sio2_td.port_ctrl1[port_cur] = p_padData->port_ctrl1;
	sio2_td.port_ctrl2[port_cur] = p_padData->port_ctrl2;
	sio2_td.regdata[index_cur] = (p_padData->reg_data & 0xFFFFFFFC) | (port & 3);
	sio2_td.regdata[index] = 0;
	return index;
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;

//----- (00404C4C) --------------------------------------------------------
u32 __cdecl readSio2OutBuffer(u32 bit, u32 port, u32 slot)
{
	u32 ptroffs; // $v0
	int outsize_old; // $v1
	int slotoffs1; // $a3
	u32 slotstuff; // $v1
	u32 slotoffs2; // $v1
	u32 out_size_plus_1; // $a1

	if ( ((sio2_td.stat6c >> 13) & 1) == 1 )
	{
		padData[port][slot].error = 1;
		return 0;
	}
	else if ( readStat6cBit(bit, &sio2_td) == 1 )
	{
		padData[port][slot].error = 1;
		return 0;
	}
	else
	{
		ptroffs = 104 * slot + 416 * port;
		outsize_old = *(u32 *)((char *)&padData[0][0].out_size + ptroffs);
		*(u32 *)((char *)&padData[0][0].error + ptroffs) = 0;
		slotoffs1 = 0;
		if ( outsize_old > 0 )
		{
			slotstuff = 3 * slot;
			do
			{
				slotoffs2 = 8 * (4 * slotstuff + slot);
				out_size_plus_1 = sio2_td.out_size + 1;
				padData[port][0].out_buffer[slotoffs1 + slotoffs2] = sio2_td.out[sio2_td.out_size];
				sio2_td.out_size = out_size_plus_1;
				slotstuff = 3 * slot;
			}
			while ( ++slotoffs1 < *(signed __int32 *)((char *)&padData[port][0].out_size + slotoffs2) );
		}
		return 1;
	}
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;

//----- (00404DF8) --------------------------------------------------------
u32 __cdecl padTransfer(u32 slot)
{
	int xferdatres; // $a0
	int port_i; // $s1
	u32 unused_4; // $v0
	u32 port; // $s0
	u32 port_1; // $s7
	u32 slot_mul; // $v0
	u32 slot_offs; // $a1
	u32 port_2; // $s0
	int i; // $s1
	u32 stat70; // $s0
	int chslot_buf_tmp[2]; // [sp+10h] [-10h]
	int porttmp[2]; // [sp+18h] [-8h]

	xferdatres = 0;
	port_i = 0;
	sio2_td.in_size = 0;
	sio2_td.out_size = 0;
	sio2_td.out_dma.addr = NULL;
	sio2_td.in_dma.addr = NULL;
	unused_4 = padData[1][slot].unused_4;
	chslot_buf_tmp[1] = 0;
	chslot_buf_tmp[0] = 0;
	porttmp[1] = 0;
	porttmp[0] = 0;
	port = unused_4 == 0x63;
	port_1 = port;
	do
	{
		if ( padData[port][slot].active && change_slot_buffer[port + 4] == 1 )
		{
			chslot_buf_tmp[port] = 1;
			porttmp[port] = xferdatres;
			xferdatres = setupTransferData(xferdatres, port, slot);
		}
		++port_i;
		port ^= 1u;
	}
	while ( port_i < 2 );
	if ( slot )
	{
		slot_mul = 2 * slot;
		if ( padData[0][slot].active == 1 )
		{
			if ( change_slot_buffer[4] != 1 )
				padData[0][slot].error = 10;
			slot_mul = 2 * slot;
		}
		slot_offs = 8 * (4 * (slot_mul + slot) + slot);
		if ( *(u32 *)((char *)&padData[1][0].active + slot_offs) == 1 && change_slot_buffer[5] != 1 )
			*(u32 *)((char *)&padData[1][0].error + slot_offs) = 10;
	}
	if ( xferdatres )
	{
		sio2_transfer2(&sio2_td);
		sio2_td.out_size = 0;
		port_2 = port_1;
		for ( i = 0; i < 2; ++i )
		{
			if ( chslot_buf_tmp[port_2] == 1 )
			{
				readSio2OutBuffer(porttmp[port_2], port_2, slot);
				sio2_td.out_size = padData[port_2][slot].out_size;
			}
			port_2 ^= 1u;
		}
		stat70 = sio2_stat70_get();
		pdSetStat70bit(0, slot, (stat70 >> 4) & 1);
		pdSetStat70bit(1u, slot, (stat70 >> 5) & 1);
		return 1;
	}
	return 0;
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;

//----- (004050B0) --------------------------------------------------------
u32 __cdecl mtapChangeSlot(u32 slot)
{
	u32 slot_offs; // $v0
	u32 slot_offs2; // $v1

	change_slot_buffer[0] = -1;
	change_slot_buffer[1] = -1;
	change_slot_buffer[2] = -1;
	change_slot_buffer[3] = -1;
	slot_offs = 2 * slot;
	if ( !padData[0][slot].active )
	{
		slot_offs = 2 * slot;
		if ( !padData[1][slot].active )
			return 0;
	}
	slot_offs2 = 8 * (4 * (slot_offs + slot) + slot);
	if ( *(u32 *)((char *)&padData[0][0].active + slot_offs2) == 1 )
		change_slot_buffer[0] = slot;
	if ( *(u32 *)((char *)&padData[1][0].active + slot_offs2) == 1 )
		change_slot_buffer[1] = slot;
	sio2_mtap_change_slot(change_slot_buffer);
	return 1;
}

//----- (00405194) --------------------------------------------------------
void pdTransfer(void)
{
	signed __int32 slot; // $s0
	int portx; // $s1

	sio2_pad_transfer_init2();
	slot = 0;
	portx = 0;
	++transferCount;
	do
	{
		if ( padData[0][portx].active == 1 || padData[1][portx].active == 1 )
		{
			if ( slot > 0 )
				mtapChangeSlot(slot);
			padTransfer(slot);
		}
		++slot;
		++portx;
	}
	while ( slot < 4 );
	mtapChangeSlot(0);
	sio2_transfer_reset2();
}
// 408310: using guessed type int transferCount;

//----- (00405250) --------------------------------------------------------
u32 __cdecl pdSetCtrl1(u32 port, u32 slot, u32 ctrl)
{
	if ( port >= 2 )
		return 0;
	padData[port][slot].port_ctrl1 = ctrl;
	return 1;
}

//----- (004052A0) --------------------------------------------------------
u32 __cdecl pdSetCtrl2(u32 port, u32 slot, u32 ctrl)
{
	if ( port >= 2 )
		return 0;
	padData[port][slot].port_ctrl2 = ctrl;
	return 1;
}

//----- (004052F0) --------------------------------------------------------
u32 __cdecl pdSetRegData(u32 port, u32 slot, u32 reg_data)
{
	if ( port >= 2 )
		return 0;
	padData[port][slot].reg_data = reg_data;
	return 1;
}

//----- (00405340) --------------------------------------------------------
s32 __cdecl pdGetError(u32 port, u32 slot)
{
	if ( port >= 2 )
		return -1;
	else
		return padData[port][slot].error;
}

//----- (00405390) --------------------------------------------------------
u32 __cdecl pdSetInSize(u32 port, u32 slot, u32 size)
{
	if ( port >= 2 )
		return 0;
	padData[port][slot].in_size = size;
	return size;
}

//----- (004053E0) --------------------------------------------------------
u32 __cdecl pdSetInBuffer(u32 port, u32 slot, u32 size, const u8 *buf)
{
	signed __int32 i1; // $t0
	u32 slotoffs; // $a1
	u32 portoffs; // $a0
	u32 slotoffs_1; // $v0
	u8 *valrval; // $v1

	if ( port < 2 )
	{
		if ( !size )
			size = padData[port][slot].in_size;
		i1 = 0;
		if ( (int)size > 0 )
		{
			slotoffs = 104 * slot;
			portoffs = 416 * port;
			slotoffs_1 = slotoffs;
			do
			{
				valrval = (u8 *)&buf[i1++];
				padData[0][0].in_buffer[slotoffs_1 + portoffs] = *valrval;
				slotoffs_1 = i1 + slotoffs;
			}
			while ( i1 < (int)size );
		}
		return size;
	}
	return 0;
}

//----- (00405498) --------------------------------------------------------
u32 __cdecl pdSetOutSize(u32 port, u32 slot, u32 size)
{
	if ( port >= 2 )
		return 0;
	padData[port][slot].out_size = size;
	return size;
}

//----- (004054E8) --------------------------------------------------------
u32 __cdecl pdGetOutBuffer(u32 port, u32 slot, u32 size, u8 *buf)
{
	signed __int32 i1; // $t0
	u32 slotoffs; // $a1
	u32 portoffs; // $a0
	u8 *bufbuf; // $v1
	u8 valrval; // $v0

	if ( port < 2 )
	{
		if ( !size )
			size = padData[port][slot].out_size;
		i1 = 0;
		if ( (int)size > 0 )
		{
			slotoffs = 104 * slot;
			portoffs = 416 * port;
			bufbuf = buf;
			do
			{
				valrval = padData[0][0].out_buffer[i1 + slotoffs + portoffs];
				++i1;
				*bufbuf = valrval;
				bufbuf = &buf[i1];
			}
			while ( i1 < (int)size );
		}
		return size;
	}
	return 0;
}

//----- (004055A0) --------------------------------------------------------
int __fastcall unusedref_4055A0(unsigned int port, u32 slot, u32 port_ctrl)
{
	u32 PortCtrl1; // $v0
	u32 PortCtrl2; // $v0
	u32 RegData; // $v0
	u32 insztmp; // $v0
	u32 OutSize; // $v0
	u8 inbuftmp[32]; // [sp+10h] [-20h] BYREF

	PortCtrl1 = sio2CmdGetPortCtrl1(0, port_ctrl, 0);
	pdSetCtrl1(port, slot, PortCtrl1);
	PortCtrl2 = sio2CmdGetPortCtrl2(0, port_ctrl);
	pdSetCtrl2(port, slot, PortCtrl2);
	RegData = pdGetRegData(0);
	pdSetRegData(port, slot, RegData);
	insztmp = pdGetInSize(0);
	pdSetInSize(port, slot, insztmp);
	OutSize = pdGetOutSize(0);
	pdSetOutSize(port, slot, OutSize);
	sio2CmdSetReadData(0, inbuftmp);
	pdSetInBuffer(port, slot, 0, inbuftmp);
	return 1;
}

//----- (00405680) --------------------------------------------------------
int __fastcall unusedref_405680(u32 port, u32 slot)
{
	u32 port_tmp; // $s5
	u32 stat70_tmp; // $v0
	u32 stat70_tmp_1; // $s2
	u32 paddata_offs; // $v1

	port_tmp = port;
	sio2_td.in_size = 0;
	sio2_td.out_size = 0;
	sio2_td.out_dma.addr = NULL;
	sio2_td.in_dma.addr = NULL;
	if ( change_slot_buffer[port + 4] != 1 )
		return 0;
	stat70_tmp = sio2_stat70_get();
	stat70_tmp_1 = stat70_tmp;
	if ( !port )
		pdSetStat70bit(0, slot, (stat70_tmp >> 4) & 1);
	if ( port == 1 )
		pdSetStat70bit(1u, slot, (stat70_tmp_1 >> 5) & 1);
	setupTransferData(0, port, slot);
	sio2_transfer2(&sio2_td);
	sio2_td.out_size = 0;
	readSio2OutBuffer(0, port, slot);
	paddata_offs = 104 * slot + 416 * port;
	sio2_td.out_size = *(u32 *)((char *)&padData[0][0].out_size + paddata_offs);
	if ( change_slot_buffer[port_tmp + 4] != 1 )
		*(u32 *)((char *)&padData[0][0].error + paddata_offs) = 10;
	return 1;
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;

//----- (004057D4) --------------------------------------------------------
int __fastcall unused_4057D4(u32 port, s32 slot)
{
	int retres; // $s4
	u32 Stat70bit; // $v0
	u32 bit70stuff; // $v0

	retres = 0;
	sio2_pad_transfer_init2();
	change_slot_buffer[2] = -1;
	change_slot_buffer[3] = -1;
	change_slot_buffer[0] = slot;
	change_slot_buffer[1] = slot;
	sio2_mtap_change_slot(change_slot_buffer);
	Stat70bit = pdGetStat70bit(0, slot);
	unusedref_4055A0(0, slot, Stat70bit);
	bit70stuff = pdGetStat70bit(1u, slot);
	unusedref_4055A0(1u, slot, bit70stuff);
	if ( unusedref_405680(port, slot) == 1 )
		retres = padData[port][slot].error == 0;
	change_slot_buffer[2] = -1;
	change_slot_buffer[3] = -1;
	change_slot_buffer[0] = 0;
	change_slot_buffer[1] = 0;
	sio2_mtap_change_slot(change_slot_buffer);
	sio2_transfer_reset2();
	return retres;
}

//----- (00405910) --------------------------------------------------------
void sio2cmdReset(void)
{
	int i1; // $v1
	int i2; // $v0

	i1 = 15;
	i2 = 15;
	do
	{
		sio2Cmds[i2].id = 0;
		--i1;
		--i2;
	}
	while ( i1 >= 0 );
	numControllers = 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405940) --------------------------------------------------------
int __cdecl SetupCmds(const sio2Cmds_t *s)
{
	int ix1; // $v1
	int ix2; // $a0
	int i1; // $a1
	int i2; // $v1
	u32 (__cdecl *setactalign)(u8 *); // $a0

	if ( numControllers + 1 >= 16 || !s )
		return 0;
	ix1 = 0;
	if ( numControllers > 0 )
	{
		ix2 = 0;
		do
		{
			++ix1;
			if ( s->id == sio2Cmds[ix2].id )
				return 0;
			++ix2;
		}
		while ( ix1 < numControllers );
	}
	sio2Cmds[numControllers].id = s->id;
	i1 = numControllers;
	i2 = numControllers;
	sio2Cmds[i2].readdata = s->readdata;
	sio2Cmds[i2].getportctrl1 = s->getportctrl1;
	sio2Cmds[i2].getportctrl2 = s->getportctrl2;
	sio2Cmds[i2].reg_data = s->reg_data;
	sio2Cmds[i2].size1 = s->size1;
	sio2Cmds[i2].size2 = s->size2;
	sio2Cmds[i2].enterconfigmode = s->enterconfigmode;
	sio2Cmds[i2].exitconfigmode = s->exitconfigmode;
	sio2Cmds[i2].querymodel = s->querymodel;
	sio2Cmds[i2].queryact = s->queryact;
	sio2Cmds[i2].querycomb = s->querycomb;
	sio2Cmds[i2].querymode = s->querymode;
	sio2Cmds[i2].querybuttonmask = s->querybuttonmask;
	sio2Cmds[i2].setbuttoninfo = s->setbuttoninfo;
	sio2Cmds[i2].setvrefparam = s->setvrefparam;
	sio2Cmds[i2].setmainmode = s->setmainmode;
	setactalign = s->setactalign;
	numControllers = i1 + 1;
	sio2Cmds[i2].setactalign = setactalign;
	return 1;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405B0C) --------------------------------------------------------
u32 __cdecl sio2cmdCheckId(u8 id)
{
	int id_hi; // $a0
	int i2; // $v1
	int i; // $a1

	id_hi = id >> 4;
	i2 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		++i2;
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
			break;
		if ( i2 >= numControllers )
			return 0;
	}
	return 1;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405B68) --------------------------------------------------------
void __cdecl sio2CmdSetReadData(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	void (__cdecl *readdata)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers > 0 )
	{
		for ( i = 0; ; ++i )
		{
			if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
			{
				readdata = sio2Cmds[i].readdata;
				if ( readdata )
					break;
			}
			if ( ++i1 >= numControllers )
				return;
		}
		((void (__fastcall *)(u8 *))readdata)(buf);
	}
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405BF8) --------------------------------------------------------
u32 __cdecl sio2CmdGetPortCtrl1(u8 id, u32 b, u8 c)
{
	int id_hi; // $a0
	int i1; // $a3
	int i; // $v1
	u32 (__cdecl *getportctrl1)(u32, u32); // $v0

	id_hi = id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			getportctrl1 = sio2Cmds[i].getportctrl1;
			if ( getportctrl1 )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return getportctrl1(b, c);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405C90) --------------------------------------------------------
u32 __cdecl sio2CmdGetPortCtrl2(u32 id, u32 b)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *getportctrl2)(u32); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			getportctrl2 = sio2Cmds[i].getportctrl2;
			if ( getportctrl2 )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u32))getportctrl2)(b);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405D24) --------------------------------------------------------
u32 __cdecl pdGetInSize(u8 id)
{
	if ( !id )
		id = 0x41;
	return 2 * (id & 0xF) + 3;
}

//----- (00405D44) --------------------------------------------------------
u32 __cdecl pdGetOutSize(u8 id)
{
	if ( !id )
		id = 0x41;
	return 2 * (id & 0xF) + 3;
}

//----- (00405D64) --------------------------------------------------------
u32 __cdecl pdGetRegData(u32 id)
{
	u8 id_low; // $s0
	u32 bor_tmp; // $s1

	id_low = id;
	bor_tmp = ((pdGetInSize(id) & 0x1FF) << 8) | 0x40;
	return bor_tmp | ((pdGetOutSize(id_low) & 0x1FF) << 18);
}

//----- (00405DB4) --------------------------------------------------------
u32 __cdecl sio2CmdSetEnterConfigMode(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *enterconfigmode)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			enterconfigmode = sio2Cmds[i].enterconfigmode;
			if ( enterconfigmode )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))enterconfigmode)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405E48) --------------------------------------------------------
u32 __cdecl sio2CmdSetExitConfigMode(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *exitconfigmode)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			exitconfigmode = sio2Cmds[i].exitconfigmode;
			if ( exitconfigmode )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))exitconfigmode)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405EDC) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryModel(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *querymodel)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			querymodel = sio2Cmds[i].querymodel;
			if ( querymodel )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))querymodel)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405F70) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryAct(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *queryact)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			queryact = sio2Cmds[i].queryact;
			if ( queryact )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))queryact)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00406004) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryComb(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *querycomb)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			querycomb = sio2Cmds[i].querycomb;
			if ( querycomb )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))querycomb)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00406098) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryMode(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *querymode)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			querymode = sio2Cmds[i].querymode;
			if ( querymode )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))querymode)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (0040612C) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryButtonMask(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *querybuttonmask)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			querybuttonmask = sio2Cmds[i].querybuttonmask;
			if ( querybuttonmask )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))querybuttonmask)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (004061C0) --------------------------------------------------------
u32 __cdecl sio2CmdSetSetButtonInfo(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *setbuttoninfo)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			setbuttoninfo = sio2Cmds[i].setbuttoninfo;
			if ( setbuttoninfo )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))setbuttoninfo)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00406254) --------------------------------------------------------
u32 __cdecl sio2CmdSetSetVrefParam(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *setvrefparam)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			setvrefparam = sio2Cmds[i].setvrefparam;
			if ( setvrefparam )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))setvrefparam)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (004062E8) --------------------------------------------------------
u32 __cdecl sio2CmdSetSetMainMode(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *setmainmode)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			setmainmode = sio2Cmds[i].setmainmode;
			if ( setmainmode )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))setmainmode)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (0040637C) --------------------------------------------------------
u32 __cdecl sio2CmdSetSetActAlign(u32 id, u8 *buf)
{
	int id_hi; // $a0
	int i1; // $a2
	int i; // $v1
	u32 (__cdecl *setactalign)(u8 *); // $v0

	id_hi = (unsigned __int8)id >> 4;
	i1 = 0;
	if ( numControllers <= 0 )
		return 0;
	for ( i = 0; ; ++i )
	{
		if ( (unsigned __int8)id_hi == sio2Cmds[i].id )
		{
			setactalign = sio2Cmds[i].setactalign;
			if ( setactalign )
				break;
		}
		if ( ++i1 >= numControllers )
			return 0;
	}
	return ((int (__fastcall *)(u8 *))setactalign)(buf);
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00406410) --------------------------------------------------------
void __cdecl FindPadsReadData(u8 *a)
{
	*a = 1;
	*(_WORD *)(a + 1) = 0x42;
	a[3] = 0;
	a[4] = 0;
}

//----- (00406430) --------------------------------------------------------
u32 __cdecl FindPadsGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (00406450) --------------------------------------------------------
u32 __cdecl FindPadsGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x2000A;
}

//----- (00406470) --------------------------------------------------------
u32 FindPadsGetSize1(void)
{
	return 5;
}

//----- (00406478) --------------------------------------------------------
u32 FindPadsGetSize2(void)
{
	return 5;
}

//----- (00406480) --------------------------------------------------------
u32 FindPadsRegData(void)
{
	u32 bor_tmp; // $s0

	bor_tmp = ((FindPadsGetSize1() & 0x1FF) << 8) | 0x40;
	return bor_tmp | ((FindPadsGetSize2() & 0x1FF) << 18);
}

//----- (004064BC) --------------------------------------------------------
u32 __cdecl FindPadsEnterConfigMode(u8 *a)
{
	(void)a;

	return 0;
}

//----- (004064C4) --------------------------------------------------------
void sio2cmdInitFindPads(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.readdata = (void (__cdecl *)(u8 *))FindPadsReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))FindPadsGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))FindPadsGetPortCtrl2;
	s.reg_data = (u32 (*)(void))FindPadsRegData;
	s.size1 = (u32 (*)(void))FindPadsGetSize1;
	s.size2 = (u32 (*)(void))FindPadsGetSize2;
	s.id = 0;
	s.enterconfigmode = (u32 (__cdecl *)(u8 *))FindPadsEnterConfigMode;
	memset(&s.exitconfigmode, 0, 40);
	SetupCmds(&s);
}

//----- (00406570) --------------------------------------------------------
void __cdecl MouseReadData(u8 *a)
{
	*a = 1;
	*(_WORD *)(a + 1) = 0x42;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
}

//----- (00406598) --------------------------------------------------------
u32 __cdecl MouseGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (004065B8) --------------------------------------------------------
u32 __cdecl MouseGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (004065D8) --------------------------------------------------------
u32 MouseRegData(void)
{
	return 0x1C0740;
}

//----- (004065E4) --------------------------------------------------------
u32 MouseSize1(void)
{
	return 7;
}

//----- (004065EC) --------------------------------------------------------
u32 MouseSize2(void)
{
	return 7;
}

//----- (004065F4) --------------------------------------------------------
u32 __cdecl MouseEnterConfigMode(u8 *a)
{
	a[1] = 0x43;
	*a = 1;
	a[2] = 0;
	*(_WORD *)(a + 3) = 1;
	a[5] = 0;
	a[6] = 0;
	return 7;
}

//----- (00406620) --------------------------------------------------------
void sio2cmdInitMouse(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.id = 1;
	s.readdata = (void (__cdecl *)(u8 *))MouseReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))MouseGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))MouseGetPortCtrl2;
	s.reg_data = (u32 (*)(void))MouseRegData;
	s.size1 = (u32 (*)(void))MouseSize1;
	s.size2 = (u32 (*)(void))MouseSize2;
	s.enterconfigmode = (u32 (__cdecl *)(u8 *))MouseEnterConfigMode;
	memset(&s.exitconfigmode, 0, 40);
	SetupCmds(&s);
}

//----- (004066D0) --------------------------------------------------------
void __cdecl DigitalReadData(u8 *a)
{
	*a = 1;
	*(_WORD *)(a + 1) = 0x42;
	a[3] = 0;
	a[4] = 0;
}

//----- (004066F0) --------------------------------------------------------
u32 __cdecl DigitalGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (00406710) --------------------------------------------------------
u32 __cdecl DigitalGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (00406730) --------------------------------------------------------
u32 DigitalRegData(void)
{
	return 0x140540;
}

//----- (0040673C) --------------------------------------------------------
u32 DigitalSize1(void)
{
	return 5;
}

//----- (00406744) --------------------------------------------------------
u32 DigitalSize2(void)
{
	return 5;
}

//----- (0040674C) --------------------------------------------------------
u32 __cdecl DigitalEnterConfigMode(u8 *a)
{
	a[1] = 0x43;
	*a = 1;
	a[2] = 0;
	*(_WORD *)(a + 3) = 1;
	return 5;
}

//----- (00406770) --------------------------------------------------------
void sio2cmdInitDigital(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.id = 4;
	s.readdata = (void (__cdecl *)(u8 *))DigitalReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))DigitalGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))DigitalGetPortCtrl2;
	s.reg_data = (u32 (*)(void))DigitalRegData;
	s.size1 = (u32 (*)(void))DigitalSize1;
	s.size2 = (u32 (*)(void))DigitalSize2;
	s.enterconfigmode = (u32 (__cdecl *)(u8 *))DigitalEnterConfigMode;
	memset(&s.exitconfigmode, 0, 40);
	SetupCmds(&s);
}

//----- (00406820) --------------------------------------------------------
void __cdecl AnalogReadData(u8 *a)
{
	*a = 1;
	*(_WORD *)(a + 1) = 0x42;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	a[9] = 0;
	a[10] = 0;
	a[11] = 0;
	a[12] = 0;
	a[13] = 0;
	a[14] = 0;
}

//----- (00406868) --------------------------------------------------------
u32 __cdecl AnalogGetPortCtrl1(u32 a, u32 b)
{
	u32 tempbtest; // $a1
	unsigned __int8 val1; // $v0
	int val2; // $a0
	int val3; // $v1
	int val4; // $a0

	if ( a )
		return 0xFF060505;
	tempbtest = b & 2;
	val1 = 5;
	if ( tempbtest )
		val1 = 10;
	val2 = 5;
	if ( tempbtest )
		val2 = 10;
	val3 = val1 | (val2 << 8);
	val4 = 0xC0;
	if ( tempbtest )
		val4 = 0x60;
	return (val3 & 0xFF00FFFF) | (val4 << 16) | 0xFF000000;
}

//----- (004068DC) --------------------------------------------------------
u32 __cdecl AnalogGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (004068FC) --------------------------------------------------------
u32 __cdecl AnalogEnterConfigMode(u8 *a)
{
	a[1] = 0x43;
	*a = 1;
	a[2] = 0;
	*(_WORD *)(a + 3) = 1;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	a[9] = 0;
	a[10] = 0;
	a[11] = 0;
	a[12] = 0;
	a[13] = 0;
	a[14] = 0;
	return 0x15;
}

//----- (00406948) --------------------------------------------------------
void sio2cmdInitAnalog(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.id = 7;
	s.readdata = (void (__cdecl *)(u8 *))AnalogReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))AnalogGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))AnalogGetPortCtrl2;
	memset(&s.reg_data, 0, 12);
	s.enterconfigmode = (u32 (__cdecl *)(u8 *))AnalogEnterConfigMode;
	memset(&s.exitconfigmode, 0, 40);
	SetupCmds(&s);
}

//----- (004069E0) --------------------------------------------------------
void __cdecl NegiconReadData(u8 *a)
{
	*a = 1;
	*(_WORD *)(a + 1) = 0x42;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
}

//----- (00406A10) --------------------------------------------------------
u32 __cdecl NegiconGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (00406A30) --------------------------------------------------------
u32 __cdecl NegiconGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (00406A50) --------------------------------------------------------
u32 NegiconRegData(void)
{
	return 0x240940;
}

//----- (00406A5C) --------------------------------------------------------
u32 NegiconSize1(void)
{
	return 9;
}

//----- (00406A64) --------------------------------------------------------
u32 NegiconSize2(void)
{
	return 9;
}

//----- (00406A6C) --------------------------------------------------------
u32 __cdecl NegiconEnterConfigMode(u8 *a)
{
	a[1] = 0x43;
	*a = 1;
	a[2] = 0;
	*(_WORD *)(a + 3) = 1;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	return 9;
}

//----- (00406AA0) --------------------------------------------------------
void sio2cmdInitNegicon(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.id = 2;
	s.readdata = (void (__cdecl *)(u8 *))NegiconReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))NegiconGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))NegiconGetPortCtrl2;
	s.reg_data = (u32 (*)(void))NegiconRegData;
	s.size1 = (u32 (*)(void))NegiconSize1;
	s.size2 = (u32 (*)(void))NegiconSize2;
	s.enterconfigmode = (u32 (__cdecl *)(u8 *))NegiconEnterConfigMode;
	memset(&s.exitconfigmode, 0, 40);
	SetupCmds(&s);
}

//----- (00406B50) --------------------------------------------------------
void __cdecl JoystickReadData(u8 *a)
{
	*a = 1;
	*(_WORD *)(a + 1) = 0x42;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
}

//----- (00406B80) --------------------------------------------------------
u32 __cdecl JoystickGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (00406BA0) --------------------------------------------------------
u32 __cdecl JoystickGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (00406BC0) --------------------------------------------------------
u32 JoystickRegData(void)
{
	return 0x240940;
}

//----- (00406BCC) --------------------------------------------------------
u32 JoystickSize1(void)
{
	return 9;
}

//----- (00406BD4) --------------------------------------------------------
u32 JoystickSize2(void)
{
	return 9;
}

//----- (00406BDC) --------------------------------------------------------
u32 __cdecl JoystickEnterConfigMode(u8 *a)
{
	a[1] = 0x43;
	*a = 1;
	a[2] = 0;
	*(_WORD *)(a + 3) = 1;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	return 9;
}

//----- (00406C10) --------------------------------------------------------
void sio2cmdInitJoystick(void)
{
	sio2Cmds_t v0; // [sp+10h] [-48h] BYREF

	v0.id = 5;
	v0.readdata = (void (__cdecl *)(u8 *))JoystickReadData;
	v0.getportctrl1 = (u32 (__cdecl *)(u32, u32))JoystickGetPortCtrl1;
	v0.getportctrl2 = (u32 (__cdecl *)(u32))JoystickGetPortCtrl2;
	v0.reg_data = (u32 (*)(void))JoystickRegData;
	v0.size1 = (u32 (*)(void))JoystickSize1;
	v0.size2 = (u32 (*)(void))JoystickSize2;
	v0.enterconfigmode = (u32 (__cdecl *)(u8 *))JoystickEnterConfigMode;
	memset(&v0.exitconfigmode, 0, 40);
	SetupCmds(&v0);
}

//----- (00406CC0) --------------------------------------------------------
void __cdecl KonamiGunReadData(u8 *a)
{
	*a = 1;
	a[1] = 0x42;
	a[2] = 0;
	*(_WORD *)(a + 3) = 0x10;
}

//----- (00406CE4) --------------------------------------------------------
u32 __cdecl KonamiGunGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (00406D04) --------------------------------------------------------
u32 __cdecl KonamiGunGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (00406D24) --------------------------------------------------------
u32 KonamiGunRegData(void)
{
	return 0x140540;
}

//----- (00406D30) --------------------------------------------------------
u32 KonamiGunSize1(void)
{
	return 5;
}

//----- (00406D38) --------------------------------------------------------
u32 KonamiGunSize2(void)
{
	return 5;
}

//----- (00406D40) --------------------------------------------------------
u32 __cdecl KonamiGunEnterConfigMode(u8 *a)
{
	a[1] = 0x43;
	*a = 1;
	a[2] = 0;
	*(_WORD *)(a + 3) = 1;
	return 5;
}

//----- (00406D64) --------------------------------------------------------
void sio2cmdInitKonamiGun(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.id = 3;
	s.readdata = (void (__cdecl *)(u8 *))KonamiGunReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))KonamiGunGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))KonamiGunGetPortCtrl2;
	s.reg_data = (u32 (*)(void))KonamiGunRegData;
	s.size1 = (u32 (*)(void))KonamiGunSize1;
	s.size2 = (u32 (*)(void))KonamiGunSize2;
	s.enterconfigmode = (u32 (__cdecl *)(u8 *))KonamiGunEnterConfigMode;
	memset(&s.exitconfigmode, 0, 40);
	SetupCmds(&s);
}

//----- (00406E10) --------------------------------------------------------
void __cdecl NamcoGunReadData(u8 *a)
{
	*a = 1;
	*(_WORD *)(a + 1) = 0x42;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
}

//----- (00406E40) --------------------------------------------------------
u32 __cdecl NamcoGunGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (00406E60) --------------------------------------------------------
u32 __cdecl NamcoGunGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (00406E80) --------------------------------------------------------
u32 NamcoGunRegData(void)
{
	return 0x240940;
}

//----- (00406E8C) --------------------------------------------------------
u32 NamcoGunSize1(void)
{
	return 9;
}

//----- (00406E94) --------------------------------------------------------
u32 NamcoGunSize2(void)
{
	return 9;
}

//----- (00406E9C) --------------------------------------------------------
u32 __cdecl NamcoGunEnterConfigMode(u8 *a)
{
	a[1] = 0x43;
	*a = 1;
	a[2] = 0;
	*(_WORD *)(a + 3) = 1;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	return 9;
}

//----- (00406ED0) --------------------------------------------------------
void sio2cmdInitNamcoGun(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.id = 6;
	s.readdata = (void (__cdecl *)(u8 *))NamcoGunReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))NamcoGunGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))NamcoGunGetPortCtrl2;
	s.reg_data = (u32 (*)(void))NamcoGunRegData;
	s.size1 = (u32 (*)(void))NamcoGunSize1;
	s.size2 = (u32 (*)(void))NamcoGunSize2;
	s.enterconfigmode = (u32 (__cdecl *)(u8 *))NamcoGunEnterConfigMode;
	memset(&s.exitconfigmode, 0, 40);
	SetupCmds(&s);
}

//----- (00406F80) --------------------------------------------------------
void __cdecl JogconReadData(u8 *a)
{
	*a = 1;
	*(_WORD *)(a + 1) = 0x42;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	a[9] = 0;
	a[10] = 0;
	a[11] = 0;
	a[12] = 0;
}

//----- (00406FC0) --------------------------------------------------------
u32 __cdecl JogconGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (00406FE0) --------------------------------------------------------
u32 __cdecl JogconGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (00407000) --------------------------------------------------------
u32 JogconRegData(void)
{
	return 0x340D40;
}

//----- (0040700C) --------------------------------------------------------
u32 JogconSize1(void)
{
	return 13;
}

//----- (00407014) --------------------------------------------------------
u32 JogconSize2(void)
{
	return 13;
}

//----- (0040701C) --------------------------------------------------------
u32 __cdecl JogconEnterConfigMode(u8 *a)
{
	a[1] = 67;
	*a = 1;
	a[2] = 0;
	*(_WORD *)(a + 3) = 1;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	a[9] = 0;
	a[10] = 0;
	a[11] = 0;
	a[12] = 0;
	return 13;
}

//----- (00407060) --------------------------------------------------------
void sio2cmdInitJogcon(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.id = 14;
	s.readdata = (void (__cdecl *)(u8 *))JogconReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))JogconGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))JogconGetPortCtrl2;
	s.reg_data = (u32 (*)(void))JogconRegData;
	s.size1 = (u32 (*)(void))JogconSize1;
	s.size2 = (u32 (*)(void))JogconSize2;
	s.enterconfigmode = (u32 (__cdecl *)(u8 *))JogconEnterConfigMode;
	memset(&s.exitconfigmode, 0, 40);
	SetupCmds(&s);
}

//----- (00407110) --------------------------------------------------------
void __cdecl ConfigReadData(u8 *a)
{
	*a = 1;
	a[1] = 0x42;
	a[2] = 0;
	a[3] = 0x5A;
	a[4] = 0x5A;
	a[5] = 0x5A;
	a[6] = 0x5A;
	a[7] = 0x5A;
	a[8] = 0x5A;
}

//----- (00407144) --------------------------------------------------------
u32 __cdecl ConfigGetPortCtrl1(u32 a, u32 b)
{
	(void)b;

	if ( a )
		return 0xFF060505;
	else
		return 0xFFC00505;
}

//----- (00407164) --------------------------------------------------------
u32 __cdecl ConfigGetPortCtrl2(u32 a)
{
	if ( a )
		return 0x2012C;
	else
		return 0x20014;
}

//----- (00407184) --------------------------------------------------------
u32 ConfigRegData(void)
{
	return 0x240940;
}

//----- (00407190) --------------------------------------------------------
u32 ConfigSize1(void)
{
	return 9;
}

//----- (00407198) --------------------------------------------------------
u32 ConfigSize2(void)
{
	return 9;
}

//----- (004071A0) --------------------------------------------------------
u32 __cdecl ConfigExitConfigMode(u8 *a)
{

	*a = 1;
	a[1] = 0x43;
	a[4] = 0x5A;
	a[5] = 0x5A;
	a[6] = 0x5A;
	a[7] = 0x5A;
	a[8] = 0x5A;
	a[2] = 0;
	a[3] = 0;
	return 9;
}

//----- (004071D8) --------------------------------------------------------
u32 __cdecl ConfigQueryModel(u8 *a)
{
	*a = 1;
	a[1] = 0x45;
	a[3] = 0x5A;
	a[4] = 0x5A;
	a[5] = 0x5A;
	a[6] = 0x5A;
	a[7] = 0x5A;
	a[8] = 0x5A;
	a[2] = 0;
	return 9;
}

//----- (00407210) --------------------------------------------------------
u32 __cdecl ConfigQueryAct(u8 *a)
{
	*a = 1;
	a[1] = 0x46;
	a[4] = 0x5A;
	a[5] = 0x5A;
	a[6] = 0x5A;
	a[7] = 0x5A;
	a[8] = 0x5A;
	a[2] = 0;
	a[3] = 0;
	return 9;
}

//----- (00407248) --------------------------------------------------------
u32 __cdecl ConfigQueryComb(u8 *a)
{
	*a = 1;
	a[1] = 0x47;
	a[4] = 0x5A;
	a[5] = 0x5A;
	a[6] = 0x5A;
	a[7] = 0x5A;
	a[8] = 0x5A;
	a[2] = 0;
	a[3] = 0;
	return 9;
}

//----- (00407280) --------------------------------------------------------
u32 __cdecl ConfigQueryMode(u8 *a)
{
	*a = 1;
	a[1] = 0x4C;
	a[4] = 0x5A;
	a[5] = 0x5A;
	a[6] = 0x5A;
	a[7] = 0x5A;
	a[8] = 0x5A;
	a[2] = 0;
	a[3] = 0;
	return 9;
}

//----- (004072B8) --------------------------------------------------------
u32 __cdecl ConfigQueryButtonMask(u8 *a)
{
	*a = 1;
	a[1] = 0x41;
	a[3] = 0x5A;
	a[4] = 0x5A;
	a[5] = 0x5A;
	a[6] = 0x5A;
	a[7] = 0x5A;
	a[8] = 0x5A;
	a[2] = 0;
	return 9;
}

//----- (004072F0) --------------------------------------------------------
u32 __cdecl ConfigSetButtonInfo(u8 *a)
{
	*a = 1;
	a[1] = 0x4F;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	return 9;
}

//----- (00407324) --------------------------------------------------------
u32 __cdecl ConfigSetVrefParam(u8 *a)
{
	*a = 1;
	a[1] = 0x40;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	return 9;
}

//----- (00407358) --------------------------------------------------------
u32 __cdecl ConfigSetMainMode(u8 *a)
{
	*a = 1;
	a[1] = 0x44;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	return 9;
}

//----- (0040738C) --------------------------------------------------------
u32 __cdecl ConfigSetSetActAlign(u8 *a)
{
	*a = 1;
	a[1] = 0x4D;
	a[2] = 0;
	a[3] = 0;
	a[4] = 0;
	a[5] = 0;
	a[6] = 0;
	a[7] = 0;
	a[8] = 0;
	return 9;
}

//----- (004073C0) --------------------------------------------------------
void sio2cmdInitConfig(void)
{
	sio2Cmds_t s; // [sp+10h] [-48h] BYREF

	s.id = 15;
	s.readdata = (void (__cdecl *)(u8 *))ConfigReadData;
	s.getportctrl1 = (u32 (__cdecl *)(u32, u32))ConfigGetPortCtrl1;
	s.getportctrl2 = (u32 (__cdecl *)(u32))ConfigGetPortCtrl2;
	s.reg_data = (u32 (*)(void))ConfigRegData;
	s.size1 = (u32 (*)(void))ConfigSize1;
	s.size2 = (u32 (*)(void))ConfigSize2;
	s.exitconfigmode = (u32 (__cdecl *)(u8 *))ConfigExitConfigMode;
	s.querymodel = (u32 (__cdecl *)(u8 *))ConfigQueryModel;
	s.queryact = (u32 (__cdecl *)(u8 *))ConfigQueryAct;
	s.querycomb = (u32 (__cdecl *)(u8 *))ConfigQueryComb;
	s.querymode = (u32 (__cdecl *)(u8 *))ConfigQueryMode;
	s.querybuttonmask = (u32 (__cdecl *)(u8 *))ConfigQueryButtonMask;
	s.setbuttoninfo = (u32 (__cdecl *)(u8 *))ConfigSetButtonInfo;
	s.setvrefparam = (u32 (__cdecl *)(u8 *))ConfigSetVrefParam;
	s.setmainmode = (u32 (__cdecl *)(u8 *))ConfigSetMainMode;
	s.enterconfigmode = NULL; // TODO no-op
	s.setactalign = (u32 (__cdecl *)(u8 *))ConfigSetSetActAlign;
	SetupCmds(&s);
}

//----- (004074B0) --------------------------------------------------------
void *__cdecl RpcPadInit(u32 *data)
{
	data[3] = padInit((void *)data[4], data[5]);
	return data;
}

//----- (004074E8) --------------------------------------------------------
void *__cdecl RpcPadEnd(u32 *data)
{
	data[3] = padEnd();
	return data;
}

//----- (00407514) --------------------------------------------------------
void *__cdecl RpcSetVerbose(u32 *data)
{
	data[2] = padSetVerbose(data[1]);
	return data;
}

//----- (00407548) --------------------------------------------------------
void *__cdecl RpcGetModVersion(u32 *data)
{
	data[3] = padGetVersion();
	return data;
}

//----- (00407574) --------------------------------------------------------
void *__cdecl RpcPadOpen(u32 *data)
{
	data[3] = padPortOpen(data[1], data[2], data[4], (struct libpad_dma_act_direct_state **)data + 5);
	return data;
}

//----- (004075B0) --------------------------------------------------------
void *__cdecl RpcPadClose(u32 *data)
{
	data[3] = padPortClose(data[1], data[2], data[4]);
	return data;
}

//----- (004075EC) --------------------------------------------------------
void *__cdecl RpcPadInfoAct(u32 *data)
{
	data[5] = padInfoAct(data[1], data[2], data[3], data[4]);
	return data;
}

//----- (0040762C) --------------------------------------------------------
void *__cdecl RpcPadInfoComb(u32 *data)
{
	data[5] = padInfoComb(data[1], data[2], data[3], data[4]);
	return data;
}

//----- (0040766C) --------------------------------------------------------
void *__cdecl RpcPadInfoMode(u32 *data)
{
	data[5] = padInfoMode(data[1], data[2], data[3], data[4]);
	return data;
}

//----- (004076AC) --------------------------------------------------------
void *__cdecl RpcPadSetMainMode(u32 *data)
{
	data[5] = padSetMainMode(data[1], data[2], data[3], data[4]);
	return data;
}

//----- (004076EC) --------------------------------------------------------
void *__cdecl RpcPadSetActDirect(u32 *data)
{
	data[5] = padSetActDirect(data[1], data[2], (u8 *)data + 12);
	return data;
}

//----- (00407724) --------------------------------------------------------
void *__cdecl RpcPadSetActAlign(u32 *data)
{
	data[5] = padSetActAlign(data[1], data[2], (const u8 *)data + 12);
	return data;
}

//----- (0040775C) --------------------------------------------------------
void *__cdecl RpcPadGetButtonMask(u32 *data)
{
	data[3] = padGetButtonMask(data[1], data[2]);
	return data;
}

//----- (00407794) --------------------------------------------------------
void *__cdecl RpcPadSetButtonInfo(u32 *data)
{
	data[4] = padSetButtonInfo(data[1], data[2], data[3]);
	return data;
}

//----- (004077D0) --------------------------------------------------------
void *__cdecl RpcPadSetVrefParam(u32 *data)
{
	data[7] = padSetVrefParam(data[1], data[2], (const u8 *)data + 12);
	return data;
}

//----- (00407808) --------------------------------------------------------
void *__cdecl RpcPadGetPortMax(u32 *data)
{
	data[3] = padGetPortMax();
	return data;
}

//----- (00407834) --------------------------------------------------------
void *__cdecl RpcPadGetSlotMax(u32 *data)
{
	data[3] = padGetSlotMax(data[1]);
	return data;
}

//----- (00407868) --------------------------------------------------------
void *__cdecl RpcSetNonblockDma(u32 *a1)
{
	a1[2] = padSetNonblockDma(a1[1]);
	return a1;
}

//----- (0040789C) --------------------------------------------------------
void *__cdecl RpcServer(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;
	switch ( *(_DWORD *)buffer )
	{
		case 1:
			RpcPadOpen((u32 *)buffer);
			break;
		case 3:
			RpcPadInfoAct((u32 *)buffer);
			break;
		case 4:
			RpcPadInfoComb((u32 *)buffer);
			break;
		case 5:
			RpcPadInfoMode((u32 *)buffer);
			break;
		case 6:
			RpcPadSetMainMode((u32 *)buffer);
			break;
		case 7:
			RpcPadSetActDirect((u32 *)buffer);
			break;
		case 8:
			RpcPadSetActAlign((u32 *)buffer);
			break;
		case 9:
			RpcPadGetButtonMask((u32 *)buffer);
			break;
		case 0xA:
			RpcPadSetButtonInfo((u32 *)buffer);
			break;
		case 0xB:
			RpcPadSetVrefParam((u32 *)buffer);
			break;
		case 0xC:
			RpcPadGetPortMax((u32 *)buffer);
			break;
		case 0xD:
			RpcPadGetSlotMax((u32 *)buffer);
			break;
		case 0xE:
			RpcPadClose((u32 *)buffer);
			break;
		case 0xF:
			RpcPadEnd((u32 *)buffer);
			break;
		case 0x10:
			RpcPadInit((u32 *)buffer);
			break;
		case 0x12:
			RpcGetModVersion((u32 *)buffer);
			break;
		case 0x13:
			goto LABEL_21;
		case 0x14:
			RpcSetVerbose((u32 *)buffer);
			break;
		case 0x18:
			RpcSetNonblockDma((u32 *)buffer);
			break;
		default:
			printf("invalid function code (%03x)\n", *(_DWORD *)buffer);
LABEL_21:
			break;
	}
	return buffer;
}

//----- (00407A28) --------------------------------------------------------
void __cdecl RpcThread(void *arg)
{
	int ThreadId; // $v0

	(void)arg;
	if ( !sceSifCheckInit() )
	{
		printf("yet sif hasn't been init\n");
		sceSifInit();
	}
	sceSifInitRpc(0);
	ThreadId = GetThreadId();
	sceSifSetRpcQueue(&rpc_qd, ThreadId);
	sceSifRegisterRpc(&rpc_sd, 0x80000100, (SifRpcFunc_t)RpcServer, rpc_buf, NULL, NULL, &rpc_qd);
	sceSifRpcLoop(&rpc_qd);
}
// 409D44: using guessed type SifRpcDataQueue_t rpc_qd;
// 409D5C: using guessed type SifRpcServerData_t rpc_sd;
// 409DA0: using guessed type int rpc_buf[32];

//----- (00407ABC) --------------------------------------------------------
void *__cdecl RpcServerExt(int fno, void *buffer, int length)
{
	(void)fno;
	(void)length;
	printf("Extend Service : this service is not support\n");
	return buffer;
}

//----- (00407AEC) --------------------------------------------------------
void __cdecl RpcThreadExt(void *arg)
{
	int ThreadId; // $v0

	(void)arg;
	if ( !sceSifCheckInit() )
	{
		printf("yet sif hasn't been init\n");
		sceSifInit();
	}
	sceSifInitRpc(0);
	ThreadId = GetThreadId();
	sceSifSetRpcQueue(&rpcext_qd, ThreadId);
	sceSifRegisterRpc(&rpcext_sd, 0x80000101, (SifRpcFunc_t)RpcServerExt, rpcext_buf, NULL, NULL, &rpcext_qd);
	sceSifRpcLoop(&rpcext_qd);
}
// 409E24: using guessed type SifRpcDataQueue_t rpcext_qd;
// 409E3C: using guessed type SifRpcServerData_t rpcext_sd;
// 409E80: using guessed type int rpcext_buf[32];

//----- (00407B80) --------------------------------------------------------
int __cdecl InitRpcServers(int prio)
{
	int priorx; // $s0
	int thid1; // $v0
	int thid2; // $v0
	iop_thread_t thparam; // [sp+10h] [-18h] BYREF

	priorx = prio;
	if ( !prio )
		priorx = 46;
	thparam.attr = 0x2000000;
	thparam.thread = (void (__cdecl *)(void *))RpcThread;
	thparam.priority = priorx;
	thparam.stacksize = 2048;
	thid1 = CreateThread(&thparam);
	ThreadIdRpcServer = thid1;
	if ( !thid1 )
		return 0;
	StartThread(thid1, NULL);
	thparam.attr = 0x2000000;
	thparam.thread = (void (__cdecl *)(void *))RpcThreadExt;
	thparam.priority = priorx;
	thparam.stacksize = 2048;
	thid2 = CreateThread(&thparam);
	ThreadIdRpcServerExt = thid2;
	if ( !thid2 )
		return 0;
	StartThread(thid2, NULL);
	return 1;
}
// 409D40: using guessed type int ThreadIdRpcServer;
// 409E20: using guessed type int ThreadIdRpcServerExt;
