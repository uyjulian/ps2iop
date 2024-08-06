



s32 start(s32 a1);
s32 module_start();
s32 module_stop();
s32 DvrdrvInit();
s32 DvrdrvResetSystem();
s32 DvrdrvSendCmdAck(s32 *itrsema, u16 command, u16 *input_word, s32 input_word_count, u16 *a5, u16 *ack_status, s32 *a7);
s32 DvrdrvSetDmaDirection(u32 a1);
s32 DvrdrvTransferDma(u8 *output_buffer, s32 a2);
void DvrPreDmaHandler(s32 bcr, s32 dir);
void DvrPostDmaHandler(s32 bcr, s32 dir);
s32 DvrdrvPrepareWaitDmaEnd(s32 *itrsema, u16 command);
s32 DvrdrvCancelWaitDmaEnd(u16 command);
s32 DvrdrvWaitDmaEnd(s32 *itrsema, u16 command);
s32 DvrdrvPrepareWaitCmdComp(s32 *itrsema, u16 command, u32 timeout);
s32 DvrdrvCancelWaitCmdComp(u16 command);
s32 DvrdrvWaitCmdComp(s32 *itrsema, u16 command, u16 *a3, u16 *comp_status, s32 *a5);
s32 DvrdrvBlockPhase();
s32 DvrdrvUnblockPhase();
s32 DvrdrvEnableIntr(u16 a1);
s32 DvrdrvDisableIntr(s16 a1);
s32 DvrdrvRegisterIntrHandler(s32 a1, s32 a2, void (*a3)(s32, s32));
s32 DvrdrvUnregisterIntrHandler(void (*a1)(s32, s32));
s32 DvrdrvEnd();
s32 DVR_INTR_HANDLER(s32 flag);
s32 INTR_DVRRDY_HANDLER(s32 a1, s32 a2);
s32 INTR_DVRRDY_TO_HANDLER(s32 *a1);
s32 INTR_CMD_ACK_HANDLER();
s32 INTR_CMD_ACK_TO_HANDLER(struct_itr_sid_tbl *a1);
s32 INTR_CMD_COMP_HANDLER();
u32 INTR_CMD_COMP_TO_HANDLER(struct_itr_sid_tbl *a1);
s32 INTR_DMAACK_HANDLER();
u32 INTR_DMAACK_TO_HANDLER(struct_itr_sid_tbl *a1);
s32 INTR_DMAEND_HANDLER();
s32 BlockAPI();
s32 UnblockAPI();
struct_itr_sid_tbl *SetItrSidTbl(s32 a1, u16 a2, s32 a3);
struct_itr_sid_tbl *GetItrSidTbl(s32 a1, u16 a2);
s32 ClearItrSidTbl(struct_itr_sid_tbl *a1);
s32 *AllocItrSema();
s32 ReleaseItrSema(s32 *itrsema);
s32 DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckComp(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDmaRecvComp(drvdrv_exec_cmd_ack *a1);
s32 DvrdrvExecCmdAckDma2Comp(drvdrv_exec_cmd_ack *a1);
void retonly();
void dev9RegisterIntrCb(s32 intr, dev9_intr_cb_t cb);
s32 dev9DmaTransfer(s32 ctrl, void *buf, s32 bcr, s32 dir);
void dev9IntrEnable(s32 mask);
void dev9IntrDisable(s32 mask);
void dev9RegisterPreDmaCb(s32 ctrl, dev9_dma_cb_t cb);
void dev9RegisterPostDmaCb(s32 ctrl, dev9_dma_cb_t cb);
s32 Kprintf(const s8 *format, ...);
s32 CpuSuspendIntr(s32 *state);
s32 CpuResumeIntr(s32 state);
s32 RegisterLibraryEntries(struct irx_export_table *exports);
s32 ReleaseLibraryEntries(struct irx_export_table *exports);
s32 printf(const s8 *format, ...);
s32 iReleaseWaitThread(s32 thread_id);
s32 GetThreadId(void);
s32 SleepThread(void);
s32 iWakeupThread(s32 thread_id);
s32 DelayThread(s32 usec);
s32 SetAlarm(iop_sys_clock_t *sys_clock, u32 (*alarm_cb)(void *), void *arg);
s32 CancelAlarm(u32 (*alarm_cb)(void *), void *arg);
void USec2SysClock(u32 usec, iop_sys_clock_t *sys_clock);
u32 GetSystemTimeLow(void);
s32 CreateSema(iop_sema_t *sema);
s32 DeleteSema(s32 sema_id);
s32 SignalSema(s32 sema_id);
s32 iSignalSema(s32 sema_id);
s32 WaitSema(s32 sema_id);


const struct irx_export_table pvrdrv_entry =
    {
        1103101952u,
        &start,
        257u,
        0u,
        {112u, 118u, 114u, 100u, 114u, 118u, 0u, 0u},
        {&retonly}};
s32 DVRDRV;
s16 word_27D4;
s32 dword_27D8;
s32 sema_id;
void (*dword_27E0)(s32, s32);
s32 dword_2860[];
s32 dword_28E0[];
struct_itr_sid_tbl itrsid_2960[];
s32 dword_2AE0[96];
s32 dword_2C60[96];
s32 dword_2DE0;
s8 byte_2DE4[];


s32 start(s32 a1)
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

    if (DvrdrvInit() == -1 || (v0 = RegisterLibraryEntries((struct irx_export_table *)&pvrdrv_entry) == 0, result = 2, !v0)) {
        result = 1;
    }
    return result;
}

s32 module_stop()
{
    bool v0;
    s32 result;

    ReleaseLibraryEntries((struct irx_export_table *)&pvrdrv_entry);
    v0 = DvrdrvEnd() == 0;
    result = 1;
    if (!v0)
        result = 2;
    return result;
}

