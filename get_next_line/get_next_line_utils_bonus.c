#include "get_next_line_bonus.h"

size_t		ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str && *str && *str++) //안되면 고치기
		len++;
	return (len);
}

void		ft_strcpy(char *src, char *dest, size_t len)
{
	size_t	i;
	
	i = 0;
	while (src && *src && i < len)
	{
		dest[i] =src[i];
		i++;
	}
	dest[i] = '\0';
}

char		*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = malloc(sizeof(char *) * size)))
		return (NULL);
	while (size--)
		*(str++) = '\0';
	return (str);
}

size_t				ft_strappend(char *src, char **dest)
{
	const size_t	s_len = ft_strlen(src);
	const size_t	d_len = ft_strlen(*dest);
	char			*temp;

	if (!(temp = ft_strnew(s_len + d_len + 1)))
		return (0);
	ft_strcpy(*dest, temp, d_len);
	if (*dest)
		free(*dest);
	*dest = temp;
	ft_strcpy(src, &temp[d_len], s_len);
	return (s_len);
}