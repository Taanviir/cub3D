/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:08 by tanas             #+#    #+#             */
/*   Updated: 2023/11/19 17:54:29 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ------------------------------ initializing ------------------------------ */
void	create_player(t_player *player, int x, int y, char view_direction)
{
	player->pos.x = x;
	player->pos.y = y;
	player->dir.x = -1;
	player->dir.y = 0;
	player->move_speed = 0.03;
	player->rot_speed = 0.03;
	player->camera_plane.x = 0;
	player->camera_plane.y = 0.66;
	if (view_direction == 'E')
		player->view_angle_rad = 0;
	else if (view_direction == 'N')
		player->view_angle_rad = PI / 2;
	else if (view_direction == 'W')
		player->view_angle_rad = PI;
	else if (view_direction == 'S')
		player->view_angle_rad = (3 * PI) / 2;
}

static void	*exit_init(t_mlx *mlx, char *error_message)
{
	if (mlx->map && mlx->img_data.addr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_data.addr);
	if (mlx->window)
		mlx_destroy_window(mlx->mlx_ptr, mlx->window);
	if (mlx->map)
		map_free(mlx->map);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	free(mlx);
	if (error_message)
		write_error_msg(error_message);
	return (NULL);
}

static t_img	create_image(void *mlx_ptr, int width, int height)
{
	t_img	image;

	image.img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!image.img_ptr)
		return ((t_img){NULL, NULL, 0, 0, 0});
	image.addr = mlx_get_data_addr(image.img_ptr, &image.bpp,
			&image.line_length, &image.endian);
	return (image);
}

t_mlx	*init_mlx_data(char *map_path)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (write_error_msg(MALLOC_FAIL), NULL);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (exit_init(mlx, MLX_INIT_FAIL));
	mlx->window = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!mlx->window)
		return (exit_init(mlx, MLX_WIN_FAIL));
	mlx->map = map_grid_validate(map_load(map_path), &mlx->player);
	if (!mlx->map)
		return (exit_init(mlx, NULL));
	mlx->img_data = create_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img_data.addr)
		return (exit_init(mlx, MLX_IMG_FAIL));
	return (mlx);
}
