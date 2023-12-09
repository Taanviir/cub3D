/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_background.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:18:46 by tanas             #+#    #+#             */
/*   Updated: 2023/12/10 02:10:29 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * @brief Stores a color into a single int
 *
 * Encodes a 3 int array representing the RGB color code, into a
 * single color int for use int mlx functions
 *
 * @param map_color a 3 int array RGB
 *
 * @return returns the int
 */
static int	encode_color(int map_color[TOTAL_COLORS])
{
	return ((map_color[R] << 16 | map_color[G] << 8 | map_color[B]));
}

/**
 * @brief displays the background image, splitting the window into
 *  two halves ceiling and a floor
 *
 * @param mlx a pointer to the mlx data structure
 */
void	display_background(t_mlx *mlx)
{
	int		current_color;
	int		ceiling_color;
	int		floor_color;
	int		y;
	int		x;

	ceiling_color = encode_color(mlx->map->c_color);
	floor_color = encode_color(mlx->map->f_color);
	current_color = ceiling_color;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
			my_pixel_put(&mlx->img_data, x++, y, current_color);
		if (y >= WIN_HEIGHT / 2)
			current_color = floor_color;
		y++;
	}
}
