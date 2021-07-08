/* cdvdman's file system support (CODE) */

#include "cdvdman-internal.h"



/* For "cdrom" device OPS */
int cdrom_init(iop_device_t *dev)
{
    iop_event_t evfp;
    int dummy;
    register int i;

    DPRINTF(0, "cdvdman Init\n");

    cdvdman_waf = 1;
    cdvdman_scmd_flg = 1;
    cdvdman_read2_flg = 0;
    cdvdman_strm_id = 0;
    cdvdman_cderror = 0;
    cdvdman_layer1 = 0;
    cdvdman_usetoc = 0;
    cdvdman_read_to = 0;
    cdvdman_pwr_flg = 0;
    cdvdman_curdvd = 0;
    cdvdman_dlemu = 0;
    cdvdman_decstate = 0;
    cdvdman_xorvalue = 0;
    cdvdman_decshift = 0;
    cdvdman_dldvd = 0xFF;
    cdvdman_nodecflg = 0;
    cdvdman_ee_ncmd = 0;
    cdvdman_spinctl = 0xFFFFFF;

    evfp.attr = EA_MULTI;
    evfp.bits = 0;
    evfp.option = 0;

    cdvdman_intr_ef = CreateEventFlag(&evfp);
    cdvdman_scmd_ef = CreateEventFlag(&evfp);
    cdvdman_ncmd_ef = CreateEventFlag(&evfp);
    cdvdman_srch_ef = CreateEventFlag(&evfp);
    cdvdman_read_ef = CreateEventFlag(&evfp);

    ClearEventFlag(cdvdman_intr_ef, 0xFFFFFFFB);
    ClearEventFlag(cdvdman_intr_ef, 0xFFFFFFEF);

    SetEventFlag(cdvdman_intr_ef, 0x29);
    SetEventFlag(cdvdman_ncmd_ef, 0x1);
    SetEventFlag(cdvdman_scmd_ef, 0x1);
    SetEventFlag(cdvdman_srch_ef, 0x1);
    SetEventFlag(cdvdman_read_ef, 0x1);

    cdvdman_spinnom = 0xFFFFFFFF;
    cdvdman_trycnt = 0xFFFFFFFF;

    sceCdSC(0xFFFFFFF3, &dummy);

    for (i = 0xF; i >= 0; i--)
        cdvdman_handles[i].fd_flags = 0;

    return 0;
}

/* For "cdrom" device OPS */
int cdrom_deinit(iop_device_t *)
{
    register int i;

    for (i = 0xF; i >= 0; i--)
        cdvdman_handles[i].fd_flags = 0;

    DeleteEventFlag(cdvdman_read_ef);
    DeleteEventFlag(cdvdman_intr_ef);
    DeleteEventFlag(cdvdman_ncmd_ef);
    DeleteEventFlag(cdvdman_scmd_ef);
    DeleteEventFlag(cdvdman_srch_ef);

    return 0;
}

/* internal routine */
int cdvdman_devready()
{
    register int i;

    if (CDVDreg_STATUS & 1)
        return -5;

    for (i = 0;; i++) {
        if (((CDVDreg_READY & 0xC0) == 0x40) && (!cdvdman_read2_flg) && (!cdvdman_ee_ncmd))
            break;
        if (i < 0x40)
            DelayThread(10000);
        else
            return -16;
    }

    return 1;
}

/* internal routine */
int cdvdman_l0check(int layer)
{
    if (!layer) {
        if (!cdvdman_dlemu) {
            if ((cdvdman_dldvd != 1) && (cdvdman_dldvd != 2))
                return 0;
        }

        return 1;
    }

    return 0;
}

/* internal routine */
void cdvdman_iormode(sceCdRMode *rmode, int fmode, int layer)
{
    register int v;

    rmode->datapattern = 0;

    // TODO: check this!
    rmode->trycount = (cdvdman_trycnt == -1) ? 0x10 : cdvdman_trycnt;

    if (!cdvdman_l0check(layer)) {
        if (cdvdman_spinnom != -1)
            rmode->spindlctrl = cdvdman_spinnom;
        else {
            switch (fmode) {
                case 0x00:
                    v = 0x00;
                    break;
                case 0x01:
                    v = 0x01;
                    break;
                case 0x02:
                    v = 0x02;
                    break;
                case 0x03:
                    v = 0x03;
                    break;
                case 0x04:
                    v = 0x04;
                    break;
                case 0x05:
                    v = 0x05;
                    break;
                case 0x06:
                case 0x07:
                case 0x08:
                case 0x09:
                case 0x0A:
                case 0x0B:
                case 0x0C:
                case 0x0D:
                case 0x0E:
                case 0x0F:
                case 0x10:
                case 0x11:
                case 0x12:
                case 0x13:
                    v = 0x01;
                    break;
                case 0x14:
                    v = 0x14;
                    break;
                default:
                    v = 0x01;
                    break;
            }

            rmode->spindlctrl = v;
        }
    } else {
        if (cdvdman_spinnom != -1) {
            if ((fmode == 0x02) || (fmode == 0x14))
                rmode->spindlctrl = cdvdman_spinnom;
            else
                rmode->spindlctrl = 0;
        } else {
            if ((fmode == 0x02) || (fmode == 0x14))
                rmode->spindlctrl = fmode;
            else
                rmode->spindlctrl = 0;
        }
    }
}

