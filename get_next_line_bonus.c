/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshonta <lshonta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 23:00:42 by lshonta           #+#    #+#             */
/*   Updated: 2021/11/26 19:07:26 by lshonta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_new_string(char *memory)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (memory[i] && memory[i] != '\n')
		i++;
	if (!memory[i])
	{
		free(memory);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(memory) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (memory[i])
		str[j++] = memory[i++];
	str[j] = '\0';
	free(memory);
	return (str);
}

char	*ft_put_line(char *memory)
{
	int		i;
	char	*str;

	i = 0;
	if (!memory[i])
		return (NULL);
	while (memory[i] && memory[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (memory[i] && memory[i] != '\n')
	{
		str[i] = memory[i];
		i++;
	}
	if (memory[i] == '\n')
	{
		str[i] = memory[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read_string(int fd, char *memory)
{
	char	*tmp;
	int		byte;

	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	byte = 1;
	while (!ft_strchr(memory, '\n') && byte != 0)
	{
		byte = read (fd, tmp, BUFFER_SIZE);
		if (byte == -1)
		{
			free (tmp);
			return (NULL);
		}
		tmp[byte] = '\0';
		memory = ft_strjoin(memory, tmp);
	}
	free (tmp);
	return (memory);
}

char	*get_next_line(int fd)
{
	static char	*memory[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	memory[fd] = ft_read_string(fd, memory[fd]);
	if (!memory[fd])
		return (NULL);
	line = ft_put_line(memory[fd]);
	memory[fd] = ft_new_string(memory[fd]);
	return (line);
}

// #include "stdio.h"
// #include <fcntl.h>

// int main()
// {
// 	int fd;

// 	fd = open("text", O_RDONLY);
// 	int fd2 = open("text2", O_RDONLY);
// 	// fd = 0;
// 	char* line = get_next_line(fd);
// 	char *line2 = get_next_line(fd2);
// 	while(line || line2)
// 	{
// 		printf("1: %s 2: %s", line, line2);
// 		line = get_next_line(fd);
// 		line2 = get_next_line(fd2);
// 	}
// }