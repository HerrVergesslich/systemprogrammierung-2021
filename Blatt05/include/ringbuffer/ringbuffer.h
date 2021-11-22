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

/**
 * @brief Initializes a ring buffer.
 * 
 * @param size Size of requested ring buffer.
 * @param f Callback function to free elements.
 * @return ring_buffer* 
 */
ring_buffer* init_buffer(size_t size, void (*f)(void *p));

/**
 * @brief Reads oldest element from the ring buffer.
 * 
 * @param cb Ring buffer to read from.
 * @return void* Pointer to oldest element.
 */
void* read_buffer(ring_buffer *cb);

/**
 * @brief Writes element to ring buffer.
 * 
 * @param cb Buffer to write to.
 * @param data Data to write.
 */
void write_buffer(ring_buffer *cb, void *data);

/**
 * @brief Frees ring buffer.
 * 
 * @param cb Buffer to free.
 * @return int Number of elements freed.
 */
int free_buffer(ring_buffer *cb);

#endif