/* internal routine */
int _sceCdSearchDir(char *dirname, int layer)
{
    sceCdlFILE fileinfo;

    DPRINTF(1, "_sceCdSearchDir: dir name %s layer %d\n", dirname, layer);

    return (sceCdLayerSearchFile(&fileinfo, dirname, layer) == 0) ? -2 : cdvdman_fs_cdsec;
}

int cdrom_dopen(iop_file_t *f, const char *dirname)
{
    char name[0x80];
    u32 resultp;
    register int rc;
    register CDVDMAN_FILEDATA *fd;
    register int i;

    DPRINTF(1, "fileIO DOPEN name= %s layer %d\n", dirname, f->unit);

    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);

    i = 0;
    do {
        if (!cdvdman_handles[i].fd_flags)
            break;
    } while (++i < 0x10);

    if (i == 0x10) {
        SetEventFlag(cdvdman_read_ef, 1);
        return -24;
    }

    f->privdata = (void *)i;
    fd = &cdvdman_handles[i];

    rc = cdvdman_devready();
    if (rc < 0) {
        SetEventFlag(cdvdman_read_ef, 1);
        return rc;
    }

    strncpy(name, dirname, 0x80);

    if (!strcmp(name, ".")) {
        strcpy(name, cdvdman_rootdir);
    }

    i = strlen(name);
    if (i < 2)
        i = 0;
    else
        i -= 2;

    if (strcmp(&name[i], cdvdman_rootdir))
        strcat(name, cdvdman_rootdir);

    if (f->unit < 2) {
        fd->file_lsn = 0;
        cdvdman_srchspd = 0;
        i = _sceCdSearchDir(name, f->unit);
        if (i >= 0) {
            fd->file_lsn = i;
            fd->read_pos = 0;
            fd->filemode = 0;
            fd->fd_flags = 1;
            fd->fd_layer = f->unit;

            SetEventFlag(cdvdman_read_ef, 1);
            return 0;
        } else
            DPRINTF(0, "open fail directory %s\n", dirname);
    } else
        DPRINTF(0, "open fail name %s\n", dirname);

    SetEventFlag(cdvdman_read_ef, 1);

    return -2;
}

/* internal routine */
void cdvdman_fillstat(void *dummy, iox_stat_t *buf, sceCdlFILE *fp)
{
    register int i = 0;

    buf->attr = 0;
    buf->private_5 = 0;
    buf->private_4 = 0;
    buf->private_3 = 0;
    buf->private_2 = 0;
    buf->private_1 = 0;
    buf->private_0 = 0;
    buf->hisize = 0;

    do {
        buf->ctime[i] = buf->atime[i] = buf->mtime[i] = fp->date[i];
    } while (++i < 8);

    buf->size = fp->size;

    // TODO: check this!
#if 0
    buf->mode = ((fp->flag & 2) ? 0x1049 : 0x2000) | 0x124;
#endif
    buf->mode = 0x1049 | 0x124;
}

/* internal routine */
int cdvdman_cdfname(char *filename)
{
    register int l;

    l = strlen(filename);
    if (l >= 3) {
        if ((filename[l - 2] == ';') || (filename[l - 1] == '1'))
            return 0;
    }

    strcat(filename, ";1");
    return 1;
}

/* For "cdrom" device OPS */
int cdrom_getstat(iop_file_t *f, const char *name, iox_stat_t *buf)
{
    sceCdlFILE fileinfo;
    char filename[0x80];
    u32 resultp;
    register int rc;

    DPRINTF(1, "fileIO GETSTAT name= %s layer= %d\n", name, f->unit);

    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);
    rc = cdvdman_devready();
    if (rc < 0) {
        SetEventFlag(cdvdman_read_ef, 1);
        return rc;
    }

    strncpy(filename, name, 0x80);
    if (!strcmp(filename, ".")) {
        *(short *)&filename[0] = *(short *)cdvdman_rootdir;
        *(char *)&filename[2] = *(char *)cdvdman_rootdir;
    }

    if (!strcmp(filename, "\\")) {
        *(short *)&filename[0] = *(short *)cdvdman_rootdir;
        *(char *)&filename[2] = *(char *)cdvdman_rootdir;
    }

    if (!strlen(filename)) {
        *(short *)&filename[0] = *(short *)cdvdman_rootdir;
        *(char *)&filename[2] = *(char *)cdvdman_rootdir;
    }

    cdvdman_srchspd = 0;

    if (!sceCdLayerSearchFile(&fileinfo, filename, f->unit)) {
        rc = cdvdman_cdfname(filename);
        if (rc) {
            rc = sceCdLayerSearchFile(&fileinfo, filename, f->unit);
        }
        if (!rc) {
            DPRINTF(0, "open fail name %s\n", name);
            SetEventFlag(cdvdman_read_ef, 1);
            return -2;
        }
    }

    cdvdman_fillstat(filename, buf, &fileinfo);
    SetEventFlag(cdvdman_read_ef, 1);
    return 1;
}

