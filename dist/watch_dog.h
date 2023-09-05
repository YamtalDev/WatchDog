/*=============================================================================

                           Customer Requirements:

===============================================================================

The WatchDog module is required to monitor a code block within a process and 
automatically restart it if terminated. It should provide functions (WDWatch 
and WDUnWatch) to initiate and clean up the monitoring process. The WDWatch 
function should take a time interval and command-line arguments, returning 
status codes for success, failure, thread errors, and internal failures. 
The WDUnWatch function should gracefully terminate the monitoring thread, 
shut down the process, and handle cleanup status codes. 

===============================================================================

                           WATCH_DOG Functionalities:

===============================================================================

1.) Function: WDWatch - Watches a code block in a process.

   Usage: status_t status = WDWatch(interval, argv)

   Description:

   The WDWatch function is responsible for monitoring a specific code block within 
   a process. It continuously checks whether the process is still running. If the 
   process terminates, the function restarts the process; otherwise, it takes no 
   action.

   Arguments:

   - interval: The time interval (in seconds) at which the process is inspected.
   - argv[]: An array of command-line arguments that must be passed to the function. 
     If this function is used outside the main function, the command-line arguments 
     should be passed as arguments to the user-defined function.

   Return value:

   - WD_SUCCESS on success: The process is being monitored.
   - WD_FAILURE on failure: The process could not be monitored.
   - WD_THREAD_FAILURE if the thread fails: The monitoring thread encountered an error.
   - WD_INTERNAL_FAILURE on internal allocation failure or the creation of internal functions: 
     Internal functions or memory allocation failed.

   Space complexity:

   - Worst case: O(1)
   - Average case: O(1)

*******************************************************************************

2.) Function: WDUnWatch - UnWatches a code block in a process.

   Usage: status_t status = WDUnWatch()

   Description:

   The WDUnWatch function is used to clean up the resources associated with the 
   code block monitoring. It terminates the monitoring thread, shuts down the 
   WatchDog process, and releases any other related resources.

   Arguments: None

   Return value:

   - WD_SUCCESS on success: The cleanup process was successful.
   - WD_FAILURE on failure: The cleanup process encountered an error.
   - WD_THREAD_FAILURE if the thread fails: The cleanup thread encountered an error.
   - WD_INTERNAL_FAILURE on internal allocation failure or cleanup of internal functions:
     Internal functions or memory allocation failed during the cleanup process.

==============================================================================*/

#ifndef __WATCH_DOG_H__
#define __WATCH_DOG_H__

typedef enum wd_status
{
    WD_SUCCESS = 0, WD_FAILURE, WD_THREAD_FAILURE, WD_INTERNAL_FAILURE

} wd_status_t;

wd_status_t WDWatch(time_t interval, char *argv[]);

wd_status_t WDUnWatch(void);

#endif /* __WATCH_DOG_H__ */