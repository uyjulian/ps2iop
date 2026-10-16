
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
	u32 fixme_used_4;
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
	u8 modeParam[12];
	u8 m_xpadding[2];
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
u32 __cdecl GetThreadsStatus(padState_t *pstate);
void __cdecl DeleteThreads(padState_t *pstate);
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
void __cdecl do_set_fixme_used_4_pad(int port, int slot, u32 val);
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
	ret2 += !!( !iReferThreadStatus(vData->tid_1, &tinfo) && (tinfo.status & 0x10) == 0 );
	ret2 += !!( !iReferThreadStatus(vData->tid_2, &tinfo) && (tinfo.status & 0x10) == 0 );
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
u32 __cdecl GetThreadsStatus(padState_t *pstate)
{
	int count; // $s0
	iop_thread_info_t tinfo; // [sp+10h] [-48h] BYREF

	count = 0;
	count += !!( !ReferThreadStatus(pstate->updatepadTid, &tinfo) && (tinfo.status & 0x10) == 0 );
	count += !!( !ReferThreadStatus(pstate->querypadTid, &tinfo) && (tinfo.status & 0x10) == 0 );
	count += !!( !ReferThreadStatus(pstate->setmainmodeTid, &tinfo) && (tinfo.status & 0x10) == 0 );
	count += !!( !ReferThreadStatus(pstate->setactalignTid, &tinfo) && (tinfo.status & 0x10) == 0 );
	count += !!( !ReferThreadStatus(pstate->setbuttoninfoTid, &tinfo) && (tinfo.status & 0x10) == 0 );
	count += !!( !ReferThreadStatus(pstate->setvrefparamTid, &tinfo) && (tinfo.status & 0x10) == 0 );
	return count < 1;
}

