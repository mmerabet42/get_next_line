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
#include <stdio.h>

int	get_next_line(const int fd, char **line)
{
	static char	buffer[BUFF_SIZE + 1];
	static int	l = 0;
	int			bread;

	if (!line)
		return (-1);
	if (ft_strlen(buffer) < BUFF_SIZE)
	{
		*line = NULL;
	}
	while (buffer[0])
	{
		//printf("P: '%s'\n", buffer);
		if ((bread = ft_strchr_pos(buffer, '\n')) != -1)
			buffer[bread] = '\0';
		//printf("l: '%s'\n", buffer);
		if (*line)
			*line = ft_strjoin_clr(*line, buffer, 0);
		else
			*line = ft_strdup(buffer);
		//printf("line: '%s'\n", *line);
		if (bread != -1)
		{
			//printf("EOL FOUND\n");
			ft_strcpy(buffer, buffer + (bread + 1));
			l = 0;
			return (1);
		}
		ft_strclr(buffer);
	}
	if ((bread = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[bread] = '\0';
		l = 1;
		return (get_next_line(fd, line));
	}
	return (*line ? 1 : bread);
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
			printf("%d : '%s'\n", nline++, buffer);
		printf("return : %d\n", r);
	}
	else
		printf("open error\n");
	return (0);
}
