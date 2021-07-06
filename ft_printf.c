/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/07/06 22:30:48 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
/*void	set_indicator(t_printf_flags **flag, char **p_format, int v_arg)
{
}*/
size_t	ft_intlen_printf(int n)
{
	size_t		result;
	long int	c;

	c = n;
	result = 1;
	if (c < 0)
		c = -c;
	while (c / 10 > 0)
	{
		result++;
		c /= 10;
	}
	return (result);
}

int	ft_putnbr_di(int nbr, int fill_0, t_bool restart)
{
	long int	l_nbr;
	static int	sum = 0;
	if (restart)
		sum = 0;
	l_nbr = nbr;
	if (l_nbr < 0)
		l_nbr = -l_nbr;
	while (fill_0-- > 0)
		sum += ft_int_putchar_fd('0', 1);
	if (l_nbr >= 10)
		ft_putnbr_di(l_nbr / 10, fill_0, false);
	sum += ft_int_putchar_fd(l_nbr % 10 + 48, 1);
	return (sum);
}

int	ft_putnbr_uxX(int nbr, char *base, int fill_0, t_bool restart)
{
	unsigned long int	l_nbr;
	int					size_base;
	static int			sum = 0;

	if (restart)
		sum = 0;
	l_nbr = nbr;
	size_base = 0;
	if (ft_check_invalid_base(base, &size_base))
		return (-1);
	while (fill_0-- > 0)
		sum += ft_int_putchar_fd('0', 1);
	if (l_nbr >= (unsigned int)size_base)
		ft_putnbr_uxX(l_nbr / size_base, base, fill_0, false);
	sum += ft_int_putchar_fd(base[l_nbr % size_base], 1);
	return (sum);
}

int	ft_putstr_s(char *str, int precision)
{
	int	sum;
	int	i;

	sum = 0;
	i = 0;
	while (*str && precision-- > 0)
		sum += ft_int_putchar_fd(*str++, 1);
	return (sum);

}
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
	// struct a modif
	flag = &(t_printf_flags){false, 0, false, false, 0, false, false, 0, false, 0};
	va_start(args, format);
	while (*p_format)
	{
		if (*p_format == '%' && *(++p_format))
		{
			if (flag->indicator != '%')
				v_arg = va_arg(args, void *);
			if (ft_is_indicator(*p_format))
			{
				flag->has_indicator = 1;
				flag->indicator = *p_format;
				if (flag->indicator == '%')
					sum += ft_int_putchar_fd(*p_format, 1);
				else if (flag->indicator == 'd' || flag->indicator == 'i')
					sum += ft_putnbr_base((int)v_arg, "0123456789", 1);
				else if (flag->indicator == 'u' || flag->indicator == 'x' || flag->indicator == 'X')
				{
					if (flag->indicator == 'u')
						sum += ft_luint_putnbr_base((unsigned int)v_arg, "0123456789", true);
					else if (flag->indicator == 'x')
						sum += ft_luint_putnbr_base((unsigned int)v_arg, "0123456789abcdef", true);
					else
						sum += ft_luint_putnbr_base((unsigned int)v_arg, "0123456789ABCDEF", true);
				}
				else if (flag->indicator == 'c')
						sum += ft_int_putchar_fd((unsigned char)v_arg, 1);
				else if (flag->indicator == 's')
				{
					if (!v_arg)
					{
						sum += ft_int_putstr_fd("(null)", 1);
					}
					else
					{
						sum += ft_int_putstr_fd((char *)v_arg, 1);
					}
				}
				else if (flag->indicator == 'p')
				{
					sum += ft_int_putstr_fd("0x", 1);
					sum += ft_luint_putnbr_base((unsigned long int)&(*v_arg), "0123456789abcdef", 1);
				}
			}
		}
		else
			sum += ft_int_putchar_fd((char)*p_format, 1);
		p_format++;
	}
	va_end(args);
	return (sum);
}
