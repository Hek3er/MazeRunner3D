/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:31:52 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/22 09:24:22 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_checker(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	ft_search(char *str)
{
	char	ptr[5];
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	ptr[0] = '.';
	ptr[1] = 'c';
	ptr[2] = 'u';
	ptr[3] = 'b';
	ptr[4] = '\0';
	while (str[i])
	{
		if (str[i] == '.')
		{
			j = i;
			while (str[j] && ptr[k] && str[j] == ptr[k])
				(j++) && (k++);
			if (k == 4 && !str[j])
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_check_files(t_game *m)
{
	int	fd;

	fd = open(m->no_texture, O_RDONLY);
	if (fd < 0)
		ft_exit(ft_strjoin(m->no_texture, "error\n"), 1);
	fd = open(m->so_texture, O_RDONLY);
	if (fd < 0)
		ft_exit(ft_strjoin(m->so_texture, "error\n"), 1);
	fd = open(m->we_texture, O_RDONLY);
	if (fd < 0)
		ft_exit(ft_strjoin(m->we_texture, "error\n"), 1);
	fd = open(m->ea_texture, O_RDONLY);
	if (fd < 0)
		ft_exit(ft_strjoin(m->ea_texture, "error\n"), 1);
}
