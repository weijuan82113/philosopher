/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:29:48 by wchen             #+#    #+#             */
/*   Updated: 2023/05/11 19:12:26 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_starving_time_longest(t_philo *philo, int index, t_philo *waiter)
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
	//printf("test3-1\n");fflush(stdout);
	pthread_mutex_lock(waiter[right].c_mutex->starving_time_mutex);
	//printf("test3-2\n");fflush(stdout);
	r_starving_time = waiter[right].starving_time;
	//printf("test3-3\n");fflush(stdout);
	pthread_mutex_unlock(waiter[right].c_mutex->starving_time_mutex);
	//printf("test3-4\n");fflush(stdout);
	pthread_mutex_lock(philo->c_mutex->starving_time_mutex);
	//printf("test3-5\n");fflush(stdout);
	starving_time = philo->starving_time;
	//printf("test3-6\n");fflush(stdout);
	pthread_mutex_unlock(philo->c_mutex->starving_time_mutex);
	//printf("test3-7\n");fflush(stdout);
	pthread_mutex_lock(waiter[left].c_mutex->starving_time_mutex);
	//printf("test3-8\n");fflush(stdout);
	l_starving_time = waiter[left].starving_time;
	//printf("test3-9\n");fflush(stdout);
	pthread_mutex_unlock(waiter[left].c_mutex->starving_time_mutex);
	//printf("test3-10\n");fflush(stdout);
	if (starving_time >= r_starving_time
		&& starving_time >= l_starving_time)
		return (true);
	//printf("test3-11\n");fflush(stdout);
	return (false);
}

bool	waiter_judge(t_philo *philo)
{
	//pthread_mutex_lock(philo->p_info->waiter_mutex); atomic化にするため、コメントアウトする
	//printf("test2-1\n");fflush(stdout);
	if (philo->p_info->p_num == 1)
		return (true);
	//printf("test2-2\n");fflush(stdout);
	if (is_starving_time_longest(philo, philo->index,
			philo->p_info->waiter) == true)
	{
		//printf("test2-3\n");fflush(stdout);
		//printf("index :%lld true\n", philo->index);
		return (true);
	}
	//pthread_mutex_unlock(philo->p_info->waiter_mutex);
	//printf("test2-4\n");fflush(stdout);
	//printf("index :%lld false\n", philo->index);
	return (false);
}
