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

void	ft_memset(char *dest, int sz, char ch)
{
	while (sz--)
		*(dest++) = ch;
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
	ft_memset(temp, size * number, ch);
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

size_t			ft_numlen(long long num, t_list *cur)
{
	int			i;
	int			b;

	b = 15;
	if (cur->base == 'd' || cur->base == 'u' || cur->base == 'i')
		b = 9;
	i = 1;
	if (num < 0){
		num = -num;
		cur->flag |= PLUS;
	}
	while(num > b)
	{
		num /= b + 1;
		i++;
	}
	return (i);
}

int					ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}