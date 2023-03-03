/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:06:52 by wchen             #+#    #+#             */
/*   Updated: 2023/03/03 00:31:06 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *thread_func(void *arg)
{
	long long	index;
	t_philo		*philo;
	errno;

	philo = (t_philo*)arg;
	usleep(20);
	pthread_mutex_lock(philo->philo_mutex);
	pthread_mutex_unlock(philo->philo_mutex);
	while (true)
	{
		//pthread_mutex_lock(philo->philo_mutex);
		if (is_someone_die(philo) == true)
			return (NULL);
		//pthread_mutex_unlock(philo->philo_mutex);
		philo->state = judge_state(philo);
		if (philo->state == e_init)
			return NULL;
		print_state(philo->state, philo->index, philo->now_time);
		do_action(philo->state, philo->index, philo->p_info);
	}
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
		if (judge_die(philo) == true && is_someone_die(philo) == false)
		{
			set_die(philo);
			print_state(e_die, philo->index, philo->now_time);
		}
		if (is_someone_die(philo) == true)
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
		if (pthread_detach(*((philo[i]).p_thread)) != 0)
			return (printf_return_int("error occuring in pthread_join\n", 1));
		if (pthread_detach(*((philo[i]).p_thread)) != 0)
			return (printf_return_int("error occuring in pthread_join\n", 1));
		i ++;
	}
	free_all(philo);
	printf("Success!\n");
	return (0);
}
