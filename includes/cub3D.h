/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:59:37 by sabdelra          #+#    #+#             */
/*   Updated: 2023/10/23 16:43:58 by tanas            ###   ########.fr       */
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

/* ---------------------------------- utils --------------------------------- */

/* --------------------------------- errors --------------------------------- */
int		write_error_msg(char *error_msg);

#endif
