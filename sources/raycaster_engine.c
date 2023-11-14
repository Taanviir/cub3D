/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:39:46 by tanas             #+#    #+#             */
/*   Updated: 2023/11/14 13:59:09 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_color(int *colors, int transperancy, int endian)
{
	if (endian)
		return ((colors[B] << 16) | (colors[G] << 8) | (colors[R])
			| (transperancy << 24));
	return ((transperancy << 24) | (colors[R] << 16) | (colors[G] << 8)
		| (colors[B]));
	
}

void	draw_ceiling_and_floor(t_img *img_data, int *c_color, int *f_color)
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
				my_pixel_put(img_data, x, y, get_color(c_color, 0, img_data->endian));
			else
				my_pixel_put(img_data, x, y, get_color(f_color, 0, img_data->endian));
		}
	}
}

void	start_raycaster(t_mlx *mlx_core)
{
	draw_ceiling_and_floor(&mlx_core->img_data, mlx_core->map->c_color, mlx_core->map->f_color);
	// draw_minimap(mlx_core);

	// get rays for horizontal and vertical intersections (DDA)
	draw_rays_3D(mlx_core->map->grid, &mlx_core->player, &mlx_core->img_data);

	mlx_put_image_to_window(mlx_core->mlx_ptr, mlx_core->window,
		mlx_core->img_data.img_ptr, 0, 0);
}
