/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:08:55 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/10 14:21:32 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ph_parse_args(int argc, char **argv, t_args *args);
static int	ph_check_arg(const char *s);
static void	ph_del_sem(void);

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc != 5 && argc != 6)
		return (ph_errorm(1, "Usage: ./prog number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_must_eat]\n", NULL));
	if (ph_parse_args(argc, argv, &args) == -1)
		return (2);
	ph_del_sem();
	if (ph_init_philosophers(&args) == -1)
		return (ph_errorm(3, "Error\n", NULL));
	ph_wait_philosophers(&args);
	free(args.pids);
	sem_close(args.sem__frks);
	sem_close(args.sem__logs);
	sem_close(args.sem__stat);
	ph_del_sem();
	return (0);
}

static int	ph_parse_args(int argc, char **argv, t_args *args)
{
	(args->philo_count) = ph_atoi(argv[1]);
	if (!ph_check_arg(argv[1]) || args->philo_count <= 0)
		return (ph_errorm(-1, "Invalid [number_of_philosophers]\n", NULL));
	(args->time_to_die) = ph_atoi(argv[2]);
	if (!ph_check_arg(argv[2]) || args->time_to_die < 0)
		return (ph_errorm(-1, "Invalid [time_to_die]\n", NULL));
	(args->time_to_eat) = ph_atoi(argv[3]);
	if (!ph_check_arg(argv[3]) || args->time_to_eat < 0)
		return (ph_errorm(-1, "Invalid [time_to_eat]\n", NULL));
	(args->time_to_sleep) = ph_atoi(argv[4]);
	if (!ph_check_arg(argv[4]) || args->time_to_sleep < 0)
		return (ph_errorm(-1, "Invalid [time_to_sleep]\n", NULL));
	if (argc == 6)
	{
		(args->eat_ammount) = ph_atoi(argv[5]);
		if (!ph_check_arg(argv[5]) || args->eat_ammount <= 0)
			return (ph_errorm(-1, "Invalid [number_of_times_each_must_eat]\n",
					NULL));
	}
	else
		(args->eat_ammount) = -1;
	return (0);
}

static int	ph_check_arg(const char *s)
{
	if (!s || !*s)
		return (0);
	while (*s == '\t' || *s == '\n' || *s == '\v'
		|| *s == '\f' || *s == '\r' || *s == ' ')
		s++;
	if (*s == '+' || *s == '-')
		s++;
	while (s && *s >= '0' && *s <= '9')
		s++;
	if (*s != '\0')
		return (0);
	return (1);
}

static void	ph_del_sem(void)
{
	sem_unlink(SEM__LOGS);
	sem_unlink(SEM__FRKS);
	sem_unlink(SEM__STAT);
}
