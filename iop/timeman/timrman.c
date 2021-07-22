//[module]	TIMEMANI
//[processor]	IOP
//[type]	ELF-IRX
//[name]	Timer_Manager
//[version]	0x101
//[memory map]	0xBF801100, 0xBF801110, 0xBF801120,
//		0xBF801450
//		0xBF801480, 0xBF801490, 0xBF8014A0,
//		0xBF8014B0, 0xBF8014C0
//[handlers]	-
//[entry point]	timrman_start, timrman_stub
//[made by]	[RO]man (roman_ps2dev@hotmail.com) 13 October 2002

#include <tamtypes.h>

#include "loadcore.h"
#include "intrman.h"

#include "timrman.h"

//timids << 2; use AllocHardTimer or ReferHardTimer to get one
#define RTC0 0xBF801100
#define RTC1 0xBF801110
#define RTC2 0xBF801120

#define RTC3 0xBF801480
#define RTC4 0xBF801490
#define RTC5 0xBF8014A0

#define RTC_HOLDREGS 0xBF8014B0
#define RTC_HOLDMODE (*(volatile unsigned int*)0xBF8014C0)

//source
#define TC_SYSCLOCK 1
#define TC_PIXEL 2
#define TC_HLINE 4
#define TC_HOLD 8

//size
#define TIMER_SIZE_16 16
#define TIMER_SIZE_32 32

//prescale
#define TIMER_PRESCALE_1 1
#define TIMER_PRESCALE_8 8
#define TIMER_PRESCALE_16 16
#define TIMER_PRESCALE_256 256

#define ERROR_INTR_CONTEXT -100
#define ERROR_NO_TIMER -150
#define ERROR_OK 0
#define ERROR_UNK -1

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


#define CONFIG_1450 (*(volatile int*)0xBF801450)

struct TIMRMAN
{
	int hwreg;
	char source, size;
	short prescale;
	int allocated;
} t[6] = {
	{RTC2, TC_SYSCLOCK, TIMER_SIZE_16, TIMER_PRESCALE_8, 0},
	{RTC5, TC_SYSCLOCK, TIMER_SIZE_32, TIMER_PRESCALE_256, 0},
	{RTC4, TC_SYSCLOCK, TIMER_SIZE_32, TIMER_PRESCALE_256, 0},
	{RTC3, TC_SYSCLOCK | TC_HLINE, TIMER_SIZE_32, TIMER_PRESCALE_1, 0},
	{RTC0, TC_SYSCLOCK | TC_PIXEL | TC_HOLD, TIMER_SIZE_16, TIMER_PRESCALE_1, 0},
	{RTC1, TC_SYSCLOCK | TC_HLINE | TC_HOLD, TIMER_SIZE_16, TIMER_PRESCALE_1, 0}};

int _start(int argc, char* argv[]);

///////////////////////////////////////////////////////////////////////[03]
void* GetTimersTable()
{
	return t; //address of the array
}

///////////////////////////////////////////////////////////////////////[04]
int AllocHardTimer(int source, int size, int prescale)
{
	register int i;
	int x;

	if (QueryIntrContext())
		return ERROR_INTR_CONTEXT; //intrman

	CpuSuspendIntr(&x); //intrman

	for (i = 0; i < 6; i++)
		if (!t[i].allocated && (t[i].source & source) &&
			(t[i].size == size) && (t[i].prescale >= prescale))
		{
			t[i].allocated++; //u8
			CpuResumeIntr(x); //intrman
			return t[i].hwreg >> 2;
		}

	CpuResumeIntr(x); //intrman
	return ERROR_NO_TIMER;
}

///////////////////////////////////////////////////////////////////////[05]
int ReferHardTimer(int source, int size, int mode, int modemask)
{
	register int i;
	int x;

	if (QueryIntrContext())
		return ERROR_INTR_CONTEXT; //intrman

	CpuSuspendIntr(&x); //intrman

	for (i = 0; i < 6; i++)
		if (t[i].allocated && (t[i].source & source) && (t[i].size == size) &&
			(int)(GetTimerStatus(t[i].hwreg >> 2) & modemask) == mode)
		{
			t[i].allocated++; //u8
			CpuResumeIntr(x); //intrman
			return t[i].hwreg >> 2;
		}

	CpuResumeIntr(x); //intrman
	return ERROR_NO_TIMER;
}

