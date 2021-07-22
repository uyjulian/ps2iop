#ifndef __DMACMAN_INTERNAL_H__
#define __DMACMAN_INTERNAL_H__

#define DMACMAN_VER 0x101

//////////////////////////////  D_CHCR - DMA Channel Control Register
#define DMAf_30 0x40000000 // unknown; set on 'to' direction
#define DMAf_TR 0x01000000 // DMA transfer
#define DMAf_LI 0x00000400 // Linked list GPU; also SPU & SIF0
#define DMAf_CO 0x00000200 // Continuous stream
#define DMAf_08 0x00000100 // unknown
#define DMAf_DR 0x00000001 // Direction to=0/from=1
// clang-format off
//  31           24 23           16 15            8 7             0
// ╓─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╖
// ║ │?│ │ │ │ │ │T║ │ │ │ │ │ │ │ ║ │ │ │ │ │L│C│?║ │ │ │ │ │ │ │D║
// ║ │?│ │ │ │ │ │R║ │ │ │ │ │ │ │ ║ │ │ │ │ │I│O│?║ │ │ │ │ │ │ │R║
// ╙─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╜
//   30          24                          10 9 8               0

//////////////////////////////  DPCR - DMA Primary Control Register
// ╓─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╖
// ║   67  │ DMA 6 ║ DMA 5 │ DMA 4 ║ DMA 3 │ DMA 2 ║ DMA 1 │ DMA 0 ║ 0xBF8010F0 DPCR
// ╙─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╜
// ╓─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╖
// ║       │ DMA85 ║ DMA12 │ DMA11 ║ DMA10 │ DMA 9 ║ DMA 8 │ DMA 7 ║ 0xBF801570 DPCR_
// ╙─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╜
// ╓─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╥─┬─┬─┬─┬─┬─┬─┬─╖
// ║       │       ║       │       ║       │ DMA15 ║ DMA14 │ DMA13 ║ 0xBF8015F0 DPCR__
// ╙─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╨─┴─┴─┴─┴─┴─┴─┴─╜
// clang-format on

////////// DPCR
#define DMAch_MDECin  0
#define DMAch_MDECout 1
#define DMAch_GPU     2 // SIF2 both directions
#define DMAch_CD      3
#define DMAch_SPU     4
#define DMAch_PIO     5
#define DMAch_GPUotc  6

#define DMAch_67 67 // strange

////////// DPCR_
#define DMAch_SPU2    7
#define DMAch_8       8
#define DMAch_SIF0    9  // SIFout IOP->EE
#define DMAch_SIF1    10 // SIFin  EE->IOP
#define DMAch_SIO2in  11
#define DMAch_SIO2out 12

#define DMAch_85 85 // stange, very strange

////////// DPCR__
#define DMAch_13 13
#define DMAch_14 14
#define DMAch_15 15

// SIF2 DMA ch 2 (GPU)
#define DMAch_SIF2_MADR      (*(vu32 *)0xBF8010A0)
#define DMAch_SIF2_BCR       (*(vu32 *)0xBF8010A4)
#define DMAch_SIF2_BCR_size  (*(vu16 *)0xBF8010A4)
#define DMAch_SIF2_BCR_count (*(vu16 *)0xBF8010A6)
#define DMAch_SIF2_CHCR      (*(vu32 *)0xBF8010A8)
// SIF0 DMA ch 9
#define DMAch_SIF9_MADR      (*(vu32 *)0xBF801520)
#define DMAch_SIF9_BCR       (*(vu32 *)0xBF801524)
#define DMAch_SIF9_BCR_size  (*(vu16 *)0xBF801524)
#define DMAch_SIF9_BCR_count (*(vu16 *)0xBF801526)
#define DMAch_SIF9_CHCR      (*(vu32 *)0xBF801528)
#define DMAch_SIF9_TADR      (*(vu32 *)0xBF80152C)
// SIF1 DMA ch 10 (0xA)
#define DMAch_SIFA_MADR      (*(vu32 *)0xBF801530)
#define DMAch_SIFA_BCR       (*(vu32 *)0xBF801534)
#define DMAch_SIFA_BCR_size  (*(vu16 *)0xBF801534)
#define DMAch_SIFA_BCR_count (*(vu16 *)0xBF801536)
#define DMAch_SIFA_CHCR      (*(vu32 *)0xBF801538)

#define DMAch_DPCR  (*(vu32 *)0xBF8010F0)
#define DMAch_DPCR2 (*(vu32 *)0xBF801570)

#endif //__DMACMAN_INTERNAL_H__
