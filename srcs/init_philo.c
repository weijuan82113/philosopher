/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:05:08 by wchen             #+#    #+#             */
/*   Updated: 2023/02/20 00:43:14 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *philo_init(int num, t_p_info *p_info)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * num);
	if (!philo)
	{
		printf("error occuring in malloc_t_philo\n");
		return NULL;
	}
	i = 0;
	while (i < num)
	{
		(philo[i]).p_thread = malloc(sizeof(pthread_t));
		if (!(philo[i]).p_thread)
		{
			printf("error occuring in malloc_pthread\n");
			return NULL;
		}
		if (gettimeofday(&(philo[i]).last_time_eat, NULL) != 0)
		{
			printf("error ocurring in get time\n");
			return NULL;
		}
		philo[i].index = i;
		philo[i].p_info = p_info;
		i ++;
	}
	return (philo);
}

t_p_info *p_info_init(long long num)
{
	int 			i;
	t_p_info		*p_info;
	pthread_mutex_t	*fork;

	p_info = malloc(sizeof(t_p_info));
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
	p_info->philo_num = num;
	return (p_info);
}
