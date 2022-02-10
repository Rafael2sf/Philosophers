/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:21:09 by rafernan          #+#    #+#             */
/*   Updated: 2021/11/01 23:14:19 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printfc(va_list args, char **format)
{
	if (**format == ('%'))
		return (ft_putchar(1, **format));
	else if (**format == ('c'))
		return (ft_putchar(1, va_arg(args, int)));
	else if (**format == ('s'))
		return (ft_putstr(1, va_arg(args, char *)));
	else if (**format == ('d') || **format == ('i'))
		return (ft_putnbr_b(1, va_arg(args, int), 10, 0));
	else if (**format == ('u'))
		return (ft_putunbr_b(1, va_arg(args, unsigned int), 10, 0));
	else if (**format == ('x'))
		return (ft_putunbr_b(1, va_arg(args, unsigned int), 16, 0));
	else if (**format == ('X'))
		return (ft_putunbr_b(1, va_arg(args, unsigned int), 16, 1));
	else if (**format == ('p'))
		return (ft_putaddr(1, va_arg(args, unsigned long)));
	return (1);
}

static int	ft_printfm(char *format, va_list args)
{
	int	bytes;

	bytes = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (ft_is(*format, "cspdiuxX%"))
				bytes += ft_printfc(args, &format);
			else
				return (bytes);
		}
		else
		{
			write(1, format, 1);
			bytes++;
		}
		format++;
	}
	return (bytes);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		bytes;

	bytes = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	bytes = ft_printfm((char *)format, args);
	va_end(args);
	return (bytes);
}
