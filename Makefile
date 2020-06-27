CW = corewar
MAKE = make
LIB = ./libft/libft.a

SRC = virtual.c op.c operations.c
HEADER = .
OBJ = $(SRC:.c=.o)
all: $(CW)

%.o: %.c
	gcc -c -o $@ $< -g
$(CW): $(LIB) $(OBJ)
	gcc -o $(CW) -I $(HEADER) $(LIB) $(OBJ) -g
$(LIB):
	$(MAKE) -C ./libft/
clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJ)
fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(CW)
re: fclean all
