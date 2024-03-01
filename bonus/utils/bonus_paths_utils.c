/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_paths_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:32:01 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/01 10:22:59 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_pipex.h"

static int	get_path_index(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H')
			return (i);
		i++;
	}
	return (-1);
}

static void	slash_paths(char **binary_paths, t_node *first)
{
	int	i;

	i = 0;
	while (binary_paths[i])
	{
		binary_paths[i] = ft_strjoin(binary_paths[i], "/", FREE_S1);
		if (!binary_paths[i])
		{
			clean_here_doc(first);
			free_paths(binary_paths);
			handle_error(&first);
		}
		i++;
	}
}

char	**get_paths(char **envp, t_node *first)
{
	int		path_index;
	char	*path;
	char	**binary_paths;

	path_index = get_path_index(envp);
	if (path_index == -1)
		binary_paths = ft_split(SECURE_PATH, ':');
	else
	{
		path = envp[path_index];
		while (*path != '/')
			path++;
		binary_paths = ft_split(path, ':');
	}
	if (!binary_paths)
	{
		clean_here_doc(first);
		handle_error(&first);
	}
	slash_paths(binary_paths, first);
	return (binary_paths);
}
