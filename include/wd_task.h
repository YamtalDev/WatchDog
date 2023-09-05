#ifndef __TASK_H__
#define __TASK_H__

#include "wd_unique_identifier.h"

typedef struct task task_t;

/*returns zero if succeed and non zero if fails*/
typedef int (*task_action_func_t)(void *parameter);
typedef void (*task_clean_func_t)(void *parameter);

/*****************************************************************************

function: TaskCreate

Usage: task_t *task = TaskCreate(action, clean, interval, when)

Description: creates a task.
Arguments: function type int action(void *), function type void clean(void *), 
           interval in seconds, time to run.

Return value: Return pointer to the task or NULL when failed.
Complexities - time Complexity O(1), space complexity O(1). */

task_t *TaskCreate(task_action_func_t action, void *parameter, task_clean_func_t clean, size_t interval, time_t when);

/*****************************************************************************

function: TaskDestroy

Usage: TaskDestroy(task)

Description: destroys the task.
Arguments: pointer to task.
Return value: no return value.
Complexities - time Complexity O(1), space complexity O(1). */

void TaskDestroy(task_t *task);

/*****************************************************************************

function: TaskRun

Usage: int status = TaskRun(task)

Description: runs the task.
Arguments: pointer to task.
Return value: return value of the action function if fails.
Complexities - time Complexity O(1), space complexity O(1). */

int TaskRun(task_t *task);

/*****************************************************************************

function: TaskGetTime

Usage: time_t when = TaskGetTime(task)

Description: gets the time of the task.
Arguments: pointer to task.
Return value: if succeeds - return time on which task will start or -1 if fails.
Complexities - time Complexity O(1), space complexity O(1). */

time_t TaskGetTime(task_t *task);

/*****************************************************************************

function: TaskSetTime

Usage: TaskSetTime(task)

Description: sets the time of the task.
Arguments: pointer to task, time_t when to run task next time.
Return value: no return value.
Complexities - time Complexity O(1), space complexity O(1). */

void TaskSetTime(task_t *task, time_t when);

/*****************************************************************************

function: TaskGetInterval

Usage: size_t interval = TaskGetInterval(task)

Description: gets the interval of the task.
Arguments: pointer to task.
Return value: size_t interval.
Complexities - time Complexity O(1), space complexity O(1). */

size_t TaskGetInterval(task_t *task);

/*****************************************************************************

function: TaskSetInterval

Usage: TaskSetInterval(task)

Description: set the interval of the task.
Arguments: pointer to task, size_t interval (in seconds).
Return value: no return value.
Complexities - time Complexity O(1), space complexity O(1). */

void TaskSetInterval(task_t *task, size_t interval);

/*****************************************************************************

function: TaskGetUID

Usage: ilrd_uid_t task_uid = TaskGetUID(task)

Description: get the uid of task.
Arguments: pointer to task.
Return value: if succeed - ilrd_uid_t (task_uid) of task, and bad uid if fails.
Complexities - time Complexity O(1), space complexity O(1). */

ilrd_uid_t TaskGetUID(task_t *task);

/*****************************************************************************/

#endif /* __TASK_H__*/
