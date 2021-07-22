
#include "loadcore.h"
#include "intrman.h"
#include "dmacman.h"
#include "sifman.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define CONFIG_1450 (*(vu32 *)0xBF801450)

#define BD0 (*(vu32 *)0xBD000000) //mscom
#define BD1 (*(vu32 *)0xBD000010) //smcom
#define BD2 (*(vu32 *)0xBD000020) //msflag
#define BD3 (*(vu32 *)0xBD000030) //smflag
#define BD4 (*(vu32 *)0xBD000040)
#define BD5 (*(vu32 *)0xBD000050)
#define BD6 (*(vu32 *)0xBD000060)
#define BD7 (*(vu32 *)0xBD000070)


// imported from other header

#define SIF_FROM_IOP 0x0
#define SIF_TO_IOP   0x1
#define SIF_FROM_EE  0x0
#define SIF_TO_EE    0x1

#define SIF_DMA_INT_I 0x2
#define SIF_DMA_INT_O 0x4
#define SIF_DMA_SPR   0x8
#define SIF_DMA_BSN   0x10
#define SIF_DMA_TAG   0x20

#define INT_VBLANK 0x00

#define INT_CDROM 0x02

#define INT_RTC0 0x04
#define INT_RTC1 0x05
#define INT_RTC2 0x06

#define INT_EVBLANK 0x0B

#define INT_RTC3 0x0E
#define INT_RTC4 0x0F
#define INT_RTC5 0x10

#define INT_DMA9  0x2A //sif0
#define INT_DMA10 0x2B //sif1

#define IMODE_DMA_IRM 0x100
#define IMODE_DMA_IQE 0x200

//SIF2 DMA ch 2 (GPU)
#define DMAch_SIF2_MADR      (*(volatile int *)0xBF8010A0)
#define DMAch_SIF2_BCR       (*(volatile int *)0xBF8010A4)
#define DMAch_SIF2_BCR_size  (*(volatile short *)0xBF8010A4)
#define DMAch_SIF2_BCR_count (*(volatile short *)0xBF8010A6)
#define DMAch_SIF2_CHCR      (*(volatile int *)0xBF8010A8)
//SIF0 DMA ch 9
#define DMAch_SIF9_MADR      (*(volatile int *)0xBF801520)
#define DMAch_SIF9_BCR       (*(volatile int *)0xBF801524)
#define DMAch_SIF9_BCR_size  (*(volatile short *)0xBF801524)
#define DMAch_SIF9_BCR_count (*(volatile short *)0xBF801526)
#define DMAch_SIF9_CHCR      (*(volatile int *)0xBF801528)
#define DMAch_SIF9_TADR      (*(volatile int *)0xBF80152C)
//SIF1 DMA ch 10 (0xA)
#define DMAch_SIFA_MADR      (*(volatile int *)0xBF801530)
#define DMAch_SIFA_BCR       (*(volatile int *)0xBF801534)
#define DMAch_SIFA_BCR_size  (*(volatile short *)0xBF801534)
#define DMAch_SIFA_BCR_count (*(volatile short *)0xBF801536)
#define DMAch_SIFA_CHCR      (*(volatile int *)0xBF801538)

#define DMAch_DPCR  (*(volatile int *)0xBF8010F0)
#define DMAch_DPCR2 (*(volatile int *)0xBF801570)

#define DMAf_30 0x40000000 // unknown; set on 'to' direction
#define DMAf_TR 0x01000000 // DMA transfer
#define DMAf_LI 0x00000400 // Linked list GPU; also SPU & SIF0
#define DMAf_CO 0x00000200 // Continuous stream
#define DMAf_08 0x00000100 // unknown
#define DMAf_DR 0x00000001 // Direction to=0/from=1

// imported from other header end

struct sifData
{
    int data,
        words,
        count,
        addr;
};

int sifSIF2Init = 0,
    sifInit = 0;

struct sm_internal
{
    short id,                 //+000	some id...?!?
        res1;                 //+002	not used
    int index;                //+004	current position in dma buffer
    struct sifData *crtbuf;   //+008	address of current used buffer
    struct sifData buf1[32];  //+00C	first buffer
    struct sifData buf2[32];  //+20C	second buffer
    void (*function)(void *); //+40C	a function ?!?
    void *param;              //+410	a parameter for function
    int res2;                 //+414	not used
} vars;

struct sifData one;
int res3, res4;

int _start(int argc, char *argv);
void RegisterSif0Handler();


