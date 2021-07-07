/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/07/07 12:08:25 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
/*void	set_indicator(t_printf_flags **flag, char **p_format, int v_arg)
{
}*/
typedef struct	s_func
{
	int		(*p_func)(va_list args);
	char	key;
}				t_func;

int	ft_set_ind_c(va_list args)
{
	int	v_arg;
	int	sum;

	sum = 0;
	v_arg = va_arg(args, int);
	return (sum += ft_int_putchar_fd(v_arg, 1));
}

int	ft_set_ind_s(va_list args)
{
	char	*v_arg;
	int		sum;

	sum = 0;
	v_arg = va_arg(args, char *);
	if (!v_arg)
		return (sum += ft_int_putstr_fd("(null)", 1));
	else
		return (sum += ft_int_putstr_fd(v_arg, 1));
}

int	ft_set_ind_d(va_list args)
{
	int		v_arg;
	int		sum;

	sum = 0;
	v_arg = va_arg(args, int);
	return (sum += ft_putnbr_base(v_arg, "0123456789", true));
}

int	ft_set_ind_i(va_list args)
{
	int		v_arg;
	int		sum;

	sum = 0;
	v_arg = va_arg(args, int);
	return (sum += ft_putnbr_base(v_arg, "0123456789", true));
}

int	ft_set_ind_u(va_list args)
{
	unsigned int	v_arg;
	int				sum;

	sum = 0;
	v_arg = va_arg(args, unsigned int);
	return (sum += ft_luint_putnbr_base(v_arg, "0123456789", true));
}

int	ft_set_ind_x(va_list args)
{
	unsigned int	v_arg;
	int				sum;

	sum = 0;
	v_arg = va_arg(args, unsigned int);
	return (sum += ft_luint_putnbr_base(v_arg, "0123456789abcdef", true));
}

int	ft_set_ind_X(va_list args)
{
	unsigned int	v_arg;
	int				sum;

	sum = 0;
	v_arg = va_arg(args, unsigned int);
	return (sum += ft_luint_putnbr_base(v_arg, "0123456789ABCDEF", true));
}

int	ft_set_ind_p(va_list args)
{
	unsigned long int	*v_arg;
	int					sum;

	sum = 0;
	v_arg = va_arg(args, unsigned long int*);
	sum += ft_int_putstr_fd("0x", 1);
	return (sum += ft_luint_putnbr_base((*v_arg), "0123456789abcdef", true));
}

int	ft_set_ind_percent(va_list args)
{
	int	sum;
	(void)args;

	sum = 0;
	return (sum += ft_int_putchar_fd('%', 1));
}
t_func	*ft_set_functions_list(void)
{
	t_func	list[10];

	list[0] = {&(ft_set_ind_c), 'c'};
}

t_func	g_tab[] = 
{
	{&(ft_set_ind_c), 'c'},
	{&(ft_set_ind_s), 's'},
	{&(ft_set_ind_d), 'd'},
	{&(ft_set_ind_i), 'i'},
	{&(ft_set_ind_u), 'u'},
	{&(ft_set_ind_x), 'x'},
	{&(ft_set_ind_X), 'X'},
	{&(ft_set_ind_p), 'p'},
	{&(ft_set_ind_percent), '%'},
	{NULL, -1}
};

int	ft_parse_ind(char c, va_list args)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (g_tab[i].key != -1)
	{
		if (g_tab[i].key == c)
		{
			sum += g_tab[i].p_func(args);
		}
		i++;
	}
	return (sum);
}

int	ft_printf(const char *format, ...)
{
	int				sum;
	char			*p_format;
	va_list	 		args;
	t_printf_flags	*flag;
	t_func			tab[10];

	p_format = (char *)format;
	sum = 0;
	// struct a modif
	flag = &(t_printf_flags){false, 0, false, false, 0, false, false, 0, false, 0};
	va_start(args, format);
	while (*p_format)
	{
		if (*p_format == '%' && *(++p_format))
		{
			if (ft_is_indicator(*p_format))
			{
				flag->has_indicator = 1;
				flag->indicator = *p_format;
				sum += ft_parse_ind(flag->indicator, args);
			}
		}
		else
			sum += ft_int_putchar_fd((char)*p_format, 1);
		p_format++;
	}
	va_end(args);
	return (sum);
}
