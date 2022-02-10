/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:56:47 by rafernan          #+#    #+#             */
/*   Updated: 2022/02/10 15:10:13 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_errorm(int error_code, char *error_message)
{
	if (error_code != 0)
		ft_putstr(STDERR_FILENO, error_message);
	return (error_code);
}
