/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_valid_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejsong <yejsong@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 19:02:38 by yejsong           #+#    #+#             */
/*   Updated: 2021/03/31 19:05:30 by yejsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isbase(char c)
{
	int	i;

	i = 0;
	while (BASE[i])
	{
		if (c == BASE[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_flag(char **str)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (**str && FLAG[i])
	{
		if (**str == FLAG[i])
		{
			ret |= (1 << i);
			i = 0;
			(*str)++;
		}
		else
			i++;
	}
	return (ret);
}

int	ft_get_width(t_list **cur, char **str, va_list *ap)
{
	int	ret;

	ret = -1;
	if (ft_isdigit(**str))
		ret = ft_atoi(str);
	else if (**str == '*')
	{
		++(*str);
		if ((*cur)->base != 0)
			ret = va_arg(*ap, int);
		if (ret < 0)
		{
			ret = -ret;
			(*cur)->flag |= LEFT;
		}
	}
	return (ret);
}

int	ft_get_prec(t_list **cur, char **str, va_list *ap)
{
	int	ret;

	ret = -1;
	if (**str == '.')
	{
		++(*str);
		if (ft_isdigit(**str))
			ret = ft_atoi(str);
		else if (**str == '*')
		{
			++(*str);
			if ((*cur)->base != 0)
				ret = va_arg(*ap, int);
		}
		else
			ret = 0;
		if (ret < 0)
			ret = -1;
	}
	return (ret);
}

int	ft_conversion(t_list *cur, va_list *ap)
{
	char	c;
	void	*p;

	c = cur->base;
	if (c == '%' || c == 'c')
		return (ft_putchar(cur, ap));
	if (c == 's')
		return (ft_putstr(cur, ap));
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == 'p')
	{
		p = va_arg(*ap, void *);
		if (c == 'p' && p == 0)
			return (ft_excep(cur));
		return (ft_put_num(cur, &p));
	}
	return (ft_putstring(cur->str, cur->size));
}
