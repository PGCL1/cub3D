/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:01:52 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/28 18:37:40 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3d.h"
#include <stdio.h>
#include "../../libft/libft.h"

char *color_path(char *line)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len && ft_isspace(line[i]))
		i++;
	return (&line[i]);
}

size_t len_matrix(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i] != NULL)
		i++;
	return (i);
}


int get_colors(char *line, int fc_color[3])
{
	size_t	i;
	size_t	len;
	char 	**numbers;

	i = 1;
	len = ft_strlen(line);
	line = color_path(line);
	while (i < len && ft_isspace(line[i]))
		i++;
   	numbers	= ft_split(&line[i], ',');
	len = len_matrix(numbers);
	if (len > 3)
		return (1);
	i = 0;
	while (i < len)
	{
		fc_color[i] = ft_atoi(numbers[i]);
		printf("%d\n", fc_color[i]);
		if (fc_color[i] < 0 || fc_color[i] > 255)
		{
			ft_free(numbers);	
			return (1);
		}
		i++;
	}
	ft_free(numbers);	
	return (0);
}

//int main()
//{
	//int num[3];
	//get_colors("                                  F 2100, 2, 4", num);
	//printf("num[0] = %d\n", num[0]);
	//printf("num[1] = %d\n", num[1]);
	//printf("num[2] = %d\n", num[2]);
	//return (0);
//}
