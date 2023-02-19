#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;

int main() {
    int status;

    status = pthread_mutex_init(&mutex, NULL);
    if (status != 0) {
        printf("Error initializing mutex.\n");
        return 1;
    }

    // Use the mutex in your program here
	
    status = pthread_mutex_destroy(&mutex);
    if (status != 0) {
        printf("Error destroying mutex.\n");
        return 1;
    }

    return 0;
}
