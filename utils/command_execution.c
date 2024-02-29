/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:30:47 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/29 22:42:51 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	close_all_fds(t_node *input)
{
	t_node	*first;

	first = ft_lstfirst(input);
	while (first)
	{
		if (is_a_command(first) && first->pipe_fds[0] != -1)
		{
			smarter_close(first->pipe_fds[0]);
			smarter_close(first->pipe_fds[1]);
		}
		first = first->next;
	}
}

static void	smart_dup2(t_node *command_node)
{
	int	infile_fd;
	int	outfile_fd;

	if (command_node->type == FIRST_COMMAND)
	{
		infile_fd = dumb_open(command_node, INFILE);
		dumb_dup2(infile_fd, STDIN_FILENO, command_node);
		dumb_dup2(command_node->pipe_fds[1], STDOUT_FILENO, command_node);
		smarter_close(infile_fd);
	}
	else if (command_node->type == LAST_COMMAND)
	{
		outfile_fd = dumb_open(command_node, OUTFILE);
		dumb_dup2(command_node->prev->pipe_fds[0], STDIN_FILENO, command_node);
		dumb_dup2(outfile_fd, STDOUT_FILENO, command_node);
		smarter_close(outfile_fd);
	}
	else if (command_node->type == PIPED_COMMAND)
	{
		dumb_dup2(command_node->prev->pipe_fds[0], STDIN_FILENO, command_node);
		dumb_dup2(command_node->pipe_fds[1], STDOUT_FILENO, command_node);
	}
}

static void	execute_command(t_node *command_node, char **envp)
{
	int		i;
	char	*cmd_path;
	char	**bin_paths;
	t_node	*first;

	i = 0;
	first = ft_lstfirst(command_node);
	smart_dup2(command_node);
	close_all_fds(command_node);
	execve(command_node->input[0], command_node->input, envp);
	bin_paths = get_paths(envp, first);
	while (bin_paths[i])
	{
		cmd_path = ft_strjoin(bin_paths[i], command_node->input[0], DONT_FREE);
		if (!cmd_path)
			return (free_paths(bin_paths), handle_error(&first));
		if (execve(cmd_path, command_node->input, envp) == -1)
		{
			free(cmd_path);
			i++;
		}
	}
	free_paths(bin_paths);
	handle_error(&first);
}

void	fork_and_execute(t_node *input, int command_count, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_lstclear(input);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (command_count > 1)
			fork_and_execute(input->next, command_count - 1, envp);
		execute_command(input, envp);
	}
}
