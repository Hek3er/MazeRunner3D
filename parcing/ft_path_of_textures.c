/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_of_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 01:12:59 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/17 01:13:55 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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
