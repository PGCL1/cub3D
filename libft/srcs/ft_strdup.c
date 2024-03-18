/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:11:48 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 16:02:08 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char			*string;
	unsigned int	len;

	len = ft_strlen((char *)s1);
	string = malloc(len + 1);
	if (!string)
		return (0);
	ft_memcpy(string, s1, len);
	string[len] = '\0';
	return (string);
}
