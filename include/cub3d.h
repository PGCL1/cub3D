/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:11:28 by glacroix          #+#    #+#             */
/*   Updated: 2024/03/29 15:37:17 by glacroix         ###   ########.fr       */
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

/*------------------------------Error_msg-------------------------------------*/
# define RESET  		"\x1B[0m"
# define P_RED  		"\x1B[31m"

/*------------------------------Colors----------------------------------------*/
# define PURPLE			0XF4ECF7 
# define ORANGE			0XFFDE5C
# define RED			0X42990010
# define GREEN			0X014421 
# define BLACK			0X000000
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

typedef struct s_design 
{
	int		floor[3];
	int		ceiling[3];
	void	*north_text;
	void	*south_text;
	void	*east_text;
	void	*west_text;
}	t_design;

/*------------------------------Utils----------------------------------------*/
void	error_msg(char *msg);
void	*ft_realloc(void *ptr, size_t len, size_t size);
void	ms_array_append(t_array *arr, char *item);
t_array	ms_array_init(void);
size_t	line_len(char *item);

/*------------------------------Parsing---------------------------------------*/
int			map_check_borders(t_array copy);

char		*texture_path(char *line);
void		*get_texture(void *mlx, char *line);

int			line_error(char *item, size_t len);
int			line_empty(char *line);
const char	*line_meaning(char *line);

void		init_colors(int floor[], int ceiling[]);
char		*color_path(char *line);
size_t		len_matrix(char **ptr);
int			get_colors(char *line, int color[]);

int			error_color(int color[]);
int			error_design(t_design *design);
int			colors_textures(void *mlx, char *line, t_design *design);
t_design	assign_design(int file, t_data *data, int *count, char *line);
#endif
