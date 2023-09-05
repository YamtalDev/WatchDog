#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "wd_unique_identifier.h" /* Including for task_uid creation */

enum status
{
	SUCCESS = 0, FAILURE 
};

typedef struct heap_scheduler heap_scheduler_t;

/*returns zero if succeed and non zero if fails*/
typedef int (*heap_scheduler_action_func_t)(void *parameter);
typedef void (*heap_scheduler_clean_func_t)(void *parameter);

/*****************************************************************************

function: HeapSchedulerCreate

Usage: heap_scheduler_t *heap_scheduler = HeapSchedulerCreate()

Description: The HeapSchedulerCreate function will create an empty heap_scheduler to be 
filed and run. 

Arguments: No arguments needed.
Return value: The function returns a pointer to heap_scheduler_t that allows access
              to the heap_scheduler. If fails returns NULL.

Complexities - time Complexity O(1), space complexity O(1). */

heap_scheduler_t *HeapSchedulerCreate(void);

/*****************************************************************************

function: HeapSchedulerDestroy

Usage: HeapSchedulerDestroy(heap_scheduler)


Description: The HeapSchedulerDestroy will clean and destroys all tasks in it and 
then it will destroy the heap_scheduler itself.

Arguments: Pointer to heap_scheduler_t type.
Return value: no return values.
Complexities - time Complexity O(n), space complexity O(1). */

void HeapSchedulerDestroy(heap_scheduler_t *heap_scheduler);

/*****************************************************************************

function: HeapSchedulerAdd

Usage: ilrd_task_uid_t task_uid = HeapSchedulerAdd(heap_scheduler, action, parameter, clean, interval, when)

Description: Adds a action to the heap_scheduler, parameter to use, clean function if 
requires, time interval to repeat and when to activate the action. 
When an interval equal to zero, task will run only once.
Important point - adding a lot of high priority task could lead to starvation - 
task with low priority might never run.

Arguments: pointer to a heap_scheduler, action function of type int action(void *),
clean function type void clean(void), interval - amount of seconds until next repeat,
when - time to activate.

Return value: Returns the task_uid of the action, if fails returns bad task_uid.
Complexities - time Complexity O(n), space complexity O(1). */

ilrd_uid_t HeapSchedulerAddTask(heap_scheduler_t *heap_scheduler, heap_scheduler_action_func_t action, void *parameter, heap_scheduler_clean_func_t clean, size_t interval, time_t when); 

/*****************************************************************************

function: HeapSchedulerRemove

Usage: HeapSchedulerRemove(heap_scheduler, task_uid)

Description: Removes a action from the heap_scheduler by its task_uid.
Arguments: pointer to a heap_scheduler, task_uid of the task.
Return value: return non zero value if fails, and zero if succeed.
Complexities - time Complexity O(n), space complexity O(1). */

int HeapSchedulerRemoveTask(heap_scheduler_t *heap_scheduler, ilrd_uid_t task_uid);

/*****************************************************************************

function: HeapSchedulerRun

Usage: HeapSchedulerRun(heap_scheduler)

Description: Runs the heap_scheduler. Please notice - only one schedular can run for one proccess.
API can't guarantee the exact time of execution because of delays.
Tasks that late and had to execute before current time will be treated first. 
Tasks like this will first of all run, and the intervals will be set from the time "when" \
that passed in SchedularAddFunction. If tasks have the same "when", then their order is undefined.

Arguments: pointer to a heap_scheduler.

Return value: if fails - return value of the failed action function 
or "-1" if something went wrong in our in a proccess of running. If user wants to
remove task from the heap_scheduler - he could return "-2" in action function to inform us.
That means that action function cannot return -1 if fails. 
If succeed - returns zero. Fail of Run stops the heap_scheduler if a failure is met or if user stops heap_scheduler.
All the task will be scheduled by the tasks "when" parameter. If the time "when" passed, 
the task will be executed by run function when it called according to the order of schedular.

Complexities - undefined. */

int HeapSchedulerRun(heap_scheduler_t *heap_scheduler);

/*****************************************************************************

function: HeapSchedulerStop

Usage: HeapSchedulerStop(heap_scheduler)

Description: Stops the heap_scheduler. In order to stop schedular asynchronous - 
user can add task that In order to stop schedular asynchronous -
user could add task that creates file in the same directory with executable and \
another task that checks if in this file there is a "stop" word. \
If the word been added - Stop function is called.
Arguments: pointer to a heap_scheduler.
Return value: no return values.
Complexities - time Complexity O(1), space complexity O(1). */

void HeapSchedulerStop(heap_scheduler_t *heap_scheduler);

/*****************************************************************************

function: HeapSchedulerSize

Usage: size_t size = HeapSchedulerSize(heap_scheduler)

Description: Counts the number of tasks in the heap_scheduler.
Arguments: pointer to a heap_scheduler.
Return value: returns size_t.
Complexities - time Complexity O(n), space complexity O(1). */

size_t HeapSchedulerSize(heap_scheduler_t *heap_scheduler);

/*****************************************************************************

function: HeapSchedulerIsEmpty

Usage: int answer = HeapSchedulerIsEmpty(heap_scheduler)

Description: Checks if the heap_scheduler is empty from tasks.
Arguments: pointer to a heap_scheduler.
Return value: returns int, non-zero if empty and 0 if not.
Complexities - time Complexity O(1), space complexity O(1). */

int HeapSchedulerIsEmpty(heap_scheduler_t *heap_scheduler);

/*****************************************************************************

function: HeapSchedulerClear

Usage: HeapSchedulerClear(heap_scheduler)

Description: Clear heap_scheduler from tasks.
Arguments: pointer to a heap_scheduler.
Return value: No return values.
Complexities - time Complexity O(n), space complexity O(1). */

void HeapSchedulerClear(heap_scheduler_t *heap_scheduler);


/*****************************************************************************/

#endif /* __SCHEDULER_H__*/