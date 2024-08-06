
#ifndef _00COMMONDEFS_H
#define _00COMMONDEFS_H

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

#endif
