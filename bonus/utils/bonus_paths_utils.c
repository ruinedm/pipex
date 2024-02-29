/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_paths_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:32:01 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/29 22:51:59 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_pipex.h"

static int	get_path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H')
			return (i);
		i++;
	}
	return (-1);
}

char	**get_paths(char **envp, t_node *first)
{
	int		path_index;
	int		i;
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
		handle_error(&first);
	i = 0;
	while (binary_paths[i])
	{
		binary_paths[i] = ft_strjoin(binary_paths[i], "/", FREE_S1);
		i++;
	}
	return (binary_paths);
}
