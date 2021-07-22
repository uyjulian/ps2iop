//[module]	HEAPLIB
//[processor]	IOP
//[type]	ELF-IRX
//[name]	Heap_lib
//[version]	0x101
//[memory map]	-
//[handlers]	-
//[entry point]	heaplib_start, heaplib_stub
//[made by]	[RO]man (roman_ps2dev@hotmail.com) 26 January 2003

#include "sysmem.h"
#include "loadcore.h"
#include "heaplib.h"

typedef struct ll_
{
    struct ll_ *next;
    struct ll_ *prev;
} ll;

typedef struct Chunk_
{
    u32 _mem;
    u32 freesize;
    u32 usedsize;
    u32 mem_16;
    u32 unk4;
    u32 unk5;
} Chunk;

typedef struct Heap_
{
    u32 plus_one;
    u32 size2free;
    ll l;
    Chunk chunk10;
} Heap;

extern int HeapChunk12(Heap *a1);
extern ll *HeapChunk13(Heap *a1, unsigned int a2);
extern int HeapChunk14(Heap *a1, int a2);

int _start(int argc, char *argv[]);

///////////////////////////////////////////////////////////////////////
void ll_reset(ll *l)
{
    l->prev = l->next = l;
}

///////////////////////////////////////////////////////////////////////
int ll_one(ll *l)
{
    return (l == l->next);
    //	return (l ^ l->next) < 1;	//l==l->next
}

///////////////////////////////////////////////////////////////////////
void ll_remove(ll *l)
{
    l->next->prev = l->prev;
    l->prev->next = l->next;
}

///////////////////////////////////////////////////////////////////////
/*int ll_one_two(ll *l){
	return (l->prev ^ l->next) < 1;	//l->prev==l->next
}*/

///////////////////////////////////////////////////////////////////////
void ll_add(ll *l, ll *n)
{
    n->next = l;
    n->prev = l->prev;
    l->prev = n;
    n->prev->next = n;
}

void HeapPrepare(void *mem, int size)
{
    Chunk *_chunk = (Chunk *)mem;

    if (mem == NULL || size < 41)
        return;

    _chunk->_mem = (long)mem - 1;
    _chunk->freesize = size;
    _chunk->usedsize = 0;
    _chunk->mem_16 = (u32)mem + 16;
    _chunk->unk5 = ((size - 16) >> 3) - 1;
    _chunk->unk4 = (long)_chunk + 8 + ((size - 16) & ~7);
    ((ll *)_chunk->unk4)->next = (void *)_chunk->mem_16;
    ((ll *)_chunk->unk4)->prev = 0;
}

int HeapChunkSize(void *chunk)
{
    Chunk *_chunk = (Chunk *)chunk;
    return 8 * (((u32)(_chunk->freesize - 16) >> 3) - _chunk->usedsize - 1);
}

///////////////////////////////////////////////////////////////////////
void *CreateHeap(int chunkSize, int memoryType)
{
    Heap *_heap;

    chunkSize = (chunkSize + 3) & ~3;
    _heap = AllocSysMemory(memoryType & 2 ? ALLOC_LAST : ALLOC_FIRST, chunkSize, NULL);
    if (_heap == NULL)
        return NULL;

    _heap->plus_one = (long)_heap + 1;
    if (memoryType & 1)
        _heap->size2free = chunkSize;
    else
        _heap->size2free = 0;
    _heap->size2free |= ((memoryType >> 1) & 1);
    ll_reset(&_heap->l);

    HeapPrepare(&_heap->chunk10, chunkSize - 4 * sizeof(int));
    return (void *)_heap;
}

///////////////////////////////////////////////////////////////////////
void DeleteHeap(void *heap)
{
    Heap *_heap = (Heap *)heap;

    Heap *v1;
    ll *v3;
    ll *v4;

    v1 = (Heap *)heap;
    if ((Heap *)_heap->plus_one == (Heap *)((char *)&_heap->plus_one + 1)) {
        v3 = _heap->l.next;
        v1->plus_one = 0;
        if (v3 != &v1->l) {
            do {
                v4 = v3->next;
                v3[1].next = 0;
                FreeSysMemory(v3);
                v3 = v4;
            } while (v4 != &v1->l);
        }
        _heap->chunk10._mem = 0;
        FreeSysMemory(v1);
    }
}

///////////////////////////////////////////////////////////////////////
void *AllocHeapMemory(void *heap, size_t size)
{
    Heap *_heap = (Heap *)heap;
    void *result;
    ll *v5;
    ll *v6;
    Heap *i;
    int v8;
    int v9;
    ll *v10;
    int v11;
    Chunk *v12;

    if ((Heap *)_heap->plus_one != (Heap *)((char *)&_heap->plus_one + 1))
        return 0;
    v5 = _heap->l.next;
    v6 = &_heap->l;
    for (i = (Heap *)&v5[1];; i = (Heap *)&v5[1]) {
        result = HeapChunk13(i, size);
        if (result)
            break;
        if (v5 == v6) {
            v8 = _heap->size2free;
            if (v8 < 4)
                return result;
            v9 = 2 * (v8 >> 1);
            if (v9 - 40 < size)
                v9 = size + 40;
            v10 = (ll *)AllocSysMemory(_heap->size2free & 1, v9, 0);
            result = 0;
            if (!v10)
                return result;
            v11 = QueryBlockSize(v10);
            ll_add(_heap->l.next, v10);
            v12 = (Chunk *)&v10[1];
            HeapPrepare(v12, v11 - 8);
            return HeapChunk13((Heap *)v12, size);
        }
        v5 = v5->next;
    }
    return result;
}

