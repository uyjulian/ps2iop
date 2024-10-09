
#ifndef COMMON_DEFS_H_
#define COMMON_DEFS_H_

#if 1
#include <stdbool.h>
#endif

#if 1
#define __fastcall
#define __cdecl
#define __noreturn
#endif

#if 1
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

#define _BOOL4 unsigned int
#define BOOL unsigned int

#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long long
#endif

#define MEMORY ((volatile unsigned int *)0x10000000)

#if 1
#define LAST_IND(x, part_type) (sizeof(x) / sizeof(part_type) - 1)
#define HIGH_IND(x, part_type) LAST_IND(x, part_type)
#define LOW_IND(x, part_type) 0

#define BYTEn(x, n) (*((_BYTE*)&(x) + n))
#define WORDn(x, n) (*((_WORD*)&(x) + n))
#define DWORDn(x, n) (*((_DWORD*)&(x) + n))
#endif

#if 1
#ifdef LOBYTE
#undef LOBYTE
#endif
#define LOBYTE(x) BYTEn(x, LOW_IND(x, _BYTE))
#ifdef LOWORD
#undef LOWORD
#endif
#define LOWORD(x) WORDn(x, LOW_IND(x, _WORD))
#define LODWORD(x) DWORDn(x, LOW_IND(x, _DWORD))
#ifdef HIBYTE
#undef HIBYTE
#endif
#define HIBYTE(x) BYTEn(x, HIGH_IND(x, _BYTE))
#ifdef HIWORD
#undef HIWORD
#endif
#define HIWORD(x) WORDn(x, HIGH_IND(x, _WORD))
#define HIDWORD(x) DWORDn(x, HIGH_IND(x, _DWORD))
#define BYTE1(x) BYTEn(x, 1)
#define BYTE2(x) BYTEn(x, 2)
#define BYTE3(x) BYTEn(x, 3)
#define BYTE4(x) BYTEn(x, 4)
#define BYTE5(x) BYTEn(x, 5)
#define BYTE6(x) BYTEn(x, 6)
#define BYTE7(x) BYTEn(x, 7)
#define BYTE8(x) BYTEn(x, 8)
#define BYTE9(x) BYTEn(x, 9)
#define BYTE10(x) BYTEn(x, 10)
#define BYTE11(x) BYTEn(x, 11)
#define BYTE12(x) BYTEn(x, 12)
#define BYTE13(x) BYTEn(x, 13)
#define BYTE14(x) BYTEn(x, 14)
#define BYTE15(x) BYTEn(x, 15)
#define WORD1(x) WORDn(x, 1)
#define WORD2(x) WORDn(x, 2) // third word of the object, unsigned
#define WORD3(x) WORDn(x, 3)
#define WORD4(x) WORDn(x, 4)
#define WORD5(x) WORDn(x, 5)
#define WORD6(x) WORDn(x, 6)
#define WORD7(x) WORDn(x, 7)
#endif

#if 1
// now signed macros (the same but with sign extension)
#define SBYTEn(x, n) (*((int8_t*)&(x) + n))
#define SWORDn(x, n) (*((int16_t*)&(x) + n))
#define SDWORDn(x, n) (*((int32_t*)&(x) + n))

