/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:04:21 by tanas             #+#    #+#             */
/*   Updated: 2023/12/11 14:04:31 by tanas            ###   ########.fr       */
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