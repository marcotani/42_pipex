/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_dups_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:46:04 by mtani             #+#    #+#             */
/*   Updated: 2024/01/27 12:44:27 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_first(t_pipex pipex)
{
	if (dup2(pipex.input, 0) == -1)
		ft_error(NULL, 8);
	if (dup2(pipex.fd[1], 1) == -1)
		ft_error(NULL, 8);
}

void	init_last(t_pipex pipex, int i)
{
	if (dup2(pipex.fd[(i - 1) * 2], 0) == -1
		|| dup2(pipex.output, 1) == -1)
		ft_error(NULL, 8);
}

void	init_mid(t_pipex pipex, int i)
{
	if (dup2(pipex.fd[(i - 1) * 2], 0) == -1
		|| dup2(pipex.fd[i * 2 + 1], 1) == -1)
		ft_error(NULL, 8);
}
