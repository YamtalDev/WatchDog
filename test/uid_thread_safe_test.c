#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include "wd_unique_identifier.h"

#define THREAD_NUM (32)
#define ROUND_NUMBER (100)
ilrd_uid_t array[THREAD_NUM];

void *func(void *input)
{
    int thread_num = *(int *)input;
    array[thread_num] = UIDCreate();
    return NULL;
}

int main(void)
{
    int i = 0, j = 0;
    pthread_t threads[THREAD_NUM];
    int thread_nums[THREAD_NUM];

	for(;j < ROUND_NUMBER; ++j)
	{
		for (i = 0; i < THREAD_NUM; i++)
		{
			thread_nums[i] = i;
			pthread_create(&threads[i], NULL, func, (void *)&thread_nums[i]);
		}

		for (i = 0; i < THREAD_NUM; i++)
		{
			pthread_join(threads[i], NULL);
		}

		for (i = 0; i < (THREAD_NUM - 1); i++)
		{
			assert(array[i].counter != array[i + 1].counter);
		}
	}

    return 0;
}
