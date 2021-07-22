
#include <tamtypes.h>

#include "sysmem.h"
#include "loadcore.h"
#include "iopelf.h"
#include "romdir.h"
#include "irx.h" // ps2sdk file for IMPORT_MAGIC

#define BOOTMODE_START *((vu32 **)0x3F0)
#define BOOTMODE_END   *((vu32 **)0x3F4)

typedef int (*func)();

enum tag_BOOTUPCB_PRIO {
    BOOTUPCB_FIRST = 0,
    BOOTUPCB_RUN_UDNL = 1,
    BOOTUPCB_NORMAL = 2,
    BOOTUPCB_LAST = 3,
    BOOTUPCB_PRIORITIES
} BOOTUPCB_PRIO;


#define FLAG_EXPORT_QUEUED 1
#define FLAG_IMPORT_QUEUED 2

#define FLAG_NO_AUTO_LINK 1

#define INS_JR    2
#define INS_ADDIU 9
#define INS_JR_RA 0x03E00008
#define INS_J     0x08000000

typedef struct boot_params
{
    int ramMBSize;       //+00/0 size of iop ram in megabytes (2 or 8)
    int bootInfo;        //+04/1 ==QueryBootMode(KEY_IOPbootinfo)
    char *udnlString;    //+08/2 points to the undl reboot string, NULL if no string
    u32 firstModuleAddr; //+0C/3 the load address of the first module (sysmem)
    int pos;             //+10/4
    int size;            //+14/5
    int numConfLines;    //+18/6 number of lines in IOPBTCONF
    u32 **moduleAddrs;   //+1C/7 pointer to an array of addresses to load modules from
} BOOT_PARAMS;           //=20


void _start(BOOT_PARAMS *init); // has to be declared first!

lc_internals_t lc_internals;

u32 free;
u32 sysmem_00;
u32 modules_count;
u32 module_index;
u32 *place;        // addr of 8 * 31 = 8 * linesInIopbtconf	//place[2][31]
u32 bootmodes[17]; // was 16?
u32 bootmodes_size;

u32 bm_end;

#if 0
struct irx_export_table loadcore_stub __attribute__((section(".text"))) = {
	EXPORT_MAGIC,
	0,
	VER(1, 1), // 1.1 => 0x101
	0,
	"loadcore",
	(func)_start, // entrypoint
	(func)retonly,
	(func)retonly,
	(func)GetLoadcoreInternalData,
	(func)FlushIcache,
	(func)FlushDcache,
	(func)RegisterLibraryEntries,
	(func)ReleaseLibraryEntries,
	(func)LinkImports,
	(func)UnlinkImports,
	(func)RegisterNonAutoLinkEntries,
	(func)QueryLibraryEntryTable,
	(func)QueryBootMode,
	(func)RegisterBootMode,
	(func)SetNonAutoLinkFlag,
	(func)UnsetNonAutoLinkFlag,
	(func)LinkModule,
	(func)UnlinkModule,
	(func)retonly,
	(func)retonly,
	(func)RegisterPostBootCallback,
	(func)SetCacheCtrl,
	(func)ReadModuleHeader,
	(func)LoadModuleImage,
	(func)FindImageInfo,
	0};
#endif

///////////////////////////////////////////////////////////////////////
void retonly() {}

///////////////////////////////////////////////////////////////////////
void RegisterBootMode(iop_bootmode_t *b)
{
    int i;

    if (((b->len + 1) * 4) < (16 - bootmodes_size)) {
        u32 *p = &bootmodes[bootmodes_size];
        for (i = 0; i < b->len + 1; i++)
            p[i] = ((u32 *)b)[i];
        p[i] = 0;
        bootmodes_size += b->len + 1;
    }
}

///////////////////////////////////////////////////////////////////////
int *QueryBootMode(int id)
{
    int *b;

    for (b = (int *)&bootmodes[0]; *b; b += ((iop_bootmode_t *)b)->len + 1)
        if (id == ((iop_bootmode_t *)b)->id)
            return b;
    return NULL;
}

///////////////////////////////////////////////////////////////////////
int match_name(struct irx_export_table *src, struct irx_export_table *dst)
{
    return (*(int *)(src->name + 0) == *(int *)(dst->name + 0)) &&
           (*(int *)(src->name + 4) == *(int *)(dst->name + 4));
}

///////////////////////////////////////////////////////////////////////
int match_version_major(struct irx_export_table *src, struct irx_export_table *dst)
{
    return ((src->version >> 8) - (dst->version >> 8));
}

