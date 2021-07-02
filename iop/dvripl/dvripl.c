



s32 irx_entry_point(s32 a1);
s32 module_start();
s32 module_stop();
s32 dvripl_df_init();
s32 dvripl_df_exit();
s32 dvripl_df_ioctl();
s32 dvripl_df_devctl(s32 a1, s32 a2, s32 a3, const s8 *a4);
s32 dvripl_df_ioctl2();
s32 dvripl_df_null();
__int64 dvripl_df_null_long();
s32 iplioctl2_update(s32 a1, s32 a2, const s8 *a3);
void dvr_ready(s32, s32);
s32 DvrdrvUnregisterIntrHandler(void (*a1)(s32, s32));
s32 DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1);
s32 Kprintf(const s8 *format, ...);
s32 open(const s8 *name, s32 flags, ...);
s32 close(s32 fd);
s32 read(s32 fd, void *ptr, s32 size);
s32 AddDrv(iop_device_t *device);
s32 DelDrv(const s8 *name);
s32 printf(const s8 *format, ...);
s32 iWakeupThread(s32 thread_id);
s32 CreateSema(iop_sema_t *sema);
s32 DeleteSema(s32 sema_id);
s32 SignalSema(s32 sema_id);
s32 WaitSema(s32 sema_id);
s32 AllocHardTimer(s32 source, s32 size, s32 prescale);
s32 FreeHardTimer(s32 timid);
u32 GetTimerCounter(s32 timid);
s32 SetupHardTimer(s32 timid, s32 source, s32 mode, s32 prescale);
s32 StartHardTimer(s32 timid);
s32 StopHardTimer(s32 timid);


s32 (*DvrFuncTbl[23])() =
    {
        &dvripl_df_init,
        &dvripl_df_exit,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_ioctl,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null,
        &dvripl_df_null_long};
s32 dvr_ready_flag;
s32 DVRMAN;
s32 dword_C54;
s32 dword_C5C;
s32 dword_C60;
s32 sema_id;
s32 dword_C68;
s8 byte_C6C;
s32 dword_D6C;
s32 dword_D70;
s32 SBUF[8192];


s32 irx_entry_point(s32 a1)
{
    s32 result;

    if (a1 >= 0)
        result = module_start();
    else
        result = module_stop();
    return result;
}

s32 module_start()
{
    bool v0;
    s32 result;

    DVRMAN = (s32) "dvr_ipl";
    dword_C5C = (s32) "Digital Video Recorder";
    dword_C60 = (s32)DvrFuncTbl;
    dword_C68 = 0;
    dword_C54 = 268435472;
    byte_C6C = 0;
    dword_D6C = -1;
    dword_D70 = 0;
    v0 = AddDrv((iop_device_t *)&DVRMAN) == 0;
    result = 2;
    if (!v0)
        result = 1;
    return result;
}

s32 module_stop()
{
    bool v0;
    s32 result;

    v0 = DelDrv("dvr_ipl") == 0;
    result = 1;
    if (!v0)
        result = 2;
    return result;
}

s32 dvripl_df_init()
{
    s32 v0;
    iop_sema_t v2;

    printf("dvripl_df_init\n");
    v2.attr = 0;
    v2.initial = 1;
    v2.max = 1;
    v2.option = 0;
    v0 = CreateSema(&v2);
    if (v0 < 0)
        return -1;
    sema_id = v0;
    return 0;
}

s32 dvripl_df_exit()
{
    bool v0;
    s32 result;

    printf("dvripl_df_exit\n");
    v0 = DeleteSema(sema_id) == 0;
    result = 0;
    if (!v0)
        result = -1;
    return result;
}

