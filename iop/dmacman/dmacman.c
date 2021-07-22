//[module]	DMACMAN
//[processor]	IOP
//[type]	ELF-IRX
//[name]	dmacman
//[version]	0x101
//[memory map]	0xBF801080,0xBF801084,0xBF801088,		00 mdec in
//		0xBF801090,0xBF801094,0xBF801098,		01 mdec out
//		0xBF8010A0,0xBF8010A4,0xBF8010A8,		02 gpu
//		0xBF8010B0,0xBF8010B4,0xBF8010B8,		03 cdrom/dvd
//		0xBF8010C0,0xBF8010C4,0xBF8010C8, 0xBF8010CC,	04 spu
//		0xBF8010D0,0xBF8010D4,0xBF8010D8,		05 pio
//		0xBF8010E0,0xBF8010E4,0xBF8010E8,		06 gpu otc
//
//		0xBF8010F0,0xBF8010F4,
//
//		0xBF801500,0xBF801504,0xBF801508,		07 SPU2
//		0xBF801510,0xBF801514,0xBF801518,		08
//		0xBF801520,0xBF801524,0xBF801528, 0xBF80152C,	09 SIF0
//		0xBF801530,0xBF801534,0xBF801538,		10 SIF1
//		0xBF801540,0xBF801544,0xBF801548,		11 SIO2in
//		0xBF801550,0xBF801554,0xBF801558,		12 SIO2out
//
//		0xBF801560,0xBF801564,0xBF801568,		   //sifman
//                    sif0	sif1	   spu
//
//		0xBF801570, 0xBF801574,0xBF801578,0xBF80157C,	   //sifman
//		0xBF8015F0
//[handlers]	-
//[entry point]	dmacman_start, dmacman_stub
//[made by]	[RO]man (roman_ps2dev@hotmail.com)

#include <tamtypes.h>

#include "dmacman.h"
#include "intrman.h"
#include "loadcore.h"
#include "sysmem.h"

#include "dmacman-internal.h"

