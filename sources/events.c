/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:34:35 by tanas             #+#    #+#             */
/*   Updated: 2023/11/16 20:06:35 by sabdelra         ###   ########.fr       */
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


void	move_player(int keycode, t_mlx *mlx)
{
	double *p[2];

	p[X] = &mlx->player.position[X];
	p[Y] = &mlx->player.position[Y];
	if (keycode == KEYCODE_W && mlx->map->grid[(int)(*p[Y] - MOVE)][(int)(*p[X])] != WALL)
		*p[Y] -= MOVE;
	else if (keycode == KEYCODE_A  && mlx->map->grid[(int)(*p[Y])][(int)(*p[X] - MOVE)] != WALL)
		*p[X] -= MOVE;
	else if (keycode == KEYCODE_S && mlx->map->grid[(int)(*p[Y] + MOVE)][(int)(*p[X])] != WALL)
		*p[Y] += MOVE;
	else if (keycode == KEYCODE_D && mlx->map->grid[(int)(*p[Y])][(int)(*p[X] + MOVE)] != WALL)
		*p[X] += MOVE;
	ft_memset(mlx->img_data.addr, 0, (WIN_HEIGHT * WIN_WIDTH * 4));
	display_background(mlx);
	ray_cast(&mlx->player, mlx->map, mlx);
}

int	handle_events(int keycode, t_mlx *mlx)
{
	if (keycode == KEYCODE_ESC)
		close_mlx(mlx);
	else if (keycode == KEYCODE_W || keycode == KEYCODE_A
		|| keycode == KEYCODE_S || keycode == KEYCODE_D)
		move_player(keycode, mlx);
	return (0);
}

int	no_event(void)
{
	return (0);
}
