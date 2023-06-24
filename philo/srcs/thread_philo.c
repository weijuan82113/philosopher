/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:02:40 by wchen             #+#    #+#             */
/*   Updated: 2023/06/24 13:46:25 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_do_action(t_philo *philo)
{
	print_state(philo->state, philo, get_now_time(philo));
	do_action(philo->state, philo->index, philo);
}

static bool	mutex_judge_state(t_philo *philo)
{
	t_state_type	state;

	pthread_mutex_lock(philo->c_mutex->state_mutex);
	state = philo->state;
	pthread_mutex_unlock(philo->c_mutex->state_mutex);
	state = judge_state(philo, state);
	pthread_mutex_lock(philo->c_mutex->state_mutex);
	philo->state = state;
	pthread_mutex_unlock(philo->c_mutex->state_mutex);
	if (state == e_finish)
		return (false);
	if (is_finish(philo) == true)
		return (false);
	return (true);
}

void	*thread_philo_func(void *arg)
{
	t_philo			*philo;
	t_state_type	state;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->philo_mutex);
	pthread_mutex_unlock(philo->philo_mutex);
	pthread_mutex_lock(philo->c_mutex->last_eat_mutex);
	philo->last_eat_time = 0;
	pthread_mutex_unlock(philo->c_mutex->last_eat_mutex);
	while (!is_finish(philo))
	{
		if (mutex_judge_state(philo) == false)
			return (NULL);
		pthread_mutex_lock(philo->c_mutex->state_mutex);
		state = philo->state;
		pthread_mutex_unlock(philo->c_mutex->state_mutex);
		if (state != e_init)
			print_do_action(philo);
	}
	return (NULL);
}
