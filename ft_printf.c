/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/23 11:30:06 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

typedef struct s_printf_flags
{
	int		has_attribute;
	char	attribute;
	int		has_field_width;
	int		width;
	int		has_precision;
	int		precision;
	int		has_indicator;
	char	indicator;
}				t_printf_flags;

int	ft_is_attribute(int c)
{
	if (!ft_strchr("0-", c))
		return (0);
	return (1);
}

int ft_is_field_width(int c)
{
	if (c < '1' || c > '9')
		return (0);
	return (1);
}

/*int	ft_is_precision(int c, int next_c)
{
}*/

int	ft_is_indicator(int c)
{
	if (!ft_strchr("diuxXcsp%", c))
		return (0);
	return (1);
}

int	ft_int_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
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


/*void	ft_putnbr_base(int nbr, char *base)
{
	long int	l_nbr;
	int			size_base;

	l_nbr = nbr;
	size_base = 0;
	if (ft_check_base(base, &size_base))
			return;
	if (l_nbr < 0)
	{
		ft_putchar_fd('-', 1);
		l_nbr = -l_nbr;
	}
	if (l_nbr >= size_base)
		ft_putnbr_base(l_nbr / size_base, base);
	ft_putchar_fd(base[l_nbr % size_base], 1);
}*/

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
	{
		ft_putnbr_base(l_nbr / size_base, base, 0);
	}
//	ft_putchar_fd(base[l_nbr % size_base], 1);
	res += ft_int_putchar_fd(base[l_nbr % size_base], 1);
	return (res);
}

void	ft_luint_putnbr_base(unsigned int nbr, char *base)
{
	unsigned long int	l_nbr;
	int					size_base;

	l_nbr = nbr;
	size_base = 0;
	if (ft_check_base(base, &size_base))
			return;
	if (l_nbr >= (unsigned int)size_base)
		ft_luint_putnbr_base(l_nbr / size_base, base);
	ft_putchar_fd(base[l_nbr % size_base], 1);
}

int	ft_printf(const char *format, ...)
{
	/* Ne pas oublier de recuperer la taille des elements pour le retour final */
	/* Ne pas oublier de gerer les eetoiles avec la width et la precision */
	/* Attention, je ne sais pas pourquoi je ne lis pas une chaine sans
	** formattage -> a resoudre */
	int				res;
	char			*p_format;
	va_list			args;
	void			*v_arg;
	t_printf_flags	*flag;

	p_format = (char *)format;
	if (!p_format)
	{
		ft_putendl_fd("(null)", 1);
		return (0);
	}
	(void) res;
	flag = &(t_printf_flags){0, 0, 0, 0, 0, 1, 0, 0};
	va_start(args, format);
	//ft_putendl_fd((char *)p_format, 1);
	while (*p_format)
	{
		/* Il faudrait également vérifier qu'il y a autant de % que d'arguments
		** en bouclant sur va_arg, donc on ferait deux boucles sur les params
		** variadiques */
		if (*p_format == '%' && *(++p_format))
	//	if (*p_format == '%')
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
				flag->attribute = *p_format;
				p_format++;
			}
			if (ft_is_field_width(*p_format))
			{
				/* Nous avons donc une largeur de champ à gérer, attention il
				** peut y avoir une étoile remplaçant cette valeur, il faut la
				** récup avec (int)v_arg */
				/* Une largeur négative est considérée comme l'attribut - suivi
				** d'une largeur de champ */
				/* Remplissage avec des espaces sur la droite, sauf si attribut
				** */
				/* Attention, checker si la largeur est un nombre à plusieurs
				** chiffres et itérer sur *format le cas échéant */
				/* Pas de troncature avec ce flag, si la largeur est inf à la
				** taille de l'argument la largeur s'adapte à cette taille */
				flag->has_field_width = 1;
				flag->width = ft_atoi(p_format);
				p_format += ft_intlen(flag->width);
			}
			if (*p_format == '.') 
			{
				/* Nous avons une précision à gérer, une précision est tjs
				** suivie d'un nombre, faire attention car il semblerait qu'une
				** précision puisse être negative */
				/* Indique le nombre de chiffres de l'argument à afficher */
				/* Si précision sur chaine de char associée à une largeur de
				** champ affiche alors "précision" max char */
				flag->has_precision = 1;
				while (*(p_format + 1) == '-')
					p_format++;
				if (ft_isdigit(*(++p_format)))
				{
					flag->precision = ft_atoi(p_format);
					p_format += ft_intlen(flag->precision);
				}
				else
					flag->precision = 0;
			}
			if (ft_is_indicator(*p_format))
			{
				flag->has_indicator = 1;
				flag->indicator = *p_format;
				if (flag->indicator == '%')
				{
					ft_putchar_fd(*p_format, 1);
				}
				else if (flag->indicator == 'd' || flag->indicator == 'i')
					ft_putnbr_base(ft_putnbr_base((unsigned int)v_arg,"0123456789", 1), "0123456789", 1);
				else if (flag->indicator == 'u' || flag->indicator == 'x' || flag->indicator == 'X')
				{
					if (flag->indicator == 'u')
						ft_luint_putnbr_base((unsigned int)v_arg, "0123456789");
					else if (flag->indicator == 'x')
						ft_luint_putnbr_base((unsigned int)v_arg,"0123456789abcdef");
					else
						ft_luint_putnbr_base((unsigned int)v_arg,"0123456789ABCDEF");
				}
				else if (flag->indicator == 'c' || flag->indicator == 's')
					ft_putstr_fd((char *)v_arg, 1);
				else if (flag->indicator == 'p')
					ft_putstr_fd((char *)v_arg, 1);
			}
		}
		else
			ft_putchar_fd((char)*p_format, 1);
		p_format++;
		// If I don't put a \n here, if there is no \n at the end, there is no output, don't know why because on the wsl this matter doesn't exist
		// It is stdout the problem -> This file is buffered before getting out its flow, so it is an expected behavior, thank you for having past one day and half on it...
		// For testing send the output toward arbitrary file descriptor that it is not stdout and make a diff a the ft_printf file and the printf file
		//ft_putchar_fd('\n', 1);
	}
	va_end(args);
	return (0);
}
