/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:44:34 by tanas             #+#    #+#             */
/*   Updated: 2023/11/17 20:12:39 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_mlx	*mlx_core;

	if (argc != 2)
		return (write_error_msg("Error: args"), -1);

	// verify argv
	mlx_core = init_mlx_core(argv[1]);
	if (!mlx_core)
		return (-1);
	start_raycaster(mlx_core);

	mlx_loop_hook(mlx_core->mlx_ptr, no_event, mlx_core);
	mlx_hook(mlx_core->window, 2, 1L << 0, handle_events, mlx_core);
	mlx_hook(mlx_core->window, 17, 1L << 17, close_mlx_core, mlx_core);
	mlx_loop(mlx_core->mlx_ptr);
	return (0);
}
