#ifndef lcthw_stack_h
#define lcthw_stack_h

struct StackNode;
typedef struct StackNode {
    void* value;
    struct StackNode* prev;
} StackNode;

#endif