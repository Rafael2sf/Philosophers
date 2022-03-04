/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:21 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/04 10:38:41 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef unsigned long	t_ulong;
typedef unsigned int	t_uint;
typedef struct timeval	t_time;
typedef pthread_t		t_thread;

typedef struct s_data
{
	int			eat_count;
	t_ulong		last_meal;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			eat_ammount;
	int			philo_count;
}				t_data;

typedef struct s_philo
{
	int			id;
	t_thread	self;
	t_ulong		last_meal;
}			t_philo;

typedef struct s_args
{
	int			*pids;
	sem_t		*forks;
	sem_t		*log_msg;
	t_philo		philo;
	t_ulong		time_start;
	int			eat_ammount;
	int			time_to_die;
	int			philo_count;
	int			time_to_eat;
	int			time_to_sleep;
	int			over;
}				t_args;

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

# define SEM_FRK "sem_frk"
# define SEM_LOG "sem_log"

int		ph_atoi(const char *str);
size_t	ph_putstr(int fd, const char *s);
int		ph_errorm(int error_code, char *error_message);
t_ulong	ph_timestamp(void);
void	ph_usleep_till(t_ulong last_meal, t_ulong time_to_die, t_ulong time);

void	*ph_init_philosphers(t_args *args);
void	*ph_process(t_args *args, int id);
void	*ph_monitor(void *args_ptr);
void	ph_clear_philosophers(t_args *args);
int		ph_log(t_args *args, t_data *data, char *str, t_ulong time);

#endif
