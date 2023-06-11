/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:57:33 by wchen             #+#    #+#             */
/*   Updated: 2023/06/11 12:52:23 by wchen            ###   ########.fr       */
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
	philo->last_eat_time = get_now_time(philo);
	pthread_mutex_unlock(philo->c_mutex->last_eat_mutex);
}

void	set_starving_time(t_philo *philo)
{
	long long	last_eat_time;

	pthread_mutex_lock(philo->c_mutex->last_eat_mutex);
	last_eat_time = philo->last_eat_time;
	pthread_mutex_unlock(philo->c_mutex->last_eat_mutex);
	pthread_mutex_lock(philo->c_mutex->starving_time_mutex);
	philo->starving_time = get_now_time(philo) - last_eat_time;
	pthread_mutex_unlock(philo->c_mutex->starving_time_mutex);
}

long long	get_now_time(t_philo *philo)
{
	long long	now_time_stamp;
	long long	start_time_stamp;

	now_time_stamp = get_time();
	pthread_mutex_lock(philo->p_info->start_time_mutex);
	start_time_stamp = philo->p_info->start_time_stamp;
	pthread_mutex_unlock(philo->p_info->start_time_mutex);
	return (now_time_stamp - start_time_stamp);
}
