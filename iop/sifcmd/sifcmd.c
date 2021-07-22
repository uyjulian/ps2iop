//[module]	SIFCMD
//[processor]	IOP
//[type]	ELF-IRX
//[name]	IOP_SIF_rpc_interface
//[version]	0x101
//[memory map]
//[handlers]
//[entry point]	sifcmd_start, sifcmd_stub
//[made by]	[RO]man (roman_ps2dev@hotmail.com)

#include "loadcore.h"
#include "intrman.h"
#include "sifman.h"
#include "thbase.h"
#include "thevent.h"
#include "sifcmd.h"
#include "stdio.h"


#define SIF_CMDI_SYSTEM 0x80000000 // system function call
#define SIF_CMDC_CHANGE_SADDR (SIF_CMDI_SYSTEM | 0x00000000)
#define SIF_CMDC_SET_SREG (SIF_CMDI_SYSTEM | 0x00000001)
#define SIF_CMDC_INIT_CMD (SIF_CMDI_SYSTEM | 0x00000002)
#define SIF_CMDC_RESET_CMD (SIF_CMDI_SYSTEM | 0x00000003)

#define SIF_CMDC_RPC_END (SIF_CMDI_SYSTEM | 0x00000008)
#define SIF_CMDC_RPC_BIND (SIF_CMDI_SYSTEM | 0x00000009)
#define SIF_CMDC_RPC_CALL (SIF_CMDI_SYSTEM | 0x0000000A)
#define SIF_CMDC_RPC_RDATA (SIF_CMDI_SYSTEM | 0x0000000C)

typedef struct
{
	unsigned int psize : 8; // packet size [16->112]
	unsigned int dsize : 24; // extra data size
	unsigned int daddr; // extra data address
	unsigned int fcode; // function code
	unsigned int opt; // optional user parameter
} SifCmdHdr;

// typedef int (*SifCmdHandler_t)(SifCmdHdr*, void*);
typedef void* (*rpch_func)(u32 code, void* param1, int param2);

typedef struct
{
	SifCmdHdr hdr;
	void* newaddr;
} SifCmdCSData;

typedef struct
{
	SifCmdHdr chdr;
	int rno;
	unsigned int value;
} SifCmdSRData;

typedef struct
{
	SifCmdHdr chdr;
	int size;
	int flag;
	char arg[80];
} SifCmdResetData;

typedef struct
{
	SifCmdHdr hdr;
	u32 rec_id;
	void* paddr;
	u32 pid;
} RPC_PACKET;

typedef struct
{
	RPC_PACKET packet;
	SifRpcClientData_t* client;
	u32 command;
	SifRpcServerData_t* server;
	void *buff, *cbuff;
} RPC_PACKET_END;

typedef struct
{
	RPC_PACKET packet;
	SifRpcClientData_t* client;
	u32 fno;
} RPC_PACKET_BIND;

typedef struct
{
	RPC_PACKET_BIND packet;
	u32 size;
	void* receive;
	u32 rsize;
	u32 rmode;
	SifRpcServerData_t* server;
} RPC_PACKET_CALL;

typedef struct
{
	RPC_PACKET packet;
	SifRpcClientData_t* client;
	void* src;
	void* dst;
	u32 size;
} RPC_PACKET_RDATA;


typedef struct
{
	SifCmdHandler_t func;
	void* data;
} SifCmdData;

#define INT_VBLANK 0x00

#define INT_CDROM 0x02

#define INT_RTC0 0x04
#define INT_RTC1 0x05
#define INT_RTC2 0x06

#define INT_EVBLANK 0x0B

#define INT_RTC3 0x0E
#define INT_RTC4 0x0F
#define INT_RTC5 0x10

#define INT_DMA9 0x2A //sif0
#define INT_DMA10 0x2B //sif1

#define IMODE_DMA_IRM 0x100
#define IMODE_DMA_IQE 0x200


int sifInitRpc = 0;

