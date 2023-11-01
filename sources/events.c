/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:34:35 by tanas             #+#    #+#             */
/*   Updated: 2023/11/01 17:50:50 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_mlx_core(t_mlx *mlx_core)
{
	mlx_destroy_window(mlx_core->mlx_ptr, mlx_core->window);
	map_free(mlx_core->map);
	free(mlx_core);
	exit(0);
}

int	handle_events(int keycode, t_mlx *mlx_core)
{
	// printf("events caled for: %i\n", keycode);
	// TODO handle WASD, ESC, CLOSE, <- ->
	if (keycode == KEYCODE_ESC)
		close_mlx_core(mlx_core);
	else if (keycode == KEYCODE_W)
		puts("W");
	else if (keycode == KEYCODE_A)
		puts("A");
	else if (keycode == KEYCODE_S)
		puts("S");
	else if (keycode == KEYCODE_D)
		puts("D");
	return (0);
}

int	no_event(void)
{
	return (0);
}
