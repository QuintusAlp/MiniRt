/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:43:35 by qalpesse          #+#    #+#             */
/*   Updated: 2025/05/05 14:52:36 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	checkrange(float nbr, float min, float max)
{
	if (nbr > max || nbr < min)
		return (0);
	else
		return (1);
}

int	checkrgb(t_rgb *color)
{
	if (!checkrange(color->r, 0, 255) || !checkrange(color->g, 0, 255)
		|| !checkrange(color->b, 0, 255))
	{
		return (0);
	}
	else
		return (1);
}

int	check_vector(t_tuple *vector)
{
	if (!checkrange(vector->x, -1, 1) || !checkrange(vector->y, -1, 1)
		|| !checkrange(vector->z, -1, 1) || (vector->x == 0 && vector->y == 0
			&& vector->z == 0))
	{
		return (0);
	}
	else
		return (1);
}

t_object_type	get_type(char *buffer)
{
	if (!ft_strcmp(buffer, "pl"))
		return (PLANE);
	if (!ft_strcmp(buffer, "sp"))
		return (SPHERE);
	if (!ft_strcmp(buffer, "cy"))
		return (CYLINDER);
	if (!ft_strcmp(buffer, "py"))
		return (PYRAMID);
	else
		return (NONE);
}

void	error_parsing(char *str, t_scene *scene)
{
	free_scene(scene);
	error_exit(str);
}