int FreeHeapMemory(void *heap, void *mem)
{
    ll *v3;
    int result;
    ll *v5;
    Heap *i;
    int v7;

    Heap *_heap = (Heap *)heap;
    if (!_heap)
        return -4;
    v3 = &_heap->l;
    if ((Heap *)_heap->plus_one != (Heap *)((char *)&_heap->plus_one + 1))
        return -4;
    v5 = _heap->l.next;
    for (i = (Heap *)&v5[1]; HeapChunk14(i, (int)mem); i = (Heap *)&v5[1]) {
        result = -1;
        if (v5 == v3)
            return result;
        v5 = v5->next;
    }
    result = 0;
    if (v5 == v3)
        return result;
    v7 = !HeapChunk12(i);
    result = 0;
    if (v7)
        return result;
    ll_remove(v5);
    v5[1].next = 0;
    FreeSysMemory(v5);
    return 0;
}

int HeapTotalFreeSize(void *heap)
{
    Heap *_heap = (Heap *)heap;

    int v1;
    ll *v2;
    ll *i;

    v1 = 0;
    if (!_heap)
        return -4;
    v2 = &_heap->l;
    if ((Heap *)_heap->plus_one != (Heap *)((char *)&_heap->plus_one + 1))
        return -4;
    for (i = _heap->l.next;; i = i->next) {
        v1 += HeapChunkSize((Chunk *)&i[1]);
        if (i == v2)
            break;
    }
    return v1;
}

int HeapChunk12(Heap *a1)
{
    int result;

    if (a1 && (Heap *)a1->plus_one == (Heap *)((char *)&a1[-1].chunk10.unk5 + 3))
        result = a1->l.next == 0;
    else
        result = 0;
    return result;
}

ll *HeapChunk13(Heap *a1, unsigned int a2)
{
    ll *result;
    unsigned int v4;
    ll *v5;
    int v6;
    ll *v7;
    ll *i;
    int v9;
    ll *v10;

    if (!a1 || (Heap *)a1->plus_one != (Heap *)((char *)&a1[-1].chunk10.unk5 + 3))
        return 0;
    v4 = a2 + 7;
    if (a2 < 8)
        v4 = (unsigned int)0xC + 3;
    v5 = a1->l.prev;
    v6 = (v4 >> 3) + 1;
    v7 = a1->l.prev;
    for (i = v7->next;; i = i->next) {
        v9 = (int)i->prev;
        if (v9 >= v6)
            break;
        v7 = i;
        if (i == v5)
            return 0;
    }
    v10 = (ll *)(v9 - v6);
    if (v9 == v6) {
        v7->next = i->next;
    } else {
        i->prev = v10;
        i += (int)v10;
        i->prev = (ll *)v6;
    }
    a1->l.prev = v7;
    i->next = (ll *)a1;
    result = i + 1;
    a1->l.next = (ll *)((char *)a1->l.next + (unsigned int)i->prev);
    return result;
}

int HeapChunk14(Heap *a1, int a2)
{
    ll *v2;
    ll *v4;
    ll *v5;
    int v6;
    ll *v7;
    ll *v8;
    ll *v9;
    int v10;
    ll *v11;
    ll *v12;

    v2 = (ll *)(a2 - 8);
    if (!a1 || (Heap *)a1->plus_one != (Heap *)((char *)&a1[-1].chunk10.unk5 + 3))
        return -4;
    if (!a2 || *(Heap **)(a2 - 8) != a1 || (int)v2->prev <= 0)
        return -1;
    if (v2 < (ll *)&a1->chunk10 || v2 >= (ll *)((char *)a1 + a1->size2free))
        return -2;
    v4 = a1->l.prev;
    if (v4 >= v2 || v2 >= v4->next) {
        while (v2 != v4) {
            v5 = v4->next;
            if (v4 < v4->next)
                goto LABEL_18;
            if (v2 < v4->next)
                goto LABEL_20;
            if (v4 >= v2) {
            LABEL_18:
                v4 = v4->next;
                if (v5 >= v2 || v2 >= v5->next)
                    continue;
            }
            v6 = v4 < v2;
            if (v2 >= v4->next)
                goto LABEL_21;
            goto LABEL_20;
        }
        return -3;
    }
LABEL_20:
    v6 = v4 < v2;
    if (v4->next < &v2[(int)v2->prev])
        return -3;
LABEL_21:
    if (v6 && v2 < &v4[(int)v4->prev])
        return -3;
    a1->l.next = (ll *)((char *)a1->l.next - (unsigned int)v2->prev);
    v7 = v2->prev;
    v8 = &v2[(u32)v7];
    if (v8 != v4->next || (v9 = v8->prev, v10 = (int)v9 <= 0, v11 = (ll *)((char *)v9 + (u32)v7), v10)) {
        v2->next = v4->next;
    } else {
        v2->prev = v11;
        v2->next = v4->next->next;
    }
    v12 = v4->prev;
    if (v2 == &v4[(u32)v12]) {
        v4->prev = (ll *)((char *)v12 + (unsigned int)v2->prev);
        v4->next = v2->next;
    } else {
        v4->next = v2;
    }
    a1->l.prev = v4;
    return 0;
}

#define MODNAME "Heap_lib"
IRX_ID(MODNAME, 1, 1);

extern struct irx_export_table _exp_heaplib;

//////////////////////////////entrypoint///////////////////////////////
int _start(int argc, char *argv[])
{
    return RegisterLibraryEntries(&_exp_heaplib);
}
