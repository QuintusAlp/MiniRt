/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_intersections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 03:46:44 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/24 12:35:16 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_sol(t_solutions *sol, int count, double s1, double s2)
{
	sol->s_count = count;
	sol->s1 = s1;
	sol->s2 = s2;
}

t_solutions	compute_delta(t_delta delta)
{
	t_solutions	res;

	delta.delta = (delta.b * delta.b) - 4 * delta.a * delta.c;
	if (delta.delta < 0 || floats_equal(delta.a, 0.0))
	{
		set_sol(&res, 0, INFINITY, INFINITY);
		return (res);
	}
	res.s1 = (-delta.b - sqrt(delta.delta)) / (2 * delta.a);
	res.s2 = (-delta.b + sqrt(delta.delta)) / (2 * delta.a);
	if (res.s1 == res.s2)
		res.s_count = 1;
	else
		res.s_count = 2;
	return (res);
}

t_solutions	intersect_sphere(t_ray ray, t_object *obj)
{
	t_sphere	*sphere;
	t_delta		delta;
	t_tuple		oc;

	sphere = (t_sphere *)(obj->shape);
	oc = tuple_substraction(ray.origin, sphere->origin);
	delta.a = dot_product(ray.direction, ray.direction);
	delta.b = 2.0 * dot_product(ray.direction, oc);
	delta.c = dot_product(oc, oc) - (sphere->radius * sphere->radius);
	return (compute_delta(delta));
}

t_solutions	intersect_plane(t_ray ray, t_object *obj)
{
	t_solutions	res;
	t_tuple		origin_to_plane;
	t_plane		*plane;
	float		denom;
	float		t;

	plane = (t_plane *)obj->shape;
	set_sol(&res, 0, INFINITY, INFINITY);
	denom = dot_product(ray.direction, plane->normal);
	if (fabs(denom) < 1e-6)
		return (res);
	origin_to_plane = tuple_substraction(plane->origin, ray.origin);
	t = dot_product(origin_to_plane, plane->normal) / denom;
	if (t >= 0)
		set_sol(&res, 1, t, t);
	return (res);
}

t_tuple	ray_at(t_ray ray, double t)
{
	return (tuple_addition(ray.origin,
			tuple_scalar_multiplication(ray.direction, t)));
}