///////////////////////////////////////////////////////////////////////
int getBD2_loopchanging()
{
    register int a, b;
    a = BD2;
    b = BD2;
    while (a != b) {
        a = b;
        b = BD2;
    }
    return a;
}

///////////////////////////////////////////////////////////////////////
int getBD3_loopchanging()
{
    register int a, b;
    a = BD3;
    b = BD3;
    while (a != b) {
        a = b;
        b = BD3;
    }
    return a;
}

///////////////////////////////////////////////////////////////////////[04]
void sceSifDma2Init()
{
    if (sifSIF2Init != 0)
        return;

    DMAch_SIF2_CHCR = 0; //reset ch. 2
    DMAch_DPCR |= 0x800; //enable dma ch. 2
    DMAch_DPCR;
    sifSIF2Init = 1;
}

///////////////////////////////////////////////////////////////////////[05]
void sceSifInit()
{
    int x, y;
    u32 msflag;

    if (sifInit != 0)
        return;

    DMAch_DPCR2 |= 0x8800; //enable dma ch. 9 and 10
    DMAch_SIF9_CHCR = 0;
    DMAch_SIFA_CHCR = 0;
    sceSifDma2Init();

    if (CONFIG_1450 & 0x10)
        CONFIG_1450 |= 0x10;
    CONFIG_1450 |= 0x1;

    RegisterSif0Handler();

    CpuSuspendIntr(&x); //intrman
    CpuEnableIntr();    //intrman

    do {                    //EE kernel sif ready
        CpuSuspendIntr(&y); //intrman
        msflag = getBD2_loopchanging();
        CpuResumeIntr(y); //intrman
    } while (!(msflag & 0x10000));

    CpuResumeIntr(x); //intrman
    sceSifSetDChain();
    sceSifSetSubAddr(0); //sif1 receive buffer
    BD3 = 0x10000;       //IOPEE_sifman_init
    BD3;
    sifInit = 1;
}

///////////////////////////////////////////////////////////////////////[02]
void SifDeinit()
{
    int x;

    DisableIntr(INT_DMA9, &x);
    ReleaseIntrHandler(INT_DMA9);
    DMAch_SIF9_CHCR = 0;
    DMAch_SIFA_CHCR = 0;
    if (CONFIG_1450 & 0x10)
        CONFIG_1450 |= 0x10;
}

///////////////////////////////////////////////////////////////////////[29]
int sceSifCheckInit()
{
    return sifInit;
}

///////////////////////////////////////////////////////////////////////[06]
void sceSifSetDChain()
{
    if ((BD4 & 0x40) == 0)
        BD4 = 0x40;
    DMAch_SIFA_CHCR = 0;
    DMAch_SIFA_BCR_size = 32;
    DMAch_SIFA_CHCR = DMAf_08 | DMAf_CO | DMAf_TR | DMAf_30; //EE->IOP (to memory)
}

///////////////////////////////////////////////////////////////////////[30]
void sceSifSetDmaIntrHandler(void (*_function)(void *), void *_param)
{
    vars.function = _function;
    vars.param = _param;
}

///////////////////////////////////////////////////////////////////////[31]
void sceSifResetDmaIntrHandler()
{
    vars.function = NULL;
    vars.param = 0;
}

