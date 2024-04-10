/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:57 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/10 13:00:43 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>
#include <stdlib.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480


int WidthScreen = 1024;
int HeightScreen = 512;

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

//posX and posY represent the position vector of the player
//dirX and dirY represent the direction of the player
//planeX and planeY the camera plane of the player.
//The ratio between the length of the direction and the camera plane determinates the FieldOfVision

#if 1
int main(int argc, char *argv[])
{

	t_game game;
	
	if (window_init(&game.data) == 1)
		return (1);
	
	//loops
	mlx_hook(game.data.win_ptr, 17, 0, ft_exit, game.data.mlx_ptr);
	mlx_hook(game.data.win_ptr, 2, 0, hook_key, game.data.mlx_ptr);
	mlx_loop(game.data.mlx_ptr);
  
}

#endif
