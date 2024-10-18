
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
	vu8 m_dev5_reg_000;
	vu8 m_dev5_reg_001;
	vu8 m_dev5_reg_002;
	vu8 m_dev5_reg_003;
	vu8 m_dev5_reg_004;
	vu8 m_dev5_reg_005;
	vu8 m_dev5_reg_006;
	vu8 m_dev5_reg_007;
	vu8 m_dev5_reg_008;
	vu8 m_dev5_reg_009;
	vu8 m_dev5_reg_00A;
	vu8 m_dev5_reg_00B;
	vu8 m_dev5_reg_00C;
	vu8 m_dev5_reg_00D;
	vu8 m_dev5_reg_00E;
	vu8 m_dev5_reg_00F;
	vu8 m_dev5_reg_010;
	vu8 m_dev5_reg_011;
	vu8 m_dev5_reg_012;
	vu8 m_dev5_reg_013;
	vu8 m_dev5_reg_014;
	vu8 m_dev5_reg_015;
	vu8 m_dev5_reg_016;
	vu8 m_dev5_reg_017;
	vu8 m_dev5_reg_018;
	vu8 m_dev5_reg_019;
	vu8 m_dev5_reg_01A;
	vu8 m_dev5_reg_01B;
	vu8 m_dev5_reg_01C;
	vu8 m_dev5_reg_01D;
	vu8 m_dev5_reg_01E;
	vu8 m_dev5_reg_01F;
	vu8 m_dev5_reg_020;
	vu8 m_dev5_reg_021;
	vu8 m_dev5_reg_022;
	vu8 m_dev5_reg_023;
	vu8 m_dev5_reg_024;
	vu8 m_dev5_reg_025;
	vu8 m_dev5_reg_026;
	vu8 m_dev5_reg_027;
	vu8 m_dev5_reg_028;
	vu8 m_dev5_reg_029;
	vu8 m_dev5_reg_02A;
	vu8 m_dev5_reg_02B;
	vu8 m_dev5_reg_02C;
	vu8 m_dev5_reg_02D;
	vu8 m_dev5_reg_02E;
	vu8 m_dev5_reg_02F;
	vu8 m_dev5_reg_030;
	vu8 m_dev5_reg_031;
	vu8 m_dev5_reg_032;
	vu8 m_dev5_reg_033;
	vu8 m_dev5_reg_034;
	vu8 m_dev5_reg_035;
	vu8 m_dev5_reg_036;
	vu8 m_dev5_reg_037;
	vu8 m_dev5_reg_038;
	vu8 m_dev5_reg_039;
	vu8 m_dev5_reg_03A;
} dev5_regs_t;

typedef struct cdrom_stm_devctl_
{
	u32 m_posszarg1;
	u32 m_posszarg2;
	void *m_buffer;
	u32 m_cmdid;
	sceCdRMode m_rmode;
	u32 m_error;
} cdrom_stm_devctl_t;

typedef struct _CD_DIR_ENTRY
{
	int m_number;
	int m_parent;
	int m_extent;
	char m_name[32];
} CD_DIR_ENTRY;

typedef struct _CDVDMAN_FILEDATA
{
	u32 m_file_lsn;
	u32 m_read_pos;
	u32 m_file_size;
	u32 m_filemode;
	int m_fd_flags;
	int m_fd_layer;
	int m_cache_file_fd;
	u8 *m_fd_rcvbuf;
	u32 m_fd_rbsize;
	void *m_max_cluster;
	int m_sector_count_total;
	int m_cluster_cur;
} CDVDMAN_FILEDATA;


typedef struct _DMA3PARAM
{
	u16 m_dma3_blkwords;
	u16 m_dma3_blkcount;
	void *m_dma3_maddress;
	int (__cdecl *m_dma3_callback)(void);
	u16 m_dma3_csectors;
	u16 m_cdvdreg_howto;
	u32 m_dma3_msectors;
} DMA3PARAM;

typedef struct CDVDMAN_PATHTBL_
{
	int m_cache_path_sz;
	int m_lsn;
	unsigned int m_nsec;
	int m_layer;
	unsigned int m_cache_hit_count;
} CDVDMAN_PATHTBL_T;

