/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:21 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/10 14:10:42 by rafernan         ###   ########.fr       */
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

typedef struct s_philo
{
	int			id;
	int			eat_count;
	t_ulong		last_meal;
	t_ulong		time_start;
	t_thread	self;
	int			dead;
}				t_philo;

typedef struct s_args
{
	pid_t		*pids;
	int			eat_ammount;
	int			time_to_die;
	int			philo_count;
	int			time_to_eat;
	int			time_to_sleep;
	sem_t		*sem__frks;
	sem_t		*sem__logs;
	sem_t		*sem__stat;
	t_philo		me;
}				t_args;

# define SEM__FRKS "./sem_frks"
# define SEM__LOGS "./sem_logs"
# define SEM__STAT "./sem_stat"

size_t	ph_putstr(int fd, const char *s);
int		ph_atoi(const char *str);
int		ph_errorm(int error_code, char *error_message, t_args *args);
t_ulong	ph_timestamp(void);
void	ph_usleep_till(t_ulong last_meal, t_ulong time_to_die, t_ulong ammount);
void	ph_log(t_args *args, char *msg, int ms);

int		ph_init_philosophers(t_args *args);
void	ph_routine(t_args *args, int id);
void	*ph_monitor(void *args_ptr);
void	ph_wait_philosophers(t_args *args);

#endif
