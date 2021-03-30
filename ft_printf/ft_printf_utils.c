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

int				ft_strlen(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (i);
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

int			ft_numlen(long long num, t_list *cur)
{
	int	idx;

	idx = 1;
	if (cur->base == 'x' || cur->base == 'X' || cur->base == 'p')
	{
		cur->numeral = 16;
		if (cur->base == 'p')
			idx += 2;
	}
	if (num < 0)
	{
		cur->flag |= PLUS;
		num = -num;
	}
	while (num > cur->numeral - 1)
	{
		++idx;
		num /= cur->numeral;
	}
	return (idx);
}

int					ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}