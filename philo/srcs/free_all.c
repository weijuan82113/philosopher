/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 00:08:30 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 18:01:37 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*free_p_info(t_p_info *p_info)
{
	int	i;

	i = 0;
	while (i < p_info->p_num)
	{
		pthread_mutex_destroy(&(p_info->fork_mutex[i]));
		i++;
	}
	pthread_mutex_destroy(p_info->judge_mutex);
	pthread_mutex_destroy(p_info->die_mutex);
	pthread_mutex_destroy(p_info->is_must_eat_mutex);
	pthread_mutex_destroy(p_info->start_time_mutex);
	pthread_mutex_destroy(p_info->waiter_mutex);
	free(p_info->fork_mutex);
	free(p_info->judge_mutex);
	free(p_info->die_mutex);
	free(p_info->is_must_eat_mutex);
	free(p_info->start_time_mutex);
	free(p_info->waiter_mutex);
	free(p_info->t_thread);
	free(p_info);
	return (NULL);
}

static void	free_common_mutex(t_common_mutex *c_mutex)
{
	pthread_mutex_destroy(c_mutex->last_eat_mutex);
	pthread_mutex_destroy(c_mutex->starving_time_mutex);
	pthread_mutex_destroy(c_mutex->state_mutex);
	pthread_mutex_destroy(c_mutex->eat_flag_mutex);
	pthread_mutex_destroy(c_mutex->must_eat_mutex);
	free(c_mutex->last_eat_mutex);
	free(c_mutex->starving_time_mutex);
	free(c_mutex->state_mutex);
	free(c_mutex->eat_flag_mutex);
	free(c_mutex->must_eat_mutex);
}

static void	free_philo_mutex(t_philo *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(philo[i].philo_mutex);
		free(philo[i].philo_mutex);
		free_common_mutex(philo[i].c_mutex);
		free(philo[i].c_mutex);
		i++;
	}
}

static void	free_philo_thread(t_philo *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(philo[i].p_thread);
		free(philo[i].m_thread);
		i++;
	}
}

void	free_all(t_philo *philo)
{
	int	num;

	num = philo->p_info->p_num;
	philo->p_info = free_p_info(philo->p_info);
	free_philo_thread(philo, num);
	free_philo_mutex(philo, num);
	free(philo);
}
