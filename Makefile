##
## EPITECH PROJECT, 2025
## PDGRUSH3
## File description:
## Makefile
##

NAME	=	myftp
SRC	=	$(wildcard ./*.cpp ./src/*.cpp ./src/handlers/*.cpp ./src/utils/*.cpp)
CFLAGS	=	-Wall -Wextra -Iinclude -Isrc -Isrc/handlers -I.
CC	=	/usr/bin/g++

all:	$(NAME)

$(NAME):	$(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ) *.gch src/*.gch

fclean: clean
	rm -f $(NAME)

re: fclean all

test: 
	$(CC) -o $(NAME) $(SRC) -lcriterion --coverage $(CFLAGS)
	
tests_run: test
	./$(NAME)

tests_re: fclean tests_run

tests_gcovr: tests_re
	gcovr --exclude tests/

debug: CFLAGS += -g3
debug: re