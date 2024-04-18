/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:01:52 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/18 17:10:24 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*color_path(char *line)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len && ft_isspace(line[i]))
		i++;
	return (&line[i]);
}

size_t	len_matrix(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i] != NULL)
		i++;
	return (i);
}

void	init_colors(int floor[], int ceiling[])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		floor[i] = -1;
		ceiling[i] = -1;
		i++;
	}
	return ;
}

int	get_colors(char *line, int color[])
{
	size_t	i;
	size_t	len;
	char	**numbers;

	i = 1;
	len = ft_strlen(line);
	line = color_path(line);
	while (i < len && ft_isspace(line[i]))
		i++;
	numbers = ft_split(&line[i], ',');
	len = len_matrix(numbers);
	if (len > 3)
		return (1);
	i = -1;
	while (++i < len)
		color[i] = ft_atoi(numbers[i]);
	ft_free(numbers);
	return (0);
}
