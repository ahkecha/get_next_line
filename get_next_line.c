/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkecha <ahkecha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:12:25 by ahkecha           #+#    #+#             */
/*   Updated: 2021/11/12 17:23:39 by ahkecha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	get_line2(int fd, char **s, char **ch)
{
	char	buffer[BUFFER_SIZE + 1];
	int		ret;

	if (!*s)
		*s = ft_strdup("");
	while (!(*ch = ft_strchr(*s, '\n')) && (ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		*ch = *s;
		*s = ft_strjoin(*s, buffer);
		free(*ch);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*s_buff;
	char		*line;
	char		*ch;
	int			tab[2];

	line = NULL;
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647 || fd < 0 || fd > 4864)
		return (NULL);
	tab[0] = get_line2(fd, &s_buff, &ch);
	if (tab[0] == -1)
		return (ft_freesec(&s_buff));
	if (ch)
	{
		tab[1] = ft_strlen(s_buff) - ft_strlen(ch);
		line = ft_substr(s_buff, 0, tab[1] + 1);
		ch = s_buff;
		s_buff = ft_strdup(s_buff + tab[1] + 1);
		free(ch);
	}
	else
	{
		line = ft_strdup(s_buff);
		ft_free(&s_buff);
		if (line[0] == '\0')
			ft_free(&line);
		return (line);
	}
	if ((tab[0] == 0 && s_buff != NULL) || tab[0])
		return (line);
	return (NULL);
}

int main()
{
	char	*line;
	char	*line2;
	int fd;
	int	fd2;

	fd = open("file.txt",O_RDONLY);
	line = NULL;
	// line = get_next_line(fd);
	// printf("|%s|", line);
	// free(line);
	while (1337)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%s", line);
			// free(line);
			// line = NULL;
		}
		// printf("test\n");
		if (line == '\0')
			break ;
	}
	close(fd);
}
