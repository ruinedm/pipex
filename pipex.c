/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:16 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/26 21:25:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void pipe_the_commands(t_node *cmd, int pipe_count)
{
    int i;
    t_node *first;

    i = 0;
    first = ft_lstfirst(cmd);
    while(i < pipe_count)
    {
        if(pipe(cmd->pipe_fds) == -1)
        {
            close_all_fds(cmd);
            handle_error(&first);
        }
        cmd = cmd->next;
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_node *input;

    if (argc < 5)
    {
        printf("Usage: ./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>\nOr: ./pipex here_doc <LIMITER> <cmd1> <cmd2> <cmd3> ... <outfile>\n");
        return 1;
    }
    input = parser(argc - 1, argv);
    pipe_the_commands(input->next, count_commands(input) - 1);
    fork_and_execute(input->next, count_commands(input), envp);
    close_all_fds(input);
    while (wait(NULL) != -1);
    unlink("/tmp/.here_doc");
    ft_lstclear(input);
}
