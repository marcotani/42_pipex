/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:45:22 by mtani             #+#    #+#             */
/*   Updated: 2023/12/13 15:01:39 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
//#include "get_next_line_utils.c"
//#include <unistd.h>
//#include <stdlib.h>
//#include <fcntl.h>
//#include <stdio.h>

char	*join_free(char *buffer, char *readbuf)
{
	char	*tmp;
	int		i;

	i = 0;
	if (buffer == NULL)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(readbuf) + 1));
		if (tmp == NULL)
			return (NULL);
		while (readbuf[i])
		{
			tmp[i] = readbuf[i];
			i++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	tmp = ft_strjoin(buffer, readbuf);
	if (tmp == NULL)
		return (NULL);
	free(buffer);
	buffer = NULL;
	return (tmp);
}

char	*clean_buf(char *buffer)
{
	char	*tmp;
	int		start;
	int		size;

	start = 0;
	if (buffer == NULL)
		return (NULL);
	while (buffer[start] != '\n' && buffer[start] != '\0')
		start++;
	if (buffer[start] == '\0')
	{
		free (buffer);
		return (NULL);
	}
	size = start + 1;
	while (buffer[size] != '\0')
		size++;
	tmp = ft_calloc(size - start + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	size = 0;
	while (buffer[start + 1] != '\0')
		tmp[size++] = buffer[(start++) + 1];
	free(buffer);
	return (tmp);
}

char	*extract_line(char *buffer)
{
	char	*line;
	int		start;
	int		i;

	i = 0;
	start = 0;
	if (buffer == NULL || buffer[0] == '\0')
		return (NULL);
	while (buffer[start] != '\n' && buffer[start] != '\0')
		start++;
	line = ft_calloc(start + 1 + (buffer[start] == '\n'), sizeof(char));
	if (line == NULL)
		return (NULL);
	if (buffer[start] == '\n')
		start++;
	while (i < start && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

char	*read_line(char *buffer, char *readbuf, int fd)
{
	int	read_check;

	read_check = 1;
	while (read_check > 0)
	{
		read_check = read(fd, readbuf, BUFFER_SIZE);
		if (read_check < 0)
			return (NULL);
		if (read_check == 0)
			break ;
		readbuf[read_check] = '\0';
		buffer = join_free(buffer, readbuf);
		if (ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*readbuf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		if (buffer != NULL)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	readbuf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (readbuf == NULL)
		return (NULL);
	if (ft_strchr(buffer, '\n') == NULL)
		buffer = read_line(buffer, readbuf, fd);
	free (readbuf);
	readbuf = NULL;
	line = extract_line(buffer);
	buffer = clean_buf(buffer);
	return (line);
}

// int main()
// {
// 	int	fd = open("nl", O_RDONLY);
// 	char *line;
// 	int i = 0;

// 	while (i < 2)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	fd = open("nl", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	close(fd);
// }