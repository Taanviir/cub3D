/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:44:34 by tanas             #+#    #+#             */
/*   Updated: 2023/11/16 19:49:41 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int main(int argc, char **argv)
// {
// #if 1 // forming struct
// 	if (argc != 2)
// 		return -1;
// 	if (!map_extension_check(argv[1]))
// 		return -1;
// 	t_map *map = map_load(argv[1]);
// 	print_t_map(map);
// 	map_free(map);
// #endif
// #if 0 // flood_fill
// 	if (argc != 2)
// 		return -1;
// 	t_map *map = NULL;
// 	map = map_load(argv[1]);
// 	if(map_is_enclosed(map, 1, 1) == -1)
// 	{
// 		printf("Fail\n");
// 		map_free(map);
// 		return 0;
// 	}
// 	for (int i = 0; i < map->n_rows; i++)
// 	{
// 		printf("%s", map->grid[i]);
// 	}
// 	map_free(map);
// #endif
// #if 0 // parsing map
// 	if (argc != 2)
// 		return -1;
// 	t_map *map = NULL;
// 	map = map_load(argv[1]);
// 	for(int i =0; i < map->n_rows; i++)
// 		ft_printf("%s", map->grid[i]);
// 	map_free(map);
// #endif
// #if 0 // mlx_core
// 	t_mlx	*mlx_core;

// 	if (argc != 2)
// 		return (write_error_msg("Error: args"), -1);
// 	// verify argv
// 	mlx_core = init_mlx_core();
// 	mlx_loop_hook(mlx_core->mlx, no_event, mlx_core);
// 	// the no event hook, needs to be there idk why, this executes code inside the no event function in case there are no events to handle
// 	mlx_key_hook(mlx_core->window, key_hook, mlx_core); // the key hook
// 	//mlx_hook() // hook is for any general event, key_hook for example only handles key-releases, a more general form is mlx_hook
// 	mlx_loop(mlx_core->mlx); // recieves events
// #endif // 0
// }


int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	char	*map_path;

	if (argc != 2)
		return (write_error_msg("Error: args"), -1);
	map_path = argv[1];
	mlx = init_mlx_data(map_path);
	if (!mlx)
		return (-1);
	display_background(mlx);
	ray_cast(&mlx->player, mlx->map, mlx);
	mlx_loop_hook(mlx->mlx_ptr, no_event, mlx);
	mlx_hook(mlx->window, 2, 1L << 0, handle_events, mlx);
	mlx_hook(mlx->window, 17, 1L << 17, close_mlx, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
