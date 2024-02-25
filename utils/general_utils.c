/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:27:31 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/25 18:22:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int is_a_command(t_node *node)
{
    if(node->type == FIRST_COMMAND || node->type == PIPED_COMMAND || node->type == LAST_COMMAND)
        return (TRUE);
    return (FALSE);
}

void dup2_and_close(int read_end, int write_end,int dup_to ,int mode)
{
    if (mode == READ_END)
    {
        close(write_end);
        dup2(read_end, dup_to);
        printf("%i BECAME %i\n", read_end, dup_to);
        close(read_end);
    }
    else if (mode == WRITE_END)
    {
        close(read_end);
        dup2(write_end, dup_to);
        printf("%i BECAME %i\n", read_end, dup_to);
        close(write_end);
    }
}
static int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int count_commands(t_node *input)
{
    int count;

    count = 0;
    while(input)
    {
        if(input->type == FIRST_COMMAND || input->type == PIPED_COMMAND || input->type == LAST_COMMAND)
            count++;
        input = input->next;
    }
    return (count);
}
