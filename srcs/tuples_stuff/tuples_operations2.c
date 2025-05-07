/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:41:08 by marlonco          #+#    #+#             */
/*   Updated: 2025/05/05 14:51:06 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	get_magnitude(t_tuple t)
{
	return (sqrt((t.x * t.x) + (t.y * t.y) + (t.z * t.z) + (t.w * t.w)));
}

void	normalize_tuple(t_tuple *v)
{
	double	magnitude;

	magnitude = get_magnitude(*v);
	if (floats_equal(magnitude, 0.0))
		error_exit("NORMALIZE TUPLE: Magnitude equals 0");
	v->x /= magnitude;
	v->y /= magnitude;
	v->z /= magnitude;
}

float	dot_product(t_tuple v1, t_tuple v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// ATTENTION: non-commutative !!!
t_tuple	compute_cross_produt(t_tuple v1, t_tuple v2)
{
	t_tuple	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	result.w = 0;
	return (result);
}

t_tuple	set_tuple(float x, float y, float z, float w)
{
	t_tuple	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;
	return (result);
}
