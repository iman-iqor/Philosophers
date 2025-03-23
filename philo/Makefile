
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC = main.c helpers1.c 


all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)


clean:
	rm -f $(SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all

