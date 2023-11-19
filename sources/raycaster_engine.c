/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:39:46 by tanas             #+#    #+#             */
/*   Updated: 2023/11/19 17:57:52 by tanas            ###   ########.fr       */
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

// double	rad_to_deg(double i_radians)
// {
// 	return (180 * i_radians / PI);
// }

// double	deg_to_rad(int a)
// {
// 	return (a * PI / 180.0);
// }

void draw_vert(t_img *img_data, int x, int y, int height, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || height >= WIN_HEIGHT || y > height)
		return ;
	while (++y <= height + 1)
		my_pixel_put(img_data, x, y, color);
}

void	ray_cast(char **grid, t_player *player, t_img *img_data)
{
	int		column; // each column of pixels in the window
	double	camera_x; // x-coordinate in camera space
	double	ray_dir_x; // x-coordinate of ray vector
	double	ray_dir_y; // y-coordinate of ray vector
	int		map_x; // x-pos of map coordinate
	int		map_y; // y-pos of map coordinate
	double	delta_dist_x; // distance from one x-side to the next x-side
	double	delta_dist_y; // distance from one y-side to the next y-side
	double	perp_wall_dist; // length of the ray

	double	side_dist_x; // length of ray from current position to next x-side
	double	side_dist_y; // length of ray from current position to next y-side

	//what direction to step in x or y-direction (either +1 or -1)
	int		step_x;
	int		step_y;

	int		side; //was a NS or a EW wall hit?
	int		hit; //was there a wall hit?
	int		line_height; // height of the vertical columns
	int		draw_start; // pixel to start vertical column from
	int		draw_end; // pixel to stop vertical column at

	delta_dist_x =  1e30;
	delta_dist_y =  1e30;
	column = -1;
	while (++column < WIN_WIDTH)
	{
		//calculate ray position and direction
		camera_x = 2 * column / (double)(WIN_WIDTH) - 1;
		ray_dir_x = player->dir.x + player->camera_plane.x * camera_x;
		ray_dir_y = player->dir.y + player->camera_plane.y * camera_x;

		//which box of the map we're in
		map_x = (int)player->pos.x;
		map_y = (int)player->pos.y;
		//length of ray from one x or y-side to next x or y-side
		if (ray_dir_x)
			delta_dist_x = fabs(1 / ray_dir_x);
		if (ray_dir_y)
			delta_dist_y = fabs(1 / ray_dir_y);

		// calculate step and initial sideDist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->pos.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->pos.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->pos.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->pos.y) * delta_dist_y;
		}

		// DDA algorithm
		hit = 0;
		while (!hit)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			hit = (grid[map_x][map_y] == '1');
		}

		if (!side)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		// calculate height of line to draw on screen
		line_height = (int)(WIN_HEIGHT / perp_wall_dist);

		// calculate lowest and highest pixel to fill in current stripe
		draw_start = (-line_height + WIN_HEIGHT) / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = (line_height + WIN_HEIGHT) / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;

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
