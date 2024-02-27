

#include "../pipex.h"

static void	add_command_node(t_node **head, char *command_str, int type)
{
	char	**command_array;
	t_node	*cmd_node;

	command_array = ft_split(command_str, ' ');
	if (!command_array)
		handle_error(head);
	cmd_node = ft_lstnew(command_array, (*head)->infile, (*head)->outfile);
	if (!cmd_node)
	{
		free(command_array);
		handle_error(head);
	}
	cmd_node->type = type;
	ft_lstadd_back(head, cmd_node);
}

static void	handle_parsing(t_node **head, char **argv, int input_count,
		int limiter_type)
{
	int	i;

	i = 3;
	add_command_node(head, argv[2], limiter_type);
	while (i < input_count)
	{
		add_command_node(head, argv[i], PIPED_COMMAND);
		i++;
	}
	add_command_node(head, argv[input_count - 1], LAST_COMMAND);
	add_command_node(head, argv[input_count], OUTFILE);
}

t_node	*parser(int input_count, char **argv)
{
	int		i;
	t_node	*head;
	char	**first_cmd_arr;

	first_cmd_arr = ft_split(argv[1], ' ');
	head = ft_lstnew(first_cmd_arr, argv[1], argv[input_count]);
	if (!head)
		return (perror("Mallocation error"), exit(EXIT_FAILURE), NULL);
	if (access(argv[1], F_OK))
		return (perror("Error when opening infile"), ft_lstclear(head),
			exit(EXIT_FAILURE), NULL);
	head->type = INFILE;
	handle_parsing(&head, argv, input_count, FIRST_COMMAND);
	return (head);
}
