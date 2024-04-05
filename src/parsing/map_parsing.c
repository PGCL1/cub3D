/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:25:16 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/05 19:49:16 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_error(char *item, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (item[i] == '1' || item[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int	map_check_borders(t_array copy)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 1;
	if (line_error(copy.items[0], copy.items_len[0]) == 1)
		return (1);
	if (line_error(copy.items[copy.len - 2], copy.items_len[copy.len - 2]) == 1)
		return (1);
	while (i < copy.len - 2)
	{
		j = 0;
		len = copy.items_len[i] - 1;
		while (j < copy.items_len[i] && ft_isspace(copy.items[i][j]))
			j++;
		if (j < copy.items_len[i] && copy.items[i][j] != '1')
			return (1);
		if (copy.items[i][len] != '1')
			return (1);
		i++;
	}
	return (0);
}

void map_assign(t_array *map, int file)
{
	char	*line;

   	line = get_next_line(file);
	while (line != NULL)
	{
		if (line_empty(line) == TRUE && map->len == 0)
		{
			free(line);
			line = get_next_line(file);
			continue;
		}
		ms_array_append(map, line);
		line = get_next_line(file);
	}
	ms_array_append(map, NULL);
}


int	map_fill(t_array *map, int y, int x, int *flag)
{
	if ((y > (int)map->len || y < 0 || x >= (int)map->items_len[y])
		|| (map->items[y][x] != '1' && map->items[y][x] != '0'
				&& map->items[y][x] != '\0' && map->items[y][x] != 'X'
				&& map->items[y][x] != 'N' && map->items[y][x] != 'S'
				&& map->items[y][x] != 'W' && map->items[y][x] != 'E'))
		return (*flag = 1, 1);
	if (((map->items[y][x] != 'N' && map->items[y][x] != 'S'
		&& map->items[y][x] != 'W' && map->items[y][x] != 'E')
				|| map->items[y][x] == '0') && *flag == 0)
	{
		map->items[y][x] = 'X';
		map_fill(map, y + 1, x, flag);
		map_fill(map, y - 1, x, flag);
		map_fill(map, y, x + 1, flag);
		map_fill(map, y, x - 1, flag);
	}
	else
		return (1);
	return (*flag);
}
