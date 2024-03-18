/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:47:48 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 16:13:14 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	length;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	length = ft_strlen(start + s);
	if (length < len)
		len = length;
	s1 = malloc(len + 1);
	if (!s1)
		return (NULL);
	ft_strlcpy(s1, (s + start), (len + 1));
	return (s1);
}
