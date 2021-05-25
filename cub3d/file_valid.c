/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:52:12 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 20:50:57 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		file_cker(char *filename, char *extension)
{
	const int len = ft_strlen(filename);
	int	i;

	i = -1;
	while (++i < len)
	{
		if (filename[i] >= 'A' && filename[i] <= 'Z')
			filename[i] += 32;
	}
	if (ft_strncmp(extension, filename + len - 4, 4))
		return (RET_ERROR);
	return (RET_SUCCESS);
}

int	texture_ck(char *s, t_info *info, int i)
{
	int fd;
	int ret;

	info->cub_info[i] = (unsigned char *)s;
	if (file_cker(s, ".xpm") == RET_ERROR)
		ft_exit("ERROR: CHECK FILE NAME");
	fd = open(s, O_RDONLY);
	ret = RET_SUCCESS;
	if (fd < 0)
		ret = RET_ERROR;
	close(fd);
	return (ret);
}

int	ft_valid(t_info *info)
{
	if (contents_ck(info) == RET_ERROR)
		ft_exit("ERROR: CHECK FILE CONTENTS");
	if (map_ck(info) == RET_ERROR)
		ft_exit("ERROR: CHECK FILE MAP");
	return (RET_SUCCESS);
}

int	contents_ck(t_info *info)
{
	char	*s;
	int	i;
	int	ret;

	i = -1;
	while(++i < 8)
	{
		s = (char *)info->cub_info[i];
		while (*s == ' ' || *s == '\t')
			s++;
		if (i >= 0 && i <= 4)
			ret = texture_ck(s, info, i);
		else if (i == 7)
			ret = win_parsing(s, info, i);
		else
			ret = rgb_parsing(s, info, i);
		if (ret == RET_ERROR)
			return (RET_ERROR);
	}
	return (RET_SUCCESS);
}