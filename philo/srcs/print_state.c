/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:32:25 by wchen             #+#    #+#             */
/*   Updated: 2023/06/24 11:11:25 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_state_type state, t_philo *philo, long long now_time)
{
	long long				philo_no;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	if (!is_finish(philo))
	{
		philo_no = philo->index + 1;
		if (state == e_eat)
			printf("%lld %lld %s\n", now_time, philo_no, EAT);
		else if (state == e_sleep)
			printf("%lld %lld %s\n", now_time, philo_no, SLEEP);
		else if (state == e_think)
			printf("%lld %lld %s\n", now_time, philo_no, THINK);
		else if (state == e_die)
		{
			set_die(philo);
			printf("\x1b[33m%lld %lld %s\n\x1b[0m", now_time, philo_no, DIE);
		}
		else
			printf("%lld %lld %s\n", now_time, philo_no, FORK);
	}
	pthread_mutex_unlock(&mutex);
}
