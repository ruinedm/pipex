/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:09:50 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/27 20:17:40 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


void	dumb_dup2(int old, int new, t_node* command_node)
{
	t_node	*first;

	first = ft_lstfirst(command_node);
	if (dup2(old, new) == -1)
	{
		close_all_fds(command_node);
		handle_error(&first);
	}

}

int		dumb_open(t_node *command_node, int mode)
{
	t_node	*first;
	int i;

	first = ft_lstfirst(command_node);
	if(mode == INFILE)
		i = open(command_node->infile, O_RDONLY, 0777);
	else if (mode == OUTFILE)
		i = open(command_node->outfile, O_WRONLY | O_CREAT
			| O_TRUNC, 0777);
	if(i == -1)
	{
		close_all_fds(command_node);
		handle_error(&first);
	}
	return (i);
}

