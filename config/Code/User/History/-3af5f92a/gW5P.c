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
    //////////////////////////////////////////////////
    /// ### ITER #1 ###
    unsigned char *w_ptr = rng_buf_write_address(buffer);
    memcpy(w_ptr, "1234", 4);
    rng_buf_write_advance(buffer, 4);

    unsigned char *r_ptr = rng_buf_read_address(buffer);
    rng_buf_read_advance(buffer, 4);

    //////////////////////////////////////////////////
    /// ### ITER #2 ###
    unsigned char garbage[buffer->size - 1];
    for (unsigned i = 0; i < sizeof(garbage); i++) garbage[i] = random();

    w_ptr = rng_buf_write_address(buffer);
    memcpy(w_ptr, garbage, sizeof(garbage));
    rng_buf_write_advance(buffer, sizeof(garbage));

    r_ptr = rng_buf_read_address(buffer);
    rng_buf_read_advance(buffer, sizeof(garbage));

    //////////////////////////////////////////////////
    /// ### ITER #3 ###
    unsigned char garb_2[buffer->size];
    for (unsigned i = 0; i < sizeof(garb_2); i++) garb_2[i] = random();

    w_ptr = rng_buf_write_address(buffer);
    memcpy(w_ptr, garb_2, sizeof(garb_2));
    rng_buf_write_advance(buffer, sizeof(garb_2));

    r_ptr = rng_buf_read_address(buffer);
    rng_buf_read_advance(buffer, sizeof(garb_2));

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