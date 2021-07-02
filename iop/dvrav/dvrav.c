



s32 irx_entry_point(s32 a1);
s32 module_start();
s32 module_stop();
s32 dvrav_df_init();
s32 dvrav_df_exit();
s32 dvrav_df_ioctl();
s32 dvrav_df_devctl(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
s32 dvrav_df_ioctl2();
s32 dvrav_df_null();
__int64 dvrav_df_null_long();
s32 avioctl2_get_tun_offset(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_tun_offset_up(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_tun_offset_down(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_tun_scan_ch(s32 a1, s32 a2, u16 *a3, s32 a4, u16 *a5);
s32 avioctl2_get_bs_gain(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_set_preset_info(s32 a1, s32 a2, u16 *a3);
s32 avioctl2_change_sound(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_set_d_audio_sel(s32 a1, s32 a2, u16 *a3);
s32 avioctl2_set_d_video_sel(s32 a1, s32 a2, u16 *a3);
s32 avioctl2_get_av_src(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_get_preset_info(s32 a1, s32 a2, u16 *a3, s32 a4, u16 *a5);
s32 avioctl2_select_position(s32 a1, s32 a2, u16 *a3);
s32 avioctl2_position_up(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_position_down(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_get_position(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 avioctl2_set_position_info(s32 a1, s32 a2, u16 *a3);
s32 avioctl2_get_position_info(s32 a1, s32 a2, u16 *a3, s32 a4, u16 *a5);
s32 avioctl2_tun_scan_mode(s32 a1, s32 a2, u16 *a3);
s32 avioctl2_f_select_position(s32 a1, s32 a2, u16 *a3);
s32 avioctl2_select_rec_src(s32 a1, s32 a2, u16 *a3);
s32 avioctl2_get_rec_src(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5);
s32 DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckComp(drvdrv_exec_cmd_ack *a1);
s32 AddDrv(iop_device_t *device);
s32 DelDrv(const s8 *name);
s32 printf(const s8 *format, ...);
s32 DelayThread(s32 usec);
s32 CreateSema(iop_sema_t *sema);
s32 DeleteSema(s32 sema_id);
s32 SignalSema(s32 sema_id);
s32 WaitSema(s32 sema_id);


s32 (*DvrFuncTbl[23])() =
    {
        &dvrav_df_init,
        &dvrav_df_exit,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_ioctl,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_null_long};
iop_device_t DVRAV;
s32 sema_id;


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
        if (((*((vu32 *)0xB0004230)) & 8) != 0)
            break;
        DelayThread(1000);
    }
    if (i == 30000) {
        printf("AV task of DVRP is not running...\n");
        result = 1;
    } else {
        DVRAV.name = "dvr_av";
        DVRAV.desc = "Digital Video Recorder AV task";
        DVRAV.type = 268435472;
        DVRAV.ops = (struct _iop_device_ops *)DvrFuncTbl;
        v1 = AddDrv(&DVRAV) == 0;
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

    v0 = DelDrv("dvr_av") == 0;
    result = 1;
    if (!v0)
        result = 2;
    return result;
}

s32 dvrav_df_init()
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

s32 dvrav_df_exit()
{
    bool v0;
    s32 result;

    v0 = DeleteSema(sema_id) == 0;
    result = 0;
    if (!v0)
        result = -1;
    return result;
}

s32 dvrav_df_ioctl()
{
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

s32 dvrav_df_devctl(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    s32 v10;
    u32 v11;
    s32 v12;

    v10 = 0;
    v11 = 0;
    WaitSema(sema_id);
    v12 = 0;
    while (*(u16 *)(v12 + 6088) != a3) {
        ++v11;
        v12 = 8 * v11;
        if (v11 >= 0x15)
            goto LABEL_5;
    }
    v10 = (*(s32(**)(s32, s32, s32, s32, s32, s32))(v12 + 6092))(a1, a3, a4, a5, a6, a7);
LABEL_5:
    if (v11 == 21)
        v10 = -22;
    SignalSema(sema_id);
    return v10;
}

s32 dvrav_df_ioctl2()
{
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

s32 dvrav_df_null()
{
    return -48;
}

__int64 dvrav_df_null_long()
{
    return -48LL;
}

s32 avioctl2_get_tun_offset(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12546;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_get_tun_offset -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("avioctl2_get_tun_offset -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.output_word[0];
        result = 0;
        a5[1] = v6.output_word[1];
    }
    return result;
}

s32 avioctl2_tun_offset_up(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12547;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_tun_offset_up -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("avioctl2_tun_offset_up -> Status error!\n");
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

s32 avioctl2_tun_offset_down(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12548;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_tun_offset_down -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("avioctl2_tun_offset_down -> Status error!\n");
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

s32 avioctl2_tun_scan_ch(s32 a1, s32 a2, u16 *a3, s32 a4, u16 *a5)
{
    u16 v5;
    s32 result;
    drvdrv_exec_cmd_ack v7;

    v7.command = 12549;
    v7.input_word[0] = *a3;
    v7.input_word[1] = a3[1];
    v5 = a3[2];
    v7.input_word_count = 3;
    v7.timeout = 35000000;
    v7.input_word[2] = v5;
    if (DvrdrvExecCmdAckComp(&v7)) {
        printf("avioctl2_tun_scan_ch -> Handshake error!\n");
        result = -5;
    } else if (v7.ack_status || v7.comp_status) {
        printf("avioctl2_tun_scan_ch -> Status error!\n");
        result = -68;
    } else {
        *a5 = v7.return_result_word[0];
        a5[1] = v7.return_result_word[1];
        a5[2] = v7.return_result_word[2];
        a5[3] = v7.return_result_word[3];
        a5[4] = v7.return_result_word[4];
        result = 0;
        a5[5] = v7.return_result_word[5];
    }
    return result;
}

s32 avioctl2_get_bs_gain(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12550;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_get_bs_gain -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v6.ack_status) {
            printf("avioctl2_get_bs_gain -> Status error!\n");
            result = -68;
        } else {
            *a5 = v6.output_word[0];
        }
    }
    return result;
}

s32 avioctl2_set_preset_info(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 12551;
    v5.input_word[0] = *a3;
    v3 = a3[1];
    v5.input_word_count = 2;
    v5.input_word[1] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("avioctl2_set_preset_info -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("avioctl2_set_preset_info -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 avioctl2_change_sound(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12552;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_change_sound -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v6.ack_status) {
            printf("avioctl2_change_sound -> Status error!\n");
            result = -68;
        } else {
            *a5 = v6.output_word[0];
        }
    }
    return result;
}

s32 avioctl2_set_d_audio_sel(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 12553;
    v5.input_word[0] = *a3;
    v5.input_word[1] = a3[1];
    v5.input_word[2] = a3[2];
    v3 = a3[3];
    v5.input_word_count = 4;
    v5.input_word[3] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("avioctl2_set_d_audio_sel -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("avioctl2_set_d_audio_sel -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 avioctl2_set_d_video_sel(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 12554;
    v3 = *a3;
    v5.input_word_count = 1;
    v5.input_word[0] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("avioctl2_set_d_video_sel -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("avioctl2_set_d_video_sel -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 avioctl2_get_av_src(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12555;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_get_av_src -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("avioctl2_get_av_src -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.output_word[0];
        result = 0;
        a5[1] = v6.output_word[1];
    }
    return result;
}

s32 avioctl2_get_preset_info(s32 a1, s32 a2, u16 *a3, s32 a4, u16 *a5)
{
    u16 v5;
    s32 result;
    drvdrv_exec_cmd_ack v7;

    v7.command = 12556;
    v5 = *a3;
    v7.input_word_count = 1;
    v7.input_word[0] = v5;
    if (DvrdrvExecCmdAck(&v7)) {
        printf("avioctl2_get_preset_info -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v7.ack_status) {
            printf("avioctl2_get_preset_info -> Status error!\n");
            result = -68;
        } else {
            *a5 = v7.output_word[0];
        }
    }
    return result;
}

s32 avioctl2_select_position(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 12558;
    v3 = *a3;
    v5.input_word_count = 1;
    v5.input_word[0] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("avioctl2_select_position -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("avioctl2_select_position -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 avioctl2_position_up(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12559;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_position_up -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v6.ack_status) {
            printf("avioctl2_position_up -> Status error!\n");
            result = -68;
        } else {
            *a5 = v6.output_word[0];
        }
    }
    return result;
}

s32 avioctl2_position_down(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12560;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_position_down -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v6.ack_status) {
            printf("avioctl2_position_down -> Status error!\n");
            result = -68;
        } else {
            *a5 = v6.output_word[0];
        }
    }
    return result;
}

s32 avioctl2_get_position(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12561;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_get_position -> Handshake error!\n");
        result = -5;
    } else if (v6.ack_status) {
        printf("avioctl2_get_position -> Status error!\n");
        result = -68;
    } else {
        *a5 = v6.output_word[0];
        printf("Now position = %d\n", v6.output_word[0]);
        result = 0;
    }
    return result;
}

s32 avioctl2_set_position_info(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 12562;
    v5.input_word[0] = *a3;
    v5.input_word[1] = a3[1];
    v5.input_word[2] = a3[2];
    v5.input_word[3] = a3[3];
    v3 = a3[4];
    v5.input_word_count = 5;
    v5.input_word[4] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("avioctl2_set_position_info -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("avioctl2_set_position_info -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 avioctl2_get_position_info(s32 a1, s32 a2, u16 *a3, s32 a4, u16 *a5)
{
    u16 v6;
    s32 result;
    drvdrv_exec_cmd_ack v8;

    v8.command = 12563;
    v6 = *a3;
    v8.input_word_count = 1;
    v8.input_word[0] = v6;
    if (DvrdrvExecCmdAck(&v8)) {
        printf("avioctl2_get_position_info -> Handshake error!\n");
        result = -5;
    } else if (v8.ack_status) {
        printf("avioctl2_get_position_info -> Status error!\n");
        result = -68;
    } else {
        *a5 = *a3;
        a5[1] = v8.output_word[0];
        a5[2] = v8.output_word[1];
        a5[3] = v8.output_word[2];
        result = 0;
        a5[4] = v8.output_word[3];
    }
    return result;
}

s32 avioctl2_tun_scan_mode(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 12564;
    v3 = *a3;
    v5.input_word_count = 1;
    v5.input_word[0] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("avioctl2_tun_scan_mode -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("avioctl2_tun_scan_mode -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 avioctl2_f_select_position(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 12565;
    v3 = *a3;
    v5.input_word_count = 1;
    v5.input_word[0] = v3;
    if (DvrdrvExecCmdAck(&v5)) {
        printf("avioctl2_f_select_position -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v5.ack_status) {
            printf("avioctl2_f_select_position -> Status error!\n");
            result = -68;
        }
    }
    return result;
}

s32 avioctl2_select_rec_src(s32 a1, s32 a2, u16 *a3)
{
    u16 v3;
    s32 result;
    drvdrv_exec_cmd_ack v5;

    v5.command = 12566;
    v3 = *a3;
    v5.input_word_count = 1;
    v5.timeout = 10000000;
    v5.input_word[0] = v3;
    if (DvrdrvExecCmdAckComp(&v5)) {
        printf("avioctl2_select_rec_src -> Handshake error!\n");
        result = -5;
    } else if (v5.ack_status || (result = 0, v5.comp_status)) {
        printf("avioctl2_select_rec_src -> Status error!\n");
        result = -68;
    }
    return result;
}

s32 avioctl2_get_rec_src(s32 a1, s32 a2, s32 a3, s32 a4, u16 *a5)
{
    s32 result;
    drvdrv_exec_cmd_ack v6;

    v6.command = 12567;
    v6.input_word_count = 0;
    if (DvrdrvExecCmdAck(&v6)) {
        printf("avioctl2_get_rec_src -> Handshake error!\n");
        result = -5;
    } else {
        result = 0;
        if (v6.ack_status) {
            printf("avioctl2_get_rec_src -> Status error!\n");
            result = -68;
        } else {
            *a5 = v6.output_word[0];
        }
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
