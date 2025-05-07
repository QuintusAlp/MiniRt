/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:34:02 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/28 13:01:04 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	compute_top_left_corner(t_window *window)
{
	t_tuple	center;
	t_tuple	top_left;
	int		d;
	t_tuple	top_left_x;
	t_tuple	top_left_y;

	d = 1;
	center = tuple_addition(window->scene->camera->ray.origin,
			tuple_scalar_multiplication(window->scene->camera->ray.direction,
				(float)d));
	top_left_x = tuple_substraction(center,
			tuple_scalar_multiplication(window->viewport.right,
				window->viewport.plane_width / 2));
	top_left_y = tuple_scalar_multiplication(window->viewport.up,
			window->viewport.plane_height / 2);
	top_left = tuple_addition(top_left_x, top_left_y);
	window->viewport.top_left = top_left;
}

void	set_primary_v(int x, int y, t_window *window)
{
	t_tuple	horizontal_offset;
	t_tuple	vertical_offset;
	t_tuple	pixel_position;
	float	u;
	float	v;

	u = ((float)x + 0.5f) / (float)WIDTH;
	v = ((float)y + 0.5f) / (float)HEIGHT;
	horizontal_offset = tuple_scalar_multiplication(window->viewport.right, u
			* window->viewport.plane_width);
	vertical_offset = tuple_scalar_multiplication(window->viewport.up, v
			* window->viewport.plane_height);
	pixel_position = tuple_substraction(tuple_addition(
				window->viewport.top_left,
				horizontal_offset), vertical_offset);
	window->scene->primary.direction = tuple_substraction(pixel_position,
			window->scene->primary.origin);
	normalize_tuple(&window->scene->primary.direction);
}
