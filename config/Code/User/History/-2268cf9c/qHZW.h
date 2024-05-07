#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include "list.h"

typedef int (*List_compare)(const void *a, const void *b);

int rc = List_bubble_sort(words, (List_compare)strcmp);
List *res = List_merge_sort(words, (List_compare)strcmp);

#endif