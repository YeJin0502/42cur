/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:10:14 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/23 18:10:14 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_isdigit(char c)
{
	return(c >= '0' && c <= '9');
}

int					ft_atoi(char **s){
	int				ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret = ret * 10 + **s - '0';
		(*s)++;
	}
	return(ret);
}

int		ft_calloc(size_t number, size_t size, void **ret, char ch)
{
	char	*temp;
	size_t	idx;

	idx = 0;
	*ret = (char *)malloc(size * number);
	if (!*ret)
		return (0);
	temp = *ret;
	while (idx++ < number * size)
		*(temp++) = ch;
	return (1);
}

size_t				ft_strlen(const char *str)
{
	size_t			i;

	i = 0;
	while (str && *str)
	{
		str++;
		i++;
	}
	return (i);
}