typedef struct CDVDMAN_FILETBL_ENTRY_
{
	sceCdlFILE m_file_struct;
	int m_file_properties;
} CDVDMAN_FILETBL_ENTRY_T;

struct __attribute__((packed)) dirTocEntry
{
	__int16 m_length;
	u32 m_fileLBA;
	u32 m_fileLBA_bigend;
	u32 m_fileSize;
	u32 m_fileSize_bigend;
	u8 m_dateStamp[6];
	u8 m_reserved1;
	u8 m_fileProperties;
	u8 m_reserved2[6];
	u8 m_filenameLength;
	char m_filename[128];
};


typedef struct cdvdman_internal_struct_
{
	char m_cdvdman_command;
	char m_last_error;
	char m_unused_002;
	char m_ncmd_intr_count;
	int m_wait_flag;
	int m_thread_id;
	int m_stream_flag;
	int m_read2_flag;
	int m_cdvdman_lsn;
	int m_cdvdman_rbuffer;
	int m_cdvdman_nsec;
	int m_cdvdman_csec;
	int m_cdvdman_rsec;
	int m_cdvdman_pattern;
	sceCdRMode m_cdvdman_cdrmode;
	int m_recover_status;
	int m_dvd_flag;
	int m_read_lsn;
	void *m_read_buf;
	int m_read_sectors;
	sceCdRMode m_read_mode;
	int m_read_chunk_reprocial_32;
	int m_dintrlsn;
	void *m_read_callback;
	int m_read_chunk;
	char m_scmd_flag;
	char m_scmd;
	char m_sdlen;
	char m_rdlen;
	char m_scmd_sd[16];
	char m_scmd_rd[16];
	int m_sync_error;
	int m_read_to;
	int m_power_flag;
	u32 m_layer_1_lsn;
	char m_use_toc;
	char m_opo_or_para;
	char m_current_dvd;
	char m_dual_layer_emulation;
	u32 m_current_dvd_lsn;
	int m_check_version;
	int m_dec_shift;
	int m_dec_state;
	int m_no_dec_flag;
	DMA3PARAM m_dma3prm;
	int m_cdvdman_dma3sec;
	int m_drive_interupt_request;
	unsigned __int16 m_dec_mode_set;
	__int16 m_dec_mode_last_set;
	int m_waf_set_test;
	int m_interupt_read_state;
	int m_cd_inited;
	int m_tray_is_open;
	int m_break_cdvdfsv_readchain;
	int m_unused[10];
} cdvdman_internal_struct_t;
#endif

#if 1
typedef struct cdvdfsv_rpc1h_packet_
{
	int m_mode;
} cdvdfsv_rpc1h_packet;
typedef struct cdvdfsv_rpc1h_outpacket_
{
	int m_retres;
	int m_cdvdfsv_ver;
	int m_cdvdman_ver;
	int m_debug_mode;
} cdvdfsv_rpc1h_outpacket;
typedef struct cdvdfsv_rpc2h_packet_
{
	int m_mode;
} cdvdfsv_rpc2h_packet;
typedef struct cdvdfsv_rpc2h_outpacket_
{
	int m_retres;
} cdvdfsv_rpc2h_outpacket;
typedef struct cdvdfsv_unaligned_data_outpacket_
{
	u32 m_b1len;
	u32 m_b2len;
	u32 m_b1dst;
	u32 m_b2dst;
	u8 m_pbuf1[64];
	u8 m_pbuf2[64];
} cdvdfsv_unaligned_data_outpacket;

typedef struct cdvdfsv_rpc4h_sz12c_packet_
{
	sceCdlFILE m_fp;
	int m_file_attributes;
	char m_path[256];
	uiptr m_eedest;
	int m_layer;
} cdvdfsv_rpc4h_sz12c_packet;

typedef struct cdvdfsv_rpc4h_sz128_packet_
{
	sceCdlFILE m_fp;
	int m_file_attributes;
	char m_path[256];
	uiptr m_eedest;
} cdvdfsv_rpc4h_sz128_packet;

typedef struct cdvdfsv_rpc4h_sz124_packet_
{
	sceCdlFILE m_fp;
	char m_path[256];
	uiptr m_eedest;
} cdvdfsv_rpc4h_sz124_packet;