///////////////////////////////////////////////////////////////////////
int Sif0Handler(void *common)
{
    struct sm_internal *vars = (struct sm_internal *)common;
    int var_10;
    if (vars->function)
        vars->function(vars->param);

    if (((DMAch_SIF9_CHCR & DMAf_TR) == 0) && (vars->index > 0)) {
        DMAch_SIF9_CHCR = 0;
        DMAch_SIF9_TADR = (int)vars->crtbuf;
        DMAch_SIF9_BCR = 32;
        if ((BD4 & 0x20) == 0)
            BD4 = 0x20;
        vars->id++;
        if (vars->crtbuf == vars->buf1) {
            vars->index = 0;
            vars->crtbuf = vars->buf2;
        } else
            vars->crtbuf = vars->buf1;
        DMAch_SIF9_CHCR = DMAf_DR | DMAf_08 | DMAf_CO | DMAf_LI | DMAf_TR; //IOP->EE (from memory)
        var_10 = DMAch_SIF9_CHCR;
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////
void RegisterSif0Handler()
{
    int x;
    vars.index = 0;
    vars.crtbuf = vars.buf1;
    vars.function = NULL;
    vars.param = 0;
    CpuSuspendIntr(&x);                                   //intrman
    RegisterIntrHandler(INT_DMA9, 1, Sif0Handler, &vars); //intrman
    EnableIntr(INT_DMA9);                                 //intrman
    CpuResumeIntr(x);                                     //intrman
}

///////////////////////////////////////////////////////////////////////
void enqueue(SifDmaTransfer_t *psd)
{
    vars.crtbuf[vars.index].data = (u32)psd->src & 0xFFFFFF; //16MB addressability
    if (psd->attr & SIF_DMA_INT_I)
        vars.crtbuf[vars.index].data |= 0x40000000;
    vars.crtbuf[vars.index].words = (psd->size + 3) / 4 & 0xFFFFFF;
    vars.crtbuf[vars.index].count = ((psd->size + 3) / 16 + (((psd->size + 3) / 4) & 3)) | 0x10000000;
    if (psd->attr & SIF_DMA_INT_O)
        vars.crtbuf[vars.index].count |= 0x80000000;
    vars.crtbuf[vars.index].addr = (u32)psd->dest & 0x1FFFFFFF; //512MB addresability
    vars.index++;
}

///////////////////////////////////////////////////////////////////////[07]
int sceSifSetDma(SifDmaTransfer_t *psd, int len)
{
    int var_20;
    register unsigned int ret;
    int i;

    if (32 - vars.index < len)
        return 0; //no place

    ret = vars.id;
    ret = (ret << 16) | ((vars.index & 0xFF) << 8) | (len & 0xFF);

    if (vars.index)
        vars.crtbuf[vars.index - 1].data &= 0x7FFFFFFF;
    for (i = 0; i < len; i++)
        enqueue(&psd[i]);
    vars.crtbuf[vars.index - 1].data |= 0x80000000;

    if ((DMAch_SIF9_CHCR & DMAf_TR) == 0) {
        DMAch_SIF9_CHCR = 0;
        DMAch_SIF9_TADR = (int)vars.crtbuf;

        if ((BD4 & 0x20) == 0)
            BD4 = 0x20;

        DMAch_SIF9_BCR_size = 32;

        vars.index = 0;
        vars.id++;
        if (vars.crtbuf == vars.buf1)
            vars.crtbuf = vars.buf2;
        //stupid :D (why the if?)

        DMAch_SIF9_CHCR = DMAf_DR | DMAf_08 | DMAf_CO | DMAf_LI | DMAf_TR; //IOP->EE
        var_20 = DMAch_SIF9_CHCR;                                          //?!?
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////[08]
int sceSifDmaStat(int id)
{
    if (DMAch_SIF9_CHCR & DMAf_TR) {
        if (id >> 16 == vars.id)
            return 1; //waiting in queue
        if ((id >> 16) + 1 == vars.id)
            return 0; //running
    }
    return -1; //terminated
}

///////////////////////////////////////////////////////////////////////[09]
void sceSifSetOneDma(SifDmaTransfer_t sd)
{
    sd.size = sd.size / 4 + ((sd.size & 3) > 0);
    one.data = ((u32)sd.src & 0xFFFFFF) | 0x80000000;
    one.words = sd.size & 0xFFFFFF;
    if (sd.attr & SIF_DMA_INT_I)
        one.data |= 0x40000000;
    one.count = (sd.size / 4 + ((sd.size & 3) > 0)) | 0x10000000;
    if (sd.attr & SIF_DMA_INT_O)
        one.count |= 0x80000000;
    one.addr = (u32)sd.dest & 0xFFFFFFF;

    if ((BD4 & 0x20) == 0)
        BD4 = 0x20;

    DMAch_SIF9_CHCR = 0;
    DMAch_SIF9_TADR = (u32)&one;
    DMAch_SIF9_BCR_size = 32;
    DMAch_SIF9_CHCR = DMAf_DR | DMAf_08 | DMAf_CO | DMAf_LI | DMAf_TR; //IOP->EE
    DMAch_SIF9_CHCR;
}

///////////////////////////////////////////////////////////////////////[10]
void sceSifSendSync()
{
    while (DMAch_SIF9_CHCR & DMAf_TR)
        ;
}

///////////////////////////////////////////////////////////////////////[11]
int sceSifIsSending()
{
    return (DMAch_SIF9_CHCR & DMAf_TR);
}

///////////////////////////////////////////////////////////////////////[12]
void sceSifDma0Transfer(void *data, int size, int attr)
{
    size = size / 4 + ((size & 3) > 0);

    if ((BD4 & 0x20) == 0)
        BD4 = 0x20;

    DMAch_SIF9_CHCR = 0;
    DMAch_SIF9_MADR = (u32)data & 0xFFFFFF;
    DMAch_SIF9_BCR_size = 32;
    DMAch_SIF9_BCR_count = size / 32 + ((size & 0x1F) > 0);
    DMAch_SIF9_CHCR = DMAf_DR | DMAf_CO | DMAf_TR;
    DMAch_SIF9_CHCR;
}

///////////////////////////////////////////////////////////////////////[13]
void sceSifDma0Sync()
{
    while (DMAch_SIF9_CHCR & DMAf_TR)
        ;
}

///////////////////////////////////////////////////////////////////////[14]
int sceSifDma0Sending()
{
    return (DMAch_SIF9_CHCR & DMAf_TR);
}

///////////////////////////////////////////////////////////////////////[15]
void sceSifDma1Transfer(void *data, int size, int attr)
{
    size = size / 4 + ((size & 3) > 0);

    if ((BD4 & 0x40) == 0)
        BD4 = 0x40;

    DMAch_SIFA_CHCR = 0;
    DMAch_SIFA_MADR = (u32)data & 0xFFFFFF;
    DMAch_SIFA_BCR_size = 32;
    DMAch_SIFA_BCR_count = size / 32 + ((size & 0x1F) > 0);
    DMAch_SIFA_CHCR = DMAf_CO | DMAf_TR |
                      (attr & SIF_DMA_BSN ? DMAf_30 : 0);
    DMAch_SIFA_CHCR;
}

///////////////////////////////////////////////////////////////////////[16]
void sceSifDma1Sync()
{
    while (DMAch_SIFA_CHCR & DMAf_TR)
        ;
}

///////////////////////////////////////////////////////////////////////[17]
int sceSifDma1Sending()
{
    return (DMAch_SIFA_CHCR & DMAf_TR);
}

///////////////////////////////////////////////////////////////////////[18]
void sceSifDma2Transfer(void *data, int size, int attr)
{
    size = size / 4 + ((size & 3) > 0);

    if ((BD4 & 0x80) == 0)
        BD4 = 0x80;

    DMAch_SIF2_CHCR = 0;
    DMAch_SIF2_MADR = (u32)data & 0xFFFFFF;
    DMAch_SIF2_BCR_size = min(size, 32);
    DMAch_SIF2_BCR_count = size / 32 + ((size & 0x1F) > 0);
    DMAch_SIF2_CHCR = DMAf_CO | DMAf_TR |
                      ((attr & SIF_TO_EE ? DMAf_DR :
                                           (attr & SIF_DMA_BSN ? DMAf_30 : 0)));
    DMAch_SIF2_CHCR;
}

///////////////////////////////////////////////////////////////////////[19]
void sceSifDma2Sync()
{
    while (DMAch_SIF2_CHCR & DMAf_TR)
        ;
}

///////////////////////////////////////////////////////////////////////[20]
int sceSifDma2Sending()
{
    return (DMAch_SIF2_CHCR & DMAf_TR);
}

///////////////////////////////////////////////////////////////////////[21]
u32 sceSifGetMSFlag()
{
    return getBD2_loopchanging();
}

///////////////////////////////////////////////////////////////////////[22]
u32 sceSifSetMSFlag(u32 val)
{
    BD2 = val;
    return getBD2_loopchanging();
}

///////////////////////////////////////////////////////////////////////[23]
u32 sceSifGetSMFlag()
{
    return getBD3_loopchanging();
}

///////////////////////////////////////////////////////////////////////[24]
u32 sceSifSetSMFlag(u32 val)
{
    BD3 = val;
    return getBD3_loopchanging();
}

///////////////////////////////////////////////////////////////////////[25]
u32 sceSifGetMainAddr()
{
    return BD0;
}

///////////////////////////////////////////////////////////////////////[26]
u32 sceSifGetSubAddr()
{
    return BD1;
}

///////////////////////////////////////////////////////////////////////[27]
u32 sceSifSetSubAddr(u32 val)
{
    BD1 = val;
    return BD1;
}

///////////////////////////////////////////////////////////////////////[28]
void sceSifIntrMain()
{
    CONFIG_1450 |= 2;
    CONFIG_1450 &= ~2;
    CONFIG_1450;
}

///////////////////////////////////////////////////////////////////////[01,03,32,33,34,35]

//////////////////////////////entrypoint///////////////////////////////


#define MODNAME "IOP_SIF_manager"
IRX_ID(MODNAME, 1, 1);
extern struct irx_export_table _exp_sifman;

//////////////////////////////entrypoint///////////////////////////////[00]
int _start(int argc, char *argv)
{

    return RegisterLibraryEntries(&_exp_sifman) > 0;
}
