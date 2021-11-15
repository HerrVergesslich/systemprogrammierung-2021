#ifndef speicherverwaltung_h
#define speicherverwaltung_h
#include <stdlib.h>

#define MAGIC_INT 0xacdcacdc
#define MEM_POOL_SIZE 4096

int cm_init(void);
void * cm_malloc(size_t size);
void cm_free(void *ptr);

typedef struct memblock{
    size_t size;
    struct memblock * next;
    unsigned short id;
}memblock;

memblock * freemem;
char mempool[MEM_POOL_SIZE];
#endif