#define SLOBYTE(x) SBYTEn(x, LOW_IND(x, int8_t))
#define SLOWORD(x) SWORDn(x, LOW_IND(x, int16_t))
#define SLODWORD(x) SDWORDn(x, LOW_IND(x, int32_t))
#define SHIBYTE(x) SBYTEn(x, HIGH_IND(x, int8_t))
#define SHIWORD(x) SWORDn(x, HIGH_IND(x, int16_t))
#define SHIDWORD(x) SDWORDn(x, HIGH_IND(x, int32_t))
#define SBYTE1(x) SBYTEn(x, 1)
#define SBYTE2(x) SBYTEn(x, 2)
#define SBYTE3(x) SBYTEn(x, 3)
#define SBYTE4(x) SBYTEn(x, 4)
#define SBYTE5(x) SBYTEn(x, 5)
#define SBYTE6(x) SBYTEn(x, 6)
#define SBYTE7(x) SBYTEn(x, 7)
#define SBYTE8(x) SBYTEn(x, 8)
#define SBYTE9(x) SBYTEn(x, 9)
#define SBYTE10(x) SBYTEn(x, 10)
#define SBYTE11(x) SBYTEn(x, 11)
#define SBYTE12(x) SBYTEn(x, 12)
#define SBYTE13(x) SBYTEn(x, 13)
#define SBYTE14(x) SBYTEn(x, 14)
#define SBYTE15(x) SBYTEn(x, 15)
#define SWORD1(x) SWORDn(x, 1)
#define SWORD2(x) SWORDn(x, 2)
#define SWORD3(x) SWORDn(x, 3)
#define SWORD4(x) SWORDn(x, 4)
#define SWORD5(x) SWORDn(x, 5)
#define SWORD6(x) SWORDn(x, 6)
#define SWORD7(x) SWORDn(x, 7)
#endif

#if 1
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned long u_long;
#endif

#if 1
#define _break(...) __builtin_trap()
#endif

#if 1
#include <cdvdman.h>
typedef struct _dev5_regs
{
	vu8 dev5_reg_000;
	vu8 dev5_reg_001;
	vu8 dev5_reg_002;
	vu8 dev5_reg_003;
	vu8 dev5_reg_004;
	vu8 dev5_reg_005;
	vu8 dev5_reg_006;
	vu8 dev5_reg_007;
	vu8 dev5_reg_008;
	vu8 dev5_reg_009;
	vu8 dev5_reg_00A;
	vu8 dev5_reg_00B;
	vu8 dev5_reg_00C;
	vu8 dev5_reg_00D;
	vu8 dev5_reg_00E;
	vu8 dev5_reg_00F;
	vu8 dev5_reg_010;
	vu8 dev5_reg_011;
	vu8 dev5_reg_012;
	vu8 dev5_reg_013;
	vu8 dev5_reg_014;
	vu8 dev5_reg_015;
	vu8 dev5_reg_016;
	vu8 dev5_reg_017;
	vu8 dev5_reg_018;
	vu8 dev5_reg_019;
	vu8 dev5_reg_01A;
	vu8 dev5_reg_01B;
	vu8 dev5_reg_01C;
	vu8 dev5_reg_01D;
	vu8 dev5_reg_01E;
	vu8 dev5_reg_01F;
	vu8 dev5_reg_020;
	vu8 dev5_reg_021;
	vu8 dev5_reg_022;
	vu8 dev5_reg_023;
	vu8 dev5_reg_024;
	vu8 dev5_reg_025;
	vu8 dev5_reg_026;
	vu8 dev5_reg_027;
	vu8 dev5_reg_028;
	vu8 dev5_reg_029;
	vu8 dev5_reg_02A;
	vu8 dev5_reg_02B;
	vu8 dev5_reg_02C;
	vu8 dev5_reg_02D;
	vu8 dev5_reg_02E;
	vu8 dev5_reg_02F;
	vu8 dev5_reg_030;
	vu8 dev5_reg_031;
	vu8 dev5_reg_032;
	vu8 dev5_reg_033;
	vu8 dev5_reg_034;
	vu8 dev5_reg_035;
	vu8 dev5_reg_036;
	vu8 dev5_reg_037;
	vu8 dev5_reg_038;
	vu8 dev5_reg_039;
	vu8 dev5_reg_03A;
} dev5_regs_t;

typedef struct cdrom_stm_devctl_
{
	u32 posszarg1;
	u32 posszarg2;
	void *buffer;
	u32 cmdid;
	sceCdRMode rmode;
	u32 error;
} cdrom_stm_devctl_t;

typedef struct _CD_DIR_ENTRY
{
	int number;
	int parent;
	int extent;
	char name[32];
} CD_DIR_ENTRY;

