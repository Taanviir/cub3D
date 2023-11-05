/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:39:46 by tanas             #+#    #+#             */
/*   Updated: 2023/11/05 12:40:31 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define CELL_SIZE 64

void	draw_cell(int x, int y, char cell_value, t_mlx *mlx_core)
{
	int	color;
	int	x_pos;
	int	y_pos;
	int	i;
	int	j;

	if (!cell_value || cell_value == '\n')
		return ;
	x_pos = x * CELL_SIZE + 400;
	y_pos = y * CELL_SIZE + 100;
	i = -1;
	while (++i < CELL_SIZE)
	{
		j = -1;
		while (++j < CELL_SIZE)
		{
			color = 0x000000;
			if (i == 0 || i == 63 || j == 0 || j == 63)
				color = 0xCCCCCC;
			else if (cell_value == '1')
				color = 0xFFFFFF;
			my_pixel_put(&mlx_core->img_data, x_pos + i, y_pos + j, color);
		}
	}
}

void	place_player(t_img *img_data, t_player *player)
{
	int	player_size;
	int	x_pos;
	int	y_pos;
	int	i;
	int	j;

	player_size = CELL_SIZE / 2;
	x_pos = player->x_coord * CELL_SIZE + 400 + (CELL_SIZE - player_size) / 2;
	y_pos = player->y_coord * CELL_SIZE + 100 + (CELL_SIZE - player_size) / 2;
	i = -1;
	while (++i < player_size)
	{
		j = -1;
		while (++j < player_size)
			my_pixel_put(img_data, x_pos + i, y_pos + j, 0x00FF0000);
	}
}

void	start_raycaster(t_mlx *mlx_core)
{
	int	x;
	int	y;

	y = -1;
	while (++y < mlx_core->map->n_rows)
	{
		x = -1;
		while (mlx_core->map->grid[y][++x])
			draw_cell(x, y, mlx_core->map->grid[y][x], mlx_core);
	}
	place_player(&mlx_core->img_data, &mlx_core->player);

	// get rays for horizontal and vertical intersections (DDA)

	// my_pixel_put(&mlx_core->img_data, 0, 0, 0x00FF0000);
	mlx_put_image_to_window(mlx_core->mlx_ptr, mlx_core->window,
		mlx_core->img_data.img_ptr, 0, 0);
}
