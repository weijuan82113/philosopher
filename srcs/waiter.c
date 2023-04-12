/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:29:48 by wchen             #+#    #+#             */
/*   Updated: 2023/03/07 01:52:45 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_starving_time_longest(t_philo *philo, int index, t_philo *waiter)
{
	long long	right;
	long long	left;

	right = (index + 1) / philo->p_info->p_num;
	if (index - 1 < 0)
		left = index - 1 + philo->p_info->p_num;
	else
		left = index - 1;
	if (philo->starving_time >= waiter[right].starving_time
		&& philo->starving_time >= waiter[left].starving_time)
		return (true);
	return (false);
}

bool	waiter_judge(t_philo *philo)
{
	if (philo->p_info->p_num == 1)
		return (true);
	if (is_starving_time_longest(philo, philo->index,
			philo->p_info->waiter) == true)
	{
		//printf("index :%lld true\n", philo->index);
		return (true);
	}
	//printf("index :%lld false\n", philo->index);
	return (false);
}
