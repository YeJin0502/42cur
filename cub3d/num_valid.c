/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:37:58 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 20:51:15 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	win_parsing(char *s, t_info *info, int inf)
{
	int	val[4];
	int	cnt;
	int tmp[2];

	cnt = -1;
	tmp[0] = info->win_x;
	tmp[1] = info->win_y;
	while (*s && cnt < 3)
	{
		if (ft_isdigit(*s))
		{
			++cnt;
			val[cnt] = ft_min(ft_atoi(&s), tmp[cnt]);
		}
		if ((*s && !ft_strchr(" \t", *s)) || val[cnt] == RET_ERROR || val[cnt] == 0)
			return (RET_ERROR);
		
		s++;
	}
	if (cnt != 1)
		return (RET_ERROR);
	return (put_num(val, info, inf));	
}

int	rgb_parsing(char *s, t_info *info, int inf)
{
	int	val[5];
	int	cnt;
	int	c;

	cnt = -1;
	c = 0;
	while (*s && cnt < 4)
	{
		if (ft_isdigit(*s) && c - 1 == cnt)
			val[++cnt] = ft_atoi(&s);
		if ((*s && !ft_strchr(" ,\t", *s)) || val[cnt] > 255 || val[cnt] == RET_ERROR)
			return (RET_ERROR);
		if (*s == ',')
			c++;
		s++;
	}
	if (cnt != 2)
		return (RET_ERROR);
	return (put_num(val, info, inf));
}

int	rgb2hex(int *tmp)
{
	int	ret;
	
	ret = 256 * 256 * tmp[0] + 256 * tmp[1] + tmp[2];
	return (ret);
}

int	put_num(int *tmp, t_info *info, int inf)
{
	if (inf == 7)
	{
		info->win_x = tmp[0];
		info->win_y = tmp[1];
	}
	else if (inf == 5)
		info->f_rgb = rgb2hex(tmp);
	else if (inf == 6)
		info->c_rgb = rgb2hex(tmp);
	return (RET_SUCCESS);
}