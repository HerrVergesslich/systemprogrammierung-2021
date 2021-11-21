#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdlib.h>
#include <stdio.h>

struct ring_buffer{
    size_t size,count,head;
    void **elems;
    void (*free_callback)(void *p);
};

void write();
void init_buffer();

#endif