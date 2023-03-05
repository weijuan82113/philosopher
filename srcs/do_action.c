/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:46:29 by wchen             #+#    #+#             */
/*   Updated: 2023/03/04 20:12:33 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	do_wait(long long start_time, long long wait_time)
{
	while (true)
	{
		if (get_time() - start_time >= wait_time)
			break;
	}
}

static void	eat(long long index, t_philo *philo)
{
	t_p_info	*p_info;

	p_info = philo->p_info;
	//printf("\x1b[31m index: %lld \x1b[0mt_eat 1:%lld\n", index, get_time());
	set_last_eat_time(philo);
	philo->eat_count ++;
	if (philo->eat_count == philo->p_info->m_eat && judge_must_eat(philo) == true)
		philo->philo_must_eat = true;
	do_wait(get_time(), p_info->t_eat);
	//printf("\x1b[31m index: %lld \x1b[0mt_eat 2:%lld\n", index, get_time());
	pthread_mutex_unlock(&p_info->fork_mutex[index]);
	pthread_mutex_unlock(&p_info->fork_mutex[(index + 1) % p_info->p_num]);
}

void	do_action(t_state_type state, long long index, t_philo *philo)
{
	if (state == e_eat)
		eat(index, philo);
	if (state == e_sleep)
	{
		//printf("\x1b[31m index: %lld \x1b[0mt_sleep 3:%lld\n", index, get_time());
		do_wait(get_time(), philo->p_info->t_sleep);
		//usleep(p_info->t_sleep * 1000);
		//printf("\x1b[31m index: %lld \x1b[0mt_sleep 4:%lld\n", index, get_time());
	}
}
