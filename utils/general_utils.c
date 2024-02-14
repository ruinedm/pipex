/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:27:31 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/14 13:55:08 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int get_command_type(char *cmd)
{
    int i;

    i = 0;
    while(cmd[i])
    {
        if (!ft_isalpha(cmd[i]) && cmd[i] != '/' && cmd[i] != '-')
            return (INVALID_CMD);
        i++;
    }
    i = 0;
    while(cmd[i])
    {
        if(!ft_isalpha(cmd[i]))
            return(PATH_CMD);
        i++;
    }
    return (ALIAS_CMD);
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

