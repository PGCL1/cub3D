/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:48:07 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/20 19:42:03 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_or_not(t_game **game)
{
	int	side;
	int	hit_wall = 0;
	char	c;

	while (!hit_wall)
	{
		if ((*game)->side_dist.x < (*game)->side_dist.y)
		{
			(*game)->side_dist.x += (*game)->delta_dist.x;
			(*game)->map_x += (*game)->step_x;
			side = 0;
		}
		else
		{
			(*game)->side_dist.y += (*game)->delta_dist.y;
			(*game)->map_y += (*game)->step_y;
			side = 1;
		}

		c = (*game)->map->items[(*game)->map_y][(*game)->map_x];
		if (c != '0')
			hit_wall = 1;
		else
			hit_wall = 0;
	}
	return side;
}

void	side_distance(t_game **g, t_vector *ray_dir)
{
	if (ray_dir->x < 0)
	{
		(*g)->step_x = -1;
		(*g)->side_dist.x = ((*g)->pos.x - (*g)->map_x) * (*g)->delta_dist.x;
	}
	else
	{
		(*g)->step_x = 1;
		(*g)->side_dist.x = ((*g)->map_x + 1.0 - (*g)->pos.x) * (*g)->delta_dist.x;
	}

	if (ray_dir->y < 0)
	{
		(*g)->step_y = -1;
		(*g)->side_dist.y = ((*g)->pos.y - (*g)->map_y) * (*g)->delta_dist.y;
	}
	else
	{
		(*g)->step_y = 1;
		(*g)->side_dist.y = ((*g)->map_y + 1.0 - (*g)->pos.y) * (*g)->delta_dist.y;
	}
}

void	distance(t_game **game, t_vector *ray_dir)
{
	if (ray_dir->x == 0)
		(*game)->delta_dist.x = 1e30;
	else
		(*game)->delta_dist.x = fabs(1.0 / ray_dir->x);
	if (ray_dir->y == 0)
		(*game)->delta_dist.y = 1e30;
	else
		(*game)->delta_dist.y = fabs(1.0 / ray_dir->y);
	side_distance(game, ray_dir);
}

int	draw_pos(t_game **game, int side)
{
	int	line_height;

	if (side == 0)
		(*game)->prep_wall_dist = ((*game)->side_dist.x - (*game)->delta_dist.x);
	else
		(*game)->prep_wall_dist = ((*game)->side_dist.y - (*game)->delta_dist.y);
	line_height = (int)(h / (*game)->prep_wall_dist);
	(*game)->draw_start = (int)(-line_height / 2 + h / 2);
	if ((*game)->draw_start < 0)
		(*game)->draw_start = 0;
	(*game)->draw_end = (int)(line_height / 2 + h / 2);
	if ((*game)->draw_end >= h)
		(*game)->draw_end = h - 1;
	return line_height;
}

void render_floor_ceiling(t_game *game, int x)
{
	int y;

	y = 0;
	while (y < game->draw_start)
	{
		if (y * w + x >= w * h)
			break;
		game->mlx_ctx->img.data[y * w + x] = game->ceiling_color;
		y++;
	}
 	while (y < w)
 	{
		if (y * w + x >= w * h)
			break;
 		game->mlx_ctx->img.data[y * w + x] = game->floor_color;
 		y++;
 	}
}

void	render_texture(t_game *game, int tex_x, int side, int tex_num, int x)
{
	int	y;
	int	tex_y;
	uint32_t	color;
	const double step = 1.0 * texHeight / game->line_height;
	double tex_pos = (game->draw_start - h / 2 + game->line_height / 2) * step;

	y = game->draw_start;
	(void) tex_num;
	(void) side;
	while (y <= game->draw_end)
	{
		tex_y = (int)tex_pos & (texHeight - 1);
		tex_pos  += step;
		color = game->textures[0].data[texHeight * tex_y + tex_x];
		if (side == 1)
			color = (color >> 1) & 0x7f7f7f;
		game->mlx_ctx->img.data[y * w + x] = color;
		y += 1;
	}
}

int	raycast(t_game *game)
{
	double camerax;	
	t_vector ray_dir;

	mlx_clear_window(game->mlx_ctx->mlx_ptr, game->mlx_ctx->win_ptr);
	printf("dir(%lf, %lf)\n", game->dir.x, game->dir.y);
	for (int x = 0; x < w; x += 1)
	{
		camerax = 2 * x / (double)w - 1;
		ray_dir.x = game->dir.x + game->plane.x * camerax;
		ray_dir.y = game->dir.y + game->plane.y * camerax;

		game->map_x = (int)game->pos.x;
		game->map_y = (int)game->pos.y;

		distance(&game, &ray_dir);

		int	side = wall_or_not(&game);


		game->line_height = draw_pos(&game, side);

		// TODO: check which direction player look at

		char	tile_type = game->map->items[game->map_y][game->map_x];
		int	texNum = (tile_type == '1') ? 0 : 1;
		double wallX;

		if (tile_type == 'N')
		{
			printf("tile_type: %c\n", tile_type);
			printf("texNum   : %d\n", texNum);
		}

		if (side == 0)
			wallX = game->pos.y + game->prep_wall_dist * ray_dir.y;
		else
			wallX = game->pos.x + game->prep_wall_dist * ray_dir.x;

		wallX -= floor(wallX);

		int	texX = (int)(wallX * (double)texWidth);

		//int	color = RED;

		if (side == 0 && ray_dir.x > 0)
		{
			texX = texWidth - texX - 1;
		}
		if (side == 1 && ray_dir.y < 0)
		{
			texX = texWidth - texX - 1;
		}

		double step = 1.0 * texHeight / game->line_height;

		double texPos = (game->draw_start - h / 2 + game->line_height / 2) * step;

		(void)texPos;

		(void) texNum;
		// TODO: fix raycasting if the player near to the wall
		render_floor_ceiling(game, x);
		render_texture(game, texX, side, texNum, x);

	}
	mlx_put_image_to_window(&game->mlx_ctx->mlx_ptr, game->mlx_ctx->win_ptr, game->mlx_ctx->img.img, 0, 0);
	return 1;
}
