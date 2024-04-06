#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include <mlx.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <float.h>
#include <time.h>
#include <sys/time.h>

static const char *res[] = {
	"./textures/redbrick.xpm",
	"./textures/greystone.xpm",
};

#define	LEN sizeof(res) / sizeof(res[0])

enum s_tex_pos
{
	TEX_NO	= 0,
	TEX_SO,
	TEX_WE,
	TEX_EA,
	TEX_LEN
};



#if __linux__
	#define KEY_ESC 				0xff1b
	#define KEY_ARROW_LEFT	0xff51
	#define KEY_ARROW_UP		0xff52
	#define KEY_ARROW_RIGHT	0xff53
	#define KEY_ARROW_DOWN	0xff54
#else
	#define KEY_ESC					0x35
	#define KEY_ARROW_LEFT	0x7b
	#define KEY_ARROW_RIGHT	0x7c
	#define KEY_ARROW_UP		0x7e
	#define KEY_ARROW_DOWN	0x7d
	#define KEY_W						0xd
	#define KEY_A						0x0
	#define KEY_D						0x2
	#define KEY_S						0x1
	
#endif

#define	RED			0xe62937
#define GREEN		0x00e430
#define	BLUE		0x0079f1
#define YELLOW	0xfdf900
#define WHITE		0xFFFFFF

#define	W	1024
#define	H	512

#define	MOVE_SPEED	0.3
#define	ROT_SPEED		0.1



#define	texWidth 64
#define	texHeight texWidth


typedef struct s_vec2
{
	double x;
	double y;
}	t_vec2;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	size_t	screen_width;
	size_t	screen_height;
}	t_mlx;

int	game_close(void)
{
	exit(0);
	return 1;
}


void	render_rect(t_mlx *mlx_ctx, int x, int y, int width, int height, int color);

typedef struct s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}	t_color;

typedef struct s_map
{
	char	**items;
	int		row_size;
	int		col_size;
}	t_map;

typedef struct s_img
{
	void	*img;
	uint32_t	*data;
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	int	width;
	int	height;


}	t_img;


typedef struct s_game
{

	// player position
	t_vec2	pos;
	// player direction
	t_vec2	dir;
	t_vec2	plane;

	t_vec2	side_dist;
	t_vec2	delta_dist;

	double	prep_wall_dist;

	int	step_x;
	int	step_y;

	int	map_x;
	int	map_y;

	int	draw_start;
	int	draw_end;
	int	line_height;

	// TODO: calculate delta time
	time_t	curr_time;
	time_t	old_time;

	// TODO: store here 4 textures from map file
	//t_img	textures[TEX_LEN];
	t_img	textures[LEN];

	t_mlx		mlx_ctx;
	t_map		map;
}	t_game;

void	draw_rect(t_mlx *ctx, t_vec2 *pos, t_vec2 *size, int color)
{
	int	y = pos->y;
	while (y < pos->y + size->y)
	{
		int x = pos->x;
		while (x < pos->x + size->x)
		{
			mlx_pixel_put(ctx->mlx, ctx->win, x, y, color);
			x += 1;
		}
		y += 1;
	}
}

void	draw_map(char **items, t_mlx *ctx)
{

	t_vec2 size = {64.0f, 64.0f};
	t_vec2 pos;


	int	y = 0;
	while (items[y])
	{
		int x = 0;
		while (items[y][x] && items[y][x] != '\n')
		{
			int	color = 0x0;
			if (items[y][x] == '1')
				color = 0xffffff;
			pos.x = x * size.x;
			pos.y = y * size.y;
			t_vec2 size2 = {size.x - 1, size.y - 1};

			draw_rect(ctx, &pos, &size2, color);
			x += 1;
		}
		y += 1;
	}

}

void draw_ver_line(t_mlx *ctx, int x, int draw_start, int draw_end, int color)
{
	int	y;

	y = draw_start;
	while (y <= draw_end)
	{
		mlx_pixel_put(ctx->mlx, ctx->win, x, y, color);
		y += 1;
	}
}



void	draw_player(t_game *game)
{
	(void) game;
}

int	is_hit_wall(t_game *game)
{
	int	side;
	int	hit = 0;

	// TODO: repcale hit by break

	while (!hit)
	{
		if (game->side_dist.x < game->side_dist.y)
		{
			game->side_dist.x += game->delta_dist.x;
			game->map_x += game->step_x;
			side = 0;
		}
		else
		{
			game->side_dist.y += game->delta_dist.y;
			game->map_y += game->step_y;
			side = 1;
		}
		if (game->map.items[game->map_y][game->map_x] != '0')
			hit = 1;
		else
			hit = 0;
	}
	return side;
}

