/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:11:28 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/30 16:21:35 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*------------------------------Libraries-------------------------------------*/
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>

/*------------------------------Error_msg-------------------------------------*/
# define RESET  		"\x1B[0m"
# define P_RED  		"\x1B[31m"

/*------------------------------Colors----------------------------------------*/
# define PURPLE			0XF4ECF7 
# define ORANGE			0XFFDE5C
# define RED			0X42990010
# define GREEN			0X014421 
# define BLACK			0X000000
# define GREY			0X808080
# define BLUE			0X191970

/*----------------------------Configurations----------------------------------*/
# define TRUE				1
# define FALSE				0
# define ESC				53
# define W					13
# define S					1
# define A					0 
# define D					2
# define UP					126
# define DOWN				125
# define LEFT				123
# define RIGHT				124
# define PLUS				69
# define MINUS				78

# define WIDTH					1020
# define HEIGHT					512
# define MOVE_SPEED			0.3
# define RO_SPEED			0.1
# define TEXWIDTH			64
# define TEXHEIGHT			TEXWIDTH

# define KEY_ESC			0x35
# define KEY_ARROW_LEFT	0x7b
# define KEY_ARROW_RIGHT	0x7c
# define KEY_ARROW_UP	0x7e
# define KEY_ARROW_DOWN	0x7d
# define KEY_W			0xd
# define KEY_A			0x0
# define KEY_D			0x2
# define KEY_S			0x1

/*----------------------------Structures--------------------------------------*/
typedef struct s_array
{
	char	**items;
	size_t	*items_len;
	size_t	cap;
	size_t	len;
}	t_array;

typedef struct s_player
{
	char	orientation;
	int		x;
	int		y;
}	t_player;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_img
{
	void		*img;
	uint32_t	*data;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	int			valid;
}	t_img;

typedef struct s_design
{
	int			floor[3];
	int			ceiling[3];
	t_img		textures[4];
}	t_design;

typedef struct s_data
{
	t_img		img;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_data;

typedef struct s_game
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		prep_wall_dist;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			draw_start;
	int			draw_end;
	int			line_height;
	int			side;
	double		wall_x;
	int			tex_x;
	int			hit_wall;
	t_img		textures[4];
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_data		*mlx_ctx;
	t_array		*map;
}	t_game;

typedef struct s_setup
{
	t_data		data;
	t_array		map;
	t_player	player;
	t_design	design;
	t_game		game;
}	t_setup;

/*------------------------------Utils-----------------------------------------*/
void		error_msg(char *msg);
void		*ft_realloc(void *ptr, size_t len, size_t size);
void		ms_array_append(t_array *arr, char *item);
t_array		ms_array_init(void);
size_t		line_len(char *item);
void		free_t_array(t_array *arr);
int			ft_exit(void);
/*------------------------------Parsing---------------------------------------*/
char		*texture_path(char *line);
void		get_texture(void *mlx, char *line, t_img *img);
char		*texture_path_cleaned(char *line);
int			line_empty(char *line);
int			line_error(char *item, size_t len);
const char	*line_meaning(char *line);
void		init_colors(int floor[], int ceiling[]);
char		*color_path(char *line);
size_t		len_matrix(char **ptr);
int			get_colors(char *line, int color[]);
int			error_color(int color[]);
int			error_design(t_design *design);
int			colors_textures(void *mlx, char *line, t_design *design);
t_design	assign_design(int file, t_data *data, int *count, char *line);
int			map_check_borders(t_array copy);
void		map_assign(t_array *map, int file);
int			map_fill(t_array *map, int y, int x, int *flag);
void		*map_original_copy(t_array map, t_array *original);
int			orientation(char c, char *player_orientation);
int			player_start(t_player *player, const t_array map);
void		player_position(t_player *player, int i, int j);
/*-----------------------------------Init-------------------------------------*/
int			window_init(t_data *data);
int			design_init(t_design *design, t_data *data, int file);
int			map_init(t_array *map, int file);
int			player_init(t_player *player, const t_array *map);
int			setup_init(t_setup *structure, int file);
int			check_file(int argc, char *input);
/*-----------------------------------Render-----------------------------------*/
int			draw_pos(t_game **game, int side);
int			is_hit_wall(t_game **game);
int			raycast(t_game *game);
void		game_background_draw(t_data *data, int color);
void		side_distance(t_game **game, t_vector *ray_dir);
void		distance(t_game **game, t_vector *ray_dir);
uint32_t	orientation_texture(t_game *game, int side, int tex_x, int tex_y);
void		render_floor_ceiling(t_game *game, int x);
void		render_texture(t_game *game, int tex_x, int side, int x);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
/*-----------------------------------Events-----------------------------------*/
int			key_press(int keycode, t_game *game);
void		movements_player_right(t_game *game);
void		movements_player_left(t_game *game);
void		movements_player_up(t_game *game);
void		movements_player_down(t_game *game);
void		movements_plane(int keycode, t_game *g);
#endif
