



s32 irx_entry_point(s32 a1, const s8 **a2);
s32 module_start(s32 a1, const s8 **a2);
s32 module_stop();
s32 dvrf_df_init();
s32 dvrf_df_exit();
s32 dvrpfs_df_chdir(s32 a1, const s8 *a2);
s32 dvrpfs_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4);
s32 dvrpfs_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7);
s32 dvrpfs_df_dopen(s32 a1, const s8 *a2);
s32 dvrpfs_df_format(s32 a1, const s8 *a2, const s8 *a3, u32 *a4, u32 a5);
s32 dvrpfs_df_getstat(s32 a1, const s8 *a2, s32 a3);
s32 dvrpfs_df_mkdir(s32 a1, const s8 *a2, u32 a3);
s32 dvrpfs_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6);
s32 dvrpfs_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4);
s32 dvrpfs_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4);
s32 dvrpfs_df_remove(s32 a1, const s8 *a2);
s32 dvrpfs_df_rename(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrpfs_df_rmdir(s32 a1, const s8 *a2);
s32 dvrpfs_df_symlink(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrpfs_df_sync(s32 a1, const s8 *a2, u32 a3);
s32 dvrpfs_df_umount(s32 a1, const s8 *a2);
s32 dvrhdd_df_chdir(s32 a1, const s8 *a2);
s32 dvrhdd_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4);
s32 dvrhdd_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7);
s32 dvrhdd_df_dopen(s32 a1, const s8 *a2);
s32 dvrhdd_df_format(s32 a1, const s8 *a2, const s8 *a3, const void *a4, u32 a5);
s32 dvrhdd_df_getstat(s32 a1, const s8 *a2, s32 a3);
s32 dvrhdd_df_mkdir(s32 a1, const s8 *a2, u32 a3);
s32 dvrhdd_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6);
s32 dvrhdd_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4);
s32 dvrhdd_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4);
s32 dvrhdd_df_remove(s32 a1, const s8 *a2);
s32 dvrhdd_df_rename(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrhdd_df_rmdir(s32 a1, const s8 *a2);
s32 dvrhdd_df_symlink(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrhdd_df_sync(s32 a1, const s8 *a2, u32 a3);
s32 dvrhdd_df_umount(s32 a1, const s8 *a2);
s32 dvrhdck_df_chdir(s32 a1, const s8 *a2);
s32 dvrhdck_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4);
s32 dvrhdck_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7);
s32 dvrhdck_df_dopen(s32 a1, const s8 *a2);
s32 dvrhdck_df_format(s32 a1, const s8 *a2, const s8 *a3, u32 *a4, u32 a5);
s32 dvrhdck_df_getstat(s32 a1, const s8 *a2, s32 a3);
s32 dvrhdck_df_mkdir(s32 a1, const s8 *a2, u32 a3);
s32 dvrhdck_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6);
s32 dvrhdck_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4);
s32 dvrhdck_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4);
s32 dvrhdck_df_remove(s32 a1, const s8 *a2);
s32 dvrhdck_df_rename(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrhdck_df_rmdir(s32 a1, const s8 *a2);
s32 dvrhdck_df_symlink(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrhdck_df_sync(s32 a1, const s8 *a2, u32 a3);
s32 dvrhdck_df_umount(s32 a1, const s8 *a2);
s32 dvrfssk_df_chdir(s32 a1, const s8 *a2);
s32 dvrfssk_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4);
s32 dvrfssk_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7);
s32 dvrfssk_df_dopen(s32 a1, const s8 *a2);
s32 dvrfssk_df_format(s32 a1, const s8 *a2, const s8 *a3, u32 *a4, u32 a5);
s32 dvrfssk_df_getstat(s32 a1, const s8 *a2, s32 a3);
s32 dvrfssk_df_mkdir(s32 a1, const s8 *a2, u32 a3);
s32 dvrfssk_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6);
s32 dvrfssk_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4);
s32 dvrfssk_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4);
s32 dvrfssk_df_remove(s32 a1, const s8 *a2);
s32 dvrfssk_df_rename(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrfssk_df_rmdir(s32 a1, const s8 *a2);
s32 dvrfssk_df_symlink(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrfssk_df_sync(s32 a1, const s8 *a2, u32 a3);
s32 dvrfssk_df_umount(s32 a1, const s8 *a2);
s32 dvrfsck_df_chdir(s32 a1, const s8 *a2);
s32 dvrfsck_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4);
s32 dvrfsck_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7);
s32 dvrfsck_df_dopen(s32 a1, const s8 *a2);
s32 dvrfsck_df_format(s32 a1, const s8 *a2, const s8 *a3, u32 *a4, u32 a5);
s32 dvrfsck_df_getstat(s32 a1, const s8 *a2, s32 a3);
s32 dvrfsck_df_mkdir(s32 a1, const s8 *a2, u32 a3);
s32 dvrfsck_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6);
s32 dvrfsck_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4);
s32 dvrfsck_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4);
s32 dvrfsck_df_remove(s32 a1, const s8 *a2);
s32 dvrfsck_df_rename(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrfsck_df_rmdir(s32 a1, const s8 *a2);
s32 dvrfsck_df_symlink(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrfsck_df_sync(s32 a1, const s8 *a2, u32 a3);
s32 dvrfsck_df_umount(s32 a1, const s8 *a2);
s32 dvrf_df_chdir(s32 a1, const s8 *a2);
s32 dvrf_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4);
s32 dvrf_df_close(s32 a1);
s32 dvrf_df_dclose(s32 a1);
s32 dvrf_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7);
s32 dvrf_df_dopen(s32 a1, const s8 *a2);
s32 dvrf_df_dread(s32 a1, s32 *a2);
s32 dvrf_df_format(s32 a1, const s8 *a2, const s8 *a3, const void *a4, u32 a5);
s32 dvrf_df_getstat(s32 a1, const s8 *a2, s32 a3);
s32 dvrf_df_ioctl(s32 a1, s32 a2, s32 a3);
s32 dvrf_df_ioctl2(s32 a1, u32 a2, u8 *a3, u32 a4, u8 *a5, u32 a6);
s32 dvrf_df_lseek(s32 a1, s32 a2, s32 a3);
unsigned __int64 dvrf_df_lseek64(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
s32 dvrf_df_mkdir(s32 a1, const s8 *a2, u32 a3);
s32 dvrf_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6);
s32 dvrf_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4);
s32 dvrf_df_read(s32 a1, s8 *a2, s32 a3);
s32 dvrf_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4);
s32 dvrf_df_remove(s32 a1, const s8 *a2);
s32 dvrf_df_rename(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrf_df_rmdir(s32 a1, const s8 *a2);
s32 dvrf_df_symlink(s32 a1, const s8 *a2, const s8 *a3);
s32 dvrf_df_sync(s32 a1, const s8 *a2, u32 a3);
s32 dvrf_df_umount(s32 a1, const s8 *a2);
s32 dvrf_df_write(s32 a1, u32 a2, s32 a3);
s32 RegisterFd(s32 a1, s32 a2);
s32 UnregisterFd(s32 a1);
s32 GetFd(s32 a1);
s32 CopySceStat(s32 a1, s32 a2);
s32 DvrdrvExecCmdAckComp(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDmaRecvComp(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDma2Comp(drvdrv_exec_cmd_ack *a1);
s32 AddDrv(iop_device_t *device);
s32 DelDrv(const s8 *name);
s32 printf(const s8 *format, ...);
void *memcpy(void *dest, const void *src, size_t size);
s32 sprintf(s8 *str, const s8 *format, ...);
s32 strcmp(const s8 *p, const s8 *q);
s8 *strcpy(s8 *dest, const s8 *src);
size_t strlen(const s8 *s);
s32 DelayThread(s32 usec);
s32 CreateSema(iop_sema_t *sema);
s32 DeleteSema(s32 sema_id);
s32 SignalSema(s32 sema_id);
s32 WaitSema(s32 sema_id);


s32 (*DvrFuncTbl_PFS[2])() = {&dvrf_df_init, &dvrf_df_exit};
s32 (*DvrFuncTbl_HDD[2])() = {&dvrf_df_init, &dvrf_df_exit};
s32 (*DvrFuncTbl_HDCK[2])() = {&dvrf_df_init, &dvrf_df_exit};
s32 (*DvrFuncTbl_FSSK[2])() = {&dvrf_df_init, &dvrf_df_exit};
s32 (*DvrFuncTbl_FSCK[2])() = {&dvrf_df_init, &dvrf_df_exit};
s32 DVRFILE;
s32 dword_5804;
s32 dword_580C;
s32 dword_5810;
s32 dword_5814;
s32 dword_5818;
s32 dword_5820;
s32 dword_5824;
s32 dword_5828;
s32 dword_582C;
s32 dword_5834;
s32 dword_5838;
s32 dword_583C;
s32 dword_5840;
s32 dword_5848;
s32 dword_584C;
s32 dword_5850;
s32 dword_5854;
s32 dword_585C;
s32 dword_5860;
s32 sema_id;
s32 dword_5868[];
s32 dword_586C[];
s32 dword_5968;
s32 dword_596C;
s8 RBUF;
s32 dword_5AB0[32688];
s32 SBUF;
s32 dword_25974;
s32 dword_25978;
s32 dword_2597C;
s8 byte_25980;


s32 irx_entry_point(s32 a1, const s8 **a2)
{
    s32 result;

    if (a1 >= 0)
        result = module_start(a1, a2);
    else
        result = module_stop();
    return result;
}

s32 module_start(s32 a1, const s8 **a2)
{
    s32 i;
    bool v5;
    s32 v6;
    s32 result;
    s32 v8;
    s32 v9;
    const s8 **v10;
    s32 v11;
    const s8 *v12;
    s32 v13;

    for (i = 0; i < 30000; ++i) {
        if (((*((vu32 *)0xB0004230)) & 0x20) != 0)
            break;
        DelayThread(1000);
    }
    v5 = i != 30000;
    v6 = 0;
    if (!v5) {
        printf("IOMAN task of DVRP is not running...\n");
        return 1;
    }
    v8 = 0;
    do {
        ++v6;
        *(u32 *)(v8 + 22632) = -1;
        *(u32 *)(v8 + 22636) = 0;
        v8 = 8 * v6;
    } while (v6 < 32);
    sema_id = -1;
    dword_596C = 0x4000;
    dword_5810 = (s32)DvrFuncTbl_PFS;
    DVRFILE = (s32) "dvr_pfs";
    dword_5968 = 0;
    dword_5804 = 268435472;
    dword_580C = (s32) "PFS Driver for DVR";
    if (AddDrv((iop_device_t *)&DVRFILE) || (dword_5824 = (s32)DvrFuncTbl_HDD,
                                             dword_5814 = (s32) "dvr_hdd",
                                             dword_5818 = 268435472,
                                             dword_5820 = (s32) "HDD Driver for DVR",
                                             AddDrv((iop_device_t *)&dword_5814))) {
    LABEL_20:
        DelDrv("dvr_pfs");
        DelDrv("dvr_hdd");
        DelDrv("dvr_hdck");
        DelDrv("dvr_fssk");
        DelDrv("dvr_fsck");
        return 1;
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
    result = 2;
    if (v9 == a1)
        return result;
    printf("dvrfile.irx : FILE SYSTEM CHECK MODE\n");
    dword_5838 = (s32)DvrFuncTbl_HDCK;
    dword_5828 = (s32) "dvr_hdck";
    dword_582C = 268435472;
    dword_5834 = (s32) "HDCK Driver for DVR";
    v11 = AddDrv((iop_device_t *)&dword_5828);
    v12 = "hdck\n";
    if (!v11) {
        dword_584C = (s32)DvrFuncTbl_FSSK;
        dword_583C = (s32) "dvr_fssk";
        dword_5840 = 268435472;
        dword_5848 = (s32) "FSSK Driver for DVR";
        v13 = AddDrv((iop_device_t *)&dword_583C);
        v12 = "fssk\n";
        if (!v13) {
            dword_5860 = (s32)DvrFuncTbl_FSCK;
            dword_5850 = (s32) "dvr_fsck";
            dword_5854 = 268435472;
            dword_585C = (s32) "FSCK Driver for DVR";
            v5 = AddDrv((iop_device_t *)&dword_5850) == 0;
            result = 2;
            if (v5)
                return result;
            v12 = "fsck\n";
        }
    }
    printf(v12);
    goto LABEL_20;
}

s32 module_stop()
{
    bool v0;
    s32 result;

    if (DelDrv("dvr_pfs") || (v0 = DelDrv("dvr_hdd") == 0, result = 1, !v0))
        result = 2;
    return result;
}

s32 dvrf_df_init()
{
    s32 result;
    s32 v1;
    iop_sema_t v2;

    result = 0;
    if (sema_id >= 0)
        return result;
    v2.attr = 0;
    v2.initial = 1;
    v2.max = 1;
    v2.option = 0;
    v1 = CreateSema(&v2);
    if (v1 < 0)
        return -1;
    sema_id = v1;
    return 0;
}

s32 dvrf_df_exit()
{
    s32 result;
    bool v1;

    result = 0;
    if (sema_id < 0)
        return result;
    v1 = DeleteSema(sema_id) != 0;
    result = -1;
    if (v1)
        return result;
    sema_id = -1;
    return 0;
}

s32 dvrpfs_df_chdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chdir(a1, v4);
}

s32 dvrpfs_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chstat(a1, v8, a3, a4);
}

s32 dvrpfs_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7)
{
    s8 v11[1040];

    sprintf(v11, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_devctl(a1, v11, a3, a4, a5, a6, a7);
}

s32 dvrpfs_df_dopen(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_dopen(a1, v4);
}

s32 dvrpfs_df_format(s32 a1, const s8 *a2, const s8 *a3, u32 *a4, u32 a5)
{
    s8 v9[1040];

    sprintf(v9, "dvr_pfs:%s", a2);
    *a4 = (*a4 << 24) + ((*a4 & 0xFF00) << 8) + ((*a4 >> 8) & 0xFF00) + HIBYTE(*a4);
    return dvrf_df_format(a1, v9, a3, a4, a5);
}

s32 dvrpfs_df_getstat(s32 a1, const s8 *a2, s32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_getstat(a1, v6, a3);
}

s32 dvrpfs_df_mkdir(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mkdir(a1, v6, a3);
}

s32 dvrpfs_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6)
{
    s8 v10[1040];

    sprintf(v10, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mount(a1, v10, a3, a4, a5, a6);
}

s32 dvrpfs_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_open(a1, v8, a3, a4);
}

s32 dvrpfs_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_readlink(a1, v8, a3, a4);
}

