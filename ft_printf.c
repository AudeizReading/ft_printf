/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/17 14:42:40 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	void	*v_arg;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(++format) != 0)
		{
			v_arg = va_arg(args, void *);
			if (*format == '%')
				ft_putchar_fd('%', 1);
			else
				ft_putstr_fd((char *)v_arg, 1);
		}
		else
			ft_putchar_fd((char)*format, 1);
		format++;
	}
	va_end(args);
	return (0);
}
