/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:57:33 by wchen             #+#    #+#             */
/*   Updated: 2023/05/18 22:48:48 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		printf_return("error ocurring in gettimeofday\n", 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	set_last_eat_time(t_philo *philo)
{
	pthread_mutex_lock(philo->c_mutex->last_eat_mutex);
	pthread_mutex_lock(philo->p_info->now_time_mutex);
	philo->last_eat_time = philo->p_info->now_time;
	pthread_mutex_unlock(philo->p_info->now_time_mutex);
	pthread_mutex_unlock(philo->c_mutex->last_eat_mutex);
}

void	set_starving_time(t_philo *philo)
{
	pthread_mutex_lock(philo->c_mutex->starving_time_mutex);
	pthread_mutex_lock(philo->p_info->now_time_mutex);
	pthread_mutex_lock(philo->c_mutex->last_eat_mutex);
	philo->starving_time = philo->p_info->now_time - philo->last_eat_time;
	pthread_mutex_unlock(philo->c_mutex->last_eat_mutex);
	pthread_mutex_unlock(philo->p_info->now_time_mutex);
	pthread_mutex_unlock(philo->c_mutex->starving_time_mutex);
}

bool	set_now_time(t_philo *philo)
{
	long long	now_time_stamp;

	now_time_stamp = get_time();
	if (now_time_stamp == 0)
		return (false);
	pthread_mutex_lock(philo->p_info->now_time_mutex);
	philo->p_info->now_time = now_time_stamp - philo->p_info->start_time_stamp;
	pthread_mutex_unlock(philo->p_info->now_time_mutex);
	return (true);
}
