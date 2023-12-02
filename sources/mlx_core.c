/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:08 by tanas             #+#    #+#             */
/*   Updated: 2023/11/29 02:40:45 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ------------------------------ initializing ------------------------------ */
static void	*exit_init(t_mlx *mlx, char *error_message)
{
	if (mlx->map && mlx->img_data.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_data.img_ptr);
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

static bool load_textures(t_mlx *mlx)
{
	char	*texture_path;
	void	**texture;
	char	**address;
	int		*width;
	int		*height;

	for(int i = 0; i < TOTAL_TEXTURES; i++)
	{
		texture = &(mlx->textures[i].img_ptr);
		address = &(mlx->textures[i].addr);
		texture_path = mlx->map->texture[i];
		width = &mlx->textures[i].img_width;
		height = &mlx->textures[i].img_height;
		texture = mlx_xpm_file_to_image(mlx->mlx_ptr, texture_path, width, height);
		if (!texture)
			return (write_error_msg(TEXTURE_FAIL));
		*address = mlx_get_data_addr(texture, &mlx->textures[i].bpp,
			&mlx->textures[i].line_length, &mlx->textures[i].endian);
		if (!address)
			return (write_error_msg(TEXTURE_FAIL));
	}
	return (true);
}

static t_img	create_image(void *mlx_ptr, int width, int height)
{
	t_img	image;

	image.img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!image.img_ptr)
		return ((t_img){0});
	image.addr = mlx_get_data_addr(image.img_ptr, &image.bpp,
			&image.line_length, &image.endian);
	return (image);
}

t_mlx	*init_mlx_data(char *map_path)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (write_error_msg(MALLOC_FAIL), NULL);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (exit_init(mlx, MLX_INIT_FAIL));
	mlx->window = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!mlx->window)
		return (exit_init(mlx, MLX_WIN_FAIL));
	mlx->map = map_load(map_path);
	if (!mlx->map)
		return (exit_init(mlx, NULL));
	if(!grid_validate(mlx->map, &mlx->player))
		return (exit_init(mlx, NULL));
	if (!mlx->map)
		return (exit_init(mlx, NULL));
	mlx->img_data = create_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img_data.addr)
		return (exit_init(mlx, MLX_IMG_FAIL));
	if (!load_textures(mlx))
		return (exit_init(mlx, TEXTURE_FAIL));
	return (mlx);
}
