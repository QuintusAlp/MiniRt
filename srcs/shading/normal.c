/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:22:34 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/23 00:32:57 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_tuple	sphere_get_normal(t_object *obj, t_tuple hit)
{
	t_sphere	*sphere;
	t_tuple		normal;

	sphere = (t_sphere *)obj->shape;
	normal = tuple_substraction(hit, sphere->origin);
	normalize_tuple(&normal);
	return (normal);
}

t_tuple	plane_get_normal(t_object *obj, t_tuple world_p)
{
	t_plane	*plane;
	t_tuple	normal;

	(void)world_p;
	plane = (t_plane *)obj->shape;
	normal = plane->normal;
	normal.w = 0;
	normalize_tuple(&normal);
	return (normal);
}

static t_tuple	cylinder_cap_normal(t_tuple axis, int top)
{
	t_tuple	normal;

	if (top == 1)
		normal = tuple_scalar_multiplication(axis, -1);
	else
		normal = axis;
	normalize_tuple(&normal);
	return (normal);
}

t_tuple	cylinder_get_normal(t_object *obj, t_tuple world_p)
{
	t_cylinder	*cylinder;
	t_tuple		normal;
	t_tuple		base_to_pt;
	t_tuple		axis_projection;
	double		projection_length;

	cylinder = (t_cylinder *)obj->shape;
	base_to_pt = tuple_substraction(world_p,
			tuple_substraction(cylinder->center,
				tuple_scalar_multiplication(cylinder->axis, cylinder->height
					/ 2.0)));
	projection_length = dot_product(base_to_pt, cylinder->axis);
	if (projection_length <= 1e-6)
		return (cylinder_cap_normal(cylinder->axis, 0));
	if (projection_length >= cylinder->height - 1e-6)
		return (cylinder_cap_normal(cylinder->axis, 1));
	axis_projection = tuple_scalar_multiplication(cylinder->axis,
			projection_length);
	normal = tuple_substraction(base_to_pt, axis_projection);
	normalize_tuple(&normal);
	return (normal);
}

// int main()
// {
//     t_cylinder  cylinder;
//     t_object    obj;

//     t_tuple center;
//     set_tuple(&center, 0, 0, 0, 1);
//     t_tuple axis;
//     set_tuple(&axis, 0, 1, 0, 0);
//     normalize_tuple(&axis);

//     cylinder.center = center;
//     cylinder.axis = axis;
//     cylinder.diameter = 2.0;
//     cylinder.height = 2.0;

//     obj.shape = &cylinder;

//     t_tuple p1;
//     set_tuple(&p1, 1, 1, 0, 1);
//     printf("Normal p1 (side) =\n");
//     print_tuple(cylinder_get_normal(&obj, p1));

//     t_tuple p2;
//     set_tuple(&p2, 0.5, 0, 0, 1);
//     printf("Normal p2 (bottom cap) =\n");
//     print_tuple(cylinder_get_normal(&obj, p2));

//     t_tuple p3;
//     set_tuple(&p3, 0.5, 2, 0, 1);
//     printf("Normal p3 (top cap) =\n");
//     print_tuple(cylinder_get_normal(&obj, p2));
// }
