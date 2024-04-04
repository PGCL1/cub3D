/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:37:05 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/04 14:50:06 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*line_meaning(char *line)
{
	const char	*options[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (j < 6)
	{
		if (starts_with(&line[i], options[j]) == TRUE)
			return (options[j]);
		j++;
	}
	return (NULL);
}

int	line_empty(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (TRUE);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (TRUE);
	return (FALSE);
}

char	*texture_path(char *line)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len && ft_isspace(line[i]))
		i++;
	return (&line[i]);
}

char	*texture_path_cleaned(char *line)
{
	size_t	i;
	size_t	len;
	char	*path_no_newline;
	//char	*path_no_space;
	
	len = ft_strlen(line);
	line = texture_path(line);
	i = 2;
	while (i < len && ft_isspace(line[i]))
		i++;
	//path_no_space = ft_strtrim(&line[i], " \n");
	path_no_newline = ft_strtrim(&line[i], "\n");
	//free(path_no_space);
	return (path_no_newline);
}

void	*get_texture(void *mlx, char *line)
{
	int		width;
	int		height;
	void	*texture;
	char	*path_cleaned;

	path_cleaned = texture_path_cleaned(line);
	texture = mlx_xpm_file_to_image(mlx, path_cleaned, &width, &height);
	free(path_cleaned);
	return (texture);
}
