/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:55:33 by wchen             #+#    #+#             */
/*   Updated: 2023/03/05 18:47:34 by wchen            ###   ########.fr       */
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
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIE	"died"
# define FORK	"has taken a fork"


/* ************************** */
/*          typedef           */
/* ************************** */
/* struct */
typedef struct s_p_info		t_p_info;
typedef struct s_philo		t_philo;

/* enum */
typedef enum e_state_type	t_state_type;
typedef enum e_fork_type	t_fork_type;

enum	e_state_type
{
	e_init,
	e_think,
	e_eat,
	e_sleep,
	e_die,
	e_fork,
	e_finish,
};

enum	e_fork_type
{
	e_dirty,
	e_clean,
};

/* ************************** */
/*          struct            */
/* ************************** */
struct	s_p_info
{
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		*monitor_mutex;
	pthread_t			*t_thread;
	long long			p_num;
	long long			t_die;
	long long			t_eat;
	long long			t_sleep;
	long long			m_eat;
	bool				die;
	bool				ready;
	bool				is_must_eat;
	long long			now_time;
	long long			start_time_stamp;
	t_philo				*waiter;
};

struct	s_philo
{
	long long			index;
	pthread_t			*p_thread;
	pthread_t			*m_thread;
	t_p_info			*p_info;
	pthread_mutex_t		*philo_mutex;
	long long 			last_eat_time;
	t_state_type		state;
	long long			starving_time;
	long long			eat_count;
	bool				philo_must_eat;
};

/* ************************** */
/*            srcs            */
/* ************************** */

t_p_info		*p_info_init(long long num, char **argv);
t_philo			*philo_init(long long num, t_p_info *p_info);
void			*printf_return(char *print_str, void *ret);
int				printf_return_int(char *print_str, int ret);
long long		get_time(void);
void			set_starving_time(t_philo *philo);
bool			set_now_time(t_philo *philo);
void			set_last_eat_time(t_philo *philo);
bool			judge_die(t_philo *philo);
void			free_all(t_philo *philo);
bool 			is_someone_die(t_philo *philo);
t_state_type	judge_state(t_philo *philo);
bool			judge_must_eat(t_philo *philo);
bool			is_everyone_eat(t_philo *philo);
void			print_state(t_state_type state, long long index, t_p_info *p_info);
void			do_action(t_state_type state, long long index, t_philo *philo);
void			set_die(t_philo *philo);
void			set_must_eat(t_philo *philo);
bool			is_finish(t_philo *philo);
bool			waiter_judge(t_philo *philo);
#endif