//----- (004002D8) --------------------------------------------------------
void __cdecl DeleteThreads(padState_t *pstate)
{
	DeleteThread(pstate->updatepadTid);
	DeleteThread(pstate->querypadTid);
	DeleteThread(pstate->setmainmodeTid);
	DeleteThread(pstate->setactalignTid);
	DeleteThread(pstate->setbuttoninfoTid);
	DeleteThread(pstate->setvrefparamTid);
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
	padState_t *pstate; // $s4
	int trid3; // $s0
	int trid2; // $s0
	int trid1; // $s0
	int state; // [sp+20h] [-20h] BYREF

	dmat_count_2 = 0;
	state = 0;
	if ( sifdma_id )
	{
		dma_stat = sceSifDmaStat(sifdma_id);
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
	for ( port = 0; port < 2; port += 1 )
	{
		for ( slot = 0; slot < 4; slot += 1 )
		{
			if ( ((openSlots[port] >> slot) & 1) != 0 )
			{
				pstate = &g_pad_state[port][slot];
				pstate->ee_pdata.frame = pstate->frame;
				pstate->ee_pdata.modeCurOffs = pstate->modeCurOffs;
				pstate->ee_pdata.nrOfActuators = pstate->numActuators;
				pstate->ee_pdata.numActComb = pstate->numActComb;
				pstate->ee_pdata.findPadRetries = pstate->findPadRetries;
				pstate->ee_pdata.modeConfig = pstate->modeConfig;
				pstate->ee_pdata.modeCurId = pstate->modeCurId;
				pstate->ee_pdata.model = pstate->model;
				pstate->ee_pdata.buttonDataReady = pstate->buttonDataReady;
				pstate->ee_pdata.nrOfModes = pstate->numModes;
				pstate->ee_pdata.val_c6 = pstate->val_c6;
				pstate->ee_pdata.mode = pstate->mode;
				pstate->ee_pdata.lock = pstate->lock;
				pstate->ee_pdata.actDirSize = pstate->ee_actDirectSize;
				pstate->ee_pdata.state = pstate->state;
				pstate->ee_pdata.reqState = pstate->reqState;
				pstate->ee_pdata.currentTask = pstate->currentTask;
				pstate->ee_pdata.runTask = pstate->runTask;
				pstate->ee_pdata.actDirData[0] = *(_DWORD *)pstate->ee_actDirectData;
				pstate->ee_pdata.actDirData[1] = *(_DWORD *)&pstate->ee_actDirectData[4];
				pstate->ee_pdata.actAlignData[0] = *(_DWORD *)pstate->ee_actAlignData;
				pstate->ee_pdata.actAlignData[1] = *(_DWORD *)&pstate->ee_actAlignData[4];
				pstate->ee_pdata.actData[0] = *(_DWORD *)&pstate->actData[0][0];
				pstate->ee_pdata.actData[1] = *(_DWORD *)&pstate->actData[1][0];
				pstate->ee_pdata.actData[2] = *(_DWORD *)&pstate->actData[2][0];
				pstate->ee_pdata.actData[3] = *(_DWORD *)&pstate->actData[3][0];
				pstate->ee_pdata.combData[0] = *(_DWORD *)&pstate->combData[0][0];
				pstate->ee_pdata.combData[1] = *(_DWORD *)&pstate->combData[1][0];
				pstate->ee_pdata.combData[2] = *(_DWORD *)&pstate->combData[2][0];
				pstate->ee_pdata.combData[3] = *(_DWORD *)&pstate->combData[3][0];
				memcpy(&pstate->ee_pdata.modeTable[0], &pstate->modeTable[0], sizeof(pstate->ee_pdata.modeTable));
				*(_DWORD *)&pstate->ee_pdata.padding[4] = *(_DWORD *)pstate->buttonMask;
				*(_DWORD *)pstate->ee_pdata.padding = *(_DWORD *)pstate->buttonInfo;
				pstate->ee_pdata.stat70bit = pstate->stat70bit;
				pstate->ee_pdata.length = ( pstate->buttonDataReady == 1 ) ? padSetupEEButtonData(port, slot, pstate) : 0;
				pstate->frame += 1;
				sifdma_td[dmat_count_2].dest = (void *)(((u32)pstate->padarea_ee_addr) + (( pstate->ee_pdata.frame & 1 ) ? 128 : 0));
				sifdma_td[dmat_count_2].src = pstate;
				sifdma_td[dmat_count_2].size = 128;
				sifdma_td[dmat_count_2].attr = 0;
				++dmat_count_2;
			}
		}
	}
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
	int i; // $a1
	_BYTE temp[32]; // [sp+0h] [-20h] BYREF

	for ( i = 0; i < 32; i += 1 )
		temp[i] = buf[i];
	buf[0] = -1;
	for ( i = 1; i < 32; i += 1 )
		buf[i] = temp[i - 1];
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
	vblank_end = 0;
	++vblankStartCount;
	frame_count += 1;
	if ( vData->init )
	{
		if ( vData->stopTransfer )
		{
			if ( (unsigned int)frame_count >= 0x12C )
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
	signed __int32 port; // $s3
	signed __int32 slot; // $s1
	padState_t *pstate; // $s0
	u32 flag_to_set; // $a1

	(void)arg;
	while ( 1 )
	{
		mainThreadCount += 1;
		if ( mainThreadCount == 3 * ((mainThreadCount / 3) - (mainThreadCount >> 31)) )
			sio2_mtap_update_slots();
		for ( port = 0; port < 2; port += 1 )
		{
			for ( slot = 0; slot < 4; slot += 1 )
			{
				pdSetActive(port, slot, 0);
				if ( ((openSlots[port] >> slot) & 1) != 0 )
				{
					pstate = &g_pad_state[port][slot];
					pstate->stat70bit = pdGetStat70bit(port, slot);
					if ( pstate->runTask )
					{
						if ( pstate->runTask == 3 )
						{
							pstate->currentTask = pstate->runTask;
							pstate->runTask = 0;
							pstate->reqState = 2;
							SetEventFlag(pstate->eventflag, 0x1000u);
						}
						else if ( pstate->currentTask == 1 )
						{
							StartThread(pstate->taskTid, NULL);
							pstate->currentTask = pstate->runTask;
							pstate->runTask = 0;
							pstate->reqState = 2;
						}
						else
						{
							pstate->runTask = 0;
							pstate->reqState = 1;
						}
					}
					flag_to_set = 0;
					switch ( pstate->currentTask )
					{
						case 1u:
							flag_to_set = 1;
							break;
						case 2u:
							flag_to_set = 2;
							pstate->buttonDataReady = 0;
							break;
						case 3u:
							pstate->buttonDataReady = 0;
							if ( GetThreadsStatus(pstate) != 1 )
								break;
							pstate->currentTask = 0;
							pstate->reqState = 0;
							openSlots[port] ^= 1 << slot;
							DeleteThreads(pstate);
							if ( pstate->m_close_wait_blocking )
							{
								SetEventFlag(pstate->eventflag, 0x400u);
							}
							else
							{
								DeleteEventFlag(pstate->eventflag);
								pstate->eventflag = 0;
							}
							break;
						case 4u:
							flag_to_set = 8;
							pstate->buttonDataReady = 0;
							break;
						case 5u:
							flag_to_set = 16;
							pstate->buttonDataReady = 0;
							break;
						case 6u:
							flag_to_set = 32;
							pstate->buttonDataReady = 0;
							break;
						case 7u:
							flag_to_set = 64;
							pstate->buttonDataReady = 0;
							break;
						default:
							break;
					}
					if ( flag_to_set )
					{
						SetEventFlag(pstate->eventflag, flag_to_set);
						WaitEventFlag(pstate->eventflag, 0x80u, 16, NULL);
						pdSetActive(port, slot, 1u);
					}
				}
			}
		}
		vblankdata.stopTransfer = 0;
		WaitClearEvent(vblankdata.eventflag, 4u);
		if ( openSlots[0] || openSlots[1] )
		{
			for ( port = 0; port < 2; port += 1 )
			{
				for ( slot = 0; slot < 4; slot += 1 )
				{
					pstate = &g_pad_state[port][slot];
					if ( pdIsActive(port, slot) == 1 )
					{
						SetEventFlag(pstate->eventflag, 0x100u);
						WaitEventFlag(pstate->eventflag, 0x200u, 16, NULL);
					}
				}
			}
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
	u32 has_result_flag; // $s3
	int i; // $a0

	has_result_flag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(pstate->modeCurId, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(pstate->modeCurId, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(pstate->modeCurId));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(pstate->modeCurId));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(pstate->modeCurId));
	for ( i = 0; i < 32; i += 1 )
	{
		pstate->inbuffer[i] = 0;
		pstate->outbuffer[i] = 0;
	}
	sio2CmdSetReadData(pstate->modeCurId, pstate->inbuffer);
	for ( i = 0; i < pstate->ee_actDirectSize; i += 1 )
		pstate->inbuffer[i + 3] = ( pstate->ee_actAlignData[i] == 255 ) ? 0 : pstate->ee_actDirectData[i];
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		has_result_flag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return has_result_flag;
}

//----- (00400F74) --------------------------------------------------------
u32 __cdecl PadIsSupported(padState_t *pstate)
{
	u32 retflag; // $s6

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0));
	sio2CmdSetReadData(0, pstate->inbuffer);
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] && sio2cmdCheckId(pstate->outbuffer[1]) == 1 && pstate->outbuffer[1] && sio2cmdCheckId(pstate->outbuffer[1]) == 1 )
		{
			pstate->modeCurId = pstate->outbuffer[1];
			do_set_fixme_used_4_pad(pstate->port, pstate->slot, pstate->modeCurId);
			retflag = 1;
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401140) --------------------------------------------------------
u32 __cdecl EnterConfigMode(u8 val, padState_t *pstate)
{
	u32 retflag; // $s4

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(val, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(val, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(val));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(val));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(val));
	sio2CmdSetEnterConfigMode(val, pstate->inbuffer);
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		retflag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (004012AC) --------------------------------------------------------
u32 __cdecl ExitConfigMode(padState_t *pstate)
{
	u32 retflag; // $s4

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetExitConfigMode(0xF3u, pstate->inbuffer);
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		retflag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401414) --------------------------------------------------------
u32 __cdecl SetMainMode(padState_t *pstate)
{
	u32 retflag; // $s4

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetSetMainMode(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = pstate->mode;
	pstate->inbuffer[4] = pstate->lock;
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
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
	int i; // $a0

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetSetActAlign(0xF3u, pstate->inbuffer);
	for ( i = 0; i < 6; i += 1 )
		pstate->inbuffer[i + 3] = pstate->ee_actAlignData[i];
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
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

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetQueryModel(0xF3u, pstate->inbuffer);
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
		{
			pstate->numActuators = pstate->outbuffer[6];
			pstate->model = pstate->outbuffer[3];
			pstate->numModes = pstate->outbuffer[4];
			pstate->modeCurOffs = pstate->outbuffer[5];
			pstate->numActComb = pstate->outbuffer[7];
			if ( (u8)(pstate->numActuators) >= 4u )
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

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetQueryAct(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = actuator;
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
		{
			pstate->actData[actuator][0] = pstate->outbuffer[5];
			pstate->actData[actuator][1] = pstate->outbuffer[6];
			pstate->actData[actuator][2] = pstate->outbuffer[7];
			retflag = 1;
			pstate->actData[actuator][3] = pstate->outbuffer[8];
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401AC4) --------------------------------------------------------
u32 __cdecl QueryComb(u32 val, padState_t *pstate)
{
	u32 retflag; // $s4

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetQueryComb(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = val;
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		if ( pstate->outbuffer[1] == 243 )
		{
			pstate->combData[val][0] = pstate->outbuffer[5];
			pstate->combData[val][1] = pstate->outbuffer[6];
			pstate->combData[val][2] = pstate->outbuffer[7];
			retflag = 1;
			pstate->combData[val][3] = pstate->outbuffer[8];
		}
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (00401C78) --------------------------------------------------------
u32 __cdecl QueryMode(u32 val, padState_t *pstate)
{
	u32 retflag; // $s4

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetQueryMode(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = val;
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
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

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, 9u);
	pdSetOutSize(pstate->port, pstate->slot, 9u);
	sio2CmdSetSetVrefParam(0xF3u, pstate->inbuffer);
	pstate->inbuffer[3] = val;
	pstate->inbuffer[4] = pstate->modeParam[val];
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
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

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetQueryButtonMask(0xF3u, pstate->inbuffer);
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
		if ( pstate->stat70bit == 1 )
			shiftarray(pstate->outbuffer);
		pstate->buttonMask[0] = ( pstate->outbuffer[8] == 90 ) ? pstate->outbuffer[3] : 0;
		pstate->buttonMask[1] = ( pstate->outbuffer[8] == 90 ) ? pstate->outbuffer[4] : 0;
		pstate->buttonMask[2] = ( pstate->outbuffer[8] == 90 ) ? pstate->outbuffer[5] : 0;
		pstate->buttonMask[3] = ( pstate->outbuffer[8] == 90 ) ? pstate->outbuffer[6] : 0;
		retflag = 1;
	}
	SetEventFlag(pstate->eventflag, 0x200u);
	return retflag;
}

//----- (0040214C) --------------------------------------------------------
u32 __cdecl SetButtonInfo(padState_t *pstate)
{
	u32 retflag; // $s3
	int i; // $a0

	retflag = 0;
	pdSetCtrl1(pstate->port, pstate->slot, sio2CmdGetPortCtrl1(0xF3u, pstate->stat70bit, pstate->model));
	pdSetCtrl2(pstate->port, pstate->slot, sio2CmdGetPortCtrl2(0xF3u, pstate->stat70bit));
	pdSetRegData(pstate->port, pstate->slot, pdGetRegData(0xF3u));
	pdSetInSize(pstate->port, pstate->slot, pdGetInSize(0xF3u));
	pdSetOutSize(pstate->port, pstate->slot, pdGetOutSize(0xF3u));
	sio2CmdSetSetButtonInfo(0xF3u, pstate->inbuffer);
	for ( i = 0; i < 4; i += 1 )
		pstate->inbuffer[i + 3] = pstate->buttonInfo[i];
	pdSetInBuffer(pstate->port, pstate->slot, 0, pstate->inbuffer);
	SetEventFlag(pstate->eventflag, 0x80u);
	WaitClearEvent(pstate->eventflag, 0x100u);
	if ( !pdGetError(pstate->port, pstate->slot) )
	{
		pdGetOutBuffer(pstate->port, pstate->slot, 0, pstate->outbuffer);
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
	u32 s; // $s0
	padState_t *pstate; // $a1
	int i; // $a0

	retval_r = 0;
	for ( p = 0; (int)p < (int)padGetPortMax(); p += 1 )
	{
		for ( s = 0; (int)s < (int)padGetSlotMax(p); s += 1 )
		{
			if ( (port != p || slot != s) && ((openSlots[p] >> s) & 1) != 0 )
			{
				pstate = &g_pad_state[p][s];
				if ( pstate->modeCurId )
					for ( i = 0; i < pstate->ee_actDirectSize; i += 1 )
						retval_r += ( pstate->ee_actAlignData[i] != 255 && pstate->ee_actDirectData[pstate->ee_actAlignData[i]] ) ? pstate->actData[pstate->ee_actAlignData[i]][3] : 0;
			}
		}
	}
	return retval_r;
}
// 409260: using guessed type int openSlots[];

//----- (00402448) --------------------------------------------------------
u32 __cdecl CheckAirDirectTotal(u32 port, u32 slot, u8 *actData)
{
	u32 total; // $s3
	padState_t *pstate; // $s2
	int i; // $s0
	int itmp; // $v1
	int totaltmp; // $v1

	total = ActDirectTotal(port, slot);
	pstate = &g_pad_state[port][slot];
	for ( i = 0; i < 6; i += 1 )
	{
		itmp = pstate->ee_actAlignData[i];
		if ( itmp != 255 && actData[itmp] )
		{
			totaltmp = total + pstate->actData[itmp][3];
			if ( totaltmp < 61 )
			{
				total = totaltmp;
			}
			else
			{
				if ( g_padman_verbose )
					Kprintf("padman: Over Consumpt Max [%d][%d]\n", port, slot);
				actData[itmp] = 0;
			}
		}
	}
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
	int i; // $a0
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	retval = 0;
	ReferThreadStatus(0, &thinfo);
	pstate = (padState_t *)thinfo.option;
	port = pstate->port;
	slot = pstate->slot;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 1u);
		ApplyActDirectFromDmaBuf(pstate);
		if ( ReadData(pstate) != 1 )
		{
			pstate->buttonDataReady = 0;
			pstate->state = 7;
			pstate->findPadRetries += 1;
			retval += pdGetError(port, slot);
			if ( retval >= 10 )
			{
				retval = 0;
				pstate->currentTask = 2;
				StartThread(pstate->querypadTid, NULL);
			}
			continue;
		}
		retval = 0;
		if ( pstate->outbuffer[2] != 90 || pstate->outbuffer[1] != pstate->modeCurId || pstate->outbuffer[1] == 243 )
		{
			pstate->buttonDataReady = 0;
			pstate->state = 5;
			pstate->currentTask = 2;
			StartThread(pstate->querypadTid, NULL);
			continue;
		}
		for ( i = 0; i < 32; i += 1 )
			pstate->buttonStatus[i] = pstate->outbuffer[i];
		pstate->buttonDataReady = 1;
		pstate->state = ( pstate->modeConfig == 1 ) ? 2 : 6;
		if ( pstate->reqState == 2 && !pstate->runTask )
			pstate->reqState = 0;
	}
}

//----- (00402704) --------------------------------------------------------
void __cdecl __noreturn QueryPadThread(void *arg)
{
	padState_t *pstate; // $s0
	int i; // $v1
	int trycnt; // $v1
	u8 modeCurId; // $s2
	u8 cur_id_tmp; // $s2
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	ReferThreadStatus(0, &thinfo);
	pstate = (padState_t *)thinfo.option;
	pstate->modeCurId = 0;
	pstate->modeConfig = 0;
	pstate->model = 0;
	pstate->numModes = 0;
	pstate->numActuators = 0;
	pstate->numActComb = 0;
	pstate->buttonDataReady = 0;
	pstate->ee_actDirectSize = 0;
	pstate->findPadRetries = 0;
	for ( i = 0; i < 4; i += 1 )
	{
		pstate->buttonInfo[i] = 0;
		pstate->buttonMask[i] = 0;
	}
	pstate->ee_actAlignData[0] = 0;
	pstate->ee_actAlignData[1] = 1;
	for ( i = 2; i < 6; i += 1 )
		pstate->ee_actAlignData[i] = -1;
	for ( i = 5; i >= 0; i -= 1 )
		pstate->ee_actDirectData[i] = 0;
	pstate->modeCurId = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 2u);
		if ( PadIsSupported(pstate) == 1 && pstate->modeCurId != 255 )
			break;
		pstate->state = 0;
		pstate->disconnected = 1;
	}
	modeCurId = pstate->modeCurId;
	pstate->modeCurId = 0;
	pstate->state = 5;
	if ( pstate->disconnected )
		for ( i = 5; i >= 0; i -= 1 )
			pstate->ee_actAlignData[i] = -1;
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 2u);
		++trycnt;
		if ( EnterConfigMode(modeCurId, pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->modeConfig = 1;
			pstate->modeCurId = modeCurId;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	pstate->modeConfig = 2;
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 2u);
		++trycnt;
		if ( QueryModel(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->modeCurId = 0;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	if ( pstate->disconnected == 1 && pstate->modeCurOffs )
	{
		pstate->mode = 0;
		pstate->lock = 0;
		trycnt = 0;
		while ( 1 )
		{
			WaitClearEvent(pstate->eventflag, 2u);
			++trycnt;
			if ( SetMainMode(pstate) == 1 )
				break;
			if ( trycnt >= 10 )
			{
				pstate->reqState = 1;
				pstate->currentTask = 1;
				ExitThread();
			}
		}
		pstate->modeCurId = 0;
		pstate->currentTask = 1;
		pstate->disconnected = 0;
		ExitThread();
	}
	for ( i = 0; (unsigned int)i < (unsigned int)pstate->numActuators; i += 1 )
	{
		trycnt = 0;
		while ( 1 )
		{
			WaitClearEvent(pstate->eventflag, 2u);
			++trycnt;
			if ( QueryAct(i, pstate) == 1 )
				break;
			if ( trycnt >= 10 )
			{
				pstate->modeCurId = 0;
				pstate->currentTask = 1;
				ExitThread();
			}
		}
	}
	for ( i = 0; (unsigned int)i < (unsigned int)pstate->numActComb; i += 1 )
	{
		trycnt = 0;
		while ( 1 )
		{
			WaitClearEvent(pstate->eventflag, 2u);
			++trycnt;
			if ( QueryComb(i, pstate) == 1 )
				break;
			if ( trycnt >= 10 )
			{
				pstate->modeCurId = 0;
				pstate->currentTask = 1;
				ExitThread();
			}
		}
	}
	for ( i = 0; (unsigned int)i < (unsigned int)pstate->numModes; i += 1 )
	{
		trycnt = 0;
		while ( 1 )
		{
			WaitClearEvent(pstate->eventflag, 2u);
			++trycnt;
			if ( QueryMode(i, pstate) == 1 )
				break;
			if ( trycnt >= 10 )
			{
				pstate->modeCurId = 0;
				pstate->currentTask = 1;
				ExitThread();
			}
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 2u);
		++trycnt;
		if ( SetActAlign(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	if ( (*(_DWORD *)&pstate->modeConfig & 0x200FF) == 0x20002 )
	{
		trycnt = 0;
		while ( 1 )
		{
			WaitClearEvent(pstate->eventflag, 2u);
			++trycnt;
			if ( QueryButtonMask(pstate) == 1 )
				break;
			if ( trycnt >= 10 )
			{
				pstate->modeCurId = 0;
				pstate->currentTask = 1;
				ExitThread();
			}
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 2u);
		++trycnt;
		if ( ExitConfigMode(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->modeCurId = 0;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 2u);
		++trycnt;
		if ( PadIsSupported(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->modeCurId = 0;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	cur_id_tmp = pstate->modeCurId;
	pstate->state = 5;
	pstate->modeCurId = 0;
	pstate->currentTask = 1;
	pstate->disconnected = 0;
	pstate->modeCurId = cur_id_tmp;
	ExitThread();
}

//----- (00402C54) --------------------------------------------------------
void __cdecl __noreturn SetMainModeThread(void *arg)
{
	int trycnt; // $s1
	padState_t *pstate; // $s0
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	ReferThreadStatus(0, &thinfo);
	pstate = (padState_t *)thinfo.option;
	pstate->buttonDataReady = 0;
	pstate->state = 5;
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 8u);
		++trycnt;
		if ( EnterConfigMode(pstate->modeCurId, pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 8u);
		++trycnt;
		if ( SetMainMode(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 8u);
		++trycnt;
		if ( ExitConfigMode(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	pstate->currentTask = 1;
	ExitThread();
}

//----- (00402D8C) --------------------------------------------------------
void __cdecl __noreturn SetActAlignThread(void *arg)
{
	int trycnt; // $s1
	padState_t *pstate; // $s0
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	ReferThreadStatus(0, &thinfo);
	pstate = (padState_t *)thinfo.option;
	pstate->buttonDataReady = 0;
	pstate->state = 5;
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 0x10u);
		++trycnt;
		if ( EnterConfigMode(pstate->modeCurId, pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 0x10u);
		++trycnt;
		if ( SetActAlign(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 0x10u);
		++trycnt;
		if ( ExitConfigMode(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	pstate->currentTask = 1;
	ExitThread();
}

//----- (00402EC4) --------------------------------------------------------
void __cdecl __noreturn SetButtonInfoThread(void *arg)
{
	int trycnt; // $s1
	int i; // $s2
	padState_t *pstate; // $s0
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	ReferThreadStatus(0, &thinfo);
	pstate = (padState_t *)thinfo.option;
	pstate->buttonDataReady = 0;
	pstate->state = 5;
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 0x20u);
		++trycnt;
		if ( EnterConfigMode(pstate->modeCurId, pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 0x20u);
		++trycnt;
		if ( SetButtonInfo(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	for ( i = 0; i < 12; i += 1 )
	{
		trycnt = 0;
		while ( 1 )
		{
			WaitClearEvent(pstate->eventflag, 0x20u);
			++trycnt;
			if ( VrefParam(i, pstate) == 1 )
				break;
			if ( trycnt >= 10 )
			{
				pstate->reqState = 1;
				pstate->currentTask = 1;
				ExitThread();
			}
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 0x20u);
		++trycnt;
		if ( ExitConfigMode(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	pstate->val_c6 = 1;
	pstate->currentTask = 1;
	ExitThread();
}

//----- (00403068) --------------------------------------------------------
void __cdecl __noreturn SetVrefParamThread(void *arg)
{
	int trycnt; // $s1
	padState_t *pstate; // $s0
	int i; // $s2
	iop_thread_info_t thinfo; // [sp+10h] [-48h] BYREF

	(void)arg;
	ReferThreadStatus(0, &thinfo);
	pstate = (padState_t *)thinfo.option;
	pstate->buttonDataReady = 0;
	pstate->state = 5;
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 0x40u);
		++trycnt;
		if ( EnterConfigMode(pstate->modeCurId, pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	for ( i = 0; i < 12; i += 1 )
	{
		trycnt = 0;
		while ( 1 )
		{
			WaitClearEvent(pstate->eventflag, 0x40u);
			++trycnt;
			if ( VrefParam(i, pstate) == 1 )
				break;
			if ( trycnt >= 10 )
			{
				pstate->reqState = 1;
				pstate->currentTask = 1;
				ExitThread();
			}
		}
	}
	trycnt = 0;
	while ( 1 )
	{
		WaitClearEvent(pstate->eventflag, 0x40u);
		++trycnt;
		if ( ExitConfigMode(pstate) == 1 )
			break;
		if ( trycnt >= 10 )
		{
			pstate->reqState = 1;
			pstate->currentTask = 1;
			ExitThread();
		}
	}
	pstate->currentTask = 1;
	ExitThread();
}

//----- (004031BC) --------------------------------------------------------
void __cdecl do_set_timer(int timer_mode, u32 timer_compare)
{
	int timerid; // $s2
	int HardTimerIntrCode; // $s1

	timerid = AllocHardTimer(4, 32, 1);
	if ( timerid < 0 )
		timerid = AllocHardTimer(4, 32, 1);
	if ( timerid < 0 )
	{
		Kprintf("Timer alloc faild\n");
		return;
	}
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
// 409268: using guessed type vblankData_t vblankdata;

//----- (004032BC) --------------------------------------------------------
int __cdecl ParseParams(int argc, char *argv[])
{
	int new_thpri_hi; // $s3
	int new_thpri_lo; // $s2
	int i; // $s4
	int thparam_after; // $s0

	new_thpri_hi = 20;
	new_thpri_lo = 46;
	for ( i = 1; i < argc; i += 1 )
	{
		if ( !strncmp("thpri=", argv[i], 6) )
		{
			thparam_after = (int)(argv[i] + 6);
			if ( (look_ctype_table(*(_BYTE *)thparam_after) & 4) != 0 )
			{
				new_thpri_hi = strtol((const char *)thparam_after, NULL, 10);
				if ( (unsigned int)(new_thpri_hi - 9) >= 0x73 )
				{
					printf("PADMAN : invalid priority %d\n");
					return 0;
				}
			}
			for ( ; (look_ctype_table(*(_BYTE *)thparam_after) & 4) != 0; thparam_after += 1 );
			if ( *(_BYTE *)thparam_after != 44 || ((look_ctype_table(*(_BYTE *)(thparam_after + 1)) & 4) == 0 || (new_thpri_lo = strtol((const char *)(thparam_after + 1), NULL, 10), (unsigned int)(new_thpri_lo - 9) < 0x73)) )
			{
				if ( new_thpri_lo < new_thpri_hi )
				{
					new_thpri_lo = new_thpri_hi;
					printf("PADMAN : high prio thread must be higher than low prio thread\n");
				}
			}
			else
			{
				printf(" SDR driver error: invalid priority %d\n");
				return 0;
			}
		}
	}
	thpri_hi = new_thpri_hi;
	thpri_lo = new_thpri_lo;
	return 1;
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
			Kprintf("padman: RegisterLibraryEntries Faild\n");
		return 1;
	}
	if ( SetRebootTimeLibraryHandlingMode(&_exp_padman, 2) )
		return 1;
	if ( !InitRpcServers(thpri_lo) )
	{
		if ( g_padman_verbose )
			Kprintf("padman: sif_init Faild\n");
		return 1;
	}
	return 0;
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
	vblankdata.tid_2 = CreateThread(&thparam);
	if ( !vblankdata.tid_2 )
		return 0;
	StartThread(vblankdata.tid_2, NULL);
	thparam.attr = 0x2000000;
	thparam.thread = (void (__cdecl *)(void *))MainThread;
	thparam.option = 1;
	thparam.stacksize = 4096;
	thparam.priority = thpri_lo;
	vblankdata.tid_1 = CreateThread(&thparam);
	if ( !vblankdata.tid_1 )
		return 0;
	StartThread(vblankdata.tid_1, NULL);
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
	s32 port; // $s1
	s32 slot; // $s0

	if ( !padman_init )
		return 1;
	for ( port = 0; port < 2; port += 1 )
		for ( slot = 0; slot < 4; slot += 1 )
			if ( ((openSlots[port] >> slot) & 1) != 0 )
				padPortClose(port, slot, 1);
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
	padState_t *pstate; // $s0
	iop_event_t efparam; // [sp+10h] [-28h] BYREF
	iop_thread_t thparam; // [sp+20h] [-18h] BYREF

	if ( (unsigned int)port >= 2 || (unsigned int)slot >= 4 )
		return 0;
	pstate = &g_pad_state[port][slot];
	*buf = pstate->m_dma_act_direct_state;
	pstate->m_dma_act_direct_state[0].m_frame = 0;
	pstate->m_dma_act_direct_state[1].m_frame = 0;
	pstate->m_dma_act_direct_state[0].m_unhandled = 0;
	pstate->m_dma_act_direct_state[1].m_unhandled = 0;
	pstate->m_dma_act_direct_state[0].m_unused = 0;
	pstate->m_dma_act_direct_state[1].m_unused = 0;
	if ( ((openSlots[port] >> slot) & 1) != 0 )
		return 0;
	pstate->port = port;
	pstate->slot = slot;
	openSlots[port] |= 1 << slot;
	pstate->state = 5;
	pstate->modeCurId = 0;
	pstate->reqState = 0;
	pstate->frame = 0;
	pstate->padarea_ee_addr = pad_area_ee_addr;
	pstate->buttonDataReady = 0;
	pstate->ee_actDirectSize = 0;
	pstate->val_c6 = 0;
	pstate->currentTask = 0;
	pstate->runTask = 0;
	pstate->m_unused1bc = 0;
	pstate->disconnected = 1;
	pstate->stat70bit = 0;
	efparam.attr = 2;
	efparam.bits = 0;
	pstate->eventflag = CreateEventFlag(&efparam);
	if ( !pstate->eventflag )
		return 0;
	thparam.option = (u32)pstate;
	thparam.attr = 0x2000000;
	thparam.thread = UpdatePadThread;
	thparam.stacksize = 1536;
	thparam.priority = thpri_lo;
	pstate->updatepadTid = CreateThread(&thparam);
	if ( !pstate->updatepadTid )
		return 0;
	thparam.option = (u32)pstate;
	thparam.attr = 0x2000000;
	thparam.thread = QueryPadThread;
	thparam.stacksize = 1536;
	thparam.priority = thpri_lo;
	pstate->querypadTid = CreateThread(&thparam);
	if ( !pstate->querypadTid )
		return 0;
	thparam.option = (u32)pstate;
	thparam.attr = 0x2000000;
	thparam.thread = SetMainModeThread;
	thparam.stacksize = 1024;
	thparam.priority = thpri_lo;
	pstate->setmainmodeTid = CreateThread(&thparam);
	if ( !pstate->setmainmodeTid )
		return 0;
	thparam.option = (u32)pstate;
	thparam.attr = 0x2000000;
	thparam.thread = SetActAlignThread;
	thparam.stacksize = 1024;
	thparam.priority = thpri_lo;
	pstate->setactalignTid = CreateThread(&thparam);
	if ( !pstate->setactalignTid )
		return 0;
	thparam.option = (u32)pstate;
	thparam.attr = 0x2000000;
	thparam.thread = SetButtonInfoThread;
	thparam.stacksize = 1024;
	thparam.priority = thpri_lo;
	pstate->setbuttoninfoTid = CreateThread(&thparam);
	if ( !pstate->setbuttoninfoTid )
		return 0;
	thparam.option = (u32)pstate;
	thparam.attr = 0x2000000;
	thparam.thread = SetVrefParamThread;
	thparam.stacksize = 1024;
	thparam.priority = thpri_lo;
	pstate->setvrefparamTid = CreateThread(&thparam);
	if ( !pstate->setvrefparamTid || pstate->currentTask >= 2u )
		return 0;
	pstate->currentTask = 1;
	StartThread(pstate->updatepadTid, NULL);
	return 1;
}
// 409260: using guessed type int openSlots[];

//----- (00403C78) --------------------------------------------------------
s32 __cdecl padPortClose(s32 port, s32 slot, s32 wait)
{
	padState_t *pstate; // $s0
	int efres[2]; // [sp+10h] [-8h] BYREF

	efres[0] = 0;
	pstate = &g_pad_state[port][slot];
	if ( ((openSlots[port] >> slot) & 1) != 0 && pstate->reqState != 2 )
	{
		pstate->runTask = 3;
		pstate->taskTid = 0;
		pstate->reqState = 2;
		pstate->m_close_wait_blocking = wait;
		if ( wait )
		{
			WaitEventFlag(pstate->eventflag, 0x400u, 16, (u32 *)efres);
			DeleteEventFlag(pstate->eventflag);
			pstate->eventflag = 0;
		}
		return 1;
	}
	return 0;
}
// 409260: using guessed type int openSlots[];
// 403C78: using guessed type u32 efres[2];

#define BSWAP16(x) ((((unsigned short int)x) << 8) | (x >> 8))

//----- (00403D48) --------------------------------------------------------
u32 __cdecl padSetupEEButtonData(u32 port, u32 slot, padState_t *pstate)
{
	padState_t *pstate_tmp; // $a1
	int i; // $v1
	__int16 swapval2; // $v1

	pstate_tmp = &g_pad_state[port][slot];
	if ( pstate_tmp->buttonDataReady == 1 )
	{
		pstate->ee_pdata.data[0] = 0;
		pstate->ee_pdata.data[1] = pstate_tmp->modeCurId;
		pstate->ee_pdata.data[31] = pstate_tmp->buttonStatus[2];
		for ( i = 2; i < 31; i += 1 )
			pstate->ee_pdata.data[i] = pstate_tmp->buttonStatus[i + 1];
		if ( pstate_tmp->modeCurId == 18 )
		{
			pstate->ee_pdata.data[2] = -1;
			pstate->ee_pdata.data[3] = -1;
			pstate->ee_pdata.data[4] = 0;
			pstate->ee_pdata.data[5] = 0;
		}
		if ( pstate_tmp->modeCurId != 121 )
			return 32;
		swapval2 = ~BSWAP16(*(_WORD *)&pstate->ee_pdata.data[2]);
		if ( (swapval2 & 0x2000) != 0 )
		{
			if ( !pstate->ee_pdata.data[8] )
				pstate->ee_pdata.data[8] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[8] )
				pstate->ee_pdata.data[8] = 0;
		}
		if ( swapval2 & 0x8000 )
		{
			if ( !pstate->ee_pdata.data[9] )
				pstate->ee_pdata.data[9] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[9] )
				pstate->ee_pdata.data[9] = 0;
		}
		if ( swapval2 & 0x1000 )
		{
			if ( !pstate->ee_pdata.data[10] )
				pstate->ee_pdata.data[10] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[10] )
				pstate->ee_pdata.data[10] = 0;
		}
		if ( swapval2 & 0x4000 )
		{
			if ( !pstate->ee_pdata.data[11] )
				pstate->ee_pdata.data[11] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[11] )
				pstate->ee_pdata.data[11] = 0;
		}
		if ( swapval2 & 0x10 )
		{
			if ( !pstate->ee_pdata.data[12] )
				pstate->ee_pdata.data[12] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[12] )
				pstate->ee_pdata.data[12] = 0;
		}
		if ( swapval2 & 0x20 )
		{
			if ( !pstate->ee_pdata.data[13] )
				pstate->ee_pdata.data[13] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[13] )
				pstate->ee_pdata.data[13] = 0;
		}
		if ( swapval2 & 0x40 )
		{
			if ( !pstate->ee_pdata.data[14] )
				pstate->ee_pdata.data[14] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[14] )
				pstate->ee_pdata.data[14] = 0;
		}
		if ( swapval2 & 0x80 )
		{
			if ( !pstate->ee_pdata.data[15] )
				pstate->ee_pdata.data[15] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[15] )
				pstate->ee_pdata.data[15] = 0;
		}
		if ( swapval2 & 4 )
		{
			if ( !pstate->ee_pdata.data[16] )
				pstate->ee_pdata.data[16] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[16] )
				pstate->ee_pdata.data[16] = 0;
		}
		if ( swapval2 & 8 )
		{
			if ( !pstate->ee_pdata.data[17] )
				pstate->ee_pdata.data[17] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[17] )
				pstate->ee_pdata.data[17] = 0;
		}
		if ( swapval2 & 1 )
		{
			if ( !pstate->ee_pdata.data[18] )
				pstate->ee_pdata.data[18] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[18] )
				pstate->ee_pdata.data[18] = 0;
		}
		if ( swapval2 & 2 )
		{
			if ( !pstate->ee_pdata.data[19] )
				pstate->ee_pdata.data[19] = 1;
		}
		else
		{
			if ( pstate->ee_pdata.data[19] )
				pstate->ee_pdata.data[19] = 0;
		}
		return 32;
	}
	pstate->ee_pdata.data[0] = -1;
	for ( i = 1; i < 32; i += 1 )
		pstate->ee_pdata.data[i] = 0;
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
	padState_t *pstate; // $v1

	pstate = &g_pad_state[port][slot];
	if ( pstate->currentTask != 1 || pstate->modeConfig < 2u )
		return 0;
	if ( act == -1 )
		return pstate->numActuators;
	if ( act >= pstate->numActuators )
		return -1;
	switch ( val )
	{
		case 1u:
			return pstate->actData[act][0];
		case 2u:
			return pstate->actData[act][1];
		case 3u:
			return pstate->actData[act][2];
		case 4u:
			return pstate->actData[act][3];
		default:
			return -1;
	}
}

//----- (00404258) --------------------------------------------------------
s32 __cdecl padInfoComb(u32 port, u32 slot, s32 val1, u32 val2)
{
	padState_t *pstate; // $v1

	pstate = &g_pad_state[port][slot];
	if ( pstate->currentTask != 1 )
		return 0;
	if ( pstate->modeConfig < 2u )
		return -1;
	if ( val1 == -1 )
		return pstate->numActComb;
	if ( val1 >= pstate->numActComb )
		return 0;
	switch ( val2 )
	{
		case -1:
			return pstate->combData[val1][0];
		case 0:
			return pstate->combData[val1][1];
		case 1:
			return pstate->combData[val1][2];
		case 2:
			return pstate->combData[val1][3];
		// Unofficial: default case
		default:
			return 0;
	}
}

//----- (00404344) --------------------------------------------------------
s32 __cdecl padInfoMode(u32 port, u32 slot, s32 val1, u32 val2)
{
	padState_t *pstate; // $v1

	pstate = &g_pad_state[port][slot];
	if ( pstate->currentTask != 1 || pstate->reqState == 2 )
		return 0;
	switch ( val1 )
	{
		case 1:
			return ( pstate->modeCurId == 243 ) ? 0 : ((u32)pstate->modeCurId >> 4);
		case 2:
			return ( pstate->modeConfig == 1 ) ? 0 : pstate->modeTable[pstate->modeCurOffs];
		case 3:
			return ( pstate->modeConfig == 1 ) ? 0 : pstate->modeCurOffs;
		case 4:
		{
			if ( pstate->modeConfig == 1 )
				return 0;
			if ( val2 == (u32)-1 )
				return pstate->numModes;
			if ( (int)val2 >= pstate->numModes )
				return 0;
			return pstate->modeTable[val2];
		}
		default:
			return -1;
	}
}

//----- (0040447C) --------------------------------------------------------
u32 __cdecl padSetActDirect(u32 port, u32 slot, u8 *actData)
{
	padState_t *pstate; // $s0
	int i; // $a0

	pstate = &g_pad_state[port][slot];
	if ( pstate->modeConfig == 1 || pstate->currentTask != 1 )
		return 0;
	CheckAirDirectTotal(port, slot, actData);
	for ( i = 0; i < 6; i += 1 )
		pstate->ee_actDirectData[i] = actData[i];
	pstate->ee_actDirectSize = 6;
	return 1;
}

//----- (0040453C) --------------------------------------------------------
u32 __cdecl padSetMainMode(u32 port, u32 slot, u32 mode, u32 lock)
{
	padState_t *pstate; // $a1

	pstate = &g_pad_state[port][slot];
	if ( pstate->currentTask != 1 || pstate->modeConfig < 2u || (int)mode >= pstate->numModes || pstate->reqState == 2 )
		return 0;
	pstate->mode = mode;
	pstate->lock = lock;
	pstate->runTask = 4;
	pstate->reqState = 2;
	pstate->taskTid = pstate->setmainmodeTid;
	return 1;
}

//----- (004045EC) --------------------------------------------------------
u32 __cdecl padSetActAlign(u32 port, u32 slot, const u8 *actData)
{
	padState_t *pstate; // $a1
	int i; // $a0

	pstate = &g_pad_state[port][slot];
	if ( pstate->currentTask != 1 || pstate->modeConfig < 2u || pstate->reqState == 2 )
		return 0;
	for ( i = 0; i < 6; i += 1 )
		pstate->ee_actAlignData[i] = actData[i];
	pstate->reqState = 2;
	pstate->runTask = 5;
	pstate->taskTid = pstate->setactalignTid;
	return 1;
}

//----- (004046A0) --------------------------------------------------------
u32 __cdecl padSetVrefParam(u32 port, u32 slot, const u8 *vparam)
{
	padState_t *pstate; // $a1
	int i; // $a0

	pstate = &g_pad_state[port][slot];
	if ( pstate->currentTask != 1 || pstate->modeConfig < 2u || pstate->model < 2u || pstate->reqState == 2 )
		return 0;
	for ( i = 0; i < 12; i += 1 )
		pstate->modeParam[i] = vparam[i];
	pstate->runTask = 7;
	pstate->reqState = 2;
	pstate->taskTid = pstate->setvrefparamTid;
	return 1;
}

//----- (00404768) --------------------------------------------------------
u32 __cdecl padSetButtonInfo(u32 port, u32 slot, u32 info)
{
	padState_t *pstate; // $a1
	int i; // $a0

	pstate = &g_pad_state[port][slot];
	if ( pstate->currentTask != 1 || pstate->modeConfig < 2u || (pstate->model & 2) == 0 || pstate->reqState == 2 )
		return 0;
	pstate->buttonInfo[1] = (unsigned __int16)((info << 6) | 0x3F) >> 8;
	pstate->buttonInfo[2] = ((info << 6) | 0x3F) >> 16;
	pstate->buttonInfo[0] = (info << 6) | 0x3F;
	pstate->buttonInfo[3] = ((info << 6) | 0x3F) >> 24;
	for ( i = 11; i >= 0; i -= 1 )
		pstate->modeParam[i] = 2;
	pstate->runTask = 6;
	pstate->reqState = 2;
	pstate->taskTid = pstate->setbuttoninfoTid;
	return 1;
}

//----- (0040484C) --------------------------------------------------------
u32 __cdecl padGetButtonMask(u32 port, u32 slot)
{
	padState_t *pstate; // $a1

	pstate = &g_pad_state[port][slot];
	return ( pstate->currentTask == 1 && pstate->modeConfig >= 2u && pstate->model >= 2u ) ? (pstate->buttonMask[0] + (pstate->buttonMask[1] << 8) + (pstate->buttonMask[2] << 16) + (pstate->buttonMask[3] << 24)) : 0;
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
	int port; // $a1
	int slot; // $v1

	for ( port = 0; port < 2; port += 1 )
	{
		for ( slot = 3; slot >= 0; slot -= 1 )
		{
			padData[port][slot].active = 0;
			// Unofficial: set stat70bit for all slots at correct port offset
			padData[port][slot].stat70bit = 0;
		}
	}
	sio2_td.in = (u8 *)g_td_in_buf;
	sio2_td.out = (u8 *)g_td_out_buf;
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;
// 4096A8: using guessed type int g_td_in_buf[64];
// 4097A8: using guessed type int g_td_out_buf[66];

//----- (004049D8) --------------------------------------------------------
void __cdecl do_set_fixme_used_4_pad(int port, int slot, u32 val)
{
	padData[port][slot].fixme_used_4 = val;
}

//----- (00404A18) --------------------------------------------------------
u32 __cdecl pdSetActive(u32 port, u32 slot, u32 active)
{
	u32 oldval; // $v0

	oldval = padData[port][slot].active;
	padData[port][slot].active = active;
	return oldval;
}

//----- (00404A64) --------------------------------------------------------
u32 __cdecl pdIsActive(u32 port, u32 slot)
{
	return padData[port][slot].active;
}

//----- (00404AA4) --------------------------------------------------------
u32 __cdecl pdSetStat70bit(u32 port, u32 slot, u32 val)
{
	u32 oldval; // $v0

	oldval = padData[port][slot].stat70bit;
	padData[port][slot].stat70bit = val;
	return oldval;
}

//----- (00404AF0) --------------------------------------------------------
u32 __cdecl pdGetStat70bit(u32 port, u32 slot)
{
	return padData[port][slot].stat70bit;
}

//----- (00404B30) --------------------------------------------------------
u32 __cdecl setupTransferData(u32 index, u32 port, u32 slot)
{
	padData_t *pdata; // $s0

	pdata = &padData[port][slot];
	memcpy(&sio2_td.in[sio2_td.in_size], pdata->in_buffer, pdata->in_size);
	sio2_td.in_size += pdata->in_size;
	sio2_td.out_size += pdata->out_size;
	sio2_td.port_ctrl1[port] = pdata->port_ctrl1;
	sio2_td.port_ctrl2[port] = pdata->port_ctrl2;
	sio2_td.regdata[index] = (pdata->reg_data & 0xFFFFFFFC) | (port & 3);
	sio2_td.regdata[index + 1] = 0;
	return index + 1;
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;

//----- (00404C4C) --------------------------------------------------------
u32 __cdecl readSio2OutBuffer(u32 bit, u32 port, u32 slot)
{
	int outsize_old; // $v1
	int i; // $a3

	if ( ((sio2_td.stat6c >> 13) & 1) == 1 || readStat6cBit(bit, &sio2_td) == 1 )
	{
		padData[port][slot].error = 1;
		return 0;
	}
	outsize_old = padData[port][slot].out_size;
	padData[port][slot].error = 0;
	for ( i = 0; i < (int)outsize_old; i += 1 )
		padData[port][slot].out_buffer[i] = sio2_td.out[sio2_td.out_size + i];
	sio2_td.out_size += outsize_old;
	return 1;
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;

//----- (00404DF8) --------------------------------------------------------
u32 __cdecl padTransfer(u32 slot)
{
	int xferdatres; // $a0
	int i; // $s1
	u32 port; // $s0
	u32 port_1; // $s7
	u32 port_2; // $s0
	u32 stat70; // $s0
	int chslot_buf_tmp[2]; // [sp+10h] [-10h]
	int porttmp[2]; // [sp+18h] [-8h]

	xferdatres = 0;
	sio2_td.in_size = 0;
	sio2_td.out_size = 0;
	sio2_td.out_dma.addr = NULL;
	sio2_td.in_dma.addr = NULL;
	chslot_buf_tmp[1] = 0;
	chslot_buf_tmp[0] = 0;
	porttmp[1] = 0;
	porttmp[0] = 0;
	port = padData[1][slot].fixme_used_4 == 0x63;
	port_1 = port;
	for ( i = 0; i < 2; i += 1 )
	{
		if ( padData[port][slot].active && change_slot_buffer[port + 4] == 1 )
		{
			chslot_buf_tmp[port] = 1;
			porttmp[port] = xferdatres;
			xferdatres = setupTransferData(xferdatres, port, slot);
		}
		port ^= 1u;
	}
	if ( slot )
	{
		if ( padData[0][slot].active == 1 && change_slot_buffer[4] != 1 )
			padData[0][slot].error = 10;
		if ( padData[1][slot].active == 1 && change_slot_buffer[5] != 1 )
			padData[1][slot].error = 10;
	}
	if ( xferdatres )
	{
		sio2_transfer2(&sio2_td);
		sio2_td.out_size = 0;
		port_2 = port_1;
		for ( i = 0; i < 2; i += 1 )
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
	change_slot_buffer[0] = -1;
	change_slot_buffer[1] = -1;
	change_slot_buffer[2] = -1;
	change_slot_buffer[3] = -1;
	if ( !padData[0][slot].active && !padData[1][slot].active )
		return 0;
	if ( padData[0][slot].active == 1 )
		change_slot_buffer[0] = slot;
	if ( padData[1][slot].active == 1 )
		change_slot_buffer[1] = slot;
	sio2_mtap_change_slot(change_slot_buffer);
	return 1;
}

//----- (00405194) --------------------------------------------------------
void pdTransfer(void)
{
	signed __int32 slot; // $s0

	sio2_pad_transfer_init2();
	++transferCount;
	for ( slot = 0; slot < 4; slot += 1 )
	{
		if ( padData[0][slot].active == 1 || padData[1][slot].active == 1 )
		{
			if ( slot > 0 )
				mtapChangeSlot(slot);
			padTransfer(slot);
		}
	}
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
	return ( port >= 2 ) ? -1 : (s32)padData[port][slot].error;
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
	signed __int32 i; // $t0

	if ( port >= 2 )
		return 0;
	if ( !size )
		size = padData[port][slot].in_size;
	for ( i = 0; i < (int)size; i += 1 )
		padData[port][slot].in_buffer[i] = buf[i];
	return size;
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
	signed __int32 i; // $t0

	if ( port >= 2 )
		return 0;
	if ( !size )
		size = padData[port][slot].out_size;
	for ( i = 0; i < (int)size; i += 1 )
		buf[i] = padData[port][slot].out_buffer[i];
	return size;
}

//----- (004055A0) --------------------------------------------------------
int __fastcall unusedref_4055A0(unsigned int port, u32 slot, u32 port_ctrl)
{
	u8 inbuftmp[32]; // [sp+10h] [-20h] BYREF

	pdSetCtrl1(port, slot, sio2CmdGetPortCtrl1(0, port_ctrl, 0));
	pdSetCtrl2(port, slot, sio2CmdGetPortCtrl2(0, port_ctrl));
	pdSetRegData(port, slot, pdGetRegData(0));
	pdSetInSize(port, slot, pdGetInSize(0));
	pdSetOutSize(port, slot, pdGetOutSize(0));
	sio2CmdSetReadData(0, inbuftmp);
	pdSetInBuffer(port, slot, 0, inbuftmp);
	return 1;
}

//----- (00405680) --------------------------------------------------------
int __fastcall unusedref_405680(u32 port, u32 slot)
{
	u32 stat70_tmp; // $v0

	sio2_td.in_size = 0;
	sio2_td.out_size = 0;
	sio2_td.out_dma.addr = NULL;
	sio2_td.in_dma.addr = NULL;
	if ( change_slot_buffer[port + 4] != 1 )
		return 0;
	stat70_tmp = sio2_stat70_get();
	if ( !port )
		pdSetStat70bit(0, slot, (stat70_tmp >> 4) & 1);
	if ( port == 1 )
		pdSetStat70bit(1u, slot, (stat70_tmp >> 5) & 1);
	setupTransferData(0, port, slot);
	sio2_transfer2(&sio2_td);
	sio2_td.out_size = 0;
	readSio2OutBuffer(0, port, slot);
	sio2_td.out_size = padData[port][slot].out_size;
	if ( change_slot_buffer[port + 4] != 1 )
		padData[port][slot].error = 10;
	return 1;
}
// 4095F0: using guessed type sio2_transfer_data_t sio2_td;

//----- (004057D4) --------------------------------------------------------
int __fastcall unused_4057D4(u32 port, s32 slot)
{
	int retres; // $s4

	retres = 0;
	sio2_pad_transfer_init2();
	change_slot_buffer[2] = -1;
	change_slot_buffer[3] = -1;
	change_slot_buffer[0] = slot;
	change_slot_buffer[1] = slot;
	sio2_mtap_change_slot(change_slot_buffer);
	unusedref_4055A0(0, slot, pdGetStat70bit(0, slot));
	unusedref_4055A0(1u, slot, pdGetStat70bit(1u, slot));
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
	int i; // $v1

	for ( i = 15; i >= 0; i -= 1 )
		sio2Cmds[i].id = 0;
	numControllers = 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405940) --------------------------------------------------------
int __cdecl SetupCmds(const sio2Cmds_t *s)
{
	int i; // $v1

	if ( numControllers + 1 >= 16 || !s )
		return 0;
	for ( i = 0; i < numControllers; i += 1 )
		if ( s->id == sio2Cmds[i].id )
			return 0;
	sio2Cmds[numControllers].id = s->id;
	sio2Cmds[numControllers].readdata = s->readdata;
	sio2Cmds[numControllers].getportctrl1 = s->getportctrl1;
	sio2Cmds[numControllers].getportctrl2 = s->getportctrl2;
	sio2Cmds[numControllers].reg_data = s->reg_data;
	sio2Cmds[numControllers].size1 = s->size1;
	sio2Cmds[numControllers].size2 = s->size2;
	sio2Cmds[numControllers].enterconfigmode = s->enterconfigmode;
	sio2Cmds[numControllers].exitconfigmode = s->exitconfigmode;
	sio2Cmds[numControllers].querymodel = s->querymodel;
	sio2Cmds[numControllers].queryact = s->queryact;
	sio2Cmds[numControllers].querycomb = s->querycomb;
	sio2Cmds[numControllers].querymode = s->querymode;
	sio2Cmds[numControllers].querybuttonmask = s->querybuttonmask;
	sio2Cmds[numControllers].setbuttoninfo = s->setbuttoninfo;
	sio2Cmds[numControllers].setvrefparam = s->setvrefparam;
	sio2Cmds[numControllers].setmainmode = s->setmainmode;
	sio2Cmds[numControllers].setactalign = s->setactalign;
	numControllers += 1;
	return 1;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405B0C) --------------------------------------------------------
u32 __cdecl sio2cmdCheckId(u8 id)
{
	int i; // $a1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id )
			return 1;
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405B68) --------------------------------------------------------
void __cdecl sio2CmdSetReadData(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
	{
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].readdata )
		{
			sio2Cmds[i].readdata(buf);
			return;
		}
	}
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405BF8) --------------------------------------------------------
u32 __cdecl sio2CmdGetPortCtrl1(u8 id, u32 b, u8 c)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].getportctrl1 )
			return sio2Cmds[i].getportctrl1(b, c);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405C90) --------------------------------------------------------
u32 __cdecl sio2CmdGetPortCtrl2(u32 id, u32 b)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].getportctrl2 )
			return sio2Cmds[i].getportctrl2(b);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405D24) --------------------------------------------------------
u32 __cdecl pdGetInSize(u8 id)
{
	return 2 * ((id ? id : 0x41) & 0xF) + 3;
}

//----- (00405D44) --------------------------------------------------------
u32 __cdecl pdGetOutSize(u8 id)
{
	return 2 * ((id ? id : 0x41) & 0xF) + 3;
}

//----- (00405D64) --------------------------------------------------------
u32 __cdecl pdGetRegData(u32 id)
{
	return (((pdGetInSize(id) & 0x1FF) << 8) | 0x40) | ((pdGetOutSize(id & 0xFF) & 0x1FF) << 18);
}

//----- (00405DB4) --------------------------------------------------------
u32 __cdecl sio2CmdSetEnterConfigMode(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].enterconfigmode )
			return sio2Cmds[i].enterconfigmode(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405E48) --------------------------------------------------------
u32 __cdecl sio2CmdSetExitConfigMode(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].exitconfigmode )
			return sio2Cmds[i].exitconfigmode(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405EDC) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryModel(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].querymodel )
			return sio2Cmds[i].querymodel(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00405F70) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryAct(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].queryact )
			return sio2Cmds[i].queryact(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00406004) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryComb(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].querycomb )
			return sio2Cmds[i].querycomb(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00406098) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryMode(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].querymode )
			return sio2Cmds[i].querymode(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (0040612C) --------------------------------------------------------
u32 __cdecl sio2CmdSetQueryButtonMask(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].querybuttonmask )
			return sio2Cmds[i].querybuttonmask(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (004061C0) --------------------------------------------------------
u32 __cdecl sio2CmdSetSetButtonInfo(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].setbuttoninfo )
			return sio2Cmds[i].setbuttoninfo(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (00406254) --------------------------------------------------------
u32 __cdecl sio2CmdSetSetVrefParam(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].setvrefparam )
			return sio2Cmds[i].setvrefparam(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (004062E8) --------------------------------------------------------
u32 __cdecl sio2CmdSetSetMainMode(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].setmainmode )
			return sio2Cmds[i].setmainmode(buf);
	return 0;
}
// 4098B0: using guessed type sio2Cmds_t sio2Cmds[16];
// 409D30: using guessed type int numControllers;

//----- (0040637C) --------------------------------------------------------
u32 __cdecl sio2CmdSetSetActAlign(u32 id, u8 *buf)
{
	int i; // $v1

	for ( i = 0; (i + 1) < numControllers; i += 1 )
		if ( (unsigned __int8)(id >> 4) == sio2Cmds[i].id && sio2Cmds[i].setactalign )
			return sio2Cmds[i].setactalign(buf);
	return 0;
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (00406450) --------------------------------------------------------
u32 __cdecl FindPadsGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x2000A;
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
	return (((FindPadsGetSize1() & 0x1FF) << 8) | 0x40) | ((FindPadsGetSize2() & 0x1FF) << 18);
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (004065B8) --------------------------------------------------------
u32 __cdecl MouseGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (00406710) --------------------------------------------------------
u32 __cdecl DigitalGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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
	return a ? 0xFF060505 :  (((((b & 2) ? 10 : 5) | (((b & 2) ? 10 : 5) << 8)) & 0xFF00FFFF) | (((b & 2) ? 0x60 : 0xC0) << 16) | 0xFF000000);
}

//----- (004068DC) --------------------------------------------------------
u32 __cdecl AnalogGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (00406A30) --------------------------------------------------------
u32 __cdecl NegiconGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (00406BA0) --------------------------------------------------------
u32 __cdecl JoystickGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (00406D04) --------------------------------------------------------
u32 __cdecl KonamiGunGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (00406E60) --------------------------------------------------------
u32 __cdecl NamcoGunGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (00406FE0) --------------------------------------------------------
u32 __cdecl JogconGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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

	return a ? 0xFF060505 : 0xFFC00505;
}

//----- (00407164) --------------------------------------------------------
u32 __cdecl ConfigGetPortCtrl2(u32 a)
{
	return a ? 0x2012C : 0x20014;
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
			break;
		case 0x14:
			RpcSetVerbose((u32 *)buffer);
			break;
		case 0x18:
			RpcSetNonblockDma((u32 *)buffer);
			break;
		default:
			printf("invalid function code (%03x)\n", *(_DWORD *)buffer);
			break;
	}
	return buffer;
}

