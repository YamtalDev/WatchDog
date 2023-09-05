/******************************************************************************

    Writer: Tal Aharon

    Reviewer: Yotam Itzhaki.

    Date: 11.06.2023

*******************************************************************************

                          Description:

  The given C program implements a watchdog mechanism. It uses atomic integers 
  to manage the internal state of the process and the watchdog. Signal handler 
  functions are defined to handle specific signals. The program sets up communication, 
  defines tasks to stop the watchdog and revive the user process, and configures 
  the watchdog scheduler. Finally, it runs the scheduler and cleans up resources, 
  returning status values to indicate the success or failure of the execution.

******************************************************************************/
#define _POSIX_SOURCE
#include "wd_internal_lib.h" /* Internal API */
/*****************************************************************************/
static atomic_int g9K3h7L5_process_state = RESTART;
static atomic_int x4M6j9N2_internal_state = RUNNING;
/*****************************************************************************/
static void SigHandler1(int);
static void SigHandler2(int);
static int StopWatchDog(void *);
static int ReviveUserProcess(void *);
static wd_status_t SetupWDCommunication(void);
/*****************************************************************************/
int main(int argc, char *argv[])
{
    heap_scheduler_action_func_t tasks[3] = {NULL};
    wd_object_t *wd_object = SetWDObject(argv, getppid());
    if(NULL == wd_object)
        return (WD_INTERNAL_FAILURE);

    if(WD_SUCCESS != SetupWDCommunication())
        return (WD_FAILURE);

    tasks[0] = StopWatchDog;
    tasks[1] = ReviveUserProcess;
    if(WD_SUCCESS != SetUpWDScheduler(wd_object, GetInterval(), tasks, 2))
        return (WD_INTERNAL_FAILURE);

    IGNORE(argc);
    kill(getpid(), SIGSTOP);
    HeapSchedulerRun(wd_object->scheduler);
    WDCleanUp(wd_object);
    return (WD_SUCCESS);
}
/*****************************************************************************/
static wd_status_t SetupWDCommunication(void)
{
    struct sigaction handler1 = {0};
    struct sigaction handler2 = {0};
    handler1.sa_flags = 0;
    handler2.sa_flags = 0;
    handler1.sa_handler = SigHandler1;
    handler2.sa_handler = SigHandler2;
    if(sigaction(SIGUSR1, &handler1, NULL))
        return (WD_INTERNAL_FAILURE);

    if(sigaction(SIGUSR2, &handler2, NULL))
        return (WD_INTERNAL_FAILURE);

    return (WD_SUCCESS);
}
/*****************************************************************************/
static void SigHandler1(int sig)
{
    g9K3h7L5_process_state = RUNNING;
    IGNORE(sig);
}
/*****************************************************************************/
static void SigHandler2(int sig)
{
    x4M6j9N2_internal_state = STOP;
    IGNORE(sig);
}
/*****************************************************************************/
static int StopWatchDog(void *object)
{
    if(STOP == x4M6j9N2_internal_state)
    {
        HeapSchedulerStop(((wd_object_t *)object)->scheduler);
        return (TASK_FAILURE);
    }

    IGNORE(object);
    return (TASK_SUCCESS);
}
/*****************************************************************************/
static int ReviveUserProcess(void *object)
{
    wd_object_t *wd_object = (wd_object_t *)object;
    if(g9K3h7L5_process_state == RESTART && x4M6j9N2_internal_state == RUNNING)
    {
        wd_object->pid = fork();
        if(-1 == wd_object->pid)
        {
            return (TASK_FAILURE);
        }
        else if(0 == wd_object->pid)
        {
            if(execvp(wd_object->argv[0], wd_object->argv))
            {
                return (TASK_FAILURE);
            }
            

            return (TASK_FAILURE);
        }
        else
        {
            return (TASK_FAILURE);
        }
    }

    IGNORE(object);
    g9K3h7L5_process_state = RESTART;
    return (TASK_SUCCESS);
}
/*****************************************************************************/
