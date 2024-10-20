/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:57:24 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/19 21:28:05 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

static int	ft_myhelper(const char *str, int i, int signe)
{
	size_t	old;
	size_t	new;

	new = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		old = new;
		new *= 10;
		if ((new / 10) != old && signe == 1)
			return (-1);
		if ((new / 10) != old && signe == -1)
			return (0);
		new += (str[i] - '0');
		i++;
	}
	return (new * signe);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		signe;

	i = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	return (ft_myhelper(str, i, signe));
}
