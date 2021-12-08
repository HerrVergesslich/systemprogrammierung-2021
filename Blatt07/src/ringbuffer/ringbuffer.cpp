#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer07/CustomAllocator.h"
#include "ringbuffer07/RingBuffer.h"

template <typename T, size_t size, typename alloc_t = std::allocator<T>>
RingBuffer::RingBuffer(){
    size = 0;
    elems = m_allocator::allocate(size);
}

RingBuffer::~RingBuffer(){
    while( size > 0){
        m_allocator::deallocate(RingBuffer::readBuffer());
    }
}


T* RingBuffer::readBuffer(){
    if( count <= 0) return NULL;
    T* temp =  head;
     head =  head + 1 %  size;
     count --;

    return temp;
}

void RingBuffer::writeBuffer(T *data){
    if(data == NULL){
        return;
    }
    if( count ==  size){
        free_callback(RingBuffer::readBuffer());
    }
    elems[( head +  count) %  size] = data;
     count ++;
}

void const RingBuffer::displayStatus() {
    //number of elems rel to size shown on the display
}