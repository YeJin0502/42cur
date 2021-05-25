/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:32:25 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 20:48:09 by song-yejin       ###   ########.fr       */
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

void	ft_memset(char *dest, int size, char ch)
{
	while (size--)
		*(dest++) = ch;
}

int		ft_strncmp(char *str1, char *str2, size_t n)
{
	char	*s1;
	char	*s2;

	s1 = str1;
	s2 = str2;
	if (!str1 || !str2)
		return (RET_ERROR);
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