///////////////////////////////////////////////////////////////////////
int match_version_minor(struct irx_export_table *src, struct irx_export_table *dst)
{
    return ((unsigned char)src->version - (unsigned char)dst->version);
}

///////////////////////////////////////////////////////////////////////
int fix_imports(struct irx_import_table *imp, struct irx_export_table *exp)
{
    void **ef;
    struct irx_import_stub *fs;
    int count = 0, ordinal;

    for (ef = exp->fptrs; *ef; ef++) {
        count++; //count number of exported functions
    }

    for (fs = (struct irx_import_stub *)imp->stubs; fs->jump; fs++) {
        if ((fs->ori_zero >> 10) != INS_ADDIU)
            break;

        ordinal = fs->fno;
        if (ordinal < count) {
            fs->jump = (((u32)exp->fptrs[ordinal] >> 2) & 0x3FFFFFF) | INS_J;
        } else {
            fs->jump = INS_JR_RA;
        }
    }

    imp->mode |= FLAG_IMPORT_QUEUED;
    return 0;
}

///////////////////////////////////////////////////////////////////////
// Check the structure of the import table.
// Return 0 if a bad or empty import table is detected.
// Return a non-zero value if a valid import table is detected.
//
int check_import_table(struct irx_import_table *imp)
{
    struct irx_import_stub *f;

    if (imp->magic != IMPORT_MAGIC)
        return 0;
    for (f = (struct irx_import_stub *)imp->stubs; f->jump; f++) {
        if (f->ori_zero >> 10 != INS_ADDIU)
            return 0;
        if ((f->jump != INS_JR_RA) && (f->jump >> 26 != INS_JR))
            return 0;
    }
    if (f->ori_zero || f->fno)
        return 0;
    return ((struct irx_import_stub *)imp->stubs < f);
}

///////////////////////////////////////////////////////////////////////[OK]

