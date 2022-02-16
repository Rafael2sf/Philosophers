/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:21 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/16 15:31:22 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <mlx.h>

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
# define MSG_SLEEP "is sleeping"
# define MSG_EAT "is eating"
# define MSG_FORK "has taken a fork"
# define MSG_THINK "is thinking"
# define STATES_COUNT 5

typedef struct s_philo
{
	int				state;
	pthread_t		self;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	long			last_meal;
	int				eat_count;
}			t_philo;

typedef struct s_args
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_ammount;
	long	time_start;
	t_philo	**philo;
}			t_args;

int		ph_atoi(const char *str);
size_t	ph_putstr(int fd, const char *s);
int		ph_errorm(int error_code, char *error_message);
long	ph_timestamp(void);
void	ph_usleep_till(long time);

void	*ph_init_philosophers(t_args *args);
void	*ph_think_eat_sleep(void *args_ptr);
void	ph_monitor_philosophers(t_args *args);
void	ph_clear_philosophers(t_args *args);

#endif
