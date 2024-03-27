/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:27:18 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/27 11:52:24 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

int	ends_with(const char *str, const char *find)
{
	int		len_find;
	size_t	len_str;

	if (!str || !find)
		return (0);
	len_str = ft_strlen(str);
	len_find = ft_strlen(find);
	while (--len_find != -1)
	{
		if (find[len_find] != str[len_str - 1])
			return (0);
		len_str--;
	}
	return (1);
}
