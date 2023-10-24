/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:59:37 by sabdelra          #+#    #+#             */
/*   Updated: 2023/10/25 03:31:28 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* -------------------------------- includes -------------------------------- */
# include <mlx.h>
# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include "keycodes.h"

# ifdef __LINUX__
#  include <X11/keysym.h>
# endif

/* ----------------------------- error messages ----------------------------- */
# define MALLOC_FAIL "failed to allocate memory"
# define MLX_INIT_FAIL "failed to initialize mlx"
# define MLX_WIN_FAIL "failed to start mlx window"
# define MAP_FAIL "failed to open map"

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

// TODO
// [ ] validate
// [ ] clean-up error handling
typedef struct s_map
{
	char			**grid;
	int				n_rows;
	int				__row_capacity;
} t_map;

t_map	*load_map(char *map_path);
void	free_map(t_map *map);
/* ---------------------------------- utils --------------------------------- */

/* --------------------------------- errors --------------------------------- */
// return 0 on error
int		write_error_msg(char *error_msg);

#endif
