
#include "cdvdman-internal.h"

/* internal routine */
int cdvdman_cmpname(const char *fn1, const char *fn2)
{
    return (u32)strncmp(fn1, fn2, 0xC) < 1;
}

/* internal routine */
int cdvdman_finddir(int parent, char *name)
{
    register int i;
    register char *n;


    n = cdvdman_dirtbl[0].name;
    i = 0;

    do {
        register int p;

        p = cdvdman_dirtbl[i].parent;

        if (!p)
            break;
        if (p == parent) {
            if (!strcmp(name, n))
                return i + 1;
        }

        n += sizeof(CD_DIR_ENTRY);
    } while (++i < CdlMAXDIR);

    return -1;
}

/* internal routine */
int CdSearchFile(sceCdlFILE *fp, const char *name, int layer)
{
    char buffer[32];
    register const char *s;
    register char *d = NULL;
    register int index;
    register int parent;

    DPRINTF(1, "CdSearchFile: start name= %s layer= %d\n", name, layer);

    if (cdvdman_fs_layer != layer)
        cdvdman_fs_cache = 0;

    if ((!cdvdman_mediactl(0)) && (cdvdman_fs_cache)) /* bad condition check scheme, possible error */
    {
        DPRINTF(1, "CdSearchFile: cache dir data used\n");
    } else {
        DPRINTF(1, "CdSearchFile Topen= %s\n", name);
        if (!CD_newmedia(layer)) {
            cdvdman_fs_cache = 0;
            return 0;
        }
        cdvdman_fs_cache = 1;
    }

    if (name[0] != '\\')
        return 0;

    buffer[0] = 0;
    parent = 1;
    s = name;
    index = 0;

    do {
        if (*s != '\\') {
            register u32 b;

            d = buffer;

            do {
                b = *(u8 *)s;
                if (!b)
                    break;

                s++;
                *d = b;
                d++;
            } while (*s != '\\');
        }

        if (!*s)
            break;

        s++;
        *d = 0;

        parent = cdvdman_finddir(parent, buffer);
        if (parent == -1) {
            buffer[0] = 0;
            break;
        } else
            index++;

    } while (index < CdlMAXLEVEL);

    if (index >= CdlMAXLEVEL) {
        DPRINTF(1, "%s: path level (%d) error\n", name, index);
        return 0;
    }

    if (buffer[0]) {
        *d = 0;
        if (CD_cachefile(parent, layer)) {
            register sceCdlFILE *f;

            DPRINTF(2, "CdSearchFile: searching %s...\n", buffer);

            index = 0;
            f = cdvdman_filetbl;
            s = cdvdman_filetbl[0].name;

            do {
                if (!cdvdman_filetbl[index].name[0])
                    break;

                DPRINTF(1, "%d %s %s\n", index, s, buffer);

                if (cdvdman_cmpname(s, buffer)) {
                    DPRINTF(2, "%s:  found\n", buffer);

                    *fp = *f;

                    if (layer)
                        fp->lsn += cdvdman_fs_base2;

                    return 1;
                }

                f++;
                s += sizeof(sceCdlFILE);
            } while (++index < CdlMAXFILE);

            DPRINTF(1, "%s: not found\n", buffer);
        } else {
            DPRINTF(1, "CdSearchFile: disc error\n");
            return 0;
        }
    } else DPRINTF(1, "%s: dir was not found\n", name);

    return 0;
}

/* Exported entry #84 */
int sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer)
{
    u32 resultp;
    register int i, r;

    if (PollEventFlag(cdvdman_srch_ef, 1, EF_WAIT_CLEAR, &resultp) == 0xFFFFFE5B)
        return 0;

    i = 0;
    do {
        if (!name[i])
            break;
        cdvdman_sfname[i] = ((u8 *)name)[i];
    } while (++i < 0x3FF);
    cdvdman_sfname[i] = 0;

    cdvdman_srchspd = 1;
    r = CdSearchFile(fp, cdvdman_sfname, layer);
    set_ev_flag(cdvdman_srch_ef, 1);

    return r;
}

/* Exported entry #10 */
int sceCdSearchFile(sceCdlFILE *fp, const char *name)
{
    return sceCdLayerSearchFile(fp, name, 0);
}
