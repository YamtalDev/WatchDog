/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Ravit.

    Date: 15.05.2023

******************************************************************************/
#include <unistd.h>            /* getpid, sleep */
#include <stdlib.h>            /* malloc, free  */
#include <stddef.h>            /* size_t, NULL  */
#include <assert.h>            /* assert        */
#include <time.h>              /* time          */

#include "wd_heap_scheduler.h" /* Internal API */
#include "wd_heap_pq.h"        /* Internal use */
#include "wd_task.h"           /* Internal use */
/*****************************************************************************/
enum state {SELF_DESTROY = -2, INTERNAL_ERROR, CONTINUE,RUN, STOP};
/*****************************************************************************/
struct heap_scheduler
{
	heap_pq_t *pq;
	int stop;
};
/*****************************************************************************/
#define TIME(X) ((time_t)X)
#define TASK(X) ((task_t *)X)
#define MAX(a,b) ((a) > (b) ? (a) : (b))
/*****************************************************************************/
static int Priority(void *when1, void *when2);
static int IsMatch(void *task, void *task_uid);
/*****************************************************************************/
heap_scheduler_t *HeapSchedulerCreate(void)
{
	heap_scheduler_t *scheduler = (heap_scheduler_t *)malloc(sizeof(heap_scheduler_t));
	if(NULL == scheduler)
	{
		return NULL;
	}

	scheduler->pq = HeapPQCreate(Priority);
	if(NULL == scheduler->pq)
	{
		free(scheduler);
		return ((scheduler = NULL));
	}

	scheduler->stop = RUN;
	return (scheduler);
}
/*****************************************************************************/
void HeapSchedulerDestroy(heap_scheduler_t *scheduler)
{
	HeapSchedulerClear(scheduler);
	HeapPQDestroy(scheduler->pq);

	scheduler->pq = NULL;
	free(scheduler);
	scheduler = NULL;
}
/*****************************************************************************/
ilrd_uid_t HeapSchedulerAddTask(heap_scheduler_t *scheduler, heap_scheduler_action_func_t action, \
void *parameter, heap_scheduler_clean_func_t clean, size_t interval, time_t when)
{
	task_t *task = NULL;
	assert(scheduler); assert(action);
	assert(clean); assert(scheduler->pq);
    assert(TIME(INTERNAL_ERROR) != when);

	task = TaskCreate(action, parameter, clean, interval, when);
	if(SUCCESS != HeapPQEnqueue(scheduler->pq, task) || NULL == task)
	{
		TaskDestroy(task);
		return (UIDGetBad());
	}

	return (TaskGetUID(task));
}
/*****************************************************************************/
int HeapSchedulerRemoveTask(heap_scheduler_t *scheduler, ilrd_uid_t task_uid)
{
	task_t *task = NULL;
	task = TASK(HeapPQErase(scheduler->pq, IsMatch, &task_uid));
	if((heap_pq_t *)task == scheduler->pq)
	{
		return (FAILURE);
	}

	TaskDestroy(task);
	return (SUCCESS);
}
/*****************************************************************************/
int HeapSchedulerRun(heap_scheduler_t *scheduler)
{
	size_t interval = 0;
	task_t *task = NULL;
	int status = CONTINUE;
	time_t task_time = TIME(0);
	time_t now = TIME(INTERNAL_ERROR);
	time_t time_to_sleep = TIME(INTERNAL_ERROR);

	assert(scheduler);
	assert(scheduler->pq);
	while(!HeapPQIsEmpty(scheduler->pq) && STOP != scheduler->stop && !status)
	{
		task = TASK(HeapPQDequeue(scheduler->pq));
		interval = TaskGetInterval(task);
		task_time = TaskGetTime(task);
		now = time(NULL);

		time_to_sleep = MAX(TaskGetTime(task) - now, 0);
		while(0 < time_to_sleep)
		{
			time_to_sleep = sleep(time_to_sleep);
		}
	
		if(SELF_DESTROY == (status = TaskRun(task)))
		{
			HeapSchedulerRemoveTask(scheduler, TaskGetUID(task));
			status = CONTINUE;
		}

		if(interval)
		{
			while(task_time <= time(NULL))
			{
				task_time += interval;
			}

			TaskSetTime(task, task_time);
			if(HeapPQEnqueue(scheduler->pq, task))
			{
				return (INTERNAL_ERROR);
			}
		}
		else
		{
			TaskDestroy(task);
		}
	}

	scheduler->stop = RUN;
	return (status);
}
/*****************************************************************************/
void HeapSchedulerStop(heap_scheduler_t *scheduler)
{
	assert(scheduler);
	scheduler->stop = STOP;
}
/*****************************************************************************/
size_t HeapSchedulerSize(heap_scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	return (HeapPQSize(scheduler->pq));
}
/*****************************************************************************/
int HeapSchedulerIsEmpty(heap_scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	return (HeapPQIsEmpty(scheduler->pq));
}
/*****************************************************************************/
void HeapSchedulerClear(heap_scheduler_t *scheduler)
{
	while(!HeapPQIsEmpty(scheduler->pq))
	{
		TaskDestroy(TASK(HeapPQDequeue(scheduler->pq)));
	}
}
/*****************************************************************************/
static int Priority(void *task2, void *task1)
{
	return ((int)(TaskGetTime(TASK(task2)) - TaskGetTime(TASK(task1))));
}
/*****************************************************************************/
static int IsMatch(void *task, void *task_uid)
{
	return (UIDIsMatch(*(ilrd_uid_t *)task_uid, TaskGetUID(TASK(task))));
}
/*****************************************************************************/
