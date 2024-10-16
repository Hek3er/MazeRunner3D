/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 04:56:46 by azainabi          #+#    #+#             */
/*   Updated: 2024/10/16 22:03:54 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

size_t get_longest_line_length(char **map) {
    size_t max_length = 0;
    if (map == NULL) {
        return 0;
    }
    for (size_t i = 0; map[i] != NULL; i++) {
        size_t len = ft_strlen(map[i]);
        if (len > max_length) {
            max_length = len;
        }
    }
    return max_length;
}

int main_loop(t_game *game)
{
    update_game(game);
    return 0;
}

void f(void)
{
	system("leaks cub3D");
}

int main(int ac, char **av)
{
	t_game	maps;

	atexit(f);
	ft_check_args(ac, av);
	ft_init_map(&maps);
	ft_textures(&maps, av[1]);
	if (ft_read_map(maps.fd, maps.line, &maps) == 1)
		ft_copy_map(av[1], &maps);
	(!maps.no_texture || !maps.so_texture || !maps.we_texture || \
	!maps.ea_texture) && \
		(write(2, "Textures doesn't exist\n", ft_strlen("Textures doesn't exist\n")), \
		my_malloc(0, 0), 0);
		printf("-----> ore: %c\n", maps.orientation);
		printf("-----> mapx : %d, mapy : %d\n", maps.mapx, maps.mapy);
		printf("-----> player_posx: %f\n", maps.player_posx);
		printf("-----> player_posy: %f\n", maps.player_posy);
		printf("-----> no_texture: %s\n", maps.no_texture);
		printf("-----> so_texture: %s\n", maps.so_texture);
		printf("-----> we_texture: %s\n", maps.we_texture);
		printf("-----> ea_texture: %s\n", maps.ea_texture);
	
	maps.player_posx += 0.5;
	maps.player_posy += 0.5;
	maps.mapx1 = maps.height;
	maps.mapy1 = get_longest_line_length(maps.map);
	init_param(&maps, &maps.cast);
	casting(&maps, &maps.cast);
	mlx_put_image_to_window(maps.mlx_t.mlx_ptr, maps.mlx_t.mlx_window, maps.mlx_t.img.mlx_img, 0, 0);
	draw_gun(&maps, "./textures/gun/0.xpm");
	init_hooks(&maps);
	mlx_loop_hook(maps.mlx_t.mlx_ptr, main_loop, &maps);
	mlx_loop(maps.mlx_t.mlx_ptr);
}
