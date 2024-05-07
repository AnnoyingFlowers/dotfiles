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

#define Queue_destroy()

#define Queue_send(Q, V)                                     \
    ({                                                       \
        QueueNode* _new_node = calloc(1, sizeof(QueueNode)); \
        _new_node->value = (V);                              \
        if (Q->recv == NULL) {                               \
            Q->recv = _new_node;                             \
            Q->peek = _new_node;                             \
        } else {                                             \
            Q->peek->next = _new_node;                       \
            _new_node->prev = Q->peek;                       \
            Q->peek = _new_node;                             \
        }                                                    \
        Q->count++;                                          \
    })

#define Queue_peek(Q) ((Q)->peek->value)

#define Queue_recv(Q) ((Q)->recv->value)

#define Queue_count(Q) ((Q)->count)
#endif