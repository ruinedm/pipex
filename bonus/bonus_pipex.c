/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:32:06 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/27 20:43:27 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static void	ft_putendl_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

static void	pipe_the_commands(t_node *cmd, int pipe_count)
{
	int		i;
	t_node	*first;

	i = 0;
	first = ft_lstfirst(cmd);
	while (i < pipe_count)
	{
		if (pipe(cmd->pipe_fds) == -1)
		{
			close_all_fds(cmd);
			handle_error(&first);
		}
		cmd = cmd->next;
		i++;
	}
}

static void print(char *infile, char *outfile, char **input, int type, int *pipe_fds)
{
    printf("INFILE %s // OUTFILE %s // COMMAND %s // TYPE: %i // READ END PIPE: %i // WRITE END PIPE :%i\n",infile,outfile, input[0], type, pipe_fds[0], pipe_fds[1]);
}

void ft_lstiter(t_node *lst, void (*f)(char *, char *, char **, int, int*))
{
    t_node *tmp;

    if (lst == NULL || f == NULL)
        return;

    while (lst != NULL) {
        tmp = lst->next;
        f(lst->infile, lst->outfile, lst->input, lst->type, lst->pipe_fds);
        lst = tmp;
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_node	*input;

	if (argc < 5 || (!ft_strcmp("here_doc", argv[1]) && argc < 6))
	{
		ft_putendl_fd("Usage: ./pipex <infile>", 2);
		ft_putendl_fd(" <cmd1> <cmd2> <cmd3> ... <outfile>\n", 2);
		ft_putendl_fd("Or: ./pipex here_doc <LIMITER> <cmd1>", 2);
		ft_putendl_fd(" <cmd2> <cmd3> ... <outfile>\n", 2);
		return (1);
	}
	input = parser(argc - 1, argv);
	ft_lstiter(input, print);
	// pipe_the_commands(input->next, count_commands(input) - 1);
	// fork_and_execute(input->next, count_commands(input), envp);
	// close_all_fds(input);
	// while (wait(NULL) != -1)
	// 	;
	// unlink("/tmp/.here_doc");
	// ft_lstclear(input);
}
