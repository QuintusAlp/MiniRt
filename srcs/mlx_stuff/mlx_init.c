/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:08:14 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/28 12:59:34 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*
	viewport = portion of the screen that is showed where the image will
	be displayed
	each pixel in the viewport = a ray in 3D space
*/
void	handle_init_errors(t_window *window, void *ptr, char *str)
{
	if (ptr == NULL)
	{
		mlx_destroy_window(window->mlx_connection, window->mlx_window);
		free(window->mlx_connection);
		error_exit(str);
	}
}

void	window_init(t_window *window, t_scene *scene)
{
	window->mlx_connection = mlx_init();
	if (window->mlx_connection == NULL)
		error_exit("MLX connection not found");
	window->name = "MiniRT";
	window->mlx_window = mlx_new_window(window->mlx_connection, WIDTH, HEIGHT,
			window->name);
	handle_init_errors(window, window->mlx_window,
		"Error while initializing MLX window");
	window->image.image_ptr = mlx_new_image(window->mlx_connection, WIDTH,
			HEIGHT);
	handle_init_errors(window, window->image.image_ptr,
		"Error while initializing MLX image");
	window->image.pixels_ptr = mlx_get_data_addr(window->image.image_ptr,
			&window->image.bpp, &window->image.line_length,
			&window->image.endian);
	window->scene = scene;
}
