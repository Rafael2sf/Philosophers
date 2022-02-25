/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:18:45 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/24 13:49:47 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_threads_wait(t_args *args);

/**
* Join all threads and free memory for each philosophers
*/
void	ph_clear_philosophers(t_args *args)
{
	int	i;

	i = 0;
	ph_threads_wait(args);
	while (i < (args->philo_count))
	{
		if (args->philo[i])
		{
			pthread_mutex_unlock(&args->philo[i]->right_fork);
			pthread_mutex_destroy(&args->philo[i]->right_fork);
			pthread_join(args->philo[i]->self, NULL);
			free(args->philo[i]);
		}
		i++;
	}
	free(args->philo);
	(args->philo) = NULL;
	pthread_mutex_destroy(&args->m1);
	pthread_mutex_destroy(&args->m2);
}

static void	ph_threads_wait(t_args *args)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < args->philo_count)
		{
			if (args->philo[i]->state != -1)
			{
				pthread_mutex_unlock(&args->philo[i]->right_fork);
				pthread_mutex_unlock(args->philo[i]->left_fork);
				break ;
			}
			i++;
		}
		if (i == args->philo_count)
			return ;
	}
}