typedef struct _CDVDMAN_FILEDATA
{
	u32 file_lsn;
	u32 read_pos;
	u32 file_size;
	u32 filemode;
	int fd_flags;
	int fd_layer;
	int cache_file_fd;
	u8 *fd_rcvbuf;
	u32 fd_rbsize;
	void *max_cluster;
	int sector_count_total;
	int cluster_cur;
} CDVDMAN_FILEDATA;


typedef struct _DMA3PARAM
{
	u16 dma3_blkwords;
	u16 dma3_blkcount;
	void *dma3_maddress;
	int (__cdecl *dma3_callback)(void);
	u16 dma3_csectors;
	u16 cdvdreg_howto;
	u32 dma3_msectors;
} DMA3PARAM;

typedef struct CDVDMAN_PATHTBL_
{
	int cache_path_sz;
	int lsn;
	unsigned int nsec;
	int layer;
	unsigned int cache_hit_count;
} CDVDMAN_PATHTBL_T;

typedef struct CDVDMAN_FILETBL_ENTRY_
{
	sceCdlFILE file_struct;
	int file_properties;
} CDVDMAN_FILETBL_ENTRY_T;

struct __attribute__((packed)) dirTocEntry
{
	__int16 length;
	u32 fileLBA;
	u32 fileLBA_bigend;
	u32 fileSize;
	u32 fileSize_bigend;
	u8 dateStamp[6];
	u8 reserved1;
	u8 fileProperties;
	u8 reserved2[6];
	u8 filenameLength;
	char filename[128];
};


typedef struct cdvdman_internal_struct_
{
	char cdvdman_command;
	char last_error;
	char field_002[2];
	int wait_flag;
	int thread_id;
	int stream_flag;
	int read2_flag;
	int cdvdman_lsn;
	int cdvdman_rbuffer;
	int cdvdman_nsec;
	int cdvdman_csec;
	int cdvdman_rsec;
	int cdvdman_pattern;
	sceCdRMode cdvdman_cdrmode;
	int recover_status;
	int dvd_flag;
	int read_lsn;
	void *read_buf;
	int read_sectors;
	sceCdRMode read_mode;
	int read_chunk_reprocial_32;
	int dintrlsn;
	void *read_callback;
	int read_chunk;
	char scmd_flag;
	char scmd;
	char sdlen;
	char rdlen;
	char scmd_sd[16];
	char scmd_rd[16];
	int sync_error;
	int read_to;
	int power_flag;
	u32 layer_1_lsn;
	char use_toc;
	char opo_or_para;
	char current_dvd;
	char dual_layer_emulation;
	u32 current_dvd_lsn;
	int check_version;
	int dec_shift;
	int dec_state;
	int no_dec_flag;
	DMA3PARAM dma3prm;
	int cdvdman_dma3sec;
	int drive_interupt_request;
	unsigned __int16 dec_mode_set;
	__int16 dec_mode_last_set;
	int waf_set_test;
	int interupt_read_state;
	int cd_inited;
	int tray_is_open;
	int m_break_cdvdfsv_readchain;
	int field_0D8;
	int field_0DC;
	int var_sc_ffffffdb;
	int field_0E4;
	int var_sc_ffffffd9;
	int field_0EC;
	int pad[4];
} cdvdman_internal_struct_t;
#endif

#if 1
typedef struct _nonblock_io_data CDVDReadResult;
typedef struct _init_io_data
{
	int result;
	int cdvdfsv_ver;
	int cdvdman_ver;
	int debug_mode;
} CDVDInitResult;
typedef struct _eeread_extra
{
	unsigned int b1len;
	unsigned int b2len;
	unsigned int b1dst;
	unsigned int b2dst;
	unsigned __int8 pbuf1[64];
	unsigned __int8 pbuf2[64];
} CDVDReadExtra;
typedef struct _block_io_data CDVDCmdResult;
typedef struct _fs_search_data
{
	int result;
	int padding[3];
} CDVDSearchResult;


