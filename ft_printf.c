/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 08:12:37 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/22 18:27:02 by alellouc         ###   ########.fr       */
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
	if (!ft_strchr("diuxXcsp%", c))
		return (0);
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long int	l_nbr;
	(void)base;

	l_nbr = nbr;
	if (l_nbr < 0)
	{
		ft_putchar_fd('-', 1);
		l_nbr = -l_nbr;
	}
	if (l_nbr >= 10)
		ft_putnbr_base(l_nbr / 10, base);
	ft_putchar_fd(l_nbr % 10 + '0', 1);
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
	flag = &(t_printf_flags){0, 0, 0, 0, 0, 0, 0, 0};
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
				/* if (*p_format == '0' || *p_format == '-')*/
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
				/*ft_putstr_fd(&flag->attribute, 1);
				ft_putstr_fd("Il y a un alignement à gerer\n", 1);
				ft_putstr_fd((char *)v_arg, 1);*/
				p_format++;
			}
			/*else*/ if (*p_format >= '1' && *p_format <= '9')
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
			/*	ft_putnbr_fd(flag->width, 1);
				ft_putstr_fd((char *)v_arg, 1);
				ft_putstr_fd("Il y a une largeur de champ à gérer\n", 1);*/
				p_format += ft_intlen(flag->width);
			}
			else if (*p_format == '.' && (ft_isdigit(*(++p_format)))) 
				/* Attention cette condition ne considere pas une precision de . qui est valide mais indique une precision 0 */
			{
				/* Nous avons une précision à gérer, une précision est tjs
				** suivie d'un nombre, faire attention car il semblerait qu'une
				** précision puisse être negative */
				/* Indique le nombre de chiffres de l'argument à afficher */
				/* Si précision sur chaine de char associée à une largeur de
				** champ affiche alors "précision" max char */
				// Faire attention a une precision negative
				flag->has_precision = 1;
				flag->precision = ft_atoi(p_format);
			/*	ft_putnbr_fd(flag->precision, 1);
				ft_putstr_fd("Il y a une précision à gérer\n", 1);*/
				p_format += ft_intlen(flag->precision);
			}
			else if (ft_is_indicator(*p_format))
			{
				flag->has_indicator = 1;
				flag->indicator = *p_format;
			//	ft_putchar_fd(*p_format, 1);
			//	ft_putchar_fd(flag->indicator, 1);
		//		ft_putchar_fd(flag->indicator, 1);
			//	ft_putstr_fd("Il y a une conversion de l'argument courant à effectuer\n", 1);/**/
				if (flag->indicator == '%')
				{
					ft_putendl_fd("\nVerif de condition", 1);
					//ft_putchar_fd(flag->indicator, 1);
					ft_putchar_fd(*p_format, 1);
				}
				else if (flag->indicator == 'd' || flag->indicator == 'i')
					ft_putnbr_fd((int)v_arg, 1);
				else if (flag->indicator == 'u' || flag->indicator == 'x' || flag->indicator == 'X')
					ft_putnbr_base((unsigned int)v_arg,"0123456789");
					/*ft_putnbr_fd((unsigned int)v_arg, 1);  ft_putnbr_base */
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
		//ft_putchar_fd('\n', 1);
	}
	va_end(args);
	return (0);
}
