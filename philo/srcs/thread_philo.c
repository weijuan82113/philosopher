/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:02:40 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 12:33:32 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_do_action(t_philo *philo)
{
	print_state(philo->state, philo->index, get_now_time(philo));
	do_action(philo->state, philo->index, philo);
}

static bool	mutex_judge_state(t_philo *philo)
{
	pthread_mutex_lock(philo->c_mutex->state_mutex);
	philo->state = judge_state(philo);
	pthread_mutex_unlock(philo->c_mutex->state_mutex);
	if (philo->state == e_finish)
		return (false);
	pthread_mutex_lock(philo->p_info->judge_mutex);
	if (is_finish(philo) == true)
	{
		pthread_mutex_unlock(philo->p_info->judge_mutex);
		return (false);
	}
	pthread_mutex_unlock(philo->p_info->judge_mutex);
	return (true);
}

void	*thread_philo_func(void *arg)
{
	t_philo			*philo;
	t_state_type	state;

	philo = (t_philo *)arg;
	// usleep(30 * philo->p_info->p_num);
	pthread_mutex_lock(philo->philo_mutex);
	pthread_mutex_unlock(philo->philo_mutex);
	pthread_mutex_lock(philo->c_mutex->last_eat_mutex);
	philo->last_eat_time = 0;
	pthread_mutex_unlock(philo->c_mutex->last_eat_mutex);
	while (true)
	{
		// if (is_finish(philo) == true)
		// 	return (NULL);
		if (mutex_judge_state(philo) == false)
			return (NULL);
		pthread_mutex_lock(philo->c_mutex->state_mutex);
		state = philo->state;
		pthread_mutex_unlock(philo->c_mutex->state_mutex);
		if (state != e_init && is_finish(philo) == false)
			print_do_action(philo);
	}
}
