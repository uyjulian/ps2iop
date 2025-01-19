
#ifndef COMMON_DEFS_H_
#define COMMON_DEFS_H_

#if 0
#include <stdbool.h>
#endif

#if 0
#define __fastcall
#define __cdecl
#define __noreturn
#endif

#if 0
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

#if 0
#define LAST_IND(x, part_type) (sizeof(x) / sizeof(part_type) - 1)
#define HIGH_IND(x, part_type) LAST_IND(x, part_type)
#define LOW_IND(x, part_type) 0

#define BYTEn(x, n) (*((_BYTE*)&(x) + n))
#define WORDn(x, n) (*((_WORD*)&(x) + n))
#define DWORDn(x, n) (*((_DWORD*)&(x) + n))
#endif

#if 0
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

#if 0
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

#if 0
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned long u_long;
#endif

#if 0
#define _break(...) __builtin_trap()
#endif

#if 1
#include <cdvdman.h>
#endif

#if 0
typedef struct dev5_mmio_hwport_
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
} dev5_mmio_hwport_t;

#if !defined(USE_DEV5_MMIO_HWPORT) && defined(_IOP)
// cppcheck-suppress-macro constVariablePointer
#define USE_DEV5_MMIO_HWPORT() dev5_mmio_hwport_t *const dev5_mmio_hwport = (dev5_mmio_hwport_t *)0xBF402000
#endif
#if !defined(USE_DEV5_MMIO_HWPORT)
#define USE_DEV5_MMIO_HWPORT()
#endif

typedef struct cdrom_stm_devctl_
{
	u32 m_posszarg1;
	u32 m_posszarg2;
	void *m_buffer;
	u32 m_cmdid;
	sceCdRMode m_rmode;
	u32 m_error;
} cdrom_stm_devctl_t;

typedef struct cdvdman_dirtbl_entry_
{
	int m_number;
	int m_parent;
	int m_extent;
	char m_name[32];
} cdvdman_dirtbl_entry_t;

typedef struct cdvdman_fhinfo_
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
} cdvdman_fhinfo_t;

typedef struct cdvdman_dma3_parameter_
{
	u16 m_dma3_blkwords;
	u16 m_dma3_blkcount;
	void *m_dma3_maddress;
	int (*m_dma3_callback)(void);
	u16 m_dma3_csectors;
	u16 m_cdvdreg_howto;
	u32 m_dma3_msectors;
} cdvdman_dma3_parameter_t;

typedef struct cdvdman_pathtbl_
{
	int m_cache_path_sz;
	int m_lsn;
	unsigned int m_nsec;
	int m_layer;
	unsigned int m_cache_hit_count;
} cdvdman_pathtbl_t;

typedef struct cdvdman_filetbl_entry_
{
	sceCdlFILE m_file_struct;
	int m_flags;
} cdvdman_filetbl_entry_t;

typedef struct iso9660_desc_
{
	// cppcheck-suppress unusedStructMember
	unsigned char m_type[1];
	unsigned char m_id[5];
	// cppcheck-suppress unusedStructMember
	unsigned char m_version[1];
	// cppcheck-suppress unusedStructMember
	unsigned char m_unused1[1];
	// cppcheck-suppress unusedStructMember
	unsigned char m_system_id[32];
	// cppcheck-suppress unusedStructMember
	unsigned char m_volume_id[32];
	// cppcheck-suppress unusedStructMember
	unsigned char m_unused2[8];
	// cppcheck-suppress unusedStructMember
	unsigned char m_volume_space_size[8];
	// cppcheck-suppress unusedStructMember
	unsigned char m_unused3[32];
	// cppcheck-suppress unusedStructMember
	unsigned char m_volume_set_size[4];
	// cppcheck-suppress unusedStructMember
	unsigned char m_volume_sequence_number[4];
	// cppcheck-suppress unusedStructMember
	unsigned char m_logical_block_size[4];
	// cppcheck-suppress unusedStructMember
	unsigned char m_path_table_size[8];
	unsigned char m_type_l_path_table[4];
	// cppcheck-suppress unusedStructMember
	unsigned char m_opt_type_l_path_table[4];
	// cppcheck-suppress unusedStructMember
	unsigned char m_type_m_path_table[4];
	// cppcheck-suppress unusedStructMember
	unsigned char m_opt_type_m_path_table[4];
	// cppcheck-suppress unusedStructMember
	unsigned char m_root_directory_record[34];
	// cppcheck-suppress unusedStructMember
	unsigned char m_volume_set_id[128];
	// cppcheck-suppress unusedStructMember
	unsigned char m_publisher_id[128];
	// cppcheck-suppress unusedStructMember
	unsigned char m_preparer_id[128];
	// cppcheck-suppress unusedStructMember
	unsigned char m_application_id[128];
	// cppcheck-suppress unusedStructMember
	unsigned char m_copyright_file_id[37];
	// cppcheck-suppress unusedStructMember
	unsigned char m_abstract_file_id[37];
	// cppcheck-suppress unusedStructMember
	unsigned char m_bibliographic_file_id[37];
	// cppcheck-suppress unusedStructMember
	unsigned char m_creation_date[17];
	// cppcheck-suppress unusedStructMember
	unsigned char m_modification_date[17];
	// cppcheck-suppress unusedStructMember
	unsigned char m_expiration_date[17];
	// cppcheck-suppress unusedStructMember
	unsigned char m_effective_date[17];
	// cppcheck-suppress unusedStructMember
	unsigned char m_file_structure_version[1];
	// cppcheck-suppress unusedStructMember
	unsigned char m_unused4[1];
	// cppcheck-suppress unusedStructMember
	unsigned char m_application_data[512];
	// cppcheck-suppress unusedStructMember
	unsigned char m_unused5[653];
} iso9660_desc_t;

