/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_p_info_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:05:02 by wchen             #+#    #+#             */
/*   Updated: 2023/06/04 16:12:34 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	init_input_var(t_p_info *p_info, char **argv)
{
	int			i;
	long long	t;

	i = 2;
	while (argv[i] != NULL)
	{
		t = ft_atoll(argv[i]);
		if (i == 2 && t > 0)
			p_info->t_die = t;
		else if (i == 3 && t > 0)
			p_info->t_eat = t;
		else if (i == 4 && t > 0)
			p_info->t_sleep = t;
		else if (i == 5 && t > 0)
			p_info->m_eat = t;
		else
			return (printf_return_int("wrong variable\n", false));
		i++;
	}
	return (true);
}

bool	init_info_var(t_p_info *p_info, char **argv)
{
	pthread_t	*t_thread;

	t_thread = malloc(sizeof(pthread_t));
	if (!t_thread)
		return (false);
	p_info->t_thread = t_thread;
	p_info->die = false;
	p_info->is_must_eat = false;
	if (init_input_var(p_info, argv) == false)
		return (false);
	return (true);
}
