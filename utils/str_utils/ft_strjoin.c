#include "../../pipex.h"

static void	free_strjoin(char *s1, char *s2, int free_flag)
{
	if (free_flag == FREE_S1)
		free(s1);
	else if (free_flag == FREE_S2)
		free(s2);
	else if (free_flag == FREE_BOTH)
	{
		free(s1);
		free(s2);
	}
}

char	*ft_strjoin(char *s1, char *s2, int free_flag)
{
	char	*finalstr;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	finalstr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	if (!finalstr)
		return (free_strjoin(s1, s2, free_flag), NULL);
	while (s1[i])
		finalstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		finalstr[j++] = s2[i++];
	finalstr[j] = 0;
	return (free_strjoin(s1, s2, free_flag), finalstr);
}
