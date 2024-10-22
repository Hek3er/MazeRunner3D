/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:44:21 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/22 08:58:42 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

int	check_firstline(char *line)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '1')
			check = 1;
		else if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			return (2);
		i++;
	}
	return (check == 1);
}

static int	check_lines_inside(char *line)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (line[i])
	{
		if (check == 0 && line[i] != ' ')
		{
			if (line[i] == '1')
				check = 1;
			else
				return (0);
		}
		i++;
	}
	if (check == 0)
		return (0);
	else if (i > 0 && line[i - 1] != '1')
		return (0);
	return (1);
}

int	check_last_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		(1) && (write(2, "map error\n", 10), my_malloc(0, 0));
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1')
			(1) && (write(2, "map error\n", 10), my_malloc(0, 0));
		i++;
	}
	return (1);
}

int	ft_read_map(int fd, char *line, t_game *maps)
{
	int		check;
	char	*ex_line;

	while (line)
	{
		check = check_firstline(line);
		line = get_next_line(fd);
		if (check == 1)
			break ;
		if (!line || check == 2)
			(1) && (close(fd), write(2, "map error\n", 10), my_malloc(0, 0));
	}
	check = 1;
	ex_line = NULL;
	while (line)
	{
		if (check_lines_inside(line) == 1)
			check++;
		else
			(1) && (close(fd),write(2, "map error\n", 10), my_malloc(0, 0));
		ex_line = line;
		line = get_next_line(fd);
	}
	maps->height = check;
	return (close(fd), check_last_line(ex_line));
}
