#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include "list.h"

#define false (int)0
#define true (int)1

#define min(_A, _B) ((_A) > (_B) ? (_B) : (_A))

typedef int (*List_compare)(const void *a, const void *b);

int List_bubble_sort(List *words, List_compare cmp);

List *List_merge_sort(List *words, List_compare cmp);

List *List_insert_sorted(List *words, void *value, List_compare cmp);

void List_bottom_up_merge_sort(List *A, List *B, int n, List_compare cmp);

#endif