/* internal routine */
int _sceCdReadDir(sceCdlFILE *fp, int dsec, int index, int layer)
{
    DPRINTF(1, "_sceCdReadDir: current= %d dsec= %d layer= %d\n", cdvdman_fs_cdsec, dsec, layer);

    if ((dsec != cdvdman_fs_cdsec) || (cdvdman_fs_layer != layer)) {
        if (cdvdman_fs_layer != layer) {
            if (CD_newmedia(layer))
                cdvdman_fs_cache = 1;
            else
                return -2;
        }

        if (!CD_cachefile(dsec, layer))
            return -2;
    }

    if (cdvdman_filetbl[index].name)
        return 0;

    DPRINTF(1, "%s: found dir_point %d\n", cdvdman_filetbl[index].name, index);

    *fp = cdvdman_filetbl[index];

    return 1;
}

/* For "cdrom" device OPS */
int cdrom_dread(iop_file_t *f, iox_dirent_t *buf)
{
    sceCdlFILE fileinfo;
    u32 resultp;
    register CDVDMAN_FILEDATA *fd;
    register int rc;

    DPRINTF(1, "fileIO DREAD\n");

    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);

    rc = cdvdman_devready();
    if (rc >= 0) {
        fd = &cdvdman_handles[(int)f->privdata];
        cdvdman_srchspd = 0;

        rc = _sceCdReadDir(&fileinfo, fd->file_lsn, fd->read_pos, fd->fd_layer);
        if (rc >= 0) {
            if (rc) {
                fd->read_pos += 1;
            }
            strcpy(buf->name, fileinfo.name);
            cdvdman_fillstat(fileinfo.name, &buf->stat, &fileinfo);
        } else {
            SetEventFlag(cdvdman_read_ef, 1);
            return -2;
        }
    }

    SetEventFlag(cdvdman_read_ef, 1);

    return rc;
}

/* internal routine */
int cdvd_odcinit(CDVDMAN_FILEDATA *fh, int mode, int id)
{
    // TODO: implement
    return 0;
#if 0
    char cachefilename[512];
    int oldstate, ioctlarg;
    register u32 i;
    register int v1, fd, v2;
    register u32 u, m;

    cdvdman_iocache = 0;

    sprintf(cachefilename, "%sCache_%d_%ld_%ld_%d", cdvdman_cachedir, fh->fd_layer, fh->file_lsn, fh->filesize, id);

    DPRINTF(1, "Cachefile:%s Open_or_Close:%d\n", cachefilename, mode);

    v1 = v2 = 0;

    if (!mode) {
    odcinit_l1:

        if (fh->fd_cf_fd != -1) {
            v2 = close(fh->fd_cf_fd);
            DPRINTF(1, "Cache File Close: %d\n", v2);

            if (!(v2 < 0)) {
                if (!strncmp(cachefilename, "pfs", 3)) {
                    v2 = remove(cachefilename);
                } else {
                    if (strncmp(cachefilename, "host", 4)) {
                        v2 = 0;
                        remove(cachefilename);
                    }
                }

                DPRINTF(1, "Cache File %s remove: %d\n", cachefilename, v2);
            }
        }

        fh->fd_cf_fd = -1;
        fh->unk1 = 0;
        fh->unk3 = (int *)-1;
        fh->unk2 = 0;

        CpuSuspendIntr(&oldstate);
        FreeSysMemory(fh->fd_rcvbuf);
        CpuResumeIntr(oldstate);
        fh->fd_rcvbuf = 0;

        if (v1 < 0)
            DPRINTF(1, "cdvd_odcinit Open  Error %d\n", v1);
        if (v2 < 0)
            DPRINTF(1, "cdvd_odcinit Close Error %d\n", v2);

        return (mode) ? v1 : v2;
    } else {
        CpuSuspendIntr(&oldstate);
        fh->fd_rbsize = (!cdvdman_rcvbsec) ? 0x800 : (cdvdman_rcvbsec << 11);
        if ((fh->fd_rcvbuf = AllocSysMemory(SMEM_High, fh->fd_rbsize, 0)) == 0) {
            register u32 a, b;

            CpuResumeIntr(oldstate);
            fh->fd_cf_fd = -1;
            v1 = open(cachefilename, O_RDWR | O_CREAT | O_TRUNC, 0x1FF);
            if (v1 < 0)
                goto odcinit_l1;
            fd = v1;

            a = fh->filesize >> 11;
            if (fh->filesize & 0x7FF)
                a++;
            u = a >> 3;
            if (a & 0x7)
                u++;
            b = u >> 3;
            if (u & 0x7)
                b++;
            m = b >> 11;
            if (b & 0x7FF)
                m++;
            i = 0;
            ioctlarg = (m + a + 8) << 11;

            if (v2 < fh->fd_rbsize) {
                do {
                    ((char *)fh->fd_rcvbuf)[i] = 0;
                } while (++i < fh->fd_rbsize);
            }

            /* code here */

            fh->fd_cf_fd = fd;
            /* fh->unk1 = r_7???; */
            fh->unk3 = (int *)-1;

            DPRINTF(1, "Cache File Maked\n");

            return 0;
        } else {
            DPRINTF(1, "Rcvbuf MemAlloc Fail\n");
            CpuResumeIntr(oldstate);
            return -12;
        }
    }
#endif
}

