/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:55:16 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 12:54:37 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// static t_tuple	reflect(t_tuple in_vector, t_tuple normal)
// {
// 	t_tuple	result;

// 	if (in_vector.w == 1 || normal.w == 1)
// 		error_exit("REFLECT: point submitted instead of vector");
// 	result = tuple_scalar_multiplication(normal, 2.0);
// 	result = tuple_scalar_multiplication(result, dot_product(in_vector,
// 				normal));
// 	result = tuple_substraction(in_vector, result);
// 	return (result);
// }

/*
	Let p1 be the intersection point of a ray with the surface
	and p2 be the light position
*/
// static bool	points_on_same_line(t_tuple p1, t_tuple p2,
// 		t_tuple camera_orientation)
// {
// 	t_tuple	vector_v1_v2;
// 	t_tuple	cross_product;

// 	if (p1.w == 0 || p2.w == 0 || camera_orientation.w == 1)
// 		error_exit("POINTS_ON_SAME_LINE: 
// 			vector provided instead of point or opposite");
// 	vector_v1_v2 = set_tuple((p2.x - p1.x), (p2.y - p1.y), (p2.z - p1.z), 0);
// 	cross_product = compute_cross_produt(vector_v1_v2, camera_orientation);
// 	if (cross_product.x == 0 && cross_product.y == 0 && cross_product.z == 0)
// 		return (1);
// 	return (0);
// }

static t_rgb	ft_diffuse(t_scene *scene, t_object *object)
{
	float	dot;
	t_tuple	light_v;
	t_rgb	diffuse;

	light_v = object->material.light_v;
	dot = fmaxf(0.0f, dot_product(light_v, object->material.normal));
	diffuse.r = object->material.color.r * scene->light->color.r
		* scene->light->brightness * dot / 255.0;
	diffuse.g = object->material.color.g * scene->light->color.g
		* scene->light->brightness * dot / 255.0;
	diffuse.b = object->material.color.b * scene->light->color.b
		* scene->light->brightness * dot / 255.0;
	return (diffuse);
}

static t_rgb	ft_specular(t_scene *scene, t_tuple position, t_object *object)
{
	t_rgb	specular;
	t_tuple	camera_v;
	t_tuple	reflect_v;
	float	dot;

	camera_v = tuple_substraction(scene->camera->ray.origin, position);
	normalize_tuple(&camera_v);
	reflect_v = tuple_substraction(tuple_scalar_multiplication(
				object->material.normal,
				2.0f * dot_product(object->material.normal,
					object->material.light_v)), object->material.light_v);
	normalize_tuple(&reflect_v);
	dot = fmaxf(0.0f, dot_product(reflect_v, camera_v));
	dot = powf(dot, 32.0f);
	specular.r = scene->light->color.r * dot * scene->light->brightness;
	specular.g = scene->light->color.g * dot * scene->light->brightness;
	specular.b = scene->light->color.b * dot * scene->light->brightness;
	return (specular);
}

double	lighting(t_scene *scene, t_object *object, t_tuple position)
{
	t_lighting_types	lights;
	t_ray				light_v_dup;

	object->material.normal = object->get_normal(object, position);
	object->material.light_v = tuple_substraction(scene->light->origin,
			position);
	normalize_tuple(&object->material.light_v);
	lights.ambient = color_multiply(object->material.color,
			scene->ambient_light->color);
	lights.ambient = color_scal_mult(lights.ambient,
			scene->ambient_light->intensity);
	light_v_dup.direction = object->material.light_v;
	light_v_dup.origin = tuple_addition(position,
			tuple_scalar_multiplication(object->material.normal, 0.001f));
	if (intersect_light(light_v_dup, scene))
		return (rgb_to_hex(lights.ambient));
	lights.diffuse = ft_diffuse(scene, object);
	lights.specular = ft_specular(scene, position, object);
	lights.color = color_addition(lights.ambient, lights.diffuse);
	lights.color = color_addition(lights.color, lights.specular);
	return (rgb_to_hex(lights.color));
}
