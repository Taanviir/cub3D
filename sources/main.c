/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:44:34 by tanas             #+#    #+#             */
/*   Updated: 2023/11/19 17:54:59 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc != 2)
		return (write_error_msg("Error: args"), -1);

	// verify argv
	mlx = init_mlx_data(argv[1]);
	if (!mlx)
		return (-1);
	start_raycaster(mlx);

	mlx_loop_hook(mlx->mlx_ptr, no_event, mlx);
	mlx_hook(mlx->window, 2, 1L << 0, handle_events, mlx);
	mlx_hook(mlx->window, 17, 1L << 17, close_mlx, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
