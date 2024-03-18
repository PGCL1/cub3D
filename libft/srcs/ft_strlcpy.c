/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:57:35 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 16:05:31 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	x;
	size_t	j;
	size_t	y;

	x = 0;
	y = ft_strlen((char *)src);
	while (src[x] != 0)
		x++;
	if (dstsize != 0)
	{
		j = 0;
		while ((j + 1) < dstsize && src[j] != '\0')
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = '\0';
	}
	return (y);
}
