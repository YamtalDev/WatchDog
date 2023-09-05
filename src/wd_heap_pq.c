/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Ravit.

    Date: 15.05.2023

******************************************************************************/
#include <stdlib.h>     /* malloc, free */
#include <assert.h>     /* assert       */

#include "wd_heap.h"    /* Internal API */
#include "wd_heap_pq.h" /* Internal API */
/*****************************************************************************/
struct heap_pq
{
	heap_t *heap;
};
/*****************************************************************************/
heap_pq_t *HeapPQCreate(heap_pq_compare_func_t compare)
{
    heap_pq_t *heap_pq = (heap_pq_t *)malloc(sizeof(heap_pq_t *));
    if(NULL == heap_pq)
    {
        return NULL;
    }

    assert(compare);
    heap_pq->heap = HeapCreate((heap_compare_func_t)compare);
    if(NULL == heap_pq->heap)
    {
        free(heap_pq);
        heap_pq = NULL;
    }

    return (heap_pq);
}
/*****************************************************************************/ 
void HeapPQDestroy(heap_pq_t *queue)
{
    HeapDestroy(queue->heap);
    free(queue);
    queue = NULL;
}
/*****************************************************************************/ 
int HeapPQEnqueue(heap_pq_t *queue, void *data)
{
    return (HeapPush(queue->heap, data));
}
/*****************************************************************************/ 
void *HeapPQDequeue(heap_pq_t *queue)
{
    return (HeapPop(queue->heap));
}
/*****************************************************************************/ 
void *HeapPQPeek(const heap_pq_t *queue)
{
    assert(queue);
    return (HeapPeek(queue->heap));
}
/*****************************************************************************/ 
int HeapPQIsEmpty(const heap_pq_t *queue)
{
    return (HeapIsEmpty(queue->heap));
}
/*****************************************************************************/ 
size_t HeapPQSize(const heap_pq_t *queue)
{
	return (HeapSize(queue->heap));
}
/*****************************************************************************/ 
void *HeapPQErase(heap_pq_t *queue, heap_pq_ismatch_func_t is_match, void *parameter)
{
    void *data = NULL;
    data = HeapRemove(queue->heap, parameter, (heap_is_match_func_t)is_match);
	return (NULL == data ? (void *)queue : data);
}
/*****************************************************************************/ 
void HeapPQClear(heap_pq_t *queue)
{
    while(!HeapIsEmpty(queue->heap))
    {
        HeapPop(queue->heap);
    }
}
/*****************************************************************************/ 