///////////////////////////////////////////////////////////////////////
void dmac_ch_set_tadr(u32 channel, u32 value)
{
    switch (channel) {
        case DMAch_SPU:
            *((vu32 *)0xBF8010CC) = value;
            break;
        case DMAch_SIF0:
            *((vu32 *)0xBF80152C) = value;
            break;
        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////////
u32 dmac_ch_get_tadr(u32 channel)
{
    switch (channel) {
        case DMAch_SPU:
            return *((vu32 *)0xBF8010CC);
        case DMAch_SIF0:
            return *((vu32 *)0xBF80152C);
        default:
            return 0;
    }
}

///////////////////////////////////////////////////////////////////////
void dmac_set_4_9_a(u32 channel, u32 value)
{
    switch (channel) {
        case DMAch_SPU:
            *((vu32 *)0xBF801568) = value;
            break;
        case DMAch_SIF0:
            *((vu32 *)0xBF801560) = value;
            break;
        case DMAch_SIF1:
            *((vu32 *)0xBF801564) = value;
            break;
        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////////
u32 dmac_get_4_9_a(u32 channel)
{
    switch (channel) {
        case DMAch_SPU:
            return *((vu32 *)0xBF801568);
        case DMAch_SIF0:
            return *((vu32 *)0xBF801560);
        case DMAch_SIF1:
            return *((vu32 *)0xBF801564);
        default:
            return 0;
    }
}

///////////////////////////////////////////////////////////////////////
void dmac_set_dpcr(u32 value) { *((vu32 *)0xBF8010F0) = value; }

///////////////////////////////////////////////////////////////////////
u32 dmac_get_dpcr() { return *((vu32 *)0xBF8010F0); }

///////////////////////////////////////////////////////////////////////
void dmac_set_dpcr2(u32 value) { *((vu32 *)0xBF801570) = value; }

///////////////////////////////////////////////////////////////////////
u32 dmac_get_dpcr2() { return *((vu32 *)0xBF801570); }

///////////////////////////////////////////////////////////////////////
void dmac_set_dpcr3(u32 value) { *((vu32 *)0xBF8015F0) = value; }

///////////////////////////////////////////////////////////////////////
u32 dmac_get_dpcr3() { return *((vu32 *)0xBF8015F0); }

///////////////////////////////////////////////////////////////////////
void dmac_set_dicr(u32 value) { *((vu32 *)0xBF8010F4) = value; }

///////////////////////////////////////////////////////////////////////
u32 dmac_get_dicr() { return *((vu32 *)0xBF8010F4); }

///////////////////////////////////////////////////////////////////////
void dmac_set_dicr2(u32 value) { *((vu32 *)0xBF801574) = value; }

///////////////////////////////////////////////////////////////////////
u32 dmac_get_dicr2() { return *((vu32 *)0xBF801574); }

///////////////////////////////////////////////////////////////////////
void dmac_set_BF80157C(u32 value) { *((vu32 *)0xBF80157C) = value; }

///////////////////////////////////////////////////////////////////////
u32 dmac_get_BF80157C() { return *((vu32 *)0xBF80157C); }

///////////////////////////////////////////////////////////////////////
void dmac_set_BF801578(u32 value) { *((vu32 *)0xBF801578) = value; }

///////////////////////////////////////////////////////////////////////
u32 dmac_get_BF801578() { return *((vu32 *)0xBF801578); }

///////////////////////////////////////////////////////////////////////
void dmac_ch_set_madr(u32 channel, u32 val)
{
    switch (channel) {
        case DMAch_MDECin:
            *((vu32 *)0xBF801080) = val;
            break;
        case DMAch_MDECout:
            *((vu32 *)0xBF801090) = val;
            break;
        case DMAch_GPU:
            *((vu32 *)0xBF8010A0) = val;
            break;
        case DMAch_CD:
            *((vu32 *)0xBF8010B0) = val;
            break;
        case DMAch_SPU:
            *((vu32 *)0xBF8010C0) = val;
            break;
        case DMAch_PIO:
            *((vu32 *)0xBF8010D0) = val;
            break;
        case DMAch_GPUotc:
            *((vu32 *)0xBF8010E0) = val;
            break;
        case DMAch_SPU2:
            *((vu32 *)0xBF801500) = val;
            break;
        case DMAch_8:
            *((vu32 *)0xBF801510) = val;
            break;
        case DMAch_SIF0:
            *((vu32 *)0xBF801520) = val;
            break;
        case DMAch_SIF1:
            *((vu32 *)0xBF801530) = val;
            break;
        case DMAch_SIO2in:
            *((vu32 *)0xBF801540) = val;
            break;
        case DMAch_SIO2out:
            *((vu32 *)0xBF801550) = val;
            break;
        default:
            return;
    }
}

///////////////////////////////////////////////////////////////////////
u32 dmac_ch_get_madr(u32 channel)
{
    switch (channel) {
        case DMAch_MDECin:
            return *((vu32 *)0xBF801080);
        case DMAch_MDECout:
            return *((vu32 *)0xBF801090);
        case DMAch_GPU:
            return *((vu32 *)0xBF8010A0);
        case DMAch_CD:
            return *((vu32 *)0xBF8010B0);
        case DMAch_SPU:
            return *((vu32 *)0xBF8010C0);
        case DMAch_PIO:
            return *((vu32 *)0xBF8010D0);
        case DMAch_GPUotc:
            return *((vu32 *)0xBF8010E0);
        case DMAch_SPU2:
            return *((vu32 *)0xBF801500);
        case DMAch_8:
            return *((vu32 *)0xBF801510);
        case DMAch_SIF0:
            return *((vu32 *)0xBF801520);
        case DMAch_SIF1:
            return *((vu32 *)0xBF801530);
        case DMAch_SIO2in:
            return *((vu32 *)0xBF801540);
        case DMAch_SIO2out:
            return *((vu32 *)0xBF801550);
        default:
            return 0;
    }
}

///////////////////////////////////////////////////////////////////////
void dmac_ch_set_bcr(u32 channel, u32 val)
{
    switch (channel) {
        case DMAch_MDECin:
            *((vu32 *)0xBF801084) = val;
            break;
        case DMAch_MDECout:
            *((vu32 *)0xBF801094) = val;
            break;
        case DMAch_GPU:
            *((vu32 *)0xBF8010A4) = val;
            break;
        case DMAch_CD:
            *((vu32 *)0xBF8010B4) = val;
            break;
        case DMAch_SPU:
            *((vu32 *)0xBF8010C4) = val;
            break;
        case DMAch_PIO:
            *((vu32 *)0xBF8010D4) = val;
            break;
        case DMAch_GPUotc:
            *((vu32 *)0xBF8010E4) = val;
            break;
        case DMAch_SPU2:
            *((vu32 *)0xBF801504) = val;
            break;
        case DMAch_8:
            *((vu32 *)0xBF801514) = val;
            break;
        case DMAch_SIF0:
            *((vu32 *)0xBF801524) = val;
            break;
        case DMAch_SIF1:
            *((vu32 *)0xBF801534) = val;
            break;
        case DMAch_SIO2in:
            *((vu32 *)0xBF801544) = val;
            break;
        case DMAch_SIO2out:
            *((vu32 *)0xBF801554) = val;
            break;
        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////////
u32 dmac_ch_get_bcr(u32 channel)
{
    switch (channel) {
        case DMAch_MDECin:
            return *((vu32 *)0xBF801084);
        case DMAch_MDECout:
            return *((vu32 *)0xBF801094);
        case DMAch_GPU:
            return *((vu32 *)0xBF8010A4);
        case DMAch_CD:
            return *((vu32 *)0xBF8010B4);
        case DMAch_SPU:
            return *((vu32 *)0xBF8010C4);
        case DMAch_PIO:
            return *((vu32 *)0xBF8010D4);
        case DMAch_GPUotc:
            return *((vu32 *)0xBF8010E4);
        case DMAch_SPU2:
            return *((vu32 *)0xBF801504);
        case DMAch_8:
            return *((vu32 *)0xBF801514);
        case DMAch_SIF0:
            return *((vu32 *)0xBF801524);
        case DMAch_SIF1:
            return *((vu32 *)0xBF801534);
        case DMAch_SIO2in:
            return *((vu32 *)0xBF801544);
        case DMAch_SIO2out:
            return *((vu32 *)0xBF801554);
        default:
            return 0;
    }
}

///////////////////////////////////////////////////////////////////////
void dmac_ch_set_chcr(u32 channel, u32 val)
{
    switch (channel) {
        case DMAch_MDECin:
            *((vu32 *)0xBF801088) = val;
            break;
        case DMAch_MDECout:
            *((vu32 *)0xBF801098) = val;
            break;
        case DMAch_GPU:
            *((vu32 *)0xBF8010A8) = val;
            break;
        case DMAch_CD:
            *((vu32 *)0xBF8010B8) = val;
            break;
        case DMAch_SPU:
            *((vu32 *)0xBF8010C8) = val;
            break;
        case DMAch_PIO:
            *((vu32 *)0xBF8010D8) = val;
            break;
        case DMAch_GPUotc:
            *((vu32 *)0xBF8010E8) = val;
            break;
        case DMAch_SPU2:
            *((vu32 *)0xBF801508) = val;
            break;
        case DMAch_8:
            *((vu32 *)0xBF801518) = val;
            break;
        case DMAch_SIF0:
            *((vu32 *)0xBF801528) = val;
            break;
        case DMAch_SIF1:
            *((vu32 *)0xBF801538) = val;
            break;
        case DMAch_SIO2in:
            *((vu32 *)0xBF801548) = val;
            break;
        case DMAch_SIO2out:
            *((vu32 *)0xBF801558) = val;
            break;
        default:
            return;
    }
}

///////////////////////////////////////////////////////////////////////
u32 dmac_ch_get_chcr(u32 channel)
{
    switch (channel) {
        case DMAch_MDECin:
            return *((vu32 *)0xBF801088);
        case DMAch_MDECout:
            return *((vu32 *)0xBF801098);
        case DMAch_GPU:
            return *((vu32 *)0xBF8010A8);
        case DMAch_CD:
            return *((vu32 *)0xBF8010B8);
        case DMAch_SPU:
            return *((vu32 *)0xBF8010C8);
        case DMAch_PIO:
            return *((vu32 *)0xBF8010D8);
        case DMAch_GPUotc:
            return *((vu32 *)0xBF8010E8);
        case DMAch_SPU2:
            return *((vu32 *)0xBF801508);
        case DMAch_8:
            return *((vu32 *)0xBF801518);
        case DMAch_SIF0:
            return *((vu32 *)0xBF801528);
        case DMAch_SIF1:
            return *((vu32 *)0xBF801538);
        case DMAch_SIO2in:
            return *((vu32 *)0xBF801548);
        case DMAch_SIO2out:
            return *((vu32 *)0xBF801558);
        default:
            return 0;
    }
}

///////////////////////////////////////////////////////////////////////
int dmacDeinit()
{
    int x;
    register int channel, value;

    CpuSuspendIntr(&x); // intrman

    dmac_set_BF801578(0);
    for (channel = 0; channel < 13; channel++) {
        value = dmac_ch_get_chcr(channel);
        if (value & DMAf_TR) // sysmem
            Kprintf("WARNING:DMA %dch has been continued until shutdown\n", channel);
        dmac_ch_set_chcr(channel, value & 0xFEFFFFFF);
    }

    CpuResumeIntr(x); // intrman
    return 1;
}

///////////////////////////////////////////////////////////////////////
int dmac_request(u32 channel, void *address, u32 size, u32 count, int dir)
{
    if (channel < 13 && channel != DMAch_GPUotc) {
        dmac_ch_set_madr(channel, 0x00FFFFFF & (u32)address);
        dmac_ch_set_bcr(channel, (count << 16) | (size & 0xFFFF));
        dmac_ch_set_chcr(channel, (dir & DMAf_DR) | DMAf_CO | (dir == 0 ? DMAf_30 : 0));
        return 1;
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////
int dmac_set_dma_chained_spu_sif0(u32 channel, u32 size, u32 tadr)
{
    if (channel != DMAch_SPU && channel != DMAch_SIF0)
        return 0;
    dmac_ch_set_bcr(channel, size & 0x0000FFFF);
    dmac_ch_set_chcr(channel, DMAf_LI | DMAf_CO | DMAf_DR); // 0x601
    dmac_ch_set_tadr(channel, tadr & 0x00FFFFFF);
    return 1;
}

///////////////////////////////////////////////////////////////////////
int dmac_set_dma_sif0(u32 channel, u32 size, u32 tadr)
{
    if (channel != DMAch_SIF0)
        return 0;
    dmac_ch_set_bcr(DMAch_SIF0, size & 0x0000FFFF);
    dmac_ch_set_chcr(DMAch_SIF0, DMAf_LI | DMAf_CO | DMAf_08 | DMAf_DR); // 0x701
    dmac_ch_set_tadr(DMAch_SIF0, tadr & 0x00FFFFFF);
    return 1;
}

///////////////////////////////////////////////////////////////////////
int dmac_set_dma_sif1(u32 channel, u32 size)
{
    if (channel != DMAch_SIF1)
        return 0;
    dmac_ch_set_bcr(DMAch_SIF1, size & 0x0000FFFF);
    dmac_ch_set_chcr(DMAch_SIF1, DMAf_30 | DMAf_CO | DMAf_08); // 0x40000300
    return 1;
}

///////////////////////////////////////////////////////////////////////
void dmac_transfer(u32 channel)
{
    if (channel < 15)
        dmac_ch_set_chcr(channel, DMAf_TR | dmac_ch_get_chcr(channel));
}

///////////////////////////////////////////////////////////////////////
// set 3-bit value of channel
void dmac_ch_set_dpcr(u32 channel, u32 value)
{
    int x;
    CpuSuspendIntr(&x); // intrman

    switch (channel) {
        case DMAch_MDECin:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFFFFFF8) | (value & 7));
            break;
        case DMAch_MDECout:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFFFFF8F) | ((value & 7) << 4));
            break;
        case DMAch_GPU:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFFFF8FF) | ((value & 7) << 8));
            break;
        case DMAch_CD:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFFF8FFF) | ((value & 7) << 12));
            break;
        case DMAch_SPU:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFF8FFFF) | ((value & 7) << 16));
            break;
        case DMAch_PIO:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFF8FFFFF) | ((value & 7) << 20));
            break;
        case DMAch_GPUotc:
            dmac_set_dpcr((dmac_get_dpcr() & 0xF8FFFFFF) | ((value & 7) << 24));
            break;
        case DMAch_SPU2:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFFFFFF8) | (value & 7));
            break;
        case DMAch_8:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFFFFF8F) | ((value & 7) << 4));
            break;
        case DMAch_SIF0:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFFFF8FF) | ((value & 7) << 8));
            break;
        case DMAch_SIF1:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFFF8FFF) | ((value & 7) << 12));
            break;
        case DMAch_SIO2in:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFF8FFFF) | ((value & 7) << 16));
            break;
        case DMAch_SIO2out:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFF8FFFFF) | ((value & 7) << 20));
            break;
        case DMAch_13:
            dmac_set_dpcr3((dmac_get_dpcr3() & 0xFFFFFFF8) | (value & 7));
            break;
        case DMAch_14:
            dmac_set_dpcr3((dmac_get_dpcr3() & 0xFFFFFF8F) | ((value & 7) << 4));
            break;
        case DMAch_15:
            dmac_set_dpcr3((dmac_get_dpcr3() & 0xFFFFF8FF) | ((value & 7) << 8));
            break;
        case DMAch_67:
            dmac_set_dpcr((dmac_get_dpcr() & 0x8FFFFFFF) | ((value & 7) << 28));
            break;
        case DMAch_85:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xF8FFFFFF) | ((value & 7) << 24));
            break;
    }

    CpuResumeIntr(x); // intrman
}

