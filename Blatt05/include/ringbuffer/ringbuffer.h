#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdlib.h>
#include <stdio.h>

typedef struct ring_buffer{
    size_t size;
    size_t count;
    size_t head;
    void **elems;
    void (*free_callback)(void *p);
} ring_buffer;

ring_buffer* init_buffer(size_t size, void (*f)(void *p));
void* read_buffer(ring_buffer *cb);
void write_buffer(ring_buffer *cb, void *data);
int free_buffer(ring_buffer *cb);


#endif