void	side_distance(t_game *game, t_vec2 *ray_dir)
{
	if (ray_dir->x < 0)
	{
		game->step_x = -1;
		game->side_dist.x = (game->pos.x - game->map_x) * game->delta_dist.x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist.x = (game->map_x + 1.0 - game->pos.x) * game->delta_dist.x;
	}

	if (ray_dir->y < 0)
	{
		game->step_y = -1;
		game->side_dist.y = (game->pos.y - game->map_y) * game->delta_dist.y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist.y = (game->map_y + 1.0 - game->pos.y) * game->delta_dist.y;
	}
}

void	distance(t_game *game, t_vec2 *ray_dir)
{
	if (ray_dir->x == 0)
		game->delta_dist.x = 1e30;
	else
		game->delta_dist.x = fabs(1.0 / ray_dir->x);
	if (ray_dir->y == 0)
		game->delta_dist.y = 1e30;
	else
		game->delta_dist.y = fabs(1.0 / ray_dir->y);
	side_distance(game, ray_dir);


}

int	draw_pos(t_game *game, int side)
{
	int	line_height;

	if (side == 0)
		game->prep_wall_dist = (game->side_dist.x - game->delta_dist.x);
	else
		game->prep_wall_dist = (game->side_dist.y - game->delta_dist.y);
	line_height = (int)(H / game->prep_wall_dist);
	game->draw_start = (int)(-line_height / 2 + H / 2);
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = (int)(line_height / 2 + H / 2);
	if (game->draw_end >= H)
		game->draw_end = H - 1;
	return line_height;
}

void	render_texture(t_game *game, int tex_x, int side, int tex_num, int x)
{
	int	y;
	int	tex_y;
	uint32_t	color;
	const double step = 1.0 * texHeight / game->line_height;
	double tex_pos = (game->draw_start - H / 2 + game->line_height / 2) * step;

	y = game->draw_start;
	while (y <= game->draw_end)
	{
		tex_y = (int)tex_pos & (texHeight - 1);
		tex_pos  += step;
		color = game->textures[tex_num].data[texHeight * tex_y + tex_x];
		if (side == 1)
			color = (color >> 1) & 0x7f7f7f;
		mlx_pixel_put(game->mlx_ctx.mlx, game->mlx_ctx.win, x, y, color);
		y += 1;
	}
}

size_t get_time(void)
{
	struct timeval tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec) * (tp.tv_usec / 1000);
}

size_t old_time = 0;
size_t curr_time = 0;

int	raycast(t_game *game)
{
	//int	x;	
	double camerax;	
	t_vec2 ray_dir;

	curr_time = get_time();

	for (int x = 0; x < W; x += 1)
	{
		camerax = 2 * x / (double)W - 1;
		ray_dir.x = game->dir.x + game->plane.x * camerax;
		ray_dir.y = game->dir.y + game->plane.y * camerax;

		game->map_x = (int)game->pos.x;
		game->map_y = (int)game->pos.y;

		distance(game, &ray_dir);

		int	side = is_hit_wall(game);
		game->line_height = draw_pos(game, side);
		int	color;
		char	tile_type = game->map.items[game->map_y][game->map_x];
		int	texNum = (tile_type == '1') ? 0 : 1;
		double wallX;

		if (side == 0)
		{
			wallX = game->pos.y + game->prep_wall_dist * ray_dir.y;
		}
		else
		{
			wallX = game->pos.x + game->prep_wall_dist * ray_dir.x;
		}

		wallX -= floor(wallX);

		int	texX = (int)(wallX * (double)texWidth);

		if (side == 0 && ray_dir.x > 0)
		{
			texX = texWidth - texX - 1;
		}
		if (side == 1 && ray_dir.y < 0)
		{
			texX = texWidth - texX - 1;
		}

		double step = 1.0 * texHeight / game->line_height;

		double texPos = (game->draw_start - H / 2 + game->line_height / 2) * step;

		(void) texPos;

		render_texture(game, texX, side, texNum, x);

		switch(game->map.items[game->map_y][game->map_x])
		{
		case '1':  color = RED;    break; //red
		case '2':  color = GREEN;  break; //green
		case '3':  color = BLUE;   break; //blue
		case '4':  color = WHITE;  break; //white
// // 		case 1:  color = RED;    break; //red
// // 		case 2:  color = GREEN;  break; //green
// // 		case 3:  color = BLUE;   break; //blue
// // 		case 4:  color = WHITE;  break; //white
		default: color = YELLOW; break; //yellow
		}
		if(side == 1) {color = color / 2;}

		//draw_ver_line(&game->mlx_ctx, x, game->draw_start, game->draw_end, color);	

	}




	return 1;
}





