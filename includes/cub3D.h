/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:59:37 by sabdelra          #+#    #+#             */
/*   Updated: 2023/11/17 21:13:25 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* -------------------------------------------------------------------------- */
/*                                    TODO                                    */
/* -------------------------------------------------------------------------- */
// [ ] implement textures
// [ ] when starting south movement is flipped
// [ ] fix collisions, they clip
// [ ] organize this mess :)
// [ ] no magic numeros
// [ ] clean ray_caster.c

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
# include "assert.h" //! are we allowed to use assert

# ifdef __LINUX__
#  include <X11/keysym.h>
# endif

/* ----------------------------------- dda ---------------------------------- */
typedef struct s_dda
{
	double	ray[2];
	int		map_cell[2]; // the cell where the player is located
	double	delta[2]; // the distance a ray has to travel to  hit the next H or V line
	double	next_hit[2];
	double	step[2]; // how much you need to step to get to the next hit (H or V)
} t_dda;

typedef struct s_player
{
	double	position[2];
	double	direction[2];
	double	cam_plane[2];
}	t_player;

/* ----------------------------------- map ---------------------------------- */
# define MAP_INITIAL_CAPACITY 5
# define DOUBLE 2

#define ACCEPTED_CHARACTERS "10VNSWE\n " // list of valid map characters
#define PLAYER_DIRECTIONS "NSWE"
#define WALL '1'

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


t_map	*map_load(char *map_path);
t_map	*grid_validate(t_map *map, t_player *player);
/* --------------------------------- player --------------------------------- */

#define X 0 // coordinates
#define Y 1 // coordinates
#define H 0
#define V 1



/* -------------------------------- mlx core -------------------------------- */

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define WIN_TITLE "cub3D"

typedef struct s_img
{
	void	*img_ptr;
	void	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx {
	void		*mlx_ptr;
	void		*window;
	t_img		img_data;
	t_map		*map;
	t_player	player;
}	t_mlx;

t_mlx	*init_mlx_data(char *map_path);
/* ------------------------------- raycaster -------------------------------- */
#define VERY_BIG_NUMBER 453211111.0f



void	ray_cast(t_mlx *mlx);
void	display_background(t_mlx *mlx_core);

/* --------------------------------- events --------------------------------- */
#define MOVE 0.05f
#define ROTATE_ANGLE 1

int		no_event(void);
int		handle_events(int keycode, t_mlx *mlx_core);
int		close_mlx(t_mlx *mlx_core);

/* ---------------------------------- utils --------------------------------- */

void	map_free(t_map *map);
void	my_pixel_put(t_img *image, int x, int y, int color);

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
# define OPEN_FAIL "Failed to open file."
# define SCENE_FAIL "Failed to load scene."
# define MAP_NOT_ENCLOSED "Map is not en-closed."
# define MAP_INVALID_CHARACTER "Invalid character in map file."
# define COLOR_ERROR "Color was not set correctly."
# define EXTENSION_ERROR "Wrong file extension."
# define INVALID_PLAYER_COUNT "Wrong number of players."

int		write_error_msg(char *error_msg);

#endif
