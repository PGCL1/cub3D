/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:12 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 16:04:22 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	i;
	size_t	x;

	j = 0;
	i = 0;
	x = ft_strlen((char *)src);
	while (dst[j] && j < dstsize)
		j++;
	while (src[i] && i + j + 1 < dstsize)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (i != 0)
		dst[i + j] = 0;
	return (x + j);
}
