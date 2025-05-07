/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:40:20 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:09:01 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ray	get_transformed_ray(t_ray initial_ray, t_matrix transformed_matrix)
{
	t_ray		result_ray;
	t_matrix	m_direction;
	t_matrix	m_origin;
	t_matrix	temp;

	temp = get_matrix_from_tuple(initial_ray.origin);
	m_origin = multiply_matrixes(transformed_matrix, temp);
	free_matrix(temp.m, 4);
	temp = get_matrix_from_tuple(initial_ray.direction);
	m_direction = multiply_matrixes(transformed_matrix, temp);
	free_matrix(temp.m, 4);
	result_ray.direction = get_tuple_from_matrix(m_direction);
	result_ray.origin = get_tuple_from_matrix(m_origin);
	free_matrix(m_origin.m, m_origin.nbr_row);
	free_matrix(m_direction.m, m_direction.nbr_row);
	free_matrix(transformed_matrix.m, 4);
	return (result_ray);
}

t_solutions	sphere_ray_intersections(t_ray transformed_ray, t_sphere sphere)
{
	t_delta		data;
	t_solutions	solutions;
	t_tuple		sphere_to_ray;

	if (transformed_ray.direction.w == 1 || transformed_ray.origin.w == 0
		|| sphere.origin.w == 0)
		error_exit("Wrong w for a direction / origin");
	sphere_to_ray = tuple_substraction(transformed_ray.origin, sphere.origin);
	data.a = dot_product(transformed_ray.direction, transformed_ray.direction);
	data.b = 2 * dot_product(transformed_ray.direction, sphere_to_ray);
	data.c = dot_product(sphere_to_ray, sphere_to_ray) - (sphere.radius
			* sphere.radius);
	data.delta = (data.b * data.b) - (4 * data.a * data.c);
	if (data.delta < 0)
	{
		solutions.s_count = 0;
		return (solutions);
	}
	solutions.s1 = (-data.b + sqrt(data.delta)) / (2 * data.a);
	solutions.s2 = (-data.b - sqrt(data.delta)) / (2 * data.a);
	solutions.s_count = 2;
	return (solutions);
}

// returns the smallest intersection
float	find_hit(t_solutions intersections)
{
	if (intersections.s_count == 0)
		return (INFINITY);
	if (intersections.s1 < 0 && intersections.s2 >= 0)
		return (intersections.s2);
	if (intersections.s2 < 0 && intersections.s1 >= 0)
		return (intersections.s1);
	if (intersections.s2 < 0 && intersections.s1 < 0)
		return (INFINITY);
	return (fmin(intersections.s1, intersections.s2));
}