// CMD data
char sif1_rcvBuffer[8 * 16]; //8 qwords
char b[4 * 16]; //not used
struct tag_cmd_common
{
	char *sif1_rcvBuffer, //+00
		*b, //+04
		*saddr; //+08
	SifCmdHandlerData_t* sysCmdBuffer; //+0C
	int sysCmdBufferSize; //+10
	SifCmdHandlerData_t* cmdBuffer; //+14
	int cmdBufferSize, //+18
		*Sreg, //+1C
		systemStatusFlag; //+20
	void (*func)(int); //+24
	int param, //+28
		_pad; //+2C
} cmd_common; //=30
SifCmdHandlerData_t sysCmds[32];
int Sreg[32];

// RPC data
int bufx[512], bufy[512];
struct tag_rpc_common
{
	int pid;
	RPC_PACKET* paddr;
	int size;
	RPC_PACKET* paddr2;
	int size2;
	void* next;
	int count;
	int base;
	void* queue;
	int _pad0,
		_pad1,
		_pad2;
} rpc_common;


int _start();

///////////////////////////////////////////////////////////////////////
//////////////////////////// CMD //////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
void cmd80000001_SET_SREG(SifCmdSRData* packet, struct tag_cmd_common* common)
{
	common->Sreg[packet->rno] = packet->value;
}

///////////////////////////////////////////////////////////////////////
void cmd80000000_CHANGE_SADDR(SifCmdCSData* packet, struct tag_cmd_common* common)
{
	common->saddr = packet->newaddr;
}

///////////////////////////////////////////////////////////////////////[06]
// TODO: wrong definition in ps2sdk!
void sceSifGetSreg(int index)
{
#if 0
	return Sreg[index];
#endif
}

///////////////////////////////////////////////////////////////////////[07]
void sceSifSetSreg(int index, unsigned int value)
{
	Sreg[index] = value;
}

///////////////////////////////////////////////////////////////////////
void* getCmdCommon()
{
	return &cmd_common;
}

///////////////////////////////////////////////////////////////////////
void cmd80000002_INIT_CMD(SifCmdCSData* packet, struct tag_cmd_common* common)
{
	if (packet->hdr.opt == 0)
	{
		iSetEventFlag(common->systemStatusFlag, 0x100);
		sceSifSetMSFlag(0x20000);
		common->saddr = packet->newaddr;
	}
	else
		iSetEventFlag(common->systemStatusFlag, 0x800);
}

///////////////////////////////////////////////////////////////////////[02]
int SifDeinitCmd()
{
	int x;
	DisableIntr(INT_DMA10, &x);
	ReleaseIntrHandler(INT_DMA10);
	// TODO: add prototype to ps2sdk
#if 0
	SifDeinit();
#endif
	return 0;
}

///////////////////////////////////////////////////////////////////////[04]
void sceSifInitCmd()
{
	sceSifSetSMFlag(0x20000);
	WaitEventFlag(cmd_common.systemStatusFlag, 0x100, 0, 0);
}

///////////////////////////////////////////////////////////////////////[05]
void sceSifExitCmd()
{
	int x;
	DisableIntr(INT_DMA10, &x);
	ReleaseIntrHandler(INT_DMA10);
}

///////////////////////////////////////////////////////////////////////[08]
// TODO: correct ps2sdk definition
void sceSifSetCmdBuffer(SifCmdHandlerData_t* cmdBuffer, int size)
{
	register SifCmdHandlerData_t* old;
	old = cmd_common.cmdBuffer;
	cmd_common.cmdBuffer = cmdBuffer;
	cmd_common.cmdBufferSize = size;
}

///////////////////////////////////////////////////////////////////////[09]
// TODO: correct ps2sdk definition
void sceSifSetSysCmdBuffer(SifCmdHandlerData_t* sysCmdBuffer, int size)
{
	register SifCmdHandlerData_t* old;
	old = cmd_common.sysCmdBuffer;
	cmd_common.sysCmdBuffer = sysCmdBuffer;
	cmd_common.sysCmdBufferSize = size;
}

///////////////////////////////////////////////////////////////////////[0A]
void sceSifAddCmdHandler(int pos, SifCmdHandler_t f, void* data)
{
	if (pos < 0)
	{
		cmd_common.sysCmdBuffer[pos & 0x1FFFFFFF].handler = f;
		cmd_common.sysCmdBuffer[pos & 0x1FFFFFFF].harg = data;
	}
	else
	{
		cmd_common.cmdBuffer[pos & 0x1FFFFFFF].handler = f;
		cmd_common.cmdBuffer[pos & 0x1FFFFFFF].harg = data;
	}
}

