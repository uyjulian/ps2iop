
#include <stdbool.h>
#include "iomanX.h"
#include "pvrdrv.h"
#include "stdio.h"
#include "thbase.h"
#include "thsemap.h"
#include "speedregs.h"
#include "errno.h"

extern int module_start();
extern int module_stop();
extern int dvrav_df_init(iop_device_t *dev);
extern int dvrav_df_exit(iop_device_t *dev);
extern int dvrav_df_ioctl(iop_file_t *f, int cmd, void *param);
extern int dvrav_df_devctl(iop_file_t *a1, const char *name, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrav_df_ioctl2(iop_file_t *f, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int dvrav_df_null();
extern s64 dvrav_df_null_long();
extern int avioctl2_select_position(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_get_position(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_position_up(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_position_down(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_set_d_audio_sel(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_get_tun_offset(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_tun_offset_up(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_tun_offset_down(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_tun_scan_ch(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_get_bs_gain(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_set_preset_info(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_change_sound(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_set_d_video_sel(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_get_av_src(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_get_preset_info(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_set_position_info(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_get_position_info(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_tun_scan_mode(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_f_select_position(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_select_rec_src(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);
extern int avioctl2_get_rec_src(iop_file_t *a1, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen);

struct DevctlCmdTbl_t
{
    u16 cmd;
    int (*fn)(iop_file_t *, int, void *, unsigned int, void *, unsigned int);
} DevctlCmdTbl[21] =
    {
        {22038u, &avioctl2_select_position},
        {22041u, &avioctl2_get_position},
        {22039u, &avioctl2_position_up},
        {22040u, &avioctl2_position_down},
        {22034u, &avioctl2_set_d_audio_sel},
        {22027u, &avioctl2_get_tun_offset},
        {22028u, &avioctl2_tun_offset_up},
        {22029u, &avioctl2_tun_offset_down},
        {22030u, &avioctl2_tun_scan_ch},
        {22031u, &avioctl2_get_bs_gain},
        {22032u, &avioctl2_set_preset_info},
        {22033u, &avioctl2_change_sound},
        {22035u, &avioctl2_set_d_video_sel},
        {22036u, &avioctl2_get_av_src},
        {22037u, &avioctl2_get_preset_info},
        {22042u, &avioctl2_set_position_info},
        {22043u, &avioctl2_get_position_info},
        {22044u, &avioctl2_tun_scan_mode},
        {22045u, &avioctl2_f_select_position},
        {22046u, &avioctl2_select_rec_src},
        {22047u, &avioctl2_get_rec_src}};

struct _iop_device_ops DvrFuncTbl =
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
        &dvrav_df_null_long,
        &dvrav_df_devctl,
        &dvrav_df_null,
        &dvrav_df_null,
        &dvrav_df_ioctl2};
iop_device_t DVRAV;
s32 sema_id;

// Based off of DESR / PSX DVR system software version 1.31.
#define MODNAME "DVRAV"
IRX_ID(MODNAME, 1, 1);

int _start(int a1, char **argv)
{
    if (a1 >= 0)
        return module_start();
    else
        return module_stop();
}

int module_start()
{
    int i;
    bool v1;
    int result;

    for (i = 0; i < 30000; ++i) {
        if (((*((vu32 *)0xB0004230)) & 8) != 0)
            break;
        DelayThread(1000);
    }
    if (i == 30000) {
        printf("AV task of DVRP is not running...\n");
        return 1;
    } else {
        DVRAV.name = "dvr_av";
        DVRAV.desc = "Digital Video Recorder AV task";
        DVRAV.type = 0x10000010;
        DVRAV.ops = &DvrFuncTbl;
        v1 = AddDrv(&DVRAV) == 0;
#if 0
        result = 2;
#else
        result = 0;
#endif
        if (!v1)
            return 1;
    }
    return result;
}

int module_stop()
{
    bool v0;
    int result;

    v0 = DelDrv("dvr_av") == 0;
    result = 1;
    if (!v0)
        return 2;
    return result;
}

int dvrav_df_init(iop_device_t *dev)
{
    int v1;
    iop_sema_t v3;

    v3.attr = 0;
    v3.initial = 1;
    v3.max = 1;
    v3.option = 0;
    v1 = CreateSema(&v3);
    if (v1 < 0)
        return -1;
    sema_id = v1;
    return 0;
}

int dvrav_df_exit(iop_device_t *dev)
{
    bool v1;
    int result;

    v1 = DeleteSema(sema_id) == 0;
    result = 0;
    if (!v1)
        return -1;
    return result;
}

int dvrav_df_ioctl(iop_file_t *f, int cmd, void *param)
{
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

int dvrav_df_devctl(
    iop_file_t *a1,
    const char *name,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int v10;
    unsigned int v11;
    unsigned int v12;

    v10 = 0;
    v11 = 0;
    WaitSema(sema_id);
    v12 = 0;
    while (DevctlCmdTbl[v12].cmd != cmd) {
        v12 = ++v11;
        if (v11 >= 21)
            goto LABEL_5;
    }
    v10 = DevctlCmdTbl[v12].fn(a1, cmd, arg, arglen, buf, buflen);
LABEL_5:
    if (v11 == 21)
        v10 = -22;
    SignalSema(sema_id);
    return v10;
}

int dvrav_df_ioctl2(iop_file_t *f, int cmd, void *arg, unsigned int arglen, void *buf, unsigned int buflen)
{
    WaitSema(sema_id);
    SignalSema(sema_id);
    return -22;
}

int dvrav_df_null()
{
    return -48;
}

s64 dvrav_df_null_long()
{
    return -48LL;
}

int avioctl2_get_tun_offset(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3102;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_get_tun_offset -> Handshake error!\n");
        return -5;
    } else if (cmdack.ack_status_ack) {
        printf("avioctl2_get_tun_offset -> Status error!\n");
        return -68;
    } else {
        *(u16 *)buf = cmdack.output_word[0];
        retval = 0;
        *((u16 *)buf + 1) = cmdack.output_word[1];
    }
    return retval;
}

int avioctl2_tun_offset_up(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3103;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_tun_offset_up -> Handshake error!\n");
        return -5;
    } else if (cmdack.ack_status_ack) {
        printf("avioctl2_tun_offset_up -> Status error!\n");
        return -68;
    } else {
        *(u16 *)buf = cmdack.output_word[0];
        *((u16 *)buf + 1) = cmdack.output_word[1];
        *((u16 *)buf + 2) = cmdack.output_word[2];
        *((u16 *)buf + 3) = cmdack.output_word[3];
        retval = 0;
        *((u16 *)buf + 4) = cmdack.output_word[4];
    }
    return retval;
}

int avioctl2_tun_offset_down(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3104;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_tun_offset_down -> Handshake error!\n");
        return -5;
    } else if (cmdack.ack_status_ack) {
        printf("avioctl2_tun_offset_down -> Status error!\n");
        return -68;
    } else {
        *(u16 *)buf = cmdack.output_word[0];
        *((u16 *)buf + 1) = cmdack.output_word[1];
        *((u16 *)buf + 2) = cmdack.output_word[2];
        *((u16 *)buf + 3) = cmdack.output_word[3];
        retval = 0;
        *((u16 *)buf + 4) = cmdack.output_word[4];
    }
    return retval;
}

int avioctl2_tun_scan_ch(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3105;
    cmdack.input_word[0] = *(u16 *)arg;
    cmdack.input_word[1] = *((u16 *)arg + 1);
    v6 = *((u16 *)arg + 2);
    cmdack.input_word_count = 3;
    cmdack.timeout = 35000000;
    cmdack.input_word[2] = v6;
    if (DvrdrvExecCmdAckComp(&cmdack)) {
        printf("avioctl2_tun_scan_ch -> Handshake error!\n");
        return -5;
    } else if (cmdack.ack_status_ack || cmdack.comp_status) {
        printf("avioctl2_tun_scan_ch -> Status error!\n");
        return -68;
    } else {
        *(u16 *)buf = cmdack.return_result_word[0];
        *((u16 *)buf + 1) = cmdack.return_result_word[1];
        *((u16 *)buf + 2) = cmdack.return_result_word[2];
        *((u16 *)buf + 3) = cmdack.return_result_word[3];
        *((u16 *)buf + 4) = cmdack.return_result_word[4];
        retval = 0;
        *((u16 *)buf + 5) = cmdack.return_result_word[5];
    }
    return retval;
}

int avioctl2_get_bs_gain(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3106;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_get_bs_gain -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_get_bs_gain -> Status error!\n");
            return -68;
        } else {
            *(u16 *)buf = cmdack.output_word[0];
        }
    }
    return retval;
}

int avioctl2_set_preset_info(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3107;
    cmdack.input_word[0] = *(u16 *)arg;
    v6 = *((u16 *)arg + 1);
    cmdack.input_word_count = 2;
    cmdack.input_word[1] = v6;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_set_preset_info -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_set_preset_info -> Status error!\n");
            return -68;
        }
    }
    return retval;
}

int avioctl2_change_sound(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3108;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_change_sound -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_change_sound -> Status error!\n");
            return -68;
        } else {
            *(u16 *)buf = cmdack.output_word[0];
        }
    }
    return retval;
}

int avioctl2_set_d_audio_sel(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3109;
    cmdack.input_word[0] = *(u16 *)arg;
    cmdack.input_word[1] = *((u16 *)arg + 1);
    cmdack.input_word[2] = *((u16 *)arg + 2);
    v6 = *((u16 *)arg + 3);
    cmdack.input_word_count = 4;
    cmdack.input_word[3] = v6;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_set_d_audio_sel -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_set_d_audio_sel -> Status error!\n");
            return -68;
        }
    }
    return retval;
}

int avioctl2_set_d_video_sel(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x310A;
    v6 = *(u16 *)arg;
    cmdack.input_word_count = 1;
    cmdack.input_word[0] = v6;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_set_d_video_sel -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_set_d_video_sel -> Status error!\n");
            return -68;
        }
    }
    return retval;
}

int avioctl2_get_av_src(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x310B;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_get_av_src -> Handshake error!\n");
        return -5;
    } else if (cmdack.ack_status_ack) {
        printf("avioctl2_get_av_src -> Status error!\n");
        return -68;
    } else {
        *(u16 *)buf = cmdack.output_word[0];
        retval = 0;
        *((u16 *)buf + 1) = cmdack.output_word[1];
    }
    return retval;
}

int avioctl2_get_preset_info(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x310C;
    v6 = *(u16 *)arg;
    cmdack.input_word_count = 1;
    cmdack.input_word[0] = v6;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_get_preset_info -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_get_preset_info -> Status error!\n");
            return -68;
        } else {
            *(u16 *)buf = cmdack.output_word[0];
        }
    }
    return retval;
}

int avioctl2_select_position(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x310E;
    v6 = *(u16 *)arg;
    cmdack.input_word_count = 1;
    cmdack.input_word[0] = v6;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_select_position -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_select_position -> Status error!\n");
            return -68;
        }
    }
    return retval;
}

int avioctl2_position_up(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x310F;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_position_up -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_position_up -> Status error!\n");
            return -68;
        } else {
            *(u16 *)buf = cmdack.output_word[0];
        }
    }
    return retval;
}

int avioctl2_position_down(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3110;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_position_down -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_position_down -> Status error!\n");
            return -68;
        } else {
            *(u16 *)buf = cmdack.output_word[0];
        }
    }
    return retval;
}

