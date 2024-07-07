/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:03:27 by sel-jett          #+#    #+#             */
/*   Updated: 2024/07/07 13:55:10 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_countt(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

void	ft_check_args(int ac, char **av)
{
	(ac != 2) && (write(2, "Invalid Arguments", 18), my_malloc(0, 0), 0);
	if (!ft_search(av[1]))
		(1) && (write(2, "Invalid file type\n", 18), my_malloc(0, 0), 0);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}


char	*ft_parser(char *av)
{
	char	*parser;
	char	*map;
	int		fd;
	char	*line;
	int		line2;

	map = NULL;
	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		parser = my_malloc(ft_countt(line) + 1, 1);
		ft_strcpy(parser, line);
		line = get_next_line(fd);
		line2 = ft_countt(line);
		(line2) && (parser = ft_strjoin(parser, "\n"));
		map = ft_strjoin(map, parser);
		if (!line2)
			break ;
	}
	close(fd);
	return (map);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while ((i + 1) < dstsize && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen((char *)src));
}