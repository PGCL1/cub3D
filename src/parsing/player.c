/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:50:12 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/22 19:48:03 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	orientation(char c, char *player_orientation)
{
	int			i;
	const char	orientation[4] = {'N', 'S', 'W', 'E'};

	i = 0;
	while (i < 4)
	{
		if (c == orientation[i])
		{
			*player_orientation = c;
			return (1);
		}
		i++;
	}
	return (0);
}

void	player_position(t_player *player, int i, int j)
{
	player->x = j;
	player->y = i;
}

int	player_start(t_player *player, const t_array map)
{
	size_t		i;
	size_t		j;
	int			count;

	i = -1;
	count = 0;
	while (++i < map.len)
	{
		j = -1;
		while (++j < map.items_len[i])
		{
			if (map.items[i][j] != '1' && map.items[i][j] != '0'
					&& map.items[i][j] != ' ')
			{
				count += 1;
				if (count > 1)
					return (1);
				player_position(player, i, j);
				if (orientation(map.items[i][j], &player->orientation) == FALSE)
					return (1);
				map.items[i][j] = '0';
			}
		}
	}
	return (count == 0);
}
