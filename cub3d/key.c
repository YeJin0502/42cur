/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:46:33 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 18:18:53 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_update(t_game *g)
{
	if (g->key.w)
	{
		if (!g->map[(int)(g->posX + g->dirX * 0.05)][(int)(g->posY)])
			g->posX += g->dirX * 0.05;
		if (!g->map[(int)(g->posX)][(int)(g->posY + g->dirY * 0.05)])
			g->posY += g->dirY * 0.05;
	}
	if (g->key.s)
	{
		if (!g->map[(int)(g->posX - g->dirX * 0.05)][(int)(g->posY)])
			g->posX -= g->dirX * 0.05;
		if (!g->map[(int)(g->posX)][(int)(g->posY - g->dirY * 0.05)])
			g->posY -= g->dirY * 0.05;
	}
	if (g->key.d)
		turn(g, -0.05);
	if (g->key.a)
		turn(g, 0.05);
}

void	turn(t_game *g, double rot)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = g->dirX;
	g->dirX = g->dirX * cos(rot) - g->dirY * sin(rot);
	g->dirY = oldDirX * sin(rot) + g->dirY * cos(rot);
	oldPlaneX = g->planeX;
	g->planeX = g->planeX * cos(rot) - g->planeY * sin(rot);
	g->planeY = oldPlaneX * sin(rot) + g->planeY * cos(rot);
}

int	key_press(int key, t_game *g)
{
	if(key == K_ESC)
		exit(0);
	else if (key == K_W)
		g->key.w = 1;
	else if (key == K_A)
		g->key.a = 1;
	else if (key == K_S)
		g->key.s = 1;
	else if (key == K_D)
		g->key.d = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == K_W)
		g->key.w = 0;
	else if (key == K_A)
		g->key.a = 0;
	else if (key == K_S)
		g->key.s = 0;
	else if (key == K_D)
		g->key.d = 0;
	return (0);
}

int		close_mouse()
{
	exit(0);
}