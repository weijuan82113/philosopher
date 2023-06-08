/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:45:19 by wchen             #+#    #+#             */
/*   Updated: 2023/06/08 20:35:07 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	take_from_left(int index, int num, pthread_mutex_t *fork,
		t_philo *philo)
{
	if (is_finish(philo) == true)
		return (false);
	pthread_mutex_lock(&fork[index]);
	pthread_mutex_lock(philo->p_info->now_time_mutex);
	print_state(e_fork, index, philo->p_info->now_time);
	pthread_mutex_unlock(philo->p_info->now_time_mutex);
	if (index == (index + 1) % num)
		return (false);
	if (is_finish(philo) == true)
	{
		pthread_mutex_unlock(&fork[index]);
		return (false);
	}
	pthread_mutex_lock(&fork[(index + 1) % num]);
	pthread_mutex_lock(philo->p_info->now_time_mutex);
	print_state(e_fork, index, philo->p_info->now_time);
	pthread_mutex_unlock(philo->p_info->now_time_mutex);
	return (true);
}

static bool	take_from_right(int index, int num, pthread_mutex_t *fork,
		t_philo *philo)
{
	if (is_finish(philo) == true)
		return (false);
	pthread_mutex_lock(&fork[(index + 1) % num]);
	pthread_mutex_lock(philo->p_info->now_time_mutex);
	print_state(e_fork, index, philo->p_info->now_time);
	pthread_mutex_unlock(philo->p_info->now_time_mutex);
	if (is_finish(philo) == true)
	{
		pthread_mutex_unlock(&fork[index]);
		return (false);
	}
	pthread_mutex_lock(&fork[index]);
	pthread_mutex_lock(philo->p_info->now_time_mutex);
	print_state(e_fork, index, philo->p_info->now_time);
	pthread_mutex_unlock(philo->p_info->now_time_mutex);
	return (true);
}

static bool	take_fork(int index, int num, pthread_mutex_t *fork, t_philo *philo)
{
	if (index % 2 == 0)
	{
		if (take_from_right(index, num, fork, philo) == false)
			return (false);
	}
	else
	{
		if (take_from_left(index, num, fork, philo) == false)
			return (false);
	}
	return (true);
}

t_state_type	judge_state(t_philo *philo)
{
	if (philo->state == e_init || philo->state == e_think)
	{
		pthread_mutex_lock(philo->c_mutex->eat_flag_mutex);
		if (philo->eat_flag == false && philo->p_info->p_num % 2 != 0)
		{
			pthread_mutex_unlock(philo->c_mutex->eat_flag_mutex);
			return (e_init);
		}
		if (take_fork(philo->index, philo->p_info->p_num,
				philo->p_info->fork_mutex, philo) == false)
		{
			pthread_mutex_unlock(philo->c_mutex->eat_flag_mutex);
			return (e_finish);
		}
		pthread_mutex_unlock(philo->c_mutex->eat_flag_mutex);
		return (e_eat);
	}
	else if (philo->state == e_eat)
		return (e_sleep);
	else
		return (e_think);
}
