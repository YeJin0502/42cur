/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:48:07 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/30 18:45:56 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_putstring(char *str, int size)
{
	write(1, str, size);
	return (size);
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
	if(!ft_calloc(1, len, (void *)&cur->buf, padding))
		return (RET_ERROR);
	if((cur->flag & LEFT))
		*(cur->buf) = ch;
	else
		*(cur->buf + len - 1) = ch;
	return (ft_putstring(cur->buf, len));
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
	if (!ft_calloc(1, sz + 1, (void *)&cur->buf, ' '))
		return (RET_ERROR);
	if ((cur->flag & LEFT))
		ft_memcpy(cur->buf, ch, len);
	else
		ft_memcpy(cur->buf + sz - len, ch, len);
	write(1, cur->buf, sz);
	return (ft_putstring(cur->buf, sz));
}

char				ft_ped(t_list *cur, long long num)
{
	int				num_len;

	num_len = ft_numlen(num, cur);
	if (num < 0 && (cur->flag & ZERO) && !(cur->flag & LEFT))
	{
		num_len++;
		if (cur->prec < num_len && cur->prec < 0)
			return ('0');

	}
	else if ((cur->flag & ZERO) && !(cur->flag & LEFT))
	{
		if (cur->prec < num_len && cur->prec < 0)
			return ('0');
	}
	return (' ');
}

long long get_type(char ch, void *p)
{
	if (ch == 'd' || ch == 'i')
		return (*(int *)p);
	else if (ch == 'u' || ch == 'x' || ch == 'X')
		return (*(unsigned int *)p);
	return (*(long long *)p);	
}

int	ft_excep(t_list *cur)
{
	int		ret;

	ret = ft_max(cur->width, 3);
	if (!cur->prec && cur->width < 3)
		ret--;
	if (ft_calloc(ret + 1, 1, (void *)&cur->buf, ' ') == RET_ERROR)
		return (RET_ERROR);
	if (cur->flag & LEFT && !cur->prec)
		ft_memcpy(cur->buf, "0x", 2);
	else if (cur->flag & LEFT)
		ft_memcpy(cur->buf, "0x0", 3);
	else if (!cur->prec)
		ft_memcpy(cur->buf + ret - 2, "0x", 2);
	else
		ft_memcpy(cur->buf + ret - 3, "0x0", 3);
	return (ft_putstring(cur->buf, ret));
}

int					ft_put_num(t_list *cur, void *p)
{
	const long long	num = get_type(cur->base, p);
	const int		len = ft_max(ft_numlen(num, cur), cur->prec);
	const char		pedding = ft_ped(cur, num);
	int				sz;
	
	sz = ft_max(len, cur->width);
	if (num < 0 && sz < len + 1)
		sz++;
	if (cur->prec == 0 && num == 0 && cur->width <= 0)
		sz = 0;
	if (!ft_calloc(1, sz + 1, (void *)&cur->buf, pedding))
		return (RET_ERROR);
	if (cur->prec == 0 && num == 0)	
		ft_memset(cur->buf, sz , ' ');
	else if ((cur->flag & LEFT))
	{
		if(cur->flag & PLUS)
			make_num(cur->buf + len, len, num, cur);
		else
			make_num(cur->buf + len - 1, len, num, cur);
	}
	else
		make_num(cur->buf + sz - 1, len, num, cur);
	return (ft_putstring(cur->buf, sz));
}

int					ft_put_pointer(t_list *cur, va_list ap)
{
	const long long int num = get_type(cur->base, ap);
	int		len = ft_max(ft_numlen(num, cur), cur->prec);
	int				sz;

	sz = ft_max(len, cur->width);
	if (num == 0 && cur->prec == 0)
		len = 1;
	if (num == 0 && cur->width < 3 && cur->prec == 0)
		sz = 2;
	if (num < 0 && sz < len + 1)
		sz++;
	if (!ft_calloc(1, sz + 1, (void *)&cur->buf, ' '))
		return (RET_ERROR);
	if ((cur->flag & LEFT))
	{
		if(cur->flag & PLUS)
			make_num(cur->buf + len, len, num, cur);
		else
			make_num(cur->buf + len - 1, len, num, cur);
	}
	else
		make_num(cur->buf + sz - 1, len, num, cur);
	return (ft_putstring(cur->buf, sz));
}