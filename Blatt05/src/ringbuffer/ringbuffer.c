#include "ringbuffer.h"

ring_buffer* init_buffer(const size_t size, void (*f)(void *p)) {
    ring_buffer *buffer = malloc(sizeof(ring_buffer));
    buffer->size = size;
    buffer->count = 0;
    buffer->head = 0;
    buffer->elems = malloc(sizeof(void *) * size);
    buffer->free_callback = f;
    return buffer;
}

void *read_buffer(ring_buffer *buffer)
{
    if (buffer->count == 0)
        return NULL;
    void *elem = buffer->elems[buffer->head];
    buffer->head = (buffer->head + 1) % buffer->size;
    buffer->count--;
    return elem;
}

void write_buffer(ring_buffer *cb, void *data)
{
    if (cb->count == cb->size)
    {
        cb->free_callback(read_buffer(cb));
    }
    cb->elems[(cb->head + cb->count) % cb->size] = data;
    cb->count++;
}

int free_buffer(ring_buffer *cb)
{
    while (cb->count > 0)
    {
        cb->free_callback(read_buffer(cb));
    }
    free(cb->elems);
    free(cb);
    return 0;
}

