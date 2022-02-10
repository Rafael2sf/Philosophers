/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:33:21 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/10 18:04:51 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/libft.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef unsigned int	t_uint;

typedef struct s_philo
{
	int				pos;
	pthread_t		self;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	struct timeval	timer;
}			t_philo;

typedef struct s_args
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_ammount;
	t_philo	**philo;
}			t_args;

int		ph_errorm(int error_code, char *error_message);
void	*ph_init_philosophers(t_args *args);
void	ph_clear_philosophers(t_args *args);

#endif
