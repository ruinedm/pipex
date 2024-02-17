static void execute_command(char *infile, char *outfile, t_node *command_node, int read_end, int write_end)
{
    static int i;

    if(command_node->type == FIRST_COMMAND)
    {
        close(read_end);
        write(write_end, "HI FROM THE LAST CHILD :D\n", 26);
        close(write_end);
    }
    else if(command_node->type == PIPED_COMMAND)
    {
        char *msg = get_next_line(read_end);
        write(write_end, )
    }
}


void fork_and_execute(char *infile, char *outfile, t_node *input, int command_count, int read_end, int write_end)
{
    int i;
    pid_t pid;
    int pipefd[2];

    i = 0;
    if(command_count == 1)
    {
        execute_command(infile, outfile, input, read_end, write_end);
        return ;
    }
    pid = fork();
    if(!pid)
    {
        command_count--;
        fork_and_execute(infile, outfile, input->prev, command_count, read_end, write_end);
    }
    else
    {
        waitpid(pid, NULL, 0);
        execute_command(infile, outfile, input, read_end, write_end);
    }
}