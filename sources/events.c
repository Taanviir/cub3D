/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:34:35 by tanas             #+#    #+#             */
/*   Updated: 2023/12/11 13:39:43by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#ifdef __LINUX__

int	close_mlx(t_mlx *mlx)
{
	int		i;
	t_map	*map;

	map = mlx->map;
	i = 0;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_data.img_ptr);
	while (i < TOTAL_TEXTURES && mlx->textures[i].img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->textures[i++].img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free(mlx);
	map_free(map);
	return (SUCCESS);
}

#elif __APPLE__

int	close_mlx(t_mlx *mlx)
{
	int		i;
	t_map	*map;

	map = mlx->map;
	i = 0;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_data.img_ptr);
	while (i < TOTAL_TEXTURES && mlx->textures[i].img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->textures[i++].img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	free(mlx->mlx_ptr);
	free(mlx);
	map_free(map);
	return (SUCCESS);
}
#endif

void	rotate_player(t_mlx *mlx, t_rot rotation)
{
	double	*camera[2];
	double	*direction[2];
	double	old_direction[2];
	double	old_camera[2];
	double	angle_step[2];

	direction[X] = &mlx->player.direction[X];
	direction[Y] = &mlx->player.direction[Y];
	camera[X] = &mlx->player.camera_plane[X];
	camera[Y] = &mlx->player.camera_plane[Y];
	old_direction[X] = mlx->player.direction[X];
	old_direction[Y] = mlx->player.direction[Y];
	old_camera[X] = mlx->player.camera_plane[X];
	old_camera[Y] = mlx->player.camera_plane[Y];
	angle_step[SIN] = sin((ROTATE_ANGLE * 3.14) / 180.0F);
	angle_step[COS] = cos((ROTATE_ANGLE * 3.14) / 180.0F);
	*direction[X] = old_direction[X] * angle_step[COS]
		- (rotation * old_direction[Y]) * angle_step[SIN];
	*camera[X] = old_camera[X] * angle_step[COS]
		- (rotation * old_camera[Y]) * angle_step[SIN];
	*direction[Y] = (rotation * old_direction[X]) * angle_step[SIN]
		+ old_direction[Y] * angle_step[COS];
	*camera[Y] = (rotation * old_camera[X]) * angle_step[SIN]
		+ old_camera[Y] * angle_step[COS];
	ray_cast(mlx);
}

void	calculate_delta_move(int keycode, t_mlx *mlx, double *move)
{

	move[ANGLE] = atan2(mlx->player.direction[Y], mlx->player.direction[X]);
	if (keycode == KEYCODE_W)
	{
		move[Y] = MOVE * sin(move[ANGLE]);
		move[X] = MOVE * cos(move[ANGLE]);
	}
	else if (keycode == KEYCODE_S)
	{
		move[Y] = -1 * (MOVE * sin(move[ANGLE]));
		move[X] = -1 * (MOVE * cos(move[ANGLE]));
	}
	else if (keycode == KEYCODE_A)
	{
		move[X] = MOVE * sin(move[ANGLE]);
		move[Y] = -1 * (MOVE * cos(move[ANGLE]));
	}
	else if (keycode == KEYCODE_D)
	{
		move[X] = -1 * (MOVE * sin(move[ANGLE]));
		move[Y] = MOVE * cos(move[ANGLE]);
	}
}

void	move_player(int keycode, t_mlx *mlx)
{
	double	*pos[2];
	double	move[3];

	pos[X] = &mlx->player.pos[X];
	pos[Y] = &mlx->player.pos[Y];
	calculate_delta_move(keycode, mlx, move);
	if (mlx->map->grid[(int)(*pos[Y] + move[Y])][(int)(*pos[X])] != WALL)
		*pos[Y] += move[Y];
	if (mlx->map->grid[(int)(*pos[Y])][(int)(*pos[X] + move[X])] != WALL)
		*pos[X] += move[X];
	ray_cast(mlx);
}

int	handle_events(int keycode, t_mlx *mlx)
{
	if (keycode == KEYCODE_ESC)
		close_mlx(mlx);
	else if (keycode == KEYCODE_W || keycode == KEYCODE_A
		|| keycode == KEYCODE_S || keycode == KEYCODE_D)
		move_player(keycode, mlx);
	else if (keycode == KEYCODE_L_ARROW)
		rotate_player(mlx, LEFT);
	else if (keycode == KEYCODE_R_ARROW)
		rotate_player(mlx, RIGHT);
	return (0);
}

int	no_event(void)
{
	return (0);
}
