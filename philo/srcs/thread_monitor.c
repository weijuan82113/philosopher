/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:38:33 by wchen             #+#    #+#             */
/*   Updated: 2023/06/04 15:38:57 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	set_ready(t_philo *philo)
{
	long long	i;

	i = 0;
	if (philo->index + 1 == philo->p_info->p_num)
	{
		while (i < philo->p_info->p_num - 1)
		{
			pthread_mutex_unlock(&philo->p_info->ready_mutex[i]);
			i++;
		}
	}
	return (true);
}

static void	wait_ready(long long index, t_p_info *p_info)
{
	if (index + 1 != p_info->p_num)
		pthread_mutex_lock(&p_info->ready_mutex[index]);
	else
		pthread_mutex_unlock(&p_info->ready_mutex[index]);
}

void	*thread_monitor_func(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(philo->philo_mutex);
	wait_ready(philo->index, philo->p_info);
	if (set_ready(philo) == false)
		return (printf_return("error occuring in set_ready\n", NULL));
	pthread_mutex_unlock(philo->philo_mutex);
	// pthread_mutex_lock(philo->c_mutex->last_eat_mutex);
	// philo->last_eat_time = 0;
	// pthread_mutex_unlock(philo->c_mutex->last_eat_mutex);
	// while (true)
	// {
	// 	if (is_finish(philo) == true)
	// 		return (NULL);
	// 	waiter_judge(philo);
	// 	if (is_finish(philo) == true)
	// 		return (NULL);
	// }
	return (NULL);
}
