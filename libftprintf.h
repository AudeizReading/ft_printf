/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:44:16 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/25 21:42:53 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "./libft/libft.h"
# include <stdarg.h>

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
