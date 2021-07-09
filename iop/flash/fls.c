
// fls_4 - detect dev9 flash device
// fls_6 - identify flash chip, open id

#include "irx_imports.h"

#define SPD_REG0004 (*((vu32 *)0xB0000004))
#define SPD_REG4800 (*((vu32 *)0xB0004800))
#define SPD_REG4804 (*((vu32 *)0xB0004804))
#define SPD_REG4808 (*((vu32 *)0xB0004808))
#define SPD_REG480C (*((vu32 *)0xB000480C))
#define SPD_REG4814 (*((vu32 *)0xB0004814))

#define SPD_BF80146E (*((vu8 *)0xBF80146E))

typedef struct flash_info_
{
    u32 id;
    u32 mbit;
    u32 byte_page;
    u32 page_block;
    u32 block_card;
} flash_info;

s32 flash_detect();
s32 fls_5();
s32 flash_identify(flash_info *a1);
s32 flash_erase(flash_info *a1, s32 a2);
s32 flash_read(flash_info *a1, s32 a2, s32 a3, void *a4);
s32 flash_write(flash_info *a1, s32 a2, s16 *a3);

iop_sys_clock_t sys_clock;


unsigned int fls_timeout(void *a1)
{
    *((u32 *)a1) = 1;
    Kprintf("alarm (100msec)\n");
    return 0;
}

s32 flash_detect()
{
    s32 result;
    s32 v1;

    if ((SPD_BF80146E & 0xF0) == 48) {
        v1 = SPD_REG0004;
        USec2SysClock(0x186A0u, &sys_clock);
        if ((v1 & 0x20) != 0) {
            printf("flash: detected. (rev3 = 0x%02x)\n", v1);
            result = 0;
        } else {
            printf("flash: not detected. (rev3 = 0x%02x)\n", v1);
            result = -1;
        }
    } else {
        printf("dev9: CXD9611 not detected.\n");
        result = -1;
    }
    return result;
}

s32 fls_5()
{
    s32 v0;
    s32 v2[2];

    SPD_REG480C = 256;
    SPD_REG4804 = 255;
    v2[0] = 0;
    SetAlarm(&sys_clock, fls_timeout, v2);
    do {
        if (v2[0]) {
            printf("ERROR(TIME OUT)\n");
            v0 = -3;
            goto LABEL_7;
        }
    } while ((SPD_REG480C & 1) == 0);
    CancelAlarm(fls_timeout, v2);
    SPD_REG4804 = 112;
    v0 = 0;
    if ((SPD_REG4814 & 1) != 0) {
        printf("STATUS ERROR(FAIL)\n");
        v0 = -6;
    }
LABEL_7:
    SPD_REG480C = 0;
    return v0;
}

s32 flash_identify(flash_info *a1)
{
    s32 v2;
    s32 v3;
    u32 *v4;

    SPD_REG4804 = 144;
    SPD_REG4808 = 0;
    SPD_REG480C = 0;
    v2 = SPD_REG4814;
    memset(a1, 0, 20);
    v3 = 0;
    v4 = 0;
    do {
        ++v3;
        if (v2 == v4[914]) {
            a1->id = v2;
            a1->mbit = v4[915];
            a1->byte_page = v4[916];
            a1->page_block = v4[917];
            a1->block_card = v4[918];
            printf("flash: ID(0x%02x) %d(Mbit) %d (byte/page) %d(page/block) %d(block/card)\n", a1->id, a1->mbit, a1->byte_page, a1->page_block, a1->block_card);
            return 0;
        }
        v4 += 5;
    } while (v3 < 5);
    return -5;
}

s32 flash_erase(flash_info *a1, s32 a2)
{
    u32 v3;
    u32 v4;
    s32 v5;
    s32 v6;
    s32 v8[2];

    SPD_REG480C = 384;
    SPD_REG4804 = 96;
    v3 = a1->id;
    v4 = a2 << 9;
    if (v3 == 118) {
        SPD_REG4808 = (u8)(v4 >> 17) | 0x100;
        v5 = (v4 >> 25) & 1;
    } else {
        if (v3 < 0x77) {
            if (v3 == 115) {
                SPD_REG4808 = (v4 >> 17) & 0x7F;
            } else if (v3 == 117) {
                SPD_REG4808 = (u8)(v4 >> 17);
            }
            goto LABEL_14;
        }
        if (v3 != 121) {
            if (v3 == 230)
                SPD_REG4808 = (v4 >> 17) & 0x3F;
            goto LABEL_14;
        }
        SPD_REG4808 = (u8)(v4 >> 17) | 0x100;
        v5 = (v4 >> 25) & 2;
    }
    SPD_REG4808 = v5;
LABEL_14:
    SPD_REG4804 = 208;
    v8[0] = 0;
    SetAlarm(&sys_clock, fls_timeout, v8);
    do {
        if (v8[0]) {
            printf("ERROR(TIME OUT)\n");
            v6 = -3;
            goto LABEL_20;
        }
    } while ((SPD_REG480C & 1) == 0);
    CancelAlarm(fls_timeout, v8);
    SPD_REG4804 = 112;
    v6 = 0;
    if ((SPD_REG4814 & 1) != 0) {
        printf("STATUS ERROR(FAIL) : %d\n", a2);
        v6 = -6;
    }
LABEL_20:
    SPD_REG480C = 0;
    return v6;
}