typedef union cdvdfsv_rpc4h_packet_
{
	cdvdfsv_rpc4h_sz12c_packet m_pkt_sz12c;
	cdvdfsv_rpc4h_sz128_packet m_pkt_sz128;
	cdvdfsv_rpc4h_sz124_packet m_pkt_sz124;
} cdvdfsv_rpc4h_packet;

typedef struct cdvdfsv_rpc4h_outpacket_
{
	int m_retres;
	int m_padding[3];
} cdvdfsv_rpc4h_outpacket;


typedef struct cdvdfsv_rpc5h_01_packet_
{
	u32 m_lbn;
	u32 m_sectors;
	uiptr m_paddr;
	sceCdRMode m_rmodeee;
	uiptr m_eeremaindest;
	uiptr m_eedest;
	u32 m_decval;
} cdvdfsv_rpc5h_01_packet;

typedef struct cdvdfsv_rpc5h_04_packet_
{
	uiptr m_eedest;
} cdvdfsv_rpc5h_04_packet;

typedef struct cdvdfsv_rpc5h_05_packet_
{
	u32 m_lbn;
} cdvdfsv_rpc5h_05_packet;

typedef struct cdvdfsv_rpc5h_0D_packet_
{
	u32 m_lbn;
	u32 m_sectors;
	void *m_buf;
	sceCdRMode m_mode;
	u8 m_unused[4];
	uiptr m_eedest;
} cdvdfsv_rpc5h_0D_packet;

typedef struct cdvdfsv_rpc5h_0F_packet_
{
	sceCdRChain m_readChain[65];
	sceCdRMode m_mode;
	uiptr m_eedest;
} cdvdfsv_rpc5h_0F_packet;

#if 0
typedef struct cdvdfsc_rpc5h_03_packet_
{
	_DWORD m_lbn;
	_DWORD m_nsectors;
	_DWORD m_buf;
	sceCdRMode m_scecdrmodeC;
	_DWORD m_eedest;
} cdvdfsc_rpc5h_03_packet;
#endif

typedef struct cdvdfsv_rpc5h_02_packet_
{
	u32 m_lbn;
	u32 m_sectors;
	uiptr m_buf;
	sceCdRMode m_mode;
	uiptr m_eeremaindest;
	uiptr m_eedest;
} cdvdfsv_rpc5h_02_packet;

typedef struct cdvdfsv_rpc3h_22_packet_
{
	int m_media;
	char m_char4;
} cdvdfsv_rpc3h_22_packet;

#if 0
typedef struct cdvdfsv_rpc3h_28_packet_
{
	const sceCdCLOCK m_clock;
	_WORD m_arg2;
	_DWORD m_arg3;
} cdvdfsv_rpc3h_28_packet;

typedef struct cdvdfsv_rpc3h_08_packet_
{
	_DWORD m_address;
	u16 m_data;
	u8 m_result;
} cdvdfsv_rpc3h_08_packet;

typedef struct cdvdfsv_rpc3h_09_packet_
{
	_DWORD m_address;
	_WORD m_data;
	u8 m_result;
} cdvdfsv_rpc3h_09_packet;

typedef struct cdvdfsv_rpc3h_2E_packet_
{
	_DWORD m_arg1;
	_DWORD m_arg2;
} cdvdfsv_rpc3h_2E_packet;

typedef struct cdvdfsv_rpc3h_3C_packet_
{
	_DWORD m_arg1;
	_DWORD m_arg2;
} cdvdfsv_rpc3h_3C_packet;

typedef struct cdvdfsv_rpc5h_0B_packet_
{
	_DWORD m_arg1;
	_DWORD m_arg2;
	_DWORD m_command;
} cdvdfsv_rpc5h_0B_packet;

typedef struct cdvdfsv_rpc3h_0A_packet_
{
	_BYTE m_arg1;
	_BYTE m_arg2;
	_BYTE m_shift;
} cdvdfsv_rpc3h_0A_packet;
#endif

typedef struct cdvdfsv_rpc3h_05_packet_
{
	int m_param;
} cdvdfsv_rpc3h_05_packet;

