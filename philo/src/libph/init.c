/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:06:53 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/16 18:43:15 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ph_init_error(int i, t_args *args);

/**
 * Allocate memory for each philosopher and start threads
*/
void	*ph_init_philosophers(t_args *args)
{
	int		i;

	(args->philo) = (t_philo **)malloc(sizeof(t_philo *) * (args->philo_count));
	if ((args->philo) == NULL)
		return (NULL);
	i = 0;
	(args->time_start) = 0;
	while (i < (args->philo_count))
	{
		(args->philo[i]) = (t_philo *)malloc(sizeof(t_philo));
		if ((args->philo[i]) == NULL)
			return (ph_init_error(i, args));
		if (i == 0)
			(args->philo[i]->left_fork) = NULL;
		else
			(args->philo[i]->left_fork) = &(args->philo[i - 1]->right_fork);
		if (i == (args->philo_count - 1))
				(args->philo[0]->left_fork) = &(args->philo[i]->right_fork);
		if (pthread_mutex_init((&args->philo[i]->right_fork), NULL) != 0)
			return (ph_init_error(i, args));
		if (pthread_create(&args->philo[i]->self, NULL, ph_think_eat_sleep, args) != 0)
			return (ph_init_error(i, args));
		(args->philo[i++]->state) = THINK;
	}
	return (args);
}

static void	*ph_init_error(int i, t_args *args)
{
	printf("Something went wrong!\n");
	(void)(i);
	(void)(args);
	args->philo[i] = NULL;
	return (NULL);
}
