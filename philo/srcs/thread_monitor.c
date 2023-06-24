/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:36:37 by wchen             #+#    #+#             */
/*   Updated: 2023/06/24 09:08:29 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_print_die(int i, t_philo *philo)
{
	bool	die_flag;

	set_starving_time(&philo[i]);
	die_flag = judge_die(&philo[i]);
	if (die_flag && is_someone_die(philo) == false)
		print_state(e_die, philo, get_now_time(philo));
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
	pthread_mutex_lock(philo->p_info->start_time_mutex);
	philo->p_info->start_time_stamp = get_time();
	pthread_mutex_unlock(philo->p_info->start_time_mutex);
	unlock_philo(philo);
	while (true)
	{
		usleep(200);
		i = 0;
		while (i < philo->p_info->p_num)
		{
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
	}
}
