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
    // 写入超过缓冲区长度的数据
    char data[] = "Hello, World!";
    // int bytes_written = RingBuffer_write(buffer, data, sizeof(data) - 1);
    // mu_assert(bytes_written == DEFAULT_LEN, "Failed to write data to
    // buffer"); mu_assert(RingBuffer_full(buffer),
    //           "RingBuffer should be full after writing");
    // mu_assert(RingBuffer_available_data(buffer) == DEFAULT_LEN,
    //           "Available data should be DEFAULT_LEN after writing");
    // mu_assert(RingBuffer_available_space(buffer) == 0,
    //           "Available space should be 0 after writing");

    // 再次写入数据，会覆盖之前的数据
    char data2[] = "1234";
    int bytes_written2 = RingBuffer_write(buffer, data2, sizeof(data2) - 1);
    mu_assert(bytes_written2 == DEFAULT_LEN, "Failed to write data to buffer");
    // mu_assert(RingBuffer_full(buffer), "RingBuffer should still be full after
    // overwriting");
    printf("\n\n ---- %d ---- \n\n", RingBuffer_available_data(buffer));
    mu_assert(RingBuffer_available_data(buffer) == DEFAULT_LEN,
              "Available data should still be 5 after overwriting");
    mu_assert(RingBuffer_available_space(buffer) == 0,
              "Available space should still be 0 after overwriting");
    mu_assert(
        bstricmp(RingBuffer_get_all(buffer), blk2bstr(data2, DEFAULT_LEN)) == 0,
        "RingBuffer should be indentical to data2");

    // 读取数据
    char target[10];
    int bytes_read = RingBuffer_read(buffer, target, 3);
    mu_assert(bytes_read == 3, "Failed to read data from buffer");
    mu_assert(memcmp(data + 5, target, bytes_read) == 0,
              "Data read doesn't match data written");

    // 再次写入数据，不会覆盖之前的数据
    char data3[] = "ABCDE";
    int bytes_written3 = RingBuffer_write(buffer, data3, sizeof(data3) - 1);
    mu_assert(bytes_written3 == 2, "Failed to write data to buffer");
    mu_assert(RingBuffer_full(buffer),
              "RingBuffer should still be full after partial writing");
    mu_assert(RingBuffer_available_data(buffer) == 5,
              "Available data should still be 5 after partial writing");
    mu_assert(RingBuffer_available_space(buffer) == 0,
              "Available space should still be 0 after partial writing");

    // 读取所有数据
    bytes_read = RingBuffer_read(buffer, target + 3, 5);
    mu_assert(bytes_read == 5, "Failed to read data from buffer");
    mu_assert(memcmp(data + 5, target + 3, bytes_read) == 0,
              "Data read doesn't match data written");

    // 测试清空缓冲区后状态
    mu_assert(RingBuffer_empty(buffer),
              "RingBuffer should be empty after reading all data");
    mu_assert(!RingBuffer_full(buffer),
              "RingBuffer should not be full after reading all data");
    mu_assert(RingBuffer_available_data(buffer) == 0,
              "Available data should be 0 after reading all data");
    mu_assert(RingBuffer_available_space(buffer) == 5,
              "Available space should be 5 after reading all data");

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