s32 DvrdrvInit()
{
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v4;
    s32 v5;
    s32 v6;
    s32 v7;
    s32 v8;
    struct_itr_sid_tbl *v9;
    struct_itr_sid_tbl *v10;
    struct_itr_sid_tbl *v11;
    iop_sema_t v12;
    iop_sema_t v13;

    v12.attr = 0;
    v12.initial = 1;
    v12.max = 1;
    v12.option = 0;
    v0 = CreateSema(&v12);
    if (v0 < 0)
        return -1;
    dword_27D8 = v0;
    v13.attr = 0;
    v13.initial = 1;
    v13.max = 1;
    v13.option = 0;
    v1 = CreateSema(&v13);
    v2 = 0;
    if (v1 < 0)
        return -1;
    sema_id = v1;
    v13.attr = 0;
    v13.initial = 0;
    v13.max = 1;
    v13.option = 0;
    do {
        v4 = CreateSema(&v13);
        v5 = 8 * v2++;
        *(u32 *)(v5 + 11744) = v4;
        *(u8 *)(v5 + 11748) = 0;
    } while (v2 < 32);
    v6 = 0;
    v7 = 0;
    do {
        ++v6;
        *(u32 *)(v7 + 10208) = 0;
        *(u32 *)(v7 + 10336) = 0;
        v7 = 4 * v6;
    } while (v6 < 32);
    v8 = 0;
    v9 = (struct_itr_sid_tbl *)dword_2C60;
    v10 = (struct_itr_sid_tbl *)dword_2AE0;
    v11 = (struct_itr_sid_tbl *)itrsid_2960;
    do {
        ClearItrSidTbl(v11);
        ClearItrSidTbl(v10);
        ClearItrSidTbl(v9++);
        ++v10;
        ++v8;
        ++v11;
    } while (v8 < 32);
    dev9RegisterIntrCb(9, DVR_INTR_HANDLER);
    DvrdrvRegisterIntrHandler(1, &DVRDRV, INTR_DVRRDY_HANDLER);
    DvrdrvRegisterIntrHandler(2, &DVRDRV, INTR_CMD_ACK_HANDLER);
    DvrdrvRegisterIntrHandler(4, &DVRDRV, INTR_CMD_COMP_HANDLER);
    DvrdrvRegisterIntrHandler(8, &DVRDRV, INTR_DMAACK_HANDLER);
    DvrdrvRegisterIntrHandler(16, &DVRDRV, INTR_DMAEND_HANDLER);
    DvrdrvEnableIntr(31);
    dev9RegisterPreDmaCb(2, DvrPreDmaHandler);
    dev9RegisterPostDmaCb(2, DvrPostDmaHandler);
    return 0;
}

s32 DvrdrvResetSystem()
{
    s32 v0;
    bool v1;
    s32 v2;
    iop_sys_clock_t v4;

    BlockAPI();
    (*((vu32 *)0xB0004008)) &= 0xFEu;
    DelayThread(100000);
    (*((vu32 *)0xB0004008)) |= 1u;
    DVRDRV = GetThreadId();
    USec2SysClock(0x1C9C380u, &v4);
    SetAlarm(&v4, (u32(*)(void *))INTR_DVRRDY_TO_HANDLER, &DVRDRV);
    v0 = SleepThread();
    CancelAlarm((u32(*)(void *))INTR_DVRRDY_TO_HANDLER, &DVRDRV);
    v1 = v0 != 0;
    v2 = -2;
    if (!v1) {
        v2 = -1;
        if ((word_27D4 & 1) != 0)
            v2 = 0;
        word_27D4 = 0;
    }
    DvrdrvDisableIntr(1);
    UnblockAPI();
    return v2;
}

s32 DvrdrvSendCmdAck(s32 *itrsema, u16 command, u16 *input_word, s32 input_word_count, u16 *a5, u16 *ack_status, s32 *a7)
{
    s32 v11;
    s32 v12;
    struct_itr_sid_tbl *v14;
    s32 v15;
    u16 *v16;
    s16 v17;
    s32 v18;
    u32 (*v19)(void *);
    s32 v20;
    s32 v21;
    u32 (*v22)(void *);
    s16 v23;
    u32 v24;
    s32 v25;
    s32 i;
    iop_sys_clock_t v28;

    v11 = -1;
    v12 = 0;
    do {
        if (((*((vu32 *)0xB0004230)) & 2) != 0)
            break;
        DelayThread(1000);
        ++v12;
    } while (v12 < 100);
    if (v12 == 100) {
        printf("DvrdrvSendCmdAck -> Command is running... (Time out)\n");
        return -2;
    }
    BlockAPI();
    v14 = SetItrSidTbl(0, command, *itrsema);
    if (!v14) {
        v11 = -1;
        printf("DvrdrvSendCmdAck() -> SetItrSidTbl Error\n");
        goto LABEL_44;
    }
    (*((vu32 *)0xB0004218)) |= 0x80u;
    while (((*((vu32 *)0xB0004218)) & 0x80) != 0)
        ;
    v15 = 0;
    if (input_word_count > 0) {
        v16 = input_word;
        do {
            v17 = *v16++;
            ++v15;
            (*((vu32 *)0xB0004214)) = v17;
        } while (v15 < input_word_count);
    }
    USec2SysClock(0x1C9C380u, &v28);
    v18 = (u16)(command & 0xF00) >> 8;
    if (v18 == 1) {
        v19 = (u32(*)(void *))INTR_CMD_ACK_TO_HANDLER;
    LABEL_18:
        SetAlarm(&v28, v19, v14);
        goto LABEL_19;
    }
    if (v18 && (u16)(command & 0xF00) >> 8 < 4u) {
        v19 = (u32(*)(void *))INTR_DMAACK_TO_HANDLER;
        goto LABEL_18;
    }
LABEL_19:
    v20 = *itrsema;
    (*((vu32 *)0xB0004210)) = command;
    WaitSema(v20);
    v21 = (u16)(command & 0xF00) >> 8;
    if (v21 == 1) {
        v22 = (u32(*)(void *))INTR_CMD_ACK_TO_HANDLER;
    } else {
        if (!v21 || (u16)(command & 0xF00) >> 8 >= 4u) {
            printf("DvrdrvSendCmdAck() -> Error!\n");
            goto LABEL_26;
        }
        v22 = (u32(*)(void *))INTR_DMAACK_TO_HANDLER;
    }
    CancelAlarm(v22, v14);
LABEL_26:
    if (!v14->byteA || v14->word8) {
        v23 = v14->word8;
        v24 = command & 0xF00;
        if ((v23 & 0x8000) == 0) {
            if (v24 >> 8 == 1) {
                v11 = 0;
                if ((v23 & 2) == 0) {
                    v11 = -1;
                    printf("DvrdrvSendCmdAck -> Interrupt Flag Error!,%04X\n", (u16)v14->word8);
                    goto LABEL_44;
                }
            } else if (v24 >> 8) {
                if (v24 >> 8 < 4) {
                    v11 = 0;
                    if ((v14->word8 & 8) == 0) {
                        v11 = -1;
                        goto LABEL_44;
                    }
                }
            }
            v25 = 64;
            if (((*((vu32 *)0xB0004228)) & 1) == 0)
                v25 = (u8)((*((vu32 *)0xB0004228)) & 0xFC) >> 2;
            *a7 = v25;
            for (i = 0; i < *a7; ++ack_status) {
                ++i;
                *ack_status = (*((vu32 *)0xB0004224));
            }
            *a5 = (*((vu32 *)0xB0004220));
            goto LABEL_44;
        }
        v11 = -3;
    } else {
        v11 = -2;
        printf("DvrdrvSendCmdAck() -> TO!\n");
    }
LABEL_44:
    ClearItrSidTbl(v14);
    UnblockAPI();
    return v11;
}

