/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:17:13 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 18:02:09 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	create_thread(long long p_num, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < p_num)
	{
		if (pthread_create((philo[i]).p_thread, NULL, thread_philo_func,
				(void *)&philo[i]) != 0)
			return (false);
		i++;
	}
	if (pthread_create(philo->p_info->t_thread, NULL, thread_monitor_func,
			(void *)philo) != 0)
		return (false);
	return (true);
}

bool	join_thread(long long p_num, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < p_num)
	{
		if (pthread_join(*((philo[i]).p_thread), NULL) != 0)
			return (false);
		i++;
	}
	if (pthread_join(*philo->p_info->t_thread, NULL) != 0)
		return (false);
	return (true);
}
