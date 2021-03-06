#include "libft.h"

int	check_endl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	check_eof(int reading, char **str)
{
	if (reading == 0)
	{
		if (str)
		{
			free(*str);
			*str = NULL;
		}
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			reading;
	char		*buff;
	static char	*str;
	char		*tmp;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (-1);
	reading = -1;
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || !line)
		return (-1);
	while (check_endl(str) == -1 && reading != 0)
	{
		reading = read(fd, buff, BUFFER_SIZE);
		buff[reading] = '\0';
		tmp = str;
		str = ft_gnl_strjoin(str, buff);
		free(tmp);
	}
	*line = ft_gnl_substr(str, 0, check_endl(str));
	tmp = str;
	str = ft_gnl_substr(str, check_endl(str) + 1, ft_strlen(str));
	free(tmp);
	free(buff);
	return (check_eof(reading, &str));
}
