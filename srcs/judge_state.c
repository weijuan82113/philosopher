/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:45:19 by wchen             #+#    #+#             */
/*   Updated: 2023/04/17 22:55:54 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	take_fork(int index, int num, pthread_mutex_t *fork, t_philo *philo)
{
	if (index % 2 == 0)
	{
		printf("test4-1\n");fflush(stdout);
		pthread_mutex_lock(&fork[index]);
		if (is_finish(philo) == true)
			return (false);
		print_state(e_fork, index, philo->p_info->now_time);
		if (index == (index + 1) % num)
			return (false);
		pthread_mutex_lock(&fork[(index + 1) % num]);
		if (is_finish(philo) == true)
			return (false);
		print_state(e_fork, index, philo->p_info->now_time);
	}
	else
	{
		printf("test4-2\n");fflush(stdout);
		pthread_mutex_lock(&fork[(index + 1) % num]);
		printf("test4-2-1\n");fflush(stdout);
		if (is_finish(philo) == true)
			return (false);
		printf("test4-2-2\n");fflush(stdout);
		print_state(e_fork, index, philo->p_info->now_time);
		printf("test4-2-3\n");fflush(stdout);
		pthread_mutex_lock(&fork[index]);
		printf("test4-2-4\n");fflush(stdout);
		if (is_finish(philo) == true)
			return (false);
		printf("test4-2-4\n");fflush(stdout);
		print_state(e_fork, index, philo->p_info->now_time);
	}
	return (true);
}

t_state_type	judge_state(t_philo *philo)
{
	printf("test1-1\n");fflush(stdout);
	if (philo->state == e_init || philo->state == e_think)
	{
		printf("test1-2\n");fflush(stdout);
		//pthread_mutex_lock(philo->p_info->waiter_mutex);
		if (waiter_judge(philo) == false && philo->p_info->p_num % 2 != 0)
			return (e_init);
		//pthread_mutex_unlock(philo->p_info->waiter_mutex);
		printf("test1-3\n");fflush(stdout);
		if (take_fork(philo->index, philo->p_info->p_num,
				philo->p_info->fork_mutex, philo) == false)
			return (e_finish);
		return (e_eat);
	}
	else if (philo->state == e_eat)
		return (e_sleep);
	else
		return (e_think);
}
