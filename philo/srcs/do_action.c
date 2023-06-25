/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:46:29 by wchen             #+#    #+#             */
/*   Updated: 2023/06/25 13:22:34 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_wait_time(long long start_time, long long wait_time)
{
	return (get_time() - start_time > wait_time);
}

static void	do_wait(long long start_time, long long wait_time)
{
	while (true)
	{
		usleep(100);
		if (is_wait_time(start_time, wait_time))
			break ;
	}
}

static void	do_eat(long long index, t_philo *philo)
{
	t_p_info	*p_info;

	p_info = philo->p_info;
	set_last_eat_time(philo);
	do_wait(get_time(), p_info->t_eat);
	pthread_mutex_unlock(&p_info->fork_mutex[index]);
	pthread_mutex_unlock(&p_info->fork_mutex[(index + 1) % p_info->p_num]);
	philo->eat_count++;
	if (philo->eat_count == philo->p_info->m_eat
		&& judge_must_eat(philo) == true)
	{
		pthread_mutex_lock(philo->c_mutex->must_eat_mutex);
		philo->philo_must_eat = true;
		pthread_mutex_unlock(philo->c_mutex->must_eat_mutex);
	}
}

void	do_action(t_state_type state, long long index, t_philo *philo)
{
	if (state == e_eat)
		do_eat(index, philo);
	if (state == e_sleep)
		do_wait(get_time(), philo->p_info->t_sleep);
}
