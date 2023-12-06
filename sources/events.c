/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:34:35 by tanas             #+#    #+#             */
/*   Updated: 2023/12/05 13:23:14 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_data.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	mlx_destroy_display(mlx->mlx_ptr); //! not there in mac
	map_free(mlx->map);
	free(mlx->mlx_ptr);
	free(mlx);
	exit(0);
}

void	rotate_player(int keycode, t_mlx *mlx, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	ft_memset(mlx->img_data.addr, 0, WIN_WIDTH * WIN_HEIGHT * 4);
	old_dir_x = player->dir.x;
	old_plane_x = player->camera_plane.x;
	if (keycode == KEYCODE_R_ARROW) // look right
	{
		//both camera direction and camera plane must be rotated
		player->dir.x = player->dir.x * cos(-player->rot_speed) - player->dir.y * sin(-player->rot_speed);
		player->dir.y = old_dir_x * sin(-player->rot_speed) + player->dir.y * cos(-player->rot_speed);
		player->camera_plane.x = player->camera_plane.x * cos(-player->rot_speed) - player->camera_plane.y * sin(-player->rot_speed);
		player->camera_plane.y = old_plane_x * sin(-player->rot_speed) + player->camera_plane.y * cos(-player->rot_speed);
	}
	else if (keycode == KEYCODE_L_ARROW) // look left
	{
		//both camera direction and camera plane must be rotated
		player->dir.x = player->dir.x * cos(player->rot_speed) - player->dir.y * sin(player->rot_speed);
		player->dir.y = old_dir_x * sin(player->rot_speed) + player->dir.y * cos(player->rot_speed);
		player->camera_plane.x = player->camera_plane.x * cos(player->rot_speed) - player->camera_plane.y * sin(player->rot_speed);
		player->camera_plane.y = old_plane_x * sin(player->rot_speed) + player->camera_plane.y * cos(player->rot_speed);
	}
	start_raycaster(mlx);
}

void	move_player(int keycode, t_mlx *mlx, t_player *player, char **grid)
{
	t_vector	new_pos;

	ft_memset(mlx->img_data.addr, 0, WIN_WIDTH * WIN_HEIGHT * 4);
	if (keycode == KEYCODE_W || keycode == KEYCODE_S) // move forward
	{
		if (keycode == KEYCODE_W)
		{
			new_pos.x = player->pos.x + (player->dir.x * player->move_speed);
			new_pos.y = player->pos.y + (player->dir.y * player->move_speed);
		}
		else
		{
			new_pos.x = player->pos.x - (player->dir.x * player->move_speed);
			new_pos.y = player->pos.y - (player->dir.y * player->move_speed);
		}
		if (grid[(int)new_pos.x][(int)player->pos.y] != '1' && grid[(int)(player->pos.x)][(int)new_pos.y] != '1')
			player->pos = new_pos;
	}
	else if (keycode == KEYCODE_D || keycode == KEYCODE_A)
	{
		if (keycode == KEYCODE_D)
		{
			new_pos.x = player->pos.x + player->camera_plane.x * player->move_speed;
			new_pos.y = player->pos.y + player->camera_plane.y * player->move_speed;
		}
		else // KEYCODE_A
		{
			new_pos.x = player->pos.x - player->camera_plane.x * player->move_speed;
			new_pos.y = player->pos.y - player->camera_plane.y * player->move_speed;
		}

		if (grid[(int)new_pos.x][(int)player->pos.y] != '1' && grid[(int)player->pos.x][(int)new_pos.y] != '1')
		{
			player->pos.x = new_pos.x;
			player->pos.y = new_pos.y;
		}
	}
	start_raycaster(mlx);
}

int	handle_events(int keycode, t_mlx *mlx)
{
	if (keycode == KEYCODE_ESC)
		close_mlx(mlx);
	else if (keycode == KEYCODE_W || keycode == KEYCODE_A
		|| keycode == KEYCODE_S || keycode == KEYCODE_D)
		move_player(keycode, mlx, &mlx->player, mlx->map->grid);
	else if (keycode == KEYCODE_L_ARROW || KEYCODE_R_ARROW)
		rotate_player(keycode, mlx, &mlx->player);
	return (0);
}

int	no_event(void)
{
	return (0);
}
