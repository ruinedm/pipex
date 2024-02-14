/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 02:20:56 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/14 10:31:35 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_node	*ft_lstnew(char *content)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->input = content;
	new_node->type = -1;
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

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->input);
        free(*lst);
		*lst = tmp;
	}
}
void	ft_lstiter(t_node *lst, void (*f)(char *, int))
{
	t_node	*tmp;

	if (lst == NULL || f == NULL)
		return ;
	while (lst != NULL)
	{
		tmp = lst->next;
		f(lst->input, lst->type);
		lst = tmp;
	}
}