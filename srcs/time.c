/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:57:33 by wchen             #+#    #+#             */
/*   Updated: 2023/02/28 01:11:10 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		printf_return("error ocurring in gettimeofday\n", 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool set_time(t_philo *philo)
{
	philo->now_time = get_time();
	if (philo->now_time == 0)
		return false;
	philo->starving_time = philo->now_time - philo->last_eat_time;
	return true;
}
