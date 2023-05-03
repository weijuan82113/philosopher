/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:02:40 by wchen             #+#    #+#             */
/*   Updated: 2023/04/17 23:25:18 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*thread_philo_func(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	usleep(30 * philo->p_info->p_num);
	pthread_mutex_lock(philo->philo_mutex);
	pthread_mutex_unlock(philo->philo_mutex);
	while (true)
	{
		if (is_finish(philo) == true)
			return (NULL);
		printf("test1\n");fflush(stdout);
		//pthread_mutex_lock(philo->c_mutex->state_mutex);
		philo->state = judge_state(philo);
		printf("test2\n");fflush(stdout);
		//pthread_mutex_unlock(philo->c_mutex->state_mutex);
		printf("test3\n");fflush(stdout);
		if (philo->state == e_finish)
			return (NULL);
		if (is_finish(philo) == true)
			return (NULL);
		if (philo->state != e_init && is_finish(philo) == false)
		{
			print_state(philo->state, philo->index, philo->p_info->now_time);
			do_action(philo->state, philo->index, philo);
		}
	}
}

static bool	set_ready(t_philo *philo)
{
	long long i;

	i = 0;
	if (philo->index + 1 == philo->p_info->p_num)
	{
		// pthread_mutex_lock(philo->p_info->start_time_mutex);
		// philo->p_info->start_time_stamp = get_time();
		// if (philo->p_info->start_time_stamp == 0)
		// 	return (false);
		// pthread_mutex_unlock(philo->p_info->start_time_mutex);
		//pthread_mutex_unlock(&philo->p_info->ready_mutex[philo->p_info->p_num - 1]);
		while (i < philo->p_info->p_num - 1)
		{
			pthread_mutex_unlock(&philo->p_info->ready_mutex[i]);
			i ++;
		}
	}
	return (true);
}

static void	wait_ready(long long index, t_p_info *p_info)
{
	if (index + 1 != p_info->p_num)
		pthread_mutex_lock(&p_info->ready_mutex[index]);
	pthread_mutex_unlock(&p_info->ready_mutex[index]);
}

void	*thread_monitor_func(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(philo->philo_mutex);
	wait_ready(philo->index, philo->p_info);
	if (set_ready(philo) == false)
		return (printf_return("error occuring in set_ready\n", NULL));
	pthread_mutex_unlock(philo->philo_mutex);

	// if (philo->index + 1 != philo->p_info->p_num)
	// 	pthread_mutex_unlock(&philo->p_info->ready_mutex[philo->index]);
	pthread_mutex_lock(philo->c_mutex->last_eat_mutex);
	philo->last_eat_time = 0;
	pthread_mutex_unlock(philo->c_mutex->last_eat_mutex);
	while (true)
	{
		usleep(500);
		pthread_mutex_lock(philo->p_info->monitor_mutex);
		set_starving_time(philo);
		if (judge_die(philo) == true && is_someone_die(philo) == false)
		{
			set_die(philo);
			pthread_mutex_lock(philo->p_info->now_time_mutex);
			print_state(e_die, philo->index, philo->p_info->now_time);
			pthread_mutex_unlock(philo->p_info->now_time_mutex);
		}
		pthread_mutex_unlock(philo->p_info->monitor_mutex);
		if (is_finish(philo) == true)
			return (NULL);
	}
}

void	*thread_time_func(void *arg)
{
	t_philo		*philo;

	philo = arg;
	philo->p_info->start_time_stamp = get_time();
	//pthread_mutex_lock(&philo->p_info->ready_mutex[philo->p_info->p_num - 1]);
	while (true)
	{
		usleep(200);
		if (is_everyone_eat(philo) == true && judge_must_eat(philo) == true)
			set_must_eat(philo);
		if (is_finish(philo) == true)
			return (NULL);
		if (set_now_time(philo) == false)
			return (printf_return("error occuring in set_now_time\n", NULL));
	}
}
