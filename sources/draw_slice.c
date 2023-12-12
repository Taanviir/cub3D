/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:57:04 by tanas             #+#    #+#             */
/*   Updated: 2023/12/12 01:03:35 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	find_col_height(double *col, int max_height, double dist_to_wall)
{
	col[HEIGHT] = max_height / dist_to_wall;
	col[TOP] = (-col[HEIGHT] / 2) + (max_height / 2);
	if (col[TOP] < 0)
		col[TOP] = 0;
	col[BOT] = (col[HEIGHT] / 2) + (max_height / 2);
	if (col[BOT] >= max_height)
		col[BOT] = max_height - 1;
}

// sets the texture X, Y and step papremeters and returns whether it should
// be a dark shade based on whether it hit a vertical wall or a horizontal one
static bool	set_texel(t_mlx *mlx, t_dda *dda, double *texel, double *column)
{
	double	wall_x;
	bool	dark;
	t_img	texture;

	texture = mlx->textures[dda->hit];
	texel[STEP] = 1.0 * texture.img_height / column[HEIGHT];
	if (dda->hit == NO || dda->hit == SO)
	{
		wall_x = mlx->player.pos[X] + dda->distance_to_wall * dda->ray[X];
		dark = false;
	}
	else
	{
		wall_x = mlx->player.pos[Y] + dda->distance_to_wall * dda->ray[Y];
		dark = true;
	}
	wall_x -= (int)wall_x;
	texel[X] = (int)(wall_x * (double)texture.img_width);
	texel[Y] = (double)((column[TOP] - (WIN_HEIGHT / 2) + column[HEIGHT] / 2)
			* texel[STEP]);
	if ((dda->hit == NO || dda->hit == SO) && dda->ray[Y] > 0)
		texel[X] = texture.img_width - texel[X] - 1;
	if ((dda->hit == WE || dda->hit == EA) && dda->ray[X] < 0)
		texel[X] = texture.img_width - texel[X] - 1;
	return (dark);
}

// returns the color of a texel :)
inline static unsigned int	get_texel_color(t_img *img, int x, int y, bool dark)
{
	unsigned int	current_color;

	current_color = 0;
	if (y >= 0 && x >= 0 && x < img->img_width && y < img->img_height)
		current_color = *((unsigned int *)(img->addr
					+ (y * img->line_length + x * (img->bpp / 8))));
	if (dark)
		current_color = (current_color >> 1) & 8355711;
	return (current_color);
}

void	draw_slice(t_mlx *mlx, t_dda *dda, int slice)
{
	double	column[3];
	bool	dark;
	double	texel[4];
	int		i;

	find_col_height(column, WIN_HEIGHT, dda->distance_to_wall);
	texel[X] = 0;
	texel[Y] = 0;
	dark = set_texel(mlx, dda, texel, column);
	i = column[TOP];
	while (i < column[BOT])
	{
		texel[COLOR] = get_texel_color(&mlx->textures[dda->hit], texel[X],
				texel[Y], dark);
		my_pixel_put(&mlx->img_data, slice, i, texel[COLOR]);
		texel[Y] += texel[STEP];
		i++;
	}
}
