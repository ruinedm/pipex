/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_execution_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:50:35 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/27 22:54:21 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_pipex.h"

void	dumb_dup2(int old, int new, t_node *command_node)
{
	t_node	*first;

	first = ft_lstfirst(command_node);
	if (dup2(old, new) == -1)
	{
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
		i = open(command_node->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (i == -1)
	{
		close_all_fds(command_node);
		handle_error(&first);
	}
	return (i);
}

char	*get_here_doc_path(t_node *first)
{
	int		i;
	char	*str;
	char	*num;

	i = 0;
	while (TRUE)
	{
		num = ft_itoa(i);
		if (!num)
			return (close_all_fds(first), handle_error(&first), NULL);
		str = ft_strjoin("/tmp/.here_doc", num, FREE_S2);
		if (!str)
			return (free(num), close_all_fds(first), handle_error(&first),
				NULL);
		if (access(str, F_OK) == -1)
			return (str);
		free(str);
		i++;
	}
}
