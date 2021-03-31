/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_num.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejsong <yejsong@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:57:32 by yejsong           #+#    #+#             */
/*   Updated: 2021/03/31 18:58:50 by yejsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				make_num(char *dest, int sz, long long num, t_list *cur)
{
	int				idx;

	idx = 0;
	if (cur->base == 'X')
		idx = 16;
	if (num < 0)
		num = -num;
	while (sz--)
	{
		*(dest--) = DIGIT[(num % cur->numeral) + idx];
		num /= cur->numeral;
	}
	if (cur->base == 'p' && ++dest)
		*(++dest) = 'x';
	while (cur->flag & PLUS && dest != cur->buf && *(dest - 1) == '0')
		dest--;
	if (cur->flag & PLUS)
		*dest = '-';
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
		ft_memset(cur->buf, sz, ' ');
	else if ((cur->flag & LEFT))
	{
		if (cur->flag & PLUS)
			make_num(cur->buf + len, len, num, cur);
		else
			make_num(cur->buf + len - 1, len, num, cur);
	}
	else
		make_num(cur->buf + sz - 1, len, num, cur);
	return (ft_putstring(cur->buf, sz));
}

int					ft_excep(t_list *cur)
{
	int				ret;

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

long long			get_type(char ch, void *p)
{
	if (ch == 'd' || ch == 'i')
		return (*(int *)p);
	else if (ch == 'u' || ch == 'x' || ch == 'X')
		return (*(unsigned int *)p);
	return (*(long long *)p);
}

char				ft_ped(t_list *cur, long long num)
{
	int	num_len;

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
