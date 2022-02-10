/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:18:45 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/10 16:20:28 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
* Join all threads and free memory for each philosophers
*/
void	ph_clear_philosophers(t_args *args)
{
	int	i;

	i = 0;
	while (i < (args->philo_count))
	{
		if (pthread_join(args->philo[i]->self, NULL) != 0)
			ft_putstr(STDERR_FILENO, "A philosopher is missing\n");
		if (pthread_mutex_destroy(&args->philo[i]->right_fork) != 0)
			ft_putstr(STDERR_FILENO, "I dont know why this hapens\n");
		free(args->philo[i]);
		i++;
	}
	free(args->philo);
}
