/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:56:35 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/28 14:30:12 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_wait_over(t_args *args);
static void	ph_wait_over_reset(t_args *args, int *i, int *dead_count);

void	ph_wait_philosophers(t_args *args)
{
	int	i;

	i = 0;
	ph_wait_over(args);
	while (1)
	{
		if (i == 0)
			pthread_mutex_lock(&args->m1);
		if (args->p[i].alive)
		{
			i = 0;
			pthread_mutex_unlock(&args->m1);
			usleep(100);
		}
		else
		{
			i++;
			if (i == args->philo_count)
				break ;
		}
	}
	pthread_mutex_unlock(&args->m1);
}

static void	ph_wait_over(t_args *args)
{
	int		i;
	int		dead_count;

	i = 0;
	dead_count = 0;
	pthread_mutex_lock(&args->m1);
	while (i < args->philo_count)
	{
		if (args->over == 1)
			break ;
		if (!args->p[i].alive)
			dead_count++;
		else if (ph_timestamp() - (args->p[i].last_meal) >= args->time_to_die)
		{
			printf("%ld\t%d\tdied\n", ph_timestamp() - (args->time_start), i + 1);
			(args->over) = 1;
			break ;
		}
		i++;
		if (dead_count == (args->philo_count))
			break ;
		if (i == (args->philo_count))
			ph_wait_over_reset(args, &i, &dead_count);
	}
	pthread_mutex_unlock(&args->m1);
}

static void	ph_wait_over_reset(t_args *args, int *i, int *dead_count)
{
	pthread_mutex_unlock(&args->m1);
	(*i) = 0;
	(*dead_count) = 0;
	usleep(100);
	pthread_mutex_lock(&args->m1);
}
