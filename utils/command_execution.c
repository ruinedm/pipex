/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:09 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/25 00:32:02 by codespace        ###   ########.fr       */
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

void print_fds(t_node *first)
{
    FILE *log_file = fopen("logfd", "a");
    fprintf(log_file, "FDS ANALYSIS ON PID %i\n", getpid());
    while(first)
    {
        if(first->pipe_fds[0] != -1)
        {
            if(is_fd_open(first->pipe_fds[0]))
                fprintf(log_file, "INPUT: %s // FD 0 IS OPEN: %i", first->input[0], first->pipe_fds[0]);
            else
                fprintf(log_file, "INPUT %s // FD 0 IS CLOSED: %i", first->input[0], first->pipe_fds[0]);

            if(first->pipe_fds[1] != -1)
            {
                if(is_fd_open(first->pipe_fds[1]))
                    fprintf(log_file, " // FD 1 IS OPEN: %i\n", first->pipe_fds[1]);
                else
                    fprintf(log_file, " // FD 1 IS CLOSED: %i\n", first->pipe_fds[1]);
            }
            else
                fprintf(log_file, "\n");
        }

        first = first->next;
    }
    fclose(log_file);
}

void close_all_fds(t_node *input)
{
    t_node *first;
    int no_touchy;

    first = ft_lstfirst(input);
    FILE *logfile = fopen("logclose", "a");
    fprintf(logfile, "CLOSE CALLED ON PID: %i\n", getpid());
    while(first)
    {
        if(is_a_command(first) && first->pipe_fds[0] != -1)
        {
            fprintf(logfile, "CLOSING: [%i] RESULT: %i\n",first->pipe_fds[0], close(first->pipe_fds[0]));
            fprintf(logfile, "CLOSING: [%i] RESULT: %i\n",first->pipe_fds[1], close(first->pipe_fds[1]));
        }
        first = first->next;
    }
    fclose(logfile);
}
static void smart_dup2(t_node *command_node, char *infile, char *outfile) 
{
    int infile_fd;
    int outfile_fd;
    pid_t pid = getpid(); // Get the PID of the current process

    FILE *log_file = fopen("logdup.txt", "a");
    if (command_node->type == FIRST_COMMAND) 
    {
        infile_fd = open(infile, O_RDONLY);
        fprintf(log_file, "PID %d: INFILE DUP2(%d, %d) RESULT: %d\n", pid, infile_fd, STDIN_FILENO, dup2(infile_fd, STDIN_FILENO));
        fprintf(log_file, "PID %d: FIRST CMD WRITE END DUP2(%d, %d) RESULT: %d\n", pid, command_node->pipe_fds[1], STDOUT_FILENO, dup2(command_node->pipe_fds[1], STDOUT_FILENO));
        close(infile_fd);
    }
    else if (command_node->type == LAST_COMMAND)
    {
        outfile_fd = open(outfile, O_WRONLY | O_CREAT , 0644);
        fprintf(log_file, "PID %d: LAST CMD PREV READ END DUP2(%d, %d) RESULT: %d\n", pid, command_node->prev->pipe_fds[0], STDIN_FILENO, dup2(command_node->prev->pipe_fds[0], STDIN_FILENO));
        fprintf(log_file, "PID %d: OUTFILE DUP2(%d, %d) RESULT: %d\n", pid, outfile_fd, STDOUT_FILENO, dup2(outfile_fd, STDOUT_FILENO));
        close(outfile_fd);
    } 
    else if (command_node->type == PIPED_COMMAND)
    {
        fprintf(log_file, "PID %d: DUPED CMD PREV READ END DUP2(%d, %d) RESULT: %d\n", pid, command_node->prev->pipe_fds[0], STDIN_FILENO, dup2(command_node->prev->pipe_fds[0], STDIN_FILENO));
        fprintf(log_file, "PID %d: DUPED CMD WRITE END DUP2(%d, %d) RESULT: %d\n", pid, command_node->pipe_fds[1], STDOUT_FILENO, dup2(command_node->pipe_fds[1], STDOUT_FILENO));
    }
    fclose(log_file);
}

static void execute_command(char *infile, char *outfile, t_node *command_node, char **bin_paths, char **envp)
{
    int i;
    char *cmd_path;

    i = 0;
    // print_fds(ft_lstfirst(command_node));
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
