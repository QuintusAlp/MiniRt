/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:58 by qalpesse          #+#    #+#             */
/*   Updated: 2025/04/22 15:34:53 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	f_light(char *b, char **buf, t_ambient_light *ambient_light)
{
	free_split(buf);
	free(b);
	free(ambient_light);
}

static void	ft_intensity(t_ambient_light *ambient_light, char **buffer,
							char *b, t_scene *data)
{
	ambient_light->intensity = ft_atof(buffer[1]);
	if (!checkrange(ambient_light->intensity, 0.0, 1.0))
		return (f_light(b, buffer, ambient_light),
			error_parsing("Ambient lightnming\'s intensity value bad value",
				data));
}

void	ft_ambiant_light(char **buffer, t_scene *data, char *b)
{
	t_ambient_light	*ambient_light;
	char			**split;

	if (data->ambient_light != NULL)
		return (free(b), free_split(buffer),
			error_parsing("You can\'t set Ambiant light two time", data));
	if (check_args_number(3, buffer))
		return (free(b), free_split(buffer),
			error_parsing("Bad number of args for ambiant light", data));
	ambient_light = malloc(sizeof(t_ambient_light));
	if (!ambient_light)
		error_parsing("ERROR : Malloc failed", data);
	ft_intensity(ambient_light, buffer, b, data);
	split = ft_split(buffer[2], ',');
	if (check_args_number(3, split))
		return (f_light(b, buffer, ambient_light), free_split(split),
			error_parsing("Bad number of args for ambiant light COLOR", data));
	set_rgb(&ambient_light->color, ft_atof(split[0]), ft_atof(split[1]),
		ft_atof(split[2]));
	free_split(split);
	if (!checkrgb(&ambient_light->color))
		return (f_light(b, buffer, ambient_light),
			error_parsing("Ambient lightning color bad value", data));
	data->ambient_light = ambient_light;
}
