/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_of_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:12:59 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/18 06:20:52 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_error_texture(void)
{
	write(2, "Invalid Textures !!\n", ft_strlen("Invalid Textures !!\n"));
	my_malloc(0, 0);
}

void	init_textures(t_textures *textures, t_game *m)
{
	textures[0] = (t_textures){"NO", &m->NO, "Duplicate North"};
	textures[1] = (t_textures){"SO", &m->SO, "Duplicate South"};
	textures[2] = (t_textures){"WE", &m->WE, "Duplicate West"};
	textures[3] = (t_textures){"EA", &m->EA, "Duplicate East"};
	textures[4] = (t_textures){"C", &m->C, "Duplicate Ciel Color"};
	textures[5] = (t_textures){"F", &m->F, "Duplicate Floor Color"};
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
				ft_exit(textures[i].error_msg, 1);
		}
		else if (pt_ciel(m->ln, textures[i].name) >= 0)
		{
			(*textures[i].field)++;
			if (*(textures[i].field) > 1)
				ft_exit(textures[i].error_msg, 1);
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
			return (ft_error_texture(), NULL);
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
