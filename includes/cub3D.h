/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:59:37 by sabdelra          #+#    #+#             */
/*   Updated: 2023/11/29 01:36:58y sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* -------------------------------------------------------------------------- */
/*                                    TODO                                    */
/* -------------------------------------------------------------------------- */

// [ ] norminette
// [ ] clean ray_caster.c
// [-] no magic numeros
// [x] validating texture path
// [x] player spawns in wall segfault, EW
	// [x] directions inverted for EW
// [x] double free on multiple players
// [-] fix error handling in map.c:225

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

/* ----------------------------------- dda ---------------------------------- */

#define X 0 // coordinates
#define Y 1 // coordinates
#define STEP 2 // texel step
#define COLOR 3 // texel color
#define H 0 // horizontal
#define V 1 // vertical

// hit side determines the texture to load
typedef enum {
	NO = 0,
	WE,
	EA,
	SO,
	TOTAL_TEXTURES
} e_texture;
typedef struct s_dda
{
	double		ray[2];
	int			map_cell[2]; // the cell where the player is located
	double		delta[2]; // the distance a ray has to travel to  hit the next H or V line
	double		next_hit[2];
	double		step[2]; // how much you need to step to get to the next hit (H or V)
	double		distance_to_wall;
	e_texture		hit;
	e_texture		side[2]; // 2 textures either horizontal or vertical
} t_dda;

typedef struct s_player
{
	double	position[2];
	double	direction[2];
	double	camera_plane[2];
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
	char	*texture[TOTAL_TEXTURES];
	int		f_color[TOTAL_COLORS];	// floor color
	int		c_color[TOTAL_COLORS];	// ceiling color
}	t_map;


t_map	*map_load(char *map_path);
t_map	*grid_validate(t_map *map, t_player *player);

/* -------------------------------- mlx core -------------------------------- */

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define WIN_TITLE "cub3D"

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		img_width;
	int		img_height;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx {
	void		*mlx_ptr;
	void		*window;
	t_img		textures[TOTAL_TEXTURES];
	t_img		img_data;
	t_map		*map;
	t_player	player;
}	t_mlx;

t_mlx	*init_mlx_data(char *map_path);
/* ------------------------------- raycaster -------------------------------- */

typedef enum {
	TOP = 0,
	BOT,
	HEIGHT
} e_slice;

#define VERY_BIG_NUMBER 453211111.0f

void	ray_cast(t_mlx *mlx);
// void	__display_background(t_mlx *mlx_core);

/* --------------------------------- events --------------------------------- */
#define MOVE 0.05f
#define ROTATE_ANGLE 2

typedef enum e_movement {
	ANGLE = 0,
	SIN,
	COS
}t_movement;

int		no_event(void);
int		handle_events(int keycode, t_mlx *mlx_core);
int		close_mlx(t_mlx *mlx_core);

/* ---------------------------------- utils --------------------------------- */

void	map_free(t_map *map);

/* ------------------------------- debug utils ------------------------------ */

// void	print_t_map(t_map *map); //? for debugging only

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
# define TEXTURE_FAIL "Failed to load texture"
# define INVALID_ARGS "invalid number of args"

int		write_error_msg(char *error_msg);

#endif
