
#include "irx_imports.h"

IRX_ID("S147NETB", 2, 2);

//----- (00400000) --------------------------------------------------------
int _start(int ac, char **av)
{
  char probebuf; // [sp+10h] [+10h] BYREF
  int fd; // [sp+14h] [+14h]
  int probe_i; // [sp+18h] [+18h]

  (void)ac;
  (void)av;
  Kprintf("\ns147netb.irx: System147 Network Boot Manager v%d.%d\n", 2, 2);
  fd = open("atfile19:usb-probe", 1);
  if ( fd < 0 )
  {
    Kprintf("s147netb.irx: Could not initialize USB memory driver\n");
    return 1;
  }
  for ( probe_i = 5; probe_i > 0; --probe_i )
  {
    read(fd, &probebuf, sizeof(probebuf));
    Kprintf(
      "\ns147netb.irx: === Wait %dsec for USB initialize... (probe=%d) ===\n",
      probe_i,
      (u8)probebuf);
    if ( probebuf == 1 )
      break;
    DelayThread(1000000);
  }
  close(fd);
  if ( !probebuf )
  {
    Kprintf("\ns147netb.irx: *** No USB memory ***\n");
    return 0;
  }
  fd = open("atfile10:ifc000.cnf", 1);
  if ( fd < 0 )
  {
    Kprintf("s147netb.irx: Could not find \"%s\"\n", "atfile10:ifc000.cnf");
    return 0;
  }
  close(fd);
  Kprintf("s147netb.irx: \"%s\" is found\n", "atfile10:ifc000.cnf");
  fd = open("atfile10:inet.irx", 1);
  if ( fd < 0 )
  {
    Kprintf("s147netb.irx: Could not find \"%s\"\n", "atfile10:inet.irx");
    return 0;
  }
  close(fd);
  Kprintf("s147netb.irx: \"%s\" is found\n", "atfile10:inet.irx");
  fd = open("atfile10:an986.irx", 1);
  if ( fd < 0 )
  {
    Kprintf("s147netb.irx: Could not find \"%s\"\n", "atfile10:an986.irx");
    return 0;
  }
  close(fd);
  Kprintf("s147netb.irx: \"%s\" is found\n", "atfile10:an986.irx");
  fd = open("atfile10:s147http.irx", 1);
  if ( fd < 0 )
  {
    Kprintf("s147netb.irx: Could not find \"%s\"\n", "atfile10:s147http.irx");
    return 0;
  }
  close(fd);
  Kprintf("s147netb.irx: \"%s\" is found\n", "atfile10:s147http.irx");
  Kprintf("s147netb.irx: LoadStartModule \"%s\" (%d)\n", "atfile10:inet.irx", LoadStartModule("atfile10:inet.irx", 0, 0, 0));
  Kprintf("s147netb.irx: LoadStartModule \"%s\" (%d)\n", "atfile10:an986.irx", LoadStartModule("atfile10:an986.irx", 0, 0, 0));
  Kprintf("s147netb.irx: LoadStartModule \"%s\" (%d)\n", "atfile10:s147http.irx", LoadStartModule("atfile10:s147http.irx", 0, 0, 0));
  return 0;
}
// 400000: using guessed type char probebuf[4];