///////////////////////////////////////////////////////////////////////
// set 4th bit of channel
void dmac_enable(u32 channel)
{
    int x;
    CpuSuspendIntr(&x); // intrman

    switch (channel) {
        case DMAch_MDECin:
            dmac_set_dpcr((dmac_get_dpcr() | 0x00000008));
            break;
        case DMAch_MDECout:
            dmac_set_dpcr((dmac_get_dpcr() | 0x00000080));
            break;
        case DMAch_GPU:
            dmac_set_dpcr((dmac_get_dpcr() | 0x00000800));
            break;
        case DMAch_CD:
            dmac_set_dpcr((dmac_get_dpcr() | 0x00008000));
            break;
        case DMAch_SPU:
            dmac_set_dpcr((dmac_get_dpcr() | 0x00080000));
            break;
        case DMAch_PIO:
            dmac_set_dpcr((dmac_get_dpcr() | 0x00800000));
            break;
        case DMAch_GPUotc:
            dmac_set_dpcr((dmac_get_dpcr() | 0x08000000));
            break;
        case DMAch_SPU2:
            dmac_set_dpcr2((dmac_get_dpcr2() | 0x00000008));
            break;
        case DMAch_8:
            dmac_set_dpcr2((dmac_get_dpcr2() | 0x00000080));
            break;
        case DMAch_SIF0:
            dmac_set_dpcr2((dmac_get_dpcr2() | 0x00000800));
            break;
        case DMAch_SIF1:
            dmac_set_dpcr2((dmac_get_dpcr2() | 0x00008000));
            break;
        case DMAch_SIO2in:
            dmac_set_dpcr2((dmac_get_dpcr2() | 0x00080000));
            break;
        case DMAch_SIO2out:
            dmac_set_dpcr2((dmac_get_dpcr2() | 0x00800000));
            break;
        case DMAch_13:
            dmac_set_dpcr3((dmac_get_dpcr3() | 0x00000008));
            break;
        case DMAch_14:
            dmac_set_dpcr3((dmac_get_dpcr3() | 0x00000080));
            break;
        case DMAch_15:
            dmac_set_dpcr3((dmac_get_dpcr3() | 0x00000800));
            break;
        case DMAch_85:
            dmac_set_dpcr2((dmac_get_dpcr2() | 0x08000000));
            break;
    }

    CpuResumeIntr(x); // intrman
}

