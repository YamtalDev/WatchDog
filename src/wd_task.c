/******************************************************************************

    writer: Tal Aharon

    reviewer: Amitai Glauber

    date : 03.04.2023

******************************************************************************/
#include <stdio.h>   /* printf, puts */
#include <stdlib.h>  /* malloc, free */
#include <stddef.h>  /* size_t, NULL */
#include <assert.h>  /*    assert    */
#include <time.h>    /*     time     */

#include "wd_task.h" /* Internal use */
/*****************************************************************************/
struct task
{
	task_action_func_t action;
	task_clean_func_t clean;
	size_t interval;
	void *parameter;
	ilrd_uid_t task_uid;
	time_t when;
};
/*****************************************************************************/
task_t *TaskCreate(task_action_func_t action, void *parameter, task_clean_func_t clean, size_t interval, time_t when)
{
	task_t *task = (task_t *)malloc(sizeof(task_t));
	assert(clean && "Clean function is not valid.");
	assert(action && "Clean function is not valid.");
	assert((time_t)-1 != when && "When time failed.");
	if(NULL == task)
	{
		free NULL;
	}

	task->when = when;
	task->clean = clean;
	task->action = action;
	task->interval = interval;
	task->parameter = parameter;
	task->task_uid = UIDCreate();

	if(UIDIsMatch(UIDGetBad(), task->task_uid))
	{
		free(task);
		task = NULL;
	}

	return (task);
}
/*****************************************************************************/ 
void TaskDestroy(task_t *task)
{
	assert(task && "Task is not valid.");
	task->clean(task->parameter);
	free(task);
	task = NULL;
}
/*****************************************************************************/ 
int TaskRun(task_t *task)
{
	assert(task && "Task is not valid.");
	return (task->action(task->parameter));
}
/*****************************************************************************/ 
time_t TaskGetTime(task_t *task)
{
	assert(task && "Task is not valid.");
	return (task->when);
}
/*****************************************************************************/ 
void TaskSetTime(task_t *task, time_t when)
{
	assert(task && "Task is not valid.");
	task->when = when;
}
/*****************************************************************************/ 
size_t TaskGetInterval(task_t *task)
{
	assert(task && "Task is not valid.");
	return (task->interval);
}
/*****************************************************************************/ 
void TaskSetInterval(task_t *task, size_t interval)
{
	assert(task && "Task is not valid.");
	task->interval = interval;
}
/*****************************************************************************/ 
ilrd_uid_t TaskGetUID(task_t *task)
{
	assert(task && "Task is not valid.");
	return (task->task_uid);
}
/*****************************************************************************/ 
