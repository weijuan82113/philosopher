/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:32:25 by wchen             #+#    #+#             */
/*   Updated: 2023/03/06 00:20:28 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_state_type state, long long index, long long now_time)
{
	if (state == e_eat)
		printf("%lld %lld %s\n", now_time, index, EAT);
	else if (state == e_sleep)
		printf("%lld %lld %s\n", now_time, index, SLEEP);
	else if (state == e_think)
		printf("%lld %lld %s\n", now_time, index, THINK);
	else if (state == e_die)
		printf("%lld %lld %s\n", now_time, index, DIE);
	else
		printf("%lld %lld %s\n", now_time, index, FORK);
}
