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

int					ft_nonval(t_list *cur)
{
	int				len;

	len = ft_strlen(cur->str);
	write(1, cur->str, len);
	return (len);
}

int					ft_putchar(t_list *cur, va_list ap)
{
	char			ch;
	char			padding;
	int				len;

	len = cur->width;
	ch = '%';
	padding = ' ';
	if (cur->base == 'c')
		ch = va_arg(ap, int);
	if (len <= 0)
		len = 1;
	if (!(cur->flag & LEFT) && (cur->flag & ZERO))
		padding = '0';
	if(ft_calloc(1, len, (void *)&cur->buf, padding) == RET_ERROR)
		return (RET_ERROR);
	if((cur->flag & LEFT))
		*(cur->buf) = ch;
	else
		*(cur->buf + len - 1) = ch;
	write(1, cur->buf, len);
	return (len);
}

int					ft_putstr(t_list *cur, va_list ap)
{
	int				sz; //출력물의 사이즈
	int				len; //문자의 길이
	char			*ch;


	ch = va_arg(ap, char *);
	if (ch == NULL)
		len = 6;
	else
		len = ft_strlen(ch);
	sz = cur->width;
	if (cur->prec != -1 && cur->prec < len)
		len = cur->prec;
	if (sz != -1 && sz < len)
		sz = len;
	if (cur->prec == 0)
		sz = cur->width;
	if (ft_calloc(1, sz + 1, (void *)&cur->buf, ' ') == RET_ERROR)
		return (RET_ERROR);
	if ((cur->flag & LEFT))
		ft_memcpy(cur->buf, ch, len);
	else
		ft_memcpy(cur->buf + sz - len, ch, len);
	write(1, cur->buf, sz);
	return (sz);
}

// int					ft_putnum(t_list *cur, va_list ap)
// {
	
// }

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