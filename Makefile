# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nflan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 10:49:49 by nflan             #+#    #+#              #
#    Updated: 2022/04/13 17:24:02 by nflan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.h libft
vpath ft_%.c libft
vpath ft_%.o libft

sources = srcs/main.c srcs/ft_colors.c srcs/ft_colors2.c srcs/ft_julia.c \
		  srcs/ft_mandelbrot.c srcs/ft_zoom.c srcs/ft_utils.c srcs/ft_window.c \
		  srcs/ft_tools.c srcs/ft_parse.c

INC = include/fractol.h

objets = ${sources:.c=.o}

sourcesB = srcsb/main_bonus.c srcsb/ft_colors_bonus.c srcsb/ft_colors2_bonus.c \
		   srcsb/ft_julia_bonus.c srcsb/ft_mandelbrot_bonus.c srcsb/ft_zoom_bonus.c \
		   srcsb/ft_utils_bonus.c srcsb/ft_window_bonus.c srcsb/ft_tools_bonus.c \
		   srcsb/ft_parse_bonus.c srcsb/ft_glynn_bonus.c

INCB = include/fractol_bonus.h

objetsB = ${sourcesB:.c=.o}

LIBFT = libft/libft.a

MINILIBX = minilibx/libmlx_Linux.a

NAME = fractol

#CC = cc

#RM = rm -f

#CFLAGS = -Wall -Wextra -Werror

DEBUG = -g3 -fsanitize=address

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

$(NAME):	${objets} ${INC} ${HEADER} ${LIBFT} ${MINILIBX}
	${CC} ${CFLAGS} ${objets} ${MINILIBX} ${LIBFT} -I ${INC} -lXext -lX11 -lm -o ${NAME}

bonus:	${objetsB} ${INCB} ${HEADER} ${LIBFT} ${MINILIBX}
	${RM} ${objets}
	${CC} ${CFLAGS} ${objetsB} ${MINILIBX} ${LIBFT} -I ${INCB} -lXext -lX11 -lm -o ${NAME}

-include libft/Makefile

ft_%.o : ft_%.c
	cc ${CFLAGS} -c $< -o $@

$(MINILIBX):
	$(MAKE) -C minilibx/

$(LIBFT):	${SRCS} ${OBJS} libft.h
	${MAKE} -C libft/

$(objets):	${INC}

$(objetsB):	${INCB}

clean:
	$(MAKE) clean -C libft/
	${RM} ${objets} ${objetsB}

fclean:
	$(MAKE) fclean -C libft/
	$(MAKE) clean -C minilibx/
	${RM} ${NAME}
	${RM} ${objets} ${objetsB}

re: fclean all

#.SECONDARY: $(objets)

.PHONY: all clean fclean bonus re
