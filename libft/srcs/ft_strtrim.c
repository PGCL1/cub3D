/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:47:24 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 16:10:58 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *_s, char const *cut)
{
	char	*s;
	size_t	size;

	s = ((char *)_s);
	if (!_s || !cut)
		return (NULL);
	while (*s && ft_strchr(cut, *s))
		s++;
	size = ft_strlen(s);
	while (size && ft_strrchr(cut, s[size]))
		size--;
	return (ft_substr(s, 0, size + 1));
}
