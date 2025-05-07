/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:31 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/24 13:47:03 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	parse_camera_origin(t_camera *camera, char **buffer, t_scene *data)
{
	char	**split;

	split = ft_split(buffer[1], ',');
	if (check_args_number(3, split))
	{
		free(camera);
		free(data->b);
		free_split(buffer);
		free_split(split);
		error_parsing("Bad number of args for camera RAY ORIGIN", data);
	}
	camera->ray.origin = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 1);
	free_split(split);
}

static void	parse_camera_direction(t_camera *camera, char **buffer,
		t_scene *data)
{
	char	**split;

	split = ft_split(buffer[2], ',');
	if (check_args_number(3, split))
	{
		free(camera);
		free(data->b);
		free_split(buffer);
		free_split(split);
		error_parsing("Bad number of args for camera RAY DIR", data);
	}
	camera->ray.direction = set_tuple(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]), 0);
	free_split(split);
	if (!check_vector(&camera->ray.direction))
	{
		free(camera);
		free(data->b);
		free_split(buffer);
		error_parsing("Camera\'s ray dirrection bad value'", data);
	}
}

void	ft_camera(char **buffer, t_scene *data, char *b)
{
	t_camera	*camera;

	if (data->camera != NULL)
		return (free(b), free_split(buffer),
			error_parsing("Can't set camera twice", data));
	if (check_args_number(4, buffer))
		return (free(b), free_split(buffer),
			error_parsing("Bad number of args for camera", data));
	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (free(b), free_split(buffer), error_parsing("malloc failed",
				data));
	data->b = b;
	parse_camera_origin(camera, buffer, data);
	parse_camera_direction(camera, buffer, data);
	normalize_tuple(&camera->ray.direction);
	camera->fov = ft_atof(buffer[3]);
	if (!checkrange(camera->fov, 0, 180))
		return (free(b), free(camera), free_split(buffer),
			error_parsing("Camera\'s fov bad value'", data));
	if (camera->fov == 180)
		camera->fov = 179;
	data->camera = camera;
}
