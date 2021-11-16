#include "speicherverwaltung/speicherverwaltung.h"
#include <stdio.h>

char mempool[MEM_POOL_SIZE];
memblock* freemem;

/**
 * Funktion zur Initialisierung des (simulierten) Heaps.
 */
int cm_init(void) {
    printf("### Use Splitting: %d ###\n", MALLOCSPLIT);

    static int alreadyCalled = 0;

    if(alreadyCalled) return 0;
    if(MEM_POOL_SIZE < 4096) return -1;

    alreadyCalled = 1;

    freemem = (memblock*) mempool;
    freemem->id = 0;
    freemem->size = MEM_POOL_SIZE - sizeof(memblock);
    freemem->next = NULL;

    return 1;
}

/**
 * Funktion zur Reservierung eines Speicherbereichs im (simulierten) Heap.
 */
void* cm_malloc(size_t needSize) {

    if(needSize <= 0) return NULL;

    static unsigned int nextId = 1;
    memblock* run = freemem;
    memblock* prev = NULL;

    if(freemem == NULL) {
        printf("freemem = NULL\n");   
        return NULL;
    }

    while(run != NULL) {

        if(run < mempool || run > mempool + MEM_POOL_SIZE) return NULL;

        if(run->size >= needSize) { //Block ist groß genug für benötigten Speicherplatz
            if(MALLOCSPLIT && run->size > needSize + 2*sizeof(memblock) + 32) {
                
                printf("(SPLIT) Needs Size: %ld\n", needSize);

                memblock* new = (memblock*) (((char*)run) + sizeof(memblock) + needSize);
                new->size = run->size - needSize - sizeof(memblock);
                new->id = 0;
                new->next = run->next;
                if(prev != NULL) prev->next = new;
                else freemem = new;

                run->size = needSize;
                run->next = (memblock*) MAGIC_INT;
                run->id = nextId ++;

                return run+1;
            } else {
                printf("(NO SPLIT) Needs Size: %ld\n", needSize);

                if(prev != NULL) prev->next = run->next;
                if(run == freemem) freemem = freemem->next;

                run->id = nextId ++;
                run->next = (memblock*) MAGIC_INT;
                            
                return run+1;
            }            
        } else {
            prev = run;
            run = run->next;
        }
    }
    printf("No free space found!\n");
    return NULL;
}

/**
 * Funktion zum Befreien eines Speicherbereichs im (simulierten) Heap.
 */
void cm_free(void *ptr){
    if(ptr == NULL) return;
    memblock* temp = (memblock*)ptr - 1;

    if(temp < mempool || temp > mempool + MEM_POOL_SIZE) {
        printf("[FREE]: Pointer ist ausserhalb des Heaps! (ptr: %p mempool: %p)\n", temp, mempool);
        return;
    }

    if(temp->next == MAGIC_INT) {
        printf("Speicher wird befreit: (ptr: %p mempool: %p)\n", temp, mempool);
        if(freemem == NULL) {
            freemem = temp;
            temp->next = NULL;
        } else {
            temp->next = freemem;
            freemem = temp;
        }
    } else {
        printf("Ist kein belegter Speicher aus dem Heap! (ptr: %p mempool: %p)\n", temp, mempool);
    }
}