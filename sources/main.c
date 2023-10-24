/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:44:34 by tanas             #+#    #+#             */
/*   Updated: 2023/10/25 03:29:19 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

int main(int argc, char **argv)
{
#if 1 // parsing map
	if (argc != 2)
		return -1;
	t_map *map = NULL;
	map = load_map(argv[1]);
	for(int i =0; i < map->n_rows; i++)
		ft_printf("%s", map->grid[i]);
	free_map(map);
#endif

#if 0 // mlx_core
	t_mlx	*mlx_core;

	mlx_core = init_mlx_core();
	mlx_loop_hook(mlx_core->mlx, no_event, mlx_core);
	// the no event hook, needs to be there idk why, this executes code inside the no event function in case there are no events to handle
	mlx_key_hook(mlx_core->window, key_hook, mlx_core); // the key hook
	//mlx_hook() // hook is for any general event, key_hook for example only handles key-releases, a more general form is mlx_hook
	mlx_loop(mlx_core->mlx); // recieves events
#endif // 0
}



