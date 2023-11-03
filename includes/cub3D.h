/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:59:37 by sabdelra          #+#    #+#             */
/*   Updated: 2023/11/03 16:49:59 by sabdelra         ###   ########.fr       */
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

typedef struct s_player
{
	int		x_coord;
	int		y_coord;
	char	view_direction;
}	t_player;

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
	int			n_rows;					// Current number of rows in the grid
	int			grid_capacity;			// Current capacity of the grid array.

	/* ---------------------------------- scene --------------------------------- */
	int			NO_texture_fd;			// fd for north texture file
	int			SO_texture_fd;			// fd for south texture file
	int			WE_texture_fd;			// fd for west texture file
	int			EA_texture_fd;			// fd for east texture file
	int			f_color[TOTAL_COLORS];	// floor color
	int			c_color[TOTAL_COLORS];	// cieling color

	/* --------------------------------- player --------------------------------- */
	t_player	player;
}	t_map;

t_map	*map_load(char *map_path);
bool	map_is_enclosed(t_map *map, int x, int y);

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
	void	*mlx_ptr;
	void	*window;
	t_img	img;
	t_map	*map;
}	t_mlx;

t_mlx	*init_mlx_core(void);

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

# define MALLOC_FAIL "failed to allocate memory"
# define MLX_INIT_FAIL "failed to initialize mlx"
# define MLX_WIN_FAIL "failed to start mlx window"
# define MLX_IMG_FAIL "failed to start mlx image"
# define OPEN_FAIL "failed to open file"
# define SCENE_FAIL "failed to load scene"
# define MAP_NOT_ENCLOSED "map is not en-closed"
# define COLOR_ERROR "color was not set correctly"
# define EXTENSION_ERROR "wrong file extension"

int		write_error_msg(char *error_msg);

#endif