s32 dvrpfs_df_remove(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_remove(a1, v4);
}

s32 dvrpfs_df_rename(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_rename(a1, v6, v7);
}

s32 dvrpfs_df_rmdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_rmdir(a1, v4);
}

s32 dvrpfs_df_symlink(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_symlink(a1, v6, v7);
}

s32 dvrpfs_df_sync(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_sync(a1, v6, a3);
}

s32 dvrpfs_df_umount(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_pfs%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_umount(a1, v4);
}

s32 dvrhdd_df_chdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chdir(a1, v4);
}

s32 dvrhdd_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chstat(a1, v8, a3, a4);
}

s32 dvrhdd_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7)
{
    s8 v11[1040];

    sprintf(v11, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_devctl(a1, v11, a3, a4, a5, a6, a7);
}

s32 dvrhdd_df_dopen(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_dopen(a1, v4);
}

s32 dvrhdd_df_format(s32 a1, const s8 *a2, const s8 *a3, const void *a4, u32 a5)
{
    s8 v9[1040];

    sprintf(v9, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_format(a1, v9, a3, a4, a5);
}

s32 dvrhdd_df_getstat(s32 a1, const s8 *a2, s32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_getstat(a1, v6, a3);
}

s32 dvrhdd_df_mkdir(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mkdir(a1, v6, a3);
}

s32 dvrhdd_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6)
{
    s8 v10[1040];

    sprintf(v10, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mount(a1, v10, a3, a4, a5, a6);
}

s32 dvrhdd_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_open(a1, v8, a3, a4);
}

s32 dvrhdd_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_readlink(a1, v8, a3, a4);
}

s32 dvrhdd_df_remove(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_remove(a1, v4);
}

s32 dvrhdd_df_rename(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_rename(a1, v6, v7);
}

s32 dvrhdd_df_rmdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_rmdir(a1, v4);
}

s32 dvrhdd_df_symlink(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_symlink(a1, v6, v7);
}