// Return 0 if successful
int link_client(struct irx_import_table *imp)
{
    struct irx_export_table *e;

    for (e = lc_internals.let_next; e; e = (struct irx_export_table *)e->magic) {

        if (!(e->mode & FLAG_NO_AUTO_LINK)) {
            if (match_name(e, (struct irx_export_table *)imp)) {
                if (match_version_major(e, (struct irx_export_table *)imp) == 0) {
                    fix_imports(imp, e);
                    imp->next = (struct irx_import_table *)e->next;
                    e->next = (struct irx_export_table *)imp;
                    FlushIcache();
                    return 0;
                }
            }
        }
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////[OK]
int LinkImports(void *addr, int size)
{
    struct irx_import_table *p;
    int i;
    u32 *_addr = (u32 *)addr;

    for (i = 0; i < size / 4; i++, _addr++) {
        p = (struct irx_import_table *)_addr;
        if ((p->magic == IMPORT_MAGIC) &&
            check_import_table(p) &&
            ((p->mode & 7) == 0) &&
            link_client(p)) {
            UnlinkImports(p, size);
            return -1;
        }
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////[OK]
int unlink_client(struct irx_import_table *i1, struct irx_import_table *i2)
{
    struct irx_import_table *i, *tmp;

    if (i1->next == i2) {
        i1->next = i2->next;
        return 0;
    }
    for (i = i1->next; i->next;) {
        tmp = i->next;
        if (tmp == i2) {
            i->next = tmp->next;
            tmp->next = NULL;
            return 0;
        }
        i = tmp;
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////[OK]
void restore_imports(struct irx_import_table *imp)
{
    struct irx_import_stub *f;

    for (f = (struct irx_import_stub *)imp->stubs; (f->jump) && ((f->ori_zero >> 10) == INS_ADDIU); f++)
        f->jump = INS_JR_RA;
}

///////////////////////////////////////////////////////////////////////[OK]
int UnlinkImports(void *addr, int size)
{
    struct irx_export_table *e;
    struct irx_export_table *i;
    struct irx_export_table *tmp;
    void *limit = addr + (size & ~0x3);

    for (e = (struct irx_export_table *)lc_internals.let_next; e; e = (struct irx_export_table *)e->magic) {
        for (i = e->next; i; i = i->next) {
            if (((u32)i >= (u32)addr) && ((u32)i < (u32)limit)) {
                if (unlink_client((struct irx_import_table *)e, (struct irx_import_table *)i))
                    return -1;
                i->mode &= ~0x7;
                restore_imports((struct irx_import_table *)i);
            }
        }
        if (((u32)e >= (u32)addr) && ((u32)e < (u32)limit))
            ReleaseLibraryEntries(e);
    }
    /*
	for (i=let.mda; i->next; )
		if ((i->next >= addr) && (i->next < limit)){
			i->next->mode &= ~0x7;
			restore_imports(i->next);
			tmp = i->next->next;
			i->next->next=NULL;
			i->next=tmp;
		}else
			i=i->next;
*/
    return 0;
}

///////////////////////////////////////////////////////////////////////
int SetNonAutoLinkFlag(struct irx_export_table *e)
{
    return (e->mode |= FLAG_NO_AUTO_LINK);
}

///////////////////////////////////////////////////////////////////////
int UnsetNonAutoLinkFlag(struct irx_export_table *e)
{
    return (e->mode &= ~FLAG_NO_AUTO_LINK);
}

///////////////////////////////////////////////////////////////////////
int RegisterPostBootCallback(BootupCallback_t function, int priority, int *result)
{
    int x;
    register int r;
    if (place == NULL) {
        x = 1;
        r = function(&x, 0);
        if (result)
            *result = r;
        return 0;
    }

    __asm__("move %0, $gp\n"
            : "=r"(x)
            :);

    place[0] = (u32)function + (priority & 3);
    place[1] = x;
    place[2] = 0;
    place += 2;
    return 1;
}

///////////////////////////////////////////////////////////////////////
void LinkModule(ModuleInfo_t *ii)
{
    ModuleInfo_t *p;
    for (p = lc_internals.image_info; p->next && (p->next < (u32)ii); p = (ModuleInfo_t *)p->next)
        ;

    ii->next = p->next;
    p->next = (u32)ii;

    ii->id = module_index++;
    modules_count++;
}

///////////////////////////////////////////////////////////////////////
void UnlinkModule(ModuleInfo_t *ii)
{
    ModuleInfo_t *p;
    if (ii)
        for (p = lc_internals.image_info; p->next; p = (ModuleInfo_t *)p->next)
            if (p->next == (u32)ii) {
                p->next = ((ModuleInfo_t *)p->next)->next;
                modules_count--;
                return;
            }
}

ModuleInfo_t *FindImageInfo(void *addr)
{
    register ModuleInfo_t *ii;
    for (ii = lc_internals.image_info; ii; ii = (ModuleInfo_t *)ii->next)
        if (((u32)addr >= ii->text_start) &&
            ((u32)addr < ii->text_start + ii->text_size + ii->data_size + ii->bss_size))
            return ii;
    return 0;
}

///////////////////////////////////////////////////////////////////////
int RegisterLibraryEntries(struct irx_export_table *es)
{
    struct irx_export_table *p;
    struct irx_export_table *plast;
    struct irx_export_table *pnext;
    struct irx_export_table *tmp;
    struct irx_export_table *snext;

    if ((es == NULL) || (es->magic != EXPORT_MAGIC))
        return -1;

    plast = NULL;
    for (p = (struct irx_export_table *)lc_internals.let_next; p; p = (struct irx_export_table *)p->magic) {
        if (match_name(es, p) == 0 ||
            match_version_major(es, p) == 0)
            continue;

        if (match_version_minor(es, p) == 0)
            return -1;
        pnext = p->next;
        p->next = NULL;

        for (tmp = pnext; tmp;) {
            if (tmp->mode & FLAG_NO_AUTO_LINK) {
                pnext->magic = (u32)tmp;
                pnext = tmp->next;
                tmp->next = NULL;
            } else {
                tmp->next = plast;
                plast = tmp;
            }
            tmp = tmp->next;
        }
    }

    if (lc_internals.mda_next) {
        for (tmp = lc_internals.mda_next; tmp->next; tmp = tmp->next) { //free
            if ((match_name(es, tmp->next)) &&
                (match_version_major(es, tmp->next) == 0)) {
                snext = tmp->next->next;
                tmp->next->next = plast;
                plast = tmp->next;
                tmp->next = snext;
            } else
                tmp = tmp->next;
        }
    }

    es->next = 0;
    while (plast) {
        snext = plast->next;
        fix_imports((struct irx_import_table *)plast, es);
        plast->next = es->next;
        es->next = plast;
        plast = snext;
    }
    es->mode &= ~FLAG_NO_AUTO_LINK;
    es->magic = (u32)lc_internals.let_next;
    lc_internals.let_next = es;
    FlushIcache();

    return 0;
}

///////////////////////////////////////////////////////////////////////
int ReleaseLibraryEntries(struct irx_export_table *e)
{
    register struct irx_export_table *n, *p, *next, *prev;

    prev = 0;
    p = lc_internals.let_next;
    while ((p) && (p != e)) {
        prev = p;
        p = (struct irx_export_table *)prev->magic;
    }
    if (p != e)    // if (0 != e)
        return -1; //japanese BUG for e==p==0

    n = e->next;
    e->next = 0;

    prev->magic = e->magic;
    e->magic = 0x41C00000;

    while (n) {
        next = n->next;
        if (link_client((struct irx_import_table *)n)) {
            restore_imports((struct irx_import_table *)n);
            n->mode = (n->mode & ~2) | 4;
            n->next = lc_internals.mda_prev;
            lc_internals.mda_prev = n;
        }
        n = next;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////
int RegisterNonAutoLinkEntries(struct irx_export_table *e)
{
    if ((e == NULL) || (e->magic != EXPORT_MAGIC)) {
        return -1;
    }
    e->mode |= FLAG_NO_AUTO_LINK;
    e->magic = (u32)lc_internals.let_next; // --add as first
    lc_internals.let_next = e;             // /
    FlushIcache();

    return 0;
}

///////////////////////////////////////////////////////////////////////
void *QueryLibraryEntryTable(iop_library_t *e)
{
    struct irx_export_table *p = lc_internals.let_next;
    while (p) {
        if ((match_name(p, e)) && (match_version_major(p, e) == 0)) {
            return (void *)p->fptrs;
        }
        p = (struct irx_export_table *)p->magic;
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////
lc_internals_t *GetLoadcoreInternalData()
{
    return &lc_internals;
}

///////////////////////////////////////////////////////////////////////
void _FlushIcache()
{
    u32 status;
    u32 s1450;
    u32 s1578;
    u32 icache;
    u32 *p;

    __asm__("mfc0 %0, $12\n"
            : "=r"(status)
            :);

    __asm__("mtc0 %0, $12\n" ::"r"(0));

    s1450 = *(vu32 *)0xBF801450;
    *(vu32 *)0xBF801450 &= ~1;
    *(vu32 *)0xBF801450;

    s1578 = *(vu32 *)0xBF801578;
    *(vu32 *)0xBF801578 = 0;
    *(vu32 *)0xBF801578;

    icache = *(vu32 *)0xFFFE0130;
    *(vu32 *)0xFFFE0130 = 0xC04;
    *(vu32 *)0xFFFE0130;

    __asm__("mtc0 %0, $12\n" ::"r"(0x10000));

    for (p = 0; p < (u32 *)0x400; p += 4) // 4KB instruction cache
        *p = 0;

    __asm__("mtc0 %0, $12\n" ::"r"(0));

    *(vu32 *)0xFFFE0130 = icache;
    *(vu32 *)0xFFFE0130;
    *(vu32 *)0xBF801578 = s1578;
    *(vu32 *)0xBF801578;
    *(vu32 *)0xBF801450 = s1450;
    *(vu32 *)0xBF801450;

    __asm__("mtc0 %0, $12\n"
            :
            : "r"(status));
}

void FlushIcache()
{
    __asm__(
        "la   $26, %0\n"
        "lui  $27, 0xA000\n"
        "or   $26, $27\n"
        "jr   $26\n"
        "nop\n"
        :
        : "i"(_FlushIcache));
}

///////////////////////////////////////////////////////////////////////
void _FlushDcache()
{
    u32 status;
    u32 s1450;
    u32 s1578;
    u32 icache;
    u32 *p;

    __asm__("mfc0 %0, $12\n"
            : "=r"(status)
            :);

    __asm__("mtc0 %0, $12\n" ::"r"(0));

    s1450 = *(vu32 *)0xBF801450;
    *(vu32 *)0xBF801450 &= ~1;
    *(vu32 *)0xBF801450;

    s1578 = *(vu32 *)0xBF801578;
    *(vu32 *)0xBF801578 = 0;
    *(vu32 *)0xBF801578;

    icache = *(vu32 *)0xFFFE0130;
    *(vu32 *)0xFFFE0130 = 0xC4;
    *(vu32 *)0xFFFE0130;

    __asm__("mtc0 %0, $12\n" ::"r"(0x10000));

    for (p = 0; p < (u32 *)0x100; p += 4) // 1KB data cache
        *p = 0;

    __asm__("mtc0 %0, $12\n" ::"r"(0));

    *(vu32 *)0xFFFE0130 = icache;
    *(vu32 *)0xFFFE0130;
    *(vu32 *)0xBF801578 = s1578;
    *(vu32 *)0xBF801578;
    *(vu32 *)0xBF801450 = s1450;
    *(vu32 *)0xBF801450;

    __asm__("mtc0 %0, $12\n"
            :
            : "r"(status));
}

void FlushDcache()
{
    __asm__(
        "la   $26, %0\n"
        "lui  $27, 0xA000\n"
        "or   $26, $27\n"
        "jr   $26\n"
        "nop\n"
        :
        : "i"(_FlushDcache));
}

///////////////////////////////////////////////////////////////////////
void _SetIcache(u32 val)
{
    u32 status;

    __asm__("mfc0 %0, $12\n"
            : "=r"(status)
            :);

    __asm__("mtc0 %0, $12\n" ::"r"(0));

    *(vu32 *)0xFFFE0130 = val;
    *(vu32 *)0xFFFE0130;

    __asm__("mtc0 %0, $12\n"
            :
            : "r"(status));
}

void SetCacheCtrl(u32 val)
{
    __asm__(
        "la   $26, %0\n"
        "lui  $27, 0xA000\n"
        "or   $26, $27\n"
        "jr   $26\n"
        "nop\n"
        :
        : "i"(_SetIcache));
}

///////////////////////////////////////////////////////////////////////
int ReadModuleHeader(void *image, FileInfo_t *result)
{
    COFF_HEADER *coffhdr = image;
    COFF_scnhdr *section = (COFF_scnhdr *)((char *)image + sizeof(COFF_HEADER)); //0x4C

    if ((coffhdr->f_magic == 0x162) && //COFF loading
        (coffhdr->opthdr.magic == 0x107) &&
        (coffhdr->f_nscns < 32) &&
        ((coffhdr->f_opthdr & 0x2FFFF) == 0x20038) &&
        (section->s_paddr == coffhdr->opthdr.text_start)) {

        if (coffhdr->opthdr.vstamp == 0x7001)
            return -1;
        result->ModuleType = 1;
        result->EntryPoint = coffhdr->opthdr.entry;
        result->gp = coffhdr->opthdr.gp_value;
        result->text_start = coffhdr->opthdr.text_start;
        result->text_size = coffhdr->opthdr.tsize;
        result->data_size = coffhdr->opthdr.dsize;
        result->bss_size = coffhdr->opthdr.bsize;
        result->MemSize = coffhdr->opthdr.bss_start + coffhdr->opthdr.bsize - coffhdr->opthdr.text_start;
        result->mod_id = (IopModuleID_t *)coffhdr->opthdr.moduleinfo;
        return result->ModuleType;
    } else {
        ELF_HEADER *eh = (ELF_HEADER *)image;
        ELF_PHR *ph = (ELF_PHR *)((char *)eh + eh->e_phoff);
        //if ((eh->e_ident[EI_CLASS] != ELFCLASS32) ||
        //(eh->e_ident[EI_DATA]) != ELFDATA2LSB))	return -1;//break
        if (*(u16 *)(eh->e_ident + 4) != 0x101)
            return -1;
        if (eh->e_machine != EM_MIPS)
            return -1; //break
        if (eh->e_phentsize != sizeof(ELF_PHR))
            return -1; //break
        if (eh->e_phnum != 2)
            return -1; //break
        if (ph[0].p_type != PT_SCE_IOPMOD)
            return -1; //break
        if (eh->e_type != ET_SCE_IOPRELEXEC) {
            if (eh->e_type != eh->e_phnum) //ET_EXEC)
                return -1;                 //only
            result->ModuleType = 3;
        } else
            result->ModuleType = 4;
        ELF_IOPMOD *im = (ELF_IOPMOD *)((char *)image + ph[0].p_offset);
        result->EntryPoint = im->entry;
        result->gp = im->gp_value;
        result->text_start = ph[1].p_vaddr;
        result->text_size = im->text_size;
        result->data_size = im->data_size;
        result->bss_size = im->bss_size;
        result->MemSize = ph[1].p_memsz;
        result->mod_id = (IopModuleID_t *)im->moduleinfo;
        return result->ModuleType;
    }
    result->ModuleType = -1;
    return -1;
}

#define MODULE_TYPE_COFF       1
#define MODULE_TYPE_2          2
#define MODULE_TYPE_EXEC       3
#define MODULE_TYPE_IOPRELEXEC 4

///////////////////////////////////////////////////////////////////////
void setImageInfo(FileInfo_t *fi, ModuleInfo_t *ii)
{
    ii->next = 0;
    ii->name = NULL;
    ii->version = 0;
    ii->flags = 0;
    ii->id = 0;
    if ((int)fi->mod_id != -1) {
        ii->name = fi->mod_id->name;
        ii->version = fi->mod_id->version;
    }
    ii->entry = fi->EntryPoint;
    ii->gp = fi->gp;
    ii->text_start = fi->text_start;
    ii->text_size = fi->text_size;
    ii->data_size = fi->data_size;
    ii->bss_size = fi->bss_size;
}

///////////////////////////////////////////////////////////////////////
void load_type_1(COFF_HEADER *image)
{
    SHDR *s0 = (SHDR *)((char *)image + *(int *)((char *)image + 0x60));
    lc_memcpy(s0, image->opthdr.text_start, image->opthdr.tsize);
    lc_memcpy((char *)s0 + image->opthdr.tsize, image->opthdr.data_start, image->opthdr.dsize);
    if (image->opthdr.bss_start && image->opthdr.bsize)
        lc_zeromem((void *)image->opthdr.bss_start, image->opthdr.bsize / 4);
}

///////////////////////////////////////////////////////////////////////
void load_type_3(void *image)
{
    ELF_PHR *ph = (ELF_PHR *)((char *)image + ((ELF_HEADER *)image)->e_phoff);
    lc_memcpy(image + ph[1].p_offset, ph[1].p_vaddr, ph[1].p_filesz);
    if (ph[1].p_filesz < ph[1].p_memsz)
        lc_zeromem(ph[1].p_vaddr + ph[1].p_filesz,
                   (ph[1].p_memsz - ph[1].p_filesz) / 4);
}

///////////////////////////////////////////////////////////////////////
#define R_MIPS_32   2
#define R_MIPS_26   4
#define R_MIPS_HI16 5
#define R_MIPS_LO16 6

void load_type_4(ELF_HEADER *image, FileInfo_t *fi)
{
    ELF_PHR *ph = (ELF_PHR *)((char *)image + image->e_phoff);
    ELF_SHR *sh = (ELF_SHR *)((char *)image + image->e_shoff);
    ELF_REL *rel;
    int i, j, scount;
    u32 *b, *b2, tmp;

    //ph[0] - .iopmod, skip
    fi->EntryPoint += (u32)fi->text_start;
    fi->gp += (u32)fi->text_start;
    if ((int)fi->mod_id != -1)
        fi->mod_id = (IopModuleID_t *)((int)fi->mod_id + fi->text_start);
    lc_memcpy((char *)image + ph[1].p_offset, fi->text_start, ph[1].p_filesz);

    if (ph[1].p_filesz < ph[1].p_memsz) {
        lc_zeromem(ph[1].p_vaddr + ph[1].p_filesz + fi->text_start, (ph[1].p_memsz - ph[1].p_filesz));
    }

    for (i = 1; i < image->e_shnum; i++) {
        if (sh[i].sh_type == SHT_REL) {
            ELF_REL *rel = (ELF_REL *)(sh[i].sh_offset + (char *)image);
            scount = sh[i].sh_size / sh[i].sh_entsize;
            for (j = 0; j < scount; j++) {
                b = (u32 *)(fi->text_start + rel[j].r_offset);
                switch ((u8)rel[j].r_info) {
                    case R_MIPS_LO16:
                        *b = (*b & 0xFFFF0000) | (((*b & 0x0000FFFF) + (u32)fi->text_start) & 0xFFFF);
                        break;
                    case R_MIPS_32:
                        *b += fi->text_start;
                        break;
                    case R_MIPS_26:
                        *b = (*b & 0xfc000000) | (((*b & 0x03ffffff) + ((u32)fi->text_start >> 2)) & 0x03ffffff);
                        break;
                    case R_MIPS_HI16:
                        b2 = (u32 *)(rel[j + 1].r_offset + fi->text_start);
                        ++j;

                        tmp = (*b << 16) + (int)(*(s16 *)b2) + (u32)fi->text_start;
                        *b = (*b & 0xffff0000) | ((((tmp >> 15) + 1) >> 1) & 0xffff);
                        *b2 = (*b2 & 0xffff0000) | (tmp & 0xffff);
                        break;
                }
            }
        }
    }
}

int LoadModuleImage(void *image, FileInfo_t *fi)
{
    u32 *ptr;
    int i;
    switch (fi->ModuleType) {
        case MODULE_TYPE_COFF:
            load_type_1(image);
            break;
        case MODULE_TYPE_EXEC:
            load_type_3(image);
            break;
        case MODULE_TYPE_IOPRELEXEC:
            load_type_4(image, fi);
            break;
        default:
            return -1;
    }

    setImageInfo(fi, (ModuleInfo_t *)((u8 *)fi->text_start - 0x30));

    return 0;
}

///////////////////////////////////////////////////////////////////////[OK]
int lc_memcpy(void *src, void *dest, int len)
{
    char *_src = (char *)src;
    char *_dst = (char *)dest;
    for (len = len; len > 0; len--)
        *_dst++ = *_src++;
    return 0;
}

///////////////////////////////////////////////////////////////////////[OK]
int lc_zeromem(void *addr, int len)
{
    for (; len > 0; len--)
        *(char *)addr++ = 0;
    return 0;
}

int lc_strlen(char *s)
{
    int len;
    if (s == NULL)
        return 0;
    for (len = 0; *s++; len++)
        ;
    return len;
}

int recursive_set_a2(int *start, int *end, int val)
{
    *start++ = val;
    if (start < end)
        return recursive_set_a2(start, end, val);
    return 0;
}

void *lc_memcpy_overlapping(char *dst, char *src, int len)
{
    if (dst == NULL)
        return 0;

    if (dst >= src)
        while (--len >= 0)
            *(dst + len) = *(src + len);
    else
        while (len-- > 0)
            *dst++ = *src++;

    return dst;
}

//////////////////////////////entrypoint///////////////////////////////
void _start(BOOT_PARAMS *init)
{
    *(volatile int *)0xFFFE0130 = 0x1e988;
    __asm__(
        "addiu $26, $0, 0\n"
        "mtc0  $26, $12\n");
    //"move  $fp, %0\n"
    //"move  $sp, %0\n"
    //: : "r"((init->ramMBSize << 20) - 0x40));
    __asm__(
        "j     loadcore_start\n");
}

extern void *_ftext, *_etext, *_end;
typedef int (*IopEntryFn)(u32, void *, void *, void *);

#define MODNAME "Module_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_loadcore;

void loadcore_start(BOOT_PARAMS *pInitParams)
{
    FileInfo_t fi;
    void (*entry)();
    u32 offset;
    u32 status = 0x401;
    int bm;
    int i;
    void **s0; // pointer in module list to current module?
    BOOT_PARAMS params;
    u32 s1, s2, s3, sp, a2;

    // Write 0x401 into the co-processor status register?
    // This enables interrupts generally, and disables (masks) them all except hardware interrupt 0?

    lc_memcpy(pInitParams, &params, sizeof(BOOT_PARAMS));
    BOOTMODE_END = BOOTMODE_START = bootmodes;

    lc_internals.let_next = (struct irx_export_table *)params.firstModuleAddr;
    lc_internals.let_prev = (struct irx_export_table *)params.firstModuleAddr;
    lc_internals.let_next->caller = 0;
    lc_internals.module_count = 2; // SYSMEM + LOADCORE
    lc_internals.mda_prev = lc_internals.mda_next = NULL;
    lc_internals.module_index = 3; // next available index

    for (i = 0; i < 17; i++) {
        bootmodes[i] = 0;
    }
    bootmodes_size = 0;

    bm = params.bootInfo | 0x00040000;
    RegisterBootMode((iop_bootmode_t *)&bm);

    lc_internals.image_info = (ModuleInfo_t *)((u32)lc_internals.let_prev - 0x30);
    lc_internals.image_info->id = 1; // SYSMEM is the first module
    lc_internals.image_info->next = (u32)&_ftext - 0x30;
    ((ModuleInfo_t *)lc_internals.image_info->next)->id = 2; // LOADCORE is the second module

    // find & fix LOADCORE imports (to SYSMEM)
    LinkImports((u32 *)&_ftext, (u32)&_etext - (u32)&_ftext);

    RegisterLibraryEntries(&_exp_loadcore);

    // reserve LOADCORE memory
    AllocSysMemory(2, (u32)((u32)&_end - (((u32)&_ftext - 0x30) >> 8 << 8)), (void *)((((u32)&_ftext - 0x30) >> 8 << 8) & 0x1FFFFFFF));

    if (params.pos)
        params.pos = (u32)AllocSysMemory(2, params.size, (void *)params.pos);

    sp = (u32)__builtin_alloca(0x10);
    s0 = (void **)((sp - 0xDF0) & 0x1FFFFF00); //=0x001ff100
    recursive_set_a2((int *)s0, (void *)(sp + 0x10), 0x11111111);
    if ((u32)s0 < QueryMemSize())
        AllocSysMemory(2, QueryMemSize() - (u32)s0, s0);

    if (params.udnlString) {
        int v0 = lc_strlen(params.udnlString);
        int *v1 = (int *)__builtin_alloca((v0 + 8 + 8) >> 3 << 3);
        lc_memcpy_overlapping((char *)&v1[6], params.udnlString, v0 + 1);
        params.udnlString = (char *)&v1[6];
        v1[4] = 0x01050000;
        v1[5] = (int)&v1[6];
        RegisterBootMode((iop_bootmode_t *)&v1[4]); // BTUPDATER bootmode 5
    }

    a2 = (params.numConfLines + 1) * 4;
    s0 = __builtin_alloca((a2 + 7) >> 3 << 3) + 0x10;
    lc_memcpy_overlapping((char *)s0, (char *)params.moduleAddrs, a2); //0x30020

    s1 = 0;
    params.moduleAddrs = (u32 **)s0;
    s2 = (u32)__builtin_alloca(params.numConfLines << 3) + 0x10;
    place = (u32 *)s2;
    *place = 0;
    i = -1;
    s3 = 1;

    s0 += 2; // skip first two: SYSMEM, LOADCORE
    for (; *s0; s0 += 1) {
        if ((u32)*s0 & 1) {
            if (((u32)*s0 & 0xF) == s3)
                s1 = (u32)*s0 >> 2;
        } else {
            i += 1;
            i &= 0xF;

            switch (ReadModuleHeader(*s0, &fi)) {
                case MODULE_TYPE_COFF:
                case MODULE_TYPE_EXEC:
                    a2 = (((u32)fi.text_start - 0x30) >> 8 << 8) & 0x1FFFFFFF;
                    if (NULL == AllocSysMemory(2, fi.MemSize + fi.text_start - a2, (void *)a2))
                        goto HALT;
                    break;

                case MODULE_TYPE_2:
                case MODULE_TYPE_IOPRELEXEC:
                    fi.text_start = (u32)((s1 == 0) ?
                                              AllocSysMemory(0, fi.MemSize + 0x30, 0) :
                                              AllocSysMemory(2, fi.MemSize + 0x30, (void *)s1));
                    if (fi.text_start != 0)
                        fi.text_start += 0x30;
                    else
                        goto HALT;
                    break;

                default:
                    goto HALT;
            }

            LoadModuleImage(*s0, &fi);

            if (0 == LinkImports((u32 *)fi.text_start, fi.text_size)) {

                FlushIcache();
                __asm__("move $gp, %0\n"
                        :
                        : "r"(fi.gp));
                // call the entry point
                s1 = ((IopEntryFn)fi.EntryPoint)(0, NULL, s0, NULL);

                if ((s1 & 3) == 0) {
                    LinkModule((ModuleInfo_t *)(fi.text_start - 0x30));
                    if (s1 & ~3)
                        RegisterPostBootCallback((int (*)(iop_init_entry_t *, int))(s1 & ~3), BOOTUPCB_NORMAL, 0);
                } else {
                    UnlinkImports((void *)fi.text_start, fi.text_size);
                    FreeSysMemory((void *)(((u32)fi.text_start - 0x30) >> 8 << 8));
                }
            } else {
                FreeSysMemory((void *)(((u32)fi.text_start - 0x30) >> 8 << 8));
            }

            s1 = 0;
        }
    }

    if (params.pos)
        FreeSysMemory((void *)params.pos);

    for (i = BOOTUPCB_FIRST; i < BOOTUPCB_PRIORITIES; i++) {
        if (i == BOOTUPCB_LAST)
            place = 0;

        for (s0 = (void **)s2; *s0; s0 += 2)
            if (((u32)*s0 & 3) == i) {
                __asm__("move $gp, %0\n"
                        :
                        : "r"(s0[1]));
                ((int (*)(int *, int))((u32)*s0 & ~3))(((u32)*s0 & 3) == BOOTUPCB_LAST ? (int *)&s0[2] : (int *)s0, 1);
            }

        if (i == BOOTUPCB_NORMAL) {
            while ((u32)s2 < (u32)s0) {
                s0 -= 2; // -8 bytes
                if (((u32)*s0 & 3) == BOOTUPCB_LAST)
                    break;
                *s0 = 0;
            }
        }
    }

HALT:
    *(vu8 *)0x80000000 = 2;
    goto HALT;
}
