/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/07/05 15:32:03 by alellouc         ###   ########.fr       */
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

int	ft_putnbr_uxX(int nbr, char *base,  int fill_0, t_bool restart)
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
	flag = &(t_printf_flags){false, 0, false, false, 0, false, false, 0, false, 0};
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
			
		/*	if (flag->attribute == '0' && flag->has_precision)
				flag->has_attribute = false;*/
			if (ft_is_indicator(*p_format))
			{
				flag->has_indicator = 1;
				flag->indicator = *p_format;
				if (flag->indicator == '%')
				{
					if (*(p_format - 1) != flag->indicator)
					{
						
						if (!flag->has_attribute)
						{
							while (flag->has_width && flag->width-- > (int)ft_strlen((const char *)&("%")))
								sum += ft_int_putchar_fd(' ', 1);
						}
						else if (flag->attribute == '0')
						{
						/*	ft_putendl_fd("Has star precision ?", 1);
							ft_putnbr_fd(flag->has_star_precision, 1);
							ft_putchar_fd('\n', 1);ft_putendl_fd("Has precision ?", 1);
							ft_putnbr_fd(flag->has_precision, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Precision", 1);
							ft_putnbr_fd(flag->precision, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Has width ?", 1);
							ft_putnbr_fd(flag->has_width, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Largeur", 1);
							ft_putnbr_fd(flag->width, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Has star width ?", 1);
							ft_putnbr_fd(flag->has_star_width, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Attribut", 1);
							ft_putchar_fd(flag->attribute, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Has attribute ?", 1);
							ft_putnbr_fd(flag->has_attribute, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Indicateur", 1);
							ft_putchar_fd(flag->indicator, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("strlen p_format ?", 1);
							ft_putnbr_fd((int)ft_strlen((const char *)&("%")), 1);
							ft_putchar_fd('\n', 1);*/
							while (flag->has_width && flag->width-- > (int)ft_strlen((const char *)&("%")))
								sum += ft_int_putchar_fd('0', 1);
						}
						sum += ft_int_putchar_fd(*p_format, 1);
						if (flag->attribute == '-')
						{
							while (flag->has_width && flag->width-- > (int)ft_strlen((const char *)&("%")))
								sum += ft_int_putchar_fd(' ', 1);
						}
					}
					else
						sum += ft_int_putchar_fd(*p_format, 1);
				}
				else if (flag->indicator == 'd' || flag->indicator == 'i')
				{
					if (flag->attribute == '0' && flag->has_precision)
						flag->has_attribute = false;
					int	fill_0;
					int fill_space;
					int size;
					int arg_len;

					fill_0 = 0;
					fill_space = 0;
					arg_len = (int)ft_intlen_printf((int)v_arg);
					if (arg_len < flag->precision)
					{
						size = flag->precision;
						fill_0 = size - arg_len;
					}
					else
						size = arg_len;
					if (size < flag->width)
						fill_space = flag->width - size;
					// Gestion 0 avec precision 0
					if (flag->has_precision && flag->precision == 0 && (int)v_arg == 0)
					{
						if (flag->has_width)
						{
							fill_space++;
							while (fill_space-- > 0)
								sum += ft_int_putchar_fd(' ', 1);
						}
						sum += 0;
					}
					else
					{
						if ((int)v_arg < 0)
							fill_space--;
						if ((!flag->has_attribute || (flag->precision > 0 && flag->attribute == '0')))
						{
							while (fill_space-- > 0)
								sum += ft_int_putchar_fd(' ', 1);
						}
						if ((int)v_arg < 0)
							ft_putchar_fd('-', 1);
						if (flag->attribute == '0' && flag->has_width && !flag->has_precision)
						{
							while (fill_space-- > 0)
								sum += ft_int_putchar_fd('0', 1);
						}
						sum += ft_putnbr_di((int)v_arg, fill_0, true);
						if (flag->attribute == '-' && (flag->has_width || flag->has_star_width))
						{
						/*	ft_putendl_fd("Has star precision ?", 1);
							ft_putnbr_fd(flag->has_star_precision, 1);
							ft_putchar_fd('\n', 1);ft_putendl_fd("Has precision ?", 1);
							ft_putnbr_fd(flag->has_precision, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Precision", 1);
							ft_putnbr_fd(flag->precision, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Has width ?", 1);
							ft_putnbr_fd(flag->has_width, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Largeur", 1);
							ft_putnbr_fd(flag->width, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Has star width ?", 1);
							ft_putnbr_fd(flag->has_star_width, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Attribut", 1);
							ft_putchar_fd(flag->attribute, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Has attribute ?", 1);
							ft_putnbr_fd(flag->has_attribute, 1);
							ft_putchar_fd('\n', 1);
							ft_putendl_fd("Indicateur", 1);
							ft_putchar_fd(flag->indicator, 1);
							ft_putchar_fd('\n', 1);*/
							while (fill_space-- > 0)
								sum += ft_int_putchar_fd(' ', 1);
						}
					}
					flag->attribute = 0;
			//		flag = &(t_printf_flags){false, 0, false, false, 0, false, false, 0, false, 0};
				}
				else if (flag->indicator == 'u' || flag->indicator == 'x' || flag->indicator == 'X')
				{
					if (flag->attribute == '0' && flag->has_precision)
						flag->has_attribute = false;
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
					{
					/*	ft_putendl_fd("Has star precision ?", 1);
						ft_putnbr_fd(flag->has_star_precision, 1);
						ft_putchar_fd('\n', 1);ft_putendl_fd("Has precision ?", 1);
						ft_putnbr_fd(flag->has_precision, 1);
						ft_putchar_fd('\n', 1);
						ft_putendl_fd("Precision", 1);
						ft_putnbr_fd(flag->precision, 1);
						ft_putchar_fd('\n', 1);
						ft_putendl_fd("Has width ?", 1);
						ft_putnbr_fd(flag->has_width, 1);
						ft_putchar_fd('\n', 1);
						ft_putendl_fd("Largeur", 1);
						ft_putnbr_fd(flag->width, 1);
						ft_putchar_fd('\n', 1);
						ft_putendl_fd("Has star width ?", 1);
						ft_putnbr_fd(flag->has_star_width, 1);
						ft_putchar_fd('\n', 1);
						ft_putendl_fd("Attribut", 1);
						ft_putchar_fd(flag->attribute, 1);
						ft_putchar_fd('\n', 1);
						ft_putendl_fd("Has attribute ?", 1);
						ft_putnbr_fd(flag->has_attribute, 1);
						ft_putchar_fd('\n', 1);
						ft_putendl_fd("Indicateur", 1);
						ft_putchar_fd(flag->indicator, 1);
						ft_putchar_fd('\n', 1);*/
						if (!flag->has_attribute)
						{
							while (flag->has_width && flag->width-- > (int)ft_strlen((const char *)&(v_arg)))
								sum += ft_int_putchar_fd(' ', 1);
						}
						else if (flag->attribute == '0')
						{
							while (flag->has_width && flag->width-- > (int)ft_strlen((const char *)&(v_arg)))
								sum += ft_int_putchar_fd('0', 1);
						}
						//sum += ft_int_putchar_fd(*p_format, 1);
						sum += ft_int_putchar_fd((char)v_arg, 1);
						if (flag->attribute == '-')
						{
							while (flag->has_width && flag->width-- > (int)ft_strlen((const char *)&(v_arg)))
								sum += ft_int_putchar_fd(' ', 1);
						}
					//	sum += ft_int_putchar_fd((char)v_arg, 1);
					}
					else
						sum += ft_int_putstr_fd((char *)v_arg, 1);
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
//	flag->width = 0;
//	ft_putnbr_base(sum, "0123456789", true);
//	ft_putchar_fd('\n', 1);
	return (sum);
}
