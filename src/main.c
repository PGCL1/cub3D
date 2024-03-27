/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/27 12:16:29 by glacroix         ###   ########.fr       */
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

int player_orientation(t_player *player, char c)
{
	char *orientation[4] = {"N", "S", "E", "W"};
	int i = 0;
	while (i < 4)
	{
		if (c == orientation[i][0])
		{
			player->orientation = c;
			printf("c = %c | orientation %c\n", c, orientation[i][0]);
			return (1);	
		}
		i += 1;
	}
	return (0);
}

//maybe create player struct here
int player_check_pos(t_array *map, t_player *player)
{
	//char player[4] = {N, S, E, W};
	int count = 0;
	size_t i = 0;
	size_t j = 0;
	char *line;
	while (i < map->len - 2)
	{
		j = 0;
		line = map->items[i];
		while (j < map->items_len[i])
		{
			if (count > 1)
				exit(1);
			if (line[j] != '1' && line[j] != '0' && line[j] != ' ')
			{
				player->x = i;
				player->y = j;
				if (player_orientation(player, line[j]) != TRUE)
				{
					printf("Error: The player orientation is wrong\n");	
					exit(1);
				}
				count += 1;
			}
			j++;
		}
		i++;
	}
	return (0);
}



//TODO: norminette
//TODO: refactor player function
//TODO: refactor function parsing map
//TODO: check that argv[1] ends in .cub
//TODO: check if file exits
int main(int argc, char **argv)
{
#if 1
	atexit(ft_leaks);
	//check input
	if (argc != 2)
		return (ft_putstr_fd("Error: program needs one argument ending in \".cub\"\n", 2) ,1);
	if (ends_with(argv[1], ".cub") != TRUE)
		return (ft_putstr_fd("Error: first argument has to end with .cub\n", 2), 2);
	return 0;
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
	printf("\n");	
	
	t_player player;
	ft_memset(&player, 0, sizeof(player));
	//CHECKER
	if (map_check_borders(map) != 0)
		return (printf("Error: map was invalid\n"), 1);
	if (player_check_pos(&map, &player) != 0)
		return (printf("Error: player position invalid | player = %p\n", &player), 1);
	else
		return (printf("ALL GOOOD\n"), 42);
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


