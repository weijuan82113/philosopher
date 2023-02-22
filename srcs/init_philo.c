/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 23:05:08 by wchen             #+#    #+#             */
/*   Updated: 2023/02/23 00:01:46 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *philo_init(int num, t_p_info *p_info)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * num);
	if (!philo)
		printf_return("error occuring in malloc_t_philo\n", NULL);
	i = 0;
	while (i < num)
	{
		(philo[i]).p_thread = malloc(sizeof(pthread_t));
		if (!(philo[i]).p_thread)
			return (printf_return("error occuring in malloc_pthread\n", NULL));
		if (gettimeofday(&(philo[i]).last_time_eat, NULL) != 0)
			printf_return("error ocurring in get time\n", NULL);
		philo[i].index = i;
		philo[i].p_info = p_info;
		i ++;
	}
	return (philo);
}

t_p_info *p_info_init(long long num, char **argv)
{
	int 			i;
	t_p_info		*p_info;
	pthread_mutex_t	*fork;

	p_info = malloc(sizeof(t_p_info));
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
	i = 2;
	while (argv[i] != NULL)
	{
		if (i == 2 && ft_atoll(argv[i]) != 0)
			p_info->t_die = ft_atoll(argv[i]);
		else if (i == 3 && ft_atoll(argv[i]) != 0)
			p_info->t_eat = ft_atoll(argv[i]);
		else if (i == 4 && ft_atoll(argv[i]) != 0)
			p_info->t_sleep = ft_atoll(argv[i]);
		else
			return (printf_return("worng variable\n", NULL));
		i ++;
	}
	if (argv[i] != NULL)
		return (printf_return("worng variable\n", NULL));
	return (p_info);
}