typedef struct cdvdfsv_rpc3h_0B_packet_
{
	u8 m_cmdNum;
	u8 m_gap1;
	u16 m_inBuffSize;
	u8 m_inBuff[16];
} cdvdfsv_rpc3h_0B_packet;

typedef struct cdvdfsv_rpc3h_15_packet_
{
	int m_mode;
} cdvdfsv_rpc3h_15_packet;

typedef struct cdvdfsv_rpc5h_0C_packet_
{
	u8 m_cmdNum;
	u8 m_gap1;
	u16 m_inBuffSize;
	// TODO: check the size of the following member
	u8 m_inBuff[16];
} cdvdfsv_rpc5h_0C_packet;

typedef struct cdvdfsv_rpc3h_23_packet_
{
	int m_priority;
} cdvdfsv_rpc3h_23_packet;

typedef struct cdvdfsv_rpc3h_25_packet_
{
	int m_param;
	int m_timeout;
} cdvdfsv_rpc3h_25_packet;

typedef struct cdvdfsv_rpc5h_04_outpacket_
{
	int m_retres;
	int m_isdvd;
} cdvdfsv_rpc5h_04_outpacket;

typedef struct cdvdfsv_rpc3h_06_outpacket_
{
	int m_retres;
	u32 m_result;
	u8 m_buffer[8];
} cdvdfsv_rpc3h_06_outpacket;

typedef struct cdvdfsv_rpc3h_1A_outpacket_
{
	int m_retres;
	u32 m_status;
	char m_buffer[16];
} cdvdfsv_rpc3h_1A_outpacket;

typedef struct cdvdfsv_rpc3h_24_outpacket_
{
	int m_retres;
	u64 m_guid;
} cdvdfsv_rpc3h_24_outpacket;

typedef struct cdvdfsv_rpc3h_26_outpacket_
{
	int m_retres;
	unsigned int m_id;
} cdvdfsv_rpc3h_26_outpacket;

#if 0
typedef struct cdvdfsv_rpc3h_12_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
	u8 m_buffer;
} cdvdfsv_rpc3h_12_outpacket;

typedef struct cdvdfsv_rpc3h_14_outpacket_
{
	_DWORD m_dword0;
	u32 m_status;
	u8 m_buffer;
} cdvdfsv_rpc3h_14_outpacket;

typedef struct cdvdfsv_rpc3h_17_outpacket_
{
	_DWORD m_dword0;
	u32 m_status;
	char m_buffer;
} cdvdfsv_rpc3h_17_outpacket;

typedef struct cdvdfsv_rpc3h_18_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_18_outpacket;

typedef struct cdvdfsv_rpc3h_1C_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_1C_outpacket;

typedef struct cdvdfsv_rpc3h_1F_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_1F_outpacket;
#endif

typedef struct cdvdfsv_rpc3h_21_outpacket_
{
	int m_retres;
	u32 m_result;
} cdvdfsv_rpc3h_21_outpacket;

#if 0
typedef struct cdvdfsv_rpc3h_20_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_20_outpacket;
#endif

typedef struct cdvdfsv_rpc3h_15_outpacket_
{
	int m_retres;
	u32 m_status;
} cdvdfsv_rpc3h_15_outpacket;

#if 0
typedef struct cdvdfsv_rpc3h_19_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_19_outpacket;

typedef struct cdvdfsv_rpc3h_29_inneroutpacket_
{
	sceCdCLOCK m_clock;
	u16 m_arg2;
	int m_arg4;
	u32 m_arg3;
} cdvdfsv_rpc3h_29_inneroutpacket;

typedef struct cdvdfsv_rpc3h_29_outpacket_
{
	_DWORD m_dword0;
	cdvdfsv_rpc3h_29_inneroutpacket m_cdvdfsv_rpc3h_29_inneroutpacket4;
} cdvdfsv_rpc3h_29_outpacket;

typedef struct cdvdfsv_rpc3h_28_outpacket_
{
	_DWORD m_dword0;
	_DWORD m_dword4;
	_DWORD m_dword8;
} cdvdfsv_rpc3h_28_outpacket;

typedef struct cdvdfsv_rpc3h_30_outpacket_
{
	_DWORD m_dword0;
	u32 m_status;
} cdvdfsv_rpc3h_30_outpacket;

