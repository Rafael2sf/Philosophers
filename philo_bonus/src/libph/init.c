/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:43:30 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/21 16:33:17 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_open_sem_list(t_args *args);

/**
* Initialize each philosopher as a process with a thread 
*/

void	*ph_init_philosphers(t_args *args)
{
	int	i;

	i = 0;
	(args->pids) = (int *)malloc(sizeof(int) * (args->philo_count));
	if (!args->pids)
		return (NULL);
	while (i < args->philo_count)
	{
		(args->pids[i]) = fork();
		//if (... == -1) Handle error
		if (args->pids[i] == 0)
		{
			if (!ph_open_sem_list(args))
				(void)(args); // Handle error
			if (pthread_create(&args->philo.self, NULL, ph_monitor, args) == -1)
				(void)(args); // Handle error
			if (pthread_detach(args->philo.self) == -1)
				(void)(args); // Handle error
			ph_process(args, i);
		}
		i++;
	}
	return (args);
}

/*
void	*ph_init_philosphers(t_args *args)
{
	int			i;
	
	i = 0;
	(args->pids) = (int *)malloc(sizeof(int) * (args->philo_count));
	if (!args->pids)
		return (NULL);
	ph_open_sems(args);
	while (i < (args->philo_count))
	{
		(args->pids[i]) = fork(); // Handle error
		if (args->pids[i] == 0)
		{
			pthread_create();
			ph_open_sems(args);
			break ;
		}
		i++;
	}
	if (i != (args->philo_count))
		ph_process(args, i);
	return (args);
}
*/

static int	ph_open_sem_list(t_args *args)
{
	(args->forks) = sem_open(SEM_FRK, O_CREAT, 0644, (args->philo_count));
	if (args->forks == SEM_FAILED)
		return (1);
	(args->log_msg) = sem_open(SEM_LOG, O_CREAT, 0644, 1);
	if (args->log_msg == SEM_FAILED)
	{
		sem_close(args->forks);
		sem_unlink(SEM_FRK);
		return (1);
	}
	return (0);
}
