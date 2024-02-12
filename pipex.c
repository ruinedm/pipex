/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:16 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/12 02:15:22 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_alias_cmd(char *file,char *cmd,char** envp)
{
    char *try_cmd;
    char *tmp_cmd;
    char **binary_paths;
    char **argv_excve;
    int i;

    i = 0;
    binary_paths = get_paths(envp);
    try_cmd = ft_strjoin(binary_paths[i],cmd, DONT_FREE);
    argv_excve = malloc(2 * sizeof(char *));
    argv_excve[0] = try_cmd;
    argv_excve[1] = NULL;
    while(execve(try_cmd ,argv_excve, envp) == -1 && binary_paths[i] != NULL)
    {
        // printf("ITERATION %i\n", i);
        i++;
        try_cmd = ft_strjoin(binary_paths[i],cmd, FREE_S1);
        argv_excve[0] = try_cmd;
        argv_excve[1] = NULL;
        print_to_debug(try_cmd);
    }
    perror("Command not found in any of the binary directories");
    free(argv_excve);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
    char *infile;
    char *outfile;
    char *cmd1;
    char *cmd2;
    int infile_fd;
    int outfile_fd;
    char **argv_excve;
    pid_t cmd1_process;
	int pipe_fds[2];
	int cmd1_type;
    // if (argc != 5) {
    //     printf("Usage: %s <infile> <cmd1> <cmd2> <outfile>\n", argv[0]);
    //     return 1;
    // }
    infile = argv[1];
    outfile = argv[4];
    cmd1 = argv[2];
    cmd2 = argv[3];
	pipe(pipe_fds);
    infile_fd = open(infile, O_RDONLY);
	cmd1_type = get_command_type(cmd1);
    argv_excve = malloc(2 * sizeof(char *));
	if(!cmd1_type)
	{
		perror("Error, invalid command!");
		exit(EXIT_FAILURE);
	}
    cmd1_process = fork();
    if(cmd1_process)
    {
        print_to_debug("I AM THE PARENT!");
		close(pipe_fds[0]);
		dup2(pipe_fds[1], 1);
		if(cmd1_type == PATH_CMD)
		{
            argv_excve[0] = cmd1;
            argv_excve[1] = NULL;
            if(execve(cmd1, argv_excve, envp) == -1)
            {
                perror("Error\n");
                return 1;
            }
		}
        else if (cmd1_type == ALIAS_CMD)
            execute_alias_cmd(infile,cmd1, envp);
    }
	else
    {
        print_to_debug("I AM THE CHILD!");
		close(pipe_fds[1]);
    }
    return 0;
}
