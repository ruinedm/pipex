/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:16 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/25 00:33:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


// static void create_fds_list(t_fd **head, int command_count)
// {
//     t_fd *new_pipe;
//     int i;

//     i = 0;
//     while(i < command_count)
//     {
//         new_pipe = ft_lstnew_int();
//         if(!new_pipe)
//             perror("Pipe t_fd mallocation error");
//         if(pipe(new_pipe->pipe_fds) == -1)
//             perror("Pipe() error");
//         ft_lstaddback_int(head, new_pipe);
//         i++;        
//     }
// }

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

static void print(char **input, int type, int *pipe_fds)
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

    tmp_file = -1;
    if (argc < 5)
    {
        printf("Usage: ./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>\nOr: ./piper here_doc <LIMITER> <cmd1> <cmd2> <cmd3> ... <outfile>\n");
        return 1;
    }
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
    command_count = count_commands(input);
    pipe_the_commands(input->next, command_count - 1);
    fork_and_execute(argv[1], argv[argc-1],input->next, command_count, bin_paths, envp);
    close_all_fds(input);
    while (wait(NULL) != -1);
}
