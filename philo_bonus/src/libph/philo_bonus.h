/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:21 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/18 17:07:14 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

typedef unsigned int	t_uint;
typedef struct timeval	t_time;

enum
{
	THINK,
	FORK_1,
	FORK_2,
	EAT,
	SLEEP
};

# define MSG_SLEEP "is sleeping\n"
# define MSG_EAT "is eating\n"
# define MSG_FORK "has taken a fork\n"
# define MSG_THINK "is thinking\n"
# define MSG_DIED "died\n"

typedef struct s_args
{
	sem_t	*forks;
	sem_t	*log_msg;
	int		*pids;
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_ammount;
	long	time_start;
}			t_args;

#define SEM_FRK "sem_frk"
#define SEM_LOG "sem_log"

int		ph_atoi(const char *str);
size_t	ph_putstr(int fd, const char *s);
int		ph_errorm(int error_code, char *error_message);
long	ph_timestamp(void);
void	ph_usleep_till(long time);

void	*ph_init_philosphers(t_args *args);
void	ph_process(t_args *args, int id);
void	ph_clear_philosophers(t_args *args);

#endif
