#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

// Define a structure for a node in a doubly linked list
struct ListNode;

// Define a structure for a doubly linked list
typedef struct ListNode {
    struct ListNode *next;  // Pointer to the next node in the list
    struct ListNode *prev;  // Pointer to the previous node in the list
    void *value;            // Pointer to the value stored in the node
} ListNode;

// Define a structure for a doubly linked list
typedef struct List {
    int count;        // Number of nodes in the list
    ListNode *first;  // Pointer to the first node in the list
    ListNode *last;   // Pointer to the last node in the list
} List;

// Function to create a new empty list
List *List_create();

// Function to destroy a list and free its memory
void List_destroy(List *list);

// Function to remove all nodes from a list
void List_clear(List *list);

// Function to remove all nodes from a list and free its memory
void List_clear_destroy(List *list);

// Macro to get the count of nodes in a list
#define List_count(A) ((A)->count)

// Macro to get the value of the first node in a list
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)

// Macro to get the value of the last node in a list
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

// Function to add a new node with the given value to the end of a list
void List_push(List *list, void *value);

// Function to remove and return the value of the last node in a list
void *List_pop(List *list);

// Function to add a new node with the given value to the beginning of a list
void List_unshift(List *list, void *value);

// Function to remove and return the value of the first node in a list
void *List_shift(List *list);

// Function to remove a specific node from a list
void *List_remove(List *list, ListNode *node);

// Macro to iterate over each node in a list
#define LIST_FOREACH(L, S, M, V) \
    ListNode *_node = NULL;      \
    ListNode *V = NULL;          \
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
