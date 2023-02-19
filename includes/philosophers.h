/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:55:33 by wchen             #+#    #+#             */
/*   Updated: 2023/02/20 00:47:12 by wchen            ###   ########.fr       */
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
	long long			philo_num;
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
/*            main            */
/* ************************** */

/* ************************** */
/*            srcs            */
/* ************************** */
t_p_info	*p_info_init(long long num);
t_philo		*philo_init(int num, t_p_info *p_info);

#endif
