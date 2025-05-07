/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:27:47 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:19:47 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_rgb	color_addition(t_rgb c1, t_rgb c2)
{
	t_rgb	result;

	set_rgb(&result, (c1.r + c2.r), (c1.g + c2.g), (c1.b + c2.b));
	return (result);
}

t_rgb	color_scal_mult(t_rgb c, float scalar)
{
	t_rgb	result;

	set_rgb(&result, (c.r * scalar), (c.g * scalar), (c.b * scalar));
	return (result);
}

t_rgb	color_multiply(t_rgb c1, t_rgb c2)
{
	t_rgb	result;

	set_rgb(&result, (c1.r * c2.r) / 255, (c1.g * c2.g) / 255, (c1.b * c2.b)
		/ 255);
	return (result);
}

unsigned int	rgb_to_hex(t_rgb color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = color.r;
	g = color.g;
	b = color.b;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

void	set_rgb(t_rgb *colour, float r, float g, float b)
{
	colour->r = r;
	colour->g = g;
	colour->b = b;
}
