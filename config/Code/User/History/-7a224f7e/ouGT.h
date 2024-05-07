#ifndef lcthw_queue_h
#define lcthw_queue_h

struct QueueNode;
typedef struct QueueNode {
    struct QueueNode* next;
    struct QueueNode* prev;
    void* value;
} QueueNode;

typedef struct Queue {
    QueueNode* peek;
    QueueNode* recv;
    int count;
} Queue;

#define Queue_create() (calloc(1, sizeof(Queue)))

#define Queue_destroy(Q)          \
    ({                            \
        while (Q->peek != NULL) { \
            free(Queue_recv(Q));  \
        }                         \
        free((Q));                \
    })

#define Queue_send(Q, V)                                     \
    ({                                                       \
        QueueNode* _new_node = calloc(1, sizeof(QueueNode)); \
        _new_node->value = (V);                              \
        if ((Q)->recv == NULL) {                             \
            (Q)->recv = _new_node;                           \
            (Q)->peek = _new_node;                           \
        } else {                                             \
            (Q)->recv->prev = _new_node;                     \
            _new_node->next = (Q)->recv;                     \
            (Q)->recv = _new_node;                           \
        }                                                    \
        (Q)->count++;                                        \
    })

#define Queue_peek(Q) ((Q)->peek->value)

#define Queue_recv(Q)                             \
    ({                                            \
        void* _result = NULL;                     \
        if ((Q)->peek) {                          \
            _result = (Q)->peek->value;           \
            QueueNode* _node_to_free = (Q)->peek; \
            (Q)->peek = (Q)->peek->prev;          \
            free(_node_to_free);                  \
            if (!(Q)->peek) {                     \
                (Q)->recv = NULL;                 \
            }                                     \
            (Q)->count--;                         \
        }                                         \
        _result;                                  \
    })

#define Queue_count(Q) ((Q)->count)

#define QUEUE_FOREACH(Q, C)  \
    QueueNode* _node = NULL; \
    QueueNode*(C) = NULL;    \
    for ((C) = _node = (Q)->peek; _node != NULL; (C) = _node = _node->prev)

/* another way
typedef List Queue;

#define Queue_create List_create
#define Queue_destroy List_destroy
#define Queue_clear List_clear
#define Queue_clear_destroy List_clear_destroy

#define Queue_enqueue List_unshift
#define Queue_dequeue List_pop

#define Queue_peek List_last
#define Queue_count List_count

#define QUEUE_FOREACH(curr, queue) LIST_FOREACH(curr, queue)
*/

#endif