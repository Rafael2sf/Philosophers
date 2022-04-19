/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:32:16 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/11 16:48:18 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_log(t_args *args, t_data *data, char *str, t_ulong time)
{
	pthread_mutex_lock(&args->m__log);
	if (args->over == 1)
	{
		pthread_mutex_unlock(&args->m__log);
		return (-1);
	}
	else if (str)
	{
		if (str[3] == 'e')
		{
			(data->last_meal) = ph_timestamp();
			(args->p[data->id].last_meal) = (data->last_meal);
			if (args->eat_ammount != -1)
				(data->eat_count) += 1;
		}
		printf("%ld %d %s\n",
			(ph_timestamp() - args->time_start) / 1000, data->id + 1, str);
	}
	pthread_mutex_unlock(&args->m__log);
	if (time != 0)
		ph_usleep_till(data->last_meal,
			ph_timestamp() + time, args->time_to_die);
	return (0);
}
