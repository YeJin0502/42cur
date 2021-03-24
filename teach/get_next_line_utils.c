// 보너스 헤더와 다르다. 보너스 채점은 보너스 헤더를 호출하기때문이다.
#include "get_next_line.h"

void	*ft_calloc(size_t number, size_t size)
{
	char	*ret;
	char	*tmp;
	size_t	idx;

	idx = 0;
	if (!(ret = malloc(size * number)))
		return (0);
	tmp = ret;
	while (idx++ < number * size)
		*(tmp++) = 0;
	return (void*)ret;
}

void	ft_free(char **s1)
{
	if (s1 && *s1)
		free(*s1);
	// 쓰레기값이 들어가 있을경우 이상한것을 출력할 수 있기 때문에 NULL로 초기화를 해준다.
	*s1 = NULL;
}

// 기존의 strlen과 조금 다르다.
// GNL은 개행을 만났다면 개행까지 출력하고,
// 다음줄에 다시 출력해야 하기때문에 개행을 검사하는 조건이 있다.
size_t	ft_strlen(char *str)
{
	size_t	len;

	// 
	if (!str || *str == '\n')
		return (0);
	len = 0;
	while (*str != '\n' && *str++)
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	char	*cpy;

	if (!dest && !src)
		return (0);
	cpy = (char *)dest;
	while (count--)
		*(cpy++) = *(char *)(src++);
	return (dest);
}

int		ft_strappend(char **line, char *buf)
{
	// 라인의 길이와, 버퍼의 길이를 먼저 구한다.
	const size_t	l_len = ft_strlen(*line);
	const size_t	b_len = ft_strlen(buf);
	int				ret;
	char			*temp;

	// 그리고 temp 변수에 두개의 길이를 합한 길이만큼 할당을 해준다.
	if (!(temp = ft_calloc(l_len + b_len + 1, 1)))
		return (RET_ERROR);
	
	// 우선 line에 있는것을 temp에 담아주고.
	ft_memcpy(temp, *line, l_len);
	// 그 뒤에 buf를 푸쉬백 해준다.
	ft_memcpy(temp + l_len, buf, b_len);

	// 이 line변수는 기존에 저장해뒀던 공간이므로, 새로운것을 뒤에 붙인것을 반환하기 위해 line을 free해준다.
	// 물론 line의 값이 있다면 free하는것이다.
	if (*line)
		free(*line);
	// temp에 저장한 값들을 line에 담아주고,
	*line = temp;
	// buf공간의 길이의 마지막 값이 개행이라면 출력 해야 하기 때문에 success를 아니라면 0을 저장해주고 마지막에 반환한다.
	ret = *(buf + b_len) == '\n' ? RET_SUCCESS : 0;
	// 만약 개행문자까지 저장했다면, buf에 있는 값들을 다음에 저장해주기 위해 앞으로 댕겨줘야한다.
	ft_memcpy(buf, buf + b_len + 1, BUFFER_SIZE - b_len);
	// 댕겨줬기 떄문에 쓰레기값이 있을 확률이 다분함으로 문자열의 끝인 0으로 초기화를 해준다.
	// 그래야 다음에 검사할때 buf의 잔여물을 안전하게 담을수 있기 떄문이다.
	buf[BUFFER_SIZE - b_len] = 0;
	return (ret);
}
