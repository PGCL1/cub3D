/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:11:28 by glacroix          #+#    #+#             */
/*   Updated: 2024/04/11 11:39:15 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*------------------------------Libraries-------------------------------------*/
# include "../libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <math.h>

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
/*# define WHITE			0XFFF5EE*/
# define BLUE			0X191970

/*------------------------------Shortcuts-------------------------------------*/
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

typedef struct s_data
{
	void	*img;
	char	*img_addr;
	int		img_bits_per_pixel;
	int		img_line_length;
	int		img_endian;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_data;

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
	double x;
	double y;
}	t_vector;

typedef struct s_texture
{
	int		width;
	int		height;
	void	*addi;	
}	t_texture;

typedef struct s_design 
{
	int		floor[3];
	int		ceiling[3];
	t_texture	north_text;
	t_texture	south_text;
	t_texture	east_text;
	t_texture	west_text;
}	t_design;

typedef struct s_win
{
	int h_y;
	int w_x;
}	t_win;

typedef struct s_setup
{
	t_data data;
	t_win	window;
	t_array map;
	t_player player;
	t_design design;
}	t_setup;

/*------------------------------Utils----------------------------------------*/
void		error_msg(char *msg);
void		*ft_realloc(void *ptr, size_t len, size_t size);
void		ms_array_append(t_array *arr, char *item);
t_array		ms_array_init(void);
size_t		line_len(char *item);
void		free_t_array(t_array *arr);

/*------------------------------Parsing---------------------------------------*/

char		*texture_path(char *line);
void		get_texture(void *mlx, char *line, t_texture *t);
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
void		player_position(t_player *player, size_t i, size_t j);

/*-----------------------------------Init-------------------------------------*/

int			window_init(t_data *data, t_win *window);
int			design_init(t_design *design, t_data *data, int file);
int			map_init(t_array *map, int file);
int			player_init(t_player *player, const t_array *map);
int			setup_init(t_setup *structure, int file);

int			check_file(int argc, char *input);

#endif
