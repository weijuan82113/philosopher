/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:32:25 by wchen             #+#    #+#             */
/*   Updated: 2023/03/04 20:07:50 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_state(t_state_type state, long long index, t_p_info *p_info)
{
	// printf("\n");
	// printf("now time before : %lld\n", get_time() - p_info->start_time_stamp);
	if (state == e_eat)
		printf ("%lld %lld %s\n", p_info->now_time, index, EAT);
	else if (state == e_sleep)
		printf ("%lld %lld %s\n", p_info->now_time, index, SLEEP);
	else if (state == e_think)
		printf ("%lld %lld %s\n", p_info->now_time, index, THINK);
	else if (state == e_die)
		printf ("%lld %lld %s\n", p_info->now_time, index, DIE);
	else
		printf ("%lld %lld %s\n", p_info->now_time, index, FORK);
	// printf("now time after : %lld\n", get_time() - p_info->start_time_stamp);
	// printf("\n");
}
