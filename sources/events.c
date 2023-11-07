/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:34:35 by tanas             #+#    #+#             */
/*   Updated: 2023/11/08 01:43:17 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_mlx_core(t_mlx *mlx_core)
{
	mlx_destroy_image(mlx_core->mlx_ptr, mlx_core->img_data.img_ptr);
	mlx_destroy_window(mlx_core->mlx_ptr, mlx_core->window);
	mlx_destroy_display(mlx_core->mlx_ptr); //! not there in mac
	map_free(mlx_core->map);
	free(mlx_core->mlx_ptr);
	free(mlx_core);
	exit(0);
}

void	move_player(int keycode, t_mlx *mlx_core)
{
	if (keycode == KEYCODE_W)
		mlx_core->player.y_pos -= 5;
	else if (keycode == KEYCODE_A)
		mlx_core->player.x_pos -= 5;
	else if (keycode == KEYCODE_S)
		mlx_core->player.y_pos += 5;
	else if (keycode == KEYCODE_D)
		mlx_core->player.x_pos += 5;
	place_player_on_minimap(&mlx_core->img_data, &mlx_core->player);
	// remove the bits left behind
	mlx_put_image_to_window(mlx_core->mlx_ptr, mlx_core->window,
		mlx_core->img_data.img_ptr, 0, 0);
}

int	handle_events(int keycode, t_mlx *mlx_core)
{
	if (keycode == KEYCODE_ESC)
		close_mlx_core(mlx_core);
	else if (keycode == KEYCODE_W || keycode == KEYCODE_A
		|| keycode == KEYCODE_S || keycode == KEYCODE_D)
		move_player(keycode, mlx_core);
	// else if (keycode == KEYCODE_L_ARROW || KEYCODE_R_ARROW)
	return (0);
}

int	no_event(void)
{
	return (0);
}
