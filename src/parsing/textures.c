/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:37:05 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/29 13:04:16 by glacroix         ###   ########.fr       */
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

void	*get_texture(void *mlx, char *line)
{
	size_t	i;
	size_t	len;
	int		width;
	int		height;
	void	*texture;
	char	*path_no_newline;

	len = ft_strlen(line);
	line = texture_path(line);
	i = 2;
	while (i < len && ft_isspace(line[i]))
		i++;
	path_no_newline = ft_strtrim(&line[i], "\n");
	texture = mlx_xpm_file_to_image(mlx, path_no_newline, &width, &height);
	free(path_no_newline);
	return (texture);
}

int	colors_textures(void *mlx, char *line, t_design *design)
{
	static int	count = 0; //line is empty and count < 6;
	if (!line_meaning(line) && line_empty(line) == FALSE)
		return (-1);
	else
	{
		if (ft_strncmp((char *)line_meaning(line), "NO", 3) == 0)
			design->north_text = get_texture(mlx, line);
		else if (ft_strncmp((char *)line_meaning(line), "SO", 3) == 0)
			design->south_text = get_texture(mlx, line);
		else if (ft_strncmp((char *)line_meaning(line), "WE", 3) == 0)
			design->west_text = get_texture(mlx, line);
		else if (ft_strncmp((char *)line_meaning(line), "EA", 3) == 0)
			design->east_text = get_texture(mlx, line);
		else if (ft_strncmp((char *)line_meaning(line), "F", 2) == 0)
			get_colors(line, design->floor);
		else if (ft_strncmp((char *)line_meaning(line), "C", 2) == 0)
			get_colors(line, design->ceiling); 
		count += 1;
	}
	printf("count = %d\n", count);
	return (count);
}
//count +=1;
//printf("count = %d\n", count);
