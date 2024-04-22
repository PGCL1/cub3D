/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_layout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabourri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:16:58 by aabourri          #+#    #+#             */
/*   Updated: 2024/04/22 20:04:14 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	orientation_texture(t_game *game, int side, int tex_x, int tex_y)
{
	uint32_t	color;

	color = 0;
	if (side == 0 && game->ray_dir.x < 0)
		color = game->textures[0].data[TEXHEIGHT * tex_y + tex_x];
	else if (side == 0 && game->ray_dir.x > 0)
		color = game->textures[1].data[TEXHEIGHT * tex_y + tex_x];
	else if (side == 1 && game->ray_dir.y < 0)
		color = game->textures[2].data[TEXHEIGHT * tex_y + tex_x];
	else if (side == 1 && game->ray_dir.y > 0)
		color = game->textures[3].data[TEXHEIGHT * tex_y + tex_x];
	return (color);
}

void	render_floor_ceiling(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < game->draw_start)
	{
		if (y * WIDTH + x >= WIDTH * HEIGHT)
			break ;
		game->mlx_ctx->img.data[y * WIDTH + x] = game->floor_color;
		y++;
	}
	while (y < WIDTH)
	{
		if (y * WIDTH + x >= WIDTH * HEIGHT)
			break ;
		game->mlx_ctx->img.data[y * WIDTH + x] = game->ceiling_color;
		y++;
	}
}

void	render_texture(t_game *game, int tex_x, int side, int x)
{
	int				y;
	int				tex_y;
	uint32_t		color;
	const double	step = 1.0 * TEXHEIGHT / game->line_height;
	double			tex_pos;

	tex_pos = (game->draw_start - HEIGHT / 2 + game->line_height / 2) * step;
	y = game->draw_start;
	while (y <= game->draw_end)
	{
		tex_y = (int)tex_pos & (TEXHEIGHT - 1);
		tex_pos += step;
		color = orientation_texture(game, side, tex_x, tex_y);
		if (side == 1)
			color = (color >> 1) & 0x7f7f7f;
		if (y * WIDTH + x >= WIDTH * HEIGHT)
			break ;
		game->mlx_ctx->img.data[y * WIDTH + x] = color;
		y += 1;
	}
}

int	draw_pos(t_game **g, int side)
{
	int	line_height;

	if (side == 0)
		(*g)->prep_wall_dist = ((*g)->side_dist.x - (*g)->delta_dist.x);
	else
		(*g)->prep_wall_dist = ((*g)->side_dist.y - (*g)->delta_dist.y);
	if ((*g)->prep_wall_dist == 0.0)
		(*g)->prep_wall_dist = 0.1;
	line_height = (int)(HEIGHT / (*g)->prep_wall_dist);
	(*g)->draw_start = (int)(-line_height / 2 + HEIGHT / 2);
	if ((*g)->draw_start < 0)
		(*g)->draw_start = 0;
	(*g)->draw_end = (int)(line_height / 2 + HEIGHT / 2);
	if ((*g)->draw_end >= HEIGHT)
		(*g)->draw_end = HEIGHT - 1;
	return (line_height);
}
