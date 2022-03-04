/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:03:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/04 18:09:15 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_update(t_args *args, t_data *data, char *str, t_ulong time);

int	ph_log(t_args *args, t_data *data, char *str, t_ulong time)
{
	sem_wait(args->log_msg);
	if (ph_timestamp() - args->philo.last_meal
		>= ((t_ulong)args->time_to_die * 1000))
	{
		if (args->over != 1)
		{
			(args->over) = 1;
			printf("%ld %d died\n",(ph_timestamp() - args->time_start) / 1000,
				args->philo.id + 1);
		}
	}
	else if (str)
		return (ph_update(args, data, str, time * 1000));
	return (-1);
}

static int	ph_update(t_args *args, t_data *data, char *str, t_ulong time)
{
	//printf("%ld %ld\n", ph_timestamp(), args->time_start);
	if (args->over == 1)
		return (-1);
	else
	{
		if (str[3] == 'e')
		{
			(data->last_meal) = ph_timestamp();
			(args->philo.last_meal) = (data->last_meal);
			if (data->eat_ammount != -1)
				(data->eat_count) += 1;
		}
		printf("%ld %d %s\n",
			(ph_timestamp() - args->time_start) / 1000,
				args->philo.id + 1, str);
	}
	sem_post(args->log_msg);
	if (time != 0)
		ph_usleep_till(data->last_meal, data->time_to_die, ph_timestamp() + time);
	else
		usleep(10);
	return (0);
}