s32 DvrdrvSetDmaDirection(u32 a1)
{
    if (a1 < 2 && ((*((vu32 *)0xB0004100)) & 2) != 0) {
        while (((*((vu32 *)0xB0004100)) & 2) != 0)
            ;
    }
    if (((*((vu32 *)0xB0004004)) & 7) == a1)
        return 0;
    (*((vu32 *)0xB0004004)) = a1 | (*((vu32 *)0xB0004004)) & 0xF8;
    (*((vu32 *)0xB0004100)) |= 1u;
    while (((*((vu32 *)0xB0004100)) & 1) != 0)
        ;
    return 0;
}

s32 DvrdrvTransferDma(u8 *output_buffer, s32 a2)
{
    s32 v4;
    s32 result;
    s32 v6;
    s32 v7;
    u32 v8;
    u16 *v9;
    s16 v10;

    v4 = 0;
    if (((u8)output_buffer & 3) != 0)
        return -1;
    BlockAPI();
    v6 = a2 / 128;
    v7 = a2 % 128;
    (*((vu32 *)0xB0004108)) = a2 / 128;
    (*((vu32 *)0xB000410C)) = 32;
    v8 = (u32)&output_buffer[128 * (u16)(a2 / 128)];
    switch ((*((vu32 *)0xB0004004)) & 7) {
        case 0:
        case 2:
        case 7:
            v4 = 0;
            goto LABEL_7;
        case 1:
        case 3:
            v4 = 1;
            goto LABEL_7;
        case 4:
        case 5:
        case 6:
            UnblockAPI();
            return -1;
        default:
        LABEL_7:
            dev9DmaTransfer(2, output_buffer, (v6 << 16) | 0x20, v4);
            if (v7 > 0) {
                v9 = (u16 *)(u16)v8;
                do {
                    v7 -= 4;
                    (*((vu32 *)0xB0004120)) = *v9;
                    v10 = *(u16 *)HIWORD(v8);
                    v8 += 4;
                    (*((vu32 *)0xB0004122)) = v10;
                    v9 = (u16 *)(u16)v8;
                } while (v7 > 0);
            }
            UnblockAPI();
            result = 0;
            break;
    }
    return result;
}

void DvrPreDmaHandler(s32 bcr, s32 dir)
{
    (*((vu32 *)0xB0004100)) |= 2u;
}

void DvrPostDmaHandler(s32 bcr, s32 dir)
{
    while (((*((vu32 *)0xB0004100)) & 2) != 0)
        ;
}

s32 DvrdrvPrepareWaitDmaEnd(s32 *itrsema, u16 command)
{
    s32 v4;

    BlockAPI();
    if (itrsema) {
        v4 = 0;
        SetItrSidTbl(1, command, *itrsema);
    } else {
        v4 = -1;
        printf("DvrdrvPrepareWaitDmaEnd : itrsema==NULL\n");
    }
    UnblockAPI();
    return v4;
}

s32 DvrdrvCancelWaitDmaEnd(u16 command)
{
    struct_itr_sid_tbl *v2;
    s32 v3;

    BlockAPI();
    v2 = GetItrSidTbl(1, command);
    if (v2) {
        ClearItrSidTbl(v2);
        v3 = 0;
    } else {
        v3 = -1;
        printf("DvrdrvCancelWaitDmaEnd -> Cannot found Sid!!\n");
    }
    UnblockAPI();
    return v3;
}

