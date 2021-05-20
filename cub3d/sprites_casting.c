/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_casting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:20:36 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/20 19:23:43 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_casting(t_game *g)
{
	t_scasting	ts;
	int			i;

	ft_memset((char *)&ts, sizeof(t_scasting), 0);
	sprite_init(g, &ts);
	i = -1;
	while (++i < g->numSprite)
	{
		sprite_calc(g, &ts, i);
		draw_sprites(g, &ts);
	}
}

void	sprite_init(t_game *g, t_scasting *ts)
{
	int	i;

	i = -1;
	ts->spriteO = (int *)ft_calloc(g->numSprite, sizeof(int), 0);
	ts->spriteD = (double *)ft_calloc(g->numSprite, sizeof(double), 0);
	while (++i < g->numSprite)
	{
		ts->spriteO[i] = i;
		ts->spriteD[i] = ((g->posX - g->s[i].x) * (g->posX - g->s[i].x) + (g->posY - g->s[i].y) * (g->posY - g->s[i].y));
	}
	sortSprites(ts->spriteO, ts->spriteD, g->numSprite);
}

void	sortSprites(int *order, double *dist, int n)
{
	t_pair *s;
	int		i;

	s = (t_pair *)malloc(sizeof(t_pair) * n);
	i = -1;
	while (++i < n)
	{
		s[i].first = dist[i];
		s[i].second = order[i];
	}
	sort_order(s, n);
	i = -1;
	while (++i < n)
	{
		dist[i] = s[n - i - 1].first;
		order[i] = s[n - i - 1].second;
	}
	free(s);
}

void	sort_order(t_pair *o, int n)
{
	t_pair	tmp;
	int	i;
	int	j;

	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < n - 1)
		{
			if (o[j].first > o[j + 1].first)
			{
				tmp.first = o[j].first;
				tmp.second = o[j].second;
				o[j].first = o[j + 1].first;
				o[j].second = o[j + 1].second;
				o[j + 1].first = tmp.first;
				o[j + 1].second = tmp.second;
			}
		}
	}
}

void	sprite_calc(t_game *g, t_scasting *ts, int i)
{
	ts->spriteX = g->s[ts->spriteO[i]].x - g->posX;
	ts->spriteY = g->s[ts->spriteO[i]].y - g->posY;
	ts->invDet = 1.0 / (g->planeX * g->dirY - g->dirX * g->planeY);
	ts->transformX = ts->invDet * (g->dirY * ts->spriteX - g->dirX * ts->spriteY);
	ts->transformY = ts->invDet * (-g->planeY * ts->spriteX + g->planeX * ts->spriteY);
	ts->spriteScreenX = (int)((g->win_x / 2) * (1 + ts->transformX / ts->transformY));
	ts->spriteH = (int)fabs(g->win_y / ts->transformY);
	ts->drawStartY = -ts->spriteH / 2 + g->win_y / 2;
	if (ts->drawStartY < 0)
		ts->drawStartY = 0;
	ts->drawEndY = ts->spriteH / 2 + g->win_y / 2;
	if (ts->drawEndY >= g->win_y)
		ts->drawEndY = g->win_y - 1;
	ts->spriteW = (int)fabs(g->win_y / ts->transformY);
	ts->drawStartX = -ts->spriteW / 2 + ts->spriteScreenX;
	if (ts->drawStartX < 0)
		ts->drawStartX = 0;
	ts->drawEndX = ts->spriteW / 2 + ts->spriteScreenX;
	if (ts->drawEndX >= g->win_x)
		ts->drawEndX = g->win_x - 1;
}

void	draw_sprites(t_game *g, t_scasting *ts)
{
	int	stripe;
	int	y;
	int texX;
	int	d;
	int	texY;
	int	color;

	stripe = ts->drawStartX - 1;
	while (++stripe < ts->drawEndX)
	{
		texX = (int)((256 * (stripe - (-ts->spriteW / 2 + ts->spriteScreenX)) * (int)g->sz_img[4].x /ts->spriteW) / 256);
		if (ts->transformY > 0 && stripe > 0 && stripe < g->win_x && ts->transformY < g->zBuffer[stripe])
		{
			y = ts->drawStartY - 1;
			while (++y < ts->drawEndY)
			{
				d = y * 256 - g->win_y * 128 + ts->spriteH * 128;
				texY = ((d * (int)g->sz_img[4].y) / ts->spriteH) / 256;
				color = g->texture[4][(int)g->sz_img[4].x * texY + texX];
				if ((color & 0x00FFFFFF) != 0)
					g->buf[y][stripe] = color;
			}
		}
	}
}