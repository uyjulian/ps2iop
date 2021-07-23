
#include "iomanX.h"
#include "pvrdrv.h"
#include "stdio.h"
#include "sysclib.h"
#include "thbase.h"
#include "thsemap.h"
#include "speedregs.h"

extern int module_start(int a1, const char **a2);
extern int module_stop();
extern int dvrf_df_init(iop_device_t *a1);
extern int dvrf_df_exit(iop_device_t *a1);
extern int dvrpfs_df_chdir(iop_file_t *a1, const char *name);
extern int dvrpfs_df_chstat(iop_file_t *a1, const char *name, iox_stat_t *stat, unsigned int statmask);
extern int dvrpfs_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrpfs_df_dopen(iop_file_t *a1, const char *name);
extern int dvrpfs_df_format(iop_file_t *a1, const char *dev, const char *blockdev, void *arg, int arglen);
extern int dvrpfs_df_getstat(iop_file_t *a1, const char *name, iox_stat_t *stat);
extern int dvrpfs_df_mkdir(iop_file_t *a1, const char *path, int mode);
extern int dvrpfs_df_mount(iop_file_t *a1, const char *fsname, const char *devname, int flag, void *arg, int arglen);
extern int dvrpfs_df_open(iop_file_t *a1, const char *name, int flags, int mode);
extern int dvrpfs_df_readlink(iop_file_t *a1, const char *path, char *buf, unsigned int buflen);
extern int dvrpfs_df_remove(iop_file_t *a1, const char *name);
extern int dvrpfs_df_rename(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrpfs_df_rmdir(iop_file_t *a1, const char *path);
extern int dvrpfs_df_symlink(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrpfs_df_sync(iop_file_t *a1, const char *dev, int flag);
extern int dvrpfs_df_umount(iop_file_t *a1, const char *fsname);
extern int dvrhdd_df_chdir(iop_file_t *a1, const char *name);
extern int dvrhdd_df_chstat(iop_file_t *a1, const char *name, iox_stat_t *stat, unsigned int statmask);
extern int dvrhdd_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrhdd_df_dopen(iop_file_t *a1, const char *path);
extern int dvrhdd_df_format(iop_file_t *a1, const char *dev, const char *blockdev, void *arg, int arglen);
extern int dvrhdd_df_getstat(iop_file_t *a1, const char *name, iox_stat_t *stat);
extern int dvrhdd_df_mkdir(iop_file_t *a1, const char *path, int mode);
extern int dvrhdd_df_mount(iop_file_t *a1, const char *fsname, const char *devname, int flag, void *arg, int arglen);
extern int dvrhdd_df_open(iop_file_t *a1, const char *name, int flags, int mode);
extern int dvrhdd_df_readlink(iop_file_t *a1, const char *path, char *buf, unsigned int buflen);
extern int dvrhdd_df_remove(iop_file_t *a1, const char *name);
extern int dvrhdd_df_rename(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrhdd_df_rmdir(iop_file_t *a1, const char *path);
extern int dvrhdd_df_symlink(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrhdd_df_sync(iop_file_t *a1, const char *dev, int flag);
extern int dvrhdd_df_umount(iop_file_t *a1, const char *fsname);
extern int dvrhdck_df_chdir(iop_file_t *a1, const char *name);
extern int dvrhdck_df_chstat(iop_file_t *a1, const char *name, iox_stat_t *stat, unsigned int statmask);
extern int dvrhdck_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrhdck_df_dopen(iop_file_t *a1, const char *path);
extern int dvrhdck_df_format(iop_file_t *a1, const char *dev, const char *blockdev, void *arg, int arglen);
extern int dvrhdck_df_getstat(iop_file_t *a1, const char *name, iox_stat_t *stat);
extern int dvrhdck_df_mkdir(iop_file_t *a1, const char *path, int mode);
extern int dvrhdck_df_mount(iop_file_t *a1, const char *fsname, const char *devname, int flag, void *arg, int arglen);
extern int dvrhdck_df_open(iop_file_t *a1, const char *name, int flags, int mode);
extern int dvrhdck_df_readlink(iop_file_t *a1, const char *path, char *buf, unsigned int buflen);
extern int dvrhdck_df_remove(iop_file_t *a1, const char *name);
extern int dvrhdck_df_rename(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrhdck_df_rmdir(iop_file_t *a1, const char *path);
extern int dvrhdck_df_symlink(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrhdck_df_sync(iop_file_t *a1, const char *dev, int flag);
extern int dvrhdck_df_umount(iop_file_t *a1, const char *fsname);
extern int dvrfssk_df_chdir(iop_file_t *a1, const char *name);
extern int dvrfssk_df_chstat(iop_file_t *a1, const char *name, iox_stat_t *stat, unsigned int statmask);
extern int dvrfssk_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrfssk_df_dopen(iop_file_t *a1, const char *path);
extern int dvrfssk_df_format(iop_file_t *a1, const char *dev, const char *blockdev, void *arg, int arglen);
extern int dvrfssk_df_getstat(iop_file_t *a1, const char *name, iox_stat_t *stat);
extern int dvrfssk_df_mkdir(iop_file_t *a1, const char *path, int mode);
extern int dvrfssk_df_mount(iop_file_t *a1, const char *fsname, const char *devname, int flag, void *arg, int arglen);
extern int dvrfssk_df_open(iop_file_t *a1, const char *name, int flags, int mode);
extern int dvrfssk_df_readlink(iop_file_t *a1, const char *path, char *buf, unsigned int buflen);
extern int dvrfssk_df_remove(iop_file_t *a1, const char *name);
extern int dvrfssk_df_rename(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrfssk_df_rmdir(iop_file_t *a1, const char *path);
extern int dvrfssk_df_symlink(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrfssk_df_sync(iop_file_t *a1, const char *dev, int flag);
extern int dvrfssk_df_umount(iop_file_t *a1, const char *fsname);
extern int dvrfsck_df_chdir(iop_file_t *a1, const char *name);
extern int dvrfsck_df_chstat(iop_file_t *a1, const char *name, iox_stat_t *stat, unsigned int statmask);
extern int dvrfsck_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrfsck_df_dopen(iop_file_t *a1, const char *path);
extern int dvrfsck_df_format(iop_file_t *a1, const char *dev, const char *blockdev, void *arg, int arglen);
extern int dvrfsck_df_getstat(iop_file_t *a1, const char *name, iox_stat_t *stat);
extern int dvrfsck_df_mkdir(iop_file_t *a1, const char *path, int mode);
extern int dvrfsck_df_mount(iop_file_t *a1, const char *fsname, const char *devname, int flag, void *arg, int arglen);
extern int dvrfsck_df_open(iop_file_t *a1, const char *name, int flags, int mode);
extern int dvrfsck_df_readlink(iop_file_t *a1, const char *path, char *buf, unsigned int buflen);
extern int dvrfsck_df_remove(iop_file_t *a1, const char *name);
extern int dvrfsck_df_rename(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrfsck_df_rmdir(iop_file_t *a1, const char *path);
extern int dvrfsck_df_symlink(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrfsck_df_sync(iop_file_t *a1, const char *dev, int flag);
extern int dvrfsck_df_umount(iop_file_t *a1, const char *fsname);
extern int dvrf_df_chdir(iop_file_t *a1, const char *name);
extern int dvrf_df_chstat(iop_file_t *a1, const char *name, iox_stat_t *stat, unsigned int statmask);
extern int dvrf_df_close(iop_file_t *a1);
extern int dvrf_df_dclose(iop_file_t *a1);
extern int dvrf_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrf_df_dopen(iop_file_t *a1, const char *path);
extern int dvrf_df_dread(iop_file_t *a1, iox_dirent_t *buf);
extern int dvrf_df_format(iop_file_t *a1, const char *dev, const char *blockdev, void *arg, int arglen);
extern int dvrf_df_getstat(iop_file_t *a1, const char *name, iox_stat_t *stat);
extern int dvrf_df_ioctl(iop_file_t *a1, int cmd, void *param);
extern int dvrf_df_ioctl2(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrf_df_lseek(iop_file_t *a1, int offset, int mode);
extern s64 dvrf_df_lseek64(iop_file_t *a1, s64 offset, int whence);
extern int dvrf_df_mkdir(iop_file_t *a1, const char *path, int mode);
extern int dvrf_df_mount(iop_file_t *a1, const char *fsname, const char *devname, int flag, void *arg, int arglen);
extern int dvrf_df_open(iop_file_t *a1, const char *name, int flags, int mode);
extern int dvrf_df_read(iop_file_t *a1, void *ptr, int size);
extern int dvrf_df_readlink(iop_file_t *a1, const char *path, char *buf, unsigned int buflen);
extern int dvrf_df_remove(iop_file_t *a1, const char *name);
extern int dvrf_df_rename(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrf_df_rmdir(iop_file_t *a1, const char *path);
extern int dvrf_df_symlink(iop_file_t *a1, const char *old, const char *new_1);
extern int dvrf_df_sync(iop_file_t *a1, const char *dev, int flag);
extern int dvrf_df_umount(iop_file_t *a1, const char *fsname);
extern int dvrf_df_write(iop_file_t *a1, void *ptr, int size);
extern int RegisterFd(iop_file_t *a1, int a2);
extern int UnregisterFd(iop_file_t *a1);
extern int GetFd(iop_file_t *a1);
extern void CopySceStat(iox_stat_t *stat, u8 *a2);

#define GEN_TRANSLATION_FUNCS(basefuncname, basedevname, shouldbswapformatarg)                                                              \
    int basefuncname##_df_chdir(iop_file_t *a1, const char *name)                                                                           \
    {                                                                                                                                       \
        char translated_name[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_name, "%s%d:%s", basedevname, a1->unit, name);                                                                   \
        return dvrf_df_chdir(a1, translated_name);                                                                                          \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_chstat(iop_file_t *a1, const char *name, iox_stat_t *stat, unsigned int statmask)                                 \
    {                                                                                                                                       \
        char translated_name[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_name, "%s%d:%s", basedevname, a1->unit, name);                                                                   \
        return dvrf_df_chstat(a1, translated_name, stat, statmask);                                                                         \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen) \
    {                                                                                                                                       \
        char translated_name[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_name, "%s%d:%s", basedevname, a1->unit, name);                                                                   \
        return dvrf_df_devctl(a1, translated_name, cmd, arg, arglen, buf, buflen);                                                          \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_dopen(iop_file_t *a1, const char *path)                                                                           \
    {                                                                                                                                       \
        char translated_path[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_path, "%s%d:%s", basedevname, a1->unit, path);                                                                   \
        return dvrf_df_dopen(a1, translated_path);                                                                                          \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_format(iop_file_t *a1, const char *dev, const char *blockdev, void *arg, int arglen)                              \
    {                                                                                                                                       \
        char translated_dev[1040];                                                                                                          \
                                                                                                                                            \
        if (shouldbswapformatarg) {                                                                                                         \
            sprintf(translated_dev, "%s:%s", basedevname, dev);                                                                             \
            *(u32 *)arg = bswap32(*(u32 *)arg);                                                                                             \
        } else {                                                                                                                            \
            sprintf(translated_dev, "%s%d:%s", basedevname, a1->unit, dev);                                                                 \
        }                                                                                                                                   \
        return dvrf_df_format(a1, translated_dev, blockdev, arg, arglen);                                                                   \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_getstat(iop_file_t *a1, const char *name, iox_stat_t *stat)                                                       \
    {                                                                                                                                       \
        char translated_name[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_name, "%s%d:%s", basedevname, a1->unit, name);                                                                   \
        return dvrf_df_getstat(a1, translated_name, stat);                                                                                  \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_mkdir(iop_file_t *a1, const char *path, int mode)                                                                 \
    {                                                                                                                                       \
        char translated_path[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_path, "%s%d:%s", basedevname, a1->unit, path);                                                                   \
        return dvrf_df_mkdir(a1, translated_path, mode);                                                                                    \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_mount(iop_file_t *a1, const char *fsname, const char *devname, int flag, void *arg, int arglen)                   \
    {                                                                                                                                       \
        char translated_fsname[1040];                                                                                                       \
                                                                                                                                            \
        sprintf(translated_fsname, "%s%d:%s", basedevname, a1->unit, fsname);                                                               \
        return dvrf_df_mount(a1, translated_fsname, devname, flag, arg, arglen);                                                            \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_open(iop_file_t *a1, const char *name, int flags, int mode)                                                       \
    {                                                                                                                                       \
        char translated_name[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_name, "%s%d:%s", basedevname, a1->unit, name);                                                                   \
        return dvrf_df_open(a1, translated_name, flags, mode);                                                                              \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_readlink(iop_file_t *a1, const char *path, char *buf, unsigned int buflen)                                        \
    {                                                                                                                                       \
        char translated_path[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_path, "%s%d:%s", basedevname, a1->unit, path);                                                                   \
        return dvrf_df_readlink(a1, translated_path, buf, buflen);                                                                          \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_remove(iop_file_t *a1, const char *name)                                                                          \
    {                                                                                                                                       \
        char translated_name[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_name, "%s%d:%s", basedevname, a1->unit, name);                                                                   \
        return dvrf_df_remove(a1, translated_name);                                                                                         \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_rename(iop_file_t *a1, const char *old, const char *new_1)                                                        \
    {                                                                                                                                       \
        char translated_old[1040];                                                                                                          \
        char translated_new[1040];                                                                                                          \
                                                                                                                                            \
        sprintf(translated_old, "%s%d:%s", basedevname, a1->unit, old);                                                                     \
        sprintf(translated_new, "%s%d:%s", basedevname, a1->unit, new_1);                                                                   \
        return dvrf_df_rename(a1, translated_old, translated_new);                                                                          \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_rmdir(iop_file_t *a1, const char *path)                                                                           \
    {                                                                                                                                       \
        char translated_path[1040];                                                                                                         \
                                                                                                                                            \
        sprintf(translated_path, "%s%d:%s", basedevname, a1->unit, path);                                                                   \
        return dvrf_df_rmdir(a1, translated_path);                                                                                          \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_symlink(iop_file_t *a1, const char *old, const char *new_1)                                                       \
    {                                                                                                                                       \
        char translated_old[1040];                                                                                                          \
        char translated_new[1040];                                                                                                          \
                                                                                                                                            \
        sprintf(translated_old, "%s%d:%s", basedevname, a1->unit, old);                                                                     \
        sprintf(translated_new, "%s%d:%s", basedevname, a1->unit, new_1);                                                                   \
        return dvrf_df_symlink(a1, translated_old, translated_new);                                                                         \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_sync(iop_file_t *a1, const char *dev, int flag)                                                                   \
    {                                                                                                                                       \
        char translated_dev[1040];                                                                                                          \
                                                                                                                                            \
        sprintf(translated_dev, "%s%d:%s", basedevname, a1->unit, dev);                                                                     \
        return dvrf_df_sync(a1, translated_dev, flag);                                                                                      \
    }                                                                                                                                       \
                                                                                                                                            \
    int basefuncname##_df_umount(iop_file_t *a1, const char *fsname)                                                                        \
    {                                                                                                                                       \
        char translated_fsname[1040];                                                                                                       \
                                                                                                                                            \
        sprintf(translated_fsname, "%s%d:%s", basedevname, a1->unit, fsname);                                                               \
        return dvrf_df_umount(a1, translated_fsname);                                                                                       \
    }

typedef struct dvrp_fd_map_struct_
{
    int dvrp_fd;
    iop_file_t *iop_fd;
} dvrp_fd_map_struct;

iop_device_ops_t DvrFuncTbl_PFS = {
    dvrf_df_init,
    dvrf_df_exit,
    dvrpfs_df_format,
    dvrpfs_df_open,
    dvrf_df_close,
    dvrf_df_read,
    dvrf_df_write,
    dvrf_df_lseek,
    dvrf_df_ioctl,
    dvrpfs_df_remove,
    dvrpfs_df_mkdir,
    dvrpfs_df_rmdir,
    dvrpfs_df_dopen,
    dvrf_df_dclose,
    dvrf_df_dread,
    dvrpfs_df_getstat,
    dvrpfs_df_chstat,
    dvrpfs_df_rename,
    dvrpfs_df_chdir,
    dvrpfs_df_sync,
    dvrpfs_df_mount,
    dvrpfs_df_umount,
    dvrf_df_lseek64,
    dvrpfs_df_devctl,
    dvrpfs_df_symlink,
    dvrpfs_df_readlink,
    dvrf_df_ioctl2,
};
iop_device_ops_t DvrFuncTbl_HDD = {
    dvrf_df_init,
    dvrf_df_exit,
    dvrhdd_df_format,
    dvrhdd_df_open,
    dvrf_df_close,
    dvrf_df_read,
    dvrf_df_write,
    dvrf_df_lseek,
    dvrf_df_ioctl,
    dvrhdd_df_remove,
    dvrhdd_df_mkdir,
    dvrhdd_df_rmdir,
    dvrhdd_df_dopen,
    dvrf_df_dclose,
    dvrf_df_dread,
    dvrhdd_df_getstat,
    dvrhdd_df_chstat,
    dvrhdd_df_rename,
    dvrhdd_df_chdir,
    dvrhdd_df_sync,
    dvrhdd_df_mount,
    dvrhdd_df_umount,
    dvrf_df_lseek64,
    dvrhdd_df_devctl,
    dvrhdd_df_symlink,
    dvrhdd_df_readlink,
    dvrf_df_ioctl2,
};
iop_device_ops_t DvrFuncTbl_HDCK = {
    dvrf_df_init,
    dvrf_df_exit,
    dvrhdck_df_format,
    dvrhdck_df_open,
    dvrf_df_close,
    dvrf_df_read,
    dvrf_df_write,
    dvrf_df_lseek,
    dvrf_df_ioctl,
    dvrhdck_df_remove,
    dvrhdck_df_mkdir,
    dvrhdck_df_rmdir,
    dvrhdck_df_dopen,
    dvrf_df_dclose,
    dvrf_df_dread,
    dvrhdck_df_getstat,
    dvrhdck_df_chstat,
    dvrhdck_df_rename,
    dvrhdck_df_chdir,
    dvrhdck_df_sync,
    dvrhdck_df_mount,
    dvrhdck_df_umount,
    dvrf_df_lseek64,
    dvrhdck_df_devctl,
    dvrhdck_df_symlink,
    dvrhdck_df_readlink,
    dvrf_df_ioctl2,
};
iop_device_ops_t DvrFuncTbl_FSSK = {
    dvrf_df_init,
    dvrf_df_exit,
    dvrfssk_df_format,
    dvrfssk_df_open,
    dvrf_df_close,
    dvrf_df_read,
    dvrf_df_write,
    dvrf_df_lseek,
    dvrf_df_ioctl,
    dvrfssk_df_remove,
    dvrfssk_df_mkdir,
    dvrfssk_df_rmdir,
    dvrfssk_df_dopen,
    dvrf_df_dclose,
    dvrf_df_dread,
    dvrfssk_df_getstat,
    dvrfssk_df_chstat,
    dvrfssk_df_rename,
    dvrfssk_df_chdir,
    dvrfssk_df_sync,
    dvrfssk_df_mount,
    dvrfssk_df_umount,
    dvrf_df_lseek64,
    dvrfssk_df_devctl,
    dvrfssk_df_symlink,
    dvrfssk_df_readlink,
    dvrf_df_ioctl2,
};
iop_device_ops_t DvrFuncTbl_FSCK = {
    dvrf_df_init,
    dvrf_df_exit,
    dvrfsck_df_format,
    dvrfsck_df_open,
    dvrf_df_close,
    dvrf_df_read,
    dvrf_df_write,
    dvrf_df_lseek,
    dvrf_df_ioctl,
    dvrfsck_df_remove,
    dvrfsck_df_mkdir,
    dvrfsck_df_rmdir,
    dvrfsck_df_dopen,
    dvrf_df_dclose,
    dvrf_df_dread,
    dvrfsck_df_getstat,
    dvrfsck_df_chstat,
    dvrfsck_df_rename,
    dvrfsck_df_chdir,
    dvrfsck_df_sync,
    dvrfsck_df_mount,
    dvrfsck_df_umount,
    dvrf_df_lseek64,
    dvrfsck_df_devctl,
    dvrfsck_df_symlink,
    dvrfsck_df_readlink,
    dvrf_df_ioctl2,
};
iop_device_t dvr_pfs_drv = {
    "dvr_pfs",
    (IOP_DT_FS | IOP_DT_FSEXT),
    1,
    "PFS Driver for DVR",
    &DvrFuncTbl_PFS};
iop_device_t dvr_hdd_drv = {
    "dvr_hdd",
    (IOP_DT_FS | IOP_DT_FSEXT),
    1,
    "HDD Driver for DVR",
    &DvrFuncTbl_HDD};
iop_device_t dvr_hdck_drv = {
    "dvr_hdck",
    (IOP_DT_FS | IOP_DT_FSEXT),
    1,
    "HDCK Driver for DVR",
    &DvrFuncTbl_HDCK};
iop_device_t dvr_fssk_drv = {
    "dvr_fssk",
    (IOP_DT_FS | IOP_DT_FSEXT),
    1,
    "FSSK Driver for DVR",
    &DvrFuncTbl_FSSK};
iop_device_t dvr_fsck_drv = {
    "dvr_fsck",
    (IOP_DT_FS | IOP_DT_FSEXT),
    1,
    "FSCK Driver for DVR",
    &DvrFuncTbl_FSCK};
s32 sema_id;
dvrp_fd_map_struct dvrp_fd_map[32];
int dvrp_fd_count;
int current_chunk_size;
int RBUF[32768];
int SBUF[32768];


int _start(int a1, const char **a2)
{
    int result;

    if (a1 >= 0)
        result = module_start(a1, a2);
    else
        result = module_stop();
    return result;
}

int module_start(int a1, const char **a2)
{
    int i;

    int v9;
    const char **v10;
    const char *v12;
    USE_SPD_REGS;

    for (i = 0; i < 30000; ++i) {
        if ((SPD_REG16(0x4230) & 0x20) != 0)
            break;
        DelayThread(1000);
    }

    if (i == 30000) {
        printf("IOMAN task of DVRP is not running...\n");
        return 1;
    }
    for (i = 0; i < 32; i += 1) {
        dvrp_fd_map[i].dvrp_fd = -1;
        dvrp_fd_map[i].iop_fd = 0;
    }
    sema_id = -1;
    current_chunk_size = 0x4000;
    dvrp_fd_count = 0;
    if (AddDrv(&dvr_pfs_drv) || AddDrv(&dvr_hdd_drv)) {
        goto LABEL_20;
    }
    v9 = 0;
    if (a1 > 0) {
        v10 = a2;
        do {
            if (!strcmp(*v10, "fschk"))
                break;
            ++v9;
            ++v10;
        } while (v9 < a1);
    }
    if (v9 == a1)
        return 2;
    printf("dvrfile.irx : FILE SYSTEM CHECK MODE\n");
    v12 = "hdck\n";
    if (AddDrv(&dvr_hdck_drv) == 0) {
        v12 = "fssk\n";
        if (AddDrv(&dvr_fssk_drv) == 0) {
            v12 = "fsck\n";
            if (AddDrv(&dvr_fsck_drv) == 0)
                return 2;
        }
    }
    printf(v12);
LABEL_20:
    DelDrv("dvr_pfs");
    DelDrv("dvr_hdd");
    DelDrv("dvr_hdck");
    DelDrv("dvr_fssk");
    DelDrv("dvr_fsck");
    return 1;
}

int module_stop()
{
    if (DelDrv("dvr_pfs") || DelDrv("dvr_hdd"))
        return 2;
    return 1;
}

static inline u32 bswap32(u32 val)
{
#if 0
    return __builtin_bswap32(val);
#else
    return (val << 24) + ((val & 0xFF00) << 8) + ((val >> 8) & 0xFF00) + ((val >> 24) & 0xFF);
#endif
}

GEN_TRANSLATION_FUNCS(dvrpfs, "dvr_pfs", 1);
GEN_TRANSLATION_FUNCS(dvrhdd, "dvr_hdd", 0);
GEN_TRANSLATION_FUNCS(dvrhdck, "dvr_hdck", 1);
GEN_TRANSLATION_FUNCS(dvrfssk, "dvr_fssk", 1);
GEN_TRANSLATION_FUNCS(dvrfsck, "dvr_fsck", 1);

int dvrf_df_init(iop_device_t *a1)
{
    int v2;
    iop_sema_t v3;

    if (sema_id >= 0)
        return 0;
    v3.attr = 0;
    v3.initial = 1;
    v3.max = 1;
    v3.option = 0;
    v2 = CreateSema(&v3);
    if (v2 < 0)
        return -1;
    sema_id = v2;
    return 0;
}

int dvrf_df_exit(iop_device_t *a1)
{
    if (sema_id < 0)
        return 0;
    if (DeleteSema(sema_id))
        return -1;
    sema_id = -1;
    return 0;
}

int dvrf_df_chdir(iop_file_t *a1, const char *name)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    strcpy((char *)SBUF, name);
    cmdack.command = 0x1101;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = strlen(name) + 1;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_chstat(iop_file_t *a1, const char *name, iox_stat_t *stat, unsigned int statmask)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    SBUF[0] = statmask;
    strcpy((char *)&SBUF[1], name);
    cmdack.command = 0x1102;
    cmdack.input_buffer = SBUF;
    cmdack.input_word_count = 2;
    cmdack.input_buffer_length = strlen(name) + 5;
    cmdack.output_buffer = RBUF;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDma2Comp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            CopySceStat(stat, (u8 *)RBUF);
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_close(iop_file_t *a1)
{
    int retval;
    int dvrp_fd;
    const char *fmterr;
    drvdrv_exec_cmd_ack cmdack;

    retval = 0;
    WaitSema(sema_id);
    cmdack.command = 0x1103;
    dvrp_fd = GetFd(a1);
    cmdack.input_word[0] = (dvrp_fd >> 16) & 0xFFFF;
    cmdack.input_word[1] = dvrp_fd;
    cmdack.input_word_count = 2;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            UnregisterFd(a1);
            --dvrp_fd_count;
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_dclose(iop_file_t *a1)
{
    int retval;
    int dvrp_fd;
    const char *fmterr;
    drvdrv_exec_cmd_ack cmdack;

    retval = 0;
    WaitSema(sema_id);
    cmdack.command = 0x1104;
    dvrp_fd = GetFd(a1);
    cmdack.input_word[0] = (dvrp_fd >> 16) & 0xFFFF;
    cmdack.input_word[1] = dvrp_fd;
    cmdack.input_word_count = 2;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            UnregisterFd(a1);
            --dvrp_fd_count;
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
    int retval;
    u32 argoffset;
    const char *fmterr;
    drvdrv_exec_cmd_ack cmdack;

    retval = 0;
    WaitSema(sema_id);
    if (cmd == 0x5065) {
        if ((*(u32 *)arg & 0x7F) != 0) {
            retval = -22;
        } else if (*(int *)arg <= 0x20000) {
            current_chunk_size = *(u32 *)arg;
        } else {
            retval = -33;
        }
        goto LABEL_18;
    }
    argoffset = arglen + 16;
    SBUF[0] = bswap32(argoffset);
    SBUF[1] = bswap32((u32)cmd);
    SBUF[2] = bswap32(buflen);
    SBUF[3] = bswap32(arglen);
    if ((int)arglen > 0)
        memcpy(&SBUF[4], arg, arglen);
    strcpy((char *)SBUF + argoffset, name);
    cmdack.input_buffer_length = argoffset + strlen(name) + 1;
    cmdack.command = 0x1105;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.output_buffer = RBUF;
    cmdack.timeout = 30000000;
    if (DvrdrvExecCmdAckDma2Comp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    LABEL_13:
        retval = -5;
        printf(fmterr, __func__, cmdack.phase);
        goto LABEL_18;
    }
    if (cmdack.comp_status) {
        fmterr = "%s -> Complete parameter error (phase %d)\n";
        goto LABEL_13;
    }
    retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
    if (!retval && buf && buflen)
        memcpy(buf, cmdack.output_buffer, buflen);
LABEL_18:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_dopen(iop_file_t *a1, const char *path)
{
    int retval;
    const char *fmterr;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    retval = -24;
    if (dvrp_fd_count < 32) {
        strcpy((char *)&SBUF, path);
        cmdack.command = 0x1106;
        cmdack.input_word_count = 0;
        cmdack.input_buffer = &SBUF;
        cmdack.input_buffer_length = strlen(path) + 1;
        cmdack.timeout = 10000000;
        if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
            fmterr = "%s -> IO error (phase %d)\n";
        LABEL_6:
            retval = -5;
            printf(fmterr, __func__, cmdack.phase);
            goto LABEL_10;
        }
        if (cmdack.comp_status) {
            fmterr = "%s -> Complete parameter error (phase %d)\n";
            goto LABEL_6;
        }
        retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
        if (retval >= 0) {
            RegisterFd(a1, retval);
            ++dvrp_fd_count;
        } else {
            printf("%s -> fd error (fd=%d)\n", __func__, retval);
        }
    }
LABEL_10:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_dread(iop_file_t *a1, iox_dirent_t *buf)
{
    int dvrp_fd;
    const char *fmterr;
    int *statbuf;
    int retval;
    iox_dirent_t *v8;
    int v12;
    iox_dirent_t *v16;
    u32 v17;
    u32 v18;
    u32 v19;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    cmdack.command = 0x1107;
    dvrp_fd = GetFd(a1);
    cmdack.input_word[0] = (dvrp_fd >> 16) & 0xFFFF;
    cmdack.input_word[1] = dvrp_fd;
    cmdack.input_word_count = 2;
    cmdack.output_buffer = RBUF;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaRecvComp(&cmdack)) {
        fmterr = "%s : IO error (phase %d)\n";
    LABEL_5:
        retval = -5;
        printf(fmterr, __func__, cmdack.phase);
        goto LABEL_14;
    }
    statbuf = (int *)RBUF;
    if (cmdack.comp_status) {
        fmterr = "%s : Complete parameter error (phase %d)\n";
        goto LABEL_5;
    }
    v8 = buf;
    do {
        v8->stat.mode = statbuf[0];
        v8->stat.attr = statbuf[1];
        v8->stat.size = statbuf[2];
        *(u32 *)v8->stat.ctime = statbuf[3];
        statbuf += 4;
        v8 = (iox_dirent_t *)((char *)v8 + 16);
    } while (statbuf != (int *)&RBUF[320]);
    v12 = 0;
    v16 = buf;
    v8->stat.mode = *statbuf;
    v17 = buf->stat.attr;
    v18 = buf->stat.size;
    buf->stat.mode = bswap32(buf->stat.mode);
    buf->stat.attr = bswap32(v17);
    v19 = buf->stat.hisize;
    buf->stat.size = bswap32(v18);
    buf->stat.hisize = bswap32(v19);
    do {
        ++v12;
        v16->stat.private_0 = bswap32(v16->stat.private_0);
        v16 = (iox_dirent_t *)((char *)v16 + 4);
    } while (v12 < 6);
    retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
LABEL_14:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_format(iop_file_t *a1, const char *dev, const char *blockdev, void *arg, int arglen)
{
    size_t blockdev_len;
    u32 dev_len;
    const char *dev_;
    u32 arg_offset;
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    dev_len = strlen(dev) + 13;
    blockdev_len = strlen(blockdev);
    dev_ = dev;
    arg_offset = dev_len + blockdev_len + 1;
    SBUF[1] = bswap32(arg_offset);
    SBUF[0] = bswap32(dev_len);
    SBUF[2] = bswap32(arglen);
    strcpy((char *)&SBUF[3], dev_);
    strcpy((char *)SBUF + dev_len, blockdev);
    memcpy((char *)SBUF + arg_offset, arg, arglen);
    cmdack.command = 0x1108;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = arg_offset + arglen;
    cmdack.timeout = 3600000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_getstat(iop_file_t *a1, const char *name, iox_stat_t *stat)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    strcpy((char *)SBUF, name);
    cmdack.command = 0x1109;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = strlen(name) + 1;
    cmdack.output_buffer = RBUF;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDma2Comp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            CopySceStat(stat, (u8 *)RBUF);
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_ioctl(iop_file_t *a1, int cmd, void *param)
{
    int dvrp_fd;
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    dvrp_fd = GetFd(a1);
    cmdack.command = 0x110A;
    cmdack.input_word[0] = (dvrp_fd >> 16) & 0xFFFF;
    cmdack.input_word[1] = dvrp_fd;
    cmdack.input_word[2] = (cmd >> 16) & 0xFFFF;
    cmdack.input_word[3] = cmd;
    cmdack.input_word[4] = ((u32)param >> 16) & 0xFFFF;
    cmdack.input_word[5] = (u32)param & 0xFFFF;
    cmdack.input_word_count = 6;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&cmdack)) {
        fmterr = "%s : IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s : Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_ioctl2(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
    int dvrp_fd;
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    dvrp_fd = GetFd(a1);
    SBUF[1] = bswap32(cmd);
    SBUF[2] = bswap32(buflen);
    SBUF[0] = bswap32(dvrp_fd);
    SBUF[3] = bswap32(arglen);
    if (arglen) {
        memcpy(((u8 *)SBUF) + 0x10, arg, arglen);
    }
    cmdack.command = 0x110B;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = arglen + 16;
    cmdack.input_word_count = 0;
    cmdack.output_buffer = RBUF;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDma2Comp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    LABEL_8:
        retval = -5;
        printf(fmterr, __func__, cmdack.phase);
        goto LABEL_12;
    }
    if (cmdack.comp_status) {
        fmterr = "%s -> Complete parameter error (phase %d)\n";
        goto LABEL_8;
    }
    retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
    if (buflen) {
        memcpy(buf, RBUF, buflen);
    }
LABEL_12:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_lseek(iop_file_t *a1, int offset, int mode)
{
    int dvrp_fd;
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    dvrp_fd = GetFd(a1);
    cmdack.command = 0x110C;
    cmdack.input_word[0] = (dvrp_fd >> 16) & 0xFFFF;
    cmdack.input_word[1] = dvrp_fd;
    cmdack.input_word[2] = (offset >> 16) & 0xFFFF;
    cmdack.input_word[3] = offset;
    cmdack.input_word[4] = (mode >> 16) & 0xFFFF;
    cmdack.input_word[5] = mode;
    cmdack.input_word_count = 6;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&cmdack)) {
        fmterr = "%s : IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s : Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

s64 dvrf_df_lseek64(iop_file_t *a1, s64 offset, int whence)
{
    int dvrp_fd;
    const char *fmterr;
    s64 retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    dvrp_fd = GetFd(a1);
    cmdack.command = 0x110D;
    cmdack.input_word[0] = (dvrp_fd >> 16) & 0xFFFF;
    cmdack.input_word[1] = dvrp_fd;
    cmdack.input_word[2] = (offset >> 48) & 0xFFFF;
    cmdack.input_word[3] = (offset >> 32) & 0xFFFF;
    cmdack.input_word[4] = (offset >> 16) & 0xFFFF;
    cmdack.input_word[5] = offset;
    cmdack.input_word[6] = (whence >> 16) & 0xFFFF;
    cmdack.input_word[7] = whence;
    cmdack.input_word_count = 8;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&cmdack)) {
        fmterr = "%s : IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = ((s64)cmdack.return_result_word[0] << 48) | ((s64)cmdack.return_result_word[1] << 32) | ((s64)cmdack.return_result_word[2] << 16) | (s64)cmdack.return_result_word[3];
            goto LABEL_7;
        }
        fmterr = "%s : Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_mkdir(iop_file_t *a1, const char *path, int mode)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    SBUF[0] = bswap32(mode);
    strcpy((char *)&SBUF[1], path);
    cmdack.command = 0x110E;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = strlen(path) + 5;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_mount(iop_file_t *a1, const char *fsname, const char *devname, int flag, void *arg, int arglen)
{
    size_t devname_len;
    u32 fsname_len;
    const char *fsname_;
    unsigned int arg_offs;
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    SBUF[0] = bswap32(flag);
    fsname_len = strlen(fsname) + 17;
    devname_len = strlen(devname);
    fsname_ = fsname;
    arg_offs = fsname_len + devname_len + 1;
    SBUF[2] = bswap32(arg_offs);
    SBUF[1] = bswap32(fsname_len);
    SBUF[3] = bswap32(arglen);
    strcpy((char *)&SBUF[4], fsname_);
    strcpy((char *)SBUF + fsname_len, devname);
    if (arglen > 0) {
        memcpy(((u8 *)SBUF) + arg_offs, arg, arglen);
    }

    cmdack.command = 0x110F;
    cmdack.input_buffer = SBUF;
    cmdack.input_word_count = 0;
    cmdack.input_buffer_length = arg_offs + arglen;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_10;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_10:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_open(iop_file_t *a1, const char *name, int flags, int mode)
{
    u16 mode_;
    int retval;
    const char *fmterr;
    drvdrv_exec_cmd_ack cmdack;

    mode_ = mode;
    WaitSema(sema_id);
    if (dvrp_fd_count >= 32) {
        retval = -24;
        goto LABEL_11;
    }
    SBUF[0] = bswap32(flags);
    mode_ = (mode_ << 8) + (mode_ >> 8);
    memcpy(&SBUF[1], &mode_, sizeof(mode_));
    strcpy((char *)&SBUF[1] + 2, name);
    cmdack.command = 0x1110;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = strlen(name) + 7;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    LABEL_7:
        retval = -5;
        printf(fmterr, __func__, cmdack.phase);
        goto LABEL_11;
    }
    if (cmdack.comp_status) {
        fmterr = "%s -> Complete parameter error (phase %d)\n";
        goto LABEL_7;
    }
    retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
    if (retval >= 0) {
        RegisterFd(a1, retval);
        ++dvrp_fd_count;
    } else {
        printf("%s -> fd error (fd=%d)\n", __func__, retval);
    }
LABEL_11:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_read(iop_file_t *a1, void *ptr, int size)
{
    size_t total_read;
    char *out_buf;
    int retval;
    int dvrp_fd;
    int remain_size;
    int unalign_size;
    int chunk_size;
    int read_size;
    drvdrv_exec_cmd_ack cmdack;

    total_read = 0;
    if (((u32)ptr & 3) != 0)
        return -14;
    WaitSema(sema_id);
    out_buf = (char *)ptr;
    if ((size & 0x7F) != 0) {
        printf("nbyte is not a multiple of 128.\n");
        out_buf = (char *)RBUF;
    }
    dvrp_fd = GetFd(a1);
    remain_size = size;
    while (1) {
        unalign_size = size & 0x7F;
        if (remain_size <= 0)
            break;
        chunk_size = current_chunk_size;
        if (remain_size < current_chunk_size)
            chunk_size = remain_size;
        cmdack.command = 0x1111;
        cmdack.input_word[0] = (dvrp_fd >> 16) & 0xFFFF;
        cmdack.input_word[1] = dvrp_fd;
        cmdack.input_word[2] = (chunk_size >> 16) & 0xFFFF;
        cmdack.input_word[3] = chunk_size;
        cmdack.input_word_count = 4;
        cmdack.output_buffer = out_buf;
        cmdack.timeout = 10000000;
        if (DvrdrvExecCmdAckDmaRecvComp(&cmdack)) {
            retval = -5;
            printf("dvrf_df_read : IO error (phase %d)\n", cmdack.phase);
            goto LABEL_19;
        }
        if (cmdack.comp_status) {
            retval = -5;
            printf("dvrf_df_read : Complete parameter error (phase %d), %04X\n", cmdack.phase, cmdack.comp_status);
            goto LABEL_19;
        }
        read_size = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
        remain_size -= read_size;
        if (read_size <= 0) {
            unalign_size = size & 0x7F;
            break;
        }
        out_buf += read_size;
        total_read += read_size;
    }
    if (unalign_size)
        memcpy(ptr, RBUF, total_read);
    retval = total_read;
LABEL_19:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_readlink(iop_file_t *a1, const char *path, char *buf, unsigned int buflen)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    SBUF[0] = bswap32(buflen);
    strcpy((char *)&SBUF[1], path);
    cmdack.input_buffer_length = strlen(path) + 5;
    cmdack.command = 0x1112;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.output_buffer = RBUF;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDma2Comp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    LABEL_5:
        retval = -5;
        printf(fmterr, __func__, cmdack.phase);
        goto LABEL_9;
    }
    if (cmdack.comp_status) {
        fmterr = "%s -> Complete parameter error (phase %d)\n";
        goto LABEL_5;
    }
    retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
    memcpy(buf, RBUF, buflen);
LABEL_9:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_remove(iop_file_t *a1, const char *name)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    strcpy((char *)SBUF, name);
    cmdack.command = 0x1113;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = strlen(name) + 1;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_rename(iop_file_t *a1, const char *old, const char *new_1)
{
    size_t old_strlen;
    const char *old_;
    size_t new_offs;
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    old_strlen = strlen(old);
    old_ = old;
    new_offs = old_strlen + 5;
    SBUF[0] = bswap32(new_offs);
    strcpy((char *)&SBUF[1], old_);
    strcpy((char *)SBUF + new_offs, new_1);
    cmdack.command = 0x1114;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = new_offs + strlen(new_1) + 1;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_rmdir(iop_file_t *a1, const char *path)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    strcpy((char *)SBUF, path);
    cmdack.command = 0x1115;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = strlen(path) + 1;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_symlink(iop_file_t *a1, const char *old, const char *new_1)
{
    size_t old_len;
    const char *old_;
    size_t new_offs;
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    old_len = strlen(old);
    old_ = old;
    new_offs = old_len + 5;
    SBUF[0] = bswap32(new_offs);
    strcpy((char *)&SBUF[1], old_);
    strcpy((char *)SBUF + new_offs, new_1);
    cmdack.command = 0x1116;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = new_offs + strlen(new_1) + 1;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_sync(iop_file_t *a1, const char *dev, int flag)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    SBUF[0] = bswap32(flag);
    strcpy((char *)&SBUF[1], dev);
    cmdack.command = 0x1117;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = strlen(dev) + 5;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_umount(iop_file_t *a1, const char *fsname)
{
    const char *fmterr;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    WaitSema(sema_id);
    strcpy((char *)SBUF, fsname);
    cmdack.command = 0x1118;
    cmdack.input_word_count = 0;
    cmdack.input_buffer = SBUF;
    cmdack.input_buffer_length = strlen(fsname) + 1;
    cmdack.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
        fmterr = "%s -> IO error (phase %d)\n";
    } else {
        if (!cmdack.comp_status) {
            retval = (cmdack.return_result_word[0] << 16) + cmdack.return_result_word[1];
            goto LABEL_7;
        }
        fmterr = "%s -> Complete parameter error (phase %d)\n";
    }
    retval = -5;
    printf(fmterr, __func__, cmdack.phase);
LABEL_7:
    SignalSema(sema_id);
    return retval;
}

int dvrf_df_write(iop_file_t *a1, void *ptr, int size)
{
    int total_write;
    char *in_buffer;
    int retval;
    const char *fmterr;
    int write_ret;
    int dvrp_fd;
    int remain_size;
    u32 chunk_size;
    int write_size_hi;
    int write_size;
    drvdrv_exec_cmd_ack cmdack;

    total_write = 0;
    in_buffer = (char *)ptr;
    if (((u32)ptr & 3) != 0) {
        printf("%s : Address is not a multiple of 4.\n", __func__);
        retval = -14;
    } else {
        WaitSema(sema_id);
        dvrp_fd = GetFd(a1);
        remain_size = size;
        while (remain_size > 0) {
            chunk_size = current_chunk_size;
            if (remain_size < current_chunk_size)
                chunk_size = remain_size;
            cmdack.command = 0x1119;
            cmdack.input_word[0] = (dvrp_fd >> 16) & 0xFFFF;
            cmdack.input_word[1] = dvrp_fd;
            cmdack.input_word[2] = (chunk_size >> 16) & 0xFFFF;
            cmdack.input_word[3] = chunk_size;
            cmdack.input_word_count = 4;
            cmdack.input_buffer = in_buffer;
            cmdack.input_buffer_length = chunk_size;
            cmdack.timeout = 10000000;
            if (DvrdrvExecCmdAckDmaSendComp(&cmdack)) {
                fmterr = "%s : IO error (phase %d)\n";
            LABEL_5:
                write_ret = -5;
                printf(fmterr, __func__, cmdack.phase);
                goto LABEL_16;
            }
            if (cmdack.comp_status) {
                fmterr = "%s : Complete parameter error (phase %d)\n";
                goto LABEL_5;
            }
            write_size_hi = cmdack.return_result_word[0] << 16;
            write_size = write_size_hi + cmdack.return_result_word[1];
            remain_size -= write_size;
            if (write_size <= 0) {
                write_ret = write_size_hi + cmdack.return_result_word[1];
                goto LABEL_16;
            }
            in_buffer += write_size;
            total_write += write_size;
        }
        write_ret = total_write;
    LABEL_16:
        SignalSema(sema_id);
        retval = write_ret;
    }
    return retval;
}

int RegisterFd(iop_file_t *a1, int a2)
{
    int i;

    for (i = 0; i < 32; i += 1) {
        if (dvrp_fd_map[i].iop_fd == 0) {
            dvrp_fd_map[i].iop_fd = a1;
            dvrp_fd_map[i].dvrp_fd = a2;
            return 0;
        }
    }
    printf("RegisterFd -> NG\n");
    return -1;
}

int UnregisterFd(iop_file_t *a1)
{
    int i;

    for (i = 0; i < 32; i += 1) {
        if (dvrp_fd_map[i].iop_fd == a1) {
            dvrp_fd_map[i].iop_fd = 0;
            dvrp_fd_map[i].dvrp_fd = -1;
            return 0;
        }
    }
    printf("UnregisterFd -> NG\n");
    return -1;
}

int GetFd(iop_file_t *a1)
{
    int i;

    for (i = 0; i < 32; i += 1) {
        if (dvrp_fd_map[i].iop_fd == a1) {
            return dvrp_fd_map[i].dvrp_fd;
        }
    }
    printf("GetFd -> NG\n");
    return -1;
}

void CopySceStat(iox_stat_t *stat, u8 *a2)
{
    stat->mode = bswap32(*(u32 *)a2);
    stat->attr = bswap32(*((u32 *)a2 + 1));
    stat->size = bswap32(*((u32 *)a2 + 2));
    *(u32 *)stat->ctime = *((u32 *)a2 + 3);
    stat->ctime[4] = a2[16];
    stat->ctime[5] = a2[17];
    *(u16 *)&stat->ctime[6] = (*((u16 *)a2 + 9) << 8) + (((u32)(*((u16 *)a2 + 9) >> 24) & 0xFF));
    *(u32 *)stat->atime = *((u32 *)a2 + 5);
    stat->atime[4] = a2[24];
    stat->atime[5] = a2[25];
    *(u16 *)&stat->atime[6] = (*((u16 *)a2 + 13) << 8) + (((u32)(*((u16 *)a2 + 13) >> 24) & 0xFF));
    *(u32 *)stat->mtime = *((u32 *)a2 + 7);
    stat->mtime[4] = a2[32];
    stat->mtime[5] = a2[33];
    *(u16 *)&stat->mtime[6] = (*((u16 *)a2 + 17) << 8) + (((u32)(*((u16 *)a2 + 17) >> 24) & 0xFF));
    stat->hisize = bswap32(*((u32 *)a2 + 9));
    stat->private_0 = bswap32(*((u32 *)a2 + 10));
    stat->private_1 = bswap32(*((u32 *)a2 + 11));
    stat->private_2 = bswap32(*((u32 *)a2 + 12));
    stat->private_3 = bswap32(*((u32 *)a2 + 13));
    stat->private_4 = bswap32(*((u32 *)a2 + 14));
    stat->private_5 = bswap32(*((u32 *)a2 + 15));
}
