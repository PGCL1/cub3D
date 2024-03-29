/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:08:30 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/29 16:51:49 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_color(int color[])
{
	//printf("\n");
	//printf("color[0] = %d\n", color[0]);
	//printf("color[1] = %d\n", color[1]);
	//printf("color[2] = %d\n", color[2]);
	int	i;

	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	error_design(t_design *design)
{
	//printf("\n");
	//printf("design->>north = %p\n", design->north_text);
	//printf("design->>south = %p\n", design->south_text);
	//printf("design->>west = %p\n", design->west_text);
	//printf("design->>east = %p\n", design->east_text);
	//printf("design->>floor[0] = %d\n", design->floor[0]);
	//printf("design->>floor[1] = %d\n", design->floor[1]);
	//printf("design->>floor[2] = %d\n", design->floor[2]);
	//printf("design->>ceiling[0] = %d\n", design->ceiling[0]);
	//printf("design->>ceiling[1] = %d\n", design->ceiling[1]);
	//printf("design->>ceiling[2] = %d\n", design->ceiling[2]);
	if (!design->north_text || !design->south_text
		|| !design->east_text || !design->west_text)
		return (1);
	if (error_color(design->floor) == TRUE || error_color(design->ceiling) == TRUE)
		return (1);
	return (0);
}

int	colors_textures(void *mlx, char *line, t_design *design)
{
	int	count;

	count = 0;
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
	return (count);
}

t_design	assign_design(int file, t_data *data, int *count, char *line)
{
	t_design	design;

	line = get_next_line(file);
	init_colors(design.floor, design.ceiling);
	while (line != NULL)
	{
		if (!line_meaning(line) && line_empty(line) == TRUE)
		{
			free(line);
			line = get_next_line(file);
			continue ;
		}
		else
		{
			*count += colors_textures(data->mlx_ptr, line, &design);
			if (*count == 6 || *count == -1)
			{
				free(line);
				break ;
			}
			free(line);
			line = get_next_line(file);
		}
	}
	return (design);
}
