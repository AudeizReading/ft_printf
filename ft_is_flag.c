/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <alellouc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 12:23:24 by alellouc          #+#    #+#             */
/*   Updated: 2021/07/02 11:21:11 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"


t_bool	ft_is_attribute(int c)
{
	if (!ft_strchr("0-", c))
		return (false);
	return (true);
}

t_bool ft_is_width(int c)
{
	if (c < '1' || c > '9')
		return (false);
	return (true);
}

t_bool	ft_is_precision(int c)
{
	if (c != '.')
		return (false);
	return (true);
}

t_bool	ft_is_indicator(int c)
{
	if (!ft_strchr("diuxXcsp%", c))
		return (false);
	return (true);
}