typedef struct cdvdfsv_rpc5h_01_packet_
{
	int lsn;
	_DWORD sec;
	_DWORD flag;
	sceCdRMode rmodeee;
} cdvdfsv_rpc5h_01_packet;

typedef struct cdvdfsv_rpc5h_0D_packet_
{
	_DWORD lsn;
	_DWORD sectors;
	void *buf;
	sceCdRMode mode;
	_BYTE gap10[4];
	_DWORD readpos_dest_addr;
} cdvdfsv_rpc5h_0D_packet;

typedef struct cdvdfsv_rpc5h_0F_packet_
{
	sceCdRChain readChain[65];
	sceCdRMode scecdrmode30C;
	_DWORD readPos;
} cdvdfsv_rpc5h_0F_packet;

typedef struct cdvdfsc_rpc5h_03_packet_
{
	_DWORD lbn;
	_DWORD nsectors;
	_DWORD buf;
	sceCdRMode scecdrmodeC;
	_DWORD eedest;
} cdvdfsc_rpc5h_03_packet;

typedef struct cdvdfsv_rpc5h_02_packet_
{
	_DWORD lbn;
	_DWORD nsectors;
	_DWORD buf;
	sceCdRMode scecdrmodeC;
	_DWORD eeremaindest;
	_DWORD eedest;
} cdvdfsv_rpc5h_02_packet;

typedef struct cdvdfsv_rpc3h_22_packet_
{
	_DWORD media;
	char char4;
} cdvdfsv_rpc3h_22_packet;

typedef struct cdvdfsv_rpc3h_28_packet_
{
	const sceCdCLOCK clock;
	_WORD arg2;
	_DWORD arg3;
} cdvdfsv_rpc3h_28_packet;

typedef struct cdvdfsv_rpc3h_08_packet_
{
	_DWORD address;
	u16 data;
	u8 result;
} cdvdfsv_rpc3h_08_packet;

typedef struct cdvdfsv_rpc3h_09_packet_
{
	_DWORD address;
	_WORD data;
	u8 result;
} cdvdfsv_rpc3h_09_packet;

typedef struct cdvdfsv_rpc3h_2E_packet_
{
	_DWORD arg1;
	_DWORD arg2;
} cdvdfsv_rpc3h_2E_packet;

typedef struct cdvdfsv_rpc3h_3C_packet_
{
	_DWORD arg1;
	_DWORD arg2;
} cdvdfsv_rpc3h_3C_packet;

typedef struct cdvdfsv_rpc5h_0B_packet_
{
	_DWORD arg1;
	_DWORD arg2;
	_DWORD command;
} cdvdfsv_rpc5h_0B_packet;

typedef struct cdvdfsv_rpc3h_0A_packet_
{
	_BYTE arg1;
	_BYTE arg2;
	_BYTE shift;
} cdvdfsv_rpc3h_0A_packet;

typedef struct cdvdfsv_rpc3h_0B_packet_
{
	_BYTE cmdNum;
	_BYTE gap1;
	_WORD inBuffSize;
	char inBuff;
} cdvdfsv_rpc3h_0B_packet;

typedef struct cdvdfsv_rpc5h_0C_packet_
{
	_BYTE cmdNum;
	_BYTE gap1;
	_WORD inBuffSize;
	char inBuff;
} cdvdfsv_rpc5h_0C_packet;

typedef struct cdvdfsv_rpc3h_25_packet_
{
	_DWORD param;
	_DWORD timeout;
} cdvdfsv_rpc3h_25_packet;

typedef struct cdvdfsv_rpc5h_04_outpacket_
{
	_DWORD dword0;
	_DWORD dword4;
} cdvdfsv_rpc5h_04_outpacket;

typedef struct cdvdfsv_rpc3h_06_outpacket_
{
	_DWORD dword0;
	u32 result;
	u8 buffer;
} cdvdfsv_rpc3h_06_outpacket;

typedef struct cdvdfsv_rpc3h_1A_outpacket_
{
	_DWORD dword0;
	u32 status;
	char buffer;
} cdvdfsv_rpc3h_1A_outpacket;

