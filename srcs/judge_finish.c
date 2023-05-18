/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:05:00 by wchen             #+#    #+#             */
/*   Updated: 2023/05/18 22:46:48 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_someone_die(t_philo *philo)
{
	pthread_mutex_lock(philo->p_info->die_mutex);
	if (philo->p_info->die == true)
	{
		pthread_mutex_unlock(philo->p_info->die_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->p_info->die_mutex);
	return (false);
}

bool	is_everyone_eat(t_philo *philo)
{
	long long	i;
	long long	m_eat_count;

	i = 0;
	m_eat_count = 0;
	while (i < philo->p_info->p_num)
	{
		if (philo[i].philo_must_eat == true)
			m_eat_count++;
		i++;
	}
	if (m_eat_count == philo->p_info->p_num)
		return (true);
	return (false);
}

void	set_die(t_philo *philo)
{
	pthread_mutex_lock(philo->p_info->die_mutex);
	philo->p_info->die = true;
	pthread_mutex_unlock(philo->p_info->die_mutex);
	pthread_mutex_lock(philo->c_mutex->state_mutex);
	philo->state = e_die;
	pthread_mutex_unlock(philo->c_mutex->state_mutex);
}


bool	judge_die(t_philo *philo)
{
	pthread_mutex_lock(philo->c_mutex->starving_time_mutex);
	if (philo->starving_time > philo->p_info->t_die)
		return (true);
	pthread_mutex_unlock(philo->c_mutex->starving_time_mutex);
	return (false);
}

bool	is_finish(t_philo *philo)
{
	if (is_someone_die(philo) == true || philo->p_info->is_must_eat == true)
		return (true);
	return (false);
}
