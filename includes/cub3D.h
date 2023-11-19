/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:59:37 by sabdelra          #+#    #+#             */
/*   Updated: 2023/11/19 17:53:27 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* -------------------------------- includes -------------------------------- */

# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include "keycodes.h"

# ifdef __LINUX__
#  include <X11/keysym.h>
# endif

/* ----------------------------------- map ---------------------------------- */

# define MAP_INITIAL_CAPACITY 1
# define DOUBLE 2

enum e_map_color
{
	R = 0,
	G,
	B,
	TOTAL_COLORS
};

/**
 * @brief Structure to hold map data including the grid and its metadata.
 *
 * The grid is represented as a dynamic array of strings, where each string represents a row.
 * The structure also holds the current number of rows (n_rows) and the current grid capacity (grid_capacity).
 */
typedef struct s_map
{
	/* ---------------------------------- grid ---------------------------------- */
	char	**grid;					// Dynamic array of strings to represent the grid.
	int		n_rows;					// Current number of rows in the grid.
	int		grid_capacity;			// Current capacity of the grid array.

	/* ---------------------------------- scene --------------------------------- */
	int		NO_texture_fd;			// fd for north texture file
	int		SO_texture_fd;			// fd for south texture file
	int		WE_texture_fd;			// fd for west texture file
	int		EA_texture_fd;			// fd for east texture file
	int		f_color[TOTAL_COLORS];	// floor color
	int		c_color[TOTAL_COLORS];	// ceiling color
}	t_map;

#define ACCEPTED_CHARACTERS "10VNSWE\n " // list of valid map characters
#define PLAYER_DIRECTIONS "NSWE"

t_map	*map_load(char *map_path);

/* --------------------------------- player --------------------------------- */

# define CELL_SIZE 64
# define PLAYER_SIZE 10
# define X_OFFSET 0
# define Y_OFFSET 0
// # define ONE_ANGLE 0.0174533
# define PI 3.1415926535

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	camera_plane;
	double		move_speed;
	double		rot_speed;
	double		view_angle_rad;
}	t_player;

/* -------------------------------- mlx core -------------------------------- */

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "cub3D"

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*window;
	t_img		img_data;
	t_map		*map;
	t_player	player;
}	t_mlx;

t_mlx	*init_mlx_data(char *map_path);
void	create_player(t_player *player, int x, int y, char view_direction);

/* ------------------------------- raycaster -------------------------------- */

void	start_raycaster(t_mlx *mlx);
t_map	*map_grid_validate(t_map *map, t_player *player);
void	draw_rays_3D(char **grid, t_player *player, t_img *img_data);

/* -------------------------------- minimap --------------------------------- */

void	draw_minimap(t_mlx *mlx);
void	place_player_on_minimap(t_img *img_data, t_player *player);

/* --------------------------------- events --------------------------------- */

int		no_event(void);
int		handle_events(int keycode, t_mlx *mlx);
int		close_mlx(t_mlx *mlx);

/* ---------------------------------- utils --------------------------------- */

bool	map_extension_check(char *map_path);
void	map_free(t_map *map);
void	my_pixel_put(t_img *img_data, int x, int y, int color);
void	draw_line(t_img *img_data, t_point a, t_point b);

/* ------------------------------- debug utils ------------------------------ */

void	print_t_map(t_map *map); //? for debugging only

/* -------------------------------------------------------------------------- */
/*                               error handling                               */
/* -------------------------------------------------------------------------- */

/* ------------------------------ return codes ------------------------------ */

# define SUCCESS 1
# define FAILURE 0
# define NOT_SET -1 // error code to handle failing during color

/* ----------------------------- error messages ----------------------------- */

# define MALLOC_FAIL "Failed to allocate memory."
# define MLX_INIT_FAIL "Failed to initialize mlx."
# define MLX_WIN_FAIL "Failed to start mlx window."
# define MLX_IMG_FAIL "Failed to create mlx image."
# define OPEN_FAIL "Failed to open file:"
# define SCENE_FAIL "Failed to load scene."
# define MAP_NOT_ENCLOSED "Map is not en-closed."
# define MAP_INVALID_CHARACTER "Invalid character in map file."
# define COLOR_ERROR "Color was not set correctly."
# define EXTENSION_ERROR "Wrong file extension."
# define INVALID_PLAYER_COUNT "Wrong number of players."

int		write_error_msg(char *error_msg);

#endif
