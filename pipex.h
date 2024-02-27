/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:30:19 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/27 22:52:07 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_node
{
	char			*infile;
	char			*outfile;
	char			**input;
	int				type;
	int				pipe_fds[2];
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

# define BUFFER_SIZE 10

enum				e_BOOLEAN
{
	FALSE,
	TRUE
};

enum				e_MODES
{
	INFILE_MODE,
	HERE_DOC_MODE
};

enum				e_INPUT_TYPES
{
	INFILE,
	OUTFILE,
	FIRST_COMMAND,
	PIPED_COMMAND,
	LAST_COMMAND
};

enum				e_FREE_FLAGS
{
	DONT_FREE,
	FREE_S1,
	FREE_S2,
	FREE_BOTH
};

enum				e_STORE_MOD
{
	GET,
	SET,
	OPEN_HERE_DOC
};

enum				e_DUP2_MODE
{
	READ_END,
	WRITE_END
};

// EXCUTION UTILS
void				fork_and_execute(t_node *input, int command_count,
						char **envp);
void				close_all_fds(t_node *input);
void				dumb_dup2(int old, int new, t_node *command_node);
int					dumb_open(t_node *command_node, int mode);
// PARSING UTILS
char				**get_paths(char **envp);
// GENERAL UTILS
int					count_commands(t_node *input);
void				handle_error(t_node **head);
int					is_a_command(t_node *node);
t_node				*parser(int input_count, char **argv);
// // STR UTILS
char				**ft_split(char const *s, char c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strjoin(char *s1, char *s2, int free_flag);
size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(char *s1);
size_t				ft_word_count(char const *s, char c);
void				free_paths(char **bin_paths);

// LINKED LIST UTILS
void				ft_clearone(t_node *node);
t_node				*ft_lstnew(char **content, char *infile, char *outfile);
t_node				*ft_lstlast(t_node *lst);
void				ft_lstadd_back(t_node **lst, t_node *new);
void				ft_lstclear(t_node *lst);
t_node				*ft_lstfirst(t_node *lst);

#endif
