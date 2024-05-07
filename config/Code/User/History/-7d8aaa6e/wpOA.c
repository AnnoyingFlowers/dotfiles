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
    char data[] = "Hello";
    int bytes_written = RingBuffer_write(buffer, data, sizeof(data) - 1);
    assert(bytes_written == 5 && "Failed to write data to buffer");

    char target[10];
    int bytes_read = RingBuffer_read(buffer, target, bytes_written);
    assert(bytes_read == bytes_written && "Failed to read data from buffer");
    assert(memcmp(data, target, bytes_written) == 0 &&
           "Data read doesn't match data written");

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