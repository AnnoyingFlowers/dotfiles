#ifndef lcthw_queue_h
#define lcthw_queue_h

struct QueueNode;
typedef struct QueueNode {
    QueueNode* next;
    QueueNode* prev;
    void* value;
} QueueNode;

typedef struct Queue {
    QueueNode* peek;
    QueueNode* recv;
    int count;
} Queue;

#define Queue_create() (calloc(1, sizeof(Queue)))

#endif