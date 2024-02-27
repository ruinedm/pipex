

#include "../pipex.h"

static int	get_path_index(char **envp)
{
	int	i;
	int	j;

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

char	**get_paths(char **envp)
{
	int		path_index;
	int		i;
	char	*path;
	char	**binary_paths;

	path_index = get_path_index(envp);
	i = 0;
	if (path_index == -1)
	{
		perror("Path was not found!");
		exit(EXIT_FAILURE);
	}
	i = 0;
	path = envp[path_index];
	while (*path != '/')
		path++;
	binary_paths = ft_split(path, ':');
	while (binary_paths[i])
	{
		binary_paths[i] = ft_strjoin(binary_paths[i], "/", FREE_S1);
		i++;
	}
	return (binary_paths);
}
