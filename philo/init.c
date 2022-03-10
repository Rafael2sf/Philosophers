/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:08:14 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/10 13:01:13 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ph_init_vars(t_args *args);
static void	*ph_thread_error(t_args *args, int i);

void	*ph_init_philosophers(t_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&args->m__log, NULL) != 0)
		return (NULL);
	(args->p) = (t_phil *)malloc(sizeof(t_phil) * (args->philo_count));
	if ((args->p) == NULL)
	{
		pthread_mutex_destroy(&args->m__log);
		return (NULL);
	}
	if (!ph_init_vars(args))
	{
		pthread_mutex_destroy(&args->m__log);
		return (NULL);
	}
	(args->over = 0);
	(args->time_start) = ph_timestamp();
	while (i < args->philo_count)
	{
		if (pthread_create(&(args->p)[i++].self, NULL, ph_routine, args) != 0)
			return (ph_thread_error(args, i));
		usleep(100);
	}
	return (args);
}

static void	*ph_init_vars(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_count)
	{
		if (pthread_mutex_init(&(args->p)[i].right_fork, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&args->p[i].right_fork);
			free(args->p);
			return (NULL);
		}
		((args->p)[i].alive) = 1;
		if (i != 0)
			((args->p)[i].left_fork) = (&(args->p)[i - 1].right_fork);
		i++;
	}
	(args->p[0].left_fork) = &(args->p[i - 1].right_fork);
	return (args);
}

static void	*ph_thread_error(t_args *args, int i)
{
	pthread_mutex_lock(&args->m__log);
	(args->over) = 1;
	pthread_mutex_unlock(&args->m__log);
	while (i >= 0)
	{
		pthread_join(args->p[i].self, NULL);
		i--;
	}
	i = 0;
	while (i != (args->philo_count))
	{
		pthread_mutex_destroy(&args->p[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(&args->m__log);
	free(args->p);
	return (NULL);
}
