/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_general_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:41 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/27 22:55:14 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_pipex.h"

int	is_a_command(t_node *node)
{
	if (node->type == FIRST_COMMAND || node->type == PIPED_COMMAND
		|| node->type == LAST_COMMAND)
		return (TRUE);
	return (FALSE);
}

int	count_commands(t_node *input)
{
	int	count;

	count = 0;
	while (input)
	{
		if (input->type == FIRST_COMMAND || input->type == PIPED_COMMAND
			|| input->type == LAST_COMMAND)
			count++;
		input = input->next;
	}
	return (count);
}

void	handle_error(t_node **head)
{
	if (!ft_strcmp("here_doc", (*head)->input[0]))
	{
		unlink((*head)->infile);
		free((*head)->infile);
	}
	ft_lstclear(*head);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	ft_clearone(t_node *node)
{
	int	i;

	i = 0;
	while (node->input[i])
	{
		free(node->input[i]);
		i++;
	}
	free(node->input);
	free(node);
}
