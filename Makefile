CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = pipex
SRC = pipex.c utils/command_execution.c utils/here_doc_input.c utils/get_next_line/get_next_line.c utils/get_next_line/get_next_line_utils.c utils/linked_list_utils.c utils/parser.c utils/general_utils.c utils/paths_utils.c utils/str_utils/ft_split.c utils/str_utils/general_str_utils.c utils/str_utils/ft_strjoin.c debug.c
OBJ = $(SRC:.c=.o)
INCLUDE = pipex.h
all: $(NAME) clean

$(NAME): $(OBJ)
	@($(CC) $^ -o $@)
	@echo "Executable linked successfully!"

%.o: %.c $(INCLUDE)
	@($(CC) -c $< -o $@)
	@echo "Compiled $<"

clean:
	@rm -f $(OBJ)
	@echo "Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@rm -f debug_file.txt
	@rm -f log.txt
	@echo "Cleaned executable and debug files"

re: fclean all
