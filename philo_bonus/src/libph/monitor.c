/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:19:40 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/04 18:09:43 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ph_monitor(void *args_ptr)
{
	t_args	*args;

	args = (t_args *)(args_ptr);
	while (1)
	{
		sem_wait(args->log_msg);
		if (args->over == 1)
			break ;
		if (ph_timestamp() - (args->philo.last_meal)
			>= (t_ulong)(args->time_to_die * 1000))
		{
			(args->over) = 1;
			printf("%ld %d died - \n",
				(ph_timestamp() - (args->time_start)) / 1000, (args->philo.id) + 1);
			sem_post(args->log_msg);
			break ;
		}
		sem_post(args->log_msg);
	}
	return (NULL);
}
