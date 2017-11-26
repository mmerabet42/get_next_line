/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 23:02:14 by mmerabet          #+#    #+#             */
/*   Updated: 2017/11/25 22:58:02 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static int	inner_get_next_line(const int fd, char **line)
{
	static char	buffer[BUFF_SIZE + 1];
	int			bread;

	if (buffer[0])
	{
		if ((bread = ft_strchr_pos(buffer, '\n')) != -1)
			buffer[bread] = '\0';
		if (*line)
			*line = ft_strjoin_clr(*line, buffer, 0);
		else
			*line = ft_strdup(buffer);
		if (bread != -1 && ft_strcpy(buffer, buffer + (bread + 1)))
			return (1);
		ft_strclr(buffer);
	}
	if ((bread = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[bread] = '\0';
		return (inner_get_next_line(fd, line));
	}
	return (*line ? 1 : bread);
}

int			get_next_line(const int fd, char **line)
{
	if (!line)
		return (-1);
	*line = NULL;
	return (inner_get_next_line(fd, line));
}

int main(int argc, char **argv)
{
	int		fd;
	char	*buffer = NULL;
	(void)argc;

	if ((fd = open(argv[1], O_RDONLY)) != -1)
	{
		int	r = 0;
		int	nline = 1;
		while ((r = get_next_line(fd, &buffer)))
			printf("%d:\t '%s'\n", nline++, buffer);
		printf("return : %d\n", r);
	}
	else
		printf("open error\n");
	return (0);
}
