/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_valid_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:10:22 by song-yejin        #+#    #+#             */
/*   Updated: 2021/03/23 18:10:22 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_isbase(char c)
{
	int i;

	i = 0;
	while (BASE[i])
	{
		if (c == BASE[i])
			return (1);
		i++;
	}
	return (0);
	
}

int					ft_get_flag(char **str)
{
	int				ret;
	int				i;

	ret = 0;
	i = 0;
	while(**str && FLAG[i])
	{
		if(**str == FLAG[i])
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

int					ft_get_width(t_list **cur, char **str, va_list ap)
{
	int				ret;

	ret = -1;
	if(ft_isdigit(**str)){
		ret = ft_atoi(str);
	}
	else if(**str == '*')
	{
		++(*str);
		ret = va_arg(ap, int);
		if(ret < 0)
		{
			ret = -ret;
			(*cur)->flag |= LEFT;
		}
	}
	return (ret);
}

int					ft_get_prec(char **str, va_list ap)
{
	int				ret;
	
	ret = -1;
	if(**str == '.')
	{
		++(*str);
		if(ft_isdigit(**str))
			ret = ft_atoi(str);
		else if(**str == '*')
		{
			++(*str);
			ret = va_arg(ap, int);
		}
		else
			ret = 0;
		if(ret < 0)
			ret = -1;
	}
	return (ret);
}
//string, num, char
int				ft_conversion(t_list *cur, va_list ap)
{
	char			ch;

	ch = cur->base;
	if(ch == '%' || ch == 'c')
		return (ft_putchar(cur, ap));
	else if (ch == 's')
		return (ft_putstr(cur, ap));
	else if (ch == 0)
		return (ft_nonval(cur));
	else if (ch == 'd' || ch == 'i' || ch == 'u')
		return (ft_put_decnum(cur, ap));
	return (0);
}