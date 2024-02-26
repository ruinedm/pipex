/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:27:31 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/26 23:41:19 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	is_a_command(t_node *node)
{
	if (node->type == FIRST_COMMAND || node->type == PIPED_COMMAND
		|| node->type == LAST_COMMAND)
		return (TRUE);
	return (FALSE);
}

static int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
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
