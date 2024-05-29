/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysirkich <ysirkich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:13:25 by yana              #+#    #+#             */
/*   Updated: 2024/05/29 19:57:49 by ysirkich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_readfile(int fd, char *storing_line);
static char	*ft_extract_line(char *storing_line);
static char	*ft_storing_new_line(char *storing_line);
static char	*ft_process_buffer(char *storing_line, char *buffer);

char	*get_next_line(int fd)
{
	static char	*storing_line;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &storing_line, 0) < 0)
		return (ft_free(&storing_line));
	storing_line = ft_readfile(fd, storing_line);
	if (!storing_line)
		return (ft_free(&storing_line));
	line = ft_extract_line(storing_line);
	if (!line)
		return (ft_free(&storing_line));
	storing_line = ft_storing_new_line(storing_line);
	return (line);
}

static char	*ft_readfile(int fd, char *storing_line)
{
	char	*buffer;
	int		bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&storing_line));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free(&storing_line));
		buffer[bytes] = '\0';
		storing_line = ft_process_buffer(storing_line, buffer);
		if (!storing_line)
		{
			ft_free (&buffer);
			return (NULL);
		}
		if (ft_strchr(storing_line, '\n'))
			break ;
	}
	ft_free(&buffer);
	return (storing_line);
}

static char	*ft_process_buffer(char *storing_line, char *buffer)
{
	char	*tmp;

	if (!storing_line)
	{
		storing_line = ft_strdup(buffer);
		if (!storing_line)
			return (NULL);
	}
	else
	{
		tmp = storing_line;
		storing_line = ft_strjoin(storing_line, buffer);
		ft_free (&tmp);
		if (!storing_line)
			return (NULL);
	}
	return (storing_line);
}

static char	*ft_extract_line(char *storing_line)
{
	int		i;
	char	*line;
	int		len;

	if (!storing_line || !*storing_line)
		return (NULL);
	i = 0;
	while (storing_line[i] && storing_line[i] != '\n')
		i++;
	len = i;
	if (storing_line[i] == '\n')
		len++;
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = storing_line[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_storing_new_line(char *storing_line)
{
	char	*new_storing_line;
	int		i;
	int		i_newline;

	i = 0;
	while (storing_line[i] && storing_line[i] != '\n')
		i++;
	if (!storing_line[i])
    {
        free(storing_line);
        return (NULL);
    }
	new_storing_line = malloc((ft_strlen(storing_line) - i) * sizeof(char));
	if (!new_storing_line)
	{
		free(storing_line);
		return (NULL);
	}
	i++;
	i_newline = 0;
	while (storing_line[i])
		new_storing_line[i_newline++] = storing_line[i++];
	new_storing_line[i_newline] = '\0';
	free(storing_line);
	return (new_storing_line);
}