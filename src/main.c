/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/29 13:38:03 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->img_addr
		+ (y * data->img_line_length + x * (data->img_bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

int	ft_exit(void)
{
	ft_putstr_fd("Exited 3D, ggboiiii\n", 1);
	exit(EXIT_SUCCESS);
}

int	hook_key(int keycode)
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
void	ft_leaks(void)
{
	system("leaks -q cub3D");
}

int	player_orientation(t_player *player, char c)
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
					error_msg("player orientation is wrong");	
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

//NOTES:	first copy textures + check
//			second copy colors  + check
//			third copy map      + check

//TODO: norminette
//TODO: refactor player function
//TODO: refactor function parsing map
//TODO: error function directly to stderr and in red

int main(int argc, char **argv)
{
#if 1
	//atexit(ft_leaks);
	//check input
	if (argc != 2)
		return (error_msg("program needs one argument ending in \".cub\""),1);
	return (0);
	if (ends_with(argv[1], ".cub") != TRUE)
		return (error_msg("first argument has to end with .cub"), 2);
	int file = open(argv[1], O_RDONLY);
	if (file < 0)
		return (error_msg("file doesn't exist"), 3);
	int dir = open(argv[1], O_DIRECTORY);
	if (dir > 0)
		return (error_msg("cannot use a directory as map"), 4);
	
	t_data	data;

	//window initialization
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (error_msg("mlx_init() failed"), 1);
		data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 300, "GG boiii");
		data.img = mlx_new_image(data.mlx_ptr, 600, 300);
		data.img_addr = mlx_get_data_addr(data.img, &data.img_bits_per_pixel, &data.img_line_length,
				&data.img_endian);

	//copying textures
	char *line = get_next_line(file);
	t_design test;
	while (line != NULL)
	{
		printf("result = %s | empty = %d | line = `%s", line_meaning(line), line_empty(line), line);
		//if line_meaning == NULL && line_empty == TRUE => free line and pass to next line
		if (!line_meaning(line) && line_empty(line) == TRUE)
		{
			free(line);
			line = get_next_line(file);
			continue;	
		}
		else
		{

			int count = colors_textures(&data.mlx_ptr, line, &test);
			if (count == 6 || count == -1)
			{
				free(line);	
				break;
			}
			free(line);
			line = get_next_line(file);
		}
	}
	//if (count == -1)
		////free memory?
	//printf("NORTH = %p\n", test.north_text);
	//printf("SOUTH = %p\n", test.south_text);
	//printf("EAST = %p\n", test.east_text);
	//printf("WEST = %p\n", test.west_text);
	printf("test.floor[0] = %d\n", test.floor[0]);
	printf("test.floor[1] = %d\n", test.floor[1]);
	printf("test.floor[2] = %d\n", test.floor[2]);
	printf("test.ceiling[0] = %d\n", test.ceiling[0]);
	printf("test.ceiling[1] = %d\n", test.ceiling[1]);
	printf("test.ceiling[2] = %d\n", test.ceiling[2]);
	printf("line = %s", get_next_line(file));
	printf("line = %s", get_next_line(file));
	printf("line = %s", get_next_line(file));
	mlx_hook(data.win_ptr, 17, 0, ft_exit, data.mlx_ptr);
	mlx_hook(data.win_ptr, 2, 0, hook_key, data.mlx_ptr);
	//mlx_loop(data.mlx_ptr);
	close(file);
	return (0);










#else


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
