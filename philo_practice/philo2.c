/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:54:15 by wchen             #+#    #+#             */
/*   Updated: 2023/02/19 22:41:33 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

typedef struct s_philo
{
	pthread_t			*philo;
	pthread_mutex_t		*fork_mutex;
	struct timeval 		start_time;
	struct timeval		time;
	int					philo_num;
	int					index;
}	t_philo;

void *thread_func(void *arg)
{
	int		index;
	errno;
	printf("test\n");fflush(stdout);
	index =((t_philo*)arg)->index;
	printf("index1 is %d\n", index);fflush(stdout);
	if (index % 2 == 1)
		usleep(500);
	if (pthread_mutex_lock(&((t_philo*)arg)->fork_mutex[index]) != 0)
	{
		printf("error occuring in mutex_lock\n");
		printf("errno : %d\n", errno);
		if (errno == EAGAIN)
		return NULL;
	}
	if (gettimeofday(&((t_philo*)arg)->time, NULL) != 0)
		printf("error ocurring in get time\n");
	printf("%d %d get right fork\n", ((t_philo*)arg)->time.tv_usec, index);fflush(stdout);
	printf("philo_num : %d\n", ((t_philo*)arg)->philo_num);fflush(stdout);
	printf("index2 is %d\n", index + 1);fflush(stdout);
	printf("left index : %d\n", ((index + 1) % (((t_philo*)arg)->philo_num)));fflush(stdout);
	if (pthread_mutex_lock(&(((t_philo*)arg)->fork_mutex[(index + 1) % ((t_philo*)arg)->philo_num])) != 0)
	{
		printf("error occuring in mutex_lock\n");
		return NULL;
	}
	if (gettimeofday(&((t_philo*)arg)->time, NULL) != 0)
		printf("error ocurring in get time\n");
	printf("%d %d get left fork\n", ((t_philo*)arg)->time.tv_usec, index);
	printf("%d %d is eating\n", ((t_philo*)arg)->time.tv_usec, index);
	usleep(500);
	pthread_mutex_unlock(&((t_philo*)arg)->fork_mutex[index]);
	pthread_mutex_unlock(&((t_philo*)arg)->fork_mutex[(index + 1) % ((t_philo*)arg)->philo_num]);
	pthread_exit(NULL);
}

t_philo *philo_init(int argc)
{
	t_philo	*p_info;
	int		i;

	p_info = malloc(sizeof(t_philo));
	if (!p_info)
	{
		printf("error occuring in malloc_t_philo\n");
		return NULL;
	}
	p_info->philo_num = argc;
	p_info->fork_mutex = malloc(sizeof(pthread_mutex_t) * (argc));
	if (!p_info->fork_mutex)
	{
		printf("error occuring in malloc_mutex\n");
		return NULL;
	}
	i = 0;
	while (i < argc)
	{
		if (pthread_mutex_init(&p_info->fork_mutex[i], NULL) != 0)
		{
			printf("error occuring in pthread_mutex_init\n");
			return NULL;
		}
		i ++;
	}
	p_info->philo = malloc(sizeof(pthread_t) * (argc));
	if (!p_info->philo)
	{
		printf("error occuring in malloc_pthread\n");
		return NULL;
	}
	if (gettimeofday(&p_info->start_time, NULL) != 0)
	{
		printf("error ocurring in get time\n");
		return NULL;
	}
	return (p_info);
}

int main(int argc, char **argv)
{
	t_philo		*philo_info;
	int			i;

	(void)argv;
	printf("argc: %d\n", argc);
	philo_info = philo_init(argc);
	i = 0;
	while (i < argc)
	{
		printf("i : %d\n", i);
		philo_info->index = i;
		if (pthread_create(&(philo_info->philo[i]), NULL, thread_func, (void *)philo_info) != 0)
		{
			printf("error occuring in pthread_create\n");
			return (1);
		}
		i ++;
	}
	i = 0;
	while (i < argc)
	{
		if (pthread_join(philo_info->philo[i], NULL) != 0)
		{
			printf("error occuring in pthread_detach\n");
			return (1);
		}
		pthread_mutex_destroy(&(philo_info->fork_mutex[i]));
		i ++;
	}
	printf("Success!\n");
	return (0);
}