int cdvdman_cacheinvl(CDVDMAN_FILEDATA *fd, int index)
{
    // TODO: handle cache
    return 0;
}

int cdvdman_invcaches()
{
    register int i = 0;
    register CDVDMAN_FILEDATA *fd = cdvdman_handles;

    do {
        if (cdvdman_handles[i].fd_flags & 4)
            cdvdman_cacheinvl(fd, i);
        fd++;
    } while (++i < 0x10);

    return 0;
}

/* For "cdrom" device OPS */
int cdrom_open(iop_file_t *f, const char *name, int mode, int arg4)
{
    sceCdlFILE fileinfo;
    char filename[0x80];
    char devctl_req[0x18];
    u32 resultp;
    int results;
    register int va0, va1, va2;
    register int rc = 0;
    register CDVDMAN_FILEDATA *fd;

    DPRINTF(1, "fileIO OPEN name= %s mode= 0x%08x layer %d\n", name, mode, f->unit);

    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);

    va0 = va1 = va2 = 0;

    do {
        if (!cdvdman_handles[va0].fd_flags) {
            if (!va1) {
                rc = va0;
                va1 = 1;
            }
        }
        if ((cdvdman_handles[va0].fd_flags & 8) != 0)
            va2 = 1;

        va0++;
    } while (va0 < 0x10);

    if ((!va1) || (va2)) {
        DPRINTF(0, "open fail name %s\n", name);
        SetEventFlag(cdvdman_read_ef, 1);
        return -24;
    }

    f->privdata = (void *)rc;
    fd = &cdvdman_handles[rc];

    strncpy(filename, name, 0x80);
    cdvdman_cdfname(filename);

    if ((mode & SCE_CdSTREAM) || (cdvdman_l0check(f->unit))) {
        cdvdman_srchspd = 0;
    } else {
        cdvdman_srchspd = (cdvdman_spinnom != -1) ? (cdvdman_spinnom > 0) : (mode & 0xFFFF);
    }

    if (f->unit < 2) {
        rc = cdvdman_devready();
        if (rc < 0) {
            SetEventFlag(cdvdman_read_ef, 1);
            return rc;
        }

        if (!sceCdLayerSearchFile(&fileinfo, filename, f->unit)) {
            DPRINTF(0, "open fail name %s\n", filename);
            SetEventFlag(cdvdman_read_ef, 1);
            return -2;
        }
        fd->fd_flags = 1;
    } else {
        DPRINTF(0, "open fail name %s\n", name);
        SetEventFlag(cdvdman_read_ef, 1);
        return -2;
    }

    cdvdman_srchspd = 0;

    if (mode & SCE_CdSTREAM) {
        memset(&devctl_req, 0, 0x18);

        ((u8 *)devctl_req)[0x12] = 0;
        ((u8 *)devctl_req)[0x11] = 0;
        ((u8 *)devctl_req)[0x10] = (cdvdman_trycnt == -1) ? 0 : cdvdman_trycnt;
        ((int *)devctl_req)[0x03] = STM0_MODE_START;
        ((int *)devctl_req)[0x00] = fileinfo.lsn;

        rc = devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &results, sizeof(int));
        if ((rc < 0) || (!results)) {
            fd->fd_flags = 0;
            SetEventFlag(cdvdman_read_ef, 1);
            return -2;
        }
        cdvdman_strmerr = 0;
        fd->fd_flags |= 8;
    }

    fd->file_lsn = fileinfo.lsn;
    fd->read_pos = 0;
    fd->filemode = mode & (~SCE_CdSTREAM);
    fd->filesize = fileinfo.size;
    fd->fd_layer = f->unit;

    if ((mode & (SCE_CdCACHE | SCE_CdSTREAM)) != SCE_CdCACHE) {
        f->mode = 1;
        SetEventFlag(cdvdman_read_ef, 1);
        return 0;
    }

    rc = -19;
    if (cdvdman_cache_fd != -1) {
        rc = cdvd_odcinit(fd, 1, (int)f->privdata);
        if (rc >= 0)
            fd->fd_flags |= 4;
    }

    if (rc < 0) {
        fd->fd_flags = 0;
        fd->fd_layer = 0;
        fd->filemode = 0;
        fd->read_pos = 0;
        fd->filesize = 0;
        fd->file_lsn = 0;
    } else
        f->mode = 1;

    SetEventFlag(cdvdman_read_ef, 1);

    return rc;
}

/* For "cdrom" device OPS */
int cdrom_close(iop_file_t *f)
{
    char devctl_req[0x18];
    u32 resultp;
    int results;
    register int rc;
    register CDVDMAN_FILEDATA *fd;

    DPRINTF(0, "fileIO CLOSE\n");

    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);
    fd = &cdvdman_handles[(int)f->privdata];

    if (fd->fd_flags & 8) {
        cdvdman_strmerr = 0;
        memset(&devctl_req, 0, 0x18);
        ((int *)devctl_req)[0x3] = STM0_MODE_STOP;
        rc = devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &results, sizeof(int));
        if ((rc < 0) || (!results)) {
            SetEventFlag(cdvdman_read_ef, 1);
            return -5;
        }
    }

    if ((fd->fd_flags & 0xC) == 4) {
        if (cdvd_odcinit(fd, 0, (int)f->privdata) < 0) {
            SetEventFlag(cdvdman_read_ef, 1);
            return -5;
        }
    }

    fd->file_lsn = 0;
    fd->read_pos = 0;
    fd->fd_flags = 0;
    fd->fd_layer = 0;
    fd->filemode = 1;

    f->mode = 0;
    SetEventFlag(cdvdman_read_ef, 1);

    return 0;
}

