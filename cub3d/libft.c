/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:41:41 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/20 20:15:14 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (!*s && !c)
		return (s);
	return (NULL);
}

int		ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int		ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int		ft_atoi(char **s, int max)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret = ret * 10 + **s - '0';
		(*s)++;
		if (ret > max)
			return (RET_ERROR);
	}
	return (ret);
}

void	ft_memset(char *dest, int size, char ch)
{
	while (size--)
		*(dest++) = ch;
}

void	ft_free(char **line)
{
	if (*line)
		free(*line);
	*line = 0;
}

void	*ft_calloc(size_t number, size_t size, char ch)
{
	void	*ret;
	size_t	idx;

	idx = 0;
	ret = (char *)malloc(size * number);
	if (!ret)
		ft_exit("ERROR memory alloc failed");
	ft_memset(ret, size * number, ch);
	return(ret);
}
int		ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

int		ft_min(int x, int y)
{
	if(x < y)
		return (x);
	return (y);
}

int		ft_strncmp(char *str1, char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (n && *s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		n--;
	}
	return (n == 0 ? 0 : *s1 - *s2);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str){
		str++;
		len++;
	}
	return (len);
}

void	*ft_memcpy(void *dest, void *src, size_t count)
{
	char	*cpy;

	if (!dest && !src)
		return (0);
	cpy = (char *)dest;
	while (count--)
		*(cpy++) = *(char *)(src++);
	return (dest);
}