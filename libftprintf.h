/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:44:16 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/18 21:46:07 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "./libft/libft.h"
# include <stdarg.h>

int	ft_printf(const char *fmt, ...);
int	ft_is_attribute(int c);
int	ft_is_indicator(int c);
#endif
