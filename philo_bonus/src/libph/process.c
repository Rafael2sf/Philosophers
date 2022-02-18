/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:36:11 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/18 17:29:57 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_think(int id, t_args *args, long *last_meal);
static int	ph_eat(int id, t_args *args, int *eat_count, long *last_meal);
static int	ph_sleep(int id, t_args *args, long *last_meal);


int	ph_log(t_args *args, const char *msg, int id, long *last_meal)
{
	long	meal_time;
	
	sem_wait(args->log_msg);
	meal_time = ph_timestamp();
	if (meal_time - *last_meal >= args->time_to_die)
	{
		sem_post(args->log_msg);
		return (-1);
	}
	(*last_meal) = meal_time;
	printf("%ld %d %s", meal_time - args->time_start, id, msg);
	sem_post(args->log_msg);
	return (0);
}

void	ph_process(t_args *args, int id)
{
	long	last_meal;
	int		eat_count;
	int		i;

	free(args->pids);
	eat_count = 0;
	i = 0;
	(args->time_start) = ph_timestamp();
	last_meal = (args->time_start);
	while (1)
	{
		if (ph_think(id, args, &last_meal) == -1)
			break ;
		if (ph_eat(id, args, &eat_count, &last_meal) == -1)
			break ;
		if (ph_sleep(id, args, &last_meal) == -1)
			break ;
		usleep(100);
	}
	printf("...\n");
	ph_log(args, MSG_DIED, id, &last_meal);
	sem_close(args->forks);
	sem_close(args->log_msg);
	exit(0);
}

static int	ph_think(int id, t_args *args, long *last_meal)
{
	if (id % 2 == 0)
		usleep(100);
	sem_wait(args->forks);
	//printf("sem = %d\n", *(int *)(args->forks));
	if (ph_log(args, MSG_FORK, id, last_meal) == -1)
		return (-1);
	sem_wait(args->forks);
	if (ph_log(args, MSG_FORK, id, last_meal) == -1)
		return (-1);
	return (0);
}

static int	ph_eat(int id, t_args *args, int *eat_count, long *last_meal)
{
	(void)(eat_count);
	if (ph_log(args, MSG_EAT, id, last_meal) == -1)
		return (-1);
	ph_usleep_till(ph_timestamp() + args->time_to_eat);
	sem_post(args->forks);
	sem_post(args->forks);
	return (0);
}

static int	ph_sleep(int id, t_args *args, long *last_meal)
{
	if (ph_log(args, MSG_SLEEP, id, last_meal) == -1)
		return (-1);
	ph_usleep_till(ph_timestamp() + args->time_to_sleep);
	if (ph_log(args, MSG_THINK, id, last_meal) == -1)
		return (-1);
	return (0);
}
