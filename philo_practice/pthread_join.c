#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_func1(void *arg) {
  int i;
  for (i = 0; i < 10; i++) {
    printf("Thread %ld: %d\n", (long)arg, i);
  }
  pthread_exit((void *)arg);
}

void *thread_func2(void *arg) {
  int i;
  for (i = 0; i < 10; i++) {
    printf("Thread %ld: %d\n", (long)arg, i);
  }
  sleep(2);
  pthread_exit((void *)arg);
}

int main(void) {
  pthread_t thread1, thread2;
  void *retval;
  int result;

  result = pthread_create(&thread1, NULL, thread_func1, (void *)1);
  if (result != 0) {
    perror("Thread creation failed");
    return 1;
  }

  result = pthread_create(&thread2, NULL, thread_func2, (void *)2);
  if (result != 0) {
    perror("Thread creation failed");
    return 1;
  }

  result = pthread_join(thread1, &retval);
  if (result != 0) {
    perror("Thread join failed");
    return 1;
  }
  printf("Thread 1 returned %ld\n", (long)retval);

  result = pthread_join(thread2, &retval);
  if (result != 0) {
    perror("Thread join failed");
    return 1;
  }
  printf("Thread 2 returned %ld\n", (long)retval);

  return 0;
}
