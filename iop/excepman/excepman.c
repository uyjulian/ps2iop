/*
 * The IOP exception manager module.
 */


#include <tamtypes.h>

#include "excepman.h"
#include "loadcore.h"

//bad exception code
#define ERROR_BAD_EXCODE -50

//no exception handler for that code
#define ERROR_EXCODE_NOTFOUND -51

//already used
#define ERROR_USED_EXCODE -52

void **extable;
exception_handler_t handlers[16];
void *defhandler;

extern void iopException();

extern void defaultEH();

void defaultEHfunc()
{
#if 0
	__printf("panic: excepman: %s\n", __FUNCTION__);
	__printf("EPC=0x%x, cause: %x\n", *(u32*)0x404, *(u32*)0x40C);
	__printf("EXECUTION HALTED\n");
#endif
    for (;;)
        ;
}

///////////////////////////////////////////////////////////////////////
void registerEH()
{
    int i;

    // Set up the chain of exception handlers, making sure that each used one is terminated by the
    // default exception handler.
    for (i = 0; i < 16; i++) {
        if (handlers[i]) {
            exception_handler_t eh = handlers[i];
            while (eh->next) {
                exception_handler_t p_handler = (exception_handler_t)(eh->info & ~3);
                exception_handler_t p_next_handler = (exception_handler_t)(((exception_handler_t)(eh->next))->info & ~3);
                p_handler->next = (void *)p_next_handler + 8;
                eh = eh->next;
            }
            {
                exception_handler_t p_handler = (exception_handler_t)(eh->info & ~3);
                p_handler->next = defhandler;
            }
        }
    }

    for (i = 0; i < 16; i++) {
        if (handlers[i]) {
            extable[i] = (void *)((handlers[i]->info & ~3) + 8);
        } else {
            extable[i] = defhandler;
        }
    }
}

//////////////////////////////entrypoint///////////////////////////////[00]
void Kputc(u8 c)
{
    *((vu8 *)0x1F80380C) = c;
}

void Kprintnum(unsigned int n)
{
    int i = 0;
    while (i < 8) {
        u32 a = n >> 28;
        if (a < 10)
            Kputc('0' + a);
        else
            Kputc('a' + (a - 10));
        n <<= 4;
        ++i;
    }
}

#define MODNAME "Exception_Manager"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_excepman;

int _start()
{
    int *src, *dst;
    int i;

    for (i = 0; i < 16; i++) {
        handlers[i] = NULL;
    }
    defhandler = NULL;
    extable = (void *)0x440;

    // Install the exception handler to address 0
    for (src = (int *)iopException, dst = 0; (u32)dst < 0x100; src++, dst++) {
        *dst = *src;
    }

    RegisterDefaultExceptionHandler((exception_handler_t)&defaultEH);
    RegisterLibraryEntries(&_exp_excepman);

    return 0;
}

///////////////////////////////////////////////////////////////////////[02]
int excepman_deinit()
{
    return 0;
}

///////////////////////////////////////////////////////////////////////[01]
int excepman_reinit()
{
    excepman_deinit();
    return _start();
}

///////////////////////////////////////////////////////////////////////[04]
int RegisterExceptionHandler(int code, exception_handler_t handler)
{
    return RegisterPriorityExceptionHandler(code, 2, handler);
}

// This is a pool of containers. They form a linked list. The info member of each points
// to a registered handler.
exception_handler_struct_t _list[32];
exception_handler_t list = NULL;


void link(exception_handler_t e)
{
    e->next = list;
    list = e;
}

exception_handler_t unlink()
{
    exception_handler_t e;
    if (list == NULL) {
        int i;

        list = _list;
        for (i = 0; i < 31; i++) {
            list[i].next = &list[i + 1];
        }
        list[i].next = 0;
    }
    e = list;
    list = e->next;
    return e;
}

///////////////////////////////////////////////////////////////////////[05]
int RegisterPriorityExceptionHandler(int code, int priority, exception_handler_t handler)
{
    exception_handler_t n;
    exception_handler_t p;
    exception_handler_t p_prev;

    if (code >= 16) {
        return ERROR_BAD_EXCODE;
    }
    if (handler->next) {
        return ERROR_USED_EXCODE;
    }

    n = unlink();

    priority &= 3;
    n->info = ((u32)handler & ~3) | priority;
    n->next = NULL;

    p = handlers[code];
    p_prev = NULL;
    // walk along the chain starting at the handlers[code] root to find our place in the queue
    while (p && ((p->info & 3) < priority)) {
        p_prev = p;
        p = p->next;
    }
    n->next = p;
    if (p_prev == NULL) {
        handlers[code] = n;
    } else {
        p_prev->next = n;
    }

    registerEH();
    return 0;
}

