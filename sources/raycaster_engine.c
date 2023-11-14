/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:39:46 by tanas             #+#    #+#             */
/*   Updated: 2023/11/14 14:01:17 by tanas            ###   ########.fr       */
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

double	rad_to_deg(double i_radians)
{
	return (180 * i_radians / PI);
}

double	deg_to_rad(int a)
{
	return (a * PI / 180.0);
}

void draw_vert(t_img *img_data, int x, int y, int height)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || height >= WIN_HEIGHT || y > height)
		return ;
	while (++y <= height + 1)
		my_pixel_put(img_data, x, y, 0xFF0000);
}

void	draw_rays_3D(char **grid, t_player *player, t_img *img_data)
{
	int	x;
	// double old_time = 0, time = 0;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(WIN_WIDTH) - 1; //x-coordinate in camera space
		double rayDirX = player->dir.x + player->camera_plane.x * cameraX;
		double rayDirY = player->dir.y + player->camera_plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)player->pos.x;
		int mapY = (int)player->pos.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->pos.y) * deltaDistY;
		}
		int side; //was a NS or a EW wall hit?
		while (!hit)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			hit = (grid[mapX][mapY] == '1');
		}
		if (!side)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		draw_vert(img_data, x, drawStart, drawEnd);
	}
	// old_time = time;
	// time = ;
	// double	frame_time = (time - old_time) / 1000.0;
	// player->move_speed = frame_time * 5.0;
	// player->rot_speed = frame_time * 3.0;
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