s32 dvripl_df_ioctl()
{
    printf("dvripl_df_ioctl\n");
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

s32 dvripl_df_devctl(s32 a1, s32 a2, s32 a3, const s8 *a4)
{
    bool v7;
    s32 v8;

    printf("dvripl_df_devctl\n");
    WaitSema(sema_id);
    v7 = a3 != 22018;
    v8 = -22;
    if (!v7)
        v8 = iplioctl2_update(a1, 22018, a4);
    SignalSema(sema_id);
    return v8;
}

s32 dvripl_df_ioctl2()
{
    printf("dvripl_df_ioctl2\n");
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

s32 dvripl_df_null()
{
    return -48;
}

__int64 dvripl_df_null_long()
{
    return -48LL;
}

s32 iplioctl2_update(s32 a1, s32 a2, const s8 *a3)
{
    s32 v3;
    s32 v4;
    s32 v5;
    s32 v6;
    const s8 *v7;
    s32 v8;
    s32 v9;
    s32 v11;
    s32 v12;
    s32 v13;
    s32 v14;
    s32 v15;
    s32 *v16;
    s32 v17;
    u32 v19;
    u32 v20;
    s32 v21;
    drvdrv_exec_cmd_ack v22;

    v3 = 0;
    v4 = 0;
    v5 = 0;
    printf("iplioctl2_update\n");
    printf("NOP\n");
    v22.command = 257;
    v22.input_word_count = 0;
    v6 = DvrdrvExecCmdAck(&v22);
    printf("dvrcmd.ack_p[0]:%x\n", v22.ack_status);
    if (v6)
        goto LABEL_2;
    v7 = "NOP -> Status error!\n";
    if (v22.ack_status) {
    LABEL_11:
        printf(v7);
        return -5;
    }
    printf("VERSION\n");
    v22.command = 258;
    v22.input_word_count = 0;
    v8 = DvrdrvExecCmdAck(&v22);
    printf("dvrcmd.ack_p[0]:%x\n", v22.ack_status);
    if (v8) {
    LABEL_2:
        printf("NOP -> Handshake error!\n");
        return -5;
    }
    if (v22.ack_status) {
        printf("NOP -> Status error!\n");
        return -5;
    }
    printf("major : %04x\n", v22.output_word[0]);
    printf("minor : %04x\n", v22.output_word[1]);
    printf("CONFIG\n");
    v22.command = 262;
    v22.input_word[0] = 1;
    v22.input_word[1] = 6;
    v22.input_word[2] = 4096;
    v22.input_word[3] = -30360;
    v22.input_word[4] = 4442;
    v22.input_word[5] = 24648;
    v22.input_word[6] = 15;
    v22.input_word[7] = 21331;
    v22.input_word_count = 8;
    v9 = DvrdrvExecCmdAck(&v22);
    printf("dvrcmd.ack_p[0]:%x\n", v22.ack_status);
    if (v9) {
        printf("CONFIG -> Handshake error!(%d)\n", v9);
        return -5;
    }
    if (v22.ack_status) {
        v7 = "CONFIG -> Status error!\n";
        goto LABEL_11;
    }
    v11 = open(a3, 1, 292);
    if (v11 >= 0) {
        v12 = 0x10000000;
        printf("Opened \"%s\"\n", a3);
        printf("Downloading  \"%s\"\n", a3);
        v13 = AllocHardTimer(1, 32, 1);
        SetupHardTimer(v13, 1, 0, 1);
        StartHardTimer(v13);
        while (1) {
            printf("%08X\n", v12);
            v14 = read(v11, SBUF, 0x8000);
            v15 = v14;
            if (v14 < 0) {
                v4 = -5;
                printf("Cannot read \"%s\"\n", a3);
                goto LABEL_30;
            }
            v16 = SBUF;
            if (!v14)
                break;
            v17 = 0;
            while (v17++ < v15 / 4) {
                v19 = *v16++;
                v5 += (v19 << 24) + ((v19 & 0xFF00) << 8) + ((v19 & 0xFF0000) >> 8) + HIBYTE(v19);
            }
            v22.command = 259;
            v22.input_word[0] = HIWORD(v12);
            v22.input_word[1] = v12;
            v22.input_word_count = 2;
            v22.input_buffer = (u32)SBUF;
            v22.input_buffer_length = v15;
            if (DvrdrvExecCmdAckDmaSendComp(&v22)) {
                v4 = -5;
                printf("Handshake error! (phase:%d)\n", v22.phase);
                goto LABEL_30;
            }
            v12 += v15;
            if (v22.ack_status)
                goto LABEL_29;
            v3 += v15;
        }
        v20 = GetTimerCounter(v13);
        printf("System Clock : %ld\n", v20);
        StopHardTimer(v13);
        FreeHardTimer(v13);
        printf("CHECK SUM\n");
        printf("total_size:%d\n", v3);
        printf("csum : %x\n", v5);
        v22.command = 261;
        v22.input_word[0] = 4096;
        v22.input_word[2] = HIWORD(v3);
        v22.input_word[4] = HIWORD(v5);
        v22.input_word[1] = 0;
        v22.input_word[3] = v3;
        v22.input_word[5] = v5;
        v22.input_word_count = 6;
        v21 = DvrdrvExecCmdAck(&v22);
        printf("result: %d\n", v21);
        printf("dvrcmd.ack_p[0]:%x\n", v22.ack_status);
        printf("dvrcmd.ack_p[1]:%x\n", v22.output_word[0]);
        printf("dvrcmd.ack_p[2]:%x\n", v22.output_word[1]);
        if (v21) {
            v4 = -5;
            goto LABEL_30;
        }
        if (v22.ack_status) {
        LABEL_29:
            v4 = -5;
            goto LABEL_30;
        }
    } else {
        v4 = -89;
    }
LABEL_30:
    close(v11);
    DvrdrvUnregisterIntrHandler(dvr_ready);
    printf("done.\n");
    return v4;
}

void dvr_ready(s32 a1, s32 a2)
{
    Kprintf("DVRRDY INTERRUPT\n");
    dvr_ready_flag = 1;
    iWakeupThread(*(u32 *)a2);
}

s32 DvrdrvUnregisterIntrHandler(void (*a1)(s32, s32))
{
    s32 result;

    return result;
}

s32 DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1)
{
    s32 result;

    return result;
}

s32 DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1)
{
    s32 result;

    return result;
}

s32 Kprintf(const s8 *format, ...)
{
    s32 result;

    return result;
}

s32 open(const s8 *name, s32 flags, ...)
{
    s32 result;

    return result;
}

s32 close(s32 fd)
{
    s32 result;

    return result;
}

s32 read(s32 fd, void *ptr, s32 size)
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

s32 iWakeupThread(s32 thread_id)
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

s32 AllocHardTimer(s32 source, s32 size, s32 prescale)
{
    s32 result;

    return result;
}

s32 FreeHardTimer(s32 timid)
{
    s32 result;

    return result;
}

u32 GetTimerCounter(s32 timid)
{
    u32 result;

    return result;
}

s32 SetupHardTimer(s32 timid, s32 source, s32 mode, s32 prescale)
{
    s32 result;

    return result;
}

s32 StartHardTimer(s32 timid)
{
    s32 result;

    return result;
}

s32 StopHardTimer(s32 timid)
{
    s32 result;

    return result;
}
