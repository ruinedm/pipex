/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_here_doc_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:48 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/28 03:57:31 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_pipex.h"

static	void	smarter_handle_error(char *here_doc_path, int here_doc_fd,
				t_node *head)
{
	unlink(here_doc_path);
	free(here_doc_path);
	close(here_doc_fd);
	handle_error(&head);
}

static void	shift_infile(t_node *lst, char *here_doc_path, int here_doc_fd)
{
	lst = ft_lstfirst(lst);
	while (lst != NULL)
	{
		lst->infile = here_doc_path;
		lst->here_doc_fd = here_doc_fd;
		lst = lst->next;
	}
}

static void	shapeshift_here_doc(t_node *input, char *here_doc_path,
		int here_doc_fd)
{
	t_node	*next_node;
	t_node	*double_next;

	next_node = input->next;
	double_next = input->next->next;
	shift_infile(input, here_doc_path, here_doc_fd);
	double_next->prev = input;
	input->next = double_next;
	input->next->type = FIRST_COMMAND;
	ft_clearone(next_node);
}

void	handle_here_doc_input(t_node *input, int tmp_file, char *here_doc_path)
{
	char	*limiter;
	char	*input_str;

	limiter = input->next->input[0];
	limiter = ft_strjoin(limiter, "\n", DONT_FREE);
	if (!limiter)
		smarter_handle_error(here_doc_path, tmp_file, input);
	write(1, "here_doc> ", 10);
	input_str = get_next_line(0, input);
	while (input_str && ft_strcmp(input_str, limiter) != 0)
	{
		write(tmp_file, input_str, ft_strlen(input_str));
		free(input_str);
		write(1, "here_doc> ", 10);
		input_str = get_next_line(0, input);
	}
	free(limiter);
	free(input_str);
	if (!input_str)
		smarter_handle_error(here_doc_path, tmp_file, input);
	shapeshift_here_doc(input, here_doc_path, tmp_file);
}