int	key_hook(int keycode, void *param)
{
	t_game *game = param;
	double	old_dir_x;
	double	old_plane_x;

	old_time = curr_time;
	curr_time = time(NULL);

	//double frame_time = (old_time - curr_time);

	//printf("frame_time: %lf\n", frame_time);



	mlx_clear_window(game->mlx_ctx.mlx, game->mlx_ctx.win);
	if (keycode == KEY_ESC)
	{
		game_close();
	}


	if (keycode == KEY_ARROW_RIGHT)
	{
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(-ROT_SPEED) - game->dir.y * sin(-ROT_SPEED);
		game->dir.y = old_dir_x * sin(-ROT_SPEED) + game->dir.y * cos(-ROT_SPEED);

		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(-ROT_SPEED) - game->plane.y * sin(-ROT_SPEED);
		game->plane.y = old_plane_x * sin(-ROT_SPEED) + game->plane.y * cos(-ROT_SPEED);
	}
	if (keycode == KEY_ARROW_LEFT)
	{
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(ROT_SPEED) - game->dir.y * sin(ROT_SPEED);
		game->dir.y = old_dir_x * sin(ROT_SPEED) + game->dir.y * cos(ROT_SPEED);

		old_plane_x = game->plane.x;
		game->plane.x = game->plane.x * cos(ROT_SPEED) - game->plane.y * sin(ROT_SPEED);
		game->plane.y = old_plane_x * sin(ROT_SPEED) + game->plane.y * cos(ROT_SPEED);
	}
	if (keycode == KEY_ARROW_UP)
	{
		int	x = (int)game->pos.x;
		int	y = (int)game->pos.y;
		int	xx = (int)(game->pos.x + game->dir.x * MOVE_SPEED);
		int	yy = (int)(game->pos.y + game->dir.y * MOVE_SPEED);

		// TODO: you swaped y and x
// 		if(map[xx][y] == 0)
// 			game->pos.x += game->dir.x * MOVE_SPEED;
// 	 	if(map[x][yy] == 0)
// 			game->pos.y += game->dir.y * MOVE_SPEED;
		if(game->map.items[xx][y] == '0')
			game->pos.x += game->dir.x * MOVE_SPEED;
	 	if(game->map.items[x][yy] == '0')
			game->pos.y += game->dir.y * MOVE_SPEED;
	}

	if (keycode == KEY_ARROW_DOWN)
	{
		int	x = (int)game->pos.x;
		int	y = (int)game->pos.y;
		int	xx = (int)(game->pos.x + game->dir.x * MOVE_SPEED);
		int	yy = (int)(game->pos.y + game->dir.y * MOVE_SPEED);

		// TODO: you swaped y and x
		if(game->map.items[xx][y] == '0')
			game->pos.x -= game->dir.x * MOVE_SPEED;
	 	if(game->map.items[x][yy] == '0')
			game->pos.y -= game->dir.y * MOVE_SPEED;
// 		if(map[xx][y] == 0)
// 			game->pos.x -= game->dir.x * MOVE_SPEED;
// 	 	if(map[x][yy] == 0)
// 			game->pos.y -= game->dir.y * MOVE_SPEED;
		
	}


	return 1;
}

t_vec2	player_pos(char **items)
{
	int	y;
	int	x;
	t_vec2	pos = {0};

	y = -1;
	while (items[++y] != NULL)
	{
		x = -1;
		while (items[y][++x] != '\0')
		{
			if (items[y][x] == 'N')
			{
				pos.x = x;
				pos.y = y;
				return pos;
			}
		}
	}
	return pos;
}

int	load_texture(void *mlx, t_img *img, const char *filepath)
{
	img->img = mlx_xpm_file_to_image(mlx, (char *)filepath, &img->width, &img->height);
	if (!img->img)
	{
		printf("Error: failed to load img: %s\n", filepath);
		return 0;
	}
	img->data = (uint32_t*)mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->size_line, &img->endian);
	if (!img->data)
	{
		printf("Error: could not get data image: %s\n", filepath);
		return 0;
	}
	return 1;
}


int main(int argc, char **argv)
{
	(void) argc;
	t_game	game;
	
	ft_bzero(&game, sizeof(game));
	game.mlx_ctx.mlx = mlx_init();
	game.mlx_ctx.win = mlx_new_window(game.mlx_ctx.mlx, W, H, "Cub3D");

// 	size_t	size;
	game.map.items = malloc(sizeof(char *)  * 25);
	int	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("%s\n", strerror(errno));
		return 1;
	}


	int i = 0;
	for (;; i += 1)
	{
		game.map.items[i] = ft_strtrim(get_next_line(fd), "\n");
		if (game.map.items[i] == NULL)
			break ;
	}
	game.map.items[i] = NULL;

	game.pos.x = 22, game.pos.y = 12;
	game.dir.x = -1, game.dir.y = 0;
	game.plane.x = 0.0, game.plane.y = 0.66;


	for (size_t i = 0; i < LEN; i += 1)
	{
		if (!load_texture(game.mlx_ctx.mlx, &game.textures[i], res[i]))
		{
			printf("Error\n");
			exit(1);
		}
	}




	mlx_loop_hook(game.mlx_ctx.mlx, raycast, &game);
	mlx_key_hook(game.mlx_ctx.win, key_hook, &game);
	mlx_hook(game.mlx_ctx.win, 17, (1 << 17), game_close, NULL);
	mlx_loop(game.mlx_ctx.mlx);

	return 0;
}