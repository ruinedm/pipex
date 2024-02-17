/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:16 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/17 10:21:32 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int main(int argc, char **argv, char **envp)
{
    t_node *input;
    int pipe_fds[2];
    int input_count;
    int tmp_file;
    char **bin_paths;

    tmp_file = -1;
    // if (argc < 5)
    // {
    //     printf("Usage: ./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>\nOr: ./piper here_doc <LIMITER> <cmd1> <cmd2> <cmd3> ... <outfile>\n");
    //     return 1;
    // }
    input_count = argc - 1;
    input = parser(input_count, argv);
    bin_paths = get_paths(envp);
    if(input->type == HERE_DOC)
    {
        tmp_file = open("/tmp/.here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
        handle_here_doc_input(input, tmp_file);
    }
    if(tmp_file != -1)
    {
        close(tmp_file);
        unlink("/tmp/.here_doc");
    }
    printf("PARENT PID: %i\n", getpid());
    pipe(pipe_fds);
    fork_and_execute(input->input[0], ft_lstlast(input)->input[0],ft_lstlast(input)->prev, input_count - 2,bin_paths, envp);
    close(pipe_fds[0]);
    close(pipe_fds[1]);
}
