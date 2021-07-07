/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:44:16 by alellouc          #+#    #+#             */
/*   Updated: 2021/07/02 13:06:03 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "./libft/libft.h"
# include <stdarg.h>

typedef struct s_printf_flags
{
	t_bool		has_attribute;
	char		attribute;
	t_bool		has_width;
	t_bool		has_star_width;
	int			width;
	t_bool		has_precision;
	t_bool		has_star_precision;;
	int			precision;
	t_bool		has_indicator;
	char		indicator;
}				t_printf_flags;

int	ft_printf(const char *fmt, ...);
t_bool	ft_is_attribute(int c);
t_bool	ft_is_width(int c);
t_bool	ft_is_precision(int c);
t_bool	ft_is_indicator(int c);
void	ft_set_attribute(t_printf_flags **flag, char **p_format);
void	ft_set_width(t_printf_flags **flag, char **p_format, int v_arg);
void	ft_set_precision(t_printf_flags **flag, char **p_format, int v_arg);
#endif
