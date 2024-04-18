/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:48:07 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/18 10:54:28 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//static const char *res[] = {
	//"./textures/file.xpm",
//};

//typedef struct s_color
//{
	//unsigned char r;
	//unsigned char g;
	//unsigned char b;
//}	t_color;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->img.data
		+ (y * data->img.size_line + x * (data->img.bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void draw_ver_line(t_data *ctx, int x, int draw_start, int draw_end, int color)
{
	int	y;

	y = draw_start;
	while (y <= draw_end)
	{
		my_mlx_pixel_put(ctx, x, y, color);
		y += 1;
	}
}

int	is_hit_wall(t_game **game)
{
	int	side;
	int	hit = 0;

	// TODO: repcale hit by break

	while (!hit)
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

		if ((*game)->map->items[(*game)->map_y][(*game)->map_x] != '0')
			hit = 1;
		else
			hit = 0;
	}
	return side;
}

void	side_distance(t_game **game, t_vector *ray_dir)
{
	if (ray_dir->x < 0)
	{
		(*game)->step_x = -1;
		(*game)->side_dist.x = ((*game)->pos.x - (*game)->map_x) * (*game)->delta_dist.x;
	}
	else
	{
		(*game)->step_x = 1;
		(*game)->side_dist.x = ((*game)->map_x + 1.0 - (*game)->pos.x) * (*game)->delta_dist.x;
	}

	if (ray_dir->y < 0)
	{
		(*game)->step_y = -1;
		(*game)->side_dist.y = ((*game)->pos.y - (*game)->map_y) * (*game)->delta_dist.y;
	}
	else
	{
		(*game)->step_y = 1;
		(*game)->side_dist.y = ((*game)->map_y + 1.0 - (*game)->pos.y) * (*game)->delta_dist.y;
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

void	render_texture(t_game *game, int tex_x, int side, int tex_num, int x)
{
	int	y;
	int	tex_y;
	uint32_t	color;
	const double step = 1.0 * texHeight / game->line_height;
	double tex_pos = (game->draw_start - h / 2 + game->line_height / 2) * step;

	y = game->draw_start;
	while (y <= game->draw_end)
	{
		tex_y = (int)tex_pos & (texHeight - 1);
		tex_pos  += step;
		color = game->textures[tex_num].data[texHeight * tex_y + tex_x];
		if (side == 1)
			color = (color >> 1) & 0x7f7f7f;
		my_mlx_pixel_put(game->mlx_ctx, x, y, color);
		y += 1;
	}
}

void game_background_draw(t_data *data, int color)
{
	int i = -1;
	int j = -1;

	while (++i < h)
	{
		j = 0;
		while (++j < w)
			my_mlx_pixel_put(data, j, i, color);
	}
}

int	raycast(t_game *game)
{
	//int	x;	
	double camerax;	
	t_vector ray_dir;

	game_background_draw(game->mlx_ctx, BLACK);
	for (int x = 0; x < w; x += 1)
	{
		camerax = 2 * x / (double)w - 1;
		ray_dir.x = game->dir.x + game->plane.x * camerax;
		ray_dir.y = game->dir.y + game->plane.y * camerax;

		game->map_x = (int)game->pos.x;
		game->map_y = (int)game->pos.y;

		distance(&game, &ray_dir);

		int	side = is_hit_wall(&game);

	//	printf("side: %d\n", side);


		game->line_height = draw_pos(&game, side);

		// TODO: check which direction player look at

		char	tile_type = game->map->items[game->map_y][game->map_x];
		int	texNum = (tile_type == '1') ? 0 : 1;
		double wallX;

		if (side == 0)
			wallX = game->pos.y + game->prep_wall_dist * ray_dir.y;
		else
			wallX = game->pos.x + game->prep_wall_dist * ray_dir.x;

		wallX -= floor(wallX);

		int	texX = (int)(wallX * (double)texWidth);

		int	color = RED;

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
		render_texture(game, texX, side, texNum, x);

		//color = RED;

		if (side)
			color /= 2;
		
		/*printf("start: %d\n", game->draw_start);*/
		/*printf("end: %d\n", game->draw_end);*/


		draw_ver_line(game->mlx_ctx, x, game->draw_start, game->draw_end, color);

	}
	mlx_put_image_to_window(&game->mlx_ctx->mlx_ptr, game->mlx_ctx->win_ptr, game->mlx_ctx->img.img, 0, 0);
	return 1;
}
