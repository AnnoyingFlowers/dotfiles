#include <assert.h>
#include <stdio.h>

#include "../src/lcthw/ringbuffer.h"
#include "minunit.h"

static RingBuffer *buffer = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3
#define DEFAULT_LEN 5

char *test_create() {
    buffer = RingBuffer_create(DEFAULT_LEN);
    mu_assert(buffer != NULL, "Failed to create ringbuffer.");
    mu_assert(RingBuffer_empty(buffer), "RingBuffer should be empty initially");
    mu_assert(!RingBuffer_full(buffer),
              "RingBuffer should not be full initially");
    mu_assert(RingBuffer_available_data(buffer) == 0,
              "Available data should be 0 initially");
    mu_assert(RingBuffer_available_space(buffer) == DEFAULT_LEN,
              "Available space should be DEFAULT_LEN initially");

    return NULL;
}

char *test_destroy() {
    mu_assert(buffer != NULL, "Failed to access ringbuffer before destroy.");
    RingBuffer_destroy(buffer);

    return NULL;
}

char *test_read_write() {
    // 情况 1: 缓冲区为空
    buffer->start = 0;
    buffer->end = 0;

    assert(RingBuffer_empty(buffer) && "RingBuffer should be empty");
    assert(!RingBuffer_full(buffer) && "RingBuffer should not be full");

    // 情况 2: 缓冲区已满
    buffer->start = 0;
    buffer->end = 5;

    assert(!RingBuffer_empty(buffer) && "RingBuffer should not be empty");
    assert(RingBuffer_full(buffer) && "RingBuffer should be full");

    // 情况 3: 缓冲区部分填充
    buffer->start = 1;
    buffer->end = 4;

    assert(!RingBuffer_empty(buffer) && "RingBuffer should not be empty");
    assert(!RingBuffer_full(buffer) && "RingBuffer should not be full");

    // 情况 4: 缓冲区 end 在缓冲区末尾右侧，start 在缓冲区范围内
    buffer->start = 2;
    buffer->end = 5;

    assert(!RingBuffer_empty(buffer) && "RingBuffer should not be empty");
    assert(RingBuffer_full(buffer) && "RingBuffer should be full");

    // 情况 5: 缓冲区 end 在缓冲区范围内，start 在缓冲区末尾右侧
    buffer->start = 5;
    buffer->end = 2;

    assert(RingBuffer_empty(buffer) && "RingBuffer should be empty");
    assert(!RingBuffer_full(buffer) && "RingBuffer should not be full");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);