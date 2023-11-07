/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:39:46 by tanas             #+#    #+#             */
/*   Updated: 2023/11/07 21:02:14 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_color(int *colors)
{
	return ((colors[R] << 16) | (colors[G] << 8) | (colors[B]));
}

void	draw_ceiling_and_floor(t_img *img_data, t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_pixel_put(img_data, x, y, get_color(map->c_color));
			else
				my_pixel_put(img_data, x, y, get_color(map->f_color));
		}
	}
}

void	start_raycaster(t_mlx *mlx_core)
{
	draw_minimap(mlx_core);

	// draw_ceiling_and_floor(&mlx_core->img_data, mlx_core->map);
	// get rays for horizontal and vertical intersections (DDA)

	mlx_put_image_to_window(mlx_core->mlx_ptr, mlx_core->window,
		mlx_core->img_data.img_ptr, 0, 0);
}
