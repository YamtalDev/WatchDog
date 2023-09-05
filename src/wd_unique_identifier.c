/******************************************************************************

    writer: Tal Aharon

    reviewer: Ishai Zilberman

    date : 02.04.2023

******************************************************************************/
#include <time.h>                 /* time         */
#include <unistd.h>               /* getpid       */

#include "wd_unique_identifier.h" /* Internal API */
/*****************************************************************************/
static atomic_size_t uid_counter = 0;
/*****************************************************************************/
ilrd_uid_t UIDCreate(void)
{
    time_t now = 0;
    ilrd_uid_t uid = {0};
    if((time_t)-1 == time(&now))
    {
        return UIDGetBad();
    }

    uid.counter = atomic_fetch_add_explicit(&uid_counter, 1, memory_order_relaxed);
    uid.time_stamp = now;
    uid.pid = getpid();
    return (uid);
}
/*****************************************************************************/ 
ilrd_uid_t UIDGetBad(void)
{
    ilrd_uid_t bad = {0};
    bad.time_stamp = 0;
    bad.counter = 0;
    bad.pid = 0;
    return (bad);
}
/*****************************************************************************/ 
int UIDIsMatch(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
    int pid_match = uid1.pid == uid2.pid;
    int counter_match =uid1.counter == uid2.counter;
    int time_stamp_match = uid1.time_stamp == uid2.time_stamp;
    return (time_stamp_match && counter_match && pid_match);
}
/*****************************************************************************/ 