typedef struct cdvdfsv_rpc3h_32_outpacket_
{
	_DWORD m_dword0;
	u32 m_arg4;
	u32 m_arg1;
	u32 m_arg2;
	u32 m_arg3;
} cdvdfsv_rpc3h_32_outpacket;

typedef struct cdvdfsv_rpc3h_31_outpacket_
{
	_DWORD m_dword0;
	u32 m_arg2;
} cdvdfsv_rpc3h_31_outpacket;

typedef struct cdvdfsv_rpc3h_38_outpacket_
{
	_DWORD m_dword0;
	u32 m_arg2;
	u32 m_arg1;
} cdvdfsv_rpc3h_38_outpacket;

typedef struct cdvdfsv_rpc3h_2A_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
	u8 m_out;
} cdvdfsv_rpc3h_2A_outpacket;

typedef struct cdvdfsv_rpc3h_2B_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_2B_outpacket;

typedef struct cdvdfsv_rpc3h_2C_outpacket_
{
	_DWORD m_dword0;
	u32 m_arg2;
	u32 m_arg1;
} cdvdfsv_rpc3h_2C_outpacket;

typedef struct cdvdfsv_rpc3h_43_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
	u32 m_arg1;
} cdvdfsv_rpc3h_43_outpacket;

typedef struct cdvdfsv_rpc3h_2F_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_2F_outpacket;

typedef struct cdvdfsv_rpc3h_35_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_35_outpacket;
#endif

typedef struct cdvdfsv_rpc3h_01_outpacket_
{
	int m_retres;
	sceCdCLOCK m_clock;
} cdvdfsv_rpc3h_01_outpacket;

#if 0
typedef struct cdvdfsv_rpc3h_02_outpacket_
{
	_DWORD m_dword0;
	_DWORD m_dword4;
	_DWORD m_dword8;
} cdvdfsv_rpc3h_02_outpacket;

typedef struct cdvdfsv_rpc3h_08_outpacket_
{
	_DWORD m_dword0;
	_DWORD m_dword4;
	_DWORD m_dword8;
} cdvdfsv_rpc3h_08_outpacket;

typedef struct cdvdfsv_rpc3h_09_outpacket_
{
	_DWORD m_dword0;
	_DWORD m_dword4;
	_DWORD m_dword8;
} cdvdfsv_rpc3h_09_outpacket;

typedef struct cdvdfsv_rpc3h_2E_outpacket_
{
	_DWORD m_dword0;
	u32 m_result2;
	u32 m_result1;
} cdvdfsv_rpc3h_2E_outpacket;

typedef struct cdvdfsv_rpc3h_39_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_39_outpacket;

typedef struct cdvdfsv_rpc3h_3A_outpacket_
{
	_DWORD m_dword0;
	_DWORD m_arg2;
} cdvdfsv_rpc3h_3A_outpacket;

typedef struct cdvdfsv_rpc3h_3B_outpacket_
{
	_DWORD m_dword0;
	_DWORD m_arg2;
	_DWORD m_arg1;
} cdvdfsv_rpc3h_3B_outpacket;

typedef struct cdvdfsv_rpc3h_3C_outpacket_
{
	_DWORD m_dword0;
	u32 m_result2;
	u32 m_result1;
} cdvdfsv_rpc3h_3C_outpacket;

typedef struct cdvdfsv_rpc3h_3D_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_3D_outpacket;

typedef struct cdvdfsv_rpc3h_3E_outpacket_
{
	_DWORD m_dword0;
	u32 m_result2;
	u32 m_result1;
} cdvdfsv_rpc3h_3E_outpacket;

typedef struct cdvdfsv_rpc3h_3F_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_3F_outpacket;

typedef struct cdvdfsv_rpc3h_0F_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_0F_outpacket;

typedef struct cdvdfsv_rpc3h_10_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
	char m_buffer;
} cdvdfsv_rpc3h_10_outpacket;

typedef struct cdvdfsv_rpc3h_11_outpacket_
{
	_DWORD m_dword0;
	u32 m_result;
} cdvdfsv_rpc3h_11_outpacket;
#endif

typedef struct cdvdfsv_rpc5h_11_outpacket_
{
	int m_retres;
	u8 m_diskid[5];
} cdvdfsv_rpc5h_11_outpacket;

