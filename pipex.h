/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:40:14 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/20 16:48:52 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <sys/wait.h>
typedef struct s_node
{
    char **input;
    int type;
    int pipe_fds[2];
    struct s_node *next;
    struct s_node *prev;
} t_node;


#define BUFFER_SIZE 10
#define OPEN_MAX 1000
enum BOOLEAN
{
    FALSE,
    TRUE
};

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

enum FREE_FLAGS
{
    DONT_FREE,
    FREE_S1,
    FREE_S2,
    FREE_BOTH
};

enum COUNTER_MODE
{
    GET,
    INCREMENT
};

enum DUP2_MODE
{
    READ_END,
    WRITE_END
};

// EXCUTION UTILS
void fork_and_execute(char *infile, char *outfile, t_node *input, int command_count, char **bin_paths, char **envp);
void close_all_fds(t_node *input);
// PARSING UTILS
t_node *parser(int input_count,char **argv);
void print_open(t_node *first, int open); // TO REMOVE
// GENERAL UTILS
char **get_paths(char **envp);
int count_commands(t_node *input);
int fork_counter(int mode);
void dup2_and_close(int read_end, int write_end,int dup_to ,int mode);
int is_a_command(t_node *node);
// STR UTILS
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2, int free_flag);
size_t ft_strlen(const char *str);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup( char *s1);
void print_to_debug(char *str);
void print(char **input, int type);
size_t	ft_word_count(char const *s, char c);

// LINKED LIST UTILS
t_node	*ft_lstnew(char **content);
t_node	*ft_lstlast(t_node *lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_lstclear(t_node **lst);
void	ft_lstiter(t_node *lst, void (*f)(char **, int));
t_node *ft_lstfirst(t_node *lst);

// GET_NEXT_LINE UTILS
char	*get_next_line(int fd);
char	*read_and_append(int fd, char **ptr_to_save);
char	*extract_line(char **ptr_to_save);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *s1);
char	*ft_strchr(char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);


// HERE_DOC UTILS
void handle_here_doc_input(t_node *input, int tmp_file);
#endif