s32 flash_read(flash_info *a1, s32 a2, s32 a3, void *a4)
{
    s16 v5;
    u32 v7;
    s32 v8;
    u32 v9;
    u16 *v10;
    s32 v12;
    s32 i;
    u32 j;
    u32 v15;
    u32 v16;
    s32 v18;
    s32 v19;

    v5 = 256;
    v19 = 0;
    v7 = a2 << 9;
    if (a1->byte_page == 512)
        v5 = 4352;
    SPD_REG480C = v5;
    if (a1->byte_page == 16)
        SPD_REG4804 = 80;
    else
        SPD_REG4804 = 0;
    v8 = v7 & 0x1FF;
    if (a1->byte_page == 16)
        v8 = v7 & 0xF;
    v9 = a1->id;
    if (a1->id == 118) {
        SPD_REG4808 = (u8)(v7 >> 17) | 0x100;
        v12 = (v7 >> 25) & 1;
        goto LABEL_21;
    }
    if (v9 < 0x77) {
        if (v9 == 115) {
            SPD_REG4808 = (u8)(v7 >> 9) | 0x100;
            v12 = (v7 >> 17) & 0x7F;
        } else {
            if (v9 != 117) {
                goto LABEL_23;
            }
            SPD_REG4808 = (u8)(v7 >> 9) | 0x100;
            v12 = (u8)(v7 >> 17);
        }
        goto LABEL_21;
    }
    if (v9 == 121) {
        SPD_REG4808 = (u8)(v7 >> 17) | 0x100;
        v12 = (v7 >> 25) & 2;
        goto LABEL_21;
    }
    if (v9 == 230) {
        SPD_REG4808 = (u8)(v7 >> 9) | 0x100;
        v12 = (v7 >> 17) & 0x3F;
    LABEL_21:
        SPD_REG4808 = v12;
    }
LABEL_23:
    v10 = a4;
    for (i = 0; i < a3; v8 = 0) {
        v18 = 0;
        SetAlarm(&sys_clock, fls_timeout, &v18);
        do {
            if (v18) {
                printf("ERROR(TIME OUT)\n");
                v19 = -3;
                goto LABEL_35;
            }
        } while ((SPD_REG480C & 1) == 0);
        CancelAlarm(fls_timeout, &v18);
        SPD_REG480C = v5 | 0x800;
        if (v8) {
            v15 = a1->byte_page;
            v16 = v8 / 2;
            while (v16 < v15 >> 1) {
                ++v16;
                *v10 = SPD_REG4800;
                v15 = a1->byte_page;
                ++v10;
            }
        } else {
            for (j = 0; j < a1->byte_page >> 2; ++v10) {
                ++j;
                *v10 = SPD_REG4800;
            }
        }
        SPD_REG480C = v5;
        ++i;
    }
LABEL_35:
    SPD_REG480C = 0;
    return v19;
}

s32 flash_write(flash_info *a1, s32 a2, s16 *a3)
{
    u32 v3;
    u32 v4;
    s32 v5;
    u32 v6;
    u32 v7;
    s16 v8;
    s32 v9;
    s32 v11[2];

    SPD_REG480C = 384;
    v3 = a2 << 9;
    SPD_REG4804 = 128;
    v4 = a1->id;
    if (a1->id == 118) {
        SPD_REG4808 = (u8)(v3 >> 17) | 0x100;
        v5 = (v3 >> 25) & 1;
        goto LABEL_13;
    }
    if (v4 < 0x77) {
        if (v4 == 115) {
            SPD_REG4808 = (u8)(v3 >> 9) | 0x100;
            v5 = (v3 >> 17) & 0x7F;
        } else {
            if (v4 != 117)
                goto LABEL_14;
            SPD_REG4808 = (u8)(v3 >> 9) | 0x100;
            v5 = (u8)(v3 >> 17);
        }
        goto LABEL_13;
    }
    if (v4 == 121) {
        SPD_REG4808 = (u8)(v3 >> 17) | 0x100;
        v5 = (v3 >> 25) & 2;
        goto LABEL_13;
    }
    if (v4 == 230) {
        SPD_REG4808 = (u8)(v3 >> 9) | 0x100;
        v5 = (v3 >> 17) & 0x3F;
    LABEL_13:
        SPD_REG4808 = v5;
    }
LABEL_14:
    v6 = 0;
    if (a1->byte_page >> 1) {
        v7 = a1->byte_page >> 1;
        do {
            v8 = *a3++;
            ++v6;
            SPD_REG4800 = v8;
        } while (v6 < v7);
    }
    SPD_REG4804 = 16;
    v11[0] = 0;
    SetAlarm(&sys_clock, fls_timeout, v11);
    do {
        if (v11[0]) {
            printf("ERROR(TIME OUT)\n");
            v9 = -3;
            goto LABEL_23;
        }
    } while ((SPD_REG480C & 1) == 0);
    CancelAlarm(fls_timeout, v11);
    SPD_REG4804 = 112;
    v9 = 0;
    if ((SPD_REG4814 & 1) != 0) {
        printf("STATUS ERROR(FAIL)\n");
        v9 = -6;
    }
LABEL_23:
    SPD_REG480C = 0;
    return v9;
}
