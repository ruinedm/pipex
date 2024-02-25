/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:20:56 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/24 21:02:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_node	*ft_lstnew(char **content)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->input = content;
	new_node->type = -1;
	new_node->pipe_fds[0] = -1;
	new_node->pipe_fds[1] = -1;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_node	*ft_lstlast(t_node *lst)
{
	t_node	*temp;

	if (lst == NULL)
		return (NULL);
	temp = lst;
	while (temp)
	{
		if (!temp->next)
			return (temp);
		temp = temp->next;
	}
	return (lst);
}

t_node *ft_lstfirst(t_node *lst)
{
	t_node *temp;

	temp = lst;
	while(temp)
	{
		if(!temp->prev)
			return (temp);
		temp = temp->prev;
	}
	return (lst);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node *last_node;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
	new->prev = last_node;
}

void	ft_lstclear(t_node **lst)
{
	t_node	*tmp;
	char **cmd_array;
	int i;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		cmd_array= (*lst)->input;
		i = 0;
		while(cmd_array[i])
		{
			free(cmd_array[i]);
			i++;
		}
		free((*lst)->input);
        free(*lst);
		*lst = tmp;
	}
}
void ft_lstiter(t_node *lst, void (*f)(char **, int, int*)) 
{
    t_node *tmp;

    if (lst == NULL || f == NULL)
        return;
    
    while (lst != NULL) {
        tmp = lst->next;
        f(lst->input, lst->type, lst->pipe_fds);
        lst = tmp;
    }
}