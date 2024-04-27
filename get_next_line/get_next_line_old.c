/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:00:03 by amdemuyn          #+#    #+#             */
/*   Updated: 2024/04/25 20:49:15 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

int	check_end_line(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*str_dup(char *str)
{
	int		i = 0;
	char	*dup;

	dup = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (0);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*str_join(char *str, char *str2)
{
	int i = 0;
	int j = 0;
	char	*join;

	join = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(str2) + 1));
	if (!join)
		return (0);

	while (str[i])
	{
		join[i] = str[i];
		i++;
	}
	while (str2[j])
	{
		join[i] = str2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_trim(char *line)
{
	int	i = 0;
	char *stash;

	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (0);
	i++;
	if (!line[i])
		return (0);
	stash = str_dup(line + i);
	line[i] = '\0';
	return (stash);
}

char	*get_line(int fd, char *buffer, char *stash)
{
	int reading;
	char *temp;

	reading = 1;
	while (reading)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading < 0)
			return (0);
		if (reading == 0)
			break;
		buffer[reading] = '\0';
		if (!stash)
			stash = str_dup("");
		temp = str_dup(stash);
		free(stash);
		stash = str_join(temp, buffer);
		free(temp);
		if (check_end_line(buffer))
			break;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	line = get_line(fd, buffer, stash);
	free (buffer);
	if (!line)
	{
		free(stash);
		return(0);
	}
	stash = ft_trim(line);
	return (line);
}


/*int	main(int argc, char **argv)
{
	(void)argc;
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}*/