s32 dvrhdd_df_sync(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_sync(a1, v6, a3);
}

s32 dvrhdd_df_umount(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdd%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_umount(a1, v4);
}

s32 dvrhdck_df_chdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chdir(a1, v4);
}

s32 dvrhdck_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chstat(a1, v8, a3, a4);
}

s32 dvrhdck_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7)
{
    s8 v11[1040];

    sprintf(v11, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_devctl(a1, v11, a3, a4, a5, a6, a7);
}

s32 dvrhdck_df_dopen(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_dopen(a1, v4);
}

s32 dvrhdck_df_format(s32 a1, const s8 *a2, const s8 *a3, u32 *a4, u32 a5)
{
    s8 v9[1040];

    sprintf(v9, "dvr_hdck:%s", a2);
    *a4 = (*a4 << 24) + ((*a4 & 0xFF00) << 8) + ((*a4 >> 8) & 0xFF00) + HIBYTE(*a4);
    return dvrf_df_format(a1, v9, a3, a4, a5);
}

s32 dvrhdck_df_getstat(s32 a1, const s8 *a2, s32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_getstat(a1, v6, a3);
}

s32 dvrhdck_df_mkdir(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mkdir(a1, v6, a3);
}

s32 dvrhdck_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6)
{
    s8 v10[1040];

    sprintf(v10, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mount(a1, v10, a3, a4, a5, a6);
}

s32 dvrhdck_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_open(a1, v8, a3, a4);
}

s32 dvrhdck_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_readlink(a1, v8, a3, a4);
}

s32 dvrhdck_df_remove(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_remove(a1, v4);
}

s32 dvrhdck_df_rename(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_rename(a1, v6, v7);
}

s32 dvrhdck_df_rmdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_rmdir(a1, v4);
}

s32 dvrhdck_df_symlink(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_symlink(a1, v6, v7);
}

s32 dvrhdck_df_sync(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_sync(a1, v6, a3);
}

s32 dvrhdck_df_umount(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_hdck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_umount(a1, v4);
}

s32 dvrfssk_df_chdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chdir(a1, v4);
}

s32 dvrfssk_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chstat(a1, v8, a3, a4);
}

s32 dvrfssk_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7)
{
    s8 v11[1040];

    sprintf(v11, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_devctl(a1, v11, a3, a4, a5, a6, a7);
}

s32 dvrfssk_df_dopen(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_dopen(a1, v4);
}

s32 dvrfssk_df_format(s32 a1, const s8 *a2, const s8 *a3, u32 *a4, u32 a5)
{
    s8 v9[1040];

    sprintf(v9, "dvr_fssk:%s", a2);
    *a4 = (*a4 << 24) + ((*a4 & 0xFF00) << 8) + ((*a4 >> 8) & 0xFF00) + HIBYTE(*a4);
    return dvrf_df_format(a1, v9, a3, a4, a5);
}

s32 dvrfssk_df_getstat(s32 a1, const s8 *a2, s32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_getstat(a1, v6, a3);
}

s32 dvrfssk_df_mkdir(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mkdir(a1, v6, a3);
}

s32 dvrfssk_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6)
{
    s8 v10[1040];

    sprintf(v10, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mount(a1, v10, a3, a4, a5, a6);
}

s32 dvrfssk_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_open(a1, v8, a3, a4);
}

s32 dvrfssk_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_readlink(a1, v8, a3, a4);
}

s32 dvrfssk_df_remove(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_remove(a1, v4);
}

s32 dvrfssk_df_rename(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_rename(a1, v6, v7);
}

s32 dvrfssk_df_rmdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_rmdir(a1, v4);
}

s32 dvrfssk_df_symlink(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_symlink(a1, v6, v7);
}

s32 dvrfssk_df_sync(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_sync(a1, v6, a3);
}

s32 dvrfssk_df_umount(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fssk%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_umount(a1, v4);
}

s32 dvrfsck_df_chdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chdir(a1, v4);
}

s32 dvrfsck_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_chstat(a1, v8, a3, a4);
}

s32 dvrfsck_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7)
{
    s8 v11[1040];

    sprintf(v11, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_devctl(a1, v11, a3, a4, a5, a6, a7);
}

s32 dvrfsck_df_dopen(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_dopen(a1, v4);
}

s32 dvrfsck_df_format(s32 a1, const s8 *a2, const s8 *a3, u32 *a4, u32 a5)
{
    s8 v9[1040];

    sprintf(v9, "dvr_fsck:%s", a2);
    *a4 = (*a4 << 24) + ((*a4 & 0xFF00) << 8) + ((*a4 >> 8) & 0xFF00) + HIBYTE(*a4);
    return dvrf_df_format(a1, v9, a3, a4, a5);
}

s32 dvrfsck_df_getstat(s32 a1, const s8 *a2, s32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_getstat(a1, v6, a3);
}

s32 dvrfsck_df_mkdir(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mkdir(a1, v6, a3);
}

s32 dvrfsck_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6)
{
    s8 v10[1040];

    sprintf(v10, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_mount(a1, v10, a3, a4, a5, a6);
}

s32 dvrfsck_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_open(a1, v8, a3, a4);
}

s32 dvrfsck_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4)
{
    s8 v8[1040];

    sprintf(v8, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_readlink(a1, v8, a3, a4);
}

s32 dvrfsck_df_remove(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_remove(a1, v4);
}

s32 dvrfsck_df_rename(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_rename(a1, v6, v7);
}

s32 dvrfsck_df_rmdir(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_rmdir(a1, v4);
}

s32 dvrfsck_df_symlink(s32 a1, const s8 *a2, const s8 *a3)
{
    s8 v6[1040];
    s8 v7[1040];

    sprintf(v6, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    sprintf(v7, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a3);
    return dvrf_df_symlink(a1, v6, v7);
}

s32 dvrfsck_df_sync(s32 a1, const s8 *a2, u32 a3)
{
    s8 v6[1040];

    sprintf(v6, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_sync(a1, v6, a3);
}

s32 dvrfsck_df_umount(s32 a1, const s8 *a2)
{
    s8 v4[1040];

    sprintf(v4, "dvr_fsck%d:%s", *(u32 *)(a1 + 4), a2);
    return dvrf_df_umount(a1, v4);
}

s32 dvrf_df_chdir(s32 a1, const s8 *a2)
{
    const s8 *v3;
    s32 v4;
    drvdrv_exec_cmd_ack v6;

    WaitSema(sema_id);
    strcpy((s8 *)&SBUF, a2);
    v6.command = 4353;
    v6.input_word_count = 0;
    v6.input_buffer = (u32)&SBUF;
    v6.input_buffer_length = strlen(a2) + 1;
    v6.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v6)) {
        v3 = "dvrf_df_chdir -> IO error (phase %d)\n";
    } else {
        if (!v6.comp_status) {
            v4 = (v6.return_result_word[0] << 16) + v6.return_result_word[1];
            goto LABEL_7;
        }
        v3 = "dvrf_df_chdir -> Complete parameter error (phase %d)\n";
    }
    v4 = -5;
    printf(v3, v6.phase);
LABEL_7:
    SignalSema(sema_id);
    return v4;
}

s32 dvrf_df_chstat(s32 a1, const s8 *a2, s32 a3, s32 a4)
{
    const s8 *v7;
    s32 v8;
    drvdrv_exec_cmd_ack v10;

    WaitSema(sema_id);
    SBUF = a4;
    strcpy((s8 *)&dword_25974, a2);
    v10.command = 4354;
    v10.input_buffer = (u32)&SBUF;
    v10.input_word_count = 2;
    v10.input_buffer_length = strlen(a2) + 5;
    v10.output_buffer = (u32)&RBUF;
    v10.timeout = 10000000;
    if (DvrdrvExecCmdAckDma2Comp(&v10)) {
        v7 = "dvrf_df_chstat -> IO error (phase %d)\n";
    } else {
        if (!v10.comp_status) {
            v8 = (v10.return_result_word[0] << 16) + v10.return_result_word[1];
            CopySceStat(a3, (s32)&RBUF);
            goto LABEL_7;
        }
        v7 = "dvrf_df_chstat -> Complete parameter error (phase %d)\n";
    }
    v8 = -5;
    printf(v7, v10.phase);
LABEL_7:
    SignalSema(sema_id);
    return v8;
}

s32 dvrf_df_close(s32 a1)
{
    s32 v2;
    s32 v3;
    const s8 *v4;
    drvdrv_exec_cmd_ack v6;

    v2 = 0;
    WaitSema(sema_id);
    v6.command = 4355;
    v3 = GetFd(a1);
    v6.input_word[0] = HIWORD(v3);
    v6.input_word[1] = v3;
    v6.input_word_count = 2;
    v6.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&v6)) {
        v4 = "dvrf_df_close -> IO error (phase %d)\n";
    } else {
        if (!v6.comp_status) {
            UnregisterFd(a1);
            --dword_5968;
            goto LABEL_7;
        }
        v4 = "dvrf_df_close -> Complete parameter (phase %d)\n";
    }
    v2 = -5;
    printf(v4, v6.phase);
