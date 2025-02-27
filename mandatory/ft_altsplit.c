/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_altsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:12 by mtani             #+#    #+#             */
/*   Updated: 2024/01/16 15:18:52 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_count_arr(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	in_arr;
	char	quote;

	i = 0;
	count = 0;
	in_arr = 0;
	quote = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '"' || s[i] == '\'') && quote == 0)
			quote = s[i];
		else if (s[i] == quote && quote != 0)
			quote = 0;
		if (s[i] != c && in_arr == 0)
		{
			count++;
			in_arr = 1;
		}
		else if (s[i] == c && quote == 0)
			in_arr = 0;
		i++;
	}
	return (count);
}

static char	*ft_make_string(char const *s, size_t start, char c, char quote)
{
	char	*division;
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = 0;
	if (s[i] == '\0' || s == 0)
		return (NULL);
	if (quote == 0)
		str_len = find_unquoted(s, c, start);
	else
		str_len = find_quoted(s, quote, start);
	division = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (division == NULL)
		return (NULL);
	while (i < str_len)
	{
		if (quote == 0)
			division[i++] = s[start++];
		else
			division[i++] = s[(start++) + 1];
	}
	division[i] = '\0';
	return (division);
}

static char	**ft_clear(char **array, size_t arr_index)
{
	while (arr_index-- > 0)
		free(array[arr_index]);
	free(array);
	return (NULL);
}

static char	**ft_make_split(char **array, char const *s, char c)
{
	int		i;
	int		in_arr;
	int		arr_index;
	char	quote;

	i = -1;
	in_arr = 0;
	arr_index = 0;
	quote = 0;
	while (s[++i] != '\0')
	{
		quote = find_quotetype(s, i, quote);
		if (s[i] != c && in_arr == 0)
		{
			array[arr_index++] = ft_make_string(s, i, c, quote);
			if (array[arr_index - 1] == NULL)
				return (ft_clear(array, arr_index));
			in_arr = 1;
		}
		else if (s[i] == c && quote == 0)
			in_arr = 0;
	}
	array[arr_index] = 0;
	return (array);
}

char	**ft_altsplit(char *s, char c)
{
	char	**array;

	array = (char **)ft_calloc(ft_count_arr(s, c) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = ft_make_split(array, s, c);
	if (array == NULL)
		return (NULL);
	else
		return (array);
}
