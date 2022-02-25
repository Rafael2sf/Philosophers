/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:56:35 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/25 15:43:13 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//static void	ph_wait_over(t_args *args);

void	ph_wait_philosophers(t_args *args)
{
	int	i;

	i = 0;
	//ph_wait_over(args);
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
/*
static void	ph_wait_over(t_args *args)
{
	while (1)
	{
		pthread_mutex_lock(&args->m1);
		if (args->over == 1)
		{
			pthread_mutex_unlock(&args->m1);
			break ;
		}
		pthread_mutex_unlock(&args->m1);
		usleep(500);
	}
}
*/