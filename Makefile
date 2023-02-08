# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzi-xian <lzi-xian@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 14:07:20 by lzi-xian          #+#    #+#              #
#    Updated: 2023/02/07 13:55:46 by lzi-xian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


PS_NAME		=	pipex
SRCS		=	pipex.c ft_child.c
LIBFT		=	libft/libft.a
OBJS		=	${SRCS:.c=.o}
NAME		=	pipex.a
ARCR		= 	ar cr
RMRF		=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror
GCC			=	gcc

.c.o:
	${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	touch $(NAME)
	cp ${LIBFT} .
	mv libft.a $(NAME)
	${ARCR} ${NAME} ${OBJS}
	make run

run:
	${GCC} ${CFLAGS} $(NAME) -o ${PS_NAME}

all:	$(NAME)

clean:
	${RMRF} ${OBJS}

fclean:	clean
	${RMRF} $(NAME) ${CHK_NAME} ${PS_NAME}

re:	fclean all