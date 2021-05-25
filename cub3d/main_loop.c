/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:41:40 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/22 18:42:51 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_game *g)
{
	calc(g);
	draw(g);
	key_update(g);
	return (0);
}

void	calc(t_game *g)
{
	floor_color(g);
	wall_casting(g);
	sprite_casting(g);
}

void	floor_color(t_game *g)
{
	int	y;
	int	x;
	int	color;

	y = g->win_y / 2;
	while (++y < g->win_y)
	{
		x = -1;
		while (++x < g->win_x)
		{
			color = g->c_rgb;
			g->buf[y][x] = color;
			color = g->f_rgb;
			g->buf[g->win_y - y - 1][x] = color;
		}
	}
}

void	draw(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < g->win_y)
	{
		x = -1;
		while (++x < g->win_x)
		{
			g->img.data[y * g->win_x + x] = g->buf[y][x];
		}
	}
	if (g->save == 0)
		mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}
