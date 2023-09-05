/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Yotam Itzhaki.

    Date: 11.06.2023

*******************************************************************************

                          Description:

  The provided C program implements a watchdog functionality using threads. It 
  includes functions for stopping the watchdog, sending signals, reviving the 
  watchdog process, and checking if the watchdog is down. A separate thread is 
  created to run the watchdog routine, which includes starting the watchdog 
  process, running the scheduler, and performing cleanup. The program provides 
  functions to watch and un watch the watchdog, and handles the internal state 
  using atomic integers.

******************************************************************************/
#define _POSIX_SOURCE

#include <pthread.h>         /* pthread_create, pthread_join */
#include "wd_internal_lib.h" /* Internal API                 */
/*****************************************************************************/
static void *WDRoutine(void *);
static int StopWatchDog(void *);
static int WDSendSignal(void *);
static int WatchDogIsDown(pid_t);
static int ReviveWatchDog(void *);
static wd_status_t SetWDPath(wd_object_t *);
/*****************************************************************************/
static pthread_t s3xW7rPd9Y3_thread = (pthread_t)0;
static atomic_int z2Q8m5Gp7V9_internal_state = RUNNING;
/*****************************************************************************/
wd_status_t WDWatch(time_t interval, char *argv[])
{
    wd_object_t *wd_object = NULL;
    heap_scheduler_action_func_t tasks[4] = {NULL};
    if(interval <= 1)
        return (WD_FAILURE);

    if(WD_SUCCESS != SetInterval(interval))
        return (WD_FAILURE);

    wd_object = SetWDObject(argv, (pid_t)-1);
    if(NULL == wd_object)
        return (WD_INTERNAL_FAILURE);

    if(WD_SUCCESS != SetWDPath(wd_object))
    {
        WDCleanUp(wd_object);
        return (WD_FAILURE);
    }

    if(WD_SUCCESS != InitWatchDog(wd_object))
    {
        WDCleanUp(wd_object);
        return (WD_INTERNAL_FAILURE);
    }

    tasks[0] = WDSendSignal;
    tasks[1] = StopWatchDog;
    tasks[2] = ReviveWatchDog;
    if(WD_SUCCESS != SetUpWDScheduler(wd_object, interval, tasks, 3))
    {
        WDCleanUp(wd_object);
        return (WD_INTERNAL_FAILURE);
    }

    if(pthread_create(&s3xW7rPd9Y3_thread, NULL, WDRoutine, (void *)wd_object))
    {
        WDCleanUp(wd_object);
        return (WD_THREAD_FAILURE);
    }

    
    return (WD_SUCCESS);
}
/*****************************************************************************/ 
wd_status_t WDUnWatch(void)
{
    z2Q8m5Gp7V9_internal_state = STOP;
    if(pthread_join(s3xW7rPd9Y3_thread, NULL))
        return (WD_THREAD_FAILURE);

    return (WD_SUCCESS);
}
/*****************************************************************************/
static int StopWatchDog(void *object)
{
    wd_object_t *wd_object = (wd_object_t *)object;
    if(STOP == z2Q8m5Gp7V9_internal_state)
    {
        kill(wd_object->pid, SIGUSR2);
        HeapSchedulerStop(wd_object->scheduler);
        waitpid(wd_object->pid, NULL, 0);
    }

    return (TASK_SUCCESS);
}
/*****************************************************************************/
static int WDSendSignal(void *arg)
{
    kill(((wd_object_t *)arg)->pid, SIGUSR1);
    return (TASK_SUCCESS);
}
/*****************************************************************************/
static void *WDRoutine(void *arg)
{
    int status = 0;
    char **argv = NULL;
    wd_object_t *wd_object = (wd_object_t *)arg;

    argv = wd_object->argv;
    kill(wd_object->pid, SIGCONT);
    status = HeapSchedulerRun(wd_object->scheduler);
    if(TASK_SUCCESS != status)
    {
        kill(wd_object->pid, SIGUSR2);
        waitpid(wd_object->pid, NULL, 0);
        WDCleanUp(wd_object);
        pthread_detach(&s3xW7rPd9Y3_thread);
        WDWatch(GetInterval(), argv);
    }

    WDCleanUp(wd_object);
    return (NULL);
}
/*****************************************************************************/
static int ReviveWatchDog(void *object)
{
    wd_object_t *wd_object = (wd_object_t *)object;
    if(WatchDogIsDown(wd_object->pid))
    {
        if(WD_SUCCESS != InitWatchDog(wd_object))
            return (TASK_FAILURE);

        kill(wd_object->pid, SIGCONT);
    }

    return (TASK_SUCCESS);
}
/*****************************************************************************/
static int WatchDogIsDown(pid_t pid)
{
    int watchdog = -1;
    do
    {
        watchdog = waitpid(pid, NULL, WNOHANG);
    } while(-1 == watchdog);
    return (watchdog);
}
/*****************************************************************************/
static wd_status_t SetWDPath(wd_object_t *wd_object)
{
    char *watchdog_path = (char *)malloc(PATH_MAX);
    if(NULL == watchdog_path)
        return (WD_INTERNAL_FAILURE);

    if(NULL == getcwd(watchdog_path, PATH_MAX))
    {
        free(watchdog_path);
        return (WD_FAILURE);
    }

    strcat(watchdog_path,"/dist/watchdog.out");
    wd_object->wd_path = watchdog_path;
    return (WD_SUCCESS);
}
/*****************************************************************************/
