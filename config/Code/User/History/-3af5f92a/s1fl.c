#include <stdarg>
#include <stddef>
#include <stdio>
#include <stdlib>
#include <string>

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
    rng_buf_t *rng_buf = buffer;
    /////////////
    mu_assert(rng_buf != NULL, "rng_buf is nullptr");
    mu_assert(rng_buf->base != NULL, "rng_buf->base is nullptr");
    mu_assert(sysconf(_SC_PAGESIZE) == (long)rng_buf->size,
              "sysconf(_SC_PAGESIZE) != rng_buf->size");

    //////////////////////////////////////////////////
    /// ### ITER #1 ###
    unsigned char *w_ptr = rng_buf_write_address(rng_buf);
    memcpy(w_ptr, "1234", 4);
    rng_buf_write_advance(rng_buf, 4);

    mu_assert(rng_buf_len(rng_buf) == 4U, "rng_buf_len(rng_buf) != 4");
    mu_assert(rng_buf_free_bytes(rng_buf) == rng_buf->size - 4,
              "rng_buf_free_bytes(rng_buf) != rng_buf->size - 4");

    unsigned char *r_ptr = rng_buf_read_address(rng_buf);
    mu_assert(memcmp(r_ptr, "1234", 4) == 0, "memcmp(r_ptr, '1234', 4) != 0");
    rng_buf_read_advance(rng_buf, 4);

    mu_assert(rng_buf_len(rng_buf) == 0U, "rng_buf_len(rng_buf) != 0");
    mu_assert(rng_buf_free_bytes(rng_buf) == rng_buf->size,
              "rng_buf_free_bytes(rng_buf) != rng_buf->size");

    //////////////////////////////////////////////////
    /// ### ITER #2 ###
    unsigned char garbage[rng_buf->size - 1];
    for (unsigned i = 0; i < sizeof(garbage); i++) garbage[i] = random();

    w_ptr = rng_buf_write_address(rng_buf);
    memcpy(w_ptr, garbage, sizeof(garbage));
    rng_buf_write_advance(rng_buf, sizeof(garbage));

    mu_assert(rng_buf_len(rng_buf) == sizeof(garbage),
              "rng_buf_len(rng_buf) != sizeof(garbage)");
    mu_assert(rng_buf_free_bytes(rng_buf) == rng_buf->size - sizeof(garbage),
              "rng_buf_free_bytes(rng_buf) != rng_buf->size - sizeof(garbage)");

    r_ptr = rng_buf_read_address(rng_buf);
    mu_assert(memcmp(r_ptr, garbage, sizeof(garbage)) == 0,
              "memcmp(r_ptr, garbage, sizeof(garbage)) != 0");
    rng_buf_read_advance(rng_buf, sizeof(garbage));

    mu_assert(rng_buf_len(rng_buf) == 0U, "rng_buf_len(rng_buf) != 0");
    mu_assert(rng_buf_free_bytes(rng_buf) == rng_buf->size,
              "rng_buf_free_bytes(rng_buf) != rng_buf->size");

    //////////////////////////////////////////////////
    /// ### ITER #3 ###
    unsigned char garb_2[rng_buf->size];
    for (unsigned i = 0; i < sizeof(garb_2); i++) garb_2[i] = random();

    w_ptr = rng_buf_write_address(rng_buf);
    memcpy(w_ptr, garb_2, sizeof(garb_2));
    rng_buf_write_advance(rng_buf, sizeof(garb_2));

    mu_assert(rng_buf_len(rng_buf) == sizeof(garb_2),
              "rng_buf_len(rng_buf) != sizeof(garb_2)");
    mu_assert(rng_buf_free_bytes(rng_buf) == rng_buf->size - sizeof(garb_2),
              "rng_buf_free_bytes(rng_buf) != rng_buf->size - sizeof(garb_2)");

    r_ptr = rng_buf_read_address(rng_buf);
    mu_assert(memcmp(r_ptr, garb_2, sizeof(garb_2)) == 0,
              "memcmp(r_ptr, garb_2, sizeof(garb_2)) != 0");
    rng_buf_read_advance(rng_buf, sizeof(garb_2));

    mu_assert(rng_buf_len(rng_buf) == 0U, "rng_buf_len(rng_buf) != 0");
    mu_assert(rng_buf_free_bytes(rng_buf) == rng_buf->size,
              "rng_buf_free_bytes(rng_buf) != rng_buf->size");

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