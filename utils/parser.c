/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:15:34 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/25 23:05:02 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void handle_error(t_node **head)
{
    ft_lstclear(*head);
    printf("Mallocation error\n");
    exit(EXIT_FAILURE);
}
static void handle_normal_parsing(t_node **head, char **argv, int input_count)
{
    int i;
    t_node *first_cmd; // THE COMMAND THAT WILL EXECUTE WITH THE INFILE
    t_node *last_cmd; // THE COMMAND THAT WILL WRITE TO THE OUTFILE
    t_node *outfile;
    t_node *looping_node;
    char **command_array;

    command_array = ft_split(argv[2], ' ');
    first_cmd = ft_lstnew(command_array);
    if(!first_cmd)
        handle_error(head);
    first_cmd->type = FIRST_COMMAND;
    ft_lstadd_back(head, first_cmd);
    i = 3;
    while(i < input_count - 1)
    {
        command_array = ft_split(argv[i], ' ');
        looping_node = ft_lstnew(command_array);
        if(!looping_node)
            handle_error(head);
        looping_node->type = PIPED_COMMAND;
        ft_lstadd_back(head, looping_node);
        i++;
    }
    command_array = ft_split(argv[input_count -1], ' ');
    last_cmd = ft_lstnew(command_array);
    if(!last_cmd)
        handle_error(head);
    last_cmd->type = LAST_COMMAND;
    ft_lstadd_back(head, last_cmd);
    command_array = ft_split(argv[input_count], ' ');
    outfile = ft_lstnew(command_array);
    if(!outfile)
        handle_error(head);
    outfile->type = OUTFILE;
    ft_lstadd_back(head, outfile);
}

static void handle_here_doc_parsing(t_node **head, char **argv, int input_count)
{
    t_node *limiter;
    t_node *outfile;
    t_node *last_cmd;
    t_node *looping_node;
    int i;
    char **command_array;

    command_array = ft_split(argv[2], ' ');
    limiter = ft_lstnew(command_array);
    if(!limiter)
        handle_error(head);
    limiter->type = LIMITER;
    ft_lstadd_back(head, limiter);
    i = 3;
    while(i < input_count - 1)
    {
        command_array = ft_split(argv[i], ' ');
        looping_node = ft_lstnew(command_array);
        if(!looping_node)
            handle_error(head);
        looping_node->type = PIPED_COMMAND;
        ft_lstadd_back(head, looping_node);
        i++;
    }
    command_array = ft_split(argv[i], ' ');
    last_cmd = ft_lstnew(command_array);
    if(!last_cmd)
        handle_error(head);
    last_cmd->type = LAST_COMMAND;
    ft_lstadd_back(head, last_cmd);
    command_array = ft_split(argv[input_count], ' ');
    outfile = ft_lstnew(command_array);
    if(!outfile)
        handle_error(head);
    outfile->type = OUTFILE;
    ft_lstadd_back(head, outfile);
}

t_node *parser(int input_count,char **argv)
{
    int i;
    t_node *head;
    char **first_cmd_arr;
    
    first_cmd_arr = ft_split(argv[1], ' ');
    head = ft_lstnew(first_cmd_arr);
    if(!ft_strcmp("here_doc", argv[1]))
    {
        head->type = HERE_DOC;
        handle_here_doc_parsing(&head, argv, input_count);
        return (head);
    }
    else
    {
        if(access(argv[1], F_OK))
        {
            printf("Invalid input: Infile [%s] doesn't exist!\n", argv[1]);
            ft_lstclear(head);
            exit(EXIT_FAILURE);
        }
        head->type = INFILE;
        handle_normal_parsing(&head, argv, input_count);
        return (head);
    }
}
