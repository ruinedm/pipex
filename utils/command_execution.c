/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:09 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/20 22:19:35 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


void print_open(t_node *first, int mode)
{
    FILE *log_file = fopen("log.txt", "a");
    if(mode == 1)
        fprintf(log_file, "START RUN FROM PID: %i\n", getpid());
    else
        fprintf(log_file, "END RUN FROM PID: %i\n", getpid());
    first = ft_lstfirst(first);
    while(first)
    {
        if(is_a_command(first) && first->pipe_fds[0] != -1)
            fprintf(log_file, "READ: %i // WRITE: %i // CMD %s\n", first->pipe_fds[0], first->pipe_fds[1], first->input[0]);
        first = first->next;
    }
    fprintf(log_file, "-----------------------\n");
    fclose(log_file);
}

void close_all_fds(t_node *input)
{
    input = ft_lstfirst(input);
    while(input)
    {
        if(is_a_command(input))
        {
            close(input->pipe_fds[0]);
            close(input->pipe_fds[1]);
        }
        input = input->next;
    }
}
static void smart_dup2(t_node *command_node, char *infile, char *outfile) 
{
    int infile_fd;
    int outfile_fd;

    infile_fd = open(infile, O_RDONLY);
    outfile_fd = open(outfile, O_WRONLY | O_CREAT , 0644);
    
    if (command_node->type == FIRST_COMMAND) 
    {
        dup2(infile_fd, STDIN_FILENO);
        dup2(command_node->pipe_fds[1], STDOUT_FILENO);
    }
    else if (command_node->type == LAST_COMMAND) 
    {
        dup2(command_node->prev->pipe_fds[0], STDIN_FILENO);
        dup2(outfile_fd, STDOUT_FILENO);
    } 
    else if (command_node->type == PIPED_COMMAND)
    {
        dup2(command_node->prev->pipe_fds[0], STDIN_FILENO);
        dup2(command_node->pipe_fds[1], STDOUT_FILENO);
    }
    close(infile_fd);
    close(outfile_fd);
}

static void execute_command(char *infile, char *outfile, t_node *command_node, char **bin_paths, char **envp)
{
    int i;
    char *cmd_path;

    i = 0;
    smart_dup2(command_node, infile, outfile);
    
    while(bin_paths[i])
    {
        cmd_path = ft_strjoin(bin_paths[i], command_node->input[0], DONT_FREE);
        if(execve(cmd_path, command_node->input, envp) == -1)
            i++;
    }
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
        close_all_fds(input);
        if (command_count > 1)
            fork_and_execute(infile, outfile, input->prev, command_count - 1, bin_paths, envp);
        else
            execute_command(infile, outfile, input, bin_paths, envp);
        exit(0);
    }
    else
    {
        close_all_fds(input);
        waitpid(pid, NULL, 0);
    }
}
