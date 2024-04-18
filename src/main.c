/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/18 17:10:22 by glacroix         ###   ########.fr       */
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

int	ft_exit(void)
{
	ft_putstr_fd("Exited 3D, ggboiiii\n", 1);
	exit(EXIT_SUCCESS);
}

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
	int	i;

	i = -1;
	setup->game.mlx_ctx = &setup->data;
	setup->game.map = &setup->map;
	setup->game.pos.x = (double)setup->player.x;
	setup->game.pos.y = (double)setup->player.y;
	//don't forget player direction N || W || S || E
	setup->game.dir.x = -1.0, setup->game.dir.y = 0.0;
	setup->game.plane.x = 0.0, setup->game.plane.y = 0.66;

	while (++i < 4)
		setup->game.textures[i] = setup->design.textures[i];
}

static void free_objects(int err, t_setup *s)
{
	int	i;

	i = -1;
	if (err >= 1)
	{
		mlx_destroy_image(s->data.mlx_ptr, s->data.img.img);
		mlx_destroy_window(s->data.mlx_ptr, s->data.win_ptr);
	}
	if (err >= 2)
	{
		while (++i < 4)
		{
			if (s->design.textures[i].valid)
				mlx_destroy_image(s->data.mlx_ptr, s->design.textures[i].img);
		}
	}
	if (err >= 3)
		free_t_array(&s->map);
	free(s->data.mlx_ptr);
}


#if 1
int main(int argc, char **argv)
{
	atexit(ft_leaks);
	t_setup	setup;
	int		file;
	int		err_init;

	file = check_file(argc, argv[1]);
	if (file < 0)
		return (1);
	err_init = setup_init(&setup, file);
	if (err_init != 0)
	{
		free_objects(err_init, &setup);
		return (1);
	}
	//game init
	game_init(&setup);

	
	//hooks
	mlx_loop_hook(setup.data.mlx_ptr, raycast, &setup.game);
	mlx_hook(setup.data.win_ptr, 17, 0, ft_exit, setup.data.mlx_ptr);

	//keyhooks
	mlx_hook(setup.data.win_ptr, 2, 0, &key_press, &setup.game);
	
	//window loop
	mlx_loop(setup.data.mlx_ptr);
	

	//remember to free memory
	free_t_array(&setup.map);
	return (0);
}

#endif
