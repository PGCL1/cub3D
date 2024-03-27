/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starts_with.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:50:36 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/27 16:55:30 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	starts_with(const char *str, const char *find)
{
	int		i;
	size_t	j;
	size_t	len_find;

	i = 0;
	j = -1;
	len_find = ft_strlen(find);
	if (!str || !find)
		return (0);
	while (++j < len_find && str[i])
	{
		if (find[j] != str[i])
			return (0);
		i++;
	}
	if (str[i] && str[i] == ' ')
		return (1);
	return (0);
}
