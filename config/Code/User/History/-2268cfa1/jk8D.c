#include "list_algos.h"

#include <stdio.h>

#include "dbg.h"
#include "list.h"

inline void ListNode_swap(ListNode *a, ListNode *b) {
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

/*
procedure bubbleSort(A : list of sortable items)
    n := length(A)
    repeat
        swapped := false
        for i := 1 to n-1 inclusive do
            { if this pair is out of order }
            if A[i-1] > A[i] then
                { swap them and remember something changed }
                swap(A[i-1], A[i])
                swapped := true
            end if
        end for
    until not swapped
end procedure
*/
int List_bubble_sort(List *words, List_compare cmp) {
    int n = words->count;
    if (n <= 1) {
        return 0;
    }

    int swapped = false;
    do {
        swapped = false;
        ListNode *node = words->first;
        for (int i = 0; i < n - 1; i++, node = node->next) {
            if (cmp(node->value, node->next->value) > 0) {
                ListNode_swap(node, node->next);
                swapped = true;
            }
        }
    } while (swapped == true);

    return 0;
}

/*
function merge(left, right) is
    var result := empty list

    while left is not empty and right is not empty do
        if first(left) ≤ first(right) then
            append first(left) to result
            left := rest(left)
        else
            append first(right) to result
            right := rest(right)

    // Either left or right may have elements left; consume them.
    // (Only one of the following loops will actually be entered.)
    while left is not empty do
        append first(left) to result
        left := rest(left)
    while right is not empty do
        append first(right) to result
        right := rest(right)
    return result
*/
inline List *List_merge(List *left, List *right, List_compare cmp) {
    List *result = List_create();
    ListNode *left_node = left->first;
    ListNode *right_node = right->first;

    while (left_node != NULL && right_node != NULL) {
        if (cmp(left_node->value, right_node->value) <= 0) {
            List_push(result, left_node->value);
            left_node = left_node->next;

        } else {
            List_push(result, right_node->value);
            right_node = right_node->next;
        }
    }
    while (left_node != NULL) {
        List_push(result, left_node->value);
        left_node = left_node->next;
    }
    while (right_node != NULL) {
        List_push(result, right_node->value);
        right_node = right_node->next;
    }

    return result;
}
/*
inline List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
    void *val = NULL;

    while(List_count(left) > 0 || List_count(right) > 0) {
        if(List_count(left) > 0 && List_count(right) > 0) {
            if(cmp(List_first(left), List_first(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } else if(List_count(left) > 0) {
            val = List_shift(left);
            List_push(result, val);
        } else if(List_count(right) > 0) {
            val = List_shift(right);
            List_push(result, val);
        }
    }

    return result;
}
*/

/*
function merge_sort(list m) is
    // Base case. A list of zero or one elements is sorted, by definition.
    if length of m ≤ 1 then
        return m

    // Recursive case. First, divide the list into equal-sized sublists
    // consisting of the first half and second half of the list.
    // This assumes lists start at index 0.
    var left := empty list
    var right := empty list
    for each x with index i in m do
        if i < (length of m)/2 then
            add x to left
        else
            add x to right

    // Recursively sort both sublists.
    left := merge_sort(left)
    right := merge_sort(right)

    // Then merge the now-sorted sublists.
    return merge(left, right)
    */
// 我的代码可能会出现内存泄露，因为没有destroy。
List *List_merge_sort(List *words, List_compare cmp) {
    int n = words->count;
    if (n <= 1) {
        return words;
    }

    ListNode *split_point = words->first;
    for (int i = 0; i < n / 2 - 1; i++) {
        split_point = split_point->next;
    }
    List *left = words;
    List *right = List_split(left, split_point);

    List *sorted_left = List_merge_sort(left, cmp);
    List *sorted_right = List_merge_sort(right, cmp);

    List *merged = List_merge(sorted_left, sorted_right, cmp);

    // Segmentation fault
    // List_destroy(sorted_left);
    // List_destroy(sorted_right);

    return merged;
}

/*
List *List_merge_sort(List *list, List_compare cmp)
{
    if(List_count(list) <= 1) {
        return list;
    }

    List *left = List_create();
    List *right = List_create();
    int middle = List_count(list) / 2;

    LIST_FOREACH(list, first, next, cur) {
        if(middle > 0) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }

        middle--;
    }

    List *sort_left = List_merge_sort(left, cmp);
    List *sort_right = List_merge_sort(right, cmp);

    if(sort_left != left) List_destroy(left);
    if(sort_right != right) List_destroy(right);

    return List_merge(sort_left, sort_right, cmp);
}
*/

List *List_insert_sorted(List *words, void *value, List_compare cmp) {
    ListNode *node = calloc(1, sizeof(ListNode));
    node->value = value;

    if (!node) {
        return words;
    }
    if (words->last == NULL) {
        words->first = node;
        words->last = node;
    } else {
        ListNode *cur = words->first;
        while (cur != NULL && cmp(node->value, cur->value) > 0) {
            cur = cur->next;
        }

        if (cur == NULL) {
            node->prev = words->last;
            words->last->next = node;
            words->last = node;
        } else if (cur->prev == NULL) {
            node->next = words->first;
            words->first->prev = node;
            words->first = node;
        } else {
            // 这里要调整一下，因为上面的while循环其实找到的是目标node的next位置。
            cur = cur->prev;
            ListNode *after = cur->next;
            cur->next = node;
            node->prev = cur;
            node->next = after;
            after->prev = node;
        }
    }

    words->count++;

    return words;
}

/*
// array A[] has the items to sort; array B[] is a work array
void BottomUpMergeSort(A[], B[], n)
{
    // Each 1-element run in A is already "sorted".
    // Make successively longer sorted runs of length 2, 4, 8, 16... until the
    // whole array is sorted.
    for (width = 1; width < n; width = 2 * width)
    {
        // Array A is full of runs of length width.
        for (i = 0; i < n; i = i + 2 * width)
        {
            // Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[]
            // or copy A[i:n-1] to B[] ( if (i+width >= n) )
            BottomUpMerge(A, i, min(i+width, n), min(i+2*width, n), B);
        }
        // Now work array B is full of runs of length 2*width.
        // Copy array B to array A for the next iteration.
        // A more efficient implementation would swap the roles of A and B.
        CopyArray(B, A, n);
        // Now array A is full of runs of length 2*width.
    }
}

//  Left run is A[iLeft :iRight-1].
// Right run is A[iRight:iEnd-1  ].
void BottomUpMerge(A[], iLeft, iRight, iEnd, B[])
{
    i = iLeft, j = iRight;
    // While there are elements in the left or right runs...
    for (k = iLeft; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iRight && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }
}

void CopyArray(B[], A[], n)
{
    for (i = 0; i < n; i++)
        A[i] = B[i];
}
*/

inline void List_bottom_up_merge(List *A, ListNode *A_iLeft_node,
                                 ListNode *B_iLeft_node,
                                 ListNode *A_iRight_node, ListNode *A_iEnd_node,
                                 List_compare cmp) {
    ListNode *i = A_iLeft_node, *j = A_iRight_node, *k = B_iLeft_node;
    while (i != A_iRight_node && j != A_iEnd_node) {
        if (cmp(i->value, j->value) <= 0) {
            k->value = i->value;
            i = i->next;
        } else {
            k->value = j->value;
            j = j->next;
        }
        k = k->next;
    }
    while (i != A_iRight_node) {
        k->value = i->value;
        i = i->next;
        k = k->next;
    }
    while (j != A_iEnd_node) {
        k->value = j->value;
        j = j->next;
        k = k->next;
    }
}

void List_bottom_up_merge_sort(List *A, List *B, int n, List_compare cmp) {
    for (int width = 1; width < n; width <<= 1) {
        for (int i = 0; i < n; i += width << 1) {
            int iLeft = i, iRight = min(i + width, i),
                iEnd = min(i + (width << 1), n);
            ListNode *A_iLeft_node = A->first;
            for (int tp = 0; tp < iLeft; tp++) {
                A_iLeft_node = A_iLeft_node->next;
            }

            ListNode *B_iLeft_node = A->first;
            for (int tp = 0; tp < iLeft; tp++) {
                B_iLeft_node = B_iLeft_node->next;
            }

            ListNode *A_iRight_node = A->first;
            for (int tp = 0; tp < iRight; tp++) {
                A_iRight_node = A_iRight_node->next;
            }

            ListNode *A_iEnd_node = A->first;
            for (int tp = 0; tp < iEnd; tp++) {
                A_iEnd_node = A_iEnd_node->next;
            }

            List_bottom_up_merge(A, A_iLeft_node, B_iLeft_node, A_iRight_node,
                                 A_iEnd_node, cmp);
        }
        A = List_copy(B);
        LIST_FOREACH(A, first, next, cur) {
            printf("%s\n", (char *)cur->value);
        }
        printf("\n");
    }
}
