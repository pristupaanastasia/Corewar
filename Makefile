CW = corewar
MAKE = make
LIB = ./libft/libft.a

SRC = virtual.c op.c operations.c operations_2.c operations_3.c operations_4.c operations_5.c
SRC_DIR 			= ./src/
OBJ_DIR 			= ./obj/

HEADER = ./header
OBJ					= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
all: $(CW)

$(OBJ)%.o: $(SRC)%.c
	gcc -c -o $@ $< -g
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	gcc -c -I $(HEADER)  $< -o $@
$(CW): $(LIB) $(OBJ) $(OBJ_DIR)
	gcc -o $(CW) -I $(HEADER) $(LIB) $(OBJ) -g
$(LIB):
	$(MAKE) -C ./libft/
$(OBJ_DIR):
	@mkdir -p obj

clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJ)
fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(CW)
re: fclean all
