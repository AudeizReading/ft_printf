/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/19 18:25:00 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

typedef struct s_printf_flags
{
	int	has_attribute;
	int	has_field_length;
	int	has_precision;
	int	has_indicator;
}				t_printf_flags;

int	ft_is_attribute(int c)
{
	if (!ft_strchr("0-", c))
		return (0);
	return (1);
}

/*int ft_is_field_lenght(int c, int prev_c)
{
	if (!ft_strchr(".", int c))
		return (0);
	return (1);
}

int	ft_is_precision(int c, int next_c)
{
}*/

int	ft_is_indicator(int c)
{
	if (!ft_strchr("diuxXcsp", c))
		return (0);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	void			*v_arg;
	t_printf_flags	*flag;

	flag = &(t_printf_flags){0, 0, 0, 0};
	va_start(args, format);
	while (*format)
	{
		/* Il faudrait également vérifier qu'il y a autant de % que d'arguments
		** en bouclant sur va_arg, donc on ferait deux boucles sur les params
		** variadiques */
		if (*format == '%' && *(++format))
		{
			v_arg = va_arg(args, void *);
			if (*format == '%')
				ft_putchar_fd('%', 1);
			else if (ft_is_attribute(*format))
			/*else if (*format == '0' || *format == '-')*/
			{
				/* if (*format == '0' || *format == '-')*/
				/* Test vogspehere a distance apres anno*/
				/* Nous avons donc un attribut à traiter, gestion alignement et
				** remplissage*/
				/* Si 0 remplissage à gauche avec des 0 si d i o u x X, sinon
				** avec des espaces*/
				/* Si - remplissage à droite avec des espaces sauf si n, prend
				** la priorité si associé avec 0*/
				/* Par défaut alignement à droite*/
				flag->has_attribute = 1;
				ft_putstr_fd("Il y a un alignement à gerer\n", 1);
				ft_putstr_fd((char *)v_arg, 1);
			}
			else if (ft_isdigit(*format) /*&& *(format - 1) != '.'*/)
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
				flag->has_field_length = 1;
				ft_putstr_fd((char *)v_arg, 1);
				ft_putstr_fd("Il y a une largeur de champ à gérer\n", 1);
			}
			else if (*format == '.' && (ft_isdigit(*(++format))))
			/*else if (*format == '.' && (ft_isdigit(*(format + 1))))*/
			{
				/* Nous avons une précision à gérer, une précision est tjs
				** suivie d'un nombre, faire attention car il semblerait qu'une
				** précision puisse être negative */
				/* Indique le nombre de chiffres de l'argument à afficher */
				/* Si précision sur chaine de char associée à une largeur de
				** champ affiche alors "précision" max char */
				flag->has_precision = 1;
				ft_putstr_fd((char *)v_arg, 1);
				ft_putstr_fd("Il y a une précision à gérer\n", 1);
			}
			else if (ft_is_indicator(*format))
			/*else if (*format == 'd' || *format == 'i' || *format == 'u' || *format == 'x' || *format == 'X' || *format == 'c' || *format == 's' || *format == 'p')*/
			{
				/* if (*format == 'd' || *format == 'i' || *format == 'u' ||
				 *format == 'x' || *format == 'X' || *format == 'c' ||
				 *format == 's' || *format == 'p')*/
				/* Nous avons donc un indicateur de conversion à gérer */
				flag->has_indicator = 1;
				ft_putstr_fd("Il y a une conversion de l'argument courant à effectuer\n", 1);
				ft_putstr_fd((char *)v_arg, 1);
			}
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