s32 DvrdrvWaitDmaEnd(s32 *itrsema, u16 command)
{
    struct_itr_sid_tbl *v3;
    s16 v4;
    s32 v5;
    s32 v6;
    s32 v7;
    s8 *v8;
    s8 v10;

    WaitSema(*itrsema);
    v3 = GetItrSidTbl(1, command);
    v4 = v3->word8;
    v5 = -3;
    if ((v4 & 0x8000) == 0) {
        if ((v4 & 0x10) != 0) {
            v5 = 0;
            if (((*((vu32 *)0xB0004228)) & 1) != 0)
                v6 = 64;
            else
                v6 = (u8)((*((vu32 *)0xB0004228)) & 0xFC) >> 2;
            v7 = 0;
            if ((u16)v6) {
                v8 = &v10;
                do {
                    ++v7;
                    *(u16 *)v8 = (*((vu32 *)0xB0004224));
                    v8 += 2;
                } while (v7 < (u16)v6);
            }
        } else {
            v5 = -1;
            printf("DvrdrvWaitDmaEnd -> Interrupt Flag Error!,%04X\n", (u16)v3->word8);
        }
    }
    ClearItrSidTbl(v3);
    return v5;
}

s32 DvrdrvPrepareWaitCmdComp(s32 *itrsema, u16 command, u32 timeout)
{
    s32 v6;
    s32 v7;
    struct_itr_sid_tbl *v8;
    iop_sys_clock_t v10;

    BlockAPI();
    if (itrsema) {
        v7 = *itrsema;
        v6 = 0;
        v8 = SetItrSidTbl(2, command, v7);
        USec2SysClock(timeout, &v10);
        SetAlarm(&v10, (u32(*)(void *))INTR_CMD_COMP_TO_HANDLER, v8);
    } else {
        v6 = -1;
        printf("DvrdrvPrepareWaitCmdComp : itrsema==NULL\n");
    }
    UnblockAPI();
    return v6;
}

s32 DvrdrvCancelWaitCmdComp(u16 command)
{
    struct_itr_sid_tbl *v2;
    struct_itr_sid_tbl *v3;
    s32 v4;

    BlockAPI();
    v2 = GetItrSidTbl(2, command);
    v3 = v2;
    if (v2) {
        CancelAlarm((u32(*)(void *))INTR_CMD_COMP_TO_HANDLER, v2);
        ClearItrSidTbl(v3);
        v4 = 0;
    } else {
        v4 = -1;
        printf("DvrdrvCancelWaitCmdComp -> Cannot found Sid!!\n");
    }
    UnblockAPI();
    return v4;
}

s32 DvrdrvWaitCmdComp(s32 *itrsema, u16 command, u16 *a3, u16 *comp_status, s32 *a5)
{
    struct_itr_sid_tbl *v8;
    s32 v9;
    s16 v10;
    s32 v11;
    s32 v12;
    u16 *v13;

    WaitSema(*itrsema);
    v8 = GetItrSidTbl(2, command);
    CancelAlarm((u32(*)(void *))INTR_CMD_COMP_TO_HANDLER, v8);
    v9 = -2;
    if (!v8->byteA) {
        v10 = v8->word8;
        v9 = -3;
        if ((v10 & 0x8000) == 0) {
            if ((v10 & 4) != 0) {
                v9 = 0;
                if (((*((vu32 *)0xB0004228)) & 1) != 0)
                    v11 = 64;
                else
                    v11 = (u8)((*((vu32 *)0xB0004228)) & 0xFC) >> 2;
                *a5 = v11;
                v12 = 0;
                if (*a5 > 0) {
                    v13 = comp_status;
                    do {
                        ++v12;
                        *v13++ = (*((vu32 *)0xB0004224));
                    } while (v12 < *a5);
                }
                *a3 = (*((vu32 *)0xB0004220));
            } else {
                v9 = -1;
                printf("DvrdrvWaitCmdComp -> Interrupt Flag Error!,%04X\n", (u16)v8->word8);
            }
        }
    }
    ClearItrSidTbl(v8);
    return v9;
}

s32 DvrdrvBlockPhase()
{
    return WaitSema(sema_id);
}

s32 DvrdrvUnblockPhase()
{
    return SignalSema(sema_id);
}

s32 DvrdrvEnableIntr(u16 a1)
{
    s32 state;

    CpuSuspendIntr(&state);
    (*((vu32 *)0xB0004208)) |= a1;
    dev9IntrEnable(512);
    CpuResumeIntr(state);
    return 0;
}

s32 DvrdrvDisableIntr(s16 a1)
{
    s32 state;

    CpuSuspendIntr(&state);
    (*((vu32 *)0xB0004208)) &= ~a1;
    (*((vu32 *)0xB0004204)) = a1;
    if (!(*((vu32 *)0xB0004208)))
        dev9IntrDisable(512);
    CpuResumeIntr(state);
    return 0;
}

s32 DvrdrvRegisterIntrHandler(s32 a1, s32 a2, void (*a3)(s32, s32))
{
    s32 v6;
    void (**v7)(s32, s32);

    BlockAPI();
    v6 = 0;
    v7 = &dword_27E0;
    do {
        if (!*v7) {
            *v7 = a3;
            dword_2860[v6] = a1;
            dword_28E0[v6] = a2;
            UnblockAPI();
            return 0;
        }
        ++v6;
        ++v7;
    } while (v6 < 32);
    UnblockAPI();
    return -1;
}

s32 DvrdrvUnregisterIntrHandler(void (*a1)(s32, s32))
{
    s32 v2;
    void (**v3)(s32, s32);

    BlockAPI();
    v2 = 0;
    v3 = &dword_27E0;
    do {
        if (*v3 == a1) {
            *v3 = 0;
            dword_2860[v2] = 0;
            UnblockAPI();
            return 0;
        }
        ++v2;
        ++v3;
    } while (v2 < 32);
    UnblockAPI();
    return -1;
}

