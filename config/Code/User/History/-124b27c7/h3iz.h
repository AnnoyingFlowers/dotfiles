#ifndef lcthw_stack_h
#define lcthw_stack_h

struct StackNode;
typedef struct StackNode {
    struct StackNode* prev;
    void* value;
} StackNode;

typedef struct Stack {
    int count;
    StackNode* peek;
} Stack;

#endif