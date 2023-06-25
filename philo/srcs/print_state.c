/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:32:25 by wchen             #+#    #+#             */
/*   Updated: 2023/06/25 13:10:24 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_state_type state, t_philo *philo)
{
	long long				philo_no;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	if (!is_finish(philo))
	{
		philo_no = philo->index + 1;
		if (state == e_eat)
			printf("%lld %lld %s\n", get_now_time(philo), philo_no, EAT);
		else if (state == e_sleep)
			printf("%lld %lld %s\n", get_now_time(philo), philo_no, SLEEP);
		else if (state == e_think)
			printf("%lld %lld %s\n", get_now_time(philo), philo_no, THINK);
		else if (state == e_die)
		{
			set_die(philo);
			printf("\x1b[33m%lld %lld %s\n\x1b[0m", get_now_time(philo),
				philo_no, DIE);
		}
		else
			printf("%lld %lld %s\n", get_now_time(philo), philo_no, FORK);
	}
	pthread_mutex_unlock(&mutex);
}
