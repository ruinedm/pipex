/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:09 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/25 00:33:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int is_fd_open(int fd) 
{
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        return 0; 
    else 
        return 1;
}

void close_all_fds(t_node *input)
{
    t_node *first;

    first = ft_lstfirst(input);
    while(first)
    {
        if(is_a_command(first) && first->pipe_fds[0] != -1)
        {
            close(first->pipe_fds[0]);
            close(first->pipe_fds[1]);
        }
        first = first->next;
    }
}

static void smart_dup2(t_node *command_node, char *infile, char *outfile) 
{
    int infile_fd;
    int outfile_fd;

    if (command_node->type == FIRST_COMMAND) 
    {
        infile_fd = open(infile, O_RDONLY);
        dup2(infile_fd, STDIN_FILENO);
        dup2(command_node->pipe_fds[1], STDOUT_FILENO);
        close(infile_fd);
    }
    else if (command_node->type == LAST_COMMAND)
    {
        outfile_fd = open(outfile, O_WRONLY | O_CREAT , 0644);
        dup2(command_node->prev->pipe_fds[0], STDIN_FILENO);
        dup2(outfile_fd, STDOUT_FILENO);
        close(outfile_fd);
    } 
    else if (command_node->type == PIPED_COMMAND)
    {
        dup2(command_node->prev->pipe_fds[0], STDIN_FILENO);
        dup2(command_node->pipe_fds[1], STDOUT_FILENO);
    }
}

static void execute_command(char *infile, char *outfile, t_node *command_node, char **bin_paths, char **envp)
{
    int i;
    char *cmd_path;

    i = 0;
    smart_dup2(command_node, infile, outfile);
    close_all_fds(command_node);
    while(bin_paths[i])
    {
        cmd_path = ft_strjoin(bin_paths[i], command_node->input[0], DONT_FREE);
        if(execve(cmd_path, command_node->input, envp) == -1)
            i++;
    }
    perror("Error during executing command");
}
int fork_counter(int mode)
{
    static int i;

    if(mode == GET)
        return i;
    else
        i++;
    return -1;
}


void fork_and_execute(char *infile, char *outfile, t_node *input, int command_count, char **bin_paths, char **envp)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        if (command_count > 1)
            fork_and_execute(infile, outfile, input->next, command_count - 1, bin_paths, envp);
        execute_command(infile, outfile, input, bin_paths, envp);
    }
}
