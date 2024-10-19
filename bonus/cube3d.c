/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:46 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/19 01:48:20 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

static size_t	get_longest_line_length(char **map)
{
	size_t	max_length;
	size_t	i;
	size_t	len;

	max_length = 0;
	i = 0;
	if (map == NULL)
	{
		return (0);
	}
	while (map[i] != NULL)
	{
		len = ft_strlen(map[i]);
		if (len > max_length)
		{
			max_length = len;
		}
		i++;
	}
	return (max_length);
}

int	main_loop(t_game *game)
{
	update_game(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	maps;

	ft_check_args(ac, av);
	ft_init_map(&maps);
	ft_textures(&maps, av[1]);
	if (ft_read_map(maps.fd, maps.line, &maps) == 1)
		ft_copy_map(av[1], &maps);
	(!maps.no_texture || !maps.so_texture || !maps.we_texture || \
	!maps.ea_texture) && \
		(write(2, "Textures doesn't exist\n", \
		ft_strlen("Textures doesn't exist\n")), \
		my_malloc(0, 0), 0);
	maps.player_posx += 0.5;
	maps.player_posy += 0.5;
	maps.mapx1 = maps.height;
	maps.mapy1 = get_longest_line_length(maps.map);
	init_param(&maps, &maps.cast);
	casting(&maps, &maps.cast);
	mlx_put_image_to_window(maps.mlx_t.mlx_ptr, \
	maps.mlx_t.mlx_window, maps.mlx_t.img.mlx_img, 0, 0);
	draw_gun(&maps, "./bonus/textures/gun/0.xpm");
	init_hooks(&maps);
	mlx_loop_hook(maps.mlx_t.mlx_ptr, main_loop, &maps);
	mlx_loop(maps.mlx_t.mlx_ptr);
}
