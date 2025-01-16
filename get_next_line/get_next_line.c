/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:57:39 by ademarti          #+#    #+#             */
/*   Updated: 2024/01/16 19:15:32 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*put_in_stash(int fd, char *buffer, char *stash)
{
	char	*temp;
	ssize_t	bytesread;

	bytesread = 1;
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (bytesread == 0)
			break ;
		buffer[bytesread] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*make_line(char *stash)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\0')
	{
		if (stash[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	sub = (char *)malloc(sizeof(char) * (i + 2));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, stash, i + 1);
	sub[i] = '\0';
	return (sub);
}

char	*remove_line(char *stash, char *line)
{
	char	*temp;
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	temp = (char *)malloc(sizeof(char *) * (
				ft_strlen(stash) - ft_strlen(line) + 1));
	if (!temp)
	{
		free(stash);
		return (NULL);
	}
	j = 0;
	i = ft_strlen(line);
	while (stash[i] != '\0')
		temp[j++] = stash[i++];
	temp[j] = '\0';
	free(stash);
	if (!*temp)
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*new_stash;
	static char	*stash;
	char		*line;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	new_stash = put_in_stash(fd, buffer, stash);
	free(buffer);
	buffer = NULL;
	if (!new_stash)
		return (NULL);
	line = make_line(new_stash);
	stash = remove_line(new_stash, line);
	return (line);
}

// #include <stdio.h>
// int main()
// {
// 	int fd;
// 	char *result;

// 	fd = open("41_no_nl", O_RDONLY);
// 	result = get_next_line(fd);
// 	printf("%s", result);
// 	free(result);
// 	result = get_next_line(fd);
// 	printf("%s", result);
// 	free(result);
// 	// result = get_next_line(fd);
// 	// printf("%s", result);
// 	// free(result);
// 	// result = get_next_line(fd);
// 	// printf("%s", result);
// 	// free(result);
// 	// result = get_next_line(fd);
// 	// printf("%s", result);
// 	// free(result);
// 	close(fd);
// }
