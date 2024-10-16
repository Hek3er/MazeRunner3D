/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:29:42 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/17 00:42:07 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_init_map(t_game *maps)
{
	maps->number_of_players = 0;
	maps->width = 0;
	maps->height = 0;
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

char	*path_of_txr(char *line)
{
	int	i;
	int	check;
	int	save_first_index;

	check = 0;
	i = 0;
	save_first_index = 0;
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

int	path_of_txr_nm(char *line, char *texture_name)
{
	int	i;
	int	check;
	int	save_first_index;

	check = 0;
	i = 0;
	save_first_index = 0;
	while (line[i] && line[i] < 33)
		i++;
	if (line[i] && !ft_strncmp(texture_name, (const char *)(line + i), 2))
		return (i);
	return (-1);
}

int	path_of_ciel(char *line, char *texture_name)
{
	int	i;
	int	save_first_index;
	int check;

	check = 0;
	save_first_index = 0;
	i = 0;
	while (line[i] && line[i] < 33)
		i++;
	if (line[i] && !ft_strncmp(texture_name, (const char *)(line + i), 1))
		return (i);
	return (-1);
}

int	ft_contain_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 0 || line[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_return_fd(t_game *maps, char *line)
{
	int	check;

	check = 0;
	check = ((path_of_txr_nm(line, "NO") >= 0) * 1 \
		+ (path_of_txr_nm(line, "EA") >= 0) * 1 + \
		(path_of_txr_nm(line, "SO") >= 0) * 1 + \
		(path_of_txr_nm(line, "WE") >= 0) * 1 + \
		(path_of_ciel(line, "C") >= 0) * 1 + \
		(path_of_ciel(line, "F") >= 0) * 1 + \
		(ft_strcmp(line, "\n") == 1) * 1 + \
		(ft_contain_map(line) == 1) * 1);
	if (check == 0 && line && line[0])
		ft_exit("Error Textures\n", 1);
	return (1);
}

int	ft_textures(t_game *maps, char *av)
{
	maps->fd2 = open(av, O_RDONLY);
	(maps->fd2 < 0) && (write(2, "File doesn't exist\n", 19), my_malloc(0, 0), 0);
	maps->ln = get_next_line(maps->fd2);
	while (maps->ln)
	{
		if (path_of_txr_nm(maps->ln, "NO") >= 0)
			maps->no_texture = path_of_txr(maps->ln + path_of_txr_nm(maps->ln, "NO") + 2);
		else if (path_of_txr_nm(maps->ln, "SO") >= 0)
			maps->so_texture = path_of_txr(maps->ln + path_of_txr_nm(maps->ln, "SO") + 2);
		else if (path_of_txr_nm(maps->ln, "WE") >= 0)
			maps->we_texture = path_of_txr(maps->ln + path_of_txr_nm(maps->ln, "WE") + 2);
		else if (path_of_txr_nm(maps->ln, "EA") >= 0)
			maps->ea_texture = path_of_txr(maps->ln + path_of_txr_nm(maps->ln, "EA") + 2);
		else if (path_of_ciel(maps->ln, "C") >= 0)
			maps->ciel_color = ft_ciel_color(path_of_txr(maps->ln + 1 + path_of_ciel(maps->ln, "C")));
		else if (path_of_ciel(maps->ln, "F") >= 0)
			maps->floor_color = ft_ciel_color(path_of_txr(maps->ln + 1 + path_of_ciel(maps->ln, "F")));
		else if (maps->no_texture && maps->we_texture && maps->ea_texture && \
		maps->so_texture && maps->floor_color != -1 && maps->ciel_color != -1)
			return (maps->fd = maps->fd2, maps->line = maps->ln, maps->fd2);
		ft_return_fd(maps, maps->ln);
		maps->ln = get_next_line(maps->fd2);
	}
	return (-1);
}
