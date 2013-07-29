/*
 *====================================================
 *	无锁编程 (内存屏障)
 *
 *====================================================
 */
#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define try_lock(lock)   __sync_bool_compare_and_swap(lock, 0, 1)
#define unlock(lock)	*(lock) = 0

long		lock;

void * fun1 (void *arg1)
{
	while (1) {
		if (try_lock (&lock))
			break;
	}
	printf ("[pthread1]  -- start\n");
	sleep (2);
	printf ("[pthread1]  -- end\n");
	unlock (&lock);
	pthread_exit ((void *) NULL);
}

void * fun2 (void *arg1)
{
	while (1) {
		if (try_lock (&lock))
			break;
	}
	printf ("[pthread2]  -- start\n");
	sleep (2);
	printf ("[pthread2]  -- end\n");
	unlock (&lock);
	pthread_exit ((void *) NULL);
}

int main(void)
{

	pthread_t pid1, pid2;
	void *tmp;

	printf ("[main] -- start\n");

	if (pthread_create (&pid1, NULL, fun1, NULL)) {
		perror ("create pthread1 error\n");
		exit (1);
	}
	if (pthread_create (&pid2, NULL, fun2, NULL)) {
		perror ("create pthread2 error\n");
		exit (1);
	}

	if (pthread_join (pid1, &tmp)) {
		perror ("join pthread1 error\n");
		exit (1);
	}

	if (pthread_join (pid2, &tmp)) {
		perror ("join pthread2 error\n");
		exit (1);
	}


	sleep (2);
	printf ("[main] -- end\n");
    return 0;
}
