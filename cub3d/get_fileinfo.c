/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fileinfo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:46:50 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 20:49:10 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_append(char **line, char ch, char flag)
{
	const size_t	l_len = ft_strlen(*line);
	int				ret;
	char			*tmp;

	tmp = ft_calloc(l_len + 2, 1, 0);
	ret = ch;
	ft_memcpy(tmp, *line, l_len);
	if (flag != ch)
		*(tmp + l_len) = ch;
	if(*line)
		free(*line);
	*line = tmp;
	return (ret == '\n' ? RET_SUCCESS : 0);
}

int		get_a_line(int fd, char **line, int flag)
{
	static char	ch;
	int			width;
	int			sz;

	width = 0;
	if (fd < 0 || !line)
		return (RET_ERROR);
	while((sz = read(fd, &ch, 1)) > 0)
	{
		width++;
		if (flag == '\n' && !*line && (ch == ' ' || ch == '\n'))
			continue;
		if (ft_append(line, ch, flag))
			return (width);
	}
	return (sz == 0 ? RET_EOF : RET_ERROR);
}

int		info_parsing(char *line, t_info *info)
{
	const char	*inf[8] = {"NO ", "SO ", "WE ", "EA ", "S ", "F ", "C ", "R "};
	const int	len = ft_strlen(line);
	int			i;
	int			inf_len;

	i  = -1;
	while(++i < 8)
	{
		inf_len = ft_strlen((char *)inf[i]);
		if (!ft_strncmp((char *)inf[i], line, inf_len) && !info->cub_info[i])
		{
			if (i < 4)
			{
				info->cub_info[i] = ft_calloc(1, len - 2, 0);
				ft_memcpy(info->cub_info[i], line + 3, len - 2);
			}
			else
			{
				info->cub_info[i] = ft_calloc(1, len, 0);
				ft_memcpy(info->cub_info[i], line + 2, len - 1);
			}
			return (1 << i);
		}
	}
	return (1 << 12);
}

int		cub_parsing(int fd, t_info *info)
{
	char		*line;
	int			status;
	int			flag;

	flag = 0;
	status = 1;
	line = 0;
	while(status > 0)
	{
		if(status >= 1 && flag < 255)
		{
			status = get_a_line(fd, &line, '\n');
			flag |= info_parsing(line, info);
			ft_free(&line);
		}
		else if (status >= 1 && (flag == 255 || flag == 511))
		{
			flag |= (1 << 8);
			status = get_a_line(fd, &line, 0);
			info->height++;
			info->width = ft_max(info->width, status);
		}
	}
	make_map(line, info);
	return (flag);
}

void	make_map(char *line, t_info *info)
{
	char	*start;
	char	*end;
	char	**tmp;
	int 	i;

	i = -1;
	end = line;
	start = line;
	tmp = ft_calloc(info->height, sizeof(char **), ' ');
	while (++i < info->height)
		*(tmp + i) = ft_calloc(info->width, sizeof(char *), ' ');
	i = -1;
	while (line && *end)
	{
		start = end;
		while(*end && *end != '\n')
			end++;
		ft_memcpy(*(tmp + (++i)), start, end - start);
		if (*end)
			end++;
	}
	info->map = tmp;
	ft_free(&line);
}