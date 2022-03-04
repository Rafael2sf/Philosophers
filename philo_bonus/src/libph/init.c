/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:43:30 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/04 17:36:37 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_open_sem_list(t_args *args);
static void	*ph_fork_error(t_args *args, int i);
static void	*ph_child_error(t_args *args);

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
	if (ph_open_sem_list(args) == -1)
		return (ph_child_error(args));
	(args->time_start) = ph_timestamp();
	(args->philo.last_meal) = (args->time_start);
	while (i < args->philo_count)
	{
		(args->pids[i]) = fork();
		if (args->pids[i] == -1)
			return (ph_fork_error(args, i));
		if (args->pids[i] == 0)
		{
			ph_process(args, i);
			ph_child_error(args);
		}
		i++;
	}
	return (args);
}

static int	ph_open_sem_list(t_args *args)
{
	(args->forks) = sem_open(SEM_FRK, O_CREAT, 0644, (args->philo_count));
	if (args->forks == SEM_FAILED)
		return (-1);
	(args->log_msg) = sem_open(SEM_LOG, O_CREAT, 0644, 0);
	if (args->log_msg == SEM_FAILED)
	{
		sem_close(args->forks);
		sem_unlink(SEM_FRK);
		return (-1);
	}
	return (0);
}

static void	*ph_fork_error(t_args *args, int i)
{
	sem_close(args->forks);
	sem_close(args->log_msg);
	while (--i <= 0)
		kill(args->pids[i], SIGKILL);
	free(args->pids);
	(args->pids) = NULL;
	return (NULL);
}

static void	*ph_child_error(t_args *args)
{
	sem_close(args->forks);
	sem_close(args->log_msg);
	free(args->pids);
	write(STDERR_FILENO, "Error\n", 6);
	exit(1);
	return (NULL);
}