///////////////////////////////////////////////////////////////////////[06]
int RegisterDefaultExceptionHandler(exception_handler_t handler)
{
    if (handler->next) {
        return ERROR_USED_EXCODE;
    }

    handler->next = defhandler;
    defhandler = &handler->funccode;

    registerEH();
    return 0;
}

///////////////////////////////////////////////////////////////////////[07]
int ReleaseExceptionHandler(int code, exception_handler_t handler)
{
    exception_handler_t p;
    exception_handler_t p_prev;

    if (code >= 16)
        return ERROR_BAD_EXCODE;

    p_prev = NULL;
    for (p = handlers[code]; p != NULL; p_prev = p, p = p->next) {
        if ((exception_handler_t)(p->info & ~3) == handler) {
            // found it
            // Mark the handler as no longer used
            ((exception_handler_t)(p->info & ~3))->next = NULL;

            if (p == handlers[code]) {
                // special case, no more list
                handlers[code] = NULL;
            } else {
                // Remove container p from the list
                p_prev->next = p->next;
            }

            link(p); // Add the container back to the pool
            registerEH();
            return 0;
        }
    }
    return ERROR_EXCODE_NOTFOUND;
}

///////////////////////////////////////////////////////////////////////[08]
int ReleaseDefaultExceptionHandler(exception_handler_t handler)
{
    exception_handler_t p;

    for (p = defhandler; p->next; p = p->next - 8) {
        if (p->next == handler->funccode) {
            p->next = handler->next;
            handler->next = 0;
            registerEH();
            return 0;
        }
    }
    return ERROR_EXCODE_NOTFOUND;
}

///////////////////////////////////////////////////////////////////////[03]
void *GetExHandlersTable()
{
    return extable;
}

// 256 bytes of this code are copied to memory address 0 in order to install the exception handling code.
// Take careful note of the alignment of the code at 0x40 and 0x80 if you change it at all.
void iopException()
{
    __asm__(
        ".set noat\n"
        "nop\nnop\nnop\nnop\n"
        "nop\nnop\nnop\nnop\n"
        "nop\nnop\nnop\nnop\n"
        "nop\nnop\nnop\nnop\n"

        /* 0x0040 */
        /* This the breakpoint exception vector location. */

        "sw    $26, 0x0420($0)\n"
        "mfc0  $27, $14\n"
        "mfc0  $26, $13\n"
        "sw    $27, 0x0424($0)\n"
        "sw    $26, 0x0428($0)\n"
        "mfc0  $27, $12\n"
        "mfc0  $26, $7\n"
        "sw    $27, 0x042C($0)\n"
        "sw    $26, 0x0430($0)\n"
        "lw    $27, 0x047C($0)\n"
        "mtc0  $0,  $7\n"
        "jr    $27\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"

        /* 0x0080 */
        /* This is the general exception vector location. */
        "sw    $1,  0x0400($0)\n" /* $1  saved at 0x400                */
        "sw    $26, 0x0410($0)\n" /* $26 saved at 0x410                */
        "mfc0  $1,  $14\n"
        "mfc0  $26, $12\n"
        "sw    $1 , 0x0404($0)\n" /* EPC    -> 0x404                   */
        "sw    $26, 0x0408($0)\n" /* STATUS -> 0x408                   */
        "mfc0  $1,  $13\n"
        "sw    $1,  0x040C($0)\n" /*  CAUSE -> 0x40C                   */
        "andi  $1,  0x3C\n"       /*  Isolate EXECODE                  */
        "lw    $1,  0x0440($1)\n"
        "jr    $1\n" /* jump via EXECODE table at 0x440   */
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"
        "nop\n"

        "nop\nnop\nnop\nnop\n"
        "nop\nnop\nnop\nnop\n"
        "nop\nnop\nnop\nnop\n"
        "nop\nnop\nnop\nnop\n"
        ".set at\n");
}
