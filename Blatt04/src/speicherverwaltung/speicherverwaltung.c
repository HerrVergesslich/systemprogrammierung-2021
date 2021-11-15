#include "speicherverwaltung/speicherverwaltung.h"
#include <stdio.h>
char mempool[MEM_POOL_SIZE];
memblock * freemem;

int cm_init(void){
    static int called = 0;
    if(MEM_POOL_SIZE<4096){
        return -1;
    }else if(called != 0){
        return 0;
    }
    called = 1;
    freemem = mempool;
    freemem->size = (MEM_POOL_SIZE-sizeof(memblock));
    freemem->id = 0;
    freemem->next = NULL;
    return 1;
}

void * cm_malloc(size_t size){
    static int number = 1;
    if(size <= 0)return NULL;
    memblock * run = freemem;
    if(freemem == NULL){
        return NULL;
    }
    while(run != NULL){
        if(size<= run->size){
            number++;
            freemem->size = freemem->size - run->size;
            run->id = number; 
            run->next = (memblock *)MAGIC_INT;
            return run;
        }
        run = run->next;
    }
    return NULL;
}
