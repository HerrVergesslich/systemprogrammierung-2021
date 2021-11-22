#include <gtest/gtest.h>
#include "ringbuffer/ringbuffer.h"

void testFreeCallback(void *p)
{
    printf("%p", p);
}

TEST(RingBuffer, initBuffer)
{
    ring_buffer* buffer = init_buffer(10, testFreeCallback);
    ASSERT_TRUE(buffer != NULL);
    ASSERT_EQ(buffer->size, 10);
    ASSERT_EQ(buffer->free_callback, testFreeCallback);
    ASSERT_EQ(buffer->head, 0);
    ASSERT_EQ(buffer->count, 0);
    free_buffer(buffer);
}

TEST(RingBuffer, addElement)
{
    ring_buffer* buffer = init_buffer(10, testFreeCallback);
    int* element = (int*) malloc(sizeof(int));
    write_buffer(buffer, element);
    ASSERT_EQ(buffer->count, 1);
    ASSERT_EQ(buffer->head, 0);
    ASSERT_EQ(element, buffer->elems[0]);
    free_buffer(buffer);
}

TEST(RingBuffer, removeElement)
{
    ring_buffer* buffer = init_buffer(10, testFreeCallback);
    int* element = (int*) malloc(sizeof(int));
    buffer->elems[0] = element;
    buffer->count = 1;
    buffer->head = 1;
    read_buffer(buffer);
    ASSERT_EQ(buffer->count, 0);
    ASSERT_EQ(buffer->head, 0);
}

TEST(RingBuffer, addAndRemoveElement)
{
    ring_buffer* buffer = init_buffer(10, testFreeCallback);
    int* element = (int*) malloc(sizeof(int));
    write_buffer(buffer, element);
    read_buffer(buffer);
    ASSERT_EQ(buffer->count, 0);
    ASSERT_EQ(buffer->head, 0);
}

TEST(RingBuffer, addTwoElements)
{
    ring_buffer* buffer = init_buffer(10, testFreeCallback);
    int* element = (int*) malloc(sizeof(int));
    write_buffer(buffer, element);
    int* element2 = (int*) malloc(sizeof(int));
    write_buffer(buffer, element2);
    ASSERT_EQ(buffer->count, 2);
    ASSERT_EQ(buffer->head, 0);
    ASSERT_EQ(element, buffer->elems[0]);
    ASSERT_EQ(element2, buffer->elems[1]);
}

TEST(RingBuffer, removeTwoElements)
{
    ring_buffer* buffer = init_buffer(10, testFreeCallback);
    int* element = (int*) malloc(sizeof(int));
    write_buffer(buffer, element);
    int* element2 = (int*) malloc(sizeof(int));
    write_buffer(buffer, element2);
    read_buffer(buffer);
    read_buffer(buffer);
    ASSERT_EQ(buffer->count, 0);
    ASSERT_EQ(buffer->head, 0);
}

TEST(RingBuffer, addTenElements)
{
    ring_buffer* buffer = init_buffer(10, testFreeCallback);
    for(int i = 0; i < 10; i++)
    {
        int* element = (int*) malloc(sizeof(int));
        write_buffer(buffer, element);
    }
    ASSERT_EQ(buffer->count, 10);
    ASSERT_EQ(buffer->head, 0);
}

TEST(RingBuffer, removeTenElements) {
    ring_buffer* buffer = init_buffer(10, testFreeCallback);
    for(int i = 0; i < 10; i++)
    {
        int* element = (int*) malloc(sizeof(int));
        buffer->elems[i] = element;
    }
    buffer->count = 10;
    buffer->head = 9;
    for(int i = 0; i < 10; i++)
    {
        read_buffer(buffer);
    }
    ASSERT_EQ(buffer->count, 0);
    ASSERT_EQ(buffer->head, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
