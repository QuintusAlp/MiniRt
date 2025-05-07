/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:28:34 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:40:45 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	free_py(char **buffer, t_scene *data, t_pyramid *pyramid)
{
	free_split(buffer);
	free(data->b);
	free(data->obj);
	free(pyramid);
}

static void	parse_pyramid_center(t_pyramid *pyramid, char **buffer,
		t_scene *data)
{
	char	**split;

	split = ft_split(buffer[1], ',');
	if (check_args_number(3, split))
	{
		free_py(buffer, data, pyramid);
		free_split(split);
		error_parsing("Bad number of args pyramid center", data);
	}
	pyramid->base_center = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 1);
	free_split(split);
}

static void	parse_pyramid_color(t_pyramid *pyramid, char **buffer,
		t_scene *data)
{
	char	**split;

	split = ft_split(buffer[4], ',');
	if (check_args_number(3, split))
	{
		free_py(buffer, data, pyramid);
		free_split(split);
		error_parsing("Bad number of args pyramid color", data);
	}
	set_rgb(&pyramid->color, ft_atof(split[0]), ft_atof(split[1]),
		ft_atof(split[2]));
	free_split(split);
	if (!checkrgb(&pyramid->color))
	{
		free_py(buffer, data, pyramid);
		error_parsing("pyramid color bad value", data);
	}
}

void	ft_pyramid(char **buffer, t_scene *data, char *b)
{
	t_pyramid	*pyramid;
	t_object	*object;

	pyramid = safe_malloc(sizeof(t_pyramid));
	object = safe_malloc(sizeof(t_object));
	data->b = b;
	data->obj = object;
	if (check_args_number(5, buffer))
	{
		free_py(buffer, data, pyramid);
		error_parsing("Bad number of args pyramid", data);
	}
	parse_pyramid_center(pyramid, buffer, data);
	pyramid->base_size = ft_atof(buffer[2]);
	pyramid->height = ft_atof(buffer[3]);
	if (pyramid->height <= 0 || pyramid->base_size <= 0)
	{
		free_py(buffer, data, pyramid);
		error_parsing("Pyramid height/bae_size <= 0", data);
	}
	parse_pyramid_color(pyramid, buffer, data);
	set_object(object, pyramid, buffer[0]);
	ft_object_addback(&data->objects, object);
}
