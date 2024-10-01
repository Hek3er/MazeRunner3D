/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:29:42 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/01 16:20:54 by sel-jett         ###   ########.fr       */
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

void	ft_error_texture(void)
{
	write(2, "Invalid Textures !!\n", ft_strlen("Invalid Textures !!\n"));
	my_malloc(0, 0);
}

char *path_of_texture(char *line)
{
	int i = 0;
	int save_first_index = 0;
	
	int check = 0;
	while (line[i])
	{
		if (!check && line[i] >= 33)
		{
			save_first_index = i;
			check++;
		}
		else if (line[i] >= 33)
			check++;
		else if (check && line[i] < 33)
			return (ft_error_texture(), NULL);
		i++;
	}
	return (line + save_first_index);
}

int path_of_texture_name(char *line, char *texture_name)
{
	int i = 0;
	int save_first_index = 0;
	
	int check = 0;
	while (line[i] && line[i] < 33)
		i++;
	if (line[i] && !ft_strncmp(texture_name, (const char *)(line + i), 2))
		return (i);
	return (-1);
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
		if (path_of_texture_name(line, "NO") >= 0)
			maps->no_texture = path_of_texture(line + path_of_texture_name(line, "NO") + 2);
		else if (path_of_texture_name(line, "SO") >= 0)
			maps->so_texture = path_of_texture(line + path_of_texture_name(line, "SO") + 2);
		else if (path_of_texture_name(line, "WE") >= 0)
			maps->we_texture = path_of_texture(line + path_of_texture_name(line, "WE") + 2);
		else if (path_of_texture_name(line, "EA") >= 0)
			maps->ea_texture = path_of_texture(line + path_of_texture_name(line, "EA") + 2);
		else if (!ft_strncmp("C", (const char *)line, 1))
			maps->ciel_color = ft_ciel_color(path_of_texture(line + 2));
		else if (!ft_strncmp("F", (const char *)line, 1))
			maps->floor_color = ft_ciel_color(path_of_texture(line + 2));
		else if (maps->no_texture && maps->we_texture && maps->ea_texture && \
			maps->so_texture  && maps->floor_color != -1 && maps->ciel_color != -1)
			return (maps->fd = fd, maps->line = line, fd);
		line = get_next_line(fd);
	}
	return (-1);
}