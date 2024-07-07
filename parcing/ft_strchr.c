/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:31:56 by sel-jett          #+#    #+#             */
/*   Updated: 2024/07/07 16:44:30 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_strchr(const char *s, t_game *maps)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
		{
			(maps->nbs_of_players)++;
			maps->player_posx = i;
			maps->player_posy = maps->Height;
		}
		else if (s[i] != '1' && s[i] != '0')
		{
			write(2, "Error!!\n", 8);
			my_malloc(0, 0);
		}
		i++;
	}
}