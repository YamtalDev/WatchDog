/******************************************************************************

    Writer: Tal Aharon

    Date: 11.06.2023

******************************************************************************/
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h> 
#include <stdio.h>

#include "watch_dog.h" /* Internal API */
#define IGNORE(X) ((void) X)
/*****************************************************************************/
void WDTest(char *args[]);
/*****************************************************************************/
int main(int argc, char *argv[])
{
    WDTest(argv);
    IGNORE(argc);
    puts("\nWDTest() : passed.");
    return (0);
}
/*****************************************************************************/
void WDTest(char *args[])
{
    int n = 30;
    time_t interval = 5;
    assert(WD_SUCCESS ==  WDWatch(interval, args));
    while(n)
    {
        sleep(1);
        --n;
    }

/*     kill(getpid(), SIGINT); */
    assert(WD_SUCCESS == WDUnWatch());
}
/*****************************************************************************/