s32 DvrdrvEnd()
{
    s32 result;
    s32 v1;
    s32 v2;

    result = -1;
    if (dword_27D8 < 0)
        return result;
    result = -1;
    if (sema_id < 0)
        return result;
    DvrdrvDisableIntr(32799);
    v1 = 0;
    DvrdrvUnregisterIntrHandler((void (*)(s32, s32))INTR_DVRRDY_HANDLER);
    DvrdrvUnregisterIntrHandler((void (*)(s32, s32))INTR_CMD_ACK_HANDLER);
    DvrdrvUnregisterIntrHandler((void (*)(s32, s32))INTR_CMD_COMP_HANDLER);
    DvrdrvUnregisterIntrHandler((void (*)(s32, s32))INTR_DMAACK_HANDLER);
    DvrdrvUnregisterIntrHandler((void (*)(s32, s32))INTR_DMAEND_HANDLER);
    DeleteSema(dword_27D8);
    DeleteSema(sema_id);
    dword_27D8 = -1;
    sema_id = -1;
    v2 = 0;
    do {
        ++v1;
        DeleteSema(*(u32 *)(v2 + 0x2DE0));
        v2 = 8 * v1;
    } while (v1 < 32);
    return 0;
}

s32 DVR_INTR_HANDLER(s32 flag)
{
    s16 v1;
    s32 v2;
    s32 *v3;
    s32 v4;
    void (*v5)(s32, s32);

    v1 = 0;
    v2 = 0;
    v3 = dword_2860;
    v4 = (*((vu32 *)0xB0004200));
    do {
        if ((*v3 & v4) != 0) {
            v5 = *(&dword_27E0 + v2);
            if (v5) {
                v5(v4, dword_28E0[v2]);
                v1 |= *(u16 *)v3;
            }
        }
        ++v2;
        ++v3;
    } while (v2 < 32);
    (*((vu32 *)0xB0004204)) = v1;
    return 1;
}

s32 INTR_DVRRDY_HANDLER(s32 a1, s32 a2)
{
    s32 v2;
    bool v3;

    v2 = *(u32 *)a2;
    v3 = *(s32 *)a2 < 0;
    *(u16 *)(a2 + 4) |= 1u;
    if (!v3)
        iWakeupThread(v2);
    return 0;
}

s32 INTR_DVRRDY_TO_HANDLER(s32 *a1)
{
    s32 v1;

    v1 = *a1;
    if (v1 >= 0)
        iReleaseWaitThread(v1);
    return 0;
}

s32 INTR_CMD_ACK_HANDLER()
{
    struct_itr_sid_tbl *v0;
    s32 v1;
    s32 v2;
    s8 *v3;
    s32 v5;
    s8 v6;

    v0 = GetItrSidTbl(0, (*((vu32 *)0xB0004220)));
    if (v0) {
        v5 = v0->dword4;
        v0->word8 |= 2u;
        if (v5 >= 0) {
            iSignalSema(v5);
            return 0;
        }
        Kprintf("Illegal Sema ID : %d\n", v5);
        return 0;
    }
    Kprintf("ACK:GetItrSidTbl(%04Xh) error\n", (*((vu32 *)0xB0004220)));
    Kprintf("Clear \"Reply FIFO\"\n");
    v1 = 64;
    if (((*((vu32 *)0xB0004228)) & 1) == 0)
        v1 = (u8)((*((vu32 *)0xB0004228)) & 0xFC) >> 2;
    v2 = 0;
    if (!v1)
        return 0;
    v3 = &v6;
    do {
        ++v2;
        *(u16 *)v3 = (*((vu32 *)0xB0004224));
        v3 += 2;
    } while (v2 < v1);
    return 0;
}

s32 INTR_CMD_ACK_TO_HANDLER(struct_itr_sid_tbl *a1)
{
    u32 v1;
    s32 v3;

    v1 = GetSystemTimeLow();
    Kprintf("CMDACK_TO:[%u]\n", v1);
    v3 = a1->dword4;
    a1->byteA = 1;
    iSignalSema(v3);
    return 0;
}

s32 INTR_CMD_COMP_HANDLER()
{
    struct_itr_sid_tbl *v0;
    s32 v1;
    s32 v2;
    s8 *v3;
    s32 v5;
    s8 v6;

    v0 = GetItrSidTbl(2, (*((vu32 *)0xB0004220)));
    if (v0) {
        v5 = v0->dword4;
        v0->word8 |= 4u;
        if (v5 >= 0) {
            iSignalSema(v5);
            return 0;
        }
        Kprintf("Illegal thread ID : %d\n", v5);
        return 0;
    }
    Kprintf("COMP:GetItrSidTbl(%04Xh) error\n", (*((vu32 *)0xB0004220)));
    Kprintf("Clear \"Reply FIFO\"\n");
    v1 = 64;
    if (((*((vu32 *)0xB0004228)) & 1) == 0)
        v1 = (u8)((*((vu32 *)0xB0004228)) & 0xFC) >> 2;
    v2 = 0;
    if (!v1)
        return 0;
    v3 = &v6;
    do {
        ++v2;
        *(u16 *)v3 = (*((vu32 *)0xB0004224));
        v3 += 2;
    } while (v2 < v1);
    return 0;
}

u32 INTR_CMD_COMP_TO_HANDLER(struct_itr_sid_tbl *a1)
{
    u32 v1;
    s32 v3;

    v1 = GetSystemTimeLow();
    Kprintf("COMP TO:[%u]\n", v1);
    v3 = a1->dword4;
    a1->byteA = 1;
    iSignalSema(v3);
    return 0;
}

s32 INTR_DMAACK_HANDLER()
{
    struct_itr_sid_tbl *v0;
    s32 v1;

    v0 = GetItrSidTbl(0, (*((vu32 *)0xB0004220)));
    if (v0) {
        v1 = v0->dword4;
        v0->word8 |= 8u;
        if (v1 >= 0) {
            iSignalSema(v1);
            return 0;
        }
        Kprintf("Illegal thread ID : %d\n", v1);
    } else {
        Kprintf("GetItrSidTbl(%04Xh) error\n", (*((vu32 *)0xB0004220)));
    }
    return 0;
}

