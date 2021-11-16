#ifndef speicherverwaltung_h
#define speicherverwaltung_h

#ifndef MALLOCSPLIT
const int MALLOCSPLIT = 0;
#endif

#include <stdlib.h>

#define MAGIC_INT 0xacdcacdc
#define MEM_POOL_SIZE 8192

/**
 * Funktion zur Initialisierung des (simulierten) Heaps.
 */
int cm_init(void);

/**
 * Funktion zur Reservierung eines Speicherbereichs im (simulierten) Heap.
 */
void * cm_malloc(size_t);

/**
 * Funktion zum Befreien eines Speicherbereichs im (simulierten) Heap.
 */
void cm_free(void*);

typedef struct memblock {
    size_t size;
    struct memblock *next;
    unsigned short id;
} memblock;

memblock * freemem;
char mempool[MEM_POOL_SIZE];
#endif