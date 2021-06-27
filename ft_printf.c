/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/27 13:17:17 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_int_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_int_putstr_fd(char *str, int fd)
{
	int	res;

	res = 0;
	while (*str)
		res += ft_int_putchar_fd(*str++, fd);
	return (res);
}

t_bool		ft_check_base(char *base, int *base_2_convert)
{
	while (base[*base_2_convert])
	{
		if (base[*base_2_convert] == base[*base_2_convert + 1]\
				|| base[*base_2_convert] == 43 || base[*base_2_convert] == 45\
				|| base[*base_2_convert] <= 32 || base[*base_2_convert] >= 126)
			return (1);
		(*base_2_convert)++;
	}
	if (*base_2_convert < 2)
		return (true);
	return (false);
}

int	ft_putnbr_base(int nbr, char *base, t_bool restart)
{
	long int	l_nbr;
	static int	sum = 0;
	int			size_base;

	if (restart)
		sum = 0;
	l_nbr = nbr;
	size_base = 0;
	if (ft_check_base(base, &size_base))
			return (-1);
	if (l_nbr < 0)
	{
		ft_putchar_fd('-', 1);
		l_nbr = -l_nbr;
		sum++;
	}
	if (l_nbr >= size_base)
		ft_putnbr_base(l_nbr / size_base, base, false);
	sum += ft_int_putchar_fd(base[l_nbr % size_base], 1);
	return (sum);
}

int	ft_luint_putnbr_base(unsigned long int nbr, char *base, t_bool restart)
{
	unsigned long int	l_nbr;
	int					size_base;
	static int			sum = 0;

	if (restart)
		sum = 0;
	l_nbr = nbr;
	size_base = 0;
	if (ft_check_base(base, &size_base))
			return (-1);
	if (l_nbr >= (unsigned int)size_base)
		ft_luint_putnbr_base(l_nbr / size_base, base, false);
	sum += ft_int_putchar_fd(base[l_nbr % size_base], 1);
	return (sum);
}

void	set_attribute(t_printf_flags **flag, char **p_format)
{
	while (ft_is_attribute(**p_format))
	{
		/* Nous avons donc un attribut à traiter, gestion alignement et
		** remplissage*/
		/* Si 0 remplissage à gauche avec des 0 si d i o u x X, sinon
		** avec des espaces*/
		/* Si - remplissage à droite avec des espaces sauf si n, prend
		** la priorité si associé avec 0*/
		/* Par défaut alignement à droite*/
		//(*flag)->has_attribute = 1;
		(*flag)->has_attribute = true;
		if (((*flag)->attribute == '0' && **p_format == '-') ||
				((*flag)->attribute == '-' && **p_format == '0'))
			(*flag)->attribute = '-';
		else
			(*flag)->attribute = **p_format;
		(*p_format)++;
	}
}

void	set_width(t_printf_flags **flag, char **p_format, int v_arg)
{
	if (ft_is_field_width(**p_format) || **p_format == '*')
	{
		/* Remplissage avec des espaces sur la gauche, sauf si attribut -
		** */
		/* Pas de troncature avec ce flag, si la largeur est inf à la
		** taille de l'argument la largeur s'adapte à cette taille */
		(*flag)->has_field_width = true;
		if (**p_format == '*')
		{
			(*flag)->has_star_width = true;
			(*flag)->width = v_arg;
			if ((*flag)->width < 0)
			{
				(*flag)->width *= -1;
				(*flag)->attribute = '-';
			}
			(*p_format)++;
		}
		else
		{
			(*flag)->width = ft_atoi(*p_format);
			(*p_format) += ft_intlen((*flag)->width);
		}
	}
}

void	set_precision(t_printf_flags **flag, char **p_format, int v_arg)
{
	if (ft_is_precision(**p_format)) 
	{
		/* Nous avons une précision à gérer, une précision est tjs
		** suivie d'un nombre, faire attention car il semblerait qu'une
		** précision puisse être negative  (avec flag *) */
		/* Indique le nombre de chiffres de l'argument à afficher */
		/* Si précision sur chaine de char associée à une largeur de
		** champ affiche alors "précision" max char */
		// Gerer etoile, est ce qu'un nombre accompagne l'etoile ?
		// gerer * avec arg < 0 -> de ce que je lis se calerait sur flag
		// s en essayant d'afficher un nombre max < 0 de caracteres ->
		// Undefined Behavior
		(*flag)->has_precision = true;
	//	while (**(p_format + 1) == '-')
	//		(*p_format)++;
		if (ft_isdigit(*(++(*p_format))))
		{
			(*flag)->precision = ft_atoi(*p_format);
			*p_format += ft_intlen((*flag)->precision);
		}
		else if (**p_format == '*')
		{
			(*flag)->has_star_precision = true;
			(*flag)->precision = v_arg;
			if ((*flag)->precision < 0)
			{
				(*flag)->has_precision = false;
				(*flag)->precision = 0;
			}
			(*p_format)++;
		}
		else
			(*flag)->precision = 0;
	}
}

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
			v_arg = va_arg(args, void *);
			set_attribute(&flag, &p_format);
			set_width(&flag, &p_format, (int)v_arg);
			if (flag->has_star_width)
				v_arg = va_arg(args, void *);
			set_precision(&flag, &p_format, (int)v_arg);
			if (flag->has_star_precision)
				v_arg = va_arg(args, void *);
			if (ft_is_indicator(*p_format))
			{
				flag->has_indicator = 1;
				flag->indicator = *p_format;
				if (flag->indicator == '%')
					sum += ft_int_putchar_fd(*p_format, 1);
				else if (flag->indicator == 'd' || flag->indicator == 'i')
					sum += ft_putnbr_base((int)v_arg,"0123456789", true);
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
	//ft_putnbr_fd(sum, 1);
	//ft_putnbr_fd(ft_int_putstr_fd(" Test fn\n", 1), 1);
	//ft_putstr_fd("Attribut : ", 1);
	//ft_putstr_fd(&flag->attribute, 1);
	//ft_putstr_fd("\n", 1);
	return (sum);
}
