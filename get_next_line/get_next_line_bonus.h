#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif
# define RET_SUCCESS 1
# define RET_ERROR -1
# define RET_EOF 0

size_t	ft_strlen(char *str);
void	ft_strcpy(char *src, char *dest, size_t len);
char	*ft_strnew(size_t size);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strappend(char *src, char **dest);
int		get_next_line(int fd, char **line);

#endif