int avioctl2_get_position(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3111;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_get_position -> Handshake error!\n");
        return -5;
    } else if (cmdack.ack_status_ack) {
        printf("avioctl2_get_position -> Status error!\n");
        return -68;
    } else {
        *(u16 *)buf = cmdack.output_word[0];
        printf("Now position = %d\n", cmdack.output_word[0]);
        return 0;
    }
}

int avioctl2_set_position_info(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3112;
    cmdack.input_word[0] = *(u16 *)arg;
    cmdack.input_word[1] = *((u16 *)arg + 1);
    cmdack.input_word[2] = *((u16 *)arg + 2);
    cmdack.input_word[3] = *((u16 *)arg + 3);
    v6 = *((u16 *)arg + 4);
    cmdack.input_word_count = 5;
    cmdack.input_word[4] = v6;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_set_position_info -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_set_position_info -> Status error!\n");
            return -68;
        }
    }
    return retval;
}

int avioctl2_get_position_info(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v7;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3113;
    v7 = *(u16 *)arg;
    cmdack.input_word_count = 1;
    cmdack.input_word[0] = v7;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_get_position_info -> Handshake error!\n");
        return -5;
    } else if (cmdack.ack_status_ack) {
        printf("avioctl2_get_position_info -> Status error!\n");
        return -68;
    } else {
        *(u16 *)buf = *(u16 *)arg;
        *((u16 *)buf + 1) = cmdack.output_word[0];
        *((u16 *)buf + 2) = cmdack.output_word[1];
        *((u16 *)buf + 3) = cmdack.output_word[2];
        retval = 0;
        *((u16 *)buf + 4) = cmdack.output_word[3];
    }
    return retval;
}