/* internal routine */
int cdvdman_ioread(iop_file_t *f, void *buf, int nbytes)
{
    sceCdRMode rmode;
    u32 read_res, read_lsn, file_lbn, offset, last_lbn, offs_ext;
    CDVDMAN_FILEDATA *fd;
    void *readbuf;
    register int fds, rda, rds, lsn, rdp, ofs, blk, sec;
    register int r;

    sec = 1;

    DPRINTF(1, "cdvd fileIO read start\n");

    r = cdvdman_devready();
    if (r < 0) {
        cdvdman_iocache = 0;
        return r;
    }

    fds = (int)f->privdata;
    fd = &cdvdman_handles[fds];
    cdvdman_iormode(&rmode, fd->filemode, f->unit);

    if (nbytes < 0)
        return -22;

    read_res = 0;
    offset = fd->read_pos;
    r = offset + nbytes;
    file_lbn = fd->file_lsn;
    if (fd->filesize < (u32)r)
        nbytes = fd->filesize - offset;

    last_lbn = (fd->filesize & 0x7FF) ? ((fd->filesize >> 11) + 1) : (fd->filesize >> 11);
    last_lbn += file_lbn;

    DPRINTF(1, "fds= %d read file_lbn= %d offset= %d\n", fds, file_lbn, offset);

    if (nbytes) {
        readbuf = 0;

        do {
            if (cdvdman_spinctl != -1) {
                rmode.spindlctrl = *(u8 *)&cdvdman_spinctl;
                switch (cdvdman_spinctl) {
                    case 0:
                        fd->filemode = 0;
                        break;
                    case 1:
                        fd->filemode = 1;
                        break;
                    case 2:
                        fd->filemode = 2;
                        break;
                    case 3:
                        fd->filemode = 3;
                        break;
                    case 4:
                        fd->filemode = 4;
                        break;
                    case 5:
                        fd->filemode = 5;
                        break;
                    default:
                        fd->filemode = 1;
                        break;
                }
            }

            offs_ext = 0;
            blk = nbytes;
            read_lsn = lsn = (offset >> 11) + file_lbn;
            ofs = offset & 0x7FF;

            if (nbytes < 0x4001) {
                register u32 t;

                r = (nbytes < 0) ? (nbytes + 0x7FF) : nbytes;
                t = r >> 11;
                if (nbytes & 0x7FF)
                    t++;
                sec = t + ((ofs > 0) ? 1 : 0);
            } else {
                blk = 0x4000;
                if ((readbuf == 0) || ((!ofs) || (!cdvdman_iocache))) {
                    sec = (!ofs) ? 8 : 9;
                } else {
                    register u32 t;

                    r = 0x800 - ofs;
                    t = sec - 1;
                    t <<= 11;
                    sec = 8;
                    lsn++;
                    offs_ext = r;
                    memcpy(buf, (void *)((u32)cdvdman_pb_fsvr + ofs + t), r);
                    cdvdman_iocache = 0;
                }
            }

            r = lsn + sec;
            readbuf = cdvdman_pb_fsvr;
            if (last_lbn < r)
                sec = last_lbn - lsn;

            DPRINTF(1, "sce_Read LBN= %d sectors= %d\n", lsn, sec);

            if ((!cdvdman_iocache) || (lsn < cdvdman_ioc_lsn) || ((lsn + sec) > (cdvdman_ioc_lsn + cdvdman_ioc_sec))) {
                if (((u32)buf & 0x3) || (ofs) || (blk != 0x4000)) {
                    rds = 8;
                    if (sec >= rds)
                        rds = sec;

                    if (last_lbn < (lsn + rds))
                        rds = last_lbn - lsn;

                    DPRINTF(1, "FIO Cache LSN:%d SEC:%d ADDR:%08x\n", lsn, rds, readbuf);

                    if (rds < 9)
                        rda = 0;
                    else
                        rda = rds - 8;

                    if (rda) {
                        for (;;) {
                            if (sceCdRE(lsn, rda, readbuf, &rmode))
                                break;
                            DPRINTF(1, "sce_Read ON Delay\n");
                            DelayThread(10000);
                        }

                        sceCdSync(0);
                        r = sceCdGetError();
                        if (r) {
                            DPRINTF(0, "Read Error= 0x%02x\n", r);
                            cdvdman_iocache = 0;
                            break;
                        }
                    }

                    rdp = (u32)rda << 11;

                    for (;;) {
                        if (sceCdRE(lsn + rda, rds - rda, (void *)((u32)readbuf + rdp), &rmode))
                            break;
                        DPRINTF(1, "sce_Read ON Delay\n");
                        DelayThread(10000);
                    }

                    sceCdSync(0);
                    r = sceCdGetError();
                    if (r) {
                        DPRINTF(0, "Read Error= 0x%02x\n", r);
                        cdvdman_iocache = 0;
                        break;
                    }

                    cdvdman_ioc_lsn = read_lsn;
                    cdvdman_ioc_sec = rds;
                    cdvdman_iocache = 1;

                    if (!offs_ext)
                        memcpy(buf, (void *)((u32)cdvdman_pb_fsvr + ofs), blk);
                    else
                        memcpy((void *)((u32)buf + offs_ext), cdvdman_pb_fsvr, blk - offs_ext);
                } else {
                    DPRINTF(1, "FIO Usr addr LSN:%d SEC:%d ADDR:%08x\n", lsn, sec, buf);

                    for (;;) {
                        if (sceCdRE(lsn, sec, buf, &rmode))
                            break;
                        DPRINTF(1, "sce_Read ON Delay\n");
                        DelayThread(10000);
                    }

                    sceCdSync(0);
                    r = sceCdGetError();
                    cdvdman_iocache = 0;
                    if (r) {
                        DPRINTF(1, "Read Error= 0x%02x\n", r);
                        break;
                    }
                }
            } else
                memcpy(buf, (void *)((u32)readbuf + ofs + ((u32)(lsn - cdvdman_ioc_sec) << 11)), blk);

            if (blk <= 0) {
                cdvdman_spinctl = -1;
                return blk;
            }

            buf = (void *)((u32)buf + blk);
            nbytes -= blk;
            offset += blk;
            read_res += blk;
        } while (nbytes);
    }

    fd->read_pos = offset;
    DPRINTF(1, "fileIO read ended\n");
    cdvdman_spinctl = -1;

    return read_res;
}

