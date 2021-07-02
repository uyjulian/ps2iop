



s32 irx_entry_point(s32 a1);
s32 module_start();
s32 module_stop();
s32 dvr_df_init();
s32 dvr_df_exit();
s32 dvr_df_ioctl();
s32 dvr_df_devctl(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
s32 dvr_df_ioctl2();
s32 dvr_df_null();
s64 dvr_df_null_long();
s32 dvrioctl2_rec_start(s32 a1, s32 a2, s32 a3, u16 *a4);
s32 dvrioctl2_rec_pause(s32 a1, s32 a2, s32 a3, u16 *a4);
s32 dvrioctl2_rec_stop();
s32 dvrioctl2_set_rec_end_time(s32 a1, s32 a2, s32 a3, u32 *a4);
s32 dvrioctl2_get_rec_info(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, u32 a7);
s32 dvrioctl2_get_rec_time(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
s32 dvrioctl2_get_ifo_time_entry(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
s32 dvrioctl2_get_ifo_vobu_entry(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u16 *a6);
s32 dvrioctl2_read_resfile();
s32 dvrioctl2_clear_resfile_flag();
s32 dvrioctl2_rec_prohibit(s32 a1, s32 a2, s32 a3, u16 *a4);
s32 dvrioctl2_epg_test(s32 a1, s32 a2, s32 a3, u16 *a4);
s32 dvrioctl2_send_timer_event(s32 a1, s32 a2, s32 a3, u32 a4, u32 a5);
s32 dvrioctl2_epg_cancel(s32 a1, s32 a2, s32 a3, u16 *a4);
s32 dvrioctl2_get_status_register(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u16 *a6);
s32 dvrioctl2_tevent_buf_clr();
s32 dvrioctl2_tevent_buf_send(s32 a1, s32 a2, s32 a3, u8 *a4, s32 a5);
s32 dvrioctl2_tevent_buf_trans_dvrp();
s32 dvrioctl2_start_hdd_test(s32 a1, s32 a2, s32 a3, u16 *a4);
s32 dvrioctl2_stop_hdd_test();
s32 dvrioctl2_get_hdd_test_stat(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
s32 dvrioctl2_pre_update_a(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u16 *a6);
s32 dvrioctl2_pre_update_b(s32 a1, s32 a2, s32 a3, u16 *a4);
s32 dvrioctl2_get_rec_vro_pckn(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u32 *a6);
s32 dvrioctl2_enc_dec_test(s32 a1, s32 a2, s32 a3, u16 *a4);
s32 dvrioctl2_make_menu(s32 a1, s32 a2, s32 a3, u16 *a4, s32 a5, s32 a6);
s32 dvrioctl2_re_enc_start(s32 a1, s32 a2, s32 a3, u16 *a4, s32 a5, s32 a6);
s32 dvrpAuthEnc(u16 a1);
s32 DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckComp(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1);
s32 AddDrv(iop_device_t *device);
s32 DelDrv(const s8 *name);
s32 printf(const s8 *format, ...);
s32 DelayThread(s32 usec);
s32 CreateSema(iop_sema_t *sema);
s32 DeleteSema(s32 sema_id);
s32 SignalSema(s32 sema_id);
s32 WaitSema(s32 sema_id);


_UNKNOWN loc_4;
_UNKNOWN loc_14;
_UNKNOWN loc_1C;
s8 dvrpAuth_tbl[] = {'\x9D'};
s32 (*DvrFuncTbl[23])() =
    {
        &dvr_df_init,
        &dvr_df_exit,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_ioctl,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null,
        &dvr_df_null_long};
s32 TEVENT_BUF[1535];
s8 byte_3CDF;
s32 tevent_p;
s32 tevent_data_sz;
iop_device_t DVR;
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
        if (((*((vu32 *)0xB0004230)) & 0x10) != 0)
            break;
        DelayThread(1000);
    }
    if (i == 30000) {
        printf("DVR task of DVRP is not running...\n");
        result = 1;
    } else {
        DVR.name = "dvr";
        DVR.desc = "Digital Video Recorder DVR task";
        DVR.type = 268435472;
        DVR.ops = (struct _iop_device_ops *)DvrFuncTbl;
        v1 = AddDrv(&DVR) == 0;
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

    v0 = DelDrv("dvr") == 0;
    result = 1;
    if (!v0)
        result = 2;
    return result;
}

s32 dvr_df_init()
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

s32 dvr_df_exit()
{
    bool v0;
    s32 result;

    v0 = DeleteSema(sema_id) == 0;
    result = 0;
    if (!v0)
        result = -1;
    return result;
}

s32 dvr_df_ioctl()
{
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

s32 dvr_df_devctl(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    s32 v11;
    u32 v12;
    s32 v13;

    v11 = 0;
    v12 = 0;
    WaitSema(sema_id);
    v13 = 0;
    while (*(u16 *)(v13 + 9112) != a3) {
        ++v12;
        v13 = 8 * v12;
        if (v12 >= 0x1B)
            goto LABEL_5;
    }
    v11 = (*(s32(**)(s32, s32, s32, s32, s32, s32, s32))(v13 + 9116))(a1, a2, a3, a4, a5, a6, a7);
LABEL_5:
    if (v12 == 27)
        v11 = -22;
    SignalSema(sema_id);
    return v11;
}

s32 dvr_df_ioctl2()
{
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

s32 dvr_df_null()
{
    return -48;
}

s64 dvr_df_null_long()
{
    return -48LL;
}

s32 dvrioctl2_rec_start(s32 a1, s32 a2, s32 a3, u16 *a4)
{
    s8 *v4;
    s32 v6;
    s32 result;
    s32 v8;
    drvdrv_exec_cmd_ack v9;

    v9.command = 8449;
    v9.input_word[0] = a4[1];
    v9.input_word[1] = *a4;
    v9.input_word[2] = a4[3];
    v9.input_word[3] = a4[2];
    v9.input_word[4] = a4[4];
    v9.input_word[5] = a4[5];
    v9.input_word[6] = a4[6];
    v4 = (s8 *)&loc_4;
    while ((s32)v4-- >= 0)
        ;
    v9.input_word_count = 7;
    v9.timeout = 5000000;
    v6 = DvrdrvExecCmdAckComp(&v9);
    if (v6) {
        printf("dvrioctl2_rec_start -> Handshake error!,%d\n", v6);
        return -5;
    }
    v8 = v9.ack_status;
    if (!v9.ack_status) {
        result = 0;
        if (!v9.comp_status)
            return result;
        v8 = v9.comp_status;
    }
    printf("dvrioctl2_rec_start -> Status error!,%04X\n", v8);
    return -68;
}

s32 dvrioctl2_rec_pause(s32 a1, s32 a2, s32 a3, u16 *a4)
{
    s32 v4;
    drvdrv_exec_cmd_ack *v5;
    u16 v6;
    s32 v7;
    s32 result;
    drvdrv_exec_cmd_ack v9;

    v4 = 0;
    v5 = &v9;
    v9.command = 8450;
    do {
        v6 = *a4++;
        ++v4;
        v5->input_word[0] = v6;
        v5 = (drvdrv_exec_cmd_ack *)((s8 *)v5 + 2);
    } while (v4 <= 0);
    v9.input_word_count = 1;
    v7 = DvrdrvExecCmdAck(&v9);
    if (v7) {
        printf("dvrioctl2_rec_pause -> Handshake error!,%d\n", v7);
        result = -5;
    } else {
        result = 0;
        if (v9.ack_status) {
            printf("dvrioctl2_rec_pause -> Status error!,%04X\n", v9.ack_status);
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_rec_stop()
{
    s32 v0;
    s32 result;
    drvdrv_exec_cmd_ack v2;

    v2.command = 8451;
    v2.input_word_count = 0;
    v2.timeout = 5000000;
    v0 = DvrdrvExecCmdAckComp(&v2);
    if (v0) {
        printf("dvrioctl2_rec_stop -> Handshake error!,%d\n", v0);
        return -5;
    }
    if (v2.ack_status) {
        printf("dvrioctl2_rec_stop -> Status error!,%04X\n", v2.ack_status);
    } else {
        result = 0;
        if (!v2.comp_status)
            return result;
        printf("dvrioctl2_rec_start -> Status error!,%04X\n", v2.comp_status);
    }
    return -68;
}

s32 dvrioctl2_set_rec_end_time(s32 a1, s32 a2, s32 a3, u32 *a4)
{
    u16 v4;
    s32 v5;
    s32 result;
    drvdrv_exec_cmd_ack v7;

    v7.command = 8452;
    v7.input_word[0] = HIWORD(*a4);
    v4 = *(u16 *)a4;
    v7.input_word_count = 2;
    v7.input_word[1] = v4;
    v5 = DvrdrvExecCmdAck(&v7);
    if (v5) {
        printf("dvrioctl2_rec_end_time -> Handshake error!,%d\n", v5);
        result = -5;
    } else {
        result = 0;
        if (v7.ack_status) {
            printf("dvrioctl2_rec_end_time -> Status error!,%04X\n", v7.ack_status);
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_get_rec_info(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, u32 a7)
{
    s32 result;
    s32 v8;
    s32 v9;
    s32 v10;
    u16 *v11;
    drvdrv_exec_cmd_ack v12;

    if (a7 >= 0x15) {
        v12.command = 8453;
        v12.input_word_count = 0;
        v8 = DvrdrvExecCmdAck(&v12);
        if (v8) {
            printf("dvrioctl2_get_rec_info -> Handshake error!,%d\n", v8);
            result = -5;
        } else {
            v9 = 0;
            if (v12.ack_status) {
                printf("dvrioctl2_get_rec_info -> Status error!,%04X\n", v12.ack_status);
                result = -68;
            } else {
                *(u16 *)a6 = 0;
                v10 = 0;
                do {
                    ++v9;
                    v11 = &v12.command + v9;
                    *(u8 *)(a6 + v10 + 1 + 2) = HIBYTE(v11[69]);
                    *(u8 *)(a6 + v10 + 2) = *((u8 *)v11 + 138);
                    v10 = 2 * v9;
                } while (v9 < 10);
                *(u8 *)(a6 + 22) = 0;
                result = 0;
            }
        }
    } else {
        printf("dvrioctl2_get_rec_info -> buflen is smaller than 21.\n");
        result = -22;
    }
    return result;
}

s32 dvrioctl2_get_rec_time(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6)
{
    s32 v6;
    s32 result;
    drvdrv_exec_cmd_ack v8;

    v8.command = 8454;
    v8.input_word_count = 0;
    v6 = DvrdrvExecCmdAck(&v8);
    if (v6) {
        printf("dvrioctl2_get_rec_time -> Handshake error!,%d\n", v6);
        result = -5;
    } else {
        result = 0;
        if (v8.ack_status) {
            printf("dvrioctl2_get_rec_time -> Status error!,%04X\n", v8.ack_status);
            result = -68;
        } else {
            *(u16 *)a6 = 0;
            *(u32 *)(a6 + 4) = (v8.output_word[0] << 16) + v8.output_word[1];
        }
    }
    return result;
}

s32 dvrioctl2_get_ifo_time_entry(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6)
{
    s32 v6;
    s32 result;
    drvdrv_exec_cmd_ack v8;

    v8.command = 8455;
    v8.input_word_count = 0;
    v6 = DvrdrvExecCmdAck(&v8);
    if (v6) {
        printf("dvrioctl2_get_ifo_time_entry -> Handshake error!,%d\n", v6);
        result = -5;
    } else if (v8.ack_status) {
        printf("dvrioctl2_get_ifo_time_entry -> Status error!,%04X\n", v8.ack_status);
        result = -68;
    } else {
        *(u16 *)a6 = 0;
        *(u16 *)(a6 + 2) = v8.output_word[0];
        *(u16 *)(a6 + 4) = v8.output_word[1];
        result = 0;
        *(u16 *)(a6 + 6) = v8.output_word[2];
        *(u32 *)(a6 + 8) = (v8.output_word[3] << 16) + v8.output_word[4];
    }
    return result;
}

s32 dvrioctl2_get_ifo_vobu_entry(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u16 *a6)
{
    s32 v6;
    s32 result;
    drvdrv_exec_cmd_ack v8;

    v8.command = 8456;
    v8.input_word_count = 0;
    v6 = DvrdrvExecCmdAck(&v8);
    if (v6) {
        printf("dvrioctl2_get_ifo_vobu_entry -> Handshake error!,%d\n", v6);
        result = -5;
    } else if (v8.ack_status) {
        printf("dvrioctl2_get_ifo_vobu_entry -> Status error!,%04X\n", v8.ack_status);
        result = -68;
    } else {
        *a6 = 0;
        a6[1] = v8.output_word[0];
        a6[2] = v8.output_word[1];
        result = 0;
        a6[3] = v8.output_word[2];
    }
    return result;
}

s32 dvrioctl2_read_resfile()
{
    s32 v0;
    s32 result;
    drvdrv_exec_cmd_ack v2;

    v2.command = 8457;
    v2.input_word_count = 0;
    v0 = DvrdrvExecCmdAck(&v2);
    if (v0) {
        printf("dvrioctl2_read_resfile -> Handshake error!,%d\n", v0);
        result = -5;
    } else {
        result = 0;
        if (v2.ack_status) {
            printf("dvrioctl2_read_resfile -> Status error!,%04X\n", v2.ack_status);
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_clear_resfile_flag()
{
    s32 v0;
    s32 result;
    drvdrv_exec_cmd_ack v2;

    v2.command = 8458;
    v2.input_word_count = 0;
    v0 = DvrdrvExecCmdAck(&v2);
    if (v0) {
        printf("dvrioctl2_clear_resfile_flag -> Handshake error!,%d\n", v0);
        result = -5;
    } else {
        result = 0;
        if (v2.ack_status) {
            printf("dvrioctl2_clear_resfile_flag -> Status error!,%04X\n", v2.ack_status);
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_rec_prohibit(s32 a1, s32 a2, s32 a3, u16 *a4)
{
    u16 v4;
    s32 v5;
    s32 result;
    drvdrv_exec_cmd_ack v7;

    v7.command = 8462;
    v4 = *a4;
    v7.input_word_count = 1;
    v7.input_word[0] = v4;
    v5 = DvrdrvExecCmdAck(&v7);
    if (v5) {
        printf("dvrioctl2_rec_prohibit -> Handshake error!,%d\n", v5);
        result = -5;
    } else {
        result = 0;
        if (v7.ack_status) {
            printf("dvrioctl2_rec_prohibit -> Status error!,%04X\n", v7.ack_status);
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_epg_test(s32 a1, s32 a2, s32 a3, u16 *a4)
{
    u16 v4;
    s32 v5;
    s32 result;
    drvdrv_exec_cmd_ack v7;

    v7.command = 8463;
    v4 = *a4;
    v7.input_word_count = 1;
    v7.input_word[0] = v4;
    v5 = DvrdrvExecCmdAck(&v7);
    if (v5) {
        printf("dvrioctl2_epg_test -> Handshake error!,%d\n", v5);
        result = -5;
    } else {
        result = 0;
        if (v7.ack_status) {
            printf("dvrioctl2_epg_test -> Status error!,%04X\n", v7.ack_status);
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_send_timer_event(s32 a1, s32 a2, s32 a3, u32 a4, u32 a5)
{
    s32 v5;
    s32 result;
    drvdrv_exec_cmd_ack v7;

    v5 = 0;
    v7.command = 8464;
    v7.input_word_count = 0;
    v7.input_buffer = a4;
    v7.timeout = 10000000;
    v7.input_buffer_length = a5;
    if (DvrdrvExecCmdAckDmaSendComp(&v7)) {
        printf("dvrioctl2_send_timer_event -> IO error (phase %d)\n", v7.phase);
        result = -5;
    } else {
        if (v7.comp_status) {
            v5 = -5;
            printf("dvrioctl2_send_timer_event -> Complete parameter (%04X) error (phase %d)\n", v7.comp_status, v7.phase);
        }
        result = v5;
    }
    return result;
}

s32 dvrioctl2_epg_cancel(s32 a1, s32 a2, s32 a3, u16 *a4)
{
    u16 v4;
    s32 v5;
    s32 result;
    drvdrv_exec_cmd_ack v7;

    v7.command = 8465;
    v4 = *a4;
    v7.input_word_count = 0;
    v7.input_word[0] = v4;
    v5 = DvrdrvExecCmdAck(&v7);
    if (v5) {
        printf("dvrioctl2_epg_cancel -> Handshake error!,%d\n", v5);
        result = -5;
    } else {
        result = 0;
        if (v7.ack_status) {
            printf("dvrioctl2_epg_cancel -> Status error!,%04X\n", v7.ack_status);
            result = -68;
        }
    }
    return result;
}

s32 dvrioctl2_get_status_register(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u16 *a6)
{
    s16 v6;
    s16 v7;

    *a6 = (*((vu32 *)0xB0004230));
    v6 = (*((vu32 *)0xB0004238));
    v7 = (*((vu32 *)0xB000423C));
    a6[1] = (*((vu32 *)0xB0004234));
    a6[2] = v6;
    a6[3] = v7;
    return 0;
}

s32 dvrioctl2_tevent_buf_clr()
{
    s32 v0;
    s8 *v1;

    v0 = 6143;
    v1 = &byte_3CDF;
    do {
        *v1 = 0;
        --v0;
        --v1;
    } while (v0 >= 0);
    tevent_p = (s32)TEVENT_BUF;
    tevent_data_sz = 0;
    return 0;
}

s32 dvrioctl2_tevent_buf_send(s32 a1, s32 a2, s32 a3, u8 *a4, s32 a5)
{
    s32 i;
    s32 v6;

    if (tevent_data_sz + a5 >= 6145)
        return 0;
    for (i = 0; i < a5; ++a4) {
        v6 = tevent_p;
        ++i;
        *(u8 *)tevent_p = *a4;
        tevent_p = v6 + 1;
    }
    tevent_data_sz += a5;
    return 0;
}

s32 dvrioctl2_tevent_buf_trans_dvrp()
{
    s32 v0;
    s32 result;
    drvdrv_exec_cmd_ack v2;

    v0 = 0;
    v2.command = 8464;
    v2.input_word_count = 0;
    v2.input_buffer = (u32)TEVENT_BUF;
    v2.timeout = 10000000;
    v2.input_buffer_length = tevent_data_sz;
    if (DvrdrvExecCmdAckDmaSendComp(&v2)) {
        printf("dvrioctl2_tevent_buf_trans_dvrp -> IO error (phase %d)\n", v2.phase);
        result = -5;
    } else {
        if (v2.comp_status) {
            v0 = -5;
            printf(
                "dvrioctl2_tevent_buf_trans_dvrp -> Complete parameter (%04X) error (phase %d)\n",
                v2.comp_status,
                v2.phase);
        }
        result = v0;
    }
    return result;
}

s32 dvrioctl2_start_hdd_test(s32 a1, s32 a2, s32 a3, u16 *a4)
{
    u16 v4;
    s32 v5;
    s32 result;
    s32 v7;
    drvdrv_exec_cmd_ack v8;

    v8.command = 8466;
    v8.input_word[0] = *a4;
    v8.input_word[1] = a4[3];
    v8.input_word[2] = a4[2];
    v8.input_word[3] = a4[5];
    v8.input_word[4] = a4[4];
    v8.input_word[5] = a4[6];
    v8.input_word[6] = a4[7];
    v4 = a4[8];
    v8.input_word_count = 8;
    v8.input_word[7] = v4;
    v8.timeout = 1000000 * (a4[8] + 30);
    v5 = DvrdrvExecCmdAckComp(&v8);
    if (v5) {
        printf("dvrioctl2_start_hdd_test -> Handshake error!,%d\n", v5);
        return -5;
    }
    v7 = v8.ack_status;
    if (!v8.ack_status) {
        result = 0;
        if (!v8.comp_status)
            return result;
        v7 = v8.comp_status;
    }
    printf("dvrioctl2_start_hdd_test -> Status error!,%04X\n", v7);
    return -68;
}

s32 dvrioctl2_stop_hdd_test()
{
    s32 v0;
    s32 result;
    s32 v2;
    drvdrv_exec_cmd_ack v3;

    v3.command = 8467;
    v3.input_word_count = 0;
    v3.timeout = 30000000;
    v0 = DvrdrvExecCmdAckComp(&v3);
    if (v0) {
        printf("dvrioctl2_stop_hdd_test -> Handshake error!,%d\n", v0);
        return -5;
    }
    v2 = v3.ack_status;
    if (!v3.ack_status) {
        result = 0;
        if (!v3.comp_status)
            return result;
        v2 = v3.comp_status;
    }
    printf("dvrioctl2_stop_hdd_test -> Status error!,%04X\n", v2);
    return -68;
}

s32 dvrioctl2_get_hdd_test_stat(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6)
{
    s32 v6;
    s32 result;
    drvdrv_exec_cmd_ack v8;

    v8.command = 8468;
    v8.input_word_count = 0;
    v6 = DvrdrvExecCmdAck(&v8);
    if (v6) {
        printf("dvrioctl2_get_hdd_test_stat -> Handshake error!,%d\n", v6);
        result = -5;
    } else if (v8.ack_status) {
        printf("dvrioctl2_get_hdd_test_stat -> Status error!,%04X\n", v8.ack_status);
        result = -68;
    } else {
        *(u16 *)a6 = v8.output_word[0];
        *(u32 *)(a6 + 4) = (v8.output_word[1] << 16) + v8.output_word[2];
        *(u32 *)(a6 + 8) = (v8.output_word[3] << 16) + v8.output_word[4];
        *(u16 *)(a6 + 12) = v8.output_word[5];
        *(u16 *)(a6 + 14) = v8.output_word[6];
        result = 0;
        *(u16 *)(a6 + 16) = v8.output_word[7];
    }
    return result;
}

s32 dvrioctl2_pre_update_a(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u16 *a6)
{
    s32 v6;
    s32 result;
    drvdrv_exec_cmd_ack v8;

    v8.command = 8469;
    v8.input_word_count = 0;
    v6 = DvrdrvExecCmdAck(&v8);
    if (v6) {
        printf("dvrioctl2_pre_update_a -> Handshake error!,%d\n", v6);
        result = -5;
    } else if (v8.ack_status) {
        printf("dvrioctl2_pre_update_a -> Status error!,%04X\n", v8.ack_status);
        result = -68;
    } else {
        *a6 = dvrpAuthEnc(v8.output_word[0]);
        result = 0;
    }
    return result;
}

s32 dvrioctl2_pre_update_b(s32 a1, s32 a2, s32 a3, u16 *a4)
{
    u16 v4;
    s32 v5;
    s32 result;
    s32 v7;
    drvdrv_exec_cmd_ack v8;

    v8.command = 8470;
    v4 = *a4;
    v8.input_word_count = 1;
    v8.timeout = 10000000;
    v8.input_word[0] = v4;
    v5 = DvrdrvExecCmdAckComp(&v8);
    if (v5) {
        printf("dvrioctl2_pre_update_b -> Handshake error!,%d\n", v5);
        return -5;
    }
    v7 = v8.ack_status;
    if (!v8.ack_status) {
        result = 0;
        if (!v8.comp_status)
            return result;
        v7 = v8.comp_status;
    }
    printf("dvrioctl2_pre_update_b -> Status error!,%04X\n", v7);
    return -68;
}

s32 dvrioctl2_get_rec_vro_pckn(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u32 *a6)
{
    s32 v6;
    s32 result;
    drvdrv_exec_cmd_ack v8;

    v8.command = 8471;
    v8.input_word_count = 0;
    v6 = DvrdrvExecCmdAck(&v8);
    if (v6) {
        printf("dvrioctl2_get_rec_vro_pckn -> Handshake error!,%d\n", v6);
        return -5;
    }
    if (v8.ack_status == 65534) {
        printf("dvrioctl2_get_rec_vro_pckn -> Mode error!,%04X\n", 65534);
    } else {
        result = 0;
        if (!v8.ack_status) {
            *a6 = (v8.output_word[0] << 16) + v8.output_word[1];
            return result;
        }
        printf("dvrioctl2_get_rec_vro_pckn -> Status error!,%04X\n", v8.ack_status);
    }
    return -68;
}

s32 dvrioctl2_enc_dec_test(s32 a1, s32 a2, s32 a3, u16 *a4)
{
    u16 v4;
    s32 v5;
    s32 result;
    drvdrv_exec_cmd_ack v7;

    v7.command = 8472;
    v4 = *a4;
    v7.input_word_count = 1;
    v7.timeout = 10000000;
    v7.input_word[0] = v4;
    v5 = DvrdrvExecCmdAckComp(&v7);
    if (v5) {
        printf("dvrioctl2_enc_dec_test -> ACK Handshake error!,%d\n", v5);
        return -5;
    }
    if (v7.ack_status) {
        printf("dvrioctl2_enc_dec_test -> ACK Status error!,%04X\n", v7.ack_status);
    } else {
        result = 0;
        if (!v7.comp_status)
            return result;
        printf("dvrioctl2_enc_dec_test -> COMP Status error!,%04X\n", v7.comp_status);
    }
    return -68;
}

s32 dvrioctl2_make_menu(s32 a1, s32 a2, s32 a3, u16 *a4, s32 a5, s32 a6)
{
    s32 v6;
    s32 v7;
    s32 v8;
    u16 v9;
    u16 *v10;
    s8 *v11;
    u16 *v12;
    s32 v13;
    s32 v15;
    s32 v16;
    u16 *v17;
    s32 v18;
    s32 v19;
    s32 v20;
    s8 *v21;
    drvdrv_exec_cmd_ack v23;

    v23.command = 8473;
    v23.input_word[0] = a4[1];
    v6 = 6;
    v23.input_word[1] = *a4;
    v7 = 1;
    v23.input_word[2] = a4[3];
    v8 = 0;
    v23.input_word[3] = a4[2];
    v9 = a4[4];
    v10 = &v23.input_word[5];
    v23.input_word[5] = 0;
    v23.input_word[4] = v9;
    do {
        v11 = (s8 *)a4 + v7;
        v7 += 2;
        v12 = &a4[v8++];
        ++v6;
        v10[1] = *((s8 *)v12 + 10) + ((u8)v11[10] << 8);
        ++v10;
    } while (v6 < 16);
    v23.input_word_count = 16;
    v23.timeout = 30000000;
    v13 = DvrdrvExecCmdAckComp(&v23);
    *(u16 *)a6 = v23.comp_status;
    if (v13) {
        printf("dvrioctl2_make_menu -> ACK Handshake error!,%d\n", v13);
        return -5;
    }
    if (v23.ack_status) {
        printf("dvrioctl2_make_menu -> ACK Status error!,%04X\n", v23.ack_status);
        return -68;
    }
    v15 = 1;
    if (v23.comp_status) {
        printf("dvrioctl2_make_menu -> COMP Status error!,%04X\n", v23.comp_status);
        return -68;
    }
    v16 = 1;
    v17 = v23.input_word;
    v18 = 0;
    do {
        v19 = a6 + v16;
        v16 += 2;
        v20 = a6 + v18;
        v18 += 2;
        ++v15;
        *(u8 *)(v20 + 2) = *((u8 *)v17 + 274);
        *(u8 *)(v19 + 2) = HIBYTE(v17[137]);
        ++v17;
    } while (v15 < 11);
    *(u8 *)(a6 + 22) = 0;
    v21 = (s8 *)&loc_14;
    while ((s32)v21-- >= 0)
        ;
    return 0;
}

s32 dvrioctl2_re_enc_start(s32 a1, s32 a2, s32 a3, u16 *a4, s32 a5, s32 a6)
{
    s32 v6;
    s32 v7;
    s32 v8;
    u16 *v9;
    s8 *v10;
    u16 *v11;
    s32 v12;
    s32 v13;
    s32 v14;
    u16 *v15;
    s8 *v16;
    u16 *v17;
    u16 v18;
    s8 *v19;
    s32 v21;
    s32 v23;
    s32 v24;
    u16 *v25;
    s32 v26;
    s32 v27;
    s32 v28;
    drvdrv_exec_cmd_ack v29;

    v29.command = 8474;
    v29.input_word[0] = a4[1];
    v29.input_word[1] = *a4;
    v29.input_word[2] = a4[3];
    v6 = 7;
    v29.input_word[3] = a4[2];
    v7 = 1;
    v29.input_word[4] = a4[4];
    v8 = 0;
    v29.input_word[5] = a4[5];
    v9 = &v29.input_word[6];
    v29.input_word[6] = a4[6];
    do {
        v10 = (s8 *)a4 + v7;
        v7 += 2;
        v11 = &a4[v8++];
        ++v6;
        v9[1] = *((s8 *)v11 + 14) + ((u8)v10[14] << 8);
        ++v9;
    } while (v6 < 17);
    v29.input_word[17] = 0;
    v12 = 18;
    v13 = 1;
    v14 = 0;
    v15 = &v29.input_word[17];
    do {
        v16 = (s8 *)a4 + v13;
        v13 += 2;
        v17 = &a4[v14++];
        ++v12;
        v15[1] = *((s8 *)v17 + 35) + ((u8)v16[35] << 8);
        ++v15;
    } while (v12 < 28);
    v29.input_word[28] = a4[28];
    v29.input_word[29] = a4[29];
    v29.input_word[30] = a4[30];
    v18 = a4[31];
    v29.input_word[32] = 0;
    v29.input_word[26] = 0;
    v29.input_word[27] = 0;
    v29.input_word[31] = v18;
    v19 = (s8 *)&loc_1C + 3;
    while ((s32)v19-- >= 0)
        ;
    v29.input_word_count = 33;
    v29.timeout = 30000000;
    v21 = DvrdrvExecCmdAckComp(&v29);
    *(u16 *)a6 = v29.comp_status;
    if (v21) {
        printf("dvrioctl2_re_enc_start -> ACK Handshake error!,%d\n", v21);
        return -5;
    }
    if (v29.ack_status) {
        printf("dvrioctl2_re_enc_start -> ACK Status error!,%04X\n", v29.ack_status);
        return -68;
    }
    v23 = 2;
    if (v29.comp_status) {
        printf("dvrioctl2_re_enc_start -> COMP Status error!,%04X\n", v29.comp_status);
        return -68;
    }
    v24 = 1;
    v25 = &v29.input_word[1];
    v26 = 0;
    do {
        v27 = a6 + v24;
        v24 += 2;
        v28 = a6 + v26;
        v26 += 2;
        ++v23;
        *(u8 *)(v28 + 2) = *((u8 *)v25 + 274);
        *(u8 *)(v27 + 2) = HIBYTE(v25[137]);
        ++v25;
    } while (v23 < 12);
    *(u8 *)(a6 + 22) = 0;
    return 0;
}

s32 dvrpAuthEnc(u16 a1)
{
    return (u8)dvrpAuth_tbl[(u8)a1] | ((u8)dvrpAuth_tbl[HIBYTE(a1)] << 8);
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
