/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:10:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/04 18:07:56 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_think(int id, t_args *args, t_data *data);
static int	ph_eat(t_args *args, t_data *data);
static int	ph_sleep(t_args *args, t_data *data);
static void	ph_parse(t_args *args, t_data *data, int id);

void	*ph_process(t_args *args, int id)
{
	t_data	data;

	if (id == args->philo_count - 1)
		sem_post(args->log_msg);
	ph_parse(args, &data, id);
	if (pthread_create(&args->philo.self, NULL, ph_monitor, args) == -1)
		return (NULL);
	//if (pthread_detach(args->philo.self) == -1)
	//	return (NULL);
	while (1)
	{
		if (ph_think(id, args, &data) == -1)
			break ;
		if (ph_eat(args, &data) == -1)
			break ;
		if (ph_sleep(args, &data) == -1)
			break ;
	}
	sem_close(args->forks);
	sem_close(args->log_msg);
	pthread_join(args->philo.self, NULL);
	exit(1);
	return (NULL);
}

static int	ph_think(int id, t_args *args, t_data *data)
{
	if (ph_log(args, data, "is thinking", 0) == -1)
		return (-1);
	if ((id % 2) == 0 && (data->philo_count) > 1)
		usleep(1000);
	sem_wait(args->forks);
	if (ph_log(args, data, "has taken a fork", 0) == -1)
		return (-1);
	if (data->philo_count == 1)
		ph_usleep_till(data->last_meal,
			data->time_to_die * 1000, ph_timestamp() + (data->time_to_die * 1000));
	else
		sem_wait(args->forks);
	if (ph_log(args, data, "has taken a fork", 0) == -1)
		return (-1);
	return (0);
}

static int	ph_eat(t_args *args, t_data *data)
{
	if (ph_log(args, data, "is eating", (data->time_to_eat)) == -1)
		return (-1);
	sem_post(args->forks);
	sem_post(args->forks);
	if ((data->eat_count) == (data->eat_ammount))
	{
		exit(0);
	}
	return (0);
}

static int	ph_sleep(t_args *args, t_data *data)
{
	if (ph_log(args, data, "is sleeping", (data->time_to_sleep)) == -1)
		return (-1);
	return (0);
}

static void	ph_parse(t_args *args, t_data *data, int id)
{
	free(args->pids);
	(data->eat_count) = 0;
	(args->philo.id) = id;
	(data->eat_ammount) = (args->eat_ammount);
	(data->time_to_die) = (args->time_to_die);
	(data->time_to_eat) = (args->time_to_eat);
	(data->time_to_sleep) = (args->time_to_sleep);
	(data->last_meal) = (args->philo.last_meal);
	(data->philo_count) = (args->philo_count);
	//(args->time_start) = ph_timestamp();
	//(args->philo.last_meal) = (args->time_start);
}