typedef struct cdvdfsv_rpc3h_24_outpacket_
{
	_DWORD dword0;
	u64 guid;
} cdvdfsv_rpc3h_24_outpacket;

typedef struct cdvdfsv_rpc3h_26_outpacket_
{
	_DWORD dword0;
	unsigned int id;
} cdvdfsv_rpc3h_26_outpacket;

typedef struct cdvdfsv_rpc3h_12_outpacket_
{
	_DWORD dword0;
	u32 result;
	u8 buffer;
} cdvdfsv_rpc3h_12_outpacket;

typedef struct cdvdfsv_rpc3h_14_outpacket_
{
	_DWORD dword0;
	u32 status;
	u8 buffer;
} cdvdfsv_rpc3h_14_outpacket;

typedef struct cdvdfsv_rpc3h_17_outpacket_
{
	_DWORD dword0;
	u32 status;
	char buffer;
} cdvdfsv_rpc3h_17_outpacket;

typedef struct cdvdfsv_rpc3h_18_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_18_outpacket;

typedef struct cdvdfsv_rpc3h_1C_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_1C_outpacket;

typedef struct cdvdfsv_rpc3h_1F_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_1F_outpacket;

typedef struct cdvdfsv_rpc3h_21_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_21_outpacket;

typedef struct cdvdfsv_rpc3h_20_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_20_outpacket;

typedef struct cdvdfsv_rpc3h_15_outpacket_
{
	_DWORD dword0;
	u32 status;
} cdvdfsv_rpc3h_15_outpacket;

typedef struct cdvdfsv_rpc3h_19_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_19_outpacket;

typedef struct cdvdfsv_rpc3h_29_inneroutpacket_
{
	sceCdCLOCK clock;
	u16 arg2;
	int arg4;
	u32 arg3;
} cdvdfsv_rpc3h_29_inneroutpacket;

typedef struct cdvdfsv_rpc3h_29_outpacket_
{
	_DWORD dword0;
	cdvdfsv_rpc3h_29_inneroutpacket cdvdfsv_rpc3h_29_inneroutpacket4;
} cdvdfsv_rpc3h_29_outpacket;

typedef struct cdvdfsv_rpc3h_28_outpacket_
{
	_DWORD dword0;
	_DWORD dword4;
	_DWORD dword8;
} cdvdfsv_rpc3h_28_outpacket;

typedef struct cdvdfsv_rpc3h_30_outpacket_
{
	_DWORD dword0;
	u32 status;
} cdvdfsv_rpc3h_30_outpacket;

typedef struct cdvdfsv_rpc3h_32_outpacket_
{
	_DWORD dword0;
	u32 arg4;
	u32 arg1;
	u32 arg2;
	u32 arg3;
} cdvdfsv_rpc3h_32_outpacket;

typedef struct cdvdfsv_rpc3h_31_outpacket_
{
	_DWORD dword0;
	u32 arg2;
} cdvdfsv_rpc3h_31_outpacket;

typedef struct cdvdfsv_rpc3h_38_outpacket_
{
	_DWORD dword0;
	u32 arg2;
	u32 arg1;
} cdvdfsv_rpc3h_38_outpacket;

typedef struct cdvdfsv_rpc3h_2A_outpacket_
{
	_DWORD dword0;
	u32 result;
	u8 out;
} cdvdfsv_rpc3h_2A_outpacket;

typedef struct cdvdfsv_rpc3h_2B_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_2B_outpacket;

typedef struct cdvdfsv_rpc3h_2C_outpacket_
{
	_DWORD dword0;
	u32 arg2;
	u32 arg1;
} cdvdfsv_rpc3h_2C_outpacket;

typedef struct cdvdfsv_rpc3h_43_outpacket_
{
	_DWORD dword0;
	u32 result;
	u32 arg1;
} cdvdfsv_rpc3h_43_outpacket;

typedef struct cdvdfsv_rpc3h_2F_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_2F_outpacket;

