#include "speicherverwaltung/speicherverwaltung.h"
#include <stdio.h>
char mempool[MEM_POOL_SIZE];
memblock * freemem;

int cm_init(void){
    /*printf("Size of memblock pointer: %d\n", sizeof(memblock*));
    printf("Size of memblock: %d\n", sizeof(memblock));*/
    static int called = 0;
    if(MEM_POOL_SIZE<4096){
        return -1;
    }else if(called != 0){
        return 0;
    }
    called = 1;
    freemem = (memblock *)mempool;
    freemem->size = (MEM_POOL_SIZE-sizeof(memblock));
    freemem->id = 0;
    freemem->next = NULL;
    return 1;
}

void * cm_malloc(size_t needSize){
    static int number = 1;
    
    if(needSize <= 0) return NULL;
    if(freemem == NULL) return NULL;

    memblock* run = freemem;
    
    while(run != NULL){

        if(run->size >= needSize){

            run->id = number++; 
            run->next = (memblock*) MAGIC_INT;

            if(freemem->size - run->size <= 0) freemem = NULL;

            return run+1;
        }

        run = run->next;
    }
    return NULL;
}

 void cm_free(void *ptr){
    memblock * temp = (memblock *) ptr;
    if(temp && temp->next == (memblock *)MAGIC_INT){
         temp->next = freemem;
         temp->id = 1;
         freemem = temp;
    }
}