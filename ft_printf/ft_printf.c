/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 15:43:10 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/18 15:43:10 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_ptf(t_list **lst)
{
	t_list			*cur;

	cur = *lst;
	while(cur)
	{
		if (cur->base == 0)
			write(1, cur->str, ft_strlen(cur->str));
		if (cur->base == 'p')
			write(1, "0x", 2);
		write(1, cur->buf, ft_strlen(cur->buf));
		cur = cur->pNext;
	}
	return ;
}

int					ft_print(t_list **lst, va_list ap)
{
	t_list			*cur;
	char			*iter;
	int				ret;
	int tmp;
	cur = (*lst)->pNext;
	ret = 0;
	while(cur)
	{
		iter = cur->str;
		cur->flag = ft_get_flag(&iter);
		cur->width = ft_get_width(&cur, &iter, ap);
		cur->prec = ft_get_prec(&iter, ap);
		tmp = ft_conversion(cur, ap);
		if(tmp == RET_ERROR)
			return (RET_ERROR);
		ret += tmp;
		cur = cur->pNext;
	}
	return (ret);
}

int					ft_printf(const char *fmt, ...)
{
	char			*tmp;
	int				ret;
	va_list			ap;
	t_list			*lst;
	t_list			*iter;

	va_start(ap, fmt);
	tmp = (char *)fmt;
	if(ft_calloc(1, sizeof(t_list), (void *)&lst, 0) == RET_ERROR)
		return (RET_ERROR);
	iter = lst;
	ft_parsing(tmp, &lst);
	ret = ft_print(&iter, ap);
	//ft_ptf(&lst);
	va_end(ap);
	//ft_free(lst);
	return (ret);
}