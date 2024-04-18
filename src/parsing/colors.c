/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:01:52 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/18 20:45:15 by glacroix         ###   ########.fr       */
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
		return (ft_free(numbers), 1);
	i = -1;
	while (++i < len)
		color[i] = ft_atoi(numbers[i]);
	ft_free(numbers);
	return (0);
}
