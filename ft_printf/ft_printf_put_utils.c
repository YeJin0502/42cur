/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:48:07 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/25 16:46:54 by song-yejin       ###   ########.fr       */
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
		len = (int)ft_strlen(ch);
	if (cur->prec != -1 && cur->prec < len)
		len = cur->prec;
	if (cur->width != -1 && cur->width > len)
		sz = cur->width;
	else
		sz = len;
	if (ft_calloc(1, sz + 1, (void *)&cur->buf, ' ') == RET_ERROR)
		return (RET_ERROR);
	if ((cur->flag & LEFT))
		ft_memcpy(cur->buf, ch, len);
	else
		ft_memcpy(cur->buf + sz - len, ch, len);
	write(1, cur->buf, sz);
	return (sz);
}

void				make_num(char *dest, int sz, long long num)
{
	int				ck;

	ck = 0;
	if (num < 0){
		num = -num;
		ck = 1;
	}
	while(sz--)
	{
		if(sz == 0 && ck == 1){
			*(dest) = '-';
		}
		else{
			*(dest--) = num % 10 + '0';
			num /= 10;
		}
	}
}
 
int					ft_put_decnum(t_list *cur, va_list ap)
{
	int				num;
	int				sz;
	int				len;
	int				tmp;

	num = va_arg(ap, int);
	len = ft_numlen(num);
	sz = cur->width;
	if (num < 0)
		cur->prec += 1;
	if(sz < cur->prec)
		sz = cur->prec;
	if(sz < len)
		sz = len;
	if (cur->prec < len)
		tmp = len;
	else
		tmp = cur->prec;
	if (!ft_calloc(1, sz + 1, (void *)&cur->buf, ' '))
		return (RET_ERROR);
	if (cur->prec < 0)
		cur->prec = 0;
	if ((cur->flag & LEFT))
	{
		ft_memset(cur->buf, cur->prec, '0');
		make_num(cur->buf + tmp - 1, tmp, num);
	}
	else
	{
		ft_memset(cur->buf + (sz - cur->prec), cur->prec, '0');
		make_num(cur->buf + sz - 1, len, num);
	}
	write(1, cur->buf, sz);
	return (sz);
}