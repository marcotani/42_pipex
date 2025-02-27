/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:33:59 by mtani             #+#    #+#             */
/*   Updated: 2024/03/18 14:05:05 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_docchild(int *fd, char **argv, char **envp, int i)
{
	char	**cmd;
	char	*valid_cmd;
	char	**path;

	cmd = ft_altsplit(argv[i + 3], ' ');
	path = ft_get_path(envp);
	valid_cmd = ft_get_valid_cmd(cmd[0], path);
	if (valid_cmd == NULL)
	{
		ft_free_all(cmd, path, valid_cmd, 0);
		free(fd);
		ft_error("Error: command not found", 127);
	}
	execve(valid_cmd, cmd, envp);
	ft_free_all(cmd, path, valid_cmd, 1);
	free(fd);
	ft_error("Error: execve failed", 7);
}

void	ft_docpipex_loop(t_pipex pipex, char **argv, char **envp, int i)
{
	while (i < pipex.cmd_num)
	{
		if (fork() == 0)
		{
			if (i == 0)
			{
				if (dup2(pipex.fd[1], 1) == -1)
					ft_error(NULL, 8);
			}
			else if (i == pipex.cmd_num - 1)
				init_last(pipex, i);
			else
				init_mid(pipex, i);
			ft_docchild(pipex.fd, argv, envp, i);
		}
		else
			ft_parent(pipex.fd, i, pipex.cmd_num);
		i++;
	}
	while (wait(NULL) > 0 && i > 0)
		i--;
}

void	doc_pipex(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	pipex.output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex.output == -1)
		ft_error("Error: could not open output file", 3);
	pipex.cmd_num = argc - 4;
	pipex.fd = malloc(sizeof(int) * ((pipex.cmd_num - 1) * 2));
	if (pipex.fd == NULL)
		ft_error("Error: fd malloc failed", 4);
	if (pipe(pipex.fd) == -1)
		ft_error("Error: pipe failed", 5);
	while (i < (pipex.cmd_num - 1))
	{
		if (pipe(pipex.fd + i * 2) == -1)
			ft_error("Error: pipe failed", 6);
		i++;
	}
	i = 0;
	ft_docpipex_loop(pipex, argv, envp, i);
	free(pipex.fd);
}

void	get_doc(int argc, char **argv, int fd[2])
{
	char	*line;
	int		i;

	i = -1;
	close(fd[0]);
	while (++i < argc - 5)
		write(1, "pipe ", 5);
	write(1, "heredoc> ", 9);
	line = get_next_line(0);
	while (line != NULL
		&& ft_strncmp(line, argv[2], ft_strlen(argv[2])) != 0)
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		i = -1;
		while (++i < argc - 5)
			write(1, "pipe ", 5);
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
	}
	free_gnl(line);
	close(fd[1]);
}

void	here_doc(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid;

	if (argc < 6)
		ft_error("Error: invalid number of arguments", 8);
	if (pipe(fd) == -1)
		ft_error("Error: pipe failed", 9);
	pid = fork();
	if (pid == -1)
		ft_error("Error: fork failed", 10);
	if (pid == 0)
		get_doc(argc, argv, fd);
	else
	{
		waitpid(pid, NULL, 0);
		if (close(fd[1]) == -1)
			ft_error("Error: close failed", 11);
		if (dup2(fd[0], 0) == -1)
			ft_error("Error: dup2 failed", 12);
		doc_pipex(argc, argv, envp);
	}
}
