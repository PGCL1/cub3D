/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:26:32 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/22 18:34:48 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(int argc, char *input)
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
	{
		close(file);
		close(dir);
		return (error_msg("cannot use a directory as map"), -1);
	}
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

/* void	ft_leaks(void)
{
	//system("leaks -groupByType -fullContent -outputGraph aa cub3D");
	system("leaks -q cub3D");
} */

void	set_orientation(t_vector *dir, t_vector *plane, char or)
{
	int				i;
	const char		ors[4] = {'W', 'E', 'N', 'S'};
	const double	values[4][4] = {
	{0, -1, 0.66, 0},
	{0, 1, -0.66, 0},
	{-1, 0, 0, -0.66},
	{1, 0, 0, 0.66},
	};

	i = -1;
	while (++i < 4)
	{
		if (ors[i] == or)
		{
			dir->x = values[i][0];
			dir->y = values[i][1];
			plane->x = values[i][2];
			plane->y = values[i][3];
			break ;
		}
	}
}

void	game_init(t_setup *s)
{
	int	i;

	i = -1;
	s->game.mlx_ctx = &s->data;
	s->game.map = &s->map;
	s->game.pos.x = (double)s->player.x;
	s->game.pos.y = (double)s->player.y;
	set_orientation(&s->game.dir, &s->game.plane, s->player.orientation);
	s->game.floor_color = (s->design.floor[0] << 16)
		| (s->design.floor[1] << 8) | s->design.floor[2];
	s->game.ceiling_color = (s->design.ceiling[0] << 16)
		| (s->design.ceiling[1] << 8) | s->design.ceiling[2];
	while (++i < 4)
		s->game.textures[i] = s->design.textures[i];
}

static void	free_objects(int err, t_setup *s)
{
	int	i;

	i = -1;
	if (err >= 3)
		free_t_array(&s->map);
	if (err >= 2)
	{
		while (++i < 4)
		{
			if (s->design.textures[i].valid)
				mlx_destroy_image(s->data.mlx_ptr, s->design.textures[i].img);
		}
	}
	if (err >= 1)
	{
		mlx_destroy_image(s->data.mlx_ptr, s->data.img.img);
		mlx_destroy_window(s->data.mlx_ptr, s->data.win_ptr);
	}
	exit(1);
}

int	main(int argc, char **argv)
{
	t_setup		setup;
	int			file;
	int			err_init;

	file = check_file(argc, argv[1]);
	if (file < 0)
		return (1);
	err_init = setup_init(&setup, file);
	if (err_init != 0)
	{
		free_objects(err_init, &setup);
		return (1);
	}
	game_init(&setup);
	mlx_loop_hook(setup.data.mlx_ptr, raycast, &setup.game);
	mlx_hook(setup.data.win_ptr, 17, 0, ft_exit, setup.data.mlx_ptr);
	mlx_hook(setup.data.win_ptr, 2, 0, &key_press, &setup.game);
	mlx_loop(setup.data.mlx_ptr);
	mlx_do_sync(setup.data.mlx_ptr);
	free_t_array(&setup.map);
	return (0);
}
