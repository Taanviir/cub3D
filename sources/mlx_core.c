/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:08 by tanas             #+#    #+#             */
/*   Updated: 2023/11/06 17:32:22 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ------------------------------ initializing ------------------------------ */
static void	*exit_init(t_mlx *mlx_core, char *error_message)
{
	if (mlx_core->map && mlx_core->img_data.addr)
		mlx_destroy_image(mlx_core->mlx_ptr, mlx_core->img_data.addr);
	if (mlx_core->window)
		mlx_destroy_window(mlx_core->mlx_ptr, mlx_core->window);
	if (mlx_core->map)
		map_free(mlx_core->map);
	if (mlx_core->mlx_ptr)
	{
		mlx_destroy_display(mlx_core->mlx_ptr);
		free(mlx_core->mlx_ptr);
	}
	free(mlx_core);
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

t_mlx	*init_mlx_core(char *map_path)
{
	t_mlx	*mlx_core;

	mlx_core = malloc(sizeof(t_mlx));
	if (!mlx_core)
		return (write_error_msg(MALLOC_FAIL), NULL);
	mlx_core->mlx_ptr = mlx_init();
	if (!mlx_core->mlx_ptr)
		return (exit_init(mlx_core, MLX_INIT_FAIL));
	mlx_core->window = mlx_new_window(mlx_core->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!mlx_core->window)
		return (exit_init(mlx_core, MLX_WIN_FAIL));
	mlx_core->map = map_grid_validate(map_load(map_path), &mlx_core->player);
	if (!mlx_core->map)
		return (exit_init(mlx_core, NULL));
	mlx_core->img_data = create_image(mlx_core->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx_core->img_data.addr)
		return (exit_init(mlx_core, MLX_IMG_FAIL));
	return (mlx_core);
}
