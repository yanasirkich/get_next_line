/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysirkich <ysirkich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:20:46 by yana              #+#    #+#             */
/*   Updated: 2024/05/24 17:15:47 by ysirkich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Helper function to find the first occurrence of a character in a string
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *) &s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}
// Helper function to join two strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i1;
	size_t	i2;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i1 = 0;
	i2 = 0;
	while (s1[i1] != '\0')
	{
		str[i1] = s1[i1];
		i1++;
	}
	while (s2[i2] != '\0')
	{
		str[i1 + i2] = s2[i2];
		i2++;
	}
	str[i1 + i2] = '\0';
	return (str);
}

// Helper function to get the length of a string
size_t ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}