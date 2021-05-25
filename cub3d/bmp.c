/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 01:47:33 by song-yejin        #+#    #+#             */
/*   Updated: 2021/05/24 19:14:29 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_header(unsigned char *header, int param)
{
	header[0] = (unsigned char)(param);
	header[1] = (unsigned char)(param >> 8);
	header[2] = (unsigned char)(param >> 16);
	header[3] = (unsigned char)(param >> 24);
}

void	bmp_test(t_game *g, int fd)
{
	const int sz = 3 * g->win_x * g->win_y;
	const int bmp_sz = 54 + sz;

	unsigned char  bmp_header[54] = {"BM"};
	bmp_header[10] = 54;
	bmp_header[14] = 40;
	bmp_header[26] = 1;
	bmp_header[28] = 24;
	set_header(&bmp_header[2], bmp_sz);
	set_header(&bmp_header[18], g->win_x);
	set_header(&bmp_header[22], g->win_y);
	write(fd, bmp_header, 54);
}

void	imgbmp(t_game *g, int fd)
{
	int i;
	int j;
	int x;
	int y;
	char bmp_pad = 0;

	j = -1;
	while (++j < g->win_y)
	{
		i = -1;
		while (++i < g->win_x)
		{
			x = i;
			y = g->win_y - 1 - j;
			int color = g->img.data[x + y * g->win_x];
			write(fd, &color, 3);
		}
		i = -1;
		while (++i < (4 - ((g->win_x * 3) % 4)) % 4)
			write(fd, &bmp_pad, 1);
	}
}

void	save_bmp(t_game *g)
{
	int		fd;
	const char	*file_name = "cub.bmp";

	main_loop(g);
	if (g->save == 0)
		return;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (!fd)
		ft_exit("ERROR: BMP");
	bmp_test(g, fd);
	imgbmp(g, fd);
	close(fd);
	printf("cub.bmp created\n");
	g->save = 0;
}