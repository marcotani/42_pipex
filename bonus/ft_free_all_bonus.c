/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:12:42 by mtani             #+#    #+#             */
/*   Updated: 2024/01/16 15:22:11 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	free_gnl(char *line)
{
	if (line != NULL)
		free(line);
	get_next_line(-1);
}
