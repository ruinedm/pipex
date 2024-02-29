/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:09:50 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/29 22:51:36 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	ft_lstset(t_node *node, int mode, int to_set)
{
	t_node	*first;

	first = ft_lstfirst(node);
	if (mode == INFILE)
	{
		while (first)
		{
			first->infile_fd = to_set;
			first = first->next;
		}
	}
	else if (mode == OUTFILE)
	{
		while (first)
		{
			first->outfile_fd = to_set;
			first = first->next;
		}
	}
}

void	dumb_dup2(int old, int new, t_node *command_node)
{
	t_node	*first;

	first = ft_lstfirst(command_node);
	if (dup2(old, new) == -1)
	{
		smarter_close(command_node->infile_fd);
		smarter_close(command_node->outfile_fd);
		close_all_fds(command_node);
		handle_error(&first);
	}
}

int	dumb_open(t_node *command_node, int mode)
{
	t_node	*first;
	int		i;

	i = 0;
	first = ft_lstfirst(command_node);
	if (mode == INFILE)
		i = open(command_node->infile, O_RDONLY, 0777);
	else if (mode == OUTFILE)
		i = open(command_node->outfile, O_WRONLY | O_CREAT
				| O_TRUNC, 0777);
	if (i == -1)
	{
		if (mode == OUTFILE)
			smarter_close(command_node->infile_fd);
		close_all_fds(command_node);
		handle_error(&first);
	}
	else
		ft_lstset(command_node, mode, i);
	return (i);
}
