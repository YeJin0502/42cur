/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:41:41 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 19:34:11 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int		ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int		ft_atoi(char **s)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret = ret * 10 + **s - '0';
		(*s)++;
		if (ret < 0)
		{
			while (ft_isdigit(**s))
				(*s)++;
			return (RET_ERROR);
		}
	}
	return (ret);
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