/* internal routine */
int cdvdman_stread(iop_file_t *f, void *buf, int nbyte)
{
    sceCdRMode rmode;
    char devctl_req[0x18];
    u32 results;
    register CDVDMAN_FILEDATA *fd;
    register u32 r;

    cdvdman_strmerr = 0;

    fd = &cdvdman_handles[(int)f->privdata];

    cdvdman_iormode(&rmode, fd->filemode, f->unit);

    nbyte >>= 11;
    rmode.spindlctrl = 0;
    rmode.trycount = 0;

    memset(&devctl_req, 0, 0x18);

    ((int *)devctl_req)[0x03] = 1;
    ((int *)devctl_req)[0x01] = nbyte;
    ((int *)devctl_req)[0x02] = (int)buf;

    devctl(cdvdman_stmdev, CDIOC_CDSTREAD0, &devctl_req, 0x18, &results, sizeof(u32));

    r = results << 11;
    fd->read_pos += r;
    cdvdman_strmerr = ((u32 *)devctl_req)[0x5];

    return r;
}

int cdrom_read(iop_file_t *f, void *buf, int nbytes)
{
    u32 result;
    register int rc;
    register CDVDMAN_FILEDATA *fd;

    if (nbytes < 0)
        return -22;

    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &result);

    fd = &cdvdman_handles[(int)f->privdata];

    if (cdvdman_mediactl(2)) {
        cdvdman_iocache = 0;
        cdvdman_invcaches();
    }

    if (!(fd->fd_flags & 8)) {
        if (fd->fd_flags & 4) {
            /* file cache code should be here */;
        } else
            rc = -1; /* dumb code */

        if (rc < 0)
            rc = cdvdman_ioread(f, buf, nbytes);
    } else {
        rc = cdvdman_stread(f, buf, nbytes);
    }

    SetEventFlag(cdvdman_read_ef, 1);

    return rc;
}

/* For "cdrom" device OPS */
int cdrom_ioctl(iop_file_t *f, int arg, void *param)
{
    register int r;

    r = 0;

    switch (arg) {
        case 0x10000:
            cdvdman_spinnom = -1;
            sceCdSpinCtrlIOP((int)param);
            return r;

#ifdef __CDVDMAN_SW_E35__
        case 0x10020:
            r = sceCdReadKey(((int *)param)[0], ((int *)param)[1], ((int *)param)[2], &((int *)param)[3]);
            if (r)
                return r;
            r = -16;
            break;
#endif

#ifdef __CDVDMAN_SW_E36__
        case 0x10008:
            sceCdDecSet(((int *)param)[0], ((int *)param)[1], ((int *)param)[2]);
            break;
#endif

#ifdef __CDVDMAN_NEWBIOS__
        case 0x10010:
            r = sceCdGetError();
            break;
#endif

#ifdef __CDVDMAN_BB_NAV__
        case 0x10030:
            r = sceCdGetDiskType();
            break;
#endif

#ifdef __CDVDMAN_NEWBIOS__
        case 0x6310:
            /* return "mfc0      $s0, PRId"*/
            break;
#endif

#ifdef __CDVDMAN_NEWBIOS__
        case 0x6311:
            /* alternate RcBypassCtl via SIO2 */
            break;
#endif

#ifdef __CDVDMAN_NEWBIOS__
        case 0x6312:
            /* RcBypassCtl via SIO2 related stuff */
            break;
#endif

        default:
            DPRINTF(0, "Un-support\n");
            r = -5;
            break;
    }

    return r;
}

