/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:19:40 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/17 15:48:19 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ph_msg(int state);
static void	ph_monitor_loop(t_args *args, int *states, long time, int i);
static int	ph_check_all_death(t_args *args);

void	ph_monitor_philosophers(t_args *args)
{
	long	time;
	int		*states;
	int		i;

	i = 0;
	time = 0;
	states = malloc(sizeof(int) * args->philo_count);
	if (!states)
		return ;
	while (i < args->philo_count)
		states[i++] = THINK;
	while (args->time_start == 0)
		(void)(args);
	usleep(10);
	ph_monitor_loop(args, states, time, i);
	free(states);
}

static void	ph_monitor_loop(t_args *args, int *states, long time, int i)
{
	while (1)
	{
		i = 0;
		time = ph_timestamp();
		while (i < args->philo_count)
		{
			if (args->philo[i]->state != -1
				&& (time - args->philo[i]->last_meal) >= args->time_to_die)
			{
				printf("%ld %d died\n", time - args->time_start, i);
				(args->time_to_die) = -1;
				return ;
			}
			if (args->philo[i]->state != -1
				&& states[i] != args->philo[i]->state)
			{
				printf("%ld %d %s\n", time - args->time_start,
					i, ph_msg(args->philo[i]->state));
				states[i] = (args->philo[i]->state);
			}
			if (ph_check_all_death(args))
				return ;
			i++;
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

static int	ph_check_all_death(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		if (args->philo[i]->state != -1)
			return (0);
		i++;
	}
	return (1);
}
