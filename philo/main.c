/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:31:13 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/11 16:43:32 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_parse_args(int argc, char **argv, t_args *args);
static int	ph_check_arg(const char *s);

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc != 5 && argc != 6)
		return (ph_errorm(1, "Usage: ./prog number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_must_eat]\n"));
	if (ph_parse_args(argc, argv, &args) == -1)
		return (2);
	if (!ph_init_philosophers(&args))
		return (ph_errorm(2, "Error\n"));
	ph_wait_philosophers(&args);
	ph_clear_philosophers(&args);
	return (0);
}

static int	ph_parse_args(int argc, char **argv, t_args *args)
{
	(args->philo_count) = ph_atoi(argv[1]);
	if (!ph_check_arg(argv[1]) || args->philo_count <= 0)
		return (ph_errorm(-1, "Invalid [number_of_philosophers]\n"));
	(args->time_to_die) = ph_atoi(argv[2]);
	if (!ph_check_arg(argv[2]) || args->time_to_die < 0)
		return (ph_errorm(-1, "Invalid [time_to_die]\n"));
	(args->time_to_eat) = ph_atoi(argv[3]);
	if (!ph_check_arg(argv[3]) || args->time_to_eat < 0)
		return (ph_errorm(-1, "Invalid [time_to_eat]\n"));
	(args->time_to_sleep) = ph_atoi(argv[4]);
	if (!ph_check_arg(argv[4]) || args->time_to_sleep < 0)
		return (ph_errorm(-1, "Invalid [time_to_sleep]\n"));
	if (argc == 6)
	{
		(args->eat_ammount) = ph_atoi(argv[5]);
		if (!ph_check_arg(argv[5]) || args->eat_ammount <= 0)
			return (ph_errorm(-1, "Invalid [number_of_times_each_must_eat]\n"));
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
