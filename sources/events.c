/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:34:35 by tanas             #+#    #+#             */
/*   Updated: 2023/12/10 19:52:59 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	#ifdef __LINUX__
	mlx_destroy_display(mlx->mlx_ptr);
	#endif
	free(mlx->mlx_ptr);
	free(mlx);
	map_free(map);
	return (SUCCESS);
}

void turn(t_mlx *mlx, t_rot rotation)
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
}

void	rotate_player(int keycode, t_mlx *mlx)
{
	if (keycode == KEYCODE_L_ARROW)
		turn(mlx, LEFT);
	else if (keycode == KEYCODE_R_ARROW)
		turn(mlx, RIGHT);
	ray_cast(mlx);
}

void	move_player(int keycode, t_mlx *mlx)
{
	double *pos[2];
	double move[3];

	move[ANGLE] = atan2(mlx->player.direction[Y],  mlx->player.direction[X]);
	move[SIN] = MOVE * sin(move[ANGLE]);
	move[COS] = MOVE * cos(move[ANGLE]);
	pos[X] = &mlx->player.pos[X];
	pos[Y] = &mlx->player.pos[Y];
	if (keycode == KEYCODE_W)
	{
		if (mlx->map->grid[(int)(*pos[Y] + move[SIN])][(int)(*pos[X])] != WALL)
			*pos[Y] += move[SIN];
		if (mlx->map->grid[(int)(*pos[Y])][(int)(*pos[X] + move[COS])] != WALL)
			*pos[X] += move[COS];
	}
	else if (keycode == KEYCODE_A)
	{
		if (mlx->map->grid[(int)(*pos[Y] - move[COS])][(int)(*pos[X])] != WALL)
			*pos[Y] -= move[COS];
		if (mlx->map->grid[(int)(*pos[Y])][(int)(*pos[X] + move[SIN])] != WALL)
			*pos[X] += move[SIN];
	}
	else if (keycode == KEYCODE_S)
	{
		if (mlx->map->grid[(int)(*pos[Y] - move[SIN])][(int)(*pos[X])] != WALL)
			*pos[Y] -= move[SIN];
		if (mlx->map->grid[(int)(*pos[Y])][(int)(*pos[X] - move[COS])] != WALL)
			*pos[X] -= move[COS];
	}
	else if (keycode == KEYCODE_D)
	{
		if (mlx->map->grid[(int)(*pos[Y] + move[COS])][(int)(*pos[X])] != WALL)
			*pos[Y] += move[COS];
		if (mlx->map->grid[(int)(*pos[Y])][(int)(*pos[X] - move[SIN])] != WALL)
			*pos[X] -= move[SIN];
	}
	ray_cast(mlx);
}

int	handle_events(int keycode, t_mlx *mlx)
{
	if (keycode == KEYCODE_ESC)
		close_mlx(mlx);
	else if (keycode == KEYCODE_W || keycode == KEYCODE_A
		|| keycode == KEYCODE_S || keycode == KEYCODE_D)
		move_player(keycode, mlx);
	else if (keycode == KEYCODE_L_ARROW || keycode == KEYCODE_R_ARROW)
		rotate_player(keycode, mlx);
	return (0);
}

int	no_event(void)
{
	return (0);
}
