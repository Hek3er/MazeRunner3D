/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:29:42 by sel-jett          #+#    #+#             */
/*   Updated: 2024/07/14 22:36:14 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_init_map(t_game *maps)
{
	maps->number_of_players = 0;
	maps->Width = 0;
	maps->Height = 0;
	maps->map = NULL;
	maps->mapx = 0;
	maps->mapy = 0;
	maps->tile_s = 0;
	maps->player_posx = 0;
	maps->player_posy = 0;
	maps->orientation = '\0';
	maps->no_texture = NULL;
	maps->so_texture = NULL;
	maps->we_texture = NULL;
	maps->ea_texture = NULL;
	maps->ciel_color = -1;
	maps->floor_color = -1;
	maps->gun_anim = 0;
	maps->start_draw = 0;
	maps->end_draw = 0;
	maps->x = 0;
}

void	print_map(char **map)
{
	while (*map)
	{
		puts(*map);
		map++;
	}
	puts("done");
	my_malloc(0, 0);
}

int	ft_textures(t_game *maps, char *av)
{
	int		fd;
	char	*line;

	fd = open(av, O_RDONLY);
	(fd < 0) && (write(2, "File doesn't exist\n", 19), my_malloc(0, 0), 0);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp("NO", (const char *)line, 2))
			maps->no_texture = line + 2;
		else if (!ft_strncmp("SO", (const char *)line, 2))
			maps->so_texture = line + 2;
		else if (!ft_strncmp("WE", (const char *)line, 2))
			maps->we_texture = line + 2;
		else if (!ft_strncmp("EA", (const char *)line, 2))
			maps->ea_texture = line + 2;
		else if (!ft_strncmp("C", (const char *)line, 1))
			maps->ciel_color = ft_ciel_color(line + 2);
		else if (!ft_strncmp("F", (const char *)line, 1))
			maps->floor_color = ft_ciel_color(line + 2);
		else if (maps->no_texture && maps->we_texture && maps->ea_texture && \
			maps->so_texture  && maps->floor_color != -1 && maps->ciel_color != -1)
			return (maps->fd = fd, maps->line = line, fd);
		line = get_next_line(fd);
	}
	return (-1);
}


// int	parcing(int ac, char **av)
// {
// 	t_game	maps;

// 	ft_check_args(ac, av);
// 	ft_init_map(&maps);
// 	ft_textures(&maps, av[1]);
// 	if (ft_read_map(maps.fd, maps.line, &maps) == 1)
// 		ft_copy_map(av[1], &maps);
// 	(!maps.no_texture || !maps.so_texture || !maps.we_texture || \
// 	!maps.ea_texture) && \
// 		(write(2, "Textures doesn't exist\n", ft_strlen("Textures doesn't exist\n")), \
// 		my_malloc(0, 0), 0);
// 	while (*(maps.map))
// 	{
// 		puts(*(maps.map));
// 		(maps.map)++;
// 	}
// 		printf("-----> ore: %c\n", maps.orientation);
// 		printf("-----> player_posx: %f\n", maps.player_posx);
// 		printf("-----> player_posy: %f\n", maps.player_posy);
// }
