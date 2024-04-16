/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/16 16:41:46 by glacroix         ###   ########.fr       */
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
		p->y -= 5;
	if (key == S || key == DOWN)
		p->y += 5;
	if (key == D || key == RIGHT)
		p->x += 5;
	if (key == A || key == LEFT)
		p->x -= 5;
}

int	close(int keycode)
{
	if (keycode == ESC)
		ft_exit();
	return (0);
}

//int	render_next_frame(t_setup *setup)
//{
	////	if window has been destroyed, we don't want to put the pixel ! 
	//if (setup->data.win_ptr != NULL)
		//mlx_pixel_put(setup->data.mlx_ptr, setup->data.win_ptr, 
				//h / 2, w / 2, RED);
	//mlx_put_image_to_window(&setup->data.mlx_ptr, setup->data.win_ptr, setup->data.img.img, 0, 0);
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

void game_init(t_setup *setup)
{
	setup->game.mlx_ctx = &setup->data;
	setup->game.map = &setup->map;
	setup->game.pos.x = (double)setup->player.x;
	setup->game.pos.y = (double)setup->player.y;
	setup->game.dir.x = -1.0, setup->game.dir.y = 0.0;
	setup->game.plane.x = 0.0, setup->game.plane.y = 0.66;

	setup->game.textures[0].img = setup->design.north_text.addi;
	setup->game.textures[1].img = setup->design.south_text.addi;
	setup->game.textures[2].img = setup->design.east_text.addi;
	setup->game.textures[3].img = setup->design.west_text.addi;
}

#if 1

//TODO: change t_texture to t_img
int main(int argc, char **argv)
{
//atexit(ft_leaks);
	t_setup	setup;
	int		file;

	file = check_file(argc, argv[1]);
	if (file < 0)
		return (1);
	if (setup_init(&setup, file) != 0)
	{
		free_t_array(&setup.map);
		free(setup.design.north_text.addi);
		free(setup.design.south_text.addi);
		free(setup.design.east_text.addi);
		free(setup.design.west_text.addi);
		mlx_destroy_image (setup.data.mlx_ptr, setup.data.img.img );
		free(setup.data.mlx_ptr);
		return (1);
	}
	//game init
	game_init(&setup);

	//free memory
	mlx_loop_hook(setup.data.mlx_ptr, raycast, &setup.game);
	mlx_key_hook(setup.game.mlx_ctx->win_ptr, key_hook, &setup.game);
	mlx_hook(setup.data.win_ptr, 17, 0, ft_exit, setup.data.mlx_ptr);
	mlx_hook(setup.data.win_ptr, 2, 0, close, setup.data.mlx_ptr);
	mlx_loop(setup.data.mlx_ptr);
	free_t_array(&setup.map);
	return (0);
}

#endif
