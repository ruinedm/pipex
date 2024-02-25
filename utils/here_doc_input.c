/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:00:33 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/25 23:03:27 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void handle_here_doc_input(t_node *input, int tmp_file)
{
    char *limiter;
    char *input_str;

    if(tmp_file == -1)
    {
        perror("Tmp file open");
        exit(EXIT_FAILURE);
    }
    limiter = input->next->input[0];
    limiter = ft_strjoin(limiter, "\n", DONT_FREE);
    write(1, "here_doc> ", 10);
    input_str = get_next_line(0);
    while(input_str && ft_strcmp(input_str, limiter) != 0)
    {
        write(tmp_file, input_str, ft_strlen(input_str));
        free(input_str);
        write(1, "here_doc> ", 10);
        input_str = get_next_line(0);
    }
}
void shapeshift_here_doc(t_node *input)
{
    input->type = INFILE;
    input->input = ft_split("/tmp/.here_doc", ' ');
    input->next = input->next->next;
    input->next->type = FIRST_COMMAND;
}
