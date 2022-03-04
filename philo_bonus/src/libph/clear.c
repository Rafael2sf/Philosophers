/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:32:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/04 11:25:46 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_clear_philosophers(t_args *args)
{
	int	i;
	int	val;

	i = 0;
	while (i < (args->philo_count))
	{
		waitpid(-1, &val, 0);
		if (val == 256)
		{
			while (i < (args->philo_count))
			{
				kill(args->pids[i], SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	free(args->pids);
	sem_close(args->forks);
	sem_close(args->log_msg);
}
