/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid_intersections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:48:30 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 12:43:42 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_solutions	intersect_base(t_pyramid *pyramid, t_ray ray)
{
	t_solutions	res;
	t_solutions	base_sols;
	t_plane		base;
	t_tuple		hit_pt;
	t_object	plane;

	set_sol(&res, 0, INFINITY, INFINITY);
	base.origin = pyramid->base_center;
	base.normal = set_tuple(0, 1, 0, 0);
	base.color = pyramid->color;
	set_object(&plane, &base, "pl");
	base_sols = plane.get_intersections(ray, &plane);
	if (base_sols.s_count != 0)
	{
		hit_pt = ray_at(ray, base_sols.s1);
		if (hit_pt.x >= pyramid->base_center.x - pyramid->base_size / 2.0
			&& hit_pt.x <= pyramid->base_center.x + pyramid->base_size / 2.0
			&& hit_pt.z >= pyramid->base_center.z - pyramid->base_size / 2.0
			&& hit_pt.z <= pyramid->base_center.z + pyramid->base_size / 2.0)
		{
			if (hit_pt.y > pyramid->base_center.y)
				res = base_sols;
		}
	}
	return (res);
}

static t_solutions	intersect_triangle(t_ray ray, t_tuple a, t_tuple b,
		t_tuple c)
{
	t_solutions	res;
	t_tuple		h;
	t_tuple		q;
	float		a_val;
	float		f;

	set_sol(&res, 0, INFINITY, INFINITY);
	h = compute_cross_produt(ray.direction, tuple_substraction(c, a));
	a_val = dot_product(tuple_substraction(b, a), h);
	if (fabs(a_val) < 1e-6)
		return (res);
	f = 1.0 / a_val;
	q = compute_cross_produt(tuple_substraction(ray.origin, a),
			tuple_substraction(b, a));
	if (f * dot_product(tuple_substraction(ray.origin, a), h) < 0.0 || f
		* dot_product(tuple_substraction(ray.origin, a), h) > 1.0)
		return (res);
	if (f * dot_product(ray.direction, q) < 0.0 || (f
			* dot_product(tuple_substraction(ray.origin, a), h) + f
			* dot_product(ray.direction, q)) > 1.0)
		return (res);
	if (f * dot_product(tuple_substraction(c, a), q) > 1e-6)
		set_sol(&res, 1, f * dot_product(tuple_substraction(c, a), q), f
			* dot_product(tuple_substraction(c, a), q));
	return (res);
}

static t_solutions	intersect_faces(t_pyramid *pyramid, t_ray ray, t_tuple apex,
		t_solutions *sols)
{
	int			i;
	t_tuple		corners[4];
	t_tuple		corner_a;
	t_tuple		corner_b;
	t_solutions	res;

	i = 0;
	set_sol(&res, 0, INFINITY, INFINITY);
	set_corners(pyramid, corners);
	while (i < 4)
	{
		corner_a = corners[i];
		corner_b = corners[(i + 1) % 4];
		res = intersect_triangle(ray, corner_a, corner_b, apex);
		if (res.s_count != 0 && res.s1 < sols->s1)
			*sols = res;
		i++;
	}
	return (*sols);
}

t_solutions	intersect_pyramid(t_ray ray, t_object *obj)
{
	t_solutions	res;
	t_pyramid	*pyramid;
	t_tuple		apex;
	t_tuple		hit_pt;

	pyramid = (t_pyramid *)obj->shape;
	normalize_tuple(&ray.direction);
	set_sol(&res, 0, INFINITY, INFINITY);
	apex = set_tuple(pyramid->base_center.x, pyramid->base_center.y
			+ pyramid->height, pyramid->base_center.z, 1);
	res = intersect_base(pyramid, ray);
	if (res.s_count != 0)
	{
		hit_pt = ray_at(ray, res.s1);
		if (hit_pt.y == pyramid->base_center.y)
			set_sol(&res, 0, INFINITY, INFINITY);
	}
	intersect_faces(pyramid, ray, apex, &res);
	return (res);
}
