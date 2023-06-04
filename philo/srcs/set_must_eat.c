/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_must_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:53:23 by wchen             #+#    #+#             */
/*   Updated: 2023/06/04 09:04:49 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	judge_must_eat(t_philo *philo)
{
	if (philo->p_info->m_eat > 0)
		return (true);
	return (false);
}
void	set_must_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->p_info->is_must_eat_mutex);
	philo->p_info->is_must_eat = true;
	pthread_mutex_unlock(philo->p_info->is_must_eat_mutex);
}

