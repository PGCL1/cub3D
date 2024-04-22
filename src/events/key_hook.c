/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:55:58 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/18 11:24:43 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_close(void)
{
	ft_putstr_fd("Exited 3D, ggboiiii\n", 1);
	exit(EXIT_SUCCESS);
}


static void	movements_plane(int keycode, t_game *g)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == KEY_ARROW_RIGHT)
	{
		old_dir_x = g->dir.x;
		g->dir.x = g->dir.x * cos(-RO_SPEED) - g->dir.y * sin(-RO_SPEED);
		g->dir.y = old_dir_x * sin(-RO_SPEED) + g->dir.y * cos(-RO_SPEED);
		old_plane_x = g->plane.x;
		g->plane.x = g->plane.x * cos(-RO_SPEED) - g->plane.y * sin(-RO_SPEED);
		g->plane.y = old_plane_x * sin(-RO_SPEED) + g->plane.y * cos(-RO_SPEED);
	}
	if (keycode == KEY_ARROW_LEFT)
	{
		old_dir_x = g->dir.x;
		g->dir.x = g->dir.x * cos(RO_SPEED) - g->dir.y * sin(RO_SPEED);
		g->dir.y = old_dir_x * sin(RO_SPEED) + g->dir.y * cos(RO_SPEED);
		old_plane_x = g->plane.x;
		g->plane.x = g->plane.x * cos(RO_SPEED) - g->plane.y * sin(RO_SPEED);
		g->plane.y = old_plane_x * sin(RO_SPEED) + g->plane.y * cos(RO_SPEED);
	}
}

static void	movements_player_up_down(t_game *game, int keycode)
{
	const int x = (int)game->pos.x;
	const int y = (int)game->pos.y;
	const int xx = (int)(game->pos.x + game->dir.x * MOVE_SPEED);
	const int yy = (int)(game->pos.y + game->dir.y * MOVE_SPEED);

	if (keycode == W)
	{
		if (game->map->items[y][xx] != '1')
			game->pos.x += game->dir.x * MOVE_SPEED;
		if (game->map->items[yy][x] != '1')
			game->pos.y += game->dir.y * MOVE_SPEED;
	}
	if (keycode == S)
	{
		if (game->map->items[y][xx] != '1')
			game->pos.x -= game->dir.x * MOVE_SPEED;
		if (game->map->items[yy][x] != '1')
			game->pos.y -= game->dir.y * MOVE_SPEED;
	}
}

static void	movements_player_left_right(t_game *game, int keycode)
{
	const int x = (int)game->pos.x;
	const int y = (int)game->pos.y;
	const int xx = (int)(game->pos.x - game->dir.y * MOVE_SPEED);
	const int yy = (int)(game->pos.y + game->dir.x * MOVE_SPEED);

	if (keycode == A)
	{
		if (game->map->items[y][xx] != '1')
			game->pos.x -= game->dir.y * MOVE_SPEED;
		if (game->map->items[yy][x] != '1')
			game->pos.y += game->dir.x * MOVE_SPEED;
	}
	if (keycode == D)
	{
		if (game->map->items[y][xx] != '1')
			game->pos.x += game->dir.y * MOVE_SPEED;
		if (game->map->items[yy][x] != '1')
			game->pos.y -= game->dir.x * MOVE_SPEED;
	}
}


int	key_press(int keycode, t_game *game)
{
	printf("keycode = %d\n", keycode);
	if (keycode == ESC)
		game_close();
	movements_plane(keycode, game);
	movements_player_up_down(game, keycode);
	movements_player_left_right(game, keycode);
	return (1);
}
