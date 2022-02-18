/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:32:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/18 17:07:22 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_clear_philosophers(t_args *args)
{
	int	i;
	int val;
	
	i = 0;
	while (i < (args->philo_count))
	{
		//printf("Waiting pid: %d\n", args->pids[i]);
		waitpid(-1, &val, 0);
		printf("val = %d\n", val);
		i++;
	}
	free(args->pids);
	sem_close(args->forks);
	sem_unlink(SEM_FRK);
	sem_close(args->log_msg);
	sem_unlink(SEM_LOG);
}
