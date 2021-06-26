/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:23:24 by alellouc          #+#    #+#             */
/*   Updated: 2021/06/26 12:26:00 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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

int	ft_is_precision(int c)
{
	if (c != '.')
		return (0);
	return (1);
}

int	ft_is_indicator(int c)
{
	if (!ft_strchr("diuxXcsp%", c))
		return (0);
	return (1);
}
