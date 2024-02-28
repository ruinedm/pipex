CC = cc
FLAGS = -Wall -Wextra -Werror

NAME = pipex
SRC = pipex.c utils/command_execution.c utils/execution_helpers.c utils/linked_list_utils.c utils/parser.c utils/general_utils.c utils/paths_utils.c utils/str_utils/ft_split.c utils/str_utils/general_str_utils.c utils/str_utils/ft_strjoin.c
OBJ = $(SRC:.c=.o)
INCLUDE = pipex.h

BONUS_SRC = bonus/bonus_pipex.c bonus/utils/bonus_command_execution.c bonus/utils/bonus_execution_helpers.c bonus/utils/bonus_here_doc_input.c bonus/utils/bonus_get_next_line/bonus_get_next_line.c bonus/utils/bonus_get_next_line/bonus_get_next_line_utils.c bonus/utils/bonus_linked_list_utils.c bonus/utils/bonus_parser.c bonus/utils/bonus_general_utils.c bonus/utils/bonus_paths_utils.c bonus/utils/bonus_str_utils/bonus_ft_split.c bonus/utils/bonus_str_utils/bonus_general_str_utils.c bonus/utils/bonus_str_utils/bonus_ft_strjoin.c bonus/utils/bonus_str_utils/bonus_ft_itoa.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)
BONUS_INCLUDE = bonus/bonus_pipex.h
BONUS_NAME = pipex_bonus

all: $(NAME)

$(NAME): $(OBJ)
	@($(CC) $(FLAGS) $(OBJ) -g -o $@)
	@echo "Executable linked successfully!"

$(OBJ): $(INCLUDE)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	@($(CC) $(FLAGS) $^ -g -o $@)
	@echo "Bonus executable linked successfully!"

$(BONUS_OBJ): $(BONUS_INCLUDE)

%.o: %.c
	@($(CC) $(FLAGS) -c -g $< -o $@)
	@echo "Compiled $<"

clean:
	@rm -f $(OBJ)
	@rm -f $(BONUS_OBJ)
	@echo "Cleaned object files for both mandatory and bonus"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@rm -f $(BONUS_OBJ)
	@echo "Cleaned executables for both mandatory and bonus"

re: fclean all