///////////////////////////////////////////////////////////////////////[0B]
void sceSifRemoveCmdHandler(int pos)
{
	if (pos < 0)
		cmd_common.sysCmdBuffer[pos & 0x1FFFFFFF].handler = 0;
	else
		cmd_common.cmdBuffer[pos & 0x1FFFFFFF].handler = 0;
}

///////////////////////////////////////////////////////////////////////
unsigned int sendCmd(unsigned int pos, int mode, SifCmdHdr* cp, int ps, void* src, void* dst, int size)
{
	int x;
	SifDmaTransfer_t dma[2];
	register int count, y;

	if (ps < 16 || ps > 112)
		return 0;

	count = 0;
	if (size > 0)
	{
		count = 1;
		dma[0].dest = dst;
		dma[0].size = size;
		dma[0].attr = 0;
		dma[0].src = src;
		cp->daddr = (u32)dst;
		cp->dsize = size;
	}
	else
	{
		cp->daddr = 0;
		cp->dsize = 0;
	}
	count++;
	cp->psize = ps;
	cp->fcode = pos;
	dma[count - 1].src = cp;
	dma[count - 1].attr = SIF_DMA_INT_O; //calls SIF0 handler
	dma[count - 1].size = ps; //on EE side after transfer;)
	dma[count - 1].dest = cmd_common.saddr;
	if (mode & 1) //interrupt mode
		return sceSifSetDma(dma, count);
	else
	{
		CpuSuspendIntr(&x);
		y = sceSifSetDma(dma, count);
		CpuResumeIntr(x);
		return y;
	}
}

///////////////////////////////////////////////////////////////////////[0C]
unsigned int sceSifSendCmd(int pos, void* cp, int ps, void* src, void* dst, int size)
{
	return sendCmd(pos, 0, cp, ps, src, dst, size);
}

///////////////////////////////////////////////////////////////////////[0D]
unsigned int isceSifSendCmd(int pos, void* cp, int ps, void* src, void* dst, int size)
{
	return sendCmd(pos, 1, cp, ps, src, dst, size);
}

///////////////////////////////////////////////////////////////////////[1A]
void sceSifSetSif1CB(void* func, int param)
{
	cmd_common.func = func;
	cmd_common.param = param;
}

///////////////////////////////////////////////////////////////////////[1B]
void sceSifClearSif1CB()
{
	cmd_common.func = 0;
	cmd_common.param = 0;
}

///////////////////////////////////////////////////////////////////////
int SIF1_handler(void* common)
{
	int buf[112 / 4];
	register int i, ps;
	register SifCmdHandlerData_t* scd;
	SifCmdHdr* packet;
	struct tag_cmd_common* c = (struct tag_cmd_common*)common;

	if (c->func)
		c->func(c->param);

	packet = (SifCmdHdr*)c->sif1_rcvBuffer;

	if ((ps = packet->psize & 0xFF) == 0)
	{
		sceSifSetDChain();
		return 1;
	}
	packet->psize = 0;

	ps = (ps + 3 < 0 ? ps + 6 : ps + 3) / 4;
	for (i = 0; i < ps; i++)
		buf[i] = ((u32*)packet)[i];

	sceSifSetDChain();
	packet = (SifCmdHdr*)buf;
	if (packet->fcode < 0)
	{
		if ((packet->fcode & 0x7FFFFFFF) >= c->sysCmdBufferSize)
			return 1;
		scd = &c->sysCmdBuffer[packet->fcode & 0x7FFFFFFF];
	}
	else
	{
		if (packet->fcode >= c->cmdBufferSize)
			return 1;
		scd = &c->cmdBuffer[packet->fcode];
	}
	if (scd->handler)
		scd->handler(packet, scd->harg);

	return 1;
}