LABEL_7:
    SignalSema(sema_id);
    return v2;
}

s32 dvrf_df_dclose(s32 a1)
{
    s32 v2;
    s32 v3;
    const s8 *v4;
    drvdrv_exec_cmd_ack v6;

    v2 = 0;
    WaitSema(sema_id);
    v6.command = 4356;
    v3 = GetFd(a1);
    v6.input_word[0] = HIWORD(v3);
    v6.input_word[1] = v3;
    v6.input_word_count = 2;
    v6.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&v6)) {
        v4 = "dvrf_df_dclose -> IO error (phase %d)\n";
    } else {
        if (!v6.comp_status) {
            UnregisterFd(a1);
            --dword_5968;
            goto LABEL_7;
        }
        v4 = "dvrf_df_dclose -> Complete parameter (phase %d)\n";
    }
    v2 = -5;
    printf(v4, v6.phase);
LABEL_7:
    SignalSema(sema_id);
    return v2;
}

s32 dvrf_df_devctl(s32 a1, const s8 *a2, u32 a3, s32 *a4, size_t a5, void *a6, u32 a7)
{
    s32 v10;
    size_t v11;
    const s8 *v12;
    drvdrv_exec_cmd_ack v14;

    v10 = 0;
    WaitSema(sema_id);
    if (a3 == 20581) {
        if ((*a4 & 0x7F) != 0) {
            v10 = -22;
        } else if (*a4 <= 0x20000) {
            dword_596C = *a4;
        } else {
            v10 = -33;
        }
        goto LABEL_18;
    }
    v11 = a5 + 16;
    SBUF = ((a5 + 16) << 24) + (((a5 + 16) & 0xFF00) << 8) + (((a5 + 16) & 0xFF0000) >> 8) + ((u32)(a5 + 16) >> 24);
    dword_25974 = (a3 << 24) + ((a3 & 0xFF00) << 8) + ((s32)(a3 & 0xFF0000) >> 8) + HIBYTE(a3);
    dword_25978 = (a7 << 24) + ((a7 & 0xFF00) << 8) + ((a7 & 0xFF0000) >> 8) + HIBYTE(a7);
    dword_2597C = (a5 << 24) + ((a5 & 0xFF00) << 8) + ((a5 & 0xFF0000) >> 8) + HIBYTE(a5);
    if (a5 > 0)
        memcpy(&byte_25980, a4, a5);
    strcpy((s8 *)&SBUF + v11, a2);
    v14.input_buffer_length = v11 + strlen(a2) + 1;
    v14.command = 4357;
    v14.input_word_count = 0;
    v14.input_buffer = (u32)&SBUF;
    v14.output_buffer = (u32)&RBUF;
    v14.timeout = 30000000;
    if (DvrdrvExecCmdAckDma2Comp(&v14)) {
        v12 = "dvrf_df_devctl -> IO error (phase %d)\n";
    LABEL_13:
        v10 = -5;
        printf(v12, v14.phase);
        goto LABEL_18;
    }
    if (v14.comp_status) {
        v12 = "dvrf_df_devctl -> Complete parameter error (phase %d)\n";
        goto LABEL_13;
    }
    v10 = (v14.return_result_word[0] << 16) + v14.return_result_word[1];
    if (!v10 && a6 && a7)
        memcpy(a6, (const void *)v14.output_buffer, a7);
LABEL_18:
    SignalSema(sema_id);
    return v10;
}

s32 dvrf_df_dopen(s32 a1, const s8 *a2)
{
    s32 v4;
    const s8 *v5;
    s32 v6;
    drvdrv_exec_cmd_ack v8;

    WaitSema(sema_id);
    v4 = -24;
    if (dword_5968 < 32) {
        strcpy((s8 *)&SBUF, a2);
        v8.command = 4358;
        v8.input_word_count = 0;
        v8.input_buffer = (u32)&SBUF;
        v8.input_buffer_length = strlen(a2) + 1;
        v8.timeout = 10000000;
        if (DvrdrvExecCmdAckDmaSendComp(&v8)) {
            v5 = "dvrf_df_dopen -> IO error (phase %d)\n";
        LABEL_6:
            v4 = -5;
            printf(v5, v8.phase);
            goto LABEL_10;
        }
        if (v8.comp_status) {
            v5 = "dvrf_df_dopen -> Complete parameter error (phase %d)\n";
            goto LABEL_6;
        }
        v6 = v8.return_result_word[0] << 16;
        v4 = v6 + v8.return_result_word[1];
        if (v4 >= 0) {
            RegisterFd(a1, v6 + v8.return_result_word[1]);
            ++dword_5968;
        } else {
            printf("dvrf_df_dopen -> fd error (fd=%d)\n", v6 + v8.return_result_word[1]);
        }
    }
LABEL_10:
    SignalSema(sema_id);
    return v4;
}

s32 dvrf_df_dread(s32 a1, s32 *a2)
{
    s32 v4;
    const s8 *v5;
    s32 *v6;
    s32 v7;
    s32 *v8;
    s32 v9;
    s32 v10;
    s32 v11;
    s32 v12;
    s32 v13;
    s32 v14;
    s32 v15;
    s32 *v16;
    u32 v17;
    u32 v18;
    u32 v19;
    drvdrv_exec_cmd_ack v21;

    WaitSema(sema_id);
    v21.command = 4359;
    v4 = GetFd(a1);
    v21.input_word[0] = HIWORD(v4);
    v21.input_word[1] = v4;
    v21.input_word_count = 2;
    v21.output_buffer = (u32)&RBUF;
    v21.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaRecvComp(&v21)) {
        v5 = "dvrf_df_dread : IO error (phase %d)\n";
    LABEL_5:
        v7 = -5;
        printf(v5, v21.phase);
        goto LABEL_14;
    }
    v6 = (s32 *)&RBUF;
    if (v21.comp_status) {
        v5 = "dvrf_df_dread : Complete parameter error (phase %d)\n";
        goto LABEL_5;
    }
    v8 = a2;
    if ((((u8)a2 | (u8)&RBUF) & 3) != 0) {
        do {
            v9 = v6[1];
            v10 = v6[2];
            v11 = v6[3];
            *v8 = *v6;
            v8[1] = v9;
            v8[2] = v10;
            v8[3] = v11;
            v6 += 4;
            v8 += 4;
        } while (v6 != dword_5AB0);
        v12 = 0;
    } else {
        do {
            v13 = v6[1];
            v14 = v6[2];
            v15 = v6[3];
            *v8 = *v6;
            v8[1] = v13;
            v8[2] = v14;
            v8[3] = v15;
            v6 += 4;
            v8 += 4;
        } while (v6 != dword_5AB0);
        v12 = 0;
    }
    v16 = a2;
    *v8 = *v6;
    v17 = a2[1];
    v18 = a2[2];
    *a2 = (*a2 << 24) + ((*a2 & 0xFF00) << 8) + ((*a2 & 0xFF0000u) >> 8) + HIBYTE(*a2);
    a2[1] = (v17 << 24) + ((v17 & 0xFF00) << 8) + ((v17 & 0xFF0000) >> 8) + HIBYTE(v17);
    v19 = a2[9];
    a2[2] = (v18 << 24) + ((v18 & 0xFF00) << 8) + ((v18 & 0xFF0000) >> 8) + HIBYTE(v18);
    a2[9] = (v19 << 24) + ((v19 & 0xFF00) << 8) + ((v19 & 0xFF0000) >> 8) + HIBYTE(v19);
    do {
        ++v12;
        v16[10] = (v16[10] << 24) + ((v16[10] & 0xFF00) << 8) + ((v16[10] & 0xFF0000u) >> 8) + HIBYTE(v16[10]);
        ++v16;
    } while (v12 < 6);
    v7 = (v21.return_result_word[0] << 16) + v21.return_result_word[1];
