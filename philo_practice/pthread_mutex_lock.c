#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t my_mutex;
int shared_resource = 0;

void *thread_func(void *arg) {
  int i;

(void) arg;
  for (i = 0; i < 50; i++) {
    pthread_mutex_lock(&my_mutex);
    shared_resource++;
    pthread_mutex_unlock(&my_mutex);
    //sleep(1);
  }
  pthread_mutex_lock(&my_mutex);
  sleep(5);
  pthread_mutex_unlock(&my_mutex);
  return NULL;
}

int main(void) {
  pthread_t thread1, thread2;
  int result;

  result = pthread_mutex_init(&my_mutex, NULL);
  if (result != 0) {
    perror("Mutex initialization failed");
    return 1;
  }

  result = pthread_create(&thread1, NULL, thread_func, NULL);
  if (result != 0) {
    perror("Thread creation failed");
    return 1;
  }

  result = pthread_create(&thread2, NULL, thread_func, NULL);
  if (result != 0) {
    perror("Thread creation failed");
    return 1;
  }
  sleep(3);
  printf("wait shared_resource : %d\n", shared_resource);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Final value of shared resource: %d\n", shared_resource);

  pthread_mutex_destroy(&my_mutex);
  return 0;
}
