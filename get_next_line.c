/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig <rarodrig@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:26:57 by rarodrig          #+#    #+#             */
/*   Updated: 2021/06/11 20:26:57 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	unsigned char	n_c;

	n_c = (unsigned char ) c;
	while (*(unsigned char *) s != n_c)
	{
		if (*(unsigned char *) s == '\0')
		{
			return (NULL);
		}
		++s;
	}
	return ((char *) s);
}

static int	appending(char **str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if ((*str)[i] == '\0')
	{
		*line = ft_strdup(*str);
		if (str != NULL)
		{
			free(*str);
			*str = ft_strdup("");
		}
		return (0);
	}
	*line = ft_substr(*str, 0, i);
	tmp = ft_strdup(*str + i + 1);
	free(*str);
	*str = tmp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			byte_was_read;
	static char	*reaminder;
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	byte_was_read = read (fd, buf, BUFFER_SIZE);
	while (byte_was_read > 0)
	{
		buf[byte_was_read] = '\0';
		if (reaminder == NULL)
			reaminder = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(reaminder, buf);
			free(reaminder);
			reaminder = tmp;
		}
		if (ft_strchr(reaminder, '\n'))
			break ;
		byte_was_read = read (fd, buf, BUFFER_SIZE);
	}
	return (appending(&reaminder, line));
}

int main(void)
{
  char  *line;
  int   fd1;

  fd1 = open("text.txt", O_RDONLY);


	get_next_line(fd1, &line);
	printf("%s\n", line);
	free(line);

	get_next_line(fd1, &line);
	printf("%s\n", line);
	free(line);

}
