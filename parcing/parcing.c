/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:29:42 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/17 01:06:10 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_init_map(t_game *mp)
{
	mp->number_of_players = 0;
	mp->width = 0;
	mp->height = 0;
	mp->map = NULL;
	mp->mapx = 0;
	mp->mapy = 0;
	mp->tile_s = 0;
	mp->player_posx = 0;
	mp->player_posy = 0;
	mp->orientation = '\0';
	mp->no_texture = NULL;
	mp->so_texture = NULL;
	mp->we_texture = NULL;
	mp->ea_texture = NULL;
	mp->ciel_color = -1;
	mp->floor_color = -1;
	mp->gun_anim = 0;
	mp->start_draw = 0;
	mp->end_draw = 0;
	mp->x = 0;
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

char	*pt_txr(char *line)
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

int	pt_ciel(char *line, char *texture_name)
{
	int	i;
	int	save_first_index;
	int	check;

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

int	ft_return_fd(t_game *mp, char *line)
{
	int	check;

	check = 0;
	check = ((path_of_txr_nm(line, "NO") >= 0) * 1 \
		+ (path_of_txr_nm(line, "EA") >= 0) * 1 + \
		(path_of_txr_nm(line, "SO") >= 0) * 1 + \
		(path_of_txr_nm(line, "WE") >= 0) * 1 + \
		(pt_ciel(line, "C") >= 0) * 1 + \
		(pt_ciel(line, "F") >= 0) * 1 + \
		(ft_strcmp(line, "\n") == 1) * 1 + \
		(ft_contain_map(line) == 1) * 1);
	if (check == 0 && line && line[0])
		ft_exit("Error Textures\n", 1);
	return (1);
}

int	ft_textures(t_game *m, char *av)
{
	m->fd2 = open(av, O_RDONLY);
	(m->fd2 < 0) && (write(2, "File doesn't exist\n", 19), my_malloc(0, 0), 0);
	m->ln = get_next_line(m->fd2);
	while (m->ln)
	{
		if (path_of_txr_nm(m->ln, "NO") >= 0)
			m->no_texture = pt_txr(m->ln + path_of_txr_nm(m->ln, "NO") + 2);
		else if (path_of_txr_nm(m->ln, "SO") >= 0)
			m->so_texture = pt_txr(m->ln + path_of_txr_nm(m->ln, "SO") + 2);
		else if (path_of_txr_nm(m->ln, "WE") >= 0)
			m->we_texture = pt_txr(m->ln + path_of_txr_nm(m->ln, "WE") + 2);
		else if (path_of_txr_nm(m->ln, "EA") >= 0)
			m->ea_texture = pt_txr(m->ln + path_of_txr_nm(m->ln, "EA") + 2);
		else if (pt_ciel(m->ln, "C") >= 0)
			m->ciel_color = ft_ciel(pt_txr(m->ln + 1 + pt_ciel(m->ln, "C")));
		else if (pt_ciel(m->ln, "F") >= 0)
			m->floor_color = ft_ciel(pt_txr(m->ln + 1 + pt_ciel(m->ln, "F")));
		else if (m->no_texture && m->we_texture && m->ea_texture && \
		m->so_texture && m->floor_color != -1 && m->ciel_color != -1)
			return (m->fd = m->fd2, m->line = m->ln, m->fd2);
		ft_return_fd(m, m->ln);
		m->ln = get_next_line(m->fd2);
	}
	return (-1);
}
