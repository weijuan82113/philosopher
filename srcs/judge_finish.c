/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_finish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:05:00 by wchen             #+#    #+#             */
/*   Updated: 2023/03/06 00:12:59 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_someone_die(t_philo *philo)
{
	if (philo->p_info->die == true)
		return (true);
	return (false);
}

bool	is_everyone_eat(t_philo *philo)
{
	long long	i;
	long long	m_eat_count;

	i = 0;
	m_eat_count = 0;
	while (i < philo->p_info->p_num)
	{
		if (philo[i].philo_must_eat == true)
			m_eat_count++;
		i++;
	}
	if (m_eat_count == philo->p_info->p_num)
		return (true);
	return (false);
}

void	set_die(t_philo *philo)
{
	philo->p_info->die = true;
	philo->state = e_die;
}

bool	judge_die(t_philo *philo)
{
	if (philo->starving_time >= philo->p_info->t_die)
		return (true);
	return (false);
}

bool	is_finish(t_philo *philo)
{
	if (is_someone_die(philo) == true || philo->p_info->is_must_eat == true)
		return (true);
	return (false);
}
