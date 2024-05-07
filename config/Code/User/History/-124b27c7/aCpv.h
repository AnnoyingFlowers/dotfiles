#ifndef lcthw_stack_h
#define lcthw_stack_h

struct StackNode;
typedef struct StackNode {
    struct StackNode* down;
    void* value;
} StackNode;

typedef struct Stack {
    int count;
    StackNode* peek;
} Stack;

#define Stack_create() (calloc(1, sizeof(Stack)));

#define Stack_destroy(A)                     \
    (STACK_FOREACH(A, C) {                   \
        StackNode* _prev_node = _node->down; \
        if (C) {                             \
        }                                    \
    })

#define STACK_FOREACH(S, C)  \
    StackNode* _node = NULL; \
    StackNode* C = NULL;     \
    for (C = _node = S->peek; _node != NULL; C = _node = _node->down)

#endif