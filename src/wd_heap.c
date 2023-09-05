/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Ravit Yahud.

    Date: 14.05.2023

*******************************************************************************

                          Description:

  This code implements a heap data structure using a vector as the underlying 
  storage. It provides operations for creating and destroying a heap, pushing 
  elements onto the heap, popping the top element, removing a specific element, 
  and retrieving the top element without removing it. The heap can be customized 
  with a comparison function to determine the order of the elements.

******************************************************************************/
#include <stdlib.h>    /* malloc, free */
#include <assert.h>    /* assert       */

#include "wd_heap.h"   /* Internal API */
#include "wd_vector.h" /* Internal API */
/*****************************************************************************/
struct heap
{
    vector_t *vector;
    heap_compare_func_t cmp;
};
/*****************************************************************************/
static void SortSwap(int *, int *);
static void HeapifyUp(heap_t *, size_t);
static void ReOrderHeap(heap_t *, size_t);
static void Swap(heap_t *,size_t, size_t);
static void HeapifyDown(heap_t *, size_t);
static int Compare(heap_t *, size_t, size_t);
static void SortHeapify(int *, size_t, size_t);
static size_t FindElementIndex(const heap_t *, const void *, heap_is_match_func_t);
/*****************************************************************************/
#define SIZE (DVectorSize(heap->vector))
#define ELEMENT(I) (DVectorGetElement(heap->vector, I))
#define SET_ELEMENT(X,Y) (DVectorSetElement(heap->vector, X, Y))
/*****************************************************************************/
heap_t *HeapCreate(heap_compare_func_t cmp)
{
    heap_t *heap = NULL;
    assert(cmp && "Comparison not valid.");
    heap = (heap_t *)malloc(sizeof(heap_t));
    if(NULL == heap)
    {
        return (NULL);
    }

    heap->vector = DVectorCreate(sizeof(heap_t));
    if(NULL == heap->vector)
    {
        free(heap);
        return (NULL);
    }

    heap->cmp = cmp;
    return (heap);
}
/*****************************************************************************/ 
void HeapDestroy(heap_t *heap)
{
    assert(heap && "Heap is not valid.");
    DVectorDestroy(heap->vector);
    free(heap);
    heap = NULL;
}
/*****************************************************************************/ 
int HeapPush(heap_t *heap, void *data)
{
    int status = SUCCESS;
    assert(heap && "Heap is not valid.");
    status = DVectorPushBack(heap->vector, data);

    if(SUCCESS == status)
    {
        HeapifyUp(heap, SIZE - 1);
    }

    return (status);
}
/*****************************************************************************/ 
void *HeapPop(heap_t *heap)
{
    void *data = NULL;
    assert(heap && "Heap not valid.");
    if(DVectorIsEmpty(heap->vector))
    {
        return (NULL);
    }

    data = ELEMENT(0);
    ReOrderHeap(heap, 0);
    return (data);
}
/*****************************************************************************/ 
void *HeapRemove(heap_t *heap, const void *data, heap_is_match_func_t is_match)
{
    void *element = NULL;
    size_t data_index = 0;
    assert(heap); assert(is_match);
    data_index = FindElementIndex(heap, data, is_match);

    if(SIZE == data_index)
    {
        return (NULL);
    }

    element = ELEMENT(data_index);
    ReOrderHeap(heap, data_index);
    return (element);
}
/*****************************************************************************/ 
void *HeapPeek(const heap_t *heap)
{
    assert(heap && "Heap not valid.");
    if(HeapIsEmpty(heap))
    {
        return (NULL);
    }

    return (ELEMENT(0));
}
/*****************************************************************************/ 
size_t HeapSize(const heap_t *heap)
{
    assert(heap && "Heap not valid.");
    return (SIZE);
}
/*****************************************************************************/ 
int HeapIsEmpty(const heap_t *heap)
{
    assert(heap && "Heap not valid.");
    return (DVectorIsEmpty(heap->vector));
}
/*****************************************************************************/ 
void HeapSort(int *data_set, size_t size)
{
    int i = (size / 2) - 1;
    for(; 0 <= i; --i)
    {
        SortHeapify(data_set, i, size);
    }

    for(i = (size - 1); 0 <= i; --i)
    {
        SortSwap(&data_set[0], &data_set[i]);
        SortHeapify(data_set, 0, i);
    }
}
/*****************************************************************************/ 
static void HeapifyUp(heap_t *heap, size_t index)
{
    size_t parent = (index - 1) / 2;
    if(index != 0 && 0 > Compare(heap, index, parent))
    {
        Swap(heap, index, parent);
        HeapifyUp(heap, parent);
    }
}
/*****************************************************************************/
static void HeapifyDown(heap_t *heap, size_t index)
{
    size_t largest_index = index;
    size_t left_child = (2 * index) + 1;
    size_t right_child = (2 * index) + 2;

    if(SIZE > left_child && 0 > Compare(heap, left_child, largest_index))
    {
        largest_index = left_child;
    }

    if(SIZE > right_child && 0 > Compare(heap, right_child, largest_index))
    {
        largest_index = right_child;
    }

    if(largest_index != index)
    {
        Swap(heap, largest_index, index);
        HeapifyDown(heap, largest_index);
    }
}
/*****************************************************************************/ 
static void Swap(heap_t *heap, size_t index1, size_t index2)
{
    void *data = ELEMENT(index1);
    void *tmp = ELEMENT(index2);
    SET_ELEMENT(index2, data);
    SET_ELEMENT(index1, tmp);
}
/*****************************************************************************/ 
static int Compare(heap_t *heap, size_t index1, size_t index2)
{
    return (heap->cmp(ELEMENT(index1), ELEMENT(index2)));
}
/*****************************************************************************/ 
static size_t FindElementIndex(const heap_t *heap, const void *data, heap_is_match_func_t is_match)
{
    size_t index = 0;
    size_t size = SIZE;

    for(;(index < size) && !is_match(ELEMENT(index), data); ++index);
    return (index);
}
/*****************************************************************************/
static void ReOrderHeap(heap_t *heap, size_t index)
{
    SET_ELEMENT(index, ELEMENT(SIZE - 1));
    DVectorSafePop(heap->vector);

    if(index > 0 && Compare(heap, index, (index - 1) / 2) > 0)
    {
        HeapifyUp(heap, index);
    }
    else
    {
        HeapifyDown(heap, index);
    }
}
/*****************************************************************************/
static void SortSwap(int *arg1, int *arg2)
{
    int temp = *arg1;
    *arg1 = *arg2;
    *arg2 = temp;
}
/*****************************************************************************/
static void SortHeapify(int *heap, size_t index, size_t size)
{
    size_t largest_index = index;
    size_t left_child = (2 * index) + 1;
    size_t right_child = (2 * index) + 2;

    if((size > left_child) && (heap[left_child] > heap[largest_index]))
    {
        largest_index = left_child;
    }

    if(size > right_child && (heap[right_child] > heap[largest_index]))
    {
        largest_index = right_child;
    }

    if(largest_index != index)
    {
        SortSwap(&heap[index], &heap[largest_index]);
        SortHeapify(heap, largest_index, size);
    }
}
/*****************************************************************************/
