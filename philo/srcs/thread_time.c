/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:36:37 by wchen             #+#    #+#             */
/*   Updated: 2023/06/04 15:37:13 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_print_die(int i, t_philo *philo)
{
	set_starving_time(&philo[i]);
	if (judge_die(&philo[i]) == true && is_someone_die(philo) == false)
	{
		set_die(&philo[i]);
		pthread_mutex_lock(philo->p_info->now_time_mutex);
		print_state(e_die, philo[i].index, philo->p_info->now_time);
		pthread_mutex_unlock(philo->p_info->now_time_mutex);
	}
}

void	*thread_time_func(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = arg;
	philo->p_info->start_time_stamp = get_time();
	while (true)
	{
		usleep(100);
		i = 0;
		while (i < philo->p_info->p_num)
		{
			if (set_now_time(philo) == false)
				return (printf_return("error occuring in set_now_time\n", NULL));
			if (is_finish(philo) == true)
				return (NULL);
			set_print_die(i, philo);
			waiter_judge(&philo[i]);
			i ++;
		}
		if (is_everyone_eat(philo) == true && judge_must_eat(philo) == true)
			set_must_eat(philo);
		if (is_finish(philo) == true)
			return (NULL);
		if (set_now_time(philo) == false)
			return (printf_return("error occuring in set_now_time\n", NULL));
	}
}
