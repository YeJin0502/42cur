/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:01:54 by song-yejin        #+#    #+#             */
/*   Updated: 2021/07/19 20:02:57 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit(char *s)
{
	write(1, s, ft_strlen(s));
	exit(0);
}

void	ft_free(char **line)
{
	if (*line)
		free(*line);
	*line = 0;
}

void			ft_memset(char *dest, int size)
{
	while (size--)
		*(dest++) = 0;
}

void			*ft_calloc(size_t number, size_t size)
{
	void		*ret;
	size_t		idx;

	idx = 0;
	ret = (char *)malloc(size * number);
	if (!ret)
		ft_exit("ERROR");
	return(ret);
}

int				ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

size_t		ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str && *str){
		str++;
		len++;
	}
	return (len);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, &*s++, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else
	{
		if (n >= 10)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

long long		ft_atoi(char **s)
{
	long long	ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret = ret * 10 + **s - '0';
		(*s)++;
	}
	return (ret);
}


size_t		ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest || !src)
		return (0);
	while (i + 1 < n && *src)
	{
		*(dest) = *(src);
		dest++;
		src++;
		i++;
	}
	if (n)
		*dest = '\0';
	while (*src)
	{
		++src;
		++i;
	}
	return (i);
}

