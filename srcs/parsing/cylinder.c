/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:37 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/24 13:47:23 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	free_cy(char **buffer, t_scene *data, t_cylinder *cy)
{
	free_split(buffer);
	if (data->b)
		free(data->b);
	if (data->obj)
		free(data->obj);
	free(cy);
}

static void	parse_cylinder_center(t_cylinder *cylinder, char **buffer,
		t_scene *data)
{
	char	**split;

	split = ft_split(buffer[1], ',');
	if (check_args_number(3, split))
	{
		free_cy(buffer, data, cylinder);
		free_split(split);
		error_parsing("Bad number of args cylinder center", data);
	}
	cylinder->center = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 1);
	free_split(split);
}

static void	parse_cylinder_axis(t_cylinder *cylinder, char **buffer,
		t_scene *data)
{
	char	**split;

	split = ft_split(buffer[2], ',');
	if (check_args_number(3, split))
	{
		free_cy(buffer, data, cylinder);
		free_split(split);
		error_parsing("Bad number of args cylinder axis", data);
	}
	cylinder->axis = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 0);
	free_split(split);
	if (!check_vector(&cylinder->axis))
	{
		free_cy(buffer, data, cylinder);
		error_parsing("cylinder axis bad value", data);
	}
}

static void	parse_cylinder_color(t_cylinder *cylinder, char **buffer,
		t_scene *data)
{
	char	**split;

	split = ft_split(buffer[5], ',');
	if (check_args_number(3, split))
	{
		free_cy(buffer, data, cylinder);
		free_split(split);
		error_parsing("Bad number of args cylinder color", data);
	}
	set_rgb(&cylinder->color, ft_atof(split[0]), ft_atof(split[1]),
		ft_atof(split[2]));
	free_split(split);
	if (!checkrgb(&cylinder->color))
	{
		free_cy(buffer, data, cylinder);
		error_parsing("cylinder color bad value", data);
	}
}

void	ft_cylinder(char **buffer, t_scene *data, char *b)
{
	t_cylinder	*cylinder;
	t_object	*object;

	cylinder = malloc(sizeof(t_cylinder));
	object = malloc(sizeof(t_object));
	data->b = b;
	data->obj = object;
	if (!cylinder || !object || check_args_number(6, buffer))
		return (free_cy(buffer, data, cylinder), error_parsing("Malloc failed",
				data));
	parse_cylinder_center(cylinder, buffer, data);
	parse_cylinder_axis(cylinder, buffer, data);
	normalize_tuple(&cylinder->axis);
	cylinder->diameter = ft_atof(buffer[3]);
	cylinder->height = ft_atof(buffer[4]);
	if (cylinder->diameter <= 0 || cylinder->height <= 0)
		return (free_cy(buffer, data, cylinder),
			error_parsing("diameter or height cylinder bad value", data));
	parse_cylinder_color(cylinder, buffer, data);
	set_object(object, cylinder, buffer[0]);
	ft_object_addback(&data->objects, object);
}
