/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/10 18:23:45 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_file(int argc, char *input)
{
	int	file;
	int	dir;

	if (argc != 2)
		return (error_msg("program needs one arg ending in \".cub\""), -1);
	if (ends_with(input, ".cub") != TRUE)
		return (error_msg("first arg has to end with .cub"), -1);
	file = open(input, O_RDONLY);
	if (file < 0)
		return (error_msg("file doesn't exist"), -1);
	dir = open(input, O_DIRECTORY);
	if (dir > 0)
		return (error_msg("cannot use a directory as map"), -1);
	close(dir);
	return (file);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->img_addr
		+ (y * data->img_line_length + x * (data->img_bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void game_background_draw(t_data *data, t_win *window, int color)
{
	int i = -1;
	int j = -1;

	while (++i < window->h_y)
	{
		j = 0;
		while (++j < window->w_x)
			my_mlx_pixel_put(data, j, i, color);
	}
}

void	draw_rectangle(t_data *data, t_player *player, int color)
{
	t_vector size = {64.0f, 64.0f};

	int	y = player->y;
	while (y < player->y + size.y)
	{
		int x = player->x;
		while (x < player->x + size.x)
		{
			my_mlx_pixel_put(data, x, y, color);
			x += 1;
		}
		y += 1;
	}
}

int	ft_exit(void)
{
	ft_putstr_fd("Exited 3D, ggboiiii\n", 1);
	exit(EXIT_SUCCESS);
}

void buttons(int key, t_player *p)
{
	if (key == W || key == UP)
		p->x += 5;
	if (key == S || key == DOWN)
		p->x -= 5;
	if (key == D || key == RIGHT)
		p->y += 5;
	if (key == A || key == LEFT)
		p->y -= 5;
}

int	hook_key(int keycode, t_player *p)
{
	(void)p;
	printf("keycode = %d\n", keycode);
	if (keycode == ESC)
		ft_exit();
	buttons(keycode, p);
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

void	ft_leaks(void)
{
	system("leaks -q cub3D");
}



#if 1

int main(int argc, char **argv)
{
//atexit(ft_leaks);
	t_game	game;
	int		file;

	file = check_file(argc, argv[1]);
	if (file < 0)
		return (1);
	if (game_init(&game, file) != 0)
	{
		free_t_array(&game.map);
		free(game.design.north_text.addi);
		free(game.design.south_text.addi);
		free(game.design.east_text.addi);
		free(game.design.west_text.addi);
		mlx_destroy_image (game.data.mlx_ptr, game.data.img );
		free(game.data.mlx_ptr);
		return (1);
	}
	printf("player.x = %d | player.y = %d\n", game.player.x, game.player.y);
	//raycast
	//game_background_draw(&game.data, &game.window, GREY);
	//draw_rectangle(&game.data, &game.player, RED);	
	//mlx_put_image_to_window(&game.data.mlx_ptr, game.data.win_ptr, game.data.img, 0, 0);
	
	//free memory
	mlx_hook(game.data.win_ptr, 17, 0, ft_exit, game.data.mlx_ptr);
	mlx_hook(game.data.win_ptr, 2, 0, hook_key, game.data.mlx_ptr);
	mlx_loop(game.data.mlx_ptr);
	free_t_array(&game.map);
	return (0);
}

#endif