///////////////////////////////////////////////////////////////////////
//////////////////////////// RPC //////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
RPC_PACKET* rpc_get_packet(struct tag_rpc_common* common)
{
	int x;
	register int pid, i;
	RPC_PACKET* packet;

	CpuSuspendIntr(&x);

	for (i = 0, packet = common->paddr; i < common->size; i++)
		if ((packet[i].rec_id & 2) == 0)
			goto found;
	for (i = 0, packet = common->paddr2; i < common->size2; i++)
		if ((packet[i].rec_id & 2) == 0)
			goto found;

	CpuResumeIntr(x);
	return 0;

found:
	packet[i].rec_id |= 2;
	pid = ++common->pid;
	if (pid == 1)
		common->pid++;
	packet[i].pid = pid;
	packet[i].paddr = &packet[i];
	CpuResumeIntr(x);
	return &packet[i];
}

///////////////////////////////////////////////////////////////////////
void rpc_free_packet(RPC_PACKET* packet)
{
	packet->pid = 0;
	packet->rec_id &= 0xFFFFFFFD; //~2
}

///////////////////////////////////////////////////////////////////////
RPC_PACKET* rpc_get_fpacket(struct tag_rpc_common* common)
{
	register int i;

	i = common->base % common->count;
	common->base = i + 1;
	return (RPC_PACKET*)(((u8*)common->next) + i * 64);
}

///////////////////////////////////////////////////////////////////////
void cmd80000008_END(RPC_PACKET_END* packet, struct tag_rpc_common* common)
{
	if (packet->command == 0x8000000A)
	{
		if (packet->client->end_function)
			packet->client->end_function(packet->client->end_param);
	}
	else if (packet->command == 0x80000009)
	{
		packet->client->server = packet->server;
		packet->client->buff = packet->buff;
		packet->client->cbuff = packet->cbuff;
	}

	if (packet->client->hdr.sema_id >= 0)
		iWakeupThread(packet->client->hdr.sema_id);

	rpc_free_packet(packet->client->hdr.pkt_addr);
	packet->client->hdr.pkt_addr = 0;
}

///////////////////////////////////////////////////////////////////////
void cmd8000000C_RDATA(RPC_PACKET_RDATA* packet, struct tag_rpc_common* common)
{
	RPC_PACKET_END* epacket;

	epacket = (RPC_PACKET_END*)rpc_get_fpacket(common);

	epacket->packet.paddr = packet->packet.paddr;
	epacket->command = 0x8000000C;
	epacket->client = packet->client;

	isceSifSendCmd(0x80000008, epacket, 0x40, packet->src, packet->dst, packet->size);
}

