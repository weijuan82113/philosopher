/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 00:08:30 by wchen             #+#    #+#             */
/*   Updated: 2023/03/01 01:23:32 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*free_p_info(t_p_info *p_info)
{
	int i;

	i = 0;
	while (i < p_info->p_num)
	{
		pthread_mutex_destroy(&(p_info->fork_mutex[i]));
		i ++;
	}
	free(p_info->fork_mutex);
	free (p_info);
	return (NULL);
}

void	free_philo_mutex(t_philo *philo, int num)
{
	int i;

	i = 0;
	while(i < num)
	{
		pthread_mutex_destroy(philo[i].philo_mutex);
		free(philo[i].philo_mutex);
		i ++;
	}
}

void	free_all(t_philo *philo)
{
	int	num;

	num = philo->p_info->p_num;
	philo->p_info = free_p_info(philo->p_info);
	free_philo_mutex(philo, num);
	free(philo);
}
