/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:14 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/13 00:00:55 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

enum CMD_TYPES
{
    INVALID_CMD,
    PATH_CMD,
    ALIAS_CMD
};

enum FREE_FLAGS
{
    DONT_FREE,
    FREE_S1,
    FREE_S2,
    FREE_BOTH
};


// GENERAL UTILS
int get_command_type(char *cmd);
char **get_paths(char **envp);

// STR UTILS
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2, int free_flag);
size_t ft_strlen(const char *str);
void print_to_debug(char *str);
#endif