
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC = main.c utils.c routine.c init.c ft_gc.c
RM = rm -f


#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)


clean:
	@printf "$(GRAY)	-nothing to clean since no obbject files are created \n"

fclean: clean
	$(RM) $(NAME)

re: fclean all

