/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:17:34 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/10 14:16:26 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_init_sem(t_args *args);
static void	ph_fork_error(t_args *args, int i);
static void	ph_child_error(t_args *args);

int	ph_init_philosophers(t_args *args)
{
	int	i;

	i = 0;
	(args->pids) = malloc(sizeof(pid_t) * (args->philo_count));
	if (!args->pids)
		return (-1);
	if (ph_init_sem(args) == -1)
	{
		free(args->pids);
		return (-1);
	}
	while (i < args->philo_count)
	{
		(args->pids)[i] = fork();
		if ((args->pids)[i] == -1)
			ph_fork_error(args, i);
		if ((args->pids)[i] == 0)
		{
			ph_routine(args, i);
			ph_child_error(args);
		}
		i++;
	}
	return (0);
}

static int	ph_init_sem(t_args *args)
{
	(args->sem__frks) = sem_open(SEM__FRKS, O_CREAT, 0644, args->philo_count);
	if (args->sem__frks == SEM_FAILED)
		return (-1);
	(args->sem__logs) = sem_open(SEM__LOGS, O_CREAT, 0644, 1);
	if (args->sem__logs == SEM_FAILED)
	{
		sem_close(args->sem__frks);
		sem_unlink(SEM__FRKS);
		return (-1);
	}
	(args->sem__stat) = sem_open(SEM__STAT, O_CREAT, 0644, 0);
	if ((args->sem__stat) == SEM_FAILED)
	{
		sem_close(args->sem__frks);
		sem_close(args->sem__logs);
		sem_unlink(SEM__FRKS);
		sem_unlink(SEM__LOGS);
		return (-1);
	}
	return (0);
}

static void	ph_fork_error(t_args *args, int i)
{
	while (--i <= 0)
		kill(args->pids[i], SIGKILL);
	ph_child_error(args);
}

static void	ph_child_error(t_args *args)
{
	free(args->pids);
	sem_close(args->sem__frks);
	sem_close(args->sem__logs);
	sem_close(args->sem__stat);
	sem_unlink(SEM__LOGS);
	sem_unlink(SEM__FRKS);
	sem_unlink(SEM__STAT);
	ph_putstr(STDERR_FILENO, "child process error\n");
	exit(1);
}
