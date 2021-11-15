#ifndef speicherverwaltung_h
#define speicherverwaltung_h

#ifndef MALLOCSPLIT
    #define MALLOCSPLIT 0
#endif

#include <stdlib.h>

#define MAGIC_INT 0xacdcacdc
#define MEM_POOL_SIZE 4096

int cm_init(void);
void * cm_malloc(size_t);
void cm_free(void*);

typedef struct memblock {
    size_t size;            // Für User nutzbare Länge des Blocks [Bytes]
    struct memblock *next;  // Zeiger auf Anfang des nächsten freien Blocks (oder NULL)
    unsigned short id;      // Fortlaufende und eindeutige Nummer des Blockes
} memblock;

memblock * freemem;
char mempool[MEM_POOL_SIZE];
#endif