u32 INTR_DMAACK_TO_HANDLER(struct_itr_sid_tbl *a1)
{
    u32 v1;

    v1 = GetSystemTimeLow();
    Kprintf("DMAACK_TO:[%u]\n", v1);
    GetItrSidTbl(0, a1->word0)->byteA = 1;
    iSignalSema(*(u32 *)&a1->word0);
    return 0;
}

s32 INTR_DMAEND_HANDLER()
{
    struct_itr_sid_tbl *v0;
    s32 v1;

    v0 = GetItrSidTbl(1, (*((vu32 *)0xB0004220)));
    if (v0) {
        v1 = v0->dword4;
        v0->word8 |= 0x10u;
        if (v1 >= 0) {
            iSignalSema(v1);
            return 0;
        }
        Kprintf("Illegal thread ID : %d\n", v1);
    } else {
        Kprintf("GetItrSidTbl(%04Xh) error\n", (*((vu32 *)0xB0004220)));
    }
    return 0;
}

s32 BlockAPI()
{
    WaitSema(dword_27D8);
    return 0;
}

s32 UnblockAPI()
{
    SignalSema(dword_27D8);
    return 0;
}

struct_itr_sid_tbl *SetItrSidTbl(s32 a1, u16 a2, s32 a3)
{
    s32 v6;
    s32 v7;
    s32 state;

    CpuSuspendIntr(&state);
    v6 = 0;
    v7 = 0x180 * a1;
    while (*(u32 *)(v7 + 0x2964) != -1) {
        if (*(u16 *)(v7 + 0x2960) != a2) {
            ++v6;
            v7 += 12;
            if (v6 < 32)
                continue;
        }
        goto LABEL_5;
    }
    *(u16 *)(v7 + 0x2960) = a2;
    *(u32 *)(v7 + 0x2964) = a3;
    *(u8 *)(v7 + 0x296A) = 0;
LABEL_5:
    CpuResumeIntr(state);
    if (v6 != 32)
        return &itrsid_2960[32 * a1 + v6];
    Kprintf("SetItrSidTbl : Error!\n");
    return 0;
}

struct_itr_sid_tbl *GetItrSidTbl(s32 a1, u16 a2)
{
    s32 v4;
    s32 v5;
    s32 v6;
    s32 state;

    CpuSuspendIntr(&state);
    v4 = 0;
    v5 = 32 * a1;
    v6 = v5 * 12;
    do {
        if (*(u16 *)(v6 + 0x2960) == a2)
            break;
        ++v4;
        v6 += 12;
    } while (v4 < 32);
    CpuResumeIntr(state);
    if (v4 != 32)
        return &itrsid_2960[v4 + v5];
    Kprintf("GetItrSidTbl : Error!\n");
    return 0;
}

s32 ClearItrSidTbl(struct_itr_sid_tbl *a1)
{
    s32 v2;
    s32 state;

    CpuSuspendIntr(&state);
    a1->byteA = 0;
    v2 = state;
    a1->word0 = 0;
    a1->dword4 = -1;
    a1->word8 = 0;
    return CpuResumeIntr(v2);
}

s32 *AllocItrSema()
{
    s32 *v0;
    s32 v1;
    s8 *v2;
    s32 *v3;
    s32 *result;
    s32 state;

    v0 = 0;
    CpuSuspendIntr(&state);
    v1 = 0;
    v2 = byte_2DE4;
    v3 = &dword_2DE0;
    while (1) {
        ++v1;
        if (!*v2)
            break;
        v2 += 8;
        v3 += 2;
        if (v1 >= 32)
            goto LABEL_5;
    }
    v0 = v3;
    *v2 = 1;
LABEL_5:
    CpuResumeIntr(state);
    result = v0;
    if (v0)
        return result;
    printf("AllocItrSema : empty\n");
    return 0;
}

s32 ReleaseItrSema(s32 *itrsema)
{
    s32 v2;
    s32 *v3;
    s32 result;
    s32 state;

    CpuSuspendIntr(&state);
    v2 = 0;
    v3 = &dword_2DE0;
    while (v3 != itrsema) {
        ++v2;
        v3 += 2;
        if (v2 >= 32)
            goto LABEL_4;
    }
    byte_2DE4[8 * v2] = 0;
LABEL_4:
    CpuResumeIntr(state);
    result = 0;
    if (v2 != 32)
        return result;
    printf("ReleaseItrSema : full\n");
    return -1;
}

s32 DvrdrvExecCmdAck(drvdrv_exec_cmd_ack *a1)
{
    s32 *v2;
    u16 v3;
    s32 v4;
    s32 result;

    v2 = AllocItrSema();
    if (v2) {
        DvrdrvBlockPhase();
        v3 = a1->command;
        a1->phase = 1;
        v4 = DvrdrvSendCmdAck(v2, v3, a1->input_word, a1->input_word_count, &a1->field_88, &a1->ack_status, &a1->field_10C);
        DvrdrvUnblockPhase();
        ReleaseItrSema(v2);
        result = v4;
    } else {
        printf("DvrdrvExecCmdAck : Cannot alloc sema\n");
        result = -1;
    }
    return result;
}

s32 DvrdrvExecCmdAckComp(drvdrv_exec_cmd_ack *a1)
{
    s32 *v2;
    s32 *v3;
    s32 result;
    u16 v5;
    s32 v6;
    u16 v7;

    v2 = AllocItrSema();
    v3 = v2;
    if (v2) {
        DvrdrvPrepareWaitCmdComp(v2, a1->command, a1->timeout);
        DvrdrvBlockPhase();
        v5 = a1->command;
        a1->phase = 1;
        v6 = DvrdrvSendCmdAck(v3, v5, a1->input_word, a1->input_word_count, &a1->field_88, &a1->ack_status, &a1->field_10C);
        if (v6) {
            DvrdrvCancelWaitCmdComp(a1->command);
            DvrdrvUnblockPhase();
        } else {
            DvrdrvUnblockPhase();
            v7 = a1->command;
            a1->phase = 4;
            v6 = DvrdrvWaitCmdComp(v3, v7, &a1->field_110, &a1->comp_status, &a1->field_194);
        }
        ReleaseItrSema(v3);
        result = v6;
    } else {
        printf("DvrdrvExecCmdAck : Cannot alloc sema\n");
        result = -1;
    }
    return result;
}

