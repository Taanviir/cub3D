/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:59:37 by sabdelra          #+#    #+#             */
/*   Updated: 2023/10/27 17:02:00 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* -------------------------------- includes -------------------------------- */
# include <mlx.h>
# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "keycodes.h"

# ifdef __LINUX__
#  include <X11/keysym.h>
# endif


/* -------------------------------- mlx core -------------------------------- */
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "cub3D"

/* ---------------------------------- keys --------------------------------- */
typedef struct s_mlx {
	void	*mlx;
	void	*window;
}	t_mlx;

t_mlx	*init_mlx_core();

/* --------------------------------- events --------------------------------- */
int		no_event(void);
int		key_hook(int keycode, t_mlx *mlx_core);
int		close_mlx(t_mlx *mlx_core);

/* ----------------------------------- map ---------------------------------- */
# define MAP_INITIAL_CAPACITY 10
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

	char			**grid;					// Dynamic array of strings to represent the grid.
	int				n_rows;					// Current number of rows in the grid
	int				grid_capacity;			// Current capacity of the grid array.

	/* ---------------------------------- scene --------------------------------- */
	int				NO_texture_fd;			// path to north texture
	int				SO_texture_fd;			// path to south texture
	int				WE_texture_fd;			// path to west texture
	int				EA_texture_fd;			// path to east texture
	int				f_color[TOTAL_COLORS];	// floor color
	int				c_color[TOTAL_COLORS];	// cieling color

	/* --------------------------------- player --------------------------------- */
	int				x;						// player starting x-coordinate
	int				y;						// player starting y-coordinate
} t_map;

t_map	*map_load(char *map_path);
void	map_free(t_map *map);
bool	map_is_enclosed(t_map *map, int x, int y);
/* ---------------------------------- utils --------------------------------- */

/* -------------------------------------------------------------------------- */
/*                               error handling                               */
/* -------------------------------------------------------------------------- */

/* ------------------------------- return codes ------------------------------ */

# define SUCCESS 1
# define FAILURE 0
/* ----------------------------- error messages ----------------------------- */

# define MALLOC_FAIL "failed to allocate memory"
# define MLX_INIT_FAIL "failed to initialize mlx"
# define MLX_WIN_FAIL "failed to start mlx window"
# define OPEN_FAIL "failed to open file"
# define SCENE_FAIL "failed to load scene"
# define MAP_NOT_ENCLOSED "map is not en-closed"

int		write_error_msg(char *error_msg);

#endif
