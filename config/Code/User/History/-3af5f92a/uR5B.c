#include "../src/lcthw/ringbuffer_posix.h"
#include "minunit.h"

static rng_buf_t *buffer = NULL;
char data[128] = {'\0'};
#define DEFAULT_LEN 128

char *test_create() {
    buffer = rng_buf_create("", 0, false);
    return NULL;
}

char *test_destroy() {
    rng_buf_destroy(&buffer);
    return NULL;
}

char *test_read_write() {
    /////////////
    mu_assert(buffer != NULL, "buffer can't be NULL");
    ASSERT_NE(nullptr, buffer->base);
    ASSERT_EQ(sysconf(_SC_PAGESIZE), (long)buffer->size);

    //////////////////////////////////////////////////
    /// ### ITER #1 ###
    unsigned char *w_ptr = rng_buf_write_address(buffer);
    memcpy(w_ptr, "1234", 4);
    rng_buf_write_advance(buffer, 4);

    ASSERT_EQ(rng_buf_len(buffer), 4U);
    ASSERT_EQ(rng_buf_free_bytes(buffer), buffer->size - 4);

    unsigned char *r_ptr = rng_buf_read_address(buffer);
    ASSERT_EQ(0, memcmp(r_ptr, "1234", 4));
    rng_buf_read_advance(buffer, 4);

    ASSERT_EQ(rng_buf_len(buffer), 0U);
    ASSERT_EQ(rng_buf_free_bytes(buffer), buffer->size);

    //////////////////////////////////////////////////
    /// ### ITER #2 ###
    unsigned char garbage[buffer->size - 1];
    for (unsigned i = 0; i < sizeof(garbage); i++) garbage[i] = random();

    w_ptr = rng_buf_write_address(buffer);
    memcpy(w_ptr, garbage, sizeof(garbage));
    rng_buf_write_advance(buffer, sizeof(garbage));

    ASSERT_EQ(rng_buf_len(buffer), sizeof(garbage));
    ASSERT_EQ(rng_buf_free_bytes(buffer), buffer->size - sizeof(garbage));

    r_ptr = rng_buf_read_address(buffer);
    ASSERT_EQ(0, memcmp(r_ptr, garbage, sizeof(garbage)));
    rng_buf_read_advance(buffer, sizeof(garbage));

    ASSERT_EQ(rng_buf_len(buffer), 0U);
    ASSERT_EQ(rng_buf_free_bytes(buffer), buffer->size);

    //////////////////////////////////////////////////
    /// ### ITER #3 ###
    unsigned char garb_2[buffer->size];
    for (unsigned i = 0; i < sizeof(garb_2); i++) garb_2[i] = random();

    w_ptr = rng_buf_write_address(buffer);
    memcpy(w_ptr, garb_2, sizeof(garb_2));
    rng_buf_write_advance(buffer, sizeof(garb_2));

    ASSERT_EQ(rng_buf_len(buffer), sizeof(garb_2));
    ASSERT_EQ(rng_buf_free_bytes(buffer), buffer->size - sizeof(garb_2));

    r_ptr = rng_buf_read_address(buffer);
    ASSERT_EQ(0, memcmp(r_ptr, garb_2, sizeof(garb_2)));
    rng_buf_read_advance(buffer, sizeof(garb_2));

    ASSERT_EQ(rng_buf_len(buffer), 0U);
    ASSERT_EQ(rng_buf_free_bytes(buffer), buffer->size);

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