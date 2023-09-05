/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Yotam Itzhaki.

    Date: 11.06.2023

******************************************************************************/
#define _POSIX_C_SOURCE 200112L

#include "wd_heap_scheduler.h" /* Internal API */
#include "wd_internal_lib.h"   /* Internal API */
/*****************************************************************************/
wd_object_t *SetWDObject(char **argv, pid_t pid)
{
    wd_object_t *wd_object = (wd_object_t *)malloc(sizeof(wd_object_t));
    if(NULL == wd_object)
        return (NULL);

    wd_object->pid = pid;
    wd_object->argv = argv;
    wd_object->scheduler = HeapSchedulerCreate();
    if(NULL == wd_object->scheduler)
    {
        free(wd_object);
        return (NULL);
    }

    return (wd_object);
}
/*****************************************************************************/
wd_status_t SetUpWDScheduler
(wd_object_t *wd_object, time_t interval, heap_scheduler_action_func_t task[], size_t functions_num)
{
    size_t rate = 1;
    int uid_status = 0;
    size_t i = 0, j = 0;
    time_t now = time(NULL);
    ilrd_uid_t check = UIDGetBad();
    if(1 <= ((size_t)interval / POLLING_RATE))
    {
        i = POLLING_RATE - 1;
        rate = (size_t)interval / POLLING_RATE;
    }

    for(; i < POLLING_RATE; ++i)
    {
        for(j = 0; j < (functions_num - 1); ++j)
        {
            uid_status += UIDIsMatch(check, HeapSchedulerAddTask \
            (wd_object->scheduler, task[j], (void *)wd_object, \
            CleanUpTask, rate, now + (time_t)i));
        }
    }

    uid_status += UIDIsMatch(check, HeapSchedulerAddTask(wd_object->scheduler, \
    task[functions_num - 1], (void *)wd_object, CleanUpTask, (size_t)interval, \
    now + interval));

    if(0 != uid_status)
        return WD_INTERNAL_FAILURE;

    return (WD_SUCCESS);
}
/*****************************************************************************/
wd_status_t InitWatchDog(wd_object_t *wd_object)
{
    int status = 0;
    wd_object->pid = fork();
    if(-1 == wd_object->pid)
    {
        return (WD_INTERNAL_FAILURE);
    }
    else if(0 == wd_object->pid)
    {
        if(execvp(wd_object->wd_path, wd_object->argv))
        {
            return (WD_INTERNAL_FAILURE);
        }

        return (WD_INTERNAL_FAILURE);
    }
    else
    {
        while(-1 == waitpid(wd_object->pid, &status, WUNTRACED));
        if(!WIFSTOPPED(status))
        {
            return ((wd_status_t)status);
        }
    }

    return (WD_SUCCESS);
}
/*****************************************************************************/
void CleanUpTask(void *object)
{
    IGNORE(object);
}
/*****************************************************************************/
void WDCleanUp(wd_object_t *wd_object)
{
    HeapSchedulerDestroy(wd_object->scheduler);
    free(wd_object->wd_path);
    free(wd_object);
}
/*****************************************************************************/
time_t GetInterval(void)
{
    char *user_interval = getenv("WD_USER_INTERVAL");
    if(NULL == user_interval)
    {
        return (1);
    }

    return ((time_t)atol(user_interval));
}
/*****************************************************************************/
wd_status_t SetInterval(time_t interval)
{
    char env_buffer[sizeof(long int) * CHAR_BIT] = {0};
    sprintf(env_buffer, "%ld", (long int)interval);
    if(setenv("WD_USER_INTERVAL", env_buffer, 1))
    {
        return (WD_FAILURE);
    }

    return (WD_SUCCESS);
}
/*****************************************************************************/
