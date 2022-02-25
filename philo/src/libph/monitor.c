/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:19:40 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/24 13:49:36 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_init_monitor(t_args *args, int *states);
static void	ph_monitor_loop(t_args *args, int *states, long time, int i);
char		*ph_msg(int state);

void	ph_monitor_philosophers(t_args *args)
{
	long	time;
	int		*states;
	int		i;

	i = 0;
	time = 0;
	states = malloc(sizeof(int) * args->philo_count);
	if (!states)
		return ;
	ph_init_monitor(args, states);
	ph_monitor_loop(args, states, time, i);
	free(states);
}

static void	ph_init_monitor(t_args *args, int *states)
{
	int		i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&args->m1);
		if (i < args->philo_count)
			states[i++] = THINK;
		else
			break ;
		pthread_mutex_unlock(&args->m1);
	}
	pthread_mutex_unlock(&args->m1);
	while (1)
	{
		pthread_mutex_lock(&args->m2);
		if (args->time_start != 0)
			break ;
		pthread_mutex_unlock(&args->m2);
		usleep(100);
	}
	pthread_mutex_unlock(&args->m2);
}

static void	ph_monitor_loop(t_args *args, int *states, long time, int i)
{
	(void)(args);
	(void)(states);
	(void)(time);
	(void)(i);
	return ;
}
