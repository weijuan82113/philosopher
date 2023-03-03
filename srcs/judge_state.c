/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:45:19 by wchen             #+#    #+#             */
/*   Updated: 2023/03/02 23:56:34 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	take_fork(int index, int num, pthread_mutex_t *fork, long long now)
{
	if (index % 2 == 0)
	{
		pthread_mutex_lock(&fork[index]);
		print_state(e_fork, index, now);
		if (index == (index + 1) % num)
			return false;
		pthread_mutex_lock(&fork[(index + 1) % num]);
		print_state(e_fork, index, now);
	}
	else
	{
		pthread_mutex_lock(&fork[(index + 1) % num]);
		print_state(e_fork, index, now);
		pthread_mutex_lock(&fork[index]);
		print_state(e_fork, index, now);
	}
	return true;
}

t_state_type judge_state(t_philo *philo)
{

	if (philo->state == e_init || philo->state == e_think)
	{
		if (take_fork(philo->index, philo->p_info->p_num, philo->p_info->fork_mutex, philo->now_time) == false)
			return (e_init);
		return (e_eat);
	}
	else if (philo->state == e_eat)
		return (e_sleep);
	else
		return (e_think);
}