typedef struct iso9660_path_
{
	unsigned char m_name_len[2];
	unsigned char m_extent[4];
	unsigned char m_parent[2];
	unsigned char m_name[];
} iso9660_path_t;

typedef struct iso9660_dirent_
{
	unsigned char m_length[1];
	unsigned char m_ext_attr_length[1];
	unsigned char m_extent[8];
	unsigned char m_size[8];
	unsigned char m_date[7];
	unsigned char m_flags[1];
	unsigned char m_file_unit_size[1];
	unsigned char m_interleave[1];
	unsigned char m_volume_sequence_number[4];
	unsigned char m_name_len[1];
	unsigned char m_name[];
} iso9660_dirent_t;

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
	int m_last_read_timeout;
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
	cdvdman_dma3_parameter_t m_dma3_param;
	int m_cdvdman_dma3sec;
	int m_drive_interupt_request;
	u16 m_dec_mode_set;
	u16 m_dec_mode_last_set;
	int m_waf_set_test;
	int m_interupt_read_state;
	int m_cd_inited;
	int m_tray_is_open;
	int m_break_cdvdfsv_readchain;
	int m_unused[10];
} cdvdman_internal_struct_t;
#endif

#if 0
typedef struct cdvdfsv_rpc1_inpacket_
{
	int m_mode;
} cdvdfsv_rpc1_inpacket_t;
typedef struct cdvdfsv_rpc1_outpacket_
{
	int m_retres;
	int m_cdvdfsv_ver;
	int m_cdvdman_ver;
	int m_debug_mode;
} cdvdfsv_rpc1_outpacket_t;
typedef struct cdvdfsv_rpc2_inpacket_
{
	int m_mode;
} cdvdfsv_rpc2_inpacket_t;
typedef struct cdvdfsv_rpc2_outpacket_
{
	int m_retres;
} cdvdfsv_rpc2_outpacket_t;
typedef struct cdvdfsv_unaligned_data_outpacket_
{
	u32 m_b1len;
	u32 m_b2len;
	u32 m_b1dst;
	u32 m_b2dst;
	u8 m_pbuf1[64];
	u8 m_pbuf2[64];
} cdvdfsv_unaligned_data_outpacket_t;

typedef struct cdvdfsv_rpc4_sz12c_inpacket_
{
	sceCdlFILE m_fp;
	int m_file_attributes;
	char m_path[256];
	uiptr m_eedest;
	int m_layer;
} cdvdfsv_rpc4_sz12c_inpacket_t;

typedef struct cdvdfsv_rpc4_sz128_inpacket_
{
	sceCdlFILE m_fp;
	int m_file_attributes;
	char m_path[256];
	uiptr m_eedest;
} cdvdfsv_rpc4_sz128_inpacket_t;

typedef struct cdvdfsv_rpc4_sz124_inpacket_
{
	sceCdlFILE m_fp;
	char m_path[256];
	uiptr m_eedest;
} cdvdfsv_rpc4_sz124_inpacket_t;

