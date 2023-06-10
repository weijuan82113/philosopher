/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:32:25 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 15:23:03 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_state_type state, long long index, long long now_time)
{
	long long	philo_no;

	philo_no = index + 1;
	if (state == e_eat)
		printf("%lld %lld %s\n", now_time, philo_no, EAT);
	else if (state == e_sleep)
		printf("%lld %lld %s\n", now_time, philo_no, SLEEP);
	else if (state == e_think)
		printf("%lld %lld %s\n", now_time, philo_no, THINK);
	else if (state == e_die)
		printf("\x1b[33m%lld %lld %s\n\x1b[0m", now_time, philo_no, DIE);
	else
		printf("%lld %lld %s\n", now_time, philo_no, FORK);
}
