/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejsong <yejsong@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:59:31 by yejsong           #+#    #+#             */
/*   Updated: 2021/03/31 19:07:58 by yejsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_memcpy(char *dest, char *src, size_t count)
{
	char			*t_dest;
	char			*t_src;
	const char		*nsrc = "(null)";

	t_dest = (char *)dest;
	t_src = (char *)src;
	if (src == NULL)
		while (count--)
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
	if (!ft_calloc(1, sizeof(t_list), (void *)&tmp, 0))
		return (RET_ERROR);
	if (!(ft_calloc(iter - fmt + 1, 1, (void *)&(tmp->str), 0)))
		return (RET_ERROR);
	ft_memcpy(tmp->str, fmt, iter - fmt);
	tmp->numeral = 10;
	tmp->size = iter - fmt;
	if (ck == 1)
		tmp->base = *iter;
	while (cur->pnext)
		cur = cur->pnext;
	cur->pnext = tmp;
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
			if (iter != fmt && ft_addline(fmt, iter, lst, 0) == RET_ERROR)
				return (RET_ERROR);
			fmt = ++iter;
			while (!(ft_isbase(*iter)))
				iter++;
			if (ft_addline(fmt, iter, lst, 1) == RET_ERROR)
				return (RET_ERROR);
			fmt = ++iter;
		}
		else
			iter++;
	}
	if (iter != fmt && ft_addline(fmt, iter, lst, 0) == RET_ERROR)
		return (RET_ERROR);
	return (RET_SUCCESS);
}

void				ft_memset(char *dest, int sz, char ch)
{
	while (sz--)
		*(dest++) = ch;
}

int					ft_strlen(char *str)
{
	int				i;

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
