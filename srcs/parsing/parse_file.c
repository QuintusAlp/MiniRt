/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:33:13 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/22 22:28:13 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	get_object(t_scene *scene, char *buffer, char **split)
{
	if (ft_strcmp(split[0], "A") == 0)
		ft_ambiant_light(split, scene, buffer);
	else if (ft_strcmp(split[0], "C") == 0)
		ft_camera(split, scene, buffer);
	else if (ft_strcmp(split[0], "L") == 0)
		ft_light(split, scene, buffer);
	else if (ft_strcmp(split[0], "pl") == 0)
		ft_plane(split, scene, buffer);
	else if (ft_strcmp(split[0], "sp") == 0)
		ft_sphere(split, scene, buffer);
	else if (ft_strcmp(split[0], "cy") == 0)
		ft_cylinder(split, scene, buffer);
	else if (ft_strcmp(split[0], "py") == 0)
		ft_pyramid(split, scene, buffer);
	else
	{
		free_split(split);
		free(buffer);
		error_parsing("Wrong identifier", scene);
	}
}

void	init_scene(t_scene *scene)
{
	scene->objects = NULL;
	scene->ambient_light = NULL;
	scene->light = NULL;
	scene->camera = NULL;
}

int	ft_onpenfile(char *file)
{
	int	fd;

	if (ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3) != 0)
		error_exit("Wrong file extension");
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		error_exit("Could not open file");
	return (fd);
}

t_scene	*ft_parsing(char *file)
{
	int		fd;
	char	*buffer;
	char	**split;
	t_scene	*scene;

	fd = ft_onpenfile(file);
	scene = safe_malloc(sizeof(t_scene));
	init_scene(scene);
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (buffer[0] == '\n')
		{
			free(buffer);
			buffer = get_next_line(fd);
			continue ;
		}
		split = ft_split(buffer, ' ');
		get_object(scene, buffer, split);
		free_split(split);
		free(buffer);
		buffer = get_next_line(fd);
	}
	return (scene);
}
