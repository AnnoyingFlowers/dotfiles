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

#define Stack_push(S, V)                                  \
    (StackNode* _new_node = calloc(1, sizeof(StackNode)); \
     _new_node->value = (V);)

#define Stack_destroy(S)                       \
    (STACK_FOREACH(S, C) {                   \
        StackNode* _prev_node = _node->down; \
        if (C) {                             \
            free(C->value);                  \
        }                                    \
    }
while (S->peek != NULL) {
}
    )

#define STACK_FOREACH(S, C)  \
    StackNode* _node = NULL; \
    StackNode* C = NULL;     \
    for (C = _node = S->peek; _node != NULL; C = _node = _node->down)

#endif