int avioctl2_tun_scan_mode(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3114;
    v6 = *(u16 *)arg;
    cmdack.input_word_count = 1;
    cmdack.input_word[0] = v6;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_tun_scan_mode -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_tun_scan_mode -> Status error!\n");
            return -68;
        }
    }
    return retval;
}

int avioctl2_f_select_position(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3115;
    v6 = *(u16 *)arg;
    cmdack.input_word_count = 1;
    cmdack.input_word[0] = v6;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_f_select_position -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_f_select_position -> Status error!\n");
            return -68;
        }
    }
    return retval;
}

int avioctl2_select_rec_src(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    u16 v6;
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3116;
    v6 = *(u16 *)arg;
    cmdack.input_word_count = 1;
    cmdack.timeout = 10000000;
    cmdack.input_word[0] = v6;
    if (DvrdrvExecCmdAckComp(&cmdack)) {
        printf("avioctl2_select_rec_src -> Handshake error!\n");
        return -5;
    } else if (cmdack.ack_status_ack || (retval = 0, cmdack.comp_status)) {
        printf("avioctl2_select_rec_src -> Status error!\n");
        return -68;
    }
    return retval;
}

int avioctl2_get_rec_src(
    iop_file_t *a1,
    int cmd,
    void *arg,
    unsigned int arglen,
    void *buf,
    unsigned int buflen)
{
    int retval;
    drvdrv_exec_cmd_ack cmdack;

    cmdack.command = 0x3117;
    cmdack.input_word_count = 0;
    if (DvrdrvExecCmdAck(&cmdack)) {
        printf("avioctl2_get_rec_src -> Handshake error!\n");
        return -5;
    } else {
        retval = 0;
        if (cmdack.ack_status_ack) {
            printf("avioctl2_get_rec_src -> Status error!\n");
            return -68;
        } else {
            *(u16 *)buf = cmdack.output_word[0];
        }
    }
    return retval;
}
