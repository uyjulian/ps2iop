



s32 irx_entry_point(s32 a1);
s32 module_start();
s32 module_stop();
s32 dvrmisc_df_init();
s32 dvrmisc_df_exit();
s32 dvrmisc_df_ioctl();
s32 dvrmisc_df_devctl(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
s32 dvrmisc_df_ioctl2();
s32 dvrmisc_df_null();
__int64 dvrmisc_df_null_long();
s32 dvrioctl2_nop();
s32 dvrioctl2_version(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 dvrioctl2_led_hdd_rec(s32 a1, s32 a2, u16 *a3);
s32 dvrioctl2_led_dvd_rec(s32 a1, s32 a2, u16 *a3);
s32 dvrioctl2_get_sircs(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 dvrioctl2_get_time(s32 a1, s32 a2, s32 a3, s32 a4, u8 *a5);
s32 dvrioctl2_set_timezone(s32 a1, s32 a2, u16 *a3);
s32 dvrioctl2_save_preset_info();
s32 dvrioctl2_load_preset_info();
s32 dvrioctl2_test_dev_rst();
s32 dvrioctl2_test_sdram_chk(s32 a1, s32 a2, s32 a3, s32 a4, u32 *a5);
s32 dvrioctl2_test_mpe_chk(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 dvrioctl2_test_mpd_chk(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 dvrioctl2_test_vdec_chk();
s32 dvrioctl2_partition_free(s32 a1, s32 a2, const s8 *a3, s32 a4, s32 a5);
s32 dvrioctl2_buzzer();
s32 dvrioctl2_clr_preset_info();
s32 dvrioctl2_get_vbi_err_rate(s32 a1, s32 a2, s32 a3, s32 a4, u32 *a5);
s32 dvrioctl2_update_dvrp_firmware(s32 a1, s32 a2, const s8 *a3);
s32 dvrioctl2_flash_write_status(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckComp(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1);
s32 open(const s8 *name, s32 flags, ...);
s32 close(s32 fd);
s32 read(s32 fd, void *ptr, s32 size);
s32 lseek(s32 fd, s32 pos, s32 mode);
s32 AddDrv(iop_device_t *device);
s32 DelDrv(const s8 *name);
s32 devctl(const s8 *name, s32 cmd, void *arg, u32 arglen, void *buf, u32 buflen);
s32 printf(const s8 *format, ...);
s32 DelayThread(s32 usec);
s32 CreateSema(iop_sema_t *sema);
s32 DeleteSema(s32 sema_id);
s32 SignalSema(s32 sema_id);
s32 WaitSema(s32 sema_id);


s32 (*DvrFuncTbl[23])() =
    {
        &dvrmisc_df_init,
        &dvrmisc_df_exit,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_ioctl,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null,
        &dvrmisc_df_null_long};
iop_device_t DVRMISC;
s32 sema_id;
s8 SBUF;
s8 byte_9D6F;


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
    s32 i;
    bool v1;
    s32 result;

    for (i = 0; i < 30000; ++i) {
        if (((*((vu32 *)0xB0004230)) & 4) != 0)
            break;
        DelayThread(1000);
    }
    if (i == 30000) {
        printf("MISC task of DVRP is not running...\n");
        result = 1;
    } else {
        DVRMISC.name = "dvr_misc";
        DVRMISC.desc = "Digital Video Recorder MISC task";
        DVRMISC.type = 268435472;
        DVRMISC.ops = (struct _iop_device_ops *)DvrFuncTbl;
        v1 = AddDrv(&DVRMISC) == 0;
        result = 2;
        if (!v1)
            result = 1;
    }
    return result;
}

s32 module_stop()
{
    bool v0;
    s32 result;

    v0 = DelDrv("dvr_misc") == 0;
    result = 1;
    if (!v0)
        result = 2;
    return result;
}

s32 dvrmisc_df_init()
{
    s32 v0;
    iop_sema_t v2;

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

s32 dvrmisc_df_exit()
{
    bool v0;
    s32 result;

    v0 = DeleteSema(sema_id) == 0;
    result = 0;
    if (!v0)
        result = -1;
    return result;
}

s32 dvrmisc_df_ioctl()
{
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

s32 dvrmisc_df_devctl(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    s32 v10;
    u32 v11;
    s32 v12;

    v10 = 0;
    v11 = 0;
    WaitSema(sema_id);
    v12 = 0;
    while (*(u16 *)(v12 + 7224) != a3) {
        ++v11;
        v12 = 8 * v11;
        if (v11 >= 0x14)
            goto LABEL_5;
    }
    v10 = (*(s32(**)(s32, s32, s32, s32, s32, s32))(v12 + 7228))(a1, a3, a4, a5, a6, a7);
LABEL_5:
    if (v11 == 20)
        v10 = -22;
    SignalSema(sema_id);
    return v10;
}

s32 dvrmisc_df_ioctl2()
{
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

s32 dvrmisc_df_null()
{
    return -48;
}

__int64 dvrmisc_df_null_long()
{
    return -48LL;
}

s32 dvrioctl2_nop()
{
    s32 result;
    drvdrv_exec_cmd_ack v1;

    v1.command = 20737;
    v1.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v1)) {
        printf("dvrioctl2_nop -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v1.ack_status) {
            printf("dvrioctl2_nop -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_version(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 20738;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("dvrioctl2_version -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("dvrioctl2_version -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.output_word[0];
        result = 0;
        a5[1] = v6.output_word[1];
    }
    return result;
}

s32 dvrioctl2_led_hdd_rec(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 20740;
    v3 = *a3;
    v5.input_word_count = 1;
    v5.input_word[0] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("dvrioctl2_led_hdd_rec -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("dvrioctl2_led_hdd_rec -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_led_dvd_rec(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 20742;
    v3 = *a3;
    v5.input_word_count = 1;
    v5.input_word[0] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("dvrioctl2_led_dvd_rec -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("dvrioctl2_led_dvd_rec -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_get_sircs(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 20743;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("dvrioctl2_get_sircs -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("dvrioctl2_get_sircs -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.output_word[0];
        a5[1] = v6.output_word[1];
        a5[2] = v6.output_word[2];
        a5[3] = v6.output_word[3];
        result = 0;
        a5[4] = v6.output_word[4];
    }
    return result;
}

s32 dvrioctl2_get_time(s32 a1, s32 a2, s32 a3, s32 a4, u8 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 20744;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("dvrioctl2_get_time -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("dvrioctl2_get_time -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.output_word[0];
        a5[1] = v6.output_word[1];
        a5[2] = v6.output_word[2];
        a5[3] = v6.output_word[3];
        a5[5] = v6.output_word[5];
        a5[6] = v6.output_word[6];
        result = 0;
        a5[7] = v6.output_word[7];
    }
    return result;
}

s32 dvrioctl2_set_timezone(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 20745;
    v5.input_word[0] = *a3;
    v3 = a3[1];
    v5.input_word_count = 2;
    v5.input_word[1] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("dvrioctl2_set_timezone -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("dvrioctl2_set_timezone -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_save_preset_info()
{
    s32 result;
    drvdrv_exec_cmd_ack v1;

    v1.command = 20746;
    v1.input_word_count = 0;
    v1.timeout = 15000000;
    if (DvrdrvExecCmdAckComp(&v1)) {
        printf("dvrioctl2_save_preset_info -> Handshake error!\n");
        result = -5;
    } else if (v1.ack_status || (result = 0, v1.comp_status)) {
        printf("dvrioctl2_save_preset_info -> Status error!\n");
        result = -68;
    }
    return result;
}

s32 dvrioctl2_load_preset_info()
{
    s32 result;
    drvdrv_exec_cmd_ack v1;

    v1.command = 20747;
    v1.input_word_count = 0;
    v1.timeout = 15000000;
    if (DvrdrvExecCmdAckComp(&v1)) {
        printf("dvrioctl2_load_preset_info -> Handshake error!\n");
        result = -5;
    } else if (v1.ack_status || (result = 0, v1.comp_status)) {
        printf("dvrioctl2_load_preset_info -> Status error!\n");
        result = -68;
    }
    return result;
}

s32 dvrioctl2_test_dev_rst()
{
    s32 result;
    drvdrv_exec_cmd_ack v1;

    v1.command = 20748;
    v1.input_word_count = 0;
    v1.timeout = 15000000;
    if (DvrdrvExecCmdAckComp(&v1)) {
        printf("dvrioctl2_test_dev_rst -> Handshake error!\n");
        result = -5;
    } else if (v1.ack_status || (result = 0, v1.comp_status)) {
        printf("dvrioctl2_test_dev_rst -> Status error!\n");
        result = -68;
    }
    return result;
}

s32 dvrioctl2_test_sdram_chk(s32 a1, s32 a2, s32 a3, s32 a4, u32 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 20749;
    v6.input_word_count = 0;
    v6.timeout = 20000000;
    if (DvrdrvExecCmdAckComp(&v6)) {
        printf("dvrioctl2_test_sdram_chk -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status || (result = 0, v6.comp_status)) {
        printf("dvrioctl2_test_sdram_chk -> Status error!\n");
        result = -68;
    } else {
        *a5 = (v6.return_result_word[0] << 16) + v6.return_result_word[1];
        a5[1] = (v6.return_result_word[2] << 16) + v6.return_result_word[3];
        a5[2] = (v6.return_result_word[4] << 16) + v6.return_result_word[5];
    }
    return result;
}

s32 dvrioctl2_test_mpe_chk(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 20750;
    v6.input_word_count = 0;
    v6.timeout = 15000000;
    if (DvrdrvExecCmdAckComp(&v6)) {
        printf("dvrioctl2_test_mpe_chk -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status || (result = 0, v6.comp_status)) {
        printf("dvrioctl2_test_mpe_chk -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.return_result_word[0];
    }
    return result;
}

s32 dvrioctl2_test_mpd_chk(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 20751;
    v6.input_word_count = 0;
    v6.timeout = 15000000;
    if (DvrdrvExecCmdAckComp(&v6)) {
        printf("dvrioctl2_test_mpd_chk -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status || (result = 0, v6.comp_status)) {
        printf("dvrioctl2_test_mpd_chk -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.return_result_word[0];
    }
    return result;
}

s32 dvrioctl2_test_vdec_chk()
{
    s32 result;
    drvdrv_exec_cmd_ack v1;

    v1.command = 20752;
    v1.input_word_count = 0;
    v1.timeout = 15000000;
    if (DvrdrvExecCmdAckComp(&v1)) {
        printf("dvrioctl2_test_vdec_chk -> Handshake error!\n");
        result = -5;
    } else if (v1.ack_status || (result = 0, v1.comp_status)) {
        printf("dvrioctl2_test_vdec_chk -> Status error!\n");
        result = -68;
    }
    return result;
}

s32 dvrioctl2_partition_free(s32 a1, s32 a2, const s8 *a3, s32 a4, s32 a5)
{
    s32 v6;
    s32 v7;
    s32 v8;
    __int64 v9;

    v6 = devctl(a3, 20482, 0, 0, 0, 0);
    v7 = v6;
    if (v6 < 0) {
        printf("dvrioctl2_partition_free : Cannot execute PDIOC_ZONEFREE.,%d\n", v6);
        return -5;
    }
    v8 = devctl(a3, 20481, 0, 0, 0, 0);
    v9 = v7 * (__int64)v8;
    if (v8 < 0) {
        printf("dvrioctl2_partition_free : Cannot execute PDIOC_ZONESZ.,%d\n", v8);
        return -5;
    }
    *(_QWORD *)a5 = v9;
    if (*(__int64 *)a5 <= 0x7FFFFFF) {
        *(u32 *)a5 = 0;
        *(u32 *)(a5 + 4) = 0;
    } else {
        *(u32 *)a5 = v9 - 0x8000000;
        *(u32 *)(a5 + 4) = HIDWORD(v9) - 1 + ((u32)(v9 - 0x8000000) < 0xF8000000);
    }
    return 0;
}

s32 dvrioctl2_buzzer()
{
    s32 result;
    drvdrv_exec_cmd_ack v1;

    v1.command = 20753;
    v1.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v1)) {
        printf("dvrioctl2_buzzer -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v1.ack_status) {
            printf("dvrioctl2_buzzer -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_clr_preset_info()
{
    s32 result;
    drvdrv_exec_cmd_ack v1;

    v1.command = 20754;
    v1.input_word_count = 0;
    v1.timeout = 20000000;
    if (DvrdrvExecCmdAckComp(&v1)) {
        printf("dvrioctl2_clr_preset_info -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v1.ack_status) {
            printf("dvrioctl2_clr_preset_info -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_get_vbi_err_rate(s32 a1, s32 a2, s32 a3, s32 a4, u32 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 20755;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("dvrioctl2_get_vbi_err_rate -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v6.ack_status) {
            printf("dvrioctl2_get_vbi_err_rate -> Status error!\n");
            result = -68;
        } else {
            *a5 = (v6.output_word[0] << 16) + v6.output_word[1];
            a5[1] = (v6.output_word[2] << 16) + v6.output_word[3];
        }
    }
    return result;
}

s32 dvrioctl2_update_dvrp_firmware(s32 a1, s32 a2, const s8 *a3)
{
    s32 v3;
    s32 v4;
    s32 v5;
    s32 v6;
    s32 v7;
    const s8 *v8;
    s32 i;
    s8 *v10;
    s32 v11;
    s32 j;
    s32 v13;
    const s8 *v14;
    drvdrv_exec_cmd_ack v16;

    v3 = 0;
    v4 = 0;
    v5 = -1;
    v6 = open(a3, 1, 73);
    if (v6 < 0) {
        v5 = -2;
        goto LABEL_38;
    }
    v7 = lseek(v6, 0, 2);
    if (lseek(v6, 0, 0) < 0)
        goto LABEL_38;
    v16.command = 20756;
    v16.input_word[0] = HIWORD(v7);
    v16.input_word[1] = v7;
    v16.input_word_count = 2;
    v16.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&v16)) {
        v8 = "FLASH_DATA_TOTALSIZE -> Handshake error!\n";
    LABEL_37:
        v5 = -5;
        printf(v8);
        goto LABEL_38;
    }
    if (v16.ack_status) {
        v8 = "FLASH_DATA_TOTALSIZE -> Status error!\n";
        goto LABEL_37;
    }
    if (v16.comp_status) {
        v8 = "FLASH_DATA_TOTALSIZE -> Status error!\n";
        goto LABEL_37;
    }
    if (v7 != (v16.return_result_word[0] << 16) + v16.return_result_word[1])
        printf("Size of firmware is not equal to Size of buffer on DVRP memory.\n");
    for (i = 0x3FFF;; i = 0x3FFF) {
        v10 = &byte_9D6F;
        do {
            *v10 = 0;
            --i;
            --v10;
        } while (i >= 0);
        v11 = read(v6, &SBUF, 0x4000);
        if (v11 <= 0)
            break;
        v16.command = 20757;
        v16.input_word[0] = HIWORD(v3);
        v16.input_word[1] = v3;
        v16.input_word_count = 2;
        v16.input_buffer = (u32)&SBUF;
        v16.input_buffer_length = v11;
        v16.timeout = 10000000;
        if (DvrdrvExecCmdAckDmaSendComp(&v16)) {
            v8 = "MISCCMD_FLASH_DATA_DOWNLOAD -> Handshake error!\n";
            goto LABEL_37;
        }
        if (v16.ack_status || (v3 += v11, v16.comp_status)) {
            v8 = "MISCCMD_FLASH_DATA_DOWNLOAD -> Status error!\n";
            goto LABEL_37;
        }
        for (j = 0; j < v11; ++j) {
            v13 = *(u8 *)(j + 23920);
            v4 += v13;
        }
    }
    v16.command = 20758;
    v16.input_word[0] = HIWORD(v7);
    v16.input_word[2] = HIWORD(v4);
    v16.input_word[1] = v7;
    v16.input_word[3] = v4;
    v16.input_word[4] = 0;
    v16.input_word[5] = 0;
    v16.input_word_count = 6;
    v16.timeout = 10000000;
    if (DvrdrvExecCmdAckComp(&v16)) {
        v8 = "MISCCMD_FLASH_DATA_CHECKSUM -> Handshake error!\n";
        goto LABEL_37;
    }
    if (v16.ack_status) {
        v14 = "MISCCMD_FLASH_DATA_CHECKSUM -> ACK Status error!\n";
    } else {
        if (v16.comp_status) {
            v5 = -68;
            printf("MISCCMD_FLASH_DATA_CHECKSUM -> COMP Status error!\n");
            printf(
                "Check sum error! IOP:%08lX,DVRP:%08lX\n",
                v4,
                (v16.return_result_word[0] << 16) | v16.return_result_word[1]);
            goto LABEL_38;
        }
        v16.command = 20759;
        v16.input_word_count = 0;
        v16.timeout = 10000000;
        if (DvrdrvExecCmdAckComp(&v16)) {
            v8 = "MISCCMD_FLASH_DATA_WRITE -> Handshake error!\n";
            goto LABEL_37;
        }
        if (v16.ack_status) {
            v14 = "MISCCMD_FLASH_DATA_WRITE -> ACK Status error!\n";
        } else {
            v5 = 0;
            if (!v16.comp_status)
                goto LABEL_38;
            v14 = "MISCCMD_FLASH_DATA_WRITE -> COMP Status error!\n";
        }
    }
    v5 = -68;
    printf(v14);
LABEL_38:
    close(v6);
    return v5;
}

s32 dvrioctl2_flash_write_status(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 20760;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("dvrioctl2_flash_write_status -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("dvrioctl2_flash_write_status -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.output_word[0];
        result = 0;
        a5[1] = v6.output_word[1];
    }
    return result;
}

s32 DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1)
{
    s32 result;

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

s32 lseek(s32 fd, s32 pos, s32 mode)
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

s32 devctl(const s8 *name, s32 cmd, void *arg, u32 arglen, void *buf, u32 buflen)
{
    s32 result;

    return result;
}

s32 printf(const s8 *format, ...)
{
    s32 result;

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
