#include <pthread.h>
#include <stdio.h>
#include <unistd.h>



void *thread_function(void *arg)
{
	printf("Hello from thread: %s\n", (char *)arg);
	sleep (2);
	pthread_exit(arg);
}

int main(void)
{
	pthread_t	thread;
	int			result;
	void		*print_char;
	void		*return_char = NULL;

	print_char = "the str from main";
	result = pthread_create(&thread, NULL, thread_function, print_char);
	if (result != 0)
	{
		perror("Thread creation failed\n");
		return 0;
	}
	if(pthread_join(thread, &return_char) != 0)
		printf("join failure\n");
	printf("return value is %s\n",(char *)return_char);
	printf("Hello form the main thread\n");
	return 0;
}
