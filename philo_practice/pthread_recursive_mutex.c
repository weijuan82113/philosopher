#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


pthread_mutex_t mutex;
static int shared_resource = 0;

void *thread_func(void *arg) {
    int status;

    status = pthread_mutex_lock(&mutex);
    if (status != 0) {
        printf("Error locking mutex in thread.\n");
        return NULL;
    }
    shared_resource ++;
    printf("Thread%d has acquired the lock.\n", *(int *)arg);
    status = pthread_mutex_lock(&mutex);
    if (status != 0) {
        printf("Error locking mutex in thread.\n");
        return NULL;
    }
    shared_resource ++;
    printf("Thread%d has acquired the lock again.\n", *(int *)arg);

    status = pthread_mutex_unlock(&mutex);
    if (status != 0) {
        printf("Error unlocking mutex in thread.\n");
        return NULL;
    }

    printf("Thread has released the lock.\n");

    status = pthread_mutex_unlock(&mutex);
    if (status != 0) {
        printf("Error unlocking mutex in thread.\n");
        return NULL;
    }

    printf("Thread has released the lock again.\n");

    return NULL;
}

int main() {
    int status;
    pthread_t thread[2];
    pthread_mutexattr_t attr;
    int *arg1;
    int *arg2;

    status = pthread_mutexattr_init(&attr);
    if (status != 0)
    {
        printf("Error initializing mutex attribure.\n");
        return 1;
    }
    status = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    if (status != 0 )
    {
        printf("Error setting mutex type to recursive.\n");
        return 1;
    }
    status = pthread_mutex_init(&mutex, &attr);
    if (status != 0) {
        printf("Error initializing mutex.\n");
        return 1;
    }
    arg1 = malloc(sizeof(int));
    *arg1 = 1;
    status = pthread_create(&thread[0], NULL, thread_func, (void *)arg1);
    if (status != 0) {
        printf("Error creating thread.\n");
        return 1;
    }
    arg2 = malloc(sizeof(int));
    *arg2 = 2;
    status = pthread_create(&thread[1], NULL, thread_func, (void *)arg2);
    if (status != 0) {
        printf("Error creating thread.\n");
        return 1;
    }
    status = pthread_join(thread[0], NULL);
    if (status != 0) {
        printf("Error joining thread.\n");
        return 1;
    }
    status = pthread_join(thread[1], NULL);
    if (status != 0) {
        printf("Error joining thread.\n");
        return 1;
    }
    printf("the finall shared_resource : %d\n", shared_resource);
    status = pthread_mutex_destroy(&mutex);
    if (status != 0) {
        printf("Error destroying mutex.\n");
        return 1;
    }
    free (arg1);
    free (arg2);
    return 0;
}
