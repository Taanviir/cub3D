/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:39:46 by tanas             #+#    #+#             */
/*   Updated: 2023/11/12 03:20:05 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	draw_cell(int x, int y, char cell_value, t_mlx *mlx_core)
// {
// 	int	color;
// 	int	i;
// 	int	j;

// 	if (!cell_value || cell_value == ' ' || cell_value == '\n')
// 		return ;
// 	x = x * CELL_SIZE + X_OFFSET;
// 	y = y * CELL_SIZE + Y_OFFSET;
// 	i = -1;
// 	while (++i < CELL_SIZE)
// 	{
// 		j = -1;
// 		while (++j < CELL_SIZE)
// 		{
// 			if (i == 0 || i == 63 || j == 0 || j == 63)
// 				color = 0xCCCCCC;
// 			else if (cell_value == '1')
// 				color = 0xFFFFFF;
// 			else
// 				break ;
// 			my_pixel_put(&mlx_core->img_data, x + i, y + j, color);
// 		}
// 	}
// }

// static void	place_player(t_mlx *mlx_core, t_player *player)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	while (++y < PLAYER_SIZE)
// 	{
// 		x = -1;
// 		while (++x < PLAYER_SIZE)
// 			my_pixel_put(&mlx_core->img_data, player->x + y, player->y + x, 0x00FF0000);
// 	}
// }

// static void	display_map_grid(t_mlx *mlx_core)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < mlx_core->map->n_rows)
// 	{
// 		x = -1;
// 		while (mlx_core->map->grid[y][++x])
// 			draw_cell(x, y, mlx_core->map->grid[y][x], mlx_core);
// 	}
// 	place_player(mlx_core, &mlx_core->player);
// 	// implement player looking direction and FOV
// }

// void	start_raycaster(t_mlx *mlx_core)
// {
// 	display_map_grid(mlx_core);
// 	// get rays for horizontal and vertical intersections (DDA)

// 	mlx_put_image_to_window(mlx_core->mlx_ptr, mlx_core->window,
// 		mlx_core->img_data.img_ptr, 0, 0);
// }
