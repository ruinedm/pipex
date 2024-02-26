/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:16 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/26 20:28:04 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



static void pipe_the_commands(t_node *cmd, int pipe_count)
{
    int i;

    i = 0;
    while(i < pipe_count)
    {
        pipe(cmd->pipe_fds);
        cmd = cmd->next;
        i++;
    }
}

void print(char *infile, char *outfile, char **input, int type, int *pipe_fds)
{
    printf("INFILE %s // OUTFILE %s // COMMAND %s // TYPE: %i // READ END PIPE: %i // WRITE END PIPE :%i\n",infile, outfile, input[0], type, pipe_fds[0], pipe_fds[1]);
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
    ft_lstiter(input, print);
    fork_and_execute(input->next, count_commands(input), envp);
    close_all_fds(input);
    while (wait(NULL) != -1);
    unlink("/tmp/.here_doc");
    ft_lstclear(input);
}
