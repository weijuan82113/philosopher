/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:57:33 by wchen             #+#    #+#             */
/*   Updated: 2023/03/06 00:19:51 by wchen            ###   ########.fr       */
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
	philo->last_eat_time = philo->p_info->now_time;
}

void	set_starving_time(t_philo *philo)
{
	philo->starving_time = philo->p_info->now_time - philo->last_eat_time;
}

bool	set_now_time(t_philo *philo)
{
	long long	now_time_stamp;

	now_time_stamp = get_time();
	if (now_time_stamp == 0)
		return (false);
	philo->p_info->now_time = now_time_stamp - philo->p_info->start_time_stamp;
	return (true);
}
