/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:10:09 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/24 13:47:29 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
static int	ph_think(int id, t_args *args);
static int	ph_eat(int id, t_args *args, int *eat_count);
static int	ph_sleep(int id, t_args *args);
*/
void	*ph_thread(void *args_ptr)
{
	int			id;
	t_args		*args;
	int			eat_count;
	static int	id_counter;

	args = (t_args *)args_ptr;
	ph_init_thread(args, &id, &eat_count, &id_counter);
	/*
	while (1)
	{
		if (ph_think(id, args) == -1)
			break ;
		if (ph_eat(id, args, &eat_count) == -1)
			break ;
		if (ph_sleep(id, args) == -1)
			break ;
		usleep(100);
	}
	*/
	(args->philo[id]->state) = -1;
	return (NULL);
}

/*
static int	ph_think(int id, t_args *args)
{
	return (0);
}

static int	ph_eat(int id, t_args *args, int *eat_count)
{
	return (0);
}

static int	ph_sleep(int id, t_args *args)
{
	return (0);
}
*/