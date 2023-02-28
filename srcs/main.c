/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:06:52 by wchen             #+#    #+#             */
/*   Updated: 2023/03/01 01:40:58 by wchen            ###   ########.fr       */
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
	printf("3 index:%lld\n", philo->index);
	pthread_mutex_lock(philo->philo_mutex);
	if (is_die(philo) == true)
		return (NULL);
	pthread_mutex_unlock(philo->philo_mutex);
	judge_state();
	print_state();
	printf("4 index:%lld\n", philo->index);
	if (pthread_mutex_lock(&((philo->p_info->fork_mutex)[index])) != 0)
	{
		printf("error occuring in mutex_lock\n");
		printf("errno : %d\n", errno);
		return NULL;
	}
	printf("%lld %lld get right fork\n", philo->now_time, index);fflush(stdout);
	if (pthread_mutex_lock(&((philo->p_info->fork_mutex)[(index + 1) % philo->p_info->p_num])) != 0)
	{
		printf("error occuring in mutex_lock\n");
		return NULL;
	}
	printf("%lld %lld get left fork\n", philo->now_time, index);
	printf("%lld %lld is eating\n", philo->now_time, index);
	usleep(500);
	pthread_mutex_unlock(&philo->p_info->fork_mutex[index]);
	pthread_mutex_unlock(&philo->p_info->fork_mutex[(index + 1) % philo->p_info->p_num]);
	pthread_mutex_unlock(philo->philo_mutex);
	return(arg);
}

void *thread_monitor_func(void *arg)
{
	t_philo *philo;

	philo = arg;
	printf("1 index:%lld\n", philo->index);
	pthread_mutex_lock(philo->philo_mutex);
	printf("2 index:%lld\n", philo->index);
	if (philo->index + 1 == philo->p_info->p_num)
	{
		philo->p_info->start_time_stamp = get_time();
		if (philo->p_info->start_time_stamp == 0)
			return (printf_return("error occuring in gettimeofday\n", NULL));
		philo->p_info->ready = true;
	}
	while (true)
	{
		if (philo->p_info->ready == true)
			break;
	}
	pthread_mutex_unlock(philo->philo_mutex);
	while (true)
	{
		if (set_time(philo) == false)
			return (printf_return("error occuring in set_time\n", NULL));
		if (judge_die(philo) == true)
			return NULL;
	}
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q philo");
}

int main(int argc, char **argv)
{
	t_philo		*philo;
	int			i;
	long long 	p_num;

	if (argc < 2)
		return (printf_return_int("wrong variable\n", 1));
	p_num = ft_atoll(argv[1]);
	if (p_num == 0)
		return (printf_return_int("wrong variable\n", 1));
	philo = philo_init(p_num, p_info_init(p_num, argv));
	if (philo == NULL)
		return 1;
	i = 0;
	while (i < p_num)
	{
		if (pthread_create((philo[i]).p_thread, NULL, thread_monitor_func, (void *)&philo[i]) != 0)
			return ((printf_return_int("error occuring in pthread_create\n", 1)));
		if (pthread_create((philo[i]).p_thread, NULL, thread_func, (void *)&philo[i]) != 0)
			return ((printf_return_int("error occuring in pthread_create\n", 1)));
		i ++;
	}
	i = 0;
	while (i < p_num)
	{
		if (pthread_join(*((philo[i]).p_thread), NULL) != 0)
			return (printf_return_int("error occuring in pthread_detach\n", 1));
		if (pthread_join(*((philo[i]).p_thread), NULL) != 0)
			return (printf_return_int("error occuring in pthread_detach\n", 1));
		i ++;
	}
	free_all(philo);
	printf("Success!\n");
	return (0);
}
