/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/28 16:59:42 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
/*void	set_indicator(t_printf_flags **flag, char **p_format, int v_arg)
{
}*/

int	ft_printf(const char *format, ...)
{
	/* Ne pas oublier de recuperer la taille des elements pour le retour final */
	/* Ne pas oublier de gerer les etoiles avec la width et la precision */
	int				sum;
	char			*p_format;
	va_list			args;
	void			*v_arg;
	t_printf_flags	*flag;

	p_format = (char *)format;
	sum = 0;
	flag = &(t_printf_flags){false, 0, false, false, 0, true, false, 1, false, 0};
	va_start(args, format);
	while (*p_format)
	{
		/* Il faudrait également vérifier qu'il y a autant de % que d'arguments
		** en bouclant sur va_arg, donc on ferait deux boucles sur les params
		** variadiques */
		if (*p_format == '%' && *(++p_format))
		{
			if (flag->indicator != '%')
				v_arg = va_arg(args, void *);
			ft_set_attribute(&flag, &p_format);
			ft_set_width(&flag, &p_format, (int)v_arg);
			if (flag->has_star_width)
				v_arg = va_arg(args, void *);
			ft_set_precision(&flag, &p_format, (int)v_arg);
			if (flag->has_star_precision)
				v_arg = va_arg(args, void *);
			if (ft_is_indicator(*p_format))
			{
				flag->has_indicator = 1;
				flag->indicator = *p_format;
				if (flag->indicator == '%')
					sum += ft_int_putchar_fd(*p_format, 1);
				else if (flag->indicator == 'd' || flag->indicator == 'i')
				{
					while (flag->has_precision && flag->precision-- > (int)ft_intlen((int) v_arg))
					{
						sum += ft_putnbr_base(0, "01", true);
					}
					sum += ft_putnbr_base((int)v_arg,"0123456789", true);
				}
				else if (flag->indicator == 'u' || flag->indicator == 'x' || flag->indicator == 'X')
				{
					if (flag->indicator == 'u')
						sum += ft_luint_putnbr_base((unsigned int)v_arg, "0123456789", true);
					else if (flag->indicator == 'x')
						sum += ft_luint_putnbr_base((unsigned int)v_arg, "0123456789abcdef", true);
					else
						sum += ft_luint_putnbr_base((unsigned int)v_arg, "0123456789ABCDEF", true);
				}
				else if (flag->indicator == 'c' || flag->indicator == 's')
				{
					if (!v_arg && flag->indicator == 's')
						sum += ft_int_putstr_fd("(null)", 1);
					else if (flag->indicator == 'c')
						sum += ft_int_putchar_fd((char)v_arg, 1);
					else
						sum += ft_int_putstr_fd((char *)v_arg, 1);
				}
				else if (flag->indicator == 'p')
				{
					sum += ft_int_putstr_fd("0x", 1);
					sum += ft_luint_putnbr_base((unsigned long int)&(*v_arg), "0123456789abcdef", 1);
				}
					//ft_putstr_fd((char *)v_arg, 1);
			}
		}
		else
			sum += ft_int_putchar_fd((char)*p_format, 1);
		p_format++;
	}
	va_end(args);
	return (sum);
}
