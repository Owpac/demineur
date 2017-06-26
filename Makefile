# définition des cibles particulières
.PHONY: clean, fclean, build, rebuild
 
# désactivation des règles implicites
.SUFFIXES:

# définition des variables
EXEC = Demineur

SRC = main.c\
	matrice.c\
	shuffle.c\
	secure.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra

RED = \033[1;31m
GREEN = \033[1;32m
NC = \033[0m

all : $(EXEC) 

$(EXEC) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)
	@echo "$(GREEN)[✓]$(NC) Executable $(EXEC) created"

$(OBJ) : $(SRC)
	@$(CC) $(CFLAGS) -c $(SRC)
	@echo "$(GREEN)[✓]$(NC) Objects compiled"

build : all clean

re : fclean all

clean :
	@rm -rf $(OBJ)
	@echo "$(RED)[-]$(NC) Objects $(OBJ) cleaned"
 
fclean : clean
	@rm -rf $(NAME)
	@echo "$(RED)[-]$(NC) Executable $(EXEC) cleaned"
