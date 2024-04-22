/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:13:20 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/22 19:48:31 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_init(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (error_msg("mlx_init() failed"), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "GG boiii");
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.data = (uint32_t *)mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel,
			&data->img.size_line, &data->img.endian);
	return (0);
}

int	design_init(t_design *design, t_data *data, int file)
{
	char	*line;	
	int		count;

	line = NULL;
	count = 0;
	*design = assign_design(file, data, &count, line);
	if (error_design(design) == TRUE || count < 0)
	{
		close(file);
		return (error_msg("wrong textures or colors"), 1);
	}
	return (0);
}

int	map_init(t_array *map, int file)
{
	*map = ms_array_init();
	map_assign(map, file);
	if (map_check_borders(*map) != 0)
	{
		ft_free(map->items);
		free(map->items_len);
		close(file);
		return (error_msg("invalid map"), 1);
	}
	close(file);
	return (0);
}

int	player_init(t_player *player, const t_array *map)
{
	ft_memset(player, 0, sizeof(player));
	if (player_start(player, *map) == 1)
		return (1);
	if (player->x == 0 && player->y == 0)
		return (error_msg("the map has to have a player"), 1);
	return (0);
}

int	setup_init(t_setup *setup, int file)
{
	int			flag;
	t_array		original;

	flag = 0;
	if (window_init(&setup->data) != 0)
		return (1);
	if (design_init(&setup->design, &setup->data, file) != 0)
		return (2);
	if (map_init(&setup->map, file) != 0)
		return (3);
	if (player_init(&setup->player, &setup->map) != 0)
		return (error_msg("player problem"), 4);
	if (map_original_copy(setup->map, &original) == NULL)
		return (5);
	if (map_fill(&original, setup->player.y, setup->player.x, &flag) == 1)
	{
		free_t_array(&original);
		return (error_msg("map is not closed"), 6);
	}
	free_t_array(&original);
	return (0);
}
