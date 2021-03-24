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
		write(1, cur->str, sizeof(cur->str));
		printf("\n");
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
		// printf("\nflag:: %d\nwidth:: %d\nprec:: %d\nstr:: %s\n", cur->flag, cur->width, cur->prec, cur->str);
		// printf("base:: %c\nbuf:: %s\n", cur->base, cur->buf);
		// puts("");
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
	
	//ft_ptf(&(iter->pNext)); //리스트 확인용 출력
	va_end(ap);
	//ft_free(lst);
	//printf("%d\n", ret);
	return (ret);
}

//d에다가 인자가 들어와야하지 않나..?
//그럼 인자를 어떻게 잘 넘겨야 잘 출력이 되는 걸가요?
//훙ㅇ양훙야!!!!!!???!!!