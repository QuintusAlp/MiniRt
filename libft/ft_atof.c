/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qalpesse <qalpesse@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-12 14:30:28 by qalpesse          #+#    #+#             */
/*   Updated: 2025/03/15 20:55:43 by qalpesse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	ft_atof(const char *str)
{
	double	int_part;
	double	dec_part;
	double	sign;
	int		i;

	int_part = 0.0;
	dec_part = 0.0;
	sign = 1.0;
	i = -1;
	if (!str)
		return (0.0);
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign = -1.0;
	}
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			dec_part += (*str++ - '0') * pow(10, i--);
	}
	return ((int_part + dec_part) * sign);
}
