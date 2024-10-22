/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_of_textures_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:12:59 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/22 08:57:43 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

void	ft_error_texture(void)
{
	write(2, "Invalid file Texture Name!!\n", \
	ft_strlen("Invalid file Texture Name!!\n\n"));
	my_malloc(0, 0);
}

void	init_textures(t_textures *textures, t_game *m)
{
	textures[0] = (t_textures){"NO", &m->no, "Duplicate North\n"};
	textures[1] = (t_textures){"SO", &m->so, "Duplicate South\n"};
	textures[2] = (t_textures){"WE", &m->we, "Duplicate West\n"};
	textures[3] = (t_textures){"EA", &m->ea, "Duplicate East\n"};
	textures[4] = (t_textures){"C", &m->c, "Duplicate Ciel Color\n"};
	textures[5] = (t_textures){"F", &m->f, "Duplicate Floor Color\n"};
	textures[6] = (t_textures){NULL, NULL, NULL};
}

char	*ft_check_duplicate(t_game *m, char *line, int save_first_index)
{
	int			i;
	t_textures	textures[7];

	init_textures(textures, m);
	i = 0;
	while (textures[i].name)
	{
		if (path_of_txr_nm(m->ln, textures[i].name) >= 0)
		{
			(*textures[i].field)++;
			if (*(textures[i].field) > 1)
				return (close(m->fd2), ft_exit(textures[i].error_msg, 1), NULL);
		}
		else if (pt_ciel(m->ln, textures[i].name) >= 0)
		{
			(*textures[i].field)++;
			if (*(textures[i].field) > 1)
				return (close(m->fd2), ft_exit(textures[i].error_msg, 1), NULL);
		}
		i++;
	}
	return (line + save_first_index);
}

char	*pt_txr(t_game *m, char *line)
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
			return (close(m->fd2), ft_error_texture(), NULL);
		i++;
	}
	return (ft_check_duplicate(m, line, save_first_index));
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
