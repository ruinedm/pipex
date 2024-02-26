/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_here_doc_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:00:33 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/27 00:45:42 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_pipex.h"

void	handle_here_doc_input(t_node *input, int tmp_file)
{
	char	*limiter;
	char	*input_str;
	char	*old;

	if (tmp_file == -1)
	{
		perror("Tmp file open");
		exit(EXIT_FAILURE);
	}
	limiter = input->next->input[0];
	limiter = ft_strjoin(limiter, "\n", DONT_FREE);
	write(1, "here_doc> ", 10);
	input_str = get_next_line(0);
	while (input_str && ft_strcmp(input_str, limiter) != 0)
	{
		write(tmp_file, input_str, ft_strlen(input_str));
		free(input_str);
		write(1, "here_doc> ", 10);
		input_str = get_next_line(0);
	}
	free(limiter);
	free(input_str);
	if (!input_str)
		return (unlink("/tmp/.here_doc"), handle_error(&input));
}

void	shift_infile(t_node *lst)
{
	t_node	*tmp;

	lst = ft_lstfirst(lst);
	while (lst != NULL)
	{
		lst->infile = "/tmp/.here_doc";
		lst = lst->next;
	}
}

void	shapeshift_here_doc(t_node *input)
{
	t_node	*next_node;
	t_node	*double_next;

	next_node = input->next;
	double_next = input->next->next;
	shift_infile(input);
	double_next->prev = input;
	input->next = double_next;
	input->next->type = FIRST_COMMAND;
	ft_clearone(next_node);
}