LABEL_14:
    SignalSema(sema_id);
    return v7;
}

s32 dvrf_df_format(s32 a1, const s8 *a2, const s8 *a3, const void *a4, u32 a5)
{
    size_t v8;
    u32 v9;
    const s8 *v10;
    u32 v11;
    const s8 *v12;
    s32 v13;
    drvdrv_exec_cmd_ack v15;

    WaitSema(sema_id);
    v9 = strlen(a2) + 13;
    v8 = strlen(a3);
    v10 = a2;
    v11 = v9 + v8 + 1;
    dword_25974 = (v11 << 24) + ((v11 & 0xFF00) << 8) + ((s32)(v11 & 0xFF0000) >> 8) + HIBYTE(v11);
    SBUF = (v9 << 24) + ((v9 & 0xFF00) << 8) + ((s32)(v9 & 0xFF0000) >> 8) + HIBYTE(v9);
    dword_25978 = (a5 << 24) + ((a5 & 0xFF00) << 8) + ((s32)(a5 & 0xFF0000) >> 8) + HIBYTE(a5);
    strcpy((s8 *)&dword_2597C, v10);
    strcpy((s8 *)&SBUF + v9, a3);
    memcpy((s8 *)&SBUF + v11, a4, a5);
    v15.command = 4360;
    v15.input_word_count = 0;
    v15.input_buffer = (u32)&SBUF;
    v15.input_buffer_length = v11 + a5;
    v15.timeout = -694967296;
    if (DvrdrvExecCmdAckDmaSendComp(&v15)) {
        v12 = "dvrf_df_format -> IO error (phase %d)\n";
    } else {
        if (!v15.comp_status) {
            v13 = (v15.return_result_word[0] << 16) + v15.return_result_word[1];
            goto LABEL_7;
        }
        v12 = "dvrf_df_format -> Complete parameter error (phase %d)\n";
    }
    v13 = -5;
    printf(v12, v15.phase);
LABEL_7:
    SignalSema(sema_id);
    return v13;
}

s32 dvrf_df_getstat(s32 a1, const s8 *a2, s32 a3)
{
    const s8 *v5;
    s32 v6;
    drvdrv_exec_cmd_ack v8;

    WaitSema(sema_id);
    strcpy((s8 *)&SBUF, a2);
    v8.command = 4361;
    v8.input_word_count = 0;
    v8.input_buffer = (u32)&SBUF;
    v8.input_buffer_length = strlen(a2) + 1;
    v8.output_buffer = (u32)&RBUF;
    v8.timeout = 10000000;
    if (DvrdrvExecCmdAckDma2Comp(&v8)) {
        v5 = "dvrf_df_getstat -> IO error (phase %d)\n";
    } else {
        if (!v8.comp_status) {
            v6 = (v8.return_result_word[0] << 16) + v8.return_result_word[1];
            CopySceStat(a3, (s32)&RBUF);
            goto LABEL_7;
        }
        v5 = "dvrf_df_getstat -> Complete parameter error (phase %d)\n";
    }
    v6 = -5;
    printf(v5, v8.phase);
LABEL_7:
    SignalSema(sema_id);
    return v6;
}

s32 dvrf_df_ioctl(s32 a1, s32 a2, s32 a3)
{
    s32 v6;
    const s8 *v7;
    s32 v8;
    drvdrv_exec_cmd_ack v10;

    WaitSema(sema_id);
    v6 = GetFd(a1);
    v10.command = 4362;
    v10.input_word[1] = v6;
    v10.input_word[2] = HIWORD(a2);
    v10.input_word[4] = HIWORD(a3);
    v10.input_word[0] = HIWORD(v6);
    v10.input_word[3] = a2;
    v10.input_word[5] = a3;
    v10.input_word_count = 6;
    v10.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&v10)) {
        v7 = "dvrf_df_ioctl : IO error (phase %d)\n";
    } else {
        if (!v10.comp_status) {
            v8 = (v10.return_result_word[0] << 16) + v10.return_result_word[1];
            goto LABEL_7;
        }
        v7 = "dvrf_df_ioctl : Complete parameter error (phase %d)\n";
    }
    v8 = -5;
    printf(v7, v10.phase);
LABEL_7:
    SignalSema(sema_id);
    return v8;
}

s32 dvrf_df_ioctl2(s32 a1, u32 a2, u8 *a3, u32 a4, u8 *a5, u32 a6)
{
    u32 v10;
    u32 v11;
    u8 *v12;
    const s8 *v13;
    u32 v14;
    s32 v15;
    u8 *v16;
    s8 v17;
    drvdrv_exec_cmd_ack v19;

    WaitSema(sema_id);
    v10 = GetFd(a1);
    v11 = 0;
    dword_25974 = (a2 << 24) + ((a2 & 0xFF00) << 8) + ((s32)(a2 & 0xFF0000) >> 8) + HIBYTE(a2);
    dword_25978 = (a6 << 24) + ((a6 & 0xFF00) << 8) + ((a6 & 0xFF0000) >> 8) + HIBYTE(a6);
    SBUF = (v10 << 24) + ((v10 & 0xFF00) << 8) + ((s32)(v10 & 0xFF0000) >> 8) + HIBYTE(v10);
    dword_2597C = (a4 << 24) + ((a4 & 0xFF00) << 8) + ((a4 & 0xFF0000) >> 8) + HIBYTE(a4);
    if (a4) {
        v12 = a3;
        do {
            *(u8 *)(v11 + 153984) = *v12;
            v12 = &a3[++v11];
        } while (v11 < a4);
    }
    v19.command = 4363;
    v19.input_buffer = (u32)&SBUF;
    v19.input_buffer_length = a4 + 16;
    v19.input_word_count = 0;
    v19.output_buffer = (u32)&RBUF;
    v19.timeout = 10000000;
    if (DvrdrvExecCmdAckDma2Comp(&v19)) {
        v13 = "dvrf_df_ioctl2 -> IO error (phase %d)\n";
    LABEL_8:
        v15 = -5;
        printf(v13, v19.phase);
        goto LABEL_12;
    }
    v14 = 0;
    if (v19.comp_status) {
        v13 = "dvrf_df_ioctl2 -> Complete parameter error (phase %d)\n";
        goto LABEL_8;
    }
    v15 = (v19.return_result_word[0] << 16) + v19.return_result_word[1];
    if (a6) {
        v16 = a5;
        do {
            v17 = *(u8 *)(v14 + 22896);
            ++v14;
            *v16 = v17;
            v16 = &a5[v14];
        } while (v14 < a6);
    }
LABEL_12:
    SignalSema(sema_id);
    return v15;
}

s32 dvrf_df_lseek(s32 a1, s32 a2, s32 a3)
{
    s32 v6;
    const s8 *v7;
    s32 v8;
    drvdrv_exec_cmd_ack v10;

    WaitSema(sema_id);
    v6 = GetFd(a1);
    v10.command = 4364;
    v10.input_word[1] = v6;
    v10.input_word[2] = HIWORD(a2);
    v10.input_word[4] = HIWORD(a3);
    v10.input_word[0] = HIWORD(v6);
    v10.input_word[3] = a2;
    v10.input_word[5] = a3;
    v10.input_word_count = 6;
    v10.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&v10)) {
        v7 = "dvrf_df_lseek : IO error (phase %d)\n";
    } else {
        if (!v10.comp_status) {
            v8 = (v10.return_result_word[0] << 16) + v10.return_result_word[1];
            goto LABEL_7;
        }
        v7 = "dvrf_df_lseek : Complete parameter error (phase %d)\n";
    }
    v8 = -5;
    printf(v7, v10.phase);
LABEL_7:
    SignalSema(sema_id);
    return v8;
}

