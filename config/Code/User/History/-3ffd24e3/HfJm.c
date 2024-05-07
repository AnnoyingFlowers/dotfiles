// #include <lcthw/dbg.h>
// #include <lcthw/list.h>
#include "list.h"

#include <assert.h>
#include <stdlib.h>

#include <cstddef>

#include "dbg.h"

List *List_create() {
    return calloc(1, sizeof(List));
}

// 有些人是这样写的，但我觉得不需要。
// 因为calloc和malloc的区别就是，calloc会将申请的内存块置零
// List *List_create() {
//     List *list = calloc(1, sizeof(List));
//     list->first = NULL;
//     list->last = NULL;
//     list->count = 0;
//     return list;
// }

void List_destroy(List *list) {
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

// gcc -E | sed '/#/d' > pre_list.c
// 仅预编译后的内容
// void List_destroy(List *list) {
//     ListNode *_node = ((void *)0);
//     ListNode *cur = ((void *)0);
//     for (cur = _node = list->first; _node != ((void *)0);
//          cur = _node = _node->next) {
//         if (cur->prev) {
//             free(cur->prev);
//         }
//     }
//     free(list->last);
//     free(list);
// }

void List_clear(List *list) {
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

// void List_clear_destroy(List *list) {
//     List_clear(list);
//     List_destroy(list);
// }

// 使这个函数更高效
void List_clear_destroy(List *list) {
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_push(List *list, void *value) {
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list) {
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value) {
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list) {
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node) {
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL,
              "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL,
              "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    check(list->count >= 0, "Invalid list, somehow got a negative count.");
    result = node->value;
    // 要记得free
    free(node);
    node = NULL;

error:
    return result;
}

List *List_copy(List *src) {
    List *copy = List_create();
    LIST_FOREACH(src, first, next, cur) {
        List_push(copy, cur->value);
    }

    return copy;
}

List *List_concat(List *dest, List *src) {
    if (dest->last) {
        dest->last->next = src->first;
    }
    if (src->first) {
        src->first->prev = dest->last;
    }
    if (src->last) {
        dest->last = src->last;
    }
    dest->count += src->count;
    if (src != NULL) {
        free(src);
        src = NULL;
    }
    printf("123  %p\n", src);
    return dest;
}

List *List_split(List *list, ListNode *split_point) {
    List *new_list = List_create();
    if (split_point == NULL) {
        return new_list;
    }

    new_list->first = split_point->next;
    new_list->last = list->last;
    list->last = split_point;
    split_point->next->prev = NULL;
    split_point->next = NULL;
    LIST_FOREACH(list, first, next, cur) {
        new_list->count++;
        if (cur == split_point) {
            break;
        }
    }
    new_list->count = list->count - new_list->count;
    list->count -= new_list->count;

    return new_list;
}