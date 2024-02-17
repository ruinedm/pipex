/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:06:50 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/16 11:43:38 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"


void print(char **input, int type) {
    if (input == NULL)
        return;
    
    int i = 0;
    while (input[i] != NULL) {
        if (type == INFILE)
            printf("INPUT: %s // TYPE: INFILE // ", input[i]);
        else if (type == OUTFILE)
            printf("INPUT: %s // TYPE: OUTFILE // ", input[i]);
        else if (type == FIRST_COMMAND)
            printf("INPUT: %s // TYPE: FIRST_COMMAND // ", input[i]);
        else if (type == LAST_COMMAND)
            printf("INPUT: %s // TYPE: LAST_COMMAND // ", input[i]);
        else if (type == PIPED_COMMAND)
            printf("INPUT: %s // TYPE: PIPED_COMMAND // ", input[i]);
        else if (type == HERE_DOC)
            printf("INPUT: %s // TYPE: HERE_DOC // ", input[i]);
        else if (type == LIMITER)
            printf("INPUT: %s // TYPE: LIMITER // ", input[i]);
        i++;
    }
	printf("\n");
}


size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while(str[i])
        i++;
    return(i);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len);
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup( char *s1)
{
	char	*copy;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	while (i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}