unsigned __int64 dvrf_df_lseek64(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 v8;
    const s8 *v9;
    unsigned __int64 v10;
    drvdrv_exec_cmd_ack v12;

    WaitSema(sema_id);
    v8 = GetFd(a1);
    v12.command = 4365;
    v12.input_word[0] = HIWORD(v8);
    v12.input_word[1] = v8;
    v12.input_word[2] = HIWORD(a4);
    v12.input_word[3] = a4;
    v12.input_word[4] = HIWORD(a3);
    v12.input_word[6] = HIWORD(a5);
    v12.input_word[5] = a3;
    v12.input_word[7] = a5;
    v12.input_word_count = 8;
    v12.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&v12)) {
        v9 = "dvrf_df_lseek64 : IO error (phase %d)\n";
    } else {
        if (!v12.comp_status) {
            v10 = (v12.return_result_word[2] << 16) + __PAIR64__(
                                                          (v12.return_result_word[0] << 16) + (u32)v12.return_result_word[1],
                                                          v12.return_result_word[3]);
            goto LABEL_7;
        }
        v9 = "dvrf_df_lseek64 : Complete parameter error (phase %d)\n";
    }
    v10 = -5LL;
    printf(v9, v12.phase);
LABEL_7:
    SignalSema(sema_id);
    return v10;
}

s32 dvrf_df_mkdir(s32 a1, const s8 *a2, u32 a3)
{
    const s8 *v5;
    s32 v6;
    drvdrv_exec_cmd_ack v8;

    WaitSema(sema_id);
    SBUF = (a3 << 24) + ((a3 & 0xFF00) << 8) + ((a3 >> 8) & 0xFF00) + HIBYTE(a3);
    strcpy((s8 *)&dword_25974, a2);
    v8.command = 4366;
    v8.input_word_count = 0;
    v8.input_buffer = (u32)&SBUF;
    v8.input_buffer_length = strlen(a2) + 5;
    v8.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v8)) {
        v5 = "dvrf_df_mkdir -> IO error (phase %d)\n";
    } else {
        if (!v8.comp_status) {
            v6 = (v8.return_result_word[0] << 16) + v8.return_result_word[1];
            goto LABEL_7;
        }
        v5 = "dvrf_df_mkdir -> Complete parameter error (phase %d)\n";
    }
    v6 = -5;
    printf(v5, v8.phase);
LABEL_7:
    SignalSema(sema_id);
    return v6;
}

s32 dvrf_df_mount(s32 a1, const s8 *a2, const s8 *a3, u32 a4, s32 a5, s32 a6)
{
    size_t v9;
    u32 v10;
    const s8 *v11;
    u32 v12;
    s32 v13;
    u32 v14;
    s8 v15;
    const s8 *v16;
    s32 v17;
    drvdrv_exec_cmd_ack v19;

    WaitSema(sema_id);
    SBUF = (a4 << 24) + ((a4 & 0xFF00) << 8) + ((s32)(a4 & 0xFF0000) >> 8) + HIBYTE(a4);
    v10 = strlen(a2) + 17;
    v9 = strlen(a3);
    v11 = a2;
    v12 = v10 + v9 + 1;
    dword_25978 = (v12 << 24) + ((v12 & 0xFF00) << 8) + ((s32)(v12 & 0xFF0000) >> 8) + HIBYTE(v12);
    dword_25974 = (v10 << 24) + ((v10 & 0xFF00) << 8) + ((s32)(v10 & 0xFF0000) >> 8) + HIBYTE(v10);
    dword_2597C = (a6 << 24) + ((a6 & 0xFF00) << 8) + ((a6 & 0xFF0000) >> 8) + HIBYTE(a6);
    strcpy(&byte_25980, v11);
    strcpy((s8 *)&SBUF + v10, a3);
    v13 = 0;
    if (a6 > 0) {
        v14 = v12;
        do {
            v15 = *(u8 *)(a5 + v13++);
            *(u8 *)(v14 + 153968) = v15;
            v14 = v12 + v13;
        } while (v13 < a6);
    }
    v19.command = 4367;
    v19.input_buffer = (u32)&SBUF;
    v19.input_word_count = 0;
    v19.input_buffer_length = v12 + a6;
    v19.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v19)) {
        v16 = "dvrf_df_mount -> IO error (phase %d)\n";
    } else {
        if (!v19.comp_status) {
            v17 = (v19.return_result_word[0] << 16) + v19.return_result_word[1];
            goto LABEL_10;
        }
        v16 = "dvrf_df_mount -> Complete parameter error (phase %d)\n";
    }
    v17 = -5;
    printf(v16, v19.phase);
LABEL_10:
    SignalSema(sema_id);
    return v17;
}

s32 dvrf_df_open(s32 a1, const s8 *a2, u32 a3, u16 a4)
{
    s32 v8;
    const s8 *v9;
    s32 v10;
    drvdrv_exec_cmd_ack v12;

    WaitSema(sema_id);
    if (dword_5968 >= 32) {
        v8 = -24;
        goto LABEL_11;
    }
    SBUF = (a3 << 24) + ((a3 & 0xFF00) << 8) + ((a3 >> 8) & 0xFF00) + HIBYTE(a3);
    LOWORD(dword_25974) = (a4 << 8) + HIBYTE(a4);
    strcpy((s8 *)&dword_25974 + 2, a2);
    v12.command = 4368;
    v12.input_word_count = 0;
    v12.input_buffer = (u32)&SBUF;
    v12.input_buffer_length = strlen(a2) + 7;
    v12.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v12)) {
        v9 = "dvrf_df_open -> IO error (phase %d)\n";
    LABEL_7:
        v8 = -5;
        printf(v9, v12.phase);
        goto LABEL_11;
    }
    if (v12.comp_status) {
        v9 = "dvrf_df_open -> Complete parameter error (phase %d)\n";
        goto LABEL_7;
    }
    v10 = v12.return_result_word[0] << 16;
    v8 = v10 + v12.return_result_word[1];
    if (v8 >= 0) {
        RegisterFd(a1, v10 + v12.return_result_word[1]);
        ++dword_5968;
    } else {
        printf("dvrf_df_open -> fd error (fd=%d)\n", v10 + v12.return_result_word[1]);
    }
LABEL_11:
    SignalSema(sema_id);
    return v8;
}

s32 dvrf_df_read(s32 a1, s8 *a2, s32 a3)
{
    size_t v6;
    s8 *v8;
    s32 v9;
    s32 v10;
    s32 v11;
    u16 v12;
    s32 v13;
    s32 v14;
    s32 v15;
    s32 v16;
    drvdrv_exec_cmd_ack v17;

    v6 = 0;
    if (((u8)a2 & 3) != 0)
        return -14;
    WaitSema(sema_id);
    v8 = a2;
    if ((a3 & 0x7F) != 0) {
        printf("nbyte is not a multiple of 128.\n");
        v8 = &RBUF;
    }
    v10 = GetFd(a1);
    v11 = a3;
    v12 = v10;
    v13 = v10 >> 16;
    while (1) {
        v14 = a3 & 0x7F;
        if (v11 <= 0)
            break;
        v15 = dword_596C;
        if (v11 < dword_596C)
            v15 = v11;
        v17.command = 4369;
        v17.input_word[0] = v13;
        v17.input_word[1] = v12;
        v17.input_word[2] = HIWORD(v15);
        v17.input_word[3] = v15;
        v17.input_word_count = 4;
        v17.output_buffer = (u32)v8;
        v17.timeout = 10000000;
        if (DvrdrvExecCmdAckDmaRecvComp(&v17)) {
            v9 = -5;
            printf("dvrf_df_read : IO error (phase %d)\n", v17.phase);
            goto LABEL_19;
        }
        if (v17.comp_status) {
            v9 = -5;
            printf("dvrf_df_read : Complete parameter error (phase %d), %04X\n", v17.phase, v17.comp_status);
            goto LABEL_19;
        }
        v16 = (v17.return_result_word[0] << 16) + v17.return_result_word[1];
        v11 -= v16;
        if (v16 <= 0) {
            v14 = a3 & 0x7F;
            break;
        }
        v8 += v16;
        v6 += v16;
    }
    if (v14)
        memcpy(a2, &RBUF, v6);
    v9 = v6;
LABEL_19:
    SignalSema(sema_id);
    return v9;
}