//----- (00407A28) --------------------------------------------------------
void __cdecl RpcThread(void *arg)
{
	(void)arg;
	if ( !sceSifCheckInit() )
	{
		printf("yet sif hasn't been init\n");
		sceSifInit();
	}
	sceSifInitRpc(0);
	sceSifSetRpcQueue(&rpc_qd, GetThreadId());
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
	(void)arg;
	if ( !sceSifCheckInit() )
	{
		printf("yet sif hasn't been init\n");
		sceSifInit();
	}
	sceSifInitRpc(0);
	sceSifSetRpcQueue(&rpcext_qd, GetThreadId());
	sceSifRegisterRpc(&rpcext_sd, 0x80000101, (SifRpcFunc_t)RpcServerExt, rpcext_buf, NULL, NULL, &rpcext_qd);
	sceSifRpcLoop(&rpcext_qd);
}
// 409E24: using guessed type SifRpcDataQueue_t rpcext_qd;
// 409E3C: using guessed type SifRpcServerData_t rpcext_sd;
// 409E80: using guessed type int rpcext_buf[32];

//----- (00407B80) --------------------------------------------------------
int __cdecl InitRpcServers(int prio)
{
	iop_thread_t thparam; // [sp+10h] [-18h] BYREF

	thparam.attr = 0x2000000;
	thparam.thread = (void (__cdecl *)(void *))RpcThread;
	thparam.priority = prio ? prio : 46;
	thparam.stacksize = 2048;
	ThreadIdRpcServer = CreateThread(&thparam);
	if ( !ThreadIdRpcServer )
		return 0;
	StartThread(ThreadIdRpcServer, NULL);
	thparam.attr = 0x2000000;
	thparam.thread = (void (__cdecl *)(void *))RpcThreadExt;
	thparam.priority = prio ? prio : 46;
	thparam.stacksize = 2048;
	ThreadIdRpcServerExt = CreateThread(&thparam);
	if ( !ThreadIdRpcServerExt )
		return 0;
	StartThread(ThreadIdRpcServerExt, NULL);
	return 1;
}
// 409D40: using guessed type int ThreadIdRpcServer;
// 409E20: using guessed type int ThreadIdRpcServerExt;
