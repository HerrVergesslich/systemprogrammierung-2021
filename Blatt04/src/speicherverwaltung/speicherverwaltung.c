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
    freemem = (memblock *)mempool;
    freemem->size = (MEM_POOL_SIZE-sizeof(memblock));
    freemem->id = 0;
    freemem->next = NULL;
    return 1;
}

void * cm_malloc(size_t size){
    static int number = 1;
    if(size <= 0) return NULL;
    memblock * run = freemem;
    if(freemem == NULL){
        return NULL;
    }
    while(run != NULL){
        if(size <= run->size){
            int temp = freemem->size - run->size;
            freemem->size = temp;
            run->id = number++; 
            run->size = size;
            run->next = (memblock *)MAGIC_INT;
            printf("%d", temp);
            if(temp <= 0)freemem = NULL;
            return run + sizeof(memblock);
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

int main() {

    char test = 'a';

    cm_init();
    cm_malloc(sizeof(test));

    return 0;
}