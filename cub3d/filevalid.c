/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filevalid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:52:12 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/20 22:16:52 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		file_cker(char *filename, char *extension)
{
	const int len = ft_strlen(filename);

	if (ft_strncmp(extension, filename + len - 4, 4))
		return (RET_ERROR);
	return (RET_SUCCESS);
}

int	texture_ck(char *s)
{
	//int fd;
	int ret;

	if (file_cker(s, ".xpm") == RET_ERROR)
		ft_exit("ERROR: CHECK FILE NAME");
	//printf("%s\n", s);
	//fd = open(s, O_RDONLY);
	ret = RET_SUCCESS;
	// if (fd < 0)
		// ret = RET_ERROR;
	// close(fd);
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

int	map_ck(t_info *info)
{
	int	player;
	int	i;
	int j;

	player = 0;
	i = -1; //세로 개수
	while (++i < info->height)
	{
		j = -1;// 가로개수
		while (++j < info->width)
		{
			if (!ft_strchr("012NSEW ", info->map[i][j]))
				return (RET_ERROR);
			if (ft_strchr("NSEW", info->map[i][j]))
			{
				info->player_x = i;
				info->player_y = j;
				player++;
			}
		}
	}
	if (player != 1)
		return (RET_ERROR);
	if (map_closed_ck(info) == RET_ERROR)
		return (RET_ERROR);
	return (RET_SUCCESS);
}

int map_closed_ck(t_info *info)
{
	int		**visit;
	int		status;
	int		i;
	
	i = -1;
	visit = ft_calloc(info->height, sizeof(int **), 0);
	while (++i < info->height)
		visit[i] = ft_calloc(info->width, sizeof(int *), 0);
	status = dfs(info->player_x, info->player_y, info, visit);
	return (status);
}

int	dfs(int x, int y, t_info *info, int **visit)
{
	const int	dx[] = {0, 0, 1, -1};
	const int	dy[] = {1, -1, 0, 0};
	int	i;
	int	nx;
	int	ny;
	
	visit[x][y] = 1;
	if(x + 1 >= info->height || y + 1 >= info->width \
	 || x - 1 < 0 || y - 1 < 0 || info->map[x][y] == ' ')
		ft_exit("ERROR: CHECK FILE MAP"); //재귀이기때문에!!! return ㄴㄴ
	i = -1;
	while (++i < 4)
	{
		nx = dx[i] + x;
		ny = dy[i] + y;
		if(visit[nx][ny] || info->map[nx][ny] == '1') 
			continue;
		dfs(nx, ny, info, visit);
	}
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
		s = (char *)info->cub_info[i]; //unsigned char
		while (*s == ' ')
			s++;
		if (i >= 0 && i <= 4)
			ret = texture_ck(s);
		else if (i == 7)
			ret = win_parsing(s, info, i);
		else
			ret = rgb_parsing(s, info, i);
		if (ret == RET_ERROR)
			return (RET_ERROR);
	}
	return (RET_SUCCESS);
}

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
			val[cnt] = ft_min(ft_atoi(&s), tmp[cnt]); //max값 나중에 수정해주세요 ^^
		}
		if (*s && *s != ' ')
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
		if ((*s && !ft_strchr(" ,", *s)) || val[cnt] > 255)
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
		info->f_rgb = rgb2hex(tmp); //나중에 줄 개수 보고 함수 빼던지 합시다! 예진!!
	else if (inf == 6)
		info->c_rgb = rgb2hex(tmp);
	return (RET_SUCCESS);
}