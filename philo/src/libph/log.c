/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:32:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/02 12:05:16 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_update(t_args *args, t_data *data, char *str, t_ulong time);

int	ph_log(t_args *args, t_data *data, char *str, t_ulong time)
{
	if (ph_timestamp() - data->last_meal >= (t_ulong)data->time_to_die * 1000)
	{
		pthread_mutex_lock(&args->m1);
		if (args->over != 1)
		{
			(args->over) = 1;
			printf("%ld %d died\n",
				(ph_timestamp() - args->time_start) / 1000, data->id + 1);
		}
		pthread_mutex_unlock(&args->m1);
		return (-1);
	}
	else if (str)
		ph_update(args, data, str, time);
	return (0);
}

static int	ph_update(t_args *args, t_data *data, char *str, t_ulong time)
{
	pthread_mutex_lock(&args->m1);
	if (args->over == 1)
	{
		pthread_mutex_unlock(&args->m1);
		return (-1);
	}
	else
	{
		if (str[3] == 'e')
		{
			(data->last_meal) = ph_timestamp();
			(args->p[data->id].last_meal) = (data->last_meal);
			if (data->eat_ammount != -1)
				(data->eat_count) += 1;
		}
		printf("%ld %d %s\n",
			(ph_timestamp() - args->time_start) / 1000, data->id + 1, str);
	}
	pthread_mutex_unlock(&args->m1);
	if (time != 0)
		ph_usleep_till(data, ph_timestamp() + time);
	return (0);
}
