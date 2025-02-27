/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:57:39 by mtani             #+#    #+#             */
/*   Updated: 2024/01/16 15:21:57 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define READ_END 0
# define WRITE_END 1
# define STDIN 0
# define STDOUT 1

typedef struct s_pipex
{
	int		*fd;
	int		input;
	int		output;
	int		cmd_num;
}	t_pipex;

void	ft_pipex_loop(t_pipex pipex, char **argv, char **envp, int i);
void	ft_parent(int *fd, int i, int cmd_num);
void	init_first(t_pipex pipex);
void	init_last(t_pipex pipex, int i);
void	init_mid(t_pipex pipex, int i);
int		ft_error(char *str, int exit_code);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
char	**ft_altsplit(char *s, char c);
char	find_quotetype(const char *s, size_t i, char quote);
int		find_unquoted(const char *s, char c, size_t start);
int		find_quoted(const char *s, char quote, size_t start);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(char *s);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_free_all(char **cmd, char **path, char *valid_cmd, int flag);
void	free_gnl(char *line);
void	here_doc(int argc, char **argv, char **envp);
char	**ft_get_path(char **envp);
char	*ft_get_valid_cmd(char *cmd, char **path);

// GNL
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);

#endif
