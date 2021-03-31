/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejsong <yejsong@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:53:06 by yejsong           #+#    #+#             */
/*   Updated: 2021/03/31 19:07:58 by yejsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_free(t_list *lst, int ret)
{
	t_list			*cur;
	t_list			*tmp;

	cur = lst;
	while (cur)
	{
		if (cur->buf)
			free(cur->buf);
		if (cur->str)
			free(cur->str);
		cur->buf = 0;
		cur->str = 0;
		tmp = cur->pnext;
		free(cur);
		cur = 0;
		cur = tmp;
	}
	return (ret);
}

int	ft_putstring(char *str, int size)
{
	write(1, str, size);
	return (size);
}

int	ft_print(t_list **lst, va_list *ap)
{
	t_list			*cur;
	char			*iter;
	int				ret;
	int				tmp;

	cur = (*lst)->pnext;
	ret = 0;
	while (cur)
	{
		iter = cur->str;
		cur->flag = ft_get_flag(&iter);
		cur->width = ft_get_width(&cur, &iter, ap);
		cur->prec = ft_get_prec(&cur, &iter, ap);
		tmp = ft_conversion(cur, ap);
		if (tmp == RET_ERROR)
			return (RET_ERROR);
		ret += tmp;
		cur = cur->pnext;
	}
	return (ret);
}

int	ft_printf(const char *fmt, ...)
{
	char			*tmp;
	int				ret;
	va_list			ap;
	t_list			*lst;
	t_list			*iter;

	va_start(ap, fmt);
	tmp = (char *)fmt;
	if (ft_calloc(1, sizeof(t_list), (void *)&lst, 0) == RET_ERROR)
		return (RET_ERROR);
	iter = lst;
	if (ft_parsing(tmp, &lst) == RET_ERROR)
		return (ft_free(iter, RET_ERROR));
	lst = iter;
	ret = ft_print(&iter, &ap);
	va_end(ap);
	return (ft_free(lst, ret));
}
