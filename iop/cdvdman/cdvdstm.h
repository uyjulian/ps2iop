/* Streaming control codes for the "cdrom_stm0:" device */
#define CDIOC_CDSTREAM0  0x4393 /* IOP STREAM */
#define CDIOC_CDSTREAD0  0x4394 /* IOP STREAM READ */
#define CDIOC_CDSTREAM1  0x4396 /* EE STREAM */
#define CDIOC_CDDASTREAM 0x4398 /* CDDA EE STREAM */

#define STM0_ARG_MODE 0x03

/* Modes for sceCdStream0() */
#define STM0_MODE_START  0x01
#define STM0_MODE_READ   0x02
#define STM0_MODE_STOP   0x03
#define STM0_MODE_SEEK   0x04
#define STM0_MODE_INIT   0x05
#define STM0_MODE_STAT   0x06
#define STM0_MODE_PAUSE  0x07
#define STM0_MODE_RESUME 0x08
#define STM0_MODE_SEEKF  0x09
