/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:39:46 by tanas             #+#    #+#             */
/*   Updated: 2023/12/05 13:36:03 by tanas            ###   ########.fr       */
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
	int	endian;

	y = -1;
	endian = img_data->endian;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				my_pixel_put(img_data, x, y, get_color(c_color, 0, endian));
			else
				my_pixel_put(img_data, x, y, get_color(f_color, 0, endian));
		}
	}
}

void draw_vert(t_img *img_data, int x, int y, int height, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || height >= WIN_HEIGHT || y > height)
		return ;
	while (++y <= height + 1)
		my_pixel_put(img_data, x, y, color);
}

void	ray_cast(char **grid, t_player *player, t_img *img_data)
{
	int			column; // each column of pixels in the window
	double		camera_x; // x-coordinate in camera space
	t_vector	ray_dir; // ray vector
	t_point		map; // map coords
	t_vector	delta_dist;
	t_vector	side_dist;
	t_point		step; // x-y step direction

	int			side; // was a NS or a EW wall hit?
	int			hit; // was there a wall hit?
	double		perp_wall_dist; // length of the ray
	int			wall_height; // height of the vertical columns
	int			draw_start; // pixel to start vertical column from
	int			draw_end; // pixel to stop vertical column at

	delta_dist.x =  1e30;
	delta_dist.y =  1e30;
	column = -1;
	while (++column < WIN_WIDTH)
	{
		// calculate ray position and direction
		camera_x = 2 * column / (double)(WIN_WIDTH) - 1;
		ray_dir.x = player->dir.x + (player->camera_plane.x * camera_x);
		ray_dir.y = player->dir.y + (player->camera_plane.y * camera_x);

		// which box of the map we're in
		map.x = (int)player->pos.x;
		map.y = (int)player->pos.y;

		// length of ray from one x or y-side to next x or y-side
		if (ray_dir.x)
			delta_dist.x = fabs(1 / ray_dir.x);
		if (ray_dir.y)
			delta_dist.y = fabs(1 / ray_dir.y);

		// calculate step and initial sideDist
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (player->pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - player->pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (player->pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - player->pos.y) * delta_dist.y;
		}

		// DDA algorithm
		// hit = check_wall_hit();
		hit = 0;
		while (!hit)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			hit = (grid[map.x][map.y] == '1');
		}

		if (!side)
			perp_wall_dist = (side_dist.x - delta_dist.x);
		else
			perp_wall_dist = (side_dist.y - delta_dist.y);

		// calculate height of line to draw on screen
		wall_height = (int)(WIN_HEIGHT / perp_wall_dist);

		// calculate lowest and highest pixel to fill in current stripe
		draw_start = (-wall_height + WIN_HEIGHT) / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = (wall_height + WIN_HEIGHT) / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;

		if (draw_end > draw_start)
			draw_vert(img_data, column, draw_start, draw_end, 0x00FF0000);
	}
}

void	start_raycaster(t_mlx *mlx)
{
	// draw_ceiling_and_floor(&mlx->img_data, mlx->map->c_color, mlx->map->f_color);
	// draw_minimap(mlx);

	ray_cast(mlx->map->grid, &mlx->player, &mlx->img_data);

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->window,
		mlx->img_data.img_ptr, 0, 0);
}
