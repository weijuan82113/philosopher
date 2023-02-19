/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phili.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:54:15 by wchen             #+#    #+#             */
/*   Updated: 2023/02/18 00:29:17 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t		my_mutex;

void *thread_func(void *arg)
{
	if (((int *)arg)[1] % 2 == 1)
		usleep(200);
	else
	{
		pthread_mutex_lock(&my_mutex);
		printf("%d %d has taken a fork\n", ((int *)arg)[0], ((int *)arg)[1]);
		printf("%d %d is eating\n", ((int *)arg)[0], ((int *)arg)[1]);
		usleep(500);

		pthread_mutex_unlock(&my_mutex);
	}

	return NULL;
}

int main(void)
{
	pthread_t			*thread;
	struct timeval		tv;
	int					*arg;
	int					i;

	if (pthread_mutex_init(&my_mutex, NULL) != 0)
	{
		printf("error occuring in pthread_mutex_init\n");
		return (1);
	}
	thread = malloc(sizeof(pthread_t) * (5));
	if (!thread)
	{
		printf("error occuring in malloc\n");
		return (1);
	}
	arg = malloc(sizeof(int) * (2));
	if (!arg)
	{
		printf("error occuring in malloc\n");
		return (1);
	}
	// if (gettimeofday(&tv, NULL) != 0)
	// 	printf("error ocurring in get time\n");
	i = 0;
	while (1)
	{
		while (i < 5)
		{
		if (gettimeofday(&tv, NULL) != 0)
			printf("error ocurring in get time\n");
		//printf("Seconds: %ld\n Microseconds: %d\n", tv.tv_sec, tv.tv_usec);
		arg[0] = tv.tv_usec;
		arg[1] = i;

		if (pthread_create(&thread[i], NULL, thread_func, (void *)arg) != 0)
		{
			printf("error occuring in pthread_create\n");
			return (1);
		}
		if (gettimeofday(&tv, NULL) != 0)
			printf("error ocurring in get time\n");
		arg[0] = tv.tv_usec;
		printf("%d %d has taken a fork\n", arg[0], arg[1]);
		if (pthread_join(thread[i], NULL) != 0)
			printf("error occuring in pthread_join\n");
		i ++;
		}
		i = 0;
	}
	if (pthread_mutex_destroy(&my_mutex) != 0)
	{
		printf("error occuring in pthread_mutex_destory\n");
		return (1);
	}
	printf("Success!\n");
}

