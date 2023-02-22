/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:06:52 by wchen             #+#    #+#             */
/*   Updated: 2023/02/23 00:00:08 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *thread_func(void *arg)
{
	long long	index;
	t_philo		*philo;
	errno;

	philo = (t_philo*)arg;
	index = philo->index;
	if (index % 2 == 1)
		usleep(500);
	if (pthread_mutex_lock(&((philo->p_info->fork_mutex)[index])) != 0)
	{
		printf("error occuring in mutex_lock\n");
		printf("errno : %d\n", errno);
		return NULL;
	}
	if (gettimeofday(&philo->now, NULL) != 0)
		printf("error ocurring in get time\n");
	printf("%d %lld get right fork\n", philo->now.tv_usec, index);fflush(stdout);
	if (pthread_mutex_lock(&((philo->p_info->fork_mutex)[(index + 1) % philo->p_info->p_num])) != 0)
	{
		printf("error occuring in mutex_lock\n");
		return NULL;
	}
	if (gettimeofday(&philo->now, NULL) != 0)
		printf("error ocurring in get time\n");
	printf("%d %lld get left fork\n", philo->now.tv_usec, index);
	printf("%d %lld is eating\n", philo->now.tv_usec, index);
	usleep(500);
	pthread_mutex_unlock(&philo->p_info->fork_mutex[index]);
	pthread_mutex_unlock(&philo->p_info->fork_mutex[(index + 1) % philo->p_info->p_num]);
	return(arg);
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
			printf_return("worng variable\n", (int *)1);
		philo = philo_init(p_num, p_info_init(p_num, argv));
	}
	else
	{
		printf("worng variable\n");
		return (1);
	}
	i = 0;
	while (i < p_num)
	{
		if (pthread_create((philo[i]).p_thread, NULL, thread_func, (void *)&philo[i]) != 0)
			printf_return("error occuring in pthread_create\n", (int *)1);
		i ++;
	}
	i = 0;
	while (i < p_num)
	{
		if (pthread_join(*((philo[i]).p_thread), NULL) != 0)
			printf_return("error occuring in pthread_detach\n", (int *)1);
		i ++;
	}
	printf("Success!\n");
	return (0);
}
