CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = pipex
SRC = pipex.c utils/general_utils.c utils/paths_utils.c utils/str_utils/ft_split.c utils/str_utils/general_str_utils.c utils/str_utils/ft_strjoin.c debug.c
OBJ = $(SRC:.c=.o)
INCLUDE = pipex.h
all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $^ -o $@

%.o: %.c $(INCLUDE)
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f debug_file.txt
re: fclean all