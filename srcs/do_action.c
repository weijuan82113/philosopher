/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:46:29 by wchen             #+#    #+#             */
/*   Updated: 2023/03/06 00:20:49 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_wait_time(t_state_type state, long long start_time,
		long long wait_time)
{
	if (state == e_sleep)
		return (get_time() - start_time >= wait_time);
	return (get_time() - start_time > wait_time);
}

static void	do_wait(t_state_type state, long long start_time,
		long long wait_time)
{
	while (true)
	{
		if (is_wait_time(state, start_time, wait_time))
			break ;
	}
}

static void	eat(long long index, t_philo *philo)
{
	t_p_info	*p_info;

	p_info = philo->p_info;
	set_last_eat_time(philo);
	philo->eat_count++;
	if (philo->eat_count == philo->p_info->m_eat
		&& judge_must_eat(philo) == true)
		philo->philo_must_eat = true;
	do_wait(philo->state, get_time(), p_info->t_eat);
	pthread_mutex_unlock(&p_info->fork_mutex[index]);
	pthread_mutex_unlock(&p_info->fork_mutex[(index + 1) % p_info->p_num]);
}

void	do_action(t_state_type state, long long index, t_philo *philo)
{
	if (state == e_eat)
		eat(index, philo);
	if (state == e_sleep)
		do_wait(philo->state, get_time(), philo->p_info->t_sleep);
}
