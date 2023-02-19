/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:54:15 by wchen             #+#    #+#             */
/*   Updated: 2023/02/19 22:32:14 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../utils/includes/libft.h"

typedef struct s_p_info
{
	pthread_mutex_t		*fork_mutex;
	long long			philo_num;
}	t_p_info;


typedef struct s_philo
{
	long long			index;
	pthread_t			*p_thread;
	t_p_info			*p_info;
	struct timeval 		*last_time_eat;
	struct timeval		*now;
}	t_philo;

void *thread_func(void *arg)
{
	long long	index;
	t_philo		*philo;
	errno;

	philo = (t_philo*)arg;
	index = philo->index;
	printf("index1 is %lld\n", index);fflush(stdout);
	printf("test segfault1\n");
	if (index % 2 == 1)
		usleep(500);
	printf("test segfault2\n");
	if (pthread_mutex_lock(&((philo->p_info->fork_mutex)[index])) != 0)
	{
		printf("error occuring in mutex_lock\n");
		printf("errno : %d\n", errno);
		return NULL;
	}
	printf("test segfault3\n");
	if (gettimeofday(philo->now, NULL) != 0)
		printf("error ocurring in get time\n");
	printf("test segfault4\n");
	printf("now:%d\n", philo->now->tv_usec);
	printf("test segfault4-1\n");
	printf("index:%lld\n", index);
	printf("test segfault4-2\n");
	printf("%d %lld get right fork\n", philo->now->tv_usec, index);fflush(stdout);
	printf("test segfault5\n");
	printf("philo_num : %lld\n", philo->p_info->philo_num);fflush(stdout);
	printf("test segfault6\n");
	printf("index2 is %lld\n", index + 1);fflush(stdout);
	printf("test segfault7\n");
	printf("left index : %lld\n", ((index + 1) % (philo->p_info->philo_num)));fflush(stdout);
	printf("test segfault8\n");
	if (pthread_mutex_lock(&((philo->p_info->fork_mutex)[(index + 1) % philo->p_info->philo_num])) != 0)
	{
		printf("error occuring in mutex_lock\n");
		return NULL;
	}
	printf("test segfault9\n");
	if (gettimeofday(philo->now, NULL) != 0)
		printf("error ocurring in get time\n");
	printf("test segfault10\n");
	printf("%d %lld get left fork\n", philo->now->tv_usec, index);
	printf("%d %lld is eating\n", philo->now->tv_usec, index);
	usleep(500);
	pthread_mutex_unlock(&philo->p_info->fork_mutex[index]);
	pthread_mutex_unlock(&philo->p_info->fork_mutex[(index + 1) % philo->p_info->philo_num]);
	pthread_exit(NULL);
}

t_philo *philo_init(int num, t_p_info *p_info)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * num);
	if (!philo)
	{
		printf("error occuring in malloc_t_philo\n");
		return NULL;
	}
	i = 0;
	while (i < num)
	{
		(philo[i]).p_thread = malloc(sizeof(pthread_t));
		if (!(philo[i]).p_thread)
		{
			printf("error occuring in malloc_pthread\n");
			return NULL;
		}
		if (gettimeofday((philo[i]).last_time_eat, NULL) != 0)
		{
			printf("error ocurring in get time\n");
			return NULL;
		}
		philo[i].index = i;
		philo[i].p_info = p_info;
		i ++;
	}
	return (philo);
}

t_p_info *p_info_init(long long num)
{
	int 			i;
	t_p_info		*p_info;
	pthread_mutex_t	*fork;

	p_info = malloc(sizeof(t_p_info));
	fork = malloc(sizeof(pthread_mutex_t) * num);
	if (!fork)
		return NULL;
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&fork[i], NULL);
		i ++;
	}
	p_info->fork_mutex = fork;
	p_info->philo_num = num;
	return (p_info);
}

int main(int argc, char **argv)
{
	t_philo		*philo;
	int			i;
	long long 	p_num;

	if (argc > 1)
	{
		p_num = ft_atoll(argv[1]);
		if (p_num == 0)
		{
			printf("worng variable\n");
			return (1);
		}
		philo = philo_init(p_num, p_info_init(p_num));
	}
	else
	{
		printf("worng variable\n");
		return (1);
	}
	i = 0;
	while (i < p_num)
	{
		printf("i : %d\n", i);
		if (pthread_create((philo[i]).p_thread, NULL, thread_func, (void *)&philo[i]) != 0)
		{
			printf("error occuring in pthread_create\n");
			return (1);
		}
		i ++;
	}
	i = 0;
	while (i < p_num)
	{
		if (pthread_join(*((philo[i]).p_thread), NULL) != 0)
		{
			printf("error occuring in pthread_detach\n");
			return (1);
		}
		i ++;
	}
	printf("Success!\n");
	return (0);
}

