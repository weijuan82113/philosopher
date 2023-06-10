/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:29:48 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 18:02:34 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_starving_time_longest(t_philo *philo,
	const int index, t_philo *waiter)
{
	long long	right;
	long long	left;
	long long	r_starving_time;
	long long	starving_time;
	long long	l_starving_time;

	right = (index + 1) % philo->p_info->p_num;
	if (index - 1 < 0)
		left = index - 1 + philo->p_info->p_num;
	else
		left = index - 1;
	pthread_mutex_lock(waiter[right].c_mutex->starving_time_mutex);
	r_starving_time = waiter[right].starving_time;
	pthread_mutex_unlock(waiter[right].c_mutex->starving_time_mutex);
	pthread_mutex_lock(philo->c_mutex->starving_time_mutex);
	starving_time = philo->starving_time;
	pthread_mutex_unlock(philo->c_mutex->starving_time_mutex);
	pthread_mutex_lock(waiter[left].c_mutex->starving_time_mutex);
	l_starving_time = waiter[left].starving_time;
	pthread_mutex_unlock(waiter[left].c_mutex->starving_time_mutex);
	if (starving_time >= r_starving_time
		&& starving_time >= l_starving_time)
		return (true);
	return (false);
}

void	waiter_judge(t_philo *philo)
{
	if (philo->p_info->p_num == 1)
	{
		pthread_mutex_lock(philo->c_mutex->eat_flag_mutex);
		philo->eat_flag = true;
		pthread_mutex_unlock(philo->c_mutex->eat_flag_mutex);
	}
	else if (is_starving_time_longest(philo, philo->index,
			philo->p_info->waiter) == true)
	{
		pthread_mutex_lock(philo->c_mutex->eat_flag_mutex);
		philo->eat_flag = true;
		pthread_mutex_unlock(philo->c_mutex->eat_flag_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->c_mutex->eat_flag_mutex);
		philo->eat_flag = false;
		pthread_mutex_unlock(philo->c_mutex->eat_flag_mutex);
	}
}
