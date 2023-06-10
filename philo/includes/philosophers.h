/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchen <wchen@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:55:33 by wchen             #+#    #+#             */
/*   Updated: 2023/06/10 18:24:28 by wchen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../utils/includes/libutils.h"
# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ************************** */
/*           macro            */
/* ************************** */
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define FORK "has taken a fork"

/* ************************** */
/*          typedef           */
/* ************************** */
/* struct */
typedef struct s_p_info			t_p_info;
typedef struct s_philo			t_philo;
typedef struct s_common_mutex	t_common_mutex;

/* enum */
typedef enum e_state_type		t_state_type;
typedef enum e_fork_type		t_fork_type;

enum							e_state_type
{
	e_init,
	e_think,
	e_eat,
	e_sleep,
	e_die,
	e_fork,
	e_finish,
};

enum							e_fork_type
{
	e_dirty,
	e_clean,
};

/* ************************** */
/*          struct            */
/* ************************** */
struct							s_p_info
{
	pthread_mutex_t				*fork_mutex;
	pthread_mutex_t				*judge_mutex;
	pthread_t					*t_thread;
	long long					p_num;
	long long					t_die;
	long long					t_eat;
	long long					t_sleep;
	long long					m_eat;
	bool						die;
	pthread_mutex_t				*die_mutex;
	bool						is_must_eat;
	pthread_mutex_t				*is_must_eat_mutex;
	long long					start_time_stamp;
	pthread_mutex_t				*start_time_mutex;
	t_philo						*waiter;
	pthread_mutex_t				*waiter_mutex;
};

struct							s_philo
{
	long long					index;
	pthread_t					*p_thread;
	pthread_t					*m_thread;
	t_p_info					*p_info;
	pthread_mutex_t				*philo_mutex;
	long long					last_eat_time;
	t_state_type				state;
	long long					starving_time;
	long long					eat_count;
	bool						philo_must_eat;
	int							eat_flag;
	t_common_mutex				*c_mutex;
};

struct							s_common_mutex
{
	pthread_mutex_t				*last_eat_mutex;
	pthread_mutex_t				*starving_time_mutex;
	pthread_mutex_t				*state_mutex;
	pthread_mutex_t				*eat_flag_mutex;
	pthread_mutex_t				*must_eat_mutex;
};

/* ************************** */
/*            srcs            */
/* ************************** */

t_p_info						*p_info_init(long long num, char **argv);
t_philo							*philo_init(long long num, t_p_info *p_info);
void							*thread_philo_func(void *arg);
void							*thread_monitor_func(void *arg);
bool							create_thread(long long p_num, t_philo *philo);
bool							join_thread(long long p_num, t_philo *philo);
void							*printf_return(char *print_str, void *ret);
int								printf_return_int(char *print_str, int ret);
long long						get_time(void);
void							set_starving_time(t_philo *philo);
long long						get_now_time(t_philo *philo);
void							set_last_eat_time(t_philo *philo);
long long						judge_die_time(t_philo *philo);
void							free_all(t_philo *philo);
bool							is_someone_die(t_philo *philo);
t_state_type					judge_state(t_philo *philo);
bool							judge_must_eat(t_philo *philo);
bool							is_everyone_eat(t_philo *philo);
void							print_state(t_state_type state, long long index,
									long long now_time);
void							do_action(t_state_type state, long long index,
									t_philo *philo);
void							set_die(t_philo *philo);
void							set_must_eat(t_philo *philo);
bool							is_finish(t_philo *philo);
void							waiter_judge(t_philo *philo);
bool							init_info_var(t_p_info *p_info, char **argv);
#endif
