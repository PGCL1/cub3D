/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:25:16 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/02 16:27:30 by glacroix         ###   ########.fr       */
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
		if (line_empty(line) == TRUE)
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

//typedef struct s_point
	//{
		//int	x;
		//int y;
	//}		t_point;

//void f_fill(char **tab, t_point size, char target, int row, int col)
//{
	//if (col < 0 || row < 0 || col >= size.x || row >= size.y)
		//return;
	//if (tab[row][col] == 'F' || tab[row][col] != target)
		//return;
	//tab[row][col] = 'F';
	//f_fill(tab, size, target, row + 1, col);
	//f_fill(tab, size, target, row - 1, col);
	//f_fill(tab, size, target, row, col + 1);
	//f_fill(tab, size, target, row, col - 1);
//}

//void flood_fill(char **tab, t_point size, t_point begin)
//{
	//char target = tab[begin.y][begin.x];
	//f_fill(tab, size, target, begin.y, begin.x);
//}
