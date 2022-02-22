/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:19:40 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/22 12:17:42 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*ph_msg(int state);
static void	ph_monitor_loop(t_args *args, int *states, long time);

void	*ph_monitor(void *args_ptr)
{
	t_args	*args;
	long	time;
	int		state;

	time = 0;
	state = THINK;
	args = (t_args *)(args_ptr);
	while (args->time_start == 0)
		usleep(10);
	ph_monitor_loop(args, &state, time);
	return (NULL);
}

static void	ph_monitor_loop(t_args *args, int *state, long time)
{
	while (1)
	{
		time = ph_timestamp();
		if (args->philo.state != -1
			&& (time - args->philo.last_meal) >= args->time_to_die)
		{
			sem_wait(args->log_msg);
			printf("%ld %d died\n",
				time - args->time_start, args->philo.id + 1);
			sem_close(args->forks);
			(args->time_to_die) = -1;
			return ;
		}
		if (args->philo.state != -1 && (*state != args->philo.state))
		{
			sem_wait(args->log_msg);
			printf("%ld %d %s\n", time - args->time_start,
				args->philo.id + 1, ph_msg(args->philo.state));
			sem_post(args->log_msg);
			(*state) = (args->philo.state);
		}
	}
}

static char	*ph_msg(int state)
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
