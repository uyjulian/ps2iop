
#ifndef _S147MDEV_H
#define _S147MDEV_H

#include <ioman.h>

extern int s147mdev_4_addfs(iop_device_t *drv, int unit10);
extern int s147mdev_5_delfs(int unit10);

#define s147mdev_IMPORTS_start DECLARE_IMPORT_TABLE(s147mdev, 1, 1)
#define s147mdev_IMPORTS_end END_IMPORT_TABLE

#define I_s147mdev_4_addfs DECLARE_IMPORT(4, s147mdev_4_addfs)
#define I_s147mdev_5_delfs DECLARE_IMPORT(5, s147mdev_5_delfs)

#endif
