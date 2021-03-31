/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejsong <yejsong@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:56:20 by yejsong           #+#    #+#             */
/*   Updated: 2021/03/31 18:57:04 by yejsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_putchar(t_list *cur, va_list *ap)
{
	char	ch;
	char	padding;
	int		len;

	len = cur->width;
	ch = '%';
	padding = ' ';
	if (cur->base == 'c')
		ch = va_arg(*ap, int);
	if (len <= 0)
		len = 1;
	if (!(cur->flag & LEFT) && (cur->flag & ZERO))
		padding = '0';
	if (!ft_calloc(1, len, (void *)&cur->buf, padding))
		return (RET_ERROR);
	if ((cur->flag & LEFT))
		*(cur->buf) = ch;
	else
		*(cur->buf + len - 1) = ch;
	return (ft_putstring(cur->buf, len));
}

int					ft_putstr(t_list *cur, va_list *ap)
{
	int				sz;
	int				len;
	char			*ch;

	ch = va_arg(*ap, char *);
	if (ch == NULL)
		len = 6;
	else
		len = ft_strlen(ch);
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
	return (ft_putstring(cur->buf, sz));
}
