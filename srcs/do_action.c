/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:46:29 by wchen             #+#    #+#             */
/*   Updated: 2023/03/02 00:15:31 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(long long index, t_p_info *p_info)
{
	usleep(p_info->t_eat * 1000);
	pthread_mutex_unlock(&p_info->fork_mutex[index]);
	pthread_mutex_unlock(&p_info->fork_mutex[(index + 1) % p_info->p_num]);
}

void do_action(t_state_type state, long long index, t_p_info *p_info)
{
	if (state == e_eat)
		eat(index, p_info);
	if (state == e_sleep)
		usleep(p_info->t_sleep * 1000);
}