/* For "cdrom" device OPS */
int cdrom_ioctl2(iop_file_t *f, int request, void *argp, size_t arglen, void *bufp, size_t buflen)
{
    char devctl_req[0x18];
    u32 resultp;
    int results;
    register int rc;
    register CDVDMAN_FILEDATA *fd;

    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);
    fd = &cdvdman_handles[(int)f->privdata];

    switch (request) {
        case CIOCSTREAMPAUSE:
            if (!(fd->fd_flags & 8)) {
                rc = -5;
                break;
            }

            memset(&devctl_req, 0, 0x18);
            ((int *)devctl_req)[0x3] = STM0_MODE_PAUSE;

            rc = devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &results, sizeof(int));
            if ((rc < 0) || (!results))
                rc = -5;
            else
                rc = 0;
            break;
        case CIOCSTREAMRESUME:
            if (!(fd->fd_flags & 8)) {
                rc = -5;
                break;
            }
            memset(&devctl_req, 0, 0x18);
            ((int *)devctl_req)[0x3] = STM0_MODE_RESUME;

            rc = devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &results, sizeof(int));
            if ((rc < 0) || (!results))
                rc = -5;
            else
                rc = 0;
            break;
        case CIOCSTREAMSTAT:
            if (!(fd->fd_flags & 8)) {
                rc = -5;
                break;
            }
            memset(&devctl_req, 0, 0x18);
            ((int *)devctl_req)[0x3] = STM0_MODE_STAT;

            rc = devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &results, sizeof(int));
            if (rc >= 0)
                rc = results;
            break;
        default:
            DPRINTF(0, "Un-support\n");
            rc = -5;
            break;
    }

    SetEventFlag(cdvdman_read_ef, 1);

    return rc;
}

/* For "cdrom" device OPS */
int cdrom_devctl(iop_file_t *f, const char *, int cmd, void *argp, unsigned int arglen, void *bufp, unsigned int buflen)
{
    char devctl_req[0x18];
    u32 resultp;
    int dummy, results;
    register int i = 0, j, rc;

    if (cmd == CDIOC_BREAK) {
        rc = i;
        if (!sceCdBreak())
            rc = -5;
        sceCdSync(4);
        return rc;
    }

    rc = 0;
    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);

    switch (cmd) {
        case CDIOC_READCLOCK:
            do {
                WaitEventFlag(cdvdman_scmd_ef, 1, EF_WAIT_AND, &resultp);
                rc = sceCdReadClock((sceCdCLOCK *)bufp);
                if (rc)
                    break;
            } while (i++ < 3);
            if (rc != 1)
                rc = -5;
            break;
        case CDIOC_GETDISKTYP:
            *(int *)bufp = sceCdGetDiskType();
            break;
        case CDIOC_GETERROR:
            if (cdvdman_strmerr)
                *(int *)bufp = cdvdman_strmerr;
            else
                *(int *)bufp = sceCdGetError();
            break;
        case CDIOC_TRAYREQ:
            if (sceCdTrayReq(*(int *)argp, (u32 *)bufp) != 1)
                rc = -5;
            break;
        case CDIOC_STATUS:
            *(int *)bufp = sceCdStatus();
            break;
        case CDIOC_POWEROFF:
            do {
                WaitEventFlag(cdvdman_scmd_ef, 1, EF_WAIT_AND, &resultp);
                rc = sceCdPowerOff((u32 *)bufp);
                if (rc)
                    break;
            } while (i++ < 3);
            if (rc != 1)
                rc = -5;
            break;
        case CDIOC_MMODE:
            sceCdMmode(*(int *)argp);
            break;
        case CDIOC_DISKRDY:
            *(int *)bufp = sceCdDiskReady(*(int *)argp);
            break;
        case CDIOC_STREAMINIT:
            memset(&devctl_req, 0, 0x18);
            ((int *)devctl_req)[0] = ((int *)argp)[0];
            ((int *)devctl_req)[1] = ((int *)argp)[1];
            ((int *)devctl_req)[3] = STM0_MODE_INIT;
            ((int *)devctl_req)[2] = ((int *)argp)[2];
            rc = devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &results, sizeof(int));
            if ((rc < 0) || (!results))
                rc = -5;
            else
                rc = 0;
            break;
        case CDIOC_SPINNOM:
            cdvdman_spinnom = 1;
            break;
        case CDIOC_SPINSTM:
            cdvdman_spinnom = 0;
            break;
        case CDIOC_TRYCNT:
            cdvdman_trycnt = *(u8 *)argp;
            break;
        case CDIOC_SEEK:
            if (sceCdSeek(*(u32 *)argp) != 1)
                rc = -5;
            else
                rc = 0;
            sceCdSync(6);
            break;
        case CDIOC_STANDBY:
            if (sceCdStandby() != 1)
                rc = -5;
            else
                rc = 0;
            sceCdSync(4);
            break;
        case CDIOC_STOP:
            if (sceCdStop() != 1)
                rc = -5;
            else
                rc = 0;
            sceCdSync(4);
            break;
        case CDIOC_PAUSE:
            if (sceCdPause() != 1)
                rc = -5;
            else
                rc = 0;
            sceCdSync(6);
            break;
        case CDIOC_GETTOC:
            rc = sceCdGetDiskType();
            /* strange compare */
            if (((rc >= 0x12) && (rc <= 0x13)) || (rc == 0x10) || (rc == 0x11)) {
                if (sceCdGetToc((u8 *)bufp) != 1)
                    rc = -5;
                else
                    rc = 0;
            } else {
                rc = -5;
                break;
            }
            break;
        case CDIOC_SETTIMEOUT:
            if (sceCdSetTimeout(1, *(int *)argp) != 1)
                rc = -5;
            else
                rc = 0;
            break;
        case CDIOC_READDVDDUALINFO:
            if (!sceCdReadDvdDualInfo(&dummy, (long unsigned int *)bufp))
                rc = -5;
            else
                rc = 0;
            break;
        case CDIOC_INIT:
            if (!sceCdInit(*(int *)argp))
                rc = -5;
            else
                rc = 0;
            break;
        case 0x438C:
            cdvdman_spinnom = 0x2;
            break;
        case 0x438D:
            cdvdman_spinnom = 0x3;
            break;
        case 0x438E:
            cdvdman_spinnom = 0x4;
            break;
        case 0x438F:
            cdvdman_spinnom = 0x5;
            break;
        case 0x4390:
            cdvdman_spinnom = 0x14;
            break;
        case 0x4391:
            *(int *)bufp = sceCdSC(0xFFFFFFF5, &dummy); /* get cdvdman_intr_ef */
            break;
        case CDIOC_APPLYSCMD:
            if (sceCdApplySCmd(*(u8 *)argp, &((int *)argp)[1], arglen - 4, bufp) != 1)
                rc = -5;
            else
                rc = 0;
            break;
        case CDIOC_FSCACHEINIT:
            if (cdvdman_cache_fd != -1) {
                rc = -16;
                break;
            }

            i = 0;

            if (arglen) {
                if (*(u8 *)argp != 0x2C) {
                    do {
                        if (!((u8 *)argp)[i])
                            break;
                        cdvdman_cachedir[i] = ((u8 *)argp)[i];
                        i++;
                        if (i == arglen)
                            break;
                    } while (((u8 *)argp)[i] != 0x2C);
                }
            }

            if (i <= arglen) {
                j = i++;
                if (i < arglen) {
                    if (((u8 *)argp)[i] != 0x2C) {
                        do {
                            if (!((u8 *)argp)[i])
                                break;
                            i++;
                            if (i >= arglen)
                                break;
                        } while (((u8 *)argp)[i] != 0x2C);
                    }
                }

                if (i <= arglen) {
                    ((char *)argp)[i] = 0;
                    cdvdman_rcvbsec = strtol(&((char *)argp)[j], 0, 10);
                    rc = cdvdman_cacheinit(strtol(&((char *)argp)[++i], 0, 10), cdvdman_cachedir, 1);
                    break;
                }
            }

            rc = -22;
            break;
        case CDIOC_FSCACHEDELETE:
            i = 0;
            do {
                if (cdvdman_handles[i].fd_flags & 4)
                    break;
                i++;
            } while (i < 0x10);
            if (i == 0x10) {
                rc = cdvdman_cacheinit(0, 0, 0);
            } else
                rc = -16;
            break;
        default:
            DPRINTF(0, "Un-support devctl %08x\n", cmd);
            rc = -5;
            break;
    }

    SetEventFlag(cdvdman_read_ef, 1);

    return rc;
}

