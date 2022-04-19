/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:51:33 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/11 16:45:19 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_parse_data(t_args *args, t_data *data, int *id_counter);
static int	ph_forks(t_args *args, t_data *data);
static int	ph_eat(t_args *args, t_data *data);

void	*ph_routine(void *args_ptr)
{
	static int	id_counter;
	t_data		data;
	t_args		*args;

	args = (t_args *)(args_ptr);
	ph_parse_data(args, &data, &id_counter);
	while (1)
	{
		if (ph_log(args, &data, "is thinking", 0) == -1)
			break ;
		if (ph_forks(args, &data) == -1)
			break ;
		if (data.eat_count == args->eat_ammount)
			break ;
		if (ph_log(args, &data, "is sleeping",
				((t_ulong)args->time_to_sleep) * 1000) == -1)
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&args->m__log);
	(data.self->alive) = 0;
	pthread_mutex_unlock(&args->m__log);
	return (NULL);
}

static void	ph_parse_data(t_args *args, t_data *data, int *id_counter)
{
	pthread_mutex_lock(&args->m__log);
	(data->id) = (*id_counter)++;
	(data->eat_count) = 0;
	(data->self) = &(args->p[data->id]);
	(args->p)[(data->id)].alive = 1;
	(data->last_meal) = (args->time_start);
	(args->p[data->id].last_meal) = (args->time_start);
	pthread_mutex_unlock(&args->m__log);
}

static int	ph_forks(t_args *args, t_data *data)
{
	if (ph_log(args, data, NULL, 0) == -1)
		return (-1);
	ph_grab_fork(args->p[data->id].left_fork,
		&args->p[data->id].right_fork, data->id);
	if (ph_log(args, data, "has taken a fork", 0) == -1)
	{
		if (data->id % 2 == 0)
			pthread_mutex_unlock(&data->self->right_fork);
		else
			pthread_mutex_unlock(data->self->left_fork);
		return (-1);
	}
	if (args->philo_count == 1)
	{
		ph_usleep_till(data->last_meal, ph_timestamp()
			+ ((t_ulong)args->time_to_die) * 1000,
			args->time_to_die);
		usleep(1000);
	}
	else
		ph_grab_fork(args->p[data->id].left_fork,
			&args->p[data->id].right_fork, data->id + 1);
	return (ph_eat(args, data));
}

static int	ph_eat(t_args *args, t_data *data)
{
	if (ph_log(args, data, "has taken a fork", 0) == -1)
	{
		ph_drop_forks(data->self->left_fork, &data->self->right_fork);
		return (-1);
	}
	if (ph_log(args, data, "is eating",
			((t_ulong)args->time_to_eat) * 1000) == -1)
	{
		ph_drop_forks(data->self->left_fork, &data->self->right_fork);
		return (-1);
	}
	ph_drop_forks(data->self->left_fork,
		&data->self->right_fork);
	return (0);
}
