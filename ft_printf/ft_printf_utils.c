/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejsong <yejsong@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:01:50 by yejsong           #+#    #+#             */
/*   Updated: 2021/03/31 19:02:11 by yejsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int					ft_atoi(char **s)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(**s))
	{
		ret = ret * 10 + **s - '0';
		(*s)++;
	}
	return (ret);
}

int					ft_calloc(size_t number, size_t size, void **ret, char ch)
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

int					ft_numlen(long long num, t_list *cur)
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
