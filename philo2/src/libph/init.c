/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:08:14 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/25 16:10:09 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//static void	*ph_init_malloc(t_args *args);
static void	*ph_init_vars(t_args *args);

void	*ph_init_philosophers(t_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&args->m1, NULL) != 0)
		return (NULL);
	(args->p) = (t_phil *)malloc(sizeof(t_phil) * (args->philo_count));
	if ((args->p) == NULL)
		return (NULL);
	if (!ph_init_vars(args))
		return (NULL);
	(args->over = 0);
	(args->time_start) = ph_timestamp();
	while (i < args->philo_count)
	{
		pthread_create(&(args->p)[i++].self, NULL, ph_routine, args);
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
