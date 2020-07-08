# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 18:27:40 by smanhack          #+#    #+#              #
#    Updated: 2019/08/02 19:10:44 by smanhack         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRC	= f_cps.c ft_atoi.c ft_bzero.c ft_diouxx_up.c ft_isdigit.c ft_itoa.c ft_itoa_base_ull.c ft_itoa_ll.c ft_number_of_digits.c ft_printf.c ft_putchar.c ft_putstr.c ft_second.c ft_strchr.c ft_strcpy.c ft_strlen.c ft_strncpy.c ft_strnew.c ft_toupper.c ft_third.c doublf.c ldoublf.c ft_strjoin.c ft_memcpy.c ft_putnbr_endl.c ft_putnbr.c doublf_part_2.c doublf_part_3.c doublf_part_4.c \
doublf_part_5.c ldoublf_part_2.c ldoublf_part_3.c ldoublf_part_4.c ldoublf_part_5.c ldoublf_part_6.c ft_fourth.c ldoublf_part_7.c ft_itoa_base_uintmax_t.c ft_itoa_intmax_t.c ft_itoa_base_size_t.c ft_itoa_ssize_t.c ft_strstr.c ft_putendl.c ft_rainbow.c ft_strsub.c ft_strdup.c ft_strcmp.c bonus_part.c

HDR = ft_printf.h libft.h

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) :
	gcc $(FLAGS) -I $(HDR) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re