s32 dvrf_df_readlink(s32 a1, const s8 *a2, u8 *a3, u32 a4)
{
    const s8 *v7;
    u32 v8;
    s32 v9;
    u8 *v10;
    s8 v11;
    drvdrv_exec_cmd_ack v13;

    WaitSema(sema_id);
    SBUF = (a4 << 24) + ((a4 & 0xFF00) << 8) + ((a4 >> 8) & 0xFF00) + HIBYTE(a4);
    strcpy((s8 *)&dword_25974, a2);
    v13.input_buffer_length = strlen(a2) + 5;
    v13.command = 4370;
    v13.input_word_count = 0;
    v13.input_buffer = (u32)&SBUF;
    v13.output_buffer = (u32)&RBUF;
    v13.timeout = 10000000;
    if (DvrdrvExecCmdAckDma2Comp(&v13)) {
        v7 = "dvrf_df_readlink -> IO error (phase %d)\n";
    LABEL_5:
        v9 = -5;
        printf(v7, v13.phase);
        goto LABEL_9;
    }
    v8 = 0;
    if (v13.comp_status) {
        v7 = "dvrf_df_readlink -> Complete parameter error (phase %d)\n";
        goto LABEL_5;
    }
    v9 = (v13.return_result_word[0] << 16) + v13.return_result_word[1];
    if (a4) {
        v10 = a3;
        do {
            v11 = *(u8 *)(v8 + 22896);
            ++v8;
            *v10 = v11;
            v10 = &a3[v8];
        } while (v8 < a4);
    }
LABEL_9:
    SignalSema(sema_id);
    return v9;
}

s32 dvrf_df_remove(s32 a1, const s8 *a2)
{
    const s8 *v3;
    s32 v4;
    drvdrv_exec_cmd_ack v6;

    WaitSema(sema_id);
    strcpy((s8 *)&SBUF, a2);
    v6.command = 4371;
    v6.input_word_count = 0;
    v6.input_buffer = (u32)&SBUF;
    v6.input_buffer_length = strlen(a2) + 1;
    v6.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v6)) {
        v3 = "dvrf_df_remove -> IO error (phase %d)\n";
    } else {
        if (!v6.comp_status) {
            v4 = (v6.return_result_word[0] << 16) + v6.return_result_word[1];
            goto LABEL_7;
        }
        v3 = "dvrf_df_remove -> Complete parameter error (phase %d)\n";
    }
    v4 = -5;
    printf(v3, v6.phase);
LABEL_7:
    SignalSema(sema_id);
    return v4;
}

s32 dvrf_df_rename(s32 a1, const s8 *a2, const s8 *a3)
{
    size_t v5;
    const s8 *v6;
    size_t v7;
    const s8 *v8;
    s32 v9;
    drvdrv_exec_cmd_ack v11;

    WaitSema(sema_id);
    v5 = strlen(a2);
    v6 = a2;
    v7 = v5 + 5;
    SBUF = ((v5 + 5) << 24) + (((v5 + 5) & 0xFF00) << 8) + (((u32)(v5 + 5) >> 8) & 0xFF00) + ((u32)(v5 + 5) >> 24);
    strcpy((s8 *)&dword_25974, v6);
    strcpy((s8 *)&SBUF + v7, a3);
    v11.command = 4372;
    v11.input_word_count = 0;
    v11.input_buffer = (u32)&SBUF;
    v11.input_buffer_length = v7 + strlen(a3) + 1;
    v11.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v11)) {
        v8 = "dvrf_df_rename -> IO error (phase %d)\n";
    } else {
        if (!v11.comp_status) {
            v9 = (v11.return_result_word[0] << 16) + v11.return_result_word[1];
            goto LABEL_7;
        }
        v8 = "dvrf_df_rename -> Complete parameter error (phase %d)\n";
    }
    v9 = -5;
    printf(v8, v11.phase);
LABEL_7:
    SignalSema(sema_id);
    return v9;
}

s32 dvrf_df_rmdir(s32 a1, const s8 *a2)
{
    const s8 *v3;
    s32 v4;
    drvdrv_exec_cmd_ack v6;

    WaitSema(sema_id);
    strcpy((s8 *)&SBUF, a2);
    v6.command = 4373;
    v6.input_word_count = 0;
    v6.input_buffer = (u32)&SBUF;
    v6.input_buffer_length = strlen(a2) + 1;
    v6.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v6)) {
        v3 = "dvrf_df_rmdir -> IO error (phase %d)\n";
    } else {
        if (!v6.comp_status) {
            v4 = (v6.return_result_word[0] << 16) + v6.return_result_word[1];
            goto LABEL_7;
        }
        v3 = "dvrf_df_rmdir -> Complete parameter error (phase %d)\n";
    }
    v4 = -5;
    printf(v3, v6.phase);
LABEL_7:
    SignalSema(sema_id);
    return v4;
}

s32 dvrf_df_symlink(s32 a1, const s8 *a2, const s8 *a3)
{
    size_t v5;
    const s8 *v6;
    size_t v7;
    const s8 *v8;
    s32 v9;
    drvdrv_exec_cmd_ack v11;

    WaitSema(sema_id);
    v5 = strlen(a2);
    v6 = a2;
    v7 = v5 + 5;
    SBUF = ((v5 + 5) << 24) + (((v5 + 5) & 0xFF00) << 8) + (((u32)(v5 + 5) >> 8) & 0xFF00) + ((u32)(v5 + 5) >> 24);
    strcpy((s8 *)&dword_25974, v6);
    strcpy((s8 *)&SBUF + v7, a3);
    v11.command = 4374;
    v11.input_word_count = 0;
    v11.input_buffer = (u32)&SBUF;
    v11.input_buffer_length = v7 + strlen(a3) + 1;
    v11.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v11)) {
        v8 = "dvrf_df_symlink -> IO error (phase %d)\n";
    } else {
        if (!v11.comp_status) {
            v9 = (v11.return_result_word[0] << 16) + v11.return_result_word[1];
            goto LABEL_7;
        }
        v8 = "dvrf_df_symlink -> Complete parameter error (phase %d)\n";
    }
    v9 = -5;
    printf(v8, v11.phase);
LABEL_7:
    SignalSema(sema_id);
    return v9;
}

s32 dvrf_df_sync(s32 a1, const s8 *a2, u32 a3)
{
    const s8 *v5;
    s32 v6;
    drvdrv_exec_cmd_ack v8;

    WaitSema(sema_id);
    SBUF = (a3 << 24) + ((a3 & 0xFF00) << 8) + ((a3 >> 8) & 0xFF00) + HIBYTE(a3);
    strcpy((s8 *)&dword_25974, a2);
    v8.command = 4375;
    v8.input_word_count = 0;
    v8.input_buffer = (u32)&SBUF;
    v8.input_buffer_length = strlen(a2) + 5;
    v8.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v8)) {
        v5 = "dvrf_df_sync -> IO error (phase %d)\n";
    } else {
        if (!v8.comp_status) {
            v6 = (v8.return_result_word[0] << 16) + v8.return_result_word[1];
            goto LABEL_7;
        }
        v5 = "dvrf_df_sync -> Complete parameter error (phase %d)\n";
    }
    v6 = -5;
    printf(v5, v8.phase);
LABEL_7:
    SignalSema(sema_id);
    return v6;
}

s32 dvrf_df_umount(s32 a1, const s8 *a2)
{
    const s8 *v3;
    s32 v4;
    drvdrv_exec_cmd_ack v6;

    WaitSema(sema_id);
    strcpy((s8 *)&SBUF, a2);
    v6.command = 4376;
    v6.input_word_count = 0;
    v6.input_buffer = (u32)&SBUF;
    v6.input_buffer_length = strlen(a2) + 1;
    v6.timeout = 10000000;
    if (DvrdrvExecCmdAckDmaSendComp(&v6)) {
        v3 = "dvrf_df_umount -> IO error (phase %d)\n";
    } else {
        if (!v6.comp_status) {
            v4 = (v6.return_result_word[0] << 16) + v6.return_result_word[1];
            goto LABEL_7;
        }
        v3 = "dvrf_df_umount -> Complete parameter error (phase %d)\n";
    }
    v4 = -5;
    printf(v3, v6.phase);
LABEL_7:
    SignalSema(sema_id);
    return v4;
}

