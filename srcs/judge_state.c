/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:45:19 by wchen             #+#    #+#             */
/*   Updated: 2023/03/05 18:47:47 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	take_fork(int index, int num, pthread_mutex_t *fork, t_philo *philo)
{
	if (index % 2 == 0)
	{
		pthread_mutex_lock(&fork[index]);
		if (is_finish(philo) == true)
			return false;
		print_state(e_fork, index, philo->p_info);
		if (index == (index + 1) % num)
			return false;
		pthread_mutex_lock(&fork[(index + 1) % num]);
		if (is_finish(philo) == true)
			return false;
		print_state(e_fork, index, philo->p_info);
	}
	else
	{
		pthread_mutex_lock(&fork[(index + 1) % num]);
		if (is_finish(philo) == true)
			return false;
		print_state(e_fork, index, philo->p_info);
		pthread_mutex_lock(&fork[index]);
		if (is_finish(philo) == true)
			return false;
		print_state(e_fork, index, philo->p_info);
	}
	return true;
}

t_state_type judge_state(t_philo *philo)
{
	if (philo->state == e_init || philo->state == e_think)
	{
		if (waiter_judge(philo) == false)
			return (e_init);
		if (take_fork(philo->index, philo->p_info->p_num, philo->p_info->fork_mutex, philo) == false)
			return (e_finish);
		return (e_eat);
	}
	else if (philo->state == e_eat)
		return (e_sleep);
	else
		return (e_think);
}
