/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:47 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/24 13:47:40 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	parse_plane_origin(t_plane *plane, char **buffer, t_scene *data)
{
	char	**split;

	split = ft_split(buffer[1], ',');
	if (check_args_number(3, split))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(plane);
		free_split(split);
		error_parsing("Bad number of args plane origin", data);
	}
	plane->origin = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 1);
	free_split(split);
}

static void	parse_plane_normal(t_plane *plane, char **buffer, t_scene *data)
{
	char	**split;

	split = ft_split(buffer[2], ',');
	if (check_args_number(3, split))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(plane);
		free_split(split);
		error_parsing("Bad number of args plane normal", data);
	}
	plane->normal = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 1);
	free_split(split);
	if (!check_vector(&plane->normal))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(plane);
		error_parsing("plane normal vector bad value", data);
	}
}

static void	plane_parse_color(t_plane *plane, char **buffer, t_scene *data)
{
	char	**split;

	split = ft_split(buffer[3], ',');
	if (check_args_number(3, split))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(plane);
		free_split(split);
		error_parsing("Bad number of args plane color", data);
	}
	set_rgb(&plane->color, ft_atof(split[0]), ft_atof(split[1]),
		ft_atof(split[2]));
	free_split(split);
	if (!checkrgb(&plane->color))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(plane);
		error_parsing("plane rgb bad value", data);
	}
}

void	ft_plane(char **buffer, t_scene *data, char *b)
{
	t_plane		*plane;
	t_object	*object;

	plane = malloc(sizeof(t_plane));
	object = malloc(sizeof(t_object));
	data->b = b;
	data->obj = object;
	if (!plane || !object || check_args_number(4, buffer))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(plane);
		error_parsing("Malloc failed", data);
	}
	parse_plane_origin(plane, buffer, data);
	parse_plane_normal(plane, buffer, data);
	normalize_tuple(&plane->normal);
	plane_parse_color(plane, buffer, data);
	set_object(object, plane, buffer[0]);
	ft_object_addback(&data->objects, object);
}
