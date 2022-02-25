/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:51:38 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/24 13:46:21 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_init_thread(t_args *args, int *id, int *eat_count, int *id_counter)
{
	pthread_mutex_lock(&args->m1);
	(*eat_count) = 0;
	(*id) = (*id_counter)++;
	(args->philo[*id]->last_meal) = ph_timestamp();
	while (1)
	{
		if (*id_counter >= args->philo_count)
		{
			pthread_mutex_unlock(&args->m1);
			break ;
		}
		pthread_mutex_unlock(&args->m1);
		usleep(100);
	}
	pthread_mutex_lock(&args->m2);
	if (args->time_start == 0)
		(args->time_start) = ph_timestamp();
	pthread_mutex_unlock(&args->m2);
}

char	*ph_msg(int state)
{
	static char	*msg_list[STATES_COUNT];

	if (!msg_list[0])
	{
		msg_list[0] = MSG_THINK;
		msg_list[1] = MSG_FORK;
		msg_list[2] = MSG_FORK;
		msg_list[3] = MSG_EAT;
		msg_list[4] = MSG_SLEEP;
	}
	return (msg_list[state]);
}
