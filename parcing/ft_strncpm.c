/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:56:15 by sel-jett          #+#    #+#             */
/*   Updated: 2024/10/17 01:11:08 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)*s1
		&& (unsigned char)*s1 == (unsigned char)*s2
		&& i < n)
	{
		i++;
		s1++;
		s2++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
