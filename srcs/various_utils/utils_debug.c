/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:07:35 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 12:55:09 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_matrix(t_matrix m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < m.nbr_row)
	{
		j = 0;
		printf("|");
		while (j < m.nbr_col)
		{
			printf("%8.10f ", m.m[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
	printf("\n");
}

void	print_tuple(t_tuple tuple)
{
	printf("x = %f\ny = %f\nz = %f\nw = %d\n", tuple.x, tuple.y, tuple.z,
		tuple.w);
}

void	print_rgb(t_rgb color)
{
	printf("r = %f, g = %f, b = %f\n", color.r, color.g, color.b);
}

void	print_light(t_light light)
{
	printf("Origin:\n");
	print_tuple(light.origin);
	printf("Brightness: %f\n", light.brightness);
	printf("Color:");
	print_rgb(light.color);
}
