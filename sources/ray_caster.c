/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 23:42:55 by sabdelra          #+#    #+#             */
/*   Updated: 2023/12/10 02:07:42 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/* ---------------------------- ray cast helpers ---------------------------- */
static void			raycast_set_step(const double *pos, t_dda *dda);
static e_texture	raycast_dda(t_dda *dda, const t_map *map);
static void			raycast_set_delta(t_dda *dda, const t_player *player,
			const int *slice, const double ncf);
static void			draw_slice(t_mlx *mlx, t_dda *dda, int slice);

/* --------------------------- draw slice helpers --------------------------- */
static bool			set_texel(t_mlx *mlx, t_dda *dda, double *texel, double *column);
static void			find_col_height(double *col, int max_height, double dist_to_wall);
inline static unsigned int	get_texel_color(t_img *image, int x, int y, bool dark);


void	ray_cast(t_mlx *mlx)
{
	t_dda		dda;
	e_texture	hit;
	int			slice;
	double		ncf;

	slice = 0;
	ncf = 2 / (double)WIN_WIDTH;
	dda.map_cell[X] = (int)mlx->player.pos[X];
	dda.map_cell[Y] = (int)mlx->player.pos[Y];
	display_background(mlx);
	while (slice < WIN_WIDTH)
	{
		raycast_set_delta(&dda, &mlx->player, &slice, ncf);
		raycast_set_step(mlx->player.pos, &dda);
		hit = raycast_dda(&dda, mlx->map);
		if (hit == dda.side[H])
			dda.distance_to_wall = dda.next_hit[H] - dda.delta[H];
		else
			dda.distance_to_wall = dda.next_hit[V] - dda.delta[V];
		draw_slice(mlx, &dda, slice);
		slice++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->window,
		mlx->img_data.img_ptr, 0, 0);
}

/**
 * @brief Sets step direction and initial hit points for raycasting in DDA.
 *
 * Determines the X and Y step directions based on the ray's direction and
 * calculates initial grid cell hit points. It also identifies the
 * first wall side (East, West, North, South) the ray encounters for
 * wall collision detection in the DDA algorithm.
 *
 * @param pos Pointer to the player's x and y positions.
 * @param dda Pointer to the DDA structure for raycasting data.
 */
static void	raycast_set_step(const double *pos, t_dda *dda)
{
	if (dda->ray[X] < 0)
	{
		dda->step[X] = -1;
		dda->next_hit[V] = (pos[X] - dda->map_cell[X]) * dda->delta[V];
		dda->side[V] = WE;
	}
	else
	{
		dda->step[X] = 1;
		dda->next_hit[V] = (dda->map_cell[X] + 1 - pos[X]) * dda->delta[V];
		dda->side[V] = EA;
	}
	if (dda->ray[Y] < 0)
	{
		dda->step[Y] = -1;
		dda->next_hit[H] = (pos[Y] - dda->map_cell[Y]) * dda->delta[H];
		dda->side[H] = SO;
	}
	else
	{
		dda->step[Y] = 1;
		dda->next_hit[H] = (dda->map_cell[Y] + 1 - pos[Y]) * dda->delta[H];
		dda->side[H] = NO;
	}
}

// returns the color of a texel :)
inline static unsigned int	get_texel_color(t_img *img, int x, int y, bool dark)
{
	unsigned int	current_color;

	if (y >= 0 && x >= 0 && x < img->img_width && y < img->img_height)
		current_color = *((unsigned int *)(img->addr
					+ (y * img->line_length + x * (img->bpp / 8))));
	if (dark)
		current_color = (current_color >> 1) & 8355711;
	return (current_color);
}

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

static void	draw_slice(t_mlx *mlx, t_dda *dda, int slice)
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

/**
 * @brief Computes ray direction and delta distances for DDA.
 *
 * Translates slice index to camera space, adjusting the ray based on the
 * player's direction and camera plane.
 * Computes delta distances for X and Y directions, used in the DDA algorithm
 * for wall collision detection.
 *
 * @param dda Pointer to the DDA structure containing raycasting data.
 * @param player Pointer to the player structure containing position and
 * direction data.
 * @param slice Pointer to the current slice index being processed.
 * @param ncf normalized camera factor used to translate the camera plane into
 * a [-1, 1] range
 */
static void	raycast_set_delta(t_dda *dda, const t_player *player,
	const int *slice, const double ncf)
{
	double	camera_x_pos;

	camera_x_pos = (*slice * ncf) - 1;
	dda->ray[X] = player->direction[X]
		+ (player->camera_plane[X] * camera_x_pos);
	dda->ray[Y] = player->direction[Y]
		+ (player->camera_plane[Y] * camera_x_pos);
	if (dda->ray[X])
		dda->delta[V] = fabs(1 / dda->ray[X]);
	else
		dda->delta[V] = VERY_BIG_NUMBER;
	if (dda->ray[Y])
		dda->delta[H] = fabs(1 / dda->ray[Y]);
	else
		dda->delta[H] = VERY_BIG_NUMBER;
}

/**
 * @brief Executes DDA algorithm for raycasting.
 *
 * Steps through the map grid based on the ray's direction to find the
 * first wall hit.
 * Updates ray's hit information for texture determination and wall rendering.
 *
 * @param dda Pointer to the DDA structure with raycasting data.
 * @param map Pointer to the game world map structure.
 *
 * @return wall side hit by the ray.
 */
static e_texture	raycast_dda(t_dda *dda, const t_map *map)
{
	int			current_grid[2];

	current_grid[X] = dda->map_cell[X];
	current_grid[Y] = dda->map_cell[Y];
	while (true)
	{
		if (dda->next_hit[V] < dda->next_hit[H])
		{
			dda->next_hit[V] += dda->delta[V];
			current_grid[X] += dda->step[X];
			dda->hit = dda->side[V];
		}
		else
		{
			dda->next_hit[H] += dda->delta[H];
			current_grid[Y] += dda->step[Y];
			dda->hit = dda->side[H];
		}
		if (map->grid[current_grid[Y]][current_grid[X]] == WALL)
			break ;
	}
	return (dda->hit);
}
