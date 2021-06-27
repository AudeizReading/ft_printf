/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:44:16 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/27 13:27:07 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "./libft/libft.h"
# include <stdarg.h>

typedef enum	e_bool
{
	false,
	true
}				t_bool;

typedef struct s_printf_flags
{
	t_bool		has_attribute;
	char		attribute;
	t_bool		has_field_width;
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
t_bool	ft_is_field_width(int c);
t_bool	ft_is_precision(int c);
t_bool	ft_is_indicator(int c);
void	ft_set_attribute(t_printf_flags **flag, char **p_format);
void	ft_set_width(t_printf_flags **flag, char **p_format, int v_arg);
void	ft_set_precision(t_printf_flags **flag, char **p_format, int v_arg);

// libft ?
int		ft_int_putchar_fd(char c, int fd);
int		ft_int_putstr_fd(char *str, int fd);
t_bool	ft_check_invalid_base(char *base, int *base_2_convert);
int		ft_putnbr_base(int nbr, char *base, t_bool restart);
int		ft_luint_putnbr_base(unsigned long int nbr, char *base, t_bool restart);
#endif