s32 DvrdrvExecCmdAckDmaSendComp(drvdrv_exec_cmd_ack *a1)
{
    s32 *v2;
    s32 *v3;
    s32 v5;
    s32 v6;
    u16 v7;
    s32 v8;
    s16 v9;
    s32 *v10;
    u16 v11;
    u16 v12;
    s16 v13[65];
    s32 v14;
    s8 v15[2];
    s16 v16[65];
    s8 v17[148];
    s32 v18;

    v2 = AllocItrSema();
    v3 = v2;
    if (!v2) {
        printf("DvrdrvExecCmdAck : Cannot alloc sema\n");
        return -1;
    }
    DvrdrvPrepareWaitCmdComp(v2, a1->command, a1->timeout);
    a1->phase = 1;
    DvrdrvBlockPhase();
    v5 = DvrdrvSendCmdAck(
        v3,
        a1->command,
        a1->input_word,
        a1->input_word_count,
        &a1->field_88,
        &a1->ack_status,
        &a1->field_10C);
    v6 = v5;
    if (v5) {
        printf("Phase1 error -> %d\n", v5);
        v7 = a1->command;
    } else {
        DvrdrvUnblockPhase();
        a1->phase = 2;
        DvrdrvBlockPhase();
        DvrdrvSetDmaDirection(1u);
        v8 = a1->input_buffer_length;
        if ((v8 & 0x7F) != 0)
            v18 = (v8 / 128 + 1) << 7;
        else
            v18 = a1->input_buffer_length;
        v9 = a1->command;
        v14 = 2;
        v12 = v9 & 0xF0FF | 0x200;
        v13[0] = HIWORD(v18);
        v13[1] = v18;
        v10 = AllocItrSema();
        DvrdrvPrepareWaitDmaEnd(v10, v12);
        v6 = DvrdrvSendCmdAck(v3, v12, v13, 2, v15, v16, (s32 *)v17);
        if (v6) {
            v7 = a1->command;
        } else {
            v6 = -1;
            if (!v16[0]) {
                if (v18 <= 0) {
                    DvrdrvCancelWaitDmaEnd(v12);
                } else {
                    DvrdrvTransferDma((s8 *)a1->input_buffer, v18);
                    DvrdrvWaitDmaEnd(v10, v12);
                }
                ReleaseItrSema(v10);
                DvrdrvUnblockPhase();
                v11 = a1->command;
                a1->phase = 4;
                v6 = DvrdrvWaitCmdComp(v3, v11, &a1->field_110, &a1->comp_status, &a1->field_194);
                goto LABEL_17;
            }
            v7 = a1->command;
        }
    }
    DvrdrvCancelWaitCmdComp(v7);
    DvrdrvUnblockPhase();
LABEL_17:
    ReleaseItrSema(v3);
    return v6;
}

s32 DvrdrvExecCmdAckDmaRecvComp(drvdrv_exec_cmd_ack *a1)
{
    s32 *v2;
    s32 *v3;
    s32 v5;
    u16 v6;
    s16 v7;
    s32 *v8;
    s32 v9;
    u16 v10;
    u16 v11;
    s8 v12[130];
    s32 v13;
    s8 v14[2];
    s16 v15[65];
    s8 v16[164];

    v2 = AllocItrSema();
    v3 = v2;
    if (!v2) {
        printf("DvrdrvExecCmdAck : Cannot alloc sema\n");
        return -1;
    }
    DvrdrvPrepareWaitCmdComp(v2, a1->command, a1->timeout);
    a1->phase = 1;
    DvrdrvBlockPhase();
    v5 = DvrdrvSendCmdAck(
        v3,
        a1->command,
        a1->input_word,
        a1->input_word_count,
        &a1->field_88,
        &a1->ack_status,
        &a1->field_10C);
    if (v5) {
        v6 = a1->command;
    } else {
        DvrdrvUnblockPhase();
        a1->phase = 3;
        DvrdrvBlockPhase();
        DvrdrvSetDmaDirection(0);
        v7 = a1->command;
        v13 = 0;
        v11 = v7 & 0xF0FF | 0x300;
        v8 = AllocItrSema();
        DvrdrvPrepareWaitDmaEnd(v8, v11);
        v5 = DvrdrvSendCmdAck(v3, v11, (s16 *)v12, 0, v14, v15, (s32 *)v16);
        if (v5) {
            v6 = a1->command;
        } else {
            v5 = -1;
            if (!v15[0]) {
                v9 = ((u16)v15[1] << 16) + (u16)v15[2];
                a1->field_1A8 = v9;
                if (v9 <= 0) {
                    DvrdrvCancelWaitDmaEnd(v11);
                } else {
                    DvrdrvTransferDma((s8 *)a1->output_buffer, v9);
                    DvrdrvWaitDmaEnd(v8, v11);
                }
                ReleaseItrSema(v8);
                DvrdrvUnblockPhase();
                v10 = a1->command;
                a1->phase = 4;
                v5 = DvrdrvWaitCmdComp(v3, v10, &a1->field_110, &a1->comp_status, &a1->field_194);
                goto LABEL_14;
            }
            v6 = a1->command;
        }
    }
    DvrdrvCancelWaitCmdComp(v6);
    DvrdrvUnblockPhase();
LABEL_14:
    ReleaseItrSema(v3);
    return v5;
}

