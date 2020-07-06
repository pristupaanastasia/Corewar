CW = corewar
MAKE = make
LIB = ./libft/
FT_PRINTF = ./ft_printf/
LIB_PRINTF = ./ft_printf/libftprintf.a
NAME_LIB 			= libft/libft.a
GCC_LIBFT 			= -L ./libft -l ft
GCC_FT_PRINTF		= -L ./ft_printf -l ft
SRC = virtual.c op.c operations.c operations_2.c operations_3.c operations_4.c operations_5.c arena.c help_func.c help_parse.c main.c parse.c play.c 
SRC_DIR 			= ./src/
OBJ_DIR 			= ./obj/

HEADER = ./header
OBJ					= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
all: $(OBJ_DIR) $(CW)

$(CW): $(LIB) $(FT_PRINTF) $(OBJ_DIR) $(OBJ) $(NAME_LIB) $(LIB_PRINTF)
	gcc -o $(CW) -I $(HEADER)  $(NAME_LIB) $(LIB_PRINTF) ./src/*.c -g
$(OBJ_DIR):
	@mkdir -p obj
$(NAME_LIB):
	@make -C libft/
$(LIB_PRINTF):
	@make -C ft_printf/
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	gcc -c -I $(HEADER) -I $(LIB) -I $(FT_PRINTF) $< -o $@
$(FT_PRINTF):
	$(MAKE) -C ./ft_printf/
$(LIB):
	$(MAKE) -C ./libft/
clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./ft_printf
	@/bin/rm -rf $(OBJ_DIR)
fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./ft_printf
	rm -f $(CW)
re: fclean all
