/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_flag_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alellouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 08:11:20 by alellouc          #+#    #+#             */
/*   Updated: 2021/07/07 08:11:41 by alellouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf_bonus.h"


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
