/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:38:45 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/10 12:36:29 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_wait_philosophers(t_args *args)
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
}
