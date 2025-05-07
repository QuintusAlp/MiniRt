/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:33:00 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:59:44 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_corners(t_pyramid *pyramid, t_tuple corners[4])
{
	double	half;

	half = pyramid->base_size / 2.0;
	corners[0] = set_tuple(pyramid->base_center.x - half,
			pyramid->base_center.y, pyramid->base_center.z - half, 1);
	corners[1] = set_tuple(pyramid->base_center.x + half,
			pyramid->base_center.y, pyramid->base_center.z - half, 1);
	corners[2] = set_tuple(pyramid->base_center.x + half,
			pyramid->base_center.y, pyramid->base_center.z + half, 1);
	corners[3] = set_tuple(pyramid->base_center.x - half,
			pyramid->base_center.y, pyramid->base_center.z + half, 1);
}

static bool	pt_in_triangle(t_tuple p, t_tuple a, t_tuple b, t_tuple c)
{
	double	denom;
	double	inv_denom;
	double	u;
	double	v;

	denom = dot_product(tuple_substraction(c, a), tuple_substraction(c, a))
		* dot_product(tuple_substraction(b, a), tuple_substraction(b, a))
		- dot_product(tuple_substraction(c, a), tuple_substraction(b, a))
		* dot_product(tuple_substraction(c, a), tuple_substraction(b, a));
	if (fabs(denom) < 1e-8)
		return (0);
	inv_denom = 1.0 / denom;
	u = (dot_product(tuple_substraction(b, a), tuple_substraction(b, a))
			* dot_product(tuple_substraction(c, a), tuple_substraction(p, a))
			- dot_product(tuple_substraction(c, a), tuple_substraction(b, a))
			* dot_product(tuple_substraction(b, a), tuple_substraction(p, a)))
		* inv_denom;
	v = (dot_product(tuple_substraction(c, a), tuple_substraction(c, a))
			* dot_product(tuple_substraction(b, a), tuple_substraction(p, a))
			- dot_product(tuple_substraction(c, a), tuple_substraction(b, a))
			* dot_product(tuple_substraction(c, a), tuple_substraction(p, a)))
		* inv_denom;
	return (u >= 0.0 && v >= 0.0 && (u + v) <= 1.0);
}

static t_tuple	faces_normal(t_tuple corners[4], t_tuple apex, t_tuple world_p)
{
	int		i;
	t_tuple	corner_a;
	t_tuple	corner_b;
	t_tuple	normal;

	i = 0;
	while (i < 4)
	{
		corner_a = corners[i];
		corner_b = corners[(i + 1) % 4];
		normal = compute_cross_produt(tuple_substraction(apex, corner_a),
				tuple_substraction(corner_b, corner_a));
		normalize_tuple(&normal);
		if (pt_in_triangle(world_p, corner_a, corner_b, apex))
			return (normal);
		i++;
	}
	normal = set_tuple(0, 1, 0, 0);
	return (normal);
}

t_tuple	pyramid_get_normal(t_object *obj, t_tuple world_p)
{
	t_pyramid	*pyramid;
	t_tuple		normal;
	t_tuple		apex;
	t_tuple		corners[4];

	pyramid = (t_pyramid *)obj->shape;
	apex = set_tuple(pyramid->base_center.x, pyramid->base_center.y
			+ pyramid->height, pyramid->base_center.z, 1);
	set_corners(pyramid, corners);
	if (fabs(world_p.y - pyramid->base_center.y) < 1e-6)
	{
		normal = set_tuple(0, 1, 0, 0);
		return (normal);
	}
	normal = faces_normal(corners, apex, world_p);
	return (normal);
}
