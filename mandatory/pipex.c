/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:11:35 by mtani             #+#    #+#             */
/*   Updated: 2024/03/18 13:56:10 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//#include "pipex_utils.c"
//#include "pipex_utils2.c"

char	*ft_get_valid_cmd(char *cmd, char **path)
{
	int		i;
	char	*valid_cmd;
	char	*tmp;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		valid_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(valid_cmd, F_OK) == 0)
			break ;
		free(valid_cmd);
		i++;
	}
	if (path[i] == NULL)
		return (NULL);
	return (valid_cmd);
}

char	**ft_get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (ft_altsplit(envp[i] + 5, ':'));
}

void	first_cmd(int *fd, char **argv, char **envp)
{
	char	**cmd;
	int		input;
	char	**path;
	char	*valid_cmd;

	input = open(argv[1], O_RDONLY, 0644);
	if (input == -1)
		ft_error("Error: could not open input file", 4);
	if (dup2(input, 0) == -1 || dup2(fd[1], 1) == -1 || close(fd[0]) == -1)
		ft_error(NULL, 6);
	cmd = ft_altsplit(argv[2], ' ');
	path = ft_get_path(envp);
	valid_cmd = ft_get_valid_cmd(cmd[0], path);
	if (valid_cmd == NULL)
	{
		ft_free_all(cmd, path, valid_cmd, 0);
		ft_error("Error: command not found", 127);
	}
	if (execve(valid_cmd, cmd, envp) == -1)
	{
		ft_free_all(cmd, path, valid_cmd, 1);
		ft_error("Error: execve failed", 5);
	}
}

void	second_cmd(int *fd, char **argv, char **envp)
{
	char	**cmd;
	int		output;
	char	**path;
	char	*valid_cmd;

	output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
		ft_error("Error: could not open output file", 4);
	if (dup2(fd[0], 0) == -1 || dup2(output, 1) == -1 || close(fd[1]) == -1)
		ft_error(NULL, 6);
	cmd = ft_altsplit(argv[3], ' ');
	path = ft_get_path(envp);
	valid_cmd = ft_get_valid_cmd(cmd[0], path);
	if (valid_cmd == NULL)
	{
		ft_free_all(cmd, path, valid_cmd, 0);
		ft_error("Error: command not found", 127);
	}
	if (execve(valid_cmd, cmd, envp) == -1)
	{
		ft_free_all(cmd, path, valid_cmd, 1);
		ft_error("Error: execve failed", 5);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pid1 = 0;
	pid2 = 0;
	ft_checks(argc, argv, envp);
	if (pipe(fd) == -1)
		return (ft_error("Error: pipe failed", 2));
	pid1 = fork();
	if (pid1 == -1)
		return (ft_error("Error: fork failed", 3));
	if (pid1 == 0)
		first_cmd(fd, argv, envp);
	if (pid1 != 0)
		ft_refork(fd, argv, envp, &pid2);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
