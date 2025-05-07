/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:06:05 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:34:42 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_tuple	tuple_addition(t_tuple t1, t_tuple t2)
{
	t_tuple	result;

	if (t1.w == 1 && t2.w == 1)
		error_exit("You can't addition two points");
	result.x = t1.x + t2.x;
	result.y = t1.y + t2.y;
	result.z = t1.z + t2.z;
	if (t1.w == 1 || t2.w == 1)
		result.w = 1;
	else
		result.w = 0;
	return (result);
}

t_tuple	tuple_substraction(t_tuple t1, t_tuple t2)
{
	t_tuple	result;

	if (t1.w == 0 && t2.w == 1)
		error_exit("You cant't substract a point from a vector");
	result.x = t1.x - t2.x;
	result.y = t1.y - t2.y;
	result.z = t1.z - t2.z;
	result.w = t1.w - t2.w;
	return (result);
}

t_tuple	tuple_scalar_multiplication(t_tuple t, float scalar)
{
	t_tuple	result;

	result.x = t.x * scalar;
	result.y = t.y * scalar;
	result.z = t.z * scalar;
	result.w = t.w * scalar;
	return (result);
}

float	tuple_distance(t_tuple p1, t_tuple p2)
{
	t_tuple	diff;

	if (p1.w != 1 || p2.w != 1)
		error_exit("tuple distance need two points not vectors");
	diff = tuple_substraction(p1, p2);
	return (sqrtf(dot_product(diff, diff)));
}
