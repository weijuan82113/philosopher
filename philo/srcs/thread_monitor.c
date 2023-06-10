/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:36:37 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 12:09:14 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_print_die(int i, t_philo *philo)
{
	long long	die_time;

	set_starving_time(&philo[i]);
	pthread_mutex_lock(philo->p_info->judge_mutex);
	die_time = judge_die_time(&philo[i]);
	if (die_time != 0 && is_someone_die(philo) == false)
	{
		set_die(&philo[i]);
		//pthread_mutex_lock(philo->p_info->now_time_mutex);
		print_state(e_die, philo[i].index, die_time);
		//pthread_mutex_unlock(philo->p_info->now_time_mutex);
	}
	pthread_mutex_unlock(philo->p_info->judge_mutex);
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
