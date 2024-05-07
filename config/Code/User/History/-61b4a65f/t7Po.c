#include <assert.h>
// #include <lcthw/list_algos.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../src/lcthw/list_algos.h"
#include "minunit.h"

char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};
#define NUM_VALUES 5

char *generate_random_string() {
    srand(clock());
    int length = rand() % 17 + 3;

    const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *rand_string = malloc((length + 1) * sizeof(char));

    if (rand_string) {
        for (int i = 0; i < length; i++) {
            int index = rand() % (int)(sizeof(charset) - 1);
            rand_string[i] = charset[index];
        }
        rand_string[length] = '\0';
    }

    return rand_string;
}

List *create_words() {
    int i = 0;
    List *words = List_create();

    for (i = 0; i < NUM_VALUES; i++) {
        List_push(words, generate_random_string());
    }

    return words;
}

int is_sorted(List *words) {
    LIST_FOREACH(words, first, next, cur) {
        if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value, (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort() {
    time_t start_t = clock();
    List *words = create_words();

    // should work on a list that needs sorting
    int rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");

    // should work on an already sorted list
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words),
              "Words should be sort if already bubble sorted.");

    List_destroy(words);

    // should work on an empty list
    words = List_create(words);
    rc = List_bubble_sort(words, (List_compare)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    List_destroy(words);
    time_t finish_t = clock();
    printf("time in bubble sort: %lu\n", finish_t - start_t);

    return NULL;
}

char *test_merge_sort() {
    time_t start_t = clock();
    List *words = create_words();

    // should work on a list that needs sorting
    List *res = List_merge_sort(words, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List *res2 = List_merge_sort(res, (List_compare)strcmp);
    mu_assert(is_sorted(res), "Should still be sorted after merge sort.");

    List_destroy(res2);
    List_destroy(res);
    List_destroy(words);

    time_t finish_t = clock();
    printf("time in merge sort: %lu\n", finish_t - start_t);

    return NULL;
}

char *test_insert_sorted() {
    time_t start_t = clock();

    List *words = List_create();
    for (int i = 0; i < NUM_VALUES; i++) {
        char *string = generate_random_string();
        List_insert_sorted(words, string, (List_compare)strcmp);
    }
    mu_assert(words->count == NUM_VALUES,
              "Count of words should be NUM_VALUES.");
    mu_assert(is_sorted(words), "Should still be sorted after inserting.");
    List_destroy(words);

    time_t finish_t = clock();
    printf("time in insert directly: %lu\n", finish_t - start_t);

    return NULL;
}

char *test_bottom_up_merge_sort() {
    time_t start_t = clock();

    List *words_A = create_words();
    List *words_B = List_copy(words_A);
    List_bottom_up_merge_sort(words_A, words_B, words_A->count,
                              (List_compare)strcmp);
    mu_assert(words_A->count == NUM_VALUES,
              "Count of words_A should be NUM_VALUES.");
    mu_assert(words_B->count == NUM_VALUES,
              "Count of words_B should be NUM_VALUES.");
    mu_assert(is_sorted(words_A),
              "Should still be sorted after bottom up merge sort.");
    List_destroy(words_A);
    List_destroy(words_B);

    time_t finish_t = clock();
    printf("time in bottom up merge sort: %lu\n", finish_t - start_t);
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
    mu_run_test(test_insert_sorted);
    mu_run_test(test_bottom_up_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);