/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:10:09 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/17 10:30:45 by mboukour         ###   ########.fr       */
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

static void add_file(char *file, char **par_arr)
{
    int i;

    i = 0;
    while(par_arr[i])
        i++;
    par_arr[i] = file;
}

static void execute_command(char *infile, char *outfile, t_node *command_node, char **bin_paths, char **envp)
{
    int i;
    char *cmd_path;

    if(command_node->type == FIRST_COMMAND)
        add_file(infile, command_node->input);
    i = 0;
    while(bin_paths[i])
    {
        cmd_path = ft_strjoin(bin_paths[i], command_node->input[0], DONT_FREE);
        if(execve(cmd_path, command_node->input, envp) == -1)
            i++;
    }
}


void fork_and_execute(char *infile, char *outfile, t_node *input, int command_count, char **bin_paths, char **envp)
{
    pid_t pid;
    int pipe_fds[2];


    if (command_count == 1) {
        close(read_end);
        dup2(write_end, 1);

        // execute_command(infile, outfile, input, bin_paths, envp);
        return;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    }

    if (!pid) 
    {
        close(read_end);
        close(write_end); 

        fork_and_execute(infile, outfile, input->prev, command_count - 1, bin_paths, envp);
    }
    else 
    {
        close(write_end);
        dup2(read_end, 0);
        close(read_end);

        waitpid(pid, NULL, 0);
        execute_command(infile, outfile, input, bin_paths, envp);
    }
}
