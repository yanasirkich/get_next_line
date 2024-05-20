/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yana <yana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:13:25 by yana              #+#    #+#             */
/*   Updated: 2024/05/20 22:57:11 by yana             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*storing_line; //storing the remaining string
	char		*line; // line to be returned

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storing_line = ft_readfile(fd, storing_line);
	if (!storing_line)
		return(NULL);
}

char	*ft_readfile(int fd, char *storing_line)
{
	char	*buffer//[BUFFER_SIZE + 1];
	int		bytes;
	
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(storing_line, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if(bytes == -1)
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