/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:04:43 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 18:24:19 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_casting(t_game *g)
{
	int	x;
	t_wcasting tw;

	ft_memset((char *)&tw, sizeof(t_wcasting), 0);
	x = -1;
	while (++x < g->win_x)
	{
		wall_init(x, g, &tw);
		dda(g, &tw);
		get_height(g, &tw);
		draw_one_line(x, g, &tw);
	}
}

void	wall_init(int x, t_game *g, t_wcasting *tw)
{
	tw->cameraX = 2 * x / (double)g->win_x - 1;
	tw->rayDirX = g->dirX + g->planeX * tw->cameraX;
	tw->rayDirY = g->dirY + g->planeY * tw->cameraX;
	tw->mapX = (int)g->posX;
	tw->mapY = (int)g->posY;
	tw->deltaDistX = fabs(1 / tw->rayDirX);
	tw->deltaDistY = fabs(1 / tw->rayDirY);
	tw->stepX = 1;
	tw->sideDistX = (tw->mapX + 1.0 - g->posX) * tw->deltaDistX;
	tw->stepY = 1;
	tw->sideDistY = (tw->mapY + 1.0 - g->posY) * tw->deltaDistY;
	if(tw->rayDirX < 0)
	{
		tw->stepX = -1;
		tw->sideDistX = (g->posX - tw->mapX) * tw->deltaDistX;
	}
	if(tw->rayDirY < 0)
	{
		tw->stepY = -1;
		tw->sideDistY = (g->posY - tw->mapY) * tw->deltaDistY;
	}
}

void	dda(t_game *g, t_wcasting *tw)
{
	tw->hit = 0;
	tw->side = 0;
	while (g->map[tw->mapX][tw->mapY] != 1)
	{
		if(tw->sideDistX < tw->sideDistY)
		{
			tw->sideDistX += tw->deltaDistX;
			tw->mapX += tw->stepX;
			tw->side = 0;
		}
		else
		{
			tw->sideDistY += tw->deltaDistY;
			tw->mapY += tw->stepY;
			tw->side = 1;
		}
	}
	tw->texNum = 1;
	if (tw->side == 0 && tw->stepX < 0)
		tw->texNum = 0;
	else if (tw->side == 1 && tw->stepY > 0)
		tw->texNum = 3;
	else if (tw->side == 1 && tw->stepY < 0)
		tw->texNum = 2;
}

void	get_height(t_game *g, t_wcasting *tw)
{
	if (tw->side == 0)
		tw->perpWallDist = (tw->mapX - g->posX + (1 - tw->stepX) / 2) / tw->rayDirX;
	else
		tw->perpWallDist = (tw->mapY - g->posY + (1 - tw->stepY) / 2) / tw->rayDirY;
	tw->lineHeight = (int)(g->win_y / tw->perpWallDist);
	tw->drawStart = -tw->lineHeight / 2 + g->win_y / 2;
	if (tw->drawStart < 0)
		tw->drawStart = 0;
	tw->drawEnd = tw->lineHeight / 2 + g->win_y / 2;
	if (tw->drawEnd >= g->win_y)
		tw->drawEnd = g->win_y - 1;
	if (tw->side == 0)
		tw->wallX = g->posY + tw->perpWallDist * tw->rayDirY;
	else
		tw->wallX = g->posX + tw->perpWallDist * tw->rayDirX;
	tw->wallX -= floor(tw->wallX);
	tw->texX = (int)(tw->wallX * (double)g->sz_img[tw->texNum].x); 
	if ((tw->side == 0 && tw->rayDirX > 0) || (tw->side == 1 && tw->rayDirY < 0))
		tw->texX = g->sz_img[tw->texNum].x - tw->texX - 1;
	tw->step = 1.0 * g->sz_img[tw->texNum].y / tw->lineHeight;
	tw->texPos = (tw->drawStart - g->win_y / 2 + tw->lineHeight / 2) * tw->step;
}

void	draw_one_line(int x, t_game *g, t_wcasting *tw)
{
	int	texY;
	int	color;
	int	y;

	y = tw->drawStart - 1;
	while (++y < tw->drawEnd)
	{
		texY = (int)tw->texPos & ((int)g->sz_img[tw->texNum].y - 1);
		tw->texPos += tw->step;
		color = g->texture[tw->texNum][(int)g->sz_img[tw->texNum].y * texY + tw->texX];
		if (tw->side == 1)
			color = (color >> 1) & 8355711;
		g->buf[y][x] = color;
	}
	g->zBuffer[x] = tw->perpWallDist;
}