typedef struct cdvdfsv_rpc5h_17_outpacket_
{
	int m_retres;
	u32 m_status;
} cdvdfsv_rpc5h_17_outpacket;

#if 0
typedef struct cdvdfsv_rpc5h_0B_outpacket_
{
	_DWORD m_dword0;
	_DWORD m_dword4;
	_DWORD m_dword8;
	_DWORD m_dwordC;
	_DWORD m_dword10;
} cdvdfsv_rpc5h_0B_outpacket;
#endif

typedef struct cdvdfsv_rpc3h_0B_outpacket_
{
	u8 m_outbuf[16];
} cdvdfsv_rpc3h_0B_outpacket;

typedef struct cdvdfsv_rpc3h_05_outpacket_
{
	int m_retres;
	u32 m_traychk;
} cdvdfsv_rpc3h_05_outpacket;

typedef struct cdvdfsv_rpc3h_27_outpacket_
{
	int m_retres;
	int m_on_dual;
	unsigned int m_layer1_start;
} cdvdfsv_rpc3h_27_outpacket;

typedef union cdvdfsv_rpc3h_packet_
{
	cdvdfsv_rpc3h_05_packet m_pkt_05;
	cdvdfsv_rpc3h_0B_packet m_pkt_0B;
	cdvdfsv_rpc3h_15_packet m_pkt_15;
	cdvdfsv_rpc3h_22_packet m_pkt_22;
	cdvdfsv_rpc3h_23_packet m_pkt_23;
	cdvdfsv_rpc3h_25_packet m_pkt_25;
} cdvdfsv_rpc3h_packet;

typedef union cdvdfsv_rpc3h_outpacket_
{
	int m_retres;
	cdvdfsv_rpc3h_01_outpacket m_pkt_01;
	cdvdfsv_rpc3h_06_outpacket m_pkt_06;
	cdvdfsv_rpc3h_1A_outpacket m_pkt_1A;
	cdvdfsv_rpc3h_24_outpacket m_pkt_24;
	cdvdfsv_rpc3h_26_outpacket m_pkt_26;
	cdvdfsv_rpc3h_21_outpacket m_pkt_21;
	cdvdfsv_rpc3h_15_outpacket m_pkt_15;
	cdvdfsv_rpc3h_0B_outpacket m_pkt_0B;
	cdvdfsv_rpc3h_05_outpacket m_pkt_05;
	cdvdfsv_rpc3h_27_outpacket m_pkt_27;
} cdvdfsv_rpc3h_outpacket;

typedef union cdvdfsv_rpc5h_packet_
{
	cdvdfsv_rpc5h_01_packet m_pkt_01;
	cdvdfsv_rpc5h_04_packet m_pkt_04;
	cdvdfsv_rpc5h_05_packet m_pkt_05;
	cdvdfsv_rpc5h_0D_packet m_pkt_0D;
	cdvdfsv_rpc5h_0F_packet m_pkt_0F;
	cdvdfsv_rpc5h_02_packet m_pkt_02;
	cdvdfsv_rpc5h_0C_packet m_pkt_0C;
} cdvdfsv_rpc5h_packet;

typedef union cdvdfsv_rpc5h_outpacket_
{
	int m_retres;
	cdvdfsv_rpc5h_04_outpacket m_pkt_04;
	cdvdfsv_rpc5h_11_outpacket m_pkt_11;
	cdvdfsv_rpc5h_17_outpacket m_pkt_17;
} cdvdfsv_rpc5h_outpacket;
#endif

#if 1
#define PRINTF(...) \
	{ \
		printf(__VA_ARGS__); \
	}
#define KPRINTF(...) \
	{ \
		Kprintf(__VA_ARGS__); \
	}
#define VERBOSE_PRINTF(level, ...) \
	{ \
		if ( g_verbose_level >= (level) ) \
		{ \
			printf(__VA_ARGS__);\
		} \
	}
#define VERBOSE_KPRINTF(level, ...) \
	{ \
		if ( g_verbose_level >= (level) ) \
		{ \
			Kprintf(__VA_ARGS__);\
		} \
	}
#endif

#endif
