CW = cwar
MAKE = make
LIB = ./libft/libft.a

SRC = virtual.c op.c operations.c
HEADER = virtual.h op.h
OBJ = $(SRC:.c=.o)
all: $(CW)

%.o: %.c
	gcc -c -o $@ $< -g
$(CW): $(LIB) $(OBJ)
	gcc -I $(HEADER) $(LIB)  $(SRC) -g 
$(LIB):
	$(MAKE) -C ./libft/
clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJ)
fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(CW)
re: fclean all
