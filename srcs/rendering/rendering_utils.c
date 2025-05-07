/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 06:37:58 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/28 13:03:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_tuple	get_position(t_ray ray, float t)
{
	t_tuple	result;

	result.x = ray.origin.x + (t * ray.direction.x);
	result.y = ray.origin.y + (t * ray.direction.y);
	result.z = ray.origin.z + (t * ray.direction.z);
	result.w = 1;
	return (result);
}

static void	my_pixel_put(int x, int y, t_image *img, unsigned int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

// trouver l'intersection la plus proche
void	handle_pixel(int x, int y, t_window *window)
{
	float		closest_i;
	double		color;
	t_tuple		position;
	t_object	*object;

	object = NULL;
	closest_i = closest_intersection(window->scene, &object);
	if (closest_i < INFINITY)
	{
		position = get_position(window->scene->primary, closest_i);
		if (tuple_distance(position, window->scene->camera->ray.origin) == 0)
			color = rgb_to_hex(object->material.color);
		else
			color = lighting(window->scene, object, position);
	}
	else
		color = 0.0;
	my_pixel_put(x, y, &window->image, color);
}

void	image_view_port(t_window *window)
{
	float	fov_x_rad;
	float	aspect_ratio;
	int		d;

	d = 1;
	fov_x_rad = window->scene->camera->fov * (M_PI / 180.0f);
	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	window->viewport.plane_width = 2 * d * tan(fov_x_rad / 2.0f);
	window->viewport.plane_height = window->viewport.plane_width / aspect_ratio;
}

void	compute_plan_vectors(t_window *window)
{
	t_tuple	world_up;
	t_tuple	right;
	t_tuple	up;

	world_up = set_tuple(0, 1, 0, 0);
	if (fabs(dot_product(window->scene->camera->ray.direction,
				world_up)) > 0.999f)
		world_up = set_tuple(1, 0, 0, 0);
	right = compute_cross_produt(world_up,
			window->scene->camera->ray.direction);
	normalize_tuple(&right);
	up = compute_cross_produt(window->scene->camera->ray.direction, right);
	normalize_tuple(&up);
	window->viewport.right = right;
	window->viewport.up = up;
}
