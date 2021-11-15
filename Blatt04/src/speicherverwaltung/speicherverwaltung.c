#include "speicherverwaltung/speicherverwaltung.h"
#include <stdio.h>

char mempool[MEM_POOL_SIZE];
memblock* freemem;

int cm_init(void) {
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

void* cm_malloc(size_t needSize) {

    if(needSize <= 0) return NULL;

    static unsigned int nextId = 1;
    memblock* run = freemem;
    memblock* prev = NULL;

    if(freemem == NULL) return NULL;

    do {
        if(run->size >= needSize) { //Block ist groß genug für benötigten Speicherplatz
            if(MALLOCSPLIT && run->size > needSize + 2*sizeof(memblock) + 32) {
                
                memblock* new = (memblock*) (run + 1) + needSize;
                new->size = run->size - needSize - sizeof(memblock);
                new->id = 0;
                new->next = run->next;
                if(prev != NULL) prev->next = new;
                
                run->size = needSize;
                run->next = (memblock*) MAGIC_INT;
                run->id = nextId ++;

                return run+1;
            } else {
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
    } while(run->next != NULL);

    return NULL;
}

void cm_free(void *ptr){
    memblock * temp = (memblock *) ptr;
    if(temp && temp->next == (memblock *)MAGIC_INT){
         temp->next = freemem;
         temp->id = 0;
         freemem = temp;
    }
}