/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:55:33 by wchen             #+#    #+#             */
/*   Updated: 2023/02/23 00:08:05 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "../utils/includes/libutils.h"

/* ************************** */
/*           macro            */
/* ************************** */

/* ************************** */
/*          typedef           */
/* ************************** */
/* struct */
typedef struct s_p_info		t_p_info;
typedef struct s_philo		t_philo;


/* enum */



/* ************************** */
/*          struct            */
/* ************************** */
struct s_p_info
{
	pthread_mutex_t		*fork_mutex;
	long long			p_num;
	long long			t_die;
	long long			t_eat;
	long long			t_sleep;
	long long			m_eat;
};

struct s_philo
{
	long long			index;
	pthread_t			*p_thread;
	t_p_info			*p_info;
	struct timeval 		last_time_eat;
	struct timeval		now;
};

/* ************************** */
/*           enum             */
/* ************************** */

/* ************************** */
/*            srcs            */
/* ************************** */

t_p_info	*p_info_init(long long num, char **argv);
t_philo		*philo_init(int num, t_p_info *p_info);
void		*printf_return(char *print_str, void *ret);

#endif
