/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:59:37 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/10 14:20:18 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ph_monitor(void *args_ptr)
{
	t_args	*args;

	args = (t_args *)(args_ptr);
	while (1)
	{
		sem_wait(args->sem__stat);
		if (ph_timestamp() - (args->me.last_meal)
			>= (t_ulong)(args->time_to_die * 1000))
		{
			sem_wait(args->sem__logs);
			printf("%ld %d died\n",
				(ph_timestamp() - (args->me.time_start)) / 1000,
				(args->me.id) + 1);
			sem_post(args->sem__stat);
			exit(1);
		}
		sem_post(args->sem__stat);
	}
	return (NULL);
}
