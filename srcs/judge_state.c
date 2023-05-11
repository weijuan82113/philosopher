/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:45:19 by wchen             #+#    #+#             */
/*   Updated: 2023/05/04 21:17:23 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	take_fork(int index, int num, pthread_mutex_t *fork, t_philo *philo)
{
	if (index % 2 == 0)
	{
		////printf("test4-1\n");fflush(stdout);
		pthread_mutex_lock(&fork[index]);
		////printf("test4-1-1\n");fflush(stdout);
		if (is_finish(philo) == true)
			return (false);
		//printf("test4-1-2\n");fflush(stdout);
		pthread_mutex_lock(philo->p_info->now_time_mutex);
		print_state(e_fork, index, philo->p_info->now_time);
		pthread_mutex_unlock(philo->p_info->now_time_mutex);
		//printf("test4-1-3\n");fflush(stdout);
		if (index == (index + 1) % num)
			return (false);
		//printf("test4-1-4\n");fflush(stdout);
		pthread_mutex_lock(&fork[(index + 1) % num]);
		//printf("test4-1-5\n");fflush(stdout);
		if (is_finish(philo) == true)
			return (false);
		//printf("test4-1-6\n");fflush(stdout);
		pthread_mutex_lock(philo->p_info->now_time_mutex);
		print_state(e_fork, index, philo->p_info->now_time);
		pthread_mutex_unlock(philo->p_info->now_time_mutex);
		//printf("test4-1-7\n");fflush(stdout);
	}
	else
	{
		//printf("test4-2\n");fflush(stdout);
		pthread_mutex_lock(&fork[(index + 1) % num]);
		//printf("test4-2-1\n");fflush(stdout);
		if (is_finish(philo) == true)
			return (false);
		//printf("test4-2-2\n");fflush(stdout);
		pthread_mutex_lock(philo->p_info->now_time_mutex);
		print_state(e_fork, index, philo->p_info->now_time);
		pthread_mutex_unlock(philo->p_info->now_time_mutex);
		//printf("test4-2-3\n");fflush(stdout);
		pthread_mutex_lock(&fork[index]);
		//printf("test4-2-4\n");fflush(stdout);
		if (is_finish(philo) == true)
			return (false);
		//printf("test4-2-4\n");fflush(stdout);
		pthread_mutex_lock(philo->p_info->now_time_mutex);
		print_state(e_fork, index, philo->p_info->now_time);
		pthread_mutex_unlock(philo->p_info->now_time_mutex);
	}
	return (true);
}

t_state_type	judge_state(t_philo *philo)
{
	//printf("test1-1\n");fflush(stdout);
	if (philo->state == e_init || philo->state == e_think)
	{
		//printf("test1-2\n");fflush(stdout);
		if (waiter_judge(philo) == false && philo->p_info->p_num % 2 != 0)
			return (e_init);
		//printf("test1-3\n");fflush(stdout);
		if (take_fork(philo->index, philo->p_info->p_num,
				philo->p_info->fork_mutex, philo) == false)
			return (e_finish);
		//printf("test1-4\n");fflush(stdout);
		return (e_eat);
		//printf("test1-5\n");fflush(stdout);
		//pthread_mutex_lock(philo->c_mutex->state_mutex);
	}
	else if (philo->state == e_eat)
	{
		//pthread_mutex_unlock(philo->c_mutex->state_mutex);
		return (e_sleep);
	}
	else
		return (e_think);
}
