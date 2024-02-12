/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:06:50 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/12 01:39:55 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

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