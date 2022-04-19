/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:56:47 by rafernan          #+#    #+#             */
/*   Updated: 2022/03/11 16:51:02 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ph_putstr(int fd, const char *s)
{
	char	*ptr;

	if (!s)
		return (write(fd, "(null)", 6));
	ptr = ((char *)(s));
	while (*ptr)
		ptr++;
	write(fd, s, ptr - s);
	return (ptr - s);
}

int	ph_atoi(const char *str)
{
	int		i;
	int		flag;
	int		nb;

	i = 0;
	flag = 1;
	nb = 0;
	if (str)
	{
		while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				flag *= -1;
			i++;
		}
		while (str[i] && str[i] >= '0' && str[i] <= '9')
		{
			nb = (nb * 10) + (str[i] - '0');
			i++;
		}
	}
	return (flag * nb);
}

int	ph_errorm(int error_code, char *error_message)
{
	if (error_code != 0)
		ph_putstr(STDERR_FILENO, error_message);
	return (error_code);
}

t_ulong	ph_timestamp(void)
{
	t_time	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000 * 1000) + (curr_time.tv_usec));
}

void	ph_usleep_till(t_ulong last_meal, t_ulong time, t_ulong time_to_die)
{
	t_ulong	now;

	while (1)
	{
		now = ph_timestamp();
		if (now >= time)
			break ;
		if (now - last_meal >= time_to_die * 1000)
			break ;
		usleep(10);
	}
}