///////////////////////////////////////////////////////////////////////[10]
int GetHardTimerIntrCode(int timid)
{
	switch (timid << 2)
	{
		case RTC2:
			return INT_RTC2;
		case RTC0:
			return INT_RTC0;
		case RTC1:
			return INT_RTC1;

		case RTC4:
			return INT_RTC4;
		case RTC3:
			return INT_RTC3;
		case RTC5:
			return INT_RTC5;
	}
	return ERROR_UNK;
}

///////////////////////////////////////////////////////////////////////[06]
int FreeHardTimer(int timid)
{
	register int i;
	int x;

	if (QueryIntrContext())
		return ERROR_INTR_CONTEXT; //intrman

	for (i = 0; i < 6; i++)
		if (t[i].hwreg == (timid << 2))
			break;

	if ((i < 6) && (t[i].allocated))
	{
		CpuSuspendIntr(&x); //intrman
		t[i].allocated--;
		CpuResumeIntr(x); //intrman
		return ERROR_OK;
	}
	return ERROR_NO_TIMER;
}

///////////////////////////////////////////////////////////////////////[07]
void SetTimerMode(int timid, int mode)
{
	*(volatile short*)((timid << 2) + 4) = mode;
}

///////////////////////////////////////////////////////////////////////[08]
u32 GetTimerStatus(int timid)
{
	return *(volatile unsigned short*)((timid << 2) + 4);
}

///////////////////////////////////////////////////////////////////////[09]
void SetTimerCounter(int timid, u32 count)
{
	if ((timid << 2) < RTC3)
		*(volatile short*)((timid << 2) + 0) = count;
	else
		*(volatile int*)((timid << 2) + 0) = count;
}

///////////////////////////////////////////////////////////////////////[0A]
u32 GetTimerCounter(int timid)
{
	if ((timid << 2) < RTC3)
		return *(volatile short*)((timid << 2) + 0);
	else
		return *(volatile int*)((timid << 2) + 0);
}

///////////////////////////////////////////////////////////////////////[0B]
void SetTimerCompare(int timid, u32 compare)
{
	if ((timid << 2) + 8 < RTC3)
		*(volatile short*)((timid << 2) + 8) = compare;
	else
		*(volatile int*)((timid << 2) + 8) = compare;
}

///////////////////////////////////////////////////////////////////////[0C]
u32 GetTimerCompare(int timid)
{
	if ((timid << 2) + 8 < RTC3)
		return *(volatile short*)((timid << 2) + 8);
	else
		return *(volatile int*)((timid << 2) + 8);
}

///////////////////////////////////////////////////////////////////////[0D]
void SetHoldMode(int holdnum, int mode)
{
	RTC_HOLDMODE = (RTC_HOLDMODE &
					   (~(0xF << (holdnum * 4)))) |
				   ((mode & 0xF) << (holdnum * 4));
}

///////////////////////////////////////////////////////////////////////[0E]
unsigned long GetHoldMode(int holdnum)
{
	return (RTC_HOLDMODE >> (holdnum * 4)) & 0xF;
}

///////////////////////////////////////////////////////////////////////[0F]
unsigned long GetHoldReg(int holdnum)
{
	return *(volatile unsigned int*)(RTC_HOLDREGS + (holdnum * 4));
}

///////////////////////////////////////////////////////////////////////[01,02]

//////////////////////////////entrypoint///////////////////////////////

#define MODNAME "Timer_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_timrman;

//////////////////////////////entrypoint///////////////////////////////[00]
int _start(int argc, char* argv[])
{
	int i;
	u32 PRid;

	__asm__(
		"mfc0   %0, $15\n"
		: "=r"(PRid)
		:);


	if ((PRid < 0x10) || (CONFIG_1450 & 8))
		return 1;

	for (i = 5; i >= 0; i--)
		t[i].allocated = 0;

	if (RegisterLibraryEntries(&_exp_timrman) > 0)
		return 1;

	EnableIntr(INT_RTC5);

	return 0; //loadcore
}
