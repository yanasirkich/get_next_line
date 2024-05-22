/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysirkich <ysirkich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:13:25 by yana              #+#    #+#             */
/*   Updated: 2024/05/22 17:08:34 by ysirkich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
}
// Function to read the file and store the contents in storing_line
char	*ft_readfile(int fd, char *storing_line)
{
	char	*buffer;//[BUFFER_SIZE + 1];
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