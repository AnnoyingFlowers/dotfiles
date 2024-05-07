#include <assert.h>
#include <stdio.h>
//#include <lcthw/list.h>
#include "../src/lcthw/list.h"
#include "minunit.h"

static List *list = NULL;
static List *dest = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create() {
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_destroy() {
    List_clear_destroy(list);

    return NULL;
}

char *test_push_pop() {
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift() {
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove() {
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}

char *test_shift() {
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *test_copy() {
    dest = List_copy(list);
    mu_assert(List_count(dest) == List_count(list), "Wrong count after copy.");

    ListNode *src_node = list->first;
    ListNode *dest_node = dest->first;
    while (src_node != NULL && dest_node != NULL) {
        mu_assert(src_node->value == dest_node->value,
                  "Wrong value after copy.");
        src_node = src_node->next;
        dest_node = dest_node->next;
    }

    return NULL;
}

char *test_concat() {
    dest = List_concat(dest, list);
    mu_assert(dest->count == 6, "Wrong count after concat.");
    mu_assert(List_first(dest) == test3, "Wrong value on first after concat.");
    mu_assert(List_last(dest) == test1, "Wrong value on dest after concat.");

    return NULL;
}

char *test_split() {
    ListNode *split_point = dest->first->next->next;
    list = List_split(dest, split_point);
    mu_assert(split_point->value == test3,
              "Wrong value on split_point after split.");
    mu_assert(dest->count == 3, "Wrong count on dest after split.");
    mu_assert(list->count == 3, "Wrong count on src after split.");
    mu_assert(List_last(dest) == test1, "Wrong value on dest after split.");
    mu_assert(List_first(list) == test3, "Wrong value on list after split.");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_copy);
    mu_run_test(test_concat);
    mu_run_test(test_split);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);