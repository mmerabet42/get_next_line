/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 23:02:14 by mmerabet          #+#    #+#             */
/*   Updated: 2017/11/26 16:28:22 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static int	inner_get_next_line(const int fd, char **line)
{
	static char	buffer[FD_MAX][BUFF_SIZE + 1];
	int			bread;

	if (buffer[fd][0])
	{
		if ((bread = ft_strchr_pos(buffer[fd], '\n')) != -1)
			buffer[fd][bread] = '\0';
		if (*line)
			*line = ft_strjoin_clr(*line, buffer[fd], 0);
		else
			*line = ft_strdup(buffer[fd]);
		if (bread != -1 && ft_strcpy(buffer[fd], buffer[fd] + (bread + 1)))
			return (1);
		ft_strclr(buffer[fd]);
	}
	if ((bread = read(fd, buffer[fd], BUFF_SIZE)) > 0)
	{
		buffer[fd][bread] = '\0';
		return (inner_get_next_line(fd, line));
	}
	return (*line ? 1 : bread);
}

int			get_next_line(const int fd, char **line)
{
	if (fd >= FD_MAX || fd < 0 || !line)
		return (-1);
	*line = NULL;
	return (inner_get_next_line(fd, line));
}
