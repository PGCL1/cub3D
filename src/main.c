/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/04 16:20:11 by glacroix         ###   ########.fr       */
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



int	test_fill(t_array *map, int y, int x, char c, int *flag)
{
	if ((y > (int)map->len || y < 0 || x >= (int)map->items_len[y]) || (map->items[y][x] != '1' && map->items[y][x] != '0' && map->items[y][x] != '\0' && map->items[y][x] != 'X' && map->items[y][x] != c))
		return (*flag = 1, printf("ERROR| [%d][%d] = %c\n", x, y, map->items[y][x]), 1);
	if ((map->items[y][x] == c || map->items[y][x] == '0') && *flag == 0)
	{

		map->items[y][x] = 'X';
		test_fill(map, y + 1, x, c, flag);
		test_fill(map, y - 1, x, c, flag);
		test_fill(map, y, x + 1, c, flag);
		test_fill(map, y, x - 1, c, flag);
	}
	else
		return (1);
		//return (printf(" 1 [%d][%d]", j, i), 1);
	return *flag;	
}

void	ft_leaks(void)
{
	system("leaks -q cub3D");
}

//TODO: figure out what to do with whitespaces in map
int main(int argc, char **argv)
{
#if 1
	//atexit(ft_leaks);
	//check input
	if (argc != 2)
		return (error_msg("program needs one argument ending in \".cub\""),1);
	if (ends_with(argv[1], ".cub") != TRUE)
		return (error_msg("first argument has to end with .cub"), 2);
	int file = open(argv[1], O_RDONLY);
	if (file < 0)
		return (error_msg("file doesn't exist"), 3);
	int dir = open(argv[1], O_DIRECTORY);
	if (dir > 0)
		return (error_msg("cannot use a directory as map"), 4);

	//window initialization
	t_data	data;
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (error_msg("mlx_init() failed"), 1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 300, "GG boiii");
	data.img = mlx_new_image(data.mlx_ptr, 600, 300);
	data.img_addr = mlx_get_data_addr(data.img, &data.img_bits_per_pixel, &data.img_line_length,
			&data.img_endian);

	//copying textures
	int count = 0;
	char *line = NULL;
	t_design test = assign_design(file, &data, &count, line);
	if (error_design(&test) == TRUE || count == -1)
	{
		//free image, window and mlx
		close(file);
		close(dir);
		return (error_msg("textures and colors were wrong"), 1);
	}

	//copying map
	t_array	map  = ms_array_init();
	map_assign(&map, file);
	//for (size_t i = 0; i < map.len; i++)
		//printf("len = %lu | %s", map.items_len[i], map.items[i]);
	//printf("\n");	

	//map_error_check
	if (map_check_borders(map) != 0)
	{
		ft_free(map.items);
		free(map.items_len);	
		return (error_msg("map was invalid"), 1);
	}
	
	//player_check
	t_player player;
	ft_memset(&player, 0, sizeof(player));
	if (player_init(&player, map) == 1)
		return (1);
	if (player.x == 0 && player.y == 0)
		return (error_msg("the map has to have a player"), 1);

	//it's the final boss: is the map closed
	int flag = 0;
	//t_array original = map_original_copy(map);
	//printf("ori = %p | map = %p\n", original.items[0], map.items[0]);
	//return (0);
	if (test_fill(&map, player.y, player.x, player.orientation, &flag) == 1)
		return (error_msg("map is not closed"), 1);

	printf("\n");	
	for (size_t i = 0; i < map.len; i++)
		printf("len = %lu | %s", map.items_len[i], map.items[i]);
	printf("\n");	
	//free memory
	mlx_hook(data.win_ptr, 17, 0, ft_exit, data.mlx_ptr);
	mlx_hook(data.win_ptr, 2, 0, hook_key, data.mlx_ptr);
	mlx_loop(data.mlx_ptr);
	ft_free(map.items);
	close(file);
	return (0);


#else




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
