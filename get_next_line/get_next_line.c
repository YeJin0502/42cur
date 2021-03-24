#include "get_next_line.h"

int ft_free_and_del(char **str)
{
	if (str && *str)
		free(*str);
	*str = NULL;
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static char		*buf[OPEN_MAX];
	size_t			r;
	char			*temp;

	if(fd >= 0 && !buf[fd])
		buf[fd] = ft_strnew(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || OPEN_MAX <= fd || !line || !buf[fd] || (read(fd, buf[fd], 0)) < 0 || !(r = 1))
		return (-1 * ft_free_and_del(&buf[fd]));
	temp = buf[fd];
	*line = ft_strnew(1);
	while (buf[fd][0] != '\n')
	{
		if(!buf[fd][0])
		{
			if(!(r = read(fd, temp, BUFFER_SIZE)))
				break;
			temp[r] = '\0';
			buf[fd] = temp;
		}
		buf[fd] += ft_strappend(buf[fd], line);
	}
	ft_strcpy(buf[fd] + (!r ? 0 : 1), temp, BUFFER_SIZE);
	buf[fd] = temp;
	return (!r ? 0 * ft_free_and_del(&buf[fd]) : 1);
}