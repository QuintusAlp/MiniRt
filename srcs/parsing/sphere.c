/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:51 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/24 12:49:53 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	parse_sphere_origin(t_sphere *sphere, char **buffer, t_scene *data)
{
	char	**split;

	split = ft_split(buffer[1], ',');
	if (check_args_number(3, split))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(sphere);
		free_split(split);
		error_parsing("Bad number of args sphere origin", data);
	}
	sphere->origin = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 1);
	free_split(split);
}

static void	parse_sphere_color(t_sphere *sphere, char **buffer, t_scene *data)
{
	char	**split;

	split = ft_split(buffer[3], ',');
	if (check_args_number(3, split))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(sphere);
		free_split(split);
		error_parsing("Bad number of args sphere color", data);
	}
	set_rgb(&sphere->color, ft_atof(split[0]), ft_atof(split[1]),
		ft_atof(split[2]));
	free_split(split);
	if (!checkrgb(&sphere->color))
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(sphere);
		error_parsing("Sphere\'s rgb bad value", data);
	}
}

static void	ft_radius(char **buffer, t_scene *data, t_sphere *sphere)
{
	sphere->radius = ft_atof(buffer[2]) / 2;
	if (sphere->radius <= 0)
	{
		free_split(buffer);
		free(data->b);
		free(data->obj);
		free(sphere);
		error_parsing("diameter of the shere can't be negative", data);
	}
}

void	ft_sphere(char **buffer, t_scene *data, char *b)
{
	t_sphere	*sphere;
	t_object	*object;

	if (check_args_number(4, buffer))
		error_parsing("Bad number of args sphere", data);
	sphere = malloc(sizeof(t_sphere));
	object = malloc(sizeof(t_object));
	data->b = b;
	data->obj = object;
	if (!sphere || !object)
		error_parsing("Malloc failed", data);
	parse_sphere_origin(sphere, buffer, data);
	ft_radius(buffer, data, sphere);
	parse_sphere_color(sphere, buffer, data);
	set_object(object, sphere, buffer[0]);
	ft_object_addback(&data->objects, object);
}
