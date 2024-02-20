/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:09 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/20 16:48:26 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


static void execute_alias_cmd(char *file,char *cmd,char** envp)
{
    char *try_cmd;
    char *tmp_cmd;
    char **binary_paths;
    char **argv_excve;
    int i;

    i = 0;
    binary_paths = get_paths(envp);
    try_cmd = ft_strjoin(binary_paths[i],cmd, DONT_FREE);
    if(file)
    {
        argv_excve = malloc(3 * sizeof(char *));
        argv_excve[0] = try_cmd;
        argv_excve[1] = file;
        argv_excve[2] = NULL;
        while(execve(try_cmd ,argv_excve, envp) == -1 && binary_paths[i] != NULL)
        {
            i++;
            try_cmd = ft_strjoin(binary_paths[i],cmd, FREE_S1);
            argv_excve[0] = try_cmd;
            argv_excve[1] = file;
            argv_excve[2] = NULL;
        }
        perror("Command not found in any of the binary directories");
        free(argv_excve);
        exit(EXIT_FAILURE);
    }
    else
    {
        argv_excve = malloc(2 * sizeof(char *));
        argv_excve[0] = try_cmd;
        argv_excve[1] = NULL;
        while(execve(try_cmd ,argv_excve, envp) == -1 && binary_paths[i] != NULL)
        {
            i++;
            try_cmd = ft_strjoin(binary_paths[i],cmd, FREE_S1);
            argv_excve[0] = try_cmd;
            argv_excve[1] = NULL;
        }
        perror("Command not found in any of the binary directories");
        free(argv_excve);
        exit(EXIT_FAILURE);
    }
}

void print_open(t_node *first, int mode)
{
    if(mode == 1)
        printf("START RUN FROM PID: %i\n", getpid());
    else
        printf("END RUN FROM PID: %i\n", getpid());
    while(first)
    {
        if(is_a_command(first) && first->pipe_fds[0] != -1)
        {
            printf("READ: %i // WRITE: %i // CMD %s\n", first->pipe_fds[0], first->pipe_fds[1], first->input[0]);
        }
        first = first->next;
    }
    printf("-----------------------\n");
}

static void close_all_fds(t_node *input)
{
    t_node *first;
    first = ft_lstfirst(input);
    input = ft_lstfirst(input);
    print_open(first, 1);
    while(input)
    {
        if(is_a_command(input))
        {
            FILE *log_file = fopen("log.txt", "a");
            fprintf(log_file, "NEW FDS: READ: %i // WRITE %i\n", input->pipe_fds[0], input->pipe_fds[1]);
            fclose(log_file);
            close(input->pipe_fds[0]);
            close(input->pipe_fds[1]);
            input->pipe_fds[0] = -1;
            input->pipe_fds[1] = -1;
        }
        input = input->next;
    }
    print_open(first, 0);
}


static void execute_command(char *infile, char *outfile, t_node *command_node, char **bin_paths, char **envp)
{
    int i;
    char *cmd_path;

    i = 0;
    // while(bin_paths[i])
    // {
    //     cmd_path = ft_strjoin(bin_paths[i], command_node->input[0], DONT_FREE);
    //     if(execve(cmd_path, command_node->input, envp) == -1)
    //         i++;
    // }
    // printf("EXECUTE WAS CALLED\n");
    close_all_fds(command_node);
    
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

    if (command_count == 1)
    {
        execute_command(infile, outfile, input, bin_paths, envp);
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (!pid)
    {
        fork_counter(INCREMENT);
        fork_and_execute(infile, outfile, input->prev, command_count - 1, bin_paths, envp);
    }
    else 
    {
        waitpid(pid, NULL, 0);
        execute_command(infile, outfile, input, bin_paths, envp);
    }
}
