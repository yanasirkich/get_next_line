/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysirkich <ysirkich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:13:25 by yana              #+#    #+#             */
/*   Updated: 2024/05/24 14:44:19 by ysirkich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_readfile(int fd, char *storing_line);
static char	*ft_extract_line(char *storing_line);
static char *ft_storing_new_line(char *storing_line);
static char *ft_storing_new_line(char *storing_line);

// Function to get the next line from the file descriptor
char	*get_next_line(int fd)
{
	static char	*storing_line; //storing the remaining/leftover string
	char		*line; // line to be returned

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storing_line = ft_readfile(fd, storing_line);
	if (!storing_line)
		return (NULL);
	line = ft_extract_line(storing_line);
	storing_line = ft_storing_new_line(storing_line);
	return (line);
}
// Function to read the file and store the contents in storing_line
static char	*ft_readfile(int fd, char *storing_line)
{
	char	*buffer;
	int		bytes;
	
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(storing_line, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if  (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		storing_line = ft_strjoin(storing_line, buffer);
	}
	free(buffer);
	return (storing_line);
}

// Function to extract a line from storing_line up to the newline or end of string
static char	*ft_extract_line(char *storing_line)
{
	int		i;
	char	*line;

	if (!storing_line)
		return (NULL);
	i = 0;
	while (storing_line[i] && storing_line[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (storing_line[i] && storing_line[i] != '\n')
	{
		line[i] = storing_line[i];
		i++;
	}
	line = '\0';
	return (line);
}
// Function to update storing_line by removing the extracted line
static char *ft_storing_new_line(char *storing_line)
{
	char *new_storing_line;
	int	i;
	int	i_newline;

	while (storing_line[i] && storing_line[i] != '\n')
		i++;
	if (!storing_line[i])
	{
		free(storing_line);
		return (NULL);
	}
	new_storing_line = malloc((ft_strlen(storing_line) - i + 1) * sizeof(char));
	if (!new_storing_line)
		return (NULL);
	i++;
	i_newline = 0;
	while (storing_line[i])
		new_storing_line[i_newline++] = storing_line[i++];
	new_storing_line = '\0';
	free(storing_line);
	return (new_storing_line);
}