typedef union cdvdfsv_rpc4_inpacket_
{
	cdvdfsv_rpc4_sz12c_inpacket_t m_pkt_sz12c;
	cdvdfsv_rpc4_sz128_inpacket_t m_pkt_sz128;
	cdvdfsv_rpc4_sz124_inpacket_t m_pkt_sz124;
} cdvdfsv_rpc4_inpacket_t;

typedef struct cdvdfsv_rpc4_outpacket_
{
	int m_retres;
	int m_padding[3];
} cdvdfsv_rpc4_outpacket_t;

typedef struct cdvdfsv_rpc3_05_inpacket_
{
	int m_param;
} cdvdfsv_rpc3_05_inpacket_t;

typedef struct cdvdfsv_rpc3_0B_inpacket_
{
	u8 m_cmdNum;
	u8 m_gap1;
	u16 m_inBuffSize;
	u8 m_inBuff[16];
} cdvdfsv_rpc3_0B_inpacket_t;

typedef struct cdvdfsv_rpc3_15_inpacket_
{
	int m_mode;
} cdvdfsv_rpc3_15_inpacket_t;

typedef struct cdvdfsv_rpc3_22_inpacket_
{
	int m_media;
	char m_char4;
} cdvdfsv_rpc3_22_inpacket_t;

typedef struct cdvdfsv_rpc3_23_inpacket_
{
	int m_priority;
} cdvdfsv_rpc3_23_inpacket_t;

typedef struct cdvdfsv_rpc3_25_inpacket_
{
	int m_param;
	int m_timeout;
} cdvdfsv_rpc3_25_inpacket_t;

typedef union cdvdfsv_rpc3_inpacket_
{
	cdvdfsv_rpc3_05_inpacket_t m_pkt_05;
	cdvdfsv_rpc3_0B_inpacket_t m_pkt_0B;
	cdvdfsv_rpc3_15_inpacket_t m_pkt_15;
	cdvdfsv_rpc3_22_inpacket_t m_pkt_22;
	cdvdfsv_rpc3_23_inpacket_t m_pkt_23;
	cdvdfsv_rpc3_25_inpacket_t m_pkt_25;
} cdvdfsv_rpc3_inpacket_t;

typedef struct cdvdfsv_rpc3_01_outpacket_
{
	int m_retres;
	sceCdCLOCK m_clock;
} cdvdfsv_rpc3_01_outpacket_t;

typedef struct cdvdfsv_rpc3_05_outpacket_
{
	int m_retres;
	u32 m_traychk;
} cdvdfsv_rpc3_05_outpacket_t;

typedef struct cdvdfsv_rpc3_06_outpacket_
{
	int m_retres;
	u32 m_result;
	u8 m_buffer[8];
} cdvdfsv_rpc3_06_outpacket_t;

typedef struct cdvdfsv_rpc3_0B_outpacket_
{
	u8 m_outbuf[16];
} cdvdfsv_rpc3_0B_outpacket_t;

typedef struct cdvdfsv_rpc3_15_outpacket_
{
	int m_retres;
	u32 m_status;
} cdvdfsv_rpc3_15_outpacket_t;

typedef struct cdvdfsv_rpc3_1A_outpacket_
{
	int m_retres;
	u32 m_status;
	char m_buffer[16];
} cdvdfsv_rpc3_1A_outpacket_t;

typedef struct cdvdfsv_rpc3_21_outpacket_
{
	int m_retres;
	u32 m_result;
} cdvdfsv_rpc3_21_outpacket_t;

typedef struct cdvdfsv_rpc3_24_outpacket_
{
	int m_retres;
	u64 m_guid;
} cdvdfsv_rpc3_24_outpacket_t;

typedef struct cdvdfsv_rpc3_26_outpacket_
{
	int m_retres;
	unsigned int m_id;
} cdvdfsv_rpc3_26_outpacket_t;

typedef struct cdvdfsv_rpc3_27_outpacket_
{
	int m_retres;
	int m_on_dual;
	unsigned int m_layer1_start;
} cdvdfsv_rpc3_27_outpacket_t;

