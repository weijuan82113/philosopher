/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:06:52 by wchen             #+#    #+#             */
/*   Updated: 2023/03/06 00:26:35 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q philo");
// }

int	main(int argc, char **argv)
{
	t_philo		*philo;
	long long	p_num;

	if (argc < 2)
		return (printf_return_int("wrong variable\n", 1));
	p_num = ft_atoll(argv[1]);
	if (p_num == 0)
		return (printf_return_int("wrong variable\n", 1));
	philo = philo_init(p_num, p_info_init(p_num, argv));
	if (philo == NULL)
		return (1);
	if (create_thread(p_num, philo) == false)
		return (printf_return_int("error occuring in pthread_create\n", 1));
	if (join_thread(p_num, philo) == false)
		return (printf_return_int("error occuring in pthread_join\n", 1));
	free_all(philo);
	return (0);
}
