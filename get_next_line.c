/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:11:49 by mac               #+#    #+#             */
/*   Updated: 2024/10/22 14:37:39 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_find_newline(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer_leido;
	int			bytes_leidos;
	int			newline;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_leido = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer_leido)
		return (NULL);
	while ((bytes_leidos = read(fd, buffer_leido, BUFFER_SIZE)) > 0)
	{
		buffer_leido[bytes_leidos] = '\0';
		saved = ft_strjoin(saved, buffer_leido);
		newline = ft_find_newline(saved);
		if (newline >= 0)
		{
			line = ft_substr(saved, 0, newline + 1);
			temp = ft_substr(saved, newline + 1, ft_strlen(saved) - newline
					- 1);
			free(saved);
			saved = temp;
			free(buffer_leido);
			return (line);
		}
	}
	if (bytes_leidos == 0 && saved && *saved)
	{
		line = ft_strdup(saved);
		free(saved);
		saved = NULL;
		free(buffer_leido);
		return (line);
	}
	free(buffer_leido);
	free(saved);
	saved = NULL;
	return (NULL);
}
