/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:57:34 by mtani             #+#    #+#             */
/*   Updated: 2024/01/13 14:50:19 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_error(char *str, int exit_code)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	else
		perror("Error");
	exit(exit_code);
}

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
	return (ft_split(envp[i] + 5, ':'));
}
