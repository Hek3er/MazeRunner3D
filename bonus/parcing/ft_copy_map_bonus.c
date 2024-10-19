/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:07:48 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/19 21:13:02 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	player_check(char **map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || \
				map[i][j] == 'W')
				k++;
			j++;
		}
		i++;
	}
	if (k != 1)
		(1) && (write(1, "player must be one\n", 19), my_malloc(0, 0));
}

void	find_player(t_game **maps)
{
	int	i;
	int	j;

	i = 0;
	while ((*maps)->map[i])
	{
		j = 0;
		while ((*maps)->map[i][j])
		{
			if ((*maps)->map[i][j] == 'N' || (*maps)->map[i][j] == 'W' || \
				(*maps)->map[i][j] == 'S' || (*maps)->map[i][j] == 'E')
			{
				(*maps)->orientation = (*maps)->map[i][j];
				(*maps)->player_posx = i;
				(*maps)->player_posy = j;
			}
			j++;
		}
		i++;
	}
}

void	ft_copy_map(char *av, t_game *maps)
{
	int		fd;
	int		i;
	char	*new_line;

	fd = open(av, O_RDONLY);
	(fd < 0) && (write(2, "error open\n", 11), my_malloc(0, 0));
	new_line = get_next_line(fd);
	while (new_line)
	{
		if (check_firstline(new_line) == 1)
		{
			i = 0;
			maps->map = my_malloc((sizeof(char *) * (maps->height + 1)), 1);
			while (new_line && i < maps->height)
			{
				maps->map[i] = ft_strdup(new_line);
				new_line = get_next_line(fd);
				i++;
			}
			maps->map[i] = NULL;
		}
		new_line = get_next_line(fd);
	}
	close(fd);
	return (find_player(&maps), ft_check_zeros(maps->map));
}
