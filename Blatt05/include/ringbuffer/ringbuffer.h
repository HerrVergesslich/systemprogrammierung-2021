#ifndef RINGBUFFER_H
#define RINGBUFFER_H

struct ring_buffer{
    size_t size,count,head;
    void **elems;
    void (*free_callback)(void *p);
};

void write();
void init_buffer();
