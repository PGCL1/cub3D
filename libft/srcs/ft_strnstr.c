/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:47:25 by glacroix          #+#    #+#             */
/*   Updated: 2024/02/19 16:09:49 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *_str, const char *to_find_, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*to_find;

	str = ((char *)_str);
	to_find = ((char *)to_find_);
	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != 0 && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j] != 0)
		{
			if (to_find[j + 1] == 0 && (i + j) < len)
				return (&(str[i]));
			j++;
		}
		i++;
	}
	return (NULL);
}
