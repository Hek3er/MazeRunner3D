/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azainabi <azainabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:28:13 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/19 21:28:05 by azainabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d_bonus.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen((char *)s1);
	str = my_malloc((sizeof(char) * (size + 1)), 1);
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
