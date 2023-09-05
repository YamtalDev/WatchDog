#ifndef __WD_INTERNAL_LIB_H__
#define __WD_INTERNAL_LIB_H__

#include <sys/types.h> /* pid_t                                                           */
#include <sys/wait.h>  /* waitpid                                                         */
#include <string.h>    /* strlen, strcat                                                  */
#include <limits.h>    /* CHAR_BIT, PATH_MAX                                              */
#include <stdlib.h>    /* malloc, free, setenv, getenv                                    */
#include <unistd.h>    /* fork, execvp, getpid, getppid, getcwd                           */
#include <stdio.h>     /* sprintf, BUFSIZ, snprintf, popen, fgetc, pclose                 */
#include <signal.h>    /* SIGUSR1, SIGUSR2, SIGCONT, SIGSTOP, sigaction, kill, atomic_int */

#define POLLING_RATE (8)
#define IGNORE(X) ((void) X)
#include "watch_dog.h"          /* Internal API */
#include "wd_heap_scheduler.h"  /* Internal API */

enum states
{
    TASK_SUCCESS = 0,
    TASK_FAILURE,
    RUNNING,
    RESTART,
    STOP
};

typedef struct wd_object
{
    heap_scheduler_t *scheduler;
    char *wd_path;
    char **argv;
    pid_t pid;

} wd_object_t;

/******************************************************************************

  The `SetUpWDScheduler` function sets up the watchdog scheduler by adding tasks 
  with specified intervals to the scheduler. It returns the status of the setup 
  operation (`WD_SUCCESS` or `WD_INTERNAL_FAILURE`) in a `wd_status_t` variable.

******************************************************************************/

wd_status_t SetUpWDScheduler(wd_object_t *, time_t, heap_scheduler_action_func_t task[], size_t);

/******************************************************************************

  The `SetWDObject` function creates and initializes a watchdog object. It 
  allocates memory for the object, sets the process ID and command-line arguments, 
  and creates a scheduler. It returns the initialized watchdog object or `NULL` 
  if an error occurs during memory allocation or scheduler creation.

******************************************************************************/

wd_object_t *SetWDObject(char **, pid_t);

/******************************************************************************

  The InitWatchDog function initializes the watchdog by setting the watchdog path, 
  forking a child process, and executing the watchdog program. It returns the status 
  of the initialization operation (WD_SUCCESS, WD_FAILURE, or WD_INTERNAL_FAILURE) 
  in a wd_status_t variable.

******************************************************************************/

wd_status_t InitWatchDog(wd_object_t *);

/******************************************************************************

  The `WDCleanUp` function Destroys the scheduler and free's 
  the wd_object structure.

******************************************************************************/

void WDCleanUp(wd_object_t *);

/******************************************************************************

  The GetInterval function retrieves the user-defined interval from the environment 
  variable "WD_USER_INTERVAL" and returns it as a time_t value. If the environment 
  variable is not set, it returns a default value of 1.

******************************************************************************/

time_t GetInterval(void);

/******************************************************************************

  The CleanUpTask function is a clean up task for the scheduler that do nothing.

******************************************************************************/

void CleanUpTask(void *);

/******************************************************************************

  The SetInterval function sets the user-defined interval by converting it to a 
  string and storing it in the environment variable "WD_USER_INTERVAL", returning 
  WD_FAILURE on failure and WD_SUCCESS on success.

******************************************************************************/

wd_status_t SetInterval(time_t);

#endif /* WD_INTERNAL_LIB_H__ */
