# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriley <mriley@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 17:36:44 by mriley            #+#    #+#              #
#    Updated: 2020/02/17 19:11:33 by mriley           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

CC = clang -Wall -Wextra -Werror

SRC = *.c

OBJ = *.o

all: $(NAME)

$(NAME):
		$(CC) -c $(SRC) -g -I /usr/include
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re:		fclean all

