/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:34:35 by tanas             #+#    #+#             */
/*   Updated: 2023/12/09 20:20:08 by tanas            ###   ########.fr       */
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

void	rotate_player(int keycode, t_mlx *mlx)
{
	double	*c[2];
	double	*d[2];
	double	old_d[2];
	double	old_c[2];
	double	sin_step;
	double	cos_step;

	d[X] = &mlx->player.direction[X];
	d[Y] = &mlx->player.direction[Y];
	c[X] = &mlx->player.camera_plane[X];
	c[Y] = &mlx->player.camera_plane[Y];
	old_d[X] = mlx->player.direction[X];
	old_d[Y] = mlx->player.direction[Y];
	old_c[X] = mlx->player.camera_plane[X];
	old_c[Y] = mlx->player.camera_plane[Y];
	sin_step = sin((ROTATE_ANGLE * 3.14) / 180.0F);
	cos_step = cos((ROTATE_ANGLE * 3.14) / 180.0F);
	if (keycode == KEYCODE_L_ARROW)
	{
		*d[X] = old_d[X] * cos_step + old_d[Y] * sin_step;
		*c[X] = old_c[X] * cos_step + old_c[Y] * sin_step;
		*d[Y] = -old_d[X] * sin_step + old_d[Y] * cos_step;
		*c[Y] = -old_c[X] * sin_step + old_c[Y] * cos_step;
	}
	else if (keycode == KEYCODE_R_ARROW)
	{
		*d[X] = old_d[X] * cos_step - old_d[Y] * sin_step;
		*c[X] = old_c[X] * cos_step - old_c[Y] * sin_step;
		*d[Y] = old_d[X] * sin_step + old_d[Y] * cos_step;
		*c[Y] = old_c[X] * sin_step + old_c[Y] * cos_step;
	}
	ray_cast(mlx);
}

void	move_player(int keycode, t_mlx *mlx)
{
	double *pos[2];
	double move[3];

	move[ANGLE] = atan2(mlx->player.direction[Y],  mlx->player.direction[X]);
	move[SIN] = MOVE * sin(move[ANGLE]);
	move[COS] = MOVE * cos(move[ANGLE]);
	pos[X] = &mlx->player.position[X];
	pos[Y] = &mlx->player.position[Y];
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
