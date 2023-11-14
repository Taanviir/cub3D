/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:34:35 by tanas             #+#    #+#             */
/*   Updated: 2023/11/14 13:56:33 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_mlx_core(t_mlx *mlx_core)
{
	mlx_destroy_image(mlx_core->mlx_ptr, mlx_core->img_data.img_ptr);
	mlx_destroy_window(mlx_core->mlx_ptr, mlx_core->window);
	mlx_destroy_display(mlx_core->mlx_ptr); //! not there in mac
	map_free(mlx_core->map);
	free(mlx_core->mlx_ptr);
	free(mlx_core);
	exit(0);
}

void	move_player(int keycode, t_mlx *mlx_core, t_player *player)
{
	ft_memset(mlx_core->img_data.addr, 0, WIN_WIDTH * WIN_HEIGHT * 4);
	if (keycode == KEYCODE_W) // move forward
	{
		if (mlx_core->map->grid[(int)(player->pos.x + player->dir.x * player->move_speed)][(int)player->pos.y] != '1')
			player->pos.x += player->dir.x * player->move_speed;
		if (mlx_core->map->grid[(int)(player->pos.x)][(int)(player->pos.y + player->dir.y * player->move_speed)] != '1')
			player->pos.y += player->dir.y * player->move_speed;
	}
	else if (keycode == KEYCODE_S) // move backward
	{
		if (mlx_core->map->grid[(int)(player->pos.x + player->dir.x * player->move_speed)][(int)player->pos.y] != '1')
			player->pos.x -= player->dir.x * player->move_speed;
		if (mlx_core->map->grid[(int)(player->pos.x)][(int)(player->pos.y + player->dir.y * player->move_speed)] != '1')
			player->pos.y -= player->dir.y * player->move_speed;
	}
	else if (keycode == KEYCODE_A) // look left
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(-player->rot_speed) - player->dir.y * sin(-player->rot_speed);
		player->dir.y = oldDirX * sin(-player->rot_speed) + player->dir.y * cos(-player->rot_speed);
		double oldPlaneX = player->camera_plane.x;
		player->camera_plane.x = player->camera_plane.x * cos(-player->rot_speed) - player->camera_plane.y * sin(-player->rot_speed);
		player->camera_plane.y = oldPlaneX * sin(-player->rot_speed) + player->camera_plane.y * cos(-player->rot_speed);
	}
	else if (keycode == KEYCODE_D) // look right
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dir.x;
		player->dir.x = player->dir.x * cos(player->rot_speed) - player->dir.y * sin(player->rot_speed);
		player->dir.y = oldDirX * sin(player->rot_speed) + player->dir.y * cos(player->rot_speed);
		double oldPlaneX = player->camera_plane.x;
		player->camera_plane.x = player->camera_plane.x * cos(player->rot_speed) - player->camera_plane.y * sin(player->rot_speed);
		player->camera_plane.y = oldPlaneX * sin(player->rot_speed) + player->camera_plane.y * cos(player->rot_speed);
	}
	start_raycaster(mlx_core);
}

int	handle_events(int keycode, t_mlx *mlx_core)
{
	if (keycode == KEYCODE_ESC)
		close_mlx_core(mlx_core);
	else if (keycode == KEYCODE_W || keycode == KEYCODE_A
		|| keycode == KEYCODE_S || keycode == KEYCODE_D)
		move_player(keycode, mlx_core, &mlx_core->player);
	// else if (keycode == KEYCODE_L_ARROW || KEYCODE_R_ARROW)
	return (0);
}

int	no_event(void)
{
	return (0);
}
