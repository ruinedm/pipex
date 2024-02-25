/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:16 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/25 23:16:24 by mboukour         ###   ########.fr       */
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

void print(char **input, int type, int *pipe_fds)
{
    printf("COMMAND %s // TYPE: %i // READ END PIPE: %i // WRITE END PIPE :%i\n", input[0], type, pipe_fds[0], pipe_fds[1]);
}

int main(int argc, char **argv, char **envp)
{
    t_node *input;
    int input_count;
    int tmp_file;
    char **bin_paths;
    int infile_fd;
    int command_count;
    char *infile;

    tmp_file = -1;
    if (argc < 5)
    {
        printf("Usage: ./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>\nOr: ./piper here_doc <LIMITER> <cmd1> <cmd2> <cmd3> ... <outfile>\n");
        return 1;
    }
    input_count = argc - 1;
    input = parser(input_count, argv);
    bin_paths = get_paths(envp);
    infile = argv[1];
    if(input->type == HERE_DOC)
    {
        infile = "/tmp/.here_doc";
        tmp_file = open("/tmp/.here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
        handle_here_doc_input(input, tmp_file);
        shapeshift_here_doc(input);
    }
    command_count = count_commands(input);
    pipe_the_commands(input->next, command_count - 1);
    fork_and_execute(infile, argv[argc-1],input->next, command_count, bin_paths, envp);
    close_all_fds(input);
    while (wait(NULL) != -1);
    if(tmp_file != -1)
    {
        close(tmp_file);
        unlink("/tmp/.here_doc");
    }
    ft_lstclear(input);
    free_paths(bin_paths);
}
