/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:57:03 by mtani             #+#    #+#             */
/*   Updated: 2024/01/16 14:57:04 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	find_quotetype(const char *s, size_t i, char quote)
{
	if ((s[i] == '"' || s[i] == '\'') && quote == 0)
		quote = s[i];
	else if (s[i] == quote && quote != 0)
		quote = 0;
	return (quote);
}

int	find_unquoted(const char *s, char c, size_t start)
{
	size_t	j;
	int		str_len;

	j = start;
	str_len = 0;
	while (s[j] != c && s[j])
	{
		j++;
		str_len++;
	}
	return (str_len);
}

int	find_quoted(const char *s, char quote, size_t start)
{
	size_t		j;
	int			str_len;

	j = start + 1;
	str_len = 0;
	while (s[j] != quote && s[j] && quote != 0)
	{
		j++;
		str_len++;
	}
	return (str_len);
}
