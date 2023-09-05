#ifndef __HEAP_PQ_H__
#define __HEAP_PQ_H__

#include <stddef.h> /*size_t */


/*****************************************************************************/

typedef struct heap_pq heap_pq_t;


/*The function we will use to sort the queue. returns an integer indicating the result of the comparison, as follows:
 positive if "new_data" has higher priority than "data" (and will be dequeued before), 
 negative if "new_data" has lower priority than "data" (and will be dequeued after),
 or 0, if the data and new_data have the same priority, (and then new_data will be dequeued after data) */

typedef int (*heap_pq_compare_func_t) (void *data, void *new_data);

/* Used in Erase. Should return non-zero if "data" match the "parameter" */
typedef int (*heap_pq_ismatch_func_t) (void *data, void *parameter);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Creation of a Queue, if creation fails it will return NULL */

heap_pq_t *HeapPQCreate(heap_pq_compare_func_t compare);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Destroy of the Queue. */

void HeapPQDestroy(heap_pq_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(log n), space complexity O(1).
   Adds element to the right position in the queue. return 0 on success. */

int HeapPQEnqueue(heap_pq_t *queue, void *data);

/*****************************************************************************/

/* Complexity - time Complexity O(log n), space complexity O(1).
   Removes element from head of queue */

void *HeapPQDequeue(heap_pq_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return the data from the head of queue */

void *HeapPQPeek(const heap_pq_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Return 1 if empty and 0 if not */

int HeapPQIsEmpty(const heap_pq_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(1), space complexity O(1).
   Returns the size of queue */

size_t HeapPQSize(const heap_pq_t *queue);

/*****************************************************************************/

/* Complexity - time Complexity O(log n), space complexity O(1).
   Returns the data of removed element, or the queue itself, in case there is no match  */
   
void *HeapPQErase(heap_pq_t *queue, heap_pq_ismatch_func_t is_match, void *parameter);

/*****************************************************************************/

/* Complexity - time Complexity O(n), space complexity O(1).
   Returns empty queue */
   
void HeapPQClear(heap_pq_t *queue);

/*****************************************************************************/

#endif /* __HEAP_PQ_H__ */
