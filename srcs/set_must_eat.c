/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_must_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:53:23 by wchen             #+#    #+#             */
/*   Updated: 2023/03/04 20:07:02 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_must_eat(t_philo *philo)
{
	philo->p_info->is_must_eat = true;
}

bool	judge_must_eat(t_philo *philo)
{
	if (philo->p_info->m_eat > 0)
		return true;
	return false;
}