typedef union cdvdfsv_rpc3_outpacket_
{
	int m_retres;
	cdvdfsv_rpc3_01_outpacket_t m_pkt_01;
	cdvdfsv_rpc3_05_outpacket_t m_pkt_05;
	cdvdfsv_rpc3_06_outpacket_t m_pkt_06;
	cdvdfsv_rpc3_0B_outpacket_t m_pkt_0B;
	cdvdfsv_rpc3_15_outpacket_t m_pkt_15;
	cdvdfsv_rpc3_1A_outpacket_t m_pkt_1A;
	cdvdfsv_rpc3_21_outpacket_t m_pkt_21;
	cdvdfsv_rpc3_24_outpacket_t m_pkt_24;
	cdvdfsv_rpc3_26_outpacket_t m_pkt_26;
	cdvdfsv_rpc3_27_outpacket_t m_pkt_27;
} cdvdfsv_rpc3_outpacket_t;

typedef struct cdvdfsv_rpc5_01_inpacket_
{
	u32 m_lbn;
	u32 m_sectors;
	uiptr m_paddr;
	sceCdRMode m_rmodeee;
	uiptr m_eeremaindest;
	uiptr m_eedest;
	u32 m_decval;
} cdvdfsv_rpc5_01_inpacket_t;

typedef struct cdvdfsv_rpc5_02_inpacket_
{
	u32 m_lbn;
	u32 m_sectors;
	uiptr m_buf;
	sceCdRMode m_mode;
	uiptr m_eeremaindest;
	uiptr m_eedest;
} cdvdfsv_rpc5_02_inpacket_t;

typedef struct cdvdfsv_rpc5_04_inpacket_
{
	uiptr m_eedest;
} cdvdfsv_rpc5_04_inpacket_t;

typedef struct cdvdfsv_rpc5_05_inpacket_
{
	u32 m_lbn;
} cdvdfsv_rpc5_05_inpacket_t;

typedef struct cdvdfsv_rpc5_0C_inpacket_
{
	u8 m_cmdNum;
	u8 m_gap1;
	u16 m_inBuffSize;
	// TODO: check the size of the following member
	u8 m_inBuff[16];
} cdvdfsv_rpc5_0C_inpacket_t;

typedef struct cdvdfsv_rpc5_0D_inpacket_
{
	u32 m_lbn;
	u32 m_sectors;
	void *m_buf;
	sceCdRMode m_mode;
	u8 m_unused[4];
	uiptr m_eedest;
} cdvdfsv_rpc5_0D_inpacket_t;

typedef struct cdvdfsv_rpc5_0F_inpacket_
{
	sceCdRChain m_readChain[65];
	sceCdRMode m_mode;
	uiptr m_eedest;
} cdvdfsv_rpc5_0F_inpacket_t;

typedef union cdvdfsv_rpc5_inpacket_
{
	cdvdfsv_rpc5_01_inpacket_t m_pkt_01;
	cdvdfsv_rpc5_02_inpacket_t m_pkt_02;
	cdvdfsv_rpc5_04_inpacket_t m_pkt_04;
	cdvdfsv_rpc5_05_inpacket_t m_pkt_05;
	cdvdfsv_rpc5_0C_inpacket_t m_pkt_0C;
	cdvdfsv_rpc5_0D_inpacket_t m_pkt_0D;
	cdvdfsv_rpc5_0F_inpacket_t m_pkt_0F;
} cdvdfsv_rpc5_inpacket_t;

typedef struct cdvdfsv_rpc5_04_outpacket_
{
	int m_retres;
	int m_isdvd;
} cdvdfsv_rpc5_04_outpacket_t;

typedef struct cdvdfsv_rpc5_11_outpacket_
{
	int m_retres;
	u8 m_diskid[5];
} cdvdfsv_rpc5_11_outpacket_t;

typedef struct cdvdfsv_rpc5_17_outpacket_
{
	int m_retres;
	u32 m_status;
} cdvdfsv_rpc5_17_outpacket_t;

typedef union cdvdfsv_rpc5_outpacket_
{
	int m_retres;
	cdvdfsv_rpc5_04_outpacket_t m_pkt_04;
	cdvdfsv_rpc5_11_outpacket_t m_pkt_11;
	cdvdfsv_rpc5_17_outpacket_t m_pkt_17;
} cdvdfsv_rpc5_outpacket_t;
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

#if 1
#ifndef CDVD_VARIANT_DNAS
#define CDVD_VARIANT_DNAS 1
#endif
#endif

#endif
