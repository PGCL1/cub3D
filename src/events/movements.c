/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:14:38 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/18 11:55:35 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movements_plane(int keycode, t_game *g)
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

void	movements_player_up(t_game *game)
{
	int	x;
	int	y;
	int	xx;
	int	yy;

	x = (int)game->pos.x;
	y = (int)game->pos.y;
	xx = (int)(game->pos.x + game->dir.x * MOVE_SPEED);
	yy = (int)(game->pos.y + game->dir.y * MOVE_SPEED);
	if (game->map->items[y][xx] == '0')
		game->pos.x += game->dir.x * MOVE_SPEED;
	if (game->map->items[yy][x] == '0')
		game->pos.y += game->dir.y * MOVE_SPEED;
}

void	movements_player_down(t_game *game)
{
	int	x;
	int	y;
	int	xx;
	int	yy;

	x = (int)game->pos.x;
	y = (int)game->pos.y;
	xx = (int)(game->pos.x + game->dir.x * MOVE_SPEED);
	yy = (int)(game->pos.y + game->dir.y * MOVE_SPEED);
	if (game->map->items[y][xx] == '0')
		game->pos.x -= game->dir.x * MOVE_SPEED;
	if (game->map->items[yy][x] == '0')
		game->pos.y -= game->dir.y * MOVE_SPEED;
}

void	movements_player_left(t_game *game)
{
	int	x;
	int	y;
	int	xx;
	int	yy;

	x = (int)game->pos.x;
	y = (int)game->pos.y;
	xx = (int)(game->pos.x - game->dir.y * MOVE_SPEED);
	yy = (int)(game->pos.y + game->dir.x * MOVE_SPEED);
	if (game->map->items[y][xx] == '0')
		game->pos.x -= game->dir.y * MOVE_SPEED;
	if (game->map->items[yy][x] == '0')
		game->pos.y += game->dir.x * MOVE_SPEED;
}

void	movements_player_right(t_game *game)
{
	int	x;
	int	y;
	int	xx;
	int	yy;

	x = (int)game->pos.x;
	y = (int)game->pos.y;
	xx = (int)(game->pos.x + game->dir.y * MOVE_SPEED);
	yy = (int)(game->pos.y - game->dir.x * MOVE_SPEED);
	if (game->map->items[y][xx] == '0')
		game->pos.x += game->dir.y * MOVE_SPEED;
	if (game->map->items[yy][x] == '0')
		game->pos.y -= game->dir.x * MOVE_SPEED;
}
