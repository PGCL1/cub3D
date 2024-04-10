/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:13:20 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/10 16:23:09 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int window_init(t_data *data, t_win *window)
{
	window->h_y = 512;
	window->w_x = 1024;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (error_msg("mlx_init() failed"), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, window->w_x, window->h_y, "GG boiii");
	data->img = mlx_new_image(data->mlx_ptr, window->w_x, window->h_y);
	data->img_addr = mlx_get_data_addr(data->img, &data->img_bits_per_pixel, &data->img_line_length,
			&data->img_endian);
	return (0);
}

int design_init(t_design *design, t_data *data, int file)
{
	char	*line;	
	int		count;

	line = NULL;
	count = 0;
	*design = assign_design(file, data, &count, line);
	if (error_design(design) == TRUE || count == -1)
	{
		//free image, window and mlx
		close(file);
		return (error_msg("wrong textures or colors"), 1);
	}
	return (0);
}

int map_init(t_array *map, int file)
{
	*map = ms_array_init();
	map_assign(map, file);
	if (map_check_borders(*map) != 0)
	{
		ft_free(map->items);
		free(map->items_len);	
		return (error_msg("invalid map"), 1);
	}
	close(file);
	return (0);
}

int player_init(t_player *player, const t_array *map)
{
	ft_memset(player, 0, sizeof(player));
	if (player_start(player, *map) == 1)
		return (1);
	if (player->x == 0 && player->y == 0)
		return (error_msg("the map has to have a player"), 1);
	return (0);	
}

int	game_init(t_game *game, int file)
{
	int			flag;
	t_array		original;

	flag = 0;
	if (window_init(&game->data, &game->window) != 0)
		return (1);
	if (design_init(&game->design, &game->data, file) != 0)
		return (1);
	if (map_init(&game->map, file) != 0)
		return (1);
	if (player_init(&game->player, &game->map) != 0)
		return (1);
	if (map_original_copy(game->map, &original) == NULL)
		return (1);
	if (map_fill(&game->map, game->player.y, game->player.x, &flag) == 1)
	{
		free_t_array(&original);
		return (error_msg("map is not closed"), 1);
	}
	free_t_array(&game->map);
	game->map = original;	
	printf("game->map = %p | original = %p\n", &game->map, &original);
	return (0);	
}
