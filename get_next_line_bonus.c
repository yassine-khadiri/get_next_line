/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:09:39 by ykhadiri          #+#    #+#             */
/*   Updated: 2021/12/10 23:27:54 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buffer)
{
	char	*buf;
	int		ret;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
	ret = 1;
	while (!ft_strchr(buffer, '\n') && ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			return (0);
		}
		buf[ret] = '\0';
		buffer = ft_strjoin(buffer, buf);
	}
	free(buf);
	return (buffer);
}

char	*ft_get_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (0);
	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		line[j++] = buffer[i++];
	if (buffer[i] == '\n')
		line[j++] = buffer[i];
	line[j] = '\0';
	return (line);
}

char	*ft_get_res(char *buffer)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (0);
	}
	len = ft_strlen(buffer) - i;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	i++;
	j = 0;
	while (buffer[i])
		res[j++] = buffer[i++];
	res[j] = '\0';
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[65535];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (0);
	line = ft_get_line(buffer[fd]);
	buffer[fd] = ft_get_res(buffer[fd]);
	return (line);
}
