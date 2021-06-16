/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/16 14:31:58 by alellouc         ###   ########.fr       */
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
		if (*format == '%' && (*(format + 1) != 0 || *(format + 1) != '%'))
		{
			v_arg = va_arg(args, void *);
			ft_putstr_fd((char *)v_arg, 1);
		}
		format++;
	}
	va_end(args);
	ft_putstr_fd((char *)format, 1);
	ft_putstr_fd("Juste pour pouvoir push sur vogsphere Yo\n", 1);
	return (0);
}
