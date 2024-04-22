/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:55:58 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/22 18:35:25 by glacroix         ###   ########.fr       */
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
	if (keycode == ESC)
		game_close();
	movements_plane(keycode, game);
	if (keycode == W)
		movements_player_up(game);
	if (keycode == S)
		movements_player_down(game);
	if (keycode == A)
		movements_player_left(game);
	if (keycode == D)
		movements_player_right(game);
	return (1);
}
