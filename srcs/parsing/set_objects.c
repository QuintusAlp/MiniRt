/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:49:06 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/23 13:08:30 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	set_sphere(t_object *object, t_sphere *sphere)
{
	set_rgb(&object->material.color, sphere->color.r, sphere->color.g,
		sphere->color.b);
	object->get_normal = sphere_get_normal;
	object->get_intersections = intersect_sphere;
}

static void	set_cylinder(t_object *object, t_cylinder *cylinder)
{
	set_rgb(&object->material.color, cylinder->color.r, cylinder->color.g,
		cylinder->color.b);
	object->get_normal = cylinder_get_normal;
	object->get_intersections = intersect_cylinder;
}

static void	set_plane(t_object *object, t_plane *plane)
{
	object->material.color = plane->color;
	object->get_normal = plane_get_normal;
	object->get_intersections = intersect_plane;
}

static void	set_pyramid(t_object *object, t_pyramid *pyramid)
{
	set_rgb(&object->material.color, pyramid->color.r, pyramid->color.g,
		pyramid->color.b);
	object->get_normal = pyramid_get_normal;
	object->get_intersections = intersect_pyramid;
}

void	set_object(t_object *object, void *shape, char *type_buff)
{
	object->type = get_type(type_buff);
	object->shape = shape;
	if (object->type == SPHERE)
		set_sphere(object, (t_sphere *)shape);
	if (object->type == CYLINDER)
		set_cylinder(object, (t_cylinder *)shape);
	if (object->type == PLANE)
		set_plane(object, (t_plane *)shape);
	if (object->type == PYRAMID)
		set_pyramid(object, (t_pyramid *)shape);
	object->next = NULL;
}
