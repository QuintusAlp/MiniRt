/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:06:59 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:43:34 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_scene			*scene;
	t_window		window;

	if (argc != 2)
		error_exit("wrong arg number");
	scene = ft_parsing(argv[1]);
	if (!scene->camera || !scene->ambient_light || !scene->light)
		error_parsing("Essential scene elements are missing", scene);
	scene->primary.origin = scene->camera->ray.origin;
	window_init(&window, scene);
	render(&window);
	events_init(&window);
	mlx_loop(window.mlx_connection);
	free_scene(scene);
	return (0);
}
