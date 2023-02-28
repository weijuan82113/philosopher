/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 01:05:00 by wchen             #+#    #+#             */
/*   Updated: 2023/03/01 01:38:19 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


bool is_die(t_philo *philo)
{
	if (philo->p_info->die == true)
		return (true);
	return (false);
}

bool judge_die(t_philo *philo)
{
	if(philo->starving_time > philo->p_info->t_die)
	{
		philo->p_info->die = true;
		return true;
	}
	return false;
}
