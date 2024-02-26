/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:15:34 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/26 20:17:59 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void handle_error(t_node **head)
{
    ft_lstclear(*head);
    printf("Mallocation error\n");
    exit(EXIT_FAILURE);
}
static void add_command_node(t_node **head, char *command_str, int type) 
{
    char **command_array;
    t_node *cmd_node;

    command_array =ft_split(command_str, ' ');
    if(!command_array)
        handle_error(head);
    cmd_node = ft_lstnew(command_array, (*head)->infile, (*head)->outfile); // HANDLE ERROR
    if(!command_array)
    {
        free(command_array);
        handle_error(head);
    }
    cmd_node->type = type;
    ft_lstadd_back(head, cmd_node);
}

static void handle_parsing(t_node **head, char **argv, int input_count, int limiter_type) 
{
    int i;

    i = 3;
    add_command_node(head, argv[2], limiter_type);
    while (i < input_count) 
    {
        add_command_node(head, argv[i], PIPED_COMMAND);
        i++;
    }
    add_command_node(head, argv[input_count - 1], LAST_COMMAND);
    add_command_node(head, argv[input_count], OUTFILE);
}

static void change_for_here_doc(t_node *input)
{
    int tmp_file;

    tmp_file = open("/tmp/.here_doc", O_RDONLY, 0777);
    if(tmp_file == -1)
    {
        ft_lstclear(input);
        exit(EXIT_FAILURE);
    }
    handle_here_doc_input(input, tmp_file);
    shapeshift_here_doc(input);
}

t_node *parser(int input_count, char **argv)
{
    int i;
    t_node *head;
    char **first_cmd_arr;

    first_cmd_arr = ft_split(argv[1], ' ');
    head = ft_lstnew(first_cmd_arr, argv[1], argv[input_count]);
    if(!ft_strcmp("here_doc", argv[1]))
    {
        head->type = HERE_DOC;
        handle_parsing(&head, argv, input_count, LIMITER);
        change_for_here_doc(head);
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
        handle_parsing(&head, argv, input_count, FIRST_COMMAND);
    }
    return (head);
}