s32 dvrf_df_write(s32 a1, u32 a2, s32 a3)
{
    s32 v4;
    u32 v5;
    s32 result;
    const s8 *v8;
    s32 v9;
    s32 v10;
    s32 v11;
    u16 v12;
    s32 v13;
    u32 v14;
    s32 v15;
    s32 v16;
    drvdrv_exec_cmd_ack v17;

    v4 = 0;
    v5 = a2;
    if ((a2 & 3) != 0) {
        printf("dvrf_df_write : Address is not a multiple of 4.\n");
        result = -14;
    } else {
        WaitSema(sema_id);
        v10 = GetFd(a1);
        v11 = a3;
        v12 = v10;
        v13 = v10 >> 16;
        while (v11 > 0) {
            v14 = dword_596C;
            if (v11 < dword_596C)
                v14 = v11;
            v17.command = 4377;
            v17.input_word[0] = v13;
            v17.input_word[1] = v12;
            v17.input_word[2] = HIWORD(v14);
            v17.input_word[3] = v14;
            v17.input_word_count = 4;
            v17.input_buffer = v5;
            v17.input_buffer_length = v14;
            v17.timeout = 10000000;
            if (DvrdrvExecCmdAckDmaSendComp(&v17)) {
                v8 = "dvrf_df_write : IO error (phase %d)\n";
            LABEL_5:
                v9 = -5;
                printf(v8, v17.phase);
                goto LABEL_16;
            }
            if (v17.comp_status) {
                v8 = "dvrf_df_write : Complete parameter error (phase %d)\n";
                goto LABEL_5;
            }
            v15 = v17.return_result_word[0] << 16;
            v16 = v15 + v17.return_result_word[1];
            v11 -= v16;
            if (v16 <= 0) {
                v9 = v15 + v17.return_result_word[1];
                goto LABEL_16;
            }
            v5 += v16;
            v4 += v16;
        }
        v9 = v4;
    LABEL_16:
        SignalSema(sema_id);
        result = v9;
    }
    return result;
}

s32 RegisterFd(s32 a1, s32 a2)
{
    s32 v2;
    s32 result;

    v2 = 0;
    while (dword_586C[2 * v2]) {
        if (++v2 >= 32)
            goto LABEL_4;
    }
    dword_5868[2 * v2] = a2;
    dword_586C[2 * v2] = a1;
LABEL_4:
    result = 0;
    if (v2 != 32)
        return result;
    printf("RegisterFd -> NG\n");
    return -1;
}

s32 UnregisterFd(s32 a1)
{
    s32 v1;
    s32 *v2;
    s32 result;

    v1 = 0;
    v2 = dword_586C;
    do {
        if (*v2 == a1) {
            result = 0;
            dword_5868[2 * v1] = -1;
            *v2 = 0;
            return result;
        }
        ++v1;
        v2 += 2;
    } while (v1 < 32);
    printf("UnregisterFd -> NG\n");
    return -1;
}

s32 GetFd(s32 a1)
{
    s32 v1;
    s32 v2;

    v1 = 0;
    v2 = 0;
    do {
        ++v1;
        if (*(u32 *)(v2 + 22636) == a1)
            return *(u32 *)(v2 + 22632);
        v2 = 8 * v1;
    } while (v1 < 32);
    printf("GetFd -> NG\n");
    return -1;
}

s32 CopySceStat(s32 a1, s32 a2)
{
    s8 v2;
    s8 v3;
    s8 v4;
    s8 v5;
    s8 v6;
    s8 v7;
    u32 v8;
    s32 result;

    *(u32 *)a1 = (*(u32 *)a2 << 24) + ((*(u32 *)a2 & 0xFF00) << 8) + ((*(u32 *)a2 & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)a2);
    *(u32 *)(a1 + 4) = (*(u32 *)(a2 + 4) << 24) + ((*(u32 *)(a2 + 4) & 0xFF00) << 8) + ((*(u32 *)(a2 + 4) & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)(a2 + 4));
    *(u32 *)(a1 + 8) = (*(u32 *)(a2 + 8) << 24) + ((*(u32 *)(a2 + 8) & 0xFF00) << 8) + ((*(u32 *)(a2 + 8) & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)(a2 + 8));
    v2 = *(u8 *)(a2 + 16);
    v3 = *(u8 *)(a2 + 17);
    *(u32 *)(a1 + 12) = *(u32 *)(a2 + 12);
    *(u8 *)(a1 + 16) = v2;
    *(u8 *)(a1 + 17) = v3;
    *(u16 *)(a1 + 18) = (*(u16 *)(a2 + 18) << 8) + HIBYTE(*(u16 *)(a2 + 18));
    v4 = *(u8 *)(a2 + 24);
    v5 = *(u8 *)(a2 + 25);
    *(u32 *)(a1 + 20) = *(u32 *)(a2 + 20);
    *(u8 *)(a1 + 24) = v4;
    *(u8 *)(a1 + 25) = v5;
    *(u16 *)(a1 + 26) = (*(u16 *)(a2 + 26) << 8) + HIBYTE(*(u16 *)(a2 + 26));
    v6 = *(u8 *)(a2 + 32);
    v7 = *(u8 *)(a2 + 33);
    *(u32 *)(a1 + 28) = *(u32 *)(a2 + 28);
    *(u8 *)(a1 + 32) = v6;
    *(u8 *)(a1 + 33) = v7;
    *(u16 *)(a1 + 34) = (*(u16 *)(a2 + 34) << 8) + HIBYTE(*(u16 *)(a2 + 34));
    *(u32 *)(a1 + 36) = (*(u32 *)(a2 + 36) << 24) + ((*(u32 *)(a2 + 36) & 0xFF00) << 8) + ((*(u32 *)(a2 + 36) & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)(a2 + 36));
    *(u32 *)(a1 + 40) = (*(u32 *)(a2 + 40) << 24) + ((*(u32 *)(a2 + 40) & 0xFF00) << 8) + ((*(u32 *)(a2 + 40) & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)(a2 + 40));
    *(u32 *)(a1 + 44) = (*(u32 *)(a2 + 44) << 24) + ((*(u32 *)(a2 + 44) & 0xFF00) << 8) + ((*(u32 *)(a2 + 44) & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)(a2 + 44));
    *(u32 *)(a1 + 48) = (*(u32 *)(a2 + 48) << 24) + ((*(u32 *)(a2 + 48) & 0xFF00) << 8) + ((*(u32 *)(a2 + 48) & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)(a2 + 48));
    *(u32 *)(a1 + 52) = (*(u32 *)(a2 + 52) << 24) + ((*(u32 *)(a2 + 52) & 0xFF00) << 8) + ((*(u32 *)(a2 + 52) & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)(a2 + 52));
    *(u32 *)(a1 + 56) = (*(u32 *)(a2 + 56) << 24) + ((*(u32 *)(a2 + 56) & 0xFF00) << 8) + ((*(u32 *)(a2 + 56) & 0xFF0000u) >> 8) + HIBYTE(*(u32 *)(a2 + 56));
    v8 = *(u32 *)(a2 + 60);
    result = (v8 & 0xFF00) << 8;
    *(u32 *)(a1 + 60) = (v8 << 24) + result + ((v8 & 0xFF0000) >> 8) + HIBYTE(v8);
    return result;
}

s32 DvrdrvExecCmdAckComp(drvdrv_exec_cmd_ack *a1)
{
    s32 result;

    return result;
}

s32 DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1)
{
    s32 result;

    return result;
}

s32 DvrdrvExecCmdAckDmaRecvComp(drvdrv_exec_cmd_ack *a1)
{
    s32 result;

    return result;
}

s32 DvrdrvExecCmdAckDma2Comp(drvdrv_exec_cmd_ack *a1)
{
    s32 result;

    return result;
}

s32 AddDrv(iop_device_t *device)
{
    s32 result;

    return result;
}

s32 DelDrv(const s8 *name)
{
    s32 result;

    return result;
}

s32 printf(const s8 *format, ...)
{
    s32 result;

    return result;
}

void *memcpy(void *dest, const void *src, size_t size)
{
    void *result;

    return result;
}

s32 sprintf(s8 *str, const s8 *format, ...)
{
    s32 result;

    return result;
}

s32 strcmp(const s8 *p, const s8 *q)
{
    s32 result;

    return result;
}

s8 *strcpy(s8 *dest, const s8 *src)
{
    s8 *result;

    return result;
}

size_t strlen(const s8 *s)
{
    size_t result;

    return result;
}

s32 DelayThread(s32 usec)
{
    s32 result;

    return result;
}

s32 CreateSema(iop_sema_t *sema)
{
    s32 result;

    return result;
}

s32 DeleteSema(s32 sema_id)
{
    s32 result;

    return result;
}

s32 SignalSema(s32 sema_id)
{
    s32 result;

    return result;
}

s32 WaitSema(s32 sema_id)
{
    s32 result;

    return result;
}
