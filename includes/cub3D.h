/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:59:37 by sabdelra          #+#    #+#             */
/*   Updated: 2023/11/06 01:22:38 by tanas            ###   ########.fr       */
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
	char		**grid;					// Dynamic array of strings to represent the grid.
	int			n_rows;					// Current number of rows in the grid.
	int			grid_capacity;			// Current capacity of the grid array.

	/* ---------------------------------- scene --------------------------------- */
	int			NO_texture_fd;			// fd for north texture file
	int			SO_texture_fd;			// fd for south texture file
	int			WE_texture_fd;			// fd for west texture file
	int			EA_texture_fd;			// fd for east texture file
	int			f_color[TOTAL_COLORS];	// floor color
	int			c_color[TOTAL_COLORS];	// ceiling color
}	t_map;

t_map	*map_load(char *map_path);
bool	map_is_enclosed(t_map *map, int x, int y);

/* --------------------------------- player --------------------------------- */

# define CELL_SIZE 64
# define PLAYER_SIZE 32
# define X_OFFSET 400
# define Y_OFFSET 100

typedef struct s_player
{
	int		x_pos;
	int		y_pos;
	char	view_direction;
}	t_player;

/* -------------------------------- mlx core -------------------------------- */

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "cub3D"

typedef struct s_img
{
	void	*img_ptr;
	void	*addr;
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

t_mlx	*init_mlx_core(char *map_path);

/* ------------------------------- raycaster -------------------------------- */

void	start_raycaster(t_mlx *mlx_core);

/* --------------------------------- events --------------------------------- */

int		no_event(void);
int		handle_events(int keycode, t_mlx *mlx_core);
int		close_mlx_core(t_mlx *mlx_core);

/* ---------------------------------- utils --------------------------------- */

bool	map_extension_check(char *map_path);
void	map_free(t_map *map);
void	my_pixel_put(t_img *image, int x, int y, int color);

/* -------------------------------------------------------------------------- */
/*                               error handling                               */
/* -------------------------------------------------------------------------- */

/* ------------------------------- return codes ------------------------------ */

# define SUCCESS 1
# define FAILURE 0
# define NOT_SET -1 // error code to handle failing during color

/* ----------------------------- error messages ----------------------------- */

# define MALLOC_FAIL "Failed to allocate memory."
# define MLX_INIT_FAIL "Failed to initialize mlx."
# define MLX_WIN_FAIL "Failed to start mlx window."
# define MLX_IMG_FAIL "Failed to create mlx image."
# define OPEN_FAIL "Failed to open file."
# define SCENE_FAIL "Failed to load scene."
# define MAP_NOT_ENCLOSED "Map is not en-closed."
# define COLOR_ERROR "Color was not set correctly."
# define EXTENSION_ERROR "Wrong file extension."
# define INVALID_MAP_ERROR "Invalid character in map file."

int		write_error_msg(char *error_msg);

#endif
