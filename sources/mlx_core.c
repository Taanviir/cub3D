/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:08 by tanas             #+#    #+#             */
/*   Updated: 2023/11/04 18:00:39 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ------------------------------ initializing ------------------------------ */
static t_img	create_mlx_image(void *mlx_ptr)
{
	t_img	image;

	image.img_ptr = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	image.addr = mlx_get_data_addr(image.img_ptr, &image.bpp,
			&image.line_length, &image.endian);
	return (image);
}

t_mlx	*init_mlx_core(char *map_path)
{
	t_mlx	*mlx_core;

	mlx_core = malloc(sizeof(t_mlx));
	if (!mlx_core && write_error_msg(MALLOC_FAIL))
		return (NULL);
	mlx_core->mlx_ptr = mlx_init();
	if (!mlx_core->mlx_ptr && write_error_msg(MLX_INIT_FAIL))
	{
		free(mlx_core);
		return (NULL);
	}
	mlx_core->window = mlx_new_window(mlx_core->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!mlx_core->window && write_error_msg(MLX_WIN_FAIL))
	{
		//! couldnt find a way to free mlx_ptr
		free(mlx_core);
		return (NULL);
	}
	mlx_core->img_data = create_mlx_image(mlx_core->mlx_ptr);
	mlx_core->map = map_load(map_path);
	if (mlx_core->map)
		mlx_core->player = mlx_core->map->player;
	return (mlx_core);
}
