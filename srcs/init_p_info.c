/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_p_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:59:30 by wchen             #+#    #+#             */
/*   Updated: 2023/03/07 01:52:54 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool set_ready_mutex(t_p_info *p_info)
{
	long long i;

	pthread_mutex_t	*ready_mutex;
	ready_mutex = malloc(sizeof(pthread_mutex_t) * p_info->p_num);
	if (!ready_mutex)
		return (false);
	i = 0;
	while (i < p_info->p_num)
	{
		pthread_mutex_init(&ready_mutex[i], NULL);
		pthread_mutex_lock(&ready_mutex[i]);
		i ++;
	}
	p_info->ready_mutex = ready_mutex;
	return true;
}

static bool	init_mutex(long long num, t_p_info *p_info)
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*monitor;
	int				i;

	fork = malloc(sizeof(pthread_mutex_t) * num);
	if (!fork)
		return (false);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	p_info->fork_mutex = fork;
	monitor = malloc(sizeof(pthread_mutex_t));
	if (!monitor)
		return (false);
	pthread_mutex_init(monitor, NULL);
	p_info->monitor_mutex = monitor;
	if (set_ready_mutex(p_info) == false)
		return (false);
	return (true);
}

static bool	init_input_var(t_p_info *p_info, char **argv)
{
	int	i;

	i = 2;
	while (argv[i] != NULL)
	{
		if (i == 2 && ft_atoll(argv[i]) != 0)
			p_info->t_die = ft_atoll(argv[i]);
		else if (i == 3 && ft_atoll(argv[i]) != 0)
			p_info->t_eat = ft_atoll(argv[i]);
		else if (i == 4 && ft_atoll(argv[i]) != 0)
			p_info->t_sleep = ft_atoll(argv[i]);
		else if (i == 5 && ft_atoll(argv[i]) != 0)
			p_info->m_eat = ft_atoll(argv[i]);
		else
			return (printf_return_int("wrong variable\n", false));
		i++;
	}
	if (argv[i] != NULL || i < 5)
		return (printf_return_int("wrong variable\n", false));
	return (true);
}

static bool	init_info_var(t_p_info *p_info, char **argv)
{
	pthread_t	*t_thread;

	t_thread = malloc(sizeof(pthread_t));
	if (!t_thread)
		return (false);
	p_info->t_thread = t_thread;
	p_info->die = false;
	p_info->is_must_eat = false;
	if (init_input_var(p_info, argv) == false)
		return (false);
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
