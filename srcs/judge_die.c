/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:05:00 by wchen             #+#    #+#             */
/*   Updated: 2023/03/03 00:29:44 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


bool is_someone_die(t_philo *philo)
{
	if (philo->p_info->die == true)
		return (true);
	return (false);
}

void set_die(t_philo *philo)
{
	philo->p_info->die = true;
	philo->state = e_die;
}


bool judge_die(t_philo *philo)
{
	if(philo->starving_time > philo->p_info->t_die)
		return true;
	return false;
}
