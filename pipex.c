/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:16 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/14 15:44:00 by mboukour         ###   ########.fr       */
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

// int main(int argc, char **argv, char **envp)
// {
//     char *infile;
//     char *outfile;
//     int outfile_fd;
//     char *cmd1;
//     char *cmd2;
//     char **cmd_1_argv_excve;
//     char **cmd_2_argv_excve;
//     pid_t cmd1_process;
// 	   int pipe_fds[2];
// 	     int cmd1_type;
// 	   int cmd2_type;
//     t_node *input;
//     if (argc < 5) 
//     {
//         printf("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n");
//         return 1;
//     }
//     infile = argv[1];
//     outfile = argv[4];
//     if(access(infile, F_OK))
//     {
//         printf("Invalid infile: %s doesn't exist!\n", infile);
//         return 1;
//     }
//     cmd1 = argv[2];
//     cmd2 = argv[3];
// 	pipe(pipe_fds);
// 	cmd1_type = get_command_type(cmd1);
//     cmd2_type = get_command_type(cmd2);
//     cmd_1_argv_excve = malloc(3 * sizeof(char *));
//     cmd_2_argv_excve = malloc(2 * sizeof(char *));
// 	if(!cmd1_type || !cmd2_type)
// 	{
// 		perror("Error, invalid command!");
// 		exit(EXIT_FAILURE);
// 	}
//     cmd1_process = fork();
//     if(cmd1_process == -1)
//     {
//         perror("Error with fork");
//         return 1;
//     }
//     else if(cmd1_process == 0)
//     {
// 		close(pipe_fds[0]);
// 		dup2(pipe_fds[1], 1);
// 		if(cmd1_type == PATH_CMD)
// 		{
//             cmd_1_argv_excve[0] = cmd1;
//             cmd_1_argv_excve[1] = infile;
//             cmd_1_argv_excve[2] = NULL;
//             if(execve(cmd1, cmd_1_argv_excve, envp) == -1)
//             {
//                 perror("Error\n");
//                 return 1;
//             }
// 		}
//         else if (cmd1_type == ALIAS_CMD)
//             execute_alias_cmd(infile,cmd1, envp);
//     }
// 	else
//     {
// 		close(pipe_fds[1]);
//         wait(NULL);
//         outfile_fd = open(outfile, O_CREAT | O_RDWR, 0777);
//         dup2(outfile_fd, 1);
//         close(outfile_fd);
//         dup2(pipe_fds[0], 0);
//         if(cmd2_type == PATH_CMD)
//         {
//             cmd_2_argv_excve[0] = cmd2;
//             cmd_2_argv_excve[1] = NULL;
//             if(execve(cmd2, cmd_2_argv_excve, envp) == -1)
//             {
//                 perror("Error\n");
//                 return 1;
//             }
//         }
//         else if (cmd2_type == ALIAS_CMD)
//             execute_alias_cmd(NULL,cmd2, envp);
//     }
//     free(cmd_1_argv_excve);
//     free(cmd_2_argv_excve);
//     return 0;
// }

// 0 READ END
// 1 WRITE END

void fork_and_execute(t_node *last_cmd, int cmd_count, char *infile, char *outfile, char **envp)
{
    int pipe_fds[2];
    pid_t pid;
    char *execve_argv[2];

    if(cmd_count == 1)
    {
        execute_alias_cmd(outfile, last_cmd->input, envp);
        return;
    }
    pipe(pipe_fds);
    pid = fork();
    if(!pid)
    {
        close(pipe_fds[0]);
        dup2(pipe_fds[1], 1);
        close(pipe_fds[1]);
        cmd_count--;
        fork_and_execute(last_cmd->prev, cmd_count, infile, outfile, envp);
    }
    else
    {
        waitpid(pid, NULL, 0);
        close(pipe_fds[1]);
        dup2(pipe_fds[0], 0);
        execve_argv[0] = last_cmd->input;
        execve_argv[1] = NULL;
        execve(last_cmd->input, execve_argv, envp);
    }
}
int main(int argc, char **argv)
{
    t_node *input;
    int pipe_fds[2];
    int input_count;

    if (argc < 5) 
    {
        printf("Usage: ./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>\n");
        return 1;
    }
    input_count = argc - 1;
    input = parser(input_count, argv);
    // pipe(pipe_fds);
    ft_lstiter(input, print);
}