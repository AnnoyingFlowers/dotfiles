#ifndef lcthw_stack_h
#define lcthw_stack_h

#include "darray.h"

typedef DArray Stack;

#define Stack_create() DArray_create(1, 10)
#define Stack_destroy(S) DArray_destroy(S)
#define Stack_clear(S) DArray_clear(S)
#define Stack_clear_destroy(S) DArray_clear_destroy(S)

#define Stack_push(S, V) DArray_push(S, V)
#define Stack_pop(S) DArray_pop(S)
#define Stack_peek(S) DArray_last(S)

#define Stack_count(S) DArray_count(S)

#define STACK_FOREACH(S, C) \
    for (int i = 0; i < DArray_end(S), C = DArray_get(S, i); i++)

/*
struct StackNode;
typedef struct StackNode {
    struct StackNode* down;
    void* value;
} StackNode;

typedef struct Stack {
    int count;
    StackNode* peek;
} Stack;

#define Stack_create() (calloc(1, sizeof(Stack)))

#define Stack_push(S, V)                                 \
    StackNode* _new_node = calloc(1, sizeof(StackNode)); \
    _new_node->value = (V);                              \
    if ((S)->peek == NULL) {                             \
        (S)->peek = _new_node;                           \
    } else {                                             \
        _new_node->down = (S)->peek;                     \
        (S)->peek = _new_node;                           \
    }                                                    \
    (S)->count++;

#define Stack_peek(S) ((S)->peek->value)

#define Stack_count(S) ((S)->count)

#define Stack_pop(S)                              \
    ({                                            \
        void* _result = NULL;                     \
        if ((S)->peek != NULL) {                  \
            _result = (S)->peek->value;           \
            StackNode* _node_to_free = (S)->peek; \
            (S)->peek = (S)->peek->down;          \
            free(_node_to_free);                  \
            (S)->count--;                         \
        }                                         \
        _result;                                  \
    })

#define Stack_destroy(S)          \
    ({                            \
        while (S->peek != NULL) { \
            free(Stack_pop(S));   \
        }                         \
        free(S);                  \
    })

#define STACK_FOREACH(S, C)  \
    StackNode* _node = NULL; \
    StackNode* C = NULL;     \
    for (C = _node = S->peek; _node != NULL; C = _node = _node->down)
*/
/* another way
typedef List Stack;

#define Stack_create List_create
#define Stack_destroy List_destroy
#define Stack_clear List_clear
#define Stack_clear_destroy List_clear_destroy

#define Stack_push List_push
#define Stack_pop List_pop
#define Stack_peek List_last

#define Stack_count List_count

#define STACK_FOREACH(curr, stack) LIST_FOREACH(curr, stack)
*/

#endif