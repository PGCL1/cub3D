/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:48:07 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/22 20:03:20 by aabourri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_or_not(t_game **game)
{
	(*game)->hit_wall = 0;
	while (!(*game)->hit_wall)
	{
		if ((*game)->side_dist.x < (*game)->side_dist.y)
		{
			(*game)->side_dist.x += (*game)->delta_dist.x;
			(*game)->map_x += (*game)->step_x;
			(*game)->side = 0;
		}
		else
		{
			(*game)->side_dist.y += (*game)->delta_dist.y;
			(*game)->map_y += (*game)->step_y;
			(*game)->side = 1;
		}
		if ((*game)->map_y >= 0 && (*game)->map_y < (int)(*game)->map->len)
		{
			if ((*game)->map->items[(*game)->map_y][(*game)->map_x] != '0')
				(*game)->hit_wall = 1;
			else
				(*game)->hit_wall = 0;
		}
		else
			(*game)->hit_wall = 1;
	}
}

void	side_distance(t_game **g, t_vector *ray_dir)
{
	const double	ddx = (*g)->delta_dist.x;
	const double	ddy = (*g)->delta_dist.y;

	if (ray_dir->x < 0)
	{
		(*g)->step_x = -1;
		(*g)->side_dist.x = ((*g)->pos.x - (*g)->map_x) * ddx;
	}
	else
	{
		(*g)->step_x = 1;
		(*g)->side_dist.x = ((*g)->map_x + 1.0 - (*g)->pos.x) * ddx;
	}
	if (ray_dir->y < 0)
	{
		(*g)->step_y = -1;
		(*g)->side_dist.y = ((*g)->pos.y - (*g)->map_y) * ddy;
	}
	else
	{
		(*g)->step_y = 1;
		(*g)->side_dist.y = ((*g)->map_y + 1.0 - (*g)->pos.y) * ddy;
	}
}

void	distance(t_game **game, t_vector *ray_dir)
{
	if ((*game)->ray_dir.x == 0)
		(*game)->delta_dist.x = 1e30;
	else
		(*game)->delta_dist.x = fabs(1.0 / (*game)->ray_dir.x);
	if ((*game)->ray_dir.y == 0)
		(*game)->delta_dist.y = 1e30;
	else
		(*game)->delta_dist.y = fabs(1.0 / (*game)->ray_dir.y);
	side_distance(game, ray_dir);
}

void	raycast2(t_game *g)
{
	if (g->side == 0)
		g->wall_x = g->pos.y + g->prep_wall_dist * g->ray_dir.y;
	else
		g->wall_x = g->pos.x + g->prep_wall_dist * g->ray_dir.x;
	g->wall_x -= floor(g->wall_x);
	g->tex_x = (int)(g->wall_x * (double)TEXWIDTH);
	if (g->side == 0 && g->ray_dir.x > 0)
		g->tex_x = TEXWIDTH - g->tex_x - 1;
	if (g->side == 1 && g->ray_dir.y < 0)
		g->tex_x = TEXWIDTH - g->tex_x - 1;
}

int	raycast(t_game *g)
{
	int		x;	
	double	camerax;	

	mlx_clear_window(g->mlx_ctx->mlx_ptr, g->mlx_ctx->win_ptr);
	x = -1;
	while (++x < WIDTH)
	{
		camerax = 2 * x / (double)WIDTH - 1;
		g->ray_dir.x = g->dir.x + g->plane.x * camerax;
		g->ray_dir.y = g->dir.y + g->plane.y * camerax;
		g->map_x = (int)g->pos.x;
		g->map_y = (int)g->pos.y;
		distance(&g, &g->ray_dir);
		wall_or_not(&g);
		g->line_height = draw_pos(&g, g->side);
		raycast2(g);
		render_floor_ceiling(g, x);
		render_texture(g, g->tex_x, g->side, x);
	}
	mlx_put_image_to_window(&g->mlx_ctx->mlx_ptr,
		g->mlx_ctx->win_ptr, g->mlx_ctx->img.img, 0, 0);
	return (1);
}
