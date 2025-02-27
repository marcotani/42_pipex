/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:45:43 by mtani             #+#    #+#             */
/*   Updated: 2024/03/18 13:56:27 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(char **cmd, char **path, char *valid_cmd, int flag)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	if (flag == 1)
		free(valid_cmd);
}

int	ft_refork(int *fd, char **argv, char **envp, pid_t *pid2)
{
	*pid2 = fork();
	if (*pid2 == -1)
		return (ft_error("Error: fork failed", 3));
	if (*pid2 == 0)
		second_cmd(fd, argv, envp);
	return (0);
}

int	ft_checks(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (ft_error("Error: wrong number of arguments", 1));
	if (envp == NULL || *envp == NULL)
		return (ft_error("Error: envp not found", 9));
	if (ft_strncmp(argv[1], argv[4], ft_strlen(argv[1])) == 0)
		return (ft_error("Error: input and output files must differ", 8));
	return (0);
}
