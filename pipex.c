/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:30:11 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/27 18:44:05 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_putstr(char *str, int fd)
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

int	main(int argc, char **argv, char **envp)
{
	t_node	*input;

	if (argc != 5)
	{
		ft_putstr("Usage: ./pipex <infile>", 2);
		ft_putstr(" <cmd1> <cmd2> <outfile>\n", 2);
		return (1);
	}
	input = parser(argc - 1, argv);
	pipe_the_commands(input->next, count_commands(input) - 1);
	fork_and_execute(input->next, count_commands(input), envp);
	close_all_fds(input);
	while (wait(NULL) != -1)
		;
	unlink("/tmp/.here_doc");
	ft_lstclear(input);
}
