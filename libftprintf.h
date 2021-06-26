/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:44:16 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/26 12:21:16 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "./libft/libft.h"
# include <stdarg.h>

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

int	ft_printf(const char *fmt, ...);
int	ft_is_attribute(int c);
int ft_is_field_width(int c);
int	ft_is_precision(int c);
int	ft_is_indicator(int c);

// libft ?
int	ft_int_putchar_fd(char c, int fd);
int	ft_int_putstr_fd(char *str, int fd);
int	ft_check_base(char *base, int *base_2_convert);
int	ft_putnbr_base(int nbr, char *base, int restart);
int	ft_luint_putnbr_base(unsigned long int nbr, char *base, int restart);
#endif
