/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:44:34 by tanas             #+#    #+#             */
/*   Updated: 2023/11/03 16:40:32 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

// static void print_t_map(t_map *map)
// {
// 	if (!map)
// 		return ;
// 	printf("----------GRID------------\n");
// 	for(int i =0; i < map->n_rows; i++)
// 		printf("%s", map->grid[i]);
// 	printf("\n--------TEXTURES----------\n");
// 	printf("NO_texture_fd = %d\n", map->NO_texture_fd);
// 	printf("SO_texture_fd = %d\n", map->SO_texture_fd);
// 	printf("WE_texture_fd = %d\n", map->WE_texture_fd);
// 	printf("EA_texture_fd = %d\n", map->EA_texture_fd);
// 	printf("---------COLORS-----------\n");
// 	printf("floor	[R] = %d\n", map->f_color[R]);
// 	printf("floor	[G] = %d\n", map->f_color[G]);
// 	printf("floor	[B] = %d\n", map->f_color[B]);
// 	printf("ceiling [R] = %d\n", map->c_color[R]);
// 	printf("ceiling [G] = %d\n", map->c_color[G]);
// 	printf("ceiling [B] = %d\n", map->c_color[B]);
// }

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
	t_mlx	*mlx_core;

	if (argc != 2)
		return (write_error_msg("Error: args"), -1);
	// verify argv
	mlx_core = init_mlx_core();
	mlx_core->map = map_load(argv[1]);

	for (int j = 100; j < 1000; j++) {
		for (int i = 100; i < 1000; i++) {
			my_pixel_put(&mlx_core->img, i, j, 0xFF0000);
		}
	}
	mlx_put_image_to_window(mlx_core->mlx_ptr, mlx_core->window, mlx_core->img.img_ptr, 0, 0);

	mlx_loop_hook(mlx_core->mlx_ptr, no_event, mlx_core);
	mlx_key_hook(mlx_core->window, handle_events, mlx_core);
	mlx_hook(mlx_core->window, 17, 1L << 17, close_mlx_core, mlx_core);
	mlx_loop(mlx_core->mlx_ptr);
	return (0);
}
