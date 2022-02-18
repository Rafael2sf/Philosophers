/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 10:43:30 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/18 17:32:09 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

static void	ph_open_sems(t_args *args);

void	*ph_init_philosphers(t_args *args)
{
	int			i;
	
	i = 0;
	(args->pids) = (int *)malloc(sizeof(int) * (args->philo_count));
	if (!args->pids)
		return (NULL);
	while (i < (args->philo_count))
	{
		(args->pids[i]) = fork(); // Handle error
		if (args->pids[i] == 0)
		{
			ph_open_sems(args);
			break ;
		}
		i++;
	}
	if (i != (args->philo_count))
		ph_process(args, i);
	ph_open_sems(args);
	return (args);
}

static void	ph_open_sems(t_args *args)
{
	(args->forks) = sem_open(SEM_FRK, O_CREAT, 0644, (args->philo_count));
	(args->log_msg) = sem_open(SEM_LOG, O_CREAT, 0644, (args->philo_count));
}