typedef struct cdvdfsv_rpc3h_35_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_35_outpacket;

typedef struct cdvdfsv_rpc3h_01_outpacke_
{
	_DWORD dword0;
	sceCdCLOCK clock;
} cdvdfsv_rpc3h_01_outpacke;

typedef struct cdvdfsv_rpc3h_02_outpacket_
{
	_DWORD dword0;
	_DWORD dword4;
	_DWORD dword8;
} cdvdfsv_rpc3h_02_outpacket;

typedef struct cdvdfsv_rpc3h_08_outpacket_
{
	_DWORD dword0;
	_DWORD dword4;
	_DWORD dword8;
} cdvdfsv_rpc3h_08_outpacket;

typedef struct cdvdfsv_rpc3h_09_outpacket_
{
	_DWORD dword0;
	_DWORD dword4;
	_DWORD dword8;
} cdvdfsv_rpc3h_09_outpacket;

typedef struct cdvdfsv_rpc3h_2E_outpacket_
{
	_DWORD dword0;
	u32 result2;
	u32 result1;
} cdvdfsv_rpc3h_2E_outpacket;

typedef struct cdvdfsv_rpc3h_39_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_39_outpacket;

typedef struct cdvdfsv_rpc3h_3A_outpacket_
{
	_DWORD dword0;
	_DWORD arg2;
} cdvdfsv_rpc3h_3A_outpacket;

typedef struct cdvdfsv_rpc3h_3B_outpacket_
{
	_DWORD dword0;
	_DWORD arg2;
	_DWORD arg1;
} cdvdfsv_rpc3h_3B_outpacket;

typedef struct cdvdfsv_rpc3h_3C_outpacket_
{
	_DWORD dword0;
	u32 result2;
	u32 result1;
} cdvdfsv_rpc3h_3C_outpacket;

typedef struct cdvdfsv_rpc3h_3D_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_3D_outpacket;

typedef struct cdvdfsv_rpc3h_3E_outpacket_
{
	_DWORD dword0;
	u32 result2;
	u32 result1;
} cdvdfsv_rpc3h_3E_outpacket;

typedef struct cdvdfsv_rpc3h_3F_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_3F_outpacket;

typedef struct cdvdfsv_rpc3h_0F_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_0F_outpacket;

typedef struct cdvdfsv_rpc3h_10_outpacket_
{
	_DWORD dword0;
	u32 result;
	char buffer;
} cdvdfsv_rpc3h_10_outpacket;

typedef struct cdvdfsv_rpc3h_11_outpacket_
{
	_DWORD dword0;
	u32 result;
} cdvdfsv_rpc3h_11_outpacket;

typedef struct cdvdfsv_rpc5h_11_outpacket_
{
	_DWORD dword0;
	_DWORD dword4;
	_WORD word8;
} cdvdfsv_rpc5h_11_outpacket;

typedef struct cdvdfsv_rpc5h_17_outpacket_
{
	_DWORD dword0;
	u32 arg1;
} cdvdfsv_rpc5h_17_outpacket;

typedef struct cdvdfsv_rpc5h_0B_outpacket_
{
	_DWORD dword0;
	_DWORD dword4;
	_DWORD dword8;
	_DWORD dwordC;
	_DWORD dword10;
} cdvdfsv_rpc5h_0B_outpacket;

typedef struct cdvdfsv_rpc3h_0B_outpacket_
{
	_DWORD dword0;
	_DWORD dword4;
	_DWORD dword8;
	_DWORD dwordC;
} cdvdfsv_rpc3h_0B_outpacket;

typedef struct cdvdfsv_rpc3h_05_outpacket_
{
	_DWORD dword0;
	u32 traychk;
} cdvdfsv_rpc3h_05_outpacket;

typedef struct cdvdfsv_rpc3h_27_outpacket_
{
	_DWORD dword0;
	int on_dual;
	unsigned int layer1_start;
} cdvdfsv_rpc3h_27_outpacket;
#endif

#endif
