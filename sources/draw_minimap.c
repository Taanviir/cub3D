/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:39:47 by tanas             #+#    #+#             */
/*   Updated: 2023/11/19 17:51:07 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_cell(int x, int y, char cell_value, t_mlx *mlx)
{
	int	color;
	int	i;
	int	j;

	if (!cell_value || cell_value == ' ' || cell_value == '\n')
		return ;
	x = x * CELL_SIZE + X_OFFSET;
	y = y * CELL_SIZE + Y_OFFSET;
	i = -1;
	while (++i < CELL_SIZE)
	{
		j = -1;
		while (++j < CELL_SIZE)
		{
			if (i == 0 || i == 63 || j == 0 || j == 63)
				color = 0xCCCCCC;
			else if (cell_value == '1')
				color = 0xFFFFFF;
			else
				color = 0;
			my_pixel_put(&mlx->img_data, x + i, y + j, color);
		}
	}
}

// void	place_player_on_minimap(t_img *img_data, t_player *player)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	while (++y < PLAYER_SIZE)
// 	{
// 		x = -1;
// 		while (++x < PLAYER_SIZE)
			// my_pixel_put(img_data, player->x_pos + x, player->y_pos + y, 0xFF0000);
	// }
// }

void	draw_minimap(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < mlx->map->n_rows)
	{
		x = -1;
		while (mlx->map->grid[y][++x])
			draw_cell(x, y, mlx->map->grid[y][x], mlx);
	}
	// place_player_on_minimap(&mlx->img_data, &mlx->player);
}