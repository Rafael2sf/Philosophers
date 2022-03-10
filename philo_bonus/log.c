/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:01:25 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/10 14:21:09 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ph_update(t_args *args, char *msg, t_ulong ms);

void	ph_log(t_args *args, char *msg, int ms)
{
	sem_wait(args->sem__stat);
	if (args->me.dead)
	{
		sem_close(args->sem__frks);
		sem_close(args->sem__logs);
		sem_close(args->sem__stat);
		exit(1);
	}
	ph_update(args, msg, ms * 1000);
}

static void	ph_update(t_args *args, char *msg, t_ulong ms)
{
	t_ulong	last_meal;

	last_meal = ph_timestamp();
	if (msg[3] == 'e')
	{
		(args->me.last_meal) = ph_timestamp();
		if (args->eat_ammount != -1)
			(args->me.eat_count) += 1;
	}
	last_meal = (args->me.last_meal);
	sem_post(args->sem__stat);
	sem_wait(args->sem__logs);
	printf("%ld %d %s\n", (ph_timestamp() - args->me.time_start) / 1000,
		args->me.id + 1, msg);
	sem_post(args->sem__logs);
	if (ms > 0)
		ph_usleep_till(last_meal,
			args->time_to_die, ph_timestamp() + ms);
}
