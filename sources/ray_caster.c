#include <cub3D.h>

/* -------------------------------- textures -------------------------------- */
typedef enum {
	TWENTY_TWO,
	SEVENTY_FIFTH
} e_hitSide;

/* -------------------------------- utilities ------------------------------- */
static int	encode_color(int map_color[TOTAL_COLORS]);

static int	ray_dda(t_dda *dda, t_map *map);

void		set_step(t_player *player, t_dda *dda);
void		draw_slice(t_mlx *mlx, double distance_to_wall, int slice, e_hitSide texture);
void		set_delta(int *slice, t_dda *dda, t_player *player);
void		display_background(t_mlx *mlx);

#define TEST_COLOR_DARK {44,180,77}
#define TEST_COLOR_LIGHT {35,144,61}

void	ray_cast(t_mlx *mlx)
{
	t_dda	dda;
	int		slice;
	double	distance_to_wall;
	e_hitSide 	hit_side;

	slice = 0;
	while (slice < WIN_WIDTH)
	{
		set_delta(&slice, &dda, &mlx->player);
		set_step(&mlx->player, &dda);
		hit_side = ray_dda(&dda, mlx->map);
		if (hit_side)
			distance_to_wall = dda.next_hit[H] - dda.delta[H];
		else
			distance_to_wall = dda.next_hit[V] - dda.delta[V];
		draw_slice(mlx, distance_to_wall, slice, hit_side);
		slice++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->window,
		mlx->img_data.img_ptr, 0, 0);
}

/**
 * @brief Stores a color into a single int
 *
 * Encodes a 3 int array representing the RGB color code, into a single color int for use int mlx functions
 *
 * @param map_color a 3 int array RGB
 *
 * @return returns the int
 */
static int encode_color(int map_color[TOTAL_COLORS])
{
	return ((map_color[R] << 16 | map_color[G] << 8 | map_color[B]));
}

void	set_step(t_player *player, t_dda *dda)
{
	if (dda->ray[X] < 0)
	{
		dda->step[X] = -1;
		dda->next_hit[V] = (player->position[X] - dda->map_cell[X]) * dda->delta[V];
	}
	else
	{
		dda->step[X] = 1;
		dda->next_hit[V] = (dda->map_cell[X] + 1 - player->position[X]) * dda->delta[V];
	}
	if (dda->ray[Y] < 0)
	{
		dda->step[Y] = -1;
		dda->next_hit[H] = (player->position[Y] - dda->map_cell[Y]) * dda->delta[H];
	}
	else
	{
		dda->step[Y] = 1;
		dda->next_hit[H] = (dda->map_cell[Y] + 1 - player->position[Y]) * dda->delta[H];
	}
}
void	draw_slice(t_mlx *mlx, double distance_to_wall, int slice, e_hitSide texture)
{
	int	slice_start;
	int slice_end;
	int	slice_height;
	int	max_height;
	int color[2][3] = {TEST_COLOR_DARK, TEST_COLOR_LIGHT};

	max_height = WIN_HEIGHT;
	slice_height = (int)(max_height / distance_to_wall);

	slice_start = (-slice_height / 2) + (max_height / 2);
	if (slice_start < 0)
		slice_start = 0;
	slice_end = (slice_height / 2) + (max_height / 2);
	if (slice_end >= max_height)
		slice_end = max_height - 1;
	for (int i = slice_start; i < slice_end; i++)
		my_pixel_put(&mlx->img_data, slice, i, encode_color(color[texture]));
}
void	set_delta(int *slice, t_dda *dda, t_player *player)
{
	double	cfx;
	double	camera_x;

	cfx = 2 / (double)WIN_WIDTH;
	dda->map_cell[X] = (int)player->position[X];
	dda->map_cell[Y] = (int)player->position[Y];
	camera_x = (*slice * cfx) - 1; // [-1, 1]
	dda->ray[X] = player->direction[X] + (player->cam_plane[X] * camera_x);
	dda->ray[Y] = player->direction[Y] + (player->cam_plane[Y] * camera_x);
	if (dda->ray[X])
		dda->delta[V] = fabs(1/dda->ray[X]);
	else
		dda->delta[V] = VERY_BIG_NUMBER;
	if (dda->ray[Y])
		dda->delta[H] = fabs(1/dda->ray[Y]);
	else
		dda->delta[H] = VERY_BIG_NUMBER;
}

static int	ray_dda(t_dda *dda, t_map *map)
{
	int		current_grid[2];
	bool	hit;
	int		hit_side;

	current_grid[X] = dda->map_cell[X];
	current_grid[Y] = dda->map_cell[Y];
	hit = false;
	while (!hit)
	{
		if (dda->next_hit[V] < dda->next_hit[H])
		{
			dda->next_hit[V] += dda->delta[V];
			current_grid[X] += dda->step[X];
			hit_side = 0; // this needs to be adjusted for faces
		}
		else
		{
			dda->next_hit[H] += dda->delta[H];
			current_grid[Y] += dda->step[Y];
			hit_side = 1; // this needs to be adjusted for faces
		}
		if (map->grid[current_grid[Y]][current_grid[X]] == WALL) {
			hit = true;
		}
	}
	return (hit_side);
}

void display_background(t_mlx *mlx)
{
	int		current_color;
	int		ceiling_color;
	int		floor_color;

	ceiling_color = encode_color(mlx->map->c_color);
	floor_color = encode_color(mlx->map->f_color);
	current_color = ceiling_color;
	for (int row = 0; row < WIN_HEIGHT; row++) {
		for (int column = 0; column < WIN_WIDTH; column++) {
			my_pixel_put(&mlx->img_data, column, row, current_color);
		}
		if (row >= WIN_HEIGHT/2)
			current_color = floor_color;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->window,
		mlx->img_data.img_ptr, 0, 0);
}
