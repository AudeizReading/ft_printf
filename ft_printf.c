/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/26 12:30:20 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*typedef struct s_printf_flags
{
	int		has_attribute;
	char	attribute;
	int		has_field_width;
	int		width;
	int		has_precision;
	int		precision;
	int		has_indicator;
	char	indicator;
}				t_printf_flags;*/

/*int	ft_is_attribute(int c)
{
	if (!ft_strchr("0-", c))
		return (0);
	return (1);
}*/

/*int ft_is_field_width(int c)
{
	if (c < '1' || c > '9')
		return (0);
	return (1);
}*/

/*int	ft_is_precision(int c)
{
	if (c != '.')
		return (0);
	return (1);
}*/

/*int	ft_is_indicator(int c)
{
	if (!ft_strchr("diuxXcsp%", c))
		return (0);
	return (1);
}*/

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

int		ft_check_base(char *base, int *base_2_convert)
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
		return (1);
	return (0);
}

int	ft_putnbr_base(int nbr, char *base, int restart)
{
	long int	l_nbr;
	static int	res = 0;
	int			size_base;

	if (restart)
		res = 0;
	l_nbr = nbr;
	size_base = 0;
	if (ft_check_base(base, &size_base))
			return (-1);
	if (l_nbr < 0)
	{
		ft_putchar_fd('-', 1);
		l_nbr = -l_nbr;
		res++;
	}
	if (l_nbr >= size_base)
		ft_putnbr_base(l_nbr / size_base, base, 0);
	res += ft_int_putchar_fd(base[l_nbr % size_base], 1);
	return (res);
}

int	ft_luint_putnbr_base(unsigned long int nbr, char *base, int restart)
{
	unsigned long int	l_nbr;
	int					size_base;
	static int			res = 0;

	if (restart)
		res = 0;
	l_nbr = nbr;
	size_base = 0;
	if (ft_check_base(base, &size_base))
			return (-1);
	if (l_nbr >= (unsigned int)size_base)
		ft_luint_putnbr_base(l_nbr / size_base, base, 0);
	res += ft_int_putchar_fd(base[l_nbr % size_base], 1);
	return (res);
}

int	ft_printf(const char *format, ...)
{
	/* Ne pas oublier de recuperer la taille des elements pour le retour final */
	/* Ne pas oublier de gerer les etoiles avec la width et la precision */
	int				res;
	char			*p_format;
	va_list			args;
	void			*v_arg;
	t_printf_flags	*flag;

	p_format = (char *)format;
	res = 0;
	flag = &(t_printf_flags){0, 0, 0, 0, 0, 1, 0, 0};
	va_start(args, format);
	while (*p_format)
	{
		/* Il faudrait également vérifier qu'il y a autant de % que d'arguments
		** en bouclant sur va_arg, donc on ferait deux boucles sur les params
		** variadiques */
		if (*p_format == '%' && *(++p_format))
		{
			v_arg = va_arg(args, void *);
			while (ft_is_attribute(*p_format))
			{
				/* Nous avons donc un attribut à traiter, gestion alignement et
				** remplissage*/
				/* Si 0 remplissage à gauche avec des 0 si d i o u x X, sinon
				** avec des espaces*/
				/* Si - remplissage à droite avec des espaces sauf si n, prend
				** la priorité si associé avec 0*/
				/* Par défaut alignement à droite*/

				/* Faire une condition que si - et 0 en meme temps alors - */

				flag->has_attribute = 1;
				if ((flag->attribute == '0' && *p_format == '-') ||
						(flag->attribute == '-' && *p_format == '0'))
					flag->attribute = '-';
				else
					flag->attribute = *p_format;
				p_format++;
			}
			if (ft_is_field_width(*p_format) || *p_format == '*')
			{
				/* Nous avons donc une largeur de champ à gérer, attention il
				** peut y avoir une étoile remplaçant cette valeur, il faut la
				** récup avec (int)v_arg */
				/* Une largeur négative est considérée comme l'attribut - suivi
				** d'une largeur de champ */
				/* Remplissage avec des espaces sur la droite, sauf si attribut
				** */
				/* Pas de troncature avec ce flag, si la largeur est inf à la
				** taille de l'argument la largeur s'adapte à cette taille */
				// Gerer le cas * avec arg < 0 (-> si - alors attribut = -)
				flag->has_field_width = 1;
				if (*p_format == '*')
				{
					flag->width = (int)v_arg;
					v_arg = va_arg(args, void *);
					p_format++;
				}
				else
				{
					flag->width = ft_atoi(p_format);
					p_format += ft_intlen(flag->width);
				}
			}
			if (ft_is_precision(*p_format)) 
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
				flag->has_precision = 1;
				while (*(p_format + 1) == '-')
					p_format++;
				if (ft_isdigit(*(++p_format)))
				{
					flag->precision = ft_atoi(p_format);
					p_format += ft_intlen(flag->precision);
				}
				else if (*p_format == '*')
				{
					flag->precision = (int)v_arg;
					v_arg = va_arg(args, void *);
					p_format++;
				}
				else
					flag->precision = 0;
			}
			if (ft_is_indicator(*p_format))
			{
				flag->has_indicator = 1;
				flag->indicator = *p_format;
				if (flag->indicator == '%')
					res += ft_int_putchar_fd(*p_format, 1);
				else if (flag->indicator == 'd' || flag->indicator == 'i')
					res += ft_putnbr_base((int)v_arg,"0123456789", 1);
				else if (flag->indicator == 'u' || flag->indicator == 'x' || flag->indicator == 'X')
				{
					if (flag->indicator == 'u')
						res += ft_luint_putnbr_base((unsigned int)v_arg, "0123456789", 1);
					else if (flag->indicator == 'x')
						res += ft_luint_putnbr_base((unsigned int)v_arg,"0123456789abcdef", 1);
					else
						res += ft_luint_putnbr_base((unsigned int)v_arg,"0123456789ABCDEF", 1);
				}
				else if (flag->indicator == 'c' || flag->indicator == 's')
				{
					if (!v_arg && flag->indicator == 's')
						res += ft_int_putstr_fd("(null)", 1);
					else if (flag->indicator == 'c')
						res += ft_int_putchar_fd((char)v_arg, 1);
					else
						res += ft_int_putstr_fd((char *)v_arg, 1);
				}
				else if (flag->indicator == 'p')
				{
					res += ft_int_putstr_fd("0x", 1);
					res += ft_luint_putnbr_base((unsigned long int)&(*v_arg), "0123456789abcdef", 1);
				}
					//ft_putstr_fd((char *)v_arg, 1);
			}
		}
		else
			res += ft_int_putchar_fd((char)*p_format, 1);
		p_format++;
	}
	va_end(args);
	//ft_putnbr_fd(res, 1);
	//ft_putnbr_fd(ft_int_putstr_fd(" Test fn\n", 1), 1);
	//ft_putstr_fd("Attribut : ", 1);
	//ft_putstr_fd(&flag->attribute, 1);
	//ft_putstr_fd("\n", 1);
	return (res);
}
