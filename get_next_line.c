/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <mel-oual@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 01:30:31 by mel-oual          #+#    #+#             */
/*   Updated: 2020/05/05 03:14:51 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	*safe_memory(char *str, char *temp)
{
	free(str);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

int		delete(char **as)
{
	if (as == NULL)
		return (0);
	free(*as);
	*as = NULL;
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*lineof[4864];
	t_gnl		g;

	g.p = 0;
	if (fd < 0 || !line || read(fd, g.buff, 0) < 0)
		return (-1);
	(!lineof[fd]) ? (lineof[fd] = ft_strnew(0)) : lineof[fd];
	while ((g.c = read(fd, g.buff, BUFF_SIZE)))
	{
		g.buff[g.c] = '\0';
		lineof[fd] = safe_memory(lineof[fd], ft_strjoin(lineof[fd], g.buff));
		if (ft_strchr(lineof[fd], '\n'))
			break ;
	}
	while (lineof[fd][g.p] != '\n' && lineof[fd][g.p] != '\0')
		g.p++;
	*line = ft_strsub(lineof[fd], 0, g.p);
	if (!ft_strlen(lineof[fd]) && !g.p && !g.c)
		return (delete(&lineof[fd]));
	if (lineof[fd][g.p] == '\n')
		lineof[fd] = safe_memory(lineof[fd], ft_strdup(lineof[fd] + g.p + 1));
	else
		lineof[fd] = safe_memory(lineof[fd], ft_strdup(lineof[fd] + g.p));
	return (1);
}
