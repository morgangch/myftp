##
## EPITECH PROJECT, 2025
## myftp
## File description:
## Makefile
##

CC = g++
CFLAGS = -Wall -Wextra -Iinclude
SRC = 	src/main.cpp src/auth.cpp src/client.cpp src/command_handler.cpp src/ftp_server.cpp src/session.cpp src/transfer.cpp src/directory.cpp

NAME = myftp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ):
	$(CC) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(NAME)

fclean: clean
	rm -f $(NAME)
re: fclean all
debug: CFLAGS += -g3
debug: re

.PHONY: all clean fclean re debug