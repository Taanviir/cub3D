/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanas <tanas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:01:24 by tanas             #+#    #+#             */
/*   Updated: 2023/12/09 16:01:32 by tanas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	char	*map_path;

	if (argc != 2)
		return (write_error_msg(INVALID_ARGS));
	map_path = argv[1];
	mlx = init_mlx_data(map_path);
	if (!mlx)
		return (-1);
	ray_cast(mlx);
	mlx_loop_hook(mlx->mlx_ptr, no_event, mlx);
	mlx_hook(mlx->window, 2, 1L << 0, handle_events, mlx);
	mlx_hook(mlx->window, 17, 1L << 17, close_mlx, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
