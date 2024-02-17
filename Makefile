CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = pipex
SRC = pipex.c utils/command_execution.c utils/here_doc_input.c utils/get_next_line/get_next_line.c utils/get_next_line/get_next_line_utils.c utils/linked_list_utils.c utils/parser.c utils/general_utils.c utils/paths_utils.c utils/str_utils/ft_split.c utils/str_utils/general_str_utils.c utils/str_utils/ft_strjoin.c debug.c
OBJ = $(SRC:.c=.o)
INCLUDE = pipex.h
all: $(NAME) clean

$(NAME): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c $(INCLUDE)
	$(CC) -c $< -o $@


clean:
	rm -f $(OBJ)


fclean: clean
	rm -f $(NAME)
	rm -f debug_file.txt
re: fclean all