/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:57:11 by mtani             #+#    #+#             */
/*   Updated: 2024/03/18 14:06:38 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
// #include "pipex_utils_bonus.c"
// #include "ft_split_bonus.c"
// #include "ft_free_all_bonus.c"

void	ft_parent(int *fd, int i, int cmd_num)
{
	if (i == 0)
	{
		if (close(fd[1]))
			ft_error("Error: close failed", 11);
	}
	else if (i == cmd_num - 1)
	{
		if (close(fd[(i - 1) * 2]) == -1)
			ft_error("Error: close failed", 12);
	}
	else
	{
		if (close(fd[(i - 1) * 2]) == -1 || close(fd[i * 2 + 1]) == -1)
			ft_error("Error: close failed", 13);
	}
}

void	ft_child(int *fd, char **argv, char **envp, int i)
{
	char	**cmd;
	char	*valid_cmd;
	char	**path;

	cmd = ft_altsplit(argv[i + 2], ' ');
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

void	ft_pipex_loop(t_pipex pipex, char **argv, char **envp, int i)
{
	while (i < pipex.cmd_num)
	{
		if (fork() == 0)
		{
			if (i == 0)
				init_first(pipex);
			else if (i == pipex.cmd_num - 1)
				init_last(pipex, i);
			else
				init_mid(pipex, i);
			ft_child(pipex.fd, argv, envp, i);
		}
		else
			ft_parent(pipex.fd, i, pipex.cmd_num);
		i++;
	}
	while (wait(NULL) > 0 && i > 0)
		i--;
}

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	pipex.input = open(argv[1], O_RDONLY);
	if (pipex.input == -1)
		ft_error("Error: could not open input file", 2);
	pipex.output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.output == -1)
		ft_error("Error: could not open output file", 3);
	pipex.cmd_num = argc - 3;
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
	ft_pipex_loop(pipex, argv, envp, i);
	free(pipex.fd);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		ft_error("Error: wrong number of arguments", 1);
	if (envp == NULL || *envp == NULL)
		ft_error("Error: envp not found", 9);
	if (ft_strncmp(argv[1], argv[argc - 1], ft_strlen(argv[1])) == 0)
		ft_error("Error: input and output files must differ", 100);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		here_doc(argc, argv, envp);
	else
		pipex(argc, argv, envp);
}