s32 DvrdrvExecCmdAckDma2Comp(drvdrv_exec_cmd_ack *a1)
{
    s32 *v2;
    s32 *v3;
    s32 v5;
    s32 v6;
    s16 v7;
    s32 *v8;
    u16 v9;
    s16 v10;
    s32 *v11;
    s32 v12;
    u16 v13;
    u16 v14;
    s16 v15[65];
    s32 v16;
    s8 v17[2];
    s16 v18[65];
    s8 v19[148];
    s32 v20;
    u16 v21;
    s8 v22[130];
    s32 v23;
    s8 v24[2];
    s16 v25[65];
    s8 v26[164];

    v2 = AllocItrSema();
    v3 = v2;
    if (!v2) {
        printf("DvrdrvExecCmdAck : Cannot alloc sema\n");
        return -1;
    }
    DvrdrvPrepareWaitCmdComp(v2, a1->command, a1->timeout);
    a1->phase = 1;
    DvrdrvBlockPhase();
    v5 = DvrdrvSendCmdAck(
        v3,
        a1->command,
        a1->input_word,
        a1->input_word_count,
        &a1->field_88,
        &a1->ack_status,
        &a1->field_10C);
    if (v5)
        goto LABEL_15;
    DvrdrvUnblockPhase();
    a1->phase = 2;
    DvrdrvBlockPhase();
    DvrdrvSetDmaDirection(1u);
    v6 = a1->input_buffer_length;
    v20 = (v6 & 0x7F) != 0 ? (v6 / 128 + 1) << 7 : a1->input_buffer_length;
    v7 = a1->command;
    v16 = 2;
    v14 = v7 & 0xF0FF | 0x200;
    v15[0] = HIWORD(v20);
    v15[1] = v20;
    v8 = AllocItrSema();
    DvrdrvPrepareWaitDmaEnd(v8, v14);
    v5 = DvrdrvSendCmdAck(v3, v14, v15, 2, v17, v18, (s32 *)v19);
    if (v5) {
    LABEL_15:
        v9 = a1->command;
        goto LABEL_16;
    }
    v5 = -1;
    if (!v18[0]) {
        if (v20 <= 0) {
            DvrdrvCancelWaitDmaEnd(v14);
        } else {
            DvrdrvTransferDma((s8 *)a1->input_buffer, v20);
            DvrdrvWaitDmaEnd(v8, v14);
        }
        ReleaseItrSema(v8);
        DvrdrvUnblockPhase();
        a1->phase = 3;
        DvrdrvBlockPhase();
        DvrdrvSetDmaDirection(0);
        v10 = a1->command;
        v23 = 0;
        v21 = v10 & 0xF0FF | 0x300;
        v11 = AllocItrSema();
        DvrdrvPrepareWaitDmaEnd(v11, v21);
        v5 = DvrdrvSendCmdAck(v3, v21, (s16 *)v22, v23, v24, v25, (s32 *)v26);
        if (!v5 && !v25[0]) {
            v12 = ((u16)v25[1] << 16) + (u16)v25[2];
            a1->field_1A8 = v12;
            if (v12 <= 0) {
                DvrdrvCancelWaitDmaEnd(v21);
            } else {
                DvrdrvTransferDma((s8 *)a1->output_buffer, v12);
                DvrdrvWaitDmaEnd(v11, v21);
            }
            ReleaseItrSema(v11);
            DvrdrvUnblockPhase();
            v13 = a1->command;
            a1->phase = 4;
            v5 = DvrdrvWaitCmdComp(v3, v13, &a1->field_110, &a1->comp_status, &a1->field_194);
            goto LABEL_21;
        }
        goto LABEL_15;
    }
    v9 = a1->command;
LABEL_16:
    DvrdrvCancelWaitCmdComp(v9);
    DvrdrvUnblockPhase();
LABEL_21:
    ReleaseItrSema(v3);
    return v5;
}

void retonly()
{
    ;
}

void dev9RegisterIntrCb(s32 intr, dev9_intr_cb_t cb)
{
    ;
}

s32 dev9DmaTransfer(s32 ctrl, void *buf, s32 bcr, s32 dir)
{
    s32 result;

    return result;
}

void dev9IntrEnable(s32 mask)
{
    ;
}

void dev9IntrDisable(s32 mask)
{
    ;
}

void dev9RegisterPreDmaCb(s32 ctrl, dev9_dma_cb_t cb)
{
    ;
}

void dev9RegisterPostDmaCb(s32 ctrl, dev9_dma_cb_t cb)
{
    ;
}

s32 Kprintf(const s8 *format, ...)
{
    s32 result;

    return result;
}

s32 CpuSuspendIntr(s32 *state)
{
    s32 result;

    return result;
}

s32 CpuResumeIntr(s32 state)
{
    s32 result;

    return result;
}

s32 RegisterLibraryEntries(struct irx_export_table *exports)
{
    s32 result;

    return result;
}

s32 ReleaseLibraryEntries(struct irx_export_table *exports)
{
    s32 result;

    return result;
}

s32 printf(const s8 *format, ...)
{
    s32 result;

    return result;
}

s32 iReleaseWaitThread(s32 thread_id)
{
    s32 result;

    return result;
}

s32 GetThreadId(void)
{
    s32 result;

    return result;
}

s32 SleepThread(void)
{
    s32 result;

    return result;
}

s32 iWakeupThread(s32 thread_id)
{
    s32 result;

    return result;
}

s32 DelayThread(s32 usec)
{
    s32 result;

    return result;
}

s32 SetAlarm(iop_sys_clock_t *sys_clock, u32 (*alarm_cb)(void *), void *arg)
{
    s32 result;

    return result;
}

s32 CancelAlarm(u32 (*alarm_cb)(void *), void *arg)
{
    s32 result;

    return result;
}

void USec2SysClock(u32 usec, iop_sys_clock_t *sys_clock)
{
    ;
}

u32 GetSystemTimeLow(void)
{
    u32 result;

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

s32 iSignalSema(s32 sema_id)
{
    s32 result;

    return result;
}

s32 WaitSema(s32 sema_id)
{
    s32 result;

    return result;
}
