#include "../src/lcthw/ringbuffer.h"
#include "minunit.h"

static RingBuffer *buffer = NULL;
char data[100] = {'\0'};
#define DEFAULT_LEN 20

char *test_create() {
    buffer = RingBuffer_create(DEFAULT_LEN);
    mu_assert(buffer != NULL, "Failed to make ringbuffer.");

    return NULL;
}

char *test_destroy() {
    RingBuffer_destroy(buffer);

    return NULL;
}

char *test_read_write() {
    // 测试初始状态
    mu_assert(RingBuffer_empty(buffer), "RingBuffer should be empty initially");
    mu_assert(!RingBuffer_full(buffer),
              "RingBuffer should not be full initially");
    mu_assert(RingBuffer_available_data(buffer) == 0,
              "Available data should be 0 initially");
    mu_assert(RingBuffer_available_space(buffer) == DEFAULT_LEN,
              "Available space should be DEFAULT_LEN initially");

    // 写入超过缓冲区长度的数据
    char data[] = "Hello, World!";
    // int bytes_written = RingBuffer_write(buffer, data, sizeof(data));
    // mu_assert(bytes_written == 5, "Failed to write data to buffer");
    // mu_assert(RingBuffer_full(buffer),
    //            "RingBuffer should be full after writing");
    // mu_assert(RingBuffer_available_data(buffer) == 5,
    //            "Available data should be 5 after writing");
    // mu_assert(RingBuffer_available_space(buffer) == 0,
    //            "Available space should be 0 after writing");

    // 再次写入数据，会覆盖之前的数据
    char data2[] = "12345";
    int bytes_written2 = RingBuffer_write(buffer, data2, sizeof(data2));
    mu_assert(bytes_written2 == 5, "Failed to write data to buffer");
    mu_assert(RingBuffer_full(buffer),
              "RingBuffer should still be full after overwriting");
    mu_assert(RingBuffer_available_data(buffer) == 5,
              "Available data should still be 5 after overwriting");
    mu_assert(RingBuffer_available_space(buffer) == 0,
              "Available space should still be 0 after overwriting");

    // 读取数据
    char target[20];
    int bytes_read = RingBuffer_read(buffer, target, 3);
    mu_assert(bytes_read == 3, "Failed to read data from buffer");
    mu_assert(memcmp(data2, target, bytes_read) == 0,
              "Data read doesn't match data written");

    // 再次写入数据，不会覆盖之前的数据
    char data3[] = "ABCDE";
    int bytes_written3 = RingBuffer_write(buffer, data3, sizeof(data3));
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

    /*
    mu_assert(RingBuffer_empty(buffer), "Should be empty.");
    mu_assert(!RingBuffer_full(buffer), "Should NOT be full.");
    debug("data is: %d, space is: %d", RingBuffer_available_data(buffer),
          RingBuffer_available_space(buffer));
    mu_assert(RingBuffer_available_data(buffer) == 0, "Should have 0 data.");
    mu_assert(RingBuffer_available_space(buffer) == 100,
              "Should have 100 space.");

    int rc = RingBuffer_write(buffer, data, 100);
    mu_assert(rc == 100, "Failed to write full buffer.");
    mu_assert(RingBuffer_available_space(buffer) == 0,
              "Invalid available space.");
    mu_assert(RingBuffer_available_data(buffer) == 100,
              "Invalid available data.");
    mu_assert(RingBuffer_full(buffer), "Buffer should be full.");
    mu_assert(!RingBuffer_empty(buffer), "Should not be empty.");
    RingBuffer_clear(buffer);

    rc = RingBuffer_write(buffer, "hello", sizeof("hello"));
    mu_assert(rc == sizeof("hello"), "Failed to write hello.");
    mu_assert(RingBuffer_available_data(buffer) == 6, "Should have 6 data.");
    mu_assert(RingBuffer_available_space(buffer) == 100 - 6,
              "Should have 100 space.");

    rc = RingBuffer_write(buffer, "Zed", sizeof("Zed"));
    mu_assert(rc == sizeof("Zed"), "Failed to write Zed.");

    mu_assert(!RingBuffer_empty(buffer), "Should NOT be empty.");
    mu_assert(!RingBuffer_full(buffer), "Should NOT be full.");

    rc = RingBuffer_read(buffer, data, sizeof("hello"));
    mu_assert(rc == sizeof("hello"), "Failed to read the hello out.");

    mu_assert(!RingBuffer_empty(buffer), "Should be empty.");
    mu_assert(!RingBuffer_full(buffer), "Should NOT be full.");

    rc = RingBuffer_read(buffer, data, sizeof("Zed"));
    mu_assert(rc == sizeof("Zed"), "Failed to read the Zed out.");
    mu_assert(RingBuffer_empty(buffer), "Should be empty.");

    bstring data = bfromcstr("Hello Again");
    rc = RingBuffer_puts(buffer, data);
    bdestroy(data);
    mu_assert(rc != -1, "Failed to write a bstring.");
    mu_assert(!RingBuffer_empty(buffer), "Should NOT be empty.");

    data = RingBuffer_gets(buffer, 2);
    mu_assert(data, "Didn't get any bstring from gets.");
    mu_assert(bisstemeqblk(data, "He", 2), "Wrong gets result.");
    bdestroy(data);

    data = RingBuffer_get_all(buffer);
    mu_assert(data, "Didn't get any bstring from gets.");
    mu_assert(bisstemeqblk(data, "llo Again", 9), "Wrong get_all result.");
    bdestroy(data);
    */
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