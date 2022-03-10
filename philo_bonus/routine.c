/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:37:40 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/10 14:20:31 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ph_set_data(t_args *args, int id);
static void	ph_forks(t_args *args);

void	ph_routine(t_args *args, int id)
{
	free(args->pids);
	ph_set_data(args, id);
	while (1)
	{
		ph_log(args, "is thinking", 0);
		ph_forks(args);
		ph_log(args, "is eating", args->time_to_eat);
		sem_post(args->sem__frks);
		sem_post(args->sem__frks);
		if (args->me.eat_count == args->eat_ammount)
		{
			sem_close(args->sem__frks);
			sem_close(args->sem__logs);
			sem_close(args->sem__stat);
			exit(0);
		}
		ph_log(args, "is sleeping", args->time_to_sleep);
	}
	sem_close(args->sem__frks);
	sem_close(args->sem__logs);
	sem_close(args->sem__stat);
	exit(1);
}

static void	ph_set_data(t_args *args, int id)
{
	(args->me.id) = id;
	if (args->me.id == args->philo_count - 1)
		sem_post(args->sem__stat);
	(args->me.eat_count) = 0;
	(args->me.dead) = 0;
	sem_wait(args->sem__stat);
	(args->me.time_start) = ph_timestamp();
	(args->me.last_meal) = (args->me.time_start);
	sem_post(args->sem__stat);
	usleep(10 * (args->philo_count / 2));
	if (pthread_create(&args->me.self, NULL, ph_monitor, args) == -1)
		ph_errorm(1, "pthread error", args);
	if (pthread_detach(args->me.self) == -1)
		ph_errorm(1, "pthread error", args);
}

static void	ph_forks(t_args *args)
{
	if ((args->me.id % 2) == 0 && (args->philo_count) > 1)
		usleep(5000);
	sem_wait(args->sem__frks);
	ph_log(args, "has taken a fork", 0);
	sem_wait(args->sem__frks);
	ph_log(args, "has taken a fork", 0);
}
