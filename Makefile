# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glacroix <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 16:34:00 by glacroix          #+#    #+#              #
#    Updated: 2024/03/18 16:40:37 by glacroix         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
# **************************************************************************** #
RESET  		= "\x1B[0m"
RED  		= "\x1B[31m"
GREEN  		= "\x1B[32m"
YELLOW  	= "\x1B[33m"
BLUE 		= "\x1B[34m"
MAGENTA 	= "\x1B[35m"
CAYN  		= "\x1B[36m"
WHITE  		= "\x1B[37m"

#Program name
# **************************************************************************** #
NAME		= cub3D 

#SRC & OBJS Details
# **************************************************************************** #
SRCS		= src/test.c\
			  src/main.c
				
OBJS		= $(SRCS:%.c=objs/%.o)

#Execution
# **************************************************************************** #
LIBFT		= libft/libft.a
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -Imlx
CFLAGS		+= -I include
CFLAGS		+= -I libft -g3 -O2 -DSTRINGPUTX11
MINI		= -lmlx -framework OpenGL -framework AppKit -g3 #-fsanitize=address

#SRC Execution
# **************************************************************************** #
$(NAME): objs $(OBJS)
	@make -sC libft
	@$(CC) $(OBJS) $(LIBFT) $(MINI) -o $(NAME)
	@echo $(MAGENTA) "\n         Cub3D Compiled!       \n" $(RESET)

#Makefile Cmds
# **************************************************************************** #
objs:
	@mkdir -p objs/src

objs/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

all: $(NAME)

clean:
	@make clean -sC libft
	@rm -rf objs

fclean: clean
	@make fclean -sC libft
	@rm -f $(NAME)
	@echo $(RED) "\n >>>>>>>> Deleted all *.o and *.a! <<<<<<<< \n" $(RESET)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re re_bonus bonus
