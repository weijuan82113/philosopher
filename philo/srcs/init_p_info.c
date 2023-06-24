/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_p_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:59:30 by wchen             #+#    #+#             */
/*   Updated: 2023/06/22 23:48:11 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	p_info_mutex_init(t_p_info *p_info)
{
	p_info->die_mutex = malloc(sizeof(pthread_mutex_t));
	if (!p_info->die_mutex)
		return (false);
	p_info->start_time_mutex = malloc(sizeof(pthread_mutex_t));
	if (!p_info->start_time_mutex)
		return (false);
	p_info->waiter_mutex = malloc(sizeof(pthread_mutex_t));
	if (!p_info->waiter_mutex)
		return (false);
	p_info->is_must_eat_mutex = malloc(sizeof(pthread_mutex_t));
	if (!p_info->is_must_eat_mutex)
		return (false);
	return (true);
}

static bool	init_mutex(long long num, t_p_info *p_info)
{
	int	i;

	p_info->fork_mutex = malloc(sizeof(pthread_mutex_t) * num);
	if (!p_info->fork_mutex)
		return (false);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&p_info->fork_mutex[i], NULL);
		i++;
	}
	if (p_info_mutex_init(p_info) == false)
		return (false);
	pthread_mutex_init(p_info->die_mutex, NULL);
	pthread_mutex_init(p_info->start_time_mutex, NULL);
	pthread_mutex_init(p_info->waiter_mutex, NULL);
	pthread_mutex_init(p_info->is_must_eat_mutex, NULL);
	return (true);
}

t_p_info	*p_info_init(long long num, char **argv)
{
	t_p_info	*p_info;

	p_info = malloc(sizeof(t_p_info));
	if (!p_info)
		return (NULL);
	p_info->p_num = num;
	if (init_mutex(num, p_info) == false)
		return (NULL);
	if (init_info_var(p_info, argv) == false)
		return (NULL);
	return (p_info);
}
