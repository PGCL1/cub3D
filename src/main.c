/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/05 18:20:40 by glacroix         ###   ########.fr       */
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
void	free_t_array(t_array *arr)
{
	ft_free(arr->items);
	free(arr->items_len);
}

void	*map_original_copy(t_array map, t_array *original)
{
	size_t	i;

	i = -1;
	original->len = map.len;
	original->items = malloc(sizeof(original->items) * map.len);
	if (!original->items)
		return (NULL);
	original->items_len = malloc(sizeof(original->items_len) * map.len);
	if (!original->items_len)
		return (NULL);
	while (++i < original->len)
	{
		original->items[i] = ft_strdup(map.items[i]);
		original->items_len[i] = ft_strlen(map.items[i]);
	}
	return (original);
}


void	ft_leaks(void)
{
	system("leaks -q cub3D");
}

int main(int argc, char **argv)
{
	atexit(ft_leaks);
	t_game	game;
	int		file;
	int		dir;

	if (argc != 2)
		return (error_msg("program needs one arg ending in \".cub\""),1);
	if (ends_with(argv[1], ".cub") != TRUE)
		return (error_msg("first arg has to end with .cub"), 2);
	file = open(argv[1], O_RDONLY);
	if (file < 0)
		return (error_msg("file doesn't exist"), 3);
	dir = open(argv[1], O_DIRECTORY);
	if (dir > 0)
		return (error_msg("cannot use a directory as map"), 4);
	close(dir);
	if (game_init(&game, file) != 0)
	{
		free_t_array(&game.map);
		free(game.design.north_text);
		free(game.design.south_text);
		free(game.design.east_text);
		free(game.design.west_text);
		mlx_destroy_image (game.data.mlx_ptr, game.data.img );
		free(game.data.mlx_ptr);
		return (1);
	}
	//free memory
	mlx_hook(game.data.win_ptr, 17, 0, ft_exit, game.data.mlx_ptr);
	mlx_hook(game.data.win_ptr, 2, 0, hook_key, game.data.mlx_ptr);
	mlx_loop(game.data.mlx_ptr);
	ft_free(game.map.items);
	free(game.map.items_len);
	close(file);
	return (0);
}
