/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:47:24 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/28 13:02:00 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_matrix(float **m, int nbr_row)
{
	int	i;

	i = 0;
	while (i < nbr_row)
	{
		free(m[i]);
		i++;
	}
	free(m);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_object(t_object *object)
{
	if (object->next)
		free_object(object->next);
	free(object->shape);
	free(object);
	return ;
}

void	free_scene(t_scene *scene)
{
	if (scene->ambient_light)
		free(scene->ambient_light);
	if (scene->light)
		free(scene->light);
	if (scene->camera)
		free(scene->camera);
	if (scene->objects)
		free_object(scene->objects);
	free(scene);
}
