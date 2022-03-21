# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nflan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 10:49:49 by nflan             #+#    #+#              #
#    Updated: 2022/03/21 18:39:06 by nflan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.h libft
vpath ft_%.c libft
vpath ft_%.o libft

sources = srcs/main.c 

INC = include/fractol.h

OBJS = ${sources:.c=.o}

sourcesB = srcsb/main_bonus.c 

INCB = include/fractol_bonus.h

OBJSB = ${sourcesB:.c=.o}

LIBFT = libft/libft.a

MINILIBX = minilibx/libmlx_Linux.a

NAME = fractol

#CC = gcc

#RM = rm -f

#CFLAGS = -Wall -Wextra -Werror

DEBUG = -g3 -fsanitize=address

#.c.o :
#	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

$(NAME): ${OBJS} ${INC} ${HEADER} ${LIBFT}
	$(MAKE) -C minilibx/
	${CC} ${CFLAGS} ${OBJS} -I ${INC} ${MINILIBX} ${LIBFT} -lXext -lX11 -lm -o ${NAME}

bonus: ${OBJSB} ${HEADER} ${LIBFT}
	${RM} ${OBJS}
	$(MAKE) -C minilibx/
	${CC} ${CFLAGS} ${OBJSB} -I ${INCB} -o ${NAME}

-include libft/Makefile

ft_%.o : ft_%.c
	gcc ${CFLAGS} -c $< -o $@

$(LIBFT) : ${SRCS} libft.h
	${MAKE} -C libft/

clean:
	$(MAKE) clean -C libft/
	$(MAKE) clean -C minilibx/
	${RM} ${OBJS} ${OBJSB}

fclean:
	$(MAKE) fclean -C libft/
	$(MAKE) clean -C minilibx/
	${RM} ${NAME}
	${RM} ${OBJS} ${OBJSB}

re: fclean all

.PHONY: all clean fclean bonus re
