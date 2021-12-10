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

#include "get_next_line_bonus.h"

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

char	*ft_freesec(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

int	get_line2(int fd, char **s, t_list *var)
{
	char	buffer[BUFFER_SIZE + 1];
	int		ret;

	if (!*s)
		*s = ft_strdup("");
	var->ch = ft_strchr(*s, '\n');
	ret = 1;
	while (!var->ch && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = '\0';
		var->ch = *s;
		*s = ft_strjoin(*s, buffer);
		free(var->ch);
		var->ch = ft_strchr(*s, '\n');
	}
	return (ret);
}

char	*d(char **s_buff, t_list *var)
{
	var->line = ft_strdup(*s_buff);
	ft_free(s_buff);
	if (var->line[0] == '\0')
		ft_free(&var->line);
	return (var->line);
}

char	*get_next_line(int fd)
{
	static char	*s_buff[10240];
	t_list		var;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 4096)
		return (NULL);
	var.tab[0] = get_line2(fd, &s_buff[fd], &var);
	if (var.tab[0] == -1)
		return (ft_freesec(&s_buff[fd]));
	if (var.ch)
	{
		var.tab[1] = ft_strlen(s_buff[fd]) - ft_strlen(var.ch);
		var.line = ft_substr(s_buff[fd], 0, var.tab[1] + 1);
		var.ch = s_buff[fd];
		s_buff[fd] = ft_strdup(s_buff[fd] + var.tab[1] + 1);
		free(var.ch);
	}
	else
		return (d(&s_buff[fd], &var));
	if ((var.tab[0] == 0 && s_buff[fd] != NULL) || var.tab[0])
		return (var.line);
	return (NULL);
}
