/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:27:44 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/25 12:46:44 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_clear_philosophers(t_args *args)
{
	int	i;

	i = 0;
	while (i < (args->philo_count))
		pthread_join(args->p[i++].self, NULL);
	i = 0;
	while (i < (args->philo_count))
		pthread_mutex_destroy(&args->p[i++].right_fork);
	i = 0;
	free(args->p);
}
