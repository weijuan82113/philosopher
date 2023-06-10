/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:36:37 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 11:40:24 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_print_die(int i, t_philo *philo)
{
	set_starving_time(&philo[i]);
	if (judge_die(&philo[i]) == true && is_someone_die(philo) == false)
	{
		pthread_mutex_lock(philo[i].philo_mutex);
		set_die(&philo[i]);
		//pthread_mutex_lock(philo->p_info->now_time_mutex);
		print_state(e_die, philo[i].index, get_now_time(philo));
		pthread_mutex_unlock(philo[i].philo_mutex);
		//pthread_mutex_unlock(philo->p_info->now_time_mutex);
	}
}


static void	unlock_philo(t_philo *philo)
{
	long long	i;

	i = 0;

	while (i < philo->p_info->p_num)
	{
		pthread_mutex_unlock(philo[i].philo_mutex);
		i++;
	}
}

void	*thread_monitor_func(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = arg;
	philo->p_info->start_time_stamp = get_time();
	unlock_philo(philo);
	while (true)
	{
		usleep(100);
		i = 0;
		while (i < philo->p_info->p_num)
		{
			// if (set_now_time(philo) == false)
			// 	return (printf_return("error occuring in set_now_time\n", NULL));
			if (is_finish(philo) == true)
				return (NULL);
			waiter_judge(&philo[i]);
			set_print_die(i, philo);
			i ++;
		}
		if (is_everyone_eat(philo) == true && judge_must_eat(philo) == true)
			set_must_eat(philo);
		if (is_finish(philo) == true)
			return (NULL);
		// if (set_now_time(philo) == false)
		// 	return (printf_return("error occuring in set_now_time\n", NULL));
	}
}
