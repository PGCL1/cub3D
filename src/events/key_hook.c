/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:55:58 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/17 13:17:09 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_close(void)
{
	ft_putstr_fd("Exited 3D, ggboiiii\n", 1);
	exit(EXIT_SUCCESS);
}

int	key_press(int keycode, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	if (keycode == ESC)
		game_close();
	if (keycode == KEY_ARROW_RIGHT)
	{
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(-ROT_SPEED) - game->dir.y * sin(-ROT_SPEED);
		game->dir.y = old_dir_x * sin(-ROT_SPEED) + game->dir.y * cos(-ROT_SPEED);

		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(-ROT_SPEED) - game->plane.y * sin(-ROT_SPEED);
		game->plane.y = old_plane_x * sin(-ROT_SPEED) + game->plane.y * cos(-ROT_SPEED);
	}
	if (keycode == KEY_ARROW_LEFT)
	{
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(ROT_SPEED) - game->dir.y * sin(ROT_SPEED);
		game->dir.y = old_dir_x * sin(ROT_SPEED) + game->dir.y * cos(ROT_SPEED);

		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(ROT_SPEED) - game->plane.y * sin(ROT_SPEED);
		game->plane.y = old_plane_x * sin(ROT_SPEED) + game->plane.y * cos(ROT_SPEED);
	}
	if (keycode == KEY_ARROW_UP)
	{
		int	x = (int)game->pos.x;
		int	y = (int)game->pos.y;
		int	xx = (int)(game->pos.x + game->dir.x * MOVE_SPEED);
		int	yy = (int)(game->pos.y + game->dir.y * MOVE_SPEED);

		if (game->map->items[y][xx] == '0')
			game->pos.x += game->dir.x * MOVE_SPEED;
	 	if (game->map->items[yy][x] == '0')
			game->pos.y += game->dir.y * MOVE_SPEED;
	}
	if (keycode == KEY_ARROW_DOWN)
	{
		int	x = (int)game->pos.x;
		int	y = (int)game->pos.y;
		int	xx = (int)(game->pos.x + game->dir.x * MOVE_SPEED);
		int	yy = (int)(game->pos.y + game->dir.y * MOVE_SPEED);

		if (game->map->items[y][xx] == '0')
			game->pos.x -= game->dir.x * MOVE_SPEED;
	 	if (game->map->items[yy][x] == '0')
			game->pos.y -= game->dir.y * MOVE_SPEED;
		
	}
	return 1;
}
