/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:55:33 by wchen             #+#    #+#             */
/*   Updated: 2023/02/28 01:55:45 by wchen            ###   ########.fr       */
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
#include <stdbool.h>

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
typedef enum e_state_type	t_state_type;

enum	e_state_type
{
	e_init,
	e_think,
	e_eat,
	e_sleep,
	e_die
};

/* ************************** */
/*          struct            */
/* ************************** */
struct	s_p_info
{
	pthread_mutex_t		*fork_mutex;
	long long			p_num;
	long long			t_die;
	long long			t_eat;
	long long			t_sleep;
	long long			m_eat;
	bool				die;
	bool				ready;
	long long			start_time_stamp;
};

struct	s_philo
{
	long long			index;
	pthread_t			*p_thread;
	t_p_info			*p_info;
	pthread_mutex_t		*philo_mutex;
	long long 			last_eat_time;
	t_state_type		state;
	long long			now_time;
	long long			starving_time;
};

/* ************************** */
/*           enum             */
/* ************************** */

/* ************************** */
/*            srcs            */
/* ************************** */

t_p_info	*p_info_init(long long num, char **argv);
t_philo		*philo_init(long long num, t_p_info *p_info);
void		*printf_return(char *print_str, void *ret);
int			printf_return_int(char *print_str, int ret);
long long	get_time(void);
bool		set_time(t_philo *philo);
bool		judge_die(t_philo *philo);
#endif
