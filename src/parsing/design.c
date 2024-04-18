/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:08:30 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/18 20:34:24 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_color(int color[])
{
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
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (design->textures[i].valid == FALSE)
			return (1);
	}
	if (error_color(design->floor) == TRUE
			|| error_color(design->ceiling) == TRUE)
		return (1);
	return (0);
}

//TODO: i don't like the -10 to exit the loop, it's ugly
int	colors_textures(void *mlx, char *line, t_design *design)
{
	int	count;

	count = 0;
	if (!line_meaning(line) && line_empty(line) == FALSE)
		return (-10);
	else
	{
		if (ft_strncmp((char *)line_meaning(line), "NO", 3) == 0)
			get_texture(mlx, line, &design->textures[0]);
		else if (ft_strncmp((char *)line_meaning(line), "SO", 3) == 0)
			get_texture(mlx, line, &design->textures[1]);
		else if (ft_strncmp((char *)line_meaning(line), "WE", 3) == 0)
			 get_texture(mlx, line, &design->textures[2]);
		else if (ft_strncmp((char *)line_meaning(line), "EA", 3) == 0)
			 get_texture(mlx, line, &design->textures[3]);
		else if (ft_strncmp((char *)line_meaning(line), "F", 2) == 0)
			get_colors(line, design->floor);
		else if (ft_strncmp((char *)line_meaning(line), "C", 2) == 0)
			get_colors(line, design->ceiling);
		count += 1;
	}
	return (count);
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
			if (*count == 6 || *count < 0)
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