/* For "cdrom" device OPS */
int cdrom_lseek(iop_file_t *f, int offset, int pos)
{
    char devctl_req[0x18];
    u32 resultp;
    int results;
    register int rc;
    register u32 loc = 0;
    register CDVDMAN_FILEDATA *fd;

    DPRINTF(0, "fileIO SEEK\n");

    WaitEventFlag(cdvdman_read_ef, 1, EF_WAIT_CLEAR, &resultp);
    fd = &cdvdman_handles[(int)f->privdata];

    switch (pos) {
        case SEEK_SET:
            loc = fd->read_pos = offset;
            break;
        case SEEK_CUR:
            loc = fd->read_pos += offset;
            break;
        case SEEK_END:
            loc = fd->read_pos = fd->filesize - offset;
            break;
    }

    if (fd->read_pos > fd->filesize)
        loc = fd->read_pos = fd->filesize;

    if (fd->fd_flags & 8) {
        memset(&devctl_req, 0, 0x18);
        ((int *)devctl_req)[0x3] = 9;
        ((int *)devctl_req)[0x0] = fd->file_lsn + (((loc >= 0) ? loc : (loc + 0x7FF)) >> 11); /* Hmm... "addiu   $t0, $s1, 0x7FF" */
        rc = devctl(cdvdman_stmdev, CDIOC_CDSTREAM0, &devctl_req, 0x18, &results, sizeof(int));
        if ((rc < 0) || (!results))
            loc = -5;
    }

    SetEventFlag(cdvdman_read_ef, 1);

    return loc;
}

/* Dummy IOP device call entry */
int cdrom_nulldev(iop_file_t *nuldev, ...)
{
    DPRINTF(0, "nulldev0 call\n");
    return -5;
}

s64 cdrom_nulldev64(iop_file_t *nuldev, ...)
{
    DPRINTF(0, "nulldev0 call\n");
    return -5;
}