///////////////////////////////////////////////////////////////////////
// reset 4th bit of channel
void dmac_disable(u32 channel)
{
    int x;
    CpuSuspendIntr(&x); // intrman

    switch (channel) {
        case DMAch_MDECin:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFFFFFF7));
            break;
        case DMAch_MDECout:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFFFFF7F));
            break;
        case DMAch_GPU:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFFFF7FF));
            break;
        case DMAch_CD:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFFF7FFF));
            break;
        case DMAch_SPU:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFFF7FFFF));
            break;
        case DMAch_PIO:
            dmac_set_dpcr((dmac_get_dpcr() & 0xFF7FFFFF));
            break;
        case DMAch_GPUotc:
            dmac_set_dpcr((dmac_get_dpcr() & 0xF7FFFFFF));
            break;
        case DMAch_SPU2:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFFFFFF7));
            break;
        case DMAch_8:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFFFFF7F));
            break;
        case DMAch_SIF0:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFFFF7FF));
            break;
        case DMAch_SIF1:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFFF7FFF));
            break;
        case DMAch_SIO2in:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFFF7FFFF));
            break;
        case DMAch_SIO2out:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xFF7FFFFF));
            break;
        case DMAch_13:
            dmac_set_dpcr3((dmac_get_dpcr3() & 0xFFFFFFF7));
            break;
        case DMAch_14:
            dmac_set_dpcr3((dmac_get_dpcr3() & 0xFFFFFF7F));
            break;
        case DMAch_15:
            dmac_set_dpcr3((dmac_get_dpcr3() & 0xFFFFF7FF));
            break;
        case DMAch_85:
            dmac_set_dpcr2((dmac_get_dpcr2() & 0xF7FFFFFF));
            break;
    }

    CpuResumeIntr(x); // intrman
}

#define MODNAME "dmacman"
IRX_ID(MODNAME, 1, 2);

extern struct irx_export_table _exp_dmacman;

//////////////////////////////entrypoint///////////////////////////////
int _start(int argc, char *argv[])
{
    int x;
    register int channel;

    if (RegisterLibraryEntries(&_exp_dmacman) != 0) {
        return 1;
    }

    CpuSuspendIntr(&x); // intrman

    dmac_set_dpcr(0x07777777);
    dmac_set_dpcr2(0x07777777);
    dmac_set_dpcr3(0x00000777);
    for (channel = 0; channel < 13; channel++) {
        dmac_ch_set_madr(channel, 0);
        dmac_ch_set_bcr(channel, 0);
        dmac_ch_set_chcr(channel, 0);
    }
    dmac_ch_set_tadr(DMAch_SPU, 0);
    dmac_ch_set_tadr(DMAch_SIF0, 0);
    dmac_set_4_9_a(DMAch_SPU, 0);
    dmac_set_4_9_a(DMAch_SIF0, 0);
    dmac_set_4_9_a(DMAch_SIF1, 0);
    dmac_set_BF801578(1);

    CpuResumeIntr(x); // intrman
    return 0;
}
