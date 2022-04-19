/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 10:59:29 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/11 16:24:36 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_grab_fork(t_mutex *lf, t_mutex *rf, int id)
{
	int	ret;

	if (id % 2 == 0)
		ret = pthread_mutex_lock(rf);
	else
	{
		usleep(100);
		ret = pthread_mutex_lock(lf);
	}
	return (ret);
}

int	ph_drop_forks(t_mutex *lf, t_mutex *rf)
{
	int	i;

	i = 0;
	i += pthread_mutex_unlock(lf);
	i += pthread_mutex_unlock(rf);
	return (i);
}
