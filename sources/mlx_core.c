/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:45:08 by tanas             #+#    #+#             */
/*   Updated: 2023/10/23 16:45:25 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ------------------------------ initializing ------------------------------ */
t_mlx	*init_mlx_core()
{
	t_mlx	*mlx_core;

	mlx_core = malloc(sizeof(t_mlx));
	if (!mlx_core && write_error_msg(MALLOC_FAIL))
		return (NULL);
	mlx_core->mlx = mlx_init();
	if (!mlx_core->mlx && write_error_msg(MLX_INIT_FAIL))
		return (NULL);
	mlx_core->window = mlx_new_window(mlx_core->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!mlx_core->window && write_error_msg(MLX_WIN_FAIL))
		return (NULL);
	return (mlx_core);
}

/* --------------------------------- events --------------------------------- */

int	no_event(void)
{
	return (0);
}
int	key_hook(int keysym, t_mlx *mlx_core)
{

	if (keysym == ESCAPE)
	{
		//! make sure to free
		close_mlx(mlx_core);
		exit(0);
	}
	return (0);
}

int	close_mlx(t_mlx *mlx_core)
{
	mlx_destroy_window(mlx_core->mlx, mlx_core->window);
	free(mlx_core);
	return (0);
}
