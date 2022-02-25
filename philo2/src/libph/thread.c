/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:51:33 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/25 18:10:01 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_parse_data(t_args *args, t_data *data, int *id_counter);

void	*ph_routine(void *args_ptr)
{
	static int	id_counter;
	t_data		data;
	t_args		*args;

	args = (t_args *)(args_ptr);	
	ph_parse_data(args, &data, &id_counter);
	while (1)
	{
		if (ph_log(args, &data, NULL, 0) == -1)
			break ;
		if (data.id % 2 == 0)
			pthread_mutex_lock(&data.self->right_fork);
		else
			pthread_mutex_lock(data.self->left_fork);
		if (ph_log(args, &data, "has taken a fork", 0) == -1)
		{
			if (data.id % 2 == 0)
				pthread_mutex_unlock(&data.self->right_fork);
			else
				pthread_mutex_unlock(data.self->left_fork);
			break ;
		}
		if (args->philo_count == 1)
			ph_usleep_till(&data, ph_timestamp() + data.time_to_die);
		else if (data.id % 2 == 0)
			pthread_mutex_lock(data.self->left_fork);
		else
			pthread_mutex_lock(&data.self->right_fork);
		if (ph_log(args, &data, "has taken a fork", 0) == -1)
		{
			pthread_mutex_unlock(&data.self->right_fork);
			pthread_mutex_unlock(data.self->left_fork);	
			break ;
		}
		if (ph_log(args, &data, "is eating", (data.time_to_eat)) == -1)
		{
			pthread_mutex_unlock(&data.self->right_fork);
			pthread_mutex_unlock(data.self->left_fork);	
			break ;
		}
		pthread_mutex_unlock(&data.self->right_fork);
		pthread_mutex_unlock(data.self->left_fork);
		if (data.eat_count == data.eat_ammount)
			break ;
		if (ph_log(args, &data, "is sleeping", (data.time_to_sleep)) == -1)
			break ;
		if (ph_log(args, &data, "is thinking", 0) == -1)
			break ;
	}
	pthread_mutex_lock(&args->m1);
	(data.self->alive) = 0;
	pthread_mutex_unlock(&args->m1);
	return (NULL);
}

static void	ph_parse_data(t_args *args, t_data *data, int *id_counter)
{
	pthread_mutex_lock(&args->m1);
	(data->id) = (*id_counter)++;
	(data->last_meal) = (args->time_start);
	(data->time_to_eat) = (args->time_to_eat);
	(data->time_to_sleep) = (args->time_to_sleep);
	(data->time_to_die) = (args->time_to_die);
	(data->eat_ammount) = (args->eat_ammount);
	(data->eat_count) = 0;
	(data->self) = &(args->p[data->id]);
	(args->p)[(data->id)].alive = 1;
	(args->over) = 0;
	pthread_mutex_unlock(&args->m1);
}
