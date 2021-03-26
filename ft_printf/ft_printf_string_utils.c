/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:10:00 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/23 18:10:00 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_memcpy(char *dest, char *src, size_t count)
{
	char	*t_dest;
	char	*t_src;
	const char	*nsrc = "(null)";

	t_dest = (char *)dest;
	t_src = (char *)src;
	if (src == NULL)
		while(count--)
		 *(t_dest++) = *(nsrc++);
	else
		while (count--)
			*(t_dest++) = *(t_src++);
}

int					ft_addline(char *fmt, char *iter, t_list **lst, int ck)
{
	t_list			*tmp;
	t_list			*cur;

	cur = *lst;
	if(!ft_calloc(1, sizeof(t_list), (void *)&tmp, 0))
		return (RET_ERROR);
	if(!(ft_calloc(iter - fmt + 1, 1, (void *)&(tmp->str), 0)))
		return (RET_ERROR);
	ft_memcpy(tmp->str, fmt, iter - fmt);
	if (ck == 1)
		tmp->base = *iter;
	while (cur->pNext)
		cur = cur->pNext;
	cur->pNext = tmp;
	return (RET_SUCCESS);
}

int					ft_parsing(char *fmt, t_list **lst)
{
	char			*iter;

	iter = fmt;
	while (*iter)
	{
		if (*iter == '%')
		{
			if(iter != fmt && ft_addline(fmt, iter, lst, 0) == RET_ERROR)
				return (RET_ERROR);
			fmt = ++iter;
			while (!(ft_isbase(*iter)))
				iter++;
			if(ft_addline(fmt, iter, lst, 1) == RET_ERROR)
				return (RET_ERROR);
			fmt = ++iter;
		}
		else
			iter++;
	}
	if(iter != fmt && ft_addline(fmt, iter, lst, 0) == RET_ERROR)
		return (RET_ERROR);
	return (RET_SUCCESS);
}

void				make_num(char *dest, int sz, long long num, t_list *cur)
{
	int				b;
	int				i;


	b = 16;
	if (cur->base == 'd' || cur->base =='i' || cur->base == 'u')
		b = 10;
	if (num < 0)
		num = -num;
	while(sz--)
	{
		i = num % b;
		*(dest--) = HEXA[i];
		num /= 10;
	}
	while(*(dest - 1) == '0')
		dest--;
	if(cur->flag & PLUS)
		*(dest) = '-';
}