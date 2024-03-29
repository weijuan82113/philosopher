/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:05:08 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 18:25:27 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	common_mutex_init(t_common_mutex *c_mutex)
{
	c_mutex->last_eat_mutex = malloc(sizeof(pthread_mutex_t));
	if (!c_mutex->last_eat_mutex)
		return (false);
	c_mutex->starving_time_mutex = malloc(sizeof(pthread_mutex_t));
	if (!c_mutex->starving_time_mutex)
		return (false);
	c_mutex->state_mutex = malloc(sizeof(pthread_mutex_t));
	if (!c_mutex->state_mutex)
		return (false);
	c_mutex->must_eat_mutex = malloc(sizeof(pthread_mutex_t));
	if (!c_mutex->must_eat_mutex)
		return (false);
	c_mutex->eat_flag_mutex = malloc(sizeof(pthread_mutex_t));
	if (!c_mutex->eat_flag_mutex)
		return (false);
	return (true);
}

static void	init_philo_state(long long i, t_philo *philo, t_p_info *p_info)
{
	pthread_mutex_init((philo[i]).philo_mutex, NULL);
	philo[i].index = i;
	philo[i].p_info = p_info;
	philo[i].state = e_init;
	philo[i].philo_must_eat = false;
	philo[i].eat_count = 0;
	pthread_mutex_init((philo[i]).c_mutex->last_eat_mutex, NULL);
	pthread_mutex_init((philo[i]).c_mutex->starving_time_mutex, NULL);
	pthread_mutex_init((philo[i]).c_mutex->state_mutex, NULL);
	pthread_mutex_init((philo[i]).c_mutex->eat_flag_mutex, NULL);
	pthread_mutex_init((philo[i]).c_mutex->must_eat_mutex, NULL);
}

static void	lock_philo_mutex(t_philo *philo)
{
	long long		i;

	i = 0;
	while (i < philo->p_info->p_num)
	{
		pthread_mutex_lock((philo[i]).philo_mutex);
		i++;
	}
}

static bool	init_philo_var(t_philo *philo, t_p_info *p_info, long long num)
{
	long long	i;

	i = 0;
	while (i < num)
	{
		(philo[i]).p_thread = malloc(sizeof(pthread_t));
		if (!(philo[i]).p_thread)
			return (printf_return_int("\
			error occuring in malloc_pthread\n", false));
		(philo[i]).m_thread = malloc(sizeof(pthread_t));
		if (!(philo[i]).m_thread)
			return (printf_return_int("\
			error occuring in malloc_pthread\n", false));
		(philo[i]).philo_mutex = malloc(sizeof(pthread_mutex_t));
		if (!(philo[i]).philo_mutex)
			return (printf_return_int("error occuring in mutex init\n", false));
		(philo[i]).c_mutex = malloc(sizeof(t_common_mutex));
		philo[i].eat_flag = 0;
		if (!(philo[i].c_mutex) || !common_mutex_init(philo[i].c_mutex))
			return (printf_return_int("error occuring in mutex init\n", false));
		init_philo_state(i, philo, p_info);
		i++;
	}
	lock_philo_mutex(philo);
	philo->p_info->waiter = philo;
	return (true);
}

t_philo	*philo_init(long long num, t_p_info *p_info)
{
	t_philo	*philo;

	if (!p_info)
		return (NULL);
	philo = malloc(sizeof(t_philo) * num);
	if (!philo)
		printf_return("error occuring in malloc_t_philo\n", NULL);
	if (init_philo_var(philo, p_info, num) == false)
		return (NULL);
	return (philo);
}
