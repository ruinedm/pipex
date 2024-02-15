/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:00:33 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/15 10:26:34 by mboukour         ###   ########.fr       */
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
    limiter = input->next->input;
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

