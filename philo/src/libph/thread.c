/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:10:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/22 12:07:04 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_think(int id, t_args *args);
static int	ph_eat(int id, t_args *args, int *eat_count);
static int	ph_sleep(int id, t_args *args);

void	*ph_thread(void *args_ptr)
{
	t_uint		id;
	t_args		*args;
	int			eat_count;
	static int	id_counter;

	eat_count = 0;
	id = id_counter++;
	args = (t_args *)(args_ptr);
	(args->philo[id]->last_meal) = ph_timestamp();
	while (id_counter < args->philo_count)
		(void)(id_counter);
	if (args->time_start == 0)
		(args->time_start) = ph_timestamp();
	while (1)
	{
		if (ph_think(id, args) == -1)
			break ;
		if (ph_eat(id, args, &eat_count) == -1)
			break ;
		if (ph_sleep(id, args) == -1)
			break ;
		usleep(100);
	}
	(args->philo[id]->state = -1);
	return (NULL);
}

static int	ph_think(int id, t_args *args)
{
	if (args->time_to_die == -1)
		return (-1);
	(args->philo[id]->state) = THINK;
	usleep(100);
	if ((id % 2) == 0)
		pthread_mutex_lock(&args->philo[id]->right_fork);
	else
		pthread_mutex_lock(args->philo[id]->left_fork);
	if (args->time_to_die == -1)
		return (-1);
	(args->philo[id]->state) = FORK_1;
	usleep(100);
	if ((id % 2) == 0)
		pthread_mutex_lock(args->philo[id]->left_fork);
	else
		pthread_mutex_lock(&args->philo[id]->right_fork);
	if (args->time_to_die == -1)
		return (-1);
	(args->philo[id]->state) = FORK_2;
	usleep(100);
	return (0);
}

static int	ph_eat(int id, t_args *args, int *eat_count)
{
	(args->philo[id]->state) = EAT;
	if (args->eat_ammount == -1 || *eat_count < args->eat_ammount)
	{
		if (*eat_count != -1)
			(*eat_count)++;
		if (args->time_to_die == -1)
			return (-1);
		(args->philo[id]->last_meal) = ph_timestamp();
		ph_usleep_till(ph_timestamp() + args->time_to_eat);
	}
	pthread_mutex_unlock(args->philo[id]->left_fork);
	pthread_mutex_unlock(&args->philo[id]->right_fork);
	if (*eat_count == args->eat_ammount)
		return (-1);
	return (0);
}

static int	ph_sleep(int id, t_args *args)
{
	if (args->time_to_die == -1)
		return (-1);
	(args->philo[id]->state) = SLEEP;
	usleep(100);
	ph_usleep_till(ph_timestamp() + args->time_to_sleep);
	return (0);
}
