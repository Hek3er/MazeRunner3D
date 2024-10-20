/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_zeros.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 02:10:21 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/19 01:41:11 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	is_not_player(char **map, int i, int j)
{
	if ((map[i][j - 1] != '0' && (map[i][j - 1] != '1') && \
		map[i][j - 1] != 'S' && map[i][j - 1] != 'N' && \
		map[i][j - 1] != 'W' && map[i][j - 1] != 'E') || \
		(map[i - 1][j] != '0' && map[i - 1][j] != '1' && \
		map[i - 1][j] != 'S' && map[i - 1][j] != 'N' && \
		map[i - 1][j] != 'W' && map[i - 1][j] != 'E') || \
		(map[i][j + 1] != '0' && map[i][j + 1] != '1' && \
		map[i][j + 1] != 'S' && map[i][j + 1] != 'N' && \
		map[i][j + 1] != 'W' && map[i][j + 1] != 'E') || \
		(map[i + 1][j] != '0' && map[i + 1][j] != '1' && \
		map[i + 1][j] != 'S' && map[i + 1][j] != 'N' && \
		map[i + 1][j] != 'W' && map[i + 1][j] != 'E'))
	{
		(1) && (write(2, "error map\n", 10), my_malloc(0, 0));
	}
}

void	ft_check_zeros(char **map)
{
	int	i;
	int	j;

	i = 0;
	player_check(map);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || \
				map[i][j] == 'E')
				map[i][j] = '0';
			if (map[i][j] == '0')
				is_not_player(map, i, j);
			j++;
		}
		i++;
	}
}
