/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:01:19 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:37:58 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	floats_equal(double a, double b)
{
	if (fabs(a - b) < FLT_EPSILON)
		return (true);
	else
		return (false);
}

void	error_exit(const char *error)
{
	printf(RED "ERROR: " RESET);
	printf(RED "%s\n" RESET, error);
	exit(EXIT_FAILURE);
}

t_matrix	get_matrix_from_tuple(t_tuple tuple)
{
	t_matrix	res;

	init_matrix(&res, 4, 1);
	res.m[0][0] = tuple.x;
	res.m[1][0] = tuple.y;
	res.m[2][0] = tuple.z;
	res.m[3][0] = tuple.w;
	return (res);
}

// if w != 1 || 0 --> will be round up/down
t_tuple	get_tuple_from_matrix(t_matrix matrix)
{
	t_tuple	result;

	result.x = matrix.m[0][0];
	result.y = matrix.m[1][0];
	result.z = matrix.m[2][0];
	result.w = matrix.m[3][0];
	return (result);
}

t_tuple	multiply_matrix_vector(float **matrix, t_tuple vector)
{
	t_tuple	result;

	result.x = matrix[0][0] * vector.x + matrix[0][1] * vector.y + matrix[0][2]
		* vector.z + matrix[0][3];
	result.y = matrix[1][0] * vector.x + matrix[1][1] * vector.y + matrix[1][2]
		* vector.z + matrix[1][3];
	result.z = matrix[2][0] * vector.x + matrix[2][1] * vector.y + matrix[2][2]
		* vector.z + matrix[2][3];
	result.w = vector.w;
	return (result);
}
