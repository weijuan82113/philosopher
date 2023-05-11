/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:05:00 by wchen             #+#    #+#             */
/*   Updated: 2023/05/06 13:14:05 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_someone_die(t_philo *philo)
{
	//printf("test6-1\n");fflush(stdout);
	pthread_mutex_lock(philo->p_info->die_mutex);
	//printf("test6-2\n");fflush(stdout);
	if (philo->p_info->die == true)
	{
		//printf("test6-3\n");fflush(stdout);
		pthread_mutex_unlock(philo->p_info->die_mutex);
		//printf("test6-4\n");fflush(stdout);
		return (true);
	}
	//printf("test6-5\n");fflush(stdout);
	pthread_mutex_unlock(philo->p_info->die_mutex);
	//printf("test6-6\n");fflush(stdout);
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
	//printf("test 7-1\n");fflush(stdout);
	pthread_mutex_lock(philo->p_info->die_mutex);
	//printf("test 7-2\n");fflush(stdout);
	philo->p_info->die = true;
	//printf("test 7-3\n");fflush(stdout);
	pthread_mutex_unlock(philo->p_info->die_mutex);
	//printf("test 7-4\n");fflush(stdout);
	pthread_mutex_lock(philo->c_mutex->state_mutex);
	//printf("test 7-5\n");fflush(stdout);
	philo->state = e_die;
	//printf("test 7-6\n");fflush(stdout);
	pthread_mutex_unlock(philo->c_mutex->state_mutex);
	//printf("test 7-7\n");fflush(stdout);
}


bool	judge_die(t_philo *philo)
{
	pthread_mutex_lock(philo->c_mutex->starving_time_mutex);
	//printf("index : %lld starving time : %lld\n", philo->index, philo->starving_time);
	if (philo->starving_time > philo->p_info->t_die)
		return (true);
	pthread_mutex_unlock(philo->c_mutex->starving_time_mutex);
	return (false);
}

bool	is_finish(t_philo *philo)
{
	//printf("test5-1\n");fflush(stdout);
	if (is_someone_die(philo) == true || philo->p_info->is_must_eat == true)
		return (true);
	//printf("test5-2\n");fflush(stdout);
	return (false);
}
