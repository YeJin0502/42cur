#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
// 버퍼사이즈는 채점서버에서 임의로 다른 숫자를 날릴 수 있다.
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
// OPEN_MAX또한 마찬가지 아닐까?
# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif
// 플래그 같은 개념이다. 정수 1, -1, 0 으로 3가지(에러, EOF, 성공)를 구분하기 위해 선언했다.
# define RET_SUCCESS 1
# define RET_ERROR -1
# define RET_EOF 0

int		get_next_line(int fd, char **line);
void	*ft_calloc(size_t number, size_t size);
void	ft_free(char **s1);
size_t	ft_strlen(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t count);
int		ft_strappend(char **line, char *buf);
#endif
