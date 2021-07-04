/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:32:43 by alellouc          #+#    #+#             */
/*   Updated: 2021/07/04 17:13:44 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_set_attribute(t_printf_flags **flag, char **p_format)
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
		//ft_putendl_fd(&(**p_format), 1);
		//ft_putchar_fd(**p_format, 1);
		(*flag)->has_attribute = true;
		if (((*flag)->attribute == '0' && **p_format == '-') || ((*flag)->attribute == '-' && **p_format == '0'))
		{
		/*	ft_putendl_fd("Attribute avant changement: ", 1);
			ft_putchar_fd((*flag)->attribute, 1);
			ft_putchar_fd('\n', 1);*/
			(*flag)->attribute = '-';
		}
		else
			(*flag)->attribute = **p_format;
		//ft_putchar_fd((*flag)->attribute, 1);
		(*p_format)++;
	}
}

void	ft_set_width(t_printf_flags **flag, char **p_format, int v_arg)
{
	if (ft_is_width(**p_format) || **p_format == '*')
	{
		/* Remplissage avec des espaces sur la gauche, sauf si attribut -
		** */
		/* Pas de troncature avec ce flag, si la largeur est inf à la
		** taille de l'argument la largeur s'adapte à cette taille */
		(*flag)->has_width = true;
		if (**p_format == '*')
		{
			(*flag)->has_star_width = true;
			(*flag)->width = v_arg;
			if ((*flag)->width < 0)
			{
				(*flag)->width *= -1;
				(*flag)->has_attribute = true;
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

void	ft_set_precision(t_printf_flags **flag, char **p_format, int v_arg)
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
		while (*(*p_format + 1) == '-')
		{
			(*p_format)++;
			(*flag)->has_precision = false;
		}
		if (ft_isdigit(*(++(*p_format))))
		{
			if ((*flag)->has_precision)
				(*flag)->precision = ft_atoi(*p_format);
			*p_format += ft_intlen((*flag)->precision);
		}
		else if (**p_format == '*')
		{
			(*flag)->has_star_precision = true;
			(*flag)->precision = v_arg;
			if ((*flag)->precision < 0)
				(*flag)->precision = 1;
			(*p_format)++;
		}
		else
			(*flag)->precision = 0;
	}
}
