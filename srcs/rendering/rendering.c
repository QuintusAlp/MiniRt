/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:20:02 by marlonco          #+#    #+#             */
/*   Updated: 2025/04/24 13:42:11 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	render(t_window *window)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	image_view_port(window);
	compute_plan_vectors(window);
	compute_top_left_corner(window);
	ft_printf("compute...\n");
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			set_primary_v(x, y, window);
			handle_pixel(x, y, window);
			x++;
		}
		y++;
		if (y % (HEIGHT / 50) == 0)
			ft_printf("#");
	}
	mlx_put_image_to_window(window->mlx_connection, window->mlx_window,
		window->image.image_ptr, 0, 0);
}
