/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:15:34 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/15 08:59:25 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void handle_error(t_node **head)
{
    ft_lstclear(head);
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

    first_cmd = ft_lstnew(ft_strdup(argv[2]));
    if(!first_cmd)
        handle_error(head);
    first_cmd->type = FIRST_COMMAND;
    ft_lstadd_back(head, first_cmd);
    i = 3;
    while(i < input_count - 1)
    {
        looping_node = ft_lstnew(ft_strdup(argv[i]));
        if(!looping_node)
            handle_error(head);
        looping_node->type = PIPED_COMMAND;
        ft_lstadd_back(head, looping_node);
        i++;
    }
    last_cmd = ft_lstnew(ft_strdup(argv[input_count - 1]));
    if(!last_cmd)
        handle_error(head);
    last_cmd->type = LAST_COMMAND;
    ft_lstadd_back(head, last_cmd);
    outfile = ft_lstnew(ft_strdup(argv[input_count]));
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

    limiter = ft_lstnew(ft_strdup(argv[2]));
    if(!limiter)
        handle_error(head);
    limiter->type = LIMITER;
    ft_lstadd_back(head, limiter);
    i = 3;
    while(i < input_count - 1)
    {
        looping_node = ft_lstnew(ft_strdup(argv[i]));
        if(!looping_node)
            handle_error(head);
        looping_node->type = PIPED_COMMAND;
        ft_lstadd_back(head, looping_node);
        i++;
    }
    last_cmd = ft_lstnew(ft_strdup(argv[input_count - 1]));
    if(!last_cmd)
        handle_error(head);
    last_cmd->type = LAST_COMMAND;
    ft_lstadd_back(head, last_cmd);
    outfile = ft_lstnew(ft_strdup(argv[input_count]));
    if(!outfile)
        handle_error(head);
    outfile->type = OUTFILE;
    ft_lstadd_back(head, outfile);
}

t_node *parser(int input_count,char **argv)
{
    int i;
    t_node *head;

    head = ft_lstnew(ft_strdup(argv[1]));
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
            printf("Invalid input: Infile [%s] doesn't exist!", argv[1]);
            ft_lstclear(&head);
            exit(EXIT_FAILURE);
        }
        head->type = INFILE;
        handle_normal_parsing(&head, argv, input_count);
        return (head);
    }
}
