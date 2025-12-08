
#include "irx_imports.h"

IRX_ID("S147NETB", 2, 2);

#define __fastcall
#define __cdecl
#define _BYTE u8
#define _WORD u16
#define _DWORD u32
#define __int8 char
#define __int32 int

//-------------------------------------------------------------------------
// Function declarations

int _start();

//----- (00400000) --------------------------------------------------------
int _start()
{
  int loadres_0; // $v0
  int loadres_1; // $v0
  int loadres_2; // $v0
  char probebuf[4]; // [sp+10h] [+10h] BYREF
  int fd_1; // [sp+14h] [+14h]
  int probe_i; // [sp+18h] [+18h]
  int fd_2; // [sp+1Ch] [+1Ch]
  int fd_3; // [sp+20h] [+20h]

  Kprintf("\ns147netb.irx: System147 Network Boot Manager v%d.%d\n", 2, 2);
  fd_1 = open("atfile19:usb-probe", 1);
  if ( fd_1 >= 0 )
  {
    for ( probe_i = 5; probe_i > 0; --probe_i )
    {
      read(fd_1, probebuf, 1);
      Kprintf(
        "\ns147netb.irx: === Wait %dsec for USB initialize... (probe=%d) ===\n",
        probe_i,
        (unsigned __int8)probebuf[0]);
      if ( probebuf[0] == 1 )
        break;
      DelayThread(1000000);
    }
    close(fd_1);
    if ( probebuf[0] )
    {
      probe_i = open("atfile10:ifc000.cnf", 1);
      if ( probe_i >= 0 )
      {
        close(probe_i);
        Kprintf("s147netb.irx: \"%s\" is found\n", "atfile10:ifc000.cnf");
        fd_1 = open("atfile10:inet.irx", 1);
        if ( fd_1 >= 0 )
        {
          close(fd_1);
          Kprintf("s147netb.irx: \"%s\" is found\n", "atfile10:inet.irx");
          fd_2 = open("atfile10:an986.irx", 1);
          if ( fd_2 >= 0 )
          {
            close(fd_2);
            Kprintf("s147netb.irx: \"%s\" is found\n", "atfile10:an986.irx");
            fd_3 = open("atfile10:s147http.irx", 1);
            if ( fd_3 >= 0 )
            {
              close(fd_3);
              Kprintf("s147netb.irx: \"%s\" is found\n", "atfile10:s147http.irx");
              loadres_0 = LoadStartModule("atfile10:inet.irx", 0, 0, 0);
              Kprintf("s147netb.irx: LoadStartModule \"%s\" (%d)\n", "atfile10:inet.irx", loadres_0);
              loadres_1 = LoadStartModule("atfile10:an986.irx", 0, 0, 0);
              Kprintf("s147netb.irx: LoadStartModule \"%s\" (%d)\n", "atfile10:an986.irx", loadres_1);
              loadres_2 = LoadStartModule("atfile10:s147http.irx", 0, 0, 0);
              Kprintf("s147netb.irx: LoadStartModule \"%s\" (%d)\n", "atfile10:s147http.irx", loadres_2);
            }
            else
            {
              Kprintf("s147netb.irx: Could not find \"%s\"\n", "atfile10:s147http.irx");
            }
            return 0;
          }
          else
          {
            Kprintf("s147netb.irx: Could not find \"%s\"\n", "atfile10:an986.irx");
            return 0;
          }
        }
        else
        {
          Kprintf("s147netb.irx: Could not find \"%s\"\n", "atfile10:inet.irx");
          return 0;
        }
      }
      else
      {
        Kprintf("s147netb.irx: Could not find \"%s\"\n", "atfile10:ifc000.cnf");
        return 0;
      }
    }
    else
    {
      Kprintf("\ns147netb.irx: *** No USB memory ***\n");
      return 0;
    }
  }
  else
  {
    Kprintf("s147netb.irx: Could not initialize USB memory driver\n");
    return 1;
  }
}
// 400000: using guessed type char probebuf[4];
