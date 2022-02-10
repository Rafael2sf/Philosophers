/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:06:53 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/10 18:05:15 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*say_hi(void *x);

/**
 * Allocate memory for each philosopher and start threads
*/
void	*ph_init_philosophers(t_args *args)
{
	int	i;
	
	(args->philo) = (t_philo **)malloc(sizeof(t_philo *) * (args->philo_count));
	if ((args->philo) == NULL)
		return (NULL);
	i = 0;
	while (i < (args->philo_count))
	{
		(args->philo[i]) = (t_philo *)malloc(sizeof(t_philo) * (args->philo_count));
		if ((args->philo[i]) == NULL)
			return (NULL);
		if (i == 0)
			(args->philo[i]->left_fork) = NULL;
		else
			(args->philo[i]->left_fork) = &(args->philo[i - 1]->right_fork);
		if (pthread_mutex_init((&args->philo[i]->right_fork), NULL) != 0)
			ft_putstr(STDERR_FILENO, "Couldn't find a fork\n");
		if (i == (args->philo_count) - 1)
				(args->philo[0]->left_fork) = &(args->philo[i]->right_fork);
		(args->philo[i]->pos) = i;
		if (pthread_create((&args->philo[i]->self), 
			NULL, say_hi, (args->philo[i])) != 0)
			ft_putstr(STDERR_FILENO, "A philosopher did not sit\n");
		i++;
	}
	return (args);
}

void	*say_hi(void *x)
{
	t_philo			*self;
	struct timeval	time;
	
	usleep(100);
	self = (t_philo *)(x);
	gettimeofday(&time, NULL);
	pthread_mutex_lock(&self->right_fork);
	pthread_mutex_lock(self->left_fork);
	printf("%d: Eating at: %d\n", self->pos, time.tv_usec);
	usleep(3000000);
	pthread_mutex_unlock(&self->right_fork);
	pthread_mutex_unlock(self->left_fork);
	return (NULL);
}
