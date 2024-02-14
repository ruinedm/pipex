/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:14 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/14 10:35:33 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

typedef struct s_node
{
    char *input;
    int type;
    struct s_node *next;
    struct s_node *prev;
} t_node;

enum MODES
{
    INFILE_MODE,
    HERE_DOC_MODE
};

enum INPUT_TYPES
{
    INFILE, // IF NO HERE_DOC, FIRST INPUT
    OUTFILE, // ALWAYS THE LAST INPUT
    HERE_DOC, // IF FIRST INPUT IS: here_doc, ITS THE FIRST INPUT
    LIMITER,
    FIRST_COMMAND, // FIRST COMMAND, READS FROM THE INFILE
    PIPED_COMMAND, // EVERY COMMAND BUT THE LAST ONE
    LAST_COMMAND // THE LAST COMMAND, WRITES TO THE OUTFILE
};

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

// PARSING UTILS
t_node *parser(int input_count,char **argv);


// GENERAL UTILS
int get_command_type(char *cmd);
char **get_paths(char **envp);
int count_commands(t_node *input);
// STR UTILS
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2, int free_flag);
size_t ft_strlen(const char *str);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup( char *s1);
void print_to_debug(char *str);
void print(char *input, int type);
size_t	ft_word_count(char const *s, char c);

// LINKED LIST UTILS
t_node	*ft_lstnew(char *content);
t_node	*ft_lstlast(t_node *lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_lstclear(t_node **lst);
void	ft_lstiter(t_node *lst, void (*f)(char *, int));
#endif