/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:10:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/21 17:22:50 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_think(int id, t_args *args);
static int	ph_eat(t_args *args);
static int	ph_sleep(t_args *args);

void	*ph_process(t_args *args, int id)
{
	free(args->pids);
	(args->philo.id) = id;
	(args->philo.eat_count) = 0;
	(args->time_start) = ph_timestamp();
	(args->philo.last_meal) = (args->time_start);
	while (1)
	{
		if (ph_think(id, args) == -1)
			break ;
		if (ph_eat(args) == -1)
			break ;
		if (ph_sleep(args) == -1)
			break ;
		usleep(100);
	}
	//(args->philo.state) = -1;
	exit(1);
	return (NULL);
}

static int	ph_think(int id, t_args *args)
{
	if (args->time_to_die == -1)
		return (-1);
	(args->philo.state) = THINK;
	usleep(100);
	if ((id % 2) == 0 && (args->philo_count) > 1)
		usleep(500);
	sem_wait(args->forks);
	if (args->time_to_die == -1)
		return (-1);
	(args->philo.state) = FORK_1;
	usleep(100);
	sem_wait(args->forks);
	if (args->time_to_die == -1)
		return (-1);
	(args->philo.state) = FORK_2;
	usleep(100);
	return (0);
}

static int	ph_eat(t_args *args)
{
	if (args->time_to_die == -1)
		return (-1);
	(args->philo.state) = EAT;
	usleep(100);
	if (args->eat_ammount > 0)
		(args->philo.eat_count) += 1;
	(args->philo.last_meal) = ph_timestamp();
	ph_usleep_till((args->philo.last_meal) + args->time_to_eat);
	sem_post(args->forks);
	sem_post(args->forks);
	if (args->eat_ammount > 0
		&& (args->philo.eat_count) == (args->eat_ammount))
		exit(0);
	return (0);
}

static int	ph_sleep(t_args *args)
{
	if (args->time_to_die == -1)
		return (-1);
	(args->philo.state) = SLEEP;
	usleep(100);
	ph_usleep_till(ph_timestamp() + args->time_to_sleep);
	return (0);
}
