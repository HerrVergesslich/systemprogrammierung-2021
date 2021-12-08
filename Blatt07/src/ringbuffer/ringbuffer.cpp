#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer07/CustomAllocator.h"
#include "ringbuffer07/RingBuffer.h"

template <typename T, size_t size, typename alloc_t = std::allocator<T>>

RingBuffer::RingBuffer(){
    
}

class RingBuffer {
public: 
    RingBuffer(){

    }

    ~RingBuffer(){

    }

    T* readBuffer(){
        return T*;
    }

    void writeBuffer(T *data){

    }

    void const displayStatus() {

    }
};