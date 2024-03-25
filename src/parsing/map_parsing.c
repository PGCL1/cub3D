/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:25:16 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/25 17:50:19 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int line_error(char *item, size_t len)
{
	size_t i = 0;
	while (i < len)
	{
		if (item[i] == '1' || item[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int map_check_borders(t_array copy)
{
	size_t i = 1;
	size_t j = 0;
	//top and bottom line check
	if (line_error(copy.items[0], copy.items_len[0]) == 1)
		return (1);
	if (line_error(copy.items[copy.len - 2], copy.items_len[copy.len - 2]) == 1)
		return (1);
	while (i < copy.len - 2)
	{
		size_t len = copy.items_len[i] - 1; 
		j = 0;
		while (j < copy.items_len[i] && ft_isspace(copy.items[i][j]))
			j++;
		if (j < copy.items_len[i] && copy.items[i][j] != '1')
			return (printf("1|| %lu 0 len = %lu | line = %s",i, copy.items_len[i], copy.items[i]), 1);
		if (copy.items[i][len] != '1')
			return (printf("error at %lu %lu %c\n", i, len, copy.items[i][len]), 1);
		i++;
	}
	return (0);
}
