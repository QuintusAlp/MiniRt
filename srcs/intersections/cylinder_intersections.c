/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:52:44 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/22 16:16:22 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	check_sol(t_cylinder *cylinder, t_ray ray, double s)
{
	t_tuple	pt;
	t_tuple	base;
	t_tuple	base_to_pt;
	double	projection;

	pt = tuple_addition(ray.origin, tuple_scalar_multiplication(ray.direction,
				s));
	base = tuple_substraction(cylinder->center,
			tuple_scalar_multiplication(cylinder->axis, cylinder->height
				/ 2.0));
	base_to_pt = tuple_substraction(pt, base);
	projection = dot_product(base_to_pt, cylinder->axis);
	if (projection >= -1e-6 && projection <= cylinder->height + 1e-6)
		return (1);
	return (0);
}

static t_solutions	within_height(t_cylinder *cylinder, t_ray ray,
		t_solutions sol)
{
	t_solutions	res;
	int			is_valid_s1;
	int			is_valid_s2;

	is_valid_s1 = 0;
	is_valid_s2 = 0;
	set_sol(&res, 0, INFINITY, INFINITY);
	if (sol.s_count >= 1)
		is_valid_s1 = check_sol(cylinder, ray, sol.s1);
	if (sol.s_count == 2)
		is_valid_s2 = check_sol(cylinder, ray, sol.s2);
	if (is_valid_s1 && is_valid_s2)
		set_sol(&res, 2, sol.s1, sol.s2);
	else if (is_valid_s1)
		set_sol(&res, 1, sol.s1, sol.s1);
	else if (is_valid_s2)
		set_sol(&res, 1, sol.s2, sol.s2);
	return (res);
}

void	get_sols(t_solutions *sols, double hit)
{
	if (sols->s_count == 0)
		set_sol(sols, 1, hit, hit);
	else if (sols->s_count == 1 && hit != sols->s1)
		set_sol(sols, 2, fmin(sols->s1, hit), fmax(sols->s1, hit));
	else if (sols->s_count == 2 && hit != sols->s1 && hit != sols->s2)
	{
		if (hit < sols->s1)
			sols->s1 = hit;
		else if (hit > sols->s2)
			sols->s2 = hit;
	}
}

void	intersect_cap(t_ray ray, t_cylinder *cylinder, t_solutions *sols,
		t_tuple cap)
{
	double	denom;
	double	t;
	t_tuple	hit_pt;
	t_tuple	to_center;

	denom = dot_product(ray.direction, cylinder->axis);
	if (fabs(denom) < 1e-6)
		return ;
	t = dot_product(tuple_substraction(cap, ray.origin), cylinder->axis)
		/ denom;
	if (t < 0)
		return ;
	hit_pt = tuple_addition(ray.origin,
			tuple_scalar_multiplication(ray.direction, t));
	to_center = tuple_substraction(hit_pt, cap);
	if (get_magnitude(to_center) <= cylinder->diameter / 2)
		get_sols(sols, t);
}

t_solutions	intersect_cylinder(t_ray ray, t_object *obj)
{
	t_cylinder	*cylinder;
	t_tuple		oc;
	t_delta		delta;
	t_solutions	hits;

	cylinder = (t_cylinder *)obj->shape;
	normalize_tuple(&ray.direction);
	normalize_tuple(&cylinder->axis);
	oc = tuple_substraction(ray.origin, cylinder->center);
	delta.a = dot_product(ray.direction, ray.direction)
		- pow(dot_product(ray.direction, cylinder->axis), 2);
	delta.b = 2.0 * (dot_product(ray.direction, oc) - dot_product(ray.direction,
				cylinder->axis) * dot_product(oc, cylinder->axis));
	delta.c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->axis), 2)
		- (cylinder->diameter / 2) * (cylinder->diameter / 2);
	hits = within_height(cylinder, ray, compute_delta(delta));
	intersect_cap(ray, cylinder, &hits, tuple_substraction(cylinder->center,
			tuple_scalar_multiplication(cylinder->axis, cylinder->height
				/ 2.0)));
	intersect_cap(ray, cylinder, &hits, tuple_addition(cylinder->center,
			tuple_scalar_multiplication(cylinder->axis, cylinder->height
				/ 2.0)));
	return (hits);
}

// int main()
// {
//     t_cylinder  cylinder;
//     t_object    obj;

//     t_tuple center;
//     set_tuple(&center, 1.2, -2.0, 1.0, 1);
//     t_tuple axis;
//     set_tuple(&axis, 0.5, 0.5, 0, 0);

//     cylinder.center = center;
//     cylinder.axis = axis;
//     cylinder.diameter = 0.5;
//     cylinder.height = 8.0;

//     obj.shape = &cylinder;

//     ////
//     t_ray   ray2;
//     t_tuple origin2;
//     set_tuple(&origin2, 1.0, -5, -12.0, 1);
//     t_tuple direction2;
//     set_tuple(&direction2, 0, 0.2, 1.0, 0);
//     ray2.origin = origin2;
//     ray2.direction = direction2;

//     t_solutions sol2;
//     set_sol(&sol2, 0, INFINITY, INFINITY);
//     sol2 = intersect_cylinder(ray2, &obj);
//     printf("Intesections found for ray 2: %d\n", sol2.s_count);
//     if (sol2.s_count > 0)
//         printf("s1 = %f\n", sol2.s1);
//     if (sol2.s_count == 2)
//         printf("s2 = %f\n", sol2.s2);
// }