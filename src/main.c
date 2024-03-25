/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/25 11:50:27 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->img_addr + (y * data->img_line_length + x * (data->img_bits_per_pixel / 8));
	*(unsigned int*)pixel = color;
}


int ft_exit()
{
	ft_putstr_fd("Exited 3D, ggboiiii\n", 1);
	exit(EXIT_SUCCESS);
}

int hook_key(int keycode)
{
	printf("keycode = %d\n", keycode);
	if (keycode == ESC)
		ft_exit();
	return (0);
}

//int	render(t_data *data)
//{
    ///* if window has been destroyed, we don't want to put the pixel ! */
    //if (data->win_ptr != NULL)
        //mlx_pixel_put(data->mlx_ptr, data->win_ptr, 
            //WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, RED_PIXEL);
    //return (0);
//}
void ft_leaks()
{
	system("leaks -q cub3D");
}


int change_map(t_array *copy)
{
	size_t i = 0;
	size_t j = 0;
	size_t real_len = copy->len - 2;
	while (i <= real_len)
	{
		j = 0;
		while (copy->items[i][j] != '\n' && copy->items[i][j] != '\0')
		{
			if (copy->items[i][j] == ' ')
				copy->items[i][j] = '1';
			j++;	
		}
		printf("real_len = %lu | j = %lu\n", real_len, j);
		//ms_array_append_len(&map, len);
		i++;
	}
	return (0);
}




int map_checker(t_array copy)
{
	size_t i = 0;
	size_t j = 0;
	size_t real_len = copy.len - 2;
	printf("%d\n",change_map(&copy));
	for (size_t a = 0; a < real_len; a++)
		printf("line[%lu] = %s | \t\t\t\t\t\tlen = %lu\n", a + 1, copy.items[a], copy.items_len[a]);
	while (i <= real_len)
	{
		j = 0;
		size_t line_len = copy.items_len[i] - 2;
		while (copy.items[i][j] != '\n' && copy.items[i][j] != '\0')
		{
			if (i == real_len && j == line_len)
				break;
			//top row is filled with 1
			if (copy.items[0][j] != '1')
				return (printf("1 problem at [0][%lu]\n", j), 1);
			//bottom row is all 1s
			if (copy.items[real_len][j] != '1')
				return (printf("2 problem at [%lu][%lu] = `%c`\n", real_len + 1, j, copy.items[real_len][j]), 1);
			//pos[0] of each row are 1s
			if (copy.items[i][0] != '1')
				return (printf("3 problem at [%lu][%lu]\n", i, j), 1);
			//last colums are all 1s
			if (copy.items[i][(int)line_len] != '1')
				return (printf("4 problem at [%lu][%lu]\n", i, line_len), 1);
			j++;	
		}
		i++;
	}
	return (0);
}




//TODO: check that argv[1] ends in .cub
int main(int argc, char **argv)
{
#if 1
//	atexit(ft_leaks);
	//check input
	if (argc != 2)
		return (ft_putstr_fd("Error: program needs one argument ending in \".cub\"\n", 2) ,1);
	
	//copying map
	t_array	map;
	int file = open(argv[1], O_RDONLY);
	map = ms_array_init();
	char *line = get_next_line(file);
	while (line != NULL)
	{
		ms_array_append(&map, line);
		line = get_next_line(file);
	}
	ms_array_append(&map, NULL);
	for (size_t i = 0; i < map.len; i++)
		printf("len = %lu | %s", map.items_len[i], map.items[i]);
	exit(1);

	//map_checker
	int err = map_checker(map);
	if (err != 0)
		return (printf("Error: map was invalid\n"), 1);
	else
		return (printf("All GOOD!"), 0);

	//free memory
	ft_free(map.items);
	return 0;

#else
	t_data	data;

	//window initialization
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (ft_putstr_fd("Error: mlx_init() failed", 2), 1);
		data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 300, "GG boiii");
		data.img = mlx_new_image(data.mlx_ptr, 600, 300);
		data.img_addr = mlx_get_data_addr(data.img, &data.img_bits_per_pixel, &data.img_line_length,
				&data.img_endian);

	//printing pixels to image in window
	for (int x = 0; x < 600; x++)
	{
		for (int y = 0; y < 300; y++)	
			my_mlx_pixel_put(&data, x, y, RED);
	}
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);

	//keyhooks
	mlx_hook(data.win_ptr, 17, 0, ft_exit, data.mlx_ptr);
	mlx_hook(data.win_ptr, 2, 0, hook_key, data.mlx_ptr);
	mlx_loop(data.mlx_ptr);
	return (0);
#endif
}


