/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:39:26 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 20:54:51 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_ck(t_info *info)
{
	int	player;
	int	i;
	int j;

	player = 0;
	i = -1;
	while (++i < info->height)
	{
		j = -1;
		while (++j < info->width)
		{
			if (!ft_strchr("012NSEW \t", info->map[i][j]))
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
	i = -1;
	while (++i < info->height)
		free(visit[i]);
	free(visit);
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
		ft_exit("ERROR: CHECK FILE MAP");
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