///////////////////////////////////////////////////////////////////////[17]
int sceSifGetOtherData(SifRpcReceiveData_t* rd, void* src, void* dst, int size, int mode)
{
	RPC_PACKET_RDATA* packet;

	if ((packet = (RPC_PACKET_RDATA*)rpc_get_packet(&rpc_common)) == 0)
		return -1;

	rd->hdr.pkt_addr = packet;
	rd->hdr.rpc_id = packet->packet.pid;
	packet->packet.paddr = packet;
	packet->client = (SifRpcClientData_t*)rd;
	packet->src = src;
	packet->dst = dst;
	packet->size = size;

	if ((mode & 1) == 0)
	{
		rd->hdr.sema_id = GetThreadId();
		if (sceSifSendCmd(0x8000000C, packet, 0x40, 0, 0, 0) == 0)
			return -2;
		SleepThread();
	}
	else
	{ //async
		rd->hdr.sema_id = -1;
		if (sceSifSendCmd(0x8000000C, packet, 0x40, 0, 0, 0) == 0)
			return -2;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////
SifRpcServerData_t* search_svdata(u32 command, struct tag_rpc_common* common)
{
	SifRpcServerData_t* q;
	SifRpcServerData_t* s;

	for (q = common->queue; q; q = q->next)
	{
		for (s = q->link; s; s = s->link)
		{
			if (s->sid == command)
				return s;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////
void cmd80000009_BIND(RPC_PACKET_BIND* packet, struct tag_rpc_common* common)
{
	RPC_PACKET_END* epacket;
	SifRpcServerData_t* s;

	epacket = (RPC_PACKET_END*)rpc_get_fpacket(common);

	epacket->packet.paddr = packet->packet.paddr;
	epacket->command = 0x80000009;
	epacket->client = packet->client;

	s = search_svdata(packet->fno, common);
	if (s == NULL)
	{
		epacket->server = 0;
		epacket->buff = 0;
		epacket->cbuff = 0;
	}
	else
	{
		epacket->server = s;
		epacket->buff = s->buff;
		epacket->cbuff = s->cbuff;
	}
	isceSifSendCmd(0x80000008, epacket, 0x40, 0, 0, 0);
}

///////////////////////////////////////////////////////////////////////[0F]
int sceSifBindRpc(SifRpcClientData_t* client, int number, int mode)
{
	RPC_PACKET_BIND* packet;

	client->command = 0;
	client->server = 0;

	packet = (RPC_PACKET_BIND*)rpc_get_packet(&rpc_common);
	if (packet == NULL)
		return -1;

	client->hdr.pkt_addr = packet;
	client->hdr.rpc_id = packet->packet.pid;
	packet->packet.paddr = packet;
	packet->client = client;
	packet->fno = number;

	if ((mode & 1) == 0)
	{
		client->hdr.sema_id = GetThreadId();
		if (sceSifSendCmd(0x80000009, packet, 0x40, 0, 0, 0) == 0)
			return -2;
		SleepThread();
	}
	else
	{ //async
		client->hdr.sema_id = -1;
		if (sceSifSendCmd(0x80000009, packet, 0x40, 0, 0, 0) == 0)
			return -2;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////
void cmd8000000A_CALL(RPC_PACKET_CALL* packet, struct tag_rpc_common* common)
{
	SifRpcDataQueue_t* qd;

	qd = packet->server->base;
	if (qd->start == 0)
		qd->start = packet->server;
	else
		qd->end->link = packet->server;
	qd->end = packet->server;
	packet->server->pkt_addr = packet->packet.packet.paddr;
	packet->server->client = packet->packet.client;
	packet->server->rpc_number = packet->packet.fno;
	packet->server->size = packet->size;
	packet->server->receive = packet->receive;
	packet->server->rsize = packet->rsize;
	packet->server->rmode = packet->rmode;
	if ((qd->thread_id >= 0) && (qd->active == 0))
		iWakeupThread(qd->thread_id);
}

///////////////////////////////////////////////////////////////////////[10]
int sceSifCallRpc(SifRpcClientData_t* client, int fno, int mode, void* send, int ssize, void* receive, int rsize, void (*end_func)(void*), void* end_para)
{
	RPC_PACKET_CALL* packet;

	if ((packet = (RPC_PACKET_CALL*)rpc_get_packet(&rpc_common)) == 0)
		return -1;
	client->hdr.pkt_addr = (void*)packet;
	client->end_function = end_func;
	client->end_param = end_para;
	client->hdr.rpc_id = packet->packet.packet.pid;

	packet->packet.packet.paddr = packet;
	packet->packet.client = client;
	packet->packet.fno = fno;
	packet->size = ssize;
	packet->receive = receive;
	packet->rsize = rsize;
	packet->server = client->server;

	if (mode & 1)
	{
		packet->rmode = (end_func != 0);
		client->hdr.sema_id = -1;
		if (sceSifSendCmd(0x8000000A, packet, 0x40, send, client->buff, ssize))
			return 0;
		return -2;
	}
	else
	{
		packet->rmode = 1;
		client->hdr.sema_id = GetThreadId();
		if (sceSifSendCmd(0x8000000A, packet, 0x40, send, client->buff, ssize) == 0)
			return -2;
		SleepThread();
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////[12]
int sceSifCheckStatRpc(SifRpcClientData_t* rd)
{
	RPC_PACKET* packet = (RPC_PACKET*)rd->hdr.pkt_addr;
	return (rd->hdr.pkt_addr &&
			(rd->hdr.rpc_id == packet->pid) &&
			(packet->rec_id & 2));
}

///////////////////////////////////////////////////////////////////////[13]
SifRpcDataQueue_t * sceSifSetRpcQueue(SifRpcDataQueue_t* qd, int key)
{
	int x;
	register SifRpcDataQueue_t *q, *i;

	CpuSuspendIntr(&x);
	qd->thread_id = key;
	qd->active = 0;
	qd->link = 0;
	qd->start = 0;
	qd->end = 0;
	qd->next = 0;
	q = (SifRpcDataQueue_t*)&rpc_common.queue;
	if (q)
	{
		for (i = q->next; i; i = q->next)
			q = q->next;
	}
	rpc_common.queue = qd;
	CpuResumeIntr(x);
	// TODO: check return value
	return q;
}

///////////////////////////////////////////////////////////////////////[11]
void sceSifRegisterRpc(SifRpcServerData_t* sd, int command,
	SifRpcFunc_t func, void* buff,
	SifRpcFunc_t cfunc, void* cbuff,
	SifRpcDataQueue_t* qd)
{
	int x;
	register SifRpcDataQueue_t *q, *i;

	CpuSuspendIntr(&x);
	sd->sid = command;
	sd->func = func;
	sd->buff = buff;
	sd->next = 0;
	sd->link = 0;
	sd->cfunc = cfunc;
	sd->cbuff = cbuff;
	sd->base = qd;

	if (qd->link == 0)
		qd->link = sd;
	else
	{
		for (q = qd->link, i = q->link; i; i = q->link)
			q = q->link;
		q->link = sd;
	}
	CpuResumeIntr(x);
}

///////////////////////////////////////////////////////////////////////[18]
SifRpcServerData_t* sceSifRemoveRpc(SifRpcServerData_t* sd, SifRpcDataQueue_t* qd)
{
	int x;
	register SifRpcServerData_t* s;

	CpuSuspendIntr(&x);

	if ((s = qd->link) == sd)
		qd->link = s->link;
	else
		for (; s; s = s->link)
			if (s->link == sd)
			{
				s->link = s->link->link;
				break;
			}
	CpuResumeIntr(x);
	return s;
}

///////////////////////////////////////////////////////////////////////[19]
SifRpcDataQueue_t* sceSifRemoveRpcQueue(SifRpcDataQueue_t* qd)
{
	int x;
	register SifRpcDataQueue_t* q;

	CpuSuspendIntr(&x);

	q = rpc_common.queue;
	if (q == qd)
	{
		rpc_common.queue = q->next;
	}
	else
	{
		for (; q; q = q->next)
		{
			if (q->next == qd)
			{
				q->next = q->next->next;
				break;
			}
		}
	}
	CpuResumeIntr(x);
	return q;
}

///////////////////////////////////////////////////////////////////////[14]
SifRpcServerData_t* sceSifGetNextRequest(SifRpcDataQueue_t* qd)
{
	int x;
	register SifRpcServerData_t* s;

	CpuSuspendIntr(&x);

	if ((s = qd->start) == 0)
		qd->active = 0;
	else
	{
		qd->active = 1;
		qd->start = qd->start->next;
	}

	CpuResumeIntr(x);
	return s;
}

///////////////////////////////////////////////////////////////////////[15]
void sceSifExecRequest(SifRpcServerData_t* sd)
{
	int x;
	register int size, id, count, i;
	register void* buff;
	RPC_PACKET_END* epacket;
	SifDmaTransfer_t dma[2];

	size = 0;
	buff = sd->func(sd->rpc_number, sd->buff, sd->size);
	if (buff != 0)
		size = sd->rsize;

	CpuSuspendIntr(&x);
	epacket = (RPC_PACKET_END*)rpc_get_fpacket(&rpc_common);
	CpuResumeIntr(x);

	epacket->command = 0x8000000A;
	epacket->client = sd->client;
	count = 0;
	if (sd->rmode)
	{
		while (sceSifSendCmd(0x80000008, epacket, 0x40, buff, sd->receive, size) == 0)
			;
		return;
	}
	else
	{
		epacket->packet.pid = 0;
		epacket->packet.rec_id = 0;
		if (size > 0)
		{
			count = 1;
			dma[count - 1].src = buff;
			dma[count - 1].size = size;
			dma[count - 1].attr = 0;
			dma[count - 1].dest = sd->receive;
		}
		count++;
		dma[count - 1].src = epacket;
		dma[count - 1].size = 0x40;
		dma[count - 1].attr = 0;
		dma[count - 1].dest = sd->pkt_addr;
		do
		{
			CpuSuspendIntr(&x);
			id = sceSifSetDma(dma, count);
			CpuResumeIntr(x);
			if (id)
				break;
			i = 0xFFFF;
			do
				--i;
			while (i != -1);
		} while (id == 0);
	}
}

///////////////////////////////////////////////////////////////////////[16]
void sceSifRpcLoop(SifRpcDataQueue_t* qd)
{
	register SifRpcServerData_t* s;

	do
	{
		s = sceSifGetNextRequest(qd);
		if (s != 0)
			sceSifExecRequest(s);
		else
			SleepThread();
	} while (1);
}

///////////////////////////////////////////////////////////////////////[0E]
void sceSifInitRpc(int mode)
{
	int x;

	sceSifInitCmd();
	CpuSuspendIntr(&x);

	if (sifInitRpc)
	{
		CpuResumeIntr(x);
	}
	else
	{
		sifInitRpc = 1;
		rpc_common.paddr = (RPC_PACKET*)bufx;
		rpc_common.size = 32;
		rpc_common.paddr2 = 0;
		rpc_common.size2 = 0;
		rpc_common.next = (RPC_PACKET*)bufy;
		rpc_common.count = 32;
		rpc_common.base = 0;
		rpc_common.pid = 1;

		sceSifAddCmdHandler(0x80000008, (SifCmdHandler_t)cmd80000008_END, &rpc_common);
		sceSifAddCmdHandler(0x80000009, (SifCmdHandler_t)cmd80000009_BIND, &rpc_common);
		sceSifAddCmdHandler(0x8000000A, (SifCmdHandler_t)cmd8000000A_CALL, &rpc_common);
		sceSifAddCmdHandler(0x8000000C, (SifCmdHandler_t)cmd8000000C_RDATA, &rpc_common);

		CpuResumeIntr(x);

		((SifCmdSRData*)bufx)->rno = 0;
		((SifCmdSRData*)bufx)->value = 1;
		sceSifSendCmd(0x80000001, (void*)bufx, sizeof(SifCmdSRData), 0, 0, 0);
	}
	WaitEventFlag(GetSystemStatusFlag(), 0x800, 0, 0);
}

#define MODNAME "IOP_SIF_rpc_interface"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_sifcmd;

//////////////////////////////entrypoint///////////////////////////////[00]
int _start()
{
	register u32 *v;
	register int i;

	v = QueryBootMode(3);
	if (v != 0)
	{
		if (v[1] & 1)
		{
			printf("%s No SIF service(sifcmd)\n", __FUNCTION__);
			return 1;
		}
		if (v[1] & 2)
		{
			printf("%s No SIFCMD/RPC service\n", __FUNCTION__);
			return 1;
		}
	}

	if (sceSifCheckInit() == 0)
		sceSifInit();

	if (RegisterLibraryEntries(&_exp_sifcmd))
		return 1;

	cmd_common.sif1_rcvBuffer = sif1_rcvBuffer;
	cmd_common.b = b;
	cmd_common.sysCmdBuffer = sysCmds;
	cmd_common.sysCmdBufferSize = 32;
	cmd_common.saddr = 0;
	cmd_common.cmdBuffer = 0;
	cmd_common.cmdBufferSize = 0;
	cmd_common.Sreg = Sreg;
	cmd_common.func = 0;
	cmd_common.param = 0;

	for (i = 0; i < 32; i++)
	{
		sysCmds[i].handler = 0;
		sysCmds[i].harg = 0;
	}
	for (i = 0; i < 32; i++)
	{
		Sreg[i] = 0;
	}

	sysCmds[0].handler = (SifCmdHandler_t)cmd80000000_CHANGE_SADDR;
	sysCmds[0].harg = &cmd_common;

	sysCmds[1].handler = (SifCmdHandler_t)cmd80000001_SET_SREG;
	sysCmds[1].harg = &cmd_common;

	cmd_common.systemStatusFlag = GetSystemStatusFlag();

	sysCmds[2].handler = (SifCmdHandler_t)cmd80000002_INIT_CMD;
	sysCmds[2].harg = &cmd_common;

	RegisterIntrHandler(INT_DMA10, 1, SIF1_handler, (void*)&cmd_common);
	EnableIntr(INT_DMA10 | IMODE_DMA_IQE);

	sceSifSetSubAddr((u32)sif1_rcvBuffer);

	return 0;
}
