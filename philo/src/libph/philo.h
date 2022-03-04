/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:21 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/02 16:31:27 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;
typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

enum
{
	THINK,
	FORK_1,
	FORK_2,
	EAT,
	SLEEP
};
# define MSG_SLEEP "is sleeping"
# define MSG_EAT "is eating"
# define MSG_FORK "has taken a fork"
# define MSG_THINK "is thinking"
# define STATES_COUNT 5

typedef struct s_phil
{
	int			alive;
	t_thread	self;
	t_mutex		*left_fork;
	t_mutex		right_fork;
	t_ulong		last_meal;
}				t_phil;

typedef struct s_data
{
	int		id;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		eat_ammount;
	int		eat_count;
	int		philo_count;
	t_ulong	last_meal;
	t_phil	*self;
}			t_data;

typedef struct s_args
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_ammount;
	int		over;
	t_ulong	time_start;
	t_mutex	m1;
	t_phil	*p;
}			t_args;

int		ph_atoi(const char *str);
size_t	ph_putstr(int fd, const char *s);
int		ph_errorm(int error_code, char *error_message);
t_ulong	ph_timestamp(void);
void	ph_usleep_till(t_data *data, t_ulong time);

void	*ph_init_philosophers(t_args *args);
void	ph_wait_philosophers(t_args *args);
void	ph_clear_philosophers(t_args *args);

void	*ph_routine(void *args_ptr);
int		ph_log(t_args *args, t_data *data, char *str, t_ulong sleep_time);

#endif
