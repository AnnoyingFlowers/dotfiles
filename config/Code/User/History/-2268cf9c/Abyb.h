#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include "list.h"

#define false (int)0
#define true (int)1
typedef int bool;

typedef int (*List_compare)(const void *a, const void *b);

int List_bubble_sort(List *words, List_compare cmp);

List *List_merge_sort(List *words, List_compare cmp);

#endif