/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:01:40 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/28 13:01:41 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	close_handler(t_window *window)
{
	free_scene(window->scene);
	mlx_destroy_image(window->mlx_connection, window->image.image_ptr);
	mlx_destroy_window(window->mlx_connection, window->mlx_window);
	mlx_destroy_display(window->mlx_connection);
	free(window->mlx_connection);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_window *window)
{
	if (keysym == ESC)
		close_handler(window);
	return (0);
}

void	events_init(t_window *window)
{
	mlx_hook(window->mlx_window, KEY_PRESS, 1L << 0, &key_handler, window);
	mlx_hook(window->mlx_window, CLOSE_WINDOW, 0, close_handler, window);
}
