/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:45:19 by wchen             #+#    #+#             */
/*   Updated: 2023/06/11 09:04:55 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	take_from_left(int index, int num, pthread_mutex_t *fork,
		t_philo *philo)
{
	pthread_mutex_lock(&fork[index]);
	if (is_finish(philo) == true)
	{
		pthread_mutex_unlock(&fork[index]);
		return (false);
	}
	print_state(e_fork, index, get_now_time(philo));
	if (index == (index + 1) % num)
		return (false);
	pthread_mutex_lock(&fork[(index + 1) % num]);
	if (is_finish(philo) == true)
	{
		pthread_mutex_unlock(&fork[index + 1]);
		return (false);
	}
	print_state(e_fork, index, get_now_time(philo));
	return (true);
}

static bool	take_from_right(int index, int num, pthread_mutex_t *fork,
		t_philo *philo)
{
	pthread_mutex_lock(&fork[(index + 1) % num]);
	if (is_finish(philo) == true)
	{
		pthread_mutex_unlock(&fork[(index + 1) % num]);
		return (false);
	}
	print_state(e_fork, index, get_now_time(philo));
	pthread_mutex_lock(&fork[index]);
	if (is_finish(philo) == true)
	{
		pthread_mutex_unlock(&fork[index]);
		return (false);
	}
	print_state(e_fork, index, get_now_time(philo));
	return (true);
}

static bool	take_fork_even(int index, int num, pthread_mutex_t *fork,
		t_philo *philo)
{
	if (index % 2 != 0)
		usleep(100);
	if (take_from_left(index, num, fork, philo) == false)
		return (false);
	return (true);
}

static bool	take_fork_odd(int index, int num, pthread_mutex_t *fork,
		t_philo *philo)
{
	if (index % 2 != 0)
		usleep(100);
	if (index % 2 == 1)
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
	bool	eat_flag;
	bool	take_fork_return;

	pthread_mutex_lock(philo->c_mutex->eat_flag_mutex);
	eat_flag = philo->eat_flag;
	pthread_mutex_unlock(philo->c_mutex->eat_flag_mutex);
	if (philo->state == e_init || philo->state == e_think)
	{
		if (eat_flag == false && philo->p_info->p_num % 2 != 0)
			return (e_init);
		if (philo->p_info->p_num % 2 == 0)
			take_fork_return = take_fork_even(philo->index, philo->p_info->p_num,
					philo->p_info->fork_mutex, philo);
		else
			take_fork_return = take_fork_odd(philo->index, philo->p_info->p_num,
				philo->p_info->fork_mutex, philo);
		if (take_fork_return == false)
			return (e_finish);
		return (e_eat);
	}
	else if (philo->state == e_eat)
		return (e_sleep);
	else
		return (e_think);
}
