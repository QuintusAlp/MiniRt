/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:41 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/24 12:49:23 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	parse_light_origin(t_light *light, char **buffer, t_scene *data)
{
	char	**split;

	split = ft_split(buffer[1], ',');
	if (check_args_number(3, split))
	{
		free(light);
		free(data->b);
		free_split(buffer);
		free_split(split);
		error_parsing("Bad number of args for light origin", data);
	}
	light->origin = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 1);
	free_split(split);
}

static void	parse_light_color(t_light *light, char **buffer, t_scene *data)
{
	char	**split;

	split = ft_split(buffer[3], ',');
	if (check_args_number(3, split))
	{
		free(light);
		free(data->b);
		free_split(buffer);
		free_split(split);
		error_parsing("Bad number of args for light color", data);
	}
	set_rgb(&light->color, ft_atof(split[0]), ft_atof(split[1]),
		ft_atof(split[2]));
	free_split(split);
	if (!checkrgb(&light->color))
	{
		free(light);
		free(data->b);
		free_split(buffer);
		error_parsing("light\'s rgb bad value", data);
	}
}

void	ft_light(char **buffer, t_scene *data, char *b)
{
	t_light	*light;

	if (data->light != NULL)
		return (free(b), free_split(buffer),
			error_parsing("Can't set light twice", data));
	if (check_args_number(4, buffer))
		return (free(b), free_split(buffer),
			error_parsing("bad number of light args", data));
	light = malloc(sizeof(t_light));
	if (!light)
		return (free(b), free_split(buffer), error_parsing("Malloc failed",
				data));
	data->b = b;
	parse_light_origin(light, buffer, data);
	light->brightness = ft_atof(buffer[2]);
	if (!checkrange(light->brightness, 0, 1))
	{
		free(b);
		free(light);
		free_split(buffer);
		error_parsing("light\'s brightness bad value", data);
	}
	parse_light_color(light, buffer, data);
	data->light = light;
}
