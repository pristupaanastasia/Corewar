CW = corewar
MAKE = make
LIB = ./libft/
NAME_LIB 			= libft/libft.a
GCC_LIBFT 			= -L ./libft -l ft
SRC = virtual.c op.c operations.c operations_2.c operations_3.c operations_4.c operations_5.c
SRC_DIR 			= ./src/
OBJ_DIR 			= ./obj/

HEADER = ./header
OBJ					= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
all: $(OBJ_DIR) $(CW)

$(CW): $(LIB) $(OBJ_DIR) $(OBJ) $(NAME_LIB)
	gcc -o $(CW) -I $(HEADER) $(GCC_LIBFT) ./src/*.c -g
$(OBJ_DIR):
	@mkdir -p obj
$(NAME_LIB):
	@make -C libft/
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	gcc -c -I $(HEADER) -I $(LIB) $< -o $@

$(LIB):
	$(MAKE) -C ./libft/
clean:
	$(MAKE) clean -C ./libft
	@/bin/rm -rf $(OBJ_DIR)
fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(CW)
re: fclean all
