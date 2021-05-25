/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:25:28 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 20:10:59 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_init(t_info *info, t_game *g)
{
	int	i;

	i = -1;
	g->buf = ft_calloc(info->win_y, sizeof(int *), 0);
	while (++i < info->win_y)
		g->buf[i] = ft_calloc(info->win_x, sizeof(int), 0);
	g->zBuffer = ft_calloc(info->win_x, sizeof(double), 0);
	load_texture(info, g);
	g->win_x = info->win_x;
	g->win_y = info->win_y;
	g->height = info->height;
	g->width = info->width;
	player_init(info, g);
	g->c_rgb = info->c_rgb;
	g->f_rgb = info->f_rgb;
	copy_map(info, g);
	g->spriteO = (int *)ft_calloc(g->numSprite, sizeof(int), 0);
	g->spriteD = (double *)ft_calloc(g->numSprite, sizeof(double), 0);
	g->save = info->save;
}

void	player_init(t_info *i, t_game *g)
{
	g->posX = 1.0 * i->player_x + 0.37;
	g->posY = 1.0 * i->player_y + 0.37;
	if (i->map[i->player_x][i->player_y] == 'N')
	{
		g->dirX = -1.0;
		g->planeY = 0.66;
	}
	else if (i->map[i->player_x][i->player_y] == 'E')
	{
		g->dirY = 1.0;
		g->planeX = 0.66;
	}
	else if (i->map[i->player_x][i->player_y] == 'S')
	{
		g->dirX = 1.0;
		g->planeY = -0.66;
	}
	else if (i->map[i->player_x][i->player_y] == 'W')
	{
		g->dirY = -1.0;
		g->planeX = -0.66;
	}
}

void	copy_map(t_info *info, t_game *g)
{
	int	i;
	int	j;

	i = -1;
	g->map = (char **)ft_calloc(info->height, sizeof(char *), 0);
	while (++i < info->height)
	{
		g->map[i] = (char *)ft_calloc(info->width, sizeof(char), 0);
		ft_memcpy(g->map[i], info->map[i], info->width);
	}
	i = -1;
	while (++i < info->height)
	{
		j = -1;
		while (++j < info->width)
		{
			if (ft_isdigit(g->map[i][j]))
				g->map[i][j] -= '0';
			else
				g->map[i][j] = 0;
			if (g->map[i][j] == 2)
				g->numSprite++;
		}
	}
	sprites_ck(info, g);
	// g->numSprite++;
	// sprites_location(info, g);
	// i = -1;
	// while (++i < info->height)
		// free(info->map[i]);
	// free(info->map);
}

void	sprites_ck(t_info *info, t_game *g)
{
	int	i;

	g->numSprite++;
	sprites_location(info, g);
	i = -1;
	while (++i < info->height)
		free(info->map[i]);
	free(info->map);
}

void	sprites_location(t_info *info, t_game *g)
{
	int	i;
	int	j;

	g->s = (t_loca *)ft_calloc(g->numSprite, sizeof(t_loca), 0);
	i = -1;
	int ck = 0;
	while (++i < info->height)
	{
		j = -1;
		while (++j < info->width)
		{
			if (g->map[i][j] == 2)
			{
				g->s[ck].x = (double)i + 0.5;
				g->s[ck].y = (double)j + 0.5;
				ck++;
				g->map[i][j] = 0;
			}
		}
	}
}