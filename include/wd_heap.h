/*=============================================================================

                           HEAP functionalities:

===============================================================================

1.) Function: HeapCreate - Creation of a heap.

Usage: heap_t *heap = HeapCreate(cmp)
Description: The function allocates a new empty heap.

Arguments:
    - cmp: A pointer to the comparison function used to determine the order of 
    elements in the heap.

Return value:
    - Pointer to the heap itself.
    - In case of failure, NULL will be returned.

Time complexity: Worst: O(1)
Space complexity: Worst: O(1)

===============================================================================

2.) Function: HeapDestroy - Destruction of a heap.

Usage: HeapDestroy(heap)

Description: The function frees the memory allocated for the heap.

Arguments:
    - heap: Pointer to the heap to be destroyed.

Time complexity: O(n) 

===============================================================================

3.) Function: HeapPush - Insertion of an element into the heap.

Usage: int result = HeapPush(heap, data)

Description: The function inserts an element into the heap according to the 
             specified order.
Arguments:
    - heap: Pointer to the heap.
    - data: Pointer to the element to be inserted.

Return value:
    - 0 if successful.
    - Non-zero value if an error occurred.

Time complexity: O(log n) 

===============================================================================

4.)  Function: HeapRemove - Removal of a specific element from the heap.

Usage: void *element = HeapRemove(heap, data, is_match)

Description: The function removes a specific element from the heap based on a 
             matching criterion.

Arguments:
    - heap: Pointer to the heap.
    - data: Pointer to the element to be removed.
    - is_match: Function pointer that determines the matching condition for removal.

Return value:
    - Pointer to the removed element if it is found and successfully removed.
    - NULL or a specific error value if the element is not found or an error occurs during removal.

Time complexity: O(log n)

===============================================================================

5.) Function: HeapPop - Removal of the top element from the heap.

Usage: void *element = HeapPop(heap)

Description: The function removes the top element (i.e., the element with the 
            highest priority) from the heap.

Arguments:
    - heap: Pointer to the heap.

Return value:
    - Pointer to the removed element.

Time complexity: O(log n) 

===============================================================================

6.) Function: HeapPeek - Access the top element of the heap.

Usage: void *element = HeapPeek(heap)

Description: The function returns a pointer to the top element of the heap 
             without removing it.

Arguments:
    - heap: Pointer to the heap.

Return value:
    - Pointer to the top element.

Time complexity: O(1)

===============================================================================

7.) Function: HeapSize - Get the number of elements in the heap.

Usage: size_t size = HeapSize(heap)

Description: The function returns the number of elements currently stored in the 
             heap.
Arguments:
    - heap: Pointer to the heap.

Return value:
    - Number of elements in the heap.

Time complexity: O(1) 

===============================================================================

8.) Function: HeapIsEmpty - Check if the heap is empty.

Usage: int is_empty = HeapIsEmpty(heap)

Description: The function checks whether the heap is empty or not.

Arguments:
    - heap: Pointer to the heap.

Return value:
    - 1 if the heap is empty.
    - 0 if the heap is not empty.

Time complexity: O(1)

==============================================================================*/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

enum status
{
    SUCCESS = 0, FAILURE
};

typedef struct heap heap_t;
typedef int (*heap_compare_func_t) (const void *data, const void *new_data);
typedef int (*heap_is_match_func_t) (const void *data, const void *new_data);

void *HeapPop(heap_t *heap);

void HeapDestroy(heap_t *heap);

void *HeapPeek(const heap_t *heap);

size_t HeapSize(const heap_t *heap);

int HeapIsEmpty(const heap_t *heap);

int HeapPush(heap_t *heap, void *data);

void HeapSort(int *data_set, size_t size);

heap_t *HeapCreate(heap_compare_func_t cmp);

void *HeapRemove(heap_t *heap, const void *data, heap_is_match_func_t is_match);


#endif /* __HEAP_H__ */
