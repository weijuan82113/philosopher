/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:05:08 by wchen             #+#    #+#             */
/*   Updated: 2023/03/05 18:27:31 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *philo_init(long long num, t_p_info *p_info)
{
	t_philo		*philo;
	long long	i;

	if (!p_info)
		return NULL;
	philo = malloc(sizeof(t_philo) * num);
	if (!philo)
		printf_return("error occuring in malloc_t_philo\n", NULL);
	i = 0;
	while (i < num)
	{
		(philo[i]).p_thread = malloc(sizeof(pthread_t));
		if (!(philo[i]).p_thread)
			return (printf_return("error occuring in malloc_pthread\n", NULL));
		(philo[i]).m_thread = malloc(sizeof(pthread_t));
		if (!(philo[i]).m_thread)
			return (printf_return("error occuring in malloc_pthread\n", NULL));
		(philo[i]).philo_mutex = malloc(sizeof(pthread_mutex_t));
		if (!(philo[i]).philo_mutex)
			return (printf_return("error occuring in mutex init\n", NULL));
		pthread_mutex_init((philo[i]).philo_mutex, NULL);
		philo[i].index = i;
		philo[i].p_info = p_info;
		philo[i].state = e_init;
		philo[i].philo_must_eat = false;
		philo[i].eat_count = 0;
		i ++;
	}
	philo->p_info->waiter = philo;
	return (philo);
}

t_p_info *p_info_init(long long num, char **argv)
{
	int 			i;
	t_p_info		*p_info;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*monitor;
	pthread_t		*t_thread;

	p_info = malloc(sizeof(t_p_info));
	if (!p_info)
		return NULL;
	p_info->p_num = num;
	fork = malloc(sizeof(pthread_mutex_t) * num);
	if (!fork)
		return NULL;
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&fork[i], NULL);
		i ++;
	}
	p_info->fork_mutex = fork;
	monitor = malloc(sizeof(pthread_mutex_t));
	if (!monitor)
		return NULL;
	pthread_mutex_init(monitor, NULL);
	p_info->monitor_mutex = monitor;
	t_thread = malloc(sizeof(pthread_t));
	if (!t_thread)
		return NULL;
	p_info->t_thread = t_thread;
	p_info->die = false;
	p_info->ready = false;
	p_info->is_must_eat = false;
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
			return (printf_return("wrong variable\n", NULL));
		i ++;
	}
	if (argv[i] != NULL || i < 5)
		return (printf_return("wrong variable\n